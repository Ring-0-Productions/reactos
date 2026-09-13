/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     TEMP-DEBUG (remove after hang debug): periodic heartbeat DPC.
 *
 * A DPC fires every 2 seconds and logs the current thread and IRQL to the
 * debug log. When the system hangs, this tells us whether the kernel is
 * still alive (heartbeats continue => display/GPU stuck) or fully wedged
 * (heartbeats stop => note the last lines before the stop).
 */

#include <ntoskrnl.h>

#define NDEBUG
#include <debug.h>

static KTIMER HbdTimer;
static KDPC HbdDpc;
static ULONG HbdTick = 0;

static
VOID
NTAPI
HbdDpcRoutine(
    _In_ PKDPC Dpc,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID Arg1,
    _In_opt_ PVOID Arg2)
{
    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(Context);
    UNREFERENCED_PARAMETER(Arg1);
    UNREFERENCED_PARAMETER(Arg2);

    HbdTick++;
    DPRINT1("HEARTBEAT: tick=%lu Thread=%p Irql=%lu\n",
            HbdTick,
            KeGetCurrentThread(),
            (ULONG)KeGetCurrentIrql());
}

VOID
NTAPI
HbdInit(VOID)
{
    LARGE_INTEGER DueTime;

    KeInitializeTimer(&HbdTimer);
    KeInitializeDpc(&HbdDpc, HbdDpcRoutine, NULL);

    /* First fire in 2 seconds, then periodic every 2 seconds */
    DueTime.QuadPart = -20000000LL;
    KeSetTimerEx(&HbdTimer, DueTime, 2000, &HbdDpc);

    DPRINT1("HEARTBEAT: watchdog started (2s period)\n");
    /* Build marker: every gaming-fix kernel prints its build date here, so
     * serial logs always prove which binaries are actually running. */
    DPRINT1("GAMING-BUILD " __DATE__ " " __TIME__ "\n");
}
