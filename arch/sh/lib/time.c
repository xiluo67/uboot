/*
 * (C) Copyright 2009
 * Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 *
 * (C) Copyright 2007-2012
 * Nobobuhiro Iwamatsu <iwamatsu@nigauri.org>
 *
 * (C) Copyright 2003
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
#include <div64.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <sh_tmu.h>

static struct tmu_regs *tmu = (struct tmu_regs *)TMU_BASE;

static u16 bit;
static unsigned long last_tcnt;
static unsigned long long overflow_ticks;

unsigned long get_tbclk(void)
{
	return get_tmu0_clk_rate() >> ((bit + 1) * 2);
}

static inline unsigned long long tick_to_time(unsigned long long tick)
{
	tick *= CONFIG_SYS_HZ;
	do_div(tick, get_tbclk());

	return tick;
}

static inline unsigned long long usec_to_tick(unsigned long long usec)
{
	usec *= get_tbclk();
	do_div(usec, 1000000);

	return usec;
}

static void tmu_timer_start(unsigned int timer)
{
	if (timer > 2)
		return;
	writeb(readb(&tmu->tstr) | (1 << timer), &tmu->tstr);
}

static void tmu_timer_stop(unsigned int timer)
{
	if (timer > 2)
		return;
	writeb(readb(&tmu->tstr) & ~(1 << timer), &tmu->tstr);
}

int timer_init(void)
{
	bit = (ffs(CONFIG_SYS_TMU_CLK_DIV) >> 1) - 1;
	writew(readw(&tmu->tcr0) | bit, &tmu->tcr0);

	tmu_timer_stop(0);
	tmu_timer_start(0);

	last_tcnt = 0;
	overflow_ticks = 0;

	return 0;
}

unsigned long long get_ticks(void)
{
	unsigned long tcnt = 0 - readl(&tmu->tcnt0);

	if (last_tcnt > tcnt) /* overflow */
		overflow_ticks++;
	last_tcnt = tcnt;

	return (overflow_ticks << 32) | tcnt;
}

void __udelay(unsigned long usec)
{
	unsigned long long tmp;
	ulong tmo;

	tmo = usec_to_tick(usec);
	tmp = get_ticks() + tmo;	/* get current timestamp */

	while (get_ticks() < tmp)	/* loop till event */
		 /*NOP*/;
}

unsigned long get_timer(unsigned long base)
{
	/* return msec */
	return tick_to_time(get_ticks()) - base;
}

void set_timer(unsigned long t)
{
	writel((0 - t), &tmu->tcnt0);
}

void reset_timer(void)
{
	tmu_timer_stop(0);
	set_timer(0);
	tmu_timer_start(0);
}
