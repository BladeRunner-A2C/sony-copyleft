/*! \file pm_init.c
*   \n
*   \brief This file contains PMIC initialization function which initializes the PMIC Comm
*   \n layer, PMIC drivers and PMIC applications.
*   \n
*   \n &copy; Copyright 2010-2023 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/framework/src/pm_loader_init.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
12/05/17   aab     Added support to log number of SPMI transaction
11/19/17   aab     Aded check for RUMI target with out PMIC
09/13/17   aab     Added target specific fn call: pm_spmi_tgt_vrm_init() 
07/21/17   czq     Use Spare reg PON_PERPH_RB_SPARE instead of PON_DVDD_RB_SPARE 
03/29/17   aab     Added function pm_spmi_config_hw_interface_ports()
03/29/17   aab     Changed SPMI channel config call to SpmiCfg_ConfigureChannels()
01/04/17   aab     Updated pm_spmi_static_chnl_init(): Added MGPI and VIOCTL PVC configuration
01/20/17   aab     Added pm_spmi_static_chnl_init() and pm_spmi_vrm_init() to support SDM845 target
08/04/16   aab     Updated pm_driver_init() to support debug logging
01/25/16   aab     Updated pm_driver_init() to support RUMI targets with out PMIC
09/25/15   aab     Updated pm_device_setup(void) and Renamed pm_target_information_spmi_chnl_cfg() to pm_bus_init() 
08/08/15   aab     Added pm_device_setup()
06/23/15   aab     Updated pm_driver_init() to ensure if pm device is initialized.
                    pm_driver_init may be called directly in dload mode.
05/31/15   aab     Removed pm_oem_init()
07/16/14   akm     Comm change Updates
03/31/14   akm     Cleanup
01/15/13   aab     Fixed KW error
05/10/11   jtn     Fix RPM init bug for 8960
07/01/10   umr     Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_resource_manager.h"
#include "pm_sbl_boot.h"
#include "pm_sbl_boot_target.h"
#include "pm_device.h"
#include "pm_comm.h"
#include "device_info.h"
#include "pm_target_information.h"
#include "SpmiCfg.h"
#include "SpmiBus.h"
#include "pm_boot.h"
#include "CoreVerify.h"
#include "pm_utils.h"
#include "pm_log_utils.h"
#include "pmio_pon.h"

#include "pm_smps_driver.h"
#include "pm_ldo_driver.h"
#include "pm_clk_driver.h"

#include "pm_bob_driver.h"
#include "pm_dt_parser.h"
#include "pm_image.h"
/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/
static pm_err_flag_type pm_spmi_config_hw_interface_ports(void);
static pm_err_flag_type pm_spmi_vrm_init(void);

/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/


static boolean pm_device_setup_done = FALSE;
static boolean pm_spmi_static_ch_init_done = FALSE;
static SpmiBusCfg_Ppid  pm_vrm_rsrc_arr[PM_VRM_RSRC_ARR_SIZE];



/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
pm_err_flag_type
pm_device_setup(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   if (FALSE == pm_device_setup_done)
   {
      //SPMI init: Must be called before calling any SPMI R/W.
      if(pm_get_img_type() == PM_IMG_LOADER)
      {
        err_flag |= pm_spmi_dynamic_chnl_init(TRUE);
      }
      else if ((pm_get_img_type() == PM_IMG_RAMDUMP) || (pm_get_img_type() == PM_IMG_DEVPROG))
      {
        err_flag |= pm_spmi_dynamic_chnl_init(FALSE);
      }

      err_flag |= pm_comm_channel_init_internal();

      err_flag |= pm_version_detect();

      pm_device_setup_done = TRUE;
   }

   pm_utils_log_err(__func__, err_flag, __LINE__);
   return err_flag;
}

uint32
pm_get_img_type(void)
{
  return PM_IMAGE_TYPE;
}


pm_err_flag_type
pm_driver_init( void )
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   uint32 initial_num_spmi_transn = 0;

   if(pm_version_is_pmic_valid(PMIC_A) == FALSE)
   {
      pm_log_message("Bootup: Driver Init, No PMIC on Target");
      return err_flag = PM_ERR_FLAG_SUCCESS;
   }

   if(!(pm_device_init_status()))
   {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
   }

   initial_num_spmi_transn = pm_get_num_spmi_transaction(0);

   err_flag |= pm_driver_pre_init();

   pm_resource_manager_init();

   err_flag |= pm_driver_post_init();

   if (err_flag == PM_ERR_FLAG_SUCCESS)
   {                                        
      err_flag = pm_comm_write_byte_mask(0, PMIO_PON_PBS_PERPH_RB_SPARE_ADDR, PON_PERPH_RB_SPARE_DRIVER_INIT_MASK, PON_PERPH_RB_SPARE_DRIVER_INIT_MASK); 
   }

   pm_log_message("Driver Init # SPMI Transn: %d", pm_get_num_spmi_transaction(initial_num_spmi_transn));

   pm_utils_log_err(__func__, err_flag, __LINE__);
   return err_flag;
}

pm_err_flag_type
pm_aop_pre_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  if(pm_version_is_pmic_valid(PMIC_A) == FALSE)
  {
     pm_log_message("Bootup: AOP-Pre Init, No PMIC on Target");
     return err_flag = PM_ERR_FLAG_SUCCESS;
  }
  
  err_flag = pm_tgt_aop_pre_init();
  
  //spmi config init for peripheral ownership
  err_flag |= pm_spmi_static_chnl_init();

  //PVC, MGPI VIOCTL port settings configuration and enablement
  err_flag |= pm_spmi_config_hw_interface_ports();

  //configure lock by bit
  err_flag |= pm_config_lock_by_bit();
  
  err_flag |= pm_spmi_ac_cfg();

  pm_utils_free_spmi_buffer();

  pm_log_message("PM Total Mem Allocated: %d ", pm_get_mem_allocated());

  pm_utils_log_err(__func__, err_flag, __LINE__);
  
  return err_flag;
}


/* =========================================================================
**  Function :  pm_target_information_spmi_chnl_cfg
** =========================================================================*/
/**
  Description: The function retrieves PMIC property handle.
               On success it queries the SPMI configurations.
               It configures SPMI channel and interrupt ownership for peripherals.
  @param [in] pmic_prop: property name
  @return
  PM_ERR_FLAG_SUCCESS on success otherwise PM_ERR_FLAG_BUS_ERR.
  @dependencies
  SPMI APIs.
  @sa None
*/
pm_err_flag_type
pm_spmi_dynamic_chnl_init(boolean init_hw)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  /* Initialize SPMI and enable SPMI global interrupt. */
  if (SpmiCfg_Init(init_hw) == SPMI_SUCCESS)
  {
    /* Auto configure SPMI channel and peripheral interrupt ownership. */
    if (SpmiCfg_SetDynamicChannelMode(TRUE) != SPMI_SUCCESS)
    {
      err_flag = PM_ERR_FLAG_BUS_ERR;
    }
  }
  else 
  {
     err_flag  = PM_ERR_FLAG_BUS_ERR;
  }

  pm_utils_log_err(__func__, err_flag, __LINE__);

  return err_flag;
}


/**
 * @brief This function configures SPMI channel.
 * 
 * @details
 *    The function retrieves PMIC property handle for the DEVCFG SDM845 target.
 *    On success it calls SPMI API to configure SPMI channels.
 *   
 * @param[in] void No input needed.
 *
 * @return pm_err_flag_type PM_ERR_FLAG_INVALID = ERROR. 
 *         PM_ERR_FLAG_SUCCESS = SUCCESS.
 *
 */

pm_err_flag_type pm_spmi_static_chnl_init(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   SpmiCfg_ChannelCfg*  spmi_cfg_ptr        = NULL;

   uint32 spmi_cfg_size = 0;

   if(pm_spmi_static_ch_init_done == TRUE)
   {
      return PM_ERR_FLAG_SUCCESS;
   }

   /* Initialize SPMI driver. */
   if (SpmiCfg_Init(FALSE) == SPMI_SUCCESS)
   {
     /* Auto configure SPMI channel and peripheral interrupt ownership. */
     if (SpmiCfg_SetDynamicChannelMode(FALSE) != SPMI_SUCCESS)
     {
       pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
       return err_flag = PM_ERR_FLAG_BUS_ERR;
     }
   }
   else 
   {
      pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
      return err_flag = PM_ERR_FLAG_BUS_ERR;
   }
  
   /* Configure SPMI channels  */
   err_flag |= pm_utils_get_spmi_channels(&spmi_cfg_ptr, &spmi_cfg_size);
   CORE_VERIFY_PTR(spmi_cfg_ptr);
   if (SpmiCfg_ConfigureChannels(spmi_cfg_ptr, spmi_cfg_size) != SPMI_SUCCESS)
   {
       pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
       return err_flag = PM_ERR_FLAG_BUS_ERR;
   }

   // initialize the SPMI BUS
   if( SpmiBus_Init() != SPMI_SUCCESS )
   {
       err_flag |= PM_ERR_FLAG_BUS_ERR;
   }

   if (err_flag == PM_ERR_FLAG_SUCCESS)
   {
      pm_spmi_static_ch_init_done = TRUE;
   }

   pm_utils_log_err(__func__, err_flag, __LINE__);
   return err_flag;
}



/**
 * @brief This function configures and enables HW interface 
 *        ports.
 * 
 * @details
 *    The function retrieves PMIC property handle for the DEVCFG SDM845 target.
 *    On success it calls SPMI API to configure PVC Ports, MGPI
 *    Ports.
 *   
 * @param[in] void No input needed.
 *
 * @return pm_err_flag_type PM_ERR_FLAG_INVALID = ERROR. 
 *         PM_ERR_FLAG_SUCCESS = SUCCESS.
 *
 */
 
static pm_err_flag_type 
pm_config_pvc(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_pvc_config  *pvc_dt_config = NULL;
  SpmiCfg_PvcPortCfg pvc_port_cfg;   
  int i = 0;
  
  pvc_dt_config = (pm_dt_pvc_config*) pm_dt_get_node( PMIC_DT_NODE_ARB_PVC );
  if((pvc_dt_config != NULL) && (pvc_dt_config->node_count > 0 ))
  {
    for(i = 0; i < pvc_dt_config->node_count; i++)
    {
      //CORE_VERIFY(pvc_dt_config->pvc_node[i]); //???check for ptr
      pvc_port_cfg.pvcPortId = pvc_dt_config->pvc_node[i].pvc_port_id;  
      pvc_port_cfg.priority = pvc_dt_config->pvc_node[i].spmi_prioriety;
      pvc_port_cfg.ppids = pvc_dt_config->pvc_node[i].addr_cfg; 
      pvc_port_cfg.numPpids = pvc_dt_config->pvc_node[i].addr_cfg_count;       
               
      if (SpmiCfg_ConfigurePvcPort(&pvc_port_cfg) != SPMI_SUCCESS)
      {
         pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
         return PM_ERR_FLAG_BUS_ERR;
      }
       
    }
  }
  
  return err_flag;   
}
 
 
static pm_err_flag_type 
pm_config_mgpi(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_mgpi_config *mgpi_dt_config = NULL;
  SpmiBusCfg_MgpiPortCfg mgpi_port_cfg; 
  int i = 0;
  
  mgpi_dt_config = (pm_dt_mgpi_config*) pm_dt_get_node( PMIC_DT_NODE_ARB_MGPI );
  if((mgpi_dt_config != NULL) && (mgpi_dt_config->cfg_count > 0 ))
  {
    for(i =0; i < mgpi_dt_config->cfg_count; i++)
    {
       //CORE_VERIFY( mgpi_dt_config->cfg_data[i] ); //check for ptr
        //10bytes for one struct            
       mgpi_port_cfg.mgpiPortId     = mgpi_dt_config->cfg_data[(i*10)];      
       mgpi_port_cfg.pvcPortId      = mgpi_dt_config->cfg_data[(i*10) + 1];       
       mgpi_port_cfg.posEdgeEn      = mgpi_dt_config->cfg_data[(i*10) + 2];       
       mgpi_port_cfg.posEdgePvcIdx  = mgpi_dt_config->cfg_data[(i*10) + 3];   
       mgpi_port_cfg.posEdgeData    = mgpi_dt_config->cfg_data[(i*10) + 4];     
       mgpi_port_cfg.negEdgeEn      = mgpi_dt_config->cfg_data[(i*10) + 5];       
       mgpi_port_cfg.negEdgePvcIdx  = mgpi_dt_config->cfg_data[(i*10) + 6];   
       mgpi_port_cfg.negEdgeData    = mgpi_dt_config->cfg_data[(i*10) + 7];     
       mgpi_port_cfg.muxSelEn       = mgpi_dt_config->cfg_data[(i*10) + 8];        
       mgpi_port_cfg.muxSelVal      = mgpi_dt_config->cfg_data[(i*10) + 9];
       
      if (SpmiCfg_ConfigureMgpiPort(&mgpi_port_cfg) != SPMI_SUCCESS)
      {
         pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
         return PM_ERR_FLAG_BUS_ERR;
      }
       
    }
  }
  
  return err_flag;   
}
 
 
__attribute__((noinline))
pm_err_flag_type pm_spmi_config_hw_interface_ports(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
   uint32 index = 0;

   SpmiCfg_PvcPortCfg** pvc_port_cfg_ptr  = NULL;
   uint32* pvc_port_cfg_size              = NULL;

   SpmiBusCfg_MgpiPortCfg** mgpi_port_cfg_ptr = NULL;
   uint32* mgpi_port_cfg_size                 = NULL;

   SpmiBusCfg_VioctlCfg**   vioctl_cfg_ptr    = NULL;
   uint32* vioctl_cfg_size                    = NULL;

   /* Configure PVC Port */
   pvc_port_cfg_ptr = (SpmiCfg_PvcPortCfg**)pm_target_information_get_specific_info(PM_PROP_PVC_PORT_CFG);
   CORE_VERIFY_PTR(pvc_port_cfg_ptr);

   pvc_port_cfg_size = (uint32*)pm_target_information_get_specific_info(PM_PROP_PVC_PORT_CFG_SIZE);
   CORE_VERIFY_PTR(pvc_port_cfg_size);

   for(index = 0; index < pvc_port_cfg_size[0]; index++)
   {
     CORE_VERIFY_PTR(pvc_port_cfg_ptr[index]);

     if (SpmiCfg_ConfigurePvcPort(pvc_port_cfg_ptr[index]) != SPMI_SUCCESS)
     {
       pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
       return err_flag = PM_ERR_FLAG_BUS_ERR;
     }
   }   
   
   err_flag |= pm_config_pvc();
  
   /* Enable PVC Ports */
   if (SpmiCfg_SetPVCPortsEnabled(TRUE) != SPMI_SUCCESS)
   {
     pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
     return err_flag = PM_ERR_FLAG_BUS_ERR;
   }

   //Config VRM resources and enable VRM port
   err_flag |= pm_spmi_vrm_init(); 
   if (err_flag != PM_ERR_FLAG_SUCCESS) 
   {
      pm_utils_log_err(__func__, err_flag, __LINE__);
      return err_flag;
   }

   /* Configure MGPI PVC Port */
   mgpi_port_cfg_ptr = (SpmiBusCfg_MgpiPortCfg**)pm_target_information_get_specific_info(PM_PROP_MGPI_PORT_CFG);
   CORE_VERIFY_PTR(mgpi_port_cfg_ptr);

   mgpi_port_cfg_size = (uint32*)pm_target_information_get_specific_info(PM_PROP_MGPI_PORT_CFG_SIZE);
   CORE_VERIFY_PTR(mgpi_port_cfg_size);
   
   /*checking the target specific configuration***/
   err_flag = pm_tgt_mgpi_cfg(mgpi_port_cfg_ptr);
   if(PM_ERR_FLAG_SUCCESS != err_flag)
   {
      pm_utils_log_err(__func__, err_flag, __LINE__);
      return err_flag;
   }

   for(index = 0; index < mgpi_port_cfg_size[0]; index++)
   {
      CORE_VERIFY_PTR(mgpi_port_cfg_ptr[index]);
      if (SpmiCfg_ConfigureMgpiPort(mgpi_port_cfg_ptr[index]) != SPMI_SUCCESS)
      {
         pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
         return err_flag = PM_ERR_FLAG_BUS_ERR;
      }
   }
   
   err_flag |= pm_config_mgpi();

   /* Enable PVC Ports */
   if (SpmiCfg_SetMgpiPortsEnabled(TRUE) != SPMI_SUCCESS)
   {
     pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
     return err_flag = PM_ERR_FLAG_BUS_ERR;
   }

    /* Configure VIOCTL Port */

   vioctl_cfg_size = (uint32*)pm_target_information_get_specific_info(PM_PROP_VIOCTL_CFG_SIZE);
   CORE_VERIFY_PTR(vioctl_cfg_size);

   if(vioctl_cfg_size[0] == 0)
   {
     return err_flag = PM_ERR_FLAG_SUCCESS;
   }

   vioctl_cfg_ptr = (SpmiBusCfg_VioctlCfg**)pm_target_information_get_specific_info(PM_PROP_VIOCTL_CFG);
   CORE_VERIFY_PTR(vioctl_cfg_ptr);

   for(index = 0; index < vioctl_cfg_size[0]; index++)
   {
      CORE_VERIFY_PTR(vioctl_cfg_ptr[index]);
      if (SpmiBusCfg_ConfigureVioctl(vioctl_cfg_ptr[index]) != SPMI_SUCCESS)
      {
         pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
         return err_flag = PM_ERR_FLAG_BUS_ERR;
      }
   }

   pm_utils_log_err(__func__, err_flag, __LINE__);
   return err_flag;
}




/**
 * @brief This function packs PMIC peripheral info for VRM port 
 *        configuration.
 * 
 * @details
 *    This function packs PMIC peripheral info for VRM port 
 *         configuration.  The following PMIc Peripherals of all
 *         PMICs, VRM would need to be configured: SMPS,LDO,
 *         LVS, GPIOs, PBS_Clients, Clocks, BOB
 *         Peripheral info gets packed in one array of type
 *         SpmiBusCfg_Ppid.  Thenin this array is added in a
 *         struct SpmiBusCfg_VrmPortCfg which then used to
 *         configure VRM port by calling
 *         SpmiCfg_ConfigureVrmPort() API.
 *   
 * @param[in] void No input needed.
 *
 * @return pm_err_flag_type PM_ERR_FLAG_INVALID = ERROR. 
 *         PM_ERR_FLAG_SUCCESS = SUCCESS.
 *
 */
static pm_err_flag_type pm_spmi_vrm_init(void)
{
   pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
   SpmiBusCfg_VrmPortCfg vrm_port_cfg;
   pm_ldo_data_type*  ldo_ptr  = NULL;
   pm_smps_data_type* smps_ptr = NULL;
   pm_clk_data_type*  clk_ptr  = NULL;
   pm_bob_data_type*  bob_ptr  = NULL;

   uint32 pmic_index    = 0;
   uint32 periph_index  = 0;
   uint32 vrm_cfg_index = 10; //Reserve first 10 for bus_id 1

   memset(&vrm_port_cfg, 0, sizeof(SpmiBusCfg_VrmPortCfg));

   //SMPS
   for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
   {
      smps_ptr = pm_smps_get_data(pmic_index);
      if (smps_ptr != NULL)
      {
         for (periph_index=0; periph_index < smps_ptr->pm_pwr_data.num_of_peripherals; periph_index++)
         {
            if (vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
            {
               pm_utils_log_err(__func__, PM_ERR_FLAG_INVALID_PARAMETER, __LINE__);
               return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
            }
            pm_vrm_rsrc_arr[vrm_cfg_index].slaveId = smps_ptr->comm_ptr->slave_id;
            pm_vrm_rsrc_arr[vrm_cfg_index].address = smps_ptr->pm_pwr_data.base_address + (smps_ptr->pm_pwr_data.pwr_reg_table->peripheral_offset * periph_index);
            vrm_cfg_index++;
            if( pm_get_pmic_model(pmic_index) != PMIC_IS_PM8150 )
            {
              if (vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
              {
                 pm_utils_log_err(__func__, PM_ERR_FLAG_INVALID_PARAMETER, __LINE__);
                 return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
              }            
              pm_vrm_rsrc_arr[vrm_cfg_index].slaveId = smps_ptr->comm_ptr->slave_id;
              pm_vrm_rsrc_arr[vrm_cfg_index].address = smps_ptr->pm_pwr_data.base_address + (smps_ptr->pm_pwr_data.pwr_reg_table->peripheral_offset * periph_index)+ 0x100;
              vrm_cfg_index++; 
            }
         }
      }
   }

   //LDO
   for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
   {
      ldo_ptr = pm_ldo_get_data(pmic_index);
      if (ldo_ptr != NULL) 
      {
         for (periph_index=0; periph_index < ldo_ptr->pm_pwr_data.num_of_peripherals; periph_index++)
         {
            if (vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
            {
               pm_utils_log_err(__func__, PM_ERR_FLAG_INVALID_PARAMETER, __LINE__);
               return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
            }
            pm_vrm_rsrc_arr[vrm_cfg_index].slaveId = ldo_ptr->comm_ptr->slave_id;
            pm_vrm_rsrc_arr[vrm_cfg_index].address = ldo_ptr->pm_pwr_data.base_address + (ldo_ptr->pm_pwr_data.pwr_reg_table->peripheral_offset * periph_index) ;
            vrm_cfg_index++;
         }
      }
   }

   //Clocks
   for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
   {
      clk_ptr = pm_clk_get_data(PM_SPMI_BUSID_0, pmic_index);
      if (clk_ptr != NULL)
      {
         for (periph_index=0; periph_index < clk_ptr->num_of_peripherals; periph_index++)
         {
            if (vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
            {
               pm_utils_log_err(__func__, PM_ERR_FLAG_INVALID_PARAMETER, __LINE__);
               return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
            }
            if (clk_ptr->periph_subtype[periph_index] != 0)
            {
               pm_vrm_rsrc_arr[vrm_cfg_index].slaveId = clk_ptr->comm_ptr->slave_id;
               pm_vrm_rsrc_arr[vrm_cfg_index].address = clk_ptr->base_address + (clk_ptr->clk_reg_table->peripheral_offset * periph_index);
            vrm_cfg_index++;
         }
      }
   }
   }

   //BOB
   for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
   {
      bob_ptr = pm_bob_get_data(pmic_index);
      if (bob_ptr != NULL)
      {
         for (periph_index=0; periph_index < bob_ptr->pm_pwr_data.num_of_peripherals; periph_index++)
         {
            if (vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
            {
               pm_utils_log_err(__func__, PM_ERR_FLAG_INVALID_PARAMETER, __LINE__);
               return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
            }
            pm_vrm_rsrc_arr[vrm_cfg_index].slaveId = bob_ptr->comm_ptr->slave_id;
            pm_vrm_rsrc_arr[vrm_cfg_index].address = bob_ptr->pm_pwr_data.base_address + (bob_ptr->pm_pwr_data.pwr_reg_table->peripheral_offset * periph_index) ;
            vrm_cfg_index++;
         }
      }
   }  
   
   //Target specific configuration
   err_flag |= pm_spmi_tgt_vrm_init(pm_vrm_rsrc_arr, &vrm_cfg_index, PM_VRM_RSRC_ARR_SIZE);
   if (err_flag != PM_ERR_FLAG_SUCCESS) 
   {
      pm_utils_log_err(__func__, err_flag, __LINE__);
      return err_flag;
   }

   //Config PMIC Resource VRM Port 
   vrm_port_cfg.priority = SPMI_ACCESS_PRIORITY_HIGH;
   vrm_port_cfg.ppids    = pm_vrm_rsrc_arr;
   vrm_port_cfg.numPpids = vrm_cfg_index;

   /* Configure VRM Ports */
   if (SpmiCfg_ConfigureVrmPort(&vrm_port_cfg) != SPMI_SUCCESS)
   {
     pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
     return err_flag = PM_ERR_FLAG_BUS_ERR;
   }

   /* Enable VRM Ports */
   if (SpmiCfg_SetVrmPortsEnabled(TRUE) != SPMI_SUCCESS)
   {
     pm_utils_log_err(__func__, PM_ERR_FLAG_BUS_ERR, __LINE__);
     return err_flag = PM_ERR_FLAG_BUS_ERR;
   }

  return err_flag;
}

