

/* INCLUDES ******************************************************************/

#include <hal.h>
//#define NDEBUG
#include <debug.h>

/* GLOBALS *******************************************************************/

PUCHAR KdComPortInUse;
KAFFINITY HalpActiveProcessors;
KAFFINITY HalpDefaultInterruptAffinity;

/* PUBLIC FUNCTIONS **********************************************************/

EXTERN_C
CODE_SEG("INIT")
VOID
NTAPI
HalInitializeProcessor(
    IN ULONG ProcessorNumber,
    IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    /* Set default IDR */
    KeGetPcr()->IDR = 0xFFFFFFFB;

    /* Set default stall count */
    KeGetPcr()->StallScaleFactor = INITIAL_STALL_COUNT;

    /* Update the interrupt affinity and processor mask */
    InterlockedBitTestAndSet((PLONG)&HalpActiveProcessors, ProcessorNumber);
    InterlockedBitTestAndSet((PLONG)&HalpDefaultInterruptAffinity, ProcessorNumber);

#if 0
    /* Update the interrupt affinity and processor mask */
    InterlockedBitTestAndSet((PLONG)&HalpActiveProcessors, ProcessorNumber);
    InterlockedBitTestAndSet((PLONG)&HalpDefaultInterruptAffinity, ProcessorNumber);

    /* Register routines for KDCOM */

    /* Register PCI Device Functions */
    KdSetupPciDeviceForDebugging = HalpSetupPciDeviceForDebugging;
    KdReleasePciDeviceforDebugging = HalpReleasePciDeviceForDebugging;

    /* Register ACPI stub */
    KdGetAcpiTablePhase0 = HalAcpiGetTable;
    KdCheckPowerButton = HalpCheckPowerButton;

    /* Register memory functions */
    KdMapPhysicalMemory64 = HalpMapPhysicalMemory64;
    KdUnmapVirtualAddress = HalpUnmapVirtualAddress;
#endif
}

CODE_SEG("INIT")
BOOLEAN
NTAPI
HalInitSystem(IN ULONG BootPhase,
              IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    __debugbreak();
    return 0;
}

