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

.text

#include <common.h>
#include <config.h>

#include <asm/macro.h>
#include <generated/asm-offsets.h>

/*
 * parameters for the SDRAM controller
 */
#define SDMC_TP1_A		(CONFIG_FTSDMC021_BASE + FTSDMC021_TP1)
#define SDMC_TP2_A		(CONFIG_FTSDMC021_BASE + FTSDMC021_TP2)
#define SDMC_CR1_A		(CONFIG_FTSDMC021_BASE + FTSDMC021_CR1)
#define SDMC_CR2_A		(CONFIG_FTSDMC021_BASE + FTSDMC021_CR2)
#define SDMC_B0_BSR_A		(CONFIG_FTSDMC021_BASE + FTSDMC021_BANK0_BSR)

#define SDMC_TP1_D		CONFIG_SYS_FTSDMC021_TP1
#define SDMC_TP2_D		CONFIG_SYS_FTSDMC021_TP2
#define SDMC_CR1_D		CONFIG_SYS_FTSDMC021_CR1
#define SDMC_CR2_D		CONFIG_SYS_FTSDMC021_CR2

#define SDMC_B0_BSR_D		CONFIG_SYS_FTSDMC021_BANK0_BSR

/*
 * parameters for the static memory controller
 */
#define SMC_BANK0_CR_A		(CONFIG_FTSMC020_BASE + FTSMC020_BANK0_CR)
#define SMC_BANK0_TPR_A		(CONFIG_FTSMC020_BASE + FTSMC020_BANK0_TPR)

#define SMC_BANK0_CR_D		FTSMC020_BANK0_LOWLV_CONFIG
#define SMC_BANK0_TPR_D		FTSMC020_BANK0_LOWLV_TIMING

/*
 * parameters for the ahbc controller
 */
#define AHBC_CR_A		(CONFIG_FTAHBC020S_BASE + FTAHBC020S_CR)
#define AHBC_BSR6_A	(CONFIG_FTAHBC020S_BASE + FTAHBC020S_SLAVE_BSR_6)

#define AHBC_BSR6_D		CONFIG_SYS_FTAHBC020S_SLAVE_BSR_6

/*
 * parameters for the pmu controoler
 */
#define PMU_PDLLCR0_A		(CONFIG_FTPMU010_BASE + FTPMU010_PDLLCR0)

/*
 * numeric 7 segment display
 */
.macro	led, num
	write32	CONFIG_DEBUG_LED, \num
.endm

/*
 * Waiting for SDRAM to set up
 */
.macro	wait_sdram
	li	$r0, CONFIG_FTSDMC021_BASE
1:
	lwi	$r1, [$r0+FTSDMC021_CR2]
	bnez	$r1, 1b
.endm

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
.globl	lowlevel_init
lowlevel_init:
	move	$r10, $lp

	led	0x0
	jal	mem_init

	led	0x10
	jal	remap

	led	0x20
	ret	$r10

mem_init:
	move	$r11, $lp

	/*
	 * mem_init:
	 *	There are 2 bank connected to FTSMC020 on AG101
	 *	BANK0: FLASH/ROM (SW5, J16), BANK1: OnBoard SDRAM.
	 *	we need to set onboard SDRAM before remap and relocation.
	 */
	led	0x01
	write32	SMC_BANK0_CR_A, SMC_BANK0_CR_D			! 0x10000052
	write32	SMC_BANK0_TPR_A, SMC_BANK0_TPR_D		! 0x00151151

	/*
	 * config AHB Controller
	 */
	led	0x02
	write32	AHBC_BSR6_A, AHBC_BSR6_D

	/*
	 * config PMU controller
	 */
	/* ftpmu010_dlldis_disable, must do it in lowleve_init */
	led	0x03
	setbf32	PMU_PDLLCR0_A, FTPMU010_PDLLCR0_DLLDIS		! 0x00010000

	/*
	 * config SDRAM controller
	 */
	led	0x04
	write32	SDMC_TP1_A, SDMC_TP1_D				! 0x00011312
	led	0x05
	write32	SDMC_TP2_A, SDMC_TP2_D				! 0x00480180
	led	0x06
	write32	SDMC_CR1_A, SDMC_CR1_D				! 0x00002326

	led	0x07
	write32	SDMC_CR2_A, FTSDMC021_CR2_IPREC			! 0x00000010
	wait_sdram

	led	0x08
	write32	SDMC_CR2_A, FTSDMC021_CR2_ISMR			! 0x00000004
	wait_sdram

	led	0x09
	write32	SDMC_CR2_A, FTSDMC021_CR2_IREF			! 0x00000008
	wait_sdram

	led	0x0a
	move	$lp, $r11
	ret

remap:
	move	$r11, $lp
#ifdef __NDS32_N1213_43U1H__	/* NDS32 V0 ISA - AG101 Only */
	bal	2f
relo_base:
	move	$r0, $lp
#else
relo_base:
	mfusr	$r0, $pc
#endif /* __NDS32_N1213_43U1H__ */

	/*
	 * Remapping
	 */
	led	0x1a
	write32	SDMC_B0_BSR_A, SDMC_B0_BSR_D		! 0x00001100

	/* clear empty BSR registers */
	led	0x1b
	li	$r4, CONFIG_FTSDMC021_BASE
	li	$r5, 0x0
	swi	$r5, [$r4 + FTSDMC021_BANK1_BSR]
	swi	$r5, [$r4 + FTSDMC021_BANK2_BSR]
	swi	$r5, [$r4 + FTSDMC021_BANK3_BSR]

#ifdef CONFIG_MEM_REMAP
	/*
	 * Copy ROM code to SDRAM base for memory remap layout.
	 * This is not the real relocation, the real relocation is the function
	 * relocate_code() is start.S which supports the systems is memory
	 * remapped or not.
	 */
	/*
	 * Doing memory remap is essential for preparing some non-OS or RTOS
	 * applications.
	 *
	 * This is also a must on ADP-AG101 board.
	 * The reason is because the ROM/FLASH circuit on PCB board.
	 * AG101-A0 board has 2 jumpers MA17 and SW5 to configure which
	 * ROM/FLASH is used to boot.
	 *
	 * When SW5 = "0101", MA17 = LO, the ROM is connected to BANK0,
	 * and the FLASH is connected to BANK1.
	 * When SW5 = "1010", MA17 = HI, the ROM is disabled (still at BANK0),
	 * and the FLASH is connected to BANK0.
	 * It will occur problem when doing flash probing if the flash is at
	 * BANK0 (0x00000000) while memory remapping was skipped.
	 *
	 * Other board like ADP-AG101P may not enable this since there is only
	 * a FLASH connected to bank0.
	 */
	led	0x11
	li	$r4, PHYS_SDRAM_0_AT_INIT		/* 0x10000000 */
	li	$r5, 0x0
	la	$r1, relo_base				/* get $pc or $lp */
	sub	$r2, $r0, $r1
	sethi	$r6, hi20(_end)
	ori	$r6, $r6, lo12(_end)
	add	$r6, $r6, $r2
1:
	lwi.p	$r7, [$r5], #4
	swi.p	$r7, [$r4], #4
	blt	$r5, $r6, 1b

	/* set remap bit */
	/*
	 * MEM remap bit is operational
	 * - use it to map writeable memory at 0x00000000, in place of flash
	 * - before remap: flash/rom 0x00000000, sdram: 0x10000000-0x4fffffff
	 * - after  remap: flash/rom 0x80000000, sdram: 0x00000000
	 */
	led	0x1c
	setbf15	AHBC_CR_A, FTAHBC020S_CR_REMAP		! 0x1

#endif /* #ifdef CONFIG_MEM_REMAP */
	move	$lp, $r11
2:
	ret

.globl show_led
show_led:
    li      $r8, (CONFIG_DEBUG_LED)
    swi     $r7, [$r8]
    ret
#endif /* #ifndef CONFIG_SKIP_LOWLEVEL_INIT */
