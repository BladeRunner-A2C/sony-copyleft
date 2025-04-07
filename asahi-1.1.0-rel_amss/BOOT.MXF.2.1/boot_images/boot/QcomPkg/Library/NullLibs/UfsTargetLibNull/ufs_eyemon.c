/**********************************************************************
 *
 *   UFS EYEMON implementation
 *
 * Copyright (c) 2022 Qualcomm Technologies, Inc.  
*  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *
 **********************************************************************/

/*======================================================================

                        EDIT HISTORY FOR MODULE


when         who     what, where, why
----------   ---     ---------------------------------------------------
2022-04-18   jt      Initial creation
=======================================================================*/

#include "ufs_api.h"
#include "ufs_eyemon.h"


int32_t ufs_eyemon_get_capabilities (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_caps *caps)
{
   return -UFS_ENOSYS; 
}

int32_t ufs_eyemon_set_config (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_config *config)
{
   return -UFS_ENOSYS; 
}

int32_t ufs_eyemon_enable (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, boolean enable)
{
   return -UFS_ENOSYS;  
}

int32_t ufs_eyemon_get_result (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_result *result)
{
   return -UFS_ENOSYS; 
}

int32_t ufs_eyemon_pm_change (struct ufs_handle *handle, uint8_t gear, uint8_t lanes, uint8_t adapt)
{
   return -UFS_ENOSYS;  
}

int32_t ufs_eyemon_set_coarse_code (struct ufs_handle *handle, uint8_t lane_num, uint8_t coarse_code)
{
   return -UFS_ENOSYS; 
}




