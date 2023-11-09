/*
 * PROJECT:     ReactOS USB XHCI Miniport Driver
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     USBXHCI declarations
 * COPYRIGHT:   Copyright 2023 Ian Marco Moffett <ian@osmora.org>
 */

#pragma once

/* Max command ring entries */
#define XHCI_COMMAND_RING_MAX 128

#include <ntddk.h>
#include <windef.h>
#include <hubbusif.h>
#include <drivers/usbport/usbmport.h>
#include "hardware.h"

/*
 * Do not use this directly!!! Use XHCI_GET_PORTSC()
 * instead.
 *
 * The spec states that the address of port status
 * and control (which can be many as many ports exist)
 * is Operational Base + (400h + (10h * (n–1)))
 * where: n = Port Number (Valid values are 1, 2, 3, ...MaxPorts
 */
#define XHCI_PORTSC(OperationalBase, PortNo) \
    (PVOID)((ULONG_PTR)OperationalBase + (0x400 + (0x10 * (PortNo - 1))))

/*
 * Ensures a port number is valid.
 */
#define XHCI_ASSERT_PORT_VALID(Portno, XhciExt)                             \
    NT_ASSERTMSG("Invalid port number of '0'", Portno != 0);                \
    NT_ASSERTMSG("Port number too high!",                                   \
                 Portno <= ((PXHCI_EXTENSION)XhciExt)->NumberOfPorts);      \

/*
 * Fetches port status and control.
 * XhciExt must be of type PXHCI_EXTENSION.
 */
#define XHCI_GET_PORTSC(Portno, XhciExt) \
    XHCI_PORTSC(((PXHCI_EXTENSION)XhciExt)->OperRegs, Portno)

extern USBPORT_REGISTRATION_PACKET RegPacket;

typedef struct _XHCI_HC_RESOURCES {
    ULONG Dcbaa[256];
    XHCI_COMMAND_TRB CommandRing[XHCI_COMMAND_RING_MAX];
} XHCI_HC_RESOURCES, *PXHCI_HC_RESOURCES;

typedef struct _XHCI_EXTENSION {
    PXHCI_HC_CAPABILITY_REGISTERS CapRegs;
    PXHCI_HC_OPER_REGS OperRegs;
    PXHCI_PORTSC PortSc;
    USHORT HcSystemErrors;
    USHORT NumberOfPorts;
    BOOL HasPPC;
} XHCI_EXTENSION, *PXHCI_EXTENSION;

/* roothub.c */
MPSTATUS
NTAPI
XHCI_RH_ChirpRootPort(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

VOID
NTAPI
XHCI_RH_GetRootHubData(
  _In_ PVOID XhciExtension,
  _In_ PVOID rootHubData);

MPSTATUS
NTAPI
XHCI_RH_GetStatus(
  _In_ PVOID XhciExtension,
  _In_ PUSHORT Status);

MPSTATUS
NTAPI
XHCI_RH_GetPortStatus(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port,
  _In_ PUSB_PORT_STATUS_AND_CHANGE PortStatus);

MPSTATUS
NTAPI
XHCI_RH_GetHubStatus(
  _In_ PVOID XhciExtension,
  _In_ PUSB_HUB_STATUS_AND_CHANGE HubStatus);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortReset(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortPower(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortEnable(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortSuspend(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnable(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortPower(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspend(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnableChange(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortConnectChange(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortResetChange(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspendChange(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortOvercurrentChange(
  _In_ PVOID XhciExtension,
  _In_ USHORT Port);

VOID
NTAPI
XHCI_RH_DisableIrq(
  _In_ PVOID XhciExtension);

VOID
NTAPI
XHCI_RH_EnableIrq(
    _In_ PVOID XhciExtension);
