/*
 * (C) Copyright 2008
 * Matthias Fuchs, esd gmbh, matthias.fuchs@esd-electronics.com
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <asm-offsets.h>
#include <ppc_asm.tmpl>
#include <asm/mmu.h>
#include <config.h>

/*
 * TLB TABLE
 *
 * This table is used by the cpu boot code to setup the initial tlb
 * entries. Rather than make broad assumptions in the cpu source tree,
 * this table lets each board set things up however they like.
 *
 * Pointer to the table is returned in r1
 */
    .section .bootpg,"ax"
    .globl tlbtab

tlbtab:
	tlbtab_start

	/*
	 * BOOT_CS (FLASH) must be first. Before relocation SA_I can be off to use the
	 * speed up boot process. It is patched after relocation to enable SA_I
	 */
	tlbentry( CONFIG_SYS_BOOT_BASE_ADDR, SZ_256M, CONFIG_SYS_BOOT_BASE_ADDR, 1, AC_RWX | SA_G )

#ifdef CONFIG_SYS_INIT_RAM_DCACHE
	/* TLB-entry for init-ram in dcache (SA_I must be turned off!) */
	tlbentry( CONFIG_SYS_INIT_RAM_ADDR, SZ_64K, CONFIG_SYS_INIT_RAM_ADDR, 0, AC_RWX | SA_G )
#endif

	/* TLB-entry for PCI Memory */
	tlbentry( CONFIG_SYS_PCI_MEMBASE, SZ_256M,  CONFIG_SYS_PCI_MEMBASE, 1, AC_RW | SA_IG )
	tlbentry( CONFIG_SYS_PCI_MEMBASE1, SZ_256M, CONFIG_SYS_PCI_MEMBASE1, 1, AC_RW | SA_IG )
	tlbentry( CONFIG_SYS_PCI_MEMBASE2, SZ_256M, CONFIG_SYS_PCI_MEMBASE2, 1, AC_RW | SA_IG )
	tlbentry( CONFIG_SYS_PCI_MEMBASE3, SZ_256M, CONFIG_SYS_PCI_MEMBASE3, 1, AC_RW | SA_IG )

	/* TLB-entry for PCI IO */
	tlbentry( CONFIG_SYS_PCI_IOBASE, SZ_64K, CONFIG_SYS_PCI_IOBASE, 1, AC_RW | SA_IG )

	/* TLB-entries for EBC:	 CPLD, DUMEM, DUIO */
	tlbentry( CONFIG_SYS_CPLD_BASE, SZ_1K, CONFIG_SYS_CPLD_BASE, 1, AC_RWX | SA_IG )
	tlbentry( CONFIG_SYS_DUMEM_BASE, SZ_1M, CONFIG_SYS_DUMEM_BASE, 1, AC_RWX | SA_IG )
	tlbentry( CONFIG_SYS_DUIO_BASE, SZ_64K, CONFIG_SYS_DUIO_BASE, 1, AC_RWX | SA_IG )

	/* TLB-entry for NAND */
	tlbentry( CONFIG_SYS_NAND0_ADDR, SZ_1K, CONFIG_SYS_NAND0_ADDR, 1, AC_RWX | SA_IG )
	tlbentry( CONFIG_SYS_NAND1_ADDR, SZ_1K, CONFIG_SYS_NAND1_ADDR, 1, AC_RWX | SA_IG )

	/* TLB-entry for Internal Registers & OCM */
	tlbentry( 0xe0000000, SZ_16M, 0xe0000000, 0,  AC_RWX | SA_I )

	/* TLB-entry PCI registers */
	tlbentry( 0xEEC00000, SZ_1K, 0xEEC00000, 1,  AC_RWX | SA_IG )

	/* TLB-entry for peripherals */
	tlbentry( 0xEF000000, SZ_16M, 0xEF000000, 1, AC_RWX | SA_IG)

	tlbtab_end
