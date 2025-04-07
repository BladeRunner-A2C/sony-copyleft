/*===============================================================================
  Copyright (c) 2018-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         EFIBootConfig.h
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  04/09/18   kpa         initial version

================================================================================*/

#ifndef __EFI_BOOT_CONFIG_H__
#define __EFI_BOOT_CONFIG_H__

/* Define the FLASH types for boot options passed by XBL Loader.
*/
typedef enum
{
  EFI_NO_FLASH_TYPE           = 0,
  EFI_NOR_FLASH_TYPE          = 1,
  EFI_NAND_FLASH_TYPE         = 2,
  EFI_ONENAND_FLASH_TYPE      = 3,
  EFI_SDC_FLASH_TYPE          = 4,
  EFI_MMC_FLASH_TYPE          = 5,
  EFI_SPI_FLASH_TYPE          = 6,
  EFI_PCIE_FLASH_TYPE         = 7,
  EFI_UFS_FLASH_TYPE          = 8,
  EFI_NVME_FLASH_TYPE         = 9,
  EFI_RESERVED_1_FLASH_TYPE   = 10,
  EFI_USB_FLASH_TYPE          = 11,
/*EFI_NVME_FLASH_TYPE         = 12,*/
  EFI_SPI_NETWORK_FLASH_TYPE  = 13,
  EFI_EMMC_NETWORK_FLASH_TYPE = 14,
  EFI_NAND_NETWORK_FLASH_TYPE = 15,
  EFI_SPI_UFS_FLASH_TYPE      = 0x10001,
  EFI_SPI_NVME_FLASH_TYPE     = 0x10002,
  EFI_SPI_EMMC_FLASH_TYPE     = 0x10003,
  EFI_SOCKET_FLASHLESS_TYPE   = 0x10004,
  EFI_USB_FLASHLESS_TYPE      = EFI_USB_FLASH_TYPE,
  EFI_PCIE_FLASHLESS_TYPE     = EFI_PCIE_FLASH_TYPE,
  EFI_MAX_FLASH_TYPE          = 0x7FFFFFFF    /* Force 4 byte alignment */
} FlashDeviceType;

#endif