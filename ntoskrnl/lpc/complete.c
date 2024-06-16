

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* PRIVATE FUNCTIONS *********************************************************/

/* PUBLIC FUNCTIONS **********************************************************/

NTSTATUS
NTAPI
NtAcceptConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_opt_ PVOID PortContext,
    _In_ PPORT_MESSAGE ConnectionRequest,
    _In_ BOOLEAN AcceptConnection,
    _Inout_opt_ PPORT_VIEW ServerView,
    _Out_opt_ PREMOTE_PORT_VIEW ClientView)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtCompleteConnectPort(_In_ HANDLE PortHandle)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

/* EOF */
