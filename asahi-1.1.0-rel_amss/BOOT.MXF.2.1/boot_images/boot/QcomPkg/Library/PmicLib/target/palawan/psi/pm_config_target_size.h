 /*! \file  pm_config_target_size.h 
 *   
 *  \brief  File Contains the PMIC Set Mode Driver Implementation 
 *  \details Set Mode Driver implementation is responsible for setting and getting 
 *  all mode settings such as Register values, memory values, etc. 
 *   
 *    PMIC code generation Version: 1.0.0.0 
 *    Date: 1/24/2024 
 *    PMIC PSI Version: Palawan-SBL-b0x0A_v0x0A - Approved 
 *    PBS RAM Version: Azura_PBS2_RAM_b0x0A_v0x0A_p0x00 
 *    PBS RAM Version: Azura_PBS1_RAM_b0x0A_v0x0A_p0x00 
 *    PBS RAM Version: Azura_PBS3_RAM_b0x0A_v0x07_p0x00 
 *    PBS RAM Version: Kohala_RAM_b0x00_v0x0C_p0x00 
 *    PBS RAM Version: Sculpin_A_RAM_b0x01_v0x03_p0x00 
 *    This file contains code for Target specific settings and modes. 
 *   
 *  Copyright (c) 2018,2024 Qualcomm Technologies, Inc. All rights reserved. 
 *  Confidential and Proprietary - Qualcomm Technologies, Inc. 
 */ 
 
# ifndef __PM_CONFIG_TARGET_SIZE_H__
# define __PM_CONFIG_TARGET_SIZE_H__

#define PM_PBS_RAM_A_ACTIVE_CODE_SIZE 	0x04A2
#define PM_PBS_RAM_B_ACTIVE_CODE_SIZE 	0x1FE0
#define PM_PBS_RAM_C_ACTIVE_CODE_SIZE 	0x02FE
#define PM_PBS_RAM_D_ACTIVE_CODE_SIZE 	0x0200
#define PM_PBS_RAM_E_ACTIVE_CODE_SIZE 	0x0200

#define PM_PBS_RAM_A_SIZE 	0x1000
#define PM_PBS_RAM_B_SIZE 	0x2000
#define PM_PBS_RAM_C_SIZE 	0x1000
#define PM_PBS_RAM_D_SIZE 	0x200
#define PM_PBS_RAM_E_SIZE 	0x400
#define PM_PBS_RAM_SIZE_TOTAL 	0x1A80
#define PM_PBS_RAM_BUF_COUNT 	0x05		//No of PBS RAM 
#define PM_SBL_COND_SEQ_SIZE	0x64
#define PM_SBL_SEQ_SIZE			1887

#define PM_SDAM_SEQ_SIZE		(11* SDAM_DATA_SIZE_MAX) 

#endif /* PM_CONFIG_TARGET_SIZE_H */
