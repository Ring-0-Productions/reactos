/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Inter-Processor Packet Interface
 * COPYRIGHT:   Copyright 2006 Alex Ionescu (alex.ionescu@reactos.org)
 *              Copyright 2022 Justin Miller <justinmiller100@gmail.com>
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
//#define NDEBUG
#include <debug.h>

#ifdef NDEBUG
#define KdpDprintf(...)
#endif

/* GLOBALS *******************************************************************/

extern KSPIN_LOCK KiReverseStallIpiLock;
#define IPI_FROZEN_RUNNING 0
#define IPI_FROZEN_THAWING 3
#define IPI_FROZEN_HALTED 2

/* PRIVATE FUNCTIONS *********************************************************/

/**
 * @brief
 * This routine counts down and executes a IPI worker at the same time on all cores
 *
 * @param[in] PacketContext
 *
 * @param[in] Function
 * The routine to be executed across the CPUs synched
 *
 * @param[in] Argument
 * Parameter for function pointer
 *
 * @param[in] Count
 * Linearly decrementing count per CPU
 */
VOID
NTAPI
KiIpiGenericCallTarget(_In_ PKIPI_CONTEXT PacketContext,
                       _In_ PKIPI_BROADCAST_WORKER Function,
                       _In_ PULONG Argument,
                       _In_ PULONG Count)
{
  //  DPRINT1("generic call target enter");
    /* A CPU has entered, decrement */
    *Count -= 1;

    /* Loop until all processors are synched */
    while (Count != 0);

    /* Call the function pointer */
    (*Function)((ULONG_PTR)Argument);

    /* we're done! */
    KiIpiSignalPacketDone(PacketContext);
}

VOID
NTAPI
KiIpiSendPacket(
    IN KAFFINITY TargetProcessors,
    IN PKIPI_WORKER WorkerFunction,
    IN PKIPI_BROADCAST_WORKER BroadcastFunction,
    IN ULONG_PTR Context,
    IN PULONG Count)
{
#ifdef CONFIG_SMP
    KAFFINITY Processor;
    LONG i;
    PKPRCB Prcb, CurrentPrcb;
    KIRQL oldIrql;

    /* Parse processor list and prep the routine to be serviced */
    CurrentPrcb = KeGetCurrentPrcb();
    for (i = 0, Processor = 1; i < KeNumberProcessors; i++, Processor <<= 1)
    {
        if (TargetProcessors & Processor)
        {
            Prcb = KiProcessorBlock[i];

            Prcb->WorkerRoutine = WorkerFunction;
            InterlockedBitTestAndSet((PLONG)&Prcb->RequestSummary, IPI_SYNCH_REQUEST);
            if (Processor != CurrentPrcb->SetMember)
            {
               // DPRINT1("Count is %X\n", Count);
            }
        }
    }

    /* If the processor entering this routine ALSO needs to execute, service the routine */
    if (TargetProcessors & CurrentPrcb->SetMember)
    {
        KeRaiseIrql(IPI_LEVEL, &oldIrql);
        KiIpiServiceRoutine(NULL, NULL);
        KeLowerIrql(oldIrql);
    }

    /* Fire off to the processors! */
    HalRequestIpi(TargetProcessors);
#endif
}

VOID FASTCALL
KiIpiSignalPacketDone(IN PKIPI_CONTEXT PacketContext)
{
    /* FIXME: TODO */
 ///   UNIMPLEMENTED;
}

VOID FASTCALL
KiIpiSignalPacketDoneAndStall(IN PKIPI_CONTEXT PacketContext, IN volatile PULONG ReverseStall)
{
    /* FIXME: TODO */
  //  UNIMPLEMENTED;
}

/**
 * @brief
 * Send a interrupt of whatever type is assigned in IpiRequest to the target CPU set
 *
 * @param[in] TargetSet
 * List of CPUs being sent IPIs
 *
 * @param[in] IpiRequest
 * The Interrupt type being sent to target CPUs
 */
VOID
NTAPI
KiIpiSendRequest(IN KAFFINITY TargetSet,
                 IN ULONG IpiRequest)
{
#ifdef CONFIG_SMP
    LONG i;
    PKPRCB Prcb;
    KAFFINITY Current;

    for (i = 0, Current = 1; i < KeNumberProcessors; i++, Current <<= 1)
    {
        if (TargetSet & Current)
        {
            /* Get the PRCB for this CPU */
            Prcb = KiProcessorBlock[i];

            InterlockedBitTestAndSet((PLONG)&Prcb->RequestSummary, IpiRequest);
        }
    }

    /* HalRequestIpi does its own mask check =*/
    HalRequestIpi(TargetSet);
#endif
}

/* PUBLIC FUNCTIONS **********************************************************/
VOID
NTAPI
KiFreezeTargetExecution(_In_ PKTRAP_FRAME TrapFrame,
                        _In_ PKEXCEPTION_FRAME ExceptionFrame);
/*
 * @implemented
 */
BOOLEAN
NTAPI
KiIpiServiceRoutine(IN PKTRAP_FRAME TrapFrame, IN PKEXCEPTION_FRAME ExceptionFrame)
{
#ifdef CONFIG_SMP
    PKPRCB Prcb;
   // ASSERT(KeGetCurrentIrql() == IPI_LEVEL);
    Prcb = KeGetCurrentPrcb();

    /* APC level! Trigger an APC interrupt */
    if (InterlockedBitTestAndReset((PLONG)&Prcb->RequestSummary, IPI_APC))
    {
        HalRequestSoftwareInterrupt(APC_LEVEL);
    }


    /* DPC level! Trigger an DPC interrupt */
    if (InterlockedBitTestAndReset((PLONG)&Prcb->RequestSummary, IPI_DPC))
    {
        HalRequestSoftwareInterrupt(DISPATCH_LEVEL);
    }

    /* Freeze level! Trigger a FREEZE interrupt */
    if (InterlockedBitTestAndReset((PLONG)&Prcb->RequestSummary, IPI_FREEZE))
    {
        KiFreezeTargetExecution(TrapFrame, ExceptionFrame);
    }


    /* SYNCH_REQUEST we have a function pointer to execute! */
    if (InterlockedBitTestAndReset((PLONG)&Prcb->RequestSummary, IPI_SYNCH_REQUEST))
    {
#if defined(_M_ARM) || defined(_M_AMD64)
            DbgBreakPoint();
#else
            (void)InterlockedDecrementUL(&Prcb->CurrentPacket[1]);
            if (InterlockedCompareExchangeUL(&Prcb->CurrentPacket[2], 0, 0))
            {
                while (0 != InterlockedCompareExchangeUL(&Prcb->CurrentPacket[1], 0, 0))
                    ;
            }
            ((VOID(NTAPI *)(PVOID))(Prcb->WorkerRoutine))(Prcb->CurrentPacket[0]);
            InterlockedBitTestAndReset((PLONG)&Prcb->TargetSet, KeGetCurrentProcessorNumber());
            if (InterlockedCompareExchangeUL(&Prcb->CurrentPacket[2], 0, 0))
            {
                while (0 != InterlockedCompareExchangeUL(&Prcb->TargetSet, 0, 0))
                    ;
            }
        (void)InterlockedExchangePointer((PVOID *)&Prcb->SignalDone, NULL);
#endif // _M_ARM
    }
#endif
    return TRUE;
}

/*
 * @implemented
 */
ULONG_PTR
NTAPI
KeIpiGenericCall(IN PKIPI_BROADCAST_WORKER Function, IN ULONG_PTR Argument)
{
    ULONG_PTR Status;
    KIRQL OldIrql, OldIrql2;
#ifdef CONFIG_SMP
    KAFFINITY Affinity;
    ULONG Count;
    PKPRCB Prcb = KeGetCurrentPrcb();
#endif

    /* Raise to DPC level if required */
    OldIrql = KeGetCurrentIrql();
    if (OldIrql < DISPATCH_LEVEL)
        KeRaiseIrql(DISPATCH_LEVEL, &OldIrql);

#ifdef CONFIG_SMP
    /* Get current processor count and affinity */
    Count = KeNumberProcessors;
    Affinity = KeActiveProcessors;
    /* Exclude ourselves */
    Affinity &= ~Prcb->SetMember;
#endif

    /* Acquire the IPI lock */
    KeAcquireSpinLockAtDpcLevel(&KiReverseStallIpiLock);

#ifdef CONFIG_SMP
    /* Make sure this is MP */
    if (Affinity)
    {
        /* Send an IPI */
        KiIpiSendPacket(Affinity, KiIpiGenericCallTarget, Function, Argument, &Count);
    }

#endif

    /* Raise to IPI level */
    KeRaiseIrql(IPI_LEVEL, &OldIrql2);

#ifdef CONFIG_SMP
    /* Let the other processors know it is time */
    Count = 0;
#endif
    /* Call the function */
    Status = Function(Argument);

#ifdef CONFIG_SMP
    /* If this is MP, wait for the other processors to finish */
    if (Affinity)
    {
        /* Sanity check */
        ASSERT(Prcb == KeGetCurrentPrcb());

        /* FIXME: TODO */
      //  ASSERTMSG("Not yet implemented\n", FALSE);
    }
#endif

    /* Release the lock */
    KeReleaseSpinLockFromDpcLevel(&KiReverseStallIpiLock);

    /* Lower IRQL back */
    KeLowerIrql(OldIrql);

    return Status;
}

/**
 * @brief
 * Send a interrupt of whatever type is assigned in IpiRequest to the target CPU set
 *
 * @param[in] TargetSet
 * List of CPUs being sent IPIs
 *
 * @param[in] IpiRequest
 * The Interrupt type being sent to target CPUs
 */
VOID
FASTCALL
KiIpiSend(IN KAFFINITY TargetProcessors, IN ULONG IpiRequest)
{
    /* Call private function */
    KiIpiSendRequest(TargetProcessors, IpiRequest);
}
