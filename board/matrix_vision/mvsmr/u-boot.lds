/*
 * (C) Copyright 2003-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 * (C) Copyright 2010
 * André Schwarz, Matrix Vision GmbH, as@matrix-vision.de
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

OUTPUT_ARCH(powerpc)

SECTIONS
{
  /* Read-only sections, merged into text segment: */
  .text      :
  {
    /* WARNING - the following is hand-optimized to fit within  */
    /* the first two sectors (=8KB) of our S29GL flash chip */
    arch/powerpc/cpu/mpc5xxx/start.o	(.text*)
    arch/powerpc/cpu/mpc5xxx/traps.o	(.text*)
    board/matrix_vision/common/libmatrix_vision.o (.text*)

    /* This is only needed to force failure if size of above code will ever */
    /* increase and grow into reserved space. */
    . = ALIGN(0x2000);	/* location counter has to be 0x4000 now */
    . += 0x4000;	/* ->0x8000, i.e. move to env_offset */

    . = env_offset;	/* ld error as soon as above ALIGN misplaces lc */
    common/env_embedded.o        (.ppcenv)

    *(.text*)
    . = ALIGN(16);
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
  }

  /* Read-write section, merged into data segment: */
  . = (. + 0x0FFF) & 0xFFFFF000;
  _erotext = .;
  PROVIDE (erotext = .);
  .reloc   :
  {
    _GOT2_TABLE_ = .;
    KEEP(*(.got2))
    KEEP(*(.got))
    PROVIDE(_GLOBAL_OFFSET_TABLE_ = . + 4);
    _FIXUP_TABLE_ = .;
    KEEP(*(.fixup))
  }
  __got2_entries = ((_GLOBAL_OFFSET_TABLE_ - _GOT2_TABLE_) >> 2) - 1;
  __fixup_entries = (. - _FIXUP_TABLE_) >> 2;

  .data    :
  {
    *(.data*)
    *(.sdata*)
  }
  _edata  =  .;
  PROVIDE (edata = .);

  . = .;
  __u_boot_cmd_start = .;
  .u_boot_cmd : { *(.u_boot_cmd) }
  __u_boot_cmd_end = .;


  . = .;
  __start___ex_table = .;
  __ex_table : { *(__ex_table) }
  __stop___ex_table = .;

  . = ALIGN(4096);
  __init_begin = .;
  .text.init : { *(.text.init) }
  .data.init : { *(.data.init) }
  . = ALIGN(4096);
  __init_end = .;

  __bss_start = .;
  .bss (NOLOAD)       :
  {
   *(.bss*)
   *(.sbss*)
   . = ALIGN(4);
  }
  __bss_end__ = . ;
  PROVIDE (end = .);
}
