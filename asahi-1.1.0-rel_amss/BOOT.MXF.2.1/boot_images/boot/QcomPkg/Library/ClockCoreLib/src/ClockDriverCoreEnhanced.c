/** @file ClockDxeCoreEnhanced.c

  This file implements clock EFI protocol interface for Api's which are supported in non-mission mode.
  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/* =========================================================================
**  Function : Clock_DumpClocksState
** =========================================================================*/
/*
  See EFIClock.h
*/
ClockResult Clock_DumpClocksState
(
  ClockDrvCtxt   *pDrvCtxt,
  uint32          nLogMask
)
{
  ClockResult          status;
  
  status = Clock_LogStateToUart(pDrvCtxt, nLogMask);
  if (status ==  CLOCK_ERROR)
  {
    DEBUG(( EFI_D_ERROR, "ClockDxe:: Dump Clocks State FAIL\n"));
  }
  return status;
}

