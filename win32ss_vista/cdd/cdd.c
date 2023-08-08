
#include "cdd.h"
#include <debug.h>

static LOGFONTW SystemFont = { 16, 7, 0, 0, 700, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, L"System" };
static LOGFONTW AnsiVariableFont = { 12, 9, 0, 0, 400, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_DONTCARE, L"MS Sans Serif" };
static LOGFONTW AnsiFixedFont = { 12, 9, 0, 0, 400, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_DONTCARE, L"Courier" };

const PALETTEENTRY BASEPALETTE[20] =
{
   { 0x00, 0x00, 0x00, 0x00 },
   { 0x80, 0x00, 0x00, 0x00 },
   { 0x00, 0x80, 0x00, 0x00 },
   { 0x80, 0x80, 0x00, 0x00 },
   { 0x00, 0x00, 0x80, 0x00 },
   { 0x80, 0x00, 0x80, 0x00 },
   { 0x00, 0x80, 0x80, 0x00 },
   { 0xC0, 0xC0, 0xC0, 0x00 },
   { 0xC0, 0xDC, 0xC0, 0x00 },
   { 0xD4, 0xD0, 0xC8, 0x00 },
   { 0xFF, 0xFB, 0xF0, 0x00 },
   { 0x3A, 0x6E, 0xA5, 0x00 },
   { 0x80, 0x80, 0x80, 0x00 },
   { 0xFF, 0x00, 0x00, 0x00 },
   { 0x00, 0xFF, 0x00, 0x00 },
   { 0xFF, 0xFF, 0x00, 0x00 },
   { 0x00, 0x00, 0xFF, 0x00 },
   { 0xFF, 0x00, 0xFF, 0x00 },
   { 0x00, 0xFF, 0xFF, 0x00 },
   { 0xFF, 0xFF, 0xFF, 0x00 },
};

DWORD
GetAvailableModes(
   HANDLE hDriver,
   PVIDEO_MODE_INFORMATION *ModeInfo,
   DWORD *ModeInfoSize)
{
   UNIMPLEMENTED;
   ULONG ulTemp;
   VIDEO_NUM_MODES Modes;
   PVIDEO_MODE_INFORMATION ModeInfoPtr;

   /*
    * Get the number of modes supported by the mini-port
    */

   if (EngDeviceIoControl(hDriver, IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES, NULL,
                          0, &Modes, sizeof(VIDEO_NUM_MODES), &ulTemp))
   {
      return 0;
   }

   if (Modes.NumModes == 0)
   {
      return 0;
   }

   *ModeInfoSize = Modes.ModeInformationLength;

   /*
    * Allocate the buffer for the miniport to write the modes in.
    */

   *ModeInfo = (PVIDEO_MODE_INFORMATION)EngAllocMem(0, Modes.NumModes *
      Modes.ModeInformationLength, ALLOC_TAG);

   if (*ModeInfo == NULL)
   {
      return 0;
   }
#if 0
   /*
    * Ask the miniport to fill in the available modes.
    */

   if (EngDeviceIoControl(hDriver, IOCTL_VIDEO_QUERY_AVAIL_MODES, NULL, 0,
                          *ModeInfo, Modes.NumModes * Modes.ModeInformationLength,
                          &ulTemp))
   {
      EngFreeMem(*ModeInfo);
      *ModeInfo = NULL;
      return 0;
   }
#endif
   EngFreeMem(*ModeInfo);
    *ModeInfo = NULL;
    return 0;
   /*
    * Now see which of these modes are supported by the display driver.
    * As an internal mechanism, set the length to 0 for the modes we
    * DO NOT support.
    */

   ulTemp = Modes.NumModes;
   ModeInfoPtr = *ModeInfo;

   /*
    * Mode is rejected if it is not one plane, or not graphics, or is not
    * one of 8, 16 or 32 bits per pel.
    */

   while (ulTemp--)
   {
      if ((ModeInfoPtr->NumberOfPlanes != 1) ||
          !(ModeInfoPtr->AttributeFlags & VIDEO_MODE_GRAPHICS) ||
          ((ModeInfoPtr->BitsPerPlane != 8) &&
           (ModeInfoPtr->BitsPerPlane != 16) &&
           (ModeInfoPtr->BitsPerPlane != 24) &&
           (ModeInfoPtr->BitsPerPlane != 32)))
      {
         ModeInfoPtr->Length = 0;
      }

      ModeInfoPtr = (PVIDEO_MODE_INFORMATION)
         (((PUCHAR)ModeInfoPtr) + Modes.ModeInformationLength);
   }

   return Modes.NumModes;
}

BOOL
IntInitScreenInfo(
   PPDEV ppdev,
   LPDEVMODEW pDevMode,
   PGDIINFO pGdiInfo,
   PDEVINFO pDevInfo)
{
   UNIMPLEMENTED;
   __debugbreak();
   return TRUE;
}

BOOL
IntInitDefaultPalette(
   PPDEV ppdev,
   PDEVINFO pDevInfo)
{
   ULONG ColorLoop;
   PPALETTEENTRY PaletteEntryPtr;

   if (ppdev->BitsPerPixel > 8)
   {
      ppdev->DefaultPalette = pDevInfo->hpalDefault =
         EngCreatePalette(PAL_BITFIELDS, 0, NULL,
            ppdev->RedMask, ppdev->GreenMask, ppdev->BlueMask);
   }
   else
   {
      ppdev->PaletteEntries = EngAllocMem(0, sizeof(PALETTEENTRY) << 8, ALLOC_TAG);
      if (ppdev->PaletteEntries == NULL)
      {
         return FALSE;
      }

      for (ColorLoop = 256, PaletteEntryPtr = ppdev->PaletteEntries;
           ColorLoop != 0;
           ColorLoop--, PaletteEntryPtr++)
      {
         PaletteEntryPtr->peRed = ((ColorLoop >> 5) & 7) * 255 / 7;
         PaletteEntryPtr->peGreen = ((ColorLoop >> 3) & 3) * 255 / 3;
         PaletteEntryPtr->peBlue = (ColorLoop & 7) * 255 / 7;
         PaletteEntryPtr->peFlags = 0;
      }

      memcpy(ppdev->PaletteEntries, BASEPALETTE, 10 * sizeof(PALETTEENTRY));
      memcpy(ppdev->PaletteEntries + 246, BASEPALETTE + 10, 10 * sizeof(PALETTEENTRY));

      ppdev->DefaultPalette = pDevInfo->hpalDefault =
         EngCreatePalette(PAL_INDEXED, 256, (PULONG)ppdev->PaletteEntries, 0, 0, 0);
    }

    return ppdev->DefaultPalette != NULL;
}

BOOL APIENTRY
IntSetPalette(
   IN DHPDEV dhpdev,
   IN PPALETTEENTRY ppalent,
   IN ULONG iStart,
   IN ULONG cColors)
{
   UNIMPLEMENTED;
   __debugbreak();
   return TRUE;
}

/* *******************************************************************/
VOID APIENTRY
DrvDisableSurface(
   IN DHPDEV dhpdev)
{
   PPDEV ppdev = (PPDEV)dhpdev;

   EngDeleteSurface(ppdev->hSurfEng);
   ppdev->hSurfEng = NULL;
}

HSURF APIENTRY
DrvEnableSurface(
   IN DHPDEV dhpdev)
{
   PPDEV ppdev = (PPDEV)dhpdev;
   HSURF hSurface;
   ULONG BitmapType;
   SIZEL ScreenSize;
   VIDEO_MEMORY_INFORMATION VideoMemoryInfo;
  // ULONG ulTemp;

   DPRINT1("DrvEnableSurface: Entry\n");
   __debugbreak();

   /*
    * Set the current mode
    */

   /*
    * Map the framebuffer into our memory.
    */

   //TODO: This is just a note, this isn't suppose to be called yet
   VideoMemoryInfo.FrameBufferBase = (PVOID)0x80000000;
#if 0
   if (EngDeviceIoControl(ppdev->hDriver, IOCTL_VIDEO_MAP_VIDEO_MEMORY,
                          &VideoMemory, sizeof(VIDEO_MEMORY),
                          &VideoMemoryInfo, sizeof(VIDEO_MEMORY_INFORMATION),
                          &ulTemp))
   {
      return NULL;
   }
#endif
   ppdev->ScreenPtr = VideoMemoryInfo.FrameBufferBase;

   switch (ppdev->BitsPerPixel)
   {
      case 8:
         IntSetPalette(dhpdev, ppdev->PaletteEntries, 0, 256);
         BitmapType = BMF_8BPP;
         break;

      case 16:
         BitmapType = BMF_16BPP;
         break;

      case 24:
         BitmapType = BMF_24BPP;
         break;

      case 32:
         BitmapType = BMF_32BPP;
         break;

      default:
         return NULL;
   }

   ppdev->iDitherFormat = BitmapType;

   ScreenSize.cx = ppdev->ScreenWidth;
   ScreenSize.cy = ppdev->ScreenHeight;

   hSurface = (HSURF)EngCreateBitmap(ScreenSize, ppdev->ScreenDelta, BitmapType,
                                     (ppdev->ScreenDelta > 0) ? BMF_TOPDOWN : 0,
                                     ppdev->ScreenPtr);
   if (hSurface == NULL)
   {
      return NULL;
   }

   /*
    * Associate the surface with our device.
    */

   if (!EngAssociateSurface(hSurface, ppdev->hDevEng, 0))
   {
      EngDeleteSurface(hSurface);
      return NULL;
   }

   ppdev->hSurfEng = hSurface;

   return hSurface;
}

VOID APIENTRY
DrvMovePointer(
   IN SURFOBJ *pso,
   IN LONG x,
   IN LONG y,
   IN RECTL *prcl)
{
   EngMovePointer(pso, x, y, prcl);
}

BOOL
APIENTRY
DrvIcmSetDeviceGammaRamp(DHPDEV  dhpdev,
                        ULONG   iFormat,
                        LPVOID  lpRamp)
{
   UNIMPLEMENTED;
   return 0;
}

ULONG APIENTRY
DrvSetPointerShape(
   IN SURFOBJ *pso,
   IN SURFOBJ *psoMask,
   IN SURFOBJ *psoColor,
   IN XLATEOBJ *pxlo,
   IN LONG xHot,
   IN LONG yHot,
   IN LONG x,
   IN LONG y,
   IN RECTL *prcl,
   IN FLONG fl)
{
   return EngSetPointerShape(pso, psoMask, psoColor, pxlo, xHot, yHot, x, y, prcl, fl);
}

ULONG
APIENTRY
DrvGetModes(_In_ HANDLE hDriver,
            _In_ ULONG cjSize,
            _Out_ DEVMODEW *pdm)
{
   UNIMPLEMENTED;
   __debugbreak();
   return 1;
}


BOOL
APIENTRY
DrvSetPalette(
   IN DHPDEV dhpdev,
   IN PALOBJ *ppalo,
   IN FLONG fl,
   IN ULONG iStart,
   IN ULONG cColors)
{
   PPALETTEENTRY PaletteEntries;
   BOOL bRet;

   if (cColors == 0)
       return FALSE;

   PaletteEntries = EngAllocMem(0, cColors * sizeof(ULONG), ALLOC_TAG);
   if (PaletteEntries == NULL)
   {
      return FALSE;
   }

   if (PALOBJ_cGetColors(ppalo, iStart, cColors, (PULONG)PaletteEntries) !=
       cColors)
   {
      EngFreeMem(PaletteEntries);
      return FALSE;
   }

   bRet = IntSetPalette(dhpdev, PaletteEntries, iStart, cColors);
   EngFreeMem(PaletteEntries);
   return bRet;
}

DHPDEV
APIENTRY
DrvEnablePDEV(
   IN DEVMODEW *pdm,
   IN LPWSTR pwszLogAddress,
   IN ULONG cPat,
   OUT HSURF *phsurfPatterns,
   IN ULONG cjCaps,
   OUT ULONG *pdevcaps,
   IN ULONG cjDevInfo,
   OUT DEVINFO *pdi,
   IN HDEV hdev,
   IN LPWSTR pwszDeviceName,
   IN HANDLE hDriver)
{
   PPDEV ppdev;
   GDIINFO GdiInfo;
   DEVINFO DevInfo;

   ppdev = EngAllocMem(FL_ZERO_MEMORY, sizeof(PDEV), ALLOC_TAG);
   if (ppdev == NULL)
   {
      return NULL;
   }

   ppdev->hDriver = hDriver;

   if (!IntInitScreenInfo(ppdev, pdm, &GdiInfo, &DevInfo))
   {
      EngFreeMem(ppdev);
      return NULL;
   }

   if (!IntInitDefaultPalette(ppdev, &DevInfo))
   {
      EngFreeMem(ppdev);
      return NULL;
   }

   memcpy(pdi, &DevInfo, min(sizeof(DEVINFO), cjDevInfo));
   memcpy(pdevcaps, &GdiInfo, min(sizeof(GDIINFO), cjCaps));

   return (DHPDEV)ppdev;
}


/*
 * @implemented
 */
VOID APIENTRY
DrvCompletePDEV(
   IN DHPDEV dhpdev,
   IN HDEV hdev)
{
   ((PPDEV)dhpdev)->hDevEng = hdev;
}

/*
 * @implemented
 */
VOID APIENTRY
DrvDisablePDEV(
   IN DHPDEV dhpdev)
{
   if (((PPDEV)dhpdev)->DefaultPalette)
   {
      EngDeletePalette(((PPDEV)dhpdev)->DefaultPalette);
   }

   if (((PPDEV)dhpdev)->PaletteEntries != NULL)
   {
      EngFreeMem(((PPDEV)dhpdev)->PaletteEntries);
   }

   EngFreeMem(dhpdev);
}
