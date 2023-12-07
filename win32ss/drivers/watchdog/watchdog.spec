@ fastcall WdEnterMonitoredSection(ptr)
@ fastcall WdExitMonitoredSection(ptr)
@ fastcall WdResetDeferredWatch(ptr)
@ fastcall WdResumeDeferredWatch(ptr long)
@ fastcall WdSuspendDeferredWatch(ptr)
@ stdcall WdAllocateDeferredWatchdog(ptr long long)
@ stdcall WdAllocateWatchdog(ptr ptr long)
@ stdcall -version=0x502+ WdAttachContext(ptr long)
@ stdcall WdCompleteEvent(ptr ptr)
@ stdcall -version=0x501 WdDdiWatchdogDpcCallback(ptr ptr ptr ptr)
@ stdcall WdDereferenceObject(ptr)
@ stdcall -version=0x502+ WdDetachContext(ptr)
@ stdcall WdFreeDeferredWatchdog(ptr)
@ stdcall WdFreeWatchdog(ptr)
@ stdcall WdGetDeviceObject(ptr)
@ stdcall WdGetLastEvent(ptr)
@ stdcall WdGetLowestDeviceObject(ptr)
@ stdcall WdMadeAnyProgress(ptr)
@ stdcall WdReferenceObject(ptr)
@ stdcall WdResetWatch(ptr)
@ stdcall WdResumeWatch(ptr long)
@ stdcall WdStartDeferredWatch(ptr ptr long)
@ stdcall WdStartWatch(ptr double ptr)
@ stdcall WdStopDeferredWatch(ptr)
@ stdcall WdStopWatch(ptr long)
@ stdcall WdSuspendWatch(ptr)
@ stdcall -version=0x602+ SMgrNotifySessionChange(long ptr)
@ stdcall -version=0x602+ SMgrRegisterSessionChangeCallout(ptr)
@ stdcall -version=0x602+ SMgrUnregisterSessionChangeCallout(ptr)
@ stdcall -version=0x602+ SMgrGdiCallout(ptr long long ptr ptr ptr)
@ stdcall -version=0x600-0x601 SMgrNotifySessionChange(long)
@ stdcall -version=0x600-0x601 SMgrRegisterGdiCallout(ptr)
@ stdcall -version=0x600-0x601 SMgrRegisterSessionStartCallout(ptr)
@ stdcall -version=0x600-0x601 SMgrUnregisterSessionStartCallout(ptr)
@ stdcall -version=0x600+ SMgrGetActiveSessionProcess()
@ stdcall -version=0x600+ SMgrGetNumberOfSessions()
