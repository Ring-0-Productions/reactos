# CoVrfCheckThreadState
# CoVrfGetThreadState
# CoVrfReleaseThreadState
# PropVariantChangeType
@ stdcall BindMoniker(ptr long ptr ptr)
@ stdcall CLIPFORMAT_UserFree(ptr ptr)
@ stdcall CLIPFORMAT_UserMarshal(ptr ptr ptr)
@ stdcall CLIPFORMAT_UserSize(ptr long ptr)
@ stdcall CLIPFORMAT_UserUnmarshal(ptr ptr ptr)
# CLSIDFromOle1Class
@ stdcall CLSIDFromProgID(wstr ptr)
@ stdcall CLSIDFromProgIDEx(wstr ptr)
@ stdcall CLSIDFromString(wstr ptr)
@ stdcall CoAddRefServerProcess()
@ stdcall CoAllowSetForegroundWindow(ptr ptr)
@ stdcall CoBuildVersion()
@ stdcall -stub CoCancelCall(long long)
@ stdcall CoCopyProxy(ptr ptr)
@ stdcall CoCreateFreeThreadedMarshaler(ptr ptr)
@ stdcall CoCreateGuid(ptr)
@ stdcall CoCreateInstance(ptr ptr long ptr ptr)
@ stdcall CoCreateInstanceEx(ptr ptr long ptr long ptr)
@ stdcall CoDecrementMTAUsage(ptr)
# CoCreateObjectInContext
# CoDeactivateObject
@ stdcall CoDisableCallCancellation(ptr)
@ stdcall -stub -version=0x600+ CoDisconnectContext(long)
@ stdcall CoDisconnectObject(ptr long)
@ stdcall CoDosDateTimeToFileTime(long long ptr) kernel32.DosDateTimeToFileTime
@ stdcall CoEnableCallCancellation(ptr)
@ stdcall CoFileTimeNow(ptr)
@ stdcall CoFileTimeToDosDateTime(ptr ptr ptr) kernel32.FileTimeToDosDateTime
@ stdcall CoFreeAllLibraries()
@ stdcall CoFreeLibrary(long)
@ stdcall CoFreeUnusedLibraries()
@ stdcall CoFreeUnusedLibrariesEx(long long)
# CoGetApartmentID
@ stdcall -version=0x600+ CoGetApartmentType(ptr ptr)
@ stdcall CoGetCallContext(ptr ptr)
@ stdcall CoGetCallerTID(ptr)
@ stdcall -stub CoGetCancelObject(long ptr ptr)
@ stdcall -stub StgSerializePropVariant()
@ stdcall -stub VariantToPropVariant()
@ stdcall -stub PropVariantToVariant()
@ stdcall -stub StgDeserializePropVariant()
@ stdcall CoGetClassObject(ptr long ptr ptr ptr)
# CoGetClassVersion
# CoGetComCatalog
@ stdcall CoGetContextToken(ptr)
@ stdcall CoGetCurrentLogicalThreadId(ptr)
@ stdcall CoGetCurrentProcess()
@ stdcall CoGetDefaultContext(long ptr ptr)
@ stdcall CoGetInstanceFromFile(ptr ptr ptr long long wstr long ptr)
@ stdcall CoGetInstanceFromIStorage(ptr ptr ptr long ptr long ptr)
@ stdcall -stub CoGetInterceptor(ptr ptr ptr ptr)
@ stdcall -stub CoGetInterceptorFromTypeInfo(ptr ptr ptr ptr ptr)
@ stdcall CoGetInterfaceAndReleaseStream(ptr ptr ptr)
@ stdcall CoGetMalloc(long ptr)
@ stdcall CoGetMarshalSizeMax(ptr ptr ptr long ptr long)
# CoGetModuleType
@ stdcall CoGetObject(wstr ptr ptr ptr)
@ stdcall CoGetObjectContext(ptr ptr)
@ stdcall CoGetPSClsid(ptr ptr)
# CoGetProcessIdentifier
@ stdcall CoGetStandardMarshal(ptr ptr long ptr long ptr)
@ stdcall CoGetState(ptr)
@ stdcall -stub CoGetStdMarshalEx(ptr long ptr)
# CoGetSystemSecurityPermissions
@ stdcall CoGetTreatAsClass(ptr ptr)
@ stdcall CoImpersonateClient()
@ stdcall CoIncrementMTAUsage(ptr)
@ stdcall CoInitialize(ptr)
@ stdcall CoInitializeEx(ptr long)
@ stdcall CoInitializeSecurity(ptr long ptr ptr long long ptr long ptr)
@ stdcall CoInitializeWOW(long long)
# CoInstall
# CoInvalidateRemoteMachineBindings
@ stdcall CoIsHandlerConnected(ptr)
@ stdcall CoIsOle1Class (ptr)
@ stdcall CoLoadLibrary(wstr long)
@ stdcall CoLockObjectExternal(ptr long long)
@ stdcall CoMarshalHresult(ptr long)
@ stdcall CoMarshalInterThreadInterfaceInStream(ptr ptr ptr)
@ stdcall CoMarshalInterface(ptr ptr ptr long ptr long)
# CoPopServiceDomain
# CoPushServiceDomain
@ stub CoQueryAuthenticationServices
@ stdcall CoQueryClientBlanket(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall CoQueryProxyBlanket(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stub CoQueryReleaseObject
# CoReactivateObject
@ stdcall CoRegisterChannelHook(ptr ptr)
@ stdcall CoRegisterClassObject(ptr ptr long long ptr)
@ stdcall CoRegisterInitializeSpy(ptr ptr)
@ stdcall CoRegisterMallocSpy (ptr)
@ stdcall CoRegisterMessageFilter(ptr ptr)
@ stdcall CoRegisterPSClsid(ptr ptr)
@ stdcall CoRegisterSurrogate(ptr)
@ stdcall CoRegisterSurrogateEx(ptr ptr)
@ stdcall CoReleaseMarshalData(ptr)
@ stdcall CoReleaseServerProcess()
@ stdcall CoResumeClassObjects()
# CoRetireServer
@ stdcall CoRevertToSelf()
@ stdcall CoRevokeClassObject(long)
@ stdcall CoRevokeInitializeSpy(int64)
@ stdcall CoRevokeMallocSpy()
# CoSetCancelObject
@ stdcall CoSetProxyBlanket(ptr long long ptr long long ptr long)
@ stdcall CoSetState(ptr)
@ stdcall CoSuspendClassObjects()
@ stdcall CoSwitchCallContext(ptr ptr)
@ stdcall CoTaskMemAlloc(long)
@ stdcall CoTaskMemFree(ptr)
@ stdcall CoTaskMemRealloc(ptr long)
# CoTestCancel
@ stdcall CoTreatAsClass(ptr ptr)
@ stdcall CoUninitialize()
@ stub CoUnloadingWOW
@ stdcall CoUnmarshalHresult(ptr ptr)
@ stdcall CoUnmarshalInterface(ptr ptr ptr)
@ stdcall CoWaitForMultipleHandles(long long long ptr ptr)
# ComPs_NdrDllCanUnloadNow
# ComPs_NdrDllGetClassObject
# ComPs_NdrDllRegisterProxy
# ComPs_NdrDllUnregisterProxy
@ stdcall CreateAntiMoniker(ptr)
@ stdcall CreateBindCtx(long ptr)
@ stdcall CreateClassMoniker(ptr ptr)
@ stdcall CreateDataAdviseHolder(ptr)
@ stdcall CreateDataCache(ptr ptr ptr ptr)
@ stdcall CreateErrorInfo(ptr)
@ stdcall CreateFileMoniker(wstr ptr)
@ stdcall CreateGenericComposite(ptr ptr ptr)
@ stdcall CreateILockBytesOnHGlobal(ptr long ptr)
@ stdcall CreateItemMoniker(wstr wstr ptr)
@ stub CreateObjrefMoniker
@ stdcall CreateOleAdviseHolder(ptr)
@ stdcall CreatePointerMoniker(ptr ptr)
# CreateStdProgressIndicator
@ stdcall CreateStreamOnHGlobal(ptr long ptr)
# DcomChannelSetHResult
@ stdcall DllDebugObjectRPCHook(long ptr)
@ stdcall DllGetClassObject(ptr ptr ptr)
@ stub DllGetClassObjectWOW
@ stdcall -private DllRegisterServer()
@ stdcall DoDragDrop(ptr ptr long ptr)
@ stub EnableHookObject
@ stdcall FmtIdToPropStgName(ptr wstr)
@ stdcall FreePropVariantArray(long ptr)
@ stdcall GetClassFile(wstr ptr)
@ stdcall GetConvertStg(ptr)
@ stub GetDocumentBitStg
@ stdcall GetErrorInfo(long ptr)
@ stdcall GetHGlobalFromILockBytes(ptr ptr)
@ stdcall GetHGlobalFromStream(ptr ptr)
@ stub GetHookInterface
@ stdcall GetRunningObjectTable(long ptr)

@ stdcall HACCEL_UserFree64() HACCEL_UserFree
@ stdcall HACCEL_UserMarshal64() HACCEL_UserMarshal
@ stdcall HACCEL_UserSize64() HACCEL_UserSize
@ stdcall HACCEL_UserUnmarshal64() HACCEL_UserUnmarshal
@ stdcall HBITMAP_UserFree64() HBITMAP_UserFree
@ stdcall HBITMAP_UserMarshal64() HBITMAP_UserMarshal
@ stdcall HBITMAP_UserSize64() HBITMAP_UserSize
@ stdcall HBITMAP_UserUnmarshal64() HBITMAP_UserUnmarshal
@ stdcall HBRUSH_UserFree64() HBRUSH_UserFree
@ stdcall HBRUSH_UserMarshal64() HBRUSH_UserMarshal
@ stdcall HBRUSH_UserSize64() HBRUSH_UserSize
@ stdcall HBRUSH_UserUnmarshal64() HBRUSH_UserUnmarshal
@ stdcall HDC_UserFree64() HDC_UserFree
@ stdcall HDC_UserMarshal64() HDC_UserMarshal
@ stdcall HDC_UserSize64() HDC_UserSize 
@ stdcall HDC_UserUnmarshal64() HDC_UserUnmarshal



@ stdcall HACCEL_UserFree(ptr ptr)
@ stdcall HACCEL_UserMarshal(ptr ptr ptr)
@ stdcall HACCEL_UserSize(ptr long ptr)
@ stdcall HACCEL_UserUnmarshal(ptr ptr ptr)
@ stdcall HBITMAP_UserFree(ptr ptr)
@ stdcall HBITMAP_UserMarshal(ptr ptr ptr)
@ stdcall HBITMAP_UserSize(ptr long ptr)
@ stdcall HBITMAP_UserUnmarshal(ptr ptr ptr)
@ stdcall HBRUSH_UserFree(ptr ptr)
@ stdcall HBRUSH_UserMarshal(ptr ptr ptr)
@ stdcall HBRUSH_UserSize(ptr long ptr)
@ stdcall HBRUSH_UserUnmarshal(ptr ptr ptr)
@ stdcall HDC_UserFree(ptr ptr)
@ stdcall HDC_UserMarshal(ptr ptr ptr)
@ stdcall HDC_UserSize(ptr long ptr)
@ stdcall HDC_UserUnmarshal(ptr ptr ptr)



@ stdcall HENHMETAFILE_UserFree(ptr ptr)
@ stdcall HENHMETAFILE_UserMarshal(ptr ptr ptr)
@ stdcall HENHMETAFILE_UserSize(ptr long ptr)
@ stdcall HENHMETAFILE_UserUnmarshal(ptr ptr ptr)
@ stdcall HGLOBAL_UserFree(ptr ptr)
@ stdcall HGLOBAL_UserMarshal(ptr ptr ptr)
@ stdcall HGLOBAL_UserSize(ptr long ptr)
@ stdcall HGLOBAL_UserUnmarshal(ptr ptr ptr)
@ stdcall HICON_UserFree(ptr ptr)
@ stdcall HICON_UserMarshal(ptr ptr ptr)
@ stdcall HICON_UserSize(ptr long ptr)
@ stdcall HICON_UserUnmarshal(ptr ptr ptr)
@ stdcall HMENU_UserFree(ptr ptr)
@ stdcall HMENU_UserMarshal(ptr ptr ptr)
@ stdcall HMENU_UserSize(ptr long ptr)
@ stdcall HMENU_UserUnmarshal(ptr ptr ptr)
@ stdcall HMETAFILEPICT_UserFree(ptr ptr)
@ stdcall HMETAFILEPICT_UserMarshal(ptr ptr ptr)
@ stdcall HMETAFILEPICT_UserSize(ptr long ptr)
@ stdcall HMETAFILEPICT_UserUnmarshal(ptr ptr ptr)
@ stdcall HMETAFILE_UserFree(ptr ptr)
@ stdcall HMETAFILE_UserMarshal(ptr ptr ptr)
@ stdcall HMETAFILE_UserSize(ptr long ptr)
@ stdcall HMETAFILE_UserUnmarshal(ptr ptr ptr)
@ stdcall HPALETTE_UserFree(ptr ptr)
@ stdcall HPALETTE_UserMarshal(ptr ptr ptr)
@ stdcall HPALETTE_UserSize(ptr long ptr)
@ stdcall HPALETTE_UserUnmarshal(ptr ptr ptr)
@ stdcall HWND_UserFree(ptr ptr)
@ stdcall HWND_UserMarshal(ptr ptr ptr)
@ stdcall HWND_UserSize(ptr long ptr)
@ stdcall HWND_UserUnmarshal(ptr ptr ptr)




@ stdcall HENHMETAFILE_UserFree64() HENHMETAFILE_UserFree
@ stdcall HENHMETAFILE_UserMarshal64() HENHMETAFILE_UserMarshal
@ stdcall HENHMETAFILE_UserSize64() HENHMETAFILE_UserSize
@ stdcall HENHMETAFILE_UserUnmarshal64() HENHMETAFILE_UserUnmarshal
@ stdcall HGLOBAL_UserFree64() HGLOBAL_UserFree
@ stdcall HGLOBAL_UserMarshal64() HGLOBAL_UserMarshal
@ stdcall HGLOBAL_UserSize64() HGLOBAL_UserSize
@ stdcall HGLOBAL_UserUnmarshal64() HGLOBAL_UserUnmarshal
@ stdcall HICON_UserFree64() HICON_UserFree
@ stdcall HICON_UserMarshal64() HICON_UserMarshal
@ stdcall HICON_UserSize64() HICON_UserSize
@ stdcall HICON_UserUnmarshal64() HICON_UserUnmarshal
@ stdcall HMENU_UserFree64() HMENU_UserFree
@ stdcall HMENU_UserMarshal64() HMENU_UserMarshal
@ stdcall HMENU_UserSize64() HMENU_UserSize
@ stdcall HMENU_UserUnmarshal64() HMENU_UserUnmarshal
@ stdcall HMETAFILEPICT_UserFree64() HMETAFILEPICT_UserFree
@ stdcall HMETAFILEPICT_UserMarshal64() HMETAFILEPICT_UserMarshal
@ stdcall HMETAFILEPICT_UserSize64() HMETAFILEPICT_UserSize
@ stdcall HMETAFILEPICT_UserUnmarshal64() HMETAFILEPICT_UserUnmarshal
@ stdcall HMETAFILE_UserFree64() HMETAFILE_UserFree
@ stdcall HMETAFILE_UserMarshal64() HMETAFILE_UserMarshal
@ stdcall HMETAFILE_UserSize64() HMETAFILE_UserSize
@ stdcall HMETAFILE_UserUnmarshal64() HMETAFILE_UserUnmarshal
@ stdcall HPALETTE_UserFree64() HPALETTE_UserFree
@ stdcall HPALETTE_UserMarshal64() HPALETTE_UserMarshal
@ stdcall HPALETTE_UserSize64() HPALETTE_UserSize
@ stdcall HPALETTE_UserUnmarshal64() HPALETTE_UserUnmarshal
@ stdcall HWND_UserFree64() HWND_UserFree
@ stdcall HWND_UserMarshal64() HWND_UserMarshal
@ stdcall HWND_UserSize64() HWND_UserSize
@ stdcall HWND_UserUnmarshal64() HWND_UserUnmarshal

# HkOleRegisterObject
@ stdcall IIDFromString(wstr ptr)
@ stdcall IsAccelerator(long long ptr ptr)
@ stdcall IsEqualGUID(ptr ptr)
@ stub IsValidIid
@ stdcall IsValidInterface(ptr)
@ stub IsValidPtrIn
@ stub IsValidPtrOut
@ stdcall MkParseDisplayName(ptr wstr ptr ptr)
@ stdcall MonikerCommonPrefixWith(ptr ptr ptr)
@ stub MonikerRelativePathTo
@ stdcall OleBuildVersion()
@ stdcall OleConvertIStorageToOLESTREAM(ptr ptr)
@ stub OleConvertIStorageToOLESTREAMEx
@ stdcall OleConvertOLESTREAMToIStorage(ptr ptr ptr)
@ stub OleConvertOLESTREAMToIStorageEx
@ stdcall OleCreate(ptr ptr long ptr ptr ptr ptr)
@ stdcall OleCreateDefaultHandler(ptr ptr ptr ptr)
@ stdcall OleCreateEmbeddingHelper(ptr ptr long ptr ptr ptr)
@ stub OleCreateEx
@ stdcall OleCreateFromData(ptr ptr long ptr ptr ptr ptr)
@ stdcall OleCreateFromDataEx(ptr ptr long long long ptr ptr ptr ptr ptr ptr ptr)
@ stdcall OleCreateFromFile(ptr wstr ptr long ptr ptr ptr ptr)
@ stdcall OleCreateFromFileEx(ptr wstr ptr long long long ptr ptr ptr ptr ptr ptr ptr)
@ stdcall OleCreateLink(ptr ptr long ptr ptr ptr ptr)
@ stub OleCreateLinkEx
@ stdcall OleCreateLinkFromData(ptr ptr long ptr ptr ptr ptr)
@ stub OleCreateLinkFromDataEx
@ stdcall OleCreateLinkToFile(ptr ptr long ptr ptr ptr ptr)
@ stub OleCreateLinkToFileEx
@ stdcall OleCreateMenuDescriptor(long ptr)
@ stdcall OleCreateStaticFromData(ptr ptr long ptr ptr ptr ptr)
@ stdcall OleDestroyMenuDescriptor(long)
@ stdcall OleDoAutoConvert(ptr ptr)
@ stdcall OleDraw(ptr long long ptr)
@ stdcall OleDuplicateData(long long long)
@ stdcall OleFlushClipboard()
@ stdcall OleGetAutoConvert(ptr ptr)
@ stdcall OleGetClipboard(ptr)
@ stdcall OleGetIconOfClass(ptr ptr long)
@ stdcall OleGetIconOfFile(wstr long)
@ stdcall OleInitialize(ptr)
@ stdcall OleInitializeWOW(long long)
@ stdcall OleIsCurrentClipboard(ptr)
@ stdcall OleIsRunning(ptr)
@ stdcall OleLoad(ptr ptr ptr ptr)
@ stdcall OleLoadFromStream(ptr ptr ptr)
@ stdcall OleLockRunning(ptr long long)
@ stdcall OleMetafilePictFromIconAndLabel(long ptr ptr long)
@ stdcall OleNoteObjectVisible(ptr long)
@ stdcall OleQueryCreateFromData(ptr)
@ stdcall OleQueryLinkFromData(ptr)
@ stdcall OleRegEnumFormatEtc(ptr long ptr)
@ stdcall OleRegEnumVerbs(ptr ptr)
@ stdcall OleRegGetMiscStatus(ptr long ptr)
@ stdcall OleRegGetUserType(ptr long ptr)
@ stdcall OleRun(ptr)
@ stdcall OleSave(ptr ptr long)
@ stdcall OleSaveToStream(ptr ptr)
@ stdcall OleSetAutoConvert(ptr ptr)
@ stdcall OleSetClipboard(ptr)
@ stdcall OleSetContainedObject(ptr long)
@ stdcall OleSetMenuDescriptor(long long long ptr ptr)
@ stdcall OleTranslateAccelerator(ptr ptr ptr)
@ stdcall OleUninitialize()
@ stub OpenOrCreateStream
@ stdcall ProgIDFromCLSID(ptr ptr)
@ stdcall PropStgNameToFmtId(wstr ptr)
@ stdcall PropSysAllocString(wstr)
@ stdcall PropSysFreeString(wstr)
@ stdcall PropVariantClear(ptr)
@ stdcall PropVariantCopy(ptr ptr)
@ stdcall ReadClassStg(ptr ptr)
@ stdcall ReadClassStm(ptr ptr)
@ stdcall ReadFmtUserTypeStg(ptr ptr ptr)
@ stub ReadOleStg
@ stub ReadStringStream
@ stdcall RegisterDragDrop(long ptr)
@ stdcall ReleaseStgMedium(ptr)
@ stdcall RevokeDragDrop(long)
@ stdcall SNB_UserFree(ptr ptr)
@ stdcall SNB_UserMarshal(ptr ptr ptr)
@ stdcall SNB_UserSize(ptr long ptr)
@ stdcall SNB_UserUnmarshal(ptr ptr ptr)
@ stdcall STGMEDIUM_UserFree(ptr ptr)
@ stdcall STGMEDIUM_UserMarshal(ptr ptr ptr)
@ stdcall STGMEDIUM_UserSize(ptr long ptr)
@ stdcall STGMEDIUM_UserUnmarshal(ptr ptr ptr)
@ stdcall SetConvertStg(ptr long)
@ stub SetDocumentBitStg
@ stdcall SetErrorInfo(long ptr)
@ stdcall StgConvertPropertyToVariant(ptr long ptr ptr)
@ stdcall StgConvertVariantToProperty(ptr long ptr ptr long long ptr)
@ stdcall StgCreateDocfile(wstr long long ptr)
@ stdcall StgCreateDocfileOnILockBytes(ptr long long ptr)
@ stdcall StgCreatePropSetStg(ptr long ptr)
@ stdcall StgCreatePropStg(ptr ptr ptr long long ptr)
@ stdcall StgCreateStorageEx(wstr long long long ptr ptr ptr ptr)
@ stub StgGetIFillLockBytesOnFile
@ stub StgGetIFillLockBytesOnILockBytes
@ stdcall StgIsStorageFile(wstr)
@ stdcall StgIsStorageILockBytes(ptr)
@ stub StgOpenAsyncDocfileOnIFillLockBytes
@ stdcall StgOpenPropStg(ptr ptr long long ptr)
@ stdcall StgOpenStorage(wstr ptr long ptr long ptr)
@ stdcall StgOpenStorageEx(wstr long long long ptr ptr ptr ptr)
# StgOpenStorageOnHandle
@ stdcall StgOpenStorageOnILockBytes(ptr ptr long ptr long ptr)
# StgPropertyLengthAsVariant
@ stdcall StgSetTimes(wstr ptr ptr ptr )
@ stdcall StringFromCLSID(ptr ptr)
@ stdcall StringFromGUID2(ptr ptr long)
@ stdcall StringFromIID(ptr ptr) StringFromCLSID
@ stub UpdateDCOMSettings
@ stub UtConvertDvtd16toDvtd32
@ stub UtConvertDvtd32toDvtd16
@ stub UtGetDvtd16Info
@ stub UtGetDvtd32Info
@ stdcall WdtpInterfacePointer_UserFree(ptr)
@ stdcall WdtpInterfacePointer_UserMarshal(ptr long ptr ptr ptr)
@ stdcall WdtpInterfacePointer_UserSize(ptr long long ptr ptr)
@ stdcall WdtpInterfacePointer_UserUnmarshal(ptr ptr ptr ptr)
@ stdcall WriteClassStg(ptr ptr)
@ stdcall WriteClassStm(ptr ptr)
@ stdcall WriteFmtUserTypeStg(ptr long ptr)
@ stub WriteOleStg
@ stub WriteStringStream
