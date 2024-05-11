# ordinal exports
101 stdcall -noname IEWinMain(wstr long)

@ stdcall -private DllCanUnloadNow()
@ stdcall -private DllGetClassObject(ptr ptr ptr)
@ stdcall -private DllRegisterServer()
@ stdcall -private DllUnregisterServer()
@ stdcall IEGetWriteableHKCU(ptr)
@ stdcall OpenURL(long long str long)

160 stdcall -stub funccool(ptr)
159 stdcall -stub funccooltwo(ptr)
141 stdcall -stub funccoolthree(ptr)