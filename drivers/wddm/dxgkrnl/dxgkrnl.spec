@ stub -version=0x600+ DpiGetDriverVersion ;9
@ stub -version=0x600+ DpiGetDxgAdapter ;10
@ stub -version=0x600+ DpiGetSchedulerCallbackState ;11
@ stub -version=0x600+ DpiSetSchedulerCallbackState ;12
@ stub -version=0x600+ DpSynchronizeExecution ;8
@ stub -version=0x600+ DxgCoreInterface ;13
@ stub -version=0x600+ DxgkSqmAddToStream ;14
@ stub -version=0x600+ DxgkSqmCommonGeneric ;15
@ stub -version=0x600+ DxgkSqmCreateDwordStreamEntry ;16
@ stub -version=0x600+ DxgkSqmCreateStringStreamEntry ;17
@ stub -version=0x600+ DxgkSqmGenericDword ;18
@ stub -version=0x600+ DxgkSqmGenericDword64 ;19
@ stub -version=0x600+ g_loggerInfo ;26
@ stub -version=0x600+ g_TdrConfig ;6
@ stub -version=0x600+ g_TdrForceTimeout ;7
@ stub -version=0x600+ TdrCompleteRecoveryContext ;1
@ stub -version=0x600+ TdrCreateRecoveryContext	;2
@ stub -version=0x600+ TdrIsRecoveryRequired ;3 
@ stub -version=0x600+ TdrIsTimeoutForcedFlip ;4
@ stub -version=0x600+ TdrResetFromTimeout ;5
@ stub -version=0x600+ TraceDxgkBlockThread ;20
@ stub -version=0x600+ TraceDxgkContext ;21
@ stub -version=0x600+ TraceDxgkDevice ;22
@ stub -version=0x600+ TraceDxgkFunctionProfiler ;23	
@ stub -version=0x600+ TraceDxgkPerformanceWarning ;24
@ stub -version=0x600+ TraceDxgkPresentHistory ;25

;Windows 8+ 
@ stub -version=0x602+ DxgkSqmCommonGeneric ;26
@ stub -version=0x602+ DxgkSqmCreateDwordStreamEntry ;27
@ stub -version=0x602+ DxgkSqmCreateStringStreamEntry ;28
@ stub -version=0x602+ DxgkSqmGenericDword ;29
@ stub -version=0x602+ DxgkSqmGenericDword64 ;30
@ stub -version=0x602+ DxgkSqmGenericString ;31
@ stub -version=0x602+ DxgkSqmOptedIn ;32
@ stub -version=0x602+ DxgkSqmSetDword ;33
@ stub -version=0x602+ TraceDxgkBlockThread ;34
@ stub -version=0x602+ TraceDxgkContext ;35
@ stub -version=0x602+ TraceDxgkDevice ;36
@ stub -version=0x602+ TraceDxgkFunctionProfiler ;37
@ stub -version=0x602+ TraceDxgkPerformanceWarning ;38
@ stub -version=0x602+ DxgkSqmSetDword ;39

