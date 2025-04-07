/**
    @file  hsuart_devcfg.h
    @brief device configuration implementation
 */
/*=============================================================================

  Copyright 2023 Qualcomm Technologies, Inc. All rights reserved
    Confidential and Proprietary - Qualcomm Technologies, Inc

=============================================================================*/

#ifndef __HSUART_DEVCFG_H__
#define __HSUART_DEVCFG_H__

#include "HSUART_config.h"



//
// CONFIGURATION START ============================================
//

// enable the cores that are used on this image
#define BOOT_USE_HSUART_11


#define TLMM_GPIO_CFG(gpio, func, dir, pull, drive) \
                          (((gpio) & 0x3FF) << 4  | \
                           ((func) & 0xF  ) << 0  | \
                           ((dir)  & 0x1  ) << 14 | \
                           ((pull) & 0x3  ) << 15 | \
                           ((drive)& 0xF  ) << 17)

#define TLMM_GPIO_INPUT      0x0
#define TLMM_GPIO_OUTPUT     0x1
#define TLMM_GPIO_NO_PULL    0x0
#define TLMM_GPIO_PULL_DOWN  0x1
#define TLMM_GPIO_PULL_UP    0x3
#define HSAURT_TLMM_GPIO_2MA        0x0


#define QUPV3_0_CORE_BASE_ADDRESS        0x00A00000
#define QUPV3_0_CORE_COMMON_BASE_ADDRESS 0x00AC0000

#define QUPV3_1_CORE_BASE_ADDRESS        0x00800000
#define QUPV3_1_CORE_COMMON_BASE_ADDRESS 0x008C0000

// set GPIOs for the defined cores
// TLMM_GPIO_CFG(gpio, func, dir, pull, drive)
// QUP0
#define HSUART_01_CTS  TLMM_GPIO_CFG(52,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_01_RFR  TLMM_GPIO_CFG(53,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_01_TX   TLMM_GPIO_CFG(54,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_01_RX   TLMM_GPIO_CFG(55,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_02_CTS  TLMM_GPIO_CFG(4,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_02_RFR  TLMM_GPIO_CFG(5,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_02_TX   TLMM_GPIO_CFG(6,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_02_RX   TLMM_GPIO_CFG(7,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_03_CTS  TLMM_GPIO_CFG(8,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_03_RFR  TLMM_GPIO_CFG(9,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_03_TX   TLMM_GPIO_CFG(10,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_03_RX   TLMM_GPIO_CFG(11,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_04_CTS  TLMM_GPIO_CFG(12,  2, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_04_RFR  TLMM_GPIO_CFG(13,  2, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_04_TX   TLMM_GPIO_CFG(14,  3, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_04_RX   TLMM_GPIO_CFG(15,  3, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_05_CTS  TLMM_GPIO_CFG(16,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_05_RFR  TLMM_GPIO_CFG(17,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_05_TX   TLMM_GPIO_CFG(18,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_05_RX   TLMM_GPIO_CFG(19,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_06_CTS  TLMM_GPIO_CFG(20,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_06_RFR  TLMM_GPIO_CFG(21,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_06_TX   TLMM_GPIO_CFG(22,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_06_RX   TLMM_GPIO_CFG(23,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_07_CTS  TLMM_GPIO_CFG(24,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_07_RFR  TLMM_GPIO_CFG(25,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_07_TX   TLMM_GPIO_CFG(26,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_07_RX   TLMM_GPIO_CFG(27,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_08_CTS  TLMM_GPIO_CFG(28,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_08_RFR  TLMM_GPIO_CFG(29,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_08_TX   TLMM_GPIO_CFG(30,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_08_RX   TLMM_GPIO_CFG(31,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
// QUP1
#define HSUART_09_CTS  TLMM_GPIO_CFG(0,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_09_RFR  TLMM_GPIO_CFG(1,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_09_TX   TLMM_GPIO_CFG(2,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_09_RX   TLMM_GPIO_CFG(3,   1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_10_CTS  TLMM_GPIO_CFG(36,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_10_RFR  TLMM_GPIO_CFG(37,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_10_TX   TLMM_GPIO_CFG(36,  3, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_10_RX   TLMM_GPIO_CFG(37,  3, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_11_CTS  TLMM_GPIO_CFG(40,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_11_RFR  TLMM_GPIO_CFG(41,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_11_TX   TLMM_GPIO_CFG(42,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_11_RX   TLMM_GPIO_CFG(43,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_12_CTS  TLMM_GPIO_CFG(44,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_12_RFR  TLMM_GPIO_CFG(45,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_12_TX   TLMM_GPIO_CFG(46,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_12_RX   TLMM_GPIO_CFG(47,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_13_CTS  TLMM_GPIO_CFG(176, 1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_13_RFR  TLMM_GPIO_CFG(177, 1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_13_TX   TLMM_GPIO_CFG(176, 2, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_13_RX   TLMM_GPIO_CFG(177, 2, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_14_CTS  TLMM_GPIO_CFG(32,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_14_RFR  TLMM_GPIO_CFG(33,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_14_TX   TLMM_GPIO_CFG(34,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_14_RX   TLMM_GPIO_CFG(35,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_15_CTS  TLMM_GPIO_CFG(56,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_15_RFR  TLMM_GPIO_CFG(57,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_15_TX   TLMM_GPIO_CFG(58,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_15_RX   TLMM_GPIO_CFG(59,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

#define HSUART_16_CTS  TLMM_GPIO_CFG(60,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)
#define HSUART_16_RFR  TLMM_GPIO_CFG(61,  1, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_16_TX   TLMM_GPIO_CFG(60,  2, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_UP,   HSAURT_TLMM_GPIO_2MA)
#define HSUART_16_RX   TLMM_GPIO_CFG(61,  2, TLMM_GPIO_OUTPUT, TLMM_GPIO_PULL_DOWN, HSAURT_TLMM_GPIO_2MA)

// CONFIGURATION END   ============================================
//

#define NUM_HSUART_CORES_IN_USE (sizeof(hsuart_device_config)/sizeof(hsuart_plat_device_config))

const char *qup_common_clock_str_0 [] =
{
    "gcc_qupv3_wrap0_core_2x_clk",
    "gcc_qupv3_wrap0_core_clk",
    "gcc_qupv3_wrap_0_s_ahb_clk",
    "gcc_qupv3_wrap_0_m_ahb_clk",
    NULL,
};

const char *qup_common_clock_str_1 [] =
{
    "gcc_qupv3_wrap1_core_2x_clk",
    "gcc_qupv3_wrap1_core_clk",
    "gcc_qupv3_wrap_1_s_ahb_clk",
    "gcc_qupv3_wrap_1_m_ahb_clk",
    NULL,
};



const char *qup_se_clock_str_0 [] =
{
    "gcc_qupv3_wrap0_s0_clk",
    "gcc_qupv3_wrap0_s1_clk",
    "gcc_qupv3_wrap0_s2_clk",
    "gcc_qupv3_wrap0_s3_clk",
    "gcc_qupv3_wrap0_s4_clk",
    "gcc_qupv3_wrap0_s5_clk",
    "gcc_qupv3_wrap0_s6_clk",
    "gcc_qupv3_wrap0_s7_clk",
};

const char *qup_se_clock_str_1 [] =
{
    "gcc_qupv3_wrap1_s0_clk",
    "gcc_qupv3_wrap1_s1_clk",
    "gcc_qupv3_wrap1_s2_clk",
    "gcc_qupv3_wrap1_s3_clk",
    "gcc_qupv3_wrap1_s4_clk",
    "gcc_qupv3_wrap1_s5_clk",
    "gcc_qupv3_wrap1_s6_clk",
    "gcc_qupv3_wrap1_s7_clk",
};



#ifdef BOOT_USE_HSUART_01
hsuart_plat_device_config hsuart_device_config_01 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x00080000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 0,
        .se_index            = 0,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_01_TX,
        .gpio_rx_config      = HSUART_01_RX,
        .gpio_cts_config     = HSUART_01_CTS,
        .gpio_rfr_config     = HSUART_01_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 0),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_02
hsuart_plat_device_config hsuart_device_config_02 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x00084000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 1,
        .se_index            = 1,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_02_TX,
        .gpio_rx_config      = HSUART_02_RX,
        .gpio_cts_config     = HSUART_02_CTS,
        .gpio_rfr_config     = HSUART_02_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 1),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_03
hsuart_plat_device_config hsuart_device_config_03 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x00088000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 2,
        .se_index            = 2,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_03_TX,
        .gpio_rx_config      = HSUART_03_RX,
        .gpio_cts_config     = HSUART_03_CTS,
        .gpio_rfr_config     = HSUART_03_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 2),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_04
hsuart_plat_device_config hsuart_device_config_04 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x0008C000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 3,
        .se_index            = 3,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_04_TX,
        .gpio_rx_config      = HSUART_04_RX,
        .gpio_cts_config     = HSUART_04_CTS,
        .gpio_rfr_config     = HSUART_04_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 3),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_05
hsuart_plat_device_config hsuart_device_config_05 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x00090000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 4,
        .se_index            = 4,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_05_TX,
        .gpio_rx_config      = HSUART_05_RX,
        .gpio_cts_config     = HSUART_05_CTS,
        .gpio_rfr_config     = HSUART_05_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 4),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_06
hsuart_plat_device_config hsuart_device_config_06 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x00094000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 5,
        .se_index            = 5,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_06_TX,
        .gpio_rx_config      = HSUART_06_RX,
        .gpio_cts_config     = HSUART_06_CTS,
        .gpio_rfr_config     = HSUART_06_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 5),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_07
hsuart_plat_device_config hsuart_device_config_07 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x00098000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 6,
        .se_index            = 6,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_07_TX,
        .gpio_rx_config      = HSUART_07_RX,
        .gpio_cts_config     = HSUART_07_CTS,
        .gpio_rfr_config     = HSUART_07_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 6),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_08
hsuart_plat_device_config hsuart_device_config_08 =
    {
        .uart_base           = (QUPV3_0_CORE_BASE_ADDRESS + 0x0009C000),
        .qup_common_base     = QUPV3_0_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 7,
        .se_index            = 7,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_08_TX,
        .gpio_rx_config      = HSUART_08_RX,
        .gpio_cts_config     = HSUART_08_CTS,
        .gpio_rfr_config     = HSUART_08_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_0,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_0 + 7),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_09
hsuart_plat_device_config hsuart_device_config_09 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x00080000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 8,
        .se_index            = 0,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_09_TX,
        .gpio_rx_config      = HSUART_09_RX,
        .gpio_cts_config     = HSUART_09_CTS,
        .gpio_rfr_config     = HSUART_09_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 0),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_10
hsuart_plat_device_config hsuart_device_config_10 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x00084000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 9,
        .se_index            = 1,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_10_TX,
        .gpio_rx_config      = HSUART_10_RX,
        .gpio_cts_config     = HSUART_10_CTS,
        .gpio_rfr_config     = HSUART_10_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 1),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_11
hsuart_plat_device_config hsuart_device_config_11 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x00088000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 10,
        .se_index            = 2,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_11_TX,
        .gpio_rx_config      = HSUART_11_RX,
        .gpio_cts_config     = HSUART_11_CTS,
        .gpio_rfr_config     = HSUART_11_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 2),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_12
hsuart_plat_device_config hsuart_device_config_12 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x0008C000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 11,
        .se_index            = 3,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_12_TX,
        .gpio_rx_config      = HSUART_12_RX,
        .gpio_cts_config     = HSUART_12_CTS,
        .gpio_rfr_config     = HSUART_12_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 3),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_13
hsuart_plat_device_config hsuart_device_config_13 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x00090000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 12,
        .se_index            = 4,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_13_TX,
        .gpio_rx_config      = HSUART_13_RX,
        .gpio_cts_config     = HSUART_13_CTS,
        .gpio_rfr_config     = HSUART_13_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 4),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_14
hsuart_plat_device_config hsuart_device_config_14 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x00094000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 13,
        .se_index            = 5,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_14_TX,
        .gpio_rx_config      = HSUART_14_RX,
        .gpio_cts_config     = HSUART_14_CTS,
        .gpio_rfr_config     = HSUART_14_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 5),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_15
hsuart_plat_device_config hsuart_device_config_15 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x00098000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 14,
        .se_index            = 6,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_15_TX,
        .gpio_rx_config      = HSUART_15_RX,
        .gpio_cts_config     = HSUART_15_CTS,
        .gpio_rfr_config     = HSUART_15_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 6),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#ifdef BOOT_USE_HSUART_16
hsuart_plat_device_config hsuart_device_config_16 =
    {
        .uart_base           = (QUPV3_1_CORE_BASE_ADDRESS + 0x0009C000),
        .qup_common_base     = QUPV3_1_CORE_COMMON_BASE_ADDRESS,
        .core_index          = 15,
        .se_index            = 7,
        .qupv3_protocol      = UART_2W_PROTOCOL,
        .gpio_tx_config      = HSUART_16_TX,
        .gpio_rx_config      = HSUART_16_RX,
        .gpio_cts_config     = HSUART_16_CTS,
        .gpio_rfr_config     = HSUART_16_RFR,
        .clock_id_index      = 0,
        .common_clock_id     = (uint8 **)qup_common_clock_str_1,
        .core_clock_id       = (uint8 **)(qup_se_clock_str_1 + 7),
        .base_freq           = 4000000,
        .irq_num             = 0,
        .tcsr_base           = 0,
        .tcsr_offset         = 0,
        .tcsr_value          = 0,
    };
#endif

#endif /*__HSUART_DEVCFG_H__*/
