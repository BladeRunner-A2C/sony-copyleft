#ifndef __PRNGML_H__
#define __PRNGML_H__
/*===========================================================================

                       P R N G E n g i n e D r i v e r

                       H e a d e r  F i l e (e x t e r n a l)

DESCRIPTION
  This header file contains HW Crypto specific declarations.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright (c) 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

#include <com_dtypes.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

typedef enum
{
    PRNGML_ERROR_NONE,
    PRNGML_ERROR_BUSY,
    PRNGML_ERROR_FAILED,
    PRNGML_ERROR_INVALID_PARAM,
    PRNGML_ERROR_UNSUPPORTED,
    PRNGML_ERROR_BAD_STATE
} PrngML_Result_Type;

#endif /*__PRNGML_H__*/
