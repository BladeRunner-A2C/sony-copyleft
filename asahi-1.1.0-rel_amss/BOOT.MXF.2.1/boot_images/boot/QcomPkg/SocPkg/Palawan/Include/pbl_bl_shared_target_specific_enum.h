/****************************************************************************** 
**  
**   Qualcomm Technologies Incorporated
** 
**   Copyright (c) 2022, 2023 Qualcomm Technologies, Inc.
**   All rights reserved.
**   Qualcomm Technologies, Inc. Confidential and Proprietary.
** 
******************************************************************************/

#ifndef PBL_BL_SHARED_TARGET_SPECIFIC_ENUM_H
#define PBL_BL_SHARED_TARGET_SPECIFIC_ENUM_H

 /**===========================================================================
 **
 **                        PRIMARY BOOT LOADER
 **                        ------------------- 
 ** FILE 
 **     pbl_bl_shared_target_specific_enum.h
 ** 
 ** GENERAL DESCRIPTION 
 **     This header file contains PBL-BL shared data structure
 **     specific details.
 ** 
 **     Any new shared data that has to be passed to BL should be
 **     added in this file. Any dependencies, like enums, defines etc ...
 **     that are supposed to be passed in this structure should be present
 **     in this file.
 ** 
 **     BL code relies heavily on this structure and hence
 **     everytime there is a change in the shared data-structure
 **     (additions/deletions of fields/new values etc) ... structure
 **     version should be incremented appropriately.
 ** 
 **     Any new shared data field that has to be added has to be
 **     at the end of the structure.
 **
 **     NOTE:
 **     -----
 **
 **     ANY CHANGES INT THIS FILE OR ANY FIELDS RELATED TO THE 
 **     SHARED DATA STRUCTURE MUST BE REVIEWED WITH BL IMAGE
 **     OWNERS.
 **
 **==========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module..
  Notice that changes are listed in reverse chronological order.



  when       who    what, where, why
  --------   ----   ---------------------------------------------------
  05/25/23   nnaram Added params as per the pbl structure
  11/14/22   rama   Initial Revision
============================================================================*/

/******************************************************************************
                         PUBLIC TYPES and TYPE-DEFINES
                         ADD NEW ONES UNDER THIS LINE  
******************************************************************************/
typedef enum _pbl_apps_xbl_shared_data_param_id_type {
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_FW_VERSION,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_PATCH_VERSION,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_RMB_MBOX_BASE_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_CPU_BOOT_SPEED_HZ,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_BOOT_MEDIA_TYPE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_IS_EDL_MODE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_DEV_PROG_ELF_ENTRY_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_CONFIG_ELF_ENTRY_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_SC_EXT_ELF_ENTRY_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_TIMESTAMPS_BUFFER_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_TIMESTAMPS_BUFFER_SIZE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_DEBUG_SHARED_INFO_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_PBL_DEBUG_SHARED_INFO_SIZE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_SC_DEBUG_LOG_ADDR,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_XBL_SC_DEBUG_LOG_SIZE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_TME_CPU_PBL_ROM_BYPASS_FUSE,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_CURRENT_IMAGE_SET = 16,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_BOOT_BLOCK_ELF_ENTRY_ADDR = 17,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_EDL_MEDIA_TYPE = 18,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_MAX,
  PBL_APPS_XBL_SHARED_DATA_PARAM_ID_SIZE = 0x7FFFFFFFF,
} pbl_apps_xbl_shared_data_param_id_type;

#define PBL_APPS_XBL_SHARED_DATA_PARAM_ID_CURRENT_IMAGE_SET PBL_APPS_XBL_SHARED_DATA_PARAM_ID_MAX

#endif /* PBL_BL_SHARED_TARGET_SPECIFIC_ENUM_H */
/*=============================================================================
                                  END OF FILE
=============================================================================*/

