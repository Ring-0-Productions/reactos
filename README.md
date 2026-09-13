# ReactOS Gaming — rama `gaming`

> Base ReactOS capaz de correr juegos 3D con driver NVIDIA real. Hito actual: **Halo Combat Evolved jugable en 3D en GT 710 (353.62), sale limpio a 1366x768 y ~60 fps en escenas ligeras**.

- Upstream: `ReactOS-Longhorn-Initiative/reactos` (`Longhorn-ReactOS-Stable`, `328deb67`).
- Registro de cambios gaming: [`GAMING-CHANGES.md`](GAMING-CHANGES.md) (#1–#31).
- Hardware validado: BIOSTAR H81MHV3, i3-4170 monoprocesador, GT 710, Realtek `10EC:8136`. Escritorio 1366x768, juego 800x600.
- Defaults gaming: `HKCU\Software\Wine\Direct3D` DWORD `csmt=0`.
- Build: RosBE-Unix 2.2.1, `configure.sh -DENABLE_ROSTESTS=1 -DENABLE_ROSAPPS=1`, `ninja -j12 bootcd` (ver `build-LH-Stable/bootcd.iso` ~504 MB).

## Media — juegos verificados

Deja tus capturas y clips aquí y se verán en esta tabla. Rutas sugeridas:

- `docs/gaming/screenshots/`
- `docs/gaming/videos/`

| Juego | Estado | Screenshot | Video |
|---|---|---|---|
| Halo Combat Evolved (fullscreen 800x600 -> restore 1366x768) | Jugable, salida limpia, 30–60 fps según draws | ![Halo gameplay](docs/gaming/screenshots/halo-gameplay.png) | [Halo gameplay](docs/gaming/videos/halo-gameplay.mp4) |
| Halo (menú / campaña) | 60 fps en escenas ~200 draws, ~30 fps con ~400 draws | ![Halo menú](docs/gaming/screenshots/halo-menu.png) | [Halo menú](docs/gaming/videos/halo-menu.mp4) |
| GTA San Andreas (vanilla, sin mods) | En validación — salida/teardown en prueba | ![GTA SA](docs/gaming/screenshots/gta-sa.png) | [GTA SA](docs/gaming/videos/gta-sa.mp4) |
| OpenGL teardown (`glteardown.exe`) | Repro crash `wglMakeCurrent` en estudio | ![glteardown](docs/gaming/screenshots/glteardown.png) | [glteardown](docs/gaming/videos/glteardown.mp4) |

> Si una imagen/video aún no existe verás un enlace roto — súbelo con ese mismo nombre y listo.

---

<p align=center>
  <a href="https://reactos.org/">
    <img alt="ReactOS" src="https://reactos.org/wiki/images/0/02/ReactOS_logo.png">
  </a>
</p>

---

<p align=center>
  <a href="https://reactos.org/project-news/reactos-0415-released/">
    <img alt="ReactOS 0.4.15 Release" src="https://img.shields.io/badge/release-0.4.15-0688CB.svg"></a>
  <a href="https://reactos.org/download/">
    <img alt="Download ReactOS" src="https://img.shields.io/badge/download-latest-0688CB.svg"></a>
  <a href="https://sourceforge.net/projects/reactos/">
    <img alt="SourceForge Download" src="https://img.shields.io/sourceforge/dm/reactos.svg?colorB=0688CB"></a>
  <a href="https://github.com/reactos/reactos/blob/master/COPYING">
    <img alt="License" src="https://img.shields.io/badge/license-GNU_GPL_2.0-0688CB.svg"></a>
  <a href="https://reactos.org/donate/">
    <img alt="Donate" src="https://img.shields.io/badge/%24-donate-E44E4A.svg"></a>
  <a href="https://twitter.com/reactos">
    <img alt="Follow on Twitter" src="https://img.shields.io/twitter/follow/reactos.svg?style=social&label=Follow%20%40reactos"></a>
</p>

## Quick Links
[Website](https://reactos.org/) &bull;
[Official chat](https://chat.reactos.org/) &bull;
[Wiki](https://reactos.org/wiki/) &bull;
[Forum](https://reactos.org/forum/) &bull;
[Community Discord](https://discord.gg/7knjvhT) &bull;
[JIRA Bug Tracker](https://jira.reactos.org/issues/) &bull;
[ReactOS Git mirror](https://git.reactos.org/) &bull;
[Testman](https://reactos.org/testman/)

## What is ReactOS?

ReactOS™ is an Open Source effort to develop a quality operating system that is compatible with applications and drivers written for the Microsoft® Windows™ NT family of operating systems (NT4, 2000, XP, 2003, Vista, 7).

The ReactOS project, although currently focused on Windows Server 2003 compatibility, is always keeping an eye toward compatibility with Windows Vista and future Windows NT releases.

The code of ReactOS is licensed under [GNU GPL 2.0](https://github.com/reactos/reactos/blob/master/COPYING).

### Product quality warning

**ReactOS is currently an Alpha quality operating system.** This means that ReactOS is under heavy development and you have to be ready to encounter some problems. Different things may not work well and it can corrupt the data present on your hard disk. It is HIGHLY recommended to test ReactOS on a virtual machine or on a computer with no sensitive or critical data!

## Building

![Build](https://github.com/reactos/reactos/workflows/Build/badge.svg) [![rosbewin.badge]][rosbewin.link] [![rosbeunix.badge]][rosbeunix.link] [![coverity.badge]][coverity.link]

To build the system it is strongly advised to use the _ReactOS Build Environment (RosBE)._
Up-to-date versions for Windows and for Unix/GNU-Linux are available from our download page at: ["Build Environment"](https://reactos.org/wiki/Build_Environment).

Alternatively one can use Microsoft Visual C++ (MSVC) version 2019+. Building with MSVC is covered here: ["Visual Studio or Microsoft Visual C++"](https://reactos.org/wiki/CMake#Visual_Studio_or_Microsoft_Visual_C.2B.2B).

See ["Building ReactOS"](https://reactos.org/wiki/Building_ReactOS) article for more details.

### Binaries

To build ReactOS you must run the `configure` script in the directory you want to have your build files. Choose `configure.cmd` or `configure.sh` depending on your system. Then run `ninja <modulename>` to build a module you want or just `ninja` to build all modules.

### Bootable images

To build a bootable CD image run `ninja bootcd` from the build directory. This will create a CD image with a filename `bootcd.iso`.

You can always download fresh binary builds of bootable images from the ["Daily builds"](https://reactos.org/getbuilds/) page.

## Installing

By default, ReactOS currently can only be installed on a machine that has a FAT16 or FAT32 partition as the active (bootable) partition.
The partition on which ReactOS is to be installed (which may or may not be the bootable partition) must also be formatted as FAT16 or FAT32.
ReactOS Setup can format the partitions if needed.

Starting with 0.4.10, ReactOS can be installed using the BtrFS file system. But consider this as an experimental feature and thus regressions not triggered on FAT setup may be observed.

To install ReactOS from the bootable CD distribution, extract the archive contents. Then burn the CD image, boot from it, and follow the instructions.

See ["Installing ReactOS"](https://reactos.org/wiki/Installing_ReactOS) Wiki page or [INSTALL](INSTALL) for more details.

## Testing

If you discover a bug in ReactOS search on JIRA first - it might be reported already. If not report the bug providing logs and as much information as possible.

See ["File Bugs"](https://reactos.org/wiki/File_Bugs) for a guide.

__NOTE:__ The bug tracker is _not_ for discussions. Please use our [official chat](https://chat.reactos.org/) or our [forum](https://reactos.org/forum/).

## Contributing  [![prwelcome.badge]](https://reactos.org/wiki/Commiting_Changes)

We are always looking for developers! Check [how to contribute](CONTRIBUTING.md) if you are willing to participate.

__Legal notice__: If you have seen proprietary Microsoft Windows source code (including but not limited to the leaked Windows NT 3.5, NT 4, 2000 source code and the Windows Research Kernel), your contribution won't be accepted because of potential copyright violation.

Try out cloud-based ReactOS development using Gitpod and Docker:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/reactos/reactos)

You can also support ReactOS by [donating](https://reactos.org/donate/)! We rely on our backers to maintain our servers and accelerate development by [hiring full-time devs](https://reactos.org/contributing/#paid-jobs).

## More information

ReactOS is a Free and Open Source operating system based on the Windows architecture,
providing support for existing applications and drivers, and an alternative to the current dominant consumer operating system.

It is not another wrapper built on Linux, like WINE. It does not attempt or plan to compete with WINE; in fact, the user-mode part of ReactOS is almost entirely WINE-based and our two teams have cooperated closely in the past.

ReactOS is also not "yet another OS". It does not attempt to be a third player like any other alternative OS out there. People are not meant to uninstall Linux and use ReactOS instead; ReactOS is a replacement for Windows users who want a Windows replacement that behaves just like Windows.

More information is available at: [reactos.org](https://reactos.org/).

Also see the [media/doc](/media/doc/) subdirectory for some sparse notes.

## Who is responsible

Active devs are listed as members of [GitHub organization](https://github.com/orgs/reactos/people).
See also the [CREDITS](CREDITS) file for others.

## Code mirrors

The main development is done on [GitHub](https://github.com/reactos/reactos). We have an [alternative mirror](https://git.reactos.org/?p=reactos.git) in case GitHub is down.

There is also an obsolete [SVN archive repository](https://svn.reactos.org/reactos/) that is kept for historical purposes.

[coverity.badge]:   https://scan.coverity.com/projects/205/badge.svg?flat=1
[rosbewin.badge]:   https://img.shields.io/badge/RosBE_Windows-2.2.1-0688CB.svg
[rosbeunix.badge]:  https://img.shields.io/badge/RosBE_Unix-2.2.1-0688CB.svg
[prwelcome.badge]:  https://img.shields.io/badge/PR-welcome-0688CB.svg

[coverity.link]:    https://scan.coverity.com/projects/205
[rosbewin.link]:    https://sourceforge.net/projects/reactos/files/RosBE-Windows/i386/2.2.1/
[rosbeunix.link]:   https://sourceforge.net/projects/reactos/files/RosBE-Unix/2.2.1/
