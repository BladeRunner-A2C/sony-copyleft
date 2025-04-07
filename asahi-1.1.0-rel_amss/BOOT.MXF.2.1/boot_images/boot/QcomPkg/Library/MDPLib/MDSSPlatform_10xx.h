#ifndef __MDSSPlatform_10xx_H__
#define __MDSSPlatform_10xx_H__
/*=============================================================================
 
  File: MDSSPlatform_10xx.h
 
  Internal header file for MDSS 10xx library
  
 
  Copyright (c) 2022-2024 Qualcomm Technologies, Inc. 
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

=============================================================================*/

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "MDPLib_i.h"

/*===========================================================================
                                Defines 
===========================================================================*/

#define XO_DEFAULT_FREQ_IN_HZ                     19200000

/* Minimal MDP core clock, this is SVS (voltage level) */
#define MDP_MIN_CORE_CLOCK                        300000000

/* MDP core bandwidth IB value, it is 800MB/s */
#define MDP_CORE_BANDWIDTH_VOTE_IB                800000000

/* MDP DSC Cores for 10xx lanai platform */
#define MDP_DSC_CORES_10XX                         6

/* Creating the mask based on number of dsc cores, 0th bit is ignored as its pointing to HAL_MDP_DSC_NONE */
#define MDP_DSC_MASK_10XX                          ((1<<(MDP_DSC_CORES_10XX + 1))-1)

/* MDP DSC Cores for 101x palawan platform */
#define MDP_DSC_CORES_101X                         3

/* Creating the mask based on number of dsc cores, 0th bit is ignored as its pointing to HAL_MDP_DSC_NONE */
#define MDP_DSC_MASK_101X                          ((1<<(MDP_DSC_CORES_101X + 1))-1)

 /*=========================================================================
     MDSS 7.x.x Tables
 ==========================================================================*/


MDPExternalClockEntry            sDSI0ExtClocks_10xx[] = 
{
   {"disp_cc_mdss_esc0_clk",           0, 1, 0, 0, 0, 0},     // Index 0 : primary source :XO , Secondary source : dsi pll
   {"disp_cc_mdss_pclk0_clk",          1, 0, 0, 0, 0, 0},     // Index 1 : Source dsi0_phy_pll_out_dsiclk
   {"disp_cc_mdss_byte0_clk",          2, 0, 0, 0, 0, 0},     // Index 2 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte0_intf_clk",     2, 0, 2, 0, 0, 0},     // Index 3 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte0_div_clk_src",  0, 0, 0, 0, 0, 0, 2},  // Index 4 : CDIV, divided by 2 is default for dphy
   {"\0",                              0, 0, 0, 0, 0, 0},  
 };

 MDPExternalClockEntry            sDSI1ExtClocks_10xx[] = 
 {
   {"disp_cc_mdss_esc1_clk",           0, 1, 0, 0, 0, 0},     // Index 0 : primary source :XO , Secondary source : dsi pll
   {"disp_cc_mdss_pclk1_clk",          3, 0, 0, 0, 0, 0},     // Index 1 : Source dsi1_phy_pll_out_dsiclk
   {"disp_cc_mdss_byte1_clk",          4, 0, 0, 0, 0, 0},     // Index 2 : Source dsi1_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_intf_clk",     4, 0, 2, 0, 0, 0},     // Index 3 : Source dsi1_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_div_clk_src",  0, 0, 0, 0, 0, 0, 2},  // Index 4 : CDIV for byte_intf_clk
   {"\0",                              0, 0, 0, 0, 0, 0},  
 };

 /*For Dual DSI Split display, DSI0/DSI1 share same PLL-- DSI0_PLL */
MDPExternalClockEntry            sDSI1SharedSourceExtClocks_10xx[] = 
{
   {"disp_cc_mdss_esc1_clk",           0, 1, 0, 0, 0, 0},     // Index 0 : primary source :XO , Secondary source : dsi pll
   {"disp_cc_mdss_pclk1_clk",          1, 0, 0, 0, 0, 0},     // Index 1 : Source dsi0_phy_pll_out_dsiclk
   {"disp_cc_mdss_byte1_clk",          2, 0, 0, 0, 0, 0},     // Index 2 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_intf_clk",     2, 0, 2, 0, 0, 0},     // Index 3 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_div_clk_src",  0, 0, 0, 0, 0, 0, 2},  // Index 4 : CDIV for byte_intf_clk
   {"\0",                              0, 0, 0, 0, 0, 0},  
 };

  /* MDSS Clock list
   * Note: Clocks are ordered in order to ensure Ahb access is available prior to accessing the core.
   */
  MDPClockEntry MDSSClocks_10xx[] =
  {
    {"gcc_disp_hf_axi_clk",               200000000, NULL, MDP_CLOCKFLAG_BUS, 0x0},
    {"disp_cc_mdss_ahb_clk",                      0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_mdp_clk",              325000000, NULL,               0x0, 0x0},
    {"disp_cc_mdss_vsync_clk",                    0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_rscc_ahb_clk",                 0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_rscc_vsync_clk",               0, NULL,               0x0, 0x0},
    {"\0",                                        0, NULL,               0x0, 0x0}
  };

  /* MDSS Clock list
   * Note: Clocks are ordered in order to ensure Ahb access is available prior to accessing the core.
   */
  MDPClockEntry MDSSClocks_101x[] =
  {
    {"gcc_disp_hf_axi_clk",               200000000, NULL, MDP_CLOCKFLAG_BUS, 0x0},
    {"disp_cc_mdss_ahb_clk",                      0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_mdp_clk",              600000000, NULL,               0x0, 0x0},
    {"disp_cc_mdss_vsync_clk",                    0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_rscc_ahb_clk",                 0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_rscc_vsync_clk",               0, NULL,               0x0, 0x0},
    {"\0",                                        0, NULL,               0x0, 0x0}
  };

  /* Core clock that need be updated dynamically */
  MDPDynamicClockEntry sMDPCoreClock_10xx=
  { 
      "disp_cc_mdss_mdp_clk",                       0, MDP_MIN_CORE_CLOCK
  };
  
  /* Record all the clocks that can be updated dynamically */
  const MDP_DynamicClockList sMDSSDynamicClock_10xx =
  {
    &sMDPCoreClock_10xx,                                  // MDP core clock
  };
  
  /* Lanai DSC Core Caps */
  MDPDSCCapsType sMDSSDSCCaps_10xx =
  {
    MDP_DSC_CORES_10XX,                                  //No of dsc cores
    MDP_DSC_MASK_10XX,                                   //DSC mask
    MDP_DSC_CORES_10XX,                                  //Available num of dscs
  };
  
  /* Palawan Core Caps */
  MDPDSCCapsType sMDSSDSCCaps_101x =
  {
    MDP_DSC_CORES_101X,                                  //No of dsc cores
    MDP_DSC_MASK_101X,                                   //DSC mask
    MDP_DSC_CORES_101X,                                  //Available num of dscs
  };
  
  /* Interface caps*/
  MDPInterfaceCapsType sMDSSInterfaceCaps_10xx =
  {
    MDP_INTERFACE_CAPS_SPR        | 
    MDP_INTERFACE_CAPS_DEMURA     | 
    MDP_INTERFACE_CAPS_FPSFUSE,                          // uInterfaceFeatureCaps
    1,                                                   // uNumVDCMCores
    0,                                                   // DSC Encoder Version
    6,                                                   // uNumDSCCores
    MDP_INTERFACE_CAPS_TWO_PPC,                          // eDSIInterfaceCaps
    MDP_INTERFACE_CAPS_TWO_PPC,                          // eDPInterfaceCaps
  };

  /* Interface caps*/
  MDPInterfaceCapsType sMDSSInterfaceCaps_1010 =
  {
    MDP_INTERFACE_CAPS_SPR        | 
    MDP_INTERFACE_CAPS_DEMURA     | 
    MDP_INTERFACE_CAPS_FPSFUSE,                          // uInterfaceFeatureCaps
    1,                                                   // uNumVDCMCores
    0,                                                   // DSC Encoder Version
    3,                                                   // uNumDSCCores
    MDP_INTERFACE_CAPS_TWO_PPC,                          // eDSIInterfaceCaps
    MDP_INTERFACE_CAPS_TWO_PPC,                          // eDPInterfaceCaps
  };
  
  /* Layer mixer capabilities */
  MDPPlatformMixerCapabilityType sPlatformMixerCaps_10xx =
  {
    MDP_PIXEL_CLOCK_CVT(4096, 2160, 30),
    MDP_PIXEL_CLOCK_CVT(4096, 2160, 30)
  };
  
  /* MDP caps */
  MDPDeviceCapsType sMDSSDeviceCaps_10xx =
  {
    &sMDSSInterfaceCaps_10xx,                             //Interface caps
    &sPlatformMixerCaps_10xx                              //Mixer Capabilities
  };
  
  /* MDP caps */
  MDPDeviceCapsType sMDSSDeviceCaps_1010 =
  {
    &sMDSSInterfaceCaps_1010,                             //Interface caps
    &sPlatformMixerCaps_10xx                              //Mixer Capabilities
  };
  
  /* Demura pipe config mapping*/
  MDPDemuraPipeMapType sMDPDemuraPipeCfg_10xx[] =
  {
    {MDP_DISPLAY_PRIMARY,   {HAL_MDP_SOURCE_PIPE_DMA_3,       HAL_MDP_SOURCE_PIPE_DMA_3_REC1}},
    {MDP_DISPLAY_SECONDARY, {HAL_MDP_SOURCE_PIPE_DMA_1_REC1,  HAL_MDP_SOURCE_PIPE_NONE}},
    {MDP_DISPLAY_MAX,       {HAL_MDP_SOURCE_PIPE_NONE,        HAL_MDP_SOURCE_PIPE_NONE}},
  };

  /* DSI0 Clock list
   */
  MDPClockEntry DSI0Clocks_10xx[] =
  {
    {"disp_cc_mdss_esc0_clk",         0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte0_clk",        0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte0_intf_clk",   0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_pclk0_clk",        0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte0_div_clk_src",0, NULL, MDP_CLOCKFLAG_CDIV, 0x0},
    {"\0",                            0, NULL, 0x0,                0x0}
  };
  
  /* DSI1 Clock list
   */
  MDPClockEntry DSI1Clocks_10xx[] =
  {
    {"disp_cc_mdss_esc1_clk",         0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte1_clk",        0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte1_intf_clk",   0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_pclk1_clk",        0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte1_div_clk_src",0, NULL, MDP_CLOCKFLAG_CDIV, 0x0},
    {"\0",                            0, NULL, 0x0,                0x0}
  };


  /* Disp CC XO clock
  */
  MDPClockEntry DispCcXoClk_10xx[] =
  {
      {"gcc_disp_ahb_clk",      0, NULL, MDP_CLOCKFLAG_SHARED, 0x0},
      {"disp_cc_xo_clk",        0, NULL, MDP_CLOCKFLAG_SHARED, 0x0},
      {"\0",                    0, NULL, 0x0                 , 0x0}
  };
  
  /* MDSS power domain list
   */
  const MDPPowerDomainEntry MDSS10xxPowerDomain[] = 
  {
      {"disp_cc_mdss_core_gdsc",        0x0},
      {"\0",                            0x0}
  };
  
  /* MDSS resource list for MDSS 10.0.0
  */
  const MDP_ResourceList sMDP100xResources =
  {
      (MDPPowerDomainEntry*)  &MDSS10xxPowerDomain,                   /* Power domain    */
      (MDPClockEntry*)        &DispCcXoClk_10xx,                      /* DISP_CC clocks  */
      (MDPClockEntry*)        &MDSSClocks_10xx,                       /* MDP clocks      */
      (MDPClockEntry*)        &DSI0Clocks_10xx,                       /* DSI0 clocks     */
      (MDPClockEntry*)        &DSI1Clocks_10xx,                       /* DSI1 clocks     */
       NULL,                                                         /* DP0 clocks      */
       NULL,                                                         /* DP1 clocks      */
       NULL,                                                         /* DP2 clocks      */
       NULL,                                                         /* DP3 Clocks      */
       NULL,                                                         /* RSSC Clocks     */
      (MDP_DynamicClockList*) &sMDSSDynamicClock_10xx,                /* Clocks that can be changed dynamically */
      (MDPDeviceCapsType *)   &sMDSSDeviceCaps_10xx,                  /* Display Core Capabilities */
      (MDPDemuraPipeMapType*) &sMDPDemuraPipeCfg_10xx,                /* Demura pipe config */
      (MDPDSCCapsType *)      &sMDSSDSCCaps_10xx,                     /* DSC Core Caps */
  };

  /* MDSS resource list for MDSS 10.1.0
  */
  const MDP_ResourceList sMDP101xResources =
  {
      (MDPPowerDomainEntry*)  &MDSS10xxPowerDomain,                   /* Power domain    */
      (MDPClockEntry*)        &DispCcXoClk_10xx,                      /* DISP_CC clocks  */
      (MDPClockEntry*)        &MDSSClocks_101x,                       /* MDP clocks      */
      (MDPClockEntry*)        &DSI0Clocks_10xx,                       /* DSI0 clocks     */
      (MDPClockEntry*)        &DSI1Clocks_10xx,                       /* DSI1 clocks     */
       NULL,                                                         /* DP0 clocks      */
       NULL,                                                         /* DP1 clocks      */
       NULL,                                                         /* DP2 clocks      */
       NULL,                                                         /* DP3 Clocks      */
       NULL,                                                         /* RSSC Clocks     */
      (MDP_DynamicClockList*) &sMDSSDynamicClock_10xx,                /* Clocks that can be changed dynamically */
      (MDPDeviceCapsType *)   &sMDSSDeviceCaps_1010,                  /* Display Core Capabilities */
      (MDPDemuraPipeMapType*) &sMDPDemuraPipeCfg_10xx,                /* Demura pipe config */
      (MDPDSCCapsType *)      &sMDSSDSCCaps_101x,                     /* DSC Core Caps */
  };
  
  /* MDP External resource list for MDSS 100x
  */
  const MDP_ExtClockResourceList sMDP100xExtClockResources =
  {
      (MDPExternalClockEntry*)    &sDSI0ExtClocks_10xx,               /* DSI0 Ext clocks      */
      (MDPExternalClockEntry*)    &sDSI1ExtClocks_10xx,               /* DSI1 Ext clocks      */
      (MDPExternalClockEntry*)    &sDSI1SharedSourceExtClocks_10xx,   /* DSI shared clocks for dual DSI */
      (MDPExternalClockEntry*)    &sDSI0ExtClocks_10xx,               /* DSI0 Ext clocks      */
  };

 /* Display resource list - MDSS 10.0.0
 */
 const DisplayResourceList sDisplayMDP100xResources =
 {
    (MDP_ResourceList*)            &sMDP100xResources,                /* MDP Resources               */
    (MDP_ExtClockResourceList*)    &sMDP100xExtClockResources,        /* MDP Ext Resources           */
 };

/* Display resource list - MDSS 10.1.0
 */
 const DisplayResourceList sDisplayMDP101xResources =
 {
    (MDP_ResourceList*)            &sMDP101xResources,                /* MDP Resources               */
    (MDP_ExtClockResourceList*)    &sMDP100xExtClockResources,        /* MDP Ext Resources           */
 };
 
 /*=========================================================================
       Top level Tables
 ==========================================================================*/

/* Resource list for MDSS 10xx
*/
const MDP_HwMinorFamilyResourceList asHardwareFamilyMinor10xx[RES_MAX_FAMILY_MINOR] = {
  {MDSS_DEVICE_VERSION_10_00, (DisplayResourceList*)&sDisplayMDP100xResources},              /* MDSS Family 10.0.x, Lanai */
  {MDSS_DEVICE_VERSION_10_01, (DisplayResourceList*)&sDisplayMDP101xResources},              /* MDSS Family 10.0.x, Palawan */
};


#endif // __MDSSPlatform_10xx_H__

