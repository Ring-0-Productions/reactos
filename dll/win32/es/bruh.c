
/*
 *  Common Dialog Boxes interface (32 bit)
 *  Find/Replace
 *
 * Copyright 1999 Bertho A. Stultiens
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>

#define _INC_WINDOWS
#define COM_NO_WINDOWS_H
#define WIN32_NO_STATUS

#include <windef.h>
#include <winbase.h>
#include <winnls.h>
#include <winreg.h>
#include <winsvc.h>
#include <winuser.h>
#include <debug.h>
static WCHAR ServiceName[] = L"EventSystem";

/***********************************************************************
 *              DllCanUnloadNow (ATL.@)
 */
HRESULT WINAPI DllCanUnloadNow(void)
{
    return S_FALSE;
}

VOID WINAPI
ControlHandler(DWORD request)
{
    switch (request)
    {
        case SERVICE_CONTROL_STOP:
        case SERVICE_CONTROL_SHUTDOWN:
            __debugbreak();
            return;

        default:
            DPRINT1("ControlHandler for ES: Request is %d", request);
            break;
    }
}

/*
 * @unimplemented
 *
 * See https://www.geoffchappell.com/studies/windows/win32/services/svchost/dll/svchostpushserviceglobals.htm
 */
VOID
WINAPI
SvchostPushServiceGlobals(PVOID lpGlobals)
{
  OutputDebugStringW(L"mswsock SvchostPushServiceGlobals stub called\n");
}

VOID WINAPI
ServiceMain(DWORD argc, LPWSTR argv[])
{
    SERVICE_STATUS_HANDLE hStatus;
    hStatus = RegisterServiceCtrlHandlerW(ServiceName,
                                          ControlHandler);
                                          UNREFERENCED_PARAMETER(hStatus);
    DPRINT1("This is from the ES Serivce\r\n!");
}

HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD Reason, LPVOID Reserved)
{
    return TRUE;
}
