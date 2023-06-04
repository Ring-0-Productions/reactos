/*
 * PROJECT:     ReactOS Boot Video Driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Definitions for framebuffer-specific DisplayController
 *              device boot-time configuration data stored in the
 *              \Registry\Machine\Hardware\Description ARC tree.
 * COPYRIGHT:   Copyright 2023 Hermès Bélusca-Maïto <hermes.belusca-maito@reactos.org>
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Framebuffer-specific device data.
 *
 * Supplemental data, extends CM_VIDEO_DEVICE_DATA.
 * Gets appended to the standard configuration resource list.
 * Any optional Irql/Vector interrupt settings are specified with
 * a CmResourceTypeInterrupt descriptor, while any other I/O port
 * is specified with a CmResourceTypePort descriptor.
 * The framebuffer base and size are specified by the first
 * CmResourceTypeMemory descriptor.
 **/
typedef struct _CM_FRAMEBUF_DEVICE_DATA
{
    CM_VIDEO_DEVICE_DATA;

    /* NOTE: FrameBufferSize == PixelsPerScanLine x ScreenHeight x PixelElementSize */

    /* Horizontal and Vertical resolution in pixels */
    ULONG ScreenWidth;
    ULONG ScreenHeight;

    /* Number of pixel elements per video memory line */
    ULONG PixelsPerScanLine;

    ULONG BitsPerPixel; // PixelDepth

    // MEMMODEL MemoryModel; // Linear, banked, ...

    /*
     * Physical format of the pixel for BPP > 8, specified by bit-mask.
     * A bit being set defines those used for the given color component,
     * such as Red, Green, Blue, or Reserved.
     */
    struct
    {
        // UCHAR NumberRedBits;
        // UCHAR NumberGreenBits;
        // UCHAR NumberBlueBits;
        // UCHAR NumberReservedBits;
        ULONG RedMask;
        ULONG GreenMask;
        ULONG BlueMask;
        ULONG ReservedMask;
    } PixelInformation;

} CM_FRAMEBUF_DEVICE_DATA, *PCM_FRAMEBUF_DEVICE_DATA;

#ifdef __cplusplus
}
#endif

/* EOF */
