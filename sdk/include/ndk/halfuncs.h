/*++ NDK Version: 0098

Copyright (c) Alex Ionescu.  All rights reserved.

Header Name:

    halfuncs.h

Abstract:

    Function definitions for the HAL.

Author:

    Alex Ionescu (alexi@tinykrnl.org) - Updated - 27-Feb-2006

--*/

#ifndef _HALFUNCS_H
#define _HALFUNCS_H

//
// Dependencies
//
#include <umtypes.h>
#include <haltypes.h>
#include <ketypes.h>
#include <section_attribs.h>

#ifndef NTOS_MODE_USER

//
// Private HAL Callbacks
//
#define HalHandlerForBus                                   HALPRIVATEDISPATCH->HalHandlerForBus
#define HalHandlerForConfigSpace                           HALPRIVATEDISPATCH->HalHandlerForConfigSpace
#define HalLocateHiberRanges                               HALPRIVATEDISPATCH->HalLocateHiberRanges
#define HalRegisterBusHandler                              HALPRIVATEDISPATCH->HalRegisterBusHandler
#define HalSetWakeEnable                                   HALPRIVATEDISPATCH->HalSetWakeEnable
#define HalSetWakeAlarm                                    HALPRIVATEDISPATCH->HalSetWakeAlarm
#define HalPciTranslateBusAddress                          HALPRIVATEDISPATCH->HalPciTranslateBusAddress
#define HalPciAssignSlotResources                          HALPRIVATEDISPATCH->HalPciAssignSlotResources
#define HalHaltSystem                                      HALPRIVATEDISPATCH->HalHaltSystem
#define HalFindBusAddressTranslation                       HALPRIVATEDISPATCH->HalFindBusAddressTranslation
#define HalResetDisplay                                    HALPRIVATEDISPATCH->HalResetDisplay
#define HalAllocateMapRegisters                            HALPRIVATEDISPATCH->HalAllocateMapRegisters
#define KdSetupPciDeviceForDebugging                       HALPRIVATEDISPATCH->KdSetupPciDeviceForDebugging
#define KdReleasePciDeviceforDebugging                     HALPRIVATEDISPATCH->KdReleasePciDeviceforDebugging
#define KdGetAcpiTablePhase0                               HALPRIVATEDISPATCH->KdGetAcpiTablePhase0
#define KdCheckPowerButton                                 HALPRIVATEDISPATCH->KdCheckPowerButton
#define HalVectorToIDTEntry                                HALPRIVATEDISPATCH->HalVectorToIDTEntry
#define KdMapPhysicalMemory64                              HALPRIVATEDISPATCH->KdMapPhysicalMemory64
#define KdUnmapVirtualAddress                              HALPRIVATEDISPATCH->KdUnmapVirtualAddress
#define KdGetPciDataByOffset                               HALPRIVATEDISPATCH->KdGetPciDataByOffset
#define KdSetPciDataByOffset                               HALPRIVATEDISPATCH->KdSetPciDataByOffset
#define HalLoadMicrocode                                   HALPRIVATEDISPATCH->HalLoadMicrocode
#define HalUnloadMicrocode                                 HALPRIVATEDISPATCH->HalUnloadMicrocode
#define HalPostMicrocodeUpdate                             HALPRIVATEDISPATCH->HalPostMicrocodeUpdate
#define HalAllocateMessageTargetOverride                   HALPRIVATEDISPATCH->HalAllocateMessageTargetOverride
#define HalFreeMessageTargetOverride                       HALPRIVATEDISPATCH->HalFreeMessageTargetOverride
#define HalDpReplaceBegin                                  HALPRIVATEDISPATCH->HalDpReplaceBegin
#define HalDpReplaceTarget                                 HALPRIVATEDISPATCH->HalDpReplaceTarget
#define HalDpReplaceControl                                HALPRIVATEDISPATCH->HalDpReplaceControl
#define HalDpReplaceEnd                                    HALPRIVATEDISPATCH->HalDpReplaceEnd
#define HalPrepareForBugcheck                              HALPRIVATEDISPATCH->HalPrepareForBugcheck
#define HalQueryWakeTime                                   HALPRIVATEDISPATCH->HalQueryWakeTime
#define HalReportIdleStateUsage                            HALPRIVATEDISPATCH->HalReportIdleStateUsage
#define HalTscSynchronization                              HALPRIVATEDISPATCH->HalTscSynchronization
#define HalWheaInitProcessorGenericSection                 HALPRIVATEDISPATCH->HalWheaInitProcessorGenericSection
#define HalStopLegacyUsbInterrupts                         HALPRIVATEDISPATCH->HalStopLegacyUsbInterrupts
#define HalReadWheaPhysicalMemory                          HALPRIVATEDISPATCH->HalReadWheaPhysicalMemory
#define HalWriteWheaPhysicalMemory                         HALPRIVATEDISPATCH->HalWriteWheaPhysicalMemory
#define HalDpMaskLevelTriggeredInterrupts                  HALPRIVATEDISPATCH->HalDpMaskLevelTriggeredInterrupts
#define HalDpUnmaskLevelTriggeredInterrupts                HALPRIVATEDISPATCH->HalDpUnmaskLevelTriggeredInterrupts
#define HalDpGetInterruptReplayState                       HALPRIVATEDISPATCH->HalDpGetInterruptReplayState
#define HalDpReplayInterrupts                              HALPRIVATEDISPATCH->HalDpReplayInterrupts
#define HalQueryIoPortAccessSupported                      HALPRIVATEDISPATCH->HalQueryIoPortAccessSupported
#define KdSetupIntegratedDeviceForDebugging                HALPRIVATEDISPATCH->KdSetupIntegratedDeviceForDebugging
#define KdReleaseIntegratedDeviceForDebugging              HALPRIVATEDISPATCH->KdReleaseIntegratedDeviceForDebugging
#define HalGetEnlightenmentInformation                     HALPRIVATEDISPATCH->HalGetEnlightenmentInformation
#define HalAllocateEarlyPages                              HALPRIVATEDISPATCH->HalAllocateEarlyPages
#define HalMapEarlyPages                                   HALPRIVATEDISPATCH->HalMapEarlyPages
//#define PVOID Dummy1                                       HALPRIVATEDISPATCH->PVOID Dummy1
//#define PVOID Dummy2                                       HALPRIVATEDISPATCH->PVOID Dummy2
#define HalNotifyProcessorFreeze                           HALPRIVATEDISPATCH->HalNotifyProcessorFreeze
#define HalPrepareProcessorForIdle                         HALPRIVATEDISPATCH->HalPrepareProcessorForIdle
#define HalRegisterLogRoutine                              HALPRIVATEDISPATCH->HalRegisterLogRoutine
#define HalResumeProcessorFromIdle                         HALPRIVATEDISPATCH->HalResumeProcessorFromIdle
//#define PVOID Dummy                                        HALPRIVATEDISPATCH->PVOID Dummy
#define HalVectorToIDTEntryEx                              HALPRIVATEDISPATCH->HalVectorToIDTEntryEx
#define HalSecondaryInterruptQueryPrimaryInformation       HALPRIVATEDISPATCH->HalSecondaryInterruptQueryPrimaryInformation
#define HalMaskInterrupt                                   HALPRIVATEDISPATCH->HalMaskInterrupt
#define HalUnmaskInterrupt                                 HALPRIVATEDISPATCH->HalUnmaskInterrupt
#define HalIsInterruptTypeSecondary                        HALPRIVATEDISPATCH->HalIsInterruptTypeSecondary
#define HalAllocateGsivForSecondaryInterrupt               HALPRIVATEDISPATCH->HalAllocateGsivForSecondaryInterrupt
#define HalAddInterruptRemapping                           HALPRIVATEDISPATCH->HalAddInterruptRemapping
#define HalRemoveInterruptRemapping                        HALPRIVATEDISPATCH->HalRemoveInterruptRemapping
#define HalSaveAndDisableHvEnlightenment                   HALPRIVATEDISPATCH->HalSaveAndDisableHvEnlightenment
#define HalRestoreHvEnlightenment                          HALPRIVATEDISPATCH->HalRestoreHvEnlightenment
#define HalFlushIoBuffersExternalCache                     HALPRIVATEDISPATCH->HalFlushIoBuffersExternalCache
#define HalFlushExternalCache                              HALPRIVATEDISPATCH->HalFlushExternalCache
#define HalPciEarlyRestore                                 HALPRIVATEDISPATCH->HalPciEarlyRestore
#define HalGetProcessorId                                  HALPRIVATEDISPATCH->HalGetProcessorId
#define HalAllocatePmcCounterSet                           HALPRIVATEDISPATCH->HalAllocatePmcCounterSet
#define HalCollectPmcCounters                              HALPRIVATEDISPATCH->HalCollectPmcCounters
#define HalFreePmcCounterSet                               HALPRIVATEDISPATCH->HalFreePmcCounterSet
#define HalProcessorHalt                                   HALPRIVATEDISPATCH->HalProcessorHalt
#define HalTimerQueryCycleCounter                          HALPRIVATEDISPATCH->HalTimerQueryCycleCounter
//#define PVOID Dummy3                                       HALPRIVATEDISPATCH->PVOID Dummy3
#define HalPciMarkHiberPhase                               HALPRIVATEDISPATCH->HalPciMarkHiberPhase
#define HalQueryProcessorRestartEntryPoint                 HALPRIVATEDISPATCH->HalQueryProcessorRestartEntryPoint
#define HalRequestInterrupt                                HALPRIVATEDISPATCH->HalRequestInterrupt
#define HalEnumerateUnmaskedInterrupts                     HALPRIVATEDISPATCH->HalEnumerateUnmaskedInterrupts
#define HalFlushAndInvalidatePageExternalCache             HALPRIVATEDISPATCH->HalFlushAndInvalidatePageExternalCache
#define KdEnumerateDebuggingDevices                        HALPRIVATEDISPATCH->KdEnumerateDebuggingDevices
#define HalFlushIoRectangleExternalCache                   HALPRIVATEDISPATCH->HalFlushIoRectangleExternalCache
#define HalPowerEarlyRestore                               HALPRIVATEDISPATCH->HalPowerEarlyRestore
#define HalQueryCapsuleCapabilities                        HALPRIVATEDISPATCH->HalQueryCapsuleCapabilities
#define HalUpdateCapsule                                   HALPRIVATEDISPATCH->HalUpdateCapsule
#define HalPciMultiStageResumeCapable                      HALPRIVATEDISPATCH->HalPciMultiStageResumeCapable
#define HalDmaFreeCrashDumpRegisters                       HALPRIVATEDISPATCH->HalDmaFreeCrashDumpRegisters
#define HalAcpiAoacCapable                                 HALPRIVATEDISPATCH->HalAcpiAoacCapable
#define HalInterruptSetDestination                         HALPRIVATEDISPATCH->HalInterruptSetDestination
#define HalGetClockConfiguration                           HALPRIVATEDISPATCH->HalGetClockConfiguration
#define HalClockTimerActivate                              HALPRIVATEDISPATCH->HalClockTimerActivate
#define HalClockTimerInitialize                            HALPRIVATEDISPATCH->HalClockTimerInitialize
#define HalClockTimerStop                                  HALPRIVATEDISPATCH->HalClockTimerStop
#define HalClockTimerArm                                   HALPRIVATEDISPATCH->HalClockTimerArm
#define HalTimerOnlyClockInterruptPending                  HALPRIVATEDISPATCH->HalTimerOnlyClockInterruptPending
#define HalAcpiGetMultiNode                                HALPRIVATEDISPATCH->HalAcpiGetMultiNode
#define HalPowerSetRebootHandler                           HALPRIVATEDISPATCH->HalPowerSetRebootHandler
#define HalIommuRegisterDispatchTable                      HALPRIVATEDISPATCH->HalIommuRegisterDispatchTable
#define HalTimerWatchdogStart                              HALPRIVATEDISPATCH->HalTimerWatchdogStart
#define HalTimerWatchdogResetCountdown                     HALPRIVATEDISPATCH->HalTimerWatchdogResetCountdown
#define HalTimerWatchdogStop                               HALPRIVATEDISPATCH->HalTimerWatchdogStop
#define HalTimerWatchdogGeneratedLastReset                 HALPRIVATEDISPATCH->HalTimerWatchdogGeneratedLastReset
#define HalTimerWatchdogTriggerSystemReset                 HALPRIVATEDISPATCH->HalTimerWatchdogTriggerSystemReset

//                                                                           
// Display Functions                                       
//                                                         
NTHALAPI                                                   
VOID                                                       
NTAPI                                                      
HalDisplayString(
    _In_ PCHAR String
);

//
// Initialization Functions
//
NTHALAPI
BOOLEAN
NTAPI
HalAllProcessorsStarted(
    VOID
);

#ifdef _ARC_
NTHALAPI
VOID
NTAPI
HalInitializeProcessor(
    _In_ ULONG ProcessorNumber,
    _In_ struct _LOADER_PARAMETER_BLOCK *LoaderBlock
);

CODE_SEG("INIT")
NTHALAPI
BOOLEAN
NTAPI
HalInitSystem(
    _In_ ULONG BootPhase,
    _In_ struct _LOADER_PARAMETER_BLOCK *LoaderBlock
);

NTHALAPI
BOOLEAN
NTAPI
HalStartNextProcessor(
    _In_ struct _LOADER_PARAMETER_BLOCK *LoaderBlock,
    _In_ PKPROCESSOR_STATE ProcessorState
);

#endif

NTHALAPI
VOID
NTAPI
HalReturnToFirmware(
    _In_ FIRMWARE_REENTRY Action
);

//
// CPU Routines
//
NTHALAPI
VOID
NTAPI
HalProcessorIdle(
    VOID
);

//
// Interrupt Functions
//
NTHALAPI
BOOLEAN
NTAPI
HalBeginSystemInterrupt(
    _In_ KIRQL Irql,
    _In_ ULONG Vector,
    _Out_ PKIRQL OldIrql
);

VOID
FASTCALL
HalClearSoftwareInterrupt(
    _In_ KIRQL Request
);

NTHALAPI
VOID
NTAPI
HalDisableSystemInterrupt(
    _In_ ULONG Vector,
    _In_ KIRQL Irql
);

NTHALAPI
BOOLEAN
NTAPI
HalEnableSystemInterrupt(
    _In_ ULONG Vector,
    _In_ KIRQL Irql,
    _In_ KINTERRUPT_MODE InterruptMode
);

#ifdef __REACTOS__
NTHALAPI
VOID
NTAPI
HalEndSystemInterrupt(
    _In_ KIRQL Irql,
    _In_ PKTRAP_FRAME TrapFrame
);
#else
NTHALAPI
VOID
NTAPI
HalEndSystemInterrupt(
    _In_ KIRQL Irql,
    _In_ UCHAR Vector
);
#endif

#ifdef _ARM_ // FIXME: ndk/arm? armddk.h?
ULONG
HalGetInterruptSource(
    VOID
);
#endif

CODE_SEG("INIT")
NTHALAPI
VOID
NTAPI
HalReportResourceUsage(
    VOID
);

NTHALAPI
VOID
FASTCALL
HalRequestSoftwareInterrupt(
    _In_ KIRQL SoftwareInterruptRequested
);

NTHALAPI
VOID
NTAPI
HalRequestIpi(
    _In_ KAFFINITY TargetSet
);

NTHALAPI
VOID
NTAPI
HalHandleNMI(
    PVOID NmiInfo
);

NTHALAPI
UCHAR
FASTCALL
HalSystemVectorDispatchEntry(
    _In_ ULONG Vector,
    _Out_ PKINTERRUPT_ROUTINE **FlatDispatch,
    _Out_ PKINTERRUPT_ROUTINE *NoConnection
);

//
// Bus Functions
//
NTHALAPI
NTSTATUS
NTAPI
HalAdjustResourceList(
    _Inout_ PIO_RESOURCE_REQUIREMENTS_LIST *pResourceList
);

//
// Environment Functions
//
#ifdef _ARC_
NTHALAPI
ARC_STATUS
NTAPI
HalSetEnvironmentVariable(
    _In_ PCH Name,
    _In_ PCH Value
);

NTHALAPI
ARC_STATUS
NTAPI
HalGetEnvironmentVariable(
    _In_ PCH Variable,
    _In_ USHORT Length,
    _Out_ PCH Buffer
);
#endif

//
// Profiling Functions
//
VOID
NTAPI
HalStartProfileInterrupt(
    _In_ KPROFILE_SOURCE ProfileSource
);

NTHALAPI
VOID
NTAPI
HalStopProfileInterrupt(
    _In_ KPROFILE_SOURCE ProfileSource
);

NTHALAPI
ULONG_PTR
NTAPI
HalSetProfileInterval(
    _In_ ULONG_PTR Interval
);

//
// Time Functions
//
NTHALAPI
BOOLEAN
NTAPI
HalQueryRealTimeClock(
    _In_ PTIME_FIELDS RtcTime
);

NTHALAPI
BOOLEAN
NTAPI
HalSetRealTimeClock(
    _In_ PTIME_FIELDS RtcTime
);

NTHALAPI
ULONG
NTAPI
HalSetTimeIncrement(
    _In_ ULONG Increment
);


//
// BIOS call API
//
NTSTATUS
NTAPI
x86BiosAllocateBuffer(
    _In_ ULONG *Size,
    _In_ USHORT *Segment,
    _In_ USHORT *Offset);

NTSTATUS
NTAPI
x86BiosFreeBuffer(
    _In_ USHORT Segment,
    _In_ USHORT Offset);

NTSTATUS
NTAPI
x86BiosReadMemory(
    _In_ USHORT Segment,
    _In_ USHORT Offset,
    _Out_writes_bytes_(Size) PVOID Buffer,
    _In_ ULONG Size);

NTSTATUS
NTAPI
x86BiosWriteMemory(
    _In_ USHORT Segment,
    _In_ USHORT Offset,
    _In_reads_bytes_(Size) PVOID Buffer,
    _In_ ULONG Size);

BOOLEAN
NTAPI
x86BiosCall(
    _In_ ULONG InterruptNumber,
    _Inout_ PX86_BIOS_REGISTERS Registers);

#endif // NTOS_MODE_USER
#endif // _HALFUNCS_H
