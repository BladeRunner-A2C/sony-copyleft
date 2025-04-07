#ifndef BOOT_SOCKET_DEV_H
#define BOOT_SOCKET_DEV_H
/*=============================================================================

                     Boot Socket Device Driver

GENERAL DESCRIPTION
  This file contains the definition for boot layer that provides the APIs
  for reading and writing to sockets.

Copyright 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
09/21/22   ck           Initial revision.
=============================================================================*/

#include "boot_media_interface_if.h"


typedef enum
{
  BL_ERR_UNSUPPORTED_SOCKET_DEV								= BL_ERR_CUSTOM_ERRORS_START,
} bl_error_socket_dev_type;

bl_error_boot_type boot_socket_dev_get_interface(void *media_interface_if);

#endif //BOOT_SOCKET_DEV_H
