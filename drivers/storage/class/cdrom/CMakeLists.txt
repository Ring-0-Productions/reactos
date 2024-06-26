
remove_definitions(-D_WIN32_WINNT=0x502)

list(APPEND SOURCE
    aacs.c
    autorun.c
    cdrom.c
    common.c
    data.c
    guid.c
    init.c
    ioctl.c
    mmc.c
    pnppower.c
    scratch.c
    sense.c
    zpodd.c
    cdrom.h)

add_library(cdrom MODULE ${SOURCE} cdrom.rc)
set_module_type(cdrom kmdfdriver)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(cdrom PRIVATE -Wno-format -Wno-unused-variable -Wno-pointer-sign)
    target_compile_options(cdrom PRIVATE -Wno-unknown-pragmas -Wno-incompatible-pointer-types -Wno-switch)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(cdrom PRIVATE -Wno-enum-conversion -Wno-tautological-constant-compare)
endif()

target_compile_definitions(cdrom PRIVATE DEBUG_USE_KDPRINT 
    WDF_DEVICE_NO_WDMSEC_H _WIN32_WINNT=0x603 NTDDI_VERSION=0x06030000)

target_link_libraries(cdrom libcntpr ${PSEH_LIB})
add_importlibs(cdrom wdfldr ntoskrnl hal)
# add_pch(cdrom cdrom.h SOURCE)
add_cd_file(TARGET cdrom DESTINATION reactos/system32/drivers NO_CAB FOR all)
add_registry_inf(cdrom_reg.inf)
add_driver_inf(cdrom cdrom.inf)
