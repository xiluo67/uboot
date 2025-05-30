/*
 * (C) Copyright 2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <stdio_dev.h>
#include <net.h>

DECLARE_GLOBAL_DATA_PTR;

#ifndef CONFIG_NETCONSOLE_BUFFER_SIZE
#define CONFIG_NETCONSOLE_BUFFER_SIZE 512
#endif

static char input_buffer[CONFIG_NETCONSOLE_BUFFER_SIZE];
static int input_size; /* char count in input buffer */
static int input_offset; /* offset to valid chars in input buffer */
static int input_recursion;
static int output_recursion;
static int net_timeout;
static uchar nc_ether[6]; /* server enet address */
static IPaddr_t nc_ip; /* server ip */
static short nc_out_port; /* target output port */
static short nc_in_port; /* source input port */
static const char *output_packet; /* used by first send udp */
static int output_packet_len;
/*
 * Start with a default last protocol.
 * We are only interested in NETCONS or not.
 */
enum proto_t net_loop_last_protocol = BOOTP;

static void nc_wait_arp_handler(uchar *pkt, unsigned dest,
				 IPaddr_t sip, unsigned src,
				 unsigned len)
{
	net_set_state(NETLOOP_SUCCESS); /* got arp reply - quit net loop */
}

static void nc_handler(uchar *pkt, unsigned dest, IPaddr_t sip, unsigned src,
			unsigned len)
{
	if (input_size)
		net_set_state(NETLOOP_SUCCESS); /* got input - quit net loop */
}

static void nc_timeout(void)
{
	net_set_state(NETLOOP_SUCCESS);
}

static int is_broadcast(IPaddr_t ip)
{
	static IPaddr_t netmask;
	static IPaddr_t our_ip;
	static int env_changed_id;
	int env_id = get_env_id();

	/* update only when the environment has changed */
	if (env_changed_id != env_id) {
		netmask = getenv_IPaddr("netmask");
		our_ip = getenv_IPaddr("ipaddr");

		env_changed_id = env_id;
	}

	return (ip == ~0 ||				/* 255.255.255.255 */
	    ((netmask & our_ip) == (netmask & ip) &&	/* on the same net */
	    (netmask | ip) == ~0));		/* broadcast to our net */
}

static int refresh_settings_from_env(void)
{
	const char *p;
	static int env_changed_id;
	int env_id = get_env_id();

	/* update only when the environment has changed */
	if (env_changed_id != env_id) {
		if (getenv("ncip")) {
			nc_ip = getenv_IPaddr("ncip");
			if (!nc_ip)
				return -1;	/* ncip is 0.0.0.0 */
			p = strchr(getenv("ncip"), ':');
			if (p != NULL) {
				nc_out_port = simple_strtoul(p + 1, NULL, 10);
				nc_in_port = nc_out_port;
			}
		} else
			nc_ip = ~0; /* ncip is not set, so broadcast */

		p = getenv("ncoutport");
		if (p != NULL)
			nc_out_port = simple_strtoul(p, NULL, 10);
		p = getenv("ncinport");
		if (p != NULL)
			nc_in_port = simple_strtoul(p, NULL, 10);

		if (is_broadcast(nc_ip))
			/* broadcast MAC address */
			memset(nc_ether, 0xff, sizeof(nc_ether));
		else
			/* force arp request */
			memset(nc_ether, 0, sizeof(nc_ether));
	}
	return 0;
}

/**
 * Called from NetLoop in net/net.c before each packet
 */
void NcStart(void)
{
	refresh_settings_from_env();
	if (!output_packet_len || memcmp(nc_ether, NetEtherNullAddr, 6)) {
		/* going to check for input packet */
		net_set_udp_handler(nc_handler);
		NetSetTimeout(net_timeout, nc_timeout);
	} else {
		/* send arp request */
		uchar *pkt;
		net_set_arp_handler(nc_wait_arp_handler);
		pkt = (uchar *)NetTxPacket + NetEthHdrSize() + IP_UDP_HDR_SIZE;
		memcpy(pkt, output_packet, output_packet_len);
		NetSendUDPPacket(nc_ether, nc_ip, nc_out_port, nc_in_port,
			output_packet_len);
	}
}

int nc_input_packet(uchar *pkt, IPaddr_t src_ip, unsigned dest_port,
	unsigned src_port, unsigned len)
{
	int end, chunk;

	if (dest_port != nc_in_port || !len)
		return 0; /* not for us */

	if (src_ip != nc_ip && !is_broadcast(nc_ip))
		return 0; /* not from our client */

	debug_cond(DEBUG_DEV_PKT, "input: \"%*.*s\"\n", len, len, pkt);

	if (input_size == sizeof(input_buffer))
		return 1; /* no space */
	if (len > sizeof(input_buffer) - input_size)
		len = sizeof(input_buffer) - input_size;

	end = input_offset + input_size;
	if (end > sizeof(input_buffer))
		end -= sizeof(input_buffer);

	chunk = len;
	if (end + len > sizeof(input_buffer)) {
		chunk = sizeof(input_buffer) - end;
		memcpy(input_buffer, pkt + chunk, len - chunk);
	}
	memcpy(input_buffer + end, pkt, chunk);

	input_size += len;

	return 1;
}

static void nc_send_packet(const char *buf, int len)
{
	struct eth_device *eth;
	int inited = 0;
	uchar *pkt;
	uchar *ether;
	IPaddr_t ip;

	debug_cond(DEBUG_DEV_PKT, "output: \"%*.*s\"\n", len, len, buf);

	eth = eth_get_dev();
	if (eth == NULL)
		return;

	if (!memcmp(nc_ether, NetEtherNullAddr, 6)) {
		if (eth->state == ETH_STATE_ACTIVE)
			return;	/* inside net loop */
		output_packet = buf;
		output_packet_len = len;
		NetLoop(NETCONS); /* wait for arp reply and send packet */
		output_packet_len = 0;
		return;
	}

	if (eth->state != ETH_STATE_ACTIVE) {
		if (eth_is_on_demand_init()) {
			if (eth_init(gd->bd) < 0)
				return;
			eth_set_last_protocol(NETCONS);
		} else
			eth_init_state_only(gd->bd);

		inited = 1;
	}
	pkt = (uchar *)NetTxPacket + NetEthHdrSize() + IP_UDP_HDR_SIZE;
	memcpy(pkt, buf, len);
	ether = nc_ether;
	ip = nc_ip;
	NetSendUDPPacket(ether, ip, nc_out_port, nc_in_port, len);

	if (inited) {
		if (eth_is_on_demand_init())
			eth_halt();
		else
			eth_halt_state_only();
	}
}

static int nc_start(void)
{
	int retval;

	nc_out_port = 6666; /* default port */
	nc_in_port = nc_out_port;

	retval = refresh_settings_from_env();
	if (retval != 0)
		return retval;

	/*
	 * Initialize the static IP settings and buffer pointers
	 * incase we call NetSendUDPPacket before NetLoop
	 */
	net_init();

	return 0;
}

static void nc_putc(char c)
{
	if (output_recursion)
		return;
	output_recursion = 1;

	nc_send_packet(&c, 1);

	output_recursion = 0;
}

static void nc_puts(const char *s)
{
	int len;

	if (output_recursion)
		return;
	output_recursion = 1;

	len = strlen(s);
	while (len) {
		int send_len = min(len, sizeof(input_buffer));
		nc_send_packet(s, send_len);
		len -= send_len;
		s += send_len;
	}

	output_recursion = 0;
}

static int nc_getc(void)
{
	uchar c;

	input_recursion = 1;

	net_timeout = 0;	/* no timeout */
	while (!input_size)
		NetLoop(NETCONS);

	input_recursion = 0;

	c = input_buffer[input_offset++];

	if (input_offset >= sizeof(input_buffer))
		input_offset -= sizeof(input_buffer);
	input_size--;

	return c;
}

static int nc_tstc(void)
{
	struct eth_device *eth;

	if (input_recursion)
		return 0;

	if (input_size)
		return 1;

	eth = eth_get_dev();
	if (eth && eth->state == ETH_STATE_ACTIVE)
		return 0;	/* inside net loop */

	input_recursion = 1;

	net_timeout = 1;
	NetLoop(NETCONS);	/* kind of poll */

	input_recursion = 0;

	return input_size != 0;
}

int drv_nc_init(void)
{
	struct stdio_dev dev;
	int rc;

	memset(&dev, 0, sizeof(dev));

	strcpy(dev.name, "nc");
	dev.flags = DEV_FLAGS_OUTPUT | DEV_FLAGS_INPUT | DEV_FLAGS_SYSTEM;
	dev.start = nc_start;
	dev.putc = nc_putc;
	dev.puts = nc_puts;
	dev.getc = nc_getc;
	dev.tstc = nc_tstc;

	rc = stdio_register(&dev);

	return (rc == 0) ? 1 : rc;
}
