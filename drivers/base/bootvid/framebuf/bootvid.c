/*
 * PROJECT:     ReactOS Generic Framebuffer Boot Video Driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Main file
 * COPYRIGHT:   Copyright 2023 Hermès Bélusca-Maïto <hermes.belusca-maito@reactos.org>
 */

#include "precomp.h"

//#include <drivers/bootvid/framebuf.h>
//#include <drivers/videoprt/vpcfgcnv.h>

#include <debug.h>

/* GLOBALS ********************************************************************/

static ULONG_PTR FrameBufferStart = 0;
static ULONG FrameBufferWidth, FrameBufferHeight, PanH, PanV;
static UCHAR BytesPerPixel;
static RGBQUAD CachedPalette[BV_MAX_COLORS];
static PUCHAR BackBuffer = NULL;

typedef struct _BOOT_FRAMEBUF_DATA
{
    PHYSICAL_ADDRESS BaseAddress; // ULONG_PTR
    ULONG BufferSize;
    ULONG ScreenWidth;
    ULONG ScreenHeight;
    ULONG PixelsPerScanLine;
    ULONG PixelFormat;
} BOOT_FRAMEBUF_DATA, *PBOOT_FRAMEBUF_DATA;

BOOT_FRAMEBUF_DATA gBootFbData = {0};

CM_MONITOR_DEVICE_DATA gMonitorConfigData = {0};

/* PRIVATE FUNCTIONS *********************************************************/

static VOID
ApplyPalette(VOID)
{
    PULONG Frame = (PULONG)FrameBufferStart;
    ULONG x, y;

    /* Top panning */
    for (x = 0; x < PanV * FrameBufferWidth; x++)
    {
        *Frame++ = CachedPalette[0];
    }

    /* Left panning */
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        Frame = (PULONG)(FrameBufferStart + FB_OFFSET(-PanH, y));

        for (x = 0; x < PanH; x++)
        {
            *Frame++ = CachedPalette[0];
        }
    }

    /* Screen redraw */
    PUCHAR Back = BackBuffer;
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        Frame = (PULONG)(FrameBufferStart + FB_OFFSET(0, y));

        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            *Frame++ = CachedPalette[*Back++];
        }
    }

    /* Right panning */
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        Frame = (PULONG)(FrameBufferStart + FB_OFFSET(SCREEN_WIDTH, y));

        for (x = 0; x < PanH; x++)
        {
            *Frame++ = CachedPalette[0];
        }
    }

    /* Bottom panning */
    Frame = (PULONG)(FrameBufferStart + FB_OFFSET(-PanH, SCREEN_HEIGHT));
    for (x = 0; x < PanV * FrameBufferWidth; x++)
    {
        *Frame++ = CachedPalette[0];
    }
}

/* PUBLIC FUNCTIONS **********************************************************/

/**
 * @brief
 * Caches configuration data for the boot-time display controller and monitor.
 *
 * This data is initialized by the NT bootloader and passed in the ARC tree
 * pointed by the loader block. It is available only for boot drivers and gets
 * freed later on.
 *
 * TODO: On Win8+, try to also read the BgContext structure.
 **/
static NTSTATUS
CaptureBootDisplayList(
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PCONFIGURATION_COMPONENT_DATA ConfigurationRoot;
    // ULONG ComponentKey = 0; // First controller.
    PCONFIGURATION_COMPONENT_DATA Entry = NULL;
    PCM_PARTIAL_RESOURCE_LIST ResourceList;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor;
    ULONG i;

    RtlZeroMemory(&gBootFbData, sizeof(gBootFbData));
    RtlZeroMemory(&gMonitorConfigData, sizeof(gMonitorConfigData));

    ConfigurationRoot = (LoaderBlock ? LoaderBlock->ConfigurationRoot : NULL);
    if (!ConfigurationRoot)
        return STATUS_DEVICE_DOES_NOT_EXIST;

    /* Enumerate and find the boot-time console display controller */
    while (TRUE)
    {
        Entry = KeFindConfigurationNextEntry(ConfigurationRoot,
                                             ControllerClass,
                                             DisplayController,
                                             NULL, // &ComponentKey
                                             &Entry);
        if (!Entry)
            break;

        if (Entry->ComponentEntry.Flags & (Output | ConsoleOut))
        {
            /* Found it */
            break;
        }
    }

    if (!Entry)
        return STATUS_DEVICE_DOES_NOT_EXIST;

    // Entry->ComponentEntry.IdentifierLength;
    DPRINT1("Display: '%s'\n", Entry->ComponentEntry.Identifier);

    if (!Entry->ConfigurationData ||
        Entry->ComponentEntry.ConfigurationDataLength < sizeof(CM_PARTIAL_RESOURCE_LIST))
    {
        /* Invalid entry?! */
        return STATUS_DEVICE_CONFIGURATION_ERROR;
    }

    ResourceList = Entry->ConfigurationData;
    for (i = 0; i < ResourceList->Count; ++i)
    {
        Descriptor = &ResourceList->PartialDescriptors[i];

        switch (Descriptor->Type)
        {
            case CmResourceTypePort:
                DPRINT1("  CmResourceTypePort\n");
                break;

            case CmResourceTypeInterrupt:
                DPRINT1("  CmResourceTypeInterrupt\n");
                break;

            case CmResourceTypeMemory:
            {
                DPRINT1("  CmResourceTypeMemory\n");

                // or CM_RESOURCE_MEMORY_WRITE_ONLY ??
                // if (!(Descriptor->Flags & CM_RESOURCE_MEMORY_READ_WRITE))
                // {
                //     /* Cannot use this framebuffer */
                //     break;
                // }

                gBootFbData.BaseAddress = Descriptor->u.Memory.Start;
                gBootFbData.BufferSize  = Descriptor->u.Memory.Length;
                break;
            }

            case CmResourceTypeDeviceSpecific:
            {
                PCM_VIDEO_DEVICE_DATA VideoData; // PCM_FRAMEBUF_DEVICE_DATA

                DPRINT1("  CmResourceTypeDeviceSpecific\n");
                /* NOTE: This descriptor *MUST* be the last one */
                if (Descriptor->u.DeviceSpecificData.DataSize < sizeof(CM_VIDEO_DEVICE_DATA))
                {
                    /* Not something we recognize */
                    break;
                }

                /* The actual device data follows the descriptor */
                VideoData = (PCM_VIDEO_DEVICE_DATA)(Descriptor + 1);
                DBG_UNREFERENCED_PARAMETER(VideoData);
                // VideoData->VideoClock; // ULONG

                // VideoData->Version  = ARC_VERSION;
                // VideoData->Revision = ARC_REVISION;

                // gBootFbData.ScreenWidth  = HalContext.ScreenWidth;
                // gBootFbData.ScreenHeight = HalContext.ScreenHeight;
                // gBootFbData.PixelsPerScanLine = HalContext.PixelsPerScanLine;
                // gBootFbData.PixelFormat       = HalContext.PixelFormat;
                break;
            }
        }
    }

    /* Now find the MonitorPeripheral to obtain more information.
     * It should be child of the display controller. */
    Entry = Entry->Child;
    /* Ignore if no monitor data is given */
    if (!Entry)
        return STATUS_SUCCESS;

    // Entry->ComponentEntry.IdentifierLength;
    DPRINT1("Monitor: '%s'\n", Entry->ComponentEntry.Identifier);

    if ((Entry->ComponentEntry.Class != PeripheralClass)   ||
        (Entry->ComponentEntry.Type  != MonitorPeripheral) ||
       !(Entry->ComponentEntry.Flags & (Output | ConsoleOut)))
    {
        /* Ignore */
        return STATUS_SUCCESS;
    }
    if (!Entry->ConfigurationData)
    {
        /* Ignore */
        return STATUS_SUCCESS;
    }

    if (Entry->ComponentEntry.ConfigurationDataLength == sizeof(MONITOR_CONFIGURATION_DATA))
    {
        /* Convert to CM_MONITOR_DEVICE_DATA */
        PMONITOR_CONFIGURATION_DATA MonitorData = Entry->ConfigurationData;

        gMonitorConfigData.Version = MonitorData->Version;
        gMonitorConfigData.Revision = MonitorData->Revision;
        gMonitorConfigData.HorizontalScreenSize = MonitorData->HorizontalScreenSize;
        gMonitorConfigData.VerticalScreenSize = MonitorData->VerticalScreenSize;
        gMonitorConfigData.HorizontalResolution = MonitorData->HorizontalResolution;
        gMonitorConfigData.VerticalResolution = MonitorData->VerticalResolution;
        gMonitorConfigData.HorizontalDisplayTimeLow = 0;
        gMonitorConfigData.HorizontalDisplayTime = MonitorData->HorizontalDisplayTime;
        gMonitorConfigData.HorizontalDisplayTimeHigh = 0;
        gMonitorConfigData.HorizontalBackPorchLow = 0;
        gMonitorConfigData.HorizontalBackPorch = MonitorData->HorizontalBackPorch;
        gMonitorConfigData.HorizontalBackPorchHigh = 0;
        gMonitorConfigData.HorizontalFrontPorchLow = 0;
        gMonitorConfigData.HorizontalFrontPorch = MonitorData->HorizontalFrontPorch;
        gMonitorConfigData.HorizontalFrontPorchHigh = 0;
        gMonitorConfigData.HorizontalSyncLow = 0;
        gMonitorConfigData.HorizontalSync = MonitorData->HorizontalSync;
        gMonitorConfigData.HorizontalSyncHigh = 0;
        gMonitorConfigData.VerticalBackPorchLow = 0;
        gMonitorConfigData.VerticalBackPorch = MonitorData->VerticalBackPorch;
        gMonitorConfigData.VerticalBackPorchHigh = 0;
        gMonitorConfigData.VerticalFrontPorchLow = 0;
        gMonitorConfigData.VerticalFrontPorch = MonitorData->VerticalFrontPorch;
        gMonitorConfigData.VerticalFrontPorchHigh = 0;
        gMonitorConfigData.VerticalSyncLow = 0;
        gMonitorConfigData.VerticalSync = MonitorData->VerticalSync;
        gMonitorConfigData.VerticalSyncHigh = 0;
    }
    else if (Entry->ComponentEntry.ConfigurationDataLength == sizeof(CM_MONITOR_DEVICE_DATA))
    {
        /* Just copy the data */
        RtlCopyMemory(&gMonitorConfigData,
                      Entry->ConfigurationData,
                      sizeof(CM_MONITOR_DEVICE_DATA));
    }
    else
    {
        /* Ignore */
        NOTHING;
    }

    /* If the individual framebuffer screen sizes are not
     * already initialized by now, use monitor data */
    if (gBootFbData.ScreenWidth == 0 || gBootFbData.ScreenHeight == 0)
    {
        gBootFbData.ScreenWidth  = gMonitorConfigData.HorizontalResolution;
        gBootFbData.ScreenHeight = gMonitorConfigData.VerticalResolution;
    }
    return STATUS_SUCCESS;
}

BOOLEAN
NTAPI
VidInitialize(
    _In_ BOOLEAN SetMode)
{
    BOOLEAN Result = FALSE;

    PHYSICAL_ADDRESS PhysControlStart = {.QuadPart = 0xFD000000};
    PHYSICAL_ADDRESS PhysFrameBufferStart = {.QuadPart = 0xF0000000};
    ULONG ControlLength = 16 * 1024 * 1024;

    // QUESTION: Get device MMIO ranges from PCI ?
    if (!CaptureBootDisplayList(KeLoaderBlock));
    {
        DPRINT1("Boot framebuffer does not exist!\n");
        return FALSE;
    }


    ULONG_PTR ControlStart = (ULONG_PTR)MmMapIoSpace(PhysControlStart, ControlLength, MmNonCached);
    if (!ControlStart)
    {
        DPRINT1("Out of memory!\n");
        return FALSE;
    }

    ULONG_PTR FrameBuffer = gBootFbData.BaseAddress;
    FrameBufferWidth  = gBootFbData.ScreenWidth;
    FrameBufferHeight = gBootFbData.ScreenHeight;

    /* Verify that the framebuffer address is page-aligned */
    ASSERT(FrameBuffer % PAGE_SIZE == 0);

    if (FrameBufferWidth < SCREEN_WIDTH || FrameBufferHeight < SCREEN_HEIGHT)
    {
        DPRINT1("Unsupported screen resolution!\n");
        goto cleanup;
    }

    BytesPerPixel = gBootFbData.PixelFormat; // FIXME!
    ASSERT(BytesPerPixel >= 1 && BytesPerPixel <= 4);

    if (BytesPerPixel != 4)
    {
        DPRINT1("Unsupported BytesPerPixel = %d\n", BytesPerPixel);
        goto cleanup;
    }

    /* Calculate panning values */
    PanH = (FrameBufferWidth - SCREEN_WIDTH) / 2;
    PanV = (FrameBufferHeight - SCREEN_HEIGHT) / 2;

    /* Verify that screen fits framebuffer size */
    ULONG FrameBufferSize = FrameBufferWidth * FrameBufferHeight * BytesPerPixel;
    if (FrameBufferSize > gBootFbData.BufferSize)
    {
        DPRINT1("Current screen resolution exceeds video memory bounds!\n");
        goto cleanup;
    }

    /*
     * Reserve off-screen area for the backbuffer that contains
     * 8-bit indexed color screen image, plus preserved row data.
     */
    ULONG BackBufferSize = SCREEN_WIDTH * (SCREEN_HEIGHT + BOOTCHAR_HEIGHT + 1);

    /* Make sure there is enough video memory for backbuffer */
    if (gBootFbData.BufferSize - FrameBufferSize < BackBufferSize)
    {
        DPRINT1("Out of memory!\n");
        goto cleanup;
    }

    /* Return the address back to GPU memory mapped I/O */
    PhysFrameBufferStart.QuadPart += FrameBuffer;
    FrameBufferStart = (ULONG_PTR)MmMapIoSpace(PhysFrameBufferStart, gBootFbData.BufferSize, MmNonCached);
    if (!FrameBufferStart)
    {
        DPRINT1("Out of memory!\n");
        goto cleanup;
    }

    Result = TRUE;

    /* Place backbuffer in the hidden part of framebuffer */
    BackBuffer = (PUCHAR)(FrameBufferStart + gBootFbData.BufferSize - BackBufferSize);

    /* Now check if we have to set the mode */
    if (SetMode)
        VidResetDisplay(TRUE);

cleanup:
    if (ControlStart)
        MmUnmapIoSpace((PVOID)ControlStart, ControlLength);

    /* Video is ready */
    return Result;
}

VOID
NTAPI
VidCleanUp(VOID)
{
    /* Just fill the screen black */
    VidSolidColorFill(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, BV_COLOR_BLACK);
}

VOID
NTAPI
VidResetDisplay(
    _In_ BOOLEAN HalReset)
{
    /* Clear the current position */
    VidpCurrentX = 0;
    VidpCurrentY = 0;

    /* Clear the screen with HAL if we were asked to */
    if (HalReset)
        HalResetDisplay();

    /* Re-initialize the palette and fill the screen black */
    RtlZeroMemory((PVOID)FrameBufferStart, gBootFbData.BufferSize);
    InitializePalette();
    VidSolidColorFill(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, BV_COLOR_BLACK);
}

VOID
NTAPI
InitPaletteWithTable(
    _In_ PULONG Table,
    _In_ ULONG Count)
{
    PULONG Entry = Table;
    ULONG i;

    for (i = 0; i < Count; i++, Entry++)
    {
        CachedPalette[i] = *Entry | 0xFF000000;
    }
    ApplyPalette();
}

VOID
PrepareForSetPixel(VOID)
{
    /* Nothing to prepare */
    NOTHING;
}

VOID
SetPixel(
    _In_ ULONG Left,
    _In_ ULONG Top,
    _In_ UCHAR Color)
{
    PUCHAR Back = BackBuffer + BB_OFFSET(Left, Top);
    PULONG Frame = (PULONG)(FrameBufferStart + FB_OFFSET(Left, Top));

    *Back = Color;
    *Frame = CachedPalette[Color];
}

VOID
NTAPI
PreserveRow(
    _In_ ULONG CurrentTop,
    _In_ ULONG TopDelta,
    _In_ BOOLEAN Restore)
{
    PUCHAR NewPosition, OldPosition;

    /* Calculate the position in memory for the row */
    if (Restore)
    {
        /* Restore the row by copying back the contents saved off-screen */
        NewPosition = BackBuffer + BB_OFFSET(0, CurrentTop);
        OldPosition = BackBuffer + BB_OFFSET(0, SCREEN_HEIGHT);
    }
    else
    {
        /* Preserve the row by saving its contents off-screen */
        NewPosition = BackBuffer + BB_OFFSET(0, SCREEN_HEIGHT);
        OldPosition = BackBuffer + BB_OFFSET(0, CurrentTop);
    }

    /* Set the count and loop every pixel of backbuffer */
    ULONG Count = TopDelta * SCREEN_WIDTH;

    RtlCopyMemory(NewPosition, OldPosition, Count);

    if (Restore)
    {
        NewPosition = BackBuffer + BB_OFFSET(0, CurrentTop);

        /* Set the count and loop every pixel of framebuffer */
        for (ULONG y = 0; y < TopDelta; y++)
        {
            PULONG Frame = (PULONG)(FrameBufferStart + FB_OFFSET(0, CurrentTop + y));

            Count = SCREEN_WIDTH;
            while (Count--)
            {
                *Frame++ = CachedPalette[*NewPosition++];
            }
        }
    }
}

VOID
NTAPI
DoScroll(
    _In_ ULONG Scroll)
{
    ULONG RowSize = VidpScrollRegion[2] - VidpScrollRegion[0] + 1;

    /* Calculate the position in memory for the row */
    PUCHAR OldPosition = BackBuffer + BB_OFFSET(VidpScrollRegion[0], VidpScrollRegion[1] + Scroll);
    PUCHAR NewPosition = BackBuffer + BB_OFFSET(VidpScrollRegion[0], VidpScrollRegion[1]);

    /* Start loop */
    for (ULONG Top = VidpScrollRegion[1]; Top <= VidpScrollRegion[3]; ++Top)
    {
        ULONG i;

        /* Scroll the row */
        RtlCopyMemory(NewPosition, OldPosition, RowSize);

        PULONG Frame = (PULONG)(FrameBufferStart + FB_OFFSET(VidpScrollRegion[0], Top));

        for (i = 0; i < RowSize; ++i)
            Frame[i] = CachedPalette[NewPosition[i]];

        OldPosition += SCREEN_WIDTH;
        NewPosition += SCREEN_WIDTH;
    }
}

VOID
NTAPI
DisplayCharacter(
    _In_ CHAR Character,
    _In_ ULONG Left,
    _In_ ULONG Top,
    _In_ ULONG TextColor,
    _In_ ULONG BackColor)
{
    /* Get the font and pixel pointer */
    PUCHAR FontChar = GetFontPtr(Character);

    /* Loop each pixel height */
    for (ULONG y = Top; y < Top + BOOTCHAR_HEIGHT; y++, FontChar += FONT_PTR_DELTA)
    {
        /* Loop each pixel width */
        ULONG x = Left;

        for (UCHAR bit = 1 << (BOOTCHAR_WIDTH - 1); bit > 0; bit >>= 1, x++)
        {
            /* Check if we should draw this pixel */
            if (*FontChar & bit)
            {
                /* We do, use the given Text Color */
                SetPixel(x, y, (UCHAR)TextColor);
            }
            else if (BackColor < BV_COLOR_NONE)
            {
                /*
                 * This is a background pixel. We're drawing it
                 * unless it's transparent.
                 */
                SetPixel(x, y, (UCHAR)BackColor);
            }
        }
    }
}

VOID
NTAPI
VidSolidColorFill(
    _In_ ULONG Left,
    _In_ ULONG Top,
    _In_ ULONG Right,
    _In_ ULONG Bottom,
    _In_ UCHAR Color)
{
    while (Top <= Bottom)
    {
        PUCHAR Back = BackBuffer + BB_OFFSET(Left, Top);
        PULONG Frame = (PULONG)(FrameBufferStart + FB_OFFSET(Left, Top));
        ULONG L = Left;

        while (L++ <= Right)
        {
            *Back++ = Color;
            *Frame++ = CachedPalette[Color];
        }
        Top++;
    }
}

VOID
NTAPI
VidScreenToBufferBlt(
    _Out_writes_bytes_(Delta * Height) PUCHAR Buffer,
    _In_ ULONG Left,
    _In_ ULONG Top,
    _In_ ULONG Width,
    _In_ ULONG Height,
    _In_ ULONG Delta)
{
    ULONG x, y;

    /* Clear the destination buffer */
    RtlZeroMemory(Buffer, Delta * Height);

    /* Start the outer Y height loop */
    for (ULONG y = 0; y < Height; y++)
    {
        /* Set current scanline */
        PUCHAR Back = BackBuffer + BB_OFFSET(Left, Top + y);
        PUCHAR Buf = Buffer + y * Delta;

        /* Start the X inner loop */
        for (x = 0; x < Width; x += sizeof(USHORT))
        {
            /* Read the current value */
            *Buf = (*Back++ & 0xF) << 4;
            *Buf |= *Back++ & 0xF;
            Buf++;
        }
    }
}
