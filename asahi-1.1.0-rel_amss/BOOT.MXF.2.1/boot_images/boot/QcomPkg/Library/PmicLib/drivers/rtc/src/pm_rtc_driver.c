/*! \file
 *  \n
 *  \brief  pm_rtc_driver.c
 *  \details
 *  Copyright (c) 2010,2023 Qualcomm Technologies, Inc. All rights reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/rtc/src/pm_rtc_driver.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/12/17    aab     Moved common Register address defination to driver file
08/20/14    al      Updating comm lib
08/29/14    al      KW fixes
05/20/14    al      Architecture update
05/09/14    va      Using common debug and assert Marco
08/01/13    al      New arch
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_rtc_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACROS AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_RTC_RW_MAX_HW_VER 0x62

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the RTC data */
static pm_rtc_data_type * pm_rtc_data_arr[PM_MAX_NUM_PMICS];

static pm_rtc_register_info_type rtc_reg =
{
  .peripheral_offset = 0x100,
  .rw_status1 = 0x08,
  .rw_status2 = 0x09,
  .rtc_en_ctl = 0x46,
  .alrm_en_ctl = 0x46,
  .alrm_clr = 0x48,
  .int_latched_clr = 0x14,
  .wdata0 = 0x40,
  .wdata1 = 0x41,
  .wdata2 = 0x42,
  .wdata3 = 0x43,
  .time_adj = 0x44,
  .rdata0 = 0x48,
  .rdata1 = 0x49,
  .rdata2 = 0x4A,
  .rdata3 = 0x4B,
  .alrm_data0 = 0x40,
  .alrm_data1 = 0x41,
  .alrm_data2 = 0x42,
  .alrm_data3 = 0x43,
  .alarm_status1 = 0x08,
  .int_rt_sts = 0x10,
  .int_set_type = 0x11,
  .int_polarity_high = 0x12,
  .int_polarity_low = 0x13,
  .int_en_set = 0x15,
  .int_en_clr = 0x16,
  .int_latched_sts = 0x18,
  .int_pending_sts = 0x19,
  .int_priority = 0x1B,
  .msec_rdata0 = 0x62,
  .msec_rdata1 = 0x63,
  .alarm_msec_data0 = 0x44,
  .alarm_msec_data1 = 0x45,
  .alarm_msec_rtc_cfg = 0x56,
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void 
pm_rtc_driver_init(pm_comm_info_type * comm_ptr, peripheral_info_type * peripheral_info, uint32 pmic_index)
{
  pm_rtc_data_type * rtc_ptr = NULL;
  uint8 num_of_peripherals = 0;

  rtc_ptr = pm_rtc_data_arr[pmic_index];

  if (NULL == rtc_ptr)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_RTC_NUM, pmic_index);
    if (num_of_peripherals == 0)
    {
      return;
    }

    pm_malloc(sizeof(pm_rtc_data_type), (void * *) &rtc_ptr);
    pm_rtc_data_arr[pmic_index] = rtc_ptr;
    rtc_ptr->base_address = peripheral_info->base_address;
  
    /*store digital major and minor version*/
    rtc_ptr->dig_maj_min_ver = (peripheral_info->digital_major_version << 4);
    rtc_ptr->dig_maj_min_ver |= peripheral_info->digital_minor_version;

    CORE_VERIFY(rtc_ptr->dig_maj_min_ver <= PMIC_RTC_RW_MAX_HW_VER);
  }

  if (rtc_ptr != NULL)
  {
    /* Assign Comm ptr */
    rtc_ptr->comm_ptr = comm_ptr;

    /* RTC Register Info - Obtaining Data through dal config */
    rtc_ptr->rtc_reg_table = &rtc_reg;
    CORE_VERIFY_PTR(rtc_ptr->rtc_reg_table);

    rtc_ptr->num_of_peripherals = num_of_peripherals;
  }
}

pm_rtc_data_type * 
pm_rtc_get_data(uint32 pmic_index)
{
  if (pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_rtc_data_arr[pmic_index];
  }

  return NULL;
}


uint8 
pm_rtc_get_num_peripherals(uint32 pmic_index)
{
  if ((pmic_index < PM_MAX_NUM_PMICS) && (pm_rtc_data_arr[pmic_index] != NULL))
  {
    return pm_rtc_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}


