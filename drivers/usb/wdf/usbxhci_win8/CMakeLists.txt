
list(APPEND SOURCE
    usbxhci.c)

add_library(usbxhci MODULE
    ${SOURCE}
    usbxhci.rc)

target_compile_definitions(cdrom PRIVATE DEBUG_USE_KDPRINT 
    WDF_DEVICE_NO_WDMSEC_H _WIN32_WINNT=0x603 NTDDI_VERSION=0x06030000)

set_module_type(usbxhci kmdfdriver)
add_importlibs(usbxhci wdfldr usbd hal ntoskrnl)
add_pch(usbxhci usbxhci.h SOURCE)
#add_cd_file(TARGET usbxhci DESTINATION reactos/system32/drivers NO_CAB FOR all)
