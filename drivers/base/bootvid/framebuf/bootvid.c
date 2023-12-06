/*
 * PROJECT:     ReactOS Generic Framebuffer Boot Video Driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Main file
 * COPYRIGHT:   Copyright 2023 Hermès Bélusca-Maïto <hermes.belusca-maito@reactos.org>
 */

#include "precomp.h"

#include <arc/arc.h>   // For MONITOR_CONFIGURATION_DATA

#include <debug.h>

#include <drivers/bootvid/framebuf.h>
#define GET_DISPLAY_BY_LDR_BLOCK
#include <drivers/bootvid/framebuf.c> // FIXME: Temporary HACK

/* GLOBALS ********************************************************************/

// FIXME: Those have been copied from xbox.h
#define BB_OFFSET(x, y)    ((y) * SCREEN_WIDTH + (x))
#define FB_OFFSET(x, y)    (((PanV + (y)) * FrameBufferWidth + PanH + (x)) * BytesPerPixel)

static ULONG_PTR FrameBufferStart = 0;
static ULONG FrameBufferWidth, FrameBufferHeight, PanH, PanV;
static UCHAR BytesPerPixel;
static RGBQUAD CachedPalette[BV_MAX_COLORS];
static PUCHAR BackBuffer = NULL;

typedef struct _BOOT_DISPLAY_INFO
{
    PHYSICAL_ADDRESS BaseAddress; // ULONG_PTR
    ULONG BufferSize; // SIZE_T ?

    PVOID FrameAddress; // Mapped framebuffer virtual address.

    /* Configuration data from hardware tree */
    CM_FRAMEBUF_DEVICE_DATA VideoConfigData;

} BOOT_DISPLAY_INFO, *PBOOT_DISPLAY_INFO;

BOOT_DISPLAY_INFO gBootDisp = {0};

/* PRIVATE FUNCTIONS *********************************************************/

static VOID
ApplyPalette(VOID)
{
    PULONG Frame = (PULONG)FrameBufferStart;
    ULONG x, y;

    /* Top panning */
    for (x = 0; x < PanV * FrameBufferWidth; x++)
    {
        *Frame++ = CachedPalette[BV_COLOR_BLACK];
    }

    /* Left panning */
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        Frame = (PULONG)(FrameBufferStart + FB_OFFSET(-PanH, y));

        for (x = 0; x < PanH; x++)
        {
            *Frame++ = CachedPalette[BV_COLOR_BLACK];
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
            *Frame++ = CachedPalette[BV_COLOR_BLACK];
        }
    }

    /* Bottom panning */
    Frame = (PULONG)(FrameBufferStart + FB_OFFSET(-PanH, SCREEN_HEIGHT));
    for (x = 0; x < PanV * FrameBufferWidth; x++)
    {
        *Frame++ = CachedPalette[BV_COLOR_BLACK];
    }
}

/* PUBLIC FUNCTIONS **********************************************************/

BOOLEAN
NTAPI
VidInitialize(
    _In_ BOOLEAN SetMode)
{
    NTSTATUS Status;
    INTERFACE_TYPE Interface;
    ULONG BusNumber;

    RtlZeroMemory(&gBootDisp, sizeof(gBootDisp));
    Status = FindBootDisplay(&gBootDisp.BaseAddress,
                             &gBootDisp.BufferSize,
                             &gBootDisp.VideoConfigData,
                             NULL,
                             &Interface,  // FIXME: Make it opt?
                             &BusNumber); // FIXME: Make it opt?
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Boot framebuffer does not exist!\n");
        return FALSE;
    }


    PHYSICAL_ADDRESS FrameBuffer = gBootDisp.BaseAddress;
    FrameBufferWidth  = gBootDisp.VideoConfigData.ScreenWidth;
    FrameBufferHeight = gBootDisp.VideoConfigData.ScreenHeight;

    /* Verify that the framebuffer address is page-aligned */
    ASSERT(FrameBuffer.QuadPart % PAGE_SIZE == 0);

    if (FrameBufferWidth < SCREEN_WIDTH || FrameBufferHeight < SCREEN_HEIGHT)
    {
        DPRINT1("Unsupported screen resolution!\n");
        goto Failure;
    }

    BytesPerPixel = (gBootDisp.VideoConfigData.BitsPerPixel / 8);
    ASSERT(BytesPerPixel >= 1 && BytesPerPixel <= 4);

    if (BytesPerPixel != 4)
    {
        DPRINT1("Unsupported BytesPerPixel = %d\n", BytesPerPixel);
        goto Failure;
    }

    /* Calculate panning values */
    PanH = (FrameBufferWidth - SCREEN_WIDTH) / 2;
    PanV = (FrameBufferHeight - SCREEN_HEIGHT) / 2;

    /* Verify that screen fits framebuffer size */
    ULONG FrameBufferSize = FrameBufferWidth * FrameBufferHeight * BytesPerPixel;
    if (FrameBufferSize > gBootDisp.BufferSize)
    {
        DPRINT1("Current screen resolution exceeds video memory bounds!\n");
        goto Failure;
    }

    /* Convert from bus-relative to physical address, and map it into system space */
   // PHYSICAL_ADDRESS TranslatedAddress;
    ULONG AddressSpace = 0;
    DPRINT1("Framebuffer %p\n", FrameBuffer.QuadPart);
    FrameBufferStart = (ULONG_PTR)MmMapIoSpace(FrameBuffer,
                                               gBootDisp.BufferSize,
                                               MmNonCached);
    if (!FrameBufferStart)
    {
        DPRINT1("Out of memory!\n");
        goto Failure;
    }
    DPRINT1("Framebuffer mapped %p\n", FrameBufferStart);


    /*
     * Reserve off-screen area for the backbuffer that contains
     * 8-bit indexed color screen image, plus preserved row data.
     */

    /* If there is enough video memory in the physical framebuffer,
     * place the backbuffer in the hidden part of the framebuffer,
     * otherwise allocate a zone for the backbuffer. */

        /* Allocate framebuffer. 600kb works out to 640x480@16bpp */
        SIZE_T BackBufferSize = gBootDisp.BufferSize;
        // PHYSICAL_ADDRESS PhysicalAddress;
        // PhysicalAddress.QuadPart = -1;
        // BackBuffer = MmAllocateContiguousMemory(BackBufferSize, PhysicalAddress);
        BackBuffer = ExAllocatePoolWithTag(NonPagedPool, BackBufferSize, 'bfGB');
        if (!BackBuffer)
        {
            DPRINT1("Out of memory!\n");
            goto Failure;
        }
    
    DPRINT1("everyting is setup\n");
    /* Now check if we have to set the mode */
    if (SetMode)
        VidResetDisplay(TRUE);

    DPRINT1("VidInitialize return true\n");
    /* Video is ready */
    return TRUE;

Failure:
    /* We failed somewhere. Unmap the I/O space if we mapped it */
    if (FrameBufferStart && (AddressSpace == 0))
        MmUnmapIoSpace((PVOID)FrameBufferStart, gBootDisp.BufferSize);

    return FALSE;
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
    /* Re-initialize the palette and fill the screen black */
    RtlZeroMemory((PVOID)FrameBufferStart, gBootDisp.BufferSize);
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
    for (y = 0; y < Height; y++)
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

/* EOF */
