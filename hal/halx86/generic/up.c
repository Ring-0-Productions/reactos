/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * FILE:        hal/halx86/generic/up.c
 * PURPOSE:     Core source file for UP alternative functions
 * PROGRAMMERS:  Copyright 2021 Justin Miller <justinmiller100@gmail.com>
 */

/* INCLUDES ******************************************************************/

#include <hal.h>
#define NDEBUG
#include <debug.h>

/* FUNCTIONS *****************************************************************/

VOID
NTAPI
HalRequestIpi(KAFFINITY TargetProcessors)
{
    /* This should never be called in UP mode */
    __debugbreak();
}

BOOLEAN
NTAPI
HalStartNextProcessor(IN PLOADER_PARAMETER_BLOCK LoaderBlock,
                      IN PKPROCESSOR_STATE ProcessorState)
{
    /* Always return false on UP systems */
    return FALSE;
}

#ifndef CONFIG_SMP
VOID
FASTCALL
HalpIpiInterruptHandler(IN PKTRAP_FRAME TrapFrame)
{
    /* DO nothing */
}
#endif