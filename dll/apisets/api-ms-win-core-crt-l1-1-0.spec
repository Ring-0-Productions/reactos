
# This file is autogenerated by update.py

@ cdecl -arch=x86_64,arm __C_specific_handler() msvcrt.__C_specific_handler
@ stdcall __isascii() msvcrt.__isascii
@ stdcall _atoi64() msvcrt._atoi64
@ stdcall _errno() msvcrt._errno
@ stdcall -version=0x600+ -arch=i386 _except_handler4_common()  msvcrt._except_handler4_common
@ stdcall -arch=i386,x86_64,arm _fltused() ntdll._fltused
@ stdcall -arch=i386 _ftol() msvcrt._ftol
@ stdcall -arch=i386 _ftol2() msvcrt._ftol2
@ stdcall -arch=i386 _ftol2_sse() msvcrt._ftol2_sse
@ stdcall _i64tow_s() msvcrt._i64tow_s
@ stdcall _itow_s() msvcrt._itow_s
@ cdecl -arch=x86_64 _local_unwind() msvcrt._local_unwind
@ stdcall -version=0x600+ -arch=i386 _local_unwind4() msvcrt._local_unwind4
@ stdcall _ltow_s() msvcrt._ltow_s
@ cdecl -arch=x86_64 _setjmp() msvcrt._setjmp
@ cdecl -arch=x86_64 _setjmpex() msvcrt._setjmpex
@ stdcall -version=0x600+ _snprintf_s() msvcrt._snprintf_s
@ stdcall -version=0x600+ _snwprintf_s() msvcrt._snwprintf_s_l
@ stdcall _splitpath_s() msvcrt._splitpath_s
@ stdcall _stricmp() msvcrt._stricmp
@ stdcall -version=0x600+ _strlwr_s() msvcrt._strlwr_s
@ stdcall _strnicmp() msvcrt._strnicmp
@ stdcall -version=0x600+ _strupr_s() msvcrt._strupr_s
@ stdcall -version=0x600+  _ui64tow_s() msvcrt._ui64tow_s
@ stdcall _ultow() msvcrt._ultow
@ stdcall -version=0x600+ _ultow_s() msvcrt._ultow_s
@ stdcall -version=0x600+ _vsnprintf_s() msvcrt._vsnprintf_s
@ stdcall -version=0x600+ _vsnwprintf_s() msvcrt._vsnwprintf_s
@ stdcall _wcsicmp() msvcrt._wcsicmp
@ stdcall -version=0x600+ _wcslwr_s() msvcrt._wcslwr_s
@ stdcall _wcsnicmp() msvcrt._wcsnicmp
@ stdcall _wcstoi64() msvcrt._wcstoi64
@ stdcall _wcstoui64() msvcrt._wcstoui64
@ stdcall -version=0x600+ _wcsupr_s() msvcrt._wcsupr_s
@ stdcall -version=0x600+ _wsplitpath_s() msvcrt._wsplitpath_s
@ stdcall _wtoi() msvcrt._wtoi
@ stdcall _wtoi64() msvcrt._wtoi64
@ stdcall _wtol() msvcrt._wtol
@ stdcall atoi() msvcrt.atoi
@ stdcall atol() msvcrt.atol
@ stdcall isalnum() msvcrt.isalnum
@ stdcall isdigit() msvcrt.isdigit
@ stdcall isgraph() msvcrt.isgraph
@ stdcall islower() msvcrt.islower
@ stdcall isprint() msvcrt.isprint
@ stdcall isspace() msvcrt.isspace
@ stdcall isupper() msvcrt.isupper
@ stdcall iswalnum() msvcrt.iswalnum
@ stdcall iswascii() msvcrt.iswascii
@ stdcall iswctype() msvcrt.iswctype
@ stdcall iswdigit() msvcrt.iswdigit
@ stdcall iswgraph() msvcrt.iswgraph
@ stdcall iswprint() msvcrt.iswprint
@ stdcall iswspace() msvcrt.iswspace
@ cdecl -arch=x86_64 longjmp() msvcrt.longjmp
@ stdcall memcmp() msvcrt.memcmp
@ stdcall memcpy() msvcrt.memcpy
@ stdcall -version=0x600+ memcpy_s() msvcrt.memcpy_s
@ stdcall memmove() msvcrt.memmove
@ stdcall -version=0x600+ memmove_s() msvcrt.memmove_s
@ stdcall memset() msvcrt.memset
@ stdcall -version=0x600+ qsort_s() msvcrt.qsort_s
@ stdcall -version=0x600+ sprintf_s() msvcrt.sprintf_s
@ stdcall -version=0x600+ sscanf_s() msvcrt.sscanf_s
@ stdcall -version=0x600+ strcat_s() msvcrt.strcat_s
@ stdcall strchr() msvcrt.strchr
@ stdcall strcmp() msvcrt.strcmp
@ stdcall -version=0x600+ strcpy_s() msvcrt.strcpy_s
@ stdcall strcspn() msvcrt.strcspn
@ stdcall strlen() msvcrt.strlen
@ stdcall -version=0x600+ strncat_s() msvcrt.strncat_s
@ stdcall strncmp() msvcrt.strncmp
@ stdcall -version=0x600+ strncpy_s() msvcrt.strncpy_s
@ stdcall -version=0x600+ strnlen() msvcrt.strnlen
@ stdcall strpbrk() msvcrt.strpbrk
@ stdcall strrchr() msvcrt.strrchr
@ stdcall strstr() msvcrt.strstr
@ stdcall -version=0x600+ strtok_s() msvcrt.strtok_s
@ stdcall strtol() msvcrt.strtol
@ stdcall strtoul() msvcrt.strtoul
@ stdcall -version=0x600+ swprintf_s() msvcrt.wprintf_s
@ stdcall tolower() msvcrt.tolower
@ stdcall toupper() msvcrt.toupper
@ stdcall towlower() msvcrt.towlower
@ stdcall towupper() msvcrt.towupper
@ stdcall -version=0x600+ vsprintf_s() msvcrt.vsprintf_s
@ stdcall -version=0x600+ vswprintf_s() msvcrt.vswprintf_s
@ stdcall -version=0x600+ wcscat_s() msvcrt.wcscat_s
@ stdcall wcschr() msvcrt.wcschr
@ stdcall wcscmp() msvcrt.wcscmp
@ stdcall -version=0x600+ wcscpy_s() msvcrt.wcscpy_s
@ stdcall wcscspn() msvcrt.wcscspn
@ stdcall wcslen() msvcrt.wcslen
@ stdcall -version=0x600+ wcsncat_s() msvcrt.wcsncat_s
@ stdcall wcsncmp() msvcrt.wcsncmp
@ stdcall -version=0x600+ wcsncpy_s() msvcrt.wcsncpy_s
@ stdcall -version=0x600+ wcsnlen() msvcrt.wcsnlen
@ stdcall wcspbrk() msvcrt.wcspbrk
@ stdcall wcsrchr() msvcrt.wcsrchr
@ stdcall wcsstr() msvcrt.wcsstr
@ stdcall -version=0x600+ wcstok_s() msvcrt.wcstok_s
@ stdcall wcstol() msvcrt.wcstol
@ stdcall wcstoul() msvcrt.wcstoul
