/*=============================================================================
 *
 * FILE:      flash_partition_services.c
 *
 * DESCRIPTION: Function and data structure declarations specific to the NAND
 *             partition layer
 *
 * PUBLIC CLASSES:  Not Applicable
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 *
 * Copyright (c) 2013, 2020,2022 QUALCOMM Technologies Incorporated.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *===========================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/NandCommonLib/flash_partition_services.c#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 10/27/22     gk      Added Jtag id check to defferentiate Pinnacles and Kuno
 * 09/22/29     tvra    Add jtag_id check for auto targets.
 * 06/21/20     sa      Cleanup.
 * 06/04/20     sa      Moved from flash.h  to nand_api.h
 * 07/02/13     sb      Initial Revision
 *==================================================================*/

/*===================================================================
 *
 *                     Include Files
 *
 ====================================================================*/

#include "flash_nand_partition.h"
#include <string.h>
#include "flash_mibib.h"
#include "flash_miparti.h"
#include "flash_micrc.h"
#include "flash_dal_util.h"
#include "crc.h"

#include "flash_nand.h"
#include "flash_nand_entry.h"

#include "string.h"
#include "HALhwio.h"
#include "ChipInfoHWIO.h"

#define GET_RAW_PAGEBUF(client_ctxt) GET_PDATA(client_ctxt)->raw_page_buffer

#define GET_FLASH_DRV_MEMORY(client_ctxt)                          \
     GET_PDATA(client_ctxt)->flash_mem_info->handle_drv_mem

static int nand_parti_read_pages(flash_client_ctxt *client_ctxt, uint32 page,
  uint32 read_type, void *buffer)
{
  int result = NAND_DEVICE_DONE;
  uint32 buffer_size = client_ctxt->flash_dev_ctxt->dev_info.page_size_bytes;
  
  /* Initialize buffer descriptors */
  //init_buffer_descriptor(client_ctxt, (uint32) buffer, 1,
  //  (DALSysMemDescList *) &parti_buff_desc);

  /* Initialize the page data IOVEC structure */
  //init_page_param(client_ctxt, page, 1, &page_data_iovec);

  result = nand_entry_read_pages(client_ctxt, (enum page_access_opcode) read_type,
    page, 1, buffer, buffer_size);

  return result;
}

static int nand_parti_write_pages(flash_client_ctxt *client_ctxt, uint32 page,
  uint32 write_type, void *buffer)
{
  int result = NAND_DEVICE_DONE;
  uint32 buffer_size = client_ctxt->flash_dev_ctxt->dev_info.page_size_bytes;

  /* Initialize buffer descriptors */
  //init_buffer_descriptor(client_ctxt, (uint32) buffer, 1,
  //  (DALSysMemDescList *) &parti_buff_desc);

  /* Initialize the page data IOVEC structure */
  //init_page_param(client_ctxt, page, 1, &page_data_iovec);

  result = nand_entry_write_pages(client_ctxt, (enum page_access_opcode) write_type,
    page, 1, buffer, buffer_size);

  return result;
}

/*
 * This function compares a partition enty name to a string to find a match.
 */
static int nand_parti_name_matches(flash_partentry_t partentry,
  const unsigned char *name)
{
  if (strncmp(partentry->name, (const char *)name, 
    FLASH_PART_NAME_LENGTH) == 0)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/*
 * This function checks the partition boundaries of MIBIB & EFS2.
 * Boundaries of these partitions shouldn't be changing.
 */
static int nand_parti_check_boundaries(flash_partable_t parti1,
                            flash_partable_t parti2)
{
  uint16 i,j;

  for (i=0; i<parti1->numparts; i++)
  {
    if (strncmp((const char *)(&parti1->part_entry[i].name), "0:MIBIB", 8) == 0)
    {
      for (j=0; j<parti2->numparts; j++)
      {
        if (strncmp((const char *)(&parti2->part_entry[j].name), "0:MIBIB", 8) == 0)
        {
          if ((parti1->part_entry[i].offset != parti2->part_entry[j].offset) ||
              (parti1->part_entry[i].length != parti2->part_entry[j].length))
        
          {
            return FALSE;
          }
        }
      }
    }  
    if (strncmp((const char *)(&parti1->part_entry[i].name), "0:EFS2", 7) == 0)
    {
      for (j=0; j<parti2->numparts; j++)
      {
        if (strncmp((const char *)(&parti2->part_entry[j].name), "0:EFS2", 7) == 0)
        {
          if ((parti1->part_entry[i].offset != parti2->part_entry[j].offset) ||
              (parti1->part_entry[i].length != parti2->part_entry[j].length))
        
          {
            return FALSE;
          }
        }
      }
    }
  }
  return TRUE;
}

/* 
 * This fundtion ensure the partition ordering is preserved.  This can be done by 
 * comparing partition names between new partition table and existing partition table
 * and ignoring the "scrub" partition name
 */
static int nand_parti_check_order(flash_partable_t parti1,
                            flash_partable_t parti2)
{
  uint16 i=0,j=0;

  if (parti1->numparts != parti2->numparts)
  {
    return FALSE;
  }

  /* We can use number of partitions from either, since they are equal */
  while(i<parti1->numparts && j<parti2->numparts)
  {
    FLASHLOG(4,("fptae:  Comparing %s to %s \n", (char *)
      &parti1->part_entry[i].name, (char *)&parti2->part_entry[j].name));

    if (!nand_parti_name_matches(&parti1->part_entry[i],
                                     (const unsigned char *)parti2->part_entry[j].name))
    {
      FLASHLOG(3,("fptae:  Names do not match\n"));
      return FALSE;
    }
    if ((parti1->part_entry[i].attrib1 != parti2->part_entry[j].attrib1) ||
        (parti1->part_entry[i].attrib2 != parti2->part_entry[j].attrib2) ||
        (parti1->part_entry[i].attrib3 != parti2->part_entry[j].attrib3))
    {
      return FALSE;
    }

    i++;
    j++;

    if (strncmp((const char *)(&parti1->part_entry[i].name), "0:SCRUB", 8) == 0)
    {
     i++;
    } 
    if (strncmp((const char *)(&parti2->part_entry[j].name), "0:SCRUB", 8) == 0)
    {
      j++;
    }
  }

  /* Every field matches exactly, indicate success. */
  return TRUE;
}

/* 
 * This function validates newly updated MIBIB partition table
 */
static int nand_parti_validate(flash_client_ctxt *client_ctxt, flash_partable_t usr_parti_ptr)
{
  flash_partable_t nand_parti_ptr =
    ( flash_partable_t )client_ctxt->flash_dev_ctxt->parti_ptr;

  if ( (usr_parti_ptr->magic1 != FLASH_PART_MAGIC1) ||
    (usr_parti_ptr->magic2 != FLASH_PART_MAGIC2))
  {
    FLASHLOG (4,("fnibm: Usr parti magic mismatch.\n"));
    return FALSE;
  }

  if(!nand_parti_check_order (nand_parti_ptr, usr_parti_ptr))
  {
    FLASHLOG(4,("Order of user partition tbl doesn't match with one in flash\n"));
    return FALSE;
  }

  if(!nand_parti_check_boundaries (nand_parti_ptr, usr_parti_ptr))
  {
    FLASHLOG(4,("Boundaries of MIBIB&EFS2 don't match with MIBIB&EFS2 in flash\n"));
    return FALSE;
  }
  return TRUE;
}

/**
* Update the MIBIB partition table in the device and driver
*
* @param handle [IN]
*   DAL interface handle
*
* @param partition_table [IN]
*   Pointer to newly updated MIBIB partition table.
*   MIBIB partition table entries are required to be ordered.
*
* @return int [OUT]
*   Result of the operation.
*
*/
int flash_partition_table_update (nand_handle_t handle, flash_partable_t parti_table)
{
  int latest_mibib_block = -1, new_mibib_block = -1;
  uint32 page, page_size_in_bits;
  uint32 crc32 = 0x0UL;
  uint32 start_block;
  mi_boot_info_t mibib_magic;
  flash_micrc_data_t mibib_crc;
  enum nand_block_state blk_state;
  unsigned char *page_buf  = NULL;
  flash_client_ctxt *client_ctxt;
  volatile uint32 jtag_id = 0;
  uint32 min_mibib_block;
  
  if((handle == NULL) || (parti_table == NULL))
  {
    return NAND_DEVICE_FAIL;
  }

  client_ctxt = (flash_client_ctxt *)handle;
  
  page_buf = (unsigned char *) (GET_RAW_PAGEBUF(client_ctxt));

  latest_mibib_block = client_ctxt->flash_dev_ctxt->mibib_info.new_mibib_block;
  
  if(!nand_parti_validate( client_ctxt, parti_table ))
  {
    FLASHLOG(4,("validating new partition table is failed\n"));
    return NAND_DEVICE_FAIL;
  }
  
   /* Start looking from first MIBIB block */
  jtag_id = HWIO_INF(TLMM_HW_REVISION_NUMBER ,PRODUCT_DEVICE_ID);
  //TODO: Revert back once pbl fixes the issue
  if((jtag_id == JTAG_ID_AUTO_1) || (jtag_id == JTAG_ID_AUTO_2) || 
      (jtag_id == JTAG_ID_PINNACLES_1) || (jtag_id == JTAG_ID_PINNACLES_2))
  {
    new_mibib_block = MIBIB_BLOCK_SEARCH_MIN_AUTO;
	min_mibib_block = MIBIB_BLOCK_SEARCH_MIN_AUTO;
  }
  else
  {
    new_mibib_block = MIBIB_BLOCK_SEARCH_MIN;
	min_mibib_block = MIBIB_BLOCK_SEARCH_MIN;
  }
 
  while (new_mibib_block <= (min_mibib_block + MIBIB_DEFAULT_PARTI_SIZE))
  {
    if (DAL_SUCCESS != nand_entry_block_get_state(client_ctxt,
        new_mibib_block, &blk_state ))
    {
      FLASHLOG (4, ("fnibm: Is Block MIBIB - Get Block Bad Failure.\n"));
      return NAND_DEVICE_FAIL;
    }

    if ((blk_state == NAND_BLOCK_BAD)||(new_mibib_block == latest_mibib_block))
    {
      new_mibib_block++;
    }
    else
    {
      /* erase the block */
      start_block = (new_mibib_block - min_mibib_block);
      if (NAND_DEVICE_DONE != nand_entry_erase_blocks(client_ctxt, start_block, 1))
      {
        FLASHLOG (4, ("Error: device failed during erase\n"));
        return NAND_DEVICE_FAIL;
      }

      page_size_in_bits =
        client_ctxt->flash_dev_ctxt->dev_info.page_size_bytes * 8;

      page = ((latest_mibib_block - min_mibib_block) * 
        client_ctxt->flash_dev_ctxt->dev_info.pages_per_block);

      /* Synchronize with other clients */
      flash_sync_enter(client_ctxt->flash_dev_ctxt->handle_dev_sync);

      if (DAL_SUCCESS != nand_parti_read_pages(client_ctxt, 
            page, NAND_ACCESS_MAIN, page_buf))
      {
        return NAND_DEVICE_FAIL;
      }

      mibib_magic = (mi_boot_info_t)page_buf;
      mibib_magic->age++;

      page = ((new_mibib_block - MIBIB_BLOCK_SEARCH_MIN) * 
        client_ctxt->flash_dev_ctxt->dev_info.pages_per_block);

      if (DAL_SUCCESS != nand_parti_write_pages(client_ctxt, 
            page, NAND_ACCESS_MAIN, page_buf))
      {
        return NAND_DEVICE_FAIL;
      }

      crc32 = crc_32_calc((uint8 *)page_buf, (uint16)page_size_in_bits, crc32);

      page++;

      flash_memset((void *)page_buf, 0xFF,
          client_ctxt->flash_dev_ctxt->dev_info.page_size_bytes);
      flash_memcpy((void *)page_buf, (void *)parti_table,
          sizeof(struct flash_partition_table));

      if (DAL_SUCCESS != nand_parti_write_pages(client_ctxt, 
            page, NAND_ACCESS_MAIN, page_buf))
      {
        return NAND_DEVICE_FAIL;
      }

      crc32 = crc_32_calc((uint8 *)page_buf, (uint16)page_size_in_bits, crc32);

      flash_memset((void *)page_buf, 0xFF,
          client_ctxt->flash_dev_ctxt->dev_info.page_size_bytes);

      mibib_crc = (flash_micrc_data_t)page_buf;
      mibib_crc->magic1 = FLASH_MIBIB_CRC_MAGIC1;
      mibib_crc->magic2 = FLASH_MIBIB_CRC_MAGIC2;
      mibib_crc->version = FLASH_MIBIB_CRC_VERSION;
      mibib_crc->crc = crc32;
   
      page = page + 2;

      if (NAND_DEVICE_DONE != nand_parti_write_pages(client_ctxt, 
            page, NAND_ACCESS_MAIN, page_buf))
      {
        return NAND_DEVICE_FAIL;
      }

      flash_memcpy(client_ctxt->flash_dev_ctxt->parti_ptr,
      ( void *)parti_table, sizeof(struct flash_partition_table));

      client_ctxt->flash_dev_ctxt->mibib_info.new_mibib_block
        = new_mibib_block;

      flash_sync_leave(client_ctxt->flash_dev_ctxt->handle_dev_sync);

      return NAND_DEVICE_DONE;
    }  
  }
  return NAND_DEVICE_FAIL;
}

/**
* Get the MIBIB partition table
*
* @param handle [IN]
*   DAL interface handle
*
* @param partition_table [OUT]
*   Pointer to buffer to read in MIBIB partition table.
*
* @return int [OUT]
*   Result of the operation.
*
*/
int flash_partition_table_get (nand_handle_t handle, flash_partable_t parti_table)
{
  flash_client_ctxt *client_ctxt;

  if((handle == NULL) || (parti_table == NULL))
  {
    return NAND_DEVICE_FAIL;
  }
  
  client_ctxt = (flash_client_ctxt *)handle;

  if (NAND_DEVICE_DONE != nand_retrieve_mibib(client_ctxt))
  {
    return NAND_DEVICE_FAIL;
  }
  
  flash_memcpy((void *)parti_table, (void *)client_ctxt->flash_dev_ctxt->parti_ptr, 
        sizeof(struct flash_partition_table));

  return NAND_DEVICE_DONE;
}

