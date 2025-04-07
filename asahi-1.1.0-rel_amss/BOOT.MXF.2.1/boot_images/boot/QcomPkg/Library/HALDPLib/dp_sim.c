/*=============================================================================

  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

=============================================================================*/

/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "stdlib.h"
#include "dp_i.h"
#include "dp_sim.h"


 /* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/

#ifdef DPDRIVER_EDP_MODE
  #define SIM_DPCD_SIZE                                    1
  #define SIM_EDPCD_SIZE                                   1
  #define SIM_EDID_SIZE                                    1   
#else
  #define SIM_DPCD_SIZE                                    0x800
  #define SIM_EDPCD_SIZE                                   ((SIM_EDPCD_END)-(SIM_EDPCD_START))
  #define SIM_EDID_SIZE                                    1024 // 4 Blocks
#endif 
#define SIM_EDPCD_START                                    0x2200
#define SIM_EDPCD_END                                      0x2300
#define SIM_EDID_START_ADDRESS                             0x50
#define SIM_EDID_SEGMENT_ADDRESS                           0x30
#define SIM_DPCD_CAPS_SIZE                                 0x100
#define SIM_DPCD_STATUS_SIZE                               0x100
#define SIM_DPCD_STATUS_START_ADDRESS                      0x200
#define PATH_LINE_LENGTH                                   128+3 // Line length + carriage return and null termination
#define SIM_MAX_AUX_READ_LENGTH                            16

// Gets Sink context depending on display id to simulate
#define SIM_GET_SINK_CTX_FROM_ID(_sinkId_) (&(gSimData.sSinkCtx[((_sinkId_)<SIM_DEVICE_MAX)?(_sinkId_):SIM_DEVICE_ID_ALT_MODE_0]))

 //-------------------------------------------------------------------------------------------------
 //  SIM_DPCDCtxType
 //
 //  @brief
 //     SIM_DPCDCtxType defines the mapping for DPCD register address
 //
 //-------------------------------------------------------------------------------------------------
 //
typedef struct
{
    uint8                             uDpcd[SIM_DPCD_SIZE];
    uint8                             uExtDpcd[SIM_EDPCD_SIZE];
}SIM_DPCDCtxType;

 //-------------------------------------------------------------------------------------------------
 //  SIM_ParamCtxType
 //
 //  @brief
 //     SIM_ParamCtxType defines the parameter for DP Simulation
 //
 //-------------------------------------------------------------------------------------------------
 //
typedef struct
{
    uint32                            uDelay;
    bool32                            bLinkTraining;
}SIM_ParamCtxType;

//-------------------------------------------------------------------------------------------------
//  SIM_EDIDCtxType
//
//  @brief
//     SIM_EDIDCtxType defines the mapping for EDID register address.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
    uint8                             uEdid[SIM_EDID_SIZE];
    uint32                            uSegNum;
    uint32                            uOffset;
}SIM_EDIDCtxType;

//-------------------------------------------------------------------------------------------------
//  SIM_SinkCtxType
//
//  @brief
//      Present Sink context for DP Simulation.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
    SIM_ParamCtxType                  sParamCtx;
    SIM_DPCDCtxType                   sDPCDCtx;
    SIM_EDIDCtxType                   sEDIDCtx;
}SIM_SinkCtxType;

//-------------------------------------------------------------------------------------------------
//  SIM_SinkDataType
//
//  @brief
//      Present Sink data for DP Simulation.
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
    SIM_SinkCtxType                   sSinkCtx[SIM_DEVICE_MAX];
}SIM_SinkDataType;

/*---------------------------------------------------------------------------------------------------------------------
 * Global Data Definitions
 *-------------------------------------------------------------------------------------------------------------------*/
static SIM_SinkDataType gSimData;

/*------------------------------------------------------------------------------------------
 * Public Functions
 *------------------------------------------------------------------------------------------*/
 /*********************************************************************************************
 *
 ** FUNCTION: SIM_LoadConfigFile()
 */
 /*!
 * \DESCRIPTION
 *     Configure Sim for selected display from file at C:\Data\Test\dpsimconfig.ini
 *
 * \param [in]   eSinkIDType
 *
 * \retval bStatus
 *
 **********************************************************************************************/
bool32 SIM_LoadConfigFile(SIM_DeviceIDType eSinkIDType)
{
    return TRUE;
}

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
                       uint32           uBufferSize)

{
  bool32 bRetStatus = TRUE;

  if ((eSinkIDType > SIM_DEVICE_MAX) ||
      (NULL == pBuffer))
  {
    bRetStatus = FALSE;
    TraceInfo(QdiTraceDP, "SIM_LoadSection: Invalid Parameter");
  }
  else
  {
    SIM_SinkCtxType *pSinkCtx = SIM_GET_SINK_CTX_FROM_ID(eSinkIDType);

    switch (eSectionType)
    {
      case SIM_SECTION_DPCD_CAPS:
      { 
        if((uBufferSize <= SIM_DPCD_SIZE) &&
           (SIM_DPCD_CAPS_SIZE <= SIM_DPCD_SIZE))
        {
          DISP_OSAL_MemZero(pSinkCtx->sDPCDCtx.uDpcd, SIM_DPCD_CAPS_SIZE);
          DISP_OSAL_MemCpyEx(pSinkCtx->sDPCDCtx.uDpcd, SIM_DPCD_CAPS_SIZE, pBuffer, uBufferSize);
        }
        else
        {
          bRetStatus = FALSE;
        }
        break;
      }
      case SIM_SECTION_DPCD_STATUS:
      {
        if(((uBufferSize + SIM_DPCD_STATUS_START_ADDRESS) <= SIM_DPCD_SIZE)           && 
           (uBufferSize <= SIM_DPCD_STATUS_SIZE)                                      && 
           ((SIM_DPCD_STATUS_START_ADDRESS + SIM_DPCD_STATUS_SIZE) <= SIM_DPCD_SIZE ))
        {
          DISP_OSAL_MemZero(&pSinkCtx->sDPCDCtx.uDpcd[SIM_DPCD_STATUS_START_ADDRESS], SIM_DPCD_STATUS_SIZE);
          DISP_OSAL_MemCpyEx(&pSinkCtx->sDPCDCtx.uDpcd[SIM_DPCD_STATUS_START_ADDRESS],
                             SIM_DPCD_STATUS_SIZE,
                             pBuffer,
                             uBufferSize);
        }
        else
        {
          bRetStatus = FALSE;
        }
        break;
      }
      case SIM_SECTION_EXT_DPCD_CAPS:
      {
        if(uBufferSize <= SIM_EDPCD_SIZE)
        {        
          DISP_OSAL_MemZero(&pSinkCtx->sDPCDCtx.uExtDpcd, SIM_EDPCD_SIZE);
          DISP_OSAL_MemCpyEx(pSinkCtx->sDPCDCtx.uExtDpcd, SIM_EDPCD_SIZE, pBuffer, uBufferSize);
        }
        else
        {
          bRetStatus = FALSE;
        }
        break;
      }
      case SIM_SECTION_EDID:
      {
        if(uBufferSize <= SIM_EDID_SIZE)
        {
          DISP_OSAL_MemZero(&pSinkCtx->sEDIDCtx, sizeof(SIM_EDIDCtxType));
          DISP_OSAL_MemCpyEx(pSinkCtx->sEDIDCtx.uEdid, SIM_EDID_SIZE, pBuffer, uBufferSize);
        }
        else
        {
          bRetStatus = FALSE;
        }
        break;
      }
      default:
      {
        TraceInfo(QdiTraceDP, "SIM_LoadSection: Invalid section type");
        bRetStatus = FALSE;
      }
    }
  }

  return bRetStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_SimulationAuxRead()
*/
/*!
* \DESCRIPTION
*     AUX/I2C read from memory instead of PHY for simulation mode 
*
* \param [in]   eSinkIDType 
                    - External sink ID to simulate
*               uAddr
                    - Register address to read from
*               uLen
                    - Number of bytes to read
*               pMessage
                    - Buffer message
                eMode
                    - Transaction mode (AUX or I2C)
*
* \retval       uint32
                     - # of bytes read
*
**********************************************************************************************/
uint32 DP_SimulationAuxRead(SIM_DeviceIDType eSinkIDType,
                            uint32           uAddr,
                            uint32           uLen,
                            uint8           *pMessage, 
                            eModeType        eMode)
{
    SIM_SinkCtxType *pSinkCtx   = SIM_GET_SINK_CTX_FROM_ID(eSinkIDType);
    uint32           uBytesRead = 0;
    uint32           uBaseIdx;

    if ((NULL == pMessage) ||
        (0 == uLen)) 
    {
        TraceInfo(QdiTraceDP, "DP_SimulationAuxRead: Invalid input parameter");
    }
    else
    {
        if (uLen > SIM_MAX_AUX_READ_LENGTH)
        {
            //The max amount of data transported over the AUX per transaction is limited to 16 bytes
            TraceInfo(QdiTraceDP, "DP_SimulationAuxRead: Warning, reading more than 16 bytes, not allowed in DP Standard");
        }
        if (eMode == DP_SIM_TRANSACTION_MODE_AUX)
        {
            // Reading of DPCD register address between 0x0 and 0x800: Standard DPCD fields 
            if ((uAddr + uLen) < SIM_DPCD_SIZE)
            {
                for (uint32 i = 0; i < uLen; i++)
                {
                    pMessage[i] = pSinkCtx->sDPCDCtx.uDpcd[uAddr + i];
                    uBytesRead++;
                }
            }
            // Reading of DPCD register address between 0x2200 and 0x2300: Extended Receiver Capability
            else if ((SIM_EDPCD_START <= uAddr) &&
                     (uAddr < SIM_EDPCD_END)    &&
                     ((uAddr + uLen) < SIM_EDPCD_END))
            {
                uBaseIdx = uAddr - SIM_EDPCD_START;

                for (uint32 i = 0; i < uLen; i++)
                {
                    pMessage[i] = pSinkCtx->sDPCDCtx.uExtDpcd[uBaseIdx + i];
                }
            }
            else
            {
                TraceInfo(QdiTraceDP, "DP_SimulationAuxRead:  Invalid address = %i", uAddr);
            }
        }
        else if (eMode == DP_SIM_TRANSACTION_MODE_I2C)
        {
            // Reading of EDID Registers
            if (uAddr >= SIM_EDID_START_ADDRESS)
            {
                // Calculate mapping of EDID address to array, with address 0x50 being the first index of array 
                uBaseIdx = (uAddr - SIM_EDID_START_ADDRESS) + pSinkCtx->sEDIDCtx.uOffset + (pSinkCtx->sEDIDCtx.uSegNum * 0x100);
                
                if ((uBaseIdx + uLen) < SIM_EDID_SIZE)
                {
                    for (uint32 i = 0; i < uLen; i++)
                    {
                        pMessage[i] = pSinkCtx->sEDIDCtx.uEdid[i + uBaseIdx];
                        uBytesRead++;
                    }
                }
            }
            else
            {
                TraceInfo(QdiTraceDP, "DP_SimulationAuxRead: Invalid EDID address");
            }
        }
        else
        {
            TraceInfo(QdiTraceDP, "DP_SimulationAuxRead: Invalid transaction mode");
        }
    }
    // Simulating timing configuration of a real physical monitor
    DP_OSAL_StallUs(pSinkCtx->sParamCtx.uDelay);

    return uBytesRead;
}
/*********************************************************************************************
*
** FUNCTION: DP_SimulationAuxWrite()
*/
/*!
* \DESCRIPTION
*    AUX/I2C write to memory instead of PHY for simulation mode 

* \param [in]   eSinkIDType
                    - External sink ID to simulate
*               uAddr
                    - Register address to write to
*               uLen
                    - Number of bytes to write
*               pMessage
                    - Data buffer
                eMode
                    - Transaction mode (AUX or I2C)
*
* \retval       uint32
                     - # of bytes read
*
**********************************************************************************************/
uint32 DP_SimulationAuxWrite(SIM_DeviceIDType eSinkIDType,
                             uint32           uAddr,
                             uint32           uLen, 
                             uint8           *pData, 
                             eModeType        eMode)
{
    SIM_SinkCtxType *pSinkCtx    = SIM_GET_SINK_CTX_FROM_ID(eSinkIDType);
    uint32           uBytesWrite = 0;

    if ((NULL == pData) ||
        (0 == uLen))
    {   
        TraceInfo(QdiTraceDP, "DP_SimulationAuxWrite: Invalid input parameter");
    }
    else
    {
        if (eMode == DP_SIM_TRANSACTION_MODE_AUX)
        {
            // Writing to DPCD register address between 0x0 and 0x800: Standard DPCD fields 
            if ((uAddr + uLen) < SIM_DPCD_SIZE)
            {
                for (uint32 i = 0; i < uLen; i++)
                {
                    pSinkCtx->sDPCDCtx.uDpcd[uAddr + i] = *pData;
                }
            }
            // Writing to DPCD register address between 0x2200 and 0x2300: Extended Receiver Capability
            else if ((SIM_EDPCD_START <= uAddr) &&
                    (uAddr < SIM_EDPCD_END) &&
                    ((uAddr + uLen) < SIM_EDPCD_END))
            {
                uint32 uBaseIdx = uAddr - SIM_EDPCD_START;

                for (uint32 i = 0; i < uLen; i++)
                {
                    pSinkCtx->sDPCDCtx.uExtDpcd[uBaseIdx + i] = *pData;
                }
            }
            else
            {
                TraceInfo(QdiTraceDP, "DP_SimulationAuxWrite: Invalid address = %i", uAddr);
            }
        }
        else if (eMode == DP_SIM_TRANSACTION_MODE_I2C)
        {
            // Writing to EDID register to request for block of I2C EDID data
            if (uAddr == SIM_EDID_START_ADDRESS)
            {
                pSinkCtx->sEDIDCtx.uOffset = *pData;
            }
            else if (uAddr == SIM_EDID_SEGMENT_ADDRESS)
            {
                pSinkCtx->sEDIDCtx.uSegNum = *pData;
            }
            else 
            {
                TraceInfo(QdiTraceDP, "DP_SimulationAuxWrite: Invalid address = %i", uAddr);
            }
        }
        else
        {
            TraceInfo(QdiTraceDP, "DP_SimulationAuxWrite: Invalid transaction mode");
        }
    }
    // Simulating timing configuration of a real physical monitor
    DP_OSAL_StallUs(pSinkCtx->sParamCtx.uDelay);

    return uBytesWrite;
}