/*
 * PROJECT:         ReactOS Watchdog driver
 * COPYRIGHT:       See COPYING in the top level directory
 * PURPOSE:         Watchdog public interface
 * PROGRAMMERS:     Christian Rendina (pizzaiolo100@proton.me)
 */
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

#if (NTDDI_VERSION >= NTDDI_VISTA)
/* Session Manager interface */

#include <ntddvdeo.h>

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
	_In_ UINT32 ProcessNow,
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
	_In_ UINT32 ProcessAll,
	_In_ UINT32 ProcessNow
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
