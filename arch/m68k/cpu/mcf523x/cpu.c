/*
 *
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copyright (C) 2004-2007, 2012 Freescale Semiconductor, Inc.
 * TsiChung Liew (Tsi-Chung.Liew@freescale.com)
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
#include <watchdog.h>
#include <command.h>
#include <netdev.h>

#include <asm/immap.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ccm_t *ccm = (ccm_t *) MMAP_CCM;

	out_8(&ccm->rcr, CCM_RCR_SOFTRST);
	/* we don't return! */
	return 0;
}

int checkcpu(void)
{
	ccm_t *ccm = (ccm_t *) MMAP_CCM;
	u16 msk;
	u16 id = 0;
	u8 ver;

	puts("CPU:   ");
	msk = (in_be16(&ccm->cir) >> 6);
	ver = (in_be16(&ccm->cir) & 0x003f);
	switch (msk) {
	case 0x31:
		id = 5235;
		break;
	}

	if (id) {
		char buf1[32], buf2[32];

		printf("Freescale MCF%d (Mask:%01x Version:%x)\n", id, msk,
		       ver);
		printf("       CPU CLK %s MHz BUS CLK %s MHz\n",
		       strmhz(buf1, gd->cpu_clk),
		       strmhz(buf2, gd->bus_clk));
	}

	return 0;
};

#if defined(CONFIG_WATCHDOG)
/* Called by macro WATCHDOG_RESET */
void watchdog_reset(void)
{
	wdog_t *wdp = (wdog_t *) (MMAP_WDOG);

	/* Count register */
	out_be16(&wdp->sr, 0x5555);
	asm("nop");
	out_be16(&wdp->sr, 0xaaaa);
}

int watchdog_disable(void)
{
	wdog_t *wdp = (wdog_t *) (MMAP_WDOG);

	/* UserManual, once the wdog is disabled, wdog cannot be re-enabled */
	/* halted watchdog timer */
	setbits_be16(&wdp->cr, WTM_WCR_HALTED);

	puts("WATCHDOG:disabled\n");
	return (0);
}

int watchdog_init(void)
{
	wdog_t *wdp = (wdog_t *) (MMAP_WDOG);
	u32 wdog_module = 0;

	/* set timeout and enable watchdog */
	wdog_module = ((CONFIG_SYS_CLK / CONFIG_SYS_HZ) * CONFIG_WATCHDOG_TIMEOUT);
	wdog_module |= (wdog_module / 8192);
	out_be16(&wdp->mr, wdog_module);

	out_be16(&wdp->cr, WTM_WCR_EN);
	puts("WATCHDOG:enabled\n");

	return (0);
}
#endif				/* CONFIG_WATCHDOG */

#if defined(CONFIG_MCFFEC)
/* Default initializations for MCFFEC controllers.  To override,
 * create a board-specific function called:
 * 	int board_eth_init(bd_t *bis)
 */

int cpu_eth_init(bd_t *bis)
{
	return mcffec_initialize(bis);
}
#endif
