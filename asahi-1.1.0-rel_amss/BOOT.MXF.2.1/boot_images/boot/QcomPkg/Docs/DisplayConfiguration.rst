.. -*- coding: utf-8 -*-

.. /*=============================================================================
     Readme file for configuring display PCDs.
   
     Copyright (c) 2019-2021 Qualcomm Technologies, Inc.
     All Rights Reserved.
     Confidential and Proprietary - Qualcomm Technologies, Inc.
   
   =============================================================================*/


.. _DisplayConfiguration:

===================
DisplayConfigration
===================


Overview
--------

The readme file describes how to configure the display PCD options.

The PCDs should be configured in the platform core dsc file(QcomPkg/SocPkg/[TARGET]/Common/Core.dsc.inc).

All of the supported display PCDs are listed as below:

- gQcomTokenSpaceGuid.PcdBacklightLevel
- gQcomTokenSpaceGuid.PcdDisplayForceSwRenderer
- gQcomTokenSpaceGuid.PcdFrameBufMaxRes
- gQcomTokenSpaceGuid.PcdPrimaryFlags
- gQcomTokenSpaceGuid.PcdUnderflowColor
- gQcomTokenSpaceGuid.PcdPresentationMode
- gQcomTokenSpaceGuid.PcdDisplayChargerPolicy
- gQcomTokenSpaceGuid.PcdSupportedDisplays


Display PCD description
-----------------------

Default backlight level::

  Configuration     : Default backlight level
  PCD Name          : gQcomTokenSpaceGuid.PcdBacklightLevel
  Description       : This PCD key indicates the percentage(1-100%) of default backlight level when booting UEFI.
  Default Value     : 60
  Supported Values  :
                      - Integer from 1-100.


Display force sw renderer::

  Configuration     : Display force sw renderer
  PCD Name          : gQcomTokenSpaceGuid.PcdDisplayForceSwRenderer
  Description       : This PCD key is used to enable/disable SW renderer mode.
  Default Value     : FALSE
  Supported Values  :
                      - FALSE
                      - TRUE


Framebuffer max allocation by resolution::

  Configuration     : Framebuffer max allocation by resolution
  PCD Name          : gQcomTokenSpaceGuid.PcdFrameBufMaxRes
  Description       : This PCD key indicates the limitation FB allocation by resolution.
                      The resolution width and height is swapped for portrait panels.
                      OEM doesn't need to handle portrait vs landscape differently.
  Default Value     : 0
  Supported Values  :
  
                     - 0 : 5K    (5120x2160)
                     - 1 : 4K    (4096x2160)
                     - 2 : UHD   (3840x2160)
                     - 3 : WQHD  (2560x1440)
                     - 4 : WUXGA (1920x1280)
                     - 5 : FHD   (1920x1080)
                     - 6 : HD    (1280x720)


Display primary flags::

  Configuration     : Display primary flags
  PCD Name          : gQcomTokenSpaceGuid.PcdPrimaryFlags
  Description       : Integer defining with each bit representing a feature that can be enabled or disabled on the primary panel.
                      Multiple flags can be combined to enable/disable multiple features.
                      All other values are invalid or not supported.
                      Refer to 80-NB116-2 "DISPLAY DRIVERS (ACPI AND XML) USER GUIDE" for details.
  Default Value     : 0x00000000
  Supported Values  :
                      - 0x00000001 : Reserved.
                      - 0x00000002 : Reserved. 
                      - 0x00000004 : Reserved.
                      - 0x00000008 : Reserved.
                      - 0x00000010 : Reserved.
                      - 0x00000100 : Reserved.
                      - 0x00000200 : Reserved.
                      - 0x00000400 : Reserved.
                      - 0x00000800 : Reserved.
                      - 0x00001000 : This flag is used to swap pixel data between DSI 0 and DSI 1.
                      - 0x00002000 : Reserved.
                      - 0x01000000 : This flag disables seamless splash.
                      - 0x02000000 : This flag enables pingpong split.
                      - 0x04000000 : This flag skip sending PPS command.
                      - 0x08000000 : Reserved.
                      - 0x10000000 : This flag enables PFS feature.


Underflow color::

  Configuration     : Underflow color
  PCD Name          : gQcomTokenSpaceGuid.PcdUnderflowColor
  Description       : This PCD key is used to set underflow color in ARGB format with 10bit per component.
  Default Value     : 0x00000000 (Black)
  Supported Values  :
                      - 0x00 to 0x3FF for each component, e.g. 0x000003FF (Blue).


Display presentation mode::

  Configuration     : Display presentation mode
  PCD Name          : gQcomTokenSpaceGuid.PcdPresentationMode
  Description       : This PCD key is used to set the default GOP render mode, this only applies 
                      when the PcdFrameBufMaxRes is smaller than the physical display resolution.
  Default Value     : 0
  Supported Values  :
                      - 0 : Letterbox to screen.
                      - 1 : Fit to screen.
                      - 2 : Crop to fit.


SecondaryDisplay presentation mode::

  Configuration     : SecondaryDisplay presentation mode
  PCD Name          : gQcomTokenSpaceGuid.PcdSecondaryPresentationMode
  Description       : This PCD key is used to set the default GOP render mode for secondary display, 
                      this only applies when the PcdFrameBufMaxRes is smaller than the physical display resolution.
  Default Value     : 0
  Supported Values  :
                      - 0 : Letterbox to screen.
                      - 1 : Fit to screen.
                      - 2 : Crop to fit.


Display charger policy::

  Configuration     : Display charger policy
  PCD Name          : gQcomTokenSpaceGuid.PcdDisplayChargerPolicy
  Description       : This PCD key is used to set the charger policy used for display.
  Default Value     : 0
  Supported Values  :
                      - 0 : Turn on backlight in off charging mode.
                      - 1 : Adjust backlight according to charger power status, turn off backlight in off charging mode.


Supported displays::

  Configuration     : Supported displays
  PCD Name          : gQcomTokenSpaceGuid.PcdSupportedDisplays
  Description       : Displays to be enabled in DisplayDxe, each bit corresponds to a display device.
  Default Value     : 0
  Supported Values  : combination of bit values
                      - Bit 0 : MDP_DISPLAY_PRIMARY
                      - Bit 1 : MDP_DISPLAY_SECONDARY
                      - Bit 2 : MDP_DISPLAY_EXTERNAL
                      - Bit 3 : MDP_DISPLAY_EXTERNAL2
                      - Bit 4 : MDP_DISPLAY_EXTERNAL3
                      - Bit 5 : MDP_DISPLAY_EXTERNAL4
                      - Bit 6 : MDP_DISPLAY_EXTERNAL5
                      - Bit 7 : MDP_DISPLAY_EXTERNAL6

