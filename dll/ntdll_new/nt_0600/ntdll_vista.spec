@ stdcall RtlInitializeConditionVariable(ptr)
@ stdcall RtlWakeConditionVariable(ptr)
@ stdcall RtlWakeAllConditionVariable(ptr)
@ stdcall RtlSleepConditionVariableCS(ptr ptr ptr)
@ stdcall RtlSleepConditionVariableSRW(ptr ptr ptr long)
@ stdcall RtlInitializeSRWLock(ptr)
@ stdcall RtlTryAcquireSRWLockExclusive(ptr)
@ stdcall RtlTryAcquireSRWLockShared(ptr)
@ stdcall RtlAcquireSRWLockShared(ptr)
@ stdcall RtlReleaseSRWLockShared(ptr)
@ stdcall RtlAcquireSRWLockExclusive(ptr)
@ stdcall RtlReleaseSRWLockExclusive(ptr)
@ stdcall RtlRunOnceInitialize(ptr)
@ stdcall RtlRunOnceBeginInitialize(ptr long ptr)
@ stdcall RtlRunOnceComplete(ptr long ptr)
@ stdcall RtlRunOnceExecuteOnce(ptr ptr ptr ptr)

@ stdcall TpAllocCleanupGroup(ptr)
@ stdcall TpAllocPool(ptr ptr)
@ stdcall TpAllocTimer(ptr ptr ptr ptr)
@ stdcall TpAllocWait(ptr ptr ptr ptr)
@ stdcall TpAllocWork(ptr ptr ptr ptr)
@ stdcall TpCallbackLeaveCriticalSectionOnCompletion(ptr ptr)
@ stdcall TpCallbackMayRunLong(ptr)
@ stdcall TpCallbackReleaseMutexOnCompletion(ptr long)
@ stdcall TpCallbackReleaseSemaphoreOnCompletion(ptr long long)
@ stdcall TpCallbackSetEventOnCompletion(ptr long)
@ stdcall TpCallbackUnloadDllOnCompletion(ptr ptr)
@ stdcall TpDisassociateCallback(ptr)
@ stdcall TpIsTimerSet(ptr)
@ stdcall TpPostWork(ptr)
@ stdcall TpReleaseCleanupGroup(ptr)
@ stdcall TpReleaseCleanupGroupMembers(ptr long ptr)
@ stdcall TpReleasePool(ptr)
@ stdcall TpReleaseTimer(ptr)
@ stdcall TpReleaseWait(ptr)
@ stdcall TpReleaseWork(ptr)
@ stdcall TpSetPoolMaxThreads(ptr long)
@ stdcall TpSetPoolMinThreads(ptr long)
@ stdcall TpSetTimer(ptr ptr long long)
@ stdcall TpSetWait(ptr long ptr)
@ stdcall TpSimpleTryPost(ptr ptr ptr)
@ stdcall TpWaitForTimer(ptr long)
@ stdcall TpWaitForWait(ptr long)
@ stdcall TpWaitForWork(ptr long)

;@ stdcall RtlConnectToSm(ptr ptr long ptr) SmConnectToSm
;@ stdcall RtlSendMsgToSm(ptr ptr) SmSendMsgToSm
