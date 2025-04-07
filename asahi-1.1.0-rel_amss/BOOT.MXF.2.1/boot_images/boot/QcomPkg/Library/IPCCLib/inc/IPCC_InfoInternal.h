#ifndef __IPCC_INFOINTERNAL_H__
#define __IPCC_INFOINTERNAL_H__
/*
===========================================================================
*/
/**
  @file IPCC_InfoInternal.h
  @brief Restricted internal interface include file for accessing the IPCC
  device driver info.

  The IPCC_InfoInternal.h file is a restricted API interface to the Inter-Processor 
  Communication Controller driver.
*/
/*
  ===========================================================================

  Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.  
  All Rights Reserved.
  Qualcomm Proprietary and Confidential.

  ===========================================================================

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/IPCCLib/inc/IPCC_InfoInternal.h#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  01/17/19   cp      Initial revision.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "IPCC_Internal.h"
#include <stdint.h>


/*=========================================================================
      Interface Declarations
==========================================================================*/


/* =========================================================================
**  Function : IPCCInfo_Init
** =========================================================================*/
/**
  Initialize the IPCC info specific portion of the driver.

  This function links up the BSP data to the driver.

  @param
  pDrv - Pointer to driver context.

  @return
  None.

  @dependencies
  None.
*/

IPCCErr
IPCCInfo_Init
(
   IPCCDrvCtxt* pDrv
); 

#endif /*__IPCC_INFOINTERNAL_H__*/
