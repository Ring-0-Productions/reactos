/*
 * PROJECT:     ReactOS Kernel - Vista+ APIs
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Ke functions of Vista+
 * COPYRIGHT:   2016 Pierre Schweitzer (pierre@reactos.org)
 *              2020 Victor Perevertkin (victor.perevertkin@reactos.org)
 */

#include <ntdef.h>
#include <ntifs.h>
#include <debug.h>

NTKRNLVISTAAPI
ULONG 
NTAPI
KeGetCurrentProcessorNumberEx(
  _Out_opt_ PPROCESSOR_NUMBER ProcNumber
)
{
    UNIMPLEMENTED;
    return 1;
}

NTKRNLVISTAAPI
ULONG
NTAPI
KeQueryActiveProcessorCount(OUT PKAFFINITY ActiveProcessors OPTIONAL)
{
    RTL_BITMAP Bitmap;
    KAFFINITY ActiveMap = KeQueryActiveProcessors();

    if (ActiveProcessors != NULL)
    {
        *ActiveProcessors = ActiveMap;
    }

    RtlInitializeBitMap(&Bitmap, (PULONG)&ActiveMap,  sizeof(ActiveMap) * 8);
    return RtlNumberOfSetBits(&Bitmap);
}

NTKRNLVISTAAPI
NTSTATUS
NTAPI
KeQueryDpcWatchdogInformation(
  OUT PKDPC_WATCHDOG_INFORMATION WatchdogInformation
)
{
    UNIMPLEMENTED;
    WatchdogInformation->DpcTimeLimit = 100000;
    WatchdogInformation->DpcTimeCount = 0;
    WatchdogInformation->DpcWatchdogLimit = 100000;
    WatchdogInformation->DpcWatchdogCount = 0;
    WatchdogInformation->Reserved = 0;
    
    return STATUS_UNSUCCESSFUL;
}

NTKRNLVISTAAPI
ULONG
NTAPI
KeQueryActiveProcessorCountEx(_In_ USHORT GroupNumber)
{
    UNIMPLEMENTED;
	return 1;
}

NTKRNLVISTAAPI
USHORT
NTAPI
KeQueryHighestNodeNumber()
{
    UNIMPLEMENTED;
	return 0;
}

NTKRNLVISTAAPI
USHORT
NTAPI
KeGetCurrentNodeNumber()
{
    UNIMPLEMENTED;
	return 0;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKRNLVISTAAPI
BOOLEAN
NTAPI
KeSetCoalescableTimer(
    _Inout_ PKTIMER Timer,
    _In_ LARGE_INTEGER DueTime,
    _In_ ULONG Period,
    _In_ ULONG TolerableDelay,
    _In_opt_ PKDPC Dpc)
{
    UNIMPLEMENTED;
    return KeSetTimerEx(Timer, DueTime, Period, Dpc);
}
