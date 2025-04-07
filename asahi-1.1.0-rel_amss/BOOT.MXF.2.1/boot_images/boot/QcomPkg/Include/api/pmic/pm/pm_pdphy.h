#ifndef __PM_PDPHY_H__
#define __PM_PDPHY_H__

/*! \file
*  \n
*  \brief  pm_schg_typec.h PMIC-SCHG MODULE RELATED DECLARATION 
*  \details  This header file contains functions and variable declarations 
*  to support Qualcomm PMIC PDPHY module.
*  \n &copy; Copyright 2017-2023 QUALCOMM Technologies Inc, All Rights Reserved
*/

#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"


/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

/////////////////////////////////////////////////////////////////
// PmPdPhy_GetRxMessage -
//      Retreive PDPHY RX Message
//
typedef struct _PM_PDPHY_RX_MESSAGE_TYPE
{
    UINT8 RxSize;
    UINT8 RxFrameType;
    UINT8* pHeader;
    UINT8* pDataObjects;
} PM_PDPHY_RX_MESSAGE_TYPE, *PPM_PDPHY_RX_MESSAGE_TYPE;

/////////////////////////////////////////////////////////////////
// PmPdPhy_SetTxMessage -
//      Configure PDPHY TX Message
//
typedef struct _PM_PDPHY_TX_MESSAGE_TYPE
{
    UINT8 TxSize;
    UINT8 TxFrameType;
    UINT8 TxRetryCount;
    UINT8* pHeader;
    UINT8* pDataObjects;
    BOOLEAN SendMessage;
} PM_PDPHY_TX_MESSAGE_TYPE, *PPM_PDPHY_TX_MESSAGE_TYPE;

typedef struct _PM_PDPHY_MESSAGE_HEADER_TYPE
{
    BOOLEAN DataRole;
    BOOLEAN PowerRole;
    UINT8 PdSpecRev;
} PM_PDPHY_MESSAGE_HEADER_TYPE, *PPM_PDPHY_MESSAGE_HEADER_TYPE;

/*===========================================================================

                 SCHG DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
* @brief This function returns the USB type-C status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* @param[in]   pmic_index:    The pmic_index of charger module.
* @param[in]   enable:  FALSE = Disable PD PHY
*                        TRUE = Enable PD PHY
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG__SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_pdphy_set_enable_control(uint32 bus_id, uint32 pmic_index, boolean enable);

/**
* @brief This function returns the USB type-C status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* @param[in]   pmic_index:      The pmic_index of charger module.
* @param[in]   message_header:  Contains information regarding datarole, powerrole, pdspec
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS                = SUCCESS.
*
*/
pm_err_flag_type pm_pdphy_set_message_header(uint32 bus_id, uint32 pmic_index, PM_PDPHY_MESSAGE_HEADER_TYPE message_header);

/**
* @brief This function returns the USB type-C status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* @param[in]   pmic_index:    The pmic_index of charger module.
* @param[in]   frame_filter:  frame filter used for masking / writing RX message
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS                = SUCCESS.
*
*/
pm_err_flag_type pm_pdphy_set_frame_filter(uint32 bus_id, uint32 pmic_index, UINT8 frame_filter);

/**
* @brief This function returns the USB type-C status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* @param[in]   pmic_index:    The pmic_index of charger module.
* @param[in]   rx_token:      token that sets/indicates the ownership of the RXBuffer
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS                = SUCCESS.
*
*/
pm_err_flag_type pm_pdphy_set_rx_token(uint32 bus_id, uint32 pmic_index, BOOLEAN rx_token);

/**
* @brief This function returns the USB type-C status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* @param[in]   pmic_index:    The pmic_index of charger module.
* @param[in]   rx_message:    message that should be read from the buffer
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS                = SUCCESS.
*
*/
pm_err_flag_type pm_pdphy_get_rx_message(uint32 bus_id, uint32 pmic_index, PPM_PDPHY_RX_MESSAGE_TYPE rx_message);

/**
* @brief This function returns the USB type-C status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* @param[in]   pmic_index:    The pmic_index of charger module.
* @param[in]   tx_message:    message that should be written to the buffer
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS                = SUCCESS.
*
*/
pm_err_flag_type pm_pdphy_set_tx_message(uint32 bus_id, uint32 pmic_index, PPM_PDPHY_TX_MESSAGE_TYPE tx_message);

/**
* @brief This function returns the USB type-C status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* @param[in]   pmic_index:    The pmic_index of charger module.
* @param[in]   rx_message:    message that should be read from the buffer
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG__FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS                = SUCCESS.
*
*/
pm_err_flag_type pm_pdphy_get_rx_token(uint32 bus_id, uint32 pmic_index, UINT8* rx_token);

#endif // __PM_PDPHY_H__