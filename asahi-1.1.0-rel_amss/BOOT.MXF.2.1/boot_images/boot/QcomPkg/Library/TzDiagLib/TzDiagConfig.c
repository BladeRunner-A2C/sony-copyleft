/**
 * @file  TzDiagTarget.c
 * @brief Contains target specific information. 
 */
/*
===============================================================================

                               Edit History

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------ 
08/17/22   var     Added error logging support for PIL authentication
09/09/20   dpk     Created.

===============================================================================
              Copyright (c) 2021-2022 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/

#include <Uefi.h>
#include <TzDiagConfigInfo.h>
#include <Protocol/EFIChipInfo.h>



tzbsp_diag_config_info_t *tz_diag_get_config_info(EFIChipInfoFamilyType chip_family)
{
    tzbsp_diag_config_info_t *p_target_config_info = NULL;
    	
    switch (chip_family)
    {
        case EFICHIPINFO_FAMILY_WAIPIO:
            p_target_config_info = &target_config_info_waipio;
            break;
        
        case EFICHIPINFO_FAMILY_FILLMORE:
            p_target_config_info = &target_config_info_fillmore;
            break;

        case EFICHIPINFO_FAMILY_PALIMA:
            p_target_config_info = &target_config_info_palima;
            break;
        
        case EFICHIPINFO_FAMILY_KAILUA:
            p_target_config_info = &target_config_info_Kailua;
            break;
        
        case EFICHIPINFO_FAMILY_AURORA:
            p_target_config_info = &target_config_info_aurora;
            break;
        
        case EFICHIPINFO_FAMILY_NETRANI:
            p_target_config_info = &target_config_info_netrani;
            break;
        
        case EFICHIPINFO_FAMILY_HALLIDAY:
            p_target_config_info = &target_config_info_halliday;
            break;
        
        case EFICHIPINFO_FAMILY_HAMOA:
            p_target_config_info = &target_config_info_hamoa;
            break;
                
        case EFICHIPINFO_FAMILY_LANAI:
            p_target_config_info = &target_config_info_lanai;
            break;
        
        default:
            DEBUG((EFI_D_ERROR,"tz_diag_get_config_info(): Target 0x%x not supported \n", chip_family));  
    }
  
    return p_target_config_info;
}

