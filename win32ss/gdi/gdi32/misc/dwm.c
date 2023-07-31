#include <precomp.h>
#include <debug.h>

VOID
WINAPI
DwmGetDirtyRgn()
{
    DPRINT1("DwmGetDirtyRgn: Userspace call\n");
    __debugbreak();
}
VOID
WINAPI
DwmGetSurfaceData()
{
    DPRINT1("DwmGetSurfaceData: Userspace call\n");
    __debugbreak();
}
