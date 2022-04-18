#include "include/psxss.h"
//#define NDEBUG
#include <debug.h>

#ifdef __PSXSS_ON_W32__
#include <windows.h>
#endif

SERVER Server =
{
     /* .Heap */
    INVALID_HANDLE_VALUE,
    /* .Directory */
    {
        {   INVALID_HANDLE_VALUE,
            L"\\"PSX_NS_SUBSYSTEM_DIRECTORY_NAME,
            {0,0,NULL}
        },
        {   INVALID_HANDLE_VALUE,
            L"\\"PSX_NS_SUBSYSTEM_DIRECTORY_NAME"\\"PSX_NS_SESSION_DIRECTORY_NAME,
            {0,0,NULL}
        },
        {   INVALID_HANDLE_VALUE,
            L"\\"PSX_NS_SUBSYSTEM_DIRECTORY_NAME"\\"PSX_NS_SYSTEM_DIRECTORY_NAME,
            {0,0,NULL}
        },
    },
    /* .Port */
    {
        {   INVALID_HANDLE_VALUE,
            L"\\"PSX_NS_SUBSYSTEM_DIRECTORY_NAME"\\"PSX_NS_API_PORT_NAME,
            {0,0,NULL},
            ApiPortListener
        },
        {   INVALID_HANDLE_VALUE,
            L"\\"PSX_NS_SUBSYSTEM_DIRECTORY_NAME"\\"PSX_NS_SBAPI_PORT_NAME,
            {0,0,NULL},
            SbApiPortListener
        },
        {   INVALID_HANDLE_VALUE,
            L"\\"PSX_NS_SUBSYSTEM_DIRECTORY_NAME"\\"PSX_NS_SESSIONAPI_PORT_NAME,
            {0,0,NULL},
            SessionPortListener
        }
    }
};

/*** FUNCTIONS *******************************************************/

/**********************************************************************
 *      PdxInitializeHeap/0                                     PRIVATE
 *
 * DESCRIPTION
 *      Initialize the PSX server process' heap.
 */
PRIVATE HANDLE NTAPI
PdxInitializeHeap (VOID)
{
        return Server.Heap = (HANDLE)NtCurrentPeb()->ProcessHeap;
}
/**********************************************************************
 *      PdxCreateDirectory/1                                    PRIVATE
 *
 * DESCRIPTION
 *      Create a directory in the system name space.
 */
PRIVATE NTSTATUS NTAPI
PdxCreateDirectory (
    IN ULONG ulIndex
    )
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS          Status;

    RtlCreateUnicodeString (
        & Server.Directory[ulIndex].usName,
        Server.Directory[ulIndex].wsName
        );
    InitializeObjectAttributes (
        & ObjectAttributes,
        & Server.Directory[ulIndex].usName,
        0,
        NULL,
        NULL
        );
    Status = NtCreateDirectoryObject(
                & Server.Directory[ulIndex].hObject,
                DIRECTORY_ALL_ACCESS,
                & ObjectAttributes
                );
    if (!NT_SUCCESS(Status))
    {
        debug_print(
          L"PSXSS: %s directory creation failed (Status = %08x)",
          Server.Directory[ulIndex].wsName,
          Status
          );

    }
    return Status;
}
/**********************************************************************
 *      PdxInitializeDirectories/0                              PRIVATE
 *
 * DESCRIPTION
 *      Create the directories used by the POSIX+ subsystem
 *      components in the system name space.
 */
PRIVATE NTSTATUS NTAPI
PdxInitializeDirectories (VOID)
{
    NTSTATUS  Status;
    ULONG     ulIndex;

    for ( ulIndex = 0;
          (ulIndex < (sizeof Server.Directory / sizeof Server.Directory[0]));
          ulIndex ++)
    {
        Status = PdxCreateDirectory (ulIndex);
        if (!NT_SUCCESS(Status)) return Status;
    }
    return STATUS_SUCCESS;
}
/**********************************************************************
 *      PdxInitializeListener/1                                 PRIVATE
 *
 * DESCRIPTION
 *      Initialize a thread to make an LPC port listen.
 */
PRIVATE NTSTATUS NTAPI
PdxInitializeListener (ULONG ulIndex)
{
    NTSTATUS          Status;
    OBJECT_ATTRIBUTES Oa;
    ULONG             ulThreadIndex;

    RtlInitUnicodeString (
        & Server.Port[ulIndex].usName,
        Server.Port[ulIndex].wsName
        );
    InitializeObjectAttributes(
        & Oa,
        & Server.Port[ulIndex].usName,
        0,
        NULL,
        NULL
        );
    /* Create the listening LPC port */
    Status = NtCreatePort (
                & Server.Port[ulIndex].hObject,
                & Oa,
                260,
                328,
                0
                );
    if (!NT_SUCCESS(Status))
    {
        debug_print(
            L"PSXSS: Unable to create port \"%s\": Status %08x\n",
            Server.Port[ulIndex].wsName,
            Status);
        return Status;
    }
    /*
     * Create the server thread that will process
     * messages sent to this port.
     */
    for ( ulThreadIndex = 0;
          (ulThreadIndex < PSXSS_THREADS_PER_PORT);
          ulThreadIndex ++
          )
    {
#ifdef __PSXSS_ON_W32__
        Server.Port[ulIndex].ThreadInfo[ulThreadIndex].hObject =
            CreateThread (
                NULL,
                0,
                (PTHREAD_START_ROUTINE) Server.Port[ulIndex].EntryPoint,
                (PVOID) ulIndex,
                CREATE_SUSPENDED,
                & Server.Port[ulIndex].ThreadInfo[ulThreadIndex].Id
                );
        if (NULL == Server.Port[ulIndex].ThreadInfo[ulThreadIndex].hObject)
#else
        if (!NT_SUCCESS(Status))
#endif
        {
            debug_print(
                L"PSXSS: Unable to create a server thread for port \"%s\": Status %08x\n",
                Server.Port[ulIndex].wsName,
                Status
                );
            NtClose (Server.Port[ulIndex].hObject);
            return Status;
        }
    }
    return STATUS_SUCCESS;
}
/**********************************************************************
 *      PsxInitializeListeners/0                                PRIVATE
 *
 * DESCRIPTION
 *      Initialize the LPC ports and associate threads.
 */
PRIVATE NTSTATUS NTAPI
PdxInitializeListeners (VOID)
{
    NTSTATUS Status;
    ULONG    ulIndex;

    for ( ulIndex = 0;
          (ulIndex < (sizeof Server.Port / sizeof Server.Port[0]));
          ulIndex ++)
    {
        Status = PdxInitializeListener (ulIndex);
        if (!NT_SUCCESS(Status)) return Status;
    }
    return STATUS_SUCCESS;
}
/**********************************************************************
 *      PdxRunServer/0                                          PRIVATE
 *
 * DESCRIPTION
 *      Wake up all suspended threads.
 */
PRIVATE NTSTATUS NTAPI
PdxRunServer (VOID)
{
    NTSTATUS Status;
    ULONG    ulIndex;
    ULONG    ulThreadIndex;
	Status = 0;
    for ( ulIndex = 0;
          (ulIndex < (sizeof Server.Port / sizeof Server.Port[0]));
          ulIndex ++)
    {
        for (ulThreadIndex = 0;
             (ulThreadIndex < PSXSS_THREADS_PER_PORT);
             ulThreadIndex ++
             )
        {
#ifdef __PSXSS_ON_W32__
            if (0xFFFFFFFF == ResumeThread (Server.Port[ulIndex].ThreadInfo[ulThreadIndex].hObject))
#else
            Status = NtResumeThread (Server.Port[ulIndex].ThreadInfo[ulThreadIndex].hObject, NULL);
            if (!NT_SUCCESS(Status))
#endif
            {
                debug_print(
                    L"PSXSS: "__FUNCTION__": NtResumeThread failed with Status = %08x",
                    Status
                    );
                return Status;
            }
        }
    }
    return STATUS_SUCCESS;
}
/**********************************************************************
 *      PsxServerInitialization/2
 *
 * DESCRIPTION
 *      Initialize the PSX server process.
 */
NTSTATUS NTAPI
PsxServerInitialization (
    IN ULONG ArgumentCount,
    IN PWSTR *ArgumentArray
    )
{
        NTSTATUS Status;
	    Status = 0;
        /* Get our heap */
        PdxInitializeHeap ();
        /* Initialize POSIX+ and Sessions */
        Status = PdxInitializeDirectories ();
       if (!NT_SUCCESS(Status)) return Status;
       /* LPCs dispatchers */
       Status = PdxInitializeListeners ();
       if (!NT_SUCCESS(Status)) return Status;
       /* Terminal manager */
       Status = PsxInitializeSessions ();
       if (!NT_SUCCESS(Status)) return Status;
       /* Process manager */
       Status = PsxInitializeProcesses ();
       if (!NT_SUCCESS(Status)) return Status;
       /* OK. Run! */
       Status = PdxRunServer ();
        /* Done */
        return Status;
}
/* EOF */