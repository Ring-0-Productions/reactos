
#include <ntdef.h>
#include <ntifs.h>
#include <debug.h>


NTKRNLVISTAAPI
LONG_PTR
FASTCALL
ObfReferenceObjectWithTag(
    _In_ PVOID Object,
    _In_ ULONG Tag)
{
    UNREFERENCED_PARAMETER(Tag);
    UNIMPLEMENTED;
    return ObfReferenceObject(Object);
}

NTKRNLVISTAAPI
LONG_PTR
FASTCALL
ObfDereferenceObjectWithTag(
    _In_ PVOID Object,
    _In_ ULONG Tag)
{
    UNREFERENCED_PARAMETER(Tag);
    UNIMPLEMENTED;
    return ObfDereferenceObject(Object);
}
