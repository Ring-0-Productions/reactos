/*
 * PROJECT:     ReactOS HAL
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Port functions
 * COPYRIGHT:   Copyright 2024 Justin Miller <justin.miller@reactos.org>
 */

/* INCLUDES ******************************************************************/

#include <hal.h>
#define NDEBUG
#include <debug.h>

//
// HAL Port to Inlined Port
//
#define H2I(Port) PtrToUshort(Port)

/* FUNCTIONS *****************************************************************/

VOID
NTAPI
READ_PORT_BUFFER_UCHAR(_In_ PUCHAR Port,
                       _Out_ PUCHAR Buffer,
                       _In_ ULONG Count)
{
    __inbytestring(H2I(Port), Buffer, Count);
}

VOID
NTAPI
READ_PORT_BUFFER_USHORT(_In_ PUSHORT Port,
                        _Out_ PUSHORT Buffer,
                        _In_ ULONG Count)
{
    __inwordstring(H2I(Port), Buffer, Count);
}

VOID
NTAPI
READ_PORT_BUFFER_ULONG(_In_ PULONG Port,
                       _Out_ PULONG Buffer,
                       _In_ ULONG Count)
{
    __indwordstring(H2I(Port), Buffer, Count);
}

UCHAR
NTAPI
READ_PORT_UCHAR(_In_ PUCHAR Port)
{
    return __inbyte(H2I(Port));
}

USHORT
NTAPI
READ_PORT_USHORT(_In_ PUSHORT Port)
{
    return __inword(H2I(Port));
}

ULONG
NTAPI
READ_PORT_ULONG(_In_ PULONG Port)
{
    return __indword(H2I(Port));
}

VOID
NTAPI
WRITE_PORT_BUFFER_UCHAR(_In_ PUCHAR Port,
                        _In_ PUCHAR Buffer,
                        _In_ ULONG Count)
{
    __outbytestring(H2I(Port), Buffer, Count);
}

VOID
NTAPI
WRITE_PORT_BUFFER_USHORT(_In_ PUSHORT Port,
                         _In_ PUSHORT Buffer,
                         _In_ ULONG Count)
{
    __outwordstring(H2I(Port), Buffer, Count);
}

VOID
NTAPI
WRITE_PORT_BUFFER_ULONG(_In_ PULONG Port,
                        _In_ PULONG Buffer,
                        _In_ ULONG Count)
{
    __outdwordstring(H2I(Port), Buffer, Count);
}

VOID
NTAPI
WRITE_PORT_UCHAR(_In_ PUCHAR Port,
                 _In_ UCHAR Value)
{
    __outbyte(H2I(Port), Value);
}

VOID
NTAPI
WRITE_PORT_USHORT(_In_ PUSHORT Port,
                  _In_ USHORT Value)
{
    __outword(H2I(Port), Value);
}

VOID
NTAPI
WRITE_PORT_ULONG(_In_ PULONG Port,
                 _In_ ULONG Value)
{
    __outdword(H2I(Port), Value);
}
