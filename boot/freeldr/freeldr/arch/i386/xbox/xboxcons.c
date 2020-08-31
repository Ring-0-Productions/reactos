/*
 *  FreeLoader
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <freeldr.h>

#include <debug.h>
DBG_DEFAULT_CHANNEL(HWDETECT);

static unsigned CurrentCursorX = 0;
static unsigned CurrentCursorY = 0;
static unsigned CurrentAttr = 0x0f;
extern PCROMWELL_CALLBACK BiosCallback;

VOID
XboxConsPutChar(int c)
{
    ULONG Width, Height, Unused;
    BOOLEAN NeedScroll;

    XboxVideoGetDisplaySize(&Width, &Height, &Unused);

    NeedScroll = (CurrentCursorY >= Height);
    if (NeedScroll)
    {
        XboxVideoScrollUp();
        --CurrentCursorY;
    }

    if (c == '\r')
    {
        CurrentCursorX = 0;
    }
    else if (c == '\n')
    {
        CurrentCursorX = 0;

        if (!NeedScroll)
            ++CurrentCursorY;
    }
    else if (c == '\t')
    {
        CurrentCursorX = (CurrentCursorX + 8) & ~ 7;
    }
    else
    {
        XboxVideoPutChar(c, CurrentAttr, CurrentCursorX, CurrentCursorY);
        CurrentCursorX++;
    }

    if (CurrentCursorX >= Width)
    {
        CurrentCursorX = 0;
        CurrentCursorY++;
    }
}

BOOLEAN
XboxConsKbHit(VOID)
{
    if (!BiosCallback)
        return FALSE;
    return (BiosCallback(CROMWELL_CALLBACK_CHECK_KEY, NULL) == 1);
}

int
XboxConsGetCh(void)
{
    if (!BiosCallback)
    {
        /* No keyboard support yet */
        ERR("No BIOS callback available!\n");
        while (1) ;
    }

    /* Return keystroke */
    return BiosCallback(CROMWELL_CALLBACK_GET_KEY, NULL);
}

/* EOF */
