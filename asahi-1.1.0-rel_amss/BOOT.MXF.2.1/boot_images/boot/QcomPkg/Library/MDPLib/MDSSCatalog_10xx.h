#ifndef __MDSSCATALOG_10xx_H__
#define __MDSSCATALOG_10xx_H__
/*=============================================================================

  Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "MDPLib_i.h"


/*=========================================================================
     Default Defines
==========================================================================*/

/* Maximum number of minor versions supported */
#define MDP_MAX_MINOR_VERSION            6


/*=========================================================================
     Local Variables
==========================================================================*/

/* MDSS10xx Resolution Capabilities
*/
const MDP_ResolutionCaps sResolutionCaps_MDSS1000 =
{
    2,     /* uMinLayerWidth  */
    2,     /* uMinLayerHeight */
    2560,  /* uMaxLayerWidth  */
    2048,  /* uMaxLayerHeight */
};

/**************************************************************
* MDSS10xx PP (Ping-Pong) Capabilities
*
* Note: set MDP_PINGPONG_CAP_PINGPONG_SPLIT in uPPFeatureFlags to enable pingpong-split
*************************************************************/
const MDP_PingPongCaps sPPCaps_MDSS1000[HAL_MDP_PINGPONG_MAX] =
{
  /* bSupported, uMaxWidth, uPPFeatureFlags */
  { FALSE,       0,         0 },                                                                        // HAL_MDP_PING_PONG_NONE
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_SPLIT | MDP_PINGPONG_CAP_PINGPONG_BUFFER_LIMIT }, // HAL_MDP_PING_PONG_0
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_SPLIT | MDP_PINGPONG_CAP_PINGPONG_BUFFER_LIMIT }, // HAL_MDP_PING_PONG_1
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_BUFFER_LIMIT },                                   // HAL_MDP_PING_PONG_2
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_BUFFER_LIMIT },                                   // HAL_MDP_PING_PONG_3
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_BUFFER_LIMIT },                                   // HAL_MDP_PING_PONG_4
  { TRUE,        2560,      MDP_PINGPONG_CAP_PINGPONG_BUFFER_LIMIT }                                    // HAL_MDP_PING_PONG_5
};

/* Mapping from master ping-pong to slave ping-pong used ONLY when ping-pong split is enabled. */
const HAL_MDP_PingPongId sMDSS1000_PPSplitSlaveMap[HAL_MDP_PINGPONG_MAX] =
{
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_NONE,
    HAL_MDP_PINGPONG_6,    // HAL_MDP_PINGPONG_0,
    HAL_MDP_PINGPONG_6,    // HAL_MDP_PINGPONG_1,
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_2,
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_3,
    HAL_MDP_PINGPONG_NONE, // HAL_MDP_PINGPONG_4,
    HAL_MDP_PINGPONG_NONE  // HAL_MDP_PINGPONG_4,
};

/* MDSS8xx DSC Capabilities */
const MDP_DSCCaps sDSCCaps_MDSS1000[HAL_MDP_DSC_MAX] =
{
  {0                                                  , HAL_MDP_DSC_NONE},  // HAL_MDP_DSC_NONE
  {MDP_DSC_CAPS_RGB_SUPPORT | MDP_DSC_CAPS_YUV_SUPPORT, HAL_MDP_DSC_1   },  // HAL_MDP_DSC_0
  {MDP_DSC_CAPS_RGB_SUPPORT | MDP_DSC_CAPS_YUV_SUPPORT, HAL_MDP_DSC_NONE},  // HAL_MDP_DSC_1
  {MDP_DSC_CAPS_RGB_SUPPORT | MDP_DSC_CAPS_YUV_SUPPORT, HAL_MDP_DSC_3   },  // HAL_MDP_DSC_2
  {MDP_DSC_CAPS_RGB_SUPPORT | MDP_DSC_CAPS_YUV_SUPPORT, HAL_MDP_DSC_NONE},  // HAL_MDP_DSC_3
  {MDP_DSC_CAPS_RGB_SUPPORT                           , HAL_MDP_DSC_5   },  // HAL_MDP_DSC_4
  {MDP_DSC_CAPS_RGB_SUPPORT                           , HAL_MDP_DSC_NONE}   // HAL_MDP_DSC_5
};

/* Slave PingPong Buffer ID for PP split for all MDP versions
*/
const HAL_MDP_PingPongId* PingPongSplitSlaveMapInfo_MDSS10xx[MDP_MAX_MINOR_VERSION] =
{
   &sMDSS1000_PPSplitSlaveMap[0],   /* MDSS 10.0.0  */
   &sMDSS1000_PPSplitSlaveMap[0],   /* MDSS 10.1.0  */
   NULL,                            /* MDSS 10.2.0  */
   NULL,                            /* MDSS 10.3.0  */
   NULL,                            /* MDSS 10.4.0  */
   NULL                             /* MDSS 10.5.0  */
};



/* MDSS10xx Device Capabilities
 */
const MDP_DeviceCaps sDeviceCaps_MDSS1000 =
{
  &sResolutionCaps_MDSS1000,
  &sPPCaps_MDSS1000[0],
  &sDSCCaps_MDSS1000[0],
};

/* MDP Device caps  for all MDP versions
 */
const MDP_DeviceCaps* DeviceCapInfo_MDSS10xx[MDP_MAX_MINOR_VERSION] =
{
  &sDeviceCaps_MDSS1000,          /* MDSS 10.0.0  */
  &sDeviceCaps_MDSS1000,          /* MDSS 10.1.0  */
  NULL,                           /* MDSS 10.2.0  */
  NULL,                           /* MDSS 10.3.0  */
  NULL,                           /* MDSS 10.4.0  */
  NULL                            /* MDSS 10.5.0  */
};

#endif
