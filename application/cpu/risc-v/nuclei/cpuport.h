/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2019-Present Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/03/26     hqfang       Nuclei RISC-V Core porting code.
 */

#ifndef __CPUPORT_H__
#define __CPUPORT_H__

#include <rtconfig.h>
#include <nuclei_sdk_soc.h>

#ifdef __cplusplus
extern "C" {
#endif
/* bytes of register width  */
#define ARCH_RISCV_FPU
#define ARCH_RISCV_FPU_S

#ifdef ARCH_CPU_64BIT
#define STORE                   sd
#define LOAD                    ld
#define REGBYTES                8
#else
#define STORE                   sw
#define LOAD                    lw
#endif

/* FPU */
#ifdef ARCH_RISCV_FPU
#ifdef ARCH_RISCV_FPU_D
#define FSTORE                  fsd
#define FLOAD                   fld
#define FREGBYTES               8
#define rv_floatreg_t           rt_int64_t
#endif
#ifdef ARCH_RISCV_FPU_S
#define FSTORE                  fsw
#define FLOAD                   flw
#define FREGBYTES               4
#define rv_floatreg_t           rt_int32_t
#endif
#endif


/* Scheduler utilities. */
#define RT_YIELD()                                                              \
{                                                                               \
    /* Set a software interrupt(SWI) request to request a context switch. */    \
    SysTimer_SetSWIRQ();                                                        \
    /* Barriers are normally not required but do ensure the code is completely  \
    within the specified behaviour for the architecture. */                     \
    __RWMB();                                                                   \
    __FENCE_I();                                                                \
}

extern void rt_hw_ticksetup(void);
extern void rt_hw_taskswitch(void);

#ifdef __cplusplus
}
#endif

#endif
