/*===========================================================================

                       Recovery Boot UEFI Source File

GENERAL DESCRIPTION
  This file contains functions to read/write Recovery Boot Info to recovery_boot_info_partition

Copyright 2023 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
03/20/23   vk      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <string.h>
#include <RecoveryBootInfoLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <recovery_boot_info.h>
#include <crc.h>
/* EFI_GUID recovery_boot_info_partition_id = { 0X5334F9BA, 0X02CE, 0X4609, { 0x90, 0x81, 0x2E, 0xC3, 0x9D, 0xCD, 0x6A, 0xC6 } }; */
/* Partition Label : recoveryinfo */

static recovery_boot_info_type recovery_boot_info;

/*==============================================================================
**  Functions
**============================================================================*/

/*=========================================================================

**  Function :  rbi_read_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads recovery boot info from storage
*
*/

recovery_boot_status rbi_get_recovery_boot_info(recovery_boot_info_type **recovery_boot_info_ptr)
{
  EFI_STATUS read_status;
  recovery_boot_status status = RBI_SUCCESS;
  UINTN recovery_boot_info_size = sizeof(recovery_boot_info_type);
  recovery_boot_info_type *ReadBuffer = NULL;
  UINTN ReadSize = 0;
  UINTN CopyLength = 0;

  do
  {
    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    *recovery_boot_info_ptr = &recovery_boot_info;

    if (recovery_boot_info.magic_cookie == RBI_MAGIC_COOKIE)
    {
      break;
    }

    read_status = ReadFromPartition (NULL, L"recoveryinfo", (void**)&ReadBuffer, &ReadSize, 0);
    if ((EFI_ERROR(read_status)) || (ReadBuffer == NULL))
    {
      status = RBI_READ_ERR;
      break;
    }

    if (ReadBuffer->magic_cookie != RBI_MAGIC_COOKIE)
    {
      /* Partition does not have data - use memory copy defaulting to set A*/
      memset ((void*)&recovery_boot_info, 0, sizeof (recovery_boot_info_type));

      recovery_boot_info.magic_cookie          = RBI_MAGIC_COOKIE;
      recovery_boot_info.version               = RBI_CURRENT_VERSION;
      recovery_boot_info.image_set_status      = SET_AB_USABLE;
      recovery_boot_info.owner                 = OWNER_UEFI;
      recovery_boot_info.boot_set.magic        = 0;
      recovery_boot_info.boot_set.selected_set = BOOT_SET_INVALID;

      goto exit;
    }
    else
    {
      /* Partition has data */
      if (ReadBuffer->recovery_boot_info_crc_enable_magic == RBI_CRC_MAGIC)
      {
        /* CRC enabled, check crc */
        uint32 calculated_crc32 = 0;
        uint16 recoveryinfo_crc_size = 0;

        recoveryinfo_crc_size = sizeof (recovery_boot_info_type) -
                                sizeof (recovery_boot_info.recovery_boot_info_crc) -
                                sizeof (recovery_boot_info.recovery_boot_info_crc_enable_magic);

        calculated_crc32 = crc_32_calc ((uint8*)ReadBuffer, recoveryinfo_crc_size, RBI_CRC32_DEFAULT_SEED);
        if (calculated_crc32 == ReadBuffer->recovery_boot_info_crc)
        {
          CopyLength = CopyMemS((void*)*recovery_boot_info_ptr, recovery_boot_info_size, ReadBuffer, recovery_boot_info_size);
          if (CopyLength != recovery_boot_info_size)
          {
            status = RBI_READ_ERR;
            break;
          }
          goto exit;
        }
        else
        {
          rbi_log_message ("RBOOT: CRC fail\n");

          /* Partition has data but CRC check failed- use memory copy defaulting to set A*/
          memset ((void*)&recovery_boot_info, 0, sizeof (recovery_boot_info_type));
          recovery_boot_info.magic_cookie          = RBI_MAGIC_COOKIE;
          recovery_boot_info.version               = RBI_CURRENT_VERSION;
          recovery_boot_info.image_set_status      = SET_AB_USABLE;
          recovery_boot_info.owner                 = OWNER_UEFI;
          recovery_boot_info.boot_set.magic        = 0;
          recovery_boot_info.boot_set.selected_set = BOOT_SET_INVALID;

          goto exit;
        }
      }
      else
      {
        CopyLength = CopyMemS((void*)*recovery_boot_info_ptr, recovery_boot_info_size, ReadBuffer, recovery_boot_info_size);
        if (CopyLength != recovery_boot_info_size)
        {
          status = RBI_READ_ERR;
          break;
        }
        goto exit;
      }
    }
  } while (FALSE);

exit:
  return status;
}

/*=========================================================================

**  Function :  rbi_write_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes recovery boot info to storage
*
*/
recovery_boot_status rbi_write_partition(recovery_boot_info_type *recovery_boot_info_ptr)
{
  EFI_STATUS write_status;
  recovery_boot_status status = RBI_SUCCESS;
  UINTN recovery_boot_info_size = sizeof(recovery_boot_info_type);

  /* If crc enabled, update with crc */
  if ((recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE) &&
      (recovery_boot_info_ptr->recovery_boot_info_crc_enable_magic == RBI_CRC_MAGIC))
  {
    uint32 calculated_crc32 = 0;
    uint16 recoveryinfo_crc_size = 0;

    recoveryinfo_crc_size = sizeof (recovery_boot_info_type) -
                            sizeof (recovery_boot_info.recovery_boot_info_crc) -
                            sizeof (recovery_boot_info.recovery_boot_info_crc_enable_magic);

    calculated_crc32 = crc_32_calc ((uint8*)recovery_boot_info_ptr, recoveryinfo_crc_size, RBI_CRC32_DEFAULT_SEED);

    recovery_boot_info_ptr->recovery_boot_info_crc = calculated_crc32;
  }

  write_status = WriteToPartition (NULL, L"recoveryinfo", (void*)recovery_boot_info_ptr, recovery_boot_info_size, 0);
  if (EFI_ERROR(write_status))
  {
    status = RBI_WRITE_ERR;
  }

  return status;
}


recovery_boot_status rbi_log_message (char* message)
{
  DEBUG((EFI_D_ERROR, "%a",  message));
  return RBI_SUCCESS;
}

