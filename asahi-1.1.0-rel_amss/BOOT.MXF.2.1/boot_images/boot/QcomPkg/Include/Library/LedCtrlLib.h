/*
* Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
*/
#ifndef LED_CTRL_LIB_H
#define LED_CTRL_LIB_H

/* port type values */
#define PORT_TP            0x00
#define PORT_AUI           0x01
#define PORT_MII           0x02
#define PORT_FIBRE         0x03
#define PORT_BNC           0x04
#define PORT_DA            0x05
#define PORT_NONE          0xef
#define PORT_OTHER         0xff

/* Enum to select trx port LED number */
typedef enum trx_port_type{
   TRX_PORT_LED1 = 0,
   TRX_PORT_LED2,
   TRX_PORT_LED1_2,
}trx_port_ledno_t;

/***************************************************************
*
* Function:       fpc_qsfp_configure
* Description:    Configures FPC402 resources.
* Usage        :  Should be called during the PHY bring up sequence.
*                 This configures the I2C instance-10 and programmes
*                 the FPC402 I2C address to 0x0c, Before invoking other
*                 transceiver functions, this must be called and successful.
*
* Return value:   0      : Success
*                -1      : Error due to an I2C instance open failure or 
*                          the FPC402 failing to configure its I2C address.
*
****************************************************************/
int fpc_qsfp_configure ();

/***************************************************************
*
* Function:       fpc_qsfp_deconfigure
* Description:    Deconfigures the FPC402 resources.
* Usage        :  Should be called during the PHY teardown
*                 sequence. It uninitializes the FPC402 resources.
* 
* Return value:   0      : Success
*                -1      : Error due to a failed FPC402 I2C init
*                          or an I2C handle that is NULL.
*
****************************************************************/
int fpc_qsfp_deconfigure ();

/***************************************************************
*
* Function:       trx_led_on
* Description:    Set the FPC402 port-0 LED on.
* Inputs:         led_num: Selects between LED1 and LED2, where TRX_PORT_LED1
*                          is to select LED1 and TRX_PORT_LED2 is LED2, and
*                          TRX_PORT_LED1_2 is to select both LED1 and LED2.
*
* Return value:   0      : Success
*                -1      : Error due to invalid input argument or FPC402 I2C was
*                          not initialized or I2C address was  not programed or
*                          transceiver module was not present or failure to read/write
*                          from FPC402 registers.
*
****************************************************************/
int trx_led_on (trx_port_ledno_t led_num);

/***************************************************************
*
* Function:       trx_led_off 
* Description:    Set the FPC402 port-0 LED to off if it is on or blinking.
* Inputs:         led_num: Selects between LED1 and LED2, where TRX_PORT_LED1
*                          is to select LED1 and TRX_PORT_LED2 is LED2, and
*                          TRX_PORT_LED1_2 is to select both LED1 and LED2.
*
* Return value:   0      : Success
*                -1      : Error due to invalid input argument or FPC402 I2C was
*                          not initialized or I2C address was  not programed or
*                          transceiver module was not present or failure to read/write
*                          from FPC402 registers.
*
****************************************************************/
int trx_led_off  (trx_port_ledno_t led_num);

/***************************************************************
*
* Function:       trx_led_blink_set
* Description:    Set FPC402 port-0 LED's in blink mode with default maximum
*                 intensity and  250msec of on and off time.
* Inputs:         led_num: Selects between LED1 and LED2, where TRX_PORT_LED1
*                          is to select LED1 and TRX_PORT_LED2 is LED2, and
*                          TRX_PORT_LED1_2 is to select both LED1 and LED2.
*
* Return value:   0      : Success
*                -1      : Error due to invalid input argument or FPC402 I2C was
*                          not initialized or I2C address was  not programed or
*                          transceiver module was not present or failure to read/write
*                          from FPC402 registers.
*
****************************************************************/
int trx_led_blink_set(trx_port_ledno_t led_num);

/***************************************************************
*
* Function:       trx_get_lane_type
* Description:    Function for determining the type of transceiver lane
*                 (DAC, OPTIC, OR OTHER).
* 
* Return value:   port-type    : If successful, the port type will be returned.
*                -1            : Error due to FPC402 I2C was not initialized or
*                                I2C address was  not programed or transceiver module
*                                was not present or failure to read connector type value
*                                from trx EEPROM 
*
****************************************************************/
int trx_get_lane_type();

/***************************************************************
*
* Function:       is_trx_module_present
* Description:    Function for determining the presence of transceiver
*                 on port 0.
* 
* Return value:   0     : Transceiver module present on port 0. 
*                 1     : Transceiver module not present on port 0.
*                -1     : Error due to FPC402 I2C was not initialized or
*                         I2C address was  not  programed or failure to
*                         read FPC402 IN_B status register.
*
****************************************************************/
int is_trx_module_present();
#endif
