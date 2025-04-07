/*===========================================================================

                    BOOT COLDPLUG DRIVER DEFINITIONS

DESCRIPTION
  Contains wrapper definition for external coldplug drivers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2019, 2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/02/19   ep      Initial Creation.

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_error_if.h"
#include "boot_coldplug_if.h"


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/


/* remove this after getting the actual coldplug api */
int coldplug_restore_primary_gpt_from_partition(enum coldplug_device_type dev_type, int is_embedded_device, const struct coldplug_guid *guid)
{
  return 0;
}

/*===========================================================================
**  Function :  boot_coldplug_get_interface
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes a boot_coldplug_get_interface
*
* @par Dependencies
*   None
*
*/
/*
bl_error_boot_type boot_coldplug_get_interface(boot_coldplug_if_type *coldplug_if)
{
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(coldplug_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_COLDPLUG, BL_ERR_INVALID_PARAMETER);
      break;
    }

    coldplug_if->open_gpt_partition = coldplug_open_gpt_partition;
    coldplug_if->open_mbr_partition = coldplug_open_mbr_partition;
    coldplug_if->close_partition = coldplug_close_partition;
    coldplug_if->read = coldplug_read;
    coldplug_if->write = coldplug_write;
    coldplug_if->init = coldplug_init;
    coldplug_if->sdcc_boot_set_device_info = sdcc_boot_set_device_info;
    coldplug_if->get_size = coldplug_get_size;
    coldplug_if->background_init_start = coldplug_background_init_start;
    coldplug_if->open_boot_device = coldplug_open_boot_device;
    coldplug_if->background_init_finish = coldplug_background_init_finish;
    coldplug_if->open_device = coldplug_open_device;

  } while(FALSE);

  return return_status;
}
*/

boot_coldplug_if_type coldplug_if =
{
  coldplug_open_gpt_partition,
  coldplug_open_mbr_partition,
  coldplug_close_partition,
  coldplug_read,
  coldplug_write,
  coldplug_init,
  sdcc_boot_set_device_info,
  coldplug_get_size,
  coldplug_background_init_start,
  coldplug_open_boot_device,
  coldplug_background_init_finish,
  coldplug_open_device,
  coldplug_iter_open,
  coldplug_iter_close,
  coldplug_iter_next,
  coldplug_get_start_lba,
  coldplug_open_partition,
  coldplug_search_and_get_partition_name,
  coldplug_set_bootable_partition,
  coldplug_get_bootable_partition,
  coldplug_restore_primary_gpt_from_partition
};
