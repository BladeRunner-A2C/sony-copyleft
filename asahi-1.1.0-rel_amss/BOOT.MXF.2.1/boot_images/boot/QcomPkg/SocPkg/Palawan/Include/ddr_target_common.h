#ifndef _DDR_TARGET_COMMON_H
#define _DDR_TARGET_COMMON_H

/*===========================================================================

                                ddr_target_common.h
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2022, 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ----------------------------------------------------------
11/21/22	bpk				target specific
02/13/23        sy                              added to support Palawan Target         
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/

typedef enum 
{
    DARE_REGION_HYP = 0,     //region0
    DARE_REGION_TZ_TA_S1,    //region1
    DARE_REGION_TA_S2,       //region2
    DARE_REGION_TUI_VM,      //region3
    DARE_REGION_OEM_VM,      //region4
    DARE_REGION_OEM_1,       //region5
    DARE_REGION_OEM_2,       //region6
    DARE_REGION_OEM_3,       //region7 
    DARE_REGION_OEM_4,       //region8
    DARE_REGION_SMMU_PT,     //region9
    DARE_REGION_RESERVED_1,  //region10
    DARE_REGION_RESERVED_2,  //region11
    DARE_REGION_MTE_DATA_R0, //region12
    DARE_REGION_MTE_AT_R0,   //region13 
    DARE_REGION_MODEM_1,     //region14
    DARE_REGION_MODEM_2,     //region15
    MAX_DARE_REGION_IDS /* Add new valid entries ABOVE this definition */
}DARE_REGION_ID;

#endif  /* _DDR_TARGET_COMMON_H */
