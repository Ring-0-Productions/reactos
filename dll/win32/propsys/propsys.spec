  3 stub GetProxyDllInfo

400 stdcall -stub PROPSYS_400()
402 stdcall -stub PROPSYS_402()
403 stdcall -stub PROPSYS_403()
404 stdcall -stub PROPSYS_404()
405 stdcall -stub PROPSYS_405()
406 stdcall -stub PROPSYS_406()
407 stdcall -stub PROPSYS_407()
408 stdcall -stub PROPSYS_408()
409 stdcall -stub PROPSYS_409()
410 stdcall -stub PROPSYS_410()
411 stdcall -stub PROPSYS_411()
412 stdcall -stub PROPSYS_412()
413 stdcall -stub PROPSYS_413()
414 stdcall -stub PROPSYS_414()
415 stdcall -stub PROPSYS_415()
416 stdcall -stub PROPSYS_416()
417 stdcall -stub PROPSYS_417()
418 stdcall -stub PROPSYS_418()
420 stdcall -stub PROPSYS_420()
421 stdcall -stub PROPSYS_421()
422 stdcall -stub PROPSYS_422()

@ stub ClearPropVariantArray
@ stub ClearVariantArray
@ stdcall -private DllCanUnloadNow()
@ stdcall -private DllGetClassObject(ptr ptr ptr)
@ stdcall -private DllRegisterServer()
@ stdcall -private DllUnregisterServer()
@ stub InitPropVariantFromBooleanVector
@ stdcall InitPropVariantFromBuffer(ptr long ptr)
@ stdcall InitPropVariantFromCLSID(ptr ptr)
@ stub InitPropVariantFromDoubleVector
@ stub InitPropVariantFromFileTime
@ stub InitPropVariantFromFileTimeVector
@ stdcall InitPropVariantFromGUIDAsString(ptr ptr)
@ stub InitPropVariantFromInt16Vector
@ stub InitPropVariantFromInt32Vector
@ stub InitPropVariantFromInt64Vector
@ stub InitPropVariantFromPropVariantVectorElem
@ stub InitPropVariantFromResource
@ stub InitPropVariantFromStrRet
@ stub InitPropVariantFromStringAsVector
@ stub InitPropVariantFromStringVector
@ stub InitPropVariantFromUInt16Vector
@ stub InitPropVariantFromUInt32Vector
@ stub InitPropVariantFromUInt64Vector
@ stub InitPropVariantVectorFromPropVariant
@ stub InitVariantFromBooleanArray
@ stdcall InitVariantFromBuffer(ptr long ptr)
@ stub InitVariantFromDoubleArray
@ stub InitVariantFromFileTime
@ stub InitVariantFromFileTimeArray
@ stdcall InitVariantFromGUIDAsString(ptr ptr)
@ stub InitVariantFromInt16Array
@ stub InitVariantFromInt32Array
@ stub InitVariantFromInt64Array
@ stub InitVariantFromResource
@ stub InitVariantFromStrRet
@ stub InitVariantFromStringArray
@ stub InitVariantFromUInt16Array
@ stub InitVariantFromUInt32Array
@ stub InitVariantFromUInt64Array
@ stub InitVariantFromVariantArrayElem
@ stub PSCoerceToCanonicalValue
@ stub PSCreateAdapterFromPropertyStore
@ stub PSCreateDelayedMultiplexPropertyStore
@ stdcall PSCreateMemoryPropertyStore(ptr ptr)
@ stdcall -stub PSCreateMultiplexPropertyStore()
@ stdcall -stub PSCreatePropertyChangeArray()
@ stdcall -stub PSCreatePropertyStoreFromObject()
@ stdcall -stub PSCreatePropertyStoreFromPropertySetStorage()
@ stdcall -stub PSCreateSimplePropertyChange()
@ stdcall -stub PSEnumeratePropertyDescriptions()
@ stdcall -stub PSFormatForDisplay()
@ stdcall -stub PSFormatForDisplayAlloc()
@ stdcall -stub PSFormatPropertyValue()
@ stdcall -stub PSGetItemPropertyHandler()
@ stdcall -stub PSGetItemPropertyHandlerWithCreateObject()
@ stdcall -stub PSGetNameFromPropertyKey(ptr ptr)
@ stub PSGetNamedPropertyFromPropertyStorage
@ stdcall PSGetPropertyDescription(ptr ptr ptr)
@ stub PSGetPropertyDescriptionByName
@ stdcall PSGetPropertyDescriptionListFromString(wstr ptr ptr)
@ stub PSGetPropertyFromPropertyStorage
@ stdcall PSGetPropertyKeyFromName(wstr ptr)
@ stdcall PSGetPropertySystem(ptr ptr)
@ stub PSGetPropertyValue
@ stub PSLookupPropertyHandlerCLSID
@ stdcall PSPropertyKeyFromString(wstr ptr)
@ stdcall PSRefreshPropertySchema()
@ stdcall PSRegisterPropertySchema(wstr)
@ stub PSSetPropertyValue
@ stdcall PSStringFromPropertyKey(ptr ptr long)
@ stdcall PSUnregisterPropertySchema(wstr)
@ stdcall PropVariantChangeType(ptr ptr long long)
@ stdcall PropVariantCompareEx(ptr ptr long long)
@ stub PropVariantGetBooleanElem
@ stub PropVariantGetDoubleElem
@ stub PropVariantGetElementCount
@ stub PropVariantGetFileTimeElem
@ stub PropVariantGetInt16Elem
@ stub PropVariantGetInt32Elem
@ stub PropVariantGetInt64Elem
@ stub PropVariantGetStringElem
@ stub PropVariantGetUInt16Elem
@ stub PropVariantGetUInt32Elem
@ stub PropVariantGetUInt64Elem
@ stub PropVariantToBSTR
@ stdcall PropVariantToBoolean(ptr ptr)
@ stub PropVariantToBooleanVector
@ stub PropVariantToBooleanVectorAlloc
@ stub PropVariantToBooleanWithDefault
@ stdcall PropVariantToBuffer(ptr ptr long)
@ stdcall PropVariantToDouble(ptr ptr)
@ stub PropVariantToDoubleVector
@ stub PropVariantToDoubleVectorAlloc
@ stub PropVariantToDoubleWithDefault
@ stub PropVariantToFileTime
@ stub PropVariantToFileTimeVector
@ stub PropVariantToFileTimeVectorAlloc
@ stdcall PropVariantToGUID(ptr ptr)
@ stdcall PropVariantToInt16(ptr ptr)
@ stub PropVariantToInt16Vector
@ stub PropVariantToInt16VectorAlloc
@ stub PropVariantToInt16WithDefault
@ stdcall PropVariantToInt32(ptr ptr)
@ stub PropVariantToInt32Vector
@ stub PropVariantToInt32VectorAlloc
@ stub PropVariantToInt32WithDefault
@ stdcall PropVariantToInt64(ptr ptr)
@ stub PropVariantToInt64Vector
@ stub PropVariantToInt64VectorAlloc
@ stub PropVariantToInt64WithDefault
@ stub PropVariantToStrRet
@ stdcall PropVariantToString(ptr ptr long)
@ stdcall PropVariantToStringAlloc(ptr ptr)
@ stub PropVariantToStringVector
@ stub PropVariantToStringVectorAlloc
@ stdcall PropVariantToStringWithDefault(ptr wstr)
@ stdcall PropVariantToUInt16(ptr ptr)
@ stub PropVariantToUInt16Vector
@ stub PropVariantToUInt16VectorAlloc
@ stub PropVariantToUInt16WithDefault
@ stdcall PropVariantToUInt32(ptr ptr)
@ stub PropVariantToUInt32Vector
@ stub PropVariantToUInt32VectorAlloc
@ stub PropVariantToUInt32WithDefault
@ stdcall PropVariantToUInt64(ptr ptr)
@ stdcall -stub PropVariantToUInt64Vector()
@ stdcall -stub PropVariantToUInt64VectorAlloc()
@ stdcall -stub PropVariantToUInt64WithDefault()
@ stdcall -stub PropVariantToVariant()
@ stdcall -stub StgDeserializePropVariant()
@ stdcall -stub StgSerializePropVariant()
@ stdcall -stub VariantCompare()
@ stdcall -stub VariantGetBooleanElem()
@ stdcall -stub VariantGetDoubleElem()
@ stdcall -stub VariantGetElementCount()
@ stdcall -stub VariantGetInt16Elem()
@ stdcall -stub VariantGetInt32Elem()
@ stdcall -stub VariantGetInt64Elem()
@ stdcall -stub VariantGetStringElem()
@ stdcall -stub VariantGetUInt16Elem()
@ stdcall -stub VariantGetUInt32Elem()
@ stdcall -stub VariantGetUInt64Elem()
@ stdcall -stub VariantToBoolean()
@ stdcall -stub VariantToBooleanArray()
@ stdcall -stub VariantToBooleanArrayAlloc()
@ stdcall -stub VariantToBooleanWithDefault()
@ stdcall -stub VariantToBuffer()
@ stdcall -stub VariantToDosDateTime()
@ stdcall -stub VariantToDouble()
@ stdcall -stub VariantToDoubleArray()
@ stdcall -stub VariantToDoubleArrayAlloc()
@ stdcall -stub VariantToDoubleWithDefault()
@ stdcall -stub VariantToFileTime()
@ stdcall VariantToGUID(ptr ptr)
@ stub VariantToInt16
@ stub VariantToInt16Array
@ stub VariantToInt16ArrayAlloc
@ stub VariantToInt16WithDefault
@ stub VariantToInt32
@ stub VariantToInt32Array
@ stub VariantToInt32ArrayAlloc
@ stub VariantToInt32WithDefault
@ stub VariantToInt64
@ stub VariantToInt64Array
@ stub VariantToInt64ArrayAlloc
@ stub VariantToInt64WithDefault
@ stub VariantToPropVariant
@ stub VariantToStrRet
@ stub VariantToString
@ stub VariantToStringAlloc
@ stub VariantToStringArray
@ stub VariantToStringArrayAlloc
@ stub VariantToStringWithDefault
@ stub VariantToUInt16
@ stub VariantToUInt16Array
@ stub VariantToUInt16ArrayAlloc
@ stub VariantToUInt16WithDefault
@ stub VariantToUInt32
@ stub VariantToUInt32Array
@ stub VariantToUInt32ArrayAlloc
@ stub VariantToUInt32WithDefault
@ stub VariantToUInt64
@ stub VariantToUInt64Array
@ stub VariantToUInt64ArrayAlloc
@ stub VariantToUInt64WithDefault
