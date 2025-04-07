/***********************************************************************
 * coldplug
 *
 * Coldplug Config items
 * Copyright (C) 2017, 2022 QUALCOMM Technologies, Inc.
 *
 * Coldplug internal configuration items.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ColdplugLib/inc/coldplug_config_i.h#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2022-10-11   sc    Set the spinor boot lun to add coldplug background_init support
  2017-05-18   rp    Create

  ===========================================================================*/

#ifndef __COLDPLUG_CONFIG_I_H__
#define __COLDPLUG_CONFIG_I_H__

#include "coldplug_config.h"

#define COLDPLUG_DEBUG_ENABLE

#ifndef COLDPLUG_DEBUG_INFO_MAX_COUNT
  #define COLDPLUG_DEBUG_INFO_MAX_COUNT (50)
#endif

/* SPI_NOR lun is set as BOOT lun for background_init support*/
#ifndef COLDPLUG_SPI_NOR_BOOT_LUN
  #define COLDPLUG_SPI_NOR_BOOT_LUN (0)
#endif

#endif /* __COLDPLUG_CONFIG_I_H__ */
