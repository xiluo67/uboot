/*
 * (C) Copyright 2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de
 *
 * Copyright 2009 Freescale Semiconductor, Inc.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "config.h"	/* CONFIG_BOARDDIR */

OUTPUT_ARCH(powerpc)
SECTIONS
{
	. = 0xfff00000;
	.text : {
		*(.text*)
	}
	_etext = .;

	.reloc : {
		_GOT2_TABLE_ = .;
		KEEP(*(.got2))
		KEEP(*(.got))
		PROVIDE(_GLOBAL_OFFSET_TABLE_ = . + 4);
		_FIXUP_TABLE_ = .;
		KEEP(*(.fixup))
	}
	__got2_entries = ((_GLOBAL_OFFSET_TABLE_ - _GOT2_TABLE_) >> 2) - 1;
	__fixup_entries = (. - _FIXUP_TABLE_) >> 2;

	. = ALIGN(8);
	.data : {
		*(.rodata*)
		*(.data*)
		*(.sdata*)
	}
	_edata  =  .;

	. = ALIGN(8);
	__init_begin = .;
	__init_end = .;
#if defined(CONFIG_FSL_IFC) /* Restrict bootpg at 4K boundry for IFC */
	.bootpg ADDR(.text) + 0x1000 :
	{
		start.o	(.bootpg)
	}
#define RESET_VECTOR_OFFSET 0x1ffc /* IFC has 8K sram */
#elif defined(CONFIG_FSL_ELBC)
#define RESET_VECTOR_OFFSET 0xffc /* LBC has 4k sram */
#else
#error unknown NAND controller
#endif
	.resetvec ADDR(.text) + RESET_VECTOR_OFFSET : {
		KEEP(*(.resetvec))
	} = 0xffff

	__bss_start = .;
	.bss : {
		*(.sbss*)
		*(.bss*)
	}
	__bss_end__ = .;
}
ASSERT(__init_end <= (0xfff00000 + RESET_VECTOR_OFFSET), "NAND bootstrap too big");
