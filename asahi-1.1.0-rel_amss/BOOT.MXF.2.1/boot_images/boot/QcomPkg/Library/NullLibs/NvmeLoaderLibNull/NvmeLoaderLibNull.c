/** @file NvmeLoaderLibNull.c
  
  Stub functions for NvmeLoaderLib

  Copyright (c) 2020-2022 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 11/23/22   ak      Added missing functions.
 07/17/20   sp      Initial revision

=============================================================================*/
#include "nvme_api.h"

uint32
nvme_boot_partition_read(struct nvme_handle *handle,
                         void   *buff,
                         uint32 start_byte,
                         uint32 num_bytes,
                         int boot_partition_id)
{
  return NVME_SUCCESS;
}

uint32
nvme_boot_partition_write(struct nvme_handle *handle,
                          void   *buff,
                          uint32 start_byte,
                          uint32 num_bytes)
{
  return NVME_SUCCESS;
}

uint32
nvme_boot_partition_commit(struct nvme_handle *handle,
                           uint32 id)
{
  return NVME_SUCCESS;
}

uint32 nvme_write_zeroes(struct nvme_handle *handle,
                         uint64             lba,
                         uint64             num_blocks)
{
  return NVME_SUCCESS;
}

uint32 nvme_format (struct nvme_handle *handle,
                    uint32 lba_size)
{
  return NVME_SUCCESS;
}

uint32
nvme_boot_partition_info(struct nvme_handle *handle,
                         uint64 *size_kb, uint8 *bp_active_id)
{
  return NVME_SUCCESS;
}

uint32 nvme_read(struct nvme_handle *handle,
                 void               *buff,
                 uint64             lba,
                 uint64             num_blocks)
{
  return NVME_SUCCESS;
}

uint32 nvme_write(struct nvme_handle *handle,
                  void               *buff,
                  uint64             lba,
                  uint64             num_blocks)
{
  return NVME_SUCCESS;
}

uint32 nvme_flush(struct nvme_handle *handle)
{
  return NVME_SUCCESS;
}

struct nvme_handle *nvme_open (uint32 id, uint32 namespace_num, uint32 *error_num)
{
  return NULL;
}

uint32 nvme_close (struct nvme_handle *handle)
{
  return NVME_SUCCESS;
}

uint32 nvme_get_namespace_sizes (struct nvme_handle *handle,
                                 struct nvme_namespace_sizes *info)
{
  return NVME_SUCCESS;
}

uint32 nvme_get_device_info (uint32 id,
                             struct nvme_device_info *info)
{
  return NVME_SUCCESS;
}
