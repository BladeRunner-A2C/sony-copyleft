/*! \file
*  
*  \brief  pm_utils.c ----This file contains the implementation of pm_malloc()
*  \details This file contains the implementation of pm_malloc()
*  
*  &copy; Copyright 2015-2023 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/utils/src/pm_utils.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
12/18/17   aab     Depricated pm_convert_time_to_timetick() and  pm_convert_timetick_to_time(), Since it assumes a fixed Clock speed
12/05/17   aab     Added support to log total number of mem allocated
07/21/17   czq     Use Spare reg PON_PERPH_RB_SPARE instead of PON_DVDD_RB_SPARE
08/12/16   aab     Added pm_sbl_get_adc_batt_id_pd_res_ohms() 
08/03/16   akm     Moved pm_clk_busy_wait to framework/src pm_busy_wait
05/26/16   al      Fix for API to return idx 
09/25/15   al      Removing the redundant check
05/01/14   aab     Added pm_clk_busy_wait()
03/20/14   aab     Added pm_boot_adc_get_mv() 
06/11/13   hs      Adding settling time for regulators.
06/20/12   hs      Created

===========================================================================*/

/*===========================================================================

INCLUDE FILES 

===========================================================================*/
#include "pm_utils.h"
#include "DALSys.h"
#include "CoreVerify.h"
#include "busywait.h"
#include "pmio_pon.h"
#include "pm_comm.h"
#include "adc.h"
#include "SpmiCfg.h"
#include "SpmiBus.h"
#include "pm_dt_parser.h"
#include "pm_target_information.h"
#include "pm_log_utils.h"
#include "TimetickUEFI.h"
#include <Library/BaseLib.h>
/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/
static uint32 pmic_malloc_total_size = 0;

char status_message[PM_STATUS_MSG_LEN + PM_STATUS_MSG_HEAD_LEN]="PM: ";
pm_err_flag_type 
pm_utils_oem_cfg_chnl_check(SpmiCfg_ChannelCfg  merged_spmi_cfg_ptr, 
                            SpmiBusCfg_OemChannelCfg spmi_oem_cfg_ptr);

typedef pm_err_flag_type 
(*pm_comm_rd_wr_ptr)(uint32 slave_id, uint16 addr, uint32 num_byte, uint8* data);

void 
pm_utils_spmi_time_cal(pm_comm_rd_wr_ptr pm_comm_rd_wr, uint16 addr, 
                       uint32 num_byte, uint8* data, uint64 *time_us);

#define SDAM_2_MEM_21_ADDR 0x7155

/* For settings validation test */
pm_register_address_type settings_test_flag_reg[2] = {0x88F, SDAM_2_MEM_21_ADDR};

static boolean validation_flag = FALSE;
static uint64 start_tick = 0;
static uint32 timetick_freq = 0;

static boolean spmi_buffer_allocated = FALSE;
static SpmiCfg_ChannelCfg*  merged_spmi_cfg_ptr = NULL;
static uint32 *spmi_cfg_size = NULL;

/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
void
pm_malloc(uint32 dwSize, void **ppMem)
{
    DALResult dalResult = DAL_SUCCESS;

    dalResult = DALSYS_Malloc(dwSize, ppMem);
    CORE_VERIFY(dalResult == DAL_SUCCESS );
    CORE_VERIFY_PTR(*ppMem);

    DALSYS_memset(*ppMem, 0, dwSize);

    pmic_malloc_total_size += dwSize;
}

void
pm_free(void **pMem)
{
  DALResult dalResult = DAL_SUCCESS;

  if (*pMem != NULL)
  {
    dalResult = DALSYS_Free(*pMem);

    CORE_VERIFY(dalResult==DAL_SUCCESS);

    *pMem = NULL;
  }
}

uint32
pm_get_mem_allocated(void)
{
  return pmic_malloc_total_size;
}

uint8
pm_utils_get_upper_idx(uint32 data_value, uint32 *data_list, uint8 list_count)
{
  uint8 idx = 0;

  if (data_list == NULL || list_count == 0)
  {
    CORE_VERIFY(0);
  }

  for (idx = 0; idx < list_count-1; idx++)
  {
    if (data_value <= data_list[idx]) 
      break;
  }
 
  return idx;
} 

boolean 
pm_driver_init_status(void)
{
  uint8 spare_data;
  uint8 perph_reset_data;  

  pm_comm_read_byte_mask(0, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, PON_PERPH_RB_SPARE_DRIVER_INIT_MASK, &spare_data);
  pm_comm_read_byte_mask(0, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK, &perph_reset_data);

  if ((spare_data == PON_PERPH_RB_SPARE_DRIVER_INIT_MASK) && (perph_reset_data == PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

boolean 
pm_device_init_status(void)
{
  uint8 spare_data;
  uint8 perph_reset_data;  

  pm_comm_read_byte_mask(0, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, PON_PERPH_RB_SPARE_DEVICE_INIT_MASK, &spare_data);
  pm_comm_read_byte_mask(0, PMIO_PON_PBS_PERPH_RESET_CTL3_ADDR, PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK, &perph_reset_data);

  if ((spare_data == PON_PERPH_RB_SPARE_DEVICE_INIT_MASK) && (perph_reset_data == PMIO_PON_PBS_PERPH_RESET_CTL3_FOLLOW_WARM_RB_BMSK))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

static uint32
pm_spmi_populate_oem_cfg(uint32* owner_dt_config, uint32 owner_dt_count,
                        SpmiBusCfg_OemChannelCfg *spmi_oem_cfg, SpmiBusCfg_OwnerMask owner)
{
  static uint32 i = 0; 
  uint32 j = 0;
  CORE_VERIFY_PTR(spmi_oem_cfg);
  CORE_VERIFY(owner <= SPMI_OWNER_INVALID);
  if(owner_dt_config == NULL)
  {
    return i;
  }

  while(owner_dt_count)
  {
    spmi_oem_cfg[i].busId = owner_dt_config[j];
    spmi_oem_cfg[i].slaveId = owner_dt_config[j+1];
    spmi_oem_cfg[i].periphId = owner_dt_config[j+2];
    spmi_oem_cfg[i].ownerMask = owner;
    spmi_oem_cfg[i].operation = owner_dt_config[j+3];
    i++;
    j = j+4;
    owner_dt_count--;
  }
  return i;
}

static uint32
pm_spmi_merge_oem_chnls(SpmiCfg_ChannelCfg*  merged_spmi_cfg_ptr, uint32 spmi_cfg_size,
                        SpmiBusCfg_OemChannelCfg *spmi_oem_cfg, uint32 total_oem_chnls)
{

  uint32 i = 0, j = 0;

  if (merged_spmi_cfg_ptr == NULL || spmi_oem_cfg == NULL || total_oem_chnls == 0)
  {
    return spmi_cfg_size;
  }

  for(i = 0; i < total_oem_chnls; i++)
  {
    switch(spmi_oem_cfg[i].operation)
    {
      case SPMI_CHNL_APPEND_IRQ:
        for (j = 0; j < spmi_cfg_size; j++)
        {

          if( merged_spmi_cfg_ptr[j].busId == spmi_oem_cfg[i].busId &&
              merged_spmi_cfg_ptr[j].slaveId == spmi_oem_cfg[i].slaveId &&
              merged_spmi_cfg_ptr[j].periphId == spmi_oem_cfg[i].periphId &&
              merged_spmi_cfg_ptr[j].irqOwnerMask == merged_spmi_cfg_ptr[j].periphOwnerMask)
          {
            pm_utils_oem_cfg_chnl_check(merged_spmi_cfg_ptr[j], spmi_oem_cfg[i]);

            merged_spmi_cfg_ptr[j].irqOwnerMask                = spmi_oem_cfg[i].ownerMask;
            merged_spmi_cfg_ptr[spmi_cfg_size].busId           = spmi_oem_cfg[i].busId;
            merged_spmi_cfg_ptr[spmi_cfg_size].slaveId         = spmi_oem_cfg[i].slaveId;
            merged_spmi_cfg_ptr[spmi_cfg_size].periphId        = spmi_oem_cfg[i].periphId;
            merged_spmi_cfg_ptr[spmi_cfg_size].irqOwnerMask    = spmi_oem_cfg[i].ownerMask;
            merged_spmi_cfg_ptr[spmi_cfg_size].periphOwnerMask = spmi_oem_cfg[i].ownerMask;
            spmi_cfg_size++;
            break;
          }
        }
  
        if( j == spmi_cfg_size )
        {
          pm_log_message(" channel for periph id 0x%x not found for appendIRQ operation", spmi_oem_cfg[i].periphId);
          CORE_VERIFY(0);
        }
        break;

      case SPMI_CHNL_APPEND:
        for (j = 0; j < spmi_cfg_size; j++)
        {
          if( merged_spmi_cfg_ptr[j].busId == spmi_oem_cfg[i].busId &&
              merged_spmi_cfg_ptr[j].slaveId == spmi_oem_cfg[i].slaveId &&
              merged_spmi_cfg_ptr[j].periphId == spmi_oem_cfg[i].periphId )
          {
            pm_utils_oem_cfg_chnl_check(merged_spmi_cfg_ptr[j], spmi_oem_cfg[i]);

            merged_spmi_cfg_ptr[spmi_cfg_size].busId           = spmi_oem_cfg[i].busId;
            merged_spmi_cfg_ptr[spmi_cfg_size].slaveId         = spmi_oem_cfg[i].slaveId;
            merged_spmi_cfg_ptr[spmi_cfg_size].periphId        = spmi_oem_cfg[i].periphId;
            merged_spmi_cfg_ptr[spmi_cfg_size].irqOwnerMask    = SPMI_OWNER_NONE;
            merged_spmi_cfg_ptr[spmi_cfg_size].periphOwnerMask = spmi_oem_cfg[i].ownerMask;
            merged_spmi_cfg_ptr[spmi_cfg_size].oemConfigurable = SPMI_CHNL_OEMCFG_ALLOWED;
            spmi_cfg_size++;
        break;
          }
        }
        
        if( j == spmi_cfg_size )
        {
          pm_log_message(" periph id 0x%x not found for append operation", spmi_oem_cfg[i].periphId);
          CORE_VERIFY(0);
        }
        break;

      case SPMI_CHNL_REMOVE:
        for (j = 0; j < spmi_cfg_size; j++)
        {
          if( merged_spmi_cfg_ptr[j].busId == spmi_oem_cfg[i].busId &&
              merged_spmi_cfg_ptr[j].slaveId == spmi_oem_cfg[i].slaveId &&
              merged_spmi_cfg_ptr[j].periphId == spmi_oem_cfg[i].periphId &&
              merged_spmi_cfg_ptr[j].periphOwnerMask == spmi_oem_cfg[i].ownerMask)
          {
            pm_utils_oem_cfg_chnl_check(merged_spmi_cfg_ptr[j], spmi_oem_cfg[i]);

            merged_spmi_cfg_ptr[j].irqOwnerMask                = SPMI_OWNER_NONE;
            merged_spmi_cfg_ptr[j].periphOwnerMask             = SPMI_OWNER_NONE;
            break;
          }
        }
        break;
      case SPMI_CHNL_INVALID_OPERATION:
        break;
      default:
        break;
    }
  }
  return spmi_cfg_size;
}

pm_err_flag_type
pm_utils_get_spmi_channels(SpmiCfg_ChannelCfg **spmi_cfg, uint32 *cfg_sz)
{

   SpmiCfg_ChannelCfg*  spmi_cfg_ptr   = NULL;
   pm_access_ctrl_config *access_dt_cfg = NULL;
   uint32 total_oem_chnls = 0;
   //uint32 oem_cfg_arr_count = 0;
   SpmiBusCfg_OemChannelCfg *spmi_oem_cfg = NULL;
   //UINTN num_bytes_copied = 0;
    
  if (cfg_sz == NULL || spmi_cfg == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

   if (spmi_buffer_allocated == TRUE)
   {
        *cfg_sz = *spmi_cfg_size;
        *spmi_cfg = merged_spmi_cfg_ptr;
        return PM_ERR_FLAG_SUCCESS;
   }

   spmi_cfg_ptr = (SpmiCfg_ChannelCfg*)pm_target_information_get_specific_info(PM_PROP_SPMI_CHANNEL_CFG);
   CORE_VERIFY_PTR(spmi_cfg_ptr);

   spmi_cfg_size = (uint32*)pm_target_information_get_specific_info(PM_PROP_SPMI_CHANNEL_CFG_SIZE);
   CORE_VERIFY_PTR(spmi_cfg_size);

   //DT Config
   access_dt_cfg = (pm_access_ctrl_config*)pm_dt_get_node( PMIC_DT_NODE_ARB_ACCESS );

   if (access_dt_cfg != NULL)
   {
      total_oem_chnls = access_dt_cfg->none_count + access_dt_cfg->apps_count + access_dt_cfg->tz_count +
                        access_dt_cfg->mss_count + access_dt_cfg->uefi_count + access_dt_cfg->adsp_count +
                        access_dt_cfg->aop_count + access_dt_cfg->ssc_count + access_dt_cfg->secpro_count +
                        access_dt_cfg->invalid_count;
   }

   if((*spmi_cfg_size + total_oem_chnls) > 0)
   {
     pm_malloc( ((spmi_cfg_size[0] + total_oem_chnls)*sizeof(SpmiCfg_ChannelCfg)), (void**)&merged_spmi_cfg_ptr );
     CORE_VERIFY_PTR(merged_spmi_cfg_ptr);
     /*num_bytes_copied =*/ DALSYS_memscpy( (void*)merged_spmi_cfg_ptr, (sizeof(SpmiCfg_ChannelCfg) * (spmi_cfg_size[0] + total_oem_chnls)), (void*)spmi_cfg_ptr, (sizeof(SpmiCfg_ChannelCfg) * spmi_cfg_size[0]) );
   }

   if (access_dt_cfg != NULL && total_oem_chnls > 0)
   {
     pm_malloc((total_oem_chnls * sizeof(SpmiBusCfg_OemChannelCfg)), (void**)&spmi_oem_cfg);

     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->none_owner,    access_dt_cfg->none_count,    spmi_oem_cfg, SPMI_OWNER_NONE);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->apps_owner,    access_dt_cfg->apps_count,    spmi_oem_cfg, SPMI_OWNER_APPS);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->tz_owner,      access_dt_cfg->tz_count,      spmi_oem_cfg, SPMI_OWNER_TZ);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->mss_owner,     access_dt_cfg->mss_count,     spmi_oem_cfg, SPMI_OWNER_MSS);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->uefi_owner,    access_dt_cfg->uefi_count,    spmi_oem_cfg, SPMI_OWNER_UEFI);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->adsp_owner,    access_dt_cfg->adsp_count,    spmi_oem_cfg, SPMI_OWNER_LPASS);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->aop_owner,     access_dt_cfg->aop_count,     spmi_oem_cfg, SPMI_OWNER_AOP);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->ssc_owner,     access_dt_cfg->ssc_count,     spmi_oem_cfg, SPMI_OWNER_SSC);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->secpro_owner,  access_dt_cfg->secpro_count,  spmi_oem_cfg, SPMI_OWNER_SECPROC);
     /*oem_cfg_arr_count += */ pm_spmi_populate_oem_cfg(access_dt_cfg->invalid_owner, access_dt_cfg->invalid_count, spmi_oem_cfg, SPMI_OWNER_INVALID);
   
     *spmi_cfg_size = pm_spmi_merge_oem_chnls(merged_spmi_cfg_ptr, spmi_cfg_size[0], spmi_oem_cfg, total_oem_chnls);
   }

   *cfg_sz = *spmi_cfg_size;
   *spmi_cfg = merged_spmi_cfg_ptr;
   spmi_buffer_allocated = TRUE;


   return PM_ERR_FLAG_SUCCESS;
}

void
pm_utils_free_spmi_buffer()
{
  pm_free((void**)&merged_spmi_cfg_ptr);
  spmi_buffer_allocated = FALSE;
}

pm_err_flag_type 
pm_utils_settings_validation_flag(uint8 *flag, boolean reset)
{
   pm_register_address_type flag_reg = 0x00;
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   *flag=0x00; 
   
   if(TRUE == pm_is_pmiclib_arch_pre7())
   {
     flag_reg = settings_test_flag_reg[0];
   }
   else
   {
     flag_reg = settings_test_flag_reg[1];
   }
   
   err_flag |= pm_comm_read_byte_mask(0, flag_reg, 0x01, flag); // read bit 0 of register retrived to decide  whether test needs to be triggered or not
   
   if (reset) 
   {
      err_flag |= pm_comm_write_byte_mask(0, flag_reg, 0x01, 0x00); // reset flag for validation test
   }    
   return err_flag;
}

void 
pm_utils_start_timer()
{
  if(!validation_flag)
  { 
    pm_utils_settings_validation_flag(&validation_flag, 0);
  }
  
  if(validation_flag)
  {
    Timetick_Init();
    Timetick_GetFreq(TIMETICK_QTIMER, &timetick_freq);
    Timetick_GetCount(TIMETICK_QTIMER, &start_tick);
  }
}

uint64 
pm_utils_get_time(char* func_name)
{
  uint64 delta_time_tick = 0;
  uint64 time_ms = 0;
  uint64 current_tick = 0;
  
  if(validation_flag)
  {
    Timetick_GetCount(TIMETICK_QTIMER, &current_tick);
    
    delta_time_tick = current_tick - start_tick;
    time_ms = (delta_time_tick*1000) / timetick_freq; // for sec to milisec

    if(func_name != NULL)
    {
      pm_log_message("%.35s execution_time %dms",func_name ,time_ms );
    }

    Timetick_GetCount(TIMETICK_QTIMER, &start_tick);
  }
  
  return delta_time_tick;
}

void
pm_utils_get_timestamp(pm_timer_units timer_units, uint64 *time_tick_value)
{
  uint64 time_tick = 0;
  uint32 tick_freq = 0;

  if(time_tick_value != NULL)
  {
    Timetick_Init();
    Timetick_GetCount(TIMETICK_QTIMER, &time_tick); // time in sec
    Timetick_GetFreq(TIMETICK_QTIMER, &tick_freq);

    switch(timer_units)
    {
      case PM_TIME_IN_SEC:
        break;
      case PM_TIME_IN_MSEC:
        time_tick = MultU64x32(time_tick, CONVERSION_SEC_TO_MSEC);
        break;
      case PM_TIME_IN_USEC:
        time_tick = MultU64x32(time_tick, CONVERSION_SEC_TO_USEC);
        break;
      default:
        pm_log_message("issue required timer units, default timer in secs->0, for msec->1 or usec->2");
        break;
    }

    *time_tick_value = DivU64x32(time_tick, tick_freq);
  }
}

void 
pm_utils_spmi_time_cal(pm_comm_rd_wr_ptr pm_comm_rd_wr, uint16 addr, uint32 num_byte, uint8* data,uint64 *time_us)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint64 delta_time_tick = 0;
  uint64 tot_time_tick = 0;
  uint32 i = 0;
  
  for(i=0; i < 1000; i++)
  {
    pm_utils_start_timer();
    err_flag = pm_comm_rd_wr(0,addr,num_byte,data);
    delta_time_tick = pm_utils_get_time(NULL);
    
    if(err_flag == PM_ERR_FLAG_SUCCESS)
     {
       tot_time_tick += delta_time_tick;
     }
    else
     {
       break;
     }
  }
  
  *time_us = MultU64x32(tot_time_tick, CONVERSION_SEC_TO_USEC);
  *time_us = DivU64x32(*time_us, timetick_freq);
  *time_us = *time_us / (i+1);
}

pm_err_flag_type
pm_utils_avg_spmi_tx_time()
{
  uint64 time_us = 0 ;
  uint8 data[8]={0};
  
  if(validation_flag)
  {  
     /***reading single byte from the location 0x4D1******/
     (void)pm_utils_spmi_time_cal(pm_comm_read_byte_array,0x4D1,1,data,&time_us);
     pm_log_message("SPMI_TX: 1 byte SPMI_RD %dus" ,time_us);
         
     /***writting single byte from the location 0x4D1******/
     (void)pm_utils_spmi_time_cal(pm_comm_write_byte_array,0x4D1,1,data,&time_us);
     pm_log_message("SPMI_TX: 1 byte SPMI_WR %dus" ,time_us);
       
     /***Reading  Multi byte from the location 0x400******/
     (void)pm_utils_spmi_time_cal(pm_comm_read_byte_array,0x400,8,data,&time_us);
     pm_log_message("SPMI_TX: Multi byte SPMI_RD %dus" ,time_us);
         
     /***writting Multi byte from the location 0x400******/
     (void)pm_utils_spmi_time_cal(pm_comm_write_byte_array,0x400,8,data,&time_us);
     pm_log_message("SPMI_TX: Multi byte SPMI_WR %dus" ,time_us);
  }
  
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type 
pm_utils_oem_cfg_chnl_check(SpmiCfg_ChannelCfg  merged_spmi_cfg_ptr, SpmiBusCfg_OemChannelCfg spmi_oem_cfg_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if (merged_spmi_cfg_ptr.oemConfigurable == SPMI_CHNL_OEMCFG_ALLOWED)
  {
    err_flag = PM_ERR_FLAG_SUCCESS;
  }
  else if ( (spmi_oem_cfg_ptr.ownerMask == SPMI_OWNER_UEFI) 
            && (merged_spmi_cfg_ptr.oemConfigurable == SPMI_CHNL_OEMCFG_UEFI))
  {
     err_flag = PM_ERR_FLAG_SUCCESS;
  }
  else
  {
     err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
  }

  
  
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {  
    pm_log_message("periph id 0x%x modification is not allowed", merged_spmi_cfg_ptr.periphId);
    CORE_VERIFY(0);
  }
  
  return err_flag;
}

void
pm_utils_log_err(const char* func_name, pm_err_flag_type err_flag, uint16 line_num)
{
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    pm_log_message("%s error; err_code: %d, line: %d", func_name, err_flag, line_num);
  }
}
