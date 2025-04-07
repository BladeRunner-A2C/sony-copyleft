#ifndef __USB4LOG_H__
#define __USB4LOG_H__

/** @file     Usb4Log.h 
    @brief    USB4 Internal Enum Logging Utility
    @details  USB4 Internal Enum Logging Utility
    @note     
    @ref      Copyright (c) 2020 Qualcomm Technologies Incorporated.
              All Rights Reserved.
              Qualcomm Confidential and Proprietary.
**/

//------------------------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------------------------

#define USB4_LOG_SIZE_LOW   (128)
#define USB4_LOG_SIZE_MED   (256)
#define USB4_LOG_SIZE_HIGH  (512)

#define USB4_LOG_CFG_SIZE   (USB4_LOG_SIZE_LOW)
#define USB4_LOG_INF_SIZE   (USB4_LOG_SIZE_HIGH)
#define USB4_LOG_ERR_SIZE   (USB4_LOG_SIZE_LOW)
#define USB4_LOG_PD_SIZE    (USB4_LOG_SIZE_LOW)
#define USB4_LOG_REG_SIZE   (USB4_LOG_SIZE_MED)
#define USB4_LOG_PHY_SIZE   (USB4_LOG_SIZE_MED)
#define USB4_LOG_CM_SIZE    (USB4_LOG_SIZE_HIGH)

typedef enum _USB4_LOG_ENUM {

  Usb4LogInvalid = 0,

  //----------------------------------------------------------------------------------------------
  // USB4_PLATFORM
  //----------------------------------------------------------------------------------------------
  Usb4Platform__Err_NullPtr__line,
  Usb4ClkEnable__Err_Invalid_Param__ClockProtocol_ClockName,
  Usb4ClkEnable__Params__ClockName_Freq_Div,
  Usb4ClkEnable__Err_Failed_GetClockID__ClockName_HrIdx,
  Usb4ClkEnable__Err_Failed_SetClockFreqHz__ClockName_ClockId_Freq,  
  Usb4ClkEnable__SetClockFreqHz__ClockName_ClockId_Freq,
  Usb4ClkEnable__Err_Failed_EnableClock__ClockName_ClockId_Freq,
  Usb4ClkEnable__Err_Failed_SetClockDivider__ClockName_ClockId_Div,
  Usb4GccEnableClocks__Params__Core_BitField,

  Usb4ClkDisable__Err_Invalid_Param__ClockProtocol_ClockName,
  Usb4ClkDisable__Err_Failed_GetClockID__ClockName_HrIdx,
  Usb4ClkDisable__Err_Failed_EnableClock__ClockName_ClockId,

  Usb4ClkReset__Err_Invalid_Param__ClockProtocol_ClockName,
  Usb4ClkReset__Err_Failed_GetClockID__ClockName_HrIdx,
  Usb4ClkReset__Err_Failed_ResetClock__ClockName_ClockId,  

  Usb4PlatformClkInit__Err_Invalid_Param__ClockProtocol_Clocks_Count,
  Usb4PlatformClkInit__Params__HrIdx_ClockProtocol_Clocks_Count,
  Usb4PlatformClkInit__Err_Failed_ClkEnable__ClockName,
  Usb4PlatformClkUnInit__Err_Invalid_Param__ClockProtocol_Clocks_Count,
  Usb4PlatformClkUnInit__Params__HrIdx_ClockProtocol_Clocks_Count,
  Usb4PlatformClkUnInit__Err_Failed_ClkDisable__ClockName,

  AssertGccClks__ErrInvalidParam__ClockProtocol,
  AssertGccClks__Err_Failed_GetClockID__ClockName,
  AssertGccClks__Err_Failed_GccAssert__ClockName,
  AssertGccClks__Err_Failed_GccDeAssert__ClockName,

  Usb4PlatformAhbConfgUsb3Mode__Entry__ConfigProtocol,
  Usb4PlatformPhyAssert__Entry__ConfigProtocol,
  Usb4PlatformPhyDeAssert__Entry__ConfigProtocol,
  Usb4PlatformPhyConfigure__Entry__ConfigProtocol,
  Usb4PlatformPhyConfigPostUcEnable__Entry__ConfigProtocol,
  Usb4PlatformPhyWaitForCl0__Entry__ConfigProtocol,
  Usb4PlatformStorePersistentData__Entry__ConfigProtocol,
  Usb4PlatformWriteBackPersistentData__Entry__ConfigProtocol,
  Usb4PlatformPhySleep__Entry__ConfigProtocol,
  Usb4PlatformPhyWake__Entry__ConfigProtocol,
  Usb4PlatformCableConnectedHandler__Entry__ConfigProtocol,
  Usb4PlatformBringUpLink__Entry__ConfigProtocol_PdInfo,
  Usb4PlatformBringUpLink__PdInfo__CC_Type_Gen,
  Usb4PlatformWake__Entry__ConfigProtocol,
  Usb4PlatformEnterSleep__Entry__ConfigProtocol,
  Usb4PlatformUnInit__Entry__ConfigProtocol,

  Usb4PlatformInit__Err_Invalid_Param__HrIdx,
  Usb4PlatformInit__Params__HrIdx,
  Usb4PlatformInit__Info__HiBaseAddr,
  Usb4PlatformInit__Info__UcPerBaseAddr,
  Usb4PlatformInit__Info__UcRamBaseAddr,
  Usb4PlatformInit__Info__PgPropBaseAddr,
  Usb4PlatformInit__Info__UsbApCfgPropAddr,
  Usb4PlatformInit__Info__Lane0BaseAddr,
  Usb4PlatformInit__Info__Lane1BaseAddr,
  Usb4PlatformInit__Info__SideBandBaseAddr,
  Usb4PlatformInit__Info__NumLanes_PhyMode_OpGen,
  Usb4DpAuxReadExpected4BytesError__Params__ReceivedNumBytes,

  getclk__Params__Core__CouldNotFindClkMask,
  AssertGccClks__Params__Core_CouldNotFindClockForMsk,
  Usb4GccEnableClocks__Params__Core_CouldNotFindClockForMsk,

  Usb4PlatformInit__Param__CreatingPlatformForCoreIndex,
  Usb4PlatformUcLoadFW__Params__LoadingCompiledFWVersion,
  Usb4PlatformUcHandleUcEvents__Error__InvalidOpCodeError,
  Usb4PlatformUcMsgRingPrintMsgs__Params__uC_Msg,

  Usb4PlatformUcHandleUcEventsError__Params__Core_uCSignaledError,
  Usb4PlatformUcHandleUcEventsInvalidOpCode__Error,
  Usb4PlatformUcHandleUcEventsError__Params__ExceptionPC,
  Usb4PlatformUcHandleUcEventsError__Params__FatalErrorPC,
  Usb4PlatformUcHandleUcEventsError__Params__WarningPC,
  Usb4PlatformUcHandleUcEventsError__Params__HSEFailed,
  Usb4PlatformUcHandleUcEventsHIAResetFailed__Error,
  Usb4PlatformUcHandleUcEventsError__Params__HwVersionMismatchExpectedVersion,
  Usb4PlatformUcHandleUcEventsUnknown__Error,
  Usb4PlatformUcHandleUcEventsUCSignaledExitOffline__Warn__Core,
  Usb4PlatformUcHandleUcEventsUCSignaledDisconnect__Warn__Core,
  Usb4PlatformUcHandleUcEventsDisconnectLtLroffReceivedFromLinkPartner__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectOurSbrxWasDrivenLowForTDisconnectRxTimeByLinkPartner__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectFwInitiatedDisconnectDueToTrainingAbortIndicastionFromPortGroup__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectFwInitiatedDisconnectDueToBondingFailIndicationFromPortGroup__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectFwSendsThisReasonAsPartOfDownstreamPortResetFlow__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectComplianceSoftwareOrCmIssuedPortOpoerationRouterOfflineModeWithEOM1__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectQdriverSentPhysicalDisconnectCommandWhileLinkWasStillEstablished__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectLane0WasDisabledByCmViaConfigSpace__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectReceivedLtFallForLane0FromDevice__Warn__Reason,
  Usb4PlatformUcHandleUcEventsDisconnectUnknown__Warn__Reason,

  assertgccrmiscesets__Params__SystemClockCoreXTookuSecToStart,
  assertgccresets__Params__SystemClockCore0TookuSecToStart,
  assertgccresets__Params__SystemClockCoreXTookuSecToStart,

  //----------------------------------------------------------------------------------------------
  // USB4_UC_UTIL
  //----------------------------------------------------------------------------------------------
  Usb4UcMsgRingPush__Entry__HrIdx_PushIdx,
  Usb4UcMsgRingPeek__Entry__HrIdx_PrintIdx,
  Usb4UcMsgRingPop__Entry__HrIdx_NumMsgs,
  Usb4UcMsgRingUnInit__Entry__HrIdx,
  Usb4UcMsgRingInit__Entry__HrIdx_MaxEntries_EntrySizeBytes,

  Usb4UcLoadFirmware__Entry__HrIdx,
  Usb4UcLoadFirmware__Err_Failed_LocateEfiPil,
  Usb4UcLoadFirmware__Err_Failed_ProcessPil,
  Usb4UcLoadFirmware__Exit__HrIdx,

  Usb4UcIoctl__Err_Invalid_Param__This_IoctlPtr,
  Usb4UcIoctl__Entry__HrIdx_IoctlPtr,
  Usb4UcIoctl__Err_Ioctl_Failed__HrIdx_IoctlPtr,

  Usb4UcPollEvents__Entry__HrIdx_Curr_Next,

  Usb4UcDeActivate__Entry__HrIdx,
  Usb4UcDeActivate__Err__Failed_Usb4UcMsgRingUnInit_HrIdx,

  Usb4UcActivate__Entry__HrIdx_Enabled,
  Usb4UcActivate__Err_Already_Enabled,
  Usb4UcActivate__Err_Enable_Timeout,
  Usb4UcActivate__Err_Failed_MsgRingInit__HrIdx,

  //----------------------------------------------------------------------------------------------
  // USB4_PLATFORM_RING
  //----------------------------------------------------------------------------------------------
  Usb4RingSetBaseSize__Entry__RingPhyAddr_RingSize,
  Usb4RingSetRingCtrl__Entry__Val_HrIdx_RingIdx_Dir,

  Usb4RingGetProdIndex__Entry__ValPtr_HrIdx_RingIdx_Dir,
  Usb4RingGetProdIndex__Exit__Val_HrIdx_RingIdx_Dir,

  Usb4RingGetConsIndex__Entry__ValPtr_HrIdx_RingIdx_Dir,
  Usb4RingGetConsIndex__Exit__Val_HrIdx_RingIdx_Dir,
  
  Usb4RingSetProdIndex__Entry__Val_HrIdx_RingIdx_Dir,
  Usb4RingSetConsIndex__Entry__Val_HrIdx_RingIdx_Dir,
  Usb4RingSetPdfMask__Entry__Val_HrIdx_RingIdx_Dir,
  Usb4RingSetRxRingVacCtrl__Entry__HrIdx_RingIdx_Dir_Thres,
  Usb4RingGetRxRingVacStatus__Entry__ValPtr_HrIdx_RingIdx_Dir,
  Usb4RingGetRxRingVacStatus__Exit__Value,
  Usb4RingGetIntStatus__Entry__StatePtr_HrIdx_RingIdx_Dir,
  Usb4RingGetIntStatus__Exit__State,
  Usb4RingGetRxVacIntStatus__Entry__StatePtr_HrIdx_RingIdx_Dir,
  Usb4RingGetRxVacIntStatus__Exit__State,
  Usb4RingClearInt__Entry__HrIdx_RingIdx_Dir,
  Usb4RingClearRxVacInt__Entry__HrIdx_RingIdx_Dir,
  Usb4RingEnableInt__Entry__HrIdx_RingIdx_Dir,
  Usb4RingEnableRxVacInt__Entry__HrIdx_RingIdx_Dir,
  Usb4RingDisableInt__Entry__HrIdx_RingIdx_Dir,
  Usb4RingDisableRxVacInt__Entry__HrIdx_RingIdx_Dir,
  Usb4RingPlatformInit__Entry,

  //----------------------------------------------------------------------------------------------
  // USB4_RING
  //----------------------------------------------------------------------------------------------
  Usb4RingSetup__Entry__Ring,
  Usb4RingSetup__Err_Mem_Alloc_Ring_Desc__Ring,
  Usb4RingSetup__Err_Mem_Alloc_Ring_DataBuff__Ring,  
  Usb4RingSetup__Exit_Success__Ring,

  Usb4RingTearDown__Entry__Ring,
  Usb4RingTearDown__Exit__Ring,

  Usb4RingSendPacket__Err_Null_Ptr__Ring_Data,
  Usb4RingSendPacket__Err_Invalid_Param__RingSize_InUseCnt_DataLen,
  Usb4RingSendPacket__Params__HrIdx_RingIdx_ProdIdx_DataLen_InUseCnt,
  Usb4RingSendPacket__Sent__HrIdx_RingIdx_ProdIdx_DataLen_InUseCnt,
  Usb4RingSendPacket__Err_Timeout,

  Usb4RingPollTxDescComp__Err_Null_Ptr__Ring,
  Usb4RingPollTxDescComp__Err_Invalid_Param__RingSize_RingDir,
  Usb4RingPollTxDescComp__Params__HrIdx_RingIdx_ConsIdx_ConsIdxHw_InUseCnt,

  Usb4RingQueueRxDesc__Err_Null_Ptr__Ring,
  Usb4RingQueueRxDesc__Err_Invalid_Param__RingSize_RingDir,
  Usb4RingQueueRxDesc__Err_Overflow__RingSize_InUseCnt,
  Usb4RingQueueRxDesc__Info__HrIdx_RingIdx_Dir_ConsIdx_InUseCnt,

  Usb4RingReceivePacket__Err_Invalid_Param__Ring_DataLen,
  Usb4RingReceivePacket__Err_Invalid_Param__RingSize_DataLen_Dir,
  Usb4RingReceivePacket__Params__HrIdx_RingIdx_Dir_ProdIdx,
  Usb4RingReceivePacket__Packet_Received__ReqStatus_DescDone_CrcErr_BufOflow,
  Usb4RingReceivePacket__Packet_Valid__DataBuff_DataLen_EofPdf_SofPdf,
  Usb4RingReceivePacket__Invalid_Condition_SofPdf_Set_In_RawMode,
  Usb4RingReceivePacket__Params__HrIdx_RingIdx_Dir,

  Usb4RingUnInit__Err_Invalid_Param__Ring,
  Usb4RingUnInit__Params__HrIdx_RingIdx_Dir_Size_Mode,
  Usb4RingUnInit__Err_RingTeardown_Failed__HrIdx_RingIdx_Dir,

  Usb4RingInit__Err_Invalid_Param__Ring_Usb4Config,
  Usb4RingInit__Params__HrIdx_RingIdx_Dir_Size_Mode,
  Usb4RingInit__Err_RingSetup_Failed,

  //----------------------------------------------------------------------------------------------
  // USB4_CTRL
  //----------------------------------------------------------------------------------------------
  Usb4Le32ToBe32__Err_Unaligned__Buff_NumBytes,

  Usb4CtrlPktPrepareTx__Err_Invalid_Param__CtrlPkt_CtrlHeader_EofPdf,
  Usb4CtrlPktPrepareTx__Err_Buff_Too_Small__EofPdf_BuffLen_MaxLen,
  Usb4CtrlPktPrepareTx__Exit_Success__CRC32_TotalLen_HeaderLen_DataLen_EofPdf,

  Usb4CtrlPktPrepareRx__Exit_Success__Len_EofPdf,

  Usb4CtrlPktValidateCrcEofPdfRx__Err__Len_EofPdf,
  Usb4CtrlPktValidateCrcEofPdfRx__Err_Crc_Mismatch__Crc_CalcCrc,

  Usb4CtrlPrintRouteStr__Info__Adp5_Adp4_Adp3_Adp2_Adp1_Adp0,

  Usb4CtrlReqReadWrite__Err_Invalid_Param__Ctrl_SizeDw_Pdf,
  Usb4CtrlReqReadWrite__Err_Req_Pending__Ctrl,
  Usb4CtrlReqReadWrite__Info__RouteStr_Type,
  Usb4CtrlReqReadWrite__Info__CS_AdpNum_Addr_SizeDW_SeqNum_DataLen,

  Usb4CtrlPktRcvdFromTargetRouter__Info__CmSet_RshMatch_RslMatch,
  Usb4CtrlPktRcvdFromTargetRouter__Resp_Info__RsHigh_RsLow, 
  Usb4CtrlPktRcvdFromTargetRouter__Req_Info__RsHigh_RsLow, 

  Usb4CtrlIsRespForRWReq__Resp_Info__Pdf_Addr_Size_AdpNum_CS_SeqNum,
  Usb4CtrlIsRespForRWReq__Req_Info__Pdf_Addr_Size_AdpNum_CS_SeqNum,
 
  Usb4CtrlSendNotifAck__RsHigh_RsLow,
  Usb4CtrlSendNotifAck__Err_Failed_to_send_notif_ack__Status,

  Usb4CtrlSendHotPlugAck__Info__RsHigh_RsLow_AdpNum_PG,
  Usb4CtrlSendHotPlugAck__Err_Failed_to_send_hotplug_ack__Status,

  Usb4CtrlReceiveResp__Err_RdResp_Len_Mismatch,
  Usb4CtrlReceiveResp__RdResp_Matches_Req,
  Usb4CtrlReceiveResp__Err_RdResp_Mismatch_Req,
  Usb4CtrlReceiveResp__WrResp_Matches_Req,
  Usb4CtrlReceiveResp__Err_WrResp_Mismatch_Req,
  Usb4CtrlReceiveResp__Err_Notif__EventCode_AdpNum,
  Usb4CtrlReceiveResp__Err_Other_Evt_Received,  
  Usb4CtrlReceiveResp__Err_Timeout,

  Usb4CtrlHandleNotifErr__Info__RSHigh_RSLow_EventCode,
  Usb4CtrlHandleHpe__Info__RsHigh_RsLow_AdpNum_UPG,

  Usb4CtrlProcessRxPktDefQ__Info_Process_pending_packet__Ctrl,
  Usb4CtrlProcessRxPktDefQ__Err_out_of_order_response__Ctrl_EofPdf,

  Usb4CtrlReceiveEvts__Err_out_of_order_response__Ctrl_EofPdf,

  Usb4CtrlUnInit__Err_Invalid_Param__Ctrl,
  Usb4CtrlUnInit__Info__Ctrl,
  Usb4CtrlUnInit__Err_RingUnInit_Failed__TxRing,
  Usb4CtrlUnInit__Err_RingUnInit_Failed__RxRing,

  Usb4CtrlInit__Err_Invalid_Param__Ctrl_HrIdx_HpeCb_ErrCb,
  Usb4CtrlInit__Info__Ctrl_HrIdx,
  Usb4CtrlInit__Err_Failed_TxRingInit__HrIdx,
  Usb4CtrlInit__Err_Failed_RxRingInit__HrIdx,

  //----------------------------------------------------------------------------------------------
  // USB4_ADP_PORT
  //----------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------
  // USB4_ROUTER
  //----------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------
  // USB4_ROUTER_OP
  //----------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------
  // USB4_PD
  //----------------------------------------------------------------------------------------------
  Usb4PD__Info__Enter,
  Usb4PD__Info__Memptr,
  Usb4PDCtrlMsgHandler__Info,
  Usb4PDCtrlMsgHandlerDeviceEnterUsbRespAck__Info,
  Usb4PDCtrlMsgHandlerReceivedAcceptBeforeTxSent__Warn,
  Usb4PDTxDiscardHandlerReTransmit__Info,
  Usb4PDEngineAttach__Error__State_SubState_Timeout,
  Usb4PDEngineStateMachineHandler__Warn__StatusPdTcpmIntStatusTxFail0x1,
  Usb4PDEngineSendSrcCap__Debug,
  Usb4PDEngineSendDiscoverIdentity__Debug,
  Usb4PDEngineSendDiscoverSvids__Debug,
  Usb4PDEngineSendEnterMode__Debug,
  Usb4PDEngineSendDiscoverModes__Debug,
  Usb4PDEngineSendExitMode__Debug,
  Usb4PDEngineHandleCableDiscoverIdentityResp__Debug,
  Usb4PDEngineHandleCableDiscoverSvidsResp__Debug,
  Usb4PDEngineHandleCableDiscoverSvidsRespNoCableModesToDiscoverContToDeviceEnterMode__Info,
  Usb4PDEngineHandleCableDiscoverModesResp__Debug,
  Usb4PDEngineHandleCableDiscoverModesRespNoMoreCableModesToDiscoverContToEnterMode__Info,
  Usb4PDEngineHandleDeviceSrcCapResp__Debug,
  Usb4PDEngineHandleDeviceDiscoverIdentityResp__Debug,
  Usb4PDEngineHandleDeviceDiscoverSvidsResp__Debug,
  Usb4PDEngineHandleDeviceDiscoverModesResp__Debug,
  Usb4PDEngineHandleCableSoptEnterModeResp__Debug,
  Usb4PDEngineHandleCableSoptEnterModeRespEnterModeRespNackTryToExitMode__Info,
  Usb4PDEngineHandleCableSoptEnterModeRespCableSoptEnterModeResp__Info,
  Usb4PDEngineHandleCableSopttEnterModeResp__Debug,
  Usb4PDEngineHandleCableSopttEnterModeRespEnterModeRespNackTryToExitMode__Info,
  Usb4PDEngineHandleCableSopttEnterModeRespCableSopttEnterModeRespAck__Info,
  Usb4PDEngineHandleDeviceEnterModeResp__Debug,
  Usb4PDEngineHandleDeviceEnterModeRespDeviceEnterModeRespNackTryToExitMode__Info,
  Usb4PDEngineHandleDeviceEnterModeRespDeviceEnterModeRespAck__Info,
  Usb4PDEngineHandleDeviceExitModeResp__Debug,
  Usb4PDEngineHandleDeviceExitModeRespExitModeRespAck__Info,
  Usb4PDEngineParseDiscoverIdentityResponse__Debug,
  Usb4PDEngineParseDiscoverSvidsResponse__Debug,
  Usb4PDEngineParseDiscoverModesResponse__Debug,
  Usb4PDEngineParseDiscoverModesResponseSinkAnswerWithBusy__Info,
  Usb4PDEngineParseDiscoverModesResponse__Params__Svid_NumModes,
  Usb4PDEngineParseDeviceSrcCapResp__Debug,
  Usb4PDPolicyCtorVdmEnterMode__Params__EnterModeNumCableSvidModes,
  Usb4PDTcpmConfigureTcpm__Params_MessageFoundOnRxRightOnTheStart,
  Usb4PDTcpmConfigureTcpmAlertByte0RegPwrStsReceived__Info,
  Usb4PDTcpmConfigureTcpm__Params__TcpcInitStatus,
  Usb4PDTcpmOnCableConnection__Params__ccstatus,
  Usb4PDTcpmOnCableConnection__Params__cc1state_cc2state,
  Usb4PDTcpmOnCableConnection__Params__PlugOrientation,
  Usb4PDTcpmOnCableConnectionNoRaDetected__Info,
  Usb4PDTcpmOnCableConnectionEnableVCONN__Info,
  Usb4PDTcpmOnCableConnection__Params__PWRCONTROL0_PWRCONTROL1,
  Usb4PDTcpmOnCableConnection__Params__tCCDebounceMsToAllowPortEnterAttachState,
  Usb4PDFrameworkInitializedSuccessfully__Info,
  Usb4PDFrameworkUnInitializedSuccessfully__Info,

  //----------------------------------------------------------------------------------------------
  // USB4_CM
  //----------------------------------------------------------------------------------------------
  Usb4CmPollEvts__Entry__CM,
  Usb4CmHiaQueueTransmitSofNotMatching__Params__Sof_Mask,
  Usb4CmHiaQueueTransmitSofNotMatching__Params__Eof_Mask,
  Usb4CmHiaVerifyTransmitedDescAddr__Params__highaddr_lowaddr,
  Usb4CmHiaVerifyTransmitedDescAddr__Params__ExpectedAddr,
  Usb4CmHiaVerifyTransmitedDataLen__Params__DescDataLength_Expected,
  Usb4CmHiaVerifyTransmitedNotDefWaTxRsAlwaysSet__Params__RS_exp,


  Usb4CmHiaVerifyTransmitedErr__Params__DescOffset_Expected,
  Usb4CmHiaVerifyTransmitedErr__Params__RS_DD,
  Usb4CmHiaVerifyRecievedErr__Params__DescAddrHigh_Low,
  Usb4CmHiaVerifyRecievedErr__Params__Expected,
  Usb4CmHiaVerifyRecievedErr__Params_DataLength_Expected,
  Usb4CmHiaVerifyRecievedErr__Params_DescOffset_Expected,
  Usb4CmHiaVerifyRecievedErr__Params__RS_DD,
  Usb4CmRouteControlPacketGotInterdomainRoute0UsingHardCodedValue__Warn,
  Usb4CmRouteControlPacketUnrelatedInterdomainPacketsReceivedDuringActiveHotplugSuspiciousActivity__Warn,
  Usb4CmConfigHardcodedPdConfigToSRCDFP__Info,
  Usb4CmWakeFlowCoreWasWakenUpInISR__Info,
  Usb4CmParseHpeERROR_Params__TopologyID_Adapter,
  Usb4CmUSB4PortHotPlugHandlerCalledFromUnsupportedStateWARNING__Params,
  Usb4CmUSB4PortHotPlugHandlerEnumerationOfTheRouterFailedExpectErrEnumOrErrNua__Info,
  Usb4CmPollForTMUSync__Params__NewRouterFreqOffsetFromMaster_Val,
  Usb4CmPollForTMUSync__Params__LowLimit_HighLimit,
  Usb4CmPollForTMUSyncSyncTook__Params__msec,
  Usb4CmStatelessPacketsHandlerERR_ADDRreceived__Warn,
  Usb4CmStatelessPacketsHandlerERR_ADPreceived__Warn,
  Usb4CmStatelessPacketsHandlerERR_LENreceived__Warn,
  Usb4CmStatelessPacketsHandlerERR_HECreceived__Warn,
  Usb4CmStatelessPacketsHandlerERR_FCreceived__Warn,
  Usb4CmStatelessPacketsHandlerERR_PLUGreceived__Warn,
  Usb4CmStatelessPacketsHandler__Params__Core_uCSignalledError,
  Usb4CmStatelessPacketsHandlerNoRetryProhibitedByUSB4_CM_QUIRK_ERR_PLUG_IS_FATAL_NO_RETRY__Warn,
  Usb4CmIoctlDeprecatedCallCheckNumberInterdomainRoutersInstead__Warn,
  Usb4CmLoggerPrintEvents__Params__CoreIndex_R_A_hpState,
  Usb4CmLoggerPrintEvents__Params__CoreIndex_R_A_hpParsed,
  Usb4CmLoggerPrintEvents__Params__CoreIndexWakeISRhappened,

  
  Usb4CmWakeSystemInitiated__Info,
  Usb4CmWake__Params__SourcesTopology_Port_WakeonConnectStatus,
  Usb4CmWake__Params__WakeonDisconnectStatus_WakeonInterDomainStatus_WakeonUSB4WakeStatus,
  Usb4CmResetHostInterfaceWARNING__Params__Core_uCSignalledError,
  Usb4CmConfigureCLxWARNING__Params__ActiveTBT3CableDoesntSupportClx,

  Usb4CmSendXDomainResponseUUIDGotInterdomainRoute0UsingHardCodedValue__Warn,
  Usb4CmHandleXDomainUUIDResponseGotInterdomainRoute0UsingHardCodedValue__Warn,
  Usb4CmHandleXDomainLinkStateStatusReqGotInterdomainRoute0UsingHardCodedValue__Warn,
  Usb4CmHandleXDomainLinkStateStatusRespGotInterdomainRoute0UsingHardCodedValue__Warn,
  Usb4CmHandleXDomainLinkStateChangeReqGotInterdomainRoute0UsingHardCodedValue__Warn,
  Usb4CmHandleXDomainLinkStateChangeRespGotInterdomainRoute0UsingHardCodedValue__Warn,
  Usb4CmHandleErrEnumZeroingOutInterdomainStateMachine__Params__InterdomainTopology,
  Usb4CmInterdomainHotPlugHandlerProcessUUIDS__Params__WrongPacketTypeExpectingUSB4cpInterdomainPacketUUIDResponse,
  Usb4CmInterdomainHotPlugHandlerCheckX2Support__Params__WrongPacketTypeExpectingUSB4cpInterdomainPacketLinkStateStatusResponse,
  Usb4CmInterdomainHotPlugHandlerMeasureIterationsWaitingWhileTheOtherHostIsBusyIterationTookLongTime__Params__100IterationsTookuSec,
  Usb4CmInterdomainHotPlugHandlerMasterFlowBond__Params__WrongPacketTypeExpectingUSB4cpInterdomainPacketLinkStateStatusResponse,
  Usb4CmInterdomainHotPlugHandlerMasterFlow__Params__100IterationsTookuSec,

  Usb4CtrlIfaceHandleErrorNotifications__Params__Router_Adapter,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRCONN__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRLINK__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRADDR__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRADP__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRENUM__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRNUA__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRLEN__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRHEC__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRFC__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRPLUG__Info,
  Usb4CtrlIfaceHandleErrorNotificationsUSB4cpNotificationEventERRLOCK__Info,
  Usb4CtrlIfaceSendAckPlgOut__Params__RouteLow_Adapter,
  Usb4CtrlIfaceSendAckPlgIn__Params__RouteLow_Adapter,

  Usb4CtrlPacketReferenceBufferToPacketReceivedPacketCRCdoesnotMatchCalculatedValue__Warn,
  DataLengthIsNotSizeofUINT32expectEERLEN__Info,
  Usb4PortReadCSsendReadFailedOnTimeout__Info,
  Usb4PortReadCSUnsupportedAdapterNullProtocolNullSubTypeNullVersion__Info,
  Usb4PortReadCSFoundUnsupportedAdapterNumber__Params__Numbers,
  Usb4PortIssuePortOperationXOpeationNotSupported__Warn,
  Usb4PortEnableSegmentPortType__Params__Type,
  Usb4PortWriteSegmentWriteNonFlowControlledBuffers__Params__Topology_Port_NonFlowControlledBuffers_TotalBuffers,
  Usb4PortWriteSegment__Params__Topology_Port_InputHopID,
  Usb4PortWriteSegment__Params__CS0OutputHopID_CS0OutputAdapter_CS0PathCreditsAllocated,
  Usb4PortWriteSegment__Params__CS0Valid_CS1Weight_CS1Priority,
  Usb4PortWriteSegment__Params__CS1CounterID_CounterEnable_IngressFlowControl,
  Usb4PortWriteSegment__Params__CS1EgressFlowControl_CS1IngressSharedBufferingEnable_CS1EgressSharedBufferingEnable,
  Usb4PortWriteSegment__Params__CS1PendingPackets_freeBuffers,
  Usb4PortUsb4PortOperationSbCsReadData__Params__pBuffAddr,
  Usb4PortPortOperationCompletionOperationNotSupported__Warn,
  Usb4RouterWriteFileToRouterDone__Info,
  Usb4RouterLoadVendorSettingsDetected__Params__Vendor_Product,
  Usb4RouterLoadVendorSettingsFailedToLoadDriverContinueGracefully__Warn,
  Usb4RouterLoadVendorSettingsPleaseCheckVendorSettingsFolder__Warn,
  Usb4RouterGetBufferAllocations__Params__Router_baMaxUSB3,
  Usb4RouterGetBufferAllocations__Params__Router_baMinDPaux,
  Usb4RouterGetBufferAllocations__Params__Router_baMinDPmain,
  Usb4RouterGetBufferAllocations__Params__Router_baMaxPCIe,
  Usb4RouterGetBufferAllocations__Params__Router_baMaxHI,
  Usb4RouterGetBufferAllocationsUnsupportedParameter__Params__IndexData,
  Usb4RouterPrepareSleepWakeSources__Params__Topology_Port_WakeonConnectStatus,
  Usb4RouterPrepareSleepWakeSources__Params__WakeonDisconnectStatus_WakeonInterDomainStatus_WakeonUSB4WakeStatus,
  Usb4RouterCheckCLxCompatibilityCLxNotSupportedDueToInterdomainLink__Params__Router_Port,
  Usb4RouterCheckCLxCompatibilityCLxNotSupportedDueTo2SingleLinks__Params__Router_Port,
  Usb4RouterCheckCLxCompatibilityCLxNotSupportedDueToPortCS18LinkCLxSupportBitClear__Params__RouterPort,
  Usb4RouterEnumerateWillEnumerate__Params__Router,
  Usb4RouterEnumeratePorts__Params__Router_Port_TotalBuffers,
  Usb4RouterEnumeratePorts__Params__Router_Port,
  Usb4RouterVerifyLinkSpeedWidthPortLaneLinkIsDown__Params__Core_Lane,
  Usb4RouterVerifyLinkSpeedWidth__Params__Core_PortLane_ExpGen,
  Usb4RouterVerifyLinkSpeedWidth__Params__ExpWidth_Speed_Width,
  Usb4RouterVerifyLinkSpeedWidth__Params__Core_PortLane_Speed_Width,
  Usb4RouterTMUSetRouterUnidirectionalModeDoesNotSupportUnidirectionalTMUMode__Params__Router,

  Usb4PathSegmentFIllPathCsTriedSetupVideoPathFromSinkToSourceCheckPathSetup__Error,
  Usb4PathSegmentWriteSegmentToRouterActivePathUndergoesAChangeOfParameters__Warn,
  Usb4PathSegmentWriteSegmentToRouterActivePathUndergoesAChangeOfDestination__Warn,
  Usb4PathSegmentInvalidateSegmentClearSegmentAdapterHasTotalBuffers__Info,
  Usb4PathSegmentCalculateSegmentCreditsRouterAllocationLimitingPathCredits__Params__From_To_router,
  Usb4PathSegmentCalculateSegmentCreditsCalculateSegmentCreditsPortLimitingPathCredits__Params__From_To_router,
  Usb4PathSegmentCalculateSegmentCreditsCalculateSegmentCredits__Params__Router_pathCreditsAllocated,
  Usb4PathSegmentCalculateSegmentCreditsCalculateSegmentCredits__Params__Adapter_hasTotalBuffers,
  Usb4PathManagerCreatePathsBuildingUSB4PathTypePCIEINpath__Info,
  Usb4PathManagerCreatePathsBuildingUSB4PathTypePCIEOUTpath__Info,
  Usb4PathManagerCreatePathsEnableUSB4PathTypePCIEINpath__Info,
  Usb4PathManagerCreatePathsEnableUSB4PathTypePCIEOUTpath__Info,
  Usb4PathManagerCreatePathsBuildingUSB4PathTypeUSB3INpath__Info,
  Usb4PathManagerCreatePathsBuildingUSB4PathTypeUSB3OUTpath__Info,
  Usb4PathManagerCreatePathsEnableUSB4PathTypeUSB3INpath__Info,
  Usb4PathManagerCreatePathsEnableUSB4PathTypeUSB3OUTpath__Info,
  Usb4PathManagerBuildingUSB4PathTypeDPMAINpath__Info,
  Usb4PathManagerBuildingUSB4PathTypeDPINAUXpath__Info,
  Usb4PathManagerBuildingUSB4_PathTypeDPOUTAUXpath__Info,
  Usb4PathManagerEnableUSB4PathTypeDPOUTAUXpath__Info,
  Usb4PathManagerEnableUSB4PathTypeDPINAUXpath__Info,
  

  //----------------------------------------------------------------------------------------------
  // USB4_PHY
  //----------------------------------------------------------------------------------------------
  Usb4PhyPrint__Params__addr_val,
  Usb4PlatformCioPhyAssertReset__Info,
  Usb4PlatformCioPhyDeAssertReset__Info,
  Usb4PlatformCioPhyStart__Info,
  Usb4PlatformCioPhyConfigure__Info,
  Usb4PlatformCioPhyConfigureREFGEEN__Error,
  Usb4PlatformCioPhyStartDpPhyCReadyIsUp__Info,
  Usb4PlatformCioPhyStartDpPhyCReadyDidntComeUp__Error,

  //----------------------------------------------------------------------------------------------
  // USB4_ENTRY
  //----------------------------------------------------------------------------------------------

  Usb4Entry__Err_Failed_to_initialize_cm__Inst_Status,
  Usb4Entry__Err_Failed_to_initialize_ClientDxe__Status,
  Usb4Entry__Err_Failed_to_register_exit_event__Status,
  Usb4Entry__Err_Failed_to_create_timer_event__Status,
  Usb4Entry__Err_Failed_to_set_timer__Status,

  //----------------------------------------------------------------------------------------------
  // Register Log
  //----------------------------------------------------------------------------------------------
  Usb4Reg_Addr_Val,

  //----------------------------------------------------------------------------------------------
  // Enumerated Type
  //----------------------------------------------------------------------------------------------
  enum__attach_mode_svid0,   /*< The default SVID reported by the device */
  enum__attach_mode_tbt3,    /*< Finish with EnterMode TBT3 alt mode (if applicable) */
  enum__attach_mode_dp_alt,  /*< Finish with EnterMode DP alt mode (if applicable) */
  enum__attach_mode_usb4,    /*< For PD3.0 finish with ENTER_USB = 4.0 */
  enum__attach_mode_usb3,    /*< Nothing for PD2.0 devices, for PD3.0 ENTER_USB = 3.0 */
  enum__attach_mode_usb2,    /*< Nothing for PD2.0 devices, for PD3.0 ENTER_USB = 2.0 */
  PD_API_ATTACH_MODE_OFFSET = enum__attach_mode_svid0,


  Usb4LogMax = 0xFFFF
} USB4_LOG_ENUM;

typedef enum _USB4_LOG_TYPE {
  USB4_LOG_CFG  = 0,
  USB4_LOG_INF,
  USB4_LOG_ERR,
  USB4_LOG_PD,
  USB4_LOG_REG,
  USB4_LOG_PHY,
  USB4_LOG_CM,
  USB4_LOG_MAX
} USB4_LOG_TYPE;

typedef struct _USB4_LOG_ENTRY {
  UINT16 SeqNum;
  USB4_LOG_ENUM Id;
  UINT16 P1;
  UINT16 P2;
  UINT16 P3;
  UINT16 P4;
  UINT16 P5;
  UINT16 P6;
} USB4_LOG_ENTRY;

typedef struct _USB4_LOG {
  UINT16 SeqNum;
  UINT16 LogIdx[USB4_LOG_MAX];

  UINT32 CfgSize;
  USB4_LOG_ENTRY Cfg[USB4_LOG_CFG_SIZE];

  UINT32 InfSize;
  USB4_LOG_ENTRY Inf[USB4_LOG_INF_SIZE];

  UINT32 ErrSize;
  USB4_LOG_ENTRY Err[USB4_LOG_ERR_SIZE];

  UINT32 PdSize;
  USB4_LOG_ENTRY Pd[USB4_LOG_PD_SIZE];

  UINT32 RegSize;
  USB4_LOG_ENTRY Reg[USB4_LOG_REG_SIZE];

  UINT32 PhySize;
  USB4_LOG_ENTRY Phy[USB4_LOG_PHY_SIZE];

  UINT32 CmSize;
  USB4_LOG_ENTRY Cm[USB4_LOG_CM_SIZE];
} USB4_LOG;

//------------------------------------------------------------------------------------------------
// Function Declarations
//------------------------------------------------------------------------------------------------
VOID
Usb4Log (
  IN USB4_LOG_TYPE LogType,
  IN USB4_LOG_ENUM LogEnum,
  IN UINT32 Offset
  );

VOID
Usb4Log1 (
  IN USB4_LOG_TYPE LogType,
  IN USB4_LOG_ENUM LogEnum,
  IN UINT32 Offset,
  IN UINT64 P1
  );

VOID
Usb4Log2 (
  IN USB4_LOG_TYPE LogType,
  IN USB4_LOG_ENUM LogEnum,
  IN UINT32 Offset,
  IN UINT64 P1,
  IN UINT32 P2
  );

VOID
Usb4Log3 (
  IN USB4_LOG_TYPE LogType,
  IN USB4_LOG_ENUM LogEnum,
  IN UINT32 Offset,
  IN UINT64 P1,
  IN UINT32 P2,
  IN UINT32 P3
  );

VOID
Usb4Log4 (
  IN USB4_LOG_TYPE LogType,
  IN USB4_LOG_ENUM LogEnum,
  IN UINT32 Offset,
  IN UINT64 P1,
  IN UINT32 P2,
  IN UINT16 P3,
  IN UINT16 P4
  );

VOID
Usb4Log5 (
  IN USB4_LOG_TYPE LogType,
  IN USB4_LOG_ENUM LogEnum,
  IN UINT32 Offset,
  IN UINT64 P1,
  IN UINT16 P2,
  IN UINT16 P3,
  IN UINT16 P4, 
  IN UINT16 P5 
  );

VOID
Usb4Log6 (
  IN USB4_LOG_TYPE LogType,
  IN USB4_LOG_ENUM LogEnum,
  IN UINT32 Offset,
  IN UINT64 P1,
  IN UINT16 P2,
  IN UINT16 P3,
  IN UINT16 P4, 
  IN UINT16 P5,
  IN UINT16 P6
  );

VOID
Usb4LogUnInit (
  VOID
  );

VOID
Usb4LogInit (
  VOID
  );

#define USB4_LOG_WARNING(LogType, LogEnum, Offset) \
  Usb4Log(LogType, LogEnum, Offset);

#define USB4_LOG_WARNING_2(LogType, LogEnum, Offset, P1, P2) \
  Usb4Log2(LogType, LogEnum, Offset, P1, P2);

#define USB4_LOG_ERROR_1(LogType, LogEnum, Offset, P1) \
  Usb4Log1(LogType, LogEnum, Offset, P1);

#define USB4_LOG_ERROR_2(LogType, LogEnum, Offset, P1, P2) \
  Usb4Log2(LogType, LogEnum, Offset, P1, P2);

#endif /* __USB4LOG_H__ */
