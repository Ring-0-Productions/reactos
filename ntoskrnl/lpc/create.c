
/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* PRIVATE FUNCTIONS *********************************************************/

/* PUBLIC FUNCTIONS **********************************************************/

NTSTATUS
NTAPI
NtCreatePort(
    _Out_ PHANDLE PortHandle,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG MaxConnectionInfoLength,
    _In_ ULONG MaxMessageLength,
    _In_ ULONG MaxPoolUsage)
{
    PAGED_CODE();

    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
NtCreateWaitablePort(
    _Out_ PHANDLE PortHandle,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG MaxConnectInfoLength,
    _In_ ULONG MaxDataLength,
    _In_opt_ ULONG NPMessageQueueSize)
{
    PAGED_CODE();

    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

/* EOF */
