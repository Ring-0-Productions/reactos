/*
 * PROJECT:     FreeLoader UEFI Support
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Hardware detection routines
 * COPYRIGHT:   Copyright 2022 Justin Miller <justinmiller100@gmail.com>
 */

/* INCLUDES ******************************************************************/

#include <uefildr.h>
#include <drivers/bootvid/framebuf.h>

#include <debug.h>
DBG_DEFAULT_CHANNEL(WARNING);

/* GLOBALS *******************************************************************/

extern EFI_SYSTEM_TABLE * GlobalSystemTable;
extern EFI_HANDLE GlobalImageHandle;
extern UCHAR PcBiosDiskCount;
extern EFI_MEMORY_DESCRIPTOR* EfiMemoryMap;
extern UINT32 FreeldrDescCount;

BOOLEAN AcpiPresent = FALSE;

/* Maximum number of COM and LPT ports */
#define MAX_COM_PORTS   4
#define MAX_LPT_PORTS   3

/* No Mouse */
#define MOUSE_TYPE_NONE            0
/* Microsoft Mouse with 2 buttons */
#define MOUSE_TYPE_MICROSOFT       1
/* Logitech Mouse with 3 buttons */
#define MOUSE_TYPE_LOGITECH        2
/* Microsoft Wheel Mouse (aka Z Mouse) */
#define MOUSE_TYPE_WHEELZ          3
/* Mouse Systems Mouse */
#define MOUSE_TYPE_MOUSESYSTEMS    4


/* Timeout in ms for sending to keyboard controller. */
#define CONTROLLER_TIMEOUT                              250

/* PS2 stuff */

/* Controller registers. */
#define CONTROLLER_REGISTER_STATUS                      0x64
#define CONTROLLER_REGISTER_CONTROL                     0x64
#define CONTROLLER_REGISTER_DATA                        0x60

/* Controller commands. */
#define CONTROLLER_COMMAND_READ_MODE                    0x20
#define CONTROLLER_COMMAND_WRITE_MODE                   0x60
#define CONTROLLER_COMMAND_GET_VERSION                  0xA1
#define CONTROLLER_COMMAND_MOUSE_DISABLE                0xA7
#define CONTROLLER_COMMAND_MOUSE_ENABLE                 0xA8
#define CONTROLLER_COMMAND_TEST_MOUSE                   0xA9
#define CONTROLLER_COMMAND_SELF_TEST                    0xAA
#define CONTROLLER_COMMAND_KEYBOARD_TEST                0xAB
#define CONTROLLER_COMMAND_KEYBOARD_DISABLE             0xAD
#define CONTROLLER_COMMAND_KEYBOARD_ENABLE              0xAE
#define CONTROLLER_COMMAND_WRITE_MOUSE_OUTPUT_BUFFER    0xD3
#define CONTROLLER_COMMAND_WRITE_MOUSE                  0xD4

/* Controller status */
#define CONTROLLER_STATUS_OUTPUT_BUFFER_FULL            0x01
#define CONTROLLER_STATUS_INPUT_BUFFER_FULL             0x02
#define CONTROLLER_STATUS_SELF_TEST                     0x04
#define CONTROLLER_STATUS_COMMAND                       0x08
#define CONTROLLER_STATUS_UNLOCKED                      0x10
#define CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL      0x20
#define CONTROLLER_STATUS_GENERAL_TIMEOUT               0x40
#define CONTROLLER_STATUS_PARITY_ERROR                  0x80
#define AUX_STATUS_OUTPUT_BUFFER_FULL                   (CONTROLLER_STATUS_OUTPUT_BUFFER_FULL | \
                                                         CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL)

/* FUNCTIONS *****************************************************************/

#define EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID \
  {0x2F707EBB,0x4A1A,0x11d4,\
    {0x9A,0x38,0x00,0x90,0x27,0x3F,0xC1,0x4D}}
extern EFI_SYSTEM_TABLE * GlobalSystemTable;
extern EFI_HANDLE GlobalImageHandle;


BOOLEAN
PcFindPciBios(PPCI_REGISTRY_INFO BusData)
{
    EFI_STATUS Status;
    EFI_GUID guid = EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID;
    EFI_HANDLE* handles = NULL;
     UINTN count;
         count = 0;
    Status = GlobalSystemTable->BootServices->LocateHandleBuffer(ByProtocol, &guid, NULL, &count, &handles);
    if (Status != EFI_SUCCESS)
    {
    }
//    Status = bs->LocateHandleBuffer(ByProtocol, &guid, NULL, &count, &handles);

      BusData->MajorRevision = 0x02;
      BusData->MinorRevision = 0x10;
      BusData->NoBuses = count;
      BusData->HardwareMechanism = 1;
        return TRUE;

}




static
PPCI_IRQ_ROUTING_TABLE
GetPciIrqRoutingTable(VOID)
{
    PPCI_IRQ_ROUTING_TABLE Table;
    PUCHAR Ptr;
    ULONG Sum;
    ULONG i;

    Table = (PPCI_IRQ_ROUTING_TABLE)0xF0000;
    while ((ULONG_PTR)Table < 0x100000)
    {
        if (Table->Signature == 'RIP$')
        {
            TRACE("Found signature\n");

            if (Table->TableSize < FIELD_OFFSET(PCI_IRQ_ROUTING_TABLE, Slot) ||
                Table->TableSize % 16 != 0)
            {
                ERR("Invalid routing table size (%u) at 0x%p. Continue searching...\n", Table->TableSize, Table);
                Table = (PPCI_IRQ_ROUTING_TABLE)((ULONG_PTR)Table + 0x10);
                continue;
            }

            Ptr = (PUCHAR)Table;
            Sum = 0;
            for (i = 0; i < Table->TableSize; i++)
            {
                Sum += Ptr[i];
            }

            if ((Sum & 0xFF) != 0)
            {
                ERR("Invalid routing table checksum (%#lx) at 0x%p. Continue searching...\n", Sum & 0xFF, Table);
            }
            else
            {
                TRACE("Valid checksum (%#lx): found routing table at 0x%p\n", Sum & 0xFF, Table);
                return Table;
            }
        }

        Table = (PPCI_IRQ_ROUTING_TABLE)((ULONG_PTR)Table + 0x10);
    }

    ERR("No valid routing table found!\n");

    return NULL;
}

VOID
DetectPciIrqRoutingTable(PCONFIGURATION_COMPONENT_DATA BusKey)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    PPCI_IRQ_ROUTING_TABLE Table;
    PCONFIGURATION_COMPONENT_DATA TableKey;
    ULONG Size;

    Table = GetPciIrqRoutingTable();
    if (Table != NULL)
    {
        TRACE("Table size: %u\n", Table->TableSize);

        /* Set 'Configuration Data' value */
        Size = FIELD_OFFSET(CM_PARTIAL_RESOURCE_LIST, PartialDescriptors) +
               2 * sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR) + Table->TableSize;
        PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
        if (PartialResourceList == NULL)
        {
            ERR("Failed to allocate resource descriptor\n");
            return;
        }

        /* Initialize resource descriptor */
        RtlZeroMemory(PartialResourceList, Size);
        PartialResourceList->Version = 1;
        PartialResourceList->Revision = 1;
        PartialResourceList->Count = 2;

        PartialDescriptor = &PartialResourceList->PartialDescriptors[0];
        PartialDescriptor->Type = CmResourceTypeBusNumber;
        PartialDescriptor->ShareDisposition = CmResourceShareDeviceExclusive;
        PartialDescriptor->u.BusNumber.Start = 0;
        PartialDescriptor->u.BusNumber.Length = 1;

        PartialDescriptor = &PartialResourceList->PartialDescriptors[1];
        PartialDescriptor->Type = CmResourceTypeDeviceSpecific;
        PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
        PartialDescriptor->u.DeviceSpecificData.DataSize = Table->TableSize;

        memcpy(&PartialResourceList->PartialDescriptors[2],
               Table,
               Table->TableSize);

            FldrCreateComponentKey(BusKey,
                               PeripheralClass,
                               RealModeIrqRoutingTable,
                               0x0,
                               0x0,
                               0xFFFFFFFF,
                               "PCI Real-mode IRQ Routing Table",
                               PartialResourceList,
                               Size,
                               &TableKey);
    }
}


VOID
DetectPci(PCONFIGURATION_COMPONENT_DATA SystemKey, ULONG *BusNumber)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    PCI_REGISTRY_INFO BusData;
    PCONFIGURATION_COMPONENT_DATA BiosKey;
    ULONG Size;
    PCONFIGURATION_COMPONENT_DATA BusKey;
    ULONG i;

PcFindPciBios(&BusData);
     /* Set 'Configuration Data' value */
        Size = FIELD_OFFSET(CM_PARTIAL_RESOURCE_LIST, PartialDescriptors);
        PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
        if (PartialResourceList == NULL)
        {
            ERR("Failed to allocate resource descriptor\n");
            return;
        }

        /* Initialize resource descriptor */
        RtlZeroMemory(PartialResourceList, Size);

        /* Create new bus key */
        FldrCreateComponentKey(SystemKey,
                               AdapterClass,
                               MultiFunctionAdapter,
                               0x0,
                               0x0,
                               0xFFFFFFFF,
                               "PCI BIOS",
                               PartialResourceList,
                               Size,
                               &BiosKey);

        /* Increment bus number */
        (*BusNumber)++;

       // DetectPciIrqRoutingTable(BiosKey);

        /* Report PCI buses */
        for (i = 0; i < (ULONG)BusData.NoBuses; i++)
        {
            /* Check if this is the first bus */
            if (i == 0)
            {
                /* Set 'Configuration Data' value */
                Size = FIELD_OFFSET(CM_PARTIAL_RESOURCE_LIST,
                                    PartialDescriptors) +
                       sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR) +
                       sizeof(PCI_REGISTRY_INFO);
                PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
                if (!PartialResourceList)
                {
                    ERR("Failed to allocate resource descriptor! Ignoring remaining PCI buses. (i = %lu, NoBuses = %lu)\n",
                        i, (ULONG)BusData.NoBuses);
                    return;
                }

                /* Initialize resource descriptor */
                RtlZeroMemory(PartialResourceList, Size);
                PartialResourceList->Version = 1;
                PartialResourceList->Revision = 1;
                PartialResourceList->Count = 1;
                PartialDescriptor = &PartialResourceList->PartialDescriptors[0];
                PartialDescriptor->Type = CmResourceTypeDeviceSpecific;
                PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
                PartialDescriptor->u.DeviceSpecificData.DataSize = sizeof(PCI_REGISTRY_INFO);
                memcpy(&PartialResourceList->PartialDescriptors[1],
                       &BusData,
                       sizeof(PCI_REGISTRY_INFO));
            }
            else
            {
                /* Set 'Configuration Data' value */
                Size = FIELD_OFFSET(CM_PARTIAL_RESOURCE_LIST,
                                    PartialDescriptors);
                PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
                if (!PartialResourceList)
                {
                    ERR("Failed to allocate resource descriptor! Ignoring remaining PCI buses. (i = %lu, NoBuses = %lu)\n",
                        i, (ULONG)BusData.NoBuses);
                    return;
                }

                /* Initialize resource descriptor */
                RtlZeroMemory(PartialResourceList, Size);
            }

            /* Create the bus key */
            FldrCreateComponentKey(SystemKey,
                                   AdapterClass,
                                   MultiFunctionAdapter,
                                   0x0,
                                   0x0,
                                   0xFFFFFFFF,
                                   "PCI",
                                   PartialResourceList,
                                   Size,
                                   &BusKey);

            /* Increment bus number */
            (*BusNumber)++;
        }

}


static
VOID
DetectKeyboardController(PCONFIGURATION_COMPONENT_DATA BusKey)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    PCONFIGURATION_COMPONENT_DATA ControllerKey;
    ULONG Size;

    /* Set 'Configuration Data' value */
    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) +
           2 * sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR);
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate resource descriptor\n");
        return;
    }

    /* Initialize resource descriptor */
    RtlZeroMemory(PartialResourceList, Size);
    PartialResourceList->Version = 1;
    PartialResourceList->Revision = 1;
    PartialResourceList->Count = 3;

    /* Set Interrupt */
    PartialDescriptor = &PartialResourceList->PartialDescriptors[0];
    PartialDescriptor->Type = CmResourceTypeInterrupt;
    PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
    PartialDescriptor->Flags = CM_RESOURCE_INTERRUPT_LATCHED;
    PartialDescriptor->u.Interrupt.Level = 1;
    PartialDescriptor->u.Interrupt.Vector = 1;
    PartialDescriptor->u.Interrupt.Affinity = 0xFFFFFFFF;

    /* Set IO Port 0x60 */
    PartialDescriptor = &PartialResourceList->PartialDescriptors[1];
    PartialDescriptor->Type = CmResourceTypePort;
    PartialDescriptor->ShareDisposition = CmResourceShareDeviceExclusive;
    PartialDescriptor->Flags = CM_RESOURCE_PORT_IO;
    PartialDescriptor->u.Port.Start.LowPart = 0x60;
    PartialDescriptor->u.Port.Start.HighPart = 0x0;
    PartialDescriptor->u.Port.Length = 1;

    /* Set IO Port 0x64 */
    PartialDescriptor = &PartialResourceList->PartialDescriptors[2];
    PartialDescriptor->Type = CmResourceTypePort;
    PartialDescriptor->ShareDisposition = CmResourceShareDeviceExclusive;
    PartialDescriptor->Flags = CM_RESOURCE_PORT_IO;
    PartialDescriptor->u.Port.Start.LowPart = 0x64;
    PartialDescriptor->u.Port.Start.HighPart = 0x0;
    PartialDescriptor->u.Port.Length = 1;

    /* Create controller key */
    FldrCreateComponentKey(BusKey,
                           ControllerClass,
                           KeyboardController,
                           Input | ConsoleIn,
                           0x0,
                           0xFFFFFFFF,
                           NULL,
                           PartialResourceList,
                           Size,
                           &ControllerKey);
    TRACE("Created key: KeyboardController\\0\n");
}


static
VOID
PS2ControllerWait(VOID)
{
    ULONG Timeout;
    UCHAR Status;

    for (Timeout = 0; Timeout < CONTROLLER_TIMEOUT; Timeout++)
    {
        Status = READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_STATUS);
        if ((Status & CONTROLLER_STATUS_INPUT_BUFFER_FULL) == 0)
            return;

        /* Sleep for one millisecond */
        StallExecutionProcessor(1000);
    }
}

static
BOOLEAN
DetectPS2AuxPort(VOID)
{
#if 1
    /* Current detection is too unreliable. Just do as if
     * the PS/2 aux port is always present
     */
    return TRUE;
#else
    ULONG Loops;
    UCHAR Status;

    /* Put the value 0x5A in the output buffer using the
     * "WriteAuxiliary Device Output Buffer" command (0xD3).
     * Poll the Status Register for a while to see if the value really turns up
     * in the Data Register. If the KEYBOARD_STATUS_MOUSE_OBF bit is also set
     * to 1 in the Status Register, we assume this controller has an
     *  Auxiliary Port (a.k.a. Mouse Port).
     */
    PS2ControllerWait();
    WRITE_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_CONTROL,
                     CONTROLLER_COMMAND_WRITE_MOUSE_OUTPUT_BUFFER);
    PS2ControllerWait();

    /* 0x5A is a random dummy value */
    WRITE_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_DATA,
                     0x5A);

    for (Loops = 0; Loops < 10; Loops++)
    {
        StallExecutionProcessor(10000);
        Status = READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_STATUS);
        if ((Status & CONTROLLER_STATUS_OUTPUT_BUFFER_FULL) != 0)
            break;
    }

    READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_DATA);

    return (Status & CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL);
#endif
}

static
BOOLEAN
DetectPS2AuxDevice(VOID)
{
    UCHAR Scancode;
    UCHAR Status;
    ULONG Loops;
    BOOLEAN Result = TRUE;

    PS2ControllerWait();
    WRITE_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_CONTROL,
                     CONTROLLER_COMMAND_WRITE_MOUSE);
    PS2ControllerWait();

    /* Identify device */
    WRITE_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_DATA, 0xF2);

    /* Wait for reply */
    for (Loops = 0; Loops < 100; Loops++)
    {
        StallExecutionProcessor(10000);
        Status = READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_STATUS);
        if ((Status & CONTROLLER_STATUS_OUTPUT_BUFFER_FULL) != 0)
            break;
    }

    Status = READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_STATUS);
    if ((Status & CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL) == 0)
        Result = FALSE;

    Scancode = READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_DATA);
    if (Scancode != 0xFA)
        Result = FALSE;

    StallExecutionProcessor(10000);

    Status = READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_STATUS);
    if ((Status & CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL) == 0)
        Result = FALSE;

    Scancode = READ_PORT_UCHAR((PUCHAR)CONTROLLER_REGISTER_DATA);
    if (Scancode != 0x00)
        Result = FALSE;

    return Result;
}

// FIXME: Missing: DetectPS2Peripheral!! (for corresponding 'PointerPeripheral')

static
VOID
DetectPS2Mouse(PCONFIGURATION_COMPONENT_DATA BusKey)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCONFIGURATION_COMPONENT_DATA ControllerKey;
    PCONFIGURATION_COMPONENT_DATA PeripheralKey;
    ULONG Size;

    if (DetectPS2AuxPort())
    {
        TRACE("Detected PS2 port\n");

        PartialResourceList = FrLdrHeapAlloc(sizeof(CM_PARTIAL_RESOURCE_LIST), TAG_HW_RESOURCE_LIST);
        if (PartialResourceList == NULL)
        {
            ERR("Failed to allocate resource descriptor\n");
            return;
        }

        /* Initialize resource descriptor */
        RtlZeroMemory(PartialResourceList, sizeof(CM_PARTIAL_RESOURCE_LIST));
        PartialResourceList->Version = 1;
        PartialResourceList->Revision = 1;
        PartialResourceList->Count = 1;

        /* Set Interrupt */
        PartialResourceList->PartialDescriptors[0].Type = CmResourceTypeInterrupt;
        PartialResourceList->PartialDescriptors[0].ShareDisposition = CmResourceShareUndetermined;
        PartialResourceList->PartialDescriptors[0].Flags = CM_RESOURCE_INTERRUPT_LATCHED;
        PartialResourceList->PartialDescriptors[0].u.Interrupt.Level = 12;
        PartialResourceList->PartialDescriptors[0].u.Interrupt.Vector = 12;
        PartialResourceList->PartialDescriptors[0].u.Interrupt.Affinity = 0xFFFFFFFF;

        /* Create controller key */
        FldrCreateComponentKey(BusKey,
                               ControllerClass,
                               PointerController,
                               Input,
                               0x0,
                               0xFFFFFFFF,
                               NULL,
                               PartialResourceList,
                               sizeof(CM_PARTIAL_RESOURCE_LIST),
                               &ControllerKey);
        TRACE("Created key: PointerController\\0\n");

        if (DetectPS2AuxDevice())
        {
            TRACE("Detected PS2 mouse\n");

            /* Initialize resource descriptor */
            Size = sizeof(CM_PARTIAL_RESOURCE_LIST) -
                   sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR);
            PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
            if (PartialResourceList == NULL)
            {
                ERR("Failed to allocate resource descriptor\n");
                return;
            }

            RtlZeroMemory(PartialResourceList, Size);
            PartialResourceList->Version = 1;
            PartialResourceList->Revision = 1;
            PartialResourceList->Count = 0;

            /* Create peripheral key */
            FldrCreateComponentKey(ControllerKey,
                                   ControllerClass,
                                   PointerPeripheral,
                                   Input,
                                   0x0,
                                   0xFFFFFFFF,
                                   "MICROSOFT PS2 MOUSE",
                                   PartialResourceList,
                                   Size,
                                   &PeripheralKey);
            TRACE("Created key: PointerPeripheral\\0\n");
        }
    }
}

PCHAR
GetHarddiskIdentifier(UCHAR DriveNumber);
PCONFIGURATION_COMPONENT_DATA ControllerKey;

static
PCM_PARTIAL_RESOURCE_LIST
XboxGetHarddiskConfigurationData(UCHAR DriveNumber, ULONG* pSize)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_DISK_GEOMETRY_DEVICE_DATA DiskGeometry;
    //EXTENDED_GEOMETRY ExtGeometry;
    GEOMETRY Geometry;
    ULONG Size;

    //
    // Initialize returned size
    //
    *pSize = 0;

    /* Set 'Configuration Data' value */
    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) +
           sizeof(CM_DISK_GEOMETRY_DEVICE_DATA);
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate resource descriptor\n");
        return NULL;
    }

    RtlZeroMemory(PartialResourceList, Size);
    PartialResourceList->Version = 1;
    PartialResourceList->Revision = 1;
    PartialResourceList->Count = 1;
    PartialResourceList->PartialDescriptors[0].Type =
        CmResourceTypeDeviceSpecific;
//  PartialResourceList->PartialDescriptors[0].ShareDisposition =
//  PartialResourceList->PartialDescriptors[0].Flags =
    PartialResourceList->PartialDescriptors[0].u.DeviceSpecificData.DataSize =
        sizeof(CM_DISK_GEOMETRY_DEVICE_DATA);

    /* Get pointer to geometry data */
    DiskGeometry = (PVOID)(((ULONG_PTR)PartialResourceList) + sizeof(CM_PARTIAL_RESOURCE_LIST));

    /* Get the disk geometry */
    //ExtGeometry.Size = sizeof(EXTENDED_GEOMETRY);

    if (MachDiskGetDriveGeometry(DriveNumber, &Geometry))
    {
        DiskGeometry->BytesPerSector = Geometry.BytesPerSector;
        DiskGeometry->NumberOfCylinders = Geometry.Cylinders;
        DiskGeometry->SectorsPerTrack = Geometry.Sectors;
        DiskGeometry->NumberOfHeads = Geometry.Heads;
    }
    else
    {
        ERR("Reading disk geometry failed\n");
        FrLdrHeapFree(PartialResourceList, TAG_HW_RESOURCE_LIST);
        return NULL;
    }
    TRACE("Disk %x: %u Cylinders  %u Heads  %u Sectors  %u Bytes\n",
          DriveNumber,
          DiskGeometry->NumberOfCylinders,
          DiskGeometry->NumberOfHeads,
          DiskGeometry->SectorsPerTrack,
          DiskGeometry->BytesPerSector);

    //
    // Return configuration data
    //
    *pSize = Size;
    return PartialResourceList;
}

VOID
DetectBiosDisks(PCONFIGURATION_COMPONENT_DATA SystemKey,
                PCONFIGURATION_COMPONENT_DATA BusKey)
{
    PCONFIGURATION_COMPONENT_DATA DiskKey;
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_INT13_DRIVE_PARAMETER Int13Drives;
    GEOMETRY Geometry;
    UCHAR DiskCount, DriveNumber;
    USHORT i;
    ULONG Size;

    /* The pre-enumeration of the BIOS disks was already done in InitializeBootDevices() */
    DiskCount = PcBiosDiskCount;

    /* Allocate resource descriptor */
    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) +
           sizeof(CM_INT13_DRIVE_PARAMETER) * DiskCount;
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate resource descriptor\n");
        return;
    }

    /* Initialize resource descriptor */
    RtlZeroMemory(PartialResourceList, Size);
    PartialResourceList->Version = 1;
    PartialResourceList->Revision = 1;
    PartialResourceList->Count = 1;
    PartialResourceList->PartialDescriptors[0].Type = CmResourceTypeDeviceSpecific;
    PartialResourceList->PartialDescriptors[0].ShareDisposition = 0;
    PartialResourceList->PartialDescriptors[0].Flags = 0;
    PartialResourceList->PartialDescriptors[0].u.DeviceSpecificData.DataSize =
        sizeof(CM_INT13_DRIVE_PARAMETER) * DiskCount;

    /* Get harddisk Int13 geometry data */
    Int13Drives = (PVOID)(((ULONG_PTR)PartialResourceList) + sizeof(CM_PARTIAL_RESOURCE_LIST));
    for (i = 0; i < DiskCount; i++)
    {
        DriveNumber = 0x80 + i;

        if (MachDiskGetDriveGeometry(DriveNumber, &Geometry))
        {
            Int13Drives[i].DriveSelect = DriveNumber;
            Int13Drives[i].MaxCylinders = Geometry.Cylinders - 1;
            Int13Drives[i].SectorsPerTrack = (USHORT)Geometry.Sectors;
            Int13Drives[i].MaxHeads = (USHORT)Geometry.Heads - 1;
            Int13Drives[i].NumberDrives = DiskCount;

            TRACE("Disk %x: %u Cylinders  %u Heads  %u Sectors  %u Bytes\n",
                  DriveNumber,
                  Geometry.Cylinders - 1,
                  Geometry.Heads - 1,
                  Geometry.Sectors,
                  Geometry.BytesPerSector);
        }
    }

    /* Update the 'System' key's configuration data with BIOS INT13h information */
    FldrSetConfigurationData(SystemKey, PartialResourceList, Size);

    /* Create and fill subkey for each harddisk */
    for (i = 0; i < DiskCount; i++)
    {
        PCHAR Identifier;

        DriveNumber = 0x80 + i;

        /* Get disk values */
        PartialResourceList = XboxGetHarddiskConfigurationData(DriveNumber, &Size);
        Identifier = GetHarddiskIdentifier(DriveNumber);

        /* Create disk key */
        FldrCreateComponentKey(ControllerKey,
                               PeripheralClass,
                               DiskPeripheral,
                               Output | Input,
                               i,
                               0xFFFFFFFF,
                               Identifier,
                               PartialResourceList,
                               Size,
                               &DiskKey);
    }
}

static
VOID
DetectIsaBios(PCONFIGURATION_COMPONENT_DATA SystemKey, ULONG *BusNumber)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCONFIGURATION_COMPONENT_DATA BusKey;
    ULONG Size;

    /* Set 'Configuration Data' value */
    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) -
           sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR);
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate resource descriptor\n");
        return;
    }

    /* Initialize resource descriptor */
    RtlZeroMemory(PartialResourceList, Size);
    PartialResourceList->Version = 1;
    PartialResourceList->Revision = 1;
    PartialResourceList->Count = 0;

    /* Create new bus key */
    FldrCreateComponentKey(SystemKey,
                           AdapterClass,
                           MultiFunctionAdapter,
                           0x0,
                           0x0,
                           0xFFFFFFFF,
                           "ISA",
                           PartialResourceList,
                           Size,
                           &BusKey);

    /* Increment bus number */
    (*BusNumber)++;

        DetectKeyboardController(BusKey);
    DetectPS2Mouse(BusKey);
  //  DetectDisplayController(BusKey);
    /* Detect ISA/BIOS devices */
    DetectBiosDisks(SystemKey, BusKey);
   // DetectSerialPorts(BusKey, XboxGetSerialPort, MAX_XBOX_COM_PORTS);
   // DetectDisplayController(BusKey);

    /* FIXME: Detect more ISA devices */
}


static
PRSDP_DESCRIPTOR
FindAcpiBios(VOID)
{
    UINTN i;
    RSDP_DESCRIPTOR* rsdp = NULL;
    EFI_GUID acpi2_guid = EFI_ACPI_20_TABLE_GUID;

    for (i = 0; i < GlobalSystemTable->NumberOfTableEntries; i++)
    {
        if (!memcmp(&GlobalSystemTable->ConfigurationTable[i].VendorGuid,
                    &acpi2_guid, sizeof(acpi2_guid)))
        {
            rsdp = (RSDP_DESCRIPTOR*)GlobalSystemTable->ConfigurationTable[i].VendorTable;
            break;
        }
    }

    return rsdp;
}

VOID
DetectAcpiBios(PCONFIGURATION_COMPONENT_DATA SystemKey, ULONG *BusNumber)
{
    PCONFIGURATION_COMPONENT_DATA BiosKey;
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    PRSDP_DESCRIPTOR Rsdp;
    PACPI_BIOS_DATA AcpiBiosData;
    ULONG TableSize;

    Rsdp = FindAcpiBios();

    if (Rsdp)
    {
        /* Set up the flag in the loader block */
        AcpiPresent = TRUE;

        /* Calculate the table size */
        TableSize = FreeldrDescCount * sizeof(BIOS_MEMORY_MAP) +
            sizeof(ACPI_BIOS_DATA) - sizeof(BIOS_MEMORY_MAP);

        /* Set 'Configuration Data' value */
        PartialResourceList = FrLdrHeapAlloc(sizeof(CM_PARTIAL_RESOURCE_LIST) +
                                             TableSize, TAG_HW_RESOURCE_LIST);
        if (PartialResourceList == NULL)
        {
            ERR("Failed to allocate resource descriptor\n");
            return;
        }

        RtlZeroMemory(PartialResourceList, sizeof(CM_PARTIAL_RESOURCE_LIST) + TableSize);
        PartialResourceList->Version = 0;
        PartialResourceList->Revision = 0;
        PartialResourceList->Count = 1;

        PartialDescriptor = &PartialResourceList->PartialDescriptors[0];
        PartialDescriptor->Type = CmResourceTypeDeviceSpecific;
        PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
        PartialDescriptor->u.DeviceSpecificData.DataSize = TableSize;

        /* Fill the table */
        AcpiBiosData = (PACPI_BIOS_DATA)&PartialResourceList->PartialDescriptors[1];

        if (Rsdp->revision > 0)
        {
            TRACE("ACPI >1.0, using XSDT address\n");
            AcpiBiosData->RSDTAddress.QuadPart = Rsdp->xsdt_physical_address;
        }
        else
        {
            TRACE("ACPI 1.0, using RSDT address\n");
            AcpiBiosData->RSDTAddress.LowPart = Rsdp->rsdt_physical_address;
        }

        AcpiBiosData->Count = FreeldrDescCount;
        memcpy(AcpiBiosData->MemoryMap, EfiMemoryMap,
            FreeldrDescCount * sizeof(BIOS_MEMORY_MAP));

        TRACE("RSDT %p, data size %x\n", Rsdp->rsdt_physical_address, TableSize);

        /* Create new bus key */
        FldrCreateComponentKey(SystemKey,
                               AdapterClass,
                               MultiFunctionAdapter,
                               0x0,
                               0x0,
                               0xFFFFFFFF,
                               "ACPI BIOS",
                               PartialResourceList,
                               sizeof(CM_PARTIAL_RESOURCE_LIST) + TableSize,
                               &BiosKey);

        /* Increment bus number */
        (*BusNumber)++;
    }
}

extern REACTOS_INTERNAL_BGCONTEXT framebufferData;
/****/extern EFI_PIXEL_BITMASK UefiGopPixelBitmask;/****/

/**
 * @brief
 * Calculates the number of bits per pixel ("PixelDepth") for
 * the given pixel format, given by the pixel color masks.
 *
 * @note
 * The calculation is done by finding the highest bit set in
 * the combined pixel color masks.
 *
 * @remark
 * When the GOP pixel format is given by PixelBitMask, the pixel
 * element size _may be_ different from 4 bytes.
 * See UEFI Spec Rev.2.10 Section 12.9 "Graphics Output Protocol":
 * example code "GetPixelElementSize()" function.
 **/
static ULONG
PixelBitmasksToBpp(
    ULONG RedMask,
    ULONG GreenMask,
    ULONG BlueMask,
    ULONG ReservedMask)
{
    ULONG CompoundMask = (RedMask | GreenMask | BlueMask | ReservedMask);
#if 1
    ULONG ret = 0;
    return (_BitScanReverse(&ret, CompoundMask) ? ret : 0);
#else
    ULONG ret = 32; // (8 * sizeof(ULONG));
    while ((CompoundMask & (1 << 31)) == 0)
    {
        ret--;
        CompoundMask <<= 1;
    }
    return ret;
#endif
}

static VOID
DetectDisplayController(PCONFIGURATION_COMPONENT_DATA BusKey)
{
    PCONFIGURATION_COMPONENT_DATA ControllerKey;
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptor;
    PCM_FRAMEBUF_DEVICE_DATA FramebufferData;
    ULONG Size;

    if (framebufferData.BufferSize == 0)
        return;

    ERR("\nStructure sizes:\n"
        "    sizeof(CM_PARTIAL_RESOURCE_LIST)       = %lu\n"
        "    sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR) = %lu\n"
        "    sizeof(CM_FRAMEBUF_DEVICE_DATA)        = %lu\n\n",
        sizeof(CM_PARTIAL_RESOURCE_LIST),
        sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR),
        sizeof(CM_FRAMEBUF_DEVICE_DATA));

    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) +
           sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR) +
           sizeof(CM_FRAMEBUF_DEVICE_DATA);
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate resource descriptor\n");
        return;
    }

    /* Initialize resource descriptor */
    RtlZeroMemory(PartialResourceList, Size);
    PartialResourceList->Version  = ARC_VERSION;
    PartialResourceList->Revision = ARC_REVISION;
    PartialResourceList->Count = 2;

    /* Set Memory */
    PartialDescriptor = &PartialResourceList->PartialDescriptors[0];
    PartialDescriptor->Type = CmResourceTypeMemory;
    PartialDescriptor->ShareDisposition = CmResourceShareDeviceExclusive;
    PartialDescriptor->Flags = CM_RESOURCE_MEMORY_READ_WRITE;
    PartialDescriptor->u.Memory.Start.QuadPart = framebufferData.BaseAddress;
    PartialDescriptor->u.Memory.Length = framebufferData.BufferSize;

    /* Set framebuffer-specific data */
    PartialDescriptor = &PartialResourceList->PartialDescriptors[1];
    PartialDescriptor->Type = CmResourceTypeDeviceSpecific;
    PartialDescriptor->ShareDisposition = CmResourceShareUndetermined;
    PartialDescriptor->Flags = 0;
    PartialDescriptor->u.DeviceSpecificData.DataSize =
        sizeof(CM_FRAMEBUF_DEVICE_DATA);

    /* Get pointer to framebuffer-specific data */
    FramebufferData = (PVOID)(PartialDescriptor + 1);
    RtlZeroMemory(FramebufferData, sizeof(*FramebufferData));
    FramebufferData->Version  = 2;
    FramebufferData->Revision = 0;

    FramebufferData->VideoClock = 0; // FIXME: Use EDID

    /* Horizontal and Vertical resolution in pixels */
    FramebufferData->ScreenWidth  = framebufferData.ScreenWidth;
    FramebufferData->ScreenHeight = framebufferData.ScreenHeight;

    /* Number of pixel elements per video memory line */
    FramebufferData->PixelsPerScanLine = framebufferData.PixelsPerScanLine;

    //
    // TODO: Investigate display rotation!
    //
    // See OpenCorePkg OcConsoleLib/ConsoleGop.c
    // if ((mGop.Rotation == 90) || (mGop.Rotation == 270))
    if (FramebufferData->ScreenWidth < FramebufferData->ScreenHeight)
    {
        #define SWAP(x, y) { (x) ^= (y); (y) ^= (x); (x) ^= (y); }
        SWAP(FramebufferData->ScreenWidth, FramebufferData->ScreenHeight);
        FramebufferData->PixelsPerScanLine = FramebufferData->ScreenWidth;
        #undef SWAP
    }

    /* Physical format of the pixel */
    // ASSERT(sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) == 4);
    switch (framebufferData.PixelFormat)
    {
        case PixelRedGreenBlueReserved8BitPerColor:
        {
            FramebufferData->BitsPerPixel = (8 * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
            FramebufferData->PixelInformation.RedMask      = 0x000000FF;
            FramebufferData->PixelInformation.GreenMask    = 0x0000FF00;
            FramebufferData->PixelInformation.BlueMask     = 0x00FF0000;
            FramebufferData->PixelInformation.ReservedMask = 0xFF000000;
            break;
        }

        case PixelBlueGreenRedReserved8BitPerColor:
        {
            FramebufferData->BitsPerPixel = (8 * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
            FramebufferData->PixelInformation.RedMask      = 0x00FF0000;
            FramebufferData->PixelInformation.GreenMask    = 0x0000FF00;
            FramebufferData->PixelInformation.BlueMask     = 0x000000FF;
            FramebufferData->PixelInformation.ReservedMask = 0xFF000000;
            break;
        }

        case PixelBitMask:
        {
            FramebufferData->BitsPerPixel =
                PixelBitmasksToBpp(UefiGopPixelBitmask.RedMask,
                                   UefiGopPixelBitmask.GreenMask,
                                   UefiGopPixelBitmask.BlueMask,
                                   UefiGopPixelBitmask.ReservedMask);
            FramebufferData->PixelInformation.RedMask      = UefiGopPixelBitmask.RedMask;
            FramebufferData->PixelInformation.GreenMask    = UefiGopPixelBitmask.GreenMask;
            FramebufferData->PixelInformation.BlueMask     = UefiGopPixelBitmask.BlueMask;
            FramebufferData->PixelInformation.ReservedMask = UefiGopPixelBitmask.ReservedMask;
            break;
        }

        case PixelBltOnly:
        default:
        {
            ERR("Unsupported UFEI GOP format %lu\n", framebufferData.PixelFormat);
            FramebufferData->BitsPerPixel = 0;
            RtlZeroMemory(&FramebufferData->PixelInformation,
                          sizeof(FramebufferData->PixelInformation));
            break;
        }
    }

    FldrCreateComponentKey(BusKey,
                           ControllerClass,
                           DisplayController,
                           Output | ConsoleOut,
                           0,
                           0xFFFFFFFF,
                           "UEFI GOP Framebuffer",
                           PartialResourceList,
                           Size,
                           &ControllerKey);

    // NOTE: Don't add a MonitorPeripheral for now...
    // We should use EDID data for it.
}

static
VOID
DetectInternal(PCONFIGURATION_COMPONENT_DATA SystemKey, ULONG *BusNumber)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCONFIGURATION_COMPONENT_DATA BusKey;
    ULONG Size;

    /* Set 'Configuration Data' value */
    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) -
           sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR);
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate resource descriptor\n");
        return;
    }

    /* Initialize resource descriptor */
    RtlZeroMemory(PartialResourceList, Size);
    PartialResourceList->Version  = ARC_VERSION;
    PartialResourceList->Revision = ARC_REVISION;
    PartialResourceList->Count = 0;

    /* Create new bus key */
    FldrCreateComponentKey(SystemKey,
                           AdapterClass,
                           MultiFunctionAdapter,
                           0,
                           0,
                           0xFFFFFFFF,
                           "UEFI Internal",
                           PartialResourceList,
                           Size,
                           &BusKey);

    /* Increment bus number */
    (*BusNumber)++;

    /* Detect devices that do not belong to "standard" buses */
    DetectDisplayController(BusKey);

    /* FIXME: Detect more devices */
}


PCONFIGURATION_COMPONENT_DATA
UefiHwDetect(
    _In_opt_ PCSTR Options)
{
    PCONFIGURATION_COMPONENT_DATA SystemKey;
    ULONG BusNumber = 0;

    TRACE("DetectHardware()\n");

    /* Create the 'System' key */
#if defined(_M_IX86) || defined(_M_AMD64)
    /* Create the 'System' key */
    FldrCreateSystemKey(&SystemKey, FALSE, "AT/AT COMPATIBLE");
#elif defined(_M_IA64)
    FldrCreateSystemKey(&SystemKey, "Intel Itanium processor family");
#elif defined(_M_ARM) || defined(_M_ARM64)
    FldrCreateSystemKey(&SystemKey, "ARM processor family");
#else
    #error Please define a system key for your architecture
#endif

    /* Detect ACPI */
    DetectAcpiBios(SystemKey, &BusNumber);
    DetectInternal(SystemKey, &BusNumber);

    TRACE("DetectHardware() Done\n");
    return SystemKey;
}
