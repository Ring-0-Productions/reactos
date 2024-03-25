

add_definitions(
    -D_NTHALDLL_
    -D_NTHAL_)
include_directories(include ${REACTOS_SOURCE_DIR}/ntoskrnl/include)

# Handle the spec file for the dll name
spec2def(halacpi.dll hal.spec ADD_IMPORTLIB)

# The components generic
list(APPEND HAL_SOURCE
    generic/halinit.cpp
    generic/io.cpp)

list(APPEND HAL_ASM_SOURCE
    generic/v86.S)

add_library(halacpi MODULE
    ${HAL_SOURCE}
    ${HAL_ASM_SOURCE}
    halacpi.rc
    ${CMAKE_CURRENT_BINARY_DIR}/halacpi.def
    ${CMAKE_CURRENT_BINARY_DIR}/halacpi_stubs.c)

set_module_type(halacpi kerneldll ENTRYPOINT HalInitSystem 8)
target_link_libraries(halacpi libcntpr wdmguid)
add_dependencies(halacpi asm psdk bugcodes xdk)
add_importlibs(halacpi ntoskrnl)
#add_pch(halacpi include/hal.h SOURCE)
add_cd_file(TARGET halacpi DESTINATION reactos/system32 NO_CAB FOR all)
