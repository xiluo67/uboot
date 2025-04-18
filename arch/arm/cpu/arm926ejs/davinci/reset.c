/*
 *  Processor reset using WDT.
 *
 * Copyright (C) 2012 Dmitry Bondar <bond@inmys.ru>
 * Copyright (C) 2007 Sergey Kubushyn <ksi@koi8.net>
 *
 * This file is released under the terms of GPL v2 and any later version.
 * See the file COPYING in the root directory of the source tree for details.
*/

#include <common.h>
#include <asm/io.h>
#include <asm/arch/timer_defs.h>
#include <asm/arch/hardware.h>

void reset_cpu(unsigned long a)
{
	struct davinci_timer *const wdttimer =
		(struct davinci_timer *)DAVINCI_TIMER1_BASE;
	writel(0x08, &wdttimer->tgcr);
	writel(readl(&wdttimer->tgcr) | 0x03, &wdttimer->tgcr);
	writel(0, &wdttimer->tim12);
	writel(0, &wdttimer->tim34);
	writel(0, &wdttimer->prd12);
	writel(0, &wdttimer->prd34);
	writel(readl(&wdttimer->tcr) | 0x40, &wdttimer->tcr);
	writel(readl(&wdttimer->wdtcr) | 0x4000, &wdttimer->wdtcr);
	writel(0xa5c64000, &wdttimer->wdtcr);
	writel(0xda7e4000, &wdttimer->wdtcr);
	writel(0x4000, &wdttimer->wdtcr);
	while (1)
		/*nothing*/;
}
