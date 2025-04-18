/*
 * (C) Copyright 2012 Nobuhiro Iwamatsu <nobuhiro.iwamatsu.yj@renesas.com>
 * (C) Copyright 2012 Renesas Solutions Corp.
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
#include <asm/io.h>
#include <asm/arch-armv7/globaltimer.h>
#include <asm/arch/rmobile.h>

static struct globaltimer *global_timer = \
		(struct globaltimer *)GLOBAL_TIMER_BASE_ADDR;

#define CLK2MHZ(clk)	(clk / 1000 / 1000)
static u64 get_cpu_global_timer(void)
{
	u32 low, high;
	u64 timer;

	u32 old = readl(&global_timer->cnt_h);
	while (1) {
		low = readl(&global_timer->cnt_l);
		high = readl(&global_timer->cnt_h);
		if (old == high)
			break;
		else
			old = high;
	}

	timer = high;
	return (u64)((timer << 32) | low);
}

static u64 get_time_us(void)
{
	u64 timer = get_cpu_global_timer();

	timer = ((timer << 2) + (CLK2MHZ(CONFIG_SYS_CPU_CLK) >> 1));
	timer /= (u64)CLK2MHZ(CONFIG_SYS_CPU_CLK);
	return timer;
}

static ulong get_time_ms(void)
{
	return (ulong)(get_time_us() / 1000);
}

int timer_init(void)
{
	writel(0x01, &global_timer->ctl);
	return 0;
}

void __udelay(unsigned long usec)
{
	u64 start, current;
	u64 wait;

	start = get_cpu_global_timer();
	wait = (u64)((usec * CLK2MHZ(CONFIG_SYS_CPU_CLK)) >> 2);
	do {
		current = get_cpu_global_timer();
	} while ((current - start) < wait);
}

ulong get_timer(ulong base)
{
	return get_time_ms() - base;
}

unsigned long long get_ticks(void)
{
	return get_cpu_global_timer();
}

ulong get_tbclk(void)
{
	return (ulong)(CONFIG_SYS_CPU_CLK >> 2);
}
