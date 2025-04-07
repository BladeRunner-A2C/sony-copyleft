#ifndef __MDSSPlatform_9xx_H__
#define __MDSSPlatform_9xx_H__
/*=============================================================================
 
  File: MDSSPlatform_9xx.h
 
  Internal header file for MDSS 9xx library
  
 
  Copyright (c) 2021-2024 Qualcomm Technologies, Inc. 
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

/* MDP DSC Cores for 9xx kailua platform */
#define MDP_DSC_CORES_9XX                         4

/* Creating the mask based on number of dsc cores, 0th bit is ignored as its pointing to HAL_MDP_DSC_NONE */
#define MDP_DSC_MASK_9XX                          ((1<<(MDP_DSC_CORES_9XX + 1))-1)

/* MDP DSC Cores for 9xx kailua platform */
#define MDP_DSC_CORES_92X                         6

/* Creating the mask based on number of dsc cores, 0th bit is ignored as its pointing to HAL_MDP_DSC_NONE */
#define MDP_DSC_MASK_92X                          ((1<<(MDP_DSC_CORES_92X + 1))-1)

 /*=========================================================================
     MDSS 7.x.x Tables
 ==========================================================================*/


MDPExternalClockEntry            sDSI0ExtClocks_9xx[] = 
{
   {"disp_cc_mdss_esc0_clk",           0, 1, 0, 0, 0, 0},     // Index 0 : primary source :XO , Secondary source : dsi pll
   {"disp_cc_mdss_pclk0_clk",          1, 0, 0, 0, 0, 0},     // Index 1 : Source dsi0_phy_pll_out_dsiclk
   {"disp_cc_mdss_byte0_clk",          2, 0, 0, 0, 0, 0},     // Index 2 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte0_intf_clk",     2, 0, 2, 0, 0, 0},     // Index 3 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte0_div_clk_src",  0, 0, 0, 0, 0, 0, 2},  // Index 4 : CDIV, divided by 2 is default for dphy
   {"\0",                              0, 0, 0, 0, 0, 0},  
 };

 MDPExternalClockEntry            sDSI1ExtClocks_9xx[] = 
 {
   {"disp_cc_mdss_esc1_clk",           0, 1, 0, 0, 0, 0},     // Index 0 : primary source :XO , Secondary source : dsi pll
   {"disp_cc_mdss_pclk1_clk",          3, 0, 0, 0, 0, 0},     // Index 1 : Source dsi1_phy_pll_out_dsiclk
   {"disp_cc_mdss_byte1_clk",          4, 0, 0, 0, 0, 0},     // Index 2 : Source dsi1_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_intf_clk",     4, 0, 2, 0, 0, 0},     // Index 3 : Source dsi1_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_div_clk_src",  0, 0, 0, 0, 0, 0, 2},  // Index 4 : CDIV for byte_intf_clk
   {"\0",                              0, 0, 0, 0, 0, 0},  
 };

 /*For Dual DSI Split display, DSI0/DSI1 share same PLL-- DSI0_PLL */
MDPExternalClockEntry            sDSI1SharedSourceExtClocks_9xx[] = 
{
   {"disp_cc_mdss_esc1_clk",           0, 1, 0, 0, 0, 0},     // Index 0 : primary source :XO , Secondary source : dsi pll
   {"disp_cc_mdss_pclk1_clk",          1, 0, 0, 0, 0, 0},     // Index 1 : Source dsi0_phy_pll_out_dsiclk
   {"disp_cc_mdss_byte1_clk",          2, 0, 0, 0, 0, 0},     // Index 2 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_intf_clk",     2, 0, 2, 0, 0, 0},     // Index 3 : Source dsi0_phy_pll_out_byteclk
   {"disp_cc_mdss_byte1_div_clk_src",  0, 0, 0, 0, 0, 0, 2},  // Index 4 : CDIV for byte_intf_clk
   {"\0",                              0, 0, 0, 0, 0, 0},  
 };

/* Rscc clock
   */
  MDPClockEntry RsccClocks_92x[]=
  {
     {"gcc_disp_ahb_clk",                   0, NULL, 0x0, 0x0},
     {"gcc_disp_xo_clk",                    0, NULL, 0x0, 0x0},
     {"disp_cc_mdss_rscc_ahb_clk",          0, NULL, 0x0, 0x0},
     {"disp_cc_mdss_rscc_vsync_clk",        0, NULL, 0x0, 0x0},
     {"\0",                                 0, NULL, 0x0, 0x0}
  };
 
  /* MDSS Clock list
   * Note: Clocks are ordered in order to ensure Ahb access is available prior to accessing the core.
   */
  MDPClockEntry MDSSClocks_9xx[] =
  {
    {"gcc_disp_hf_axi_clk",               200000000, NULL, MDP_CLOCKFLAG_BUS, 0x0},
    {"disp_cc_mdss_ahb_clk",                      0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_mdp_clk",              325000000, NULL,               0x0, 0x0},
    {"disp_cc_mdss_vsync_clk",                    0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_rscc_ahb_clk",                 0, NULL,               0x0, 0x0},
    {"disp_cc_mdss_rscc_vsync_clk",               0, NULL,               0x0, 0x0},
    {"\0",                                        0, NULL,               0x0, 0x0}
  };


  /* Core clock that need be updated dynamically */
  MDPDynamicClockEntry sMDPCoreClock_9xx=
  { 
      "disp_cc_mdss_mdp_clk",                       0, MDP_MIN_CORE_CLOCK
  };
  
  /* Record all the clocks that can be updated dynamically */
  const MDP_DynamicClockList sMDSSDynamicClock_9xx =
  {
    &sMDPCoreClock_9xx,                                  // MDP core clock
  };

  /* 9xx platform DSC Core Caps */
  MDPDSCCapsType sMDSSDSCCaps_9xx =
  {
    MDP_DSC_CORES_9XX,                                  //no of dsc cores
    MDP_DSC_MASK_9XX,                                   //dsc mask
    MDP_DSC_CORES_9XX,                                  //available num of dscs
  };
  
  /* Hamoa DSC Core Caps */
  MDPDSCCapsType sMDSSDSCCaps_92x =
  {
    MDP_DSC_CORES_92X,                                  //no of dsc cores
    MDP_DSC_MASK_92X,                                   //dsc mask
    MDP_DSC_CORES_92X,                                  //available num of dscs
  };
  
  /* Interface caps*/
  MDPInterfaceCapsType sMDSSInterfaceCaps_9xx =
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

  MDPInterfaceCapsType sMDSSInterfaceCaps_92x =
  {
    MDP_INTERFACE_CAPS_NONE,                             // uInterfaceFeatureCaps
    0,                                                   // uNumVDCMCores
    0,                                                   // DSC Encoder Version
    6,                                                   // uNumDSCCores
    MDP_INTERFACE_CAPS_TWO_PPC,                          // eDSIInterfaceCaps
    MDP_INTERFACE_CAPS_TWO_PPC,                          // eDPInterfaceCaps
  };

  /* Layer mixer capabilities */
  MDPPlatformMixerCapabilityType sPlatformMixerCaps_92x =
  {
    MDP_PIXEL_CLOCK_CVT(4096, 2160, 30),
    MDP_PIXEL_CLOCK_RB(3840, 2160, 60)
  };
  
  /* MDP caps */
  MDPDeviceCapsType sMDSSDeviceCaps_92x = 
  {
    &sMDSSInterfaceCaps_92x,                             //Interface caps
    &sPlatformMixerCaps_92x                              //Mixer Capabilities
  };

  /* MDP caps */
  MDPDeviceCapsType sMDSSDeviceCaps_9xx =
  {
    &sMDSSInterfaceCaps_9xx,                             //Interface caps
    NULL                                                 //Mixer Capabilities
  };
  
  /* Interface caps*/
  MDPInterfaceCapsType sMDSSInterfaceCaps_91x =
  {
    MDP_INTERFACE_CAPS_NONE,                             // uInterfaceFeatureCaps
    0,                                                   // uNumVDCMCores
    0,                                                   // DSC Encoder Version
    4,                                                   // uNumDSCCores
	MDP_INTERFACE_CAPS_TWO_PPC,                          // eDSIInterfaceCaps
    MDP_INTERFACE_CAPS_TWO_PPC,                          // eDPInterfaceCaps
  };

  /* MDP caps */
  MDPDeviceCapsType sMDSSDeviceCaps_91x =
  {
    &sMDSSInterfaceCaps_91x,                             //Interface caps
    NULL                                                 //Mixer Capabilities
  };

  /* Demura pipe config mapping*/
  MDPDemuraPipeMapType sMDPDemuraPipeCfg_9xx[] =
  {
    {MDP_DISPLAY_PRIMARY,   {HAL_MDP_SOURCE_PIPE_DMA_3,       HAL_MDP_SOURCE_PIPE_DMA_3_REC1}},
    {MDP_DISPLAY_SECONDARY, {HAL_MDP_SOURCE_PIPE_DMA_1_REC1,  HAL_MDP_SOURCE_PIPE_NONE}},
    {MDP_DISPLAY_MAX,       {HAL_MDP_SOURCE_PIPE_NONE,        HAL_MDP_SOURCE_PIPE_NONE}},
  };

  /* DSI0 Clock list
   */
  MDPClockEntry DSI0Clocks_9xx[] =
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
  MDPClockEntry DSI1Clocks_9xx[] =
  {
    {"disp_cc_mdss_esc1_clk",         0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte1_clk",        0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte1_intf_clk",   0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_pclk1_clk",        0, NULL, 0x0,                0x0},
    {"disp_cc_mdss_byte1_div_clk_src",0, NULL, MDP_CLOCKFLAG_CDIV, 0x0},
    {"\0",                            0, NULL, 0x0,                0x0}
  };

  /* DP0 Clock list
   */
  MDPClockEntry DP0Clocks_92x[] =
  {
    {"disp_cc_mdss_dptx0_pixel0_clk",     0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx0_link_clk",       0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx0_aux_clk",        0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx0_link_intf_clk",  0, NULL, 0x0, 0x0},
    {"tcsr_edp_clkref_en",                0, NULL, 0x0, 0x0},
    {"gcc_usb3_prim_phy_pipe_clk",        0, NULL, 0x0, 0x0},
    {"gcc_usb30_prim_sleep_clk",          0, NULL, 0x0, 0x0},
    {"gcc_usb3_prim_phy_aux_clk",         0, NULL, 0x0, 0x0},
    {"gcc_usb3_prim_phy_com_aux_clk",     0, NULL, 0x0, 0x0},
    {"\0",                                0, NULL, 0x0, 0x0}
  };

  /* DP1 Clock list
   */
  MDPClockEntry DP1Clocks_92x[] =
  {
    {"disp_cc_mdss_dptx1_pixel0_clk",     0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx1_link_clk",       0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx1_aux_clk",        0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx1_link_intf_clk",  0, NULL, 0x0, 0x0},
    {"tcsr_edp_clkref_en",                0, NULL, 0x0, 0x0},
    {"gcc_usb3_sec_phy_pipe_clk",         0, NULL, 0x0, 0x0},
    {"tcsr_usb4_1_clkref_en",             0, NULL, 0x0, 0x0},
    {"gcc_usb3_sec_phy_aux_clk",          0, NULL, 0x0, 0x0},
    {"gcc_usb30_sec_sleep_clk",           0, NULL, 0x0, 0x0},
    {"gcc_usb3_sec_phy_com_aux_clk",      0, NULL, 0x0, 0x0},
    {"\0",                                0, NULL, 0x0, 0x0}
  };

  /* DP2 Clock list
   */
  MDPClockEntry DP2Clocks_92x[] =
  {
    {"disp_cc_mdss_dptx2_pixel0_clk",     0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx2_link_clk",       0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx2_aux_clk",        0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx2_link_intf_clk",  0, NULL, 0x0, 0x0},
    {"tcsr_edp_clkref_en",                0, NULL, 0x0, 0x0},
    {"gcc_usb3_tert_phy_pipe_clk",        0, NULL, 0x0, 0x0},
    {"tcsr_usb4_2_clkref_en",             0, NULL, 0x0, 0x0},
    {"gcc_usb3_tert_phy_aux_clk",         0, NULL, 0x0, 0x0},
    {"gcc_usb30_tert_sleep_clk",          0, NULL, 0x0, 0x0},
    {"gcc_usb3_tert_phy_com_aux_clk",     0, NULL, 0x0, 0x0},
    {"\0",                                0, NULL, 0x0, 0x0}
  };

  /* DP3 Clock list
   */
  MDPClockEntry DP3Clocks_92x[] =
  {
    {"disp_cc_mdss_dptx3_pixel0_clk",    0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx3_link_clk",      0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx3_aux_clk",       0, NULL, 0x0, 0x0},
    {"disp_cc_mdss_dptx3_link_intf_clk", 0, NULL, 0x0, 0x0},
    {"tcsr_edp_clkref_en",               0, NULL, 0x0, 0x0},
    {"\0",                               0, NULL, 0x0, 0x0}
  };

  /* Disp CC XO clock
  */
  MDPClockEntry DispCcXoClk_9xx[] =
  {
      {"gcc_disp_ahb_clk",      0, NULL, MDP_CLOCKFLAG_SHARED, 0x0},
      {"disp_cc_xo_clk",        0, NULL, MDP_CLOCKFLAG_SHARED, 0x0},
      {"\0",                    0, NULL, 0x0                 , 0x0}
  };
  
  /* MDSS power domain list
   */
  const MDPPowerDomainEntry MDSS9xxPowerDomain[] = 
  {
      {"disp_cc_mdss_core_gdsc",        0x0},
      {"\0",                            0x0}
  };
  
  /* MDSS resource list for MDSS 8.0.0
  */
  const MDP_ResourceList sMDP90xResources =
  {
      (MDPPowerDomainEntry*)  &MDSS9xxPowerDomain,                   /* Power domain    */
      (MDPClockEntry*)        &DispCcXoClk_9xx,                      /* DISP_CC clocks  */
      (MDPClockEntry*)        &MDSSClocks_9xx,                       /* MDP clocks      */
      (MDPClockEntry*)        &DSI0Clocks_9xx,                       /* DSI0 clocks     */
      (MDPClockEntry*)        &DSI1Clocks_9xx,                       /* DSI1 clocks     */
       NULL,                                                         /* DP0 clocks      */
       NULL,                                                         /* DP1 clocks      */
       NULL,                                                         /* DP2 clocks      */
       NULL,                                                         /* DP3 Clocks      */
       NULL,                                                         /* RSSC Clocks     */
      (MDP_DynamicClockList*) &sMDSSDynamicClock_9xx,                /* Clocks that can be changed dynamically */
      (MDPDeviceCapsType *)   &sMDSSDeviceCaps_9xx,                  /* Display Core Capabilities */
      (MDPDemuraPipeMapType*) &sMDPDemuraPipeCfg_9xx,                /* Demura pipe config */
      (MDPDSCCapsType *)      &sMDSSDSCCaps_9xx,                     /* DSC Core Caps */
  };
  
  /* MDSS resource list for MDSS 9.1.0
  */
  const MDP_ResourceList sMDP91xResources =
  {
      (MDPPowerDomainEntry*)  &MDSS9xxPowerDomain,                   /* Power domain    */
      (MDPClockEntry*)        &DispCcXoClk_9xx,                      /* DISP_CC clocks  */
      (MDPClockEntry*)        &MDSSClocks_9xx,                       /* MDP clocks      */
      (MDPClockEntry*)        &DSI0Clocks_9xx,                       /* DSI0 clocks     */
      (MDPClockEntry*)        &DSI1Clocks_9xx,                       /* DSI1 clocks     */
       NULL,                                                         /* DP0 clocks      */
       NULL,                                                         /* DP1 clocks      */
       NULL,                                                         /* DP2 clocks      */
       NULL,                                                         /* DP3 Clocks      */
       NULL,                                                         /* RSSC Clocks     */
      (MDP_DynamicClockList*) &sMDSSDynamicClock_9xx,                /* Clocks that can be changed dynamically */
      (MDPDeviceCapsType *)   &sMDSSDeviceCaps_91x,                  /* Display Core Capabilities */
       NULL,                                                         /* Demura pipe config */
      (MDPDSCCapsType *)      &sMDSSDSCCaps_9xx,                     /* DSC Core Caps */
  };
  
  /* MDP External resource list for MDSS 80x
  */
  const MDP_ExtClockResourceList sMDP90xExtClockResources =
  {
      (MDPExternalClockEntry*)    &sDSI0ExtClocks_9xx,               /* DSI0 Ext clocks      */
      (MDPExternalClockEntry*)    &sDSI1ExtClocks_9xx,               /* DSI1 Ext clocks      */
      (MDPExternalClockEntry*)    &sDSI1SharedSourceExtClocks_9xx,   /* DSI shared clocks for dual DSI */
      (MDPExternalClockEntry*)    &sDSI0ExtClocks_9xx,               /* DSI0 Ext clocks      */
  };

 /* Display resource list - MDSS 8.0.0
 */
 const DisplayResourceList sDisplayMDP90xResources =
 {
    (MDP_ResourceList*)            &sMDP90xResources,                /* MDP Resources               */
    (MDP_ExtClockResourceList*)    &sMDP90xExtClockResources,        /* MDP Ext Resources           */
 };
 
 /* Display resource list - MDSS 9.1.0
 */
 const DisplayResourceList sDisplayMDP91xResources =
 {
    (MDP_ResourceList*)            &sMDP91xResources,                /* MDP Resources               */
    (MDP_ExtClockResourceList*)    &sMDP90xExtClockResources,        /* MDP Ext Resources           */
 };

 /* MDSS resource list for MDSS 9.2.0
 */
 const MDP_ResourceList sMDP92xResources =
 {
    (MDPPowerDomainEntry*)  &MDSS9xxPowerDomain,                   /* Power domain                           */
    (MDPClockEntry*)        &DispCcXoClk_9xx,                      /* DISP_CC clocks                         */
    (MDPClockEntry*)        &MDSSClocks_9xx,                       /* MDP clocks                             */
    NULL,                                                          /* DSI0 clocks                            */
    NULL,                                                          /* DSI1 clocks                            */
    (MDPClockEntry*)        &DP0Clocks_92x,                        /* DP0 clocks                             */
    (MDPClockEntry*)        &DP1Clocks_92x,                        /* DP1 clocks                             */
    (MDPClockEntry*)        &DP2Clocks_92x,                        /* DP2 clocks                             */
    (MDPClockEntry*)        &DP3Clocks_92x,                        /* DP3 clocks                             */
    (MDPClockEntry*)        &RsccClocks_92x,                       /* RSCC clocks                            */
    (MDP_DynamicClockList*) &sMDSSDynamicClock_9xx,                /* Clocks that can be changed dynamically */
    (MDPDeviceCapsType *)   &sMDSSDeviceCaps_92x,                  /* Display Core Capabilities              */
    NULL,                                                          /* Demura pipe config                     */
    (MDPDSCCapsType *)      &sMDSSDSCCaps_92x,                     /* DSC Core Caps */
 };

 /* Display resource list - MDSS 9.2.0
 */
 const DisplayResourceList sDisplayMDP92xResources =
 {
    (MDP_ResourceList*)            &sMDP92xResources,                /* MDP Resources                        */
     NULL,                                                           /* MDP Ext Resources                    */    
 };

 /*=========================================================================
       Top level Tables
 ==========================================================================*/

/* Resource list for MDSS 9xx
*/
const MDP_HwMinorFamilyResourceList asHardwareFamilyMinor9xx[RES_MAX_FAMILY_MINOR] = {
  {MDSS_DEVICE_VERSION_09_00, (DisplayResourceList*)&sDisplayMDP90xResources},              /* MDSS Family 9.0.x, Kailua */
  {MDSS_DEVICE_VERSION_09_01, (DisplayResourceList*)&sDisplayMDP91xResources},              /* MDSS Family 9.0.x, Kailua */
  {MDSS_DEVICE_VERSION_09_02, (DisplayResourceList*)&sDisplayMDP92xResources}               /* MDSS Family 9.2.x, Hamoa  */
};


#endif // __MDSSPlatform_9xx_H__

