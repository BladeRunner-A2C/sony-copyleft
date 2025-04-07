#ifndef __BUTTONSDTPARSER_H__
#define __BUTTONSDTPARSER_H__

/** @file
ButtonsDtParser.h

  This file contains the function definitions for Buttons Device Tree

  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved

**/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when          who     what, where, why
----------    ---     ----------------------------------------------------------
28-09-2022    gan     file created
===========================================================================*/
#define BTN_DT_GPIO_CONFIG_ITEM_SIZE   6

#define FDT_RETURNED_SUCCESS    0
#define DTB_LINE_BUF_SIZE       0x80

typedef enum
{
  BUTTON_DT_NODE_GPIO_CONFIG,
  BUTTON_DT_NODE_PF_KEY_MAP_CONFIG,
  BUTTON_DT_NODE_INVALID,
}ButtonDtNodeType;

typedef struct
{
  UINT32 ButtonGpioCfgCount;    
  UINT32 *ButtonGpioCfg;
}ButtonDtGpioConfig;

typedef struct
{
  UINT32 PfKeyMapsCount;    
  UINT32 *PfKeyMapsConfig;
}ButtonDtPfKeyMapsConfig;

VOID*
ButtonDtGetNode(ButtonDtNodeType Node);

#endif   /*__BUTTONSDTPARSER_H__*/
