/*===========================================================================

                    I P C    R O U T E R   I N I T

   This file does the node and OS specific initialization of IPC Router
   and sets up all the links.

  ---------------------------------------------------------------------------
  Copyright (c) 2012-2013, 2017 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/IpcrtrLib/src/ipc_router_init.c#1 $
$DateTime: 2024/04/02 23:00:31 $
$Author: cirrusp4svc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/26/17   jlg     ipc_router_proc_info_type moved to ipc_router_settings.h
==========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include "ipc_router_core.h"
#include "ipc_router_xal.h"
#ifdef FEATURE_IPC_ROUTER_XAL_SMDL_SUPPORTED
#include "ipc_router_xal_smdl.h"
#endif /* FEATURE_IPC_ROUTER_XAL_SMDL_SUPPORTED */
#ifdef FEATURE_IPC_ROUTER_XAL_GLINK_SUPPORTED
#include "ipc_router_xal_glink.h"
#endif /* FEATURE_IPC_ROUTER_XAL_GLINK_SUPPORTED */    
#ifdef FEATURE_IPC_ROUTER_XAL_MHI_SUPPORTED
#include "ipc_router_xal_mhi.h"
#endif /* FEATURE_IPC_ROUTER_XAL_MHI_SUPPORTED */    
#include "ipc_router_policy.h"
#include "DALSys.h"
#include "DALSysTypes.h"
#include "ipc_router_settings.h"

/* This file is just a template. Each target must maintain its own version of ipc_router_init.c */

#define IPC_ROUTER_DEFAULT_PROCESSOR_ID 1

extern void ipc_router_qdi_init(void);
extern void qsocket_init(void);

static int ipc_router_inited = 0;
static ipc_router_xal_info_type *ipc_router_xals_info;

extern const ipc_router_proc_info_type ipc_router_devcfg_proc;

static unsigned int ipc_router_get_processor_id(void)
{
  ipc_router_proc_info_type *proc_info;
  /*DALSYS_PROPERTY_HANDLE_DECLARE(handle);
  
  DALSYSPropertyVar prop;
  DALResult result;

  result = DALSYS_GetDALPropertyHandleStr("/dev/core/mproc/ipc_router", handle);
  if(result != DAL_SUCCESS)
  {
    return IPC_ROUTER_DEFAULT_PROCESSOR_ID;
  }
  result = DALSYS_GetPropertyValue(handle, "proc_info", 0, &prop);
  if(result != DAL_SUCCESS)
  {
    return IPC_ROUTER_DEFAULT_PROCESSOR_ID;
  }
  */
  proc_info = (ipc_router_proc_info_type *)&ipc_router_devcfg_proc;
  return proc_info->id;
}

extern const ipc_router_xal_info_type ipc_router_devcfg_xals[];
static void ipc_router_xal_init(void)
{
  uint32 xal_idx;
  /*DALSYS_PROPERTY_HANDLE_DECLARE(handle);
  DALSYSPropertyVar prop;
  DALResult result;
  

  result = DALSYS_GetDALPropertyHandleStr("/dev/core/mproc/ipc_router", handle);
  if(result != DAL_SUCCESS)
  {
    return;
  }
  result = DALSYS_GetPropertyValue(handle, "xals_info", 0, &prop);
  if(result != DAL_SUCCESS)
  {
    return;
  }
  */
  ipc_router_xals_info = (ipc_router_xal_info_type *)ipc_router_devcfg_xals;

  for (xal_idx = 0; ipc_router_xals_info[xal_idx].name != NULL; xal_idx++)
  {
#ifdef FEATURE_IPC_ROUTER_XAL_SMDL_SUPPORTED
    if (strcmp("SMDL", ipc_router_xals_info[xal_idx].name) == 0)
    {
      ipc_router_xal_smdl_param_type *params;
      uint32 idx;
      
      params = (ipc_router_xal_smdl_param_type*)
                    ipc_router_xals_info[xal_idx].table;
      
      for (idx = 0; params[idx].remote != NULL; idx++)
      {
        ipc_router_xal_start_xport(&ipc_router_xal_smdl, 
                                   (void *)&params[idx], 
                                   0, 
                                   params[idx].remote);
      }
    }
#endif /* FEATURE_IPC_ROUTER_XAL_SMDL_SUPPORTED */

#ifdef FEATURE_IPC_ROUTER_XAL_GLINK_SUPPORTED
    if (strcmp("GLINK", ipc_router_xals_info[xal_idx].name) == 0)
    {
      ipc_router_xal_glink_param_type *params;
      uint32 idx;
      
      params = (ipc_router_xal_glink_param_type*)
                    ipc_router_xals_info[xal_idx].table;
      
      for (idx = 0; params[idx].remote_ss != NULL; idx++)
      {
        ipc_router_xal_start_xport(&ipc_router_xal_glink, 
                                   (void *)&params[idx], 
                                   0, 
                                   params[idx].remote_ss);
      }
    }
#endif /* FEATURE_IPC_ROUTER_XAL_GLINK_SUPPORTED */    

#ifdef FEATURE_IPC_ROUTER_XAL_MHI_SUPPORTED
    if (strcmp("MHI", ipc_router_xals_info[xal_idx].name) == 0)
    {
      ipc_router_xal_mhi_param_type *params;
      uint32 idx=0;  
      params = (ipc_router_xal_mhi_param_type*)
                    ipc_router_xals_info[xal_idx].table;
      
      for (idx = 0; params[idx].remote_ss != NULL; idx++) /* Check if zero is valid */ 
      {
        ipc_router_xal_start_xport(&ipc_router_xal_mhi, 
                                   (void *)&params[idx], 
                                   0, 
                                   params[idx].remote_ss);
      }
    }
#endif /* FEATURE_IPC_ROUTER_XAL_MHI_SUPPORTED */    
  }
}

void ipc_router_init(void)
{
  if(ipc_router_inited)
    return;
  ipc_router_inited = 1;
  /* Initialize router and start transports */
  ipc_router_core_init(ipc_router_get_processor_id());
  ipc_router_policy_register(&ipc_router_impl_policy);

  qsocket_init();

#ifdef FEATURE_IPC_ROUTER_QDI_DRIVER
  ipc_router_qdi_init();
#endif

  /* Initialize transports */
  ipc_router_xal_init();
}

