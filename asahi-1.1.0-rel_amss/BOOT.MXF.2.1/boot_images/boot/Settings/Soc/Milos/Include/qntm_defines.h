#ifndef __QNTM_DEFINES_H__
#define __QNTM_DEFINES_H__


/*=============================================================================   
    @file  qntm_defines.h
    @brief interface to device configuration
   
    Copyright (c) by Qualcomm Technologies, Inc.  All Rights Reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 07/21/23   rd      Added new include file.
=============================================================================*/

#define IORT_INPUT_BASE(n)	( (IORT_WORLD_ID_NON_SECURE << IORT_WORLD_ID_SHIFT) \
                            | (IORT_DYNAMIC_MAPPING_NO << IORT_DYNAMIC_MAPPING_SHIFT) \
                            | (IORT_TRANSLATION_TYPE_NESTED << IORT_TRANSLATION_TYPE_SHIFT) \
                            | (n) )

#define LPASS_INPUT_BASE_MILOS      IORT_INPUT_BASE(2)
#define COMPUTE_INPUT_BASE_MILOS    IORT_INPUT_BASE(1)

#endif
