/*! \file
 *  
 *  \brief  pm_xo_node.c ----This file contains initialization functions
 *                           prm-xo node device layer
 *  
 * Copyright (c) 2023 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
 * QUALCOMM Proprietary.  Export of this technology or software is regulated 
 * by the U.S. Government. Diversion contrary to U.S. law prohibited.
 *
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header:$ 
$DateTime:$ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/16/22   al      Initial port
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "cmd_db.h"
#include "pmapp_npa.h"
#include "pm_xo_node.h"
#include "pm_log_utils.h"
#include "pm_prm_device.h"
#include "DALSys.h"
#include "pm_prm_stubs.h"
#include "CoreVerify.h"

/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/
extern boolean bPMICStub;


/*===========================================================================

                FUNCTION DEFINITIONS

===========================================================================*/

npa_resource_state
pm_xo_driver_fcn (npa_resource      *resource,
                  npa_client_handle  client,
                  npa_resource_state state)
{

  pm_xo_rsrc_data_type    *rsrc_data = NULL;
  pm_rpmh_data_type       *rpmh_data = NULL;
  boolean                 is_nas_req = FALSE; 
  uint32                  msg_id     = 0;
  rpmh_command_set_t      active_set; 
  rpmh_command_set_t      sleep_set;

  rsrc_data = (pm_xo_rsrc_data_type*)resource->definition->data;
  rpmh_data = &rsrc_data->rpmh_data;

  DALSYS_memset(&active_set, 0, sizeof(rpmh_command_set_t));
  DALSYS_memset(&sleep_set,  0, sizeof(rpmh_command_set_t));


  /*  Immediate request is received but nas requests are still pending,
   *  it means that pmic got a request from IST context on wake-up before
   *  npa serviced the nas callback for the resource. In this case, 
   *  clear out the nas request flag and honor the immediate request since 
   *  the aggregation has changed. 
   *  No need to lock the resource here as its locked by npa already. 
   *  There is no chance of having concurrency issues since resource is 
   *  also locked in the nas callback function before doing any operations
   *  Note: Immediate requests cannot come before system has gone through 
   *        sleep-cycle as NAS requests are scheduled just before entering 
   *        sleep per design
   */
  if(client->type == NPA_CLIENT_REQUIRED ||
      client->type == NPA_CLIENT_SUPPRESSIBLE)
  {   
    rpmh_data->active_set   = resource->request_state;
    rpmh_data->sleep_set    = NPA_RESOURCE_REQUIRED_REQUEST(resource);
    rpmh_data->dirty_active = TRUE;
    rpmh_data->dirty_sleep  = TRUE;
  }
  else if (client->type == NPA_CLIENT_INITIALIZE)
  {
    //Retrun state during initialization call
    return state;
  }
  else
  {    
    PM_LOG_MSG_ERR_FATAL ("Client type not supported");
  }

  pm_rpmh_create_cmd_set(&active_set, &sleep_set, rpmh_data, is_nas_req);

  pm_rpmh_post_set(&active_set, &sleep_set, rpmh_data, &msg_id, is_nas_req);

  if (!(msg_id == 0 || 
        npa_request_has_attribute(client, NPA_REQUEST_FIRE_AND_FORGET)))
  {
    pm_rpmh_barrier_single(msg_id);
  }

  /*PM_LOG_MSG_INFO("Done Rsrc=%a, Client=%a, state=%d, Type=0x%x, attr=0x%x\r\n",
                  client->resource_name, client->name, state, 
                  client->type, client->request_attr);*/

  return state;
}

void
pm_xo_node_init(void)
{
  pm_xo_node_config_type *xo_node_target_cfg = pm_xo_node_get_target_data();
  pm_xo_rsrc_data_type* pm_xo_data = NULL;
  npa_node_definition* pm_xo_node = NULL;
  uint32 i = 0, xo_node_count = 0;

  /* Check if target supports XO resource voting from image */
  if (xo_node_target_cfg == NULL)
  {
    return;
  }

  xo_node_count = xo_node_target_cfg->pm_xo_node_count;

  for(i = 0; i < xo_node_count; i++)
  {
    pm_xo_node = &xo_node_target_cfg->pm_xo_node_data[i];
    
    pm_xo_data = pm_xo_node->resources->data;

    pm_xo_data->rpmh_data.address = cmd_db_query_addr(pm_xo_data->cmd_db_name);

    if((pm_xo_data->rpmh_data.address == 0) && (bPMICStub == FALSE))
    {
      PM_LOG_MSG_ERR_FATAL("Unable to get VRM address for XO%d Node", i);
    }

    if (bPMICStub == TRUE)
    {
      npa_stub_resource(pm_xo_node->resources->name);
    }
    else
    {
      npa_define_node(pm_xo_node, NULL, NULL);
    }
  }

} /* end of pm_xo_node_init() */

