/*
 * PROJECT:     ReactOS Universal Serial Bus Bulk Enhanced Host Controller Interface
 * LICENSE:     GPL - See COPYING in the top level directory
 * FILE:        drivers/usb/hidparse/hidparse.c
 * PURPOSE:     HID Parser
 * PROGRAMMERS:
 *              Michael Martin (michael.martin@reactos.org)
 *              Johannes Anderwald (johannes.anderwald@reactos.org)
 */

#include "hidparse.h"
#include <hidpmem.h>

#define NDEBUG
#include <debug.h>

PVOID
NTAPI
AllocFunction(
    IN ULONG ItemSize)
{
    PVOID Item = ExAllocatePoolWithTag(NonPagedPool, ItemSize, HIDPARSE_TAG);
    if (Item)
    {
        //
        // zero item
        //
        RtlZeroMemory(Item, ItemSize);
    }

    //
    // done
    //
    return Item;
}

VOID
NTAPI
FreeFunction(
    IN PVOID Item)
{
    //
    // free item
    //
    ExFreePoolWithTag(Item, HIDPARSE_TAG);
}

VOID
NTAPI
ZeroFunction(
    IN PVOID Item,
    IN ULONG ItemSize)
{
    //
    // zero item
    //
    RtlZeroMemory(Item, ItemSize);
}

VOID
NTAPI
CopyFunction(
    IN PVOID Target,
    IN PVOID Source,
    IN ULONG Length)
{
    //
    // copy item
    //
    RtlCopyMemory(Target, Source, Length);
}

NTSTATUS
NTAPI
DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegPath)
{
    DPRINT("********* HID PARSE *********\n");
    return STATUS_SUCCESS;
}
