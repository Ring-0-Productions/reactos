

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* PUBLIC FUNCTIONS **********************************************************/

NTSTATUS
NTAPI
LpcRequestPort(
    _In_ PVOID Port,
    _In_ PPORT_MESSAGE LpcMessage)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
LpcRequestWaitReplyPort(
    _In_ PVOID Port,
    _In_ PPORT_MESSAGE LpcMessageRequest,
    _Out_ PPORT_MESSAGE LpcMessageReply)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtRequestPort(
    _In_ HANDLE PortHandle,
    _In_ PPORT_MESSAGE LpcMessage)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS
NTAPI
NtRequestWaitReplyPort(
    _In_ HANDLE PortHandle,
    _Out_ PPORT_MESSAGE LpcReply,
    _In_ PPORT_MESSAGE LpcRequest)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

/* EOF */
