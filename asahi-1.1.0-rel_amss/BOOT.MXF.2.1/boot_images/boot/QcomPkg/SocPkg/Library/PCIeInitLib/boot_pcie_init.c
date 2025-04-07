/*===========================================================================

                         Boot PCIe utility functions

GENERAL DESCRIPTION
 Boot PCIe APIs

Copyright 2021-2023 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who             what, where, why
--------   ---         --------------------------------------------------
02/11/23   batta       Replaced OEM_CONFIG0 register with BOOT_CONFIG register
07/08/21   rhy         Enabled Fast boot and PCIe Reset Separation
07/08/21   ck          Renamed xbl_pcie_dump_enabled to xbl_pcie_fast_boot_enabled
02/10/21   vk          Initial rev

===========================================================================*/

#include <comdef.h>
#include "HALhwio.h"
#include "HALbootHWIO.h"

boolean xbl_pcie_fast_boot_enabled(void);

boolean xbl_pcie_fast_boot_enabled(void)
{
  boolean retval = FALSE;
  
  #ifdef HWIO_BOOT_CONFIG_FAST_BOOT_NAND_PCIE_FVAL
    retval = (HWIO_INF(BOOT_CONFIG, FAST_BOOT) == HWIO_BOOT_CONFIG_FAST_BOOT_NAND_PCIE_FVAL);
  #endif
  
  #ifdef HWIO_BOOT_CONFIG_FAST_BOOT_EMMC_PCIE_FVAL
    retval |= (HWIO_INF(BOOT_CONFIG, FAST_BOOT) == HWIO_BOOT_CONFIG_FAST_BOOT_EMMC_PCIE_FVAL);
  #endif

  /* BOOT_OPTION_3 will indicate NAND-PCIe options for Kuno */
  #ifdef HWIO_BOOT_CONFIG_FAST_BOOT_BOOT_OPTION_3_FVAL
    retval |= (HWIO_INF(BOOT_CONFIG, FAST_BOOT) == HWIO_BOOT_CONFIG_FAST_BOOT_BOOT_OPTION_3_FVAL);
  #endif
  
  return retval;
}

boolean xbl_pcie_reset_sep_enabled (void)
{
  return ( (HWIO_IN(AOSS_CC_PCIE_RESET_CTRL)) & (1 << HWIO_SHFT(AOSS_CC_PCIE_RESET_CTRL, PCIE_RESET_SEP_EN)) );
}

