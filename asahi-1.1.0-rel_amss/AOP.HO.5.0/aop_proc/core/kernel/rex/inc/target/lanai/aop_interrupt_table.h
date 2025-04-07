#ifndef AOP_INTERRUPT_TABLE_H
#define AOP_INTERRUPT_TABLE_H
/*===========================================================================
                             aop_interrupt_table.h

DESCRIPTION:
  AOP interrupt table for external interrupts. This provides the exhaustive
  list of all the AOP interrupts supported on this target.

Copyright (c) 2016-2019 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/


//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include"aop_hwio.h"
//---------------------------------------------------------------------------
// Constant / Define Declarations
//---------------------------------------------------------------------------
typedef enum
{
    CPRF_NSPHMX_IRQ                          =    0  ,
    TBD_1                                    =    1  ,
    TBD_2                                    =    2  ,
    TBD_3                                    =    3  ,
    TBD_4                                    =    4  ,
    CPRF_MXC_IRQ                             =    5  ,
    APSS_DBGCOREPWRUP_IRQ                    =    6  ,
    QDSS_DCC_TASK_DONE_IRQ                   =    7  ,
    CPRF_NSPCX_IRQ                           =    8  ,
    IPCC_ROUTER_TOP_IRQ                      =    9  ,
    TME_AOP_IRQ                              =    10 ,
    MI_PMU_ERROR_IRQ                         =    11 ,
    CPRF_MMCX_IRQ                            =    12 ,
    CPRF_CX_IRQ                              =    13 ,
    CPRF_MX_IRQ                              =    14 ,
    GFX_RBIF_IRQ                             =    15 ,
    GCC_GDS_HW_CTRL_IRQ                      =    16 ,
    TCSR_REGS_SUMMARY_IRQ                    =    17 ,
    VSENSE_RPM_ALARM_IRQ                     =    18 ,
    DDRSS_AOP_IRQ                            =    19 ,
    APCS_SYSWDOGBITEINT                      =    20 ,
    TLMM_SUMMARY_INTR                        =    21 ,
    TLMM_DIR_CONN_INTR                       =    22 ,
    CRC_ERROR_INT                            =    23 ,
    DCC_CRC_ERR_IRQ                          =    24 ,
    DCC_TO_ERR_IRQ                           =    25 ,
    TBD_26                                   =    26 ,
    TBD_27                                   =    27 ,
    TBD_28                                   =    28 ,
    TBD_29                                   =    29 ,
    TBD_30                                   =    30 ,
    AOP_PDC_IRQ_OUT_15                       =    31 ,
    RSCC_TIMEOUT_SUMMARY_IRQ                 =    32 ,
    ARC_LPINOC_IRQ                           =    33,
    ARC_NSP_ISR                              =    34 ,
    CSYSPWRUPREQ_n                           =    35 ,
    CSYSPWRUPREQ                             =    36 ,
    AOP_PDC_IRQ_OUT_0                        =    37 ,
    AOP_PDC_IRQ_OUT_1                        =    38 ,
    AOP_PDC_IRQ_OUT_2                        =    39 ,
    TSENSE0_0C_INT                           =    40 ,
    TSENSE1_0C_INT                           =    41 ,
    AOP_PDC_IRQ_OUT_5                        =    42 ,
    AOP_PDC_IRQ_OUT_6                        =    43 ,
    AOP_PDC_IRQ_OUT_7                        =    44 ,
    SOC_SLEEP_PDC_AOP_UNLOCK_REQ             =    45 ,
    AOSSPWRDWNREQ                            =    46 ,
    ARC_MMCX_INTERRUPT                       =    47 ,
    ARC_CX_INTERRUPT                         =    48 ,
    ARC_MX_INTERRUPT                         =    49 ,
    ARC_DDRPHY_INTERRUPT                     =    50 ,
    ARC_SSCX_INTERRUPT                       =    51 ,
    ARC_SSCMX_INTERRUPT                      =    52 ,
    ARC_GFX_INTERRUPT                        =    53 ,
    ARC_MSS_INTERRUPT                        =    54 ,
    ARC_DDR_INTERRUPT                        =    55 ,
    ARC_NSP2_INTERRUPT                       =    56 ,
    BCM_IRQ_0                                =    57 ,
    BCM_IRQ_1                                =    58 ,
    BCM_IRQ_2                                =    59 ,
    BCM_IRQ_3                                =    60 ,
    BCM_IRQ_4                                =    61 ,
    BCM_IRQ_5                                =    62 ,
    BCM_IRQ_6                                =    63 ,
    BCM_IRQ_7                                =    64 ,
    VOLTAGE_VOTE_INTERRUPT                   =    65 ,
    ENABLE_VOTE_INTERRUPT                    =    66 ,
    MODE_VOTE_INTERRUPT                      =    67 ,
    EUD_CLIENT_ACTIVE_HIGH                   =    68 ,
    VOLTAGE_CHANGE_INTERRUPT                 =    69 ,
    ENABLE_CHANGE_INTERRUPT                  =    70 ,
    MODE_CHANGE_INTERRUPT                    =    71 ,
    EUD_CLIENT_ACTIVE_LOW                    =    72 ,
    VOLTAGE_SETTLED_INTERRUPT                =    73 ,
    ENABLE_SETTLED_INTERRUPT                 =    74 ,
    MODE_SETTLED_INTERRUPT                   =    75 ,
    ARC_MXC_INTERRUPT                        =    76 ,
    SEQUENCERS_INTERRUPT                     =    77 ,
    VRM_ERROR_INTERRUPT                      =    78 ,
    SOC_SLEEP_PDC_AOP_LOCK_REQ               =    79 ,
    CX_COLLAPSE_PDC_AOP_UNLOCK_REQ           =    80 ,
    CX_COLLAPSE_PDC_AOP_LOCK_REQ             =    81 ,
    AOP_PDC_IRQ_OUT_9                        =    82 ,
    DBG_RSRC_REL_PDC_AOP_LOCK_REQ            =    83 ,
    DBG_RSRC_REL_PDC_AOP_UNLOCK_REQ          =    84 ,
    PDC_AOP_SUMMARY_IRQ                      =    85 ,
    DDR_AUX_IRQ_0                            =    86 ,
    DDR_AUX_IRQ_1                            =    87 ,
    DDR_AUX_IRQ_2                            =    88 ,
    DDR_AUX_IRQ_3                            =    89 ,
    DDR_AUX_IRQ_4                            =    90,
    DDR_AUX_IRQ_5                            =    91,
    DDR_AUX_IRQ_6                            =    92,
    DDR_AUX_IRQ_7                            =    93,
    CPRF_IRQ                                 =    94,
    IPCB_TIMEOUT                             =    95,
    EE4_RPM_SPMI_PERIPH_IRQ                  =    96,
    AOP_WDOG_BARK_IRQ                        =    97,
    AOP_QTIMER_INTR_0                        =    98,
    AOP_QTIMER_INTR_1                        =    99,
    VOLTAGE_COMP_DONE                        =    100,
    AOP_PDC_IRQ_OUT_10                       =    101,
    AOP_PDC_IRQ_OUT_11                       =    102,
    AOP_PDC_IRQ_OUT_12                       =    103,
    AOP_PDC_IRQ_OUT_13                       =    104,
    AOP_PDC_IRQ_OUT_14                       =    105,
    AOP_PDC_IRQ_OUT_16                       =    106,
    AOP_PDC_IRQ_OUT_17                       =    107,
    AOP_PDC_IRQ_OUT_18                       =    108,
    AOP_PDC_IRQ_OUT_19                       =    109,
    AOP_PDC_IRQ_OUT_20                       =    110,
    AOP_PDC_IRQ_OUT_21                       =    111,
    AOP_PDC_IRQ_OUT_22                       =    112,
    AOP_PDC_IRQ_OUT_23                       =    113,
    AOP_PDC_IRQ_OUT_24                       =    114,
    AOP_PDC_IRQ_OUT_25                       =    115,
    RPMH_IDLE                                =    116,
    AOP_RSCC_O_RSC_CORE_COMP_IRQ             =    117,
    ARC_CXO_INTERRUPT                        =    118,
    TBD_119                                  =    119,
    TBD_120                                  =    120,
    TBD_121                                  =    121,
    TBD_122                                  =    122,
    TBD_123                                  =    123,
    TBD_124                                  =    124,
    TBD_125                                  =    125,
    TBD_126                                  =    126,
    TBD_127                                  =    127,
    RISCV_INT_MAX
} interrupt_number;

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------
static unsigned int polarity_registers[4] =
{
    HWIO_AOP_INTR_POLARITY_0_ADDR,
    HWIO_AOP_INTR_POLARITY_1_ADDR,
    HWIO_AOP_INTR_POLARITY_2_ADDR,
    HWIO_AOP_INTR_POLARITY_3_ADDR,
};

static unsigned int edge_registers[4] =
{
    HWIO_AOP_INTR_EDG_LVL_0_ADDR,
    HWIO_AOP_INTR_EDG_LVL_1_ADDR,
    HWIO_AOP_INTR_EDG_LVL_2_ADDR,
    HWIO_AOP_INTR_EDG_LVL_3_ADDR,
};

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//===========================================================================
//                             Function Definitions
//===========================================================================
/** 
 * <!-- aop_interrupt_init -->
 *
 * @brief Configures all the aop interrupts to their default type, and
 *        register system exception ISRs.
 *
 *  This is used to configure all the aop interrupts to their default
 *  type by modifying the POLARITY and EGDE bit for the corresponding
 *  interrupt and register the ISRs to the system exception interrupts such
 *  as APSS non secure watchdog bite interrupt.
 *
 *  @param client : None 
 *  @param context : None
 *
 *  @return void
 */
void aop_interrupt_init(void);

#endif /* AOP_INTERRUPT_TABLE_H */

