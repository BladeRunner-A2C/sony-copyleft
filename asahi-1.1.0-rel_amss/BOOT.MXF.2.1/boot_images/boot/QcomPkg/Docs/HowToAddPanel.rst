.. -*- coding: utf-8 -*-

.. /*=============================================================================
     Guideline for adding new panel
   
     Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
     All Rights Reserved.
     Confidential and Proprietary - Qualcomm Technologies, Inc.
   
   =============================================================================*/


.. _HowToAddPanel:

=============
HowToAddPanel
=============


Introduction
------------

UEFI can read the panel config from 3 places::

  Drvier C code:
  sPhysicalPanelConfigTable table in file QcomPkg\SocPkg\<Chip>\Library\MDPPlatformLib\MDPPlatformLibPanelConfig.c
  This is the physical panel that UEFI can support.

  mainfv:
  QcomPkg\Settings\Panel\PanelSimConfig.csv in mainfv, mainfv is a fv that built into UEFI binary.
  This simulation panel config.

  imagefv_b:
  PanelSimConfig.csv in imagefv_b, imagefv_b is a partition, user can easily overwrite partition with fastboot command.
  This is simulation panel config.

.. Note::

   The simulation panels are only for development purposes and not for production.


Below is the description for how a panel config is selected in the form of pseudocode::

  PanelName = DetectFromCDT

  if (fastboot override) then
     PanelName = OverrideName

  if (PanelName in MDPPlatformLibPanelConfig.c::sPhysicalPanelConfigTable)
  {
      Setup physical panel config
  }
  else if (PanelName in mainFv->PanelSimConfig.csv)
  {
      Setup simulation panel config using mainFv->PanelSimConfig.csv
  }
  else if (PanelName in imagefv_b->PanelSimConfig.csv)
  {
      Setup simulation panel config using imaegfv_b->PanelSimConfig.csv
  }
  else
  {
      Passing PanelName to kernel
  }



Adding physical panel
---------------------

1) Prepare panel xml file, add the xml file into QcomPkg\SocPkg\<Chip>\Common\Core.fdf
2) In QcomPkg\SocPkg\<Chip>\Library\MDPPlatformLib\MDPPlatformLibPanelConfig.c, add new line config into sPhysicalPanelConfigTable table.

   An example as below::

     {"sharp_4k_dsc_cmd", "Panel_sharp_4k_dsc_cmd.xml", "qcom,mdss_dsi_sharp_4k_dsc_cmd:",  &sModeConfig[MDP_MODE_DUALDSI], &sHwConfig[HW_CONFIG_DEFAULT]},

   Some description as below::
   
     1st column is panel name
     2nd column is the xml config that this panel is using
     3rd column is the DT label string that will be passed to kernel
     4th column is the display mode this panel is using, check DisplayModeType in QcomPkg\Include\Library\DisplayUtils.h
         to see what mode can be selected. Different mode can be combined, below example shows that this panel is using
         dual dsi interface and also pingpong split is enabled:
         DISP_MODE_DUAL_DSI|DISP_MODE_PING_PONG_SPLIT
     
         sModeConfig is hardcoded table that contains mostly used mode, so when adding a new mode for a panel,
         we first check whether an existed config can be found in sModeConfig table, otherwise need to add new mode config into sModeConfig table.
     
     5th column is the HW config for this panel. HW config includes: GPIO, power/reset sequence, peripheral power,
         brightness control. sHwConfig table is hardcoded table that contains mostly used HW configs. So when adding a
         new HW config for a panel, we first check whether an existed config can be found in sHwConfig table, otherwise need to add new HW config into sHwConfig table.

3) In QcomPkg\SocPkg\<Chip>\Library\MDPPlatformLib\MDPPlatformLibPanelCommon.h, modify below to map default panel name to specific platform::

     #define DISPLAY_PANEL_QRD          "r66451_120hz_fhd_dsc_cmd"
     #define DISPLAY_PANEL_MTP          DISPLAY_PANEL_QRD
     #define DISPLAY_PANEL_CDP_V01      "sharp_qhd_plus_dsc_cmd"
     #define DISPLAY_PANEL_CDP_V23      DISPLAY_PANEL_QRD

   DISPLAY_PANEL_QRD is default panel name for QRD

   DISPLAY_PANEL_MTP is default panel name for MTP

   DISPLAY_PANEL_CDP_V01/DISPLAY_PANEL_CDP_V23 is default panel name for specific version of CDP



Adding default simulation panel
-------------------------------

1) Modify QcomPkg\Settings\Panel\PanelSimConfig.csv, add a new line that contain simulation panel config into this
   file, example as below::

     Name,                           DTLabel,                                        KernelModeInfo  
     r66451_120hz_fhd_dsc_cmd_cphy,  "qcom,mdss_dsi_r66451_fhd_plus_cphy_cmd:",      "config2:timing2:"

   .. Note::
   
      Name column does not need quote, Label and KernelModeInfo column needs surrounded by quote.

   When panel name from "fastboot oem select-display-panel" matches name of a line in PanelSimConfig.csv, that line will be parsed.

   Both DTLabel and KernelModeInfo will be parsed out and considered as pure text. DTLabel stands for "Device Tree Label",
   this string will be used by kernel for device tree related operations,  while KernelModeInfo is some more additional
   info about this panel that will be passed to kernel, like config number and timing number in this example. User can add more text
   into KernelModeInfo if more infomation needs pass to kernel. When passing to kernel, the quotes will be removed from both
   DTLabel and KernelModeInfoKernel, then ModeInfo will be appended after DTLabel, and the new generated string will be passed to kernel.

   In this example finally, qcom,mdss_dsi_r66451_fhd_plus_cphy_cmd:config2:timing2: will be passed to kernel.



Adding external simulation panel
--------------------------------

1) Modify PanelSimConfig.csv inside QcomPkg\Settings\Panel\PanelConfig.img, PanelConfig.img is a fat16 image with blank csv file inside.

   a. mkdir tmp
   
   b. sudo mount PanelConfig.img tmp && cd tmp
   
   c. Add a new line in PanelSimConfig.csv, below is an example::
   
        r66451_120hz_fhd_dsc_cmd_cphy,  "qcom,mdss_dsi_r66451_fhd_plus_cphy_cmd:", "config2:timing2:"

   d. cd .. && sudo umount tmp
   
2) Flash PanelConfig.img

   a. fastboot flash imagefv_b PanelConfig.img

Comparing to "Adding default simulation panel", the benefit of "Adding external simulation panel" is we can avoid
recompiling UEFI.

