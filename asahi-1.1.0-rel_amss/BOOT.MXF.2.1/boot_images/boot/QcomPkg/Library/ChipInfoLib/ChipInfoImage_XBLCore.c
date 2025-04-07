/*
 ===============================================================================

FILE: ChipInfoImage.c

DESCRIPTION:  Image-specific implementations of external functions used by
              ChipInfo which are accessed using different APIs on each image

 ================================================================================
 Copyright (c) 2017, 2019 Qualcomm Technologies Incorporated.
 All Rights Reserved.
 QUALCOMM Proprietary and Confidential
 ================================================================================

 $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ChipInfoLib/ChipInfoImage_XBLCore.c#1 $
 $DateTime: 2024/04/02 23:00:31 $
 $Author: cirrusp4svc $

 =============================================================================*/

/*=============================================================================
  Include Files
  =============================================================================*/
#include <string.h>
#include "Library/MemoryAllocationLib.h"
#include "ChipInfoImage.h"
#include "PlatformInfoDefs.h"
#include "smem.h"

/*=============================================================================
  Macros
  =============================================================================*/


/*=============================================================================
  Data definitions
  =============================================================================*/


/*=============================================================================
  Functions
  =============================================================================*/
DalPlatformInfoSMemType *
ChipInfo_GetSocInfo
(
  void
)
{
  DalPlatformInfoSMemType *pSMem;
  uint32 nSize;

  pSMem = (DalPlatformInfoSMemType *)smem_get_addr(SMEM_HW_SW_BUILD_ID, &nSize);
  if (pSMem == NULL || nSize == 0)
  {
    return NULL;
  }

  return pSMem;
}

void
ChipInfo_UnmapSMem
(
  void
)
{
  // Nothing to unmap
  return;
}

void *
ChipInfo_malloc
(
  uint32 nSize
)
{
  return AllocatePool(nSize);
}


void *
ChipInfo_memcpy
(
  void *restrict pDest,
  uint32 nDestLen,
  const void *restrict pSrc,
  uint32 nSrcLen
)
{

  if (pDest == NULL || nDestLen == 0 || pSrc == NULL || nSrcLen == 0)
  {
    return NULL;
  }

  return memcpy(pDest, pSrc, nDestLen);
}


char *
ChipInfo_strcpy
(
  char *szDest,
  const char *szSrc,
  uint32 nDestLen
)
{
  if (szDest == NULL || szSrc == NULL || nDestLen == 0)
  {
    return NULL;
  }

  strlcpy(szDest, szSrc, nDestLen);
  return szDest;
}
