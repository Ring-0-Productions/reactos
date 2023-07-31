#include <win32k.h>
//#define NDEBUG
#include <debug.h>

extern PEPROCESS GlobalDwmProcess;

PVOID
APIENTRY
NtGdiDwmGetDirtyRgn(PVOID x1, PVOID x2, PVOID x3, PVOID x4, PVOID x5)
{
    DPRINT1("NtGdiDwmGetDirtyRgn: Has been called - NO idea what's this for\n");
    DPRINT1("Please stop and recoup in the ReactOS Longhorn discord!\n");
    DPRINT1("Param 1: 0x%X\nParam 2: 0x%X\nParam 3: 0x%x\n", x1, x2, x3);
    __debugbreak();
    return NULL;
}

BOOLEAN
APIENTRY
NtGdiDwmGetSurfaceData(PVOID x1, PVOID x2)
{
    DPRINT1("NtGdiDwmGetDirtyRgn: Has been called - NO idea what's this for\n");
    DPRINT1("Please stop and recoup in the ReactOS Longhorn discord!\n");
    DPRINT1("Param 1: 0x%X\nParam 2: 0x%X\n", x1, x2);
    __debugbreak();
    return FALSE;
}
