/*============================================================================

 FILE:      ChipInfoNullLib.c

 DESCRIPTION:
 This file is NULL implementation for the Chip Info APIs common to both XBL Loader and Core

 PUBLIC CLASSES:
 ChipInfo_GetRawDeviceFamily
 ChipInfo_GetRawDeviceNumber

 ============================================================================
 Copyright (c) 2016-2017, 2019, 2022, 2023 Qualcomm Technologies, Inc.
 All Rights Reserved.
 QUALCOMM Proprietary/GTDR
 ============================================================================

 $Header: //components/dev/core.boot/6.1/sairajma.core.boot.6.1.Chip_info_enhanced/QcomPkg/Library/ChipInfoLib/ChipInfo.c#1 $
 $DateTime: 2023/04/14 12:36:15 $
 $Author: sairajma $

==========================================================================*/

/*=========================================================================
 Include Files
 ==========================================================================*/

#include "ChipInfoLocal.h"
#include "DALStdErr.h"
#include "DALStdDef.h"
#include "ChipInfoImage.h"
#include "ChipInfoDefs.h"


/* ===========================================================================
 **  FUNCTION      ChipInfo_GetRawChipDeviceFamily
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

uint32 ChipInfo_GetRawDeviceFamily(void)
{
  return 0;
} /* END ChipInfo_GetRawDeviceFamily */

/* ===========================================================================
 **  FUNCTION      ChipInfo_GetRawChipDeviceNumber
 **
 **  DESCRIPTION   See ChipInfo.h
 ** ======================================================================== */

uint32 ChipInfo_GetRawDeviceNumber(void)
{
  return 0;
} /* END ChipInfo_GetRawDeviceNumber */