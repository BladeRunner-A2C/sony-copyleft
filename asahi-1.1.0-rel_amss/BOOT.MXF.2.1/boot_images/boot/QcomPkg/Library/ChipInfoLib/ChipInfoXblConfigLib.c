/*==============================================================================
  @file ChipInfoTargetLib.c

  ChipInfo functions for the XBL Loader ChipInfo Driver.

================================================================================
  Copyright (c) 2017, 2019, 2023, 2024 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Waipio/Library/ChipInfoTargetLib/ChipInfoTargetLib.c#1 $
  $DateTime: 2020/06/24 18:36:20 $
  $Author: pwbldsvc $

==============================================================================*/

/*==============================================================================
      Include Files
==============================================================================*/
#include "ChipInfoLocal.h"
#include "cfg_item_config.h"
#include "DALSys.h"

/*==============================================================================
**  Macros
**============================================================================*/
/*
 *   Minmum size required for XBL_CONFIG_SIZE is CHIPINFO_NUM_PARTS * 8 
 *   Each part contains 8 bytes of info in the binary file.
 */
#define XBL_CONFIG_SIZE                CHIPINFO_NUM_PARTS * 8

/*
 *   Default type in disabled_features.bin taking as short,
 *   Initializing with 0x00000000 into a 4byte int array.
 *   Reading the offset from 4 to ignore the first 4 bytes.
 *   TODO: Need to fix it later
 */
#define READ_OFFSET_FOR_DIS_FEATURES_DATA           4

extern ChipInfoCtxtType ChipInfoCtxt;


/*==============================================================================
**  Functions
**============================================================================*/

/*==============================================================================
  FUNCTION      ChipInfo_GetXblConfigDisabledFeatures

  DESCRIPTION   Reads the disabled parts info from xbl_config file.

==============================================================================*/

void ChipInfo_UpdateDisabledFeaturesFromXblConfig(void)
{
  uint32 *xblconfiglocal = NULL;
  uint32 xbl_cfg_h=0,xbl_cfg_size = 0,nNumPartsInXblConfig = 0;
  config_status_type xblcfg_err_flag = CONFIG_SUCCESS;
  
  ChipInfoCtxtType *pChipInfoCtxt = &ChipInfoCtxt;
  static boolean init_disabled_feature = FALSE;

  if(!init_disabled_feature)
  {
    // XBLConfig Initialization
    xblcfg_err_flag |= cfg_item_config_open("/disabled_features.bin", &xbl_cfg_h, &xbl_cfg_size);
    if(xblcfg_err_flag == CONFIG_SUCCESS)
    {
      if( DALSYS_Malloc(XBL_CONFIG_SIZE,(void *)&xblconfiglocal) == DAL_SUCCESS)
      {
        xblcfg_err_flag |= cfg_item_config_read(xbl_cfg_h, READ_OFFSET_FOR_DIS_FEATURES_DATA, 
                                                (xbl_cfg_size - READ_OFFSET_FOR_DIS_FEATURES_DATA), xblconfiglocal);

       /* xblconfiglocal[0] --> Number of parts in XBL config
        * xblconfiglocal[i] --> PART_ENUM
        * xblconfiglocal[i+1] --> Disabled features associated with PART_ENUM
        */

        nNumPartsInXblConfig = xblconfiglocal[0];
        if((xblcfg_err_flag == CONFIG_SUCCESS) && (xbl_cfg_size != 0) )
        {
           uint32 nPartIdx=0;
           for(uint32 i=0; i < nNumPartsInXblConfig; i++)
            {
               nPartIdx = (i*2) + 1;
               if(xblconfiglocal[nPartIdx] < CHIPINFO_NUM_PARTS)
               {
                 pChipInfoCtxt->aDisabledFeatures[xblconfiglocal[nPartIdx]] |= xblconfiglocal[nPartIdx+1];
               }
            }
          /* Storing partial CPU information in aCPUClusters as we are handling CPU case seperately*/
          pChipInfoCtxt->aCPUClusters[0] |= xblconfiglocal[(2*CHIPINFO_PART_CPU)];
          DALSYS_Free(xblconfiglocal);
          init_disabled_feature = TRUE;
        }
      }
    }
  }
}