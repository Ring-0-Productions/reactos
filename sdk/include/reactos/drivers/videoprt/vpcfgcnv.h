/*
 * PROJECT:     ReactOS Video Port Driver
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Conversion helpers between legacy and newer
 *              video/monitor configuration data structures.
 * COPYRIGHT:   Copyright 2023 Hermès Bélusca-Maïto <hermes.belusca-maito@reactos.org>
 */

/**
 * @defgroup VpCfgConv  ReactOS Video Port Configuration Data Conversion Helpers
 *
 * @brief
 * Conversion helpers between legacy video/monitor configuration data
 * structures, and newer ones compatible with CM_PARTIAL_RESOURCE_LIST
 * resource descriptors.
 *
 * RATIONALE:
 *
 * The legacy, MIPS-derived, video display controller and monitor
 * peripheral configuration data is specified, respectively, with
 * the VIDEO_HARDWARE_CONFIGURATION_DATA (see DDK video.h, with
 * data starting at the 'Version' field and following) and the
 * MONITOR_CONFIGURATION_DATA structures (see arc.h), both with
 * Version == 0 or 1, Revision == 0, as set by the NT OS loader.
 * They are compatible with the ARC Specification Revision 1.00.
 *
 * The newer way to specify configuration data, compatible with
 * the ARC Specification Revision 1.2, is to use a CM_PARTIAL_RESOURCE_LIST
 * with one or more CM_PARTIAL_RESOURCE_DESCRIPTOR's for enumerating
 * standard resources (Interrupts, I/O ports, Memory...) as well
 * as free-form device-specific information data.
 *
 * For video display controllers, all the legacy data can be
 * described by a set of standard CM_PARTIAL_RESOURCE_DESCRIPTOR's:
 * - The Irql/Vector interrupt settings are now provided with
 *   a CmResourceTypeInterrupt descriptor.
 * - Both ControlBase/Size and CursorBase/Size memory I/O ports
 *   are provided with successive CmResourceTypePort descriptors,
 *   *respectively in this order*.
 * - The framebuffer's FrameBase/Size is provided, in a 64-bit
 *   compatible way, with a CmResourceTypeMemory descriptor.
 *
 * Any other extended video controller-specific data, that would
 * have been described with a vendor-specific extended version of
 * the VIDEO_HARDWARE_CONFIGURATION_DATA structure, can now be
 * specified with a CmResourceTypeDeviceSpecific descriptor appended
 * to the CM_PARTIAL_RESOURCE_LIST.
 * For example, in ReactOS, extended framebuffer format of the
 * boot console may be specified with the ReactOS-specific
 * CM_FRAMEBUF_DEVICE_DATA structure (see framebuf.h).
 *
 * For monitor peripherals, all the legacy data is extended by
 * the CM_MONITOR_DEVICE_DATA structure (see DDK ntddk.h or wdm.h),
 * to be specified with a CmResourceTypeDeviceSpecific descriptor.
 *
 * The ReactOS loader specifies this configuration data in the
 * new format. In order to ensure backward compatibility with
 * _legacy_ Windows video miniports that could use this data
 * (typically NT <= 4 or 5, mostly for MIPS machines but also
 * few x86 ones), and for interoperability of our code with the
 * Windows NT loader, we define a set of conversion functions
 * that can translate between legacy (ARC Rev.1.00) and newer
 * (ARC Rev.1.2) configuration data structures.
 **/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * Data returned with VpMonitorData.
 *
 * This structure describes the legacy ARC Rev.1.00 monitor peripheral
 * configuration data, as stored in the \Registry\Machine\Hardware\Description
 * configuration tree and reported by VideoPortGetDeviceData().
 *
 * It has a similar layout as the display controller DDK video.h
 * VIDEO_HARDWARE_CONFIGURATION_DATA structure, where:
 * - The first two fields, InterfaceType and BusNumber, are
 *   common with the CM_FULL_RESOURCE_DESCRIPTOR header;
 * - The Version and Revision fields correspond to the first
 *   two fields of CM_PARTIAL_RESOURCE_LIST;
 * - The other fields are of legacy layout.
 **/
#include <pshpack1.h>
typedef struct _MONITOR_HARDWARE_CONFIGURATION_DATA
{
    INTERFACE_TYPE InterfaceType;
    ULONG BusNumber;
    MONITOR_CONFIGURATION_DATA;
} MONITOR_HARDWARE_CONFIGURATION_DATA, *PMONITOR_HARDWARE_CONFIGURATION_DATA;
#include <poppack.h>


FORCEINLINE
BOOLEAN
IsLegacyConfigData(
    _In_ PVOID ConfigurationData,
    _In_ ULONG ConfigurationDataLength,
    _In_ ULONG ExpectedConfigurationDataLength)
{
    PCM_PARTIAL_RESOURCE_LIST ResourceList;

    if (!ConfigurationData)
        return FALSE;

    /*
     * A valid legacy configuration data covers:
     * - The first two fields, InterfaceType and BusNumber,
     *   of the CM_FULL_RESOURCE_DESCRIPTOR header;
     * - The first two fields, Version and Revision,
     *   of CM_PARTIAL_RESOURCE_LIST.
     */
    if ((ConfigurationDataLength < FIELD_OFFSET(CM_FULL_RESOURCE_DESCRIPTOR,
                                                PartialResourceList.Count)) ||
        (ConfigurationDataLength != ExpectedConfigurationDataLength))
    {
        return FALSE;
    }

    /* Cast to PCM_PARTIAL_RESOURCE_LIST to access
     * the common Version and Revision fields. */
    ResourceList = &((PCM_FULL_RESOURCE_DESCRIPTOR)ConfigurationData)->PartialResourceList;

    /* If Version/Revision is larger or equal to 1.2,
     * this cannot be a legacy configuration data */
    if ( (ResourceList->Version >  1) ||
        ((ResourceList->Version == 1) && (ResourceList->Revision > 1)) )
    {
        return FALSE;
    }

    return TRUE;
}

FORCEINLINE
BOOLEAN
IsNewConfigData(
    _In_ PVOID ConfigurationData,
    _In_ ULONG ConfigurationDataLength)
{
    PCM_PARTIAL_RESOURCE_LIST ResourceList;

    if (!ConfigurationData)
        return FALSE;

#if 0
    if (ConfigurationDataLength < sizeof(CM_FULL_RESOURCE_DESCRIPTOR) -
                                  sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR))
#else
    if (ConfigurationDataLength < FIELD_OFFSET(CM_FULL_RESOURCE_DESCRIPTOR,
                                               PartialResourceList.PartialDescriptors))
#endif
    {
        return FALSE;
    }

    /* Cast to PCM_PARTIAL_RESOURCE_LIST to access
     * the common Version and Revision fields. */
    ResourceList = &((PCM_FULL_RESOURCE_DESCRIPTOR)ConfigurationData)->PartialResourceList;

    /* If Version/Revision is strictly lower than 1.2, this cannot be
     * a new configuration data (even if the length appears to match
     * a CM_FULL_RESOURCE_DESCRIPTOR with zero or more descriptors). */
    if ( (ResourceList->Version <  1) ||
        ((ResourceList->Version == 1) && (ResourceList->Revision <= 1)) )
    {
        return FALSE;
    }

    /* This should be a new configuration data */
    return TRUE;
}


/**
 * @brief
 * Given a CM_PARTIAL_RESOURCE_LIST, obtain pointers to resource descriptors
 * for legacy video configuration: interrupt, control and cursor I/O ports,
 * and framebuffer memory descriptors.  In addition, retrieve any
 * device-specific resource present.
 **/
FORCEINLINE
VOID
GetVideoData(
    _In_ PCM_PARTIAL_RESOURCE_LIST ResourceList,
    _Out_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR* Interrupt,
    _Out_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR* ControlPort,
    _Out_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR* CursorPort,
    _Out_ PCM_PARTIAL_RESOURCE_DESCRIPTOR* FrameBuffer,
    _Out_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR* DeviceSpecific)
{
    PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor;
    ULONG PortCount = 0, IntCount = 0, MemCount = 0;
    ULONG i;

    /* Initialize the return values */
    if (Interrupt)   *Interrupt   = NULL;
    if (ControlPort) *ControlPort = NULL;
    if (CursorPort)  *CursorPort  = NULL;
    *FrameBuffer = NULL;
    if (DeviceSpecific) *DeviceSpecific = NULL;

    for (i = 0; i < ResourceList->Count; ++i)
    {
        Descriptor = &ResourceList->PartialDescriptors[i];

        switch (Descriptor->Type)
        {
            case CmResourceTypePort:
            {
                /* We only check for memory I/O ports */
                // if (!(Descriptor->Flags & CM_RESOURCE_PORT_MEMORY))
                if (Descriptor->Flags & CM_RESOURCE_PORT_IO)
                    break;

                /* If more than two memory I/O ports
                 * have been encountered, ignore them */
                if (PortCount > 2)
                    break;
                ++PortCount;

                /* First port is Control; Second port is Cursor */
                if (PortCount == 1)
                {
                    // Descriptor->u.Port;
                    if (ControlPort)
                        *ControlPort = Descriptor;
                }
                else // if (PortCount == 2)
                {
                    // Descriptor->u.Port;
                    if (CursorPort)
                        *CursorPort = Descriptor;
                }
                break;
            }

            case CmResourceTypeInterrupt:
            {
                /* If more than one interrupt resource
                 * has been encountered, ignore them */
                if (IntCount > 1)
                    break;
                ++IntCount;

                // Descriptor->u.Interrupt;
                if (Interrupt)
                    *Interrupt = Descriptor;
                break;
            }

            case CmResourceTypeMemory:
            {
                /* If more than one memory resource
                 * has been encountered, ignore them */
                if (MemCount > 1)
                    break;
                ++MemCount;

                // or CM_RESOURCE_MEMORY_WRITE_ONLY ??
                // if (!(Descriptor->Flags & CM_RESOURCE_MEMORY_READ_WRITE))
                // {
                //     /* Cannot use this framebuffer */
                //     break;
                // }

                // Descriptor->u.Memory;
                *FrameBuffer = Descriptor;
                break;
            }

            case CmResourceTypeDeviceSpecific:
            {
                /* NOTE: This descriptor *MUST* be the last one.
                 * The actual device data follows the descriptor. */
                ASSERT(i == ResourceList->Count - 1);
                i = ResourceList->Count; // To force-break the for-loop.

                if (DeviceSpecific)
                    *DeviceSpecific = Descriptor;
                break;
            }
        }
    }
}

static inline
VOID
DoConvertVideoDataToLegacyConfigData(
    _Inout_ PVIDEO_HARDWARE_CONFIGURATION_DATA configData,
    _In_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR Interrupt,
    _In_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR ControlPort,
    _In_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR CursorPort,
    _In_ PCM_PARTIAL_RESOURCE_DESCRIPTOR FrameBuffer)
{
    if (Interrupt)
    {
        if ((Interrupt->u.Interrupt.Level & 0xFFFF0000) != 0)
        {
            DPRINT1("WARNING: Interrupt Level %lu truncated to 16 bits!\n",
                    Interrupt->u.Interrupt.Level);
        }
        configData->Irql   = (USHORT)Interrupt->u.Interrupt.Level;
        configData->Vector = Interrupt->u.Interrupt.Vector;
    }

    if (ControlPort)
    {
        if (ControlPort->u.Port.Start.HighPart != 0)
        {
            DPRINT1("WARNING: Port %I64u truncated to 32 bits!\n",
                    ControlPort->u.Port.Start.QuadPart);
        }
        configData->ControlBase = ControlPort->u.Port.Start.LowPart;
        configData->ControlSize = ControlPort->u.Port.Length;
    }

    if (CursorPort)
    {
        if (CursorPort->u.Port.Start.HighPart != 0)
        {
            DPRINT1("WARNING: Port %I64u truncated to 32 bits!\n",
                    CursorPort->u.Port.Start.QuadPart);
        }
        configData->CursorBase = CursorPort->u.Port.Start.LowPart;
        configData->CursorSize = CursorPort->u.Port.Length;
    }

    if (FrameBuffer)
    {
        if (FrameBuffer->u.Memory.Start.HighPart != 0)
        {
            DPRINT1("WARNING: Memory %I64u truncated to 32 bits!\n",
                    FrameBuffer->u.Memory.Start.QuadPart);
        }
        configData->FrameBase = FrameBuffer->u.Memory.Start.LowPart;
        configData->FrameSize = FrameBuffer->u.Memory.Length;
    }
}

/**
 * @brief
 * Convert video resource descriptor data into legacy video configuration.
 **/
FORCEINLINE
VOID
ConvertVideoDataToLegacyConfigData(
    _Inout_ PVIDEO_HARDWARE_CONFIGURATION_DATA configData,
    _In_ PCM_FULL_RESOURCE_DESCRIPTOR cmDescriptor)
{
    PCM_PARTIAL_RESOURCE_LIST ResourceList = &cmDescriptor->PartialResourceList;

    PCM_PARTIAL_RESOURCE_DESCRIPTOR Interrupt;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR ControlPort;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR CursorPort;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR FrameBuffer;

    configData->InterfaceType = cmDescriptor->InterfaceType;
    configData->BusNumber     = cmDescriptor->BusNumber;

    /* The legacy configuration data is from ARC Specification Revision 1.00 */
    configData->Version  = 1; // ResourceList->Version;
    configData->Revision = 0; // ResourceList->Revision;

    GetVideoData(ResourceList,
                 &Interrupt,
                 &ControlPort,
                 &CursorPort,
                 &FrameBuffer,
                 NULL);

    DoConvertVideoDataToLegacyConfigData(configData,
                                         Interrupt,
                                         ControlPort,
                                         CursorPort,
                                         FrameBuffer);
}

/**
 * @brief
 * Convert legacy video configuration data into video resource descriptor.
 **/
FORCEINLINE
VOID
ConvertLegacyVideoConfigDataToDeviceData(
    _In_ PVIDEO_HARDWARE_CONFIGURATION_DATA configData,
#if 0
    _Out_opt_ PUSHORT Version,
    _Out_opt_ PUSHORT Revision,
#endif
    _Out_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR Interrupt,
    _Out_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR ControlPort,
    _Out_opt_ PCM_PARTIAL_RESOURCE_DESCRIPTOR CursorPort,
    _Out_ PCM_PARTIAL_RESOURCE_DESCRIPTOR FrameBuffer)
{
    // cmDescriptor->InterfaceType = configData->InterfaceType;
    // cmDescriptor->BusNumber     = configData->BusNumber;

#if 0
    /* The new configuration data is from ARC Specification Revision 1.2 */
    if (Version)  *Version  = 1; // configData->Version;
    if (Revision) *Revision = 2; // configData->Revision;
#endif

    if (Interrupt)
    {
        Interrupt->Type = CmResourceTypeInterrupt;

        Interrupt->u.Interrupt.Level  = configData->Irql;
        Interrupt->u.Interrupt.Vector = configData->Vector;
    }

    if (ControlPort)
    {
        ControlPort->Type = CmResourceTypePort;

        /* We only check for memory I/O ports */
        ControlPort->Flags &= ~CM_RESOURCE_PORT_IO;
        ControlPort->Flags |= CM_RESOURCE_PORT_MEMORY;

        ControlPort->u.Port.Start.HighPart = 0;
        ControlPort->u.Port.Start.LowPart  = configData->ControlBase;
        ControlPort->u.Port.Length = configData->ControlSize;
    }

    if (CursorPort)
    {
        CursorPort->Type = CmResourceTypePort;

        /* We only check for memory I/O ports */
        CursorPort->Flags &= ~CM_RESOURCE_PORT_IO;
        CursorPort->Flags |= CM_RESOURCE_PORT_MEMORY;

        CursorPort->u.Port.Start.HighPart = 0;
        CursorPort->u.Port.Start.LowPart  = configData->CursorBase;
        CursorPort->u.Port.Length = configData->CursorSize;
    }

    FrameBuffer->Type = CmResourceTypeMemory;

    // FrameBuffer->Flags |= CM_RESOURCE_MEMORY_READ_WRITE;
    // or CM_RESOURCE_MEMORY_WRITE_ONLY ??

    FrameBuffer->u.Memory.Start.HighPart = 0;
    FrameBuffer->u.Memory.Start.LowPart  = configData->FrameBase;
    FrameBuffer->u.Memory.Length = configData->FrameSize;
}


/**
 * @brief
 * Given a CM_PARTIAL_RESOURCE_LIST, obtain a pointer to resource descriptor
 * for monitor configuration data, listed as a device-specific resource.
 **/
FORCEINLINE
VOID
GetMonitorData(
    _In_ PCM_PARTIAL_RESOURCE_LIST ResourceList,
    _Out_ PCM_PARTIAL_RESOURCE_DESCRIPTOR* DeviceSpecific)
{
    PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor;
    ULONG i;

    /* Initialize the return values */
    *DeviceSpecific = NULL;

    /* Find the CmResourceTypeDeviceSpecific CM_MONITOR_DEVICE_DATA */
    for (i = 0; i < ResourceList->Count; ++i)
    {
        Descriptor = &ResourceList->PartialDescriptors[i];
        if (Descriptor->Type == CmResourceTypeDeviceSpecific)
        {
            /* NOTE: This descriptor *MUST* be the last one.
             * The actual device data follows the descriptor. */
            // PCM_MONITOR_DEVICE_DATA MonitorData = (PCM_MONITOR_DEVICE_DATA)(Descriptor + 1);

            ASSERT(i == ResourceList->Count - 1);

            if (DeviceSpecific)
                *DeviceSpecific = Descriptor;
            break; // Exit the for-loop.
        }
    }
}

static inline
VOID
DoConvertMonitorDataToLegacyConfigData(
    _Inout_ PMONITOR_HARDWARE_CONFIGURATION_DATA configData,
    _In_ PCM_MONITOR_DEVICE_DATA MonitorData)
{
    configData->HorizontalResolution = MonitorData->HorizontalResolution;
    if (MonitorData->HorizontalDisplayTimeHigh != 0)
    {
        DPRINT1("WARNING: Monitor HorizontalDisplayTime truncated to 16 bits!\n");
        configData->HorizontalDisplayTime = MonitorData->HorizontalDisplayTimeLow;
    }
    else
    {
        configData->HorizontalDisplayTime = MonitorData->HorizontalDisplayTime;
    }
    if (MonitorData->HorizontalBackPorchHigh != 0)
    {
        DPRINT1("WARNING: Monitor HorizontalBackPorch truncated to 16 bits!\n");
        configData->HorizontalBackPorch = MonitorData->HorizontalBackPorchLow;
    }
    else
    {
        configData->HorizontalBackPorch = MonitorData->HorizontalBackPorch;
    }
    if (MonitorData->HorizontalFrontPorchHigh != 0)
    {
        DPRINT1("WARNING: Monitor HorizontalFrontPorch truncated to 16 bits!\n");
        configData->HorizontalFrontPorch = MonitorData->HorizontalFrontPorchLow;
    }
    else
    {
        configData->HorizontalFrontPorch = MonitorData->HorizontalFrontPorch;
    }
    if (MonitorData->HorizontalSyncHigh != 0)
    {
        DPRINT1("WARNING: Monitor HorizontalSync truncated to 16 bits!\n");
        configData->HorizontalSync = MonitorData->HorizontalSyncLow;
    }
    else
    {
        configData->HorizontalSync = MonitorData->HorizontalSync;
    }

    configData->VerticalResolution = MonitorData->VerticalResolution;
    if (MonitorData->VerticalBackPorchHigh != 0)
    {
        DPRINT1("WARNING: Monitor VerticalBackPorch truncated to 16 bits!\n");
        configData->VerticalBackPorch = MonitorData->VerticalBackPorchLow;
    }
    else
    {
        configData->VerticalBackPorch = MonitorData->VerticalBackPorch;
    }
    if (MonitorData->VerticalFrontPorchHigh != 0)
    {
        DPRINT1("WARNING: Monitor VerticalFrontPorch truncated to 16 bits!\n");
        configData->VerticalFrontPorch = MonitorData->VerticalFrontPorchLow;
    }
    else
    {
        configData->VerticalFrontPorch = MonitorData->VerticalFrontPorch;
    }
    if (MonitorData->VerticalSyncHigh != 0)
    {
        DPRINT1("WARNING: Monitor VerticalSync truncated to 16 bits!\n");
        configData->VerticalSync = MonitorData->VerticalSyncLow;
    }
    else
    {
        configData->VerticalSync = MonitorData->VerticalSync;
    }

    configData->HorizontalScreenSize = MonitorData->HorizontalScreenSize;
    configData->VerticalScreenSize = MonitorData->VerticalScreenSize;
}

/**
 * @brief
 * Convert monitor resource descriptor data into legacy monitor configuration.
 **/
FORCEINLINE
VOID
ConvertMonitorDataToLegacyConfigData(
    _Inout_ PMONITOR_HARDWARE_CONFIGURATION_DATA configData,
    _In_ PCM_FULL_RESOURCE_DESCRIPTOR cmDescriptor)
{
    PCM_PARTIAL_RESOURCE_LIST ResourceList = &cmDescriptor->PartialResourceList;

    PCM_PARTIAL_RESOURCE_DESCRIPTOR Descriptor;

    configData->InterfaceType = cmDescriptor->InterfaceType;
    configData->BusNumber     = cmDescriptor->BusNumber;

    /* The legacy configuration data is from ARC Specification Revision 1.00 */
    configData->Version  = 1; // ResourceList->Version;
    configData->Revision = 0; // ResourceList->Revision;

    GetMonitorData(ResourceList, &Descriptor);

    if (Descriptor)
    {
        /* NOTE: This descriptor *MUST* be the last one.
         * The actual device data follows the descriptor. */
        PCM_MONITOR_DEVICE_DATA MonitorData = (PCM_MONITOR_DEVICE_DATA)(Descriptor + 1);
        DoConvertMonitorDataToLegacyConfigData(configData, MonitorData);
    }
}

/**
 * @brief
 * Convert legacy monitor configuration data into monitor resource descriptor.
 **/
FORCEINLINE
VOID
ConvertLegacyMonitorConfigDataToDeviceData(
    _In_ PMONITOR_HARDWARE_CONFIGURATION_DATA configData,
    _Out_ PCM_MONITOR_DEVICE_DATA MonitorData)
{
    // cmDescriptor->InterfaceType = configData->InterfaceType;
    // cmDescriptor->BusNumber     = configData->BusNumber;

#if 0
    /* The new configuration data is from ARC Specification Revision 1.2 */
    MonitorData->Version  = 1; // configData->Version;
    MonitorData->Revision = 2; // configData->Revision;
#else
    MonitorData->Version  = 0;
    MonitorData->Revision = 0;
#endif

    MonitorData->HorizontalScreenSize = configData->HorizontalScreenSize;
    MonitorData->VerticalScreenSize   = configData->VerticalScreenSize;
    MonitorData->HorizontalResolution = configData->HorizontalResolution;
    MonitorData->VerticalResolution   = configData->VerticalResolution;

    MonitorData->HorizontalDisplayTimeLow  = 0;
    MonitorData->HorizontalDisplayTime     = configData->HorizontalDisplayTime;
    MonitorData->HorizontalDisplayTimeHigh = 0;

    MonitorData->HorizontalBackPorchLow  = 0;
    MonitorData->HorizontalBackPorch     = configData->HorizontalBackPorch;
    MonitorData->HorizontalBackPorchHigh = 0;

    MonitorData->HorizontalFrontPorchLow  = 0;
    MonitorData->HorizontalFrontPorch     = configData->HorizontalFrontPorch;
    MonitorData->HorizontalFrontPorchHigh = 0;

    MonitorData->HorizontalSyncLow  = 0;
    MonitorData->HorizontalSync     = configData->HorizontalSync;
    MonitorData->HorizontalSyncHigh = 0;

    MonitorData->VerticalBackPorchLow  = 0;
    MonitorData->VerticalBackPorch     = configData->VerticalBackPorch;
    MonitorData->VerticalBackPorchHigh = 0;

    MonitorData->VerticalFrontPorchLow  = 0;
    MonitorData->VerticalFrontPorch     = configData->VerticalFrontPorch;
    MonitorData->VerticalFrontPorchHigh = 0;

    MonitorData->VerticalSyncLow  = 0;
    MonitorData->VerticalSync     = configData->VerticalSync;
    MonitorData->VerticalSyncHigh = 0;
}

#ifdef __cplusplus
}
#endif

/* EOF */
