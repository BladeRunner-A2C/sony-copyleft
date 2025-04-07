/** @file UsbSharedLibTargetConfig.h
**/
//============================================================================
/**
  Copyright (c) 2022,2023 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================

/*=============================================================================
                              EDIT HISTORY

 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 05/30/22   pw       Init Check-in
=============================================================================*/


#ifndef _USB_SHAREDLIB_TARGET_CONFIG_H_
#define _USB_SHAREDLIB_TARGET_CONFIG_H_


#include "i2c_api.h"

#define USB_SEC_FLAG 0
#define USB_TER_FLAG 0
#define USB_MP_FLAG 0
#define USB_HS_ONLY_FLAG 0

#define USB_ONSEMI_REDRIVER_FLAG (1)
#define USB_KB8001_RETIMER_FLAG  (0)
#define USB_PS8330_RETIMER_FLAG  (0)

#define USB_REPEATER_RESET_NULL (1)

#define USB_RUMI            (0)
#define USB_APB_REG_FLAG    (1)
#define USB_EUSB_SKIP_FLAG_N    (1)

#define USB_WCD_I2C_INSTANCE_PRIMARY  (I2C_INSTANCE_001)
#define USB_WCD_I2C_SLAVE_ADDRESS          (0xE)
#define USB_WCD_PAGE0_PAGE_REG             (0x0)
#define USB_WCD_USB_REG_PAGE               (0x4)
#define USB_WCD_USB_DIG_USB_RST_CTL_REG    (0x414)
#define USB_WCD_USB_RESET_VALUE            (0x0)
#define USB_WCD_USB_NORMAL_VALUE           (0x3)
#define USB_WCD_SWITCH_RST_N_GPIO          (119)
#define USB_WCD_PMP_OUT1_VALUE             (0x28)   //CP_PFM_LOOP_VHIGH(bit5) = 1:SET_CP_PFM_LOOP_VHIGH + reset_value 0x8
#define USB_WCD_PMP_OUT1_ADDR              (0x2)
#define USB_SHARED_PLATFORM_QRD_SUBTYPE__RETIMER (0x3)


#ifndef USB_REDUCE_BOOT_TIME
#define USB_PHY_WRITE_DELAY (10)
#else
#define USB_PHY_WRITE_DELAY (100)
#endif


#define USB_I2C_TIMEOUT_MAX                             (2500)
#define USB_I2C_FREQUENCY_KHZ                           (400)
#define USB_I2C_MAX_CLOCK_STRETCH_US                    (500)

// Allow 3 times retry for the scenario of slave NACKED.
#define USB_I2C_SLAVE_NACKED                            (1 << 3)
#define USB_I2C_RETRY_COUNT_MAX                         (3)



/* The enumeration for GPIO drive strength */
typedef enum 
{
 USB_TLMM_GPIO_DRV_STR_2MA         = 0x0,
 USB_TLMM_GPIO_DRV_STR_4MA         = 0x1,
 USB_TLMM_GPIO_DRV_STR_6MA         = 0x2,
 USB_TLMM_GPIO_DRV_STR_8MA         = 0x3,
 USB_TLMM_GPIO_DRV_STR_10MA        = 0x4,
 USB_TLMM_GPIO_DRV_STR_12MA        = 0x5,
 USB_TLMM_GPIO_DRV_STR_14MA        = 0x6,
 USB_TLMM_GPIO_DRV_STR_16MA        = 0x7,
 USB_TLMM_GPIO_DRV_STR_11MA        = 0x7,
 USB_TLMM_GPIO_DRV_STR_MAX_SUPPORTED,
 USB_TLMM_GPIO_DRV_STR_MAX         = 0xFFFFFFFF,
 USB_TLMM_GPIO_DRV_STR_UNSUPPORTED = USB_TLMM_GPIO_DRV_STR_MAX
} USB_TLMM_GPIO_drv_str_type;

/* Enumeration for GPIO pull-up, pull-down type */
typedef enum
{
  USB_TLMM_GPIO_NO_PULL    = 0,
  USB_TLMM_GPIO_PULL_DOWN  = 0x1,
  USB_TLMM_GPIO_KEEPER     = 0x2,
  USB_TLMM_GPIO_PULL_UP    = 0x3,
  USB_TLMM_GPIO_PULL_SIZE  = 0x7FFFFFFF
} usb_shared_tlmm_gpio_pullup_pulldown_type;


typedef enum
{
  USB_TLMM_GPIO_FUN_GPIO    = 0x0,
  USB_TLMM_GPIO_FUN_MUX_SEL = 0x1,
  USB_TLMM_GPIO_FUN_MAX     = 0x7FFFFFFF
} usb_shared_tlmm_gpio_fun_select_type;




typedef enum {
  USB_PRI_CORE = 0,
#if USB_SEC_FLAG
  USB_SEC_CORE,
#endif  
#if USB_TER_FLAG
  USB_TRI_CORE,
#endif
#if USB_MP_FLAG
  USB_MP_CORE,
#endif
#if USB_HS_ONLY_FLAG
  USB_HS_ONLY_CORE,
#endif
  USB_MAX_NUM_CORE,    /**< Invalid Core. */
} QCOM_USB_CORE_NUM_SOC;



typedef struct
{
    // member variables
    i2c_instance instance;
    i2c_slave_config config;
    boolean opened;
    void *handle;
} usb_i2c_ctx_type;

typedef struct
{
  boolean enable;
}usb_repeater_ctx_type;

typedef struct
{
  boolean enable;
  usb_i2c_ctx_type i2c_ctx;
}usb_redriver_ctx_type;

typedef struct 
{
  usb_i2c_ctx_type i2c_ctx;
  uint32 usb_mode;
  uint32 cc_lane;
} usb_retimer_ctx_type;


typedef struct 
{
  uint16  reg;
  uint8  data;
} usb_booster_cfg_type;

typedef struct
{
  usb_repeater_ctx_type usb_repeater_ctx[USB_MAX_NUM_CORE];
  usb_redriver_ctx_type usb_redriver_ctx[USB_MAX_NUM_CORE];
  usb_retimer_ctx_type  usb_retimer_ctx[USB_MAX_NUM_CORE];
} usb_booster_ctx_type;





boolean usb_shared_pmic_gpio_enable(uint32 gpio_index, boolean is_enable);
#define USB_REPEATER_RESET_GPIO_IDX (0x6)

//============================================================================
/**
* @function  usb_shared_tlmm_gpio_high
*
* @brief For device mode: Configure GPIO high and enabled
*
* @Note : None
*
* @param  GPIO number 
*
* @return None
*
*/
//============================================================================
usb_platform_ctx usb_get_platform (void);

void usb_shared_tlmm_gpio_high(uint32 gpio_number);
void usb_shared_tlmm_gpio_low (uint32 gpio_number);
boolean usb_shared_is_retimer_force_dp4lane_enabled(void);


boolean usb_shared_i2c_open(usb_i2c_ctx_type* i2c_ctx, i2c_instance instance, uint32 slave_addr);

boolean usb_shared_i2c_close(usb_i2c_ctx_type* i2c_ctx);

boolean usb_shared_i2c_write(usb_i2c_ctx_type* i2c_ctx, uint16 addr, uint8* buffer, uint16 buffer_len);

boolean usb_shared_i2c_read(usb_i2c_ctx_type* i2c_ctx, uint16 addr, uint8* buffer, uint16 buffer_len);

boolean usb_shared_spmi_write(uint32 core_num, uint16 addr, uint8 data);

boolean usb_shared_spmi_read(uint32 core_num, uint16 addr, uint8* data);

boolean usb_shared_spmi_init(uint32 core_num);


boolean usb_shared_i2c_process_cfg_reg_array
(
  usb_i2c_ctx_type*             i2c_ctx,
  const usb_booster_cfg_type*   cfg_table,
  uint32                        start_index, 
  uint32                        array_entry_cnt,
  BOOLEAN                       is_write_flag
);

boolean usb_shared_spmi_process_cfg_reg_array
(
  UINT32                       core_num,
  const usb_booster_cfg_type*  cfg_table,
  UINT32                       start_index, 
  UINT32                       array_entry_cnt,
  BOOLEAN                      is_write_flag
);

boolean usb_shared_i2c_bus_scan (uint32 i2c_instance);

#endif /* _USB_SHAREDLIB_TARGET_CONFIG_H_ */
