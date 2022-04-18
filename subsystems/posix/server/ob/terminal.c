
#include "../include/psxss.h"

/**********************************************************************
 *	WriteTerminal/4
 */
NTSTATUS NTAPI
WriteTerminal (
	IN     PPSX_TERMINAL Terminal,
	IN     PVOID Buffer,
	IN     ULONG Size,
	IN OUT PULONG WrittenSize
	)
{
	return STATUS_NOT_IMPLEMENTED;
}

/**********************************************************************
 *	ReadTerminal/4
 */
NTSTATUS NTAPI
ReadTerminal (
	IN     PPSX_TERMINAL Terminal,
	IN OUT PVOID Buffer,
	IN     ULONG Size,
	IN OUT PULONG ReadSize
	)
{
	return STATUS_NOT_IMPLEMENTED;
}
/* EOF */
