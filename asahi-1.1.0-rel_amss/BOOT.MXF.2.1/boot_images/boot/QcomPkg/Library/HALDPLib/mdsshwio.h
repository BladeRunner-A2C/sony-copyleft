/*! \file */

/*
===========================================================================

FILE:        mdsshwio.h

DESCRIPTION:  
  Top level MDSS HW Access Definition file.  It includes:
  [1] MDSS Register file
  [2] HW Access Macros
  [3] Additionally Defined Fields for HW Access

===========================================================================

                             Edit History


===========================================================================
  Copyright (c) 2010-2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
===========================================================================
*/
#ifndef MDSSHWIO_H
#define MDSSHWIO_H



/* -----------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------- */

// Basic Register Access Macros
#include "mdsshalhwio.h"

// Database Header file of all MDSS Registers: MDP, DSI, HDMI and eDP
// Static MDP Base Defined Here

extern uintPtr MDSS_BASE_PTR;
extern uintPtr USB4_HOST_ROUTER_BASE_PTR;
extern uintPtr QMP_PHY_0_BASE_PTR;
extern uintPtr QMP_PHY_1_BASE_PTR;


#define        MDSS_REG_BASE                              (MDSS_BASE_PTR)
#define        MDSS_BASE                                  (MDSS_REG_BASE)
#define        USB4_HOST_ROUTER_BASE                      (USB4_HOST_ROUTER_BASE_PTR)
#define        QMP_PHY_0_BASE                             (QMP_PHY_0_BASE_PTR)
#define        QMP_PHY_1_BASE                             (QMP_PHY_1_BASE_PTR)


#include "mdssreg.h"

#endif // MDSSHWIO_H
