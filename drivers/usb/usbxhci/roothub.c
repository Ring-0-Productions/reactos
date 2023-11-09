/*
 * PROJECT:     ReactOS USB xHCI Miniport Driver
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     USBXHCI root hub functions
 * COPYRIGHT:   Copyright 2023 Ian Marco Moffett <ian@osmora.org>
 */

#include "usbxhci.h"

//m#define NDEBUG
#include <debug.h>

/**
 * Sets port power state.
 *
 * @XhciExtension: xHCI Extension structure
 * @Port: Port to set state of
 * @State: State (1: power on, 0: power off)
 */
MPSTATUS
NTAPI
XHCI_RH_SetPortPower(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port,
    _In_ UCHAR State)
{
    PXHCI_EXTENSION XhciExt = XhciExtension;
    PXHCI_PORTSC PortScPtr;
    XHCI_PORTSC PortSc;
    UCHAR PowerOnAttempts = 0;

    /*
     * If the host controller does not implement
     * port power switching then the port should
     * be, by default, powered on, meaning we don't
     * have to do anything here...
     */
    if (XhciExt->HasPPC == 0)
    {
        return MP_STATUS_SUCCESS;
    }

    State &= 1;

    XHCI_ASSERT_PORT_VALID(Port, XhciExtension);
    PortScPtr = XHCI_GET_PORTSC(Port, XhciExtension);

    PortSc.AsULONG = READ_REGISTER_ULONG(&PortScPtr->AsULONG);
    PortSc.PortPower = State;
    WRITE_REGISTER_ULONG(&PortScPtr->AsULONG, PortSc.AsULONG);

    /* Ensure PortPower reached desired state */
    do
    {
        PortSc.AsULONG = READ_REGISTER_ULONG(&PortScPtr->AsULONG);
        ++PowerOnAttempts;

        if (PortSc.PortPower == State)
        {
            return MP_STATUS_SUCCESS;
        }

        /* Did all attempts fail? */
        if (PowerOnAttempts == 3)
        {
            DPRINT1("XHCI_InitPorts: Could not power on port %d\n", Port);
            return MP_STATUS_FAILURE;
        }
    } while (1);

    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ChirpRootPort(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_ChirpRootPort: Port - %x\n", Port);
    XHCI_ASSERT_PORT_VALID(Port, XhciExtension);

    return MP_STATUS_SUCCESS;
}

VOID
NTAPI
XHCI_RH_GetRootHubData(
    _In_ PVOID XhciExtension,
    _In_ PVOID RootHubData)
{
    PUSBPORT_ROOT_HUB_DATA RH_Data;
    PXHCI_EXTENSION XhciExt;

    RH_Data = RootHubData;
    RtlZeroMemory(RH_Data, sizeof(*RH_Data));

    XhciExt = XhciExtension;
    RH_Data->NumberOfPorts = XhciExt->NumberOfPorts;
}

MPSTATUS
NTAPI
XHCI_RH_GetStatus(
    _In_ PVOID XhciExtension,
    _Out_ PUSHORT Status)
{
    DPRINT("XHCI_RH_GetStatus: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_GetPortStatus(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port,
    _Out_ PUSB_PORT_STATUS_AND_CHANGE PortStatus)
{
    DPRINT("XHCI_RH_GetPortStatus: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_GetHubStatus(
    _In_ PVOID XhciExtension,
    _Out_ PUSB_HUB_STATUS_AND_CHANGE HubStatus)
{
    DPRINT("XHCI_RH_GetHubStatus: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortReset(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_SetFeaturePortReset: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortPower(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    return XHCI_RH_SetPortPower(XhciExtension, Port, 1);
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortEnable(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_SetFeaturePortEnable: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortSuspend(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_SetFeaturePortSuspend: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortPower(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    return XHCI_RH_SetPortPower(XhciExtension, Port, 0);
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspend(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_ClearFeaturePortSuspend: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnable(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnableChange(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_ClearFeaturePortEnableChange: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortConnectChange(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_ClearFeaturePortConnectChange: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortResetChange(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_ClearFeaturePortResetChange: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspendChange(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_ClearFeaturePortSuspend: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortOvercurrentChange(
    _In_ PVOID XhciExtension,
    _In_ USHORT Port)
{
    DPRINT("XHCI_RH_ClearFeaturePortOvercurrentChange: UNIMPLEMENTED. FIXME\n");
    return MP_STATUS_SUCCESS;
}

VOID
NTAPI
XHCI_RH_DisableIrq(_In_ PVOID XhciExtension)
{
    DPRINT("XHCI_RH_DisableIrq: UNIMPLEMENTED. FIXME\n");
}

VOID
NTAPI
XHCI_RH_EnableIrq(_In_ PVOID XhciExtension)
{
    DPRINT("XHCI_RH_EnableIrq: UNIMPLEMENTED. FIXME\n");
}
