#ifndef __TZDIAGCONFIGINFO_H__
#define __TZDIAGCONFIGINFO_H__

/**
 * @file  TzDiagConfigInfo.h
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
              Copyright (c) 2020, 2022 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/

#include <Uefi.h>
#include <TzDiagConfig.h>


/*
*  NOTE:: Keeping the size constraints in mind, always maintain the information of required targets only. 
*/

/* WAIPIO */
tzbsp_diag_config_info_t target_config_info_waipio = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* FILLMORE */
tzbsp_diag_config_info_t target_config_info_fillmore = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* PALIMA */
tzbsp_diag_config_info_t target_config_info_palima = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* KAILUA */
tzbsp_diag_config_info_t target_config_info_Kailua = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* AURORA */
tzbsp_diag_config_info_t target_config_info_aurora = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* NETRANI */
tzbsp_diag_config_info_t target_config_info_netrani = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* HALLIDAY */
tzbsp_diag_config_info_t target_config_info_halliday = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* HAMOA */
tzbsp_diag_config_info_t target_config_info_hamoa = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* LANAI */
tzbsp_diag_config_info_t target_config_info_lanai = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

#endif
