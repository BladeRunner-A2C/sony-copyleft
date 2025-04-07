 /*! \file  pm_config_target_size.h 
 *   
 *  \brief  File Contains the PMIC Set Mode Driver Implementation 
 *  \details Set Mode Driver implementation is responsible for setting and getting 
 *  all mode settings such as Register values, memory values, etc. 
 *   
 *    PMIC code generation Version: 1.0.0.0 
 *    Date: 7/21/2023 
 *    PMIC PSI Version: Lanai-SBL-b0x05_v0x4E - Approved 
 *    PBS RAM Version: Azura_PBS2_RAM_b0x05_v0x0B_p0x00 
 *    PBS RAM Version: Azura_PBS1_RAM_b0x05_v0x32_p0x00 
 *    PBS RAM Version: Azura_PBS3_RAM_b0x05_v0x18_p0x00 
 *    PBS RAM Version: Kohala_RAM_b0x05_v0x0E_p0x00 
 *    This file contains code for Target specific settings and modes. 
 *   
 *  &copy; Copyright 2023 Qualcomm Technologies Incorporated, All Rights Reserved 
 */ 
 
# ifndef __PM_CONFIG_TARGET_SIZE_H__
# define __PM_CONFIG_TARGET_SIZE_H__

#define PM_PBS_RAM_A_ACTIVE_CODE_SIZE 	0x04A2
#define PM_PBS_RAM_B_ACTIVE_CODE_SIZE 	0x1F72
#define PM_PBS_RAM_C_ACTIVE_CODE_SIZE 	0x02FE
#define PM_PBS_RAM_D_ACTIVE_CODE_SIZE 	0x0200

#define PM_PBS_RAM_A_SIZE 	0x1000
#define PM_PBS_RAM_B_SIZE 	0x3000
#define PM_PBS_RAM_C_SIZE 	0x1000
#define PM_PBS_RAM_D_SIZE 	0x200
#define PM_PBS_RAM_SIZE_TOTAL 	0x28EE
#define PM_PBS_RAM_BUF_COUNT 	0x04		//No of PBS RAM 
#define PM_SBL_COND_SEQ_SIZE	0x2A
#define PM_SBL_SEQ_SIZE			1902

#define PM_SDAM_SEQ_SIZE		(0* SDAM_DATA_SIZE_MAX) 

#endif /* PM_CONFIG_TARGET_SIZE_H */