/** @file SPSSLib.h

  Secure Processor SubSystem (SPSS) Insider Attack Resistance (IAR) support.

  Copyright (c) 2019 - 2020, 2022  Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
 when         who     what, where, why
 --------     ---     -----------------------------------------------------------
12/08/22      gn      Unified driver for Hamoa and Lanai
07/14/22      nc      Merge Lanai and Hamoa SPSS drivers in core.boot.6.1
=============================================================================*/

#include <Uefi.h>

/*===========================================================================*/
/*                  DEFINES                                                  */
/*===========================================================================*/
#define SPSS_CONFIG_TEST_MASK_1 0x00000001
#define SPSS_CONFIG_TEST_MASK_2 0x00000002
#define EFI_FAILURE (80)

#define SP_CNOC_SP_SCSR_BASE_ADDR        0x01880000
/* Register to write to incase SPSS load fails */
#define SP_CNOC_SP_SCSR_RMB_GPm(m)       (0x01881100 + (0x4*m))
/* Register to write to if flash type is UFS */
#define SP_CNOC_SP_SCSR_MBn_CL2SP_GPm(n,m)       (0x01885028 + (0x2000*n) + (0x4*m))
/* Bit mask to be used to indicate SPSS load failure */
#define SP_SCSR_RMB_GP_LOAD_FAILURE_MASK 0x00000001
#define SP_SCSR_REGISTER_ACCESS_ERROR    0xDEADBEEF
/* Bit mask (15th bit) to be used to indicate to SPSS that flash type is UFS */
#define SP_SCSR_RMB_MB_GP_FLASH_TYPE_UFS_MASK 0x00008000
#define SP_SCSR_RMB_MB_GP_FLASH_TYPE_SPI_MASK 0xFFFF7FFF

EFI_STATUS SPSSLib_Entry
(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
);

