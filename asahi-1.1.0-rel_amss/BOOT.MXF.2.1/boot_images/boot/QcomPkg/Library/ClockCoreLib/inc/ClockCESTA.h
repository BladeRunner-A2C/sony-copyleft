#ifndef __CLOCKCESTA_H__
#define __CLOCKCESTA_H__
/*
===========================================================================
*/
/**
  @file ClockCESTA.h

  Internal header file for the clock cesta
*/
/*
  ====================================================================

  Copyright (c) 2022-2023 QUALCOMM Technologies, Inc.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: 
  $DateTime: 
  $Author: 

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDefs.h"

/*=========================================================================
      Function Declarations
==========================================================================*/
/* =========================================================================
**  Function : Clock_InitCESTA
** =========================================================================*/
/**
  Initializes CESTA HW

  This function initializes CESTA instances 
  that are set to be default configured

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/
ClockResult Clock_InitCESTA(void);

/* =========================================================================
**  Function : Clock_InitCESTAInstance
** =========================================================================*/
/**
  Initializes a particular CESTA instance 

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/
ClockResult Clock_InitCESTAInstance(const ClockCESTA *pCESTA);

/* =========================================================================
**  Function : Clock_CESTAEnableDependencies
** =========================================================================*/
/**
  Enable dependencies for a CESTA instance 

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/
ClockResult Clock_CESTAEnableDependencies(const ClockCESTA* pCESTA);

/* =========================================================================
**  Function : Clock_CESTADisableDependencies
** =========================================================================*/
/**
  Disable dependencies for a CESTA instance 

  @return
  CLOCK_SUCCESS -- Init was successful.
  CLOCK_ERROR -- Initialization failed.

  @dependencies
  None.
*/
ClockResult Clock_CESTADisableDependencies(const ClockCESTA* pCESTA);
    

#endif /* !__CLOCK_CESTA_H__ */

