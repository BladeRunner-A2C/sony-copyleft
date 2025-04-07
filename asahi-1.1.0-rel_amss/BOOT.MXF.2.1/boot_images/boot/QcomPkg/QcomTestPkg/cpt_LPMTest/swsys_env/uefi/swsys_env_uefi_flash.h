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

uint64_t swsys_flash_write_uefi (void* buf, uint64_t size, uint64_t count, char* partition);
uint64_t swsys_flash_read_uefi (void* buf, uint64_t size, uint64_t count, char* partition, uint64_t* bytes_read);

#endif // SWSYS_ENV_UEFI_FLASH_H
