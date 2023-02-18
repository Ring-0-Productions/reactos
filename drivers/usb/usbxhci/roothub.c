/*
 * PROJECT:         ReactOS system libraries
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         roothub functions of xHCI
 * PROGRAMMER:      Rama Teja Gampa <ramateja.g@gmail.com>
*/
#include "usbxhci.h"
//#define NDEBUG
#include <debug.h>
#define NDEBUG_XHCI_ROOT_HUB
#include "dbg_xhci.h"

VOID
NTAPI
XHCI_RH_GetRootHubData(_Inout_ PVOID hcExtension,
                       _Inout_ PVOID rootHubData)
{
    PUSBPORT_ROOT_HUB_DATA RootHubData;
    PXHCI_EXTENSION XhciExtension;

    DPRINT("XHCI_RH_GetRootHubData: function initiated\n");
    XhciExtension = (PXHCI_EXTENSION)hcExtension;
    DPRINT_RH("XHCI_RH_GetRootHubData: XhciExtension - %p, rootHubData - %p\n",
              XhciExtension,
              rootHubData);

    RootHubData = (PUSBPORT_ROOT_HUB_DATA)rootHubData;
    RootHubData->NumberOfPorts = XhciExtension->NumberOfPorts;

    /*
        Identifies a Compound Device: Hub is not part of a compound device.
        Over-current Protection Mode: Global Over-current Protection.
    */
    RootHubData->HubCharacteristics.AsUSHORT &= 3;
    RootHubData->PowerOnToPowerGood = 2;
    RootHubData->HubControlCurrent = 0;
}

MPSTATUS
NTAPI
XHCI_RH_GetStatus(IN PVOID xhciExtension,
                  IN PUSHORT Status)
{
    DPRINT1("XHCI_RH_GetStatus: function initiated\n");
    *Status = USB_GETSTATUS_SELF_POWERED;
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_GetPortStatus(IN PVOID xhciExtension,
                      IN USHORT Port,
                      IN PUSB_PORT_STATUS_AND_CHANGE PortStatus)
{
    
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_GetHubStatus(IN PVOID xhciExtension,
                     IN PUSB_HUB_STATUS_AND_CHANGE HubStatus)
{
    DPRINT("XHCI_RH_GetHubStatus: function initiated\n"); //removed to reduce windbg output
    HubStatus->AsUlong32 = 0;
    return MP_STATUS_SUCCESS;
}

VOID
NTAPI
XHCI_RH_FinishReset(IN PVOID xhciExtension,
                    IN PUSHORT Port)
{
    DPRINT1("XHCI_RH_FinishReset: function initiated\n");
}

ULONG
NTAPI
XHCI_RH_PortResetComplete(IN PVOID xhciExtension,
                          IN PUSHORT Port)
{
    DPRINT1("XHCI_RH_PortResetComplete: function initiated\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortReset(IN PVOID xhciExtension,
                            IN USHORT Port)
{
    DPRINT1("XHCI_RH_SetFeaturePortReset: function initiated\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortPower(_Inout_ PVOID hcExtension,
                            _In_    USHORT Port)
{
    XHCI_PORT_STATUS_CONTROL PortStatusRegister;
    PXHCI_EXTENSION XhciExtension;
    PULONG PortStatusRegPointer;

    DPRINT1("XHCI_RH_SetFeaturePortPower: function initiated\n");
    XhciExtension = (PXHCI_EXTENSION)hcExtension;
    ASSERT(Port != 0 && Port <= XhciExtension->NumberOfPorts);
    PortStatusRegPointer = (XhciExtension->OperationalRegs) + (XHCI_PORTSC + (Port - 1)*4);
    PortStatusRegister.AsULONG = READ_REGISTER_ULONG(PortStatusRegPointer);
    PortStatusRegister.AsULONG = PortStatusRegister.AsULONG & PORT_STATUS_MASK;
    PortStatusRegister.PortPower = 1;

    WRITE_REGISTER_ULONG(PortStatusRegPointer, PortStatusRegister.AsULONG );
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortEnable(IN PVOID xhciExtension,
                             IN USHORT Port)
{
    DPRINT_RH("XHCI_RH_SetFeaturePortEnable: Not supported\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_SetFeaturePortSuspend(IN PVOID xhciExtension,
                              IN USHORT Port)
{
    DPRINT1("XHCI_RH_SetFeaturePortSuspend: function initiated\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnable(IN PVOID xhciExtension,
                               IN USHORT Port)
{
    DPRINT1("XHCI_RH_ClearFeaturePortEnable: function initiated\n");
    return MP_STATUS_SUCCESS;    
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortPower(IN PVOID xhciExtension,
                              IN USHORT Port)
{
    DPRINT1("XHCI_RH_ClearFeaturePortPower: function initiated\n");
    return MP_STATUS_SUCCESS;
}

VOID
NTAPI
XHCI_RH_PortResumeComplete(IN PULONG xhciExtension,
                           IN PUSHORT Port)
{
   DPRINT1("XHCI_RH_PortResumeComplete: function initiated\n");
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspend(IN PVOID xhciExtension,
                                IN USHORT Port)
{
    DPRINT1("XHCI_RH_ClearFeaturePortSuspend: function initiated\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortEnableChange(IN PVOID xhciExtension,
                                     IN USHORT Port)
{
    DPRINT1("XHCI_RH_ClearFeaturePortEnableChange: function initiated\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortConnectChange(_Inout_ PVOID hcExtension,
                                      _In_    USHORT Port)
{
    XHCI_PORT_STATUS_CONTROL PortStatusRegister;
    PXHCI_EXTENSION XhciExtension;
    PULONG PortStatusRegPointer;

    DPRINT1("XHCI_RH_ClearFeaturePortConnectChange: function initiated\n");
    XhciExtension = (PXHCI_EXTENSION)hcExtension;
    ASSERT(Port != 0 && Port <= XhciExtension->NumberOfPorts);
    PortStatusRegPointer = (XhciExtension->OperationalRegs) + (XHCI_PORTSC + (Port - 1)*4);
    PortStatusRegister.AsULONG = READ_REGISTER_ULONG(PortStatusRegPointer);
    PortStatusRegister.AsULONG = PortStatusRegister.AsULONG & PORT_STATUS_MASK;
    PortStatusRegister.ConnectStatusChange = 1;

    WRITE_REGISTER_ULONG(PortStatusRegPointer, PortStatusRegister.AsULONG );
    PortStatusRegister.AsULONG = READ_REGISTER_ULONG(PortStatusRegPointer) ;

    ASSERT(PortStatusRegister.ConnectStatusChange == 0);
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortResetChange(IN PVOID xhciExtension,
                                    IN USHORT Port)
{
    DPRINT1("XHCI_RH_ClearFeaturePortResetChange: function initiated\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortSuspendChange(IN PVOID xhciExtension,
                                      IN USHORT Port)
{
    DPRINT1("XHCI_RH_ClearFeaturePortSuspendChange: function initiated\n");
    return MP_STATUS_SUCCESS;
}

MPSTATUS
NTAPI
XHCI_RH_ClearFeaturePortOvercurrentChange(IN PVOID xhciExtension,
                                          IN USHORT Port)
{
    DPRINT1("XHCI_RH_ClearFeaturePortOvercurrentChange: function initiated\n");
    return MP_STATUS_SUCCESS;
}

VOID
NTAPI
XHCI_RH_DisableIrq(_In_ PVOID hcExtension)
{
   PXHCI_EXTENSION XhciExtension;
   XHCI_USB_COMMAND usbCommand;
   PULONG OperationalRegs;

   DPRINT("XHCI_RH_DisableIrq: function initiated\n");
   XhciExtension = (PXHCI_EXTENSION)hcExtension;
   OperationalRegs = XhciExtension->OperationalRegs;
   usbCommand.AsULONG =READ_REGISTER_ULONG(OperationalRegs + XHCI_USBCMD);
   if (usbCommand.InterrupterEnable != 0)
   {
        usbCommand.InterrupterEnable = 0;

       WRITE_REGISTER_ULONG(OperationalRegs + XHCI_USBCMD,usbCommand.AsULONG);
   }

}

VOID
NTAPI
XHCI_RH_EnableIrq(_In_ PVOID hcExtension)
{
    PXHCI_EXTENSION XhciExtension;
    XHCI_USB_COMMAND usbCommand;
    PULONG OperationalRegs;

    DPRINT("XHCI_RH_EnableIrq: function initiated\n");
    XhciExtension = (PXHCI_EXTENSION)hcExtension;
    OperationalRegs = XhciExtension->OperationalRegs;
    usbCommand.AsULONG =READ_REGISTER_ULONG(OperationalRegs + XHCI_USBCMD);

    if (usbCommand.InterrupterEnable != 1)
    {
        usbCommand.InterrupterEnable = 1;
        WRITE_REGISTER_ULONG(OperationalRegs + XHCI_USBCMD,usbCommand.AsULONG);
    }
}
