#ifndef __PM_COMM_H__
#define __PM_COMM_H__

/*! \file pm_comm.h
 *  \n
 *  \brief
 *  \n
 *  &copy; Copyright 2014-2019,2021 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/api/pmic/pm/pm_comm_lite.h#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
30/08/21   aab     File added

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_err_flags.h"

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

pm_err_flag_type
pm_comm_read_byte(uint32 slave_id ,
                  uint16 addr,
                  uint8* data);


#endif /* __PM_COMM_H__ */

