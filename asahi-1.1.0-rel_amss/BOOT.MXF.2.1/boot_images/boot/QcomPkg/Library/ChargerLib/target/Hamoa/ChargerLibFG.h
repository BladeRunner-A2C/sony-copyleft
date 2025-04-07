/**
@file  ChargerLibFG.c
@brief Implementation of ChargerLib API for FG module
*/
/*=============================================================================
Copyright (c) 2018 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
04/24/20   ravi    Added permanent failure status APIs
09/27/18   ivy     support fg ship mode
09/24/18   cs      enable soc threshold and loading FW by default
06/28/18   cs      fixed i2c open failure.
06/21/18   cs      Initial Release
=============================================================================*/
#ifndef __CHARGERLIB_FG_H__
#define __CHARGERLIB_FG_H__

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>
/**
  Library Dependencies
*/
#include "i2c_api.h"
#include <Library/UefiBootServicesTableLib.h>

/*===========================================================================*/
/*                  TYPEDEF AND MACRO DEFINITIONS                            */
/*===========================================================================*/
#define MANUFACTURER_NAME_MAX_SIZE  20

typedef VOID *SmartChargerFG_HandleType;

// I2C Slave Context for FG Device
typedef struct
{
  SmartChargerFG_HandleType hI2CFGHandle;           /**< I2C handle for slave addresses */
  i2c_instance              I2CFGInstance;          /**< I2C core Number */
  i2c_slave_config          I2CFGCfg;               /**< I2C configuration */
  UINT32                    TimeoutMs;              /**< Timeout in milisecond - in case required */
} SmartChargerFG_SlaveType;


typedef struct _FG_BATT_STATUS_DATA
{
    BOOLEAN bDischarging;       // 0 = CHARGE mode. 1 = DISCHARGE or RELAX mode.
    BOOLEAN bFullCharge;        // 0 = not fully charged. 1 = fully charged when GaugingStatus()[FC]=1
}FG_BATT_STATUS_DATA, *PFG_BATT_STATUS_DATA;

typedef struct
{
  UINT32 StateOfCharge;
  INT32  ChargeCurrent;
  INT32  BatteryVoltage;
  INT32  BatteryTemperature;
  FG_BATT_STATUS_DATA BatteryChargeStatus;
}SmartChargerFG_BattStatusInfo;

//FG HW information
typedef struct _FG_PORTHW_HW_INFO
{
    UINT32  Index;
    UINT32  Address;
} FG_PORTHW_HW_INFO;

typedef enum
{
    FG_TYPE_BQ,
    FG_TYPE_VIRTUAL,
    FG_TYPE_INVALID,
}FG_TYPE;
/*===========================================================================*/
/*                  FUNCTION PROTOTYPES                                      */
/*===========================================================================*/
/**
  Initialize the interface to FG module

  @param None

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
SmartChargerLibFG_Init(void);

/**
  De-initialize the interface to FG module

  @param None

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
SmartChargerLibFG_Deinit(void);



/**
  Get Battery Status from FG Module

  @param[IN]    HwInfo          Hardware Information for this request
  @param[OUT]   BatteryStatus   Return the battery status

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS
SmartChargerLibFG_GetBatteryStatus(
  SmartChargerFG_BattStatusInfo *pBatteryStatus);


EFI_STATUS SmartChargerLibFG_GetManufactureName(UINT8 *manufacture_name, size_t size);

EFI_STATUS SmartChargerLibFG_GetChargingCurrentVoltage(UINT16* charging_current, UINT16* charging_voltage);
/**
  Enable FG ship mode

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS SmartChargerLibFG_SetShipMode(void);

/**
  Get battery PF Active

  @param[OUT]   bPFActive        Return the battery Permanent Failure Active status

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS SmartChargerLibFG_GetBatteryPFActive(BOOLEAN *bPFActive);

/**
  Get battery pack permanent failure status

  @param[OUT]   PfStatus        Return the battery permanent failure status

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS SmartChargerLibFG_GetBatteryPFStatus(UINT32 *pPFStatus);

/**
  Get battery pack FG type

  @return fg type
*/
FG_TYPE SmartChargerLibFG_GetFGType(void);


/**
  Get battery present status

  @param[OUT]   present        Return battery present status

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS SmartChargerLibFG_GetBatteryPresent(BOOLEAN* present);

/**
 * I2C Read/Write Interface for FG Module
 */
EFI_STATUS fg_i2c_read(UINT8 offset, UINT8 *data_out, UINT16 size_out);

EFI_STATUS fg_i2c_write(UINT8 offset, UINT8* data_in, UINT16 size_in);

#endif  /* __CHARGERLIB_FG_H__ */
