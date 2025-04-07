/**************************************************************************
 * FILE: devprg_transport_pcie.h
 *
 * PCIE abstraction layer for TX and RX.
 *
 * Copyright (c) 2018, 2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/5.1/QcomPkg/Library/DevPrgLib/devprg_transport_pcie.h#1 $
  $DateTime: 2021/02/25 15:01:58 $
  $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2023-01-09   gml  Added Pinnacles DevPrg PCIe support
2021-02-21   sa   Ported to Olympic.
2018-11-08   eo   Create.

===========================================================================*/

#ifndef __DEVPRG_TRANSPORT_PCIE_H__
#define __DEVPRG_TRANSPORT_PCIE_H__

#include "comdef.h"
#include "devprg_transport.h"


/* Initializes PCIE and returns the function pointers for PCIE TX/RX. */
struct devprg_transport *devprg_transport_pcie_init(void);

#endif /* __DEVPRG_TRANSPORT_PCIE_H__ */
