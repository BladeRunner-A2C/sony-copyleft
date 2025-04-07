/*! \file rgb_api.c
*  \n
*  \details This file contains the top-level API wrappers for the RGB
*           peripheral.
*
*  \n &copy; Copyright 2015-2020 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/rgb/src/pm_rgb.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
0/15/20    xp      Remove unused APIs
11/02/15   al      Updaing RGB with latest
04/06/15   aab     Updating pm_rgb_enable
08/20/14   al      Updating comm lib
05/20/14   al      Architecture update
===========================================================================*/

/*===========================================================================
INCLUDE FILES
===========================================================================*/
#include "pm_rgb.h"
#include "pm_rgb_driver.h"

#define ADDRESS(x) (rgb_ptr->base_address + rgb_ptr->rgb_reg_table->x)
#define SLAVE_ID   (rgb_ptr->comm_ptr->slave_id)

#if defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP)
/* Need to refer PMIC_Software_User_Guide: 80-40939-100
 * Also refer msm-kernel/drivers/leds/leds-qti-flash.c */
#define FLASH_LED_ENABLE(id)            (0x01 << id)
#define FLASH_LED_BASE                  0xEE00
#define FLASH_LED_SAFETY_TIMER(id)      (FLASH_LED_BASE + 0x3E + id)
#define FLASH_LED_ITARGET(id)           (FLASH_LED_BASE + 0x42 + id)
#define FLASH_LED_STROBE_CTRL(id)       (FLASH_LED_BASE + 0x4A + id)
#define FLASH_ENABLE_CONTROL            (FLASH_LED_BASE + 0x46)
#define FLASH_EN_LED_CTRL               (FLASH_LED_BASE + 0x4E)
#define FLASH_LED_IRESOLUTION           (FLASH_LED_BASE + 0x49)
#define FLASH_LED_IRESOLUTION_MASK(id)  (0x01 << id)
#define FLASH_LED_ITARGET_MASK          (0x7F)
#define FLASH_LED_SAFETY_TIMER_EN_MASK  (0x01 << 7)
#define FLASH_LED_HW_SW_STROBE_SEL      (0x01 << 2)
#define FLASH_MODULE_ENABLE             (0x01 << 7)
#define EN_LED_MSK                      (0x0F << 0)
#endif /* defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP) */

pm_err_flag_type pm_rgb_enable
(
  uint32 pmic_chip,
  uint32 rgb_mask,
  boolean enable
)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_rgb_data_type *rgb_ptr = pm_rgb_get_data(pmic_chip);
  pm_register_address_type reg = 0;
  pm_register_data_type rgb_en_ctl_val;

  if (rgb_ptr == NULL)
  {
    err_flag =  PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (rgb_mask > PM_RGB_SEGMENT_ALL)
  {
    err_flag =  PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    reg = ADDRESS(en_ctl);
    rgb_en_ctl_val = enable ? (rgb_mask << 5) : 0x00; /*<R: Bit 7, G: Bit6, B: Bit 5>*/
    rgb_mask = rgb_mask << 5;

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, reg, rgb_mask, rgb_en_ctl_val);
  }

  return err_flag;
}

#if defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP)
pm_err_flag_type pm_enable_flash_led_registers(uint32 slave_id, uint32 flash_led_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_LED_IRESOLUTION, FLASH_LED_IRESOLUTION_MASK(flash_led_id), 0x00);
  err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_LED_ITARGET(flash_led_id), FLASH_LED_ITARGET_MASK, 0x00);
  err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_LED_SAFETY_TIMER(flash_led_id), FLASH_LED_SAFETY_TIMER_EN_MASK, 0x00);
  err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_LED_STROBE_CTRL(flash_led_id), FLASH_LED_HW_SW_STROBE_SEL, 0x00);

  return err_flag;
}

pm_err_flag_type pm_flash_led_module_control(uint32 pmic_device_index, uint8 enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;

  err_flag = pm_get_slave_id(pmic_device_index, 0, &slave_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
    return err_flag;

  if (enable == 1)
  {
    uint8 leds = FLASH_LED_ENABLE(0) | FLASH_LED_ENABLE(3);
    err_flag |= pm_enable_flash_led_registers(slave_id, 0); //FLASH_LED0
    err_flag |= pm_enable_flash_led_registers(slave_id, 3); //FLASH_LED3

    err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_ENABLE_CONTROL, FLASH_MODULE_ENABLE, FLASH_MODULE_ENABLE);
    err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_EN_LED_CTRL, EN_LED_MSK, leds);
  }
  else
  {
    err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_EN_LED_CTRL, EN_LED_MSK, 0x00);
    err_flag |= pm_comm_write_byte_mask(slave_id, FLASH_ENABLE_CONTROL, FLASH_MODULE_ENABLE, 0x00);
  }
  return err_flag;
}
#endif /* defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP) */
