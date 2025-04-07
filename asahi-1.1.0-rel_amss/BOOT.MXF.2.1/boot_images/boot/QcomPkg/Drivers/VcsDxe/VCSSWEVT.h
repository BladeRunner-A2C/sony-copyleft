#ifndef __VCSSWEVT_H__
#define __VCSSWEVT_H__
/*
===========================================================================
*/
/**
  @file VCSSWEVT.h

  This header provides a variety of preprocessor definitions, type, data, and
  function declarations for QDSS event logging.

  This file provides an abstraction layer for QDSS tracer features.

*/
/*
  ====================================================================

  Copyright (c) 2017- 2019 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Drivers/VcsDxe/VCSSWEVT.h#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/


#ifdef VCS_TRACER_SWEVT
#include "tracer.h"
#include "VCSSWEventId.h"
#endif


/*=========================================================================
      Macros
==========================================================================*/


#ifdef VCS_TRACER_SWEVT
#define VCS_SWEvent(...)  \
  tracer_event_simple_vargs(__VA_ARGS__);
#else
#define VCS_SWEvent(...)
#endif


#endif // __VCSSWEVT_H__

