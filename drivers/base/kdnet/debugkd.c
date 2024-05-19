/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Base functions for the kernel network debugger
 * COPYRIGHT:   Copyright 2009-2016 Timo Kreuzer <timo.kreuzer@reactos.org>
 *              Copyright 2022 Hervé Poussineau <hpoussin@reactos.org>
 */

#define NOEXTAPI
#include <ntifs.h>
#include <windbgkd.h>
#include <arc/arc.h>
#include <kddll.h>
#include <stdio.h>
#include <stdlib.h>
#include "dbgkd.h"

#include <cportlib/cportlib.h>


/* Serial debug connection */
#if defined(SARCH_PC98)
#define DEFAULT_DEBUG_PORT      2 /* COM2 */
#define DEFAULT_DEBUG_COM1_IRQ  4
#define DEFAULT_DEBUG_COM2_IRQ  5
#define DEFAULT_DEBUG_BAUD_RATE 9600
#define DEFAULT_BAUD_RATE       9600
#else
#define DEFAULT_DEBUG_PORT      2 /* COM2 */
#define DEFAULT_DEBUG_COM1_IRQ  4
#define DEFAULT_DEBUG_COM2_IRQ  3
#define DEFAULT_DEBUG_BAUD_RATE 115200
#define DEFAULT_BAUD_RATE       19200
#endif

#if defined(_M_IX86) || defined(_M_AMD64)
#if defined(SARCH_PC98)
const ULONG BaseArray[] = {0, 0x30, 0x238};
#else
const ULONG BaseArray[] = {0, 0x3F8, 0x2F8, 0x3E8, 0x2E8};
#endif
#elif defined(_M_PPC)
const ULONG BaseArray[] = {0, 0x800003F8};
#elif defined(_M_MIPS)
const ULONG BaseArray[] = {0, 0x80006000, 0x80007000};
#elif defined(_M_ARM)
const ULONG BaseArray[] = {0, 0xF1012000};
#else
#error Unknown architecture
#endif

#define MAX_COM_PORTS   (sizeof(BaseArray) / sizeof(BaseArray[0]) - 1)

/* GLOBALS ********************************************************************/

CPPORT KdComPort;
ULONG  KdComPortIrq = 0; // Not used at the moment.
#ifdef KDDEBUG
CPPORT KdDebugComPort;
#endif

VOID
NTAPI
DebugKdNetSendByte(IN UCHAR Byte)
{
    /* Send the byte */
    CpPutByte(&KdComPort, Byte);
}

ULONG KdNetDebugPrint(const char *Format, ...)
{
    va_list ap;
    int Length;
    char* ptr;
    CHAR Buffer[512];

    va_start(ap, Format);
    Length = _vsnprintf(Buffer, sizeof(Buffer), Format, ap);
    va_end(ap);

    /* Check if we went past the buffer */
    if (Length == -1)
    {
        /* Terminate it if we went over-board */
        Buffer[sizeof(Buffer) - 1] = '\n';

        /* Put maximum */
        Length = sizeof(Buffer);
    }

    ptr = Buffer;
    while (Length--)
    {
        if (*ptr == '\n')
            CpPutByte(&KdComPort, '\r');

        CpPutByte(&KdComPort, *ptr++);
    }

    return 0;
}

void
KdpDebgOutput()
{
    CpInitialize(&KdComPort,
                          UlongToPtr(BaseArray[1]),
                          115200);
    KdNetDebugPrint("KdNet Debugger Initialization.... %X\n", 0x12345678);
}