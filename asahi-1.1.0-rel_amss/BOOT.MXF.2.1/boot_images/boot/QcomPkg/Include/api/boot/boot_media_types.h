#ifndef BOOT_MEDIA_TYPE_H
#define BOOT_MEDIA_TYPE_H

/*===========================================================================

                                Boot Media Type
                                Header File
Copyright 2019-2020, 2022-2023 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   --------     ------------------------------------------------------
05/25/23   nnaram       Updated the media types as per latest pbl strucuture
02/19/23   suhas        Added EEPROM entry to the media family check.
01/05/23   suhas        Added boot_media_family_type
09/22/22   ck           Added SOCKET_FLASHLESS
07/21/20   ck           Adjusted boot_media_type to provide true number of entries
05/13/20   ck           Added EEPROM_FLASH
05/07/20   ck           Added PBL_MEDIA
09/08/19   ds           Initial creation
============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/* Define the media types.*/
typedef enum {
  NO_FLASH           = 0,
  NOR_FLASH          = 1,
  NAND_FLASH         = 2,
  ONENAND_FLASH      = 3,
  SDC_FLASH          = 4,
  EMMC_FLASH         = 5,
  MMC_FLASH          = EMMC_FLASH,
  SPI_FLASH          = 6,
  PCIE_FLASHLESS     = 7,
  UFS_FLASH          = 8,
  RESERVED_0_FLASH   = 9,
  RESERVED_1_FLASH   = 10,
  USB_FLASHLESS      = 11,               /* this is not a real flash type, it's used only for sw_type */
  NVME_FLASH         = 12,
  SPI_NETWORK_FLASH  = 13,
  EMMC_NETWORK_FLASH = 14,
  NAND_NETWORK_FLASH = 15,
  USB_EDL_FLASH      = 16,
  PCIE_EDL_FLASH     = 17,               /*This is used for boot option based FEDL boot through TCSR cookie*/
  GENERIC_EDL_FLASH  = 18,
  SPI_UFS_FLASH      = 19,
  SPI_NVME_FLASH     = 20,
  SPI_EMMC_FLASH     = 21,
  DSPI_FLASH         = 22,
  DSPI_UFS_FLASH     = 23,
  DSPI_NVME_FLASH    = 24,
  DSPI_EMMC_FLASH    = 25,
  QSPI_FLASH         = 26,
  QSPI_UFS_FLASH     = 27,
  QSPI_NVME_FLASH    = 28,
  QSPI_EMMC_FLASH    = 29,
  SOCKET_FLASHLESS   = 30,            
  PBL_MEDIA          = 31,             /* Special, used by XBL to indicate MediaInterface to use PBL passed value */
  MEDIA_TYPE_MAX     = 32,             /* Used to know max number of unique medias */
  SIZE_FLASH_TYPE    = 0x7FFFFFFF      /* Force 4 byte alignment */
 }boot_media_type;

/* Enum to encapsulate like media type in a family */
typedef enum 
{
  BOOT_MEDIA_FAMILY_FLASHLESS = 0,
  BOOT_MEDIA_FAMILY_PAGE,
  BOOT_MEDIA_FAMILY_BLOCK,
  BOOT_MEDIA_FAMILY_NET,
  BOOT_MEDIA_FAMILY_EEPROM,
  BOOT_MEDIA_FAMILY_MAX
} boot_media_family;

#endif /* BOOT_MEDIA_TYPE_H */