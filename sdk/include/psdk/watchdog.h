/*
 * PROJECT:         ReactOS Watchdog driver
 * COPYRIGHT:       See COPYING in the top level directory
 * PURPOSE:         Watchdog public interface
 * PROGRAMMERS:     Christian Rendina (pizzaiolo100@proton.me)
 */
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

#if (NTDDI_VERSION >= NTDDI_VISTA)
#include <ntddvdeo.h>
#endif

/*
	The internal structure is not exposed by the public api
*/
typedef struct _WATCHDOG WATCHDOG;
typedef WATCHDOG* PWATCHDOG;

/**
 * Types of watchdog events
*/
enum WATCHDOG_EVENT_TYPE
{
	/**
	 * No event happend
	*/
	WATCHDOG_EVENT_NONE					= 0x0,

	/**
	 * This event is used when the timer was cancelled by the user (via WdStopWatch)
	*/
	WATCHDOG_EVENT_CANCELLED_BY_USER 	= 0x1,

	/**
	 * This event is used when the timer has expired
	*/
	WATCHDOG_EVENT_EXPIRED 				= 0x2,

	/**
	 * This event is used when the timer has been restarted
	*/
	WATCHDOG_EVENT_RESTARTED 			= 0x3,
};

/**
 * Types of monitoring that the watchdog have to do
*/
enum WATCHDOG_MONITOR_TYPE
{
	/**
	 * Monitors only the differences in the kernel thread run-time
	*/
	WATCHDOG_MONITOR_KERNEL_TIME = 1,

	/**
	 * Monitors only the differences in the user thread run-time
	*/
	WATCHDOG_MONITOR_USER_TIME = 2,

	/**
	 * Monitors the differences between both the times
	*/
	WATCHDOG_MONITOR_ALL_TIMES = 3,
};

/**
 * Starts a section in the code that has to be monitored
 * @param[in] Watchdog Watchdog
 * @note This API is only available in a deferred watch
*/
VOID
FASTCALL
WdEnterMonitoredSection(
	_In_ PWATCHDOG Watchdog
);

/**
 * Stop monitoring a section
 * @param[in] Watchdog Watchdog
 * @note This API is only available in a deferred watch
*/
VOID
FASTCALL
WdExitMonitoredSection(
	_In_ PWATCHDOG Watchdog
);

/**
 * Resets the deferred watchdog to it's inital state
 * @param[in] Watchdog Watchdog to reset
*/
VOID
FASTCALL
WdResetDeferredWatch(
	_In_ PWATCHDOG Watchdog
);

/**
 * Attempts to resume the deferred watchdog
 * @param[in] Watchdog Watchdog to resume
 * @param[in] ResetSuspensionCount If this variable is set to TRUE, then the suspension counts of the
 * 	watchdog will be set to 0
 * @note Resetting the suspension count DOES NOT resume the deferred watchdog
*/
VOID
FASTCALL
WdResumeDeferredWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ BOOLEAN ResetSuspensionCount
);

/**
 * Attempts to suspend the current watchdog and increment the suspension count by 1
 * @param[in] pWatchdog Watchdog to suspend
*/
VOID
FASTCALL
WdSuspendDeferredWatch(
	_In_ PWATCHDOG Watchdog
);

/**
 * Allocates a new deferred watchdog
 * @param[in] DeviceObject Device driver object to link the watchdog with
 * @param[in] Type Type of watchdog
 * @param[in] AllocationTag Tag to use for memory allocation
*/
PWATCHDOG
NTAPI
WdAllocateDeferredWatchdog(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ UINT32 Type,
	_In_ ULONG AllocationTag
);

/**
 * Allocates a new watchdog
 * @param[in] DeviceObject Device driver object to link the watchdog with
 * @param[in] Type Type of monitoring that the watchdog has to do
 * @param[in] AllocationTag Tag to use for memory allocation
 * @see WATCHDOG_MONITOR_TYPE for the types of monitoring
*/
PWATCHDOG
NTAPI
WdAllocateWatchdog(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ UINT32 Type,
	_In_ ULONG AllocationTag
);

/**
 * Notify the watchdog that the event previously fired to the DPC has been completed
 * @param[in] Watchdog Watchdog to signal
 * @param[in] ThreadObject a pointer to the thread object that is passed in the completion handler
*/
VOID
NTAPI
WdCompleteEvent(
	_In_ PWATCHDOG Watchdog,
	_In_ PVOID ThreadObject
);

#if (NTDDI_VERSION == NTDDI_WINXP)
/**
 * This is a special watchdog dpc callback that is executed for attempting to restore (or bugcheck)
 * the video driver
 * @param[in] Dpc Dpc pointer that called this function
 * @param[in] DeferredContext
 * @param[in] SystemArgument1
 * @param[in] SystemArgument2
 * @note in Windows Server 2003, it's present in VIDEOPRT.SYS
*/
VOID
NTAPI
WdDdiWatchdogDpcCallback(
	_In_ PKDPC Dpc,
	_In_opt_ PVOID DeferredContext,
	_In_opt_ PVOID SystemArgument1,
	_In_opt_ PVOID SystemArgument2
);
#endif

/**
 * Unreferences the current object, decrementing it's reference count
 * @param[in] Watchdog Watchdog to decrement
*/
VOID
NTAPI
WdDereferenceObject(
	_In_ PWATCHDOG Watchdog
);

/**
 * Frees an allocated deferred watchdog
 * @param[in] Watchdog Watchdog to free
*/
VOID
NTAPI
WdFreeDeferredWatchdog(
	_In_ PWATCHDOG Watchdog
);

/**
 * Frees an allocated deferred watchdog
 * @param[in] Watchdog Watchdog to free
*/
void
NTAPI
WdFreeWatchdog(
	_In_ PWATCHDOG Watchdog
);

/**
 * Gets the linked device driver object of the current watchdog
 * @param[in] Watchdog Watchdog to get the device object
 * @return Device object
*/
PDEVICE_OBJECT
NTAPI
WdGetDeviceObject(
	_In_ PWATCHDOG Watchdog
);

/**
 * Gets the last event that happend in the watchdog
 * @param[in] Watchdog Watchdog
 * @return Any value from WATCHDOG_EVENT_TYPE
*/
ULONG
NTAPI
WdGetLastEvent(
	_In_ PWATCHDOG Watchdog
);

/**
 * Gets the lowest-level device object from the attached device driver
 * @param[in] Watchdog Watchdog
 * @return Lowest-level device object
*/
PDEVICE_OBJECT
NTAPI
WdGetLowestDeviceObject(
	_In_ PWATCHDOG Watchdog
);

/**
 * Checks if the runner thread was frozen or it has made a progress
 * @param[in] Watchdog Watchdog
 * @return Returns FALSE if the watchdog hasn't made any progress
*/
BOOLEAN
NTAPI
WdMadeAnyProgress(
	_In_ PWATCHDOG Watchdog
);

/**
 * Add a reference the current object, incrementing it's reference count
 * @param[in] Watchdog Watchdog to increment
*/
VOID
NTAPI
WdReferenceObject(
	_In_ PWATCHDOG Watchdog
);

/**
 * Resets the watchdog to it's inital state
 * @param[in] Watchdog Watchdog to reset
 * @note The reset only works if the watchdog has been already started
*/
VOID
NTAPI
WdResetWatch(
	_In_ PWATCHDOG Watchdog
);

/**
 * Attempts to resume the watchdog
 * @param[in] Watchdog Watchdog to resume
 * @param[in] CheckForResumeCount If this is set to TRUE, the suspension count is
 *  decremented and will be checked before resuming the watchdog
 * @note Setting CheckForResumeCount to FALSE will forcefully resume the watchdog
*/
VOID
NTAPI
WdResumeWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ BOOLEAN CheckForResumeCount
);

/**
 * Starts a deferred watchdog
 * @param[in] Watchdog Watchdog to start
 * @param[in] Dpc DPC to be queued for execution after the timer expired or restarted
 * @param[in] DueTime Time when the watchdog will be hitted
 * @note DueTime is rappresented in milliseconds relative to the system time
*/
VOID
NTAPI
WdStartDeferredWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ PRKDPC Dpc,
	_In_ ULONG DueTime
);

/**
 * Starts the watchdog
 * @param[in] Watchdog Watchdog to start
 * @param[in] DueTime Time when the watchdog will be hitted
 * @param[in] Dpc DPC to be queued for execution after the timer expired or restarted
 */
VOID
NTAPI
WdStartWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ LARGE_INTEGER DueTime,
	_In_ PKDPC Dpc
);

VOID
NTAPI
WdStopDeferredWatch(
	_In_ PWATCHDOG Watchdog
);

/**
 * Attempts to stop the watchdog
 * @param[in] Watchdog Watchdog to stop
 * @param[in] CheckForStartCount If this is set to TRUE, the start count is
 *  decremented and will be checked before stopping the watchdog
 * @note Setting CheckForStartCount to FALSE will forcefully stop the watchdog
*/
VOID
NTAPI
WdStopWatch(
	_In_ PWATCHDOG Watchdog,
	_In_ BOOLEAN CheckForStartCount
);

/**
 * Attempts to suspend the current watchdog and increment the suspension count by 1
 * @param[in] pWatchdog Watchdog to suspend
*/
VOID
NTAPI
WdSuspendWatch(
	_In_ PWATCHDOG pWatchdog
);

#if (NTDDI_VERSION >= NTDDI_WS03)
/**
 * Attaches a new context
 * @param[in] Watchdog Watchdog
 * @param[in] ContextSize Size of the context to allocate
*/
VOID
NTAPI
WdAttachContext(
    _In_ PWATCHDOG Watchdog,
    _In_ SIZE_T ContextSize
);

/**
 * Detaches a previously allocated context
 * @param[in] Watchdog Watchdog
*/
VOID
NTAPI
WdDetachContext(
    _In_ PWATCHDOG Watchdog
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
/* Session Manager interface */

/**
 Types of session notifications that can be sent
*/
enum WATCHDOG_SESSION_CHANGE_TYPE
{
#if (NTDDI_VERSION >= NTDDI_WIN8)
	/**
	 Registers the current process
	*/
	WATCHDOG_SESSION_OPEN = 0,

	/**
	 Unregister the current process
	*/
	WATCHDOG_SESSION_CLOSE = 1,

	/**
	 Similar to close but it doesn't try to unregister the process
	*/
	WACTHDOG_SESSION_RUNDOWN = 2,

	/**
	 Sets the current session process as the one used during SwithConsole callouts
	*/
	WATCHDOG_SESSION_SET_CONSOLESESSIONID_TO_CURRENT = 3,

	/**
	* Unsets the previously setted session id
	*/
	WATCHDOG_SESSION_UNSET_CONSOLESESSIONID = 4,
#else
	/**
	 Unregister the current process
	*/
	WATCHDOG_SESSION_CLOSE = 0,

	/**
	 Registers the current process
	*/
	WATCHDOG_SESSION_OPEN = 1,
#endif
};

#if (NTDDI_VERSION >= NTDDI_WIN8)

/** When this flag is passed, the execution simply fails. Unsure what it used to be. */
#define WATCHDOG_GDI_CALLOUT_NO_EXECUTION				0x300000000U

/**
   Executes the callout for all processes that matches the Console ID callout
   @note The stored session ID are used only if the callee current active console Id is -1 (not active)
 */
#define WATCHDOG_GDI_CALLOUT_EXECUTE_ONLY_CONSOLEID		0x200000000U

/** Executes the callout for all processes */
#define WATCHDOG_GDI_CALLOUT_EXECUTE_FOR_ALL			0x100000000U

/** Session change callout (See also WATCHDOG_SESSION_CHANGE_TYPE) */
typedef NTSTATUS(NTAPI* PWATCHDOG_SESSION_CHANGE_CALLOUT)(UINT32 Type);

/* Undiscovered, might subject to change */
typedef struct _VIDEO_SCENARIO_CONTEXT* PVIDEO_SCENARIO_CONTEXT;

/**
	@brief Notifies a change in the registred session processes.
	@param[in] Type type of change to notify.
	@param[in] Callout Callout used when registring a new session process.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrNotifySessionChange(
	_In_ WATCHDOG_SESSION_CHANGE_TYPE Type,
	_In_opt_ PVIDEO_WIN32K_CALLOUT Callout
);

/**
	@brief Registers a callout that will be executed everytime SMgrNotifySessionChange is used.
	@param[in] Callout Callout to register.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrRegisterSessionChangeCallout(
	_In_ PWATCHDOG_SESSION_CHANGE_CALLOUT Callout
);

/**
	@brief Unregister a previously registred callout.
	@param[in] Callout Callout to unregister.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrUnregisterSessionChangeCallout(
	_In_ PWATCHDOG_SESSION_CHANGE_CALLOUT Callout
);

/**
	@brief Queues a win32k callout execution for later or immediatly handles one.
	@param[in] CallbackParams Parameters to execute.
	@param[in] TargetSessionId Session id to execute the callouts for.
	@param[in] ProcessNow if this parameter is true, then the callback params are not queued, instead
	 they are dispatched immediatly to win32k.
	@param[in] StatusCallback This callback will be executed during the handling for any new update.
	@param[in] UserData Custom user data that will be passed to StatusCallback.
	@param[in] ScenarioContext Scenario context that will be updated.
	@note TargetSessionId can also be any of the special WATCHDOG_GDI_CALLOUT_* flags.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrGdiCallout(
	_In_ PVIDEO_WIN32K_CALLBACKS_PARAMS CallbackParams,
	_In_ UINT64 TargetSessionId,
	_In_ BOOLEAN ProcessNow,
	_In_opt_ PWATCHDOG_CALLOUT_STATUS_CALLBACK StatusCallback,
	_In_opt_ void* UserData,
	_In_opt_ PVIDEO_SCENARIO_CONTEXT* ScenarioContext
);

#else

/** Session start callout */
typedef void(NTAPI* PWATCHDOG_SESSION_START_CALLOUT)(void);

/**
	@brief Notifies a change in the registred session processes.
	@param[in] Type type of change to notify. (See WATCHDOG_SESSION_CHANGE_TYPE)
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrNotifySessionChange(
	_In_ UINT32 Type
);

/**
	@brief Registers a global win32k GDI callout.
	@param[in] Callout Global callout to register.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrRegisterGdiCallout(
	_In_ PVIDEO_WIN32K_CALLOUT Callout
);

/**
	@brief Registers a new callout that will be called by any new session open.
	@param[in] Callout Callout to be registred.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrRegisterSessionStartCallout(
	_In_ PWATCHDOG_SESSION_START_CALLOUT Callout
);

/**
	@brief Unregister the previously registred callout.
	@param[in] Callout Callout to be unregistred.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrUnregisterSessionStartCallout(
	_In_ PWATCHDOG_SESSION_START_CALLOUT Callout
);

/**
	@brief Queues a win32k callout execution for later or immediatly handles one.
	@param[in] CallbackParams Parameters to execute.
	@param[in] ProcessAll if this parameter is true, then the callout will be executed
	 for every registred process, this is the same as WATCHDOG_GDI_CALLOUT_EXECUTE_FOR_ALL.
	@param[in] ProcessNow if this parameter is true, then the callback params are not queued, instead
	 they are dispatched immediatly to win32k.
	@return Status indicating any error.
*/
NTSTATUS
NTAPI
SMgrGdiCallout(
	_In_ PVIDEO_WIN32K_CALLBACKS_PARAMS CallbackParams,
	_In_ BOOLEAN ProcessAll,
	_In_ BOOLEAN ProcessNow
);

#endif /* NTDDI_VERSION >= NTDDI_WIN8 */

/**
	@brief Gets the first active process for the current session id.
	@return A handle to a process or NULL in case no associated process is found.
*/
HANDLE
NTAPI
SMgrGetActiveSessionProcess();

/**
	@brief Gets all the currently registred session process.
	@return The number of registred processes.
*/
ULONG
NTAPI
SMgrGetNumberOfSessions();

#endif /* NTDDI_VERSION >= NTDDI_VISTA */
#endif /* _WATCHDOG_H_ */
