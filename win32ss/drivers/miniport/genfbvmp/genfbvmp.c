/*
 * PROJECT:     ReactOS Generic Framebuffer Video Miniport Driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Main file.
 * COPYRIGHT:   Copyright 2022-2023 Justin Miller <justinmiller100@gmail.com>
 *              Copyright 2023 Hermès Bélusca-Maïto <hermes.belusca-maito@reactos.org>
 */

#include <ntifs.h>
#include <arc/arc.h>

#include <dderror.h>
#define __BROKEN__
#include <miniport.h>
#include <video.h>
#include <devioctl.h>

#include <section_attribs.h>

#include <debug.h>
// #define DPRINT(fmt, ...)    VideoDebugPrint((Info, fmt, ##__VA_ARGS__))
// #define DPRINT1(fmt, ...)   VideoDebugPrint((Error, fmt, ##__VA_ARGS__))

#include <drivers/bootvid/framebuf.h>
#include <drivers/videoprt/vpcfgcnv.h>

/********************************** Globals ***********************************/

/**
 * @brief
 * Registry Identification strings used in GenFbVmpFindAdapter()
 * for "HardwareInformation.AdapterString", "HardwareInformation.BiosString",
 * "HardwareInformation.ChipType", and "HardwareInformation.DacType".
 **/
static const WCHAR AdapterString[]   = L"Generic Framebuffer"; // "Basic Display Driver"
static const WCHAR AdapterChipType[] = L"Framebuffer";
static const WCHAR AdapterDacType[]  = L"Internal";

typedef struct _BOOT_FRAMEBUF_DATA
{
    PHYSICAL_ADDRESS BaseAddress; // ULONG_PTR
    ULONG BufferSize;
    ULONG ScreenWidth;
    ULONG ScreenHeight;
    ULONG PixelsPerScanLine;
    ULONG PixelFormat;
} BOOT_FRAMEBUF_DATA, *PBOOT_FRAMEBUF_DATA;

#if 0
typedef struct
{
    PUCHAR Mapped;
    PHYSICAL_ADDRESS RangeStart;
    ULONG RangeLength;
    UCHAR RangeInIoSpace;
} GENFB_ADDRESS_RANGE;
#endif

typedef struct
{
    BOOT_FRAMEBUF_DATA FrameBufData;
    // GENFB_ADDRESS_RANGE FrameBuffer;
    PVOID FrameAddress; // Mapped framebuffer virtual address.

    /* Configuration data from hardware tree */
    CM_FRAMEBUF_DEVICE_DATA VideoConfigData;
    CM_MONITOR_DEVICE_DATA MonitorConfigData;

    /* The one and only video mode we support */
    VIDEO_MODE_INFORMATION CurrentVideoMode;
} GENFB_DEVICE_EXTENSION, *PGENFB_DEVICE_EXTENSION;


/********************************** Private ***********************************/

/**
 * @brief
 * Maps the video framebuffer to the requested preferred address.
 **/
static VP_STATUS
GenFbVmpMapVideoMemory(
    _In_ PGENFB_DEVICE_EXTENSION DeviceExtension,
    _In_ PVIDEO_MEMORY RequestedAddress,
    _Out_ PVIDEO_MEMORY_INFORMATION MapInformation,
    _Out_ PSTATUS_BLOCK StatusBlock)
{
    VP_STATUS Status;
    PBOOT_FRAMEBUF_DATA FrameBufData = &DeviceExtension->FrameBufData;
    PHYSICAL_ADDRESS FrameBuffer = FrameBufData->BaseAddress;
    ULONG InIoSpace = VIDEO_MEMORY_SPACE_MEMORY;

    /* Map the framebuffer (set up by the firmware) to the
     * preferred address the user requests, if possible. */
    MapInformation->VideoRamBase = RequestedAddress->RequestedVirtualAddress;
    MapInformation->VideoRamLength = FrameBufData->BufferSize;

// NOTE: VideoRamLength == VideoMemoryBitmapHeight * ScreenStride
// and:  FrameBufferLength == VisScreenHeight * ScreenStride.

    Status = VideoPortMapMemory(DeviceExtension,
                                FrameBuffer,
                                &MapInformation->VideoRamLength,
                                &InIoSpace,
                                &MapInformation->VideoRamBase);
    if (Status != NO_ERROR)
    {
        DPRINT1("Failed to map framebuffer memory 0x%I64x\n", FrameBuffer.QuadPart);
        return Status;
    }

    /* For framebuffers, it is expected that FrameBufferBase == VideoRamBase */
    MapInformation->FrameBufferBase   = MapInformation->VideoRamBase;
    MapInformation->FrameBufferLength = MapInformation->VideoRamLength;

    DPRINT1("Mapped 0x%x bytes of phys mem at 0x%I64x to virt addr 0x%p\n",
            MapInformation->VideoRamLength,
            FrameBuffer.QuadPart,
            MapInformation->VideoRamBase);

    StatusBlock->Information = sizeof(VIDEO_MEMORY_INFORMATION);
    return Status;
}

/**
 * @brief
 * Releases the mapping between the virtual address space
 * and the adapter's framebuffer and video RAM.
 **/
static VP_STATUS
GenFbVmpUnmapVideoMemory(
    _In_ PGENFB_DEVICE_EXTENSION DeviceExtension,
    _In_ PVIDEO_MEMORY VideoMemory,
    _Out_ PSTATUS_BLOCK StatusBlock)
{
    return VideoPortUnmapMemory(DeviceExtension,
                                VideoMemory->RequestedVirtualAddress,
                                NULL);
}


static inline
ULONG _vid_popcount(
    _In_ ULONG x)
{
#ifdef HAVE___BUILTIN_POPCOUNT
    return __popcnt(x);
#else
    x -= (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    return ((x + (x >> 4)) & 0x0f0f0f0f) * 0x01010101 >> 24;
#endif
}

static BOOLEAN
GenFbVmpSetupCurrentMode(
    _In_ PGENFB_DEVICE_EXTENSION DeviceExtension)
{
    PVIDEO_MODE_INFORMATION VideoMode = &DeviceExtension->CurrentVideoMode;
    PBOOT_FRAMEBUF_DATA FrameBufData  = &DeviceExtension->FrameBufData;
    PCM_FRAMEBUF_DEVICE_DATA VideoData  = &DeviceExtension->VideoConfigData;
    PCM_MONITOR_DEVICE_DATA MonitorData = &DeviceExtension->MonitorConfigData;
    UCHAR BytesPerPixel;

    VideoMode->Length = sizeof(VIDEO_MODE_INFORMATION);
    VideoMode->ModeIndex = 0;

    /* If the individual framebuffer screen sizes are not
     * already initialized by now, use monitor data. */
    if ((FrameBufData->ScreenWidth == 0) || (FrameBufData->ScreenHeight == 0))
    {
        FrameBufData->ScreenWidth  = VideoData->ScreenWidth;
        FrameBufData->ScreenHeight = VideoData->ScreenHeight;
    }
    // FIXME: Remove redundancies between those fields...
    if ((FrameBufData->ScreenWidth == 0) || (FrameBufData->ScreenHeight == 0))
    {
        VideoData->ScreenWidth  = MonitorData->HorizontalResolution;
        VideoData->ScreenHeight = MonitorData->VerticalResolution;

        FrameBufData->ScreenWidth  = MonitorData->HorizontalResolution;
        FrameBufData->ScreenHeight = MonitorData->VerticalResolution;
    }

    if (FrameBufData->ScreenWidth <= 1 || FrameBufData->ScreenHeight <= 1)
    {
        DPRINT1("Cannot obtain current screen resolution!\n");
        return FALSE;
    }

    VideoMode->VisScreenWidth  = FrameBufData->ScreenWidth;
    VideoMode->VisScreenHeight = FrameBufData->ScreenHeight;

    BytesPerPixel = VideoData->BitsPerPixel / 8;
    ASSERT(BytesPerPixel >= 1 && BytesPerPixel <= 4);

    /*
     * Number of bytes per scan-line ("Pitch").
     * It may be greater than ScreenWidth in case scan lines are padded to
     * an amount of memory alignment (e.g. for performance reasons, or due
     * to hardware restrictions). These padding pixels are outside of the
     * visible area.
     */
    VideoMode->ScreenStride = /*FrameBufData*/VideoData->PixelsPerScanLine * BytesPerPixel;

    VideoMode->NumberOfPlanes = 1;
    VideoMode->BitsPerPlane = VideoData->BitsPerPixel / VideoMode->NumberOfPlanes;

    /* Video frequency in Hertz */
    VideoMode->Frequency = VideoData->VideoClock;
    if (VideoMode->Frequency == 0) // or 1 ?
        VideoMode->Frequency = 60; // Default value.

    /* Use metrics from the monitor, if any */
    VideoMode->XMillimeter = MonitorData->HorizontalScreenSize;
    VideoMode->YMillimeter = MonitorData->VerticalScreenSize;
    if ((VideoMode->XMillimeter == 0) || (VideoMode->YMillimeter == 0))
    {
        /* Assume 96 DPI and 25.4 millimeters per inch, round to nearest */
        static const ULONG dpi = 96;
        // VideoMode->XMillimeter = FrameBufData->ScreenWidth  * 254 / 960;
        // VideoMode->YMillimeter = FrameBufData->ScreenHeight * 254 / 960;
        VideoMode->XMillimeter = ((ULONGLONG)FrameBufData->ScreenWidth  * 254 + (dpi * 5)) / (dpi * 10);
        VideoMode->YMillimeter = ((ULONGLONG)FrameBufData->ScreenHeight * 254 + (dpi * 5)) / (dpi * 10);
    }

    // FrameBufData->PixelFormat;
    if (VideoData->BitsPerPixel > 8) // (BytesPerPixel > 1)
    {
        if (VideoData->PixelInformation.RedMask   == 0 &&
            VideoData->PixelInformation.GreenMask == 0 &&
            VideoData->PixelInformation.BlueMask  == 0)
        {
            /* Determine pixel mask given color depth and color channel */
            switch (VideoData->BitsPerPixel)
            {
                case 32:
                case 24: /* 8:8:8 */
                    // ulMask = 0x00FF0000 >> (Channel * 8);
                    VideoMode->RedMask   = 0x00FF0000;
                    VideoMode->GreenMask = 0x0000FF00;
                    VideoMode->BlueMask  = 0x000000FF;
                    break;
                case 15: /* 5:5:5 */
                    // ulMask = 0x00007C00 >> (Channel * 5);
                    VideoMode->RedMask   = 0x00007C00;
                    VideoMode->GreenMask = 0x000003E0;
                    VideoMode->BlueMask  = 0x0000001F;
                    break;
                case 16: /* 5:6:5 */
                    VideoMode->RedMask   = 0x0000F800;
                    VideoMode->GreenMask = 0x000007E0;
                    VideoMode->BlueMask  = 0x0000001F;
                    break;
                case 8:
                case 4:
                default:
                    /* Palettized modes don't have a mask */
                    VideoMode->RedMask   = 0;
                    VideoMode->GreenMask = 0;
                    VideoMode->BlueMask  = 0;
            }
        }
        else
        {
            VideoMode->RedMask   = VideoData->PixelInformation.RedMask;
            VideoMode->GreenMask = VideoData->PixelInformation.GreenMask;
            VideoMode->BlueMask  = VideoData->PixelInformation.BlueMask;
        }

        VideoMode->NumberRedBits   = _vid_popcount(VideoMode->RedMask);
            // VideoData->PixelInformation.NumberRedBits;
        VideoMode->NumberGreenBits = _vid_popcount(VideoMode->GreenMask);
            // VideoData->PixelInformation.NumberGreenBits;
        VideoMode->NumberBlueBits  = _vid_popcount(VideoMode->BlueMask);
            // VideoData->PixelInformation.NumberBlueBits;
    }
    else
    {
        /* FIXME: not implemented */
        DPRINT1("BitsPerPixel %d not implemented\n", VideoData->BitsPerPixel);
    }

    VideoMode->VideoMemoryBitmapWidth  = VideoMode->VisScreenWidth; // ScreenStride;
    VideoMode->VideoMemoryBitmapHeight = VideoMode->VisScreenHeight;

    VideoMode->AttributeFlags =
        VIDEO_MODE_GRAPHICS | VIDEO_MODE_COLOR | VIDEO_MODE_NO_OFF_SCREEN |
        ((VideoData->BitsPerPixel <= 8) ? VIDEO_MODE_PALETTE_DRIVEN : 0);
    VideoMode->DriverSpecificAttributeFlags = 0;

    return TRUE;
}


/*********************************** Public ***********************************/

VP_STATUS
GenFbAcquireResources(
    _In_ PVOID HwDeviceExtension,
    _In_ ULONG NumAccessRanges,
    _In_ PVIDEO_ACCESS_RANGE AccessRanges)
{
    VP_STATUS status;
    ULONG i;

    /*
     * Claim the video resources if we are loaded as fall-back device.
     * Otherwise, another video driver is handling the video display
     * and claimed the resources, so we can fail loading.
     */

    /*
     * Try to acquire video resources exclusively.
     */
    for (i = 0; i < NumAccessRanges; ++i)
    {
        AccessRanges[i].RangeShareable = FALSE;
    }
    status = VideoPortVerifyAccessRanges(HwDeviceExtension,
                                         NumAccessRanges,
                                         AccessRanges);
    if (status != NO_ERROR)
    {
        /*
         * We could not obtain the resources exclusively: this means
         * another driver is handling this display. Fail to load!
         */
        return status;
    }

    /*
     * The resources have been obtained exclusively: we are the default
     * fall-back driver. Re-claim those resources in shared mode, so that
     * a PnP driver for this display can take over later, claiming those
     * resources and load successfully.
     */
    for (i = 0; i < NumAccessRanges; ++i)
    {
        AccessRanges[i].RangeShareable = TRUE;
    }
    return VideoPortVerifyAccessRanges(HwDeviceExtension,
                                       NumAccessRanges,
                                       AccessRanges);
}

/**
 * @brief
 * Callback routine for the VideoPortGetDeviceData function.
 *
 * @return
 * - NO_ERROR if the function completed properly.
 * - ERROR_DEV_NOT_EXIST if we did not find the device.
 * - ERROR_INVALID_PARAMETER otherwise.
 **/
static VP_STATUS
NTAPI
GenFbGetDeviceDataCallback(
    _In_ PVOID HwDeviceExtension,
    _In_ PVOID Context,
    _In_ VIDEO_DEVICE_DATA_TYPE DeviceDataType,
    _In_ PVOID Identifier,
    _In_ ULONG IdentifierLength,
    _In_ PVOID ConfigurationData,
    _In_ ULONG ConfigurationDataLength,
    _Inout_ PVOID ComponentInformation,
    _In_ ULONG ComponentInformationLength)
{
    PGENFB_DEVICE_EXTENSION DeviceExtension = HwDeviceExtension;
    PVIDEO_PORT_CONFIG_INFO ConfigInfo = Context;
    PWCHAR identifier = Identifier;
    PCM_COMPONENT_INFORMATION CompInfo = ComponentInformation;
    VIDEO_ACCESS_RANGE accessRanges[1];
    VP_STATUS status;

    switch (DeviceDataType)
    {
        case VpControllerData:
        {
            DPRINT1("Getting controller information: Display: '%.*ws'\n",
                    IdentifierLength/sizeof(WCHAR), identifier);

            if (!ConfigurationData ||
                (ConfigurationDataLength < sizeof(VIDEO_HARDWARE_CONFIGURATION_DATA)))
            {
                DPRINT1("Invalid display configuration data %p %lu\n",
                        ConfigurationData, ConfigurationDataLength);
                return ERROR_DEV_NOT_EXIST;
            }

            if (CompInfo && (ComponentInformationLength == sizeof(CM_COMPONENT_INFORMATION)) &&
                !(CompInfo->Flags.Output && CompInfo->Flags.ConsoleOut))
            {
                DPRINT1("Weird: this DisplayController has flags %lu\n", CompInfo->Flags);
            }

            /* Pre-initialize VideoConfigData */
            VideoPortZeroMemory(&DeviceExtension->VideoConfigData,
                                sizeof(DeviceExtension->VideoConfigData));

            /* Initialize the display adapter parameters, converting
             * them to the new format if needed */
            if (IsLegacyConfigData(ConfigurationData, ConfigurationDataLength,
                                   sizeof(VIDEO_HARDWARE_CONFIGURATION_DATA)))
            {
                /* Legacy configuration data, convert it into new format */
                CM_PARTIAL_RESOURCE_DESCRIPTOR FrameBuffer;

                DPRINT1("    GenFbVmp: Legacy Config data found\n");

                ConvertLegacyVideoConfigDataToDeviceData(
                    ConfigurationData,
                #if 0
                    &(DeviceExtension->VideoConfigData.Version),
                    &(DeviceExtension->VideoConfigData.Revision),
                #endif
                    NULL, // Interrupt
                    NULL, // ControlPort
                    NULL, // CursorPort
                    &FrameBuffer);

                /* Save the framebuffer base and size */
                DeviceExtension->FrameBufData.BaseAddress = FrameBuffer.u.Memory.Start;
                DeviceExtension->FrameBufData.BufferSize  = FrameBuffer.u.Memory.Length;

                DPRINT1("**  GenFbVmp: Legacy framebuffer address (32-bit only): 0x%x\n",
                        DeviceExtension->FrameBufData.BaseAddress);

                /* The legacy video controller configuration data does not
                 * contain any information regarding framebuffer format, etc.
                 * We will later calculate default values. */
            }
            else if (IsNewConfigData(ConfigurationData, ConfigurationDataLength))
            {
                /* New configuration data */
                PCM_FULL_RESOURCE_DESCRIPTOR cmDescriptor = ConfigurationData;
                PCM_PARTIAL_RESOURCE_DESCRIPTOR FrameBuffer, Descriptor;

                DPRINT1("    GenFbVmp: New Config data found\n");

                GetVideoData(&cmDescriptor->PartialResourceList,
                             NULL, // Interrupt
                             NULL, // ControlPort
                             NULL, // CursorPort
                             &FrameBuffer,
                             &Descriptor);

                if (FrameBuffer)
                {
                    /* Save the framebuffer base and size */
                    DeviceExtension->FrameBufData.BaseAddress = FrameBuffer->u.Memory.Start;
                    DeviceExtension->FrameBufData.BufferSize  = FrameBuffer->u.Memory.Length;

                    DPRINT1("**  GenFbVmp: Got framebuffer address: 0x%p\n",
                            DeviceExtension->FrameBufData.BaseAddress);
                }
                else
                {
                    /* No framebuffer base?! Zero it out */
                    DPRINT1("**  GenFbVmp: No framebuffer address?!\n");
                    DeviceExtension->FrameBufData.BaseAddress.QuadPart = 0;
                    DeviceExtension->FrameBufData.BufferSize = 0;
                }

                if (Descriptor &&
                    (Descriptor->u.DeviceSpecificData.DataSize >= sizeof(CM_FRAMEBUF_DEVICE_DATA)))
                {
                    /* NOTE: This descriptor *MUST* be the last one.
                     * The actual device data follows the descriptor. */
                    PCM_FRAMEBUF_DEVICE_DATA VideoData = (PCM_FRAMEBUF_DEVICE_DATA)(Descriptor + 1);
                    DeviceExtension->VideoConfigData = *VideoData;

                    DPRINT1("**  GenFbVmp: Framebuffer information data found\n");
                }
                else
                {
                    /* The configuration data does not contain any
                     * information regarding framebuffer format, etc.
                     * We will later calculate default values. */
                    DPRINT1("**  GenFbVmp: Framebuffer information data NOT FOUND\n");
                }
            }

            /* Fail if no framebuffer was provided */
            if ((DeviceExtension->FrameBufData.BaseAddress.QuadPart == 0) ||
                (DeviceExtension->FrameBufData.BufferSize == 0))
            {
                DPRINT1("No framebuffer found!\n");
                return ERROR_DEV_NOT_EXIST;
            }


            /*
             * Fill up the device extension and the configuration
             * information with the appropriate data.
             */

            DBG_UNREFERENCED_PARAMETER(ConfigInfo);
            // ConfigInfo->BusInterruptLevel  = ConfigData->Irql;
            // ConfigInfo->BusInterruptVector = ConfigData->Vector;

            /* Setup the access ranges */
            // QUESTION: Do we need to also set up the
            // ConfigData->ControlBase/Size and ConfigData->CursorBase/Size
            // memory ports, or any other resource we get,
            // besides setting up the framebuffer?
            accessRanges[0].RangeStart = DeviceExtension->FrameBufData.BaseAddress;
            accessRanges[0].RangeLength = DeviceExtension->FrameBufData.BufferSize;
            accessRanges[0].RangeInIoSpace = VIDEO_MEMORY_SPACE_MEMORY;
            accessRanges[0].RangeVisible = FALSE;
            accessRanges[0].RangeShareable = FALSE;
            accessRanges[0].RangePassive = FALSE;

            /* Try to acquire those hardware resources */
            status = GenFbAcquireResources(HwDeviceExtension,
                                           RTL_NUMBER_OF(accessRanges),
                                           accessRanges);
            if (status != NO_ERROR)
                return status;

            /* Save framebuffer information */
            // DeviceExtension->PhysicalFrameAddress = ConfigData->FrameBase;
            // DeviceExtension->FrameLength = ConfigData->FrameSize;

            // QUESTION: If set up above, should we also map the
            // video controller and cursor register?
            // DeviceExtension->VideoAddress

            /* Map the video memory into the system virtual
             * address space so we can clear it out. */
            DeviceExtension->FrameAddress =
                VideoPortGetDeviceBase(DeviceExtension,
                                       accessRanges[0].RangeStart, // Frame
                                       accessRanges[0].RangeLength,
                                       accessRanges[0].RangeInIoSpace);
            if (!DeviceExtension->FrameAddress)
            {
                /* We failed, release the acquired resources and bail out */
                VideoPortVerifyAccessRanges(HwDeviceExtension, 0, NULL);
                return ERROR_INVALID_PARAMETER;
            }

            DPRINT1("GenFbVmpFindAdapter: Mapped framebuffer 0x%I64x to 0x%p - size %lu\n",
                    accessRanges[0].RangeStart,
                    DeviceExtension->FrameAddress,
                    accessRanges[0].RangeLength);

            return NO_ERROR;
        }

        case VpMonitorData:
        {
            DPRINT1("Getting monitor information: Monitor: '%.*ws'\n",
                    IdentifierLength/sizeof(WCHAR), identifier);

            if (!ConfigurationData ||
                (ConfigurationDataLength < sizeof(MONITOR_HARDWARE_CONFIGURATION_DATA)))
            {
                DPRINT1("Invalid monitor configuration data %p %lu\n",
                        ConfigurationData, ConfigurationDataLength);
                return ERROR_DEV_NOT_EXIST;
            }

            if (CompInfo && (ComponentInformationLength == sizeof(CM_COMPONENT_INFORMATION)) &&
                !(CompInfo->Flags.Output && CompInfo->Flags.ConsoleOut))
            {
                DPRINT1("Weird: this MonitorPeripheral has flags %lu\n", CompInfo->Flags);
            }

            /* Pre-initialize MonitorConfigData */
            VideoPortZeroMemory(&DeviceExtension->MonitorConfigData,
                                sizeof(DeviceExtension->MonitorConfigData));

            /* Initialize the monitor parameters, converting
             * them to the new format if needed */
            if (IsLegacyConfigData(ConfigurationData, ConfigurationDataLength,
                                   sizeof(MONITOR_HARDWARE_CONFIGURATION_DATA)))
            {
                /* Legacy configuration data, convert it into new format */
                ConvertLegacyMonitorConfigDataToDeviceData(
                    ConfigurationData,
                    &DeviceExtension->MonitorConfigData);
            }
            else if (IsNewConfigData(ConfigurationData, ConfigurationDataLength))
            {
                /* New configuration data */
                PCM_FULL_RESOURCE_DESCRIPTOR cmDescriptor = ConfigurationData;
                PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor;

                GetMonitorData(&cmDescriptor->PartialResourceList,
                               &Descriptor);

                if (Descriptor &&
                    (Descriptor->u.DeviceSpecificData.DataSize >= sizeof(CM_MONITOR_DEVICE_DATA)))
                {
                    /* NOTE: This descriptor *MUST* be the last one.
                     * The actual device data follows the descriptor. */
                    PCM_MONITOR_DEVICE_DATA MonitorData = (PCM_MONITOR_DEVICE_DATA)(Descriptor + 1);
                    DeviceExtension->MonitorConfigData = *MonitorData;
                }
                else
                {
                    /* The configuration data does not contain any
                     * information regarding the monitor.
                     * We will later calculate default values. */
                }
            }

            return NO_ERROR;
        }

        default:
        {
            DPRINT1("Unknown device type %lu\n", DeviceDataType);
            return ERROR_INVALID_PARAMETER;
        }
    }
}

CODE_SEG("PAGE")
VP_STATUS NTAPI
GenFbVmpFindAdapter(
    _In_ PVOID HwDeviceExtension,
    _In_ PVOID HwContext,
    _In_ PWSTR ArgumentString,
    _Inout_ PVIDEO_PORT_CONFIG_INFO ConfigInfo,
    _In_ PUCHAR Again)
{
    PGENFB_DEVICE_EXTENSION DeviceExtension = HwDeviceExtension;
    PBOOT_FRAMEBUF_DATA FrameBufData = &DeviceExtension->FrameBufData;
    PCM_FRAMEBUF_DEVICE_DATA VideoData = &DeviceExtension->VideoConfigData;
    ULONG VRamInMB;

    PAGED_CODE();

    DPRINT1("GenFbVmpFindAdapter(%p, %p, %s, %p, %p)\n",
        HwDeviceExtension, HwContext, ArgumentString, ConfigInfo, Again);

    *Again = FALSE;

    if (ConfigInfo->Length < sizeof(VIDEO_PORT_CONFIG_INFO))
        return ERROR_INVALID_PARAMETER;

    // if (ConfigInfo->AdapterInterfaceType == Internal) { ... }

    /*
     * Retrieve configuration data for the boot-time display controller and monitor.
     *
     * This data is initialized by the NT bootloader and passed in the ARC tree
     * pointed by the loader block. It is available only for boot drivers and gets
     * freed later on.
     *
     * TODO: On Win8+, try first to read the BgContext structure.
     */

    VideoPortZeroMemory(FrameBufData, sizeof(*FrameBufData));

    /* Enumerate and find the boot-time console display controller */
    // ControllerClass, DisplayController
    if (VideoPortGetDeviceData(HwDeviceExtension,
                               VpControllerData,
                               GenFbGetDeviceDataCallback,
                               ConfigInfo) != NO_ERROR)
    {
        DPRINT1("GenFbVmp: getting controller info failed\n");
        return ERROR_DEV_NOT_EXIST;
    }

    /* Now find the MonitorPeripheral to obtain more information.
     * It should be child of the display controller. */
    if (VideoPortGetDeviceData(HwDeviceExtension,
                               VpMonitorData,
                               GenFbGetDeviceDataCallback,
                               ConfigInfo) != NO_ERROR)
    {
        /* Ignore if no monitor data is given */
        DPRINT1("GenFbVmp: optional monitor info not found\n");
    }

    /* From the captured video framebuffer and monitor data,
     * synthesize our single video mode information structure. */
    if (!GenFbVmpSetupCurrentMode(HwDeviceExtension))
    {
        /* We failed, release the acquired resources and bail out */
        // VideoPortFreeDeviceBase(HwDeviceExtension, ...);
        VideoPortVerifyAccessRanges(HwDeviceExtension, 0, NULL);
        return ERROR_DEV_NOT_EXIST;
    }

    /* Zero out the emulator entries since we do not support them (not VGA) */
    ConfigInfo->NumEmulatorAccessEntries = 0;
    ConfigInfo->EmulatorAccessEntries = NULL;
    ConfigInfo->EmulatorAccessEntriesContext = 0;
    ConfigInfo->VdmPhysicalVideoMemoryAddress.LowPart = 0;
    ConfigInfo->VdmPhysicalVideoMemoryAddress.HighPart = 0;
    ConfigInfo->VdmPhysicalVideoMemoryLength = 0;
    ConfigInfo->HardwareStateSize = 0;

    /*
     * For a list of possible parameters, consult
     * https://learn.microsoft.com/windows-hardware/drivers/display/setting-hardware-information-in-the-registry
     */

    /* Chipset information */
    VideoPortSetRegistryParameters(HwDeviceExtension,
                                   L"HardwareInformation.AdapterString",
                                   (PVOID)AdapterString,
                                   sizeof(AdapterString));
    // L"HardwareInformation.BiosString"
    VideoPortSetRegistryParameters(HwDeviceExtension,
                                   L"HardwareInformation.ChipType",
                                   (PVOID)AdapterChipType,
                                   sizeof(AdapterChipType));
    VideoPortSetRegistryParameters(HwDeviceExtension,
                                   L"HardwareInformation.DacType",
                                   (PVOID)AdapterDacType,
                                   sizeof(AdapterDacType));

    /* Video Memory in *MB* */
    VRamInMB = FrameBufData->BufferSize / (1024 * 1024);
    VideoPortSetRegistryParameters(HwDeviceExtension,
                                   L"HardwareInformation.MemorySize",
                                   &VRamInMB,
                                   sizeof(VRamInMB));

    /* Note: Don't use VideoMode->Frequency since that value is
     * the regularized one, and not the original reported one. */
    if (VideoData->VideoClock != 0)
    {
        ULONG VideoClock = VideoData->VideoClock;
        VideoPortSetRegistryParameters(HwDeviceExtension,
                                       L"HardwareInformation.CurrentChipClockSpeed",
                                       &VideoClock,
                                       sizeof(VideoClock));

        // Other undocumented speed indicators:
        // L"HardwareInformation.CurrentMemClockSpeed"
        // L"HardwareInformation.CurrentPixelClockSpeed"
    }

    return NO_ERROR;
}

CODE_SEG("PAGE")
BOOLEAN NTAPI
GenFbVmpInitialize(
    _In_ PVOID HwDeviceExtension)
{
    PGENFB_DEVICE_EXTENSION DeviceExtension = HwDeviceExtension;

    PAGED_CODE();

    DPRINT1("GenFbVmpInitialize(%p)\n", HwDeviceExtension);

    /* Zero the frame buffer */
    VideoPortZeroDeviceMemory(DeviceExtension->FrameAddress,
                              DeviceExtension->FrameBufData.BufferSize);

    return TRUE;
}

CODE_SEG("PAGE")
static VOID
GenFbVmpShowIOControl(ULONG IoControlCode)
{
    PAGED_CODE();

    switch (IoControlCode)
    {
    case IOCTL_VIDEO_ENABLE_VDM:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_ENABLE_VDM\n");
        break;

    case IOCTL_VIDEO_DISABLE_VDM:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_DISABLE_VDM\n");
        break;

    case IOCTL_VIDEO_REGISTER_VDM:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_REGISTER_VDM\n");
        break;

    case IOCTL_VIDEO_SET_OUTPUT_DEVICE_POWER_STATE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_OUTPUT_DEVICE_POWER_STATE\n");
        break;

    case IOCTL_VIDEO_GET_OUTPUT_DEVICE_POWER_STATE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_GET_OUTPUT_DEVICE_POWER_STATE\n");
        break;

    case IOCTL_VIDEO_MONITOR_DEVICE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_MONITOR_DEVICE\n");
        break;

    case IOCTL_VIDEO_ENUM_MONITOR_PDO:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_ENUM_MONITOR_PDO\n");
        break;

    case IOCTL_VIDEO_INIT_WIN32K_CALLBACKS:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_INIT_WIN32K_CALLBACKS\n");
        break;

    case IOCTL_VIDEO_HANDLE_VIDEOPARAMETERS:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_HANDLE_VIDEOPARAMETERS\n");
        break;

    case IOCTL_VIDEO_IS_VGA_DEVICE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_IS_VGA_DEVICE\n");
        break;

    case IOCTL_VIDEO_USE_DEVICE_IN_SESSION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_USE_DEVICE_IN_SESSION\n");
        break;

    case IOCTL_VIDEO_PREPARE_FOR_EARECOVERY:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_PREPARE_FOR_EARECOVERY\n");
        break;

    case IOCTL_VIDEO_DISABLE_CURSOR:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_DISABLE_CURSOR\n");
        break;

    case IOCTL_VIDEO_DISABLE_POINTER:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_DISABLE_POINTER\n");
        break;

    case IOCTL_VIDEO_ENABLE_CURSOR:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_ENABLE_CURSOR\n");
        break;

    case IOCTL_VIDEO_ENABLE_POINTER:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_ENABLE_POINTER\n");
        break;

    case IOCTL_VIDEO_FREE_PUBLIC_ACCESS_RANGES:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_FREE_PUBLIC_ACCESS_RANGES\n");
        break;

    case IOCTL_VIDEO_GET_BANK_SELECT_CODE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_GET_BANK_SELECT_CODE\n");
        break;

    case IOCTL_VIDEO_GET_CHILD_STATE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_GET_CHILD_STATE\n");
        break;

    case IOCTL_VIDEO_GET_POWER_MANAGEMENT:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_GET_POWER_MANAGEMENT\n");
        break;

    case IOCTL_VIDEO_LOAD_AND_SET_FONT:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_LOAD_AND_SET_FONT\n");
        break;

    case IOCTL_VIDEO_MAP_VIDEO_MEMORY:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_MAP_VIDEO_MEMORY\n");
        break;

    case IOCTL_VIDEO_QUERY_AVAIL_MODES:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_AVAIL_MODES\n");
        break;

    case IOCTL_VIDEO_QUERY_COLOR_CAPABILITIES:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_COLOR_CAPABILITIES\n");
        break;

    case IOCTL_VIDEO_QUERY_CURRENT_MODE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_CURRENT_MODE\n");
        break;

    case IOCTL_VIDEO_QUERY_CURSOR_ATTR:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_CURSOR_ATTR\n");
        break;

    case IOCTL_VIDEO_QUERY_CURSOR_POSITION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_CURSOR_POSITION\n");
        break;

    case IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES\n");
        break;

    case IOCTL_VIDEO_QUERY_POINTER_ATTR:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_POINTER_ATTR\n");
        break;

    case IOCTL_VIDEO_QUERY_POINTER_CAPABILITIES:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_POINTER_CAPABILITIES\n");
        break;

    case IOCTL_VIDEO_QUERY_POINTER_POSITION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_POINTER_POSITION\n");
        break;

    case IOCTL_VIDEO_QUERY_PUBLIC_ACCESS_RANGES:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_PUBLIC_ACCESS_RANGES\n");
        break;

    case IOCTL_VIDEO_RESET_DEVICE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_RESET_DEVICE\n");
        break;

    case IOCTL_VIDEO_RESTORE_HARDWARE_STATE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_RESTORE_HARDWARE_STATE\n");
        break;

    case IOCTL_VIDEO_SAVE_HARDWARE_STATE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SAVE_HARDWARE_STATE\n");
        break;

    case IOCTL_VIDEO_SET_CHILD_STATE_CONFIGURATION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_CHILD_STATE_CONFIGURATION\n");
        break;

    case IOCTL_VIDEO_SET_COLOR_REGISTERS:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_COLOR_REGISTERS\n");
        break;

    case IOCTL_VIDEO_SET_CURRENT_MODE:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_CURRENT_MODE\n");
        break;

    case IOCTL_VIDEO_SET_CURSOR_ATTR:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_CURSOR_ATTR\n");
        break;

    case IOCTL_VIDEO_SET_CURSOR_POSITION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_CURSOR_POSITION\n");
        break;

    case IOCTL_VIDEO_SET_PALETTE_REGISTERS:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_PALETTE_REGISTERS\n");
        break;

    case IOCTL_VIDEO_SET_POINTER_ATTR:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_POINTER_ATTR\n");
        break;

    case IOCTL_VIDEO_SET_POINTER_POSITION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_POINTER_POSITION\n");
        break;

    case IOCTL_VIDEO_SET_POWER_MANAGEMENT:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_POWER_MANAGEMENT\n");
        break;

    case IOCTL_VIDEO_SHARE_VIDEO_MEMORY:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SHARE_VIDEO_MEMORY\n");
        break;

    case IOCTL_VIDEO_SWITCH_DUALVIEW:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SWITCH_DUALVIEW\n");
        break;

    case IOCTL_VIDEO_UNMAP_VIDEO_MEMORY:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_UNMAP_VIDEO_MEMORY\n");
        break;

    case IOCTL_VIDEO_UNSHARE_VIDEO_MEMORY:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_UNSHARE_VIDEO_MEMORY\n");
        break;

    case IOCTL_VIDEO_SET_COLOR_LUT_DATA:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_COLOR_LUT_DATA\n");
        break;

    case IOCTL_VIDEO_VALIDATE_CHILD_STATE_CONFIGURATION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_VALIDATE_CHILD_STATE_CONFIGURATION\n");
        break;

    case IOCTL_VIDEO_SET_BANK_POSITION:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_BANK_POSITION\n");
        break;

    case IOCTL_VIDEO_QUERY_SUPPORTED_BRIGHTNESS:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_SUPPORTED_BRIGHTNESS\n");
        break;

    case IOCTL_VIDEO_QUERY_DISPLAY_BRIGHTNESS:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_QUERY_DISPLAY_BRIGHTNESS\n");
        break;

    case IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS:
        DPRINT1("GenFbVmpStartIO: IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS\n");
        break;

    default:
        DPRINT1("GenFbVmpStartIO: Unknown 0x%x\n", IoControlCode);
        break;
    }
}

CODE_SEG("PAGE")
BOOLEAN NTAPI
GenFbVmpStartIO(
    _In_ PVOID HwDeviceExtension,
    _Inout_ PVIDEO_REQUEST_PACKET RequestPacket)
{
    PSTATUS_BLOCK StatusBlock = RequestPacket->StatusBlock;
    VP_STATUS Status = ERROR_INVALID_PARAMETER;

    PAGED_CODE();

    GenFbVmpShowIOControl(RequestPacket->IoControlCode);

    switch (RequestPacket->IoControlCode)
    {
        case IOCTL_VIDEO_SET_CURRENT_MODE:
        {
            PVIDEO_MODE RequestedMode;
            ULONG RequestedModeNum;

            if (RequestPacket->InputBufferLength < sizeof(VIDEO_MODE))
            {
                Status = ERROR_INSUFFICIENT_BUFFER;
                break;
            }

            RequestedMode = (PVIDEO_MODE)RequestPacket->InputBuffer;
            RequestedModeNum = RequestedMode->RequestedMode &
                ~(VIDEO_MODE_NO_ZERO_MEMORY | VIDEO_MODE_MAP_MEM_LINEAR);

            /* There is nothing to do. We only support one
             * single mode and we are already in that mode. */
            if (RequestedModeNum != 0)
            {
                Status = ERROR_INVALID_PARAMETER;
                break;
            }

#if 0
            /* Zero the frame buffer */
            if (!(RequestedMode->RequestedMode & VIDEO_MODE_NO_ZERO_MEMORY))
            {
                PGENFB_DEVICE_EXTENSION DeviceExtension = HwDeviceExtension;
                VideoPortZeroDeviceMemory(DeviceExtension->FrameAddress,
                                          DeviceExtension->FrameBufData.BufferSize);
            }
#endif

            Status = NO_ERROR;
            break;
        }

        case IOCTL_VIDEO_MAP_VIDEO_MEMORY:
        {
            if (RequestPacket->OutputBufferLength < sizeof(VIDEO_MEMORY_INFORMATION) ||
                RequestPacket->InputBufferLength < sizeof(VIDEO_MEMORY))
            {
                Status = ERROR_INSUFFICIENT_BUFFER;
                break;
            }

            Status = GenFbVmpMapVideoMemory(
                        (PGENFB_DEVICE_EXTENSION)HwDeviceExtension,
                        (PVIDEO_MEMORY)RequestPacket->InputBuffer,
                        (PVIDEO_MEMORY_INFORMATION)RequestPacket->OutputBuffer,
                        StatusBlock);
            break;
        }

        case IOCTL_VIDEO_UNMAP_VIDEO_MEMORY:
        {
            if (RequestPacket->InputBufferLength < sizeof(VIDEO_MEMORY))
            {
                Status = ERROR_INSUFFICIENT_BUFFER;
                break;
            }

            Status = GenFbVmpUnmapVideoMemory(
                        (PGENFB_DEVICE_EXTENSION)HwDeviceExtension,
                        (PVIDEO_MEMORY)RequestPacket->InputBuffer,
                        StatusBlock);
            break;
        }

        case IOCTL_VIDEO_RESET_DEVICE:
        {
            /* There is nothing to be done here */
            // TODO: Maybe zero memory the framebuffer?
            Status = NO_ERROR;
            break;
        }

        case IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES:
        {
            PVIDEO_NUM_MODES Modes;

            if (RequestPacket->OutputBufferLength < sizeof(VIDEO_NUM_MODES))
            {
                Status = ERROR_INSUFFICIENT_BUFFER;
                break;
            }

            /* We only support one single mode set at boot time */
            Modes = (PVIDEO_NUM_MODES)RequestPacket->OutputBuffer;
            Modes->NumModes = 1;
            Modes->ModeInformationLength = sizeof(VIDEO_MODE_INFORMATION);
            StatusBlock->Information = sizeof(VIDEO_NUM_MODES);
            Status = NO_ERROR;
            break;
        }

        case IOCTL_VIDEO_QUERY_AVAIL_MODES:
            /* Since we support only one single mode, return
             * only that mode that is also the active one. */
        case IOCTL_VIDEO_QUERY_CURRENT_MODE:
        {
            PGENFB_DEVICE_EXTENSION DeviceExtension = (PGENFB_DEVICE_EXTENSION)HwDeviceExtension;
            PVIDEO_MODE_INFORMATION VideoMode;

            if (RequestPacket->OutputBufferLength < sizeof(VIDEO_MODE_INFORMATION))
            {
                Status = ERROR_INSUFFICIENT_BUFFER;
                break;
            }

            /* Copy back our existing current mode */
            VideoMode = (PVIDEO_MODE_INFORMATION)RequestPacket->OutputBuffer;
            VideoPortMoveMemory(VideoMode,
                                &DeviceExtension->CurrentVideoMode,
                                sizeof(VIDEO_MODE_INFORMATION));
            StatusBlock->Information = sizeof(VIDEO_MODE_INFORMATION);
            Status = NO_ERROR;
            break;
        }

        default:
        {
            DPRINT1("GenFbVmpStartIO: 0x%x not implemented\n", RequestPacket->IoControlCode);
            StatusBlock->Information = 0;
            Status = ERROR_INVALID_FUNCTION;
            break;
        }
    }

    StatusBlock->Status = Status;
    return TRUE;
}

CODE_SEG("PAGE")
VP_STATUS NTAPI
GenFbVmpSetPowerState(
    _In_ PVOID HwDeviceExtension,
    _In_ ULONG HwId,
    _In_ PVIDEO_POWER_MANAGEMENT VideoPowerControl)
{
    PAGED_CODE();

    /* Unused */
    __debugbreak();
    return ERROR_INVALID_FUNCTION; // NO_ERROR;
}

CODE_SEG("PAGE")
VP_STATUS NTAPI
GenFbVmpGetPowerState(
    _In_ PVOID HwDeviceExtension,
    _In_ ULONG HwId,
    _Out_ PVIDEO_POWER_MANAGEMENT VideoPowerControl)
{
    PAGED_CODE();

    /* Unused */
    __debugbreak();
    return ERROR_INVALID_FUNCTION; // NO_ERROR;
}

CODE_SEG("PAGE")
VP_STATUS NTAPI
GenFbVmpGetVideoChildDescriptor(
    _In_ PVOID HwDeviceExtension,
    _In_ PVIDEO_CHILD_ENUM_INFO ChildEnumInfo,
    _Out_ PVIDEO_CHILD_TYPE VideoChildType,
    _Out_ PUCHAR pChildDescriptor,
    _Out_ PULONG UId,
    _Out_ PULONG pUnused)
{
    PAGED_CODE();

    /* Unused */
    DPRINT1("GenFbVmpGetVideoChildDescriptor(%p)\n", HwDeviceExtension);
    __debugbreak();
    return NO_ERROR; // FIXME: Should return VIDEO_ENUM_NO_MORE_DEVICES;
}

CODE_SEG("INIT")
ULONG NTAPI
DriverEntry(
    _In_ PVOID Context1,
    _In_ PVOID Context2)
{
    VIDEO_HW_INITIALIZATION_DATA VideoInitData;
    ULONG Status;

    VideoDebugPrint((Info, "GenFbVmp: DriverEntry\n"));
    __debugbreak();

    VideoPortZeroMemory(&VideoInitData, sizeof(VideoInitData));
    VideoInitData.HwInitDataSize = sizeof(VideoInitData);
    VideoInitData.HwFindAdapter = GenFbVmpFindAdapter;
    VideoInitData.HwInitialize = GenFbVmpInitialize;
    // VideoInitData.HwInterrupt = NULL;
    VideoInitData.HwStartIO = GenFbVmpStartIO;
    VideoInitData.HwDeviceExtensionSize = sizeof(GENFB_DEVICE_EXTENSION);
    // VideoInitData.HwResetHw = NULL;
    // VideoInitData.HwTimer = NULL;
    // VideoInitData.HwStartDma = NULL;

#if 0
// FIXME: For now, keep the miniport as non-PnP
    VideoInitData.HwSetPowerState = GenFbVmpSetPowerState;
    VideoInitData.HwGetPowerState = GenFbVmpGetPowerState;
    VideoInitData.HwGetVideoChildDescriptor = GenFbVmpGetVideoChildDescriptor;
#endif

    // VideoInitData.HwQueryInterface = NULL;
    // VideoInitData.HwChildDeviceExtensionSize = 0;
    // VideoInitData.HwLegacyResourceList  = NULL;
    // VideoInitData.HwLegacyResourceCount = 0;
    // VideoInitData.HwGetLegacyResources  = NULL
    // VideoInitData.AllowEarlyEnumeration = FALSE;


    /* Start with parameters for Device0 */
    VideoInitData.StartingDeviceNumber = 0;

    /*
     * Our main purpose is to find the *only* boot-time framebuffer
     * display controller available on the system, so don't declare
     * ourselves as PnP (yet? should we?). Instead look at specific
     * buses and enumerate the internal ARC device tree set up by
     * the bootloader.
     */

    {
    INTERFACE_TYPE Types[] = {PCIBus, Internal, Isa, Eisa, MicroChannel /*, TurboChannel*/};
    ULONG i;

    // QUESTION: Loop from interface type == 0 to MaximumInterfaceType ??
    // for (Type = 0; Type < MaximumInterfaceType; Type++)
    // { }

    for (i = 0; i < RTL_NUMBER_OF(Types); ++i)
    {
        VideoInitData.AdapterInterfaceType = Types[i];
        Status = VideoPortInitialize(Context1, Context2, &VideoInitData, NULL);
        if (Status == STATUS_SUCCESS)
            break;
    }
    }

    return Status;
}
