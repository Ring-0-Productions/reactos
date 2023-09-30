/*
 * PROJECT:     ReactOS Explorer
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later)
 * PURPOSE:     Notification area
 * COPYRIGHT:   Copyright 2006-2007 Thomas Weidenmueller <w3seek@reactos.org>
 * COPYRIGHT:   Copyright 2018-2022 Ged Murphy <gedmurphy@reactos.org>
 */
#include "precomp.h"
#include <commoncontrols.h>

#ifndef TRAYNTFY_H
#define TRAYNTFY_H


static const WCHAR szTrayNotifyWndClass[] = L"TrayNotifyWnd";

#define TRAY_NOTIFY_WND_SPACING_X   1
#define TRAY_NOTIFY_WND_SPACING_Y   1

/*
 * TrayNotifyWnd
 */

class CTrayNotifyWnd :
    public CComCoClass<CTrayNotifyWnd>,
    public CComObjectRootEx<CComMultiThreadModelNoCS>,
    public CWindowImpl < CTrayNotifyWnd, CWindow, CControlWinTraits >,
    public IOleWindow
{
    CComPtr<IUnknown> m_clock;
public:
    CTrayShowDesktopButton m_ShowDesktopButton;
private:
    CComPtr<IUnknown> m_pager;

    HWND m_hwndClock;
    HWND m_hwndShowDesktop;
    HWND m_hwndPager;

    HTHEME TrayTheme;
    SIZE szTrayClockMin;
    SIZE szTrayShowDesktop;
    SIZE szTrayNotify;
    MARGINS ContentMargin;
    BOOL IsHorizontal;

public:

    CTrayNotifyWnd();
    virtual ~CTrayNotifyWnd();
    LRESULT OnThemeChanged();
    LRESULT OnThemeChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    BOOL GetMinimumSize(IN OUT PSIZE pSize);
    VOID Size(IN OUT SIZE *pszClient);
    VOID AlignControls(IN PRECT prcClient OPTIONAL);
    LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetMinimumSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCtxMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnClockMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnTaskbarSettingsChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnPagerMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnRealign(INT uCode, LPNMHDR hdr, BOOL& bHandled);
    HRESULT WINAPI GetWindow(HWND* phwnd);
    HRESULT WINAPI ContextSensitiveHelp(BOOL fEnterMode);
    HRESULT Initialize(IN HWND hwndParent);

    DECLARE_NOT_AGGREGATABLE(CTrayNotifyWnd)

    DECLARE_PROTECT_FINAL_CONSTRUCT()
    BEGIN_COM_MAP(CTrayNotifyWnd)
        COM_INTERFACE_ENTRY_IID(IID_IOleWindow, IOleWindow)
    END_COM_MAP()

    DECLARE_WND_CLASS_EX(szTrayNotifyWndClass, CS_DBLCLKS, COLOR_3DFACE)

    BEGIN_MSG_MAP(CTrayNotifyWnd)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_THEMECHANGED, OnThemeChanged)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
        MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
        MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnMouseMove)
        MESSAGE_HANDLER(WM_CONTEXTMENU, OnCtxMenu)
        MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK, OnClockMessage)
        MESSAGE_HANDLER(WM_SETFONT, OnClockMessage)
        MESSAGE_HANDLER(WM_SETTINGCHANGE, OnPagerMessage)
        MESSAGE_HANDLER(WM_COPYDATA, OnPagerMessage)
        MESSAGE_HANDLER(TWM_SETTINGSCHANGED, OnTaskbarSettingsChanged)
        NOTIFY_CODE_HANDLER(NTNWM_REALIGN, OnRealign)
        MESSAGE_HANDLER(TNWM_GETMINIMUMSIZE, OnGetMinimumSize)
    END_MSG_MAP()
};

#endif
