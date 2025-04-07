#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__


/*=============================================================================   
    @file  spi_config.h
    @brief interface to device configuration
   
    Copyright (c) 2019, 2021-2022 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/13/22   mp       updated the cfg_protocol
 03/25/22   bn       Updated polled_mode data type
 01/10/19    bng      created
=============================================================================*/


#include "spi_types.h"

#define MAX_SPI_FREQ_CNT 7
#define MAX_SPI_COMMON_CLK_CNT 4
#define MAX_QSPI_GPIO 6

typedef enum
{
   SPI_MODE_0,   /*CPOL = 0, CPHA = 0*/
   SPI_MODE_1,   /*CPOL = 0, CPHA = 1*/
   SPI_MODE_2,   /*CPOL = 1, CPHA = 0*/
   SPI_MODE_3,   /*CPOL = 1, CPHA = 1*/
}spi_mode_t;


typedef enum
{
   CS_ACTIVE_LOW,/**< During idle state CS  line is held low*/
   CS_ACTIVE_HIGH,/**< During idle state CS line is held high*/
   CS_ACTIVE_INVALID = 0x7FFFFFFF
}spi_cs_polarity_t;

/*Note - Endian ness - it is unclear  whether we can
 * support this in all (FIFO/GSI) modes !
 * Order in which bytes from tx/rx buffer words are put on the bus.
 */
typedef enum
{
    SPI_NATIVE = 0,
    SPI_LITTLE_ENDIAN = 0,
    SPI_BIG_ENDIAN /* network*/
}spi_byte_order_t;


/* SPI configuration passed to the spi_full_duplex() function. */
typedef struct
{
   spi_mode_t spi_mode;
   spi_cs_polarity_t spi_cs_polarity;
   spi_byte_order_t endianness;
   uint8 spi_bits_per_word;  /*4 <= N <= 32*/
   uint8 spi_slave_index;
   /**< Slave index, beginning at 0, if mulitple SPI devices are connected to the same master
   At most 7 slaves are allowed. If an invalid number (7 or higher) is set, CS
   signal will not be used*/
   uint32 clk_freq_hz;
   /**< Host will set the SPI clk frequency closest to the requested frequency */
   uint8 cs_clk_delay_cycles;
   /*Num of clk cycles to wait after asserting CS before starting txfer*/
   uint8 inter_word_delay_cycles;
   /*Num of clk cycles to wait between SPI words*/
   boolean cs_toggle;
   /*1 = CS deasserts between words
     0 = CS stays asserted between words.*/
   boolean loopback_mode;
   /**<Normally 0. If set, SPI controller will enable loopback mode, used primarily for testing */
} spi_config_t;

typedef struct
{
    uint8  *tx_buf;
    uint8  *rx_buf;
    uint32  tx_len;
    uint32  rx_len;
    boolean leave_cs_asserted;
}spi_descriptor_t;

typedef enum 
{
	SPI_PROTOCOL  = 1, //QUPv3 protocols as in FW register
	SPI_SLAVE_PROTOCOL  = 5,
	QSPI_HID_PROTOCOL = 8,
	QSPI_PROTOCOL = 9,

}cfg_protocol;

typedef enum
{
	SPI_SLAVE_STATE_NOT_READY = 0,
	SPI_SLAVE_STATE_READY  = 1,

}spi_slave_state;

typedef struct spi_plat_clock_config 
{
    //uint8   se_clock_dfs_index;
    uint32  se_clock_frequency_khz;
    uint32  bus_speed_khz;
    uint8   clk_div;

} spi_plat_clock_config;

/* The order of entries in this structure and DT file should be same else 
  there will be a compatibility mismatch */
typedef struct spi_plat_device_config
{
    uint8      *core_base_addr;
    uint8      *common_base_addr;
    uint32      core_offset;
    uint8       qupv3_instance;
    uint8       core_index;
	cfg_protocol qupv3_protocol;
    uint8       se_index;
    uint8       gpi_index;
    uint32      core_irq;
    uint8       polled_mode;
    uint32      min_data_length_for_dma;
    
    uint32      miso_encoding;
    uint32      mosi_encoding;
	uint32      cs_encoding;
	uint32      clk_encoding;
	
	uint32 		qspi_data_0;
	uint32 		qspi_data_1;
	
	uint32		sleep_miso_encoding;
    uint32      sleep_mosi_encoding;
    uint32      sleep_cs_encoding;
    uint32      sleep_clk_encoding;


    uint32      tcsr_reg_offset;
    uint8      *tcsr_base_addr;
    uint32      tcsr_reg_value;

    uint32      se_clock_frequency;
    uint8       se_clock_dfs_index;

    uint8     **common_clocks;
    uint8     **se_clock;

    spi_plat_clock_config   *clock_config;

} spi_plat_device_config;

#endif
