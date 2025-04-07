/**
 *   @file OEMInfo.c
 *
 *   Interface implementation file for the OEMInfo driver.
 **/

/*
 *====================================================================
 *
 *     Copyright (c) 2022 Qualcomm Technologies, Incorporated.  All Rights Reserved.
 *       QUALCOMM Proprietary and Confidential.
 *
 *====================================================================
 *
 *
 *====================================================================
 */


/*=========================================================================
 *   Include Files
==========================================================================*/
#include "OEMInfo.h"
#include "OEMInfoDefs.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*========================================================================
 *   Global Data
=========================================================================*/

/* =============================================================================
 *  Function : OEMInfo_GetVarNum
 * ===========================================================================*/
/**
 * @brief       Getter function to retrieve OEM variant value.
 *
 * @param[in]   N/A
 * @return      Value of the unique OEM variant
 */
uint32_t
OEMInfo_GetVariant(void)
{
    return 0;
}
