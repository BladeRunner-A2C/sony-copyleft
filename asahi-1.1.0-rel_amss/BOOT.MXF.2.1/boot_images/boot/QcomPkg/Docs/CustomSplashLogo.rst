.. -*- coding: utf-8 -*-

.. /*=============================================================================
     Readme file for setting up custom splash logo in UEFI.
   
     Copyright (c) 2016, 2019, 2021 Qualcomm Technologies, Inc. 
     All rights reserved.
     Confidential and Proprietary - Qualcomm Technologies, Inc.
   
   =============================================================================*/


.. _CustomSplashLogo:

================
CustomSplashLogo
================


Supported Image formats
-----------------------

- 8-bit BMP
- 24-bit BMP
- 32-bit BMP
- 8-bit indexed BMP

Compressed bitmaps are not supported.

.. note::

   Since the firmware volume is already compressed, any BMPs being stored inside will also be compressed automatically.



Logo File Naming
----------------

Logos should be named as logo1.bmp, logo2.bmp, logo3.bmp ...

The default configuration of the driver is to use logo1.bmp as the filename for the default logo, but this can be overwritten using the steps below.


Adding the logo file to the firmware volume (FV)
------------------------------------------------

Add logo files into Fv and select which logo should be used for display.

How to add logo bitmap
^^^^^^^^^^^^^^^^^^^^^^

1) Adding logo bitmap to the FV compilation.

   Put logo bitmap such as logo1.bmp into QcomPkg\Logo\Common folder.

2) Injecting the logo bitmap in to the firmware volume (FV).

   User could choose to save logo bitmap in MainFv or ImageFv.
   
   .. note::
   
      The MainFv may have limited space so larger logos should move to the ImageFv.

   a. How to enable MainFv
   
      Add the entry for the logo1.bmp in QcomPkg\SocPkg\[TARGET]\Common\Core.fdf::

        FILE FREEFORM = 8f2a919c-35f3-4cb5-8541-689f58c5f018 {
            SECTION UI = "logo1.bmp"
            SECTION RAW = QcomPkg/Logo/Common/logo1.bmp
        }

   b. How to enable ImageFv
   
      i. Set "EnableDisplayImageFv = 0x1" in QcomPkg\SocPkg\[TARGET]\Common\uefiplat.cfg.

      ii. Add the entry for the logo1.bmp in QcomPkg\SocPkg\[TARGET]\[LAA|LAB|WP]\ImageFv.fdf.inc::

           FILE FREEFORM = 8f2a919c-35f3-4cb5-8541-689f58c5f018 {
               SECTION UI = "logo1.bmp"
               SECTION RAW = QcomPkg/Logo/Common/logo1.bmp
           }

      iii. Flash imagefv after compiling the build.

           ``fastboot flash imagefv QcomPkg\SocPkg\[TARGET]\Bin\[LAA|LAB|WP]\[DEBUG|RELEASE]\imagefv.elf``

           .. note::

              For other OSes this would be through mass storage or the emmcdl tool.


Mapping the display to the logo image file
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Update property in QcomPkg\SocPkg\[TARGET]\Common\uefiplat.cfg.

1) Primary display:

   Set "PrimaryLogoIndex = 1" to use logo1.bmp.

2) Secondary display:

   Set "SecondaryLogoIndex = 2" to use logo2.bmp, or set other index to use other logo.
   
   It is not mandatory to have unique logo bmp file per display, a previously used index may be reused.

.. note::

   If these sections are missing then the default is to use logo1.bmp.

