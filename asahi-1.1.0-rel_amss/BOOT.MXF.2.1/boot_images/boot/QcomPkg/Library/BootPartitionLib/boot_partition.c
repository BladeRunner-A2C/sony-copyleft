/*=============================================================================
                     Boot Partition

GENERAL DESCRIPTION
  This file contains the implementation for the boot-specific partition 
  creation information.

Copyright 2022 - 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================
                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
02/19/23   suhas        Added new APIs enable/disable image set and interface.
12/12/22   suhas        Initial revision.
=============================================================================*/


#include <string.h>
#include <boot_partition.h>
#include <boot_target_partitions.h>


/**************************************************************************************
* FUNCTION      get_partition_id_by_partition
*
* DESCRIPTION   This function is used to extract the partition IDs based upon 
*               image set, media type and parition name
*
* PARAMETERS    image_set                 The image set requested with partition name
*               media_family              Type of media corresponding to storage set
*               partition                 The partition name of the required ID
*               result_partition_id       Output buffer to hold partition IDs
*               result_partition_id_size  The output buffer size
*
* RETURN VALUE  BL_ERR_NONE if success
*****************************************************************************************/
bl_error_boot_type get_partition_id_by_partition(boot_media_family media_family, 
                                                 boot_image_set_t image_set, 
                                                 boot_partition_t partition, 
                                                 const uint8 ** result_partition_id, 
                                                 uint8 * result_partition_id_size)
{
  bl_error_boot_type status = BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND;
  uint32 num_partition_definitions = 0;
  uint32 partition_definition_index = 0;


  /* Validating Pointers */
  if ((result_partition_id == NULL) || (result_partition_id_size == NULL))
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Validate partition name */
  if (partition >= MAX_PARTITION)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }


  /* Validate image set */
  if (image_set >= IMAGE_SET_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }


  /* Calculate number of partition definitions entries */
  num_partition_definitions = sizeof(partition_definitions) / sizeof(storage_set_t);


  /* Locate the storage set using the requested media type */
  for (partition_definition_index = 0; 
       partition_definition_index < num_partition_definitions; 
       partition_definition_index++)
  {
    if (partition_definitions[partition_definition_index].media_family == media_family)
    {
      /* Verify the image set is enabled */
      if ((internal_image_set_status[media_family] & (1 << image_set)) ||
          (partition_definitions[partition_definition_index].image_sets[image_set].image_set_valid != TRUE))
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_BOOT_PARTITION_IMAGE_SET_NOT_ENABLED);
        goto exit;
      }

      /* Verify the partition entry is valid */
      if (partition_definitions[partition_definition_index].image_sets[image_set].partition_entries[partition].partition_entry_valid != TRUE)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_BOOT_PARTITION_PARTITION_ENTRY_NOT_ENABLED);
        goto exit;
      }

      /* Partition Entry has been found and validated, returning the pointer */
      *result_partition_id = partition_definitions[partition_definition_index].image_sets[image_set].partition_entries[partition].partition_id;
      *result_partition_id_size = PARTITION_ID_MAX_LENGTH;
      
      status = BL_ERR_NONE;
      break;
    }
  }


 exit:
  return status;
}


/**************************************************************************************
* FUNCTION      get_image_set
*
* DESCRIPTION   This function is used to extract complete image set structure  
*               based on media type and image set.
*
* PARAMETERS    image_set             The image set requested with partition name
*               media_family          Type of media corresponding to storage set
*               result_image_set      Output buffer to hold partition IDs
*               result_image_set_size The output buffer size
*
* RETURN VALUE  BL_ERR_NONE if success
*
*****************************************************************************************/
bl_error_boot_type get_image_set(boot_media_family media_family, 
                                 boot_image_set_t image_set,
                                 const image_set_t ** result_image_set,
                                 uint32 * result_image_set_size) 
{
  bl_error_boot_type status = BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND;
  uint32 num_partition_definitions = 0;
  uint32 partition_definition_index = 0;


  /* Validating Pointers */
  if ((result_image_set == NULL) || (result_image_set_size == NULL))
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Validate image set */
  if (image_set >= IMAGE_SET_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }


  /* Calculate number of partition definition entries */
  num_partition_definitions = sizeof(partition_definitions) / sizeof(storage_set_t);


  /* Locate storage set using requested media type */
  for (partition_definition_index = 0;
       partition_definition_index < num_partition_definitions;
       partition_definition_index++)
  {
    if (partition_definitions[partition_definition_index].media_family == media_family)
    {
      /* Verify image set is valid */
      if ((internal_image_set_status[media_family] & (1 << image_set)) || 
          (partition_definitions[partition_definition_index].image_sets[image_set].image_set_valid != TRUE))
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_BOOT_PARTITION_IMAGE_SET_NOT_ENABLED);
        goto exit;
      }

      /* Image set has been found and validated, returning the pointer */
      *result_image_set = &partition_definitions[partition_definition_index].image_sets[image_set];
      *result_image_set_size = sizeof(image_set_t);              

      status = BL_ERR_NONE;
      break;
    }
  }


 exit:
  return status;
}


/**************************************************************************************
* FUNCTION      get_storage_set
*
* DESCRIPTION   This function is used to extract the storage set structure 
*               based upon the requested media type.
*
* PARAMETERS    media_family            Type of media corresponding to storage set
*               result_storage_set      Output buffer to hold partition IDs
*               result_storage_set_size The output buffer size
*
* RETURN VALUE  BL_ERR_NONE if success
*
*****************************************************************************************/
bl_error_boot_type get_storage_set(boot_media_family media_family,
                                   const storage_set_t ** result_storage_set,
                                   uint32 * result_storage_set_size)
{
  bl_error_boot_type status = BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND;
  uint32 partition_definition_index = 0;
  uint32 num_partition_definitions = 0;


  /* Validating Pointers */
  if ((result_storage_set == NULL) || (result_storage_set_size == NULL))
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }


  /* Calculate the number of partition definitions */
  num_partition_definitions = sizeof(partition_definitions) / sizeof(storage_set_t);
  

  /* Locating the partition definition using requested media type */
  for (partition_definition_index = 0; 
       partition_definition_index < num_partition_definitions;
       partition_definition_index++)
  {
    if (partition_definitions[partition_definition_index].media_family == media_family)
    {
      *result_storage_set = &partition_definitions[partition_definition_index];
      *result_storage_set_size = sizeof(storage_set_t);

      status = BL_ERR_NONE;
      break;
    }
  }


 exit:
  return status;
}


/**************************************************************************************
* FUNCTION      boot_partition_enable_image_set
*
* DESCRIPTION   This function is used to enable a single image set.
*
* PARAMETERS    media_family            Type of media corresponding to storage set
*               image_set               The image set requested with partition name
*
* RETURN VALUE  BL_ERR_NONE if success
*
*****************************************************************************************/
bl_error_boot_type boot_partition_enable_image_set(boot_media_family media_family,
                                                   boot_image_set_t image_set)
{
  bl_error_boot_type status = BL_ERR_NONE;


  /* Validating media_family */
  if (media_family >= BOOT_MEDIA_FAMILY_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND);
    goto exit;
  }


  /* Validate image set */
  if (image_set >= IMAGE_SET_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }


  /* Write 0 to the particular Image_Set bit for enabling it internally */
  internal_image_set_status[media_family] &= ~(1 << image_set);// 


 exit:
  return status;
}


/**************************************************************************************
* FUNCTION      boot_partition_disable_image_set
*
* DESCRIPTION   This function is used to disable a single image set.
*
* PARAMETERS    media_family            Type of media corresponding to storage set
*               image_set               The image set requested with partition name
*
* RETURN VALUE  BL_ERR_NONE if success
*
*****************************************************************************************/
bl_error_boot_type boot_partition_disable_image_set(boot_media_family media_family,
                                                    boot_image_set_t image_set)
{
  bl_error_boot_type status = BL_ERR_NONE;


  /* Validating media_family */
  if (media_family >= BOOT_MEDIA_FAMILY_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND);
    goto exit;
  }


  /* Validate image set */
  if (image_set >= IMAGE_SET_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_INVALID_PARAMETER);
    goto exit;
  }


  /* Write 1 to the particular Image_Set bit for disabling it internally */
  internal_image_set_status[media_family] |= (1 << image_set);


 exit:
  return status;
}


/**************************************************************************************
* FUNCTION      boot_partition_enable_all_image_sets
*
* DESCRIPTION   This function is used to enable all the image sets in a media family.
*
* PARAMETERS    media_family            Type of media corresponding to storage set
*
* RETURN VALUE  BL_ERR_NONE if success
*
*****************************************************************************************/
bl_error_boot_type boot_partition_enable_all_image_sets(boot_media_family media_family)
{
  bl_error_boot_type status = BL_ERR_NONE;


  /* Validating media_family */
  if (media_family >= BOOT_MEDIA_FAMILY_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND);
    goto exit;
  }


  /* Write all 0's to enable all the image sets in a media family */
  internal_image_set_status[media_family] = 0;


 exit:
  return status;
}


/**************************************************************************************
* FUNCTION      boot_partition_disable_all_image_sets
*
* DESCRIPTION   This function is used to diable all the image sets in a media family.
*
* PARAMETERS    media_family            Type of media corresponding to storage set
*
* RETURN VALUE  BL_ERR_NONE if success
*
*****************************************************************************************/
bl_error_boot_type boot_partition_disable_all_image_sets(boot_media_family media_family)
{
  bl_error_boot_type status = BL_ERR_NONE;


  /* Validating media_family */
  if (media_family >= BOOT_MEDIA_FAMILY_MAX)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_BOOT_PARTITION_MEDIA_FAMILY_NOT_FOUND);
    goto exit;
  }


  /* Write all 1's to disable all the image sets in a media family */
  internal_image_set_status[media_family] = -1;


 exit:
  return status;
}


/* Initializing the interface structure */
boot_partition_if_type partition_if = 
{
  get_partition_id_by_partition,         // get_partition_id_by_partition()
  get_image_set,                         // get_image_set()
  get_storage_set,                       // get_storage_set()
  boot_partition_enable_image_set,       // boot_partition_enable_image_set()
  boot_partition_disable_image_set,      // boot_partition_disable_image_set()
  boot_partition_enable_all_image_sets,  // boot_partition_enable_all_image_sets()
  boot_partition_disable_all_image_sets  // boot_partition_disable_all_image_sets()
};