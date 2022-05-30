/*
 * PROJECT:     ReactOS CRT library
 * LICENSE:     MIT (https://spdx.org/licenses/MIT)
 * PURPOSE:     Implementation of __rt_udiv64
 * COPYRIGHT:   Copyright 2022 Justin Miller<justinmiller100@gmail.com>
 */

/* INCLUDES ******************************************************************/

#include <kxarm64.h>

    IMPORT __rt_udiv64_worker

/* CODE **********************************************************************/

    TEXTAREA

    NESTED_ENTRY __rt_udiv64
    NESTED_END __rt_udiv64

    END
/* EOF */
