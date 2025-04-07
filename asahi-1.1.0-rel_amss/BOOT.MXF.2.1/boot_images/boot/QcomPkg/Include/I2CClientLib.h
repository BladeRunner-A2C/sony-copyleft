#ifndef __I2CCLIENT_DT_H__
#define __I2CCLIENT_DT_H__

/*
===========================================================================
*/
/**
  @file  I2cClient_DT.h
  @brief I2C Client device tree parser header file
*/
/*  
  ====================================================================
  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  ==================================================================== 
  
  ====================================================================
*/

/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 10/15/22  rgotur   Adding I2C Client Library for I2C keyboard and Trackpad Inbox support and Device tree integration
=============================================================================*/

/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>

/*=========================================================================
      Macro Definitions
==========================================================================*/
#define HID_DESC_SIZE 2

/*=========================================================================
      Type Definitions
==========================================================================*/

 /**
   Slave configuration parameters that the client uses to communicate to a slave.
 */
 typedef struct
 {
    UINT32      BusFrequencyKhz;          /**< Bus speed in kHz. */
    UINT32      SlaveAddress;             /**< 7-bit I2C slave address. 7-bit I3C dynamic address */
    UINT32      I2cMode;                  /**< Protocol mode. Refer #i2c_mode */
    UINT32      SlaveMaxClockStretchUs;   /**< Maximum time in microseconds that an I2C slave may hold the SCL line low. Not applicable for I3C*/
    UINT32      CoreConfiguration1;       /**< Core Specific Configuration. Recommended 0. */
    UINT32      CoreConfiguration2;       /**< Core Specific Configuration. Recommended 0. */
 }I2C_SLAVE_CONFIG;

 typedef struct _GPIO_SETTINGS{
    UINT32 FunctionSelect;
    UINT32 Direction;
    UINT32 Pull;
    UINT32 DriveStrength;
    UINT32 GpioPin;
    UINT32 GpioVal;
    UINT32 Enable;
 }GPIO_SETTINGS;
 
 typedef struct _PMICGPIO_SETTINGS{
    UINT32 GpioConfigType;
    UINT32 Index;
    UINT32 Gpio;
    UINT32 OutBufCfgType;
    UINT32 VoltageSrcType;
    UINT32 SrcConfigType;
    UINT32 OutDriveStrength;
    UINT32 Pulltype;
    UINT32 Enable;
    UINT32 SetOutputLvl;
 }PMICGPIO_SETTINGS;

typedef struct _VREG_SETTINGS{
  UINT32 PmicDeviceIndex;
  UINT32 VoltageRegId;
  UINT32 Voltage;
  UINT32 Enable;
  UINT32 SwPowerMode;
} VREG_SETTINGS;
 
 typedef struct _CONFIG_POWERON
 {
    CHAR8 *NodeName;
    union{
        GPIO_SETTINGS TlmmGpio;
        PMICGPIO_SETTINGS PmicGpio;
        VREG_SETTINGS PmicVReg;
        UINT32 Delay;
    };
 }CONFIG_POWER;
 
 typedef struct _I2CCLIENT_DEVICE_INFO{
   UINT32  HidDesc[HID_DESC_SIZE];
   UINT32  TransferDelay;
   UINT32  I2cInstance;
   UINT32  I2cClientInt;
   CHAR8 *pmicResourceName;
   CHAR8 *pmicClientName;
   I2C_SLAVE_CONFIG  I2cSlaveConfig;
   CONFIG_POWER **PowerOnList;
   UINT8 PowerOnListLen;
   CONFIG_POWER **PowerOffList;
   UINT8 PowerOffListLen;
 } I2CCLIENT_DEVICE_INFO;
 
extern I2CCLIENT_DEVICE_INFO *I2cClientStruct;


/*=========================================================================
      Function Definitions
==========================================================================*/

/**
  Init I2C client device tree structure.

  @param  I2cClientNodeName       The I2C client device tree node name

  @retval I2CCLIENT_DEVICE_INFO   Pointer to I2CCLIENT_DEVICE_INFO structure if device tree it available
  @retval NULL                    If Fails to read device tree

**/
I2CCLIENT_DEVICE_INFO* I2CClientInitDT(char *I2cClientNodeName);

/**
  Sets De-Init I2C client DT strcuture.

  @param  I2cClientNodeName       The I2C_KB_DEV instance.

  @retval EFI_SUCCESS             If Deinit failure .
  @retval EFI_ERROR               If fails.
**/
EFI_STATUS I2CClientDeInitDT(I2CCLIENT_DEVICE_INFO* I2cKbDTNode);

EFI_STATUS I2CClientGetI2cInstance(char *I2cClientNodeName, i2c_instance *I2cInstance);

EFI_STATUS I2CClientGetSlaveCfg(char *I2cClientNodeName, i2c_slave_config *I2cSlavecfg);

EFI_STATUS I2CClientGetHidDescCfg(char *I2cClientNodeName, UINT8 *AddrHigh, UINT8 *AddrLow);

EFI_STATUS I2CClientGetGpioStatus(char *I2cClientNodeName, UINT32 *GpioIntValue);

EFI_STATUS I2CClientPowerOn(char *I2cClientNodeName);

EFI_STATUS I2CClientPowerOff(char *I2cClientNodeName);

EFI_STATUS I2CClientGetGpioCfg(char* I2cClientNodeName, GPIO_SETTINGS *clientgpiocfg);

EFI_STATUS I2CClientGetGpioInitInterval(char *I2cClientNodeName, UINT32 *GpioInitInterval);

EFI_STATUS I2CClientGetTimeoutValue(char *I2cClientNodeName, UINT32 *TimeoutValue);

#endif /* __I2CCLIENT_DT_H__ */