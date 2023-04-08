#pragma once
// Standard C-runtime headers
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <initguid.h>
// NTOS headers
#include <ntddk.h>
#ifndef FAR
#define FAR
#endif
// Windows headers
#include <windef.h>
#include <winerror.h>
// Windows GDI headers
#include <wingdi.h>
// Windows DDI headers
//#include <winddi.h>
#include <d3dkmddi.h>
//#include <d3dkmthk.h>
//#include <ntstrsafe.h>
//#include <ntintsafe.h>
#include <dispmprt.h>