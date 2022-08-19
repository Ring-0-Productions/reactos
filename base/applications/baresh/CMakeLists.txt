
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/subsys/posix)

list(APPEND SOURCE
    sh.c
    baresh.rc)

add_executable(baresh ${SOURCE})
set_module_type(baresh win32gui UNICODE ENTRYPOINT main)
add_importlibs(baresh psxdll)

if(MSVC)
    add_importlibs(baresh ntdll)
endif()

add_cd_file(TARGET baresh DESTINATION reactos/system32 FOR all)
