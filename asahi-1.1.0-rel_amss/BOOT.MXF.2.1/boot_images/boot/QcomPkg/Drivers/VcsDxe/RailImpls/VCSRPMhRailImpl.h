#ifndef __VCSRPMHRAILIMPL_H__
#define __VCSRPMHRAILIMPL_H__
/*
===========================================================================
*/
/**
  @file VCSRailRPMh.h

  Interface definitions for the RPMh rail impl type.
*/
/*
  ====================================================================

  Copyright (c) 2017,2021 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Drivers/VcsDxe/RailImpls/VCSRPMhRailImpl.h#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "../VCSBSP.h"
#include "rpmh_client.h"


/*=========================================================================
      Extern data
==========================================================================*/

extern VCSRailControlType VCSRPMhRailImplControl;


/*=========================================================================
      Type Definitions
==========================================================================*/

typedef struct VCSRPMhHandleType
{
  RSCSW_DRV_MAPPING  eDRVId;
  rpmh_client_handle hHandle;
} VCSRPMhHandleType;

/*
 * VCSRPMhRailImplType
 *
 *  szName       - Name of RPMh RSC resource.
 *  anAddress    - Array of addresses to the RSC for this rail.
 *  pRPMh        - Pointer to our RPMh handle data.
 *  eCornerPrior - Prior corner.
 *  aHLVL        - Mapped HLVL values.
 *  aSets        - Array of command sets for this batch.
 */
typedef struct VCSRPMhRailImplType
{
  const char         *szName;
  uint32_t            nAddress;

  VCSRPMhHandleType  *pRPMh;
  rail_voltage_level  eCornerPrior;
  VCSRailNodeType    *pNextInBatch;
  uint8_t             aHLVL[RPMH_NUM_SETS];
  rpmh_command_set_t  aSets[RPMH_NUM_SETS];
} VCSRPMhRailImplType;


#endif  /* __VCSRPMHRAILIMPL_H__ */ 

