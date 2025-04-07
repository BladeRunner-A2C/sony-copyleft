/** @file
ButtonsDtParser.c

This file contains the implementation of dtb parsing

Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
EDIT HISTORY

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
--------    ---      ----------------------------------------------------------
28-09-2022  gan      file created
=============================================================================*/
#include <Base.h>
#include <stdio.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/OfflineCrashDump.h>
#include "comdef.h"
#include "DTBExtnLib.h"
#include "ButtonsDtParser.h"
#include "DALSys.h"


static ButtonDtGpioConfig      *ButtonGpioDtConfig;
static ButtonDtPfKeyMapsConfig *PfKeyMapDtConfig;

static char* NodeStrArr[] = 
{
  [BUTTON_DT_NODE_GPIO_CONFIG]        = "/soc/buttons/buttons-config",
  [BUTTON_DT_NODE_PF_KEY_MAP_CONFIG]  = "/soc/buttons/platform-key-maps",
};

static VOID
AllocateMem(void **ppMem, UINT32 DwSize)
{
  DALSYS_Malloc(DwSize, ppMem);

  DALSYS_memset(*ppMem, 0, DwSize);
}

static VOID
FreeMem(void **pMem)
{
  if(*pMem != NULL)
  {
    DALSYS_Free(*pMem);

    *pMem = NULL;
  }
}

static VOID 
ButtonDtErrorCheck(EFI_STATUS Status, char* Msg)
{
  if(EFI_ERROR(Status) && (Msg != NULL)) 
  {
    DEBUG(( EFI_D_ERROR, "Buttons DT Parser Err: %s\r\n", Msg ));
  } 
}

/*parse buttons config node*/
static VOID*
ButtonDtParseGpioConfig(UINT32 PropId)
{
  static BOOLEAN Parsed = FALSE;
  fdt_node_handle hNode = {0};
  UINT32 ConfigSize = 0; 
  int FdtRet = FDT_RETURNED_SUCCESS;
  EFI_STATUS Status = EFI_SUCCESS;

  if(Parsed)
  {
    return ButtonGpioDtConfig;
  }

  AllocateMem((VOID**)&ButtonGpioDtConfig, sizeof(ButtonDtGpioConfig));
  FdtRet = fdt_get_node_handle(&hNode, NULL, NodeStrArr[PropId]);
  if(FdtRet == FDT_RETURNED_SUCCESS)
  {  
    FdtRet = fdt_get_prop_size(&hNode, "gpio-configs", &ConfigSize);
    Status |= FdtRet;

    if((ConfigSize > 0) && (FdtRet == FDT_RETURNED_SUCCESS))
    {
      ButtonGpioDtConfig->ButtonGpioCfgCount = ConfigSize / (BTN_DT_GPIO_CONFIG_ITEM_SIZE * sizeof(UINT32)); //divide by 8 since there are 8 members per entry
      
      AllocateMem((VOID**)&ButtonGpioDtConfig->ButtonGpioCfg, ConfigSize);  
      FdtRet = fdt_get_uint32_prop_list(&hNode, "gpio-configs", ButtonGpioDtConfig->ButtonGpioCfg, ConfigSize);
      if (FdtRet != FDT_RETURNED_SUCCESS)
      {
        FreeMem((VOID**)&ButtonGpioDtConfig->ButtonGpioCfg);
      }
      Status |= FdtRet;
    }
    ButtonDtErrorCheck(Status, "gpio-configs");

    Parsed = TRUE;
  }
  else
  {
    FreeMem((VOID**)&ButtonGpioDtConfig);
  }

  return ButtonGpioDtConfig;
}

/*parse platform key maps config node*/
static VOID*
ButtonDtParsePfKeyMapsConfig(UINT32 PropId)
{
  static BOOLEAN Parsed = FALSE;
  fdt_node_handle hNode = {0};
  UINT32 ConfigSize = 0; 
  int FdtRet = FDT_RETURNED_SUCCESS;
  EFI_STATUS Status = EFI_SUCCESS;

  if(Parsed)
  {
    return PfKeyMapDtConfig;
  }

  AllocateMem((VOID**)&PfKeyMapDtConfig, sizeof(ButtonDtPfKeyMapsConfig));  
  FdtRet = fdt_get_node_handle(&hNode, NULL, NodeStrArr[PropId]);
  if(FdtRet == FDT_RETURNED_SUCCESS)
  {  
    FdtRet = fdt_get_prop_size(&hNode, "key-maps", &ConfigSize);
    Status |= FdtRet;

    if((ConfigSize > 0) && (FdtRet == FDT_RETURNED_SUCCESS))
    {
      PfKeyMapDtConfig->PfKeyMapsCount = ConfigSize / sizeof(uint32);

      AllocateMem((VOID**)&PfKeyMapDtConfig->PfKeyMapsConfig, ConfigSize);  
      FdtRet = fdt_get_uint32_prop_list(&hNode, "key-maps", PfKeyMapDtConfig->PfKeyMapsConfig, ConfigSize);
      if (FdtRet != FDT_RETURNED_SUCCESS)
      {
        FreeMem((VOID**)&PfKeyMapDtConfig->PfKeyMapsConfig);
      }
      Status |= FdtRet;
    }
    ButtonDtErrorCheck(Status, "key-maps");

    Parsed = TRUE;
  }
  else
  {
    FreeMem((VOID**)&PfKeyMapDtConfig);
  }

  return PfKeyMapDtConfig;
}

VOID*
ButtonDtGetNode(ButtonDtNodeType Node)
{
  VOID* NodeProp = NULL;

  switch(Node)
  {
    case BUTTON_DT_NODE_GPIO_CONFIG:       
      NodeProp = (VOID*)ButtonDtParseGpioConfig(Node);
      break;

    case BUTTON_DT_NODE_PF_KEY_MAP_CONFIG:       
      NodeProp = (VOID*)ButtonDtParsePfKeyMapsConfig(Node);
      break;

    default:
      break;
  }

  return NodeProp;
}
