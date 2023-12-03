#include <ntddk.h>
#include <windef.h>
#include <hubbusif.h>
#include <drivers/usbport/usbmport.h>

EXTERN_C
NTSTATUS
NTAPI
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath)
{
    return 0;
}
