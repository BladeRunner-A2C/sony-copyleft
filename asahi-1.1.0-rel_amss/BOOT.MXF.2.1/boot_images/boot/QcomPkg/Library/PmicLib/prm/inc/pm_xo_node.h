#ifndef __PM_XO_NODE_H__
#define __PM_XO_NODE_H__

/*! \file
 *  
 *  \brief  pm_xo_node.h ----This file contains prototypes and definitions for
 *                           for XO node
 *  
 *    Copyright (c) 2022 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
 *    QUALCOMM Proprietary.  Export of this technology or software is regulated 
 *    by the U.S. Government. Diversion contrary to U.S. law prohibited.
 *
 */
/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time. 

$Header:$
$DateTime:$

===========================================================================*/

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/
#include "com_dtypes.h"
#include "npa.h"
#include "npa_resource.h"
#include "pm_rpmh.h"

/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/
#define PMIC_NODE_XO "node/pmic/client/xo"
#define PMIC_NODE_XO2 "node/pmic/client/xo2"


typedef struct
{   
  /* Resource data */
  const char        *cmd_db_name;
  
  /* RPMh Data */
  pm_rpmh_data_type  rpmh_data;
}pm_xo_rsrc_data_type;


typedef struct
{
  npa_node_definition *pm_xo_node_data;
  uint32              pm_xo_node_count;
}pm_xo_node_config_type;


/*===========================================================================

                FUNCTION DEFINITIONS

===========================================================================*/

/*===========================================================================

FUNCTION pm_xo_node_init

DESCRIPTION
    This function initializes xo node.

INPUT PARAMETERS
  None.

RETURN VALUE
  None.

DEPENDENCIES
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void
pm_xo_node_init (void);

/*===========================================================================

FUNCTION pm_xo_driver_fcn

DESCRIPTION
    This function handles xo node aggregation and populates RPMh cmd_set.

INPUT PARAMETERS
  @resource[in]: npa_resource pointer
  @client[in]: npa_client_handle
  @state[in]: npa_resource_state

RETURN VALUE
  npa_resource_state. #Refer npa.h

DEPENDENCIES
  None.

SIDE EFFECTS
  None.

===========================================================================*/
npa_resource_state
pm_xo_driver_fcn(npa_resource *resource,
                npa_client_handle client,
                npa_resource_state state);



/*===========================================================================

FUNCTION pm_xo_node_get_target_data

DESCRIPTION
    This function gets pointer to target specific xo node data 

INPUT PARAMETERS

RETURN VALUE
  pm_xo_node_config_type. #Refer pm_xo_node_target.h

DEPENDENCIES
  None.

SIDE EFFECTS
  None.

===========================================================================*/
pm_xo_node_config_type*
pm_xo_node_get_target_data(void);


#endif //__PM_XO_NODE_H__
