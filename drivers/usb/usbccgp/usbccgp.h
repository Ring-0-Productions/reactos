#ifndef USBEHCI_H__
#define USBEHCI_H__

#include <wdm.h>
#include <hubbusif.h>
#include <usbbusif.h>
#include <usbdlib.h>

#include <stdio.h>

typedef struct
{
    BOOLEAN IsFDO;                                           // is device a FDO or PDO
}COMMON_DEVICE_EXTENSION, *PCOMMON_DEVICE_EXTENSION;

typedef
_Must_inspect_result_
NTSTATUS
(USB_BUSIFFN *PUSB_BUSIFFN_QUERY_BUS_TIME_EX) (
  _In_opt_ PVOID,
  _Out_opt_ PULONG);

typedef
_Must_inspect_result_
NTSTATUS
(USB_BUSIFFN *PUSB_BUSIFFN_QUERY_CONTROLLER_TYPE) (
  _In_opt_ PVOID,
  _Out_opt_ PULONG,
  _Out_opt_ PUSHORT,
  _Out_opt_ PUSHORT,
  _Out_opt_ PUCHAR,
  _Out_opt_ PUCHAR,
  _Out_opt_ PUCHAR,
  _Out_opt_ PUCHAR);

typedef struct _USB_BUS_INTERFACE_USBDI_V3 {
  USHORT Size;
  USHORT Version;
  PVOID BusContext;
  PINTERFACE_REFERENCE InterfaceReference;
  PINTERFACE_DEREFERENCE InterfaceDereference;
  PUSB_BUSIFFN_GETUSBDI_VERSION GetUSBDIVersion;
  PUSB_BUSIFFN_QUERY_BUS_TIME QueryBusTime;
  PUSB_BUSIFFN_SUBMIT_ISO_OUT_URB SubmitIsoOutUrb;
  PUSB_BUSIFFN_QUERY_BUS_INFORMATION QueryBusInformation;
  PUSB_BUSIFFN_IS_DEVICE_HIGH_SPEED IsDeviceHighSpeed;
  PUSB_BUSIFFN_ENUM_LOG_ENTRY EnumLogEntry;
  PUSB_BUSIFFN_QUERY_BUS_TIME_EX QueryBusTimeEx;
  PUSB_BUSIFFN_QUERY_CONTROLLER_TYPE QueryControllerType;
} USB_BUS_INTERFACE_USBDI_V3, *PUSB_BUS_INTERFACE_USBDI_V3;

DEFINE_GUID(USB_BUS_INTERFACE_USBC_CONFIGURATION_GUID,
  0x893b6a96, 0xb7f, 0x4d4d, 0xbd, 0xb4, 0xbb, 0xd4, 0xce, 0xeb, 0xb3, 0x1c);

#define USBC_FUNCTION_FLAG_APPEND_ID 0x1

typedef struct _USBC_FUNCTION_DESCRIPTOR{
  UCHAR FunctionNumber;
  UCHAR NumberOfInterfaces;
  PUSB_INTERFACE_DESCRIPTOR *InterfaceDescriptorList;
  UNICODE_STRING HardwareId;
  UNICODE_STRING CompatibleId;
  UNICODE_STRING FunctionDescription;
  ULONG FunctionFlags;
  PVOID Reserved;
} USBC_FUNCTION_DESCRIPTOR, *PUSBC_FUNCTION_DESCRIPTOR;

typedef
_Must_inspect_result_
NTSTATUS
(USB_BUSIFFN *USBC_START_DEVICE_CALLBACK)(
  _In_ PUSB_DEVICE_DESCRIPTOR DeviceDescriptor,
  _In_ PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor,
  _Outptr_result_bytebuffer_maybenull_(*FunctionDescriptorBufferLength)
    PUSBC_FUNCTION_DESCRIPTOR *FunctionDescriptorBuffer,
  _Out_ PULONG FunctionDescriptorBufferLength,
  _In_ PDEVICE_OBJECT FdoDeviceObject,
  _In_ PDEVICE_OBJECT PdoDeviceObject);

typedef
_Must_inspect_result_
BOOLEAN
(USB_BUSIFFN *USBC_PDO_ENABLE_CALLBACK)(
  _In_ PVOID Context,
  _In_ USHORT FirstInterfaceNumber,
  _In_ USHORT NumberOfInterfaces,
  _In_ UCHAR FunctionClass,
  _In_ UCHAR FunctionSubClass,
  _In_ UCHAR FunctionProtocol);

#define USBC_DEVICE_CONFIGURATION_INTERFACE_VERSION_1         0x0001

typedef struct _USBC_DEVICE_CONFIGURATION_INTERFACE_V1 {
  USHORT Size;
  USHORT Version;
  PVOID Context;
  PINTERFACE_REFERENCE InterfaceReference;
  PINTERFACE_DEREFERENCE InterfaceDereference;
  USBC_START_DEVICE_CALLBACK StartDeviceCallback;
  USBC_PDO_ENABLE_CALLBACK PdoEnableCallback;
  PVOID Reserved[7];
} USBC_DEVICE_CONFIGURATION_INTERFACE_V1, *PUSBC_DEVICE_CONFIGURATION_INTERFACE_V1;

typedef struct
{
    COMMON_DEVICE_EXTENSION Common;                          // shared with PDO
    PDRIVER_OBJECT DriverObject;                             // driver object
    PDEVICE_OBJECT PhysicalDeviceObject;                     // physical device object
    PDEVICE_OBJECT NextDeviceObject;                         // lower device object
    PUSB_DEVICE_DESCRIPTOR DeviceDescriptor;                 // usb device descriptor
    PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor;   // usb configuration descriptor
    DEVICE_CAPABILITIES Capabilities;                        // device capabilities
    PUSBD_INTERFACE_LIST_ENTRY InterfaceList;                // interface list
    ULONG InterfaceListCount;                                // interface list count
    USBD_CONFIGURATION_HANDLE ConfigurationHandle;           // configuration handle
    USBC_DEVICE_CONFIGURATION_INTERFACE_V1 BusInterface;     // bus custom enumeration interface
    PUSBC_FUNCTION_DESCRIPTOR FunctionDescriptor;            // usb function descriptor
    ULONG FunctionDescriptorCount;                           // number of function descriptor
    PDEVICE_OBJECT * ChildPDO;                               // child pdos
    LIST_ENTRY ResetPortListHead;                            // reset port list head
    LIST_ENTRY CyclePortListHead;                            // cycle port list head
    UCHAR ResetPortActive;                                   // reset port active
    UCHAR CyclePortActive;                                   // cycle port active
    KSPIN_LOCK Lock;                                         // reset / cycle port list lock
}FDO_DEVICE_EXTENSION, *PFDO_DEVICE_EXTENSION;

#define USBCCPG_TAG 'cbsu'

typedef struct
{
    COMMON_DEVICE_EXTENSION Common;                          // shared with FDO
    PUSBC_FUNCTION_DESCRIPTOR FunctionDescriptor;            // function descriptor
    PDEVICE_OBJECT NextDeviceObject;                         // next device object
    DEVICE_CAPABILITIES Capabilities;                        // device capabilities
    ULONG FunctionIndex;                                     // function index
    USB_DEVICE_DESCRIPTOR DeviceDescriptor;                  // usb device descriptor
    PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor;   // usb configuration descriptor
    USBD_CONFIGURATION_HANDLE ConfigurationHandle;           // configuration handle
    PUSBD_INTERFACE_LIST_ENTRY InterfaceList;                // interface list
    ULONG InterfaceListCount;                                // interface list count
    PFDO_DEVICE_EXTENSION FDODeviceExtension;                // pointer to fdo's pdo list
}PDO_DEVICE_EXTENSION, *PPDO_DEVICE_EXTENSION;

/* descriptor.c */

VOID
DumpConfigurationDescriptor(
    IN PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor);

NTSTATUS
USBCCGP_GetDescriptors(
    IN PDEVICE_OBJECT DeviceObject);

NTSTATUS
USBCCGP_SelectConfiguration(
    IN PDEVICE_OBJECT DeviceObject,
    IN PFDO_DEVICE_EXTENSION DeviceExtension);

NTSTATUS
NTAPI
USBCCGP_GetDescriptor(
    IN PDEVICE_OBJECT DeviceObject,
    IN UCHAR DescriptorType,
    IN ULONG DescriptorLength,
    IN UCHAR DescriptorIndex,
    IN LANGID LanguageId,
    OUT PVOID *OutDescriptor);

NTSTATUS
NTAPI
USBCCGP_GetStringDescriptor(
    IN PDEVICE_OBJECT DeviceObject,
    IN ULONG DescriptorLength,
    IN UCHAR DescriptorIndex,
    IN LANGID LanguageId,
    OUT PVOID *OutDescriptor);

ULONG
CountInterfaceDescriptors(
    IN PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor);

NTSTATUS
AllocateInterfaceDescriptorsArray(
    IN PUSB_CONFIGURATION_DESCRIPTOR ConfigurationDescriptor,
    OUT PUSB_INTERFACE_DESCRIPTOR **OutArray);

/* misc.c */

NTSTATUS
USBCCGP_SyncUrbRequest(
    IN PDEVICE_OBJECT DeviceObject,
    OUT PURB UrbRequest);

PVOID
AllocateItem(
    IN POOL_TYPE PoolType,
    IN ULONG ItemSize);

VOID
FreeItem(
    IN PVOID Item);

VOID
DumpFunctionDescriptor(
    IN PUSBC_FUNCTION_DESCRIPTOR FunctionDescriptor,
    IN ULONG FunctionDescriptorCount);

/* fdo.c */

NTSTATUS
FDO_Dispatch(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp);

/* pdo.c */

NTSTATUS
PDO_Dispatch(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp);

/* function.c */

NTSTATUS
USBCCGP_QueryInterface(
    IN PDEVICE_OBJECT DeviceObject,
    OUT PUSBC_DEVICE_CONFIGURATION_INTERFACE_V1 BusInterface);

NTSTATUS
USBCCGP_EnumerateFunctions(
    IN PDEVICE_OBJECT DeviceObject);

#endif /* USBEHCI_H__ */
