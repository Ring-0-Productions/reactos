
#ifndef _HAL_PCH_
#define _HAL_PCH_

/* INCLUDES ******************************************************************/

/* C Headers */
#include <stdio.h>

/* WDK HAL Compilation hack */
#include <excpt.h>
#include <ntdef.h>

#ifndef _MINIHAL_
  #undef NTSYSAPI
  #define NTSYSAPI __declspec(dllimport)
#else
  #undef NTSYSAPI
  #define NTSYSAPI
#endif

/* IFS/DDK/NDK Headers */
#include <ntifs.h>
#include <arc/arc.h>

#include <ndk/asm.h>
#include <ndk/halfuncs.h>
#include <ndk/inbvfuncs.h>
#include <ndk/iofuncs.h>
#include <ndk/kefuncs.h>
#include <ndk/rtlfuncs.h>

#include <wdmguid.h>

/* Internal shared PCI and ACPI header */
#include <drivers/pci/pci.h>
#include <drivers/acpi/acpi.h>

/* Internal kernel headers */
#define KeGetCurrentThread _KeGetCurrentThread

#ifdef _M_AMD64
  #include <internal/amd64/ke.h>
  #include <internal/amd64/mm.h>
  #include "internal/amd64/intrin_i.h"
#else
  #include <internal/i386/ke.h>
  #include <internal/i386/mm.h>
  #include "internal/i386/intrin_i.h"
#endif

#define TAG_HAL         ' laH'
#define TAG_BUS_HANDLER 'BusH'


#endif /* _HAL_PCH_ */

