/** @file SdccJtagBspLib.c

  SDCC driver BSP
  This file implements the SDCC driver BSP for the board in use

  Copyright (c) 2016-2022, 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
2022-04-12   gml     Updated Speed mode values as per DT
2022-01-17   ss      Add support for sdcc bootup using Device Tree Config
2022-01-05   jt      Updates for Kailua 
2021-11-10   jt      Update device tree path 
2021-10-07   ss      Added the sdcc_bsp_get_config function
2021-07-22   vm      Add voltage ON/OFF support for SD Card
2021-07-16   jt      Allow logging of device tree entries
2021-05-24   jt      Add device tree support
2020-06-04   jt      Add power management support  
2020-04-28   jt      Waipio updates
2020-01-30   jt      Update HS200 frequency to 202 MHz
2019-07-22   jt      Add SMMU configuration API  
2019-06-10   jt      Change to 202 MHz clock 
2018-11-09   jt      Update TLMM addr for Kona 
2018-07-13   jt      Add voltage switch functions 
2018-01-25   vk      Remove ArmLib
2017-10-30   jt      Add sdcc_bsp_busy_wait() 
2017-08-22   jt      Update TLMM addr for Hana  
2017-06-16   sb      Get platform specific speed config 
2017-06-12   jt      Update drive strength 
2017-01-17   jt      Update sdcc_bsp_get_max_supported_clk()
2016-12-08   jt      Update for Napali. Rename file.  
2016-01-18   jt      Initial version. Branched from 8996 XBL 

=============================================================================*/


#include <api/systemdrivers/busywait.h>

#include "pm_ldo.h"
#include "pm_version.h"
#include "boot_logger.h"
#include "SdccBspConfig.h"

boolean busywait_inited = FALSE; 

/*=============================================================================
 * FUNCTION      sdcc_bsp_target_cap_overrides
 *
 * DESCRIPTION   This function provides target specific cap overrides
 *
 * PARAMETERS    [IN]: slot number
 *               [IN/OUT]: Capability 0 (HC_REG_40_42)
 *               [IN/OUT]: Capability 1 (HC_REG_44_46)
 *
 * RETURN VALUE  None
 *
 *===========================================================================*/
void sdcc_bsp_target_cap_overrides (UINT32 slot_num, UINT32 *caps0, UINT32 *caps1)
{
   return; 
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_base_addr
 *
 * DESCRIPTION   This function queries the SDCC register base addresses
 *
 * PARAMETERS    [OUT]: sdcc_base_addr_type pointer to retrieve the SDCC base addresses
 *
 * RETURN VALUE  sdcc_bsp_err_type
 *
 *===========================================================================*/
sdcc_bsp_err_type
sdcc_bsp_get_base_addr (sdcc_base_addr_type *sdcc_base_addr)
{
  sdcc_base_addr->sdc2_base_hc = HWIO_SDC2_SDCC5_HC_ADDR;
  
  return SDCC_BSP_NO_ERROR;
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_slot_type
 *
 * DESCRIPTION   This function queries the slot to find out if the slot is designated
 *               for eMMC, SD or no device.
 *
 * PARAMETERS    [IN]: slot number
 *
 * RETURN VALUE  sdcc_bsp_slot_type
 *
 *===========================================================================*/
sdcc_bsp_slot_type
sdcc_bsp_get_slot_type (UINT32 slot_num)
{
   sdcc_bsp_slot_type slot_type = SDCC_BSP_NO_SLOT;

   if (slot_num >= SDCC_BSP_NUM_SLOTS)
   {
      /* Return No slot available*/
      slot_type = SDCC_BSP_NO_SLOT;
   }
   else
   {
      slot_type = sdcc_bsp_slot_config [slot_num];
   }

   return slot_type;
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_slot_access_type
 *
 * DESCRIPTION   This function queries the slot to find out if the slot is designated
 *               as internal or external memory device. Hotplug needs this info
 *               to determine which memory device to boot from.
 *
 * PARAMETERS    [IN]: slot number
 *
 * RETURN VALUE  sdcc_bsp_slot_access_type
 *
 *===========================================================================*/
sdcc_bsp_slot_access_type
sdcc_bsp_get_slot_access_type (UINT32 slot_num)
{
   sdcc_bsp_slot_access_type slot_access_type = SDCC_BSP_SLOT_INVALID;

   if (slot_num >= SDCC_BSP_NUM_SLOTS)
   {
      /* Return No slot available*/
      slot_access_type = SDCC_BSP_SLOT_INVALID;
   }
   else
   {
      slot_access_type = sdcc_bsp_slot_access_config [slot_num];
   }

   return slot_access_type;
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_hsr_settings
 *
 * DESCRIPTION   This function gets the HSR settings for DLL configuration
 *
 * PARAMETERS    [IN]: slot number
 *               [IN]: speed mode 
 *               [OUT]: hsr_settings
 *
 * RETURN VALUE  sdcc_bsp_err_type
 *
 *===========================================================================*/
sdcc_bsp_err_type sdcc_bsp_get_hsr_settings (UINT32 slot_num, sdcc_bsp_speed_mode speed_mode, 
                                             sdcc_bsp_hsr_settings_type *hsr_settings)
{
   (void)slot_num; 
   (void)speed_mode;
   (void)hsr_settings; 
   
   return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_gpio_control
 *
 * DESCRIPTION   This function enables/disables the GPIO interface to the
 *               card slot.
 *
 * PARAMETERS    [IN]: slot number
 *               [IN]: GPIO ON/OFF
 *
 * RETURN VALUE  sdcc_bsp_err_type.
 *
 *===========================================================================*/
sdcc_bsp_err_type
sdcc_bsp_gpio_control (UINT32 slot_num, UINT32 state)
{
   if(slot_num >= SDCC_BSP_NUM_SLOTS)
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   if(SDCC_BSP_NO_SLOT == sdcc_bsp_slot_config [slot_num])
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   switch(slot_num)
   {
      case SDCC_BSP_SLOT_1:
         out_dword (HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR, SDCC_BSP_DEFAULT_DRIVE_STRENGTH);
         break;
      default:
         return SDCC_BSP_ERR_INVALID_PARAM;
   }

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_max_supported_mclk_freq
*
* DESCRIPTION   Get the maximum mclock frequency supported
*
* PARAMETERS    [IN]: drive number
*
* RETURN VALUE  Clock frequency supported
*
******************************************************************************/
sdcc_bsp_clk_type
sdcc_bsp_get_max_supported_clk (UINT32 driveno)
{   
   switch(driveno)
   {
   case SDCC_BSP_SLOT_1:
      return SDCC_BSP_CLK_202_MHZ;
   default:
      return SDCC_BSP_CLK_INVALID;
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_supported_freq
*
* DESCRIPTION   Get the supported frequency for various speed modes
*
* PARAMETERS    [IN]: drive number
*               [OUT]: Frequency for corresponding speed modes
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_get_supported_freq (UINT32 driveno, sdcc_bsp_supported_frequencies *freq)
{
   if (driveno == SDCC_BSP_SLOT_1) 
   {
      freq->ds_mode = SDCC_BSP_CLK_25_MHZ;
      freq->hs_mode = SDCC_BSP_CLK_50_MHZ;
      freq->sdr12_mode = SDCC_BSP_CLK_INVALID;
      freq->sdr25_mode = SDCC_BSP_CLK_INVALID;
      freq->sdr50_mode = SDCC_BSP_CLK_INVALID;
      freq->ddr50_mode = SDCC_BSP_CLK_INVALID; 
      freq->hs200_mode = SDCC_BSP_CLK_INVALID;
      freq->hs400_mode = SDCC_BSP_CLK_INVALID; 
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_busy_wait
*
* DESCRIPTION   Waits for the specified amount of us
*
* PARAMETERS    [IN]: us to wait 
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_busy_wait(UINT32 us)
{
   if (FALSE == busywait_inited)
   {
      busywait_init(); 
      busywait_inited = TRUE; 
   }
   busywait(us); 
}

/******************************************************************************
* FUNCTION      sdcc_bsp_cache_operation
*
* DESCRIPTION   Performs cache operations on the provided memory region.
*               Used for DMA related operations only.
*
* PARAMETERS    [IN]: cache operation type
*               [IN]: start address of the memory region
*               [IN]: length of the memory region
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_cache_operation
(
   sdcc_bsp_cache_op_type op,
   void *addr,
   UINT32 length
)
{
   switch(op)
   {
      case SDCC_BSP_CACHE_FLUSH:
        WriteBackInvalidateDataCacheRange (addr, length);
        break;

      case SDCC_BSP_CACHE_INVAL:
        InvalidateDataCacheRange (addr, length);
        break;

      default:
        break;
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_vreg_switch_status
*
* DESCRIPTION   Check whether PMIC APIs work (for UHS-1) by enabling the VDD
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_get_vreg_switch_status (UINT32 driveno)
{
   if (SDCC_BSP_SLOT_1 == driveno)
   {
      return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;  
   }
   else
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_lower_volt_level
*
* DESCRIPTION   Lower the VDD to 1.8V for UHS1
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_lower_volt_level (UINT32 driveno)
{
   if (SDCC_BSP_SLOT_1 == driveno)
   {
      return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;  
   }
   else
   {
      return SDCC_BSP_ERR_INVALID_PARAM; 
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_memory_barrier
*
* DESCRIPTION   Performs data memory barrier operation.
*
* PARAMETERS    None
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_memory_barrier(void)
{
   ArmDataMemoryBarrier(); 
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_slot_count
*
* DESCRIPTION   Get the maximum SDCC number of slots support
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  Maximum number of slots on the target
*
******************************************************************************/
UINT32 sdcc_bsp_get_slot_count (VOID)
{
   return SDCC_BSP_NUM_SLOTS;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_platform_speed_config
*
* DESCRIPTION   Get the speed config based on the platform
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  Speed config based on the platform
*
******************************************************************************/
UINT8 sdcc_bsp_get_platform_speed_config (UINT32 driveno)
{
   switch(driveno)
   {
      case SDCC_BSP_SLOT_1:
         return SDCC_HS_MODE;        
      default:
         return SDCC_INVALID_SPEED; 
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_configure_smmu
*
* DESCRIPTION   Configure the SMMU for SDCC
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_configure_smmu() 
{
   return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_default_volt_corner
*
* DESCRIPTION   Provides the default voltage corner 
*
* PARAMETERS    [OUT]: volt_corner
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_default_volt_corner (UINT8 *volt_corner)
{
   (void)volt_corner; 

   return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_check_valid_operational_mode
*
* DESCRIPTION   Checks whether the voltage corner and speed mode are compatible
*
* PARAMETERS    [IN]: driveno
*               [IN]: volt_corner
*               [IN]: speed_mode
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_check_valid_operational_mode (UINT32 driveno, 
                                                         UINT8 volt_corner, 
                                                         UINT8 speed_mode)
{
   (void)driveno;
   (void)volt_corner;
   (void)speed_mode;

   return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_operational_mode_info
*
* DESCRIPTION   Provides information about speed modes and voltage corners
*               supported
*
* PARAMETERS    [IN]: driveno
*               [IN]: curr_speed_mode
*               [OUT]: caps
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_operational_mode_info (UINT32 driveno,
                                                  sdcc_bsp_speed_mode curr_speed_mode, 
                                                  void *caps)
{
   (void)driveno; 
   (void)curr_speed_mode;
   (void)caps;

   return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_volt_set
*
* DESCRIPTION   Turns on voltage regulators for SD Card(SDC2)
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_volt_set (UINT32 driveno, sdcc_bsp_regulator_mode mode)
{
   (void)driveno; 
   (void)mode;
   
   return SDCC_BSP_NO_ERROR;   
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_config
*
* DESCRIPTION   Get the SDCC configuration for differnt parameters from the target specific files
*
* PARAMETERS    [IN]: Drive Number , sdcc_bsp_config structure
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_get_config (UINT32 driveno, sdcc_bsp_config *sdcc_config_data)
{
	sdcc_config_data->ExtSlotNumber   =  1;
	sdcc_config_data->MAXSlotNumber   =  1;
	sdcc_config_data->DmaEnabled      =  TRUE;
	sdcc_config_data->EmmcSlotNumber  =  0;
	sdcc_config_data->SpeedMode       =  SDCC_HS_MODE;
	
	if (driveno ==  SDCC_BSP_SLOT_1)
	{
	  sdcc_config_data->SpeedMode   = sdcc_bsp_get_platform_speed_config(driveno);
	}
	
	return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_rca
*
* DESCRIPTION   Get the SDCC Relative Card Address from the target specific files
*
* PARAMETERS    [IN]: Drive Number
*
* RETURN VALUE  RCA value
*
******************************************************************************/
UINT16 sdcc_bsp_get_rca (UINT32 driveno)
{
	UINT16 rca = 0;
	
	if (driveno == SDCC_BSP_SLOT_0)
	{
	    rca = 2;
	}
	return rca;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_is_adma_supported
*
* DESCRIPTION   Get the SDCC ADMA availability from the target specific files
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  Boolean value
*
******************************************************************************/
BOOLEAN sdcc_bsp_is_adma_supported() 
{
	BOOLEAN ret = TRUE;
	return ret;
}
