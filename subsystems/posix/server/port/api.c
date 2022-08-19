/* $Id: api.c,v 1.4 2003/12/21 20:11:46 ea Exp $
 *
 * PROJECT    : ReactOS / POSIX+ Environment Subsystem Server
 * FILE       : reactos/subsys/psx/server/port/api.c
 * DESCRIPTION: \POSIX+\ApiPort LPC port logic.
 * DATE       : 2001-04-04
 * AUTHOR     : Emanuele Aliberti <eal@users.sf.net>
 *
 * --------------------------------------------------------------------
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING. If not, write
 * to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.  
 *
 * --------------------------------------------------------------------
 */
#include "../include/psxss.h"
#include <psx/lpcproto.h>
#include "utils.h"

/**********************************************************************
 *	ProcessConnectionRequest/				PRIVATE
 *
 * DESCRIPTION
 *	This is called when a PSX process attaches to PSXDLL.DLL.
 */
PRIVATE NTSTATUS NTAPI
ProcessConnectionRequest (PLPC_MAX_MESSAGE pRequest)
{
    PPSX_CONNECT_PORT_DATA pConnectData = (PPSX_CONNECT_PORT_DATA) & pRequest->Data;
    NTSTATUS               Status;
    HANDLE                 hConnectedPort;
    ULONG                  ulPortIdentifier;

    debug_print ("PSXSS: ->%s\n", __FUNCTION__);
    /* Check if the caller is a process */
    Status = PsxCheckConnectionRequest (
                pConnectData,
                PSX_CONNECTION_TYPE_PROCESS
		);
    if (!NT_SUCCESS(Status))
    {
        Status = NtAcceptConnectPort (
                    & hConnectedPort,
		    NULL,
		    (PPORT_MESSAGE)& pRequest->Header,
		    FALSE, /* reject connection request */
		    NULL,
		    NULL
		    );
        if (!NT_SUCCESS(Status))
        {
            debug_print("PSXSS: %s: NtAcceptConnectPort failed with status=%08x\n",
                        __FUNCTION__,
                        Status
                        );
        }
        return STATUS_UNSUCCESSFUL;
    }
    /* OK, accept the connection */
    Status = NtAcceptConnectPort (
                & hConnectedPort,
		& ulPortIdentifier,
	        (PPORT_MESSAGE)& pRequest->Header,
		TRUE, /* accept connection request */
		NULL,
		NULL
		);
    if (!NT_SUCCESS(Status))
    {
        debug_print("PSXSS: %s: NtAcceptConnectPort failed with status=%08x\n", __FUNCTION__, Status);
        return Status;
    }
    Status = PsxCreateProcess (pRequest,hConnectedPort,ulPortIdentifier);
    if (!NT_SUCCESS(Status))
    {
        debug_print("PSXSS: %s: PsxCreateProcess failed with status=%08x\n", __FUNCTION__, Status);
        return Status;
    }
    Status = NtCompleteConnectPort (hConnectedPort);
    if (!NT_SUCCESS(Status))
    {
        debug_print("PSXSS: %s: NtCompleteConnectPort failed with status=%08x\n", __FUNCTION__, Status);
        return Status;
    }
    debug_print ("PSXSS: <-%s\n", __FUNCTION__);
    return STATUS_SUCCESS;
}
/**********************************************************************
 *	ProcessRequest/				PRIVATE
 *
 * DESCRIPTION
 *	This is the actual POSIX system calls dispatcher.
 */
PRIVATE NTSTATUS NTAPI
ProcessRequest (PPSX_MAX_MESSAGE pRequest)
{
    debug_print ("PSXSS: ->%s\n", __FUNCTION__);

    if (pRequest->PsxHeader.Procedure < PSX_SYSCALL_APIPORT_COUNT)
    {
        pRequest->PsxHeader.Status =
            SystemCall [pRequest->PsxHeader.Procedure] (pRequest);
    }
    else
    {
        pRequest->PsxHeader.Status = STATUS_INVALID_SYSTEM_SERVICE;
    }
    return STATUS_SUCCESS;
}
/**********************************************************************
 *	ApiPortListener/1
 *
 * DESCRIPTION
 *	The thread to process messages from the \POSIX+\ApiPort
 *	LPC port. Mostly used by PSXDLL.DLL.
 */
ULONG NTAPI
ApiPortListener (PVOID pArg)
{
    ULONG            ulIndex = (ULONG)(ULONG_PTR)pArg;
    NTSTATUS         Status;
    LPC_TYPE         RequestType;
   // ULONG            PortIdentifier;
    PSX_MAX_MESSAGE  Request;
    PPSX_MAX_MESSAGE Reply = NULL;
    BOOL             NullReply = FALSE;

    debug_print ("PSXSS: ->%s pArg=%d\n", __FUNCTION__, ulIndex);

    while (TRUE)
    {
        Reply = NULL;
        NullReply = FALSE;
        while (!NullReply)
        {
            Status = NtReplyWaitReceivePort (
                        Server.Port[ulIndex].hObject,
                        0,
                        (PPORT_MESSAGE)Reply,
                        (PPORT_MESSAGE)& Request);
            if (!NT_SUCCESS(Status))
            {
                break;
            }
            RequestType = (LPC_TYPE)Request.Header.MessageType;
            switch (RequestType)
            {
            case LPC_CONNECTION_REQUEST:
                ProcessConnectionRequest ((PLPC_MAX_MESSAGE) & Request);
                NullReply = TRUE;
                continue;
            case LPC_CLIENT_DIED:
            case LPC_PORT_CLOSED:
            case LPC_DEBUG_EVENT:
            case LPC_ERROR_EVENT:
            case LPC_EXCEPTION:
                NullReply = TRUE;
                continue;
            default:
                if (RequestType != LPC_REQUEST)
                {
                    NullReply = TRUE;
                    continue;
                }
            }
            Reply = & Request;
            Reply->PsxHeader.Status = ProcessRequest (& Request);
            NullReply = FALSE;
        }
        if ((STATUS_INVALID_HANDLE == Status) ||
            (STATUS_OBJECT_TYPE_MISMATCH == Status))
        {
            break;
        }
    }
    NtTerminateThread(NtCurrentThread(),Status);

    return 0;
}
/* EOF */
