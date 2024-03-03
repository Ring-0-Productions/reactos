/*
 * PROJECT:     ReactOS ATA Port Driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Request handling
 * COPYRIGHT:   Copyright 2024 Dmitry Borisov (di.sean@protonmail.com)
 */

/* INCLUDES *******************************************************************/

#include "atapi.h"

/* FUNCTIONS ******************************************************************/

static
ULONG
AtaSendRequestSense(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    PSCSI_REQUEST_BLOCK Srb;
    PCDB Cdb;
    ULONG DataTransferLength;

    /* Don't use DMA for the transfer to avoid DMA errors */
    Request->Flags &= ~(REQUEST_FLAG_DATA_OUT | REQUEST_FLAG_DMA_ENABLED);
    Request->Flags |= REQUEST_FLAG_REQUEST_SENSE | REQUEST_FLAG_DATA_IN;

    Srb = Request->Srb;

    DataTransferLength = Srb->SenseInfoBufferLength;

    ChannelExtension->DataBuffer = Srb->SenseInfoBuffer;
    ChannelExtension->BytesToTransfer = DataTransferLength;

    /* Save the request data length */
    Request->OldDataTransferLength = Request->DataTransferLength;
    Request->DataTransferLength = DataTransferLength;

    /* Build CDB for REQUEST SENSE */
    Cdb = (PCDB)Request->Cdb;
    Cdb->CDB6INQUIRY.OperationCode = SCSIOP_REQUEST_SENSE;
    Cdb->CDB6INQUIRY.LogicalUnitNumber = 0;
    Cdb->CDB6INQUIRY.Reserved1 = 0;
    Cdb->CDB6INQUIRY.PageCode = 0;
    Cdb->CDB6INQUIRY.IReserved = 0;
    Cdb->CDB6INQUIRY.AllocationLength = (UCHAR)DataTransferLength;
    Cdb->CDB6INQUIRY.Control = 0;

    return AtaExecuteCommand(ChannelExtension);
}

static
VOID
AtaSendCdb(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;

    /* Command packet transfer */
    ATA_WRITE_BLOCK_16((PUSHORT)ChannelExtension->Registers.Data,
                       (PUSHORT)Request->Cdb,
                       Request->DeviceExtension->CdbSize);

    if (Request->Flags & REQUEST_FLAG_DMA_ENABLED)
    {
        /* Start the DMA engine */

        ChannelExtension->CommandFlags &= ~CMD_FLAG_REQUEST_MASK;
        ChannelExtension->CommandFlags |= CMD_FLAG_DMA_TRANSFER;
    }
}

static
VOID
AtaReadTaskFile(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;

    Request->TaskFile.Error = ATA_READ(ChannelExtension->Registers.Error);
    Request->TaskFile.SectorCount = ATA_READ(ChannelExtension->Registers.SectorCount);
    Request->TaskFile.LowLba = ATA_READ(ChannelExtension->Registers.LowLba);
    Request->TaskFile.MidLba = ATA_READ(ChannelExtension->Registers.MidLba);
    Request->TaskFile.HighLba = ATA_READ(ChannelExtension->Registers.HighLba);
    Request->TaskFile.DriveSelect = ATA_READ(ChannelExtension->Registers.DriveSelect);
    Request->TaskFile.Command = ATA_READ(ChannelExtension->Registers.Command);

    if (Request->Flags & REQUEST_FLAG_LBA48)
    {
        UCHAR Control = ATA_READ(ChannelExtension->Registers.Control);

        ATA_WRITE(ChannelExtension->Registers.Control, Control | IDE_HIGH_ORDER_BYTE);

        /* Read the extra information from the second byte of FIFO */
        Request->TaskFile.FeatureEx = ATA_READ(ChannelExtension->Registers.Feature);
        Request->TaskFile.SectorCountEx = ATA_READ(ChannelExtension->Registers.SectorCount);
        Request->TaskFile.LowLbaEx = ATA_READ(ChannelExtension->Registers.LowLba);
        Request->TaskFile.MidLbaEx = ATA_READ(ChannelExtension->Registers.MidLba);
        Request->TaskFile.HighLbaEx = ATA_READ(ChannelExtension->Registers.HighLba);

        ATA_WRITE(ChannelExtension->Registers.Control, Control);
    }
}

static
VOID
AtaPioDataIn(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ ULONG ByteCount)
{
    ByteCount = min(ByteCount, ChannelExtension->BytesToTransfer);

    /* Transfer the data block */
    ATA_READ_BLOCK_16((PUSHORT)ChannelExtension->Registers.Data,
                      (PUSHORT)ChannelExtension->DataBuffer,
                      ByteCount / sizeof(USHORT));

    /* Read one last byte */
    if (ByteCount & (sizeof(USHORT) - 1))
    {
        PUCHAR Buffer = ChannelExtension->DataBuffer + ByteCount - 1;

        *Buffer = ATA_READ(ChannelExtension->Registers.Data);
    }

    ChannelExtension->DataBuffer += ByteCount;
    ChannelExtension->BytesToTransfer -= ByteCount;
}

static
VOID
AtaPioDataOut(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ ULONG ByteCount)
{
    ByteCount = min(ByteCount, ChannelExtension->BytesToTransfer);

    /* Transfer the data block */
    ATA_WRITE_BLOCK_16((PUSHORT)ChannelExtension->Registers.Data,
                       (PUSHORT)ChannelExtension->DataBuffer,
                       ByteCount / sizeof(USHORT));

    /* Write one last byte */
    if (ByteCount & (sizeof(USHORT) - 1))
    {
        PUCHAR Buffer = ChannelExtension->DataBuffer + ByteCount - 1;

        ATA_WRITE(ChannelExtension->Registers.Data, *Buffer);
    }

    ChannelExtension->DataBuffer += ByteCount;
    ChannelExtension->BytesToTransfer -= ByteCount;
}

BOOLEAN
AtaProcessRequest(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ UCHAR IdeStatus,
    _In_ UCHAR DmaStatus)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    UCHAR InterruptReason;
    ULONG ByteCount;
    BOOLEAN Success;
    ULONG SrbStatus;

    ASSERT(!(IdeStatus & IDE_STATUS_BUSY));

    switch (ChannelExtension->CommandFlags & CMD_FLAG_REQUEST_MASK)
    {
        case CMD_FLAG_DMA_TRANSFER:
        {
            if (DmaStatus & DMA_STATUS_ERROR)
            {
                SrbStatus = SRB_STATUS_ERROR;
            }
            else if ((DmaStatus & DMA_STATUS_ACTIVE) &&
                     !(ChannelExtension->Flags & CHANNEL_IGNORE_ACTIVE_DMA))
            {
                SrbStatus = SRB_STATUS_DATA_OVERRUN;
            }
            else
            {
                SrbStatus = SRB_STATUS_SUCCESS;
            }

            Success = !(IdeStatus & IDE_STATUS_ERROR);
            goto Complete;
        }

        case CMD_FLAG_ATA_REQUEST:
        {
            ULONG BlockCount;

            if (IdeStatus & (IDE_STATUS_ERROR | IDE_STATUS_DEVICE_FAULT))
            {
                Success = FALSE;
                break;
            }

            if (!(IdeStatus & IDE_STATUS_DRQ))
            {
                Success = TRUE;
                break;
            }

            if (Request->Flags & REQUEST_FLAG_READ_WRITE_MULTIPLE)
                BlockCount = Request->DeviceExtension->MultiSectorTransfer;
            else
                BlockCount = 1;
            ByteCount = BlockCount * Request->DeviceExtension->SectorSize;

            if (ChannelExtension->CommandFlags & CMD_FLAG_DATA_IN)
            {
                AtaPioDataIn(ChannelExtension, ByteCount);

                if (!ChannelExtension->BytesToTransfer)
                {
                    Success = TRUE;
                    break;
                }
            }
            else
            {
                AtaPioDataOut(ChannelExtension, ByteCount);
            }

            return FALSE;
        }

        case CMD_FLAG_ATAPI_REQUEST:
        {
            InterruptReason = ATA_READ(ChannelExtension->Registers.InterruptReason);
            InterruptReason &= ATAPI_INTERRUPT_REASON_MASK;
            InterruptReason |= IdeStatus & IDE_STATUS_DRQ;

            switch (InterruptReason)
            {
                case ATAPI_INTERRUPT_REASON_AWAIT_CDB:
                {
                    if (ChannelExtension->CommandFlags & CMD_FLAG_CDB)
                    {
                        WARN("Invalid interrupt reason %02x\n", InterruptReason);
                        Success = FALSE;
                        break;
                    }
                    ChannelExtension->CommandFlags |= CMD_FLAG_CDB;

                    AtaSendCdb(ChannelExtension);
                    return FALSE;
                }

                case ATAPI_INTERRUPT_REASON_DATA_IN:
                {
                    if (ChannelExtension->CommandFlags & CMD_FLAG_DATA_OUT)
                    {
                        WARN("Invalid interrupt reason %02x\n", InterruptReason);
                        Success = FALSE;
                        break;
                    }

                    ByteCount = ATA_READ(ChannelExtension->Registers.ByteCountLow) |
                                (ATA_READ(ChannelExtension->Registers.ByteCountHigh) << 8);

                    AtaPioDataIn(ChannelExtension, ByteCount);
                    return FALSE;
                }

                case ATAPI_INTERRUPT_REASON_DATA_OUT:
                {
                    if (ChannelExtension->CommandFlags & CMD_FLAG_DATA_IN)
                    {
                        WARN("Invalid interrupt reason %02x\n", InterruptReason);
                        Success = FALSE;
                        break;
                    }

                    ByteCount = ATA_READ(ChannelExtension->Registers.ByteCountLow) |
                                (ATA_READ(ChannelExtension->Registers.ByteCountHigh) << 8);

                    AtaPioDataOut(ChannelExtension, ByteCount);
                    return FALSE;
                }

                case ATAPI_INTERRUPT_REASON_INVALID:
                {
                    /* The NEC CDR-260 drive clears CoD and IO on command completion */
                    if (!(Request->DeviceExtension->Flags & DEVICE_IS_NEC_CDR260))
                    {
                        WARN("Invalid interrupt reason %02x\n", InterruptReason);
                        Success = FALSE;
                        break;
                    }
                    __fallthrough;
                }
                case ATAPI_INTERRUPT_REASON_CMD_COMPLETION:
                {
                    Success = !(IdeStatus & (IDE_STATUS_ERROR | IDE_STATUS_DEVICE_FAULT));
                    break;
                }

                default:
                {
                    WARN("Invalid interrupt reason %02x\n", InterruptReason);
                    Success = FALSE;
                    break;
                }
            }

            break;
        }

        default:
        {
            ASSERT(FALSE);
            UNREACHABLE;
        }
    }

    if (ChannelExtension->BytesToTransfer)
        SrbStatus = SRB_STATUS_DATA_OVERRUN;
    else
        SrbStatus = SRB_STATUS_SUCCESS;

Complete:

    if (!Success)
    {
        UCHAR Error = ATA_READ(ChannelExtension->Registers.Error);

        SrbStatus = SRB_STATUS_ERROR;

        Request->Error = Error;

        Request->DataTransferLength = 0;
    }

    if (SrbStatus == SRB_STATUS_DATA_OVERRUN)
    {
        ASSERT(Request->DataTransferLength >= ChannelExtension->BytesToTransfer);
        Request->DataTransferLength -= ChannelExtension->BytesToTransfer;
    }

    Request->SrbStatus = SrbStatus;
    Request->Status = IdeStatus;

    /* Make sure that the request handler won't be invoked from the interrupt handler */
    ChannelExtension->CommandFlags = CMD_FLAG_NONE;

    /* Handle failed ATAPI commands */
    if ((SrbStatus == SRB_STATUS_ERROR) && (Request->Flags & REQUEST_FLAG_PACKET_COMMAND))
    {
        PSCSI_REQUEST_BLOCK Srb = Request->Srb;

        /* Send the REQUEST SENSE command to figure out why the current command failed */
        if (Srb->SenseInfoBuffer && Srb->SenseInfoBufferLength &&
            !(Request->Flags & REQUEST_FLAG_REQUEST_SENSE))
        {
            SrbStatus = AtaSendRequestSense(ChannelExtension);
            if (SrbStatus == SRB_STATUS_PENDING)
                return FALSE;

            Request->SrbStatus = SrbStatus;
        }
    }

    /* Save the latest copy of the task file registers */
    if (Request->Flags & REQUEST_FLAG_SAVE_TASK_FILE)
    {
        Request->Flags |= REQUEST_FLAG_HAS_TASK_FILE;

        AtaReadTaskFile(ChannelExtension);
    }

    Request->Flags |= REQUEST_FLAG_COMPLETED;

    /* Complete the request */
    KeInsertQueueDpc(&ChannelExtension->Dpc, NULL, NULL);
    return TRUE;
}

BOOLEAN
NTAPI
AtaPciIdeChannelIsr(
    _In_ PKINTERRUPT Interrupt,
    _In_ PVOID Context)
{
    return TRUE;
}

BOOLEAN
NTAPI
AtaIdeChannelIsr(
    _In_ PKINTERRUPT Interrupt,
    _In_ PVOID Context)
{
    PATAPORT_CHANNEL_EXTENSION ChannelExtension = Context;
    UCHAR IdeStatus;

    UNREFERENCED_PARAMETER(Interrupt);

    /* Acknowledge the IDE interrupt */
    IdeStatus = ATA_READ(ChannelExtension->Registers.Status);

    /* This interrupt is spurious or not ours */
    if (!(ChannelExtension->CommandFlags & CMD_FLAG_AWAIT_INTERRUPT) ||
        (IdeStatus & IDE_STATUS_BUSY))
    {
        WARN("Spurious IDE interrupt %02x\n", IdeStatus);
        return FALSE;
    }

    AtaProcessRequest(ChannelExtension, IdeStatus, 0);

    return TRUE;
}

static
ULONG
AtaExecuteAtaCommand(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    ULONG CommandFlags;
    UCHAR Status;

    /* Prepare the registers */
    if (Request->Flags & REQUEST_FLAG_LBA48)
    {
        ATA_WRITE(ChannelExtension->Registers.Feature, Request->TaskFile.FeatureEx);
        ATA_WRITE(ChannelExtension->Registers.SectorCount, Request->TaskFile.SectorCountEx);
        ATA_WRITE(ChannelExtension->Registers.LowLba, Request->TaskFile.LowLbaEx);
        ATA_WRITE(ChannelExtension->Registers.MidLba, Request->TaskFile.MidLbaEx);
        ATA_WRITE(ChannelExtension->Registers.HighLba, Request->TaskFile.HighLbaEx);

        /* Store the extra information in the second byte of FIFO */
    }
    ATA_WRITE(ChannelExtension->Registers.Feature, Request->TaskFile.Feature);
    ATA_WRITE(ChannelExtension->Registers.SectorCount, Request->TaskFile.SectorCount);
    ATA_WRITE(ChannelExtension->Registers.LowLba, Request->TaskFile.LowLba);
    ATA_WRITE(ChannelExtension->Registers.MidLba, Request->TaskFile.MidLba);
    ATA_WRITE(ChannelExtension->Registers.HighLba, Request->TaskFile.HighLba);
    if (Request->Flags & REQUEST_FLAG_SET_DEVICE_REGISTER)
    {
        ATA_WRITE(ChannelExtension->Registers.DriveSelect,
                  Request->TaskFile.DriveSelect | (DeviceExtension->DeviceHead & 0xF8));
    }
    ATA_WRITE(ChannelExtension->Registers.Command, Request->TaskFile.Command);

    CommandFlags = Request->Flags & REQUEST_FLAG_ASYNC_MODE; // Set CMD_FLAG_AWAIT_INTERRUPT

    if (Request->Flags & REQUEST_FLAG_DMA_ENABLED)
    {
        /* Start the DMA engine */

        /* Wait for an interrupt */
        goto WaitIntr;
    }

    CommandFlags |= CMD_FLAG_ATA_REQUEST;

    /*
     * For PIO writes we need to send the first data block
     * to make the devive to start generating interrupts.
     */
    if ((Request->Flags & (REQUEST_FLAG_DATA_OUT | REQUEST_FLAG_ASYNC_MODE)) ==
        (REQUEST_FLAG_DATA_OUT | REQUEST_FLAG_ASYNC_MODE))
    {
        ULONG BlockCount, ByteCount;

        /* Need to wait for a valid status */
        ATA_IO_WAIT();

        Status = ATA_READ(ChannelExtension->Registers.Status);

        /* Wait for busy being cleared and DRQ or ERR bit being set */
        ATA_WAIT_ON_BUSY(ChannelExtension, &Status, ATA_TIME_BUSY_NORMAL);
        if (Status & IDE_STATUS_BUSY)
        {
            TRACE("Timeout, status 0x%02x\n", Status);
            return SRB_STATUS_TIMEOUT;
        }
        if (Status & IDE_STATUS_ERROR)
        {
            TRACE("Device error, status 0x%02x\n", Status);

            /* On device error we will get an interrupt anyway */
            goto WaitIntr;
        }
        ATA_WAIT_FOR_DRQ(ChannelExtension, &Status, IDE_STATUS_DRDY, ATA_TIME_DRQ_NORMAL);
        if (!(Status & IDE_STATUS_DRQ))
        {
            TRACE("DRQ timeout, status 0x%02x\n", Status);
            return SRB_STATUS_TIMEOUT;
        }

        if (Request->Flags & REQUEST_FLAG_READ_WRITE_MULTIPLE)
            BlockCount = Request->DeviceExtension->MultiSectorTransfer;
        else
            BlockCount = 1;
        ByteCount = BlockCount * Request->DeviceExtension->SectorSize;

        /* Transfer the first data block */
        AtaPioDataOut(ChannelExtension, ByteCount);
    }

    /* Wait for remaining interrupts */
WaitIntr:
    CommandFlags |= (Request->Flags & (REQUEST_FLAG_DATA_IN | REQUEST_FLAG_DATA_OUT));
    ChannelExtension->CommandFlags = CommandFlags;

    return SRB_STATUS_PENDING;
}

static
ULONG
AtaExecutePacketCommand(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension,
    _In_ PATAPORT_DEVICE_EXTENSION DeviceExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    ULONG CommandFlags;
    USHORT ByteCount;
    UCHAR Status, Feature;

    CommandFlags = Request->Flags & REQUEST_FLAG_ASYNC_MODE; // Set CMD_FLAG_AWAIT_INTERRUPT

    /* Prepare to transfer a device command */
    if (Request->Flags & REQUEST_FLAG_DMA_ENABLED)
    {
        /* DMA transfer */
        ByteCount = 0;
        Feature = 1;
        CommandFlags |= CMD_FLAG_DMA_TRANSFER;
    }
    else
    {
        /* PIO transfer */
        ByteCount = min(ChannelExtension->BytesToTransfer, 0xFFFF - 1);
        Feature = 0;
        CommandFlags |= CMD_FLAG_ATAPI_REQUEST;
    }
    ATA_WRITE(ChannelExtension->Registers.ByteCountLow, (UCHAR)ByteCount);
    ATA_WRITE(ChannelExtension->Registers.ByteCountHigh, ByteCount >> 8);
    ATA_WRITE(ChannelExtension->Registers.Feature, Feature);
    ATA_WRITE(ChannelExtension->Registers.Command, IDE_COMMAND_ATAPI_PACKET);

    /* Wait for an interrupt that signals that device is ready to accept the command packet */
    if (DeviceExtension->Flags & DEVICE_HAS_CDB_INTERRUPT)
    {
        CommandFlags &= ~CMD_FLAG_DMA_TRANSFER;
        goto WaitIntr;
    }

    CommandFlags |= CMD_FLAG_CDB;

    /* Need to wait for a valid status */
    ATA_IO_WAIT();

    Status = ATA_READ(ChannelExtension->Registers.Status);

    /* Wait for busy being cleared and DRQ or ERR bit being set */
    ATA_WAIT_ON_BUSY(ChannelExtension, &Status, ATA_TIME_BUSY_NORMAL);
    if (Status & IDE_STATUS_BUSY)
    {
        TRACE("Timeout, status 0x%02x\n", Status);
        return SRB_STATUS_TIMEOUT;
    }
    if (Status & IDE_STATUS_ERROR)
    {
        TRACE("Device error, status 0x%02x\n", Status);

        /* On device error we will get an interrupt anyway */
        goto WaitIntr;
    }
    ATA_WAIT_FOR_DRQ(ChannelExtension, &Status, 0, ATA_TIME_DRQ_NORMAL);
    if (!(Status & IDE_STATUS_DRQ))
    {
        TRACE("DRQ timeout, status 0x%02x\n", Status);
        return SRB_STATUS_TIMEOUT;
    }

    /* Command packet transfer */
    ATA_WRITE_BLOCK_16((PUSHORT)ChannelExtension->Registers.Data,
                       (PUSHORT)Request->Cdb,
                       DeviceExtension->CdbSize);

    if (Request->Flags & REQUEST_FLAG_DMA_ENABLED)
    {
        /* Start the DMA engine */
    }

    /* Wait for remaining interrupts */
WaitIntr:
    CommandFlags |= (Request->Flags & (REQUEST_FLAG_DATA_IN | REQUEST_FLAG_DATA_OUT));
    ChannelExtension->CommandFlags = CommandFlags;

    return SRB_STATUS_PENDING;
}

BOOLEAN
AtaDevicePresent(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    UCHAR Status;

    /* Do a quick check first */
    Status = ATA_READ(ChannelExtension->Registers.Status);
    if (Status == 0xFF || Status == 0x7F)
        return FALSE;

    /* Look at controller */
    ATA_WRITE(ChannelExtension->Registers.ByteCountLow, 0x55);
    ATA_WRITE(ChannelExtension->Registers.ByteCountLow, 0xAA);
    ATA_WRITE(ChannelExtension->Registers.ByteCountLow, 0x55);
    if (ATA_READ(ChannelExtension->Registers.ByteCountLow) != 0x55)
        return FALSE;
    ATA_WRITE(ChannelExtension->Registers.ByteCountHigh, 0xAA);
    ATA_WRITE(ChannelExtension->Registers.ByteCountHigh, 0x55);
    ATA_WRITE(ChannelExtension->Registers.ByteCountHigh, 0xAA);
    if (ATA_READ(ChannelExtension->Registers.ByteCountHigh) != 0xAA)
        return FALSE;

    return TRUE;
}

static
VOID
AtaChangeInterruptMode(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    UCHAR Control;

    if (Request->Flags & REQUEST_FLAG_ASYNC_MODE)
        Control = 0;
    else
        Control = IDE_DC_DISABLE_INTERRUPTS;
    ATA_WRITE(ChannelExtension->Registers.Control, Control);
}

ULONG
AtaExecuteCommand(
    _In_ PATAPORT_CHANNEL_EXTENSION ChannelExtension)
{
    PATA_DEVICE_REQUEST Request = &ChannelExtension->Request;
    UCHAR Status;

    /* Select the device */
    ATA_SELECT_DEVICE(ChannelExtension, Request->DeviceExtension->DeviceHead);

    /* Determine device presence */
    if (SRB_GET_FLAGS(Request->Srb) & SRB_FLAG_DEVICE_CHECK)
    {
        if (!AtaDevicePresent(ChannelExtension))
            return SRB_STATUS_SELECTION_TIMEOUT;
    }

    /* Wait for busy to clear */
    Status = ATA_READ(ChannelExtension->Registers.Status);
    ATA_WAIT_ON_BUSY(ChannelExtension, &Status, ATA_TIME_BUSY_SELECT);
    if (Status & IDE_STATUS_BUSY)
        return SRB_STATUS_BUSY;

    AtaChangeInterruptMode(ChannelExtension);

    /* Execute the command */
    if (Request->Flags & REQUEST_FLAG_PACKET_COMMAND)
        return AtaExecutePacketCommand(ChannelExtension, Request->DeviceExtension);
    else
        return AtaExecuteAtaCommand(ChannelExtension, Request->DeviceExtension);
}
