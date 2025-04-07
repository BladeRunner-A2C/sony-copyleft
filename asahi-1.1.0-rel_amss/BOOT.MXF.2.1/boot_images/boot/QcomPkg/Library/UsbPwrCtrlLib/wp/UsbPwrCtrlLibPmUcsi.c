/**
@file  UsbPwrCtrlLibPmSchg.c
@brief Implementation of UsbPWrCtrlLibrary API for PMIC SCHG module
*/
/*=============================================================================
Copyright (c) 2017-2019 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================

                    EDIT HISTORY

when       who     what, where, why
--------   ---     -----------------------------------------------------------
01/25/19   dch     Support PD Status API
01/25/19   dch     Perform UCSI poll only for Type-C Port
10/21/18   ivy     Initial Release
=============================================================================*/

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/

#include <Uefi.h>
/**
  Library Dependencies
*/
#include <string.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>

/**
  Protocol Dependencies
*/
#include <Protocol/EFIPmicGlink.h>


/**
  Internal Dependencies
*/
#include "UsbPwrCtrlLibPmUcsi.h"



/*===========================================================================*/
/*                  TYPEDEF AND MACRO DEFINITIONS                            */
/*===========================================================================*/
#define TYPEC_STATUS_POLL_INTERVAL		(2000 * 10000U)  /* 2 Sec */

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/


/*===========================================================================*/
/*                  LOCAL VARIABLE DECLARATIONS                              */
/*===========================================================================*/

static EFI_PMIC_GLINK_PROTOCOL	*PmicGlinkProtocol 		= NULL;
static EFI_EVENT TypeCStsEvt                          = NULL;
static USBPD_UCSI_CONNECTOR_STATUS_INFO UsbPwrCtrlUcsiStatus[EFI_USB_PWR_CTRL_PORTHW_MAX_PORT_NO];
static UINT8 UsbPwrCtrlCCOrientation[EFI_USB_PWR_CTRL_PORTHW_MAX_PORT_NO];
static BOOLEAN ccOrientationInfoAvailable             = FALSE;
static USBPD_DPM_USBC_PORT_PIN_ASSIGNMENT_DATA UsbPwrCtrlPinAsgmtInfo[EFI_USB_PWR_CTRL_PORTHW_MAX_PORT_NO];

/**
  Initialize the interface to PMIC UCSI Module

  @param none

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
UsbPwrCtrlLibPmUcsi_Init(VOID)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  if (NULL == PmicGlinkProtocol)
  {
    Status = gBS->LocateProtocol(&gpmicGlinkProtocolGuid, NULL, (void**)&PmicGlinkProtocol);

    if (EFI_ERROR(Status))
    {
      PmicGlinkProtocol = NULL;
    }
  }
  
  /* Create a timer to poll TypeC status */	 
  Status = gBS->CreateEvent( 			   
  			EVT_TIMER | EVT_NOTIFY_SIGNAL,
  			TPL_CALLBACK,
  			UsbPwrCtrlLibPmUcsi_StatusChgCb,
  			NULL,				
  			&TypeCStsEvt
  			);	  
  
  if(EFI_ERROR(Status))    
  {		
    USBPWRCTRL_LIB_DEBUG((EFI_D_ERROR, "%a TypeC status CreateEvent Failed \r\n", __FUNCTION__));
    return Status;	  
  }    
  
  gBS->SignalEvent(TypeCStsEvt);	 

  /* Set the polling period for the USB TypeC periodic event */	  
  Status = gBS->SetTimer(				 
  				TypeCStsEvt,				 
  				TimerPeriodic, 			   
  				TYPEC_STATUS_POLL_INTERVAL
  				);
  
  if(EFI_ERROR(Status))	
  {		 
    USBPWRCTRL_LIB_DEBUG((EFI_D_ERROR, "%a TypeC status event SetTimer Failed \r\n", __FUNCTION__));		 
    return Status;    
  }

  
  return Status;
}

VOID 
EFIAPI 
UsbPwrCtrlLibPmUcsi_StatusChgCb(
	IN EFI_EVENT Event,
	IN VOID		*Context
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINT8 PortIndex;

	EFI_PM_GLINK_LINK_STATUS									PmGlinkStatus = {0};
	USBPD_UCSI_GET_CONNECTOR_STATUS_DATA			UCSIConnectorStatusReq;
	USBPD_UCSI_GET_CONNECTOR_STATUS_DATA			UCSIConnectorStatusResp;
	PUSBPD_UCSI_GET_CONNECTOR_STATUS_DATA			pUCSIConnectorStatusResp = &UCSIConnectorStatusResp;
	USBPD_DPM_USBC_READ_BUFFER								USBCReadBuff;
	PUSBPD_DPM_USBC_READ_BUFFER								pUSBCReadBuff = &USBCReadBuff;
	
	memset(&UCSIConnectorStatusReq, 0, sizeof(UCSIConnectorStatusReq));
	memset(&UCSIConnectorStatusResp, 0, sizeof(UCSIConnectorStatusResp));	
	memset(&USBCReadBuff, 0, sizeof(USBCReadBuff));

	/* ================================================== */
	/*             Check Pmic Glink Status                */
	/* ================================================== */
	
	if (NULL == PmicGlinkProtocol)
	{
		Status = gBS->LocateProtocol(&gpmicGlinkProtocolGuid, NULL, (void**)&PmicGlinkProtocol);

		if (EFI_ERROR(Status))
    {
     		PmicGlinkProtocol = NULL;
    }
	  return;
	}
	
	Status = PmicGlinkProtocol->LinkStatus(&PmGlinkStatus);
	if (EFI_ERROR(Status) || FALSE == PmGlinkStatus.IsPMICChannelOpen)
	{
	  return;
	}
	
	/* ================================================== */
	/* Get UCSI Connector Status for all active PortIndex */
	/* ================================================== */

	if (pActiveHwInfo->NoOfPorts > EFI_USB_PWR_CTRL_PORTHW_MAX_PORT_NO)
	{
		USBPWRCTRL_LIB_DEBUG((EFI_D_ERROR, "%a Number of active ports exceeds the maximum possible value %d. \r\n", __FUNCTION__, EFI_USB_PWR_CTRL_PORTHW_MAX_PORT_NO));
		return;
	}

	for (PortIndex = 0; PortIndex < pActiveHwInfo->NoOfPorts; PortIndex ++)
	{
		if(pActiveHwInfo->Ports[PortIndex].ConnectorType != EFI_USB_PWR_CTRL_PORTHW_CONNECTOR_TYPEC)
		{
			UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable = TRUE;
			UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.message_in.ConnectStatus = FALSE;
			continue;
		}

		/* Construct request command - Control field */
		UCSIConnectorStatusReq.control.Command = USBPD_UCSI_COMMAND_CODE_GET_CONNECTOR_STATUS;
		UCSIConnectorStatusReq.control.ConnectorNumber = PortIndex + 1;

		/* Write the request command to Glink */
		Status = PmicGlinkProtocol->UCSIWriteBuffer((UINT8*)&UCSIConnectorStatusReq, (UINT8)sizeof(UCSIConnectorStatusReq));

		if (EFI_ERROR(Status))
		{
		  USBPWRCTRL_LIB_DEBUG((EFI_D_ERROR, "%a Write UCSI Get Connector Status to Glink for PortIndex %d Failed \r\n", __FUNCTION__, PortIndex));
		  UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable = FALSE;
		  continue;
		}
		
		/* Read the response from Glink */
		Status |= PmicGlinkProtocol->UCSIReadBuffer((UINT8**)&pUCSIConnectorStatusResp, (UINT8)sizeof(UCSIConnectorStatusResp));

		if (EFI_ERROR(Status))
		{
		  USBPWRCTRL_LIB_DEBUG((EFI_D_ERROR, "%a Read UCSI Get Connector Status from Glink for PortIndex %d Failed \r\n", __FUNCTION__, PortIndex));
		  UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable = FALSE;
		  continue;
		}
		else
		{
	  	UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable = TRUE;
		}
		/* Save Connector Status to buffer */
		memscpy(&(UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts), sizeof(USBPD_UCSI_GET_CONNECTOR_STATUS_DATA), 
					&UCSIConnectorStatusResp, sizeof(USBPD_UCSI_GET_CONNECTOR_STATUS_DATA));
	}	  

	/* ================================================== */
	/* Get CC Orientation Info and Pin Assignment for all active PortIndex */
	/* ================================================== */

    Status = PmicGlinkProtocol->USBCReadBuffer((UINT8**)&pUSBCReadBuff, (UINT8)sizeof(USBCReadBuff));    

	if ((Status == EFI_SUCCESS) && (USBCReadBuff.data_type == USBPD_DPM_USBC_READ_DATA_PIN_ASSIGNMENT))
	{
		for (PortIndex = 0; PortIndex < pActiveHwInfo->NoOfPorts; PortIndex ++)
		{
			USBPWRCTRL_LIB_DEBUG((EFI_D_INFO, "%a Read USBC CC Orientation PortIndex=%d, Orientation=%d,  mux_ctrl=%d, svid=%X, vid=%X, extend=%X\r\n", 
						__FUNCTION__, 
						USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.port_index, 
						USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.orientation,
						USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.mux_ctrl,
						USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.svid, 
						USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.vid, 
						USBCReadBuff.data_payload.pin_assignment.port[PortIndex].extended[0]));

			if(pActiveHwInfo->Ports[PortIndex].ConnectorType == EFI_USB_PWR_CTRL_PORTHW_CONNECTOR_TYPEC)
				UsbPwrCtrlCCOrientation[PortIndex] = (USBPD_PIN_ASSIGNMENT_ORIENTATION_TYPE)(USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.orientation);
			else
				UsbPwrCtrlCCOrientation[PortIndex] = USBPD_PIN_ASSIGNMENT_ORIENTATION_INVALID_OPEN;

            UsbPwrCtrlPinAsgmtInfo[PortIndex].common.orientation = UsbPwrCtrlCCOrientation[PortIndex];
            UsbPwrCtrlPinAsgmtInfo[PortIndex].common.mux_ctrl = USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.mux_ctrl;
            UsbPwrCtrlPinAsgmtInfo[PortIndex].common.vid = USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.vid;
            UsbPwrCtrlPinAsgmtInfo[PortIndex].common.svid = USBCReadBuff.data_payload.pin_assignment.port[PortIndex].common.svid;
            UsbPwrCtrlPinAsgmtInfo[PortIndex].extended[0] = USBCReadBuff.data_payload.pin_assignment.port[PortIndex].extended[0];
		}
		ccOrientationInfoAvailable = TRUE;
	}
	else
	{
		ccOrientationInfoAvailable = FALSE;
		USBPWRCTRL_LIB_DEBUG((EFI_D_ERROR, "%a Read USBC CC Orientation (Pin Assignment) Info from Glink Failed \r\n", __FUNCTION__));
	}

	return;
}


/**
  Get Vbus Detect result from PMIC UCSI Module

  @param[IN]    HwInfo          Hardware Information for this request
  @param[OUT]   bVbusDetect     Return the result of Vbus Detect

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
UsbPwrCtrlLibPmUcsi_GetVbusDetect(
  UINT8 PortIndex,
  BOOLEAN *bVbusDetect)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  //USBPD_UCSI_VERSION_DATA version;
  USBPD_UCSI_CCI_DATA	cci;
  USBPD_UCSI_GET_CONNECTOR_STATUS_MESSAGE_DATA message_in;

  if (bVbusDetect == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  //version    = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.version;
  cci   	   = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.cci;
  message_in = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.message_in;

	if (UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable && !cci.ErrorIndicator)
  {
  	/* bVbusDetect is True when ConnectStatus is 1 (connected) and PowerDirection is 0 (consumer)*/
  	*bVbusDetect = (message_in.ConnectStatus) & (!message_in.PowerDirection);
  }	
  else
  {
  	Status = EFI_DEVICE_ERROR;
  }
  
  return Status;
}

/**
  Get Vbus Source OK result from Library

  @param[IN]    HwInfo          Hardware Information for this request
  @param[OUT]   bVbusSourceOK   Return the result of Vbus SourceOK

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
UsbPwrCtrlLibPmUcsi_GetVbusSourceOK(
  UINT8 PortIndex,
  BOOLEAN *bVbusSourceOK)
{
  EFI_STATUS Status = EFI_SUCCESS;
  //USBPD_UCSI_VERSION_DATA version;
  USBPD_UCSI_CCI_DATA cci;
  USBPD_UCSI_GET_CONNECTOR_STATUS_MESSAGE_DATA message_in;

  if (bVbusSourceOK == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  //version    = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.version;
  cci        = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.cci;
  message_in = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.message_in;

  if (UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable && !cci.ErrorIndicator)
  {
  	/* bVbusSourceOK is True when ConnectStatus is 1 (connected) and PowerDirection is 1 (provider)*/
    *bVbusSourceOK = (message_in.ConnectStatus) & (message_in.PowerDirection);
  }	
  else
  {
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}

/**
  Get HSUSB Charger Port Type

  @param[IN]    HwInfo          Hardware Information for this request
  @param[OUT]   ChgPortType     Return Charger Port Tpye

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
UsbPwrCtrlLibPmUcsi_GetHSUsbPortType(
  UINT8 PortIndex,
  EFI_USB_PWR_CTRL_HSUSB_CHGPORT_TYPE *ChgPortType)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (ChgPortType == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

// TODO: currently not used. hardcoded to SDP
  *ChgPortType = EFI_USB_PWR_CTRL_HSUSB_CHGPORT_SDP;
  	
  return Status;
}

/**
  Get TypeC Port Status

  @param[IN]    HwInfo          Hardware Information for this request
  @param[OUT]   TypeCPortStatus Return TypeC port Status;

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
UsbPwrCtrlLibPmUcsi_GetTypeCPortStatus(
  UINT8 PortIndex,
  EFI_USB_PWR_CTRL_TYPEC_PORT_STATUS *TypeCPortStatus)
{
  EFI_STATUS Status = EFI_SUCCESS;
  //USBPD_UCSI_VERSION_DATA version;
  USBPD_UCSI_CCI_DATA cci;
  USBPD_UCSI_GET_CONNECTOR_STATUS_MESSAGE_DATA message_in;


  if (TypeCPortStatus == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  //version    = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.version;
  cci	       = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.cci;
  message_in = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.message_in;

  if (UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable && ccOrientationInfoAvailable && !cci.ErrorIndicator)
  {
    if (message_in.ConnectStatus)
    {
      TypeCPortStatus->ConnectSts = TRUE;
		
      switch (message_in.PowerDirection)
      {
        case USBPD_UCSI_CSC_POWER_DIRECTION_AS_CONSUMER:
	  	
          TypeCPortStatus->PowerRole = EFI_USB_PWR_CTRL_TYPEC_POWERROLE_SINK;
          TypeCPortStatus->DataRole = EFI_USB_PWR_CTRL_TYPEC_DATAROLE_UFP;					
          TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_NONE;
		
          switch(message_in.PowerOpMode)
          {	
            case USBPD_UCSI_CSC_POWER_OPMODE_TYPEC_DFT:
            case USBPD_UCSI_CSC_POWER_OPMODE_BC:
              TypeCPortStatus->DetectedSinkType = EFI_USB_PWR_CTRL_TYPEC_PORT_SNK_DEFAULT;
              break;
            case USBPD_UCSI_CSC_POWER_OPMODE_PD:
            case USBPD_UCSI_CSC_POWER_OPMODE_TYPEC_1P5A:
              TypeCPortStatus->DetectedSinkType = EFI_USB_PWR_CTRL_TYPEC_PORT_SNK_1P5;
              break;
            case USBPD_UCSI_CSC_POWER_OPMODE_TYPEC_3A:
              TypeCPortStatus->DetectedSinkType = EFI_USB_PWR_CTRL_TYPEC_PORT_SNK_3P0;
              break;
            default:
              TypeCPortStatus->DetectedSinkType = EFI_USB_PWR_CTRL_TYPEC_PORT_SNK_NONE;
              break;
          }
          break;
				
        case USBPD_UCSI_CSC_POWER_DIRECTION_AS_PROVIDER:
		  	
          TypeCPortStatus->PowerRole = EFI_USB_PWR_CTRL_TYPEC_POWERROLE_SOURCE;
          TypeCPortStatus->DataRole = EFI_USB_PWR_CTRL_TYPEC_DATAROLE_DFP;
          TypeCPortStatus->DetectedSinkType = EFI_USB_PWR_CTRL_TYPEC_PORT_SNK_NONE;	

					switch(message_in.ConnectPartnerType)
          {
            case USBPD_UCSI_CSC_CONNECTOR_PARTNER_DFP:
              TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_NONE;
              break;
            case USBPD_UCSI_CSC_CONNECTOR_PARTNER_UFP:
              TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_RD_OPEN;
              break;
            case USBPD_UCSI_CSC_CONNECTOR_PARTNER_POWERCABLE_NOUFP:
              TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_RA_OPEN;
              break;
            case USBPD_UCSI_CSC_CONNECTOR_PARTNER_POWERCABLE_UFP:
              TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_RD_RA_VCONN;
              break;
            case USBPD_UCSI_CSC_CONNECTOR_PARTNER_DEBUG_ACCESSORY:
              TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_UNORIENTED_RD_RD;
              break;
            case USBPD_UCSI_CSC_CONNECTOR_PARTNER_AUDIO_ACCESSORY:
              TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_RA_RA;
              break;
            default:
              TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_NONE;
              break;
          }
          break;
        default:
          /* Should never be here*/
          TypeCPortStatus->PowerRole = EFI_USB_PWR_CTRL_TYPEC_POWERROLE_UNKNOWN;
          TypeCPortStatus->DataRole = EFI_USB_PWR_CTRL_TYPEC_DATAROLE_UNKNOWN;
          TypeCPortStatus->DetectedSinkType = EFI_USB_PWR_CTRL_TYPEC_PORT_SNK_NONE;	
          break;		
      }

      switch (UsbPwrCtrlCCOrientation[PortIndex])
      {
        case USBPD_PIN_ASSIGNMENT_ORIENTATION_NORMAL_CC1:
          TypeCPortStatus->CCOrientation = EFI_USB_PWR_CTRL_TYPEC_ORIENTATION_CC1;
          break;
        case USBPD_PIN_ASSIGNMENT_ORIENTATION_FLIP_CC2:
          TypeCPortStatus->CCOrientation = EFI_USB_PWR_CTRL_TYPEC_ORIENTATION_CC2;
          break;
        default:
          TypeCPortStatus->CCOrientation = EFI_USB_PWR_CTRL_TYPEC_ORIENTATION_OPEN;
        break;
      }

    }
    else
    {
      TypeCPortStatus->ConnectSts = FALSE;
      TypeCPortStatus->PowerRole = EFI_USB_PWR_CTRL_TYPEC_POWERROLE_UNKNOWN;
      TypeCPortStatus->DataRole = EFI_USB_PWR_CTRL_TYPEC_DATAROLE_UNKNOWN;
      TypeCPortStatus->DetectedSinkType = EFI_USB_PWR_CTRL_TYPEC_PORT_SNK_NONE;
      TypeCPortStatus->DetectedSourceType = EFI_USB_PWR_CTRL_TYPEC_PORT_SRC_NONE;
      TypeCPortStatus->CCOrientation = EFI_USB_PWR_CTRL_TYPEC_ORIENTATION_OPEN;  

    }
  }
  else
  { 
    Status = EFI_DEVICE_ERROR; 
  }

  return Status;
}

/**
  Get Port PD Status

  @param[IN]    PortIndex       Specify which port the request is for
  @param[OUT]   PDStatus        Return PD Status;

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
UsbPwrCtrlLibPmUcsi_GetPDStatus(
    UINT8 PortIndex,
    EFI_USB_PWR_CTRL_PD_STATUS  *PDStatus)
{
  EFI_STATUS Status = EFI_SUCCESS;
  //USBPD_UCSI_VERSION_DATA version;
  USBPD_UCSI_CCI_DATA cci;
  USBPD_UCSI_GET_CONNECTOR_STATUS_MESSAGE_DATA message_in;

  if (PDStatus == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  //version    = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.version;
  cci	       = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.cci;
  message_in = UsbPwrCtrlUcsiStatus[PortIndex].UcsiConSts.message_in;

  if (UsbPwrCtrlUcsiStatus[PortIndex].InfoAvailable && ccOrientationInfoAvailable && !cci.ErrorIndicator)
  {
    if ( message_in.ConnectStatus &&
        (message_in.PowerDirection == USBPD_UCSI_CSC_POWER_DIRECTION_AS_CONSUMER) && 
        (message_in.PowerOpMode == USBPD_UCSI_CSC_POWER_OPMODE_PD) &&
        (message_in.RequestDataObject != 0))
    {
      PDStatus->bPDConsumer = TRUE;
    }
    else
    {
      PDStatus->bPDConsumer = FALSE;
    }
  }
  else
  { 
    Status = EFI_DEVICE_ERROR; 
  }

  return Status;    
}

/**
  Get Port Pin Assignment

  @param[IN]    PortIndex       Specify which port the request is for
  @param[OUT]   PinAsgmt        Return Pin Assignment;

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
UsbPwrCtrlLibPmUcsi_GetPinAsgmt(
    UINT8 PortIndex,
    EFI_USB_PWR_CTRL_PIN_ASGMT_INFO *PinAsgmt)
{
    if ( (PinAsgmt == NULL) || (PortIndex >= EFI_USB_PWR_CTRL_PORTHW_MAX_PORT_NO) )
    {
        USBPWRCTRL_LIB_DEBUG((EFI_D_WARN, "%a :: Invalid input parameter\r\n", __FUNCTION__));
        return EFI_DEVICE_ERROR;
    }
    
    EFI_STATUS Status = EFI_SUCCESS;
    if(UsbPwrCtrlPinAsgmtInfo[PortIndex].common.orientation > (UINT32)EFI_USB_PWR_CTRL_PIN_ASGMT_ORI_INVALID_OPEN)
        return EFI_DEVICE_ERROR;
    PinAsgmt->orientation = (EFI_USB_PWR_CTRL_PIN_ASGMT_ORI_TYPE)UsbPwrCtrlPinAsgmtInfo[PortIndex].common.orientation;
    
    if(UsbPwrCtrlPinAsgmtInfo[PortIndex].common.mux_ctrl > (UINT32)EFI_USB_PWR_CTRL_PIN_ASGMT_MUXCTRL_USB3P_PDAM2LANES)
        return EFI_DEVICE_ERROR;
    PinAsgmt->mux_ctrl = (EFI_USB_PWR_CTRL_PIN_ASGMT_MUXCTRL_TYPE)UsbPwrCtrlPinAsgmtInfo[PortIndex].common.mux_ctrl;

    PinAsgmt->vid = (unsigned short)UsbPwrCtrlPinAsgmtInfo[PortIndex].common.vid;
    PinAsgmt->svid = (unsigned short)UsbPwrCtrlPinAsgmtInfo[PortIndex].common.svid;

    unsigned char extended = UsbPwrCtrlPinAsgmtInfo[PortIndex].extended[0];
    unsigned char hpd = extended & 0x3F;
    if(hpd > (unsigned char)EFI_USB_PWR_CTRL_PIN_ASGMT_DPAM_HPD_F)
        return EFI_DEVICE_ERROR;
    PinAsgmt->extended.dp.hpd = (EFI_USB_PWR_CTRL_PIN_ASGMT_DPAM_HPD_TYPE)hpd; // Get bit[0:5]
    PinAsgmt->extended.dp.hpd_state = (extended & 0x40) >> 6; // Get bit[6:6]
    PinAsgmt->extended.dp.hpd_irq = (extended & 0x80) >> 7; // Get bit[7:7]

    USBPWRCTRL_LIB_DEBUG((EFI_D_INFO, "%a :: Get PinAssignment PortIndex=%d, Orientation=%d, mux_ctrl=%d, vid=%X, svid=%X, extend=%X, hpd=%x, hpd_state=%X, hpd_irq=%X\r\n", 
                        __FUNCTION__, 
                        PortIndex, PinAsgmt->orientation, PinAsgmt->mux_ctrl, PinAsgmt->vid, PinAsgmt->svid, \
                        extended, PinAsgmt->extended.dp.hpd, PinAsgmt->extended.dp.hpd_state, PinAsgmt->extended.dp.hpd_irq ));
    return Status;
    
}

