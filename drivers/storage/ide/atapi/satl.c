/*
 * PROJECT:     ReactOS ATA Port Driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     SCSI/ATA Translation layer
 * COPYRIGHT:   Copyright 2024 Dmitry Borisov (di.sean@protonmail.com)
 */

/* INCLUDES *******************************************************************/

#include "atapi.h"

/* GLOBALS ********************************************************************/

const UCHAR AtapAtaCommand[12][2] =
{
    /* Write */
    { IDE_COMMAND_WRITE,          IDE_COMMAND_WRITE_EXT              },
    { IDE_COMMAND_WRITE_MULTIPLE, IDE_COMMAND_WRITE_MULTIPLE_EXT     },
    { IDE_COMMAND_WRITE_DMA,      IDE_COMMAND_WRITE_DMA_EXT          },

    /* Read */
    { IDE_COMMAND_READ,           IDE_COMMAND_READ_EXT               },
    { IDE_COMMAND_READ_MULTIPLE,  IDE_COMMAND_READ_MULTIPLE_EXT      },
    { IDE_COMMAND_READ_DMA,       IDE_COMMAND_READ_DMA_EXT           },

    /* Write FUA */
    { 0,                          0                                  },
    { 0,                          IDE_COMMAND_WRITE_MULTIPLE_FUA_EXT },
    { 0,                          IDE_COMMAND_WRITE_DMA_FUA_EXT      },

    /* Read FUA */
    { 0,                          0                                  },
    { 0,                          0                                  },
    { 0,                          0                                  },
};

/* FUNCTIONS ******************************************************************/

static
VOID
AtaReqCopySatlBuffer(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    ULONG BytesCount = min(ChannelExtension->Request.DataTransferLength,
                           Srb->DataTransferLength);

    RtlCopyMemory(Srb->DataBuffer, ChannelExtension->SatlScratchBuffer, BytesCount);

    Srb->DataTransferLength = BytesCount;
    Srb->SrbStatus = SRB_STATUS_SUCCESS;
}

static
ULONG
AtaReqTerminateCommand(
    _In_ PSCSI_REQUEST_BLOCK Srb,
    _In_ UCHAR AdditionalSenseCode)
{
    PSENSE_DATA SenseData;
    ULONG SrbStatus;

    SrbStatus = SRB_STATUS_INVALID_REQUEST;
    Srb->ScsiStatus = SCSISTAT_CHECK_CONDITION;

    if (Srb->SenseInfoBuffer && Srb->SenseInfoBufferLength >= sizeof(*SenseData))
    {
        SrbStatus |= SRB_STATUS_AUTOSENSE_VALID;

        SenseData = Srb->SenseInfoBuffer;

        RtlZeroMemory(SenseData, sizeof(*SenseData));
        SenseData->ErrorCode = SCSI_SENSE_ERRORCODE_FIXED_CURRENT;
        SenseData->SenseKey = SCSI_SENSE_ILLEGAL_REQUEST;
        SenseData->AdditionalSenseCode = AdditionalSenseCode;
    }

    return SrbStatus;
}

static
ULONG
AtaReqTerminateInvalidField(
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    return AtaReqTerminateCommand(Srb, SCSI_ADSENSE_INVALID_CDB);
}

static
ULONG
AtaReqTerminateInvalidOpCode(
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    return AtaReqTerminateCommand(Srb, SCSI_ADSENSE_ILLEGAL_COMMAND);
}

static
ATA_COMPLETION_STATUS
AtaReqCompleteNoOp(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    return COMPLETE_IRP;
}

static
VOID
AtaReqBuildIdentifyCommand(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;

    Request->DeviceExtension = DeviceExtension;
    Request->DataBuffer = &DeviceExtension->IdentifyDeviceData;
    Request->DataTransferLength = sizeof(DeviceExtension->IdentifyDeviceData);
    Request->Mdl = NULL;
    Request->Flags = REQUEST_FLAG_DATA_IN;

    RtlZeroMemory(&Request->TaskFile, sizeof(Request->TaskFile));
    Request->TaskFile.Command = IDE_COMMAND_IDENTIFY;
}

static
ULONG
AtaReqReadWrite(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PATA_TASKFILE TaskFile = &Request->TaskFile;
    PCDB Cdb;
    ULONG64 Lba;
    ULONG SectorCount;

    Request->Complete = AtaReqCompleteNoOp;
    Request->DeviceExtension = DeviceExtension;
    Request->DataBuffer = Srb->DataBuffer;
    Request->DataTransferLength = Srb->DataTransferLength;
    Request->Mdl = Request->Irp->MdlAddress;
    Request->Flags = REQUEST_FLAG_ASYNC_MODE | REQUEST_FLAG_SET_DEVICE_REGISTER;

    Cdb = (PCDB)Srb->Cdb;
    switch (Cdb->AsByte[0])
    {
        case SCSIOP_READ6:
        case SCSIOP_WRITE6:
        {
            Lba = (Cdb->CDB6READWRITE.LogicalBlockMsb0 << 8) |
                  (Cdb->CDB6READWRITE.LogicalBlockLsb << 0);
            break;
        }

        case SCSIOP_READ:
        case SCSIOP_WRITE:
        {
            Lba = (Cdb->CDB10.LogicalBlockByte0 << 24) |
                  (Cdb->CDB10.LogicalBlockByte1 << 16) |
                  (Cdb->CDB10.LogicalBlockByte2 << 8) |
                  (Cdb->CDB10.LogicalBlockByte3 << 0);
            break;
        }

        case SCSIOP_READ12:
        case SCSIOP_WRITE12:
        {
            Lba = (Cdb->CDB12.LogicalBlock[0] << 24) |
                  (Cdb->CDB12.LogicalBlock[1] << 16) |
                  (Cdb->CDB12.LogicalBlock[2] << 8) |
                  (Cdb->CDB12.LogicalBlock[3] << 0);
            break;
        }

        case SCSIOP_READ16:
        case SCSIOP_WRITE16:
        {
            Lba = ((ULONG64)Cdb->CDB16.LogicalBlock[0] << 56) |
                  ((ULONG64)Cdb->CDB16.LogicalBlock[1] << 48) |
                  ((ULONG64)Cdb->CDB16.LogicalBlock[2] << 40) |
                  ((ULONG64)Cdb->CDB16.LogicalBlock[3] << 32) |
                  ((ULONG64)Cdb->CDB16.LogicalBlock[4] << 24) |
                  ((ULONG64)Cdb->CDB16.LogicalBlock[5] << 16) |
                  ((ULONG64)Cdb->CDB16.LogicalBlock[6] << 8) |
                  ((ULONG64)Cdb->CDB16.LogicalBlock[7] << 0);
            break;
        }

        default:
            ASSERT(FALSE);
            UNREACHABLE;
    }

    /* Check for write operations */
    if (Cdb->AsByte[0] & 0x02)
        Request->Flags |= REQUEST_FLAG_DATA_OUT;
    else
        Request->Flags |= REQUEST_FLAG_DATA_IN;

    if (!(DeviceExtension->Flags & DEVICE_PIO_ONLY))
    {
        Request->Flags |= REQUEST_FLAG_DMA_ENABLED;
    }
    if (DeviceExtension->MultiSectorTransfer != 0)
    {
        Request->Flags |= REQUEST_FLAG_READ_WRITE_MULTIPLE;
    }

    /* Ignore the transfer length field in the CDB, use the DataTransferLength field instead */
    SectorCount = Request->DataTransferLength + (DeviceExtension->SectorSize - 1);
    SectorCount /= DeviceExtension->SectorSize;

    /* Make sure the sector count do not exceed the maximum transfer length */
    ASSERT(SectorCount <= 0x100);

    /* 28-bit or 48-bit command */
    if (DeviceExtension->Flags & DEVICE_LBA_MODE)
    {
        TaskFile->Feature = 0;
        TaskFile->SectorCount = (UCHAR)SectorCount;
        TaskFile->LowLba = (UCHAR)Lba;                // LBA bits 0-7
        TaskFile->MidLba = (UCHAR)(Lba >> 8);         // LBA bits 8-15
        TaskFile->HighLba = (UCHAR)(Lba >> 16);       // LBA bits 16-23

        /* 48-bit command */
        if ((DeviceExtension->Flags & DEVICE_LBA48) && (AtaReadWriteUseLba48(Lba, SectorCount)))
        {
            TaskFile->SectorCountEx = (UCHAR)(SectorCount >> 8);

            TaskFile->LowLbaEx = (UCHAR)(Lba >> 24);  // LBA bits 24-31
            TaskFile->MidLbaEx = (UCHAR)(Lba >> 32);  // LBA bits 32-39
            TaskFile->HighLbaEx = (UCHAR)(Lba >> 40); // LBA bits 40-47
            TaskFile->DriveSelect = IDE_LBA_MODE;

            Request->Flags |= REQUEST_FLAG_LBA48;
        }
        else
        {
            TaskFile->DriveSelect = ((Lba >> 24) & 0x0F) | IDE_LBA_MODE; // LBA bits 24-27
        }
    }
    else
    {
        ULONG ChsTemp, Cylinder, Head, Sector;

        ChsTemp = (ULONG)Lba / DeviceExtension->SectorsPerTrack;

        /* Legacy CHS translation */
        Cylinder = ChsTemp / DeviceExtension->Heads;
        Head = ChsTemp % DeviceExtension->Heads;
        Sector = ((ULONG)Lba % DeviceExtension->SectorsPerTrack) + 1;

        TaskFile->Feature = 0;
        TaskFile->SectorCount = (UCHAR)SectorCount;
        TaskFile->LowLba = (UCHAR)Cylinder;
        TaskFile->MidLba = (UCHAR)Sector;
        TaskFile->HighLba = (UCHAR)(Sector >> 8);
        TaskFile->DriveSelect = (UCHAR)Head;
    }

    /* Choose the command opcode */
    TaskFile->Command = AtaReadWriteCommand(Request, DeviceExtension);

    /* Terminate the request when the FUA is not supported */
    if (TaskFile->Command == 0)
        return AtaReqTerminateInvalidField(Srb);

    return SRB_STATUS_PENDING;
}

static
ULONG
AtaReqSynchronizeCache(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PATA_TASKFILE TaskFile = &Request->TaskFile;

    Request->Complete = AtaReqCompleteNoOp;
    Request->DeviceExtension = DeviceExtension;
    Request->DataBuffer = NULL;
    Request->DataTransferLength = 0;
    Request->Mdl = NULL;
    Request->Flags = REQUEST_FLAG_ASYNC_MODE;

    /* NOTE: This command may take longer than 30 seconds to complete */
    if (DeviceExtension->Flags & DEVICE_LBA48)
        TaskFile->Command = IDE_COMMAND_FLUSH_CACHE_EXT;
    else
        TaskFile->Command = IDE_COMMAND_FLUSH_CACHE;

    return SRB_STATUS_PENDING;
}

static
ULONG
AtaReqScsiReportLuns(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PCDB Cdb = (PCDB)Srb->Cdb;
    PLUN_LIST LunList;
    ULONG LunListLength;

    Request->DataTransferLength = Cdb->REPORT_LUNS.AllocationLength[0] << 24 |
                                  Cdb->REPORT_LUNS.AllocationLength[1] << 16 |
                                  Cdb->REPORT_LUNS.AllocationLength[2] << 8 |
                                  Cdb->REPORT_LUNS.AllocationLength[3];

    if (Srb->DataTransferLength < Request->DataTransferLength)
        return AtaReqTerminateInvalidField(Srb);

    LunList = (PLUN_LIST)ChannelExtension->SatlScratchBuffer;
    LunListLength = RTL_FIELD_SIZE(LUN_LIST, Lun[0]);

    RtlZeroMemory(LunList, sizeof(*LunList));
    LunList->LunListLength[0] = (UCHAR)(LunListLength >> 24);
    LunList->LunListLength[1] = (UCHAR)(LunListLength >> 16);
    LunList->LunListLength[2] = (UCHAR)(LunListLength >> 8);
    LunList->LunListLength[3] = (UCHAR)(LunListLength >> 0);

    AtaReqCopySatlBuffer(ChannelExtension, Srb);
    return SRB_STATUS_SUCCESS;
}

static
ATA_COMPLETION_STATUS
AtaReqCompleteReadCapacity(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PATAPORT_DEVICE_EXTENSION DeviceExtension = Request->DeviceExtension;
    PSCSI_REQUEST_BLOCK Srb = Request->Srb;

    AtaPdoSetAddressingMode(DeviceExtension);

    if (Srb->Cdb[0] == SCSIOP_READ_CAPACITY)
    {
        PREAD_CAPACITY_DATA CapacityData;
        ULONG MaximumLba;

        MaximumLba = min(DeviceExtension->TotalSectors - 1, 0xFFFFFFFF);

        CapacityData = Srb->DataBuffer;
        CapacityData->LogicalBlockAddress = RtlUlongByteSwap(MaximumLba);
        CapacityData->BytesPerBlock = RtlUlongByteSwap(DeviceExtension->SectorSize);

        Request->DataTransferLength = sizeof(*CapacityData);
    }
    else // SCSIOP_READ_CAPACITY16
    {
        PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
        PREAD_CAPACITY16_DATA CapacityData;
        ULONG LogicalPerPhysicalExponent, LogicalSectorsPerPhysicalSector;
        ULONG LogicalSectorAlignment, LowestAlignedBlock;
        ULONG64 MaximumLba;

        LogicalSectorsPerPhysicalSector =
            AtaLogicalSectorsPerPhysicalSector(&DeviceExtension->IdentifyDeviceData,
                                               &LogicalPerPhysicalExponent);

        LogicalSectorAlignment = AtaLogicalSectorAlignment(&DeviceExtension->IdentifyDeviceData);

        LowestAlignedBlock = (LogicalSectorsPerPhysicalSector - LogicalSectorAlignment);
        LowestAlignedBlock %= LogicalSectorsPerPhysicalSector;

        MaximumLba = DeviceExtension->TotalSectors - 1;

        CapacityData = (PREAD_CAPACITY16_DATA)ChannelExtension->SatlScratchBuffer;

        RtlZeroMemory(CapacityData, sizeof(*CapacityData));
        CapacityData->LogicalBlockAddress.QuadPart = RtlUlonglongByteSwap(MaximumLba);
        CapacityData->BytesPerBlock = RtlUlongByteSwap(DeviceExtension->SectorSize);
        CapacityData->LogicalPerPhysicalExponent = LogicalPerPhysicalExponent;
        CapacityData->LowestAlignedBlock_MSB = (UCHAR)(LowestAlignedBlock >> 8);
        CapacityData->LowestAlignedBlock_LSB = (UCHAR)LowestAlignedBlock;

        if (AtaHasTrimFunction(&DeviceExtension->IdentifyDeviceData))
        {
            if (AtaHasDratFunction(&DeviceExtension->IdentifyDeviceData))
            {
                CapacityData->LBPME = 1;

                if (AtaHasRzatFunction(&DeviceExtension->IdentifyDeviceData))
                    CapacityData->LBPRZ = 1;
            }
        }

        Request->DataTransferLength = CdbGetAllocationLength16(Srb);

        AtaReqCopySatlBuffer(ChannelExtension, Srb);
    }

    Request->SrbStatus = SRB_STATUS_SUCCESS;
    return COMPLETE_IRP;
}

static
ULONG
AtaReqScsiReadCapacity(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;

    if (Srb->Cdb[0] == SCSIOP_READ_CAPACITY)
    {
        if (Srb->DataTransferLength < sizeof(READ_CAPACITY_DATA))
            return AtaReqTerminateInvalidField(Srb);
    }
    else // SCSIOP_READ_CAPACITY16
    {
        if (Srb->DataTransferLength < CdbGetAllocationLength16(Srb))
            return AtaReqTerminateInvalidField(Srb);
    }

    /* Update the identify data */
    AtaReqBuildIdentifyCommand(ChannelExtension, DeviceExtension, Srb);

    Request->Complete = AtaReqCompleteReadCapacity;
    return SRB_STATUS_PENDING;
}

static
ULONG
AtaReqControlModePage(
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PVOID Buffer)
{
    PMODE_CONTROL_PAGE PageData = Buffer;

    PageData->PageCode = MODE_PAGE_CONTROL;
    PageData->PageLength = sizeof(PageData) - 2;
    PageData->QERR = 0;
    PageData->QueueAlgorithmModifier = 1;
    PageData->BusyTimeoutPeriod[0] = 0xFF;
    PageData->BusyTimeoutPeriod[1] = 0xFF;

    return sizeof(PageData);
}

static
ULONG
AtaReqControlExtensionModePage(
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PVOID Buffer)
{
    PMODE_CONTROL_EXTENSION_PAGE PageData = Buffer;

    PageData->SubPageFormat = 1;
    PageData->SubPageCode = 0x00;
    PageData->PageCode = MODE_PAGE_CONTROL;
    PageData->PageLength[1] = sizeof(PageData) - 4;

    return sizeof(PageData);
}

static
ULONG
AtaReqRwErrorRecoveryModePage(
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PVOID Buffer)
{
    PMODE_READ_WRITE_RECOVERY_PAGE PageData = Buffer;

    PageData->PageCode = MODE_PAGE_ERROR_RECOVERY;
    PageData->PageLength = sizeof(PageData) - 2;
    PageData->AWRE = 1;

    return sizeof(PageData);
}

static
ULONG
AtaReqCachingModePage(
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PVOID Buffer)
{
    PMODE_CACHING_PAGE_SPC5 PageData = Buffer;


    PageData->PageCode = MODE_PAGE_CACHING;
    PageData->PageLength = sizeof(PageData) - 2;

    if (AtaDeviceIsVolatileWriteCacheEnabled(&DeviceExtension->IdentifyDeviceData))
        PageData->WriteCacheEnable = 1;

    if (AtaDeviceIsReadLookAHeadEnabled(&DeviceExtension->IdentifyDeviceData))
        PageData->DisableReadAHead = 1;

    return sizeof(PageData);
}

static
ULONG
AtaReqInformationalExceptionsControlModePage(
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PVOID Buffer)
{
    PMODE_INFO_EXCEPTIONS PageData = Buffer;

    PageData->PageCode = MODE_PAGE_FAULT_REPORTING;
    PageData->PageLength = sizeof(PageData) - 2;

    /* Only report informational exception condition on request */
    PageData->ReportMethod = 6;

    return sizeof(PageData);
}

static
ULONG
AtaReqPowerConditionModePage(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PVOID Buffer)
{
    PPOWER_CONDITION_PAGE PageData = Buffer;
    ULONG StandbyTimer;

    PageData->PageCode = MODE_PAGE_POWER_CONDITION;
    PageData->PageLength = sizeof(PageData) - 2;

    if (AtaStandybyTimerPeriodsValid(&DeviceExtension->IdentifyDeviceData))
    {
        switch (ChannelExtension->StandbyTimerPeriod)
        {
            case 0xFC:
            {
                /* 21 min */
                StandbyTimer = 12600;
                break;
            }
            case 0xFD:
            {
                /* 8 h to 12 h */
                StandbyTimer = 432000;
                break;
            }
            case 0xFF:
            {
                /* 21 min, 15 s */
                StandbyTimer = 12750;
                break;
            }
            default:
            {
                if (ChannelExtension->StandbyTimerPeriod >= 0x01 &&
                    ChannelExtension->StandbyTimerPeriod <= 0xF0)
                {
                    /* 5 s to 1200 s */
                    StandbyTimer = ChannelExtension->StandbyTimerPeriod * 50;
                }
                else if (ChannelExtension->StandbyTimerPeriod >= 0xF1 &&
                         ChannelExtension->StandbyTimerPeriod <= 0xFB)
                {
                    /* 30 min to 330 min */
                    StandbyTimer = (ChannelExtension->StandbyTimerPeriod - 240) * 18000;
                }
                else
                {
                    /* n/a */
                    StandbyTimer = 0xFFFFFFFF;
                }
                break;
            }
        }

        PageData->Standby = 1;
        PageData->StandbyTimer[0] = (UCHAR)(StandbyTimer >> 24);
        PageData->StandbyTimer[1] = (UCHAR)(StandbyTimer >> 16);
        PageData->StandbyTimer[2] = (UCHAR)(StandbyTimer >> 8);
        PageData->StandbyTimer[4] = (UCHAR)(StandbyTimer >> 0);
    }

    return sizeof(PageData);
}

static
ATA_COMPLETION_STATUS
AtaReqCompleteModeSense(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PATAPORT_DEVICE_EXTENSION DeviceExtension;
    UCHAR PageCode;
    USHORT ModeDataLength;
    PUCHAR Buffer;
    BOOLEAN Is6ByteCommand, IsWriteProtected;
    PMODE_PARAMETER_HEADER ModeHeader6;
    PMODE_PARAMETER_HEADER10 ModeHeader10;
    PCDB Cdb;

    DeviceExtension = Request->DeviceExtension;

    /* Determine the media status */
    if ((ChannelExtension->TranslationState == 0) &&
        (DeviceExtension->Flags & DEVICE_HAS_MEDIA_STATUS))
    {
        Request->Flags = REQUEST_FLAG_ASYNC_MODE;
        Request->TaskFile.Command = IDE_COMMAND_GET_MEDIA_STATUS;

        ++ChannelExtension->TranslationState;
        return COMPLETE_START_AGAIN;
    }

    RtlZeroMemory(ChannelExtension->SatlScratchBuffer,
                  sizeof(ChannelExtension->SatlScratchBuffer));

    Cdb = (PCDB)Request->Srb->Cdb;
    Is6ByteCommand = (Cdb->AsByte[0] == SCSIOP_MODE_SENSE);

    Buffer = ChannelExtension->SatlScratchBuffer;

    /* Media status outputs */
    if (ChannelExtension->TranslationState != 0)
    {
        IsWriteProtected = (Request->Status & IDE_STATUS_ERROR) &&
                           !(Request->Error & IDE_ERROR_COMMAND_ABORTED) &&
                           (Request->Error & IDE_ERROR_WRITE_PROTECT);
    }
    else
    {
        IsWriteProtected = FALSE;
    }

    /* Mode parameter header */
    if (Is6ByteCommand)
    {
        ModeHeader6 = (PMODE_PARAMETER_HEADER)Buffer;

        if (IsWriteProtected)
            ModeHeader6->DeviceSpecificParameter |= MODE_DSP_WRITE_PROTECT;
        if (DeviceExtension->Flags & DEVICE_HAS_FUA)
            ModeHeader6->DeviceSpecificParameter |= MODE_DSP_FUA_SUPPORTED;

        Buffer += sizeof(*ModeHeader6);
    }
    else
    {
        ModeHeader10 = (PMODE_PARAMETER_HEADER10)Buffer;

        if (IsWriteProtected)
            ModeHeader10->DeviceSpecificParameter |= MODE_DSP_WRITE_PROTECT;
        if (DeviceExtension->Flags & DEVICE_HAS_FUA)
            ModeHeader10->DeviceSpecificParameter |= MODE_DSP_FUA_SUPPORTED;

        Buffer += sizeof(*ModeHeader10);
    }

    /* Short LBA mode parameter block descriptor */
    if (!Cdb->MODE_SENSE.Dbd)
    {
        PFORMAT_DESCRIPTOR FormatDescriptor;

        if (Is6ByteCommand)
        {
            ModeHeader6->BlockDescriptorLength = sizeof(*FormatDescriptor);
        }
        else
        {
            ModeHeader10->BlockDescriptorLength[0] = (UCHAR)(sizeof(*FormatDescriptor) >> 8);
            ModeHeader10->BlockDescriptorLength[1] = (UCHAR)(sizeof(*FormatDescriptor) >> 0);
        }

        FormatDescriptor = (PFORMAT_DESCRIPTOR)Buffer;
        FormatDescriptor->BlockLength[0] = (UCHAR)(DeviceExtension->SectorSize >> 16);
        FormatDescriptor->BlockLength[1] = (UCHAR)(DeviceExtension->SectorSize >> 8);
        FormatDescriptor->BlockLength[2] = (UCHAR)(DeviceExtension->SectorSize >> 0);

        Buffer += sizeof(*FormatDescriptor);
    }

    PageCode = Cdb->MODE_SENSE.PageCode;

    /* Return SCSI mode pages */
    if (PageCode == MODE_PAGE_CONTROL || PageCode == MODE_SENSE_RETURN_ALL)
    {
        UCHAR SubPageCode = Cdb->MODE_SENSE.Reserved3;

        if (SubPageCode == 0x00 || SubPageCode == 0xFF)
            Buffer += AtaReqControlModePage(DeviceExtension, Buffer);
        if (SubPageCode == 0x01 || SubPageCode == 0xFF)
            Buffer += AtaReqControlExtensionModePage(DeviceExtension, Buffer);
    }
    if (PageCode == MODE_PAGE_ERROR_RECOVERY || PageCode == MODE_SENSE_RETURN_ALL)
    {
        Buffer += AtaReqRwErrorRecoveryModePage(DeviceExtension, Buffer);
    }
    if (PageCode == MODE_PAGE_CACHING || PageCode == MODE_SENSE_RETURN_ALL)
    {
        Buffer += AtaReqCachingModePage(DeviceExtension, Buffer);
    }
    if (PageCode == MODE_PAGE_FAULT_REPORTING || PageCode == MODE_SENSE_RETURN_ALL)
    {
        Buffer += AtaReqInformationalExceptionsControlModePage(DeviceExtension, Buffer);
    }
    if (PageCode == MODE_PAGE_POWER_CONDITION || PageCode == MODE_SENSE_RETURN_ALL)
    {
        Buffer += AtaReqPowerConditionModePage(ChannelExtension, DeviceExtension, Buffer);
    }

    ModeDataLength = Buffer - ChannelExtension->SatlScratchBuffer;
    Request->DataTransferLength = ModeDataLength;

    if (Is6ByteCommand)
    {
        ModeDataLength -= RTL_SIZEOF_THROUGH_FIELD(MODE_PARAMETER_HEADER, MediumType);

        ModeHeader6->ModeDataLength = ModeDataLength;
    }
    else
    {
        ModeDataLength -= RTL_SIZEOF_THROUGH_FIELD(MODE_PARAMETER_HEADER10, MediumType);

        ModeHeader10->ModeDataLength[0] = (UCHAR)(ModeDataLength >> 8);
        ModeHeader10->ModeDataLength[1] = (UCHAR)(ModeDataLength >> 0);
    }

    AtaReqCopySatlBuffer(ChannelExtension, Request->Srb);

    Request->SrbStatus = SRB_STATUS_SUCCESS;
    return COMPLETE_IRP;
}

static
ULONG
AtaReqModeSense(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb,
    _In_ BOOLEAN Is6ByteCommand)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    ULONG AllocationLength;
    PCDB Cdb;

    if (Is6ByteCommand)
        AllocationLength = CdbGetAllocationLength6(Srb);
    else
        AllocationLength = CdbGetAllocationLength10(Srb);

    if (Srb->DataTransferLength < AllocationLength)
        return AtaReqTerminateInvalidField(Srb);

    Cdb = (PCDB)Srb->Cdb;

    if (Cdb->MODE_SENSE.Pc == MODE_SENSE_SAVED_VALUES)
        return AtaReqTerminateInvalidField(Srb);

    switch (Cdb->MODE_SENSE.PageCode)
    {
        case MODE_PAGE_FAULT_REPORTING:
        {
            if (!AtaDeviceHasSmartFeature(&DeviceExtension->IdentifyDeviceData))
                return AtaReqTerminateInvalidField(Srb);

            break;
        }

        case MODE_PAGE_CONTROL:
        {
            UCHAR SubPageCode = Cdb->MODE_SENSE.Reserved3;

            if (SubPageCode != 0x00 && SubPageCode != 0x01 && SubPageCode != 0xFF)
                return AtaReqTerminateInvalidField(Srb);

            break;
        }

        case MODE_PAGE_ERROR_RECOVERY:
        case MODE_PAGE_POWER_CONDITION:
        case MODE_PAGE_CACHING:
        case MODE_SENSE_RETURN_ALL:
            break;

        default:
            return AtaReqTerminateInvalidField(Srb);
    }

    ChannelExtension->TranslationState = 0;

    /* Update the identify data */
    AtaReqBuildIdentifyCommand(ChannelExtension, DeviceExtension, Srb);

    Request->Complete = AtaReqCompleteModeSense;
    return SRB_STATUS_PENDING;
}

static
ULONG
AtaReqModeSelect(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb,
    _In_ BOOLEAN Is6ByteCommand)
{
    return AtaReqTerminateInvalidField(Srb);
}

static
ULONG
AtaReqInquiry(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PCDB Cdb = (PCDB)Srb->Cdb;

    Request->DataTransferLength = (Cdb->AsByte[3] << 8) | Cdb->AsByte[3];

    if (Srb->DataTransferLength < Request->DataTransferLength)
        return AtaReqTerminateInvalidField(Srb);

    if (!Cdb->CDB6INQUIRY3.EnableVitalProductData)
    {
        ULONG BytesCount;

        if (Cdb->CDB6INQUIRY3.PageCode != 0)
            return AtaReqTerminateInvalidField(Srb);

        BytesCount = min(Request->DataTransferLength, Srb->DataTransferLength);
        BytesCount = min(BytesCount, sizeof(DeviceExtension->InquiryData));

        RtlCopyMemory(Srb->DataBuffer, &DeviceExtension->InquiryData, BytesCount);

        Srb->DataTransferLength = BytesCount;
        return SRB_STATUS_SUCCESS;
    }

    switch (Cdb->CDB6INQUIRY3.PageCode)
    {
        case VPD_SUPPORTED_PAGES:
        {
            PVPD_SUPPORTED_PAGES_PAGE SupportedPages;
            ULONG i;

            SupportedPages = (PVPD_SUPPORTED_PAGES_PAGE)ChannelExtension->SatlScratchBuffer;
            SupportedPages->DeviceType = DeviceExtension->InquiryData.DeviceType;
            SupportedPages->DeviceTypeQualifier = DeviceExtension->InquiryData.DeviceTypeQualifier;
            SupportedPages->PageCode = VPD_SUPPORTED_PAGES;
            SupportedPages->Reserved = 0;
            i = 0;
            SupportedPages->SupportedPageList[i++] = VPD_SUPPORTED_PAGES;
            SupportedPages->SupportedPageList[i++] = VPD_SERIAL_NUMBER;
            //SupportedPages->SupportedPageList[i++] = VPD_DEVICE_IDENTIFIERS;
            //SupportedPages->SupportedPageList[i++] = VPD_MODE_PAGE_POLICY;
            //SupportedPages->SupportedPageList[i++] = VPD_ATA_INFORMATION;
            //SupportedPages->SupportedPageList[i++] = VPD_BLOCK_LIMITS;
            //SupportedPages->SupportedPageList[i++] = VPD_BLOCK_DEVICE_CHARACTERISTICS;
            //SupportedPages->SupportedPageList[i++] = VPD_LOGICAL_BLOCK_PROVISIONING;
            //SupportedPages->SupportedPageList[i++] = VPD_ZONED_BLOCK_DEVICE_CHARACTERISTICS;
            //SupportedPages->SupportedPageList[i++] = 0x8A; // Power Condition VPD page
            SupportedPages->PageLength = i;

            AtaReqCopySatlBuffer(ChannelExtension, Srb);
            return SRB_STATUS_SUCCESS;
        }

        case VPD_SERIAL_NUMBER:
        {
            PVPD_SERIAL_NUMBER_PAGE SerialNumberPage;

            SerialNumberPage = (PVPD_SERIAL_NUMBER_PAGE)ChannelExtension->SatlScratchBuffer;

            RtlZeroMemory(SerialNumberPage, FIELD_OFFSET(VPD_SERIAL_NUMBER_PAGE, SerialNumber));
            SerialNumberPage->DeviceType = DeviceExtension->InquiryData.DeviceType;
            SerialNumberPage->DeviceTypeQualifier =
            SerialNumberPage->PageCode = VPD_SERIAL_NUMBER;
            SerialNumberPage->PageLength = RTL_FIELD_SIZE(IDENTIFY_DEVICE_DATA, SerialNumber);

            RtlCopyMemory(SerialNumberPage->SerialNumber,
                          &DeviceExtension->IdentifyDeviceData.SerialNumber,
                          RTL_FIELD_SIZE(IDENTIFY_DEVICE_DATA, SerialNumber));
            AtaSwapIdString(SerialNumberPage->SerialNumber,
                            RTL_FIELD_SIZE(IDENTIFY_DEVICE_DATA, SerialNumber) / 2);

            AtaReqCopySatlBuffer(ChannelExtension, Srb);
            break;
        }

        default:
            ASSERT(0);
    }

    return SRB_STATUS_SUCCESS;
}

static
ULONG
AtaReqTestUnitReady(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    Srb->DataTransferLength = 0;

    return SRB_STATUS_SUCCESS;
}

static
ULONG
AtaReqExecuteScsiAta(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    switch (Srb->Cdb[0])
    {
        case SCSIOP_REPORT_LUNS:
            return AtaReqScsiReportLuns(ChannelExtension, DeviceExtension, Srb);

        case SCSIOP_INQUIRY:
            return AtaReqInquiry(ChannelExtension, DeviceExtension, Srb);

        case SCSIOP_TEST_UNIT_READY:
            return AtaReqTestUnitReady(ChannelExtension, DeviceExtension, Srb);

        case SCSIOP_MODE_SENSE:
        case SCSIOP_MODE_SENSE10:
            return AtaReqModeSense(ChannelExtension,
                                   DeviceExtension,
                                   Srb,
                                   (Srb->Cdb[0] == SCSIOP_MODE_SENSE));

        case SCSIOP_MODE_SELECT:
        case SCSIOP_MODE_SELECT10:
            return AtaReqModeSelect(ChannelExtension,
                                    DeviceExtension,
                                    Srb,
                                    (Srb->Cdb[0] == SCSIOP_MODE_SELECT));

        case SCSIOP_SERVICE_ACTION_IN16:
        {
            if (((PCDB)Srb->Cdb)->READ_CAPACITY16.ServiceAction != SERVICE_ACTION_READ_CAPACITY16)
                break;

            __fallthrough;
        }
        case SCSIOP_READ_CAPACITY:
            return AtaReqScsiReadCapacity(ChannelExtension, DeviceExtension, Srb);

        case SCSIOP_READ6:
        case SCSIOP_WRITE6:
        case SCSIOP_READ:
        case SCSIOP_WRITE:
        case SCSIOP_READ12:
        case SCSIOP_WRITE12:
        case SCSIOP_READ16:
        case SCSIOP_WRITE16:
            return AtaReqReadWrite(ChannelExtension, DeviceExtension, Srb);

        case SCSIOP_SYNCHRONIZE_CACHE:
        case SCSIOP_SYNCHRONIZE_CACHE16:
            return AtaReqSynchronizeCache(ChannelExtension, DeviceExtension, Srb);

        // TODO: more commands

        default:
            break;
    }

    return AtaReqTerminateInvalidOpCode(Srb);
}

static
ULONG
AtaReqPreparePacketCommand(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;

    Request->Complete = AtaReqCompleteNoOp;
    Request->DeviceExtension = DeviceExtension;
    Request->DataBuffer = Srb->DataBuffer;
    Request->DataTransferLength = Srb->DataTransferLength;
    Request->Mdl = Request->Irp->MdlAddress;
    Request->Flags = REQUEST_FLAG_ASYNC_MODE | REQUEST_FLAG_PACKET_COMMAND |
                     (Srb->SrbFlags & SRB_FLAGS_UNSPECIFIED_DIRECTION);

    if ((!ChannelExtension->Flags & DEVICE_PIO_ONLY) && AtaAtapiUseDma(Srb->Cdb[0]))
    {
        Request->Flags |= REQUEST_FLAG_DMA_ENABLED;
    }

    RtlCopyMemory(Request->Cdb, Srb->Cdb, RTL_FIELD_SIZE(SCSI_REQUEST_BLOCK, Cdb));

    return SRB_STATUS_PENDING;
}

ULONG
AtaReqExecuteScsi(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    if (IS_ATAPI(DeviceExtension))
        return AtaReqPreparePacketCommand(ChannelExtension, DeviceExtension, Srb);
    else
        return AtaReqExecuteScsiAta(ChannelExtension, DeviceExtension, Srb);
}

static
ATA_COMPLETION_STATUS
AtaReqCompleteTaskFile(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PSCSI_REQUEST_BLOCK Srb;
    PIRP Irp;

    Srb = Request->Srb;
    ASSERT(Srb);
    Irp = Srb->OriginalRequest;

    Srb->SrbStatus = Request->SrbStatus;

    KeSetEvent(Irp->UserEvent, IO_NO_INCREMENT, FALSE);

    return COMPLETE_NO_IRP;
}

ULONG
AtaReqPrepareTaskFile(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension,
    _In_ PSCSI_REQUEST_BLOCK Srb)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PATA_TASKFILE TaskFile;

    if (SRB_GET_FLAGS(Srb) & SRB_FLAG_PACKET_COMMAND)
    {
        RtlCopyMemory(&Request->Cdb, Srb->Cdb, Srb->CdbLength);
        Request->Flags = REQUEST_FLAG_ASYNC_MODE | REQUEST_FLAG_PACKET_COMMAND;
    }
    else
    {
        TaskFile = Request->Irp->UserBuffer;

        RtlCopyMemory(&Request->TaskFile, TaskFile, sizeof(*TaskFile));
        Request->Flags = REQUEST_FLAG_ASYNC_MODE;
    }

    Request->Complete = AtaReqCompleteTaskFile;
    Request->DeviceExtension = DeviceExtension;
    Request->DataBuffer = Srb->DataBuffer;
    Request->DataTransferLength = Srb->DataTransferLength;
    Request->Mdl = Request->Irp->MdlAddress;
    Request->Flags |= (Srb->SrbFlags & SRB_FLAGS_UNSPECIFIED_DIRECTION);

    if (SRB_GET_FLAGS(Srb) & SRB_FLAG_POLL)
    {
        Request->Flags &= ~REQUEST_FLAG_ASYNC_MODE;
    }

    return SRB_STATUS_PENDING;
}
