#ifndef __OEMINFO_H__
#define __OEMINFO_H__

/**
 *   @file OEMInfo.h
 *   @brief Public interface include file for accessing the OEMInfo driver.
 **/

/*=============================================================================
 *   Copyright (c) 2022, 2024 Qualcomm Technologies, Inc. All rights reserved.
 *   Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*=========================================================================
 *   Include Files
=========================================================================*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "OEMInfoDefs.h"

/*=========================================================================
 *   Type Definitions
=========================================================================*/

/*=========================================================================
 *   Function Definitions
=========================================================================*/
/**
 * OEMInfo_GetVariant - return OEM variant number
 *
 * @param N/A
 *
 * Note: This public-facing API will provide the value if already initialized,
 *          otherwise, it will call internal functions to create the local
 *          context and populate its values
 *
 * @returns OEM variant number based on hardware signals
 */
uint32_t OEMInfo_GetVariant(void);

#endif
