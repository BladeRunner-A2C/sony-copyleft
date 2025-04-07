#ifndef BOOT_ARM_IF_H
#define BOOT_ARM_IF_H
/*===========================================================================

                    BOOT ARM IF DEFINITIONS

DESCRIPTION
  Contains definition for arm if 

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020, 2023 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/15/23   ck      Renamed to boot_arm_if
05/21/20   rama    Initial revision

===========================================================================*/


typedef struct boot_arm_if_type
{
  void (*ArmDataSynchronizationBarrier)(void);
  void (*ArmDataMemoryBarrier) (void);
  //UINT32 (*ArmReadCpacr) (void);
  void (*ArmWriteCpacr) (UINT32 Access);
  void (*ArmInstructionSynchronizationBarrier) (void);
  void (*ArmInvalidateDataCache) (void);
  void (*ArmInvalidateInstructionCache) (void);
  //void(*ArmEnableCachesAndMmu) (void);
  void (*ArmDisableCachesAndMmu) (void);
} boot_arm_if_type;

extern boot_arm_if_type arm_if; 


#endif /* BOOT_ARM_IF_H */