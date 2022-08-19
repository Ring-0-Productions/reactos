/* $Id: sbapi.c,v 1.4 2003/12/21 20:11:46 ea Exp $
 *
 * PROJECT    : ReactOS / POSIX+ Environment Subsystem Server
 * FILE       : reactos/subsys/psx/server/port/sbapi.c
 * DESCRIPTION: \POSIX+\SbApiPort LPC logic.
 * DATE       : 2001-03-23
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
#include "utils.h"


/**********************************************************************
 *	ProcessConnectionRequest/				PRIVATE
 */
PRIVATE NTSTATUS NTAPI
ProcessConnectionRequest (PPSX_MESSAGE pRequest)
{
    return STATUS_NOT_IMPLEMENTED;
}
#if 0
/**********************************************************************
 *	ProcessRequest/				PRIVATE
 */
PRIVATE NTSTATUS NTAPI
ProcessRequest (PPSX_MESSAGE pRequest)
{
    return STATUS_NOT_IMPLEMENTED;
}
#endif
/**********************************************************************
 *	SbApiPortListener/1
 *
 * DESCRIPTION
 *	The \POSIX+\SbApiPort LPC port message dispatcher.
 *
 * NOTE
 *	what is this port for? Is "Sb" for "shared block"?
 */
ULONG NTAPI
SbApiPortListener (PVOID pArg)
{
    NTSTATUS         Status;
    Status = 0;
   // ULONG            PortIdentifier;
    PSX_MAX_MESSAGE  Request;
    //PPSX_MAX_MESSAGE Reply = NULL;

    debug_print ("PSXSS: ->%s pArg=%d\n", __FUNCTION__, (ULONG) pArg);

    RtlZeroMemory (& Request, sizeof Request);
    /* TODO */
    NtTerminateThread(NtCurrentThread(),Status);

    return 0;
}
/* EOF */
