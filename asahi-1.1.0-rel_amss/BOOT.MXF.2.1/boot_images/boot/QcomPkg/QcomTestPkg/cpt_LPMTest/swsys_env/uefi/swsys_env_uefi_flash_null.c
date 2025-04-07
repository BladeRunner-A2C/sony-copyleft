/*
===========================================================================
*/
/**
  @file swsys_env_uefi_flash_null.c

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

#include <stdio.h>

#include <Protocol/EFIUsbDevice.h>

#include "swsys_env_uefi_flash.h"
#include "../swsys_env.h"

STATIC
EFI_STATUS
swsys_enumerate_partitions(uint32_t* HandleCount)
{
  return EFI_SUCCESS;
}

uint64_t swsys_flash_write_uefi (void* buf, uint64_t size, uint64_t count, char* partition)
{
  return EFI_SUCCESS;
}

uint64_t swsys_flash_read_uefi (void* buf, uint64_t size, uint64_t count, char* partition, uint64_t* bytes_read)
{
  return EFI_SUCCESS;
}
