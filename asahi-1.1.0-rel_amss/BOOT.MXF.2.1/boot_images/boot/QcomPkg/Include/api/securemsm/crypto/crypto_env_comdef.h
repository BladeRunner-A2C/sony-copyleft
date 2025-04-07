#ifndef UC_COMDEF_H
#define UC_COMDEF_H


/*===========================================================================

               A S W   S E C U R I T Y   S E R V I C E S

                    C O M M O N   U T I L I T I E S

GENERAL DESCRIPTION


EXTERNALIZED FUNCTIONS


INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright (c) 2012, 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/api/securemsm/crypto/crypto_env_comdef.h#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/16/12   yk     initial version
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <stdint.h>
#include "string.h"
#include "boot_comdef.h"

/* -----------------------------------------------------------------------
** Standard Types
** ----------------------------------------------------------------------- */

/* The following definitions are the same accross platforms.  This first
** group are the sanctioned types.
*/

typedef unsigned int boolean_t;

#ifndef NULL
  #define NULL  0
#endif

#ifndef MIN
   #define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#endif // UC_COMDEF_H
