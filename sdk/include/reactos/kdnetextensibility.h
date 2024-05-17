#pragma once

typedef NTSTATUS
(NTAPI *KD_GET_RX_PACKET)(
    _In_ PVOID Adapter,
    _Out_ PULONG Handle,
    _Out_ PVOID *Packet,
    _Out_ PULONG Length);

typedef VOID
(NTAPI *KD_RELEASE_RX_PACKET)(
    _In_ PVOID Adapter,
    _In_ ULONG Handle);

typedef NTSTATUS
(NTAPI *KD_GET_TX_PACKET)(
    _In_ PVOID Adapter,
    _Out_ PULONG Handle);

typedef NTSTATUS
(NTAPI *KD_SEND_TX_PACKET)(
    _In_ PVOID Adapter,
    _In_ ULONG Handle,
    _In_ ULONG Length);

typedef PVOID
(NTAPI *KD_GET_PACKET_ADDRESS)(
    _In_ PVOID Adapter,
    _In_ ULONG Handle);

typedef ULONG
(NTAPI *KD_GET_PACKET_LENGTH)(
    _In_ PVOID Adapter,
    _In_ ULONG Handle);

#define KDNET_EXT_EXPORTS 13

typedef struct _KDNET_EXTENSIBILITY_EXPORTS
{
    ULONG FunctionCount;
    PVOID KdInitializeController;
    PVOID KdShutdownController;
    PVOID KdSetHibernateRange;
    KD_GET_RX_PACKET KdGetRxPacket;
    KD_RELEASE_RX_PACKET KdReleaseRxPacket;
    KD_GET_TX_PACKET KdGetTxPacket;
    KD_SEND_TX_PACKET KdSendTxPacket;
    KD_GET_PACKET_ADDRESS KdGetPacketAddress;
    KD_GET_PACKET_LENGTH KdGetPacketLength;
    PVOID KdGetHardwareContextSize;
    PVOID KdDeviceControl;
    PVOID KdReadSerialByte;
    PVOID KdWriteSerialByte;
    PVOID DebugSerialOutputInit;
    PVOID DebugSerialOutputByte;
} KDNET_EXTENSIBILITY_EXPORTS, *PKDNET_EXTENSIBILITY_EXPORTS;

#define KDNET_EXT_IMPORTS 30

/* Imports */
typedef ULONG
(NTAPI *GET_PCI_DATA_BY_OFFSET)(
        _In_ ULONG BusNumber,
        _In_ ULONG SlotNumber,
        _Out_writes_bytes_(Length) PVOID Buffer,
        _In_ ULONG Offset,
        _In_ ULONG Length);

typedef ULONG
(NTAPI *SET_PCI_DATA_BY_OFFSET)(
        _In_ ULONG BusNumber,
        _In_ ULONG SlotNumber,
        _In_reads_bytes_(Length) PVOID Buffer,
        _In_ ULONG Offset,
        _In_ ULONG Length);

typedef PHYSICAL_ADDRESS
(NTAPI *GET_PHYSICAL_ADDRESS)(
        _In_ PVOID Address);

typedef VOID
(NTAPI *STALL_EXECUTION_PROCESSOR)(
        _In_ ULONG Microseconds);

typedef VOID
(NTAPI *STALL_EXECUTION_PROCESSOR)(
        _In_ ULONG Microseconds);

typedef UCHAR
(NTAPI *INT_READ_REGISTER_UCHAR)(
        _In_ UCHAR *Register);

typedef USHORT
(NTAPI *INT_READ_REGISTER_USHORT)(
        _In_ USHORT *Register);

typedef ULONG
(NTAPI *INT_READ_REGISTER_ULONG)(
        _In_ ULONG *Register);

typedef ULONG64
(NTAPI *INT_READ_REGISTER_ULONG64)(
        _In_ ULONG64 *Register);

typedef VOID
(NTAPI *INT_WRITE_REGISTER_UCHAR)(
        _In_ UCHAR *Register,
        _In_ UCHAR Value);

typedef VOID
(NTAPI *INT_WRITE_REGISTER_USHORT)(
        _In_ USHORT *Register,
        _In_ USHORT Value);

typedef VOID
(NTAPI *INT_WRITE_REGISTER_ULONG)(
        _In_ ULONG *Register,
        _In_ ULONG Value);

typedef VOID
(NTAPI *INT_WRITE_REGISTER_ULONG64)(
        _In_ ULONG64 *Register,
        _In_ ULONG64 Value);

typedef UCHAR
(NTAPI *INT_READ_PORT_UCHAR)(
        _In_ UCHAR *Port);

typedef USHORT
(NTAPI *INT_READ_PORT_USHORT)(
        _In_ USHORT *Port);

typedef ULONG
(NTAPI *INT_READ_PORT_ULONG)(
        _In_ ULONG *Port);

typedef ULONG64
(NTAPI *INT_READ_PORT_ULONG64)(
        _In_ ULONG64 *Port);

typedef VOID
(NTAPI *INT_WRITE_PORT_UCHAR)(
        _In_ UCHAR *Port,
        _In_ UCHAR Value);

typedef VOID
(NTAPI *INT_WRITE_PORT_USHORT)(
        _In_ USHORT *Port,
        _In_ USHORT Value);

typedef VOID
(NTAPI *INT_WRITE_PORT_ULONG)(
        _In_ ULONG *Port,
        _In_ ULONG Value);

typedef VOID
(NTAPI *INT_WRITE_PORT_ULONG64)(
        _In_ ULONG64 *Register,
        _In_ ULONG64 Value);

typedef VOID
(NTAPI *INT_SET_HIBER_RANGE)(
            IN PVOID HiberContext,
            IN ULONG Flags,
            IN OUT PVOID StartPage,
            IN ULONG Length,
            IN ULONG PageTag);

typedef VOID
(NTAPI *KD_DEBUG_PRINT_F)(
        _In_ PCSTR Format,
        ...);

typedef VOID
(NTAPI *INT_UNMAP_VIRTUAL_ADDRESS)(
        _In_ PVOID VirtualAddress,
        _In_ PFN_COUNT PageCount);
    
typedef PVOID
(NTAPI *INT_MAP_PHYSICAL_MEMORY64)(
            _In_ PHYSICAL_ADDRESS PhysicalAddress,
            _In_ PFN_COUNT PageCount,
            _In_ BOOLEAN FlushCurrentTL);

typedef ULONG64
(NTAPI *INT_READ_CYCLE_COUNTER)(
        VOID);

typedef VOID
(NTAPI *INT_BUGCHECK_EX)(
        _In_ ULONG BugCheckCode,
        _In_ ULONG_PTR BugCheckParameter1,
        _In_ ULONG_PTR BugCheckParameter2,
        _In_ ULONG_PTR BugCheckParameter3,
        _In_ ULONG_PTR BugCheckParameter4);

typedef struct _KDNET_EXTENSIBILITY_IMPORTS
{
    ULONG FunctionCount;
    PKDNET_EXTENSIBILITY_EXPORTS Exports;

    /* Function imports - Windows 10 */
    GET_PCI_DATA_BY_OFFSET         GetPciDataByOffset;
    SET_PCI_DATA_BY_OFFSET         SetPciDataByOffset;
    GET_PHYSICAL_ADDRESS           GetPhysicalAddress;
    STALL_EXECUTION_PROCESSOR      StallExecutionProcessor;
    INT_READ_REGISTER_UCHAR        ReadRegisterUChar;
    INT_READ_REGISTER_USHORT       ReadRegisterUShort;
    INT_READ_REGISTER_ULONG        ReadRegisterULong;
    INT_READ_REGISTER_ULONG64      ReadRegisterULong64;
    INT_WRITE_REGISTER_UCHAR       WriteRegisterUChar;
    INT_WRITE_REGISTER_USHORT      WriteRegisterUShort;
    INT_WRITE_REGISTER_ULONG       WriteRegisterULong;
    INT_WRITE_REGISTER_ULONG64     WriteRegisterULong64;
    INT_READ_PORT_UCHAR            ReadPortUChar;
    INT_READ_PORT_USHORT           ReadPortUShort;
    INT_READ_PORT_ULONG            ReadPortULong;
    INT_READ_PORT_ULONG64          ReadPortULong64;
    INT_WRITE_PORT_UCHAR           WritePortUChar;
    INT_WRITE_PORT_USHORT          WritePortUShort;
    INT_WRITE_PORT_ULONG           WritePortULong;
    INT_WRITE_PORT_ULONG64         WritePortULong64;
    INT_SET_HIBER_RANGE            SetHiberRange;
    INT_BUGCHECK_EX                BugCheckEx;
    INT_MAP_PHYSICAL_MEMORY64      MapPhysicalMemory64;
    INT_UNMAP_VIRTUAL_ADDRESS      UnmapVirtualAddress; 
    INT_READ_CYCLE_COUNTER         ReadCycleCounter;
    KD_DEBUG_PRINT_F               KdNetDbgPrintf;
    NTSTATUS*                      KdNetErrorStatus;
    PWSTR*                         KdNetErrorString;
    PULONG                         KdNetHardwareID;
} KDNET_EXTENSIBILITY_IMPORTS, *PKDNET_EXTENSIBILITY_IMPORTS;

extern PKDNET_EXTENSIBILITY_EXPORTS KdNetExtensibilityExports;

#define KdGetRxPacket KdNetExtensibilityExports->KdGetRxPacket
#define KdReleaseRxPacket KdNetExtensibilityExports->KdReleaseRxPacket
#define KdGetTxPacket KdNetExtensibilityExports->KdGetTxPacket
#define KdSendTxPacket KdNetExtensibilityExports->KdSendTxPacket
#define KdGetPacketAddress KdNetExtensibilityExports->KdGetPacketAddress
#define KdGetPacketLength KdNetExtensibilityExports->KdGetPacketLength

NTSTATUS
NTAPI
KdInitializeLibrary(
    _In_ PKDNET_EXTENSIBILITY_IMPORTS ImportTable,
    _In_opt_ PCHAR LoaderOptions,
    _Inout_ PDEBUG_DEVICE_DESCRIPTOR Device);
