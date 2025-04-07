#ifndef _DP_REDIRECTOR_H_
#define _DP_REDIRECTOR_H_
/*! \file */
/*============================================================================================
  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================================*/

/* --------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"

/*---------------------------------------------------------------------------------------------------------------------
 * Public Functions
 *-------------------------------------------------------------------------------------------------------------------*/

//-------------------------------------------------------------------------------------------------
//  DP_Redirector_ConfigureOverrides
//
//  @brief
//      Configure redirector with provided overrides.
//
//  @params
//      [IN] eDeviceID
//          DP Device ID to configure.
//      [IN] pOverrideCfg
//          Override configuration containing buffers to replace and mode of override.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
DP_Status DP_Redirector_ConfigureOverrides(DP_DeviceIDType         eDeviceID,
                                           DP_Config_OverrideType *pOverrideCfg);

//-------------------------------------------------------------------------------------------------
//  DP_Redirector_ConfigureSlave
//
//  @brief
//      Configure redirector to redirect to a master AUX device for bonded mode.
//      EDIDs will be redirected to master, and failed DPCD sections will redirect to master on read.
//
//  @params
//      [IN] eDeviceID
//          DP Device ID to configure.
//      [IN] eMasterAUXDeviceID
//          Device ID of the master AUX.
//      [IN] pOverrideCfg
//          Override configuration containing buffers to replace and mode of override.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
DP_Status DP_Redirector_ConfigureSlave(DP_DeviceIDType         eDeviceID,
                                       DP_DeviceIDType         eMasterAUXDeviceID,
                                       DP_Config_OverrideType *pOverrideCfg);

//-------------------------------------------------------------------------------------------------
//  DP_Host_Redirector_ClientRead
//
//  @brief
//      This function will redirect AUX/I2C reads to SIM, an particular device, or a dummy function.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN/OUT] psReadPacket
//          The read packet.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_Redirector_ClientRead(DP_DisplayCtxType *pDisplayCtx,
                                        DP_ReadPacketType *psReadPacket);

//-------------------------------------------------------------------------------------------------
//  DP_Host_Redirector_ClientWrite
//
//  @brief
//      This function will redirect AUX/I2C writes to SIM, an particular device, or a dummy function.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN/OUT] psWritePacket
//          The written packet.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_Redirector_ClientWrite(DP_DisplayCtxType  *pDisplayCtx,
                                         DP_WritePacketType *psWritePacket);


#endif // __DP_REDIRECTOR__