@ stdcall -private DllGetClassObject(ptr ptr ptr) ; Win 7
@ stdcall -private DllCanUnloadNow()
@ stdcall -stub LCEControlServer()
@ stdcall -stub NotifyLogoffUser()
@ stdcall -stub NotifyLogonUser()
@ stdcall ServiceMain(long ptr)
@ stdcall SvchostPushServiceGlobals(ptr)