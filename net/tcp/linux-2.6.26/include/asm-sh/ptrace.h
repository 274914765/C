#ifndef __ASM_SH_PTRACE_H
#define __ASM_SH_PTRACE_H

/*
 * Copyright (C) 1999, 2000  Niibe Yutaka
 *
 */
#if defined(__SH5__) || defined(CONFIG_SUPERH64)
struct pt_regs {
    unsigned long long pc;
    unsigned long long sr;
    unsigned long long syscall_nr;
    unsigned long long regs[63];
    unsigned long long tregs[8];
    unsigned long long pad[2];
};
#else
/*
 * GCC defines register number like this:
 * -----------------------------
 *     0 - 15 are integer registers
 *    17 - 22 are control/special registers
 *    24 - 39 fp registers
 *    40 - 47 xd registers
 *    48 -    fpscr register
 * -----------------------------
 *
 * We follows above, except:
 *    16 --- program counter (PC)
 *    22 --- syscall #
 *    23 --- floating point communication register
 */
#define REG_REG0     0
#define REG_REG15    15

#define REG_PC        16

#define REG_PR        17
#define REG_SR        18
#define REG_GBR        19
#define REG_MACH    20
#define REG_MACL    21

#define REG_SYSCALL    22

#define REG_FPREG0    23
#define REG_FPREG15    38
#define REG_XFREG0    39
#define REG_XFREG15    54

#define REG_FPSCR    55
#define REG_FPUL    56

/*
 * This struct defines the way the registers are stored on the
 * kernel stack during a system call or other kernel entry.
 */
struct pt_regs {
    unsigned long regs[16];
    unsigned long pc;
    unsigned long pr;
    unsigned long sr;
    unsigned long gbr;
    unsigned long mach;
    unsigned long macl;
    long tra;
};

/*
 * This struct defines the way the DSP registers are stored on the
 * kernel stack during a system call or other kernel entry.
 */
struct pt_dspregs {
    unsigned long    a1;
    unsigned long    a0g;
    unsigned long    a1g;
    unsigned long    m0;
    unsigned long    m1;
    unsigned long    a0;
    unsigned long    x0;
    unsigned long    x1;
    unsigned long    y0;
    unsigned long    y1;
    unsigned long    dsr;
    unsigned long    rs;
    unsigned long    re;
    unsigned long    mod;
};

#define    PTRACE_GETDSPREGS    55
#define    PTRACE_SETDSPREGS    56
#endif

#ifdef __KERNEL__
#include <asm/addrspace.h>

#define user_mode(regs)            (((regs)->sr & 0x40000000)==0)
#define instruction_pointer(regs)    ((unsigned long)(regs)->pc)

extern void show_regs(struct pt_regs *);

#ifdef CONFIG_SH_DSP
#define task_pt_regs(task) \
    ((struct pt_regs *) (task_stack_page(task) + THREAD_SIZE \
         - sizeof(struct pt_dspregs) - sizeof(unsigned long)) - 1)
#else
#define task_pt_regs(task) \
    ((struct pt_regs *) (task_stack_page(task) + THREAD_SIZE \
         - sizeof(unsigned long)) - 1)
#endif

static inline unsigned long profile_pc(struct pt_regs *regs)
{
    unsigned long pc = instruction_pointer(regs);

#ifdef P2SEG
    if (pc >= P2SEG && pc < P3SEG)
        pc -= 0x20000000;
#endif

    return pc;
}
#endif /* __KERNEL__ */

#endif /* __ASM_SH_PTRACE_H */
