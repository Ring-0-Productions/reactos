
@ stdcall LogonIdFromWinStationNameA(ptr ptr ptr)
@ stdcall LogonIdFromWinStationNameW(ptr ptr ptr)
@ stdcall RemoteAssistancePrepareSystemRestore(ptr)
@ stdcall ServerGetInternetConnectorStatus(ptr ptr ptr)
@ stdcall ServerLicensingClose(ptr)
@ stdcall ServerLicensingDeactivateCurrentPolicy(ptr)
@ stdcall ServerLicensingFreePolicyInformation(ptr)
@ stdcall ServerLicensingGetAvailablePolicyIds(ptr ptr ptr)
@ stdcall ServerLicensingGetPolicy(ptr ptr)
@ stdcall ServerLicensingGetPolicyInformationA(ptr ptr ptr ptr)
@ stdcall ServerLicensingGetPolicyInformationW(ptr ptr ptr ptr)
@ stdcall ServerLicensingLoadPolicy(ptr ptr)
@ stdcall ServerLicensingOpenA(ptr)
@ stdcall ServerLicensingOpenW(ptr)
@ stdcall ServerLicensingSetPolicy(ptr ptr ptr)
@ stdcall ServerLicensingUnloadPolicy(ptr ptr)
@ stdcall ServerQueryInetConnectorInformationA(ptr ptr ptr ptr)
@ stdcall ServerQueryInetConnectorInformationW(ptr ptr ptr ptr)
@ stdcall ServerSetInternetConnectorStatus(ptr ptr ptr)
@ stdcall WinStationActivateLicense(ptr ptr ptr ptr)
@ stdcall WinStationAutoReconnect(ptr)
@ stdcall WinStationBroadcastSystemMessage(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationCanLogonProceed(ptr ptr ptr)
@ stdcall WinStationCheckAccess(ptr ptr ptr)
@ stdcall WinStationCheckLoopBack(ptr ptr ptr ptr)
@ stdcall WinStationCloseServer(ptr ptr ptr ptr)
@ stdcall WinStationConnectA(ptr)
@ stdcall WinStationConnectCallback(ptr ptr ptr ptr ptr)
@ stdcall WinStationConnectEx(ptr ptr)
@ stdcall WinStationConnectW(ptr ptr ptr ptr ptr)
@ stdcall WinStationDisconnect(ptr ptr ptr)
@ stdcall WinStationDynVirtualChanRead(ptr ptr ptr ptr ptr)
@ stdcall WinStationDynVirtualChanWrite(ptr ptr ptr ptr)
@ stdcall WinStationEnumerateA(ptr ptr ptr)
@ stdcall WinStationEnumerateLicenses(ptr ptr ptr)
@ stdcall WinStationEnumerateProcesses(ptr ptr)
@ stdcall WinStationEnumerateW(ptr ptr ptr)
@ stdcall WinStationEnumerate_IndexedA(ptr ptr ptr ptr ptr)
@ stdcall WinStationEnumerate_IndexedW(ptr ptr ptr ptr ptr)
@ stdcall WinStationFreeGAPMemory(ptr ptr ptr)
@ stdcall WinStationFreeMemory(ptr)
@ stdcall WinStationFreeUserCertificates(ptr)
@ stdcall WinStationFreeUserCredentials(ptr)
@ stdcall WinStationGenerateLicense(ptr ptr ptr ptr)
@ stdcall WinStationGetAllProcesses(ptr ptr ptr ptr)
@ stdcall WinStationGetConnectionProperty(ptr ptr ptr)
@ stdcall WinStationGetInitialApplication(ptr ptr ptr ptr ptr)
@ stdcall WinStationGetLanAdapterNameA(ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationGetLanAdapterNameW(ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationGetLoggedOnCount(ptr ptr)
@ stdcall WinStationGetMachinePolicy(ptr ptr)
@ stdcall WinStationGetProcessSid(ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationGetTermSrvCountersValue(ptr ptr ptr)
@ stdcall WinStationGetUserCertificates(ptr)
@ stdcall WinStationGetUserCredentials(ptr)
@ stdcall WinStationGetUserProfile(ptr ptr ptr ptr)
@ stdcall WinStationInstallLicense(ptr ptr ptr)
@ stdcall WinStationIsHelpAssistantSession(ptr ptr)
@ stdcall WinStationIsSessionPermitted()
@ stdcall WinStationNameFromLogonIdA(ptr ptr ptr)
@ stdcall WinStationNameFromLogonIdW(ptr ptr ptr)
@ stdcall WinStationNtsdDebug(ptr ptr ptr ptr ptr)
@ stdcall WinStationOpenServerA(ptr)
@ stdcall WinStationOpenServerW(ptr)
@ stdcall WinStationQueryAllowConcurrentConnections()
@ stdcall WinStationQueryEnforcementCore(ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationQueryInformationA(ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationQueryInformationW(ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationQueryLicense(ptr ptr ptr)
@ stdcall WinStationQueryLogonCredentialsW(ptr)
@ stdcall WinStationQueryUpdateRequired(ptr ptr)
@ stdcall WinStationRedirectErrorMessage(ptr ptr)
@ stdcall WinStationRegisterConsoleNotification(ptr ptr ptr)
@ stdcall WinStationRegisterConsoleNotificationEx(ptr ptr ptr ptr)
@ stdcall WinStationRegisterNotificationEvent(ptr ptr ptr ptr)
@ stdcall WinStationRemoveLicense(ptr ptr ptr)
@ stdcall WinStationRenameA(ptr ptr ptr)
@ stdcall WinStationRenameW(ptr ptr ptr)
@ stdcall WinStationRequestSessionsList(ptr ptr ptr)
@ stdcall WinStationReset(ptr ptr ptr)
@ stdcall WinStationSendMessageA(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationSendMessageW(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationSendWindowMessage(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall WinStationServerPing(ptr)
@ stdcall WinStationSetInformationA(ptr ptr ptr ptr ptr)
@ stdcall WinStationSetInformationW(ptr ptr ptr ptr ptr)
@ stdcall WinStationSetPoolCount(ptr ptr ptr)
@ stdcall WinStationShadow(ptr ptr ptr ptr ptr)
@ stdcall WinStationShadowStop(ptr ptr ptr)
@ stdcall WinStationShutdownSystem(ptr ptr)
@ stdcall WinStationSwitchToServicesSession()
@ stdcall WinStationSystemShutdownStarted()
@ stdcall WinStationSystemShutdownWait(ptr ptr)
@ stdcall WinStationTerminateProcess(ptr ptr ptr)
@ stdcall WinStationUnRegisterConsoleNotification(ptr ptr)
@ stdcall WinStationUnRegisterNotificationEvent(ptr)
@ stdcall WinStationUserLoginAccessCheck(ptr ptr ptr ptr)
@ stdcall WinStationVirtualOpen(ptr ptr ptr)
@ stdcall WinStationVirtualOpenEx(ptr ptr ptr ptr)
@ stdcall WinStationWaitSystemEvent(ptr ptr ptr)
@ stdcall _NWLogonQueryAdmin(ptr ptr ptr)
@ stdcall _NWLogonSetAdmin(ptr ptr ptr)
@ stdcall _WinStationAnnoyancePopup(ptr ptr)
@ stdcall _WinStationBeepOpen(ptr ptr ptr)
@ stdcall _WinStationBreakPoint(ptr ptr ptr)
@ stdcall _WinStationCallback(ptr ptr ptr)
@ stdcall _WinStationCheckForApplicationName(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall _WinStationFUSCanRemoteUserDisconnect(ptr ptr ptr)
@ stdcall _WinStationGetApplicationInfo(ptr ptr ptr ptr)
@ stdcall _WinStationNotifyDisconnectPipe()
@ stdcall _WinStationNotifyLogoff()
@ stdcall _WinStationNotifyLogon(ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall _WinStationNotifyNewSession(ptr ptr)
@ stdcall _WinStationOpenSessionDirectory(ptr ptr)
@ stdcall _WinStationReInitializeSecurity(ptr)
@ stdcall _WinStationReadRegistry(ptr)
@ stdcall _WinStationSessionInitialized()
@ stdcall _WinStationShadowTarget(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ stdcall _WinStationShadowTargetSetup(ptr ptr)
@ stdcall _WinStationUpdateClientCachedCredentials(ptr ptr ptr ptr ptr ptr ptr)
@ stdcall _WinStationUpdateSettings(ptr ptr ptr)
@ stdcall _WinStationUpdateUserConfig(ptr)
@ stdcall _WinStationWaitForConnect()

@ stdcall  WinStationFreePropertyValue()