
#include <ntifs.h>
#include <watchdog.h>

#define NDEBUG
#include <debug.h>

NTSTATUS
NTAPI
DriverEntry (
    _In_ PDRIVER_OBJECT	DriverObject,
    _In_ PUNICODE_STRING RegistryPath)
{
    UNIMPLEMENTED;
    return STATUS_SUCCESS;
}

VOID
NTAPI
WdAllocateWatchdog(
    PVOID p1,
    PVOID p2,
    ULONG p3)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdAllocateDeferredWatchdog(
    PVOID p1,
    PVOID p2,
    ULONG p3)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdFreeWatchdog(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdFreeDeferredWatchdog(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStartWatch(
    PVOID p1,
    LARGE_INTEGER p2,
    ULONG p3)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStartDeferredWatch(
    PVOID p1,
    PVOID p2,
    ULONG p3)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStopWatch(
    PVOID p1,
    ULONG p2)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStopDeferredWatch(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdSuspendWatch(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdSuspendDeferredWatch(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdResumeWatch(
    PVOID p1,
    PVOID p2)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdResumeDeferredWatch(
    PVOID p1,
    PVOID p2)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdResetWatch(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdResetDeferredWatch(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdEnterMonitoredSection(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdExitMonitoredSection(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdAttachContext(
    PVOID p1,
    PVOID p2)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdDetachContext(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdGetDeviceObject(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdGetLowestDeviceObject(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdGetLastEvent(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdCompleteEvent(
    PVOID p1,
    PVOID p2)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdReferenceObject(
    PVOID p1)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdDereferenceObject(
    PVOID p1)
{
    UNIMPLEMENTED;
}

BOOLEAN
NTAPI
WdMadeAnyProgress(
    PVOID p1)
{
    UNIMPLEMENTED;
    return FALSE;
}

#if (NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSTATUS
NTAPI
SMgrNotifySessionChange(
	_In_ WATCHDOG_SESSION_CHANGE_TYPE Type,
	_In_opt_ PVIDEO_WIN32K_CALLOUT Callout
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;
}

NTSTATUS
NTAPI
SMgrRegisterSessionChangeCallout(
	_In_ PWATCHDOG_SESSION_CHANGE_CALLOUT Callout
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;
}

NTSTATUS
NTAPI
SMgrUnregisterSessionChangeCallout(
	_In_ PWATCHDOG_SESSION_CHANGE_CALLOUT Callout
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;   
}

NTSTATUS
NTAPI
SMgrGdiCallout(
	_In_ PVIDEO_WIN32K_CALLBACK_PARAMS CallbackParams,
	_In_ UINT64 TargetSessionId,
	_In_ UINT32 ProcessNow,
	_In_opt_ PWATCHDOG_CALLOUT_STATUS_CALLBACK StatusCallback,
	_In_opt_ void* UserData,
	_In_opt_ PVIDEO_SCENARIO_CONTEXT* ScenarioContext
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;   
}
#else
NTSTATUS
NTAPI
SMgrNotifySessionChange(
	_In_ UINT32 Type
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;   
}

NTSTATUS
NTAPI
SMgrRegisterGdiCallout(
	_In_ PVIDEO_WIN32K_CALLOUT Callout
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;   
}

NTSTATUS
NTAPI
SMgrRegisterSessionStartCallout(
	_In_ PWATCHDOG_SESSION_START_CALLOUT Callout
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;   
}

NTSTATUS
NTAPI
SMgrUnregisterSessionStartCallout(
	_In_ PWATCHDOG_SESSION_START_CALLOUT Callout
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;   
}

NTSTATUS
NTAPI
SMgrGdiCallout(
	_In_ PVIDEO_WIN32K_CALLBACKS_PARAMS CallbackParams,
	_In_ UINT32 ProcessAll,
	_In_ UINT32 ProcessNow
)
{
    UNIMPLEMENTED;
    return STATUS_INVALID_PARAMETER;   
}
#endif

HANDLE
NTAPI
SMgrGetActiveSessionProcess()
{
    UNIMPLEMENTED;
    return NULL;   
}

ULONG
NTAPI
SMgrGetNumberOfSessions()
{
    UNIMPLEMENTED;
    return 0;   
}
#endif /* #if (NTDDI_VERSION >= NTDDI_VISTA) */
