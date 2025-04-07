
/*! \file  pm_config_pam.c
 *  
 *  \brief  File Contains the PMIC NPA PAM Data
 *  \details  This file contains the PAM data for the PMIC NPA layer.
 *  
 *    Platform: Palawan.XX.2.0
 *    Revision: NO REVISIONS (Working Set)
 *    Template Version: pam/rpmh/pm_config_pam_uefi.c
 *    $Header: $ 
 *    $DateTime: $  $Author: $
 *  
 *  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pmapp_npa.h"
#include "pm_prm_device_defs.h"
#include "npa_remote_resource.h"
#include "pm_config_setting.h"

/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/

#define PMIC_NPA_CLIENT_NODE_DISP_EXT_DP "/node/pmic/client/disp_ext_dp"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM "/node/pmic/client/disp_prim"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM_AMOLED "/node/pmic/client/disp_prim_amoled"
#define PMIC_NPA_CLIENT_NODE_PCIE0 "/node/pmic/client/pcie0"
#define PMIC_NPA_CLIENT_NODE_SD "/node/pmic/client/sd"
#define PMIC_NPA_CLIENT_NODE_UFS_CARD "/node/pmic/client/ufs_card"
#define PMIC_NPA_CLIENT_NODE_USB_HS1 "/node/pmic/client/usb_hs1"
#define PMIC_NPA_CLIENT_NODE_USB_SS1 "/node/pmic/client/usb_ss1"
#define PM_ADD_PROP_CONFIG(id, val) { .prop_id = id, .ptr = (void*)val}
/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/*************************** DISP_EXT_DP Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_ext_dp_b_ldo2 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_ext_dp_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_ext_dp_rails_info [] = 
{
    { (void*)pm_pam_disp_ext_dp_b_ldo2, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_ext_dp_b_ldo4, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_ext_dp [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 2 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
};

/*************************** DISP_PRIM Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_prim_b_ldo2 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_b_ldo8 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_prim_rails_info [] = 
{
    { (void*)pm_pam_disp_prim_b_ldo2, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_b_ldo4, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_b_ldo8, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_prim [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 2 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 8 ),
};

/*************************** DISP_PRIM_AMOLED Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo2 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo8 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo19 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 3000, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 3000, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_c_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_prim_amoled_rails_info [] = 
{
    { (void*)pm_pam_disp_prim_amoled_b_ldo2, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_b_ldo4, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_b_ldo8, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_b_ldo19, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_c_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_prim_amoled [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 2 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 8 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 19 ),
    PM_PRM_CLIENT_VREG_DEP ( c,  ldo, 3 ),
};

/*************************** PCIE0 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_pcie0_b_ldo2 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_pcie0_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_pcie0_rails_info [] = 
{
    { (void*)pm_pam_pcie0_b_ldo2, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_pcie0_b_ldo4, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_pcie0 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 2 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
};

/*************************** SD Client ***************************/

const pm_prm_vreg_data_type
pm_pam_sd_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_sd_b_ldo13 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 2960, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 2960, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_sd_b_ldo23 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_sd_rails_info [] = 
{
    { (void*)pm_pam_sd_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_sd_b_ldo13, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_sd_b_ldo23, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_sd [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 13 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 23 ),
};

/*************************** UFS_CARD Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs_card_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_ufs_card_b_ldo12 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 2504, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 2504, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_ufs_card_d_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 912, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 912, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_ufs_card_d_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs_card_rails_info [] = 
{
    { (void*)pm_pam_ufs_card_b_ldo4, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_ufs_card_b_ldo12, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_ufs_card_d_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_ufs_card_d_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs_card [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 12 ),
    PM_PRM_CLIENT_VREG_DEP ( d,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( d,  ldo, 3 ),
};

/*************************** USB_HS1 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo2 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo7 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo17 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 3104, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 3104, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_usb_hs1_rails_info [] = 
{
    { (void*)pm_pam_usb_hs1_b_ldo2, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_b_ldo4, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_b_ldo7, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_b_ldo17, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_usb_hs1 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 2 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 7 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 17 ),
};

/*************************** USB_SS1 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_usb_ss1_b_ldo2 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_ss1_b_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_ss1_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_usb_ss1_rails_info [] = 
{
    { (void*)pm_pam_usb_ss1_b_ldo2, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_ss1_b_ldo3, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_ss1_b_ldo4, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_usb_ss1 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 2 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 3 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
};

/*************************** NPA NODE RESOURCE ***************************/

const pm_prm_node_resource_info
pm_prm_pam_rsrcs [] =
{
   {
     PMIC_NPA_GROUP_ID_DISP_EXT_DP,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_disp_ext_dp_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_DISP_EXT_DP, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_disp_ext_dp,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_disp_ext_dp),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_DISP_PRIM,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_disp_prim_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_DISP_PRIM, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_disp_prim,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_disp_prim),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_disp_prim_amoled_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_DISP_PRIM_AMOLED, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_disp_prim_amoled,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_disp_prim_amoled),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_PCIE0,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_DEFAULT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_pcie0_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_PCIE0, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_pcie0,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_pcie0),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_SD,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_sd_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_SD, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_sd,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_sd),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_UFS_CARD,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_ufs_card_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_UFS_CARD, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_ufs_card,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_ufs_card),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_USB_HS1,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_DEFAULT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_usb_hs1_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_USB_HS1, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_usb_hs1,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_usb_hs1),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_USB_SS1,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_DEFAULT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_usb_ss1_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_USB_SS1, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_usb_ss1,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_usb_ss1),  // Deps Count
   },
};

uint32 num_of_pam_rsrcs [] = { sizeof(pm_prm_pam_rsrcs) / sizeof(pm_prm_node_resource_info) };

/*************************** Device Layer Resources ***************************/

pm_prm_rsrc_data_type
pm_prm_device_rsrc_data [] =
{
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 2, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_2),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 4, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_4),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 5, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_5),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 7, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_7),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 8, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_8),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 12, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_12),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 13, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_13),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 17, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_17),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 19, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_19),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 23, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_23),
    PM_PRM_DEV_RSRC_VREG ( c, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
    PM_PRM_DEV_RSRC_VREG ( d, ldo, 1, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_1),
    PM_PRM_DEV_RSRC_VREG ( d, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
};

pm_prm_resource_type
pm_prm_device_rsrcs [] =
{
    {
        pm_prm_device_rsrc_data, 
        sizeof(pm_prm_device_rsrc_data)/sizeof(pm_prm_rsrc_data_type), //Number of Resources
        14
    }
};

pm_config_data_kvp pm_pam_config_data[] = 
{
    PM_ADD_PROP_CONFIG( PM_PROP_PRM_PAM_RSRCS, pm_prm_pam_rsrcs),
    PM_ADD_PROP_CONFIG( PM_PROP_PRM_PAM_RSRC_NUM, num_of_pam_rsrcs),
    PM_ADD_PROP_CONFIG( PM_PROP_PRM_DEVICE_RSRCS, pm_prm_device_rsrcs),
};

pm_err_flag_type
pm_config_pam_data(  pm_config_data_kvp **pam_config_data, 
                            uint32 *pam_config_data_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  if ((pam_config_data == NULL) || (pam_config_data_size == NULL))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    *pam_config_data = pm_pam_config_data;
    *pam_config_data_size = ((sizeof(pm_pam_config_data))/(sizeof(pm_pam_config_data[0])));
  }

  return err_flag;
}
