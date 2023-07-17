/*
 * PROJECT:     ReactOS Hardware Abstraction Layer
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Initialize the APIC HAL
 * COPYRIGHT:   Copyright 2011 Timo Kreuzer <timo.kreuzer@reactos.org>
 */

/* INCLUDES *****************************************************************/

#include <hal.h>
#include "apicp.h"
#include <smp.h>
#define NDEBUG
#include <debug.h>
extern UCHAR HalpVectorToIndex[256];

VOID
NTAPI
ApicInitializeLocalApic(ULONG Cpu);

/* FUNCTIONS ****************************************************************/

VOID
NTAPI
HalpInitProcessor(
    IN ULONG ProcessorNumber,
    IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
#ifdef CONFIG_SMP
    if (ProcessorNumber == 0)
    {
#endif
        HalpParseApicTables(LoaderBlock);
#ifdef CONFIG_SMP
    }

    HalpSetupProcessorsTable(ProcessorNumber);
#endif

    /* Initialize the local APIC for this cpu */
    ApicInitializeLocalApic(ProcessorNumber);
    if(ProcessorNumber != 0)
    {
    /* Set interrupt handlers in the IDT */
    KeRegisterInterruptHandler(APIC_CLOCK_VECTOR, HalpClockInterrupt);
    KeRegisterInterruptHandler(APIC_IPI_VECTOR, HalpIpiInterrupt);
#ifndef _M_AMD64
    KeRegisterInterruptHandler(APC_VECTOR, HalpApcInterrupt);
    KeRegisterInterruptHandler(DISPATCH_VECTOR, HalpDispatchInterrupt);
#endif

    /* Register the vectors for APC and dispatch interrupts */
    HalpRegisterVector(IDT_INTERNAL, 0, APC_VECTOR, APC_LEVEL);
    HalpRegisterVector(IDT_INTERNAL, 0, DISPATCH_VECTOR, DISPATCH_LEVEL);

    /* Restore interrupt state */
    //if (EnableInterrupts) EFlags |= EFLAGS_INTERRUPT_MASK;
    }
    if(ProcessorNumber == 0)
    {
    /* Initialize profiling data (but don't start it) */
        HalInitializeProfiling();
    }
    /* Initialize the timer */
    //ApicInitializeTimer(ProcessorNumber);
}

VOID
HalpInitPhase0(IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    DPRINT1("Using HAL: APIC %s %s\n",
            (HalpBuildType & PRCB_BUILD_UNIPROCESSOR) ? "UP" : "SMP",
            (HalpBuildType & PRCB_BUILD_DEBUG) ? "DBG" : "REL");

    HalpPrintApicTables();

    /* Enable clock interrupt handler */
    HalpEnableInterruptHandler(IDT_INTERNAL,
                               0,
                               APIC_CLOCK_VECTOR,
                               CLOCK2_LEVEL,
                               HalpClockInterrupt,
                               Latched);

    /* Enable IPI interrupt handler */
    HalpEnableInterruptHandler(IDT_INTERNAL,
                               0,
                               APIC_IPI_VECTOR,
                               IPI_LEVEL,
                               HalpIpiInterruptHandler,
                               Latched);
}

VOID
HalpInitPhase1(VOID)
{
    if(KeNumberProcessors < 2)
    {
        HalpInitDma();
    }
    /* Initialize DMA. NT does this in Phase 0 */
}

/* EOF */
