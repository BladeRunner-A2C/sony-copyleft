.. -*- coding: utf-8 -*-

.. /*=============================================================================
     Readme file for configuring display PCDs.
   
     Copyright (c) 2021 Qualcomm Technologies, Inc.
     All Rights Reserved.
     Confidential and Proprietary - Qualcomm Technologies, Inc.
   
   =============================================================================*/


.. _DisplayFastbootCmds.rst:

===================
DisplayFastbootCmds
===================


Overview
--------

The readme file describes how to run display fastboot commands.

All of the supported display fastboot commands are listed as below:

- fastboot oem select-display-panel none
- fastboot oem select-display-panel <Panel Name>
- fastboot oem select-display-panel prim0:<Panel Name>
- fastboot oem select-display-panel prim1:<Panel Name>
- fastboot oem select-display-panel prim2:<Panel Name>
- fastboot oem select-display-panel sec0:<Panel Name>
- fastboot oem select-display-panel sec1:<Panel Name>
- fastboot oem select-display-panel sec2:<Panel Name>
- fastboot oem select-display-panel prim:<Panel Name>

  fastboot oem select-display-panel :sec:<Panel Name>
  
- fastboot oem select-display-panel prim<0/1/2>:<Panel Name>

  fastboot oem select-display-panel :sec<0/1/2>:<Panel Name>
  
- fastboot oem select-display-panel <Panel Name>:cs<0/1>
- fastboot oem select-display-panel <Panel Name>:skip


Display Fastboot Commands Description
-------------------------------------

Command1::

  Command Name   : fastboot oem select-display-panel none
  Description    : This command is used to disable UEFI display and use kernel panel settings.

Command2::

  Command Name   : fastboot oem select-display-panel <Panel Name>
  Description    : This command is used to select the specific panel for primary display.

Command3::

  Command Name   : fastboot oem select-display-panel prim0:<Panel Name>
  Description    : This command is used to select the specific panel for primary display,
                   display is set to on state and cont-splash is on.
                   0 is optional to select panel, same as "fastboot oem select-display-panel prim:<Panel Name>".

Command4::

  Command Name   : fastboot oem select-display-panel prim1:<Panel Name>
  Description    : This command is used to select the specific panel for primary display,
                   display is set to on state and cont-splash is off.

Command5::

  Command Name   : fastboot oem select-display-panel prim2:<Panel Name>
  Description    : This command is used to select the specific panel for primary display,
                   display is set to off state, but still pass the panel command line to kernel.

Command6::

  Command Name   : fastboot oem select-display-panel sec0:<Panel Name>
  Description    : This command is used to select the specific panel for secondary display,
                   display is set to on state and cont-splash is on.
                   0 is optional to select panel, same as "fastboot oem select-display-panel sec:<Panel Name>".

Command7::

  Command Name   : fastboot oem select-display-panel sec1:<Panel Name>
  Description    : This command is used to select the specific panel for secondary display,
                   display is set to on state and cont-splash is off.

Command8::

  Command Name   : fastboot oem select-display-panel sec2:<Panel Name>
  Description    : This command is used to select the specific panel for secondary display,
                   display is set to off state, but still pass the panel command line to kernel.

Command9::

  Command Name   : fastboot oem select-display-panel prim:<Panel Name>
                   fastboot oem select-display-panel :sec:<Panel Name>
  Description    : These commands are used to select the specific panels for dual display.

Command10::

  Command Name   : fastboot oem select-display-panel prim<0/1/2>:<Panel Name>
                   fastboot oem select-display-panel :sec<0/1/2>:<Panel Name>
  Description    : These commands are used to select the specific panels for dual display,
                   each panel of dual display can be controlled independently.

Command11::

  Command Name   : fastboot oem select-display-panel <Panel Name>:cs<0/1>
  Description    : This command is used to control cont-splash to on/off state for specific panel,
                   cs0: cont-splash off, cs1: cont-splash on.

Command12::

  Command Name   : fastboot oem select-display-panel <Panel Name>:skip
  Description    : This command is used to skip bootloader process for specific panel.
