@ stdcall CcCanIWrite(ptr long long long)
@ stdcall CcCopyRead(ptr ptr long long ptr ptr)
@ stdcall CcCopyWrite(ptr ptr long long ptr)
@ stdcall CcDeferWrite(ptr ptr ptr ptr long long)
@ stdcall CcFastCopyRead(ptr long long long ptr ptr)
@ stdcall CcFastCopyWrite(ptr long long ptr)
@ extern CcFastMdlReadWait
@ extern CcFastReadNotPossible
@ extern CcFastReadWait
@ stdcall CcFlushCache(ptr ptr long ptr)
@ stdcall CcGetDirtyPages(ptr ptr ptr ptr)
@ stdcall CcGetFileObjectFromBcb(ptr)
@ stdcall CcGetFileObjectFromSectionPtrs(ptr)
@ stdcall CcGetFlushedValidData(ptr long)
@ stdcall CcGetLsnForFileObject(ptr ptr)
@ stdcall CcInitializeCacheMap(ptr ptr long ptr ptr)
@ stdcall CcIsThereDirtyData(ptr)
@ stdcall CcMapData(ptr ptr long long ptr ptr)
@ stdcall CcMdlRead(ptr ptr long ptr ptr)
@ stdcall CcMdlReadComplete(ptr ptr)
@ stdcall CcMdlWriteAbort(ptr ptr)
@ stdcall CcMdlWriteComplete(ptr ptr ptr)
@ stdcall CcPinMappedData(ptr ptr long long ptr)
@ stdcall CcPinRead(ptr ptr long long ptr ptr)
@ stdcall CcPrepareMdlWrite(ptr ptr long ptr ptr)
@ stdcall CcPreparePinWrite(ptr ptr long long long ptr ptr)
@ stdcall CcPurgeCacheSection(ptr ptr long long)
@ stdcall CcRemapBcb(ptr)
@ stdcall CcRepinBcb(ptr)
@ stdcall CcScheduleReadAhead(ptr ptr long)
@ stdcall CcSetAdditionalCacheAttributes(ptr long long)
@ stdcall CcSetBcbOwnerPointer(ptr ptr)
@ stdcall CcSetDirtyPageThreshold(ptr long)
@ stdcall CcSetDirtyPinnedData(ptr ptr)
@ stdcall CcSetFileSizes(ptr ptr)
@ stdcall CcSetLogHandleForFile(ptr ptr ptr)
@ stdcall CcSetReadAheadGranularity(ptr long)
@ stdcall CcUninitializeCacheMap(ptr ptr ptr)
@ stdcall CcUnpinData(ptr)
@ stdcall CcUnpinDataForThread(ptr ptr)
@ stdcall CcUnpinRepinnedBcb(ptr long ptr)
@ stdcall CcWaitForCurrentLazyWriterActivity()
@ stdcall CcZeroData(ptr ptr ptr long)
@ stdcall CmRegisterCallback(ptr ptr ptr)
@ stdcall CmUnRegisterCallback(long long)
@ stdcall DbgBreakPoint()
@ stdcall DbgBreakPointWithStatus(long)
@ stdcall DbgCommandString(ptr ptr)
@ stdcall -stub -version=0x601+ DbgkLkmdRegisterCallback()
@ stdcall DbgLoadImageSymbols(ptr ptr long)
@ varargs DbgPrint(str)
@ varargs DbgPrintEx(long long str)
@ varargs DbgPrintReturnControlC(str)
@ stdcall DbgPrompt(str ptr long)
@ stdcall DbgQueryDebugFilterState(long long)
@ stdcall DbgSetDebugFilterState(long long long)
@ stdcall -stub -version=0x600+ EmProviderDeregister()
@ stdcall -stub -version=0x600+ EmProviderRegister()
@ stdcall -version=0x600+ EtwEventEnabled(int64 ptr)
@ stdcall -version=0x600+ EtwRegister(ptr ptr ptr ptr)
@ stdcall -version=0x600+ EtwUnregister(int64)
@ stdcall -version=0x600+ EtwWrite(int64 ptr ptr long ptr)
@ stdcall -arch=x86_64 ExAcquireFastMutex(ptr)
@ fastcall ExAcquireFastMutexUnsafe(ptr)
@ stdcall ExAcquireResourceExclusiveLite(ptr long)
@ stdcall ExAcquireResourceSharedLite(ptr long)
@ fastcall ExAcquireRundownProtection(ptr) ExfAcquireRundownProtection
@ fastcall ExAcquireRundownProtectionCacheAware(ptr) ExfAcquireRundownProtectionCacheAware
@ fastcall ExAcquireRundownProtectionCacheAwareEx(ptr long) ExfAcquireRundownProtectionCacheAwareEx
@ fastcall ExAcquireRundownProtectionEx(ptr long) ExfAcquireRundownProtectionEx
@ stdcall ExAcquireSharedStarveExclusive(ptr long)
@ stdcall ExAcquireSharedWaitForExclusive(ptr long)
@ stdcall ExAllocateCacheAwareRundownProtection(long long)
@ stdcall ExAllocateFromPagedLookasideList(ptr) ExiAllocateFromPagedLookasideList
@ stdcall ExAllocatePool(long long)
@ stdcall ExAllocatePoolWithQuota(long long)
@ stdcall ExAllocatePoolWithQuotaTag(long long long)
@ stdcall ExAllocatePoolWithTag(long long long)
@ stdcall ExAllocatePoolWithTagPriority(long long long long)
@ stdcall ExConvertExclusiveToSharedLite(ptr)
@ stdcall ExCreateCallback(ptr ptr long long)
@ stdcall ExDeleteNPagedLookasideList(ptr)
@ stdcall ExDeletePagedLookasideList(ptr)
@ stdcall ExDeleteResourceLite(ptr)
@ extern ExDesktopObjectType
@ stdcall ExDisableResourceBoostLite(ptr)
@ fastcall ExEnterCriticalRegionAndAcquireFastMutexUnsafe(ptr)
@ stdcall ExEnterCriticalRegionAndAcquireResourceExclusive(ptr)
@ stdcall ExEnterCriticalRegionAndAcquireResourceShared(ptr)
@ stdcall ExEnterCriticalRegionAndAcquireSharedWaitForExclusive(ptr)
@ stdcall -version=0x600+ ExEnterPriorityRegionAndAcquireResourceExclusive(ptr)
@ stdcall -version=0x600+ ExEnterPriorityRegionAndAcquireResourceShared(ptr)
@ stdcall ExEnumHandleTable(ptr ptr ptr ptr)
@ extern ExEventObjectType
@ stdcall ExExtendZone(ptr ptr long)
@ stdcall ExFreeCacheAwareRundownProtection(ptr)
@ stdcall ExFreePool(ptr)
@ stdcall ExFreePoolWithTag(ptr long)
@ stdcall ExFreeToPagedLookasideList(ptr ptr) ExiFreeToPagedLookasideList
@ stdcall ExGetCurrentProcessorCounts(ptr ptr ptr)
@ stdcall ExGetCurrentProcessorCpuUsage(ptr)
@ stdcall ExGetExclusiveWaiterCount(ptr)
@ stdcall ExGetPreviousMode()
@ stdcall ExGetSharedWaiterCount(ptr)
@ stdcall -version=0x600+ ExDeleteLookasideListEx(ptr)
@ stdcall -version=0x600+ ExInitializeLookasideListEx(ptr ptr ptr ptr long long long long)
@ stdcall ExInitializeNPagedLookasideList(ptr ptr ptr long long long long)
@ stdcall ExInitializePagedLookasideList(ptr ptr ptr long long long long)
@ stdcall ExInitializeResourceLite(ptr)
@ fastcall ExInitializeRundownProtection(ptr) ExfInitializeRundownProtection
@ stdcall ExInitializeRundownProtectionCacheAware(ptr long)
@ stdcall ExInitializeZone(ptr long ptr long)
@ stdcall ExInterlockedAddLargeInteger(ptr long long ptr)
@ fastcall -arch=i386 ExInterlockedAddLargeStatistic(ptr long)
@ stdcall ExInterlockedAddUlong(ptr long ptr)
@ fastcall -arch=i386 ExInterlockedCompareExchange64(ptr ptr ptr ptr)
@ stdcall -arch=i386 ExInterlockedDecrementLong(ptr ptr)
@ stdcall -arch=i386 ExInterlockedExchangeUlong(ptr long ptr)
@ stdcall ExInterlockedExtendZone(ptr ptr long ptr)
@ fastcall -arch=i386 ExInterlockedFlushSList(ptr)
@ stdcall -arch=i386 ExInterlockedIncrementLong(ptr ptr)
@ stdcall ExInterlockedInsertHeadList(ptr ptr ptr)
@ stdcall ExInterlockedInsertTailList(ptr ptr ptr)
@ stdcall ExInterlockedPopEntryList(ptr ptr)
@ fastcall -arch=i386 ExInterlockedPopEntrySList(ptr ptr)
@ stdcall ExInterlockedPushEntryList(ptr ptr ptr)
@ fastcall -arch=i386 ExInterlockedPushEntrySList(ptr ptr ptr)
@ stdcall ExInterlockedRemoveHeadList(ptr ptr)
@ stdcall ExIsProcessorFeaturePresent(long)
@ stdcall ExIsResourceAcquiredExclusiveLite(ptr)
@ stdcall ExIsResourceAcquiredSharedLite(ptr)
@ stdcall ExLocalTimeToSystemTime(ptr ptr)
@ stdcall ExNotifyCallback(ptr ptr ptr)
@ stdcall -arch=x86_64,arm ExQueryDepthSList(ptr) RtlQueryDepthSList
@ stdcall ExQueryPoolBlockSize(ptr ptr)
@ stdcall ExQueueWorkItem(ptr long)
@ stdcall ExRaiseAccessViolation()
@ stdcall ExRaiseDatatypeMisalignment()
@ stdcall ExRaiseException(ptr) RtlRaiseException
@ stdcall ExRaiseHardError(long long long ptr long ptr)
@ stdcall ExRaiseStatus(long) RtlRaiseStatus
@ fastcall ExReInitializeRundownProtection(ptr) ExfReInitializeRundownProtection
@ fastcall ExReInitializeRundownProtectionCacheAware(ptr) ExfReInitializeRundownProtectionCacheAware
@ stdcall ExRegisterCallback(ptr ptr ptr)
@ stdcall ExReinitializeResourceLite(ptr)
@ stdcall -arch=x86_64 ExReleaseFastMutex(ptr)
@ fastcall ExReleaseFastMutexUnsafe(ptr)
@ fastcall ExReleaseFastMutexUnsafeAndLeaveCriticalRegion(ptr)
@ fastcall ExReleaseResourceAndLeaveCriticalRegion(ptr)
@ fastcall -version=0x600+ ExReleaseResourceAndLeavePriorityRegion(ptr)
@ stdcall ExReleaseResourceForThreadLite(ptr long)
@ fastcall ExReleaseResourceLite(ptr)
@ fastcall ExReleaseRundownProtection(ptr) ExfReleaseRundownProtection
@ fastcall ExReleaseRundownProtectionCacheAware(ptr) ExfReleaseRundownProtectionCacheAware
@ fastcall ExReleaseRundownProtectionCacheAwareEx(ptr long) ExfReleaseRundownProtectionCacheAwareEx
@ fastcall ExReleaseRundownProtectionEx(ptr long) ExfReleaseRundownProtectionEx
@ fastcall ExRundownCompleted(ptr) ExfRundownCompleted
@ fastcall ExRundownCompletedCacheAware(ptr) ExfRundownCompletedCacheAware
@ extern ExSemaphoreObjectType
@ stdcall ExSetResourceOwnerPointer(ptr ptr)
@ stdcall ExSetTimerResolution(long long)
@ stdcall ExSizeOfRundownProtectionCacheAware()
@ stdcall ExSystemExceptionFilter()
@ stdcall ExSystemTimeToLocalTime(ptr ptr)
@ stdcall -arch=x86_64 ExTryToAcquireFastMutex(ptr)
@ stdcall ExUnregisterCallback(ptr)
@ stdcall ExUuidCreate(ptr)
@ stdcall ExVerifySuite(long)
@ fastcall ExWaitForRundownProtectionRelease(ptr) ExfWaitForRundownProtectionRelease
@ fastcall ExWaitForRundownProtectionReleaseCacheAware(ptr) ExfWaitForRundownProtectionReleaseCacheAware
@ extern ExWindowStationObjectType
@ fastcall ExfAcquirePushLockExclusive(ptr)
@ fastcall ExfAcquirePushLockShared(ptr)
@ fastcall -arch=i386 ExfInterlockedAddUlong(ptr long ptr)
@ fastcall -arch=i386 ExfInterlockedCompareExchange64(ptr ptr ptr)
@ fastcall -arch=i386 ExfInterlockedInsertHeadList(ptr ptr ptr)
@ fastcall -arch=i386 ExfInterlockedInsertTailList(ptr ptr ptr)
@ fastcall -arch=i386 ExfInterlockedPopEntryList(ptr ptr)
@ fastcall -arch=i386 ExfInterlockedPushEntryList(ptr ptr ptr)
@ fastcall -arch=i386 ExfInterlockedRemoveHeadList(ptr ptr)
@ fastcall ExfReleasePushLock(ptr)
@ fastcall ExfReleasePushLockExclusive(ptr)
@ fastcall ExfReleasePushLockShared(ptr)
@ fastcall ExfTryToWakePushLock(ptr)
@ fastcall ExfUnblockPushLock(ptr ptr)
@ stdcall -arch=x86_64,arm ExpInterlockedFlushSList(ptr) RtlInterlockedFlushSList
@ stdcall -arch=x86_64,arm ExpInterlockedPopEntrySList(ptr ptr) RtlInterlockedPopEntrySList
@ stdcall -arch=x86_64,arm ExpInterlockedPushEntrySList(ptr ptr) RtlInterlockedPushEntrySList
@ fastcall -arch=i386 Exfi386InterlockedDecrementLong(ptr)
@ fastcall -arch=i386 Exfi386InterlockedExchangeUlong(ptr long)
@ fastcall -arch=i386 Exfi386InterlockedIncrementLong(ptr)
@ stdcall -arch=i386 Exi386InterlockedDecrementLong(ptr)
@ stdcall -arch=i386 Exi386InterlockedExchangeUlong(ptr long)
@ stdcall -arch=i386 Exi386InterlockedIncrementLong(ptr)
@ fastcall -arch=i386 ExiAcquireFastMutex(ptr) ExAcquireFastMutex
@ fastcall -arch=i386 ExiReleaseFastMutex(ptr) ExReleaseFastMutex
@ fastcall -arch=i386 ExiTryToAcquireFastMutex(ptr) ExTryToAcquireFastMutex
@ stdcall FsRtlAcquireFileExclusive(ptr)
@ stdcall FsRtlAddBaseMcbEntry(ptr long long long long long long)
@ stdcall FsRtlAddLargeMcbEntry(ptr long long long long long long)
@ stdcall FsRtlAddMcbEntry(ptr long long long)
@ stdcall FsRtlAddToTunnelCache(ptr long long ptr ptr long long ptr)
@ stdcall FsRtlAllocateFileLock(ptr ptr)
@ stdcall FsRtlAllocatePool(long long)
@ stdcall FsRtlAllocatePoolWithQuota(long long)
@ stdcall FsRtlAllocatePoolWithQuotaTag(long long long)
@ stdcall FsRtlAllocatePoolWithTag(long long long)
@ stdcall FsRtlAllocateResource()
@ stdcall FsRtlAreNamesEqual(ptr ptr long wstr)
@ stdcall FsRtlBalanceReads(ptr)
@ stdcall FsRtlCheckLockForReadAccess(ptr ptr)
@ stdcall FsRtlCheckLockForWriteAccess(ptr ptr)
@ stdcall FsRtlCheckOplock(ptr ptr ptr ptr ptr)
@ stdcall FsRtlCopyRead(ptr ptr long long long ptr ptr ptr)
@ stdcall FsRtlCopyWrite(ptr ptr long long long ptr ptr ptr)
@ stdcall FsRtlCreateSectionForDataScan(ptr ptr ptr ptr long ptr ptr long long long)
@ stdcall FsRtlCurrentBatchOplock(ptr)
@ stdcall FsRtlDeleteKeyFromTunnelCache(ptr long long)
@ stdcall FsRtlDeleteTunnelCache(ptr)
@ stdcall FsRtlDeregisterUncProvider(ptr)
@ stdcall FsRtlDissectDbcs(long ptr ptr ptr)
@ stdcall FsRtlDissectName(long ptr ptr ptr)
@ stdcall FsRtlDoesDbcsContainWildCards(ptr)
@ stdcall FsRtlDoesNameContainWildCards(ptr)
@ stdcall FsRtlFastCheckLockForRead(ptr ptr ptr long ptr ptr)
@ stdcall FsRtlFastCheckLockForWrite(ptr ptr ptr long ptr ptr)
@ stdcall FsRtlFastUnlockAll(ptr ptr ptr ptr)
@ stdcall FsRtlFastUnlockAllByKey(ptr ptr ptr long ptr)
@ stdcall FsRtlFastUnlockSingle(ptr ptr ptr ptr ptr long ptr long)
@ stdcall FsRtlFindInTunnelCache(ptr long long ptr ptr ptr ptr ptr)
@ stdcall FsRtlFreeFileLock(ptr)
@ stdcall FsRtlGetFileSize(ptr ptr)
@ stdcall FsRtlGetNextBaseMcbEntry(ptr long ptr ptr ptr)
@ stdcall FsRtlGetNextFileLock(ptr long)
@ stdcall FsRtlGetNextLargeMcbEntry(ptr long ptr ptr ptr)
@ stdcall FsRtlGetNextMcbEntry(ptr long ptr ptr ptr)
@ stdcall FsRtlIncrementCcFastReadNoWait()
@ stdcall FsRtlIncrementCcFastReadNotPossible()
@ stdcall FsRtlIncrementCcFastReadResourceMiss()
@ stdcall FsRtlIncrementCcFastReadWait()
@ stdcall FsRtlInitializeBaseMcb(ptr ptr)
@ stdcall FsRtlInitializeFileLock(ptr ptr ptr)
@ stdcall FsRtlInitializeLargeMcb(ptr long)
@ stdcall FsRtlInitializeMcb(ptr long)
@ stdcall FsRtlInitializeOplock(ptr)
@ stdcall FsRtlInitializeTunnelCache(ptr)
@ stdcall FsRtlInsertPerFileObjectContext(ptr ptr)
@ stdcall FsRtlInsertPerStreamContext(ptr ptr)
@ stdcall FsRtlIsDbcsInExpression(ptr ptr)
@ stdcall FsRtlIsFatDbcsLegal(long ptr long long long)
@ stdcall FsRtlIsHpfsDbcsLegal(long ptr long long long)
@ stdcall FsRtlIsNameInExpression(ptr ptr long wstr)
@ stdcall FsRtlIsNtstatusExpected(long)
@ stdcall FsRtlIsPagingFile(ptr)
@ stdcall FsRtlIsTotalDeviceFailure(ptr)
@ extern FsRtlLegalAnsiCharacterArray
@ stdcall FsRtlLookupBaseMcbEntry(ptr long long ptr ptr ptr ptr ptr)
@ stdcall FsRtlLookupLargeMcbEntry(ptr long long ptr ptr ptr ptr ptr)
@ stdcall FsRtlLookupLastBaseMcbEntry(ptr ptr ptr)
@ stdcall FsRtlLookupLastBaseMcbEntryAndIndex(ptr ptr ptr ptr)
@ stdcall FsRtlLookupLastLargeMcbEntry(ptr ptr ptr)
@ stdcall FsRtlLookupLastLargeMcbEntryAndIndex(ptr ptr ptr ptr)
@ stdcall FsRtlLookupLastMcbEntry(ptr ptr ptr)
@ stdcall FsRtlLookupMcbEntry(ptr long ptr ptr ptr)
@ stdcall FsRtlLookupPerFileObjectContext(ptr ptr ptr)
@ stdcall FsRtlLookupPerStreamContextInternal(ptr ptr ptr)
@ stdcall FsRtlMdlRead(ptr ptr long long ptr ptr)
@ stdcall FsRtlMdlReadComplete(ptr ptr)
@ stdcall FsRtlMdlReadCompleteDev(ptr ptr ptr)
@ stdcall FsRtlMdlReadDev(ptr ptr long long ptr ptr ptr)
@ stdcall FsRtlMdlWriteComplete(ptr ptr ptr)
@ stdcall FsRtlMdlWriteCompleteDev(ptr ptr ptr ptr)
@ stdcall FsRtlNormalizeNtstatus(long long)
@ stdcall FsRtlNotifyChangeDirectory(ptr ptr ptr ptr long long ptr)
@ stdcall FsRtlNotifyCleanup(ptr ptr ptr)
@ stdcall FsRtlNotifyFilterChangeDirectory(ptr ptr ptr ptr long long long ptr ptr ptr ptr)
@ stdcall FsRtlNotifyFilterReportChange(ptr ptr ptr long ptr ptr long long ptr ptr)
@ stdcall FsRtlNotifyFullChangeDirectory(ptr ptr ptr ptr long long long ptr ptr ptr)
@ stdcall FsRtlNotifyFullReportChange(ptr ptr ptr long ptr ptr long long ptr)
@ stdcall FsRtlNotifyInitializeSync(ptr)
@ stdcall FsRtlNotifyReportChange(ptr ptr ptr ptr long)
@ stdcall FsRtlNotifyUninitializeSync(ptr)
@ stdcall FsRtlNotifyVolumeEvent(ptr long)
@ stdcall FsRtlNumberOfRunsInBaseMcb(ptr)
@ stdcall FsRtlNumberOfRunsInLargeMcb(ptr)
@ stdcall FsRtlNumberOfRunsInMcb(ptr)
@ stdcall FsRtlOplockFsctrl(ptr ptr long)
@ stdcall FsRtlOplockIsFastIoPossible(ptr)
@ stdcall FsRtlPostPagingFileStackOverflow(ptr ptr ptr)
@ stdcall FsRtlPostStackOverflow(ptr ptr ptr)
@ stdcall FsRtlPrepareMdlWrite(ptr ptr long long ptr ptr)
@ stdcall FsRtlPrepareMdlWriteDev(ptr ptr long long ptr ptr ptr)
@ stdcall FsRtlPrivateLock(ptr ptr ptr ptr ptr long long long ptr ptr ptr long)
@ stdcall FsRtlProcessFileLock(ptr ptr ptr)
@ stdcall FsRtlRegisterFileSystemFilterCallbacks(ptr ptr)
@ stdcall FsRtlRegisterUncProvider(ptr ptr long)
@ stdcall FsRtlReleaseFile(ptr)
@ stdcall FsRtlRemoveBaseMcbEntry(ptr long long long long)
@ stdcall FsRtlRemoveLargeMcbEntry(ptr long long long long)
@ stdcall FsRtlRemoveMcbEntry(ptr long long)
@ stdcall FsRtlRemovePerFileObjectContext(ptr ptr ptr)
@ stdcall FsRtlRemovePerStreamContext(ptr ptr ptr)
@ stdcall FsRtlResetBaseMcb(ptr)
@ stdcall FsRtlResetLargeMcb(ptr long)
@ stdcall FsRtlSplitBaseMcb(ptr long long long long)
@ stdcall FsRtlSplitLargeMcb(ptr long long long long)
@ stdcall FsRtlSyncVolumes(long long long)
@ stdcall FsRtlTeardownPerStreamContexts(ptr)
@ stdcall FsRtlTruncateBaseMcb(ptr long long)
@ stdcall FsRtlTruncateLargeMcb(ptr long long)
@ stdcall FsRtlTruncateMcb(ptr long)
@ stdcall FsRtlUninitializeBaseMcb(ptr)
@ stdcall FsRtlUninitializeFileLock(ptr)
@ stdcall FsRtlUninitializeLargeMcb(ptr)
@ stdcall FsRtlUninitializeMcb(ptr)
@ stdcall FsRtlUninitializeOplock(ptr)
@ extern HalDispatchTable
@ fastcall HalExamineMBR(ptr long long ptr)
@ extern HalPrivateDispatchTable
@ stdcall HeadlessDispatch(long ptr long ptr ptr)
@ stdcall InbvAcquireDisplayOwnership()
@ stdcall InbvCheckDisplayOwnership()
@ stdcall InbvDisplayString(str)
@ stdcall InbvEnableBootDriver(long)
@ stdcall InbvEnableDisplayString(long)
@ stdcall InbvInstallDisplayStringFilter(ptr)
@ stdcall InbvIsBootDriverInstalled()
@ stdcall InbvNotifyDisplayOwnershipLost(ptr)
@ stdcall InbvResetDisplay()
@ stdcall InbvSetScrollRegion(long long long long)
@ stdcall InbvSetTextColor(long)
@ stdcall InbvSolidColorFill(long long long long long)
@ extern InitSafeBootMode
@ fastcall -arch=i386,arm InterlockedCompareExchange(ptr long long)
@ fastcall -arch=i386,arm InterlockedDecrement(ptr)
@ fastcall -arch=i386,arm InterlockedExchange(ptr long)
@ fastcall -arch=i386,arm InterlockedExchangeAdd(ptr long)
@ fastcall -arch=i386,arm InterlockedIncrement(ptr)
@ fastcall -arch=i386 InterlockedPopEntrySList(ptr)
@ fastcall -arch=i386 InterlockedPushEntrySList(ptr ptr)
@ stdcall -arch=arm InterlockedPopEntrySList(ptr) RtlInterlockedPopEntrySList
@ stdcall -arch=arm InterlockedPushEntrySList(ptr ptr) RtlInterlockedPushEntrySList
@ stdcall -arch=x86_64 InitializeSListHead(ptr) RtlInitializeSListHead
@ stdcall IoAcquireCancelSpinLock(ptr)
@ stdcall IoAcquireRemoveLockEx(ptr ptr str long long)
@ stdcall IoAcquireVpbSpinLock(ptr)
@ extern IoAdapterObjectType
@ stdcall IoAllocateAdapterChannel(ptr ptr long ptr ptr)
@ stdcall IoAllocateController(ptr ptr ptr ptr)
@ stdcall IoAllocateDriverObjectExtension(ptr ptr long ptr)
@ stdcall IoAllocateErrorLogEntry(ptr long)
@ stdcall IoAllocateIrp(long long)
@ stdcall IoAllocateMdl(ptr long long long ptr)
@ stdcall IoAllocateWorkItem(ptr)
@ fastcall IoAssignDriveLetters(ptr ptr ptr ptr)
@ stdcall IoAssignResources(ptr ptr ptr ptr ptr ptr)
@ stdcall IoAttachDevice(ptr ptr ptr)
@ stdcall IoAttachDeviceByPointer(ptr ptr)
@ stdcall IoAttachDeviceToDeviceStack(ptr ptr)
@ stdcall IoAttachDeviceToDeviceStackSafe(ptr ptr ptr)
@ stdcall IoBuildAsynchronousFsdRequest(long ptr ptr long ptr ptr)
@ stdcall IoBuildDeviceIoControlRequest(long ptr ptr long ptr long long ptr ptr)
@ stdcall IoBuildPartialMdl(ptr ptr ptr long)
@ stdcall IoBuildSynchronousFsdRequest(long ptr ptr long ptr ptr ptr)
@ stdcall IoCallDriver(ptr ptr)
@ stdcall IoCancelFileOpen(ptr ptr)
@ stdcall IoCancelIrp(ptr)
@ stdcall IoCheckDesiredAccess(ptr long)
@ stdcall IoCheckEaBufferValidity(ptr long ptr)
@ stdcall IoCheckFunctionAccess(long long long long ptr ptr)
@ stdcall IoCheckQuerySetFileInformation(long long long)
@ stdcall IoCheckQuerySetVolumeInformation(long long long)
@ stdcall IoCheckQuotaBufferValidity(ptr long ptr)
@ stdcall IoCheckShareAccess(long long ptr ptr long)
@ stdcall IoCompleteRequest(ptr long)
@ stdcall IoConnectInterrupt(ptr ptr ptr ptr long long long long long long long)
@ stdcall IoCreateController(long)
@ stdcall IoCreateDevice(ptr long ptr long long long ptr)
@ stdcall IoCreateDisk(ptr ptr)
@ stdcall IoCreateDriver(ptr ptr)
@ stdcall IoCreateFile(ptr long ptr ptr ptr long long long long ptr long long ptr long)
@ stdcall IoCreateFileSpecifyDeviceObjectHint(ptr long ptr ptr ptr long long long long ptr long long ptr long ptr)
@ stdcall IoCreateNotificationEvent(ptr ptr)
@ stdcall IoCreateStreamFileObject(ptr ptr)
@ stdcall IoCreateStreamFileObjectEx(ptr ptr ptr)
@ stdcall IoCreateStreamFileObjectLite(ptr ptr)
@ stdcall IoCreateSymbolicLink(ptr ptr)
@ stdcall IoCreateSynchronizationEvent(ptr ptr)
@ stdcall IoCreateUnprotectedSymbolicLink(ptr ptr)
@ stdcall IoCsqInitialize(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall IoCsqInitializeEx(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall IoCsqInsertIrp(ptr ptr ptr)
@ stdcall IoCsqInsertIrpEx(ptr ptr ptr ptr)
@ stdcall IoCsqRemoveIrp(ptr ptr)
@ stdcall IoCsqRemoveNextIrp(ptr ptr)
@ stdcall IoDeleteController(ptr)
@ stdcall IoDeleteDevice(ptr)
@ stdcall IoDeleteDriver(ptr)
@ stdcall IoDeleteSymbolicLink(ptr)
@ stdcall IoDetachDevice(ptr)
@ extern IoDeviceHandlerObjectSize
@ extern IoDeviceHandlerObjectType
@ extern IoDeviceObjectType
@ stdcall IoDisconnectInterrupt(ptr)
@ extern IoDriverObjectType
@ stdcall IoEnqueueIrp(ptr)
@ stdcall IoEnumerateDeviceObjectList(ptr ptr long ptr)
@ stdcall IoEnumerateRegisteredFiltersList(ptr long ptr)
@ stdcall IoFastQueryNetworkAttributes(ptr long long ptr ptr)
@ extern IoFileObjectType
@ stdcall IoForwardAndCatchIrp(ptr ptr) IoForwardIrpSynchronously
@ stdcall IoForwardIrpSynchronously(ptr ptr)
@ stdcall IoFreeController(ptr)
@ stdcall IoFreeErrorLogEntry(ptr)
@ stdcall IoFreeIrp(ptr)
@ stdcall IoFreeMdl(ptr)
@ stdcall IoFreeWorkItem(ptr)
@ stdcall IoGetAttachedDevice(ptr)
@ stdcall IoGetAttachedDeviceReference(ptr)
@ stdcall IoGetBaseFileSystemDeviceObject(ptr)
@ stdcall IoGetBootDiskInformation(ptr long)
@ stdcall IoGetConfigurationInformation()
@ stdcall IoGetCurrentProcess()
@ stdcall IoGetDeviceAttachmentBaseRef(ptr)
@ stdcall IoGetDeviceInterfaceAlias(ptr ptr ptr)
@ stdcall IoGetDeviceInterfaces(ptr ptr long ptr)
@ stdcall IoGetDeviceObjectPointer(ptr long ptr ptr)
@ stdcall IoGetDeviceProperty(ptr long long ptr ptr)
@ stdcall IoGetDeviceToVerify(ptr)
@ stdcall IoGetDiskDeviceObject(ptr ptr)
@ stdcall IoGetDmaAdapter(ptr ptr ptr)
@ stdcall IoGetDriverObjectExtension(ptr ptr)
@ stdcall IoGetFileObjectGenericMapping()
@ stdcall IoGetInitialStack()
@ stdcall IoGetLowerDeviceObject(ptr)
@ fastcall IoGetPagingIoPriority(ptr)
@ stdcall IoGetRelatedDeviceObject(ptr)
@ stdcall IoGetRequestorProcess(ptr)
@ stdcall IoGetRequestorProcessId(ptr)
@ stdcall IoGetRequestorSessionId(ptr ptr)
@ stdcall IoGetStackLimits(ptr ptr)
@ stdcall IoGetTopLevelIrp()
@ stdcall IoInitializeIrp(ptr long long)
@ stdcall IoInitializeRemoveLockEx(ptr long long long long)
@ stdcall IoInitializeTimer(ptr ptr ptr)
@ stdcall IoInvalidateDeviceRelations(ptr long)
@ stdcall IoInvalidateDeviceState(ptr)
@ stdcall -arch=x86_64 IoIs32bitProcess(ptr)
@ stdcall IoIsFileOriginRemote(ptr)
@ stdcall IoIsOperationSynchronous(ptr)
@ stdcall IoIsSystemThread(ptr)
@ stdcall IoIsValidNameGraftingBuffer(ptr ptr)
@ stdcall IoIsWdmVersionAvailable(long long)
@ stdcall IoMakeAssociatedIrp(ptr long)
@ stdcall IoOpenDeviceInterfaceRegistryKey(ptr long ptr)
@ stdcall IoOpenDeviceRegistryKey(ptr long long ptr)
@ stdcall IoPageRead(ptr ptr ptr ptr ptr)
@ stdcall IoPnPDeliverServicePowerNotification(long long long long)
@ stdcall IoQueryDeviceDescription(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall IoQueryFileDosDeviceName(ptr ptr)
@ stdcall IoQueryFileInformation(ptr long long ptr ptr)
@ stdcall IoQueryVolumeInformation(ptr long long ptr ptr)
@ stdcall IoQueueThreadIrp(ptr)
@ stdcall IoQueueWorkItem(ptr ptr long ptr)
@ stdcall IoRaiseHardError(ptr ptr ptr)
@ stdcall IoRaiseInformationalHardError(long ptr ptr)
@ stdcall IoReadDiskSignature(ptr long ptr)
@ extern IoReadOperationCount
@ fastcall IoReadPartitionTable(ptr long long ptr)
@ stdcall IoReadPartitionTableEx(ptr ptr)
@ extern IoReadTransferCount
@ stdcall IoRegisterBootDriverReinitialization(ptr ptr ptr)
@ stdcall IoRegisterDeviceInterface(ptr ptr ptr ptr)
@ stdcall IoRegisterDriverReinitialization(ptr ptr ptr)
@ stdcall IoRegisterFileSystem(ptr)
@ stdcall IoRegisterFsRegistrationChange(ptr ptr)
@ stdcall IoRegisterLastChanceShutdownNotification(ptr)
@ stdcall IoRegisterPlugPlayNotification(long long ptr ptr ptr ptr ptr)
@ stdcall IoRegisterShutdownNotification(ptr)
@ stdcall IoReleaseCancelSpinLock(long)
@ stdcall IoReleaseRemoveLockAndWaitEx(ptr ptr long)
@ stdcall IoReleaseRemoveLockEx(ptr ptr long)
@ stdcall IoReleaseVpbSpinLock(long)
@ stdcall IoRemoveShareAccess(ptr ptr)
@ stdcall IoReportDetectedDevice(ptr long long long ptr ptr long ptr)
@ stdcall IoReportHalResourceUsage(ptr ptr ptr long)
@ stdcall IoReportResourceForDetection(ptr ptr long ptr ptr long ptr)
@ stdcall IoReportResourceUsage(ptr ptr ptr long ptr ptr long long ptr)
@ stdcall IoReportTargetDeviceChange(ptr ptr)
@ stdcall IoReportTargetDeviceChangeAsynchronous(ptr ptr ptr ptr)
@ stdcall IoRequestDeviceEject(ptr)
@ stdcall IoReuseIrp(ptr long)
@ stdcall IoSetCompletionRoutineEx(ptr ptr ptr ptr long long long)
@ stdcall IoSetDeviceInterfaceState(ptr long)
@ stdcall IoSetDeviceToVerify(ptr ptr)
@ stdcall IoSetFileOrigin(ptr long)
@ stdcall IoSetHardErrorOrVerifyDevice(ptr ptr)
@ stdcall IoSetInformation(ptr ptr long ptr)
@ stdcall IoSetIoCompletion(ptr ptr ptr long ptr long)
@ stdcall -stub -version=0x600+ IoSetIoCompletionEx()
@ fastcall IoSetPartitionInformation(ptr long long long)
@ stdcall IoSetPartitionInformationEx(ptr long ptr)
@ stdcall IoSetShareAccess(long long ptr ptr)
@ stdcall IoSetStartIoAttributes(ptr long long)
@ stdcall IoSetSystemPartition(ptr)
@ stdcall IoSetThreadHardErrorMode(long)
@ stdcall IoSetTopLevelIrp(ptr)
@ stdcall IoStartNextPacket(ptr long)
@ stdcall IoStartNextPacketByKey(ptr long long)
@ stdcall IoStartPacket(ptr ptr ptr ptr)
@ stdcall IoStartTimer(ptr)
@ extern IoStatisticsLock
@ stdcall IoStopTimer(ptr)
@ stdcall IoSynchronousInvalidateDeviceRelations(ptr long)
@ stdcall IoSynchronousPageWrite(ptr ptr ptr ptr ptr)
@ stdcall IoThreadToProcess(ptr)
@ stdcall IoTranslateBusAddress(long long long long ptr ptr)
@ stdcall IoUnregisterFileSystem(ptr)
@ stdcall IoUnregisterFsRegistrationChange(ptr ptr)
@ stdcall IoUnregisterPlugPlayNotification(ptr)
@ stdcall IoUnregisterShutdownNotification(ptr)
@ stdcall IoUpdateShareAccess(ptr ptr)
@ stdcall IoValidateDeviceIoControlAccess(ptr long)
@ stdcall IoVerifyPartitionTable(ptr long)
@ stdcall IoVerifyVolume(ptr long)
@ stdcall IoVolumeDeviceToDosName(ptr ptr)
@ stdcall IoWMIAllocateInstanceIds(ptr long ptr)
@ stdcall IoWMIDeviceObjectToInstanceName(ptr ptr ptr)
@ stdcall -arch=x86_64 IoWMIDeviceObjectToProviderId(ptr)
@ stdcall IoWMIExecuteMethod(ptr ptr long long ptr ptr)
@ stdcall IoWMIHandleToInstanceName(ptr ptr ptr)
@ stdcall IoWMIOpenBlock(ptr long ptr)
@ stdcall IoWMIQueryAllData(ptr ptr ptr)
@ stdcall IoWMIQueryAllDataMultiple(ptr long ptr ptr)
@ stdcall IoWMIQuerySingleInstance(ptr ptr ptr ptr)
@ stdcall IoWMIQuerySingleInstanceMultiple(ptr ptr long ptr ptr)
@ stdcall IoWMIRegistrationControl(ptr long)
@ stdcall IoWMISetNotificationCallback(ptr ptr ptr)
@ stdcall IoWMISetSingleInstance(ptr ptr long long ptr)
@ stdcall IoWMISetSingleItem(ptr ptr long long long ptr)
@ stdcall IoWMISuggestInstanceName(ptr ptr long ptr)
@ stdcall IoWMIWriteEvent(ptr)
@ stdcall IoWriteErrorLogEntry(ptr)
@ extern IoWriteOperationCount
@ fastcall IoWritePartitionTable(ptr long long long ptr)
@ stdcall IoWritePartitionTableEx(ptr ptr)
@ extern IoWriteTransferCount
@ fastcall IofCallDriver(ptr ptr)
@ fastcall IofCompleteRequest(ptr long)
@ stdcall KdChangeOption(long long ptr long ptr ptr)
@ extern KdDebuggerEnabled
@ extern KdDebuggerNotPresent
@ stdcall KdDisableDebugger()
@ stdcall KdEnableDebugger()
@ extern KdEnteredDebugger
@ stdcall KdPollBreakIn()
@ stdcall KdPowerTransition(long)
@ stdcall KdRefreshDebuggerNotPresent()
@ stdcall KdSystemDebugControl(long ptr long ptr long ptr long)
@ stdcall -arch=i386 Ke386CallBios(long ptr)
@ stdcall -arch=i386 Ke386IoSetAccessProcess(ptr long)
@ stdcall -arch=i386 Ke386QueryIoAccessMap(long ptr)
@ stdcall -arch=i386 Ke386SetIoAccessMap(long ptr)
@ fastcall KeAcquireGuardedMutex(ptr)
@ fastcall KeAcquireGuardedMutexUnsafe(ptr)
@ cdecl -arch=x86_64 KeAcquireInStackQueuedSpinLock(ptr ptr)
@ fastcall KeAcquireInStackQueuedSpinLockAtDpcLevel(ptr ptr)
@ fastcall KeAcquireInStackQueuedSpinLockForDpc(ptr ptr)
@ cdecl -arch=x86_64 KeAcquireInStackQueuedSpinLockRaiseToSynch(ptr ptr)
@ stdcall KeAcquireInterruptSpinLock(ptr)
@ cdecl -arch=x86_64 KeAcquireQueuedSpinLock(long)
@ cdecl -arch=x86_64 KeAcquireQueuedSpinLockRaiseToSynch(long)
@ stdcall KeAcquireSpinLockAtDpcLevel(ptr)
@ fastcall KeAcquireSpinLockForDpc(ptr)
@ stdcall -arch=x86_64 KeAcquireSpinLockRaiseToDpc(ptr)
@ stdcall -arch=x86_64 KeAcquireSpinLockRaiseToSynch(ptr)
@ stdcall KeAddSystemServiceTable(ptr ptr long ptr long)
@ stdcall -version=0x600+ KeAlertThread(ptr ptr)
@ stdcall KeAreAllApcsDisabled()
@ stdcall KeAreApcsDisabled()
@ stdcall KeAttachProcess(ptr)
@ stdcall KeBugCheck(long)
@ stdcall KeBugCheckEx(long ptr ptr ptr ptr)
@ stdcall KeCancelTimer(ptr)
@ stdcall KeCapturePersistentThreadState(ptr long long long long long ptr)
@ stdcall KeClearEvent(ptr)
@ stdcall KeConnectInterrupt(ptr)
@ stdcall KeDelayExecutionThread(long long ptr)
@ stdcall KeDeregisterBugCheckCallback(ptr)
@ stdcall KeDeregisterBugCheckReasonCallback(ptr)
@ stdcall KeDeregisterNmiCallback(ptr)
@ stdcall KeDetachProcess()
@ stdcall KeDisconnectInterrupt(ptr)
@ stdcall KeEnterCriticalRegion() _KeEnterCriticalRegion
@ stdcall KeEnterGuardedRegion() _KeEnterGuardedRegion
@ stdcall KeEnterKernelDebugger()
;@ stdcall -arch=x86_64 KeExpandKernelStackAndCallout(ptr ptr double)
@ stdcall -version=0x600+ KeExpandKernelStackAndCallout(ptr ptr long)
@ stdcall KeFindConfigurationEntry(ptr long long ptr)
@ stdcall KeFindConfigurationNextEntry(ptr long long ptr ptr)
@ stdcall KeFlushEntireTb(long long)
@ stdcall -arch=arm KeFlushIoBuffers(ptr long long)
@ stdcall KeFlushQueuedDpcs()
@ stdcall KeGenericCallDpc(ptr ptr)
@ stdcall KeGetCurrentThread()
@ stdcall KeGetPreviousMode()
@ stdcall KeGetRecommendedSharedDataAlignment()
@ stdcall -arch=i386 KeI386AbiosCall(long ptr ptr long)
@ stdcall -arch=i386 KeI386AllocateGdtSelectors(ptr long)
@ stdcall -arch=i386 KeI386Call16BitCStyleFunction(long long ptr long)
@ stdcall -arch=i386 KeI386Call16BitFunction(ptr)
@ stdcall -arch=i386 KeI386FlatToGdtSelector(long long long)
@ stdcall -arch=i386 KeI386GetLid(long long long ptr ptr)
@ extern -arch=i386 KeI386MachineType
@ stdcall -arch=i386 KeI386ReleaseGdtSelectors(ptr long)
@ stdcall -arch=i386 KeI386ReleaseLid(long ptr)
@ stdcall -arch=i386 KeI386SetGdtSelector(long ptr)
@ stdcall KeInitializeApc(ptr ptr long ptr ptr ptr long ptr)
@ stdcall KeInitializeCrashDumpHeader(long long ptr long ptr)
@ stdcall KeInitializeDeviceQueue(ptr)
@ stdcall KeInitializeDpc(ptr ptr ptr)
@ stdcall KeInitializeEvent(ptr long long)
@ fastcall KeInitializeGuardedMutex(ptr)
@ stdcall KeInitializeInterrupt(ptr ptr ptr ptr long long long long long long long)
@ stdcall KeInitializeMutant(ptr long)
@ stdcall KeInitializeMutex(ptr long)
@ stdcall KeInitializeQueue(ptr long)
@ stdcall KeInitializeSemaphore(ptr long long)
@ stdcall -arch=i386,arm KeInitializeSpinLock(ptr) _KeInitializeSpinLock
@ stdcall KeInitializeThreadedDpc(ptr ptr ptr)
@ stdcall KeInitializeTimer(ptr)
@ stdcall KeInitializeTimerEx(ptr long)
@ stdcall KeInsertByKeyDeviceQueue(ptr ptr long)
@ stdcall KeInsertDeviceQueue(ptr ptr)
@ stdcall KeInsertHeadQueue(ptr ptr)
@ stdcall KeInsertQueue(ptr ptr)
@ stdcall KeInsertQueueApc(ptr ptr ptr long)
@ stdcall KeInsertQueueDpc(ptr ptr ptr)
@ stdcall KeInvalidateAllCaches()
@ stdcall KeIpiGenericCall(ptr ptr)
@ stdcall KeIsAttachedProcess()
@ stdcall -arch=i386,arm KeIsExecutingDpc()
@ stdcall KeIsWaitListEmpty(ptr)
;@ cdecl -arch=x86_64 KeLastBranchMSR()
@ stdcall KeLeaveCriticalRegion() _KeLeaveCriticalRegion
@ stdcall KeLeaveGuardedRegion() _KeLeaveGuardedRegion
@ extern KeLoaderBlock
@ cdecl -arch=x86_64 -private KeLowerIrql(long) KxLowerIrql
@ extern KeNumberProcessors
@ stdcall -arch=i386,arm KeProfileInterrupt(ptr)
@ stdcall KeProfileInterruptWithSource(ptr long)
@ stdcall KePulseEvent(ptr long long)
@ stdcall -stub -version=0x600+ KeQueryActiveProcessorCount(long)
@ stdcall -stub -version=0x600+ KeQueryActiveProcessorCountEx(long)
@ stdcall KeQueryActiveProcessors()
@ stdcall -arch=i386,arm KeQueryInterruptTime()
;@ cdecl -arch=x86_64 KeQueryMultiThreadProcessorSet
;@ cdecl -arch=x86_64 KeQueryPrcbAddress
@ stdcall KeQueryPriorityThread(ptr)
@ stdcall KeQueryRuntimeThread(ptr ptr)
@ stdcall -arch=i386,arm KeQuerySystemTime(ptr)
@ stdcall -arch=i386,arm KeQueryTickCount(ptr)
@ stdcall KeQueryTimeIncrement()
@ cdecl -arch=x86_64 -private KeRaiseIrqlToDpcLevel() KxRaiseIrqlToDpcLevel
@ stdcall KeRaiseUserException(long)
@ stdcall KeReadStateEvent(ptr)
@ stdcall KeReadStateMutant(ptr)
@ stdcall KeReadStateMutex(ptr) KeReadStateMutant
@ stdcall KeReadStateQueue(ptr)
@ stdcall KeReadStateSemaphore(ptr)
@ stdcall KeReadStateTimer(ptr)
@ stdcall KeRegisterBugCheckCallback(ptr ptr ptr long ptr)
@ stdcall KeRegisterBugCheckReasonCallback(ptr ptr ptr ptr)
@ stdcall KeRegisterNmiCallback(ptr ptr)
@ fastcall KeReleaseGuardedMutex(ptr)
@ fastcall KeReleaseGuardedMutexUnsafe(ptr)
@ cdecl -arch=x86_64 KeReleaseInStackQueuedSpinLock(ptr)
@ fastcall KeReleaseInStackQueuedSpinLockForDpc(ptr)
@ fastcall KeReleaseInStackQueuedSpinLockFromDpcLevel(ptr)
@ stdcall KeReleaseInterruptSpinLock(ptr long)
@ stdcall KeReleaseMutant(ptr long long long)
@ stdcall KeReleaseMutex(ptr long)
@ cdecl -arch=x86_64 KeReleaseQueuedSpinLock(long long)
@ stdcall KeReleaseSemaphore(ptr long long long)
@ stdcall -arch=x86_64 KeReleaseSpinLock(ptr long)
@ fastcall KeReleaseSpinLockForDpc(ptr long)
@ stdcall KeReleaseSpinLockFromDpcLevel(ptr)
@ stdcall KeRemoveByKeyDeviceQueue(ptr long)
@ stdcall KeRemoveByKeyDeviceQueueIfBusy(ptr long)
@ stdcall KeRemoveDeviceQueue(ptr)
@ stdcall KeRemoveEntryDeviceQueue(ptr ptr)
@ stdcall KeRemoveQueue(ptr long ptr)
@ stdcall KeRemoveQueueDpc(ptr)
@ stdcall KeRemoveSystemServiceTable(long)
@ stdcall KeResetEvent(ptr)
@ stdcall -arch=i386 KeRestoreFloatingPointState(ptr)
@ stdcall -arch=x86_64 KeRestoreFloatingPointState(ptr) KxRestoreFloatingPointState
@ stdcall KeRevertToUserAffinityThread()
@ stdcall KeRundownQueue(ptr)
@ stdcall -arch=i386 KeSaveFloatingPointState(ptr)
;@ stdcall -arch=x86_64 KeSaveFloatingPointState(ptr) KxSaveFloatingPointState
@ cdecl KeSaveStateForHibernate(ptr)
@ extern KeServiceDescriptorTable
@ stdcall KeSetAffinityThread(ptr long)
@ stdcall KeSetBasePriorityThread(ptr long)
@ stdcall KeSetDmaIoCoherency(long)
@ stdcall KeSetEvent(ptr long long)
@ stdcall KeSetEventBoostPriority(ptr ptr)
@ stdcall KeSetIdealProcessorThread(ptr long)
@ stdcall KeSetImportanceDpc(ptr long)
@ stdcall KeSetKernelStackSwapEnable(long)
@ stdcall KeSetPriorityThread(ptr long)
@ stdcall KeSetProfileIrql(long)
@ stdcall KeSetSystemAffinityThread(long)
@ stdcall KeSetTargetProcessorDpc(ptr long)
@ stdcall KeSetTimeIncrement(long long)
@ stdcall KeSetTimer(ptr long long ptr)
@ stdcall KeSetTimerEx(ptr long long long ptr)
@ stdcall KeSignalCallDpcDone(ptr)
@ stdcall KeSignalCallDpcSynchronize(ptr)
@ stdcall KeStackAttachProcess(ptr ptr)
@ stdcall KeSynchronizeExecution(ptr ptr ptr)
@ stdcall KeTerminateThread(long)
@ stdcall -version=0x600+ KeTestAlertThread(ptr)
@ fastcall KeTestSpinLock(ptr)
@ extern -arch=i386,arm KeTickCount
@ fastcall KeTryToAcquireGuardedMutex(ptr)
@ cdecl -arch=x86_64 KeTryToAcquireQueuedSpinLock(long long)
@ cdecl -arch=x86_64 KeTryToAcquireQueuedSpinLockRaiseToSynch(long long)
@ fastcall KeTryToAcquireSpinLockAtDpcLevel(ptr)
@ stdcall KeUnstackDetachProcess(ptr)
@ stdcall KeUpdateRunTime(ptr long)
@ fastcall KeUpdateSystemTime(ptr long long)
@ stdcall KeUserModeCallback(long ptr long ptr ptr)
@ stdcall KeWaitForMultipleObjects(long ptr long long long long ptr ptr)
@ stdcall KeWaitForMutexObject(ptr long long long ptr) KeWaitForSingleObject
@ stdcall KeWaitForSingleObject(ptr long long long ptr)
@ fastcall -arch=i386,arm KefAcquireSpinLockAtDpcLevel(ptr)
@ fastcall -arch=i386,arm KefReleaseSpinLockFromDpcLevel(ptr)
@ stdcall -arch=i386 Kei386EoiHelper()
@ cdecl -arch=x86_64 -private KfRaiseIrql(long) KxRaiseIrql
@ fastcall -arch=i386 KiEoiHelper(ptr) #ReactOS-Specific
@ fastcall -arch=i386,arm KiAcquireSpinLock(ptr)
@ extern KiBugCheckData
@ stdcall KiCheckForKernelApcDelivery()
@ fastcall -arch=i386 KiCheckForSListAddress(ptr)
@ stdcall -arch=i386 KiCoprocessorError()
;@ cdecl -arch=x86_64 KiCpuId()
@ stdcall -arch=i386,arm KiDeliverApc(long ptr ptr)
@ stdcall -arch=i386 KiDispatchInterrupt()
@ extern -arch=i386,arm KiEnableTimerWatchdog
@ stdcall -arch=i386,arm KiIpiServiceRoutine(ptr ptr)
@ fastcall -arch=i386,arm KiReleaseSpinLock(ptr)
@ cdecl -arch=i386,arm KiUnexpectedInterrupt()
@ stdcall -arch=i386 Kii386SpinOnSpinLock(ptr long)
@ stdcall LdrAccessResource(ptr ptr ptr ptr)
@ stdcall LdrEnumResources(ptr ptr long ptr ptr)
@ stdcall LdrFindResourceDirectory_U(ptr ptr long ptr)
@ stdcall LdrFindResource_U(ptr ptr long ptr)
@ stdcall -stub -version=0x600+ LdrResFindResource()
@ stdcall -stub -version=0x600+ LdrResFindResourceDirectory()
@ extern LpcPortObjectType
@ stdcall LpcRequestPort(ptr ptr)
@ stdcall LpcRequestWaitReplyPort(ptr ptr ptr)
@ stdcall -version=0x600+ LpcRequestWaitReplyPortEx(ptr ptr ptr)
@ stdcall LsaCallAuthenticationPackage(long long ptr long ptr ptr ptr)
@ stdcall LsaDeregisterLogonProcess(long)
@ stdcall LsaFreeReturnBuffer(ptr)
@ stdcall LsaLogonUser(long ptr long long ptr long ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall LsaLookupAuthenticationPackage(long ptr ptr)
@ stdcall LsaRegisterLogonProcess(ptr ptr ptr)
@ extern Mm64BitPhysicalAddress
@ stdcall MmAddPhysicalMemory(ptr ptr)
@ stdcall MmAddVerifierThunks(ptr long)
@ stdcall MmAdjustWorkingSetSize(long long long long)
@ stdcall MmAdvanceMdl(ptr long)
@ stdcall MmAllocateContiguousMemory(long long long)
@ stdcall MmAllocateContiguousMemorySpecifyCache(long long long long long long long long)
@ stdcall MmAllocateMappingAddress(long long)
@ stdcall MmAllocateNonCachedMemory(long)
@ stdcall MmAllocatePagesForMdl(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall MmAllocatePagesForMdlEx(long long long long long long long long long)
@ stdcall MmBuildMdlForNonPagedPool(ptr)
@ stdcall MmCanFileBeTruncated(ptr ptr)
@ stdcall MmCommitSessionMappedView(ptr ptr)
@ stdcall MmCreateMdl(ptr ptr long)
@ stdcall MmCreateMirror()
@ stdcall MmCreateSection(ptr long ptr ptr long long ptr ptr)
@ stdcall MmDisableModifiedWriteOfSection(long)
@ stdcall MmDoesFileHaveUserWritableReferences(ptr)
@ stdcall MmFlushImageSection(ptr long)
@ stdcall MmForceSectionClosed(ptr long)
@ stdcall MmFreeContiguousMemory(ptr)
@ stdcall MmFreeContiguousMemorySpecifyCache(ptr long long)
@ stdcall MmFreeMappingAddress(ptr long)
@ stdcall MmFreeNonCachedMemory(ptr long)
@ stdcall MmFreePagesFromMdl(ptr)
@ stdcall MmGetPhysicalAddress(ptr)
@ stdcall MmGetPhysicalMemoryRanges()
@ stdcall MmGetSystemRoutineAddress(ptr)
@ stdcall MmGetVirtualForPhysical(long long)
@ stdcall MmGrowKernelStack(ptr)
@ extern MmHighestUserAddress
@ stdcall MmIsAddressValid(ptr)
@ stdcall MmIsDriverVerifying(ptr)
@ stdcall MmIsIoSpaceActive(long long ptr)
@ stdcall MmIsNonPagedSystemAddressValid(ptr)
@ stdcall MmIsRecursiveIoFault()
@ stdcall MmIsThisAnNtAsSystem()
@ stdcall MmIsVerifierEnabled(ptr)
@ stdcall MmLockPagableDataSection(ptr) MmLockPageableDataSection
@ stdcall MmLockPagableImageSection(ptr) MmLockPageableDataSection
@ stdcall MmLockPagableSectionByHandle(ptr) MmLockPageableSectionByHandle
@ stdcall MmMapIoSpace(long long long long)
@ stdcall MmMapLockedPages(ptr long)
@ stdcall MmMapLockedPagesSpecifyCache(ptr long long ptr long long)
@ stdcall MmMapLockedPagesWithReservedMapping(ptr long ptr long)
@ stdcall MmMapMemoryDumpMdl(ptr)
@ stdcall MmMapUserAddressesToPage(ptr long ptr)
@ stdcall MmMapVideoDisplay(long long long long)
@ stdcall MmMapViewInSessionSpace(ptr ptr ptr)
@ stdcall MmMapViewInSystemSpace(ptr ptr ptr)
@ stdcall MmMapViewOfSection(ptr ptr ptr long long ptr ptr long long long)
@ stdcall MmMarkPhysicalMemoryAsBad(ptr ptr)
@ stdcall MmMarkPhysicalMemoryAsGood(ptr ptr)
@ stdcall MmPageEntireDriver(ptr)
@ stdcall MmPrefetchPages(long ptr)
@ stdcall MmProbeAndLockPages(ptr long long)
@ stdcall MmProbeAndLockProcessPages(ptr ptr long long)
@ stdcall MmProbeAndLockSelectedPages(ptr ptr long long)
@ stdcall MmProtectMdlSystemAddress(ptr long)
@ stdcall MmQuerySystemSize()
@ stdcall MmRemovePhysicalMemory(ptr ptr)
@ stdcall MmResetDriverPaging(ptr)
@ extern MmSectionObjectType
@ stdcall MmSecureVirtualMemory(ptr long long)
@ stdcall MmSetAddressRangeModified(ptr long)
@ stdcall MmSetBankedSection(long long long long long long)
@ stdcall MmSizeOfMdl(ptr long)
@ extern MmSystemRangeStart
@ stdcall MmTrimAllSystemPagableMemory(long) MmTrimAllSystemPageableMemory
@ stdcall MmUnlockPagableImageSection(ptr) MmUnlockPageableImageSection
@ stdcall MmUnlockPages(ptr)
@ stdcall MmUnmapIoSpace(ptr long)
@ stdcall MmUnmapLockedPages(ptr ptr)
@ stdcall MmUnmapReservedMapping(ptr long ptr)
@ stdcall MmUnmapVideoDisplay(ptr long)
@ stdcall MmUnmapViewInSessionSpace(ptr)
@ stdcall MmUnmapViewInSystemSpace(ptr)
@ stdcall MmUnmapViewOfSection(ptr ptr)
@ stdcall MmUnsecureVirtualMemory(ptr)
@ extern MmUserProbeAddress
@ extern NlsAnsiCodePage
@ extern NlsLeadByteInfo
@ extern NlsMbCodePageTag
@ extern NlsMbOemCodePageTag
@ extern NlsOemCodePage
@ extern NlsOemLeadByteInfo
@ stdcall NtAddAtom(wstr long ptr)
@ stdcall NtAdjustPrivilegesToken(ptr long ptr long ptr ptr)
@ stdcall NtAllocateLocallyUniqueId(ptr)
@ stdcall NtAllocateUuids(ptr ptr ptr ptr)
@ stdcall NtAllocateVirtualMemory(ptr ptr long ptr long long)
@ stdcall -version=0x600+ NtAlpcCancelMessage(ptr long ptr)
@ stdcall -version=0x600+ NtAlpcConnectPort(ptr wstr ptr ptr long ptr ptr long ptr ptr ptr)
@ stdcall -version=0x600+ NtAlpcCreatePortSection(ptr long ptr long ptr long)
@ stdcall -version=0x600+ NtAlpcCreateResourceReserve(ptr long long ptr)
@ stdcall -version=0x600+ NtAlpcCreateSectionView(ptr long ptr)
@ stdcall -version=0x600+ NtAlpcCreateSecurityContext(ptr long ptr)
@ stdcall -version=0x600+ NtAlpcDeletePortSection(ptr long ptr)
@ stdcall -version=0x600+ NtAlpcDeleteSectionView(ptr long ptr)
@ stdcall -version=0x600+ NtAlpcDeleteSecurityContext(ptr long ptr)
@ stdcall -version=0x600+ NtAlpcDisconnectPort(ptr long)
@ stdcall -version=0x600+ NtAlpcQueryInformation(ptr ptr ptr long long)
@ stdcall -version=0x600+ NtAlpcSendWaitReceivePort(ptr long ptr ptr ptr long ptr ptr)
@ stdcall -version=0x600+ NtAlpcSetInformation(ptr ptr ptr long)
@ extern NtBuildNumber
@ stdcall NtClose(ptr)
@ stdcall NtConnectPort(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall NtCreateEvent(ptr long ptr long long)
@ stdcall NtCreateFile(ptr long ptr ptr ptr long long long long ptr long)
@ stdcall -version=0x600+ NtCreateIoCompletion(ptr long ptr long)
@ stdcall NtCreateSection(ptr long ptr ptr long long ptr)
@ stdcall NtDeleteAtom(ptr)
@ stdcall NtDeleteFile(ptr)
@ stdcall NtDeviceIoControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
@ stdcall NtDuplicateObject(ptr ptr ptr ptr long long long)
@ stdcall NtDuplicateToken(ptr long ptr long long ptr)
@ stdcall NtFindAtom(wstr long ptr)
@ stdcall NtFreeVirtualMemory(ptr ptr ptr long)
@ stdcall NtFsControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
@ extern NtGlobalFlag
@ stdcall -version=0x600+ NtImpersonateAnonymousToken(ptr)
@ stdcall NtLockFile(ptr ptr ptr ptr ptr ptr ptr long long long)
@ stdcall NtMakePermanentObject(ptr)
@ stdcall NtMapViewOfSection(ptr ptr ptr long long ptr ptr long long long)
@ stdcall NtNotifyChangeDirectoryFile(ptr ptr ptr ptr ptr ptr long long long)
@ stdcall NtOpenFile(ptr long ptr ptr long long)
@ stdcall NtOpenProcess(ptr long ptr ptr)
@ stdcall NtOpenProcessToken(ptr long ptr)
@ stdcall NtOpenProcessTokenEx(ptr long long ptr)
@ stdcall NtOpenThread(ptr long ptr ptr)
@ stdcall NtOpenThreadToken(ptr long long ptr)
@ stdcall NtOpenThreadTokenEx(ptr long long long ptr)
@ stdcall NtQueryDirectoryFile(ptr ptr ptr ptr ptr ptr long long long ptr long)
@ stdcall NtQueryEaFile(ptr ptr ptr long long ptr long ptr long)
@ stdcall NtQueryInformationAtom(long long ptr long ptr)
@ stdcall NtQueryInformationFile(ptr ptr ptr long long)
@ stdcall NtQueryInformationProcess(ptr long ptr long ptr)
@ stdcall NtQueryInformationThread(ptr long ptr long ptr)
@ stdcall NtQueryInformationToken(ptr long ptr long ptr)
@ stdcall -version=0x600+ NtQueryLicenseValue(ptr ptr ptr long ptr)
@ stdcall NtQueryQuotaInformationFile(ptr ptr ptr long long ptr long ptr long)
@ stdcall NtQuerySecurityObject(ptr long ptr long ptr)
@ stdcall NtQuerySystemInformation(long ptr long ptr)
@ stdcall NtQueryVolumeInformationFile(ptr ptr ptr long long)
@ stdcall NtReadFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
@ stdcall -version=0x600+ NtRemoveIoCompletionEx(ptr ptr long ptr ptr long)
@ stdcall NtRequestPort(ptr ptr)
@ stdcall NtRequestWaitReplyPort(ptr ptr ptr)
@ stdcall NtSetEaFile(ptr ptr ptr long)
@ stdcall NtSetEvent(ptr ptr)
@ stdcall NtSetInformationFile(ptr ptr ptr long long)
@ stdcall NtSetInformationProcess(ptr long ptr long)
@ stdcall NtSetInformationThread(ptr long ptr long)
@ stdcall NtSetQuotaInformationFile(ptr ptr ptr long)
@ stdcall NtSetSecurityObject(ptr long ptr)
@ stdcall NtSetVolumeInformationFile(ptr ptr ptr long long)
@ stdcall NtShutdownSystem(long)
@ stdcall NtTraceEvent(long long long ptr)
@ stdcall NtUnlockFile(ptr ptr ptr ptr long)
@ stdcall NtVdmControl(long ptr)
@ stdcall NtWaitForSingleObject(ptr long ptr)
@ stdcall NtWriteFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
@ stdcall ObAssignSecurity(ptr ptr ptr ptr)
@ stdcall ObCheckCreateObjectAccess(ptr long ptr ptr long long ptr)
@ stdcall ObCheckObjectAccess(ptr ptr long long ptr)
@ stdcall ObCloseHandle(ptr long)
@ stdcall ObCreateObject(long ptr ptr long ptr long long long ptr)
@ stdcall ObCreateObjectType(ptr ptr ptr ptr)
@ stdcall ObDeleteCapturedInsertInfo(ptr)
@ stdcall ObDereferenceObject(ptr)
@ stdcall ObDereferenceSecurityDescriptor(ptr long)
@ stdcall ObFindHandleForObject(ptr ptr ptr ptr ptr)
@ stdcall ObGetObjectSecurity(ptr ptr ptr)
@ stdcall -version=0x601+ ObGetObjectType(ptr)
@ stdcall ObInsertObject(ptr ptr long long ptr ptr)
@ stdcall ObLogSecurityDescriptor(ptr ptr long)
@ stdcall ObMakeTemporaryObject(ptr)
@ stdcall ObOpenObjectByName(ptr ptr long ptr long ptr ptr)
@ stdcall ObOpenObjectByPointer(ptr long ptr long ptr long ptr)
@ stdcall -version=0x601+ ObQueryNameInfo(ptr)
@ stdcall ObQueryNameString(ptr ptr long ptr)
@ stdcall ObQueryObjectAuditingByHandle(ptr ptr)
@ stdcall ObReferenceObjectByHandle(ptr long ptr long ptr ptr)
@ stdcall ObReferenceObjectByName(ptr long ptr long ptr long ptr ptr)
@ stdcall ObReferenceObjectByPointer(ptr long ptr long)
@ stdcall ObReferenceSecurityDescriptor(ptr long)
@ stdcall ObReleaseObjectSecurity(ptr long)
@ stdcall ObSetHandleAttributes(ptr ptr long)
@ stdcall ObSetSecurityDescriptorInfo(ptr ptr ptr ptr long ptr)
@ stdcall ObSetSecurityObjectByPointer(ptr long ptr)
@ fastcall ObfDereferenceObject(ptr)
@ fastcall ObfReferenceObject(ptr)
@ stdcall PfxFindPrefix(ptr ptr)
@ stdcall PfxInitialize(ptr)
@ stdcall PfxInsertPrefix(ptr ptr ptr)
@ stdcall PfxRemovePrefix(ptr ptr)
@ stdcall PoCallDriver(ptr ptr)
@ stdcall PoCancelDeviceNotify(ptr)
@ stdcall -stub -version=0x600+ PoDisableSleepStates()
@ stdcall PoQueueShutdownWorkItem(ptr)
@ stdcall -stub -version=0x600+ PoReenableSleepStates()
@ stdcall PoRegisterDeviceForIdleDetection(ptr long long long)
@ stdcall PoRegisterDeviceNotify(ptr long long long ptr ptr)
@ stdcall PoRegisterSystemState(ptr long)
@ stdcall PoRequestPowerIrp(ptr long long ptr ptr ptr)
@ stdcall PoRequestShutdownEvent(ptr)
@ stdcall PoSetHiberRange(ptr long ptr long long)
@ stdcall PoSetPowerState(ptr long long)
@ stdcall PoSetSystemState(long)
@ stdcall PoShutdownBugCheck(long long ptr ptr ptr ptr)
@ stdcall PoStartNextPowerIrp(ptr)
@ stdcall PoUnregisterSystemState(ptr)
@ stdcall -stub -version=0x600+ PoUserShutdownInitiated()
@ stdcall ProbeForRead(ptr long long)
@ stdcall ProbeForWrite(ptr long long)
@ stdcall -version=0x600+ PsAcquireProcessExitSynchronization(ptr)
@ stdcall PsAssignImpersonationToken(ptr ptr)
@ stdcall PsChargePoolQuota(ptr long long)
@ stdcall PsChargeProcessNonPagedPoolQuota(ptr long)
@ stdcall PsChargeProcessPagedPoolQuota(ptr long)
@ stdcall PsChargeProcessPoolQuota(ptr long long)
@ stdcall PsCreateSystemProcess(ptr long ptr)
@ stdcall PsCreateSystemThread(ptr long ptr ptr ptr ptr ptr)
@ stdcall PsDereferenceImpersonationToken(ptr) PsDereferencePrimaryToken
@ stdcall PsDereferencePrimaryToken(ptr)
@ stdcall PsDisableImpersonation(ptr ptr)
@ stdcall -version=0x600+ PsEnterPriorityRegion()
@ stdcall PsEstablishWin32Callouts(ptr)
@ stdcall PsGetContextThread(ptr ptr long)
@ stdcall PsGetCurrentProcess() IoGetCurrentProcess
@ stdcall PsGetCurrentProcessId()
@ stdcall PsGetCurrentProcessSessionId()
@ stdcall PsGetCurrentProcessWin32Process()
;@ cdecl -arch=x86_64 PsGetCurrentProcessWow64Process()
@ stdcall PsGetCurrentThread() KeGetCurrentThread
@ stdcall PsGetCurrentThreadId()
@ stdcall PsGetCurrentThreadPreviousMode()
@ stdcall PsGetCurrentThreadProcess()
@ stdcall PsGetCurrentThreadProcessId()
@ stdcall PsGetCurrentThreadStackBase()
@ stdcall PsGetCurrentThreadStackLimit()
@ stdcall PsGetCurrentThreadTeb()
@ stdcall PsGetCurrentThreadWin32Thread()
@ stdcall PsGetCurrentThreadWin32ThreadAndEnterCriticalRegion(ptr)
@ stdcall PsGetJobLock(ptr)
@ stdcall PsGetJobSessionId(ptr)
@ stdcall PsGetJobUIRestrictionsClass(ptr)
@ stdcall PsGetProcessCreateTimeQuadPart(ptr)
@ stdcall PsGetProcessDebugPort(ptr)
@ stdcall PsGetProcessExitProcessCalled(ptr)
@ stdcall PsGetProcessExitStatus(ptr)
@ stdcall PsGetProcessExitTime()
@ stdcall PsGetProcessId(ptr)
@ stdcall PsGetProcessImageFileName(ptr)
@ stdcall PsGetProcessInheritedFromUniqueProcessId(ptr)
@ stdcall PsGetProcessJob(ptr)
@ stdcall PsGetProcessPeb(ptr)
@ stdcall PsGetProcessPriorityClass(ptr)
@ stdcall PsGetProcessSectionBaseAddress(ptr)
@ stdcall PsGetProcessSecurityPort(ptr)
@ stdcall PsGetProcessSessionId(ptr)
@ stdcall PsGetProcessSessionIdEx(ptr)
@ stdcall PsGetProcessWin32Process(ptr)
@ stdcall PsGetProcessWin32WindowStation(ptr)
;@ cdecl -arch=x86_64 PsGetProcessWow64Process()
@ stdcall PsGetThreadFreezeCount(ptr)
@ stdcall PsGetThreadHardErrorsAreDisabled(ptr)
@ stdcall PsGetThreadId(ptr)
@ stdcall PsGetThreadProcess(ptr)
@ stdcall PsGetThreadProcessId(ptr)
@ stdcall PsGetThreadSessionId(ptr)
@ stdcall PsGetThreadTeb(ptr)
@ stdcall PsGetThreadWin32Thread(ptr)
@ stdcall PsGetVersion(ptr ptr ptr ptr)
@ stdcall PsImpersonateClient(ptr ptr long long long)
@ extern PsInitialSystemProcess
@ stdcall PsIsProcessBeingDebugged(ptr)
@ stdcall -version=0x600+ PsIsProtectedProcess(ptr)
@ stdcall PsIsSystemProcess(ptr)
@ stdcall PsIsSystemThread(ptr)
@ stdcall PsIsThreadImpersonating(ptr)
@ stdcall PsIsThreadTerminating(ptr)
@ extern PsJobType
@ stdcall -version=0x600+ PsLeavePriorityRegion()
@ stdcall PsLookupProcessByProcessId(ptr ptr)
@ stdcall PsLookupProcessThreadByCid(ptr ptr ptr)
@ stdcall PsLookupThreadByThreadId(ptr ptr)
@ extern PsProcessType
@ stdcall PsReferenceImpersonationToken(ptr ptr ptr ptr)
@ stdcall PsReferencePrimaryToken(ptr)
@ stdcall -version=0x600+ PsReleaseProcessExitSynchronization(ptr)
@ stdcall PsRemoveCreateThreadNotifyRoutine(ptr)
@ stdcall PsRemoveLoadImageNotifyRoutine(ptr)
@ stdcall PsRestoreImpersonation(ptr ptr)
@ stdcall PsReturnPoolQuota(ptr long long)
@ stdcall PsReturnProcessNonPagedPoolQuota(ptr long)
@ stdcall PsReturnProcessPagedPoolQuota(ptr long)
@ stdcall PsRevertThreadToSelf(ptr)
@ stdcall PsRevertToSelf()
@ stdcall PsSetContextThread(ptr ptr long)
@ stdcall PsSetCreateProcessNotifyRoutine(ptr long)
@ stdcall PsSetCreateThreadNotifyRoutine(ptr)
@ stdcall PsSetJobUIRestrictionsClass(ptr long)
@ stdcall PsSetLegoNotifyRoutine(ptr)
@ stdcall PsSetLoadImageNotifyRoutine(ptr)
@ stdcall PsSetProcessPriorityByClass(ptr ptr)
@ stdcall PsSetProcessPriorityClass(ptr long)
@ stdcall PsSetProcessSecurityPort(ptr ptr)
@ stdcall PsSetProcessWin32Process(ptr ptr ptr)
@ stdcall PsSetProcessWindowStation(ptr ptr)
@ stdcall PsSetThreadHardErrorsAreDisabled(ptr long)
@ stdcall PsSetThreadWin32Thread(ptr ptr ptr)
@ stdcall PsTerminateSystemThread(long)
@ extern PsThreadType
@ stdcall PsWrapApcWow64Thread(ptr ptr)
@ stdcall -arch=i386,arm READ_REGISTER_BUFFER_UCHAR(ptr ptr long)
@ stdcall -arch=i386,arm READ_REGISTER_BUFFER_ULONG(ptr ptr long)
@ stdcall -arch=i386,arm READ_REGISTER_BUFFER_USHORT(ptr ptr long)
@ stdcall -arch=i386,arm READ_REGISTER_UCHAR(ptr)
@ stdcall -arch=i386,arm READ_REGISTER_ULONG(ptr)
@ stdcall -arch=i386,arm READ_REGISTER_USHORT(ptr)
@ stdcall RtlAbsoluteToSelfRelativeSD(ptr ptr ptr)
@ stdcall RtlAddAccessAllowedAce(ptr long long ptr)
@ stdcall RtlAddAccessAllowedAceEx(ptr long long long ptr)
@ stdcall RtlAddAce(ptr long long ptr long)
@ stdcall RtlAddAtomToAtomTable(ptr wstr ptr)
@ stdcall RtlAddRange(ptr long long long long long long ptr ptr)
@ stdcall RtlAllocateHeap(ptr long long)
@ stdcall RtlAnsiCharToUnicodeChar(ptr)
@ stdcall RtlAnsiStringToUnicodeSize(ptr) RtlxAnsiStringToUnicodeSize
@ stdcall RtlAnsiStringToUnicodeString(ptr ptr long)
@ stdcall RtlAppendAsciizToString(ptr str)
@ stdcall RtlAppendStringToString(ptr ptr)
@ stdcall RtlAppendUnicodeStringToString(ptr ptr)
@ stdcall RtlAppendUnicodeToString(ptr wstr)
@ stdcall RtlAreAllAccessesGranted(long long)
@ stdcall RtlAreAnyAccessesGranted(long long)
@ stdcall RtlAreBitsClear(ptr long long)
@ stdcall RtlAreBitsSet(ptr long long)
@ stdcall RtlAssert(str str long str)
@ stdcall RtlCaptureContext(ptr)
@ stdcall RtlCaptureStackBackTrace(long long ptr ptr)
@ stdcall RtlCharToInteger(str long ptr)
@ stdcall RtlCheckRegistryKey(long wstr)
@ stdcall RtlClearAllBits(ptr)
@ stdcall RtlClearBit(ptr long)
@ stdcall RtlClearBits(ptr long long)
@ stdcall RtlCompareMemory(ptr ptr long)
@ stdcall RtlCompareMemoryUlong(ptr long long)
@ stdcall RtlCompareString(ptr ptr long)
@ stdcall RtlCompareUnicodeString(ptr ptr long)
@ stdcall RtlCompressBuffer(long ptr long ptr long long ptr ptr)
@ stdcall RtlCompressChunks(ptr long ptr long ptr long ptr)
@ stdcall RtlConvertLongToLargeInteger(long)
@ stdcall RtlConvertSidToUnicodeString(ptr ptr long)
@ stdcall RtlConvertUlongToLargeInteger(long)
@ stdcall RtlCopyLuid(ptr ptr)
@ stdcall -arch=x86_64 RtlCopyMemory(ptr ptr int64) memmove
@ stdcall -arch=x86_64 RtlCopyMemoryNonTemporal(ptr ptr int64) memmove
@ stdcall RtlCopyRangeList(ptr ptr)
@ stdcall RtlCopySid(long ptr ptr)
@ stdcall RtlCopyString(ptr ptr)
@ stdcall RtlCopyUnicodeString(ptr ptr)
@ stdcall RtlCreateAcl(ptr long long)
@ stdcall RtlCreateAtomTable(long ptr)
@ stdcall RtlCreateHeap(long ptr long long ptr ptr)
@ stdcall RtlCreateRegistryKey(long wstr)
@ stdcall RtlCreateSecurityDescriptor(ptr long)
@ stdcall RtlCreateSystemVolumeInformationFolder(ptr)
@ stdcall RtlCreateUnicodeString(ptr wstr)
@ stdcall RtlCustomCPToUnicodeN(ptr wstr long ptr ptr long)
@ stdcall RtlDecompressBuffer(long ptr long ptr long ptr)
@ stdcall RtlDecompressChunks(ptr long ptr long ptr long ptr)
@ stdcall RtlDecompressFragment(long ptr long ptr long long ptr ptr)
@ stdcall RtlDelete(ptr)
@ stdcall RtlDeleteAce(ptr long)
@ stdcall RtlDeleteAtomFromAtomTable(ptr ptr)
@ stdcall RtlDeleteElementGenericTable(ptr ptr)
@ stdcall RtlDeleteElementGenericTableAvl(ptr ptr)
@ stdcall RtlDeleteNoSplay(ptr ptr)
@ stdcall RtlDeleteOwnersRanges(ptr ptr)
@ stdcall RtlDeleteRange(ptr long long long long ptr)
@ stdcall RtlDeleteRegistryValue(long wstr wstr)
@ stdcall RtlDescribeChunk(long ptr ptr ptr ptr)
@ stdcall RtlDestroyAtomTable(ptr)
@ stdcall RtlDestroyHeap(ptr)
@ stdcall RtlDowncaseUnicodeString(ptr ptr long)
@ stdcall RtlEmptyAtomTable(ptr long)
@ stdcall -arch=win32 RtlEnlargedIntegerMultiply(long long)
@ stdcall -arch=win32 RtlEnlargedUnsignedDivide(long long long ptr)
@ stdcall -arch=win32 RtlEnlargedUnsignedMultiply(long long)
@ stdcall RtlEnumerateGenericTable(ptr long)
@ stdcall RtlEnumerateGenericTableAvl(ptr long)
@ stdcall RtlEnumerateGenericTableLikeADirectory(ptr ptr ptr long ptr ptr ptr)
@ stdcall RtlEnumerateGenericTableWithoutSplaying(ptr ptr)
@ stdcall RtlEnumerateGenericTableWithoutSplayingAvl(ptr ptr)
@ stdcall RtlEqualLuid(ptr ptr)
@ stdcall RtlEqualSid(ptr ptr)
@ stdcall RtlEqualString(ptr ptr long)
@ stdcall RtlEqualUnicodeString(ptr ptr long)
@ stdcall -arch=win32 RtlExtendedIntegerMultiply(long long long)
@ stdcall -arch=win32 RtlExtendedLargeIntegerDivide(long long long ptr)
@ stdcall -arch=win32 RtlExtendedMagicDivide(long long long long long)
@ stdcall RtlFillMemory(ptr long long)
@ stdcall -arch=i386,arm RtlFillMemoryUlong(ptr long long)
@ stdcall RtlFindClearBits(ptr long long)
@ stdcall RtlFindClearBitsAndSet(ptr long long)
@ stdcall RtlFindClearRuns(ptr ptr long long)
@ stdcall RtlFindFirstRunClear(ptr ptr)
@ stdcall RtlFindLastBackwardRunClear(ptr long ptr)
@ stdcall RtlFindLeastSignificantBit(long long)
@ stdcall RtlFindLongestRunClear(ptr ptr)
@ stdcall RtlFindMessage(ptr long long long ptr)
@ stdcall RtlFindMostSignificantBit(long long)
@ stdcall RtlFindNextForwardRunClear(ptr long ptr)
@ stdcall RtlFindRange(ptr long long long long long long long long ptr ptr ptr)
@ stdcall RtlFindSetBits(ptr long long)
@ stdcall RtlFindSetBitsAndClear(ptr long long)
@ stdcall RtlFindUnicodePrefix(ptr ptr long)
@ stdcall RtlFormatCurrentUserKeyPath(ptr)
@ stdcall RtlFreeAnsiString(ptr)
@ stdcall RtlFreeHeap(ptr long ptr)
@ stdcall RtlFreeOemString(ptr)
@ stdcall RtlFreeRangeList(ptr)
@ stdcall RtlFreeUnicodeString(ptr)
@ stdcall RtlGUIDFromString(ptr ptr)
@ stdcall RtlGenerate8dot3Name(ptr ptr long ptr)
@ stdcall RtlGetAce(ptr long ptr)
@ stdcall RtlGetCallersAddress(ptr ptr)
@ stdcall RtlGetCompressionWorkSpaceSize(long ptr ptr)
@ stdcall RtlGetDaclSecurityDescriptor(ptr ptr ptr ptr)
@ stdcall RtlGetDefaultCodePage(ptr ptr)
@ stdcall RtlGetElementGenericTable(ptr long)
@ stdcall RtlGetElementGenericTableAvl(ptr long)
@ stdcall RtlGetFirstRange(ptr ptr ptr)
@ stdcall RtlGetGroupSecurityDescriptor(ptr ptr ptr)
@ stdcall -version=0x600+ RtlGetIntegerAtom(wstr long)
@ stdcall RtlGetNextRange(ptr ptr long)
@ stdcall RtlGetNtGlobalFlags()
@ stdcall RtlGetOwnerSecurityDescriptor(ptr ptr ptr)
@ stdcall RtlGetSaclSecurityDescriptor(ptr ptr ptr ptr)
@ stdcall RtlGetSetBootStatusData(ptr long long ptr long long)
@ stdcall -stub -version=0x600+ RtlGetThreadLangIdByIndex()
@ stdcall RtlGetVersion(ptr)
@ stdcall RtlHashUnicodeString(ptr long long ptr)
@ stdcall RtlImageDirectoryEntryToData(ptr long long ptr)
@ stdcall RtlImageNtHeader(ptr)
@ stdcall RtlInitAnsiString(ptr str)
@ stdcall RtlInitAnsiStringEx(ptr str)
@ stdcall RtlInitCodePageTable(ptr ptr)
@ stdcall RtlInitString(ptr str)
@ stdcall RtlInitUnicodeString(ptr wstr)
@ stdcall RtlInitUnicodeStringEx(ptr wstr)
@ stdcall RtlInitializeBitMap(ptr ptr long)
@ stdcall RtlInitializeGenericTable(ptr ptr ptr ptr ptr)
@ stdcall RtlInitializeGenericTableAvl(ptr ptr ptr ptr ptr)
@ stdcall RtlInitializeRangeList(ptr)
@ stdcall RtlInitializeSid(ptr ptr long)
@ stdcall RtlInitializeUnicodePrefix(ptr)
@ stdcall RtlInsertElementGenericTable(ptr ptr long ptr)
@ stdcall RtlInsertElementGenericTableAvl(ptr ptr long ptr)
@ stdcall RtlInsertElementGenericTableFull(ptr ptr long ptr ptr long)
@ stdcall RtlInsertElementGenericTableFullAvl(ptr ptr long ptr ptr ptr)
@ stdcall RtlInsertUnicodePrefix(ptr ptr ptr)
@ stdcall RtlInt64ToUnicodeString(long long long ptr)
@ stdcall RtlIntegerToChar(long long long ptr)
@ stdcall RtlIntegerToUnicode(long long long ptr)
@ stdcall RtlIntegerToUnicodeString(long long ptr)
@ stdcall RtlInvertRangeList(ptr ptr)
@ stdcall RtlIpv4AddressToStringA(ptr ptr)
@ stdcall RtlIpv4AddressToStringExA(ptr long ptr ptr)
@ stdcall RtlIpv4AddressToStringExW(ptr long ptr ptr)
@ stdcall RtlIpv4AddressToStringW(ptr ptr)
@ stdcall RtlIpv4StringToAddressA(str long ptr ptr)
@ stdcall RtlIpv4StringToAddressExA(str long ptr ptr)
@ stdcall RtlIpv4StringToAddressExW(wstr long ptr ptr)
@ stdcall RtlIpv4StringToAddressW(wstr long ptr ptr)
@ stdcall RtlIpv6AddressToStringA(ptr ptr)
@ stdcall RtlIpv6AddressToStringExA(ptr long long ptr ptr)
@ stdcall RtlIpv6AddressToStringExW(ptr long long ptr ptr)
@ stdcall RtlIpv6AddressToStringW(ptr ptr)
@ stdcall RtlIpv6StringToAddressA(str ptr ptr)
@ stdcall RtlIpv6StringToAddressExA(str ptr ptr ptr)
@ stdcall RtlIpv6StringToAddressExW(wstr ptr ptr ptr)
@ stdcall RtlIpv6StringToAddressW(wstr ptr ptr)
@ stdcall RtlIsGenericTableEmpty(ptr)
@ stdcall RtlIsGenericTableEmptyAvl(ptr)
@ stdcall RtlIsNameLegalDOS8Dot3(ptr ptr ptr)
@ stdcall RtlIsRangeAvailable(ptr long long long long long long ptr ptr ptr)
@ stdcall RtlIsValidOemCharacter(ptr)
@ stdcall -arch=win32 RtlLargeIntegerAdd(long long long long)
@ stdcall -arch=win32 RtlLargeIntegerArithmeticShift(long long long)
@ stdcall -arch=win32 RtlLargeIntegerDivide(long long long long ptr)
@ stdcall -arch=win32 RtlLargeIntegerNegate(long long)
@ stdcall -arch=win32 RtlLargeIntegerShiftLeft(long long long)
@ stdcall -arch=win32 RtlLargeIntegerShiftRight(long long long)
@ stdcall -arch=win32 RtlLargeIntegerSubtract(long long long long)
@ stdcall RtlLengthRequiredSid(long)
@ stdcall RtlLengthSecurityDescriptor(ptr)
@ stdcall RtlLengthSid(ptr)
@ stdcall RtlLockBootStatusData(ptr)
@ stdcall RtlLookupAtomInAtomTable(ptr wstr ptr)
@ stdcall RtlLookupElementGenericTable(ptr ptr)
@ stdcall RtlLookupElementGenericTableAvl(ptr ptr)
@ stdcall RtlLookupElementGenericTableFull(ptr ptr ptr ptr)
@ stdcall RtlLookupElementGenericTableFullAvl(ptr ptr ptr ptr)
@ cdecl -arch=x86_64 RtlLookupFunctionEntry(double ptr ptr)
@ stdcall RtlMapGenericMask(ptr ptr)
@ stdcall RtlMapSecurityErrorToNtStatus(long)
@ stdcall RtlMergeRangeLists(ptr ptr ptr long)
@ stdcall RtlMoveMemory(ptr ptr long)
@ stdcall RtlMultiByteToUnicodeN(ptr long ptr str long)
@ stdcall RtlMultiByteToUnicodeSize(ptr str long)
@ stdcall RtlNextUnicodePrefix(ptr long)
@ stdcall RtlNtStatusToDosError(long)
@ stdcall RtlNtStatusToDosErrorNoTeb(long)
@ stdcall RtlNumberGenericTableElements(ptr)
@ stdcall RtlNumberGenericTableElementsAvl(ptr)
@ stdcall RtlNumberOfClearBits(ptr)
@ stdcall RtlNumberOfSetBits(ptr)
@ stdcall RtlOemStringToCountedUnicodeString(ptr ptr long)
@ stdcall RtlOemStringToUnicodeSize(ptr) RtlxOemStringToUnicodeSize
@ stdcall RtlOemStringToUnicodeString(ptr ptr long)
@ stdcall RtlOemToUnicodeN(wstr long ptr ptr long)
@ cdecl -arch=x86_64 RtlPcToFileHeader(ptr ptr)
@ stdcall RtlPinAtomInAtomTable(ptr ptr)
@ fastcall RtlPrefetchMemoryNonTemporal(ptr long)
@ stdcall RtlPrefixString(ptr ptr long)
@ stdcall RtlPrefixUnicodeString(ptr ptr long)
@ stdcall RtlQueryAtomInAtomTable(ptr ptr ptr ptr ptr ptr)
@ stdcall -version=0x600+ RtlQueryElevationFlags(long)
@ stdcall RtlQueryRegistryValues(long wstr ptr ptr ptr)
@ stdcall RtlQueryTimeZoneInformation(ptr)
@ stdcall RtlRaiseException(ptr)
@ stdcall RtlRandom(ptr)
@ stdcall RtlRandomEx(ptr)
@ stdcall RtlRealPredecessor(ptr)
@ stdcall RtlRealSuccessor(ptr)
@ stdcall RtlRemoveUnicodePrefix(ptr ptr)
@ stdcall RtlReserveChunk(long ptr ptr ptr long)
@ cdecl -arch=x86_64 RtlRestoreContext(ptr ptr)
@ stdcall RtlSecondsSince1970ToTime(long ptr)
@ stdcall RtlSecondsSince1980ToTime(long ptr)
@ stdcall RtlSelfRelativeToAbsoluteSD(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall RtlSelfRelativeToAbsoluteSD2(ptr long)
@ stdcall RtlSetAllBits(ptr)
@ stdcall RtlSetBit(ptr long)
@ stdcall RtlSetBits(ptr long long)
@ stdcall RtlSetDaclSecurityDescriptor(ptr long ptr long)
@ stdcall RtlSetGroupSecurityDescriptor(ptr ptr long)
@ stdcall RtlSetOwnerSecurityDescriptor(ptr ptr long)
@ stdcall RtlSetSaclSecurityDescriptor(ptr long ptr long)
@ stdcall RtlSetTimeZoneInformation(ptr)
@ stdcall RtlSizeHeap(ptr long ptr)
@ stdcall RtlSplay(ptr)
@ stdcall RtlStringFromGUID(ptr ptr)
@ stdcall RtlSubAuthorityCountSid(ptr)
@ stdcall RtlSubAuthoritySid(ptr long)
@ stdcall RtlSubtreePredecessor(ptr)
@ stdcall RtlSubtreeSuccessor(ptr)
@ stdcall RtlTestBit(ptr long)
@ stdcall RtlTimeFieldsToTime(ptr ptr)
@ stdcall RtlTimeToElapsedTimeFields(ptr ptr)
@ stdcall RtlTimeToSecondsSince1970(ptr ptr)
@ stdcall RtlTimeToSecondsSince1980(ptr ptr)
@ stdcall RtlTimeToTimeFields(ptr ptr)
@ stdcall RtlTraceDatabaseAdd(ptr long ptr ptr)
@ stdcall RtlTraceDatabaseCreate(long ptr long long ptr)
@ stdcall RtlTraceDatabaseDestroy(ptr)
@ stdcall RtlTraceDatabaseEnumerate(ptr ptr ptr)
@ stdcall RtlTraceDatabaseFind(ptr long ptr ptr)
@ stdcall RtlTraceDatabaseLock(ptr)
@ stdcall RtlTraceDatabaseUnlock(ptr)
@ stdcall RtlTraceDatabaseValidate(ptr)
@ fastcall -arch=i386,arm RtlUlongByteSwap(long)
@ fastcall -arch=i386,arm RtlUlonglongByteSwap(long long)
@ stdcall RtlUnicodeStringToAnsiSize(ptr) RtlxUnicodeStringToAnsiSize
@ stdcall RtlUnicodeStringToAnsiString(ptr ptr long)
@ stdcall RtlUnicodeStringToCountedOemString(ptr ptr long)
@ stdcall RtlUnicodeStringToInteger(ptr long ptr)
@ stdcall RtlUnicodeStringToOemSize(ptr) RtlxUnicodeStringToOemSize
@ stdcall RtlUnicodeStringToOemString(ptr ptr long)
@ stdcall RtlUnicodeToCustomCPN(ptr ptr long ptr wstr long)
@ stdcall RtlUnicodeToMultiByteN(ptr long ptr wstr long)
@ stdcall RtlUnicodeToMultiByteSize(ptr wstr long)
@ stdcall RtlUnicodeToOemN(ptr long ptr wstr long)
@ stdcall RtlUnlockBootStatusData(ptr)
@ stdcall RtlUnwind(ptr ptr ptr ptr)
@ cdecl -arch=x86_64 RtlUnwindEx(double double ptr ptr ptr ptr)
@ stdcall RtlUpcaseUnicodeChar(long)
@ stdcall RtlUpcaseUnicodeString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeStringToAnsiString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeStringToCountedOemString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeStringToOemString(ptr ptr long)
@ stdcall RtlUpcaseUnicodeToCustomCPN(ptr ptr long ptr wstr long)
@ stdcall RtlUpcaseUnicodeToMultiByteN(ptr long ptr wstr long)
@ stdcall RtlUpcaseUnicodeToOemN(ptr long ptr wstr long)
@ stdcall RtlUpperChar(long)
@ stdcall RtlUpperString(ptr ptr)
@ fastcall -arch=i386,arm RtlUshortByteSwap(long)
@ stdcall RtlValidRelativeSecurityDescriptor(ptr long long)
@ stdcall RtlValidSecurityDescriptor(ptr)
@ stdcall RtlValidSid(ptr)
@ stdcall RtlVerifyVersionInfo(ptr long long long)
@ cdecl -arch=x86_64 RtlVirtualUnwind(long double double ptr ptr ptr ptr ptr)
@ stdcall RtlVolumeDeviceToDosName(ptr ptr) IoVolumeDeviceToDosName
@ stdcall RtlWalkFrameChain(ptr long long)
@ stdcall RtlWriteRegistryValue(long wstr wstr long ptr long)
@ stdcall RtlZeroHeap(ptr long)
@ stdcall RtlZeroMemory(ptr long)
@ stdcall RtlxAnsiStringToUnicodeSize(ptr)
@ stdcall RtlxOemStringToUnicodeSize(ptr)
@ stdcall RtlxUnicodeStringToAnsiSize(ptr)
@ stdcall RtlxUnicodeStringToOemSize(ptr)
@ stdcall SeAccessCheck(ptr ptr ptr long long ptr ptr long ptr ptr)
@ stdcall SeAppendPrivileges(ptr ptr)
@ stdcall SeAssignSecurity(ptr ptr ptr long ptr ptr ptr)
@ stdcall SeAssignSecurityEx(ptr ptr ptr ptr long long ptr ptr ptr)
@ stdcall SeAuditHardLinkCreation(ptr ptr long)
@ stdcall SeAuditingFileEvents(long ptr)
@ stdcall SeAuditingFileEventsWithContext(long ptr ptr)
@ stdcall SeAuditingFileOrGlobalEvents(long ptr ptr)
@ stdcall SeAuditingHardLinkEvents(long ptr)
@ stdcall SeAuditingHardLinkEventsWithContext(long ptr ptr)
@ stdcall SeCaptureSecurityDescriptor(ptr long long long ptr)
@ stdcall SeCaptureSubjectContext(ptr)
@ stdcall SeCloseObjectAuditAlarm(ptr ptr long)
@ stdcall SeCreateAccessState(ptr ptr long ptr)
@ stdcall SeCreateClientSecurity(ptr ptr long ptr)
@ stdcall SeCreateClientSecurityFromSubjectContext(ptr ptr long ptr)
@ stdcall SeDeassignSecurity(ptr)
@ stdcall SeDeleteAccessState(ptr)
@ stdcall SeDeleteObjectAuditAlarm(ptr ptr)
@ extern SeExports
@ stdcall SeFilterToken(ptr long ptr ptr ptr ptr)
@ stdcall SeFreePrivileges(ptr)
@ stdcall SeImpersonateClient(ptr ptr)
@ stdcall SeImpersonateClientEx(ptr ptr)
@ stdcall SeLockSubjectContext(ptr)
@ stdcall SeMarkLogonSessionForTerminationNotification(ptr)
@ stdcall SeOpenObjectAuditAlarm(ptr ptr ptr ptr ptr long long long ptr)
@ stdcall SeOpenObjectForDeleteAuditAlarm(ptr ptr ptr ptr ptr long long long ptr)
@ stdcall SePrivilegeCheck(ptr ptr long)
@ stdcall SePrivilegeObjectAuditAlarm(ptr ptr long ptr long long)
@ extern SePublicDefaultDacl
@ stdcall SeQueryAuthenticationIdToken(ptr ptr)
@ stdcall SeQueryInformationToken(ptr long ptr)
@ stdcall SeQuerySecurityDescriptorInfo(ptr ptr ptr ptr)
@ stdcall SeQuerySessionIdToken(ptr ptr)
@ stdcall SeRegisterLogonSessionTerminatedRoutine(ptr)
@ stdcall SeReleaseSecurityDescriptor(ptr long long)
@ stdcall SeReleaseSubjectContext(ptr)
@ stdcall SeReportSecurityEvent(long ptr ptr ptr)
@ stdcall SeSetAccessStateGenericMapping(ptr ptr)
@ stdcall SeSetAuditParameter(ptr long long ptr)
@ stdcall SeSetSecurityDescriptorInfo(ptr ptr ptr ptr long ptr)
@ stdcall SeSetSecurityDescriptorInfoEx(ptr ptr ptr ptr long long ptr)
@ stdcall SeSinglePrivilegeCheck(long long long)
@ extern SeSystemDefaultDacl
@ stdcall SeTokenImpersonationLevel(ptr)
@ stdcall SeTokenIsAdmin(ptr)
@ stdcall SeTokenIsRestricted(ptr)
@ extern SeTokenObjectType
@ stdcall SeTokenType(ptr)
@ stdcall SeUnlockSubjectContext(ptr)
@ stdcall SeUnregisterLogonSessionTerminatedRoutine(ptr)
@ stdcall SeValidSecurityDescriptor(long ptr)
@ stdcall VerSetConditionMask(long long long long)
@ cdecl VfFailDeviceNode(ptr long long long ptr ptr ptr)
@ cdecl VfFailDriver(long long long ptr ptr ptr)
@ cdecl VfFailSystemBIOS(long long long ptr ptr ptr)
@ stdcall VfIsVerificationEnabled(long ptr)
@ stdcall -arch=i386,arm WRITE_REGISTER_BUFFER_UCHAR(ptr ptr long)
@ stdcall -arch=i386,arm WRITE_REGISTER_BUFFER_ULONG(ptr ptr long)
@ stdcall -arch=i386,arm WRITE_REGISTER_BUFFER_USHORT(ptr ptr long)
@ stdcall -arch=i386,arm WRITE_REGISTER_UCHAR(ptr long)
@ stdcall -arch=i386,arm WRITE_REGISTER_ULONG(ptr long)
@ stdcall -arch=i386,arm WRITE_REGISTER_USHORT(ptr long)
@ stdcall WmiFlushTrace(ptr)
@ fastcall WmiGetClock(long ptr)
@ stdcall WmiQueryTrace(ptr)
@ stdcall WmiQueryTraceInformation(long ptr long ptr ptr)
@ stdcall WmiStartTrace(ptr)
@ stdcall WmiStopTrace(ptr)
@ fastcall WmiTraceFastEvent(ptr)
@ varargs WmiTraceMessage(int64 long ptr long)
@ stdcall WmiTraceMessageVa(int64 long ptr long ptr)
@ stdcall WmiUpdateTrace(ptr)
@ stdcall XIPDispatch(long ptr long)
@ stdcall ZwAccessCheckAndAuditAlarm(ptr ptr ptr ptr ptr long ptr long ptr ptr ptr)
@ stdcall ZwAddBootEntry(ptr long)
@ stdcall ZwAddDriverEntry(ptr long)
@ stdcall ZwAdjustPrivilegesToken(ptr long ptr long ptr ptr)
@ stdcall ZwAlertThread(ptr)
@ stdcall ZwAllocateVirtualMemory(ptr ptr long ptr long long)
@ stdcall -version=0x600+ ZwAlpcCancelMessage(ptr long ptr) NtAlpcCancelMessage
@ stdcall -version=0x600+ ZwAlpcConnectPort(ptr wstr ptr ptr long ptr ptr long ptr ptr ptr) NtAlpcConnectPort
@ stdcall -version=0x600+ ZwAlpcCreatePortSection(ptr long ptr long ptr long) NtAlpcCreatePortSection
@ stdcall -version=0x600+ ZwAlpcCreateResourceReserve(ptr long long ptr) NtAlpcCreateResourceReserve
@ stdcall -version=0x600+ ZwAlpcCreateSectionView(ptr long ptr) NtAlpcCreateSectionView
@ stdcall -version=0x600+ ZwAlpcCreateSecurityContext(ptr long ptr) NtAlpcCreateSecurityContext
@ stdcall -version=0x600+ ZwAlpcDeletePortSection(ptr long ptr) NtAlpcDeletePortSection
@ stdcall -version=0x600+ ZwAlpcDeleteSectionView(ptr long ptr) NtAlpcDeleteSectionView
@ stdcall -version=0x600+ ZwAlpcDeleteSecurityContext(ptr long ptr) NtAlpcDeleteSecurityContext
@ stdcall -version=0x600+ ZwAlpcDisconnectPort(ptr long) NtAlpcDisconnectPort
@ stdcall -version=0x600+ ZwAlpcQueryInformation(ptr ptr ptr long long) NtAlpcQueryInformation
@ stdcall -version=0x600+ ZwAlpcSendWaitReceivePort(ptr long ptr ptr ptr long ptr ptr) NtAlpcSendWaitReceivePort
@ stdcall -version=0x600+ ZwAlpcSetInformation(ptr ptr ptr long) NtAlpcSetInformation
@ stdcall ZwAssignProcessToJobObject(ptr ptr)
@ stdcall ZwCancelIoFile(ptr ptr)
@ stdcall ZwCancelTimer(ptr ptr)
@ stdcall ZwClearEvent(ptr)
@ stdcall ZwClose(ptr)
@ stdcall ZwCloseObjectAuditAlarm(ptr ptr long)
@ stdcall ZwConnectPort(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall ZwCreateDirectoryObject(ptr long ptr)
@ stdcall ZwCreateEvent(ptr long ptr long long)
@ stdcall ZwCreateFile(ptr long ptr ptr ptr long long long long ptr long)
@ stdcall -version=0x600+ ZwCreateIoCompletion(ptr long ptr long) NtCreateIoCompletion
@ stdcall ZwCreateJobObject(ptr long ptr)
@ stdcall ZwCreateKey(ptr long ptr long ptr long ptr)
@ stdcall ZwCreateSection(ptr long ptr ptr long long ptr)
@ stdcall ZwCreateSymbolicLinkObject(ptr long ptr ptr)
@ stdcall ZwCreateTimer(ptr long ptr long)
@ stdcall ZwDeleteBootEntry(long)
@ stdcall ZwDeleteDriverEntry(long)
@ stdcall ZwDeleteFile(ptr)
@ stdcall ZwDeleteKey(ptr)
@ stdcall ZwDeleteValueKey(ptr ptr)
@ stdcall ZwDeviceIoControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
@ stdcall ZwDisplayString(ptr)
@ stdcall ZwDuplicateObject(ptr ptr ptr ptr long long long)
@ stdcall ZwDuplicateToken(ptr long ptr long long ptr)
@ stdcall ZwEnumerateBootEntries(ptr ptr)
@ stdcall ZwEnumerateDriverEntries(ptr ptr)
@ stdcall ZwEnumerateKey(ptr long long ptr long ptr)
@ stdcall ZwEnumerateValueKey(ptr long long ptr long ptr)
@ stdcall ZwFlushInstructionCache(ptr ptr long)
@ stdcall ZwFlushKey(ptr)
@ stdcall ZwFlushVirtualMemory(ptr ptr ptr ptr)
@ stdcall ZwFreeVirtualMemory(ptr ptr ptr long)
@ stdcall ZwFsControlFile(ptr ptr ptr ptr ptr long ptr long ptr long)
@ stdcall -version=0x600+ ZwImpersonateAnonymousToken(ptr) NtImpersonateAnonymousToken
@ stdcall ZwInitiatePowerAction(long long long long)
@ stdcall ZwIsProcessInJob(ptr ptr)
@ stdcall ZwLoadDriver(ptr)
@ stdcall ZwLoadKey(ptr ptr)
@ stdcall ZwMakeTemporaryObject(ptr)
@ stdcall ZwMapViewOfSection(ptr ptr ptr long long ptr ptr long long long)
@ stdcall ZwModifyBootEntry(ptr)
@ stdcall ZwModifyDriverEntry(ptr)
@ stdcall ZwNotifyChangeKey(ptr ptr ptr ptr ptr long long ptr long long)
@ stdcall ZwOpenDirectoryObject(ptr long ptr)
@ stdcall ZwOpenEvent(ptr long ptr)
@ stdcall ZwOpenFile(ptr long ptr ptr long long)
@ stdcall ZwOpenJobObject(ptr long ptr)
@ stdcall ZwOpenKey(ptr long ptr)
@ stdcall ZwOpenProcess(ptr long ptr ptr)
@ stdcall ZwOpenProcessToken(ptr long ptr)
@ stdcall ZwOpenProcessTokenEx(ptr long long ptr)
@ stdcall ZwOpenSection(ptr long ptr)
@ stdcall ZwOpenSymbolicLinkObject(ptr long ptr)
@ stdcall ZwOpenThread(ptr long ptr ptr)
@ stdcall ZwOpenThreadToken(ptr long long ptr)
@ stdcall ZwOpenThreadTokenEx(ptr long long long ptr)
@ stdcall ZwOpenTimer(ptr long ptr)
@ stdcall ZwPowerInformation(long ptr long ptr long)
@ stdcall ZwPulseEvent(ptr ptr)
@ stdcall ZwQueryBootEntryOrder(ptr ptr)
@ stdcall ZwQueryBootOptions(ptr ptr)
@ stdcall ZwQueryDefaultLocale(long ptr)
@ stdcall ZwQueryDefaultUILanguage(ptr)
@ stdcall ZwQueryDirectoryFile(ptr ptr ptr ptr ptr ptr long long long ptr long)
@ stdcall ZwQueryDirectoryObject(ptr ptr long long long ptr ptr)
@ stdcall ZwQueryDriverEntryOrder(ptr ptr)
@ stdcall ZwQueryEaFile(ptr ptr ptr long long ptr long ptr long)
@ stdcall ZwQueryFullAttributesFile(ptr ptr)
@ stdcall ZwQueryInformationFile(ptr ptr ptr long long)
@ stdcall ZwQueryInformationJobObject(ptr long ptr long ptr)
@ stdcall ZwQueryInformationProcess(ptr long ptr long ptr)
@ stdcall ZwQueryInformationThread(ptr long ptr long ptr)
@ stdcall ZwQueryInformationToken(ptr long long long ptr)
@ stdcall ZwQueryInstallUILanguage(ptr)
@ stdcall ZwQueryKey(ptr long ptr long ptr)
@ stdcall -version=0x600+ ZwQueryLicenseValue(ptr ptr ptr long ptr) NtQueryLicenseValue
@ stdcall ZwQueryObject(ptr long ptr long ptr)
@ stdcall ZwQuerySection(ptr long ptr long ptr)
@ stdcall ZwQuerySecurityObject(ptr long ptr long ptr)
@ stdcall ZwQuerySymbolicLinkObject(ptr ptr ptr)
@ stdcall ZwQuerySystemInformation(long ptr long ptr)
@ stdcall ZwQueryValueKey(ptr ptr long ptr long ptr)
@ stdcall ZwQueryVolumeInformationFile(ptr ptr ptr long long)
@ stdcall ZwReadFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
@ stdcall -version=0x600+ ZwRemoveIoCompletionEx(ptr ptr long ptr ptr long) NtRemoveIoCompletionEx
@ stdcall ZwReplaceKey(ptr ptr ptr)
@ stdcall ZwRequestWaitReplyPort(ptr ptr ptr)
@ stdcall ZwResetEvent(ptr ptr)
@ stdcall ZwRestoreKey(ptr ptr long)
@ stdcall ZwSaveKey(ptr ptr)
@ stdcall ZwSaveKeyEx(ptr ptr long)
@ stdcall ZwSecureConnectPort(ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall ZwSetBootEntryOrder(ptr ptr)
@ stdcall ZwSetBootOptions(ptr long)
@ stdcall ZwSetDefaultLocale(long long)
@ stdcall ZwSetDefaultUILanguage(long)
@ stdcall ZwSetDriverEntryOrder(ptr ptr)
@ stdcall ZwSetEaFile(ptr ptr ptr long)
@ stdcall ZwSetEvent(ptr ptr)
@ stdcall ZwSetInformationFile(ptr ptr ptr long long)
@ stdcall ZwSetInformationJobObject(ptr long ptr long)
@ stdcall ZwSetInformationObject(ptr long ptr long)
@ stdcall ZwSetInformationProcess(ptr long ptr long)
@ stdcall ZwSetInformationThread(ptr long ptr long)
@ stdcall ZwSetSecurityObject(ptr long ptr)
@ stdcall ZwSetSystemInformation(long ptr long)
@ stdcall ZwSetSystemTime(ptr ptr)
@ stdcall ZwSetTimer(ptr ptr ptr ptr long long ptr)
@ stdcall ZwSetValueKey(ptr ptr long long ptr long)
@ stdcall ZwSetVolumeInformationFile(ptr ptr ptr long long)
@ stdcall ZwTerminateJobObject(ptr long)
@ stdcall ZwTerminateProcess(ptr long)
@ stdcall ZwTranslateFilePath(ptr long ptr long)
@ stdcall ZwUnloadDriver(ptr)
@ stdcall ZwUnloadKey(ptr)
@ stdcall ZwUnmapViewOfSection(ptr ptr)
@ stdcall ZwWaitForMultipleObjects(long ptr long long ptr)
@ stdcall ZwWaitForSingleObject(ptr long ptr)
@ stdcall ZwWriteFile(ptr ptr ptr ptr ptr ptr long ptr ptr)
@ stdcall ZwYieldExecution()
@ cdecl -arch=x86_64,arm __C_specific_handler(ptr long ptr ptr)
@ cdecl -arch=arm __jump_unwind()
@ cdecl -arch=x86_64 __chkstk()
;@ cdecl -arch=x86_64 __misaligned_access()
@ cdecl -arch=i386 _CIcos()
@ cdecl -arch=i386 _CIsin()
@ cdecl -arch=i386 _CIsqrt()
@ cdecl -arch=i386,arm _abnormal_termination()
@ cdecl -arch=i386 _alldiv()
@ cdecl -arch=i386 _alldvrm()
@ cdecl -arch=i386 _allmul()
@ cdecl -arch=i386 _alloca_probe()
@ cdecl -arch=i386 _allrem()
@ cdecl -arch=i386 _allshl()
@ cdecl -arch=i386 _allshr()
@ cdecl -arch=i386 _aulldiv()
@ cdecl -arch=i386 _aulldvrm()
@ cdecl -arch=i386 _aullrem()
@ cdecl -arch=i386 _aullshr()
@ cdecl -arch=i386,arm _except_handler2()
@ cdecl -arch=i386,arm _except_handler3()
@ cdecl -arch=i386,arm _global_unwind2()
@ cdecl _itoa()
@ cdecl _itow()
@ cdecl -arch=i386,arm _local_unwind2()
@ cdecl -arch=x86_64 _local_unwind()
@ cdecl _purecall()
@ cdecl -arch=x86_64,arm _setjmp(ptr ptr)
@ cdecl -arch=x86_64,arm _setjmpex(ptr ptr)
@ cdecl _snprintf()
@ cdecl _snwprintf()
@ cdecl _stricmp()
@ cdecl _strlwr()
@ cdecl _strnicmp()
@ cdecl _strnset()
@ cdecl _strrev()
@ cdecl _strset()
@ cdecl _strupr()
@ stub swprintf_s
@ cdecl _vsnprintf()
@ cdecl _vsnwprintf()
;@ cdecl -stub -version=0x600+ _vswprintf(ptr wstr ptr)
@ cdecl _wcsicmp()
@ cdecl _wcslwr()
@ cdecl _wcsnicmp()
@ cdecl _wcsnset()
@ cdecl _wcsrev()
@ cdecl _wcsupr()
@ cdecl atoi()
@ cdecl atol()
@ cdecl isdigit()
@ cdecl islower()
@ cdecl isprint()
@ cdecl isspace()
@ cdecl isupper()
@ cdecl isxdigit()
@ cdecl -arch=x86_64,arm longjmp(ptr long)
@ cdecl mbstowcs()
@ cdecl mbtowc()
@ cdecl memchr()
@ cdecl -arch=x86_64 memcmp()
@ cdecl memcpy()
@ cdecl memmove()
@ cdecl memset()
@ cdecl qsort()
@ cdecl rand()
@ varargs sprintf(ptr str)
@ cdecl srand()
@ cdecl strcat()
@ cdecl strchr()
@ cdecl strcmp()
@ cdecl strcpy()
@ cdecl strlen()
@ cdecl strncat()
@ cdecl strncmp()
@ cdecl strncpy()
@ cdecl strrchr()
@ cdecl strspn()
@ cdecl strstr()
@ cdecl swprintf()
;@ varargs -version=0x601+ swprintf_s(ptr long wstr)
@ cdecl tolower()
@ cdecl toupper()
@ cdecl towlower()
@ cdecl towupper()
@ stdcall vDbgPrintEx(long long str ptr)
@ stdcall vDbgPrintExWithPrefix(str long long str ptr)
@ cdecl vsprintf(ptr str ptr)
;@ stub -version=0x601+ vsprintf_s
;@ stub -version=0x600+ vswprintf_s
@ cdecl wcscat()
@ cdecl -version=0x601+ wcscat_s(wstr long wstr)
@ cdecl wcschr()
@ cdecl wcscmp()
@ cdecl wcscpy()
@ cdecl -version=0x601+ wcscpy_s(ptr long wstr)
@ cdecl wcscspn()
@ cdecl wcslen()
@ cdecl wcsncat()
@ cdecl wcsncmp()
@ cdecl wcsncpy()
@ cdecl -version=0x601+ wcsncpy_s(ptr long wstr long)
@ cdecl wcsrchr()
@ cdecl wcsspn()
@ cdecl wcsstr()
@ cdecl wcstombs()
@ cdecl wctomb()

# FIXME: check if this is correct
@ stdcall -arch=arm __dtoi64()
@ stdcall -arch=arm __dtou64()
@ stdcall -arch=arm __i64tod()
@ stdcall -arch=arm __u64tod()
@ stdcall -arch=arm __rt_sdiv()
@ stdcall -arch=arm __rt_sdiv64()
@ stdcall -arch=arm __rt_udiv()
@ stdcall -arch=arm __rt_udiv64()
@ stdcall -arch=arm __rt_srsh()


; The following functions are out of order on purpose
; Please be aware these shouldn't even be called on NTSHIM branch without doing something WEIRD

;@ stub -version=0x602+ BgkDisplayCharacter
;@ stub -version=0x602+ BgkGetConsoleState
;@ stub -version=0x602+ BgkGetCursorState
;@ stub -version=0x602+ BgkSetCursor
;@ stub -version=0x602+ CcAddDirtyPagesToExternalCache
;@ stub -version=0x602+ CcCopyReadEx
;@ stub -version=0x602+ CcCopyWriteEx
;@ stub -version=0x602+ CcDeductDirtyPagesFromExternalCache
;@ stub -version=0x602+ CcFlushCacheToLsn
;@ stub -version=0x602+ CcIsThereDirtyLoggedPages
;@ stub -version=0x602+ CcRegisterExternalCache
;@ stub -version=0x602+ CcScheduleReadAheadEx
;@ stub -version=0x602+ CcSetAdditionalCacheAttributesEx
;@ stub -version=0x602+ CcSetLogHandleForFileEx
;@ stub -version=0x602+ CcSetLoggedDataThreshold
;@ stub -version=0x602+ CcSetReadAheadGranularityEx
;@ stub -version=0x602+ CcUnmapFileOffsetFromSystemCache
;@ stub -version=0x602+ CcUnregisterExternalCache
;@ stub -version=0x602+ CcZeroDataOnDisk
;@ stub -version=0x602+ CmCallbackGetKeyObjectIDEx
;@ stub -version=0x602+ CmCallbackReleaseKeyObjectIDEx
;@ stub -version=0x602+ ExBlockOnAddressPushLock
;;@ stub -version=0x602+ ExBlockPushLock
;@ stub -version=0x602 ExCompositionSurfaceObjectType
;@ stub -version=0x602+ ExGetFirmwareEnvironmentVariable
;@ stub -version=0x602+ ExNotifyBootDeviceRemoval
;@ stub -version=0x602-0xA00 ExQueryFastCacheAppOrigin
;@ stub -version=0x602+ ExQueryFastCacheDevLicense
;@ stub -version=0x602+ ExQueryTimerResolution
;@ stub -version=0x602+ ExQueryWnfStateData
;@ stub -version=0x602+ ExRealTimeIsUniversal
;@ stub -version=0x602+ ExRegisterBootDevice
;@ stub -version=0x602+ ExSetFirmwareEnvironmentVariable
;@ stub -version=0x602+ ExSubscribeWnfStateChange
;@ stub -version=0x602+ ExTimedWaitForUnblockPushLock
;@ stub -version=0x602+ ExTryQueueWorkItem
;@ stub -version=0x602+ ExUnsubscribeWnfStateChange
;;@ stub -version=0x602+ ExWaitForUnblockPushLock
;@ stub -version=0x602+ FsRtlAcquireEofLock
;@ stub -version=0x602+ FsRtlAcquireHeaderMutex
;@ stub -version=0x602+ FsRtlAreThereWaitingFileLocks
;@ stub -version=0x602+ FsRtlCheckLockForOplockRequest
;@ stub -version=0x602+ FsRtlDismountComplete
;@ stub -version=0x602+ FsRtlGetFilenameInformation
;@ stub -version=0x602+ FsRtlGetIoAtEof
;@ stub -version=0x602+ FsRtlGetSectorSizeInformation
;@ stub -version=0x602+ FsRtlGetSupportedFeatures
;@ stub -version=0x602+ FsRtlInitializeEofLock
;@ stub -version=0x602+ FsRtlIsSystemPagingFile
;@ stub -version=0x602+ FsRtlIssueDeviceIoControl
;@ stub -version=0x602+ FsRtlKernelFsControlFile
;@ stub -version=0x602+ FsRtlMdlReadEx
;@ stub -version=0x602+ FsRtlPrepareMdlWriteEx
;@ stub -version=0x602+ FsRtlPrepareToReuseEcp
;@ stub -version=0x602+ FsRtlQueryCachedVdl
;@ stub -version=0x602+ FsRtlQueryKernelEaFile
;@ stub -version=0x602+ FsRtlReleaseEofLock
;@ stub -version=0x602+ FsRtlReleaseFileNameInformation
;@ stub -version=0x602+ FsRtlReleaseHeaderMutex
;@ stub -version=0x602+ FsRtlSetKernelEaFile
;@ stub -version=0x602+ FsRtlTryToAcquireHeaderMutex
;@ stub -version=0x602+ FsRtlUpdateDiskCounters
;@ stub -version=0x602+ HvlGetLpIndexFromApicId
;@ stub -arch=x86_64 -version=0x602+ HvlPerformEndOfInterrupt
;@ stub -version=0x602+ HvlQueryActiveHypervisorProcessorCount
;@ stub -version=0x602+ HvlQueryActiveProcessors
;@ stub -version=0x602+ HvlQueryHypervisorProcessorNodeNumber
;@ stub -version=0x602+ HvlQueryProcessorTopology
;@ stub -version=0x602+ HvlQueryProcessorTopologyCount
;@ stub -version=0x602+ HvlQueryProcessorTopologyHighestId
;@ stub -version=0x602+ HvlRegisterInterruptCallback
;@ stub -version=0x602+ HvlRegisterWheaErrorNotification
;@ stub -version=0x602+ HvlUnregisterInterruptCallback
;@ stub -version=0x602+ HvlUnregisterWheaErrorNotification
;@ stub -version=0x602+ InbvNotifyDisplayOwnershipChange
;@ stub -version=0x602+ IoBoostThreadIo
;@ stub -version=0x602+ IoClearActivityIdThread
;@ stub -version=0x602  IoClearReservedDependency
;@ stub -version=0x602+ IoCompletionObjectType
;@ stub -version=0x602+ IoCopyDeviceObjectHint
;@ stub -version=0x602+ IoCreateStreamFileObjectEx2
;@ stub -version=0x602+ IoCreateSystemThread
;@ stub -version=0x602+ IoDecrementKeepAliveCount
;@ stub -version=0x602+ IoGetActivityIdIrp
;@ stub -version=0x602+ IoGetActivityIdThread
;@ stub -version=0x602+ IoGetDeviceInterfacePropertyData
;@ stub -version=0x602+ IoGetInitiatorProcess
;@ stub -version=0x602+ IoGetOplockKeyContextEx
;@ stub -version=0x602+ IoIncrementKeepAliveCount
;@ stub -version=0x602+ IoInitializeMiniCompletionPacket
;@ stub -version=0x602+ IoIsActivityTracingEnabled
;@ stub -arch=i386 -version=0x602+ IoIsInitiator32bitProcess
;@ stub -version=0x602+ IoIsValidIrpStatus
;@ stub -version=0x602+ IoPropagateActivityIdToThread
;@ stub -version=0x602+ IoQueueWorkItemToNode
;@ stub -version=0x602+ IoRegisterBootDriverCallback
;@ stub -version=0x602+ IoRegisterIoTracking
;@ stub -version=0x602+ IoReportInterruptActive
;@ stub -version=0x602+ IoReportInterruptInactive
;@ stub -version=0x602+ IoReserveDependency
;@ stub -version=0x602+ IoResolveDependency
;@ stub -version=0x602+ IoSetActivityIdIrp
;@ stub -version=0x602+ IoSetActivityIdThread
;@ stub -version=0x602+ IoSetDeviceInterfacePropertyData
;@ stub -version=0x602+ IoSetMasterIrpStatus
;@ stub -version=0x602+ IoSynchronousCallDriver
;@ stub -version=0x602+ IoTransferActivityId
;@ stub -version=0x602+ IoTryQueueWorkItem
;@ stub -version=0x602+ IoUnregisterBootDriverCallback
;@ stub -version=0x602+ IoUnregisterIoTracking
;@ stub -version=0x602+ IoVolumeDeviceToGuid
;@ stub -version=0x602+ IoVolumeDeviceToGuidPath
;@ stub -version=0x602+ KdLogDbgPrint
;@ stdcall -arch=i386 -version=0x602+ KeAcquireSpinLock() hal.KeAcquireSpinLock ;heh, they deprecated hal in NT6.2+, so now we get some free functions :p
;@ stub -version=0x602+ KeDispatchSecondaryInterrupt
;@ stub -version=0x602+ KeForceEnableNx
;@ stub -version=0x602 KeGetNextTimerExpirationDueTime
;@ stub -version=0x602+ KeHwPolicyLocateResource
;@ stub -version=0x602+ KeInitializeSecondaryInterruptServices
;@ stub -version=0x602+ KeLoadMTRR
;@ stub -version=0x602+ KeQueryEffectivePriorityThread
;@ stub -version=0x602+ KeQueryInterruptTimePrecise
;@ stub -version=0x602+ KeQueryTotalCycleTimeThread
;@ stub -version=0x602+ KeStallWhileFrozen
;@ stub -version=0x602+ KeSweepLocalCaches
;@ stub -version=0x602 KeUpdateTime
;@ stub -version=0x602 KeUpdateTimeAssist
;@ stub -version=0x602+ KeWriteProtectPAT
;@ stdcall -arch=i386 -version=0x602+ KfAcquireSpinLock() hal.KfAcquireSpinLock
;@ stdcall -arch=i386 -version=0x602+ KfReleaseSpinLock() hal.KfReleaseSpinLock
;@ stub -arch=i386 -version=0x602+ KiEndThreadAccountingPeriod
;@ stub -arch=i386 -version=0x602+ KiEntropyQueueDpc
;@ stub -version=0x602+ KseQueryDeviceData
;@ stub -version=0x602+ KseQueryDeviceDataList
;@ stub -version=0x602+ KseQueryDeviceFlags
;@ stub -version=0x602+ KseRegisterShim
;@ stub -version=0x602+ KseRegisterShimEx
;@ stub -version=0x602+ KseSetDeviceFlags
;@ stub -version=0x602+ KseUnregisterShim
;@ stub -version=0x602+ MmAllocateContiguousNodeMemory
;@ stub -version=0x602+ MmAllocateMdlForIoSpace
;@ stub -version=0x602+ MmAllocateNodePagesForMdlEx
;@ stub -version=0x602+ MmAreMdlPagesCached
;@ stub -version=0x602+ MmGetMaximumFileSectionSize
;@ stub -version=0x602+ MmIsDriverSuspectForVerifier
;@ stub -version=0x602+ MmMapViewInSessionSpaceEx
;;@ stub -version=0x602+ MmMapViewInSystemSpaceEx
;@ stub -version=0x602+ MmMdlPageContentsState
;@ stub -version=0x602+ MmPrefetchVirtualAddresses
;@ stub -version=0x602+ NtSetInformationVirtualMemory
;;@ stub -version=0x602+ ObDuplicateObject
;;@ stub -version=0x602+ ObReferenceObjectSafe
;@ stub -version=0x602+ ObReferenceObjectSafeWithTag
;@ stub -version=0x602+ ObWaitForMultipleObjects
;@ stub -version=0x602+ ObWaitForSingleObject
;@ stub -version=0x602 PoAllProcessorsDeepIdle
;@ stub -version=0x602+ PoFxCompleteDevicePowerNotRequired
;@ stub -version=0x602+ PoFxCompleteIdleCondition
;@ stub -version=0x602+ PoFxCompleteIdleState
;@ stub -version=0x602+ PoFxIdleComponent
;@ stub -version=0x602+ PoFxNotifySurprisePowerOn
;@ stub -version=0x602+ PoFxPowerControl
;@ stub -version=0x602+ PoFxProcessorNotification
;@ stub -version=0x602+ PoFxRegisterCoreDevice
;@ stub -version=0x602+ PoFxRegisterDevice
;@ stub -version=0x602+ PoFxRegisterPlugin
;@ stub -version=0x602+ PoFxRegisterPluginEx
;@ stub -version=0x602+ PoFxRegisterPrimaryDevice
;@ stub -version=0x602+ PoFxReportDevicePoweredOn
;@ stub -version=0x602+ PoFxSetComponentLatency
;@ stub -version=0x602+ PoFxSetComponentResidency
;@ stub -version=0x602+ PoFxSetComponentWake
;@ stub -version=0x602+ PoFxSetDeviceIdleTimeout
;@ stub -version=0x602+ PoFxStartDevicePowerManagement
;@ stub -version=0x602+ PoFxUnregisterDevice
;@ stub -version=0x602+ PoGetProcessorIdleAccounting
;@ stub -version=0x602+ PoInitiateProcessorWake
;@ stub -version=0x602+ PoLatencySensitivityHint
;@ stub -version=0x602 PoNotifyDisableDynamicTick
;@ stub -version=0x602+ PoNotifyVSyncChange
;@ stub -version=0x602+ PoRegisterCoalescingCallback
;@ stub -version=0x602+ PoSetUserPresent
;@ stub -version=0x602+ PoUnregisterCoalescingCallback
;@ stub -version=0x602+ PoUserShutdownCancelled
;@ stub -version=0x602+ PsChargeProcessWakeCounter
;@ stub -version=0x602+ PsCreateSystemThreadEx
;@ stub -version=0x602+ PsDereferenceKernelStack
;@ stub -version=0x602+ PsGetProcessCommonJob
;@ stub -version=0x602+ PsGetProcessSignatureLevel
;@ stub -version=0x602+ PsGetThreadExitStatus
;@ stub -version=0x602+ PsIsDiskCountersEnabled
;@ stub -version=0x602+ PsQueryProcessAttributesByToken
;@ stub -version=0x602+ PsQueryTotalCycleTimeProcess
;@ stub -version=0x602+ PsReferenceKernelStack
;@ stub -version=0x602+ PsReleaseProcessWakeCounter
;@ stub -version=0x602+ PsUpdateDiskCounters
;@ stub -version=0x602+ RtlAddAtomToAtomTableEx
;@ stub -version=0x602+ RtlAddResourceAttributeAce
;@ stub -version=0x602+ RtlCheckPortableOperatingSystem
;@ stub -version=0x602+ RtlCheckTokenCapability
;@ stub -version=0x602+ RtlCheckTokenMembership
;@ stub -version=0x602+ RtlCheckTokenMembershipEx
;@ stub -version=0x602+ RtlCopyBitMap
;@ stub -version=0x602+ RtlCrc32
;@ stub -version=0x602+ RtlCrc64
;@ stub -version=0x602+ RtlCreateAtomTableEx
;@ stub -version=0x602+ RtlCreateHashTableEx
;;@ stub -version=0x602+ RtlCreateUserThread
;@ stub -version=0x602+ RtlCultureNameToLCID
;@ stub -version=0x602+ RtlDecompressBufferEx
;@ stub -version=0x602+ RtlDeleteElementGenericTableAvlEx
;@ stub -version=0x602+ RtlEqualWnfChangeStamps
;@ stub -version=0x602+ RtlExtractBitMap
;@ stub -version=0x602+ RtlGenerateClass5Guid
;@ stub -version=0x602+ RtlGetAppContainerNamedObjectPath
;@ stub -version=0x602+ RtlIsUntrustedObject
;@ stub -version=0x602+ RtlLCIDToCultureName
;@ stub -version=0x602+ RtlNumberOfClearBitsInRange
;@ stub -version=0x602+ RtlNumberOfSetBitsInRange
;;@ stub -version=0x602+ RtlOpenCurrentUser
;@ stub -version=0x602+ RtlQueryInformationAcl
;@ stub -version=0x602+ RtlQueryPackageIdentity
;@ stub -version=0x602+ RtlQueryRegistryValuesEx
;@ stub -version=0x602+ RtlQueryValidationRunlevel
;@ stub -version=0x602+ RtlRbInsertNodeEx
;@ stub -version=0x602+ RtlRbRemoveNode
;;@ stub -version=0x602+ RtlSetControlSecurityDescriptor
;@ stub -version=0x602+ RtlSetPortableOperatingSystem
;@ stub -version=0x602+ SeAccessCheckFromStateEx
;@ stub -version=0x602+ SeAuditingAnyFileEventsWithContextEx
;@ stub -version=0x602+ SeAuditingFileEventsWithContextEx
;@ stub -version=0x602+ SeCreateClientSecurityFromSubjectContextEx
;@ stub -version=0x602+ SeGetLogonSessionToken
;@ stub -version=0x602+ SeQuerySecureBootPolicyValue
;;@ stub -version=0x602+ SeSystemDefaultSd
;@ stub -version=0x602+ SeTokenFromAccessInformation
;@ stub -version=0x602+ TmInitializeTransactionManager
;@ stub -version=0x602+ TmIsKTMCommitCoordinator
;@ stub -version=0x602+ TmRenameTransactionManager
;@ stub -version=0x602+ TmSinglePhaseReject
;@ stub -arch=x86_64 -version=0x602+ WheaRegisterInUsePageOfflineNotification
;@ stub -arch=x86_64 -version=0x602+ WheaUnregisterInUsePageOfflineNotification
;@ stub -version=0x602+ ZwAlpcConnectPortEx
;@ stub -version=0x602+ ZwCreateWnfStateName
;@ stub -version=0x602+ ZwDeleteWnfStateData
;@ stub -version=0x602+ ZwDeleteWnfStateName
;@ stub -version=0x602+ ZwFlushBuffersFileEx
;@ stub -version=0x602+ ZwQuerySystemEnvironmentValueEx
;@ stub -version=0x602+ ZwQueryWnfStateData
;@ stub -version=0x602+ ZwQueryWnfStateNameInformation
;@ stub -version=0x602+ ZwSetCachedSigningLevel
;@ stub -version=0x602+ ZwSetInformationKey
;@ stub -version=0x602+ ZwSetInformationVirtualMemory
;@ stub -version=0x602+ ZwSetSystemEnvironmentValueExEx
;@ stub -version=0x602+ ZwUpdateWnfStateData
;@ stub -version=0x602+ bsearch_s
;
;# NT6.3 obviously..
;@ stub -version=0x603+ DbgkWerCaptureLiveKernelDump
;@ stub -version=0x603+ ExAcquireCacheAwarePushLockExclusiveEx
;@ stub -version=0x603+ ExAcquireCacheAwarePushLockSharedEx
;@ stub -version=0x603+ ExAcquirePushLockExclusiveEx
;@ stub -version=0x603+ ExAcquirePushLockSharedEx
;@ stub -version=0x603+ ExAllocateTimer
;@ stub -version=0x603+ ExCancelTimer
;@ stub -version=0x603+ ExCompositionObjectType
;@ stub -version=0x603+ ExDeleteTimer
;@ stub -version=0x603+ ExReleaseCacheAwarePushLockExclusiveEx
;@ stub -version=0x603+ ExReleaseCacheAwarePushLockSharedEx
;@ stub -version=0x603+ ExReleasePushLockEx
;@ stub -version=0x603+ ExReleasePushLockExclusiveEx
;@ stub -version=0x603+ ExReleasePushLockSharedEx
;@ stub -version=0x603+ ExSetTimer
;@ stub -version=0x603+ ExTryAcquirePushLockExclusiveEx
;@ stub -version=0x603+ ExTryAcquirePushLockSharedEx
;@ stub -version=0x603+ ExTryConvertPushLockSharedToExclusiveEx
;;@ stub -version=0x603+ ExTryToAcquireResourceExclusiveLite
;@ stub -version=0x603+ ExUnblockOnAddressPushLockEx
;@ stub -version=0x603+ ExUnblockPushLockEx
;@ stub -version=0x603+ FsRtlCheckUpperOplock
;@ stub -version=0x603+ FsRtlHeatInit
;@ stub -version=0x603+ FsRtlHeatLogIo
;@ stub -version=0x603+ FsRtlHeatLogTierMove
;@ stub -version=0x603+ FsRtlHeatUninit
;@ stub -version=0x603-0xA00 FsRtlInsertReservedPerFileContext
;@ stub -version=0x603-0xA00 FsRtlInsertReservedPerStreamContext
;@ stub -version=0x603-0xA00 FsRtlLookupReservedPerFileContext
;@ stub -version=0x603-0xA00 FsRtlLookupReservedPerStreamContext
;@ stub -version=0x603-0xA00 FsRtlRemoveReservedPerFileContext
;@ stub -version=0x603-0xA00 FsRtlRemoveReservedPerStreamContext
;@ stub -version=0x603+ FsRtlSendModernAppTermination
;@ stub -version=0x603+ FsRtlUpperOplockFsctrl
;@ stub -version=0x603+ HvlQueryNumaDistance
;;@ stub -version=0x603+ InterlockedPushListSList
;@ stub -version=0x603+ IoConvertFileHandleToKernelHandle
;@ stub -version=0x603+ IoGetGenericIrpExtension
;@ stub -arch=x86_64 -version=0x603+ IoLoadCrashDumpDriver
;@ stub -version=0x603+ IoPropagateIrpExtension
;@ stub -version=0x603+ IoQueryFullDriverPath
;@ stub -version=0x603+ IoSetGenericIrpExtension
;@ stub -version=0x603+ IoSizeofGenericIrpExtension
;@ stub -version=0x603+ IoTestDependency
;@ stub -version=0x603+ KdAcquireDebuggerLock
;@ stub -version=0x603+ KdDeregisterPowerHandler
;@ stub -version=0x603+ KdRegisterPowerHandler
;@ stub -version=0x603+ KdReleaseDebuggerLock
;@ stub -version=0x603+ KeClockInterruptNotify
;@ stub -version=0x603+ KeClockTimerPowerChange
;@ stub -version=0x603+ KeFindFirstSetRightAffinityEx
;@ stub -version=0x603+ KeGetClockOwner
;@ stub -version=0x603+ KeGetClockTimerResolution
;@ stub -version=0x603+ KeGetNextClockTickDuration
;@ stub -version=0x603+ KeRemoveQueueDpcEx
;@ stub -version=0x603+ KitLogFeatureUsage
;@ stub -version=0x603+ MmCopyMemory
;@ stub -version=0x603+ MmGetCacheAttribute
;@ stub -version=0x603+ MmMdlPagesAreZero
;@ stub -version=0x603+ PoFxPowerOnCrashdumpDevice
;@ stub -version=0x603+ PoFxRegisterCrashdumpDevice
;@ stub -version=0x603+ PsGetProcessProtection
;@ stub -version=0x603+ PsIsProtectedProcessLight
;@ stub -version=0x603+ RtlAvlInsertNodeEx
;@ stub -version=0x603+ RtlAvlRemoveNode
;@ stub -version=0x603+ RtlGetAppContainerParent
;@ stub -version=0x603+ RtlGetAppContainerSidType
;;@ stub -version=0x603+ RtlImageNtHeaderEx
;@ stub -version=0x603+ RtlInterlockedClearBitRun
;@ stub -version=0x603+ RtlInterlockedSetBitRun
;@ stub -version=0x603+ RtlInterlockedSetClearRun
;@ stub -version=0x603+ SeAdjustAccessStateForTrustLabel
;@ stub -version=0x603+ SeGetCachedSigningLevel
;@ stub -version=0x603+ SeIsParentOfChildAppContainer
;@ stub -version=0x603+ SeRegisterImageVerificationCallback
;@ stub -version=0x603+ SeShouldCheckForAccessRightsFromParent
;@ stub -version=0x603+ SeUnregisterImageVerificationCallback
;@ stub -version=0x603+ VfInsertContext
;@ stub -version=0x603+ VfQueryDeviceContext
;@ stub -version=0x603+ VfQueryDispatchTable
;@ stub -version=0x603+ VfQueryDriverContext
;@ stub -version=0x603+ VfQueryIrpContext
;@ stub -version=0x603+ VfQueryThreadContext
;@ stub -version=0x603+ VfRemoveContext
;@ stub -version=0x603+ ZwAssociateWaitCompletionPacket
;@ stub -version=0x603+ ZwCancelIoFileEx
;@ stub -version=0x603+ ZwCreateWaitCompletionPacket
;;@ stub -version=0x603+ ZwLockVirtualMemory
;;@ stub -version=0x603+ ZwProtectVirtualMemory
;@ stdcall -stub -version=0x603+ ZwQuerySystemInformationEx(long ptr long ptr long long)