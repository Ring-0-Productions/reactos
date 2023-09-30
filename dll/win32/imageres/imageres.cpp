/*
 * PROJECT:     ReactOS imageres.dll
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later)
 * PURPOSE:     imageres.dll
 * COPYRIGHT:   Copyright 2023 Ethan Rodensky <splitwirez@gmail.com>
 */

#include <windef.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>

#include "imageres.h"

BOOL
WINAPI
DllMain(
    _In_ HINSTANCE hInstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpv)
{
    return TRUE;
}
