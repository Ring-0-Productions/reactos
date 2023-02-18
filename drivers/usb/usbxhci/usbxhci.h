/*
 * PROJECT:         ReactOS system libraries
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         resources definitions
 * PROGRAMMER:      Rama Teja Gampa <ramateja.g@gmail.com>
*/
#ifndef USBXHCI_H__
#define USBXHCI_H__

#include <ntddk.h>
#include <windef.h>
#include <stdio.h>
#include <hubbusif.h>
#include <usbbusif.h>
#include <usbdlib.h>
#include <usbport/usbmport.h>
#include "xhcitrb.h"
#include "hardware.h"

extern USBPORT_REGISTRATION_PACKET RegPacket;

#define XHCI_FLAGS_CONTROLLER_SUSPEND 0x01
#define XHCI_MAX_ENDPOINTS 32;

#define EHCI_MAX_CONTROL_TRANSFER_SIZE    0x10000
#define EHCI_MAX_INTERRUPT_TRANSFER_SIZE  0x1000
#define EHCI_MAX_BULK_TRANSFER_SIZE       0x400000
#define EHCI_MAX_FS_ISO_TRANSFER_SIZE     0x40000
#define EHCI_MAX_HS_ISO_TRANSFER_SIZE     0x180000


#define EHCI_MAX_CONTROL_TD_COUNT    6
#define EHCI_MAX_INTERRUPT_TD_COUNT  4
#define EHCI_MAX_BULK_TD_COUNT       209

/* Generic TRBs ***********************************************************************************/

typedef struct _XHCI_GENERIC_TRB {
    ULONG Word0;
    ULONG Word1;
    ULONG Word2;
    ULONG Word3;
}XHCI_GENERIC_TRB, *PXHCI_GENERIC_TRB;
C_ASSERT(sizeof(XHCI_GENERIC_TRB) == 16);

typedef struct _XHCI_EVENT_GENERIC_TRB
{
    ULONG Word0;
    ULONG Word1;
    ULONG Word2;
    struct
    {
        ULONG CycleBit          : 1;
        ULONG RsvdZ1            : 9;
        ULONG TRBType           : 6;
        ULONG RsvdZ2            : 8;
        ULONG SlotID            : 8;
    };
}XHCI_EVENT_GENERIC_TRB;
C_ASSERT(sizeof(XHCI_EVENT_GENERIC_TRB) == 16);

typedef union _XHCI_COMMAND_TRB
{
    XHCI_COMMAND_NO_OP_TRB NoOperation;
    XHCI_ENABLE_SLOT_COMMAND_TRB SlotEnable;
    XHCI_ADDRESS_DEVICE_COMMAND_TRB AddressDevice;
}XHCI_COMMAND_TRB, *PXHCI_COMMAND_TRB;
C_ASSERT(sizeof(XHCI_COMMAND_TRB) == 16);

typedef union _XHCI_CONTROL_TRB
{
    XHCI_CONTROL_SETUP_TRB  SetupTRB;
    XHCI_CONTROL_DATA_TRB   DataTRB;
    XHCI_CONTROL_STATUS_TRB StatusTRB;
    XHCI_GENERIC_TRB    GenericTRB;
} XHCI_CONTROL_TRB, *PXHCI_CONTROL_TRB;
C_ASSERT(sizeof(XHCI_CONTROL_TRB) == 16);

typedef union _XHCI_EVENT_TRB
{
    XHCI_EVENT_COMMAND_COMPLETION_TRB   CommandCompletionTRB;
    XHCI_EVENT_PORT_STATUS_CHANGE_TRB   PortStatusChangeTRB;
    XHCI_EVENT_GENERIC_TRB              EventGenericTRB;
} XHCI_EVENT_TRB, *PXHCI_EVENT_TRB;
C_ASSERT(sizeof(XHCI_EVENT_TRB) == 16);

typedef union _XHCI_TRB
{
    XHCI_COMMAND_TRB    CommandTRB;
    XHCI_LINK_TRB       LinkTRB;
    XHCI_CONTROL_TRB    ControlTRB;
    XHCI_EVENT_TRB      EventTRB;
    XHCI_GENERIC_TRB    GenericTRB;
} XHCI_TRB, *PXHCI_TRB;
C_ASSERT(sizeof(XHCI_TRB) == 16);

extern USBPORT_REGISTRATION_PACKET RegPacket;

typedef struct  _XHCI_DEVICE_CONTEXT_BASE_ADD_ARRAY
{
    PHYSICAL_ADDRESS ContextBaseAddr [256];
} XHCI_DEVICE_CONTEXT_BASE_ADD_ARRAY, *PXHCI_DEVICE_CONTEXT_BASE_ADD_ARRAY;

typedef struct _XHCI_SEGMENT
{
    XHCI_TRB XhciTrb[256];
    PVOID nextSegment;
} XHCI_SEGMENT, *PXHCI_SEGMENT;

typedef struct _XHCI_RING
{
    XHCI_SEGMENT firstSeg;
    PXHCI_TRB dequeue_pointer;
    PXHCI_TRB enqueue_pointer;
    PXHCI_SEGMENT enqueue_segment;
    PXHCI_SEGMENT dequeue_segment;
    struct
    {
        UCHAR ProducerCycleState : 1;
        UCHAR ConsumerCycleState : 1;
    };
} XHCI_RING, *PXHCI_RING;

typedef struct _XHCI_TRANSFER_RING
{
    XHCI_SEGMENT firstSeg;
    PXHCI_TRB dequeue_pointer;
    PXHCI_TRB enqueue_pointer;
    PXHCI_SEGMENT enqueue_segment;
    PXHCI_SEGMENT dequeue_segment;
    struct
    {
        UCHAR ProducerCycleState             : 1;
        UCHAR ConsumerCycleState             : 1;
    };
} XHCI_TRANSFER_RING, *PXHCI_TRANSFER_RING;


/* 6.5 */
typedef struct _XHCI_EVENT_RING_SEGMENT_TABLE
{
    ULONGLONG RingSegmentBaseAddr;
    struct
    {
        ULONGLONG RingSegmentSize :  16;
        ULONGLONG RsvdZ           :  48;
    };
} XHCI_EVENT_RING_SEGMENT_TABLE;


typedef struct _XHCI_HC_RESOURCES
{
    XHCI_DEVICE_CONTEXT_BASE_ADD_ARRAY DCBAA;
    DECLSPEC_ALIGN(16) XHCI_RING         EventRing ;
    DECLSPEC_ALIGN(64) XHCI_RING         CommandRing ;
    DECLSPEC_ALIGN(64) XHCI_RING         TransferRing ;
    DECLSPEC_ALIGN(64) XHCI_EVENT_RING_SEGMENT_TABLE EventRingSegTable;
} XHCI_HC_RESOURCES, *PXHCI_HC_RESOURCES;
C_ASSERT (FIELD_OFFSET(XHCI_HC_RESOURCES,EventRing)% 16 == 0);
C_ASSERT (FIELD_OFFSET(XHCI_HC_RESOURCES,CommandRing)% 64 == 0);
C_ASSERT (FIELD_OFFSET(XHCI_HC_RESOURCES,TransferRing)% 64 == 0);
C_ASSERT (FIELD_OFFSET(XHCI_HC_RESOURCES,EventRingSegTable)% 64 == 0);

typedef struct _XHCI_EXTENSION
{
    ULONG Reserved;
    ULONG Flags;
    PULONG BaseIoAdress;
    PULONG OperationalRegs;
    PULONG RunTimeRegisterBase;
    PULONG DoorBellRegisterBase;
    UCHAR FrameLengthAdjustment;
    BOOLEAN IsStarted;
    USHORT HcSystemErrors;
    ULONG PortRoutingControl;
    USHORT NumberOfPorts; // HCSPARAMS1 => N_PORTS
    USHORT PortPowerControl; // HCSPARAMS => Port Power Control (PPC)
    USHORT PageSize;
    USHORT MaxScratchPadBuffers;
    PMDL ScratchPadArrayMDL;
    PMDL ScratchPadBufferMDL;
    PXHCI_HC_RESOURCES HcResourcesVA;
    PHYSICAL_ADDRESS HcResourcesPA;
} XHCI_EXTENSION, *PXHCI_EXTENSION;

typedef union _XHCI_LINK_ADDR
{
    struct
    {
        ULONGLONG RsvdZ1                     : 4;
        ULONGLONG RingSegmentPointerLo       : 28;
        ULONGLONG RingSegmentPointerHi       : 32;
    };
    ULONGLONG AsULONGLONG;
} XHCI_LINK_ADDR;

/* 6.6 */
typedef union _XHCI_SCRATCHPAD_BUFFER_ARRAY
{
    struct
    {
        ULONGLONG RsvdZ1              :  12;
        ULONGLONG bufferBaseAddr      :  52;
    };
    ULONGLONG AsULONGLONG;
} XHCI_SCRATCHPAD_BUFFER_ARRAY, *PXHCI_SCRATCHPAD_BUFFER_ARRAY;
C_ASSERT(sizeof(XHCI_SCRATCHPAD_BUFFER_ARRAY) == 8);

/* Endpoint Context *******************************************************************************/

/* 6.2.3 */
typedef struct _XHCI_ENDPOINT_CONTEXT
{
    /* Offset 00h */
    struct
    {
        ULONG EPState                        : 3;
        ULONG RsvdZ1                         : 5;
        ULONG Mult                           : 2;
        ULONG MaxPStreams                    : 5;
        ULONG LSA                            : 1;
        ULONG Interval                       : 8;
        ULONG MaxESITHigh                    : 8;
    };
    /* Offset 04h */
    struct
    {
        ULONG RsvdZ2                         : 1;
        ULONG CErr                           : 2;
        ULONG EPType                         : 3;
        ULONG RsvdZ3                         : 1;
        ULONG HID                            : 1;
        ULONG MaxBurstSize                   : 8;
        ULONG MaxPacketSize                  : 16;

    };
    /* Offset 08h */
    struct
    {
        ULONG DCS                            : 1;
        ULONG Rsvdz4                         : 3;
        ULONGLONG TRDeqPtr                   : 60;
    };

    /* Offset 10h */
    struct
    {
        ULONG AverageTRBLength               : 16;
        ULONG MaxESITPayload                 : 16;
    };
} XHCI_ENDPOINT_CONTEXT, *PXHCI_ENDPOINT_CONTEXT;

typedef struct _XHCI_ISO_ENDPOINT
{
    UINT32 temp : 1;
} XHCI_ISO_ENDPOINT, *PXHCI_ISO_ENDPOINT;

typedef struct _XHCI_ENDPOINT_TYPE
{
    XHCI_ISO_ENDPOINT   IsoEndpoint;

} XHCI_ENDPOINT_TYPE, *PXHCI_ENDPOINT_TYPE;


/* Slot Context ***********************************************************************************/

/* 6.2.2 */
typedef struct _XHCI_SLOT_CONTEXT
{
    struct
    {
        ULONG RouteString                    : 20;
        ULONG Speed                          : 4;   /* Deprecated in latest spec */
        ULONG RsvdZ1                         : 1;
        ULONG MultiTT                        : 1;
        ULONG Hub                            : 1;
        ULONG ContextEntries                 : 5;
    };
    struct
    {
        ULONG MaxExitLatency                 : 16;
        ULONG RootHubPortNumber              : 8;
        ULONG NumberOfPorts                  : 8;
    };
    struct
    {
        ULONG ParentHubSlotID                : 8;
        ULONG ParentPortNumber               : 8;
        ULONG TTThinkTime                    : 2;
        ULONG RsvdZ2                         : 4;
        ULONG InterrupterTarget              : 10;
    };
    struct
    {
        ULONG USBDeviceAddress               : 8;
        ULONG RsvdZ3                         : 19;
        ULONG SlotState                      : 5;
    };
    struct
    {
        ULONG RsvdZ4                         : 32;
    };
    struct
    {
        ULONG RsvdZ5                         : 32;
    };
    struct
    {
        ULONG RsvdZ6                         : 32;
    };
    struct
    {
        ULONG RsvdZ7                         : 32;
    };
} XHCI_SLOT_CONTEXT, *PXHCI_SLOT_CONTEXT;

/* Input Control Context **************************************************************************/

/* 6.2.5.1 */
typedef struct _XHCI_INPUT_CONTROL_CONTEXT
{
    //Offset 00h
    struct
    {
        ULONG RsvdZ1                         : 2;
        ULONG DropContextFlags               : 30;
    };
    // Offset 04h
    struct
    {
        ULONG A0                             : 1;
        ULONG A1                             : 1;
        ULONG AddContextFlags                : 30;
    };
    struct
    {
        ULONG RsvdZ2                         : 32;
    };
      struct
    {
        ULONG RsvdZ3                         : 32;
    };
      struct
    {
        ULONG RsvdZ4                         : 32;
    };
      struct
    {
        ULONG RsvdZ5                         : 32;
    };
      struct
    {
        ULONG RsvdZ6                         : 32;
    };
    // Offset 1Ch
    struct
    {
        ULONG ConfigVal                      : 8;
        ULONG InterfaceNum                   : 8;
        ULONG AltSetting                     : 8;
        ULONG RsvdZ7                         : 8;
    };
} XHCI_INPUT_CONTROL_CONTEXT, *PXHCI_INPUT_CONTROL_CONTEXT;

/* Device Context *********************************************************************************/

/* 6.2.1 */
typedef struct _XHCI_DEVICE_CONTEXT
{
    struct
    {
        ULONG RsvdZ1                         : 6;
        ULONGLONG DeviceContextBA            : 58;
    };
    struct
    {
        ULONG RsvdZ2                         : 6;
        ULONGLONG ScratchPadBufferBA         : 58;
    };
} XHCI_DEVICE_CONTEXT, *PXHCI_DEVICE_CONTEXT;


typedef struct _XHCI_ENDPOINT
{
    ULONG EndpointStatus;
    ULONG EndpointState;
    /* xhci_device */
    /*xhci_slot*/
    USBPORT_ENDPOINT_PROPERTIES EndpointProperties;
    UINT32 ContextIndex;
    XHCI_ENDPOINT_TYPE EndpointType;
    UINT32 Interval;
    XHCI_ENDPOINT_CONTEXT *Context;
    XHCI_RING TransferRing;

    PVOID DmaBufferVA;
    ULONG DmaBufferPA;
    PVOID FirstTD;
    ULONG MaxTDs;
    ULONG PendingTDs;
    ULONG RemainTDs;
 // PEHCI_HCD_QH QH;
 // PEHCI_HCD_TD HcdHeadP;
  //PEHCI_HCD_TD HcdTailP;
   LIST_ENTRY ListTDs;
 // const EHCI_PERIOD * PeriodTable;
//  PEHCI_STATIC_QH StaticQH;
} XHCI_ENDPOINT, *PXHCI_ENDPOINT;

/* Input Context **********************************************************************************/

/* 6.2.5 */
typedef struct _XHCI_INPUT_CONTEXT
{
    XHCI_INPUT_CONTROL_CONTEXT InputContext;
    XHCI_SLOT_CONTEXT SlotContext;
    XHCI_ENDPOINT EndpointList[31]; /* Hard value in spec */
} XHCI_INPUT_CONTEXT, *PXHCI_INPUT_CONTEXT;

/* Device Context *********************************************************************************/

/* 6.2.5 */
typedef struct _XHCI_OUTPUT_DEVICE_CONTEXT
{
    PXHCI_SLOT_CONTEXT SlotContext;
    XHCI_ENDPOINT EndpointList[31]; /* Hard value in spec */
} XHCI_OUTPUT_DEVICE_CONTEXT, *PXHCI_OUTPUT_DEVICE_CONTEXT;


/* XHCI Transfer follows USBPORT Transfer */
typedef struct _XHCI_TRANSFER {
  ULONG Reserved;
  PUSBPORT_TRANSFER_PARAMETERS TransferParameters;
  ULONG USBDStatus;
  ULONG TransferLen;
  PXHCI_ENDPOINT XhciEndpoint;
  ULONG PendingTDs;
  ULONG TransferOnAsyncList;
} XHCI_TRANSFER, *PXHCI_TRANSFER;

//roothub functions
VOID
NTAPI
XHCI_RH_GetRootHubData(_Inout_ PVOID hcExtension,
                       _Inout_ PVOID rootHubData);

MPSTATUS
NTAPI
XHCI_RH_GetStatus(
  IN PVOID xhciExtension,
  IN PUSHORT Status);

MPSTATUS
NTAPI
XHCI_RH_GetPortStatus(
  IN PVOID xhciExtension,
  IN USHORT Port,
  IN PUSB_PORT_STATUS_AND_CHANGE PortStatus);

MPSTATUS
NTAPI
XHCI_RH_GetHubStatus(
  IN PVOID xhciExtension,
  IN PUSB_HUB_STATUS_AND_CHANGE HubStatus);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortReset(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortPower(_Inout_ PVOID hcExtension,
                            _In_    USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortEnable(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortSuspend(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnable(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortPower(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspend(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnableChange(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortConnectChange(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortResetChange(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspendChange(
  IN PVOID xhciExtension,
  IN USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortOvercurrentChange(
  IN PVOID xhciExtension,
  IN USHORT Port);

VOID
NTAPI
XHCI_RH_DisableIrq(_In_ PVOID hcExtension);

VOID
NTAPI
XHCI_RH_EnableIrq(_In_ PVOID hcExtension);
//-----------------------------------------------------------------------
//priavte
VOID
NTAPI
XHCI_PortStatusChange(_Inout_ PXHCI_EXTENSION XhciExtension, _In_ ULONG PortID);

MPSTATUS
NTAPI
XHCI_SendCommand (IN XHCI_TRB CommandTRB,
                  IN PXHCI_EXTENSION XhciExtension);

                  VOID
NTAPI
XHCI_Write64bitReg(IN PULONG BaseAddr,
                   IN ULONGLONG Data);
#endif /* USBXHCI_H__ */