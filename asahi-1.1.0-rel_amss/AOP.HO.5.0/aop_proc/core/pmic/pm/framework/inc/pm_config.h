#ifndef __PM_CONFIG_H__
#define __PM_CONFIG_H__

/*! \file pm_config.h
*  \n
*  \brief Contains enums and macro definitions used in config data.
*  \n
*  \n &copy; Copyright 2014-2017 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/core/pmic/pm/framework/inc/pm_config.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/20/14   kt      Created
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "vrm.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/
// Max voltage supported by VRM for regulators
// can be updated to 0x1FFF in future
#define PM_VRM_MAX_VOLTAGE    0x1FFA

#endif // __PM_CONFIG_H__


