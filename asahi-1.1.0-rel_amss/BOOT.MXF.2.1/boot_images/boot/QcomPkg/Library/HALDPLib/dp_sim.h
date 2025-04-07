#ifndef __DP_SIM__
#define __DP_SIM__
/*=============================================================================

  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

=============================================================================*/

/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------------------------------------
 * Defines
 *---------------------------------------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------------------------------------
 * Enumerated types
 *---------------------------------------------------------------------------------------------------------------------*/

/* Simulation Device ID types */
typedef enum
{
    SIM_DEVICE_ID_NONE = 0x00000000,
    SIM_DEVICE_ID_ALT_MODE_0,                                             /**< DP over Type-C Port 0 */
    SIM_DEVICE_ID_ALT_MODE_1,                                             /**< DP over Type-C Port 1 */
    SIM_DEVICE_ID_ALT_MODE_2,                                             /**< DP over Type-C Port 2 */
    SIM_DEVICE_ID_EDP,                                                    /**< EDP Port              */
    SIM_DEVICE_MAX,
    SIM_DEVICE_FORCE_32BIT = 0x7FFFFFFF
} SIM_DeviceIDType;

/* Aux Transaction mode types */
typedef enum
{
    DP_SIM_TRANSACTION_MODE_NONE = 0x00000000,
    DP_SIM_TRANSACTION_MODE_AUX,                                             /**< This is an native AUX Transaction       */
    DP_SIM_TRANSACTION_MODE_I2C,                                             /**< This is an I2C over AUX Transaction     */
    DP_SIM_TRANSACTION_MODE_MAX,
    DP_SIM_TRANSACTION_MODE_FORCE_32BIT = 0x7FFFFFFF
} eModeType;

/* Simulated section types */
typedef enum
{
  SIM_SECTION_EDID = 0,       /**< EDID section */
  SIM_SECTION_DPCD_CAPS,      /**< DPCD caps section */
  SIM_SECTION_DPCD_STATUS,    /**< DPCD link status section */
  SIM_SECTION_EXT_DPCD_CAPS,  /**< Extended DPCD caps section */
  SIM_SECTION_MAX,
  SIM_SECTION_FORCE_32BIT = 0x7FFFFFFF,
} SIM_SectionType;

/* --------------------------------------------------------------------------------------------------------------------
 * Public Functions
 *---------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------
//
//  FUNCTION: SIM_LoadSection
//
//  @brief
//    Manually overwrite SIM section to be simulated.
//
//  @params
//   [IN] eSinkIDType
//      Sink divice ID.
//   [IN] eSectionType
//      SIM section to overwrite.
//   [IN] pBuffer
//      Buffer to overwrite section with.
//   [IN] uBufferSize
//      Size of buffer in bytes.
//  @return
//    TRUE or FALSE if section overwritten succesfully.
//
// ----------------------------------------------------------------------------------------------------
//
bool32 SIM_LoadSection(SIM_DeviceIDType eSinkIDType,
                       SIM_SectionType  eSectionType,
                       uint8           *pBuffer,
                       uint32           uBufferSize);

//----------------------------------------------------------------------------------------------------
//
//  FUNCTION: SIM_LoadConfigFile
//
//  @brief
//    Configure DP Sim data 
//
//  @params
//   [IN] eSinkIDType 
//       Sink divice Id
//  @return
//    TRUE or FALSE if config written succesfully.
//
// ----------------------------------------------------------------------------------------------------
//
bool32 SIM_LoadConfigFile(SIM_DeviceIDType eSinkIDType);

//----------------------------------------------------------------------------------------------------
//
//  FUNCTION: DP_SimulationAuxRead
//
//  @brief
//    DP SIM function to read AUX CH from memory
//
//  @params
//   [IN] eSinkIDType 
//       Display Id
//   [IN] uAddr 
//       Address to read from
//   [IN] uLen 
//       Length of data to be read
//   [IN] pMessage 
//       Data buffer
//   [IN] eMode
//      Transaction mode
//  @return
//    Number of bytes read
//
// ----------------------------------------------------------------------------------------------------
//
uint32 DP_SimulationAuxRead(SIM_DeviceIDType eSinkIDType,
                            uint32           uAddr,
                            uint32           uLen,
                            uint8           *pMessage,
                            eModeType        eMode);

//----------------------------------------------------------------------------------------------------
//
//  FUNCTION: DP_SimulationAuxWrite
//
//  @brief
//    DP SIM function to write to AUX CH to memory
//
//  @params
//   [IN] eSinkIDType 
//       Display Id
//   [IN] uAddr 
//       Address to write to
//   [IN] uLen 
//       Length of data to write
//   [IN] pMessage 
//       Data buffer
//   [IN] eMode
//      Transaction mode
//  @return
//    Number of byte written
//
// ----------------------------------------------------------------------------------------------------
//
uint32 DP_SimulationAuxWrite(SIM_DeviceIDType eSinkIDType,
                             uint32           uAddr,
                             uint32           uLen,
                             uint8           *uData,
                             eModeType        eMode);
#endif // __DP_SIM__