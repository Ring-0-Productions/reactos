
# This file is autogenerated by update.py

@ stub _Exit
@ stdcall __control87_2() msvcrt.__control87_2
@ stdcall __doserrno() msvcrt.__doserrno
@ stdcall __fpe_flt_rounds() msvcrt.__fpe_flt_rounds
@ stdcall __fpecode() msvcrt.__fpecode
@ stdcall -arch=i386 __p___argc() msvcrt.__p___argc
@ stdcall -arch=i386 __p___argv() msvcrt.__p___argv
@ stdcall -arch=i386 __p___wargv() msvcrt.__p___wargv
@ stdcall -arch=i386 __p__acmdln() msvcrt.__p__acmdln
@ stdcall -arch=i386 __p__pgmptr() msvcrt.__p__pgmptr
@ stdcall -arch=i386 __p__wcmdln() msvcrt.__p__wcmdln
@ stdcall -arch=i386 __p__wpgmptr() msvcrt.__p__wpgmptr
@ stdcall __pxcptinfoptrs() msvcrt.__pxcptinfoptrs
@ stub __sys_errlist
@ stub __sys_nerr
@ stdcall __threadhandle() msvcrt.__threadhandle
@ stdcall __threadid() msvcrt.__threadid
@ stdcall __wcserror() msvcrt.__wcserror
@ stub __wcserror_s
@ stdcall _assert() msvcrt._assert
@ stdcall _beginthread() msvcrt._beginthread
@ stdcall _beginthreadex() msvcrt._beginthreadex
@ stdcall _c_exit() msvcrt._c_exit
@ stdcall _cexit() msvcrt._cexit
@ stdcall -arch=i386,x86_64 _clearfp() msvcrt._clearfp
@ stdcall -version=0x600+ _configure_narrow_argv() msvcrt._configure_narrow_argv
@ stdcall -version=0x600+ _configure_wide_argv() msvcrt._configure_wide_argv
@ stdcall -arch=i386,x86_64 _control87() msvcrt._control87
@ stdcall _controlfp() msvcrt._controlfp
@ stdcall -version=0x600+ _controlfp_s() msvcrt._controlfp_s
@ stub _crt_at_quick_exit
@ stdcall -version=0x600+ _crt_atexit() msvcrt._crt_atexit
@ stub _crt_debugger_hook
@ stdcall _endthread() msvcrt._endthread
@ stdcall _endthreadex() msvcrt._endthreadex
@ stdcall _errno() msvcrt._errno
@ stdcall -version=0x601+ _execute_onexit_table() msvcrt._execute_onexit_table
@ stdcall _exit() msvcrt._exit
@ stdcall -arch=i386 _fpieee_flt() msvcrt._fpieee_flt
@ stdcall -stub -arch=x86_64 _fpieee_flt() # ucrtbase._fpieee_flt (msvcrt x64 doesn't have this!)
@ stdcall _fpreset() msvcrt._fpreset
@ stub _get_doserrno
@ stub _get_errno
@ stdcall -version=0x600+ _get_initial_narrow_environment() msvcrt._get_initial_narrow_environment
@ stdcall -version=0x600+ _get_initial_wide_environment() msvcrt._get_initial_wide_environment
@ stub _get_invalid_parameter_handler
@ stub _get_narrow_winmain_command_line
@ stub _get_pgmptr
@ stub _get_terminate
@ stub _get_thread_local_invalid_parameter_handler
@ stdcall -version=0x600+ _get_wide_winmain_command_line() msvcrt._get_wide_winmain_command_line
@ stub _get_wpgmptr
@ stdcall _getdllprocaddr() msvcrt._getdllprocaddr
@ stdcall _getpid() msvcrt._getpid
@ stdcall -version=0x600+ _initialize_narrow_environment() msvcrt._initialize_narrow_environment
@ stdcall -version=0x600+ _initialize_onexit_table() msvcrt._initialize_onexit_table
@ stdcall -version=0x600+ _initialize_wide_environment() msvcrt._initialize_wide_environment
@ stdcall _initterm() msvcrt._initterm
@ stdcall -version=0x600+ _initterm_e() msvcrt._initterm_e
@ stdcall -version=0x600+ _invalid_parameter() msvcrt._invalid_parameter
@ stdcall -version=0x600+ _invalid_parameter_noinfo() msvcrt._invalid_parameter_noinfo
@ stdcall -version=0x600+ _invalid_parameter_noinfo_noreturn() msvcrt._invalid_parameter_noinfo_noreturn
@ stub _invoke_watson
@ stub _query_app_type
@ stdcall -version=0x601+ _register_onexit_function() msvcrt._register_onexit_function
@ stdcall -version=0x600+ _register_thread_local_exe_atexit_callback() msvcrt._register_thread_local_exe_atexit_callback
@ stdcall _resetstkoflw() msvcrt._resetstkoflw
@ cdecl -version=0x601+ _seh_filter_dll() msvcrt.__CppXcptFilter
@ cdecl -version=0x601+ _seh_filter_exe() msvcrt._XcptFilter
@ stub _set_abort_behavior
@ cdecl _set_app_type() msvcrt._set_app_type
@ stub _set_controlfp
@ stub _set_doserrno
@ stub _set_errno
@ stdcall _set_error_mode() msvcrt._set_error_mode
@ stub _set_invalid_parameter_handler
@ stub _set_new_handler
@ stub _set_thread_local_invalid_parameter_handler
@ stdcall _seterrormode() msvcrt._seterrormode
@ stdcall _sleep() msvcrt._sleep
@ stdcall _statusfp() msvcrt._statusfp
@ stub _statusfp2
@ stdcall _strerror() msvcrt._strerror
@ stdcall -version=0x600+ _strerror_s() msvcrt._strerror_s
@ stub _wassert
@ stdcall _wcserror() msvcrt._wcserror
@ stub _wcserror_s
@ stdcall _wperror() msvcrt._wperror
@ stdcall _wsystem() msvcrt._wsystem
@ stdcall abort() msvcrt.abort
@ stdcall exit() msvcrt.exit
@ stub feclearexcept
@ stub fegetenv
@ stub fegetexceptflag
@ stub fegetround
@ stub feholdexcept
@ stub fesetenv
@ stub fesetexceptflag
@ stub fesetround
@ stub fetestexcept
@ stdcall perror() msvcrt.perror
@ stub quick_exit
@ stdcall raise() msvcrt.raise
@ stub set_terminate
@ stdcall signal() msvcrt.signal
@ stdcall strerror() msvcrt.strerror
@ stub strerror_s
@ stdcall system() msvcrt.system
@ stdcall -version=0x600+ terminate() msvcrt.terminate
