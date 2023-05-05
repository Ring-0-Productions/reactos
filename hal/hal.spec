@ fastcall -arch=i386 ExAcquireFastMutex(ptr) ntoskrnl.ExiAcquireFastMutex
@ fastcall -arch=i386 ExReleaseFastMutex(ptr) ntoskrnl.ExiReleaseFastMutex
@ fastcall -arch=i386 ExTryToAcquireFastMutex(ptr) ntoskrnl.ExiTryToAcquireFastMutex
@ stdcall HalAcquireDisplayOwnership(ptr)
@ stdcall HalAdjustResourceList(ptr)
@ stdcall HalAllProcessorsStarted()
@ stdcall HalAllocateAdapterChannel(ptr ptr long ptr)
@ stdcall HalAllocateCommonBuffer(ptr long ptr long)
@ stdcall HalAllocateCrashDumpRegisters(ptr ptr)
@ stdcall HalAssignSlotResources(ptr ptr ptr ptr long long long ptr)
@ stdcall -arch=i386,arm HalBeginSystemInterrupt(long long ptr)
@ stdcall HalCalibratePerformanceCounter(ptr long long)
;@ stdcall -arch=x86_64 HalCallBios()
@ fastcall HalClearSoftwareInterrupt(long)
@ stdcall HalDisableSystemInterrupt(long long)
@ stdcall HalDisplayString(str)
@ stdcall HalEnableSystemInterrupt(long long long)
@ stdcall -arch=i386,arm HalEndSystemInterrupt(long long)
@ stdcall HalFlushCommonBuffer(long long long long long)
@ stdcall HalFreeCommonBuffer(ptr long long long ptr long)
@ stdcall HalGetAdapter(ptr ptr)
@ stdcall HalGetBusData(long long long ptr long)
@ stdcall HalGetBusDataByOffset(long long long ptr long long)
@ stdcall HalGetEnvironmentVariable(str long str)
@ fastcall -arch=arm HalGetInterruptSource()
@ stdcall HalGetInterruptVector(long long long long ptr ptr)
;@ stdcall -arch=x86_64 HalHandleMcheck()
@ stdcall -arch=i386,x86_64 HalHandleNMI(ptr)
@ stdcall HalInitSystem(long ptr)
@ stdcall HalInitializeProcessor(long ptr)
;@ stdcall -arch=x86_64 HalIsHyperThreadingEnabled()
@ stdcall HalMakeBeep(long)
@ stdcall HalProcessorIdle()
@ stdcall HalQueryDisplayParameters(ptr ptr ptr ptr)
@ stdcall HalQueryRealTimeClock(ptr)
@ stdcall HalReadDmaCounter(ptr)
@ stdcall HalReportResourceUsage()
@ stdcall HalRequestIpi(long)
@ fastcall HalRequestSoftwareInterrupt(long)
@ stdcall HalReturnToFirmware(long)
;@ stdcall -arch=x86_64 HalSendNMI()
;@ stdcall -arch=x86_64 HalSendSoftwareInterrupt()
@ stdcall HalSetBusData(long long long ptr long)
@ stdcall HalSetBusDataByOffset(long long long ptr long long)
@ stdcall HalSetDisplayParameters(long long)
@ stdcall HalSetEnvironmentVariable(str str)
@ stdcall HalSetProfileInterval(long)
@ stdcall HalSetRealTimeClock(ptr)
@ stdcall HalSetTimeIncrement(long)
@ stdcall HalStartNextProcessor(ptr ptr)
@ stdcall HalStartProfileInterrupt(long)
@ stdcall HalStopProfileInterrupt(long)
@ fastcall -arch=arm HalSweepIcache()
@ fastcall -arch=arm HalSweepDcache()
@ fastcall HalSystemVectorDispatchEntry(long long long)
@ stdcall HalTranslateBusAddress(long long long long ptr ptr)
@ stdcall -arch=i386,x86_64 IoAssignDriveLetters(ptr str ptr ptr) HalpAssignDriveLetters
@ stdcall IoFlushAdapterBuffers(ptr ptr ptr ptr long long)
@ stdcall IoFreeAdapterChannel(ptr)
@ stdcall IoFreeMapRegisters(ptr ptr long)
@ stdcall IoMapTransfer(ptr ptr ptr ptr ptr long)
@ stdcall -arch=i386,x86_64 IoReadPartitionTable(ptr long long ptr) HalpReadPartitionTable
@ stdcall -arch=i386,x86_64 IoSetPartitionInformation(ptr long long long) HalpSetPartitionInformation
@ stdcall -arch=i386,x86_64 IoWritePartitionTable(ptr long long long ptr) HalpWritePartitionTable
@ extern KdComPortInUse
@ fastcall -arch=i386 KeAcquireInStackQueuedSpinLock(ptr ptr)
@ fastcall -arch=i386 KeAcquireInStackQueuedSpinLockRaiseToSynch(ptr ptr)
@ fastcall -arch=i386 KeAcquireQueuedSpinLock(ptr)
@ fastcall -arch=i386 KeAcquireQueuedSpinLockRaiseToSynch(ptr)
@ stdcall -arch=i386 KeAcquireSpinLock(ptr ptr)
@ fastcall -arch=i386 KeAcquireSpinLockRaiseToSynch(ptr)
@ stdcall KeFlushWriteBuffer()
@ stdcall -arch=i386,arm KeGetCurrentIrql()
@ stdcall -arch=i386 KeLowerIrql(long)
@ stdcall KeQueryPerformanceCounter(ptr)
@ stdcall -arch=i386 KeRaiseIrql(long ptr)
@ stdcall -arch=i386 KeRaiseIrqlToDpcLevel()
@ stdcall -arch=i386 KeRaiseIrqlToSynchLevel()
@ fastcall -arch=i386 KeReleaseInStackQueuedSpinLock(ptr)
@ fastcall -arch=i386 KeReleaseQueuedSpinLock(ptr long)
@ stdcall -arch=i386 KeReleaseSpinLock(ptr long)
@ stdcall KeStallExecutionProcessor(long)
@ fastcall -arch=i386 KeTryToAcquireQueuedSpinLock(long ptr)
@ fastcall -arch=i386 KeTryToAcquireQueuedSpinLockRaiseToSynch(long ptr)
@ fastcall -arch=i386 KfAcquireSpinLock(ptr)
@ fastcall -arch=i386,arm KfLowerIrql(long)
@ fastcall -arch=i386,arm KfRaiseIrql(long)
@ fastcall -arch=i386 KfReleaseSpinLock(ptr long)
@ stdcall -arch=i386,arm READ_PORT_BUFFER_UCHAR(ptr ptr long)
@ stdcall -arch=i386,arm READ_PORT_BUFFER_ULONG(ptr ptr long)
@ stdcall -arch=i386,arm READ_PORT_BUFFER_USHORT(ptr ptr long)
@ stdcall -arch=i386,arm READ_PORT_UCHAR(ptr)
@ stdcall -arch=i386,arm READ_PORT_ULONG(ptr)
@ stdcall -arch=i386,arm READ_PORT_USHORT(ptr)
@ stdcall -arch=i386,arm WRITE_PORT_BUFFER_UCHAR(ptr ptr long)
@ stdcall -arch=i386,arm WRITE_PORT_BUFFER_ULONG(ptr ptr long)
@ stdcall -arch=i386,arm WRITE_PORT_BUFFER_USHORT(ptr ptr long)
@ stdcall -arch=i386,arm WRITE_PORT_UCHAR(ptr long)
@ stdcall -arch=i386,arm WRITE_PORT_ULONG(ptr long)
@ stdcall -arch=i386,arm WRITE_PORT_USHORT(ptr long)
@ stdcall -version=0x0502 -arch=x86_64 x86BiosAllocateBuffer(ptr ptr ptr)
@ stdcall -version=0x0600+ -arch=i386,x86_64 x86BiosAllocateBuffer(ptr ptr ptr)
@ stdcall -version=0x0502 -arch=x86_64 x86BiosCall(long ptr)
@ stdcall -version=0x0600+ -arch=i386,x86_64 x86BiosCall(long ptr)
@ stdcall -version=0x0502 -arch=x86_64 x86BiosFreeBuffer(long long)
@ stdcall -version=0x0600+ -arch=i386,x86_64 x86BiosFreeBuffer(long long)
@ stdcall -version=0x0502 -arch=x86_64 x86BiosReadMemory(long long ptr long)
@ stdcall -version=0x0600+ -arch=i386,x86_64 x86BiosReadMemory(long long ptr long)
@ stdcall -version=0x0502 -arch=x86_64 x86BiosWriteMemory(long long ptr long)
@ stdcall -version=0x0600+ -arch=i386,x86_64 x86BiosWriteMemory(long long ptr long)
