#pragma once

extern BOOL gbBaseVideo;

NTSTATUS
NTAPI
InitVideo(VOID);

VOID
NTAPI
UserSeedDesktopMode(PDEVMODEW pdm);
