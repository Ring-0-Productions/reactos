
add_definitions(
    -D__WINESRC__
    -DUSE_WIN32_OPENGL)

include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/wine)
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/psdk)

spec2def(dwrite.dll dwrite.spec ADD_IMPORTLIB)

list(APPEND SOURCE
analyzer.c
bidi.c
bracket.c
font.c
freetype.c
gdiinterop.c
layout.c
linebreak.c
main.c
mirror.c
opentype.c
scripts.c
shape.c)

add_library(dwrite SHARED
    ${SOURCE}
    ${CMAKE_CURRENT_BINARY_DIR}/dwrite_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/dwrite.def)

set_module_type(dwrite win32dll)
target_link_libraries(dwrite wine uuid dxguid)
add_importlibs(dwrite d3dwine msvcrt dxgi kernel32 ntdll gdi32)
add_dependencies(dwrite wineheaders)
add_cd_file(TARGET dwrite DESTINATION reactos/system32 FOR all)
