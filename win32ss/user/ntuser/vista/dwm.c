#include <win32k.h>

#include <debug.h>

PEPROCESS GlobalDwmProcess;
PVOID GlobalDwmApiPort;

/* 
 * NtUserDwmGetDxRgn
 * @ UNIMPLEMENTED
 * UNDOCUMENTED
 */
UINT32
APIENTRY
NtUserDwmGetDxRgn(PVOID x1, PVOID x2, PVOID x3)
{
    DPRINT1("NtUserDwmGetDxRgn: Has been called - NO idea what's this for\n");
    DPRINT1("Please stop and recoup in the ReactOS Longhorn discord!\n");
    DPRINT1("Param 1: 0x%X\nParam 2: 0x%X\nParam 3: 0x%x\n", x1, x2 ,x3);
    __debugbreak();
    return 0;
}

/*
 * NtUserDwmGetDxRgn
 * @ UNIMPLEMENTED
 * UNDOCUMENTED
 */
UINT32
APIENTRY
NtUserDwmHintDxUpdate(PVOID x1, PVOID x2)
{
    DPRINT1("NtUserDwmHintDxUpdate: Has been called - NO idea what's this for\n");
    DPRINT1("Please stop and recoup in the ReactOS Longhorn discord!\n");
    DPRINT1("Param 1: 0x%X\nParam 2: 0x%X\n", x1, x2);
    __debugbreak();
    return 0;
}

PEPROCESS GlobalDwmProcessPtr;
HANDLE GlobalDwmApiPort;

NTSTATUS
InternalDwmStartup()
{

    DPRINT1("Starting DWM Internal\n");
    __debugbreak();
    return 0;
}



/*
 * Ugh the history of this function is fruturating.
 * Acording to PDBs:
 * -> Longhorn 5048: DwmStartup
 * -> Vista RTM:     DwmStartRedirection
 *
 * @ UNIMPLEMENTED
 * UNDOCUMENTED
 * HOWEVER, instead of uDWM triggering the start it's done by dwmapi? i guess?
 *
 * Param 1 i just made match 5048 for now, i don't think it's right.
 */
BOOLEAN
APIENTRY
NtUserDwmStartRedirection(HANDLE Handle)
{
    DPRINT1("NtUserDwmStartRedirection: Enter\n");
    __debugbreak();   
    NTSTATUS Status;
    if ( GlobalDwmProcessPtr )
        return TRUE;

    /* Set the state and reference the handle */
    Status = ObReferenceObjectByHandle(Handle, 0, LpcPortObjectType, 1, &Handle, 0);
    GlobalDwmApiPort = Handle;

    if (Status == STATUS_SUCCESS)
    {
        GlobalDwmProcessPtr = PsGetCurrentProcess();
        Status = InternalDwmStartup();

        if (Status == STATUS_SUCCESS)
            return TRUE;

        /* We failed, let's clean up */
        if (GlobalDwmApiPort)
          ObfDereferenceObject(GlobalDwmApiPort);

        GlobalDwmApiPort = 0;
        GlobalDwmProcessPtr = (PEPROCESS)NULL;
    }

    /* Dwm is not on :( */
    return FALSE;
}

typedef struct _PORT_MESSAGE_HEADER {
  USHORT DataSize;
  USHORT MessageSize;
  USHORT MessageType;
  USHORT VirtualRangesOffset;
  CLIENT_ID ClientId;
  ULONG MessageId;
  ULONG SectionSize;
} PORT_MESSAGE_HEADER, *PPORT_MESSAGE_HEADER;

NTSTATUS
NTAPI
DwmNotifyProtocolChange(USHORT ProtocolType, BOOLEAN bConnect)
{
    NTSTATUS Status = STATUS_UNSUCCESSFUL;
    PORT_MESSAGE Msg = {0};
    
    if(GlobalDwmApiPort != NULL)
    {
        Msg.u1.s1.DataLength = 8;//sizeof(lpc_message); // 8
        Msg.u1.s1.TotalLength = 0x20;// sizeof(PORT_MESSAGE) + sizeof(lpc_message); // 0x20
        Msg.u2.s2.Type = LPC_KERNELMODE_MESSAGE; 
        Msg.MessageId = 0x4000003a; // CallbackId? MessageId?
        
        if(ProtocolType && ProtocolType != 0xFFFF)
        {
            __debugbreak();
            Msg.u2.s2.Type = ProtocolType;
            if(!bConnect)
                Msg.u2.s2.Type = -1;
        }
        
        Status = LpcRequestPort(GlobalDwmApiPort, &Msg);
        if (Status != 0)
        {
            DPRINT("Ahh %X\n", Status);
            __debugbreak();
        }
    }

    return Status;
}

/*
 * Acording to PDBs:
 * -> Longhorn 5048: DwmStop
 * -> Vista RTM:     DwmStopRedirection
 *
 * @ UNIMPLEMENTED
 * UNDOCUMENTED
 */
BOOLEAN
APIENTRY
NtUserDwmStopRedirection(VOID)
{
    NTSTATUS Status;
    BOOLEAN IsRedirectionStopped;

    DPRINT1("NtUserDwmStopRedirection: Has been called\n");
    IsRedirectionStopped = TRUE;


    /* Some kind of internal call here? */
    Status = 1;//IntDwmStopRedirection()

    if (Status != STATUS_SUCCESS)
    {
        IsRedirectionStopped = FALSE;
        DPRINT1("NtUserDwmStopRedirection: Failed to enable redirection Status: 0x%X\n", Status);
    }

    return IsRedirectionStopped;
}
/*
 *  Setup and connect the global DWM port
 *  @ UNIMPLEMENTED
 */
UINT32
APIENTRY
NtUserRegisterSessionPort(HANDLE Handle)
{
    NTSTATUS Status;

    Status = 0;
    if (GlobalDwmProcess)
    {
        DPRINT1("Already Initialized Session Port\n");
        return STATUS_ALREADY_INITIALIZED;
    }

    Status = ObReferenceObjectByHandle(Handle, 1, LpcPortObjectType, 1, &Handle, NULL);
    if (Status != STATUS_SUCCESS)
    {
        DPRINT1("NtUserRegisterSessionPort: ObReferenceObjectByHandle failed with Status: %d\n", Status);
        return Status;
    }
    GlobalDwmApiPort = (PVOID)Handle;
    GlobalDwmProcess = PsGetCurrentProcess();

    Status = ObReferenceObjectByPointer(GlobalDwmProcess, 0x1FFFFFu, (POBJECT_TYPE)PsProcessType, 0);
    if (Status != STATUS_SUCCESS)
    {
        DPRINT1("NtUserRegisterSessionPort: ObReferenceObjectByHandle failed with Status: %d\n", Status);
        return 0;
    }
    //LockObjectAssignment(&grpdeskDwmCouldCompose, *(PVOID *)(v7 + 60));
   DwmNotifyProtocolChange(-1, 1);
    //DwmNotifyProtocolChange(gProtocolType, gbConnected);
    //__debugbreak();
    EngSetLastError(ERROR_SUCCESS);
    return 0;
}
#if 0
INT 
NTAPI
NtUserUpdateWindowTransform(HWND hWnd, D3DMATRIX* pMatrix, BOOL bSetTransform)
{
	BOOL bSuccess = FALSE;

	EnterCrit();
	gbValidateHandleforIL = FALSE;

	INT iLockCount = ThreadLockCount(TRUE);

	WND* pWnd = ValidateHwnd(hWnd);

	if(pWnd)
	{
		// Some reason the third param has to be 1 for this to be valid
		// The parent of the window must also be the desktop?
		if(bSetTransform == TRUE && pWnd->spwndParent == pWnd->head.rpdesk->spwnd)
		{
			// Only the DWM process can set the transform of a window
			if(PsGetCurrentProcess() == gpepDwm)
			{
				bSuccess = TRUE;
				ResetWindowTransform(pWnd);

				// If NULL was passed we were just clearing the transform
				if(pMatrix != NULL)
				{
					D3DMATRIX* pMatrixCopy = (D3DMATRIX*)ExAllocatePoolWithTag(MmNonCached,sizeof(D3DMATRIX), 'Ussy');

					// if pMatrixCopy is NULL then we failed to allocate memory
					if(pMatrixCopy != NULL)
					{
						// Check for overflow and range compliance
						if(pMatrix + sizeof(D3DMATRIX) > W32UserProbeAddress || pMatrix + sizeof(D3DMATRIX) < pMatrix)
							W32UserProbeAddress = 0;

						// Copy the new transform to our newly created object
						memcpy(pMatrixCopy, pMatrix, sizeof(D3DMATRIX));
						
						// Set the window transform at 0xA4 to new transform
						pWnd->pD3dTransformMatrix = pMatrixCopy;
					}
					else
					{
						bSuccess = FALSE;
						UserSetLastError(ERROR_NOT_ENOUGH_MEMORY);
					}
				}
			}
			else
			{
				UserSetLastError(ERROR_ACCESS_DENIED);
			}
		}
		else
		{
			UserSetLastError(ERROR_INVALID_PARAMETER);
		}
	}

	ThreadLockCheck(iLockCount);
	LeaveCrit();

	return bSuccess;
}
#endif