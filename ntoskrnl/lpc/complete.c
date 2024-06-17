

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* PRIVATE FUNCTIONS *********************************************************/

/* PUBLIC FUNCTIONS **********************************************************/

NTSTATUS
NTAPI
NtConnectPort(
    _Out_ PHANDLE PortHandle,
    _In_ PUNICODE_STRING PortName,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Inout_opt_ PPORT_VIEW ClientView,
    _Inout_opt_ PREMOTE_PORT_VIEW ServerView,
    _Out_opt_ PULONG MaxMessageLength,
    _Inout_opt_ PVOID ConnectionInformation,
    _Inout_opt_ PULONG ConnectionInformationLength)
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
