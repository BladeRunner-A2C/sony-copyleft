/*
===========================================================================
*/
/**
  @file swsys_env_uefi_flash.h

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/14/17   jh      Initial revision.

  ====================================================================
*/

#ifndef SWSYS_ENV_UEFI_FLASH_H
#define SWSYS_ENV_UEFI_FLASH_H

#include <Guid/EventGroup.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskIo.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/EFIUsbDevice.h>

EFI_STATUS FastbootErasePartition (IN CHAR8 *PartitionName);

#endif // SWSYS_ENV_UEFI_FLASH_H
