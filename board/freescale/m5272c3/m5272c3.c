/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copyright (C) 2012 Freescale Semiconductor, Inc. All Rights Reserved.
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
#include <asm/immap.h>
#include <asm/io.h>


int checkboard (void) {
	puts ("Board: ");
	puts ("Freescale MCF5272C3 EVB\n");
	return 0;
	};

phys_size_t initdram (int board_type) {
	sdramctrl_t * sdp = (sdramctrl_t *)(MMAP_SDRAM);

	out_be16(&sdp->sdram_sdtr, 0xf539);
	out_be16(&sdp->sdram_sdcr, 0x4211);

	/* Dummy write to start SDRAM */
	*((volatile unsigned long *)0) = 0;

	return CONFIG_SYS_SDRAM_SIZE * 1024 * 1024;
	};

int testdram (void) {
	/* TODO: XXX XXX XXX */
	printf ("DRAM test not implemented!\n");

	return (0);
}
