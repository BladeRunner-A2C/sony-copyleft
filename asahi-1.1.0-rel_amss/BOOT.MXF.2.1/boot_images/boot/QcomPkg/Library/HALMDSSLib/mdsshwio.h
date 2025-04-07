/*
 Copyright (c) 2010-2022 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
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


#define        MDSS_REG_BASE                              (MDSS_BASE_PTR)
#define        MDSS_BASE                                  (MDSS_REG_BASE)

#if defined(MDSS920)
#include "mdssreg_920.h"
#else
#include "mdssreg_1000.h"
#endif
#endif // MDSSHWIO_H
