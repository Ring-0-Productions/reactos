
@ stdcall InitOnceExecuteOnce(ptr ptr ptr ptr)
@ stdcall InitOnceBeginInitialize(ptr long ptr ptr)
@ stdcall InitOnceComplete(ptr long ptr)
@ stdcall GetFileInformationByHandleEx(long long ptr long)
@ stdcall -ret64 GetTickCount64()

@ stdcall InitializeSRWLock(ptr)
@ stdcall AcquireSRWLockExclusive(ptr)
@ stdcall AcquireSRWLockShared(ptr)
@ stdcall ReleaseSRWLockExclusive(ptr)
@ stdcall ReleaseSRWLockShared(ptr)

@ stdcall InitializeConditionVariable(ptr)
@ stdcall SleepConditionVariableCS(ptr ptr long)
@ stdcall SleepConditionVariableSRW(ptr ptr long long)
@ stdcall WakeAllConditionVariable(ptr)
@ stdcall WakeConditionVariable(ptr)

@ stdcall InitializeCriticalSectionEx(ptr long long)

@ stdcall ApplicationRecoveryFinished(long)
@ stdcall ApplicationRecoveryInProgress(ptr)
@ stdcall CreateSymbolicLinkA(str str long)
@ stdcall CreateSymbolicLinkW(wstr wstr long)
@ stdcall GetApplicationRecoveryCallback(ptr ptr ptr ptr ptr)
@ stdcall GetApplicationRestart(ptr wstr ptr ptr)
@ stdcall GetFileBandwidthReservation(ptr ptr ptr ptr ptr ptr)
@ stdcall GetFileMUIInfo(long wstr ptr ptr)
@ stdcall GetFileMUIPath(long wstr wstr ptr wstr ptr ptr)
@ stdcall GetFinalPathNameByHandleA(ptr str long long)
@ stdcall GetFinalPathNameByHandleW(ptr wstr long long)
@ stdcall GetSystemPreferredUILanguages(long ptr wstr ptr)
@ stdcall GetThreadPreferredUILanguages(long ptr wstr ptr)
@ stdcall GetThreadUILanguage()
@ stdcall GetQueuedCompletionStatusEx(ptr ptr long ptr long long)
@ stdcall GetUILanguageInfo(long wstr wstr ptr ptr)
@ stdcall GetUserPreferredUILanguages(long ptr wstr ptr)
@ stdcall OpenFileById(ptr ptr long long ptr long)
@ stdcall QueryFullProcessImageNameA(ptr long str ptr)
@ stdcall QueryFullProcessImageNameW(ptr long wstr ptr)
@ stdcall RegisterApplicationRecoveryCallback(ptr ptr long long)
@ stdcall RegisterApplicationRestart(wstr long)
@ stdcall ResolveLocaleName(ptr ptr long)
@ stdcall SetFileBandwidthReservation(ptr long long long ptr ptr)
@ stdcall SetThreadPreferredUILanguages(long wstr ptr)
