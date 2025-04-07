#ifndef IPC_ROUTER_DEBUG_H
#define IPC_ROUTER_DEBUG_H
/*===========================================================================

                      I P C    R O U T E R    D E B U G
                          H E A D E R    F I L E

   This file describes the debugging interface of the router

  ---------------------------------------------------------------------------
  Copyright (c) 2010-2011 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/IpcrtrLib/src/ipc_router_debug.h#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/


/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
/*===========================================================================
                  CONSTANT / MACRO DACLARATIONS
===========================================================================*/
/*===========================================================================
                        TYPE DECLARATIONS
===========================================================================*/
/*===========================================================================
FUNCTION      ipc_router_core_list_*

DESCRIPTION   Debug functions for listing xports, clients and servers

ARGUMENTS     None

RETURN VALUE  None

SIDE EFFECTS  Debug information printed out using message macros
===========================================================================*/
void ipc_router_core_list_xports(void);
void ipc_router_core_list_clients(void);
void ipc_router_core_list_servers(void);
void ipc_router_core_list_procs(void);

#endif
