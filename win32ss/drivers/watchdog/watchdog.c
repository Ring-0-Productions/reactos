
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

PWATCHDOG
NTAPI
WdAllocateWatchdog(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ UINT32 Type,
	_In_ ULONG AllocationTag)
{
    UNIMPLEMENTED;
    return NULL;
}

PWATCHDOG
NTAPI
WdAllocateDeferredWatchdog(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ UINT32 Type,
	_In_ ULONG AllocationTag)
{
    UNIMPLEMENTED;
    return NULL;
}

VOID
NTAPI
WdFreeWatchdog(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdFreeDeferredWatchdog(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStartWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ LARGE_INTEGER DueTime,
	_In_ PKDPC Dpc)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStartDeferredWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ PRKDPC Dpc,
	_In_ ULONG DueTime)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStopWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ BOOLEAN CheckForStartCount)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdStopDeferredWatch(
	_In_ PWATCHDOG pWatchdog)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdSuspendWatch(
	_In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdSuspendDeferredWatch(
	_In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdResumeWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ BOOLEAN CheckForResumeCount)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdResumeDeferredWatch(
    _In_ PWATCHDOG Watchdog,
    _In_ BOOLEAN ResetSuspensionCount)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdResetWatch(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdResetDeferredWatch(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdEnterMonitoredSection(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
FASTCALL
WdExitMonitoredSection(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

#if (NTDDI_VERSION >= NTDDI_WS03)
VOID
NTAPI
WdAttachContext(
    _In_ PWATCHDOG Watchdog,
    _In_ SIZE_T ContextSize)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdDetachContext(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}
#endif

PDEVICE_OBJECT
NTAPI
WdGetDeviceObject(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
    return NULL;
}

PDEVICE_OBJECT
NTAPI
WdGetLowestDeviceObject(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
    return NULL;
}

ULONG
NTAPI
WdGetLastEvent(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
    return 0;
}

VOID
NTAPI
WdCompleteEvent(
	_In_ PWATCHDOG Watchdog,
	_In_ PVOID ThreadObject)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdReferenceObject(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

VOID
NTAPI
WdDereferenceObject(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
}

BOOLEAN
NTAPI
WdMadeAnyProgress(
    _In_ PWATCHDOG Watchdog)
{
    UNIMPLEMENTED;
    return FALSE;
}

#if (NTDDI_VERSION == NTDDI_WINXP)
VOID
NTAPI
WdDdiWatchdogDpcCallback(
	_In_ PKDPC Dpc,
	_In_opt_ PVOID DeferredContext,
	_In_opt_ PVOID SystemArgument1,
	_In_opt_ PVOID SystemArgument2
)
{
    UNIMPLEMENTED;
}
#endif

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
	_In_ BOOLEAN ProcessNow,
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
	_In_ BOOLEAN ProcessAll,
	_In_ BOOLEAN ProcessNow
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
