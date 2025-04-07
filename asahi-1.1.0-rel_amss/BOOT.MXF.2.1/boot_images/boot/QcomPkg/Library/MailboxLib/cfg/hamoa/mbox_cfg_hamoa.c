/*=============================================================================

                       MAILBOX CONFIG


 Copyright (c) 2023 QUALCOMM Technologies, Incorporated.
 All rights reserved.
 Qualcomm Confidential and Proprietary

=============================================================================*/

/*=============================================================================
                         EDIT HISTORY FOR FILE

$Header:  $
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "mbox_cfg.h"
#include "mbox_internal.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/*=============================================================================
                       LOCAL DATA DECLARATIONS
=============================================================================*/

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/
mbox_ch_cfg_type mbox_ipc_channels[MBOX_NUM_REMOTES][MBOX_IPC_NUM_CHS] = 
{
  /* All AP<>PDP0 channels in NS domain */
  { {"qppc1", 0, 0}, {"qppc2", 1, MBOX_INVALID_CH_ID}, {"qppc3", 2, MBOX_INVALID_CH_ID}, {"qppc4", 3, MBOX_INVALID_CH_ID}, {"debug_log", 4, 4}, {"scmi", 5, 7}, {"test", 6, MBOX_INVALID_CH_ID}, {"test2", MBOX_INVALID_CH_ID, 10}},
  
  /* All AP<>PDP1 channels in NS domain */
  { {"qppc1", 0, 1}, {"qppc2", 1, MBOX_INVALID_CH_ID}, {"qppc3", 2, MBOX_INVALID_CH_ID}, {"qppc4", 3, MBOX_INVALID_CH_ID}, {"debug_log", 4, 5}, {"scmi", 5, 8}},
  
  /* All AP<>PDP2 channels in NS domain */
  { {"qppc1", 0, 2}, {"qppc2", 1, MBOX_INVALID_CH_ID}, {"qppc3", 2, MBOX_INVALID_CH_ID}, {"qppc4", 3, MBOX_INVALID_CH_ID}, {"debug_log", 4, 6}, {"scmi", 5, 9}},
  
  /* AP<>CPUCP channels in NS domain*/
  { {"qppc1",MBOX_INVALID_CH_ID ,MBOX_INVALID_CH_ID}, {"qppc2",MBOX_INVALID_CH_ID ,MBOX_INVALID_CH_ID}, {"qppc3",MBOX_INVALID_CH_ID ,MBOX_INVALID_CH_ID}, {"qppc4",MBOX_INVALID_CH_ID ,MBOX_INVALID_CH_ID}, {"test",MBOX_INVALID_CH_ID ,MBOX_INVALID_CH_ID}},
};

mbox_cfg_type mbox_cfgs[MBOX_NUM_REMOTES] = 
{
  /* AP<->PDP0 */
  {
    8,
    {
      {0x19980000, NULL, 1, 0x300},
      0x0,           /* idr reg offset */
      0x100          /* cmnd reg offset */
    },
    {
      {0x17420000, NULL, 0, 0x4C08},
      0x0,           /* idr reg offset */
      0x100,         /* cmnd reg offset */
      0x4000,        /* Offset of where the MAP registers start, from IDR */
      0x4400,        /* Offset of where the STATUS registers start, from IDR */
      0x4800,        /* Offset of where the CLEAR registers start, from IDR */
      0x4c00,        /* Offset of EN (ENable) registers from IDR */
      {66, INTR_CONFIG_LEVEL_TRIGGER} /* Interrupt vector */
    }
  },
  
  /* AP<->PDP1 */
  {
    6,
    {
      {0x1A980000, NULL, 1, 0x300},
      0x0,           /* idr reg offset */
      0x100          /* cmnd reg offset */
    },
    {
      {0x17420000, NULL, 0, 0x4C08},
      0x0,           /* idr reg offset */
      0x100,         /* cmnd reg offset */
      0x4008,        /* Offset of where the MAP registers start, from IDR */
      0x4408,        /* Offset of where the STATUS registers start, from IDR */
      0x4808,        /* Offset of where the CLEAR registers start, from IDR */
      0x4c00,        /* Offset of EN (ENable) registers from IDR */
      {67, INTR_CONFIG_LEVEL_TRIGGER} /* Interrupt vector */
    }
  },
  
  /* AP<->PDP2 */
  {
    6,
    {
      {0x1B980000, NULL, 1, 0x300},
      0x0,           /* idr reg offset */
      0x100          /* cmnd reg offset */
    },
    {
      {0x17420000, NULL, 0, 0x4C08},
      0x0,           /* idr reg offset */
      0x100,         /* cmnd reg offset */
      0x4010,        /* Offset of where the MAP registers start, from IDR */
      0x4410,        /* Offset of where the STATUS registers start, from IDR */
      0x4810,        /* Offset of where the CLEAR registers start, from IDR */
      0x4c00,        /* Offset of EN (ENable) registers from IDR */
      {68, INTR_CONFIG_LEVEL_TRIGGER} /* Interrupt vector */
    }
  },
  /* AP<->CPUCP  */
  {
    5,
    {
      {0x18830000, NULL, 1, 0x300},  // TODO: APSS_CPUCP_AP2CPUCP_C | 0x18830000
      0x0,           /* idr reg offset */
      0x100          /* cmnd reg offset */
    },
    {
      {0x17430000, NULL, 0, 0x4C08},
      0x0,           /* idr reg offset */
      0x100,         /* cmnd reg offset */
      0x4000,        /* Offset of where the MAP registers start, from IDR */
      0x4400,        /* Offset of where the STATUS registers start, from IDR */
      0x4800,        /* Offset of where the CLEAR registers start, from IDR */
      0x4c00,        /* Offset of EN (ENable) registers from IDR */
      {60, INTR_CONFIG_LEVEL_TRIGGER} /* Interrupt vector */
    }
  }
};

