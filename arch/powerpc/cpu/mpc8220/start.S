/*
 *  Copyright (C) 1998	Dan Malek <dmalek@jlc.net>
 *  Copyright (C) 1999	Magnus Damm <kieraypc01.p.y.kie.era.ericsson.se>
 *  Copyright (C) 2000 - 2003 Wolfgang Denk <wd@denx.de>
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

/*
 *  U-Boot - Startup Code for MPC8220 CPUs
 */
#include <asm-offsets.h>
#include <config.h>
#include <mpc8220.h>
#include <version.h>

#define _LINUX_CONFIG_H 1   /* avoid reading Linux autoconf.h file  */

#include <ppc_asm.tmpl>
#include <ppc_defs.h>

#include <asm/cache.h>
#include <asm/mmu.h>
#include <asm/u-boot.h>

/* We don't want the  MMU yet.
*/
#undef	MSR_KERNEL
/* Floating Point enable, Machine Check and Recoverable Interr. */
#ifdef DEBUG
#define MSR_KERNEL (MSR_FP|MSR_RI)
#else
#define MSR_KERNEL (MSR_FP|MSR_ME|MSR_RI)
#endif

/*
 * Set up GOT: Global Offset Table
 *
 * Use r12 to access the GOT
 */
	START_GOT
	GOT_ENTRY(_GOT2_TABLE_)
	GOT_ENTRY(_FIXUP_TABLE_)

	GOT_ENTRY(_start)
	GOT_ENTRY(_start_of_vectors)
	GOT_ENTRY(_end_of_vectors)
	GOT_ENTRY(transfer_to_handler)

	GOT_ENTRY(__init_end)
	GOT_ENTRY(__bss_end__)
	GOT_ENTRY(__bss_start)
	END_GOT

/*
 * Version string
 */
	.data
	.globl	version_string
version_string:
	.ascii U_BOOT_VERSION_STRING, "\0"

/*
 * Exception vectors
 */
	.text
	. = EXC_OFF_SYS_RESET
	.globl	_start
_start:
	mfmsr	r5		    /* save msr contents    */

	/* replace default MBAR base address from 0x80000000
	    to 0xf0000000 */

#if defined(CONFIG_SYS_DEFAULT_MBAR) && !defined(CONFIG_SYS_RAMBOOT)
	lis	r3, CONFIG_SYS_MBAR@h
	ori	r3, r3, CONFIG_SYS_MBAR@l

	/* MBAR is mirrored into the MBAR SPR */
	mtspr	MBAR,r3
	mtspr	SPRN_SPRG7W,r3
	lis	r4, CONFIG_SYS_DEFAULT_MBAR@h
	stw	r3, 0(r4)
#endif /* CONFIG_SYS_DEFAULT_MBAR */

	/* Initialise the MPC8220 processor core			*/
	/*--------------------------------------------------------------*/

	bl  init_8220_core

	/* initialize some things that are hard to access from C	*/
	/*--------------------------------------------------------------*/

	/* set up stack in on-chip SRAM */
	lis	r3, CONFIG_SYS_INIT_RAM_ADDR@h
	ori	r3, r3, CONFIG_SYS_INIT_RAM_ADDR@l
	ori	r1, r3, CONFIG_SYS_INIT_SP_OFFSET

	li	r0, 0		/* Make room for stack frame header and */
	stwu	r0, -4(r1)	/* clear final stack frame so that	*/
	stwu	r0, -4(r1)	/* stack backtraces terminate cleanly	*/

	/* let the C-code set up the rest				*/
	/*								*/
	/* Be careful to keep code relocatable !			*/
	/*--------------------------------------------------------------*/

	GET_GOT			/* initialize GOT access		*/

	/* r3: IMMR */
	bl	cpu_init_f	/* run low-level CPU init code (in Flash)*/

	bl	board_init_f	/* run 1st part of board init code (in Flash)*/

	/* NOTREACHED - board_init_f() does not return */

/*
 * Vector Table
 */

	.globl	_start_of_vectors
_start_of_vectors:

/* Machine check */
	STD_EXCEPTION(0x200, MachineCheck, MachineCheckException)

/* Data Storage exception. */
	STD_EXCEPTION(0x300, DataStorage, UnknownException)

/* Instruction Storage exception. */
	STD_EXCEPTION(0x400, InstStorage, UnknownException)

/* External Interrupt exception. */
	STD_EXCEPTION(0x500, ExtInterrupt, external_interrupt)

/* Alignment exception. */
	. = 0x600
Alignment:
	EXCEPTION_PROLOG(SRR0, SRR1)
	mfspr	r4,DAR
	stw	r4,_DAR(r21)
	mfspr	r5,DSISR
	stw	r5,_DSISR(r21)
	addi	r3,r1,STACK_FRAME_OVERHEAD
	EXC_XFER_TEMPLATE(Alignment, AlignmentException, MSR_KERNEL, COPY_EE)

/* Program check exception */
	. = 0x700
ProgramCheck:
	EXCEPTION_PROLOG(SRR0, SRR1)
	addi	r3,r1,STACK_FRAME_OVERHEAD
	EXC_XFER_TEMPLATE(ProgramCheck, ProgramCheckException,
		MSR_KERNEL, COPY_EE)

	STD_EXCEPTION(0x800, FPUnavailable, UnknownException)

	/* I guess we could implement decrementer, and may have
	 * to someday for timekeeping.
	 */
	STD_EXCEPTION(0x900, Decrementer, timer_interrupt)

	STD_EXCEPTION(0xa00, Trap_0a, UnknownException)
	STD_EXCEPTION(0xb00, Trap_0b, UnknownException)
	STD_EXCEPTION(0xc00, SystemCall, UnknownException)
	STD_EXCEPTION(0xd00, SingleStep, UnknownException)

	STD_EXCEPTION(0xe00, Trap_0e, UnknownException)
	STD_EXCEPTION(0xf00, Trap_0f, UnknownException)

	STD_EXCEPTION(0x1000, InstructionTLBMiss, UnknownException)
	STD_EXCEPTION(0x1100, DataLoadTLBMiss, UnknownException)
	STD_EXCEPTION(0x1200, DataStoreTLBMiss, UnknownException)
#ifdef DEBUG
	. = 0x1300
	/*
	 * This exception occurs when the program counter matches the
	 * Instruction Address Breakpoint Register (IABR).
	 *
	 * I want the cpu to halt if this occurs so I can hunt around
	 * with the debugger and look at things.
	 *
	 * When DEBUG is defined, both machine check enable (in the MSR)
	 * and checkstop reset enable (in the reset mode register) are
	 * turned off and so a checkstop condition will result in the cpu
	 * halting.
	 *
	 * I force the cpu into a checkstop condition by putting an illegal
	 * instruction here (at least this is the theory).
	 *
	 * well - that didnt work, so just do an infinite loop!
	 */
1:	b	1b
#else
	STD_EXCEPTION(0x1300, InstructionBreakpoint, DebugException)
#endif
	STD_EXCEPTION(0x1400, SMI, UnknownException)

	STD_EXCEPTION(0x1500, Trap_15, UnknownException)
	STD_EXCEPTION(0x1600, Trap_16, UnknownException)
	STD_EXCEPTION(0x1700, Trap_17, UnknownException)
	STD_EXCEPTION(0x1800, Trap_18, UnknownException)
	STD_EXCEPTION(0x1900, Trap_19, UnknownException)
	STD_EXCEPTION(0x1a00, Trap_1a, UnknownException)
	STD_EXCEPTION(0x1b00, Trap_1b, UnknownException)
	STD_EXCEPTION(0x1c00, Trap_1c, UnknownException)
	STD_EXCEPTION(0x1d00, Trap_1d, UnknownException)
	STD_EXCEPTION(0x1e00, Trap_1e, UnknownException)
	STD_EXCEPTION(0x1f00, Trap_1f, UnknownException)
	STD_EXCEPTION(0x2000, Trap_20, UnknownException)
	STD_EXCEPTION(0x2100, Trap_21, UnknownException)
	STD_EXCEPTION(0x2200, Trap_22, UnknownException)
	STD_EXCEPTION(0x2300, Trap_23, UnknownException)
	STD_EXCEPTION(0x2400, Trap_24, UnknownException)
	STD_EXCEPTION(0x2500, Trap_25, UnknownException)
	STD_EXCEPTION(0x2600, Trap_26, UnknownException)
	STD_EXCEPTION(0x2700, Trap_27, UnknownException)
	STD_EXCEPTION(0x2800, Trap_28, UnknownException)
	STD_EXCEPTION(0x2900, Trap_29, UnknownException)
	STD_EXCEPTION(0x2a00, Trap_2a, UnknownException)
	STD_EXCEPTION(0x2b00, Trap_2b, UnknownException)
	STD_EXCEPTION(0x2c00, Trap_2c, UnknownException)
	STD_EXCEPTION(0x2d00, Trap_2d, UnknownException)
	STD_EXCEPTION(0x2e00, Trap_2e, UnknownException)
	STD_EXCEPTION(0x2f00, Trap_2f, UnknownException)


	.globl	_end_of_vectors
_end_of_vectors:

	. = 0x3000

/*
 * This code finishes saving the registers to the exception frame
 * and jumps to the appropriate handler for the exception.
 * Register r21 is pointer into trap frame, r1 has new stack pointer.
 */
	.globl	transfer_to_handler
transfer_to_handler:
	stw	r22,_NIP(r21)
	lis	r22,MSR_POW@h
	andc	r23,r23,r22
	stw	r23,_MSR(r21)
	SAVE_GPR(7, r21)
	SAVE_4GPRS(8, r21)
	SAVE_8GPRS(12, r21)
	SAVE_8GPRS(24, r21)
	mflr	r23
	andi.	r24,r23,0x3f00	    /* get vector offset */
	stw	r24,TRAP(r21)
	li	r22,0
	stw	r22,RESULT(r21)
	lwz	r24,0(r23)		/* virtual address of handler */
	lwz	r23,4(r23)		/* where to go when done */
	mtspr	SRR0,r24
	mtspr	SRR1,r20
	mtlr	r23
	SYNC
	rfi			    /* jump to handler, enable MMU */

int_return:
	mfmsr	r28		    /* Disable interrupts */
	li	r4,0
	ori	r4,r4,MSR_EE
	andc	r28,r28,r4
	SYNC			    /* Some chip revs need this... */
	mtmsr	r28
	SYNC
	lwz	r2,_CTR(r1)
	lwz	r0,_LINK(r1)
	mtctr	r2
	mtlr	r0
	lwz	r2,_XER(r1)
	lwz	r0,_CCR(r1)
	mtspr	XER,r2
	mtcrf	0xFF,r0
	REST_10GPRS(3, r1)
	REST_10GPRS(13, r1)
	REST_8GPRS(23, r1)
	REST_GPR(31, r1)
	lwz	r2,_NIP(r1)	    /* Restore environment */
	lwz	r0,_MSR(r1)
	mtspr	SRR0,r2
	mtspr	SRR1,r0
	lwz	r0,GPR0(r1)
	lwz	r2,GPR2(r1)
	lwz	r1,GPR1(r1)
	SYNC
	rfi

/*
 * This code initialises the MPC8220 processor core
 * (conforms to PowerPC 603e spec)
 * Note: expects original MSR contents to be in r5.
 */

	.globl	init_8220_core
init_8220_core:

	/* Initialize machine status; enable machine check interrupt	*/
	/*--------------------------------------------------------------*/

	li	r3, MSR_KERNEL	    /* Set ME and RI flags		*/
	rlwimi	r3, r5, 0, 25, 25   /* preserve IP bit set by HRCW	*/
#ifdef DEBUG
	rlwimi	r3, r5, 0, 21, 22   /* debugger might set SE & BE bits	*/
#endif
	SYNC			    /* Some chip revs need this...	*/
	mtmsr	r3
	SYNC
	mtspr	SRR1, r3	    /* Make SRR1 match MSR		*/

	/* Initialize the Hardware Implementation-dependent Registers	*/
	/* HID0 also contains cache control				*/
	/*--------------------------------------------------------------*/

	lis	r3, CONFIG_SYS_HID0_INIT@h
	ori	r3, r3, CONFIG_SYS_HID0_INIT@l
	SYNC
	mtspr	HID0, r3

	lis	r3, CONFIG_SYS_HID0_FINAL@h
	ori	r3, r3, CONFIG_SYS_HID0_FINAL@l
	SYNC
	mtspr	HID0, r3

	/* Enable Extra BATs */
	mfspr	r3, 1011    /* HID2 */
	lis	r4, 0x0004
	ori	r4, r4, 0x0000
	or	r4, r4, r3
	mtspr	1011, r4
	sync

	/* clear all BAT's						*/
	/*--------------------------------------------------------------*/

	li	r0, 0
	mtspr	DBAT0U, r0
	mtspr	DBAT0L, r0
	mtspr	DBAT1U, r0
	mtspr	DBAT1L, r0
	mtspr	DBAT2U, r0
	mtspr	DBAT2L, r0
	mtspr	DBAT3U, r0
	mtspr	DBAT3L, r0
	mtspr	DBAT4U, r0
	mtspr	DBAT4L, r0
	mtspr	DBAT5U, r0
	mtspr	DBAT5L, r0
	mtspr	DBAT6U, r0
	mtspr	DBAT6L, r0
	mtspr	DBAT7U, r0
	mtspr	DBAT7L, r0
	mtspr	IBAT0U, r0
	mtspr	IBAT0L, r0
	mtspr	IBAT1U, r0
	mtspr	IBAT1L, r0
	mtspr	IBAT2U, r0
	mtspr	IBAT2L, r0
	mtspr	IBAT3U, r0
	mtspr	IBAT3L, r0
	mtspr	IBAT4U, r0
	mtspr	IBAT4L, r0
	mtspr	IBAT5U, r0
	mtspr	IBAT5L, r0
	mtspr	IBAT6U, r0
	mtspr	IBAT6L, r0
	mtspr	IBAT7U, r0
	mtspr	IBAT7L, r0
	SYNC

	/* invalidate all tlb's						*/
	/*								*/
	/* From the 603e User Manual: "The 603e provides the ability to */
	/* invalidate a TLB entry. The TLB Invalidate Entry (tlbie)	*/
	/* instruction invalidates the TLB entry indexed by the EA, and */
	/* operates on both the instruction and data TLBs simultaneously*/
	/* invalidating four TLB entries (both sets in each TLB). The	*/
	/* index corresponds to bits 15-19 of the EA. To invalidate all */
	/* entries within both TLBs, 32 tlbie instructions should be	*/
	/* issued, incrementing this field by one each time."		*/
	/*								*/
	/* "Note that the tlbia instruction is not implemented on the	*/
	/* 603e."							*/
	/*								*/
	/* bits 15-19 correspond to addresses 0x00000000 to 0x0001F000	*/
	/* incrementing by 0x1000 each time. The code below is sort of	*/
	/* based on code in "flush_tlbs" from arch/powerpc/kernel/head.S	*/
	/*								*/
	/*--------------------------------------------------------------*/

	li	r3, 32
	mtctr	r3
	li	r3, 0
1:	tlbie	r3
	addi	r3, r3, 0x1000
	bdnz	1b
	SYNC

	/* Done!							*/
	/*--------------------------------------------------------------*/

	blr

/* Cache functions.
 *
 * Note: requires that all cache bits in
 * HID0 are in the low half word.
 */
	.globl	icache_enable
icache_enable:
	lis	r4, 0
	ori	r4, r4, CONFIG_SYS_HID0_INIT /* set ICE & ICFI bit		*/
	rlwinm	r3, r4, 0, 21, 19     /* clear the ICFI bit		*/

	/*
	 * The setting of the instruction cache enable (ICE) bit must be
	 * preceded by an isync instruction to prevent the cache from being
	 * enabled or disabled while an instruction access is in progress.
	 */
	isync
	mtspr	HID0, r4	      /* Enable Instr Cache & Inval cache */
	mtspr	HID0, r3	      /* using 2 consec instructions	*/
	isync
	blr

	.globl	icache_disable
icache_disable:
	mfspr	r3, HID0
	rlwinm	r3, r3, 0, 17, 15     /* clear the ICE bit		*/
	mtspr	HID0, r3
	isync
	blr

	.globl	icache_status
icache_status:
	mfspr	r3, HID0
	rlwinm	r3, r3, HID0_ICE_BITPOS + 1, 31, 31
	blr

	.globl	dcache_enable
dcache_enable:
	lis	r4, 0
	ori	r4, r4, HID0_DCE|HID0_DCFI /* set DCE & DCFI bit	*/
	rlwinm	r3, r4, 0, 22, 20     /* clear the DCFI bit		*/

	/* Enable address translation in MSR bit */
	mfmsr	r5
	ori	r5, r5, 0x


	/*
	 * The setting of the instruction cache enable (ICE) bit must be
	 * preceded by an isync instruction to prevent the cache from being
	 * enabled or disabled while an instruction access is in progress.
	 */
	isync
	mtspr	HID0, r4	      /* Enable Data Cache & Inval cache*/
	mtspr	HID0, r3	      /* using 2 consec instructions	*/
	isync
	blr

	.globl	dcache_disable
dcache_disable:
	mfspr	r3, HID0
	rlwinm	r3, r3, 0, 18, 16     /* clear the DCE bit */
	mtspr	HID0, r3
	isync
	blr

	.globl	dcache_status
dcache_status:
	mfspr	r3, HID0
	rlwinm	r3, r3, HID0_DCE_BITPOS + 1, 31, 31
	blr

	.globl	get_pvr
get_pvr:
	mfspr	r3, PVR
	blr

/*------------------------------------------------------------------------------*/

/*
 * void relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code.
 *
 * r3 = dest
 * r4 = src
 * r5 = length in bytes
 * r6 = cachelinesize
 */
	.globl	relocate_code
relocate_code:
	mr	r1,  r3	    /* Set new stack pointer		*/
	mr	r9,  r4	    /* Save copy of Global Data pointer */
	mr	r10, r5	    /* Save copy of Destination Address */

	GET_GOT
	mr	r3,  r5	    /* Destination Address		*/
	lis	r4, CONFIG_SYS_MONITOR_BASE@h	/* Source Address	*/
	ori	r4, r4, CONFIG_SYS_MONITOR_BASE@l
	lwz	r5, GOT(__init_end)
	sub	r5, r5, r4
	li	r6, CONFIG_SYS_CACHELINE_SIZE	/* Cache Line Size	*/

	/*
	 * Fix GOT pointer:
	 *
	 * New GOT-PTR = (old GOT-PTR - CONFIG_SYS_MONITOR_BASE) + Destination Address
	 *
	 * Offset:
	 */
	sub	r15, r10, r4

	/* First our own GOT */
	add	r12, r12, r15
	/* then the one used by the C code */
	add	r30, r30, r15

	/*
	 * Now relocate code
	 */

	cmplw	cr1,r3,r4
	addi	r0,r5,3
	srwi.	r0,r0,2
	beq	cr1,4f	    /* In place copy is not necessary	*/
	beq	7f	    /* Protect against 0 count		*/
	mtctr	r0
	bge	cr1,2f

	la	r8,-4(r4)
	la	r7,-4(r3)
1:	lwzu	r0,4(r8)
	stwu	r0,4(r7)
	bdnz	1b
	b	4f

2:	slwi	r0,r0,2
	add	r8,r4,r0
	add	r7,r3,r0
3:	lwzu	r0,-4(r8)
	stwu	r0,-4(r7)
	bdnz	3b

/*
 * Now flush the cache: note that we must start from a cache aligned
 * address. Otherwise we might miss one cache line.
 */
4:	cmpwi	r6,0
	add	r5,r3,r5
	beq	7f	    /* Always flush prefetch queue in any case	*/
	subi	r0,r6,1
	andc	r3,r3,r0
	mfspr	r7,HID0	    /* don't do dcbst if dcache is disabled	*/
	rlwinm	r7,r7,HID0_DCE_BITPOS+1,31,31
	cmpwi	r7,0
	beq	9f
	mr	r4,r3
5:	dcbst	0,r4
	add	r4,r4,r6
	cmplw	r4,r5
	blt	5b
	sync		    /* Wait for all dcbst to complete on bus	*/
9:	mfspr	r7,HID0	    /* don't do icbi if icache is disabled	*/
	rlwinm	r7,r7,HID0_ICE_BITPOS+1,31,31
	cmpwi	r7,0
	beq	7f
	mr	r4,r3
6:	icbi	0,r4
	add	r4,r4,r6
	cmplw	r4,r5
	blt	6b
7:	sync		    /* Wait for all icbi to complete on bus	*/
	isync

/*
 * We are done. Do not return, instead branch to second part of board
 * initialization, now running from RAM.
 */

	addi	r0, r10, in_ram - _start + EXC_OFF_SYS_RESET
	mtlr	r0
	blr

in_ram:

	/*
	 * Relocation Function, r12 point to got2+0x8000
	 *
	 * Adjust got2 pointers, no need to check for 0, this code
	 * already puts a few entries in the table.
	 */
	li	r0,__got2_entries@sectoff@l
	la	r3,GOT(_GOT2_TABLE_)
	lwz	r11,GOT(_GOT2_TABLE_)
	mtctr	r0
	sub	r11,r3,r11
	addi	r3,r3,-4
1:	lwzu	r0,4(r3)
	cmpwi	r0,0
	beq-	2f
	add	r0,r0,r11
	stw	r0,0(r3)
2:	bdnz	1b

	/*
	 * Now adjust the fixups and the pointers to the fixups
	 * in case we need to move ourselves again.
	 */
	li	r0,__fixup_entries@sectoff@l
	lwz	r3,GOT(_FIXUP_TABLE_)
	cmpwi	r0,0
	mtctr	r0
	addi	r3,r3,-4
	beq	4f
3:	lwzu	r4,4(r3)
	lwzux	r0,r4,r11
	cmpwi	r0,0
	add	r0,r0,r11
	stw	r4,0(r3)
	beq-	5f
	stw	r0,0(r4)
5:	bdnz	3b
4:
clear_bss:
	/*
	 * Now clear BSS segment
	 */
	lwz	r3,GOT(__bss_start)
	lwz	r4,GOT(__bss_end__)

	cmplw	0, r3, r4
	beq	6f

	li	r0, 0
5:
	stw	r0, 0(r3)
	addi	r3, r3, 4
	cmplw	0, r3, r4
	bne	5b
6:

	mr	r3, r9	    /* Global Data pointer	*/
	mr	r4, r10	    /* Destination Address	*/
	bl	board_init_r

	/*
	 * Copy exception vector code to low memory
	 *
	 * r3: dest_addr
	 * r7: source address, r8: end address, r9: target address
	 */
	.globl	trap_init
trap_init:
	mflr	r4	    /* save link register		*/
	GET_GOT
	lwz	r7, GOT(_start)
	lwz	r8, GOT(_end_of_vectors)

	li	r9, 0x100   /* reset vector always at 0x100	*/

	cmplw	0, r7, r8
	bgelr		    /* return if r7>=r8 - just in case	*/
1:
	lwz	r0, 0(r7)
	stw	r0, 0(r9)
	addi	r7, r7, 4
	addi	r9, r9, 4
	cmplw	0, r7, r8
	bne	1b

	/*
	 * relocate `hdlr' and `int_return' entries
	 */
	li	r7, .L_MachineCheck - _start + EXC_OFF_SYS_RESET
	li	r8, Alignment - _start + EXC_OFF_SYS_RESET
2:
	bl	trap_reloc
	addi	r7, r7, 0x100	    /* next exception vector	    */
	cmplw	0, r7, r8
	blt	2b

	li	r7, .L_Alignment - _start + EXC_OFF_SYS_RESET
	bl	trap_reloc

	li	r7, .L_ProgramCheck - _start + EXC_OFF_SYS_RESET
	bl	trap_reloc

	li	r7, .L_FPUnavailable - _start + EXC_OFF_SYS_RESET
	li	r8, SystemCall - _start + EXC_OFF_SYS_RESET
3:
	bl	trap_reloc
	addi	r7, r7, 0x100	    /* next exception vector	    */
	cmplw	0, r7, r8
	blt	3b

	li	r7, .L_SingleStep - _start + EXC_OFF_SYS_RESET
	li	r8, _end_of_vectors - _start + EXC_OFF_SYS_RESET
4:
	bl	trap_reloc
	addi	r7, r7, 0x100	    /* next exception vector	    */
	cmplw	0, r7, r8
	blt	4b

	mfmsr	r3		    /* now that the vectors have    */
	lis	r7, MSR_IP@h	    /* relocated into low memory    */
	ori	r7, r7, MSR_IP@l    /* MSR[IP] can be turned off    */
	andc	r3, r3, r7	    /* (if it was on)		    */
	SYNC			    /* Some chip revs need this...  */
	mtmsr	r3
	SYNC

	mtlr	r4		    /* restore link register	    */
	blr
