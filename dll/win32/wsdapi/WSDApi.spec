@ stdcall -stub WSDAddFirewallCheck(long ptr)
@ stdcall -stub WSDAllocateLinkedMemory(ptr long)
@ stdcall -stub WSDAttachLinkedMemory(ptr ptr)
@ stdcall -stub WSDCancelNetworkChangeNotify(ptr)
@ stdcall -stub WSDCompareEndpoints(ptr ptr)
@ stdcall -stub WSDCopyEndpoint(ptr ptr)
@ stdcall -stub WSDCopyNameList(ptr ptr)
@ stdcall -stub WSDCreateDeviceHost(ptr ptr ptr)
@ stdcall -stub WSDCreateDeviceHost2(ptr ptr ptr ptr ptr)
@ stdcall -stub WSDCreateDeviceHostAdvanced(ptr ptr ptr long ptr)
@ stdcall -stub WSDCreateDeviceProxy(str str ptr ptr)
@ stdcall -stub WSDCreateDeviceProxy2(str str ptr ptr long ptr)
@ stdcall -stub WSDCreateDeviceProxyAdvanced(str ptr str ptr ptr)
@ stdcall -stub WSDCreateDiscoveryProvider(ptr ptr)
@ stdcall -stub WSDCreateDiscoveryProvider2(ptr ptr long ptr)
@ stdcall -stub WSDCreateDiscoveryPublisher(ptr ptr)
@ stdcall -stub WSDCreateDiscoveryPublisher2(ptr ptr str ptr)
@ stdcall -stub WSDCreateHttpAddress(ptr)
@ stdcall -stub WSDCreateHttpMessageParameters(ptr)
@ stdcall -stub WSDCreateHttpTransport(ptr ptr ptr)
@ stdcall -stub WSDCreateMetadataAgent(long long long long ptr)
@ stdcall -stub WSDCreateOutboundAttachment(ptr)
@ stdcall -stub WSDCreateUdpAddress(ptr)
@ stdcall -stub WSDCreateUdpMessageParameters(ptr)
@ stdcall -stub WSDCreateUdpTransport(ptr)
@ stdcall -stub WSDDetachLinkedMemory(ptr)
@ stdcall -stub WSDFreeLinkedMemory(ptr)
@ stdcall -stub WSDGenerateFault(str str str str ptr ptr)
@ stub WSDGenerateFaultEx ;Lol sneak MS trying to hide this one
@ stdcall -stub WSDGenerateRandomDelay(long long long long)
@ stdcall -stub WSDGetConfigurationOption(long str long)
@ stdcall -stub WSDNotifyNetworkChange(long long ptr)
@ stdcall -stub WSDProcessFault(long ptr long)
@ stdcall -stub WSDRemoveFirewallCheck(ptr)
@ stdcall -stub WSDSetConfigurationOption(long ptr long)
@ stdcall -stub WSDUriDecode(str long ptr ptr)
@ stdcall -stub WSDUriEncode(str long ptr ptr)
@ stdcall -stub WSDXMLAddChild(ptr ptr)
@ stdcall -stub WSDXMLAddSibling(ptr ptr)
@ stdcall -stub WSDXMLBuildAnyForSingleElement(ptr str ptr)
@ stdcall -stub WSDXMLCleanupElement(ptr)
@ stdcall -stub WSDXMLCompareNames(ptr ptr)
@ stdcall -stub WSDXMLCreateContext(ptr)
@ stdcall -stub WSDXMLGetNameFromBuiltinNamespace(str str ptr)
@ stdcall -stub WSDXMLGetValueFromAny(str str ptr ptr)
