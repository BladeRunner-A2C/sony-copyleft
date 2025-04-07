/*! \file
*  
*  \brief  pm_dump.c ----This file contain PMIC dump related API 
*  \details This file contain PMIC dump related API 
*  
*  &copy; Copyright 2021-2023 Qualcomm Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/utils/src/pm_dump.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
07/20/21   zxz     Created

===========================================================================*/

/*===========================================================================

INCLUDE FILES 

===========================================================================*/
#include "pm_dump.h"
#include "pm_comm.h"
#include "pm_prop_ids.h"
#include "pm_utils.h"
#include "pm_resource_manager.h"
#include "pm_target_information.h"
#include "CoreVerify.h"


/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/
#define PM_MAX_PERIPHERALS_PER_SLAVE  0XFF
#define PM_MAX_BIT_WIDTH              8

/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
pm_err_flag_type pm_dump_pbus_logger(uint8* buf, uint64 offset, uint64 size, 
                                     uint64* dumped_size, boolean* complete)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}


pm_err_flag_type pm_pmic_dump_entry(uint8* buf, uint64 offset, uint64 size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint64 dumped_size = 0;

  static boolean s_pmic_register_dump_complete = FALSE;
  static boolean s_pbus_logger_dump_complete = FALSE;

  if (NULL == buf)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(FALSE == s_pmic_register_dump_complete)
  {
    err_flag |= pm_dump_pmic_register(buf, offset, size, &dumped_size, &s_pmic_register_dump_complete);
    if(FALSE == s_pmic_register_dump_complete)
    {
      // if dump isn't complete, we need to dump from offset 0 next time
      dumped_size = 0;
    }
  }

  if((TRUE == s_pmic_register_dump_complete) && (FALSE == s_pbus_logger_dump_complete))
  {
    buf = buf + dumped_size;
    err_flag |= pm_dump_pbus_logger(buf, offset, size - dumped_size, &dumped_size, &s_pbus_logger_dump_complete);
    
    if(FALSE == s_pbus_logger_dump_complete)
    {
      // if dump isn't complete, we need to dump from offset 0 next time
      dumped_size = 0;
    }
  }

  return err_flag;
}

// Do NOT use end_offset unless complete is set to TRUE
pm_err_flag_type pm_dump_pmic_register(uint8* buf, uint64 offset, uint64 size, uint64* dumped_size, boolean* complete)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean arch_pre7 = pm_is_pmiclib_arch_pre7();
  uint8 *bitmap_ptr = NULL;
  uint8 *bitmap_per_slave_ptr = NULL;
  uint8 bit_index = 0;
  uint32 periph_count = 0;
  uint32 pmic_info_size = 0;
  uint64 index = 0;
  uint64 cpy_cnt = 0, remain_cnt = 0, copied_cnt = 0;
  pm_dump_header_type header = {0};
  pm_pmic_info_type pmic_info[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_PMICS] = {0};  
  uint32 slave_count = 0, periph_index = 0;
  uint32 bus_id = 0, sid_index = 0;
  uint32 pmic_index = 0;
  pm_model_type pmic_model = PMIC_IS_INVALID;
  pm_device_info_type pmic_device_info = {0};

  static boolean s_header_saved = FALSE;
  static boolean s_pbuf_save_complete = TRUE;
  static boolean s_dump_complete = FALSE;
  static uint32 s_bus_id = 0, s_pmic_index = 0;
  static uint32 s_sindex = 0, s_pindex = 0;
  static uint8 s_pbuf[PERIPH_BUF_SIZE];
  static uint32 s_pbuf_index = 0; // point to the buf which dumped to given buffer

  if (NULL == buf || (NULL == dumped_size) || (NULL == complete))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  // Zero the buf to avoid random value in dump
  DALSYS_memset(buf, 0, size);

  *complete = s_dump_complete;
  if((TRUE == s_dump_complete)
    || (0 != (size % 4))
    || (size < sizeof(pm_dump_header_type)))
  {
    // only initialize buf to 0 after dump complete
    // do nothing for invalid input parameter. We suppose the buffer size is not too small.
    return err_flag;
  }

  bitmap_ptr = pm_target_information_get_specific_info(PM_PROP_PERIPH_BITMAP);
  CORE_VERIFY_PTR(bitmap_ptr);

  // Save header and pmic info. This usually requires around 76 byte which is samller than buffer size.
  // The buffer usually > 1KB so don't check the size during saving header and pmic info.
  // So pmic register dump should be executed at the beginning of buffer padding, otherwise need to check
  // if remain buffer is enough
  if(FALSE == s_header_saved)
  {
    // Save PMIC register dump header here
    header.version = PMIC_DUMP_VERSION;
    header.dump_sign = REG_DUMP_START_SIGNATURE;
    header.image_name = IMAGE_SBL;
    header.max_pmic_number = PM_MAX_NUM_PMICS;
    header.max_buses_supported = PM_MAX_BUSES_SUPPORTED;


    // Count the number of valid peripheral
    for(bus_id = 0; bus_id < PM_MAX_BUSES_SUPPORTED; bus_id++)
    {
      for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
      {
        err_flag = pm_get_pmic_info_ex(bus_id, pmic_index, &pmic_device_info);

        pmic_info[bus_id][pmic_index].bus_id = bus_id;
        pmic_info[bus_id][pmic_index].pmic_index = pmic_index;
        
        pmic_model = pmic_device_info.ePmicModel;
        slave_count = pmic_device_info.nSlaveCount;

        if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
        {
          continue;
        }

        pmic_info[bus_id][pmic_index].pmic_model = pmic_model;
        pmic_info[bus_id][pmic_index].revision = pmic_device_info.nPmicAllLayerRevision;

        for(sid_index = 0; sid_index < slave_count; sid_index++)
        {
          if(arch_pre7)
          {
            bitmap_per_slave_ptr = bitmap_ptr + (bus_id * PM_MAX_NUM_SLAVE_IDS * PM_MAX_BITMAP_ENTRIES) +
                                              (pmic_index * (slave_count * PM_MAX_BITMAP_ENTRIES)) + 
                                              (sid_index * PM_MAX_BITMAP_ENTRIES);
          }
          else
          {
            bitmap_per_slave_ptr = bitmap_ptr + (bus_id * PM_MAX_NUM_SLAVE_IDS * PM_MAX_BITMAP_ENTRIES) +
                                              (pmic_index * PM_MAX_BITMAP_ENTRIES);
          }

          for(periph_index = 0; periph_index <= 0xFF; ++periph_index)
          {
            // 8 bit for each byte
            bit_index = periph_index & 0x7;
            if((bitmap_per_slave_ptr[periph_index >> 3] & (1 << bit_index)) != 0)
            {
              ++periph_count;
            }
          }
        }
      }
    }

    header.pm_dump_size = periph_count * PERIPH_BUF_SIZE;

    // Header is not well copied to buf due to incorrect of sizeof(header)
    copied_cnt = DALSYS_memscpy(buf + index, size - index, &header, sizeof(header));
    if(0 == copied_cnt || copied_cnt < sizeof(header))
    {
      // fail to copy
      // It means download fail without right end signature
      return err_flag;
    }

    index += sizeof(header);

    pmic_info_size = sizeof(pmic_info);
    copied_cnt = DALSYS_memscpy(buf + index, size - index, pmic_info, pmic_info_size);
    if(0 == copied_cnt || copied_cnt != pmic_info_size)
    {
      return err_flag;
    }
    index += pmic_info_size;

    s_header_saved = TRUE;

    if(index >= size)
    {
      return err_flag;
    }
  }

  // Save header complete, go through peripheral one by one
  for (;s_bus_id < PM_MAX_BUSES_SUPPORTED; s_bus_id++)
  {
    for(; s_pmic_index < PM_MAX_NUM_PMICS; s_pmic_index++)
    {
      err_flag = pm_get_pmic_info_ex(s_bus_id, s_pmic_index, &pmic_device_info);
        
      pmic_model = pmic_device_info.ePmicModel;
      slave_count = pmic_device_info.nSlaveCount;
      
      if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
      {
        continue;
      }

      for(; s_sindex < slave_count; s_sindex++)
      {
        pm_comm_info_type *comm_ptr = pm_comm_get_comm_info(s_bus_id, s_pmic_index, s_sindex);
        CORE_VERIFY_PTR(comm_ptr);

        if(arch_pre7)
        {
          bitmap_per_slave_ptr = bitmap_ptr + (s_bus_id * PM_MAX_NUM_SLAVE_IDS * PM_MAX_BITMAP_ENTRIES) +
                                            (s_pmic_index * (slave_count * PM_MAX_BITMAP_ENTRIES)) + 
                                            (s_sindex * PM_MAX_BITMAP_ENTRIES);
        }
        else
        {
          bitmap_per_slave_ptr = bitmap_ptr + (s_bus_id * PM_MAX_NUM_SLAVE_IDS * PM_MAX_BITMAP_ENTRIES) +
                                            (s_pmic_index * PM_MAX_BITMAP_ENTRIES);
        }

        // Each sid include at most 0xFF peripheral
        for(; s_pindex <= 0xFF; ++s_pindex)
        {
          // identify if this peripheral index valid
          if((bitmap_per_slave_ptr[s_pindex / 8] & (1 << (s_pindex % 8))) == 0)
          {
            continue;
          }

          if(TRUE == s_pbuf_save_complete)
          {
            // if pbuf have been saved to buf completely, update the whole buffer with next peripheral
            // and then save as much as possible 
            // Store bus id/slave id/peripheral index/reserved and 256 byte register for existing peripheral
            s_pbuf[s_pbuf_index++] = comm_ptr->bus_id; // Bus id
            s_pbuf[s_pbuf_index++] = comm_ptr->slave_id; // sid
            s_pbuf[s_pbuf_index++] = s_pindex;
            s_pbuf[s_pbuf_index++] = 0; // reserved

            err_flag = pm_comm_read_byte_array_ex(comm_ptr->bus_id, comm_ptr->slave_id, s_pindex * PERIPH_OFFSET, REG_NUM_PER_PERIPHERAL, s_pbuf + s_pbuf_index);
            
            if(err_flag != PM_ERR_FLAG_SUCCESS)
            {
               return err_flag;
            }
            
            // Reset s_pbuf_index to original 0. It would be used to point to the mid of s_pbuf if remain buf is not enough,
            // otherwise it will be used as index of next s_pbuf
            s_pbuf_index = 0;
          }

          // Calculate if remain buffer is enough for the whole peripheral dump
          remain_cnt = sizeof(s_pbuf) - s_pbuf_index;

          if(size - index >= remain_cnt)
          {
            // Remain buffer is enough
            cpy_cnt = remain_cnt;
          }
          else
          {
            cpy_cnt = size - index;
          }


          if(s_pbuf_index >= sizeof(s_pbuf))
          {
            // due to error, don't dump further
            s_dump_complete = TRUE;
            return err_flag;
          }

          copied_cnt = DALSYS_memscpy(buf + index, size - index, s_pbuf + s_pbuf_index, cpy_cnt);
          if(0 == copied_cnt || copied_cnt != cpy_cnt)
          {
            // handle of memcpy failure
            return err_flag;
          }

          if(size - index >= remain_cnt)
          {
            // Remain buffer is enough, the whole peripheral has been saved
            // Reset pbuf related static variable to default value
            s_pbuf_index = 0;
            s_pbuf_save_complete = TRUE;

            index += cpy_cnt;
          }
          else
          {
            s_pbuf_index += cpy_cnt; // point to next position of buf which next copy will start from
            s_pbuf_save_complete = FALSE;

            // buf is not enough for current peripheral, copy part of pbuf and wait for next copy cycle
            return err_flag;
          }
        }
        s_pindex = 0; // reset to for next iteration
      }

      s_sindex = 0;
    }
  }

  // index is checked after each copy action, so needn't to check here.
  *((uint32*)(buf + index)) = REG_DUMP_COMPLETE_SIGNATURE;
  s_dump_complete = TRUE;
  *complete = s_dump_complete;
  *dumped_size = index + sizeof(uint32);

  return err_flag;
}

