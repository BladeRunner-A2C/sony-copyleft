#ifndef __OEMINFODEFS_H__
#define __OEMINFODEFS_H__

/**
 *   @file OEMInfo.h
 *   @brief Public interface include file for accessing the OEMInfo driver.
 **/

/*=============================================================================
 *   Copyright (c) 2022 Qualcomm Technologies, Incorporated.
 *   All rights reserved.
 *   Qualcomm Confidential and Proprietary
=============================================================================*/

/*=========================================================================
 *   Include Files
=========================================================================*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*=========================================================================
 *   Type Definitions
=========================================================================*/
/**
 * Return values of internal OEM functions
 */
typedef enum
{
    OEMINFO_SUCCESS             = 0,    /**< Success or already initialized     */
    OEMINFO_FAILURE             = -1,   /**< Failure to initilize OEMInfo       */
    OEMINFO_DTB_FAILURE         = -2,   /**< DTB function failure               */
    OEMINFO_READ_FAILURE        = -3,   /**< IO device read failure             */
    OEMINFO_ATTACH_FAILURE      = -4,   /**< IO device attach/enable failure    */
    OEMINFO_SETVAR_FAILURE      = -5,   /**< Failure to set OEM variant value   */
    OEMINFO_SUCCESS_NO_DT        = 1
} OEMInfoResult;
 
#endif
