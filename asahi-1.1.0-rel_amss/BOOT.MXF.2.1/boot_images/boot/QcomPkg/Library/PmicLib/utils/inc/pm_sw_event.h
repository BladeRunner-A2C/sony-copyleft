#ifndef __PMICSWEVT_H__
#define __PMICSWEVT_H__
/*
===========================================================================
*/
/**
  @file ClockSWEVT.h

  This header provides a variety of preprocessor definitions, type, data, and
  function declarations for QDSS event logging.

  This file provides an abstraction layer for QDSS tracer features.

*/
/*
  ====================================================================

  Copyright (c) 2011-2013 Qualcomm Technologies, Incorporated.  All Rights Reserved.
  Qualcomm Technologies, Inc Proprietary and Confidential.

  ====================================================================

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/utils/inc/pm_sw_event.h#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  02/08/13   vk     Created.

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/


#ifdef PMIC_NPA_LOGGING
#include "tracer.h"
#include "pm_sw_event_id.h"
#endif


/*=========================================================================
      Macros
==========================================================================*/


#ifdef PMIC_NPA_LOGGING
#define pm_sw_event(...)  \
  tracer_event_simple_vargs(__VA_ARGS__);
#else
#define pm_sw_event(...)
#endif


#endif // __PMICSWEVT_H__

