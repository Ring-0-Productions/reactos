
BOOL
LdrpCleanupThreadTlsData(VOID)
{
    BOOL Result = TRUE;
    PTLS_VECTOR TargetReclaimTlsVector = NULL;
    PTLS_VECTOR PreviousReclaimVector = NULL;
    const HANDLE CurrentThreadHandle = NtCurrentTeb()->RealClientId.UniqueThread;
   PTLS_RECLAIM_TABLE_ENTRY FoundReclaimEntry = (PTLS_RECLAIM_TABLE_ENTRY)&LdrpDelayedTlsReclaimTable[((ULONG_PTR)CurrentThreadHandle >> 2) & 0xF];
    PTLS_VECTOR CurrentReclaimVector = FoundReclaimEntry->TlsVector;

#if 1
    RtlAcquireSRWLockExclusive(&FoundReclaimEntry->Lock);
#endif

    while (CurrentReclaimVector)
    {
        const PTLS_VECTOR NextReclaimVector = CurrentReclaimVector->PreviousDeferredTlsVector;

        if (CurrentReclaimVector->ThreadId == CurrentThreadHandle)
        {
            if (PreviousReclaimVector)
                PreviousReclaimVector->PreviousDeferredTlsVector = NextReclaimVector;
            else
                FoundReclaimEntry->TlsVector = NextReclaimVector;

            CurrentReclaimVector->PreviousDeferredTlsVector = TargetReclaimTlsVector;
            TargetReclaimTlsVector = CurrentReclaimVector;
            CurrentReclaimVector = PreviousReclaimVector;
        }

        PreviousReclaimVector = CurrentReclaimVector;
        CurrentReclaimVector = NextReclaimVector;
    }

#if 1
    RtlReleaseSRWLockExclusive(&FoundReclaimEntry->Lock);
#endif

    while (TargetReclaimTlsVector)
    {
        const PTLS_VECTOR NextReclaimTlsVector = TargetReclaimTlsVector->PreviousDeferredTlsVector;

        Result = RtlFreeHeap(RtlGetProcessHeap(), 0, TargetReclaimTlsVector);
        TargetReclaimTlsVector = NextReclaimTlsVector;
    }

    return Result;
}