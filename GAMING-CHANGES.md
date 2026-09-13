# ReactOS Gaming — registro de cambios

Objetivo: base ReactOS capaz de ejecutar juegos 3D con driver NVIDIA real
(GT 710, 353.62). Hito: Halo campaña jugable en 3D.

Árboles: `LH` = Longhorn-ReactOS-Stable (Linux) · `WDDM` = reactos-Wddm-Win32k-Branch (Windows)
Estados: [PERMANENT] va a la publicación · [TEMP-DEBUG] revertir antes de publicar ·
[TOLERANCE] frontera ante drivers cerrados · [PARKED] aparcado con motivo

## 1. Fixes del arco gaming (esta sesión)

| # | Fichero (árbol) | Cambio | Por qué | Estado |
|---|---|---|---|---|
| 1 | `ntoskrnl/ke/i386/traphdlr.c` (LH) | `KiTrap07Handler`: reanudar siempre con TS limpio (`Cr0 \|= Cr0NpxState & ~TS`, retorno incondicional) | Reanudar con TS re-faultea inmediato: bucle #NM cerrado en modo kernel (`fxsave` en `Ke386SaveFpuState`, 475× visto), doble falta en usuario; con 3 hilos = livelock + "is hung" | [PERMANENT] |
| 2 | `ntoskrnl/ke/i386/traphdlr.c` (LH) | `FPUTRAP`: `DPRINT1` → `DPRINT` | Cada falta costaba ~10 ms de serie; la tormenta convertía ms en minutos | [TEMP-DEBUG] revertir o mantener degradado |
| 3 | `ntoskrnl/mm/ARM3/mdlsup.c` (LH) | `MiUnmapLockedPagesInUserSpace`: `MiDeletePde` condicional al boundary | `ASSERT MiIsPteOnPdeBoundary` cazado en vivo por serie | [PERMANENT] |
| 4 | `win32ss/user/winsrv/usersrv/init.c` (LH) | `SrvGetThreadConsoleDesktop`: impresión eliminada | nvoglnt sondea `GetThreadDesktop` en hot path (6.5K llamadas); cada fallo imprimía por serie 115200 → csrss 99% + display muerto | [TEMP-DEBUG] el fix correcto (fallback en servidor) está [PARKED]: 0 SERVERFAIL + fallo by-design sin efecto semántico |
| 5 | `win32ss/user/user32/misc/desktop.c` (LH) | caller-ID rate-limited (8/proceso, `ERR`) + rama `SERVERFAIL` | Identificar al sondeador: nvoglnt (`69D9871C`), éxito siempre (`desk=144`) | [TEMP-DEBUG] revertir |
| 6 | `win32ss/gdi/eng/driverobj.c` (LH) | `DRIVEROBJ_vCleanup`: `_SEH2_TRY/EXCEPT` + save/restore **ULONG** de `CombinedApcDisable` + TID en el log | Cleanup de nv4_disp (`+0x210b2a` → `EngDeviceIoControl` con device muerto → `0xC0000005` en `IoBuildDeviceIoControlRequest`) tumbaba la sesión al salir del juego. v1 forzaba el contador a 0 y rompía el invariante inverso (región legítima de win32k → break en `resource.c:1863`); v2 guarda/restaura; v2b corrige `SHORT`→`ULONG` (el campo son DOS contadores: low=kernel, high=guarded; el SHORT truncaba un guarded retenido `0xFFFF0000`) | [TOLERANCE] frontera ante driver cerrado |
| 7 | `ntoskrnl/ke/hbd.c` (LH) | DPC heartbeat cada ~2 s (`tick`, thread, IRQL por serie) | Prueba de vida del kernel con display muerto; distinguió cuelgue-kernel de cuelgue-presentación | [TEMP-DEBUG] revertir |
| 8 | `ntoskrnl/ps/kill.c` (LH) | `PspExitThread`: limpia `NpxThread` del PRCB si es el hilo saliente | Estado FPU colgando tras muerte de hilo (ruta Halo+WMI) | [PERMANENT] |
| 9 | `ntoskrnl/ps/kill.c` (LH) | `APCTRACE`: log de `CombinedApcDisable` al entrar a `PspExitThread` y antes del assert `kill.c:841` | Cazar quién filtra el disable: nonzero al entrar = leak de vida del hilo; solo antes del assert = leak del teardown | [TEMP-DEBUG] revertir |
| 10 | `win32ss/gdi/eng/pdevobj.c`, `bitblt.c`, `copybits.c`, `ntgdi/wingl.c` (LH) | `DDITRACE` enter/exit en `DrvEnableSurface` / `DrvAssertMode` / `DrvDisableSurface` / `DrvBitBlt` / `DrvCopyBits` / `DrvDescribePixelFormat(+max)` / `DrvSetPixelFormat` / `DrvSwapBuffers` | El último `enter` sin `exit` delata el DDI donde muere nv4_disp (`+0x2116DF`, `0x50` en transición a 3D). Veredicto parcial: switch + blts completan; GL-DDIs casi sin uso (Halo va por ICD); sospecha actual: `MapMemory` de dxg (#15) | [TEMP-DEBUG] revertir |
| 15 | `win32ss/reactx/dxg/ddsurf.c` (LH) | `DDITRACE` en `MapMemory` del driver (vía `DbgPrint`) | El crash cae tras churn MDL sin frame win32k: dxg.sys llama al driver DIRECTO. `MapMemory` mapea VRAM al proceso justo tras el switch y lee linkage PDEV que puede estar rancio → `0x9D009C00` constante | [TEMP-DEBUG] revertir |
| 16 | `ntoskrnl/mm/ARM3/procsup.c` (LH) | `PDETBL` + `VADCLEAN` + safety net, con PID de la VICTIMA (`Process->UniqueProcessId`, no ejecutor) | El log global entrelaza procesos Y el teardown puede correr en hilo ajeno (System limpiando a otro): el PID ejecutor mentia. Pendiente: `PDETBL pid=4` con idx0+idx498 - victima real por confirmar (apagado vs salida de Halo) | [TEMP-DEBUG] revertir |
| 17 | `win32ss/gdi/ntgdi/init.c` (LH) | `GdiProcessDestroy`: desmapea `GdiSharedHandleTable` + log `GDIDESTROY` con su direccion (en contexto, seguro) | Asimetria mapear/liberar; candidata a tabla zombie (la direccion dira si es idx498) | [PERMANENT] si se confirma |
| 11 | `win32ss/gdi/eng/device.c` (LH) | `EngDeviceIoControl`: valida el handle (`MmIsAddressValid` + `Type` + `StackSize`) antes de tocarlo | El cleanup del driver pasaba un device muerto: una vez fault en `IoBuild` (`0xC0000005`), otra bugcheck `0x35` (`StackSize` 0). El SEH no traga bugchecks; el chequeo sí los evita. v1 incluía `Size == sizeof(DEVICE_OBJECT)` y mataba el arranque (`0xB4`): `IoCreateDevice` suma la extensión al `Size`. Solo `Type`+`StackSize` | [TOLERANCE] validación de frontera |
| 12 | `win32ss/gdi/eng/device.c` (LH) | `EngpUpdateGraphicsDeviceList`: backoff 60 s a devices que fallan al registrar | `Video1` (2º head, CREATE denegado `0x22`) nunca entraba en lista → cada `EnumDisplayDevices` (Afterburner/monitores lo sondean en hot-loop) reintentaba el open + print → miles de líneas + CPU. Con backoff el sondeo es barato; el print genuino queda | [PERMANENT] |
| 13 | `ntoskrnl/mm/ARM3/procsup.c` (LH) | Safety net libera TABLAS VACIAS (`MiDeletePde` si 0 PTEs validos) | Hallazgo: el path generico solo libera tablas via dec->0 por PTE borrado; las tablas que quedan vacias (todas las de un TerminateProcess) no las libera nadie -> refs al directorio -> assert. Solo visible en debug (leak silencioso en release) | [PERMANENT] fix de leak real |
| 14 | `win32ss/gdi/ntgdi/gdiobj.c` (LH) | `GDI_CleanupForProcess`: destruye DRIVEROBJs PRIMERO (dos pasadas) | Causa raíz de los `0x50` de salida: el cleanup iba en orden de handle y el callback del driver leía objetos hermanos ya liberados (sesión). Clave: esos faults son a dirección kernel → `MmAccessFault` hace bugcheck directo SIN dispatch: ningún SEH del mundo los traga; solo el orden los evita | [PERMANENT] fix de orden real |

## 2. Trabajo previo habilitante (heredado al inicio de sesión)

- KSE portado (`ntoskrnl/kse/{kse,driverscope,versionlie}.c`, `kse.h`, `drvmain.xml/sdb`, hooks en driver/iomgr/sysldr) → driver 353.62 carga. [PERMANENT]
- Build fixes GCC 8.4 (mayúsculas WIDL, `C_ASSERT`, vtbls d2d1/dwrite, exports ntdll/psapi, `ksecdd`, `Dxgk.c`, MediaFoundation/ffmpeg/winedmo/colorcnv/wmvdecod). [PERMANENT]
- Perfil español: `IDS_LOCALLOWAPPDATA/IDS_ROAMINGAPPDATA` + `CreateStandardProfile` crea intermedios (árbol WDDM). [PERMANENT]

## 3. Herramientas de laboratorio (no se publican con el OS)

- `rx.c` / `xmsend.py`: receptor XMODEM-CRC en ReactOS + emisor Python; `rx stage` agenda canje vía `PendingFileRenameOperations`. Plan B ante serie-RX rota.
- `kdbwatch.sh`: vigilante que ante prompt KDB inyecta `b`→`bt`→`cont` (requiere serie TX viva).

## 4. Mapa de despliegue (binario → contenido → destino)

| Binario | Lleva (#) | Destino target |
|---|---|---|
| `ntoskrnl_FPUFIX.exe` | 1, 2, 7, 8 | `C:\` + entrada freeldr (sustituido por APCDBG) |
| `ntoskrnl_APCDBG.exe` (+`GAMING-BUILD <fecha>`) | 1, 2, 7, 8, 9, 13, 16, 18 | `C:\` + entrada freeldr. LECCION: el reloj WSL invierte mtimes y ninja salta recompilas (binarios rancios con cara de frescos); verificar por `strings`, no por hash/fecha. Forzar con `touch` ante duda |
| `winsrv_SILENT.dll` | 4 | `C:\ReactOS\system32\winsrv.dll` |
| `user32_CALLER2.dll` | 5 | `C:\ReactOS\system32\user32.dll` |
| `win32k_CLEANUP.sys` | 6, 10, 11, 12, 14 | `C:\ReactOS\system32\win32k.sys` |
| `dxg_TRACE.sys` | 15 | `C:\ReactOS\system32\drivers\dxg.sys` |

## 5. Pendientes

- [ ] Crash salida: verificar salida limpia con #6 (modo 800x600: `Failed to restore display mode` es bug separado, `display.c:947`).
- [ ] Rendimiento 3-5fps: no es el serie (igual sin debug). Candidatos: wined3d sin FBO (`GL_FRAMEBUFFER_UNSUPPORTED` por frame), checked build, uniprocesador. Experimentos: Taskmgr %CPU, 640x480.
- [ ] `STOP 0x50` en `nv4_disp+0x2116DF` (`cmp (%edi),%eax`, `edi=[param1+0x338]=0x9D009C00`) en mode-switch: determinista en stack viejo, pendiente de reproducir en stack nuevo.
- [ ] Serie RX del target muerta (cable+adaptador sanos; socket DB9 del target). Plan: otra PC.
- [ ] Antes de publicar: revertir todo [TEMP-DEBUG] (2 parcial, 5, 7) y decidir #4 (restaurar print o dejar fallback).
| 18 | `ntoskrnl/ke/hbd.c` (LH) | `GAMING-BUILD __DATE__ __TIME__` al arrancar | Los logs no probaban que binario corria (frankenkernels); el marker lo hace trivial | [PERMANENT] |

## #19 Fullscreen Halo: drenaje VRAM con ShareCount (procsup.c)
- Rama device-physical borraba PTEs sin `MiDecrementShareCount` de la tabla -> `MiDeletePde`/`MiDeletePte` assert `ShareCount==1` (virtual.c:511) en VAD 64MB `[14330000-1832FFFF]` type=1. Fix: decrementar ShareCount por PTE como `MiDeletePteRange`/mdlsup. TEMP-DEBUG hasta salida completa limpia.

## #20 Restaurar resolucion al salir de fullscreen (display.c)
- `UserDisplayNotifyShutdown(NULL)` leia `DefaultSettings.X/YResolution` del registro; en esta maquina no existen -> `BADMODE` (`Devmode doesn't specify`) y el escritorio quedaba en el modo del juego. Fix: al primer `CDS_FULLSCREEN` se guarda el modo escritorio (`gdmRestoreDesktop`) y el restore lo usa si el registro no trae resolucion; un cambio normal lo invalida. PERMANENT (comportamiento Windows: volver al modo previo).

## #21 0x50 en nv4_disp free proc + traza forense (driverobj.c/device.c)
- Nuevo crash a la salida: `nv4_disp+0x210aa6` desde `DRIVEROBJ_vCleanup`, lee `0x9D00DBA4` (fuera de todo VAD del juego). El SEH no lo contuvo (bugcheck en `MmArmAccessFault`). Sospechas: (a) el free proc no chequea el error de `EngDeviceIoControl` stale-handle y persigue un puntero basura; (b) contexto dhpdev ya liberado. TEMP-DEBUG: log de `free proc/obj/dhpdev/hdev` antes de llamar + `caller` en el reject stale-handle, para ordenar causa/efecto en el proximo log.

## #22 Restore fuerza re-assert + forense DISPRESTORE (display.c)
- El record decia escritorio pero el hardware seguia en juego (divergencia via DXG): el `matches -> skip` nunca re-afirmaba el modo. Ahora el restore (`pdm==NULL`) NO salta aunque coincida: fuerza `PDEVOBJ_bSwitchMode` (re-assert; el exito limpia `gpFullscreen`). Forense `DISPRESTORE`: modo guardado a la entrada, candidato vs actual a la salida. TEMP-DEBUG el log, PERMANENT el re-assert si funciona.

## #23 Baseline desde el modo de arranque, no de la entrada fullscreen (display.c/mdevobj.c)
- Causa real del 800x600 atascado: mi guardado leia `pdmwDev` DESPUES de que el juego ya lo habia cambiado (plain switch previo al primer FULLSCREEN) -> guardaba 800x600. Fix: `UserSeedDesktopMode` siembra la baseline desde el probe de defaults del driver (modo de arranque 1366x768, estatico en runtime) en `MDEVOBJ_Create(!pdm)`; el FULLSCREEN solo guarda si no hay baseline; el plain ya NO invalida; solo `CDS_UPDATEREGISTRY` exitoso la resetea. PERMANENT.

## #24 Higiene de logs (procsup.c/kill.c)
- Manguera TEMP-DEBUG a `DPRINT` (fuera del binario): `VADCLEAN`, `PDETBL`, `safety net`, `APCTRACE` (~150 lineas por salida de proceso -> 0). Verificado por `strings`: ausentes, `GAMING-BUILD` intacto. Se quedan en `ERR` (raros y valiosos): `DISPRESTORE`, `stale device handle`, `driver free proc faulted/tolerated`, `GDIDESTROY`, heartbeat. Para re-depurar, revertir a `DPRINT1` y reconstruir.

---
## ESTADO FINAL FASE ESTABILIDAD (2026-09-11, verificado en GT 710 + 353.62)
Combo que juega Halo fullscreen, sale limpio, restaura 1366x768 y sobrevive:
- `ntoskrnl_APCDBG.exe` `569baf363eba68ade7258470f3c593fee6ba4e7d5c57f32d33473ea4f3f44ee6` -> `C:\` + freeldr
- `win32k_CLEANUP.sys` `83e5ff9869719e4c8d71beb1d9247a0b3b72ecd99ee48c8be614e9994c07100e` -> `system32\win32k.sys`
- `dxg_TRACE.sys` `daed3a06e459bea8b70a09c12fd3e2bd8b46e821cb660a667c49a3479161cb9c` -> `system32\drivers\dxg.sys`
- `winsrv_SILENT.dll` `21d10786b30c3df418a63a0780484dffcac1d8711285dcf12a10a938f8fc2fa7` -> `system32\winsrv.dll`
Sintomas cerrados: APC disable imbalance, VAD VRAM asserts (ShareCount), DRIVEROBJ free-proc 0x50 (guardia stale-handle), modo no restaurado (baseline de arranque + re-assert). Ruido serie reducido (#24).
Pendiente conocido: `nv4_disp` free proc a veces persigue punteros basura (nondeterminista, contenido por la guardia); `Video1 0xc0000022` (Afterburner, backoff); 3-5fps -> ver FASE RENDIMIENTO.

---
## FASE RENDIMIENTO
- #25 Medicion: `d3dwine` fps-meter (presents+draws). Present inocente (<1ms/frame, via GL). Draws ~400/frame a ~0.5ms c/u con CSMT on.
- #26 `HKCU\Software\Wine\Direct3D` DWORD `csmt=0` (single-threaded command stream): 5fps -> ~30fps estables en i3 monoprocesador. El handoff entre hilos por draw era el impuesto. DEFAULT GAMING; documentado, no binario.
- #27 VRAM=0 descartado: fallback a 1280MB de la DB no mueve fps. `card GTX470 10de:06cd`, HW vertex processing (`software 0x0`), GL 4.4 NVIDIA: todo el pipeline es hardware.
- Pendiente 30->60: frame clavado en ~33.5ms aunque los draws varien 335<->477 => espera fija (vsync a 60Hz cayendo cada 2 vblanks, o cap 30fps del propio Halo). Mirar ajuste Framerate/VSync del juego.

- #28 Hito 60fps: con `csmt=0` + ajustes bajos, 120 frames en ~2010ms = 59.7fps estables (vsync 60Hz; el present absorbe la espera: 400-900ms/120). Ley: fps ~= 1/max(draws*80us, 16.7ms): ~200 draws -> 60fps, ~400 -> 30fps, ~1000 -> 20fps. Pendiente: bajar coste/draw (build -O0) para 60fps en escenas pesadas.

- #29 Ratón FPS atrapado en bordes (dinput/mouse.c): `warp_check` solo recentraba UNA vez por acquire (`if (!clipped)`); despues el cursor vagaba dentro del clip hasta clavarse en un borde y los deltas morian (igual en ventana y completa). Fix: recentrar siempre en cada poll exclusivo (throttle 10ms) + mantener clip. Marker `GAMING-MOUSE exclusive acquire`. PERMANENT (mecanica FPS estandar).

- #30 Contencion de faults del driver en switches de modo (pdevobj.c): 0x50 en `nv4+0x2102ef` leyendo pool liberado tras doble switch consecutivo (UAF del driver, misma zona que el 0x50 del free proc). `PDEVOBJ_bSwitchMode` partido en `Unsafe` + wrapper SEH: un fault aborta el switch con restore best-effort y devuelve FALSE en vez de bugcheck; semaforos siempre liberados; APC-count preservado. TEMP-HARDEN hasta confirmar.
- #31 Ratón Win32 (no dinput): Halo nunca adquiere el mouse por dinput (teclado sí) -> usa ClipCursor + posiciones absolutas sin recentrar; el clip lo clava en bordes. Traza `GAMING-MOUSE` en `UserClipCursor`/`UserSetCursorPos` (win32k) para ver rects. Pendiente: decidir fix (p.ej. recentrado asistido o `MouseWarpOverride=force` si el juego tolera dinput).
