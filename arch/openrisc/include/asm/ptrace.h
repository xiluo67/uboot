/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __ASM_OPENRISC_PTRACE_H
#define __ASM_OPENRISC_PTRACE_H

#include <asm/spr-defs.h>

#ifndef __ASSEMBLY__
/*
 * This is the layout of the regset returned by the GETREGSET ptrace call
 */
struct user_regs_struct {
	/* GPR R0-R31... */
	unsigned long gpr[32];
	unsigned long pc;
	unsigned long sr;
	unsigned long pad1;
	unsigned long pad2;
};
#endif

#ifdef __KERNEL__

/*
 * Make kernel PTrace/register structures opaque to userspace... userspace can
 * access thread state via the regset mechanism.  This allows us a bit of
 * flexibility in how we order the registers on the stack, permitting some
 * optimizations like packing call-clobbered registers together so that
 * they share a cacheline (not done yet, though... future optimization).
 */

#ifndef __ASSEMBLY__
/*
 * This struct describes how the registers are laid out on the kernel stack
 * during a syscall or other kernel entry.
 *
 * This structure should always be cacheline aligned on the stack.
 * FIXME: I don't think that's the case right now.  The alignment is
 * taken care of elsewhere... head.S, process.c, etc.
 */

struct pt_regs {
	union {
		struct {
			/* Named registers */
			long  sr;	/* Stored in place of r0 */
			long  sp;	/* r1 */
		};
		struct {
			/* Old style */
			long offset[2];
			long gprs[30];
		};
		struct {
			/* New style */
			long gpr[32];
		};
	};
	long  pc;
	long  orig_gpr11;	/* For restarting system calls */
	long  syscallno;	/* Syscall number (used by strace) */
	long dummy;		/* Cheap alignment fix */
};
#endif /* __ASSEMBLY__ */

/* TODO: Rename this to REDZONE because that's what it is */
#define STACK_FRAME_OVERHEAD  128  /* size of minimum stack frame */

#define instruction_pointer(regs)	((regs)->pc)
#define user_mode(regs)			(((regs)->sr & SPR_SR_SM) == 0)
#define user_stack_pointer(regs)	((unsigned long)(regs)->sp)
#define profile_pc(regs)		instruction_pointer(regs)

/*
 * Offsets used by 'ptrace' system call interface.
 */
#define PT_SR         0
#define PT_SP         4
#define PT_GPR2       8
#define PT_GPR3       12
#define PT_GPR4       16
#define PT_GPR5       20
#define PT_GPR6       24
#define PT_GPR7       28
#define PT_GPR8       32
#define PT_GPR9       36
#define PT_GPR10      40
#define PT_GPR11      44
#define PT_GPR12      48
#define PT_GPR13      52
#define PT_GPR14      56
#define PT_GPR15      60
#define PT_GPR16      64
#define PT_GPR17      68
#define PT_GPR18      72
#define PT_GPR19      76
#define PT_GPR20      80
#define PT_GPR21      84
#define PT_GPR22      88
#define PT_GPR23      92
#define PT_GPR24      96
#define PT_GPR25      100
#define PT_GPR26      104
#define PT_GPR27      108
#define PT_GPR28      112
#define PT_GPR29      116
#define PT_GPR30      120
#define PT_GPR31      124
#define PT_PC	      128
#define PT_ORIG_GPR11 132
#define PT_SYSCALLNO  136

#endif /* __KERNEL__ */

#endif /* __ASM_OPENRISC_PTRACE_H */
