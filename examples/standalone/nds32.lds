/*
 * Copyright (C) 2011 Andes Technology Corporation
 * Shawn Lin, Andes Technology Corporation <nobuhiro@andestech.com>
 * Macpaul Lin, Andes Technology Corporation <macpaul@andestech.com>
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

OUTPUT_FORMAT("elf32-nds32", "elf32-nds32", "elf32-nds32")
OUTPUT_ARCH(nds32)
ENTRY(_start)
SECTIONS
{
	. = ALIGN(4);
	.text :
	{
		*(.text)
	}

	. = ALIGN(4);
	.data : { *(.data) }

	. = ALIGN(4);

	.got : {
		__got_start = .;
		*(.got)
		__got_end = .;
	}

	. = ALIGN(4);
	__bss_start = .;
	.bss : { *(.bss) }
	__bss_end = .;

	. = ALIGN(4);
	.rela.text : { *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*) }

	_end = .;
}
