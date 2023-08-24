

add_definitions(
    -D__WINESRC__)

include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/wine)
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/psdk)

spec2def(d2d1.dll d2d1.spec ADD_IMPORTLIB)

add_library(d2d1 MODULE
    bitmap_render_target.c
    bitmap.c
    brush.c
    dc_render_target.c
    factory.c
    geometry.c
    hwnd_render_target.c
    layer.c
    mesh.c
    state_block.c
    stroke.c
    wic_render_target.c
    ${CMAKE_CURRENT_BINARY_DIR}/d2d1_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/d2d1.def)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(d2d1 PRIVATE -Wno-sequence-point -Wno-unused-function -Wno-unused-but-set-variable -Wno-error) # Our favourite compiler :)
endif()

set_module_type(d2d1 win32dll)
target_link_libraries(d2d1 dxguid uuid wine)
add_importlibs(d2d1 advapi32 gdi32 user32 d3dwine msvcrt kernel32 ntdll)
add_dependencies(d2d1 wineheaders)
add_cd_file(TARGET d2d1 DESTINATION reactos/system32 FOR all)
