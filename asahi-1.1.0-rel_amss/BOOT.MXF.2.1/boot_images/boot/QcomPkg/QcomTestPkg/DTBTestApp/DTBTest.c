/** @file DTBTest.c

  Test DTB functionality

  Copyright (c) 2021, 2023 Qualcomm Technologies Inc. All rights reserved.
  Portions Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/13/23   tmt     Update test to print lookup times for each node
 03/24/21   tmt     Update to use new Protocol wrapper library
 01/28/21   ai      Sample DTB usecase
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/TestInterface.h>
#include <Protocol/EFIDtbExtn.h>
#include <Library/DTBExtnUEFILib.h>
#include <libfdt.h>
#include <Library/QcomBaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include "comdef.h"
#include "DTBExtnLib.h"

#define Log_BUF_Size 128
#define LIM 80
/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
CHAR8 *names[LIM];
INT32 top = -1;
INT32 pop(CHAR8 **name)
{
  if (top != -1) {
    *name = names[top];
  }
  return top--;
}
INT32 push(CHAR8 *name)
{
  if (top != LIM - 1) {
    names[top + 1] = name;
  }
  return top++;
}
EFI_STATUS
EFIAPI
DTB_All_Nodes()
{
  INT32 ret_value = 0;
  fdt_node_handle node;
  INT32 subnode = 0;
  CONST CHAR8 *name;
  INT32 len;
  CHAR8 dbuf[Log_BUF_Size];
  CHAR8 *dup = NULL;

  UINT64 bts, ets;
  CHAR8 *currname = "/";

  while (ret_value > -1)
  {
    bts = GetTimerCountus();
    ret_value = fdt_get_node_handle(&node, NULL, currname);
    ets = GetTimerCountus();
  //Ret = FdtGetNodeHandle(&Node, "/sw/boot");
    DEBUG((EFI_D_ERROR, "lookup time[%d]..node[%a]\n", (ets - bts), currname));

    fdt_for_each_subnode(subnode, node.blob, node.offset)
    {
      name = fdt_get_name(node.blob, subnode, &len);
      if (NULL == name) {
		  DEBUG((EFI_D_ERROR, "fdt_get_name returned NULL [%d]\n", len));
		  goto exit;
	  }
      strlcpy(dbuf, currname, Log_BUF_Size);
      if (strcmp(currname, "/") != 0)
        strlcat(dbuf, "/", Log_BUF_Size);
      strlcat(dbuf, name, Log_BUF_Size);
      dup = AllocatePool(Log_BUF_Size);
      if (dup == NULL)
      {
        DEBUG((EFI_D_ERROR, "failed memory allocation\n"));
        goto exit;
  }
      strlcpy(dup, dbuf, Log_BUF_Size);
      ret_value = push((char *)dup);
  //Ret = FdtGetUint32PropList(&Node, "config", (VOID *)&DTBConfig, sizeof(DTBConfig));
      if (ret_value == LIM - 1)
      {
        DEBUG((EFI_D_ERROR, "overflow\n"));
    //DEBUG((EFI_D_ERROR, "FdtGetUint32PropList: %r\n", Status));
        goto exit;
  }
    }
    ret_value = pop(&currname);
  }

  for (int i=0; i<LIM; i++) {
    if (names[i] != NULL) {
      FreePool(names[i]);
    }
  }
  ret_value = 0;

exit:
	if (ret_value)
		return ret_value;
	else
		return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DTBTestMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status = EFI_DEVICE_ERROR;

  TEST_START("DTBTest");
  Status = DTB_All_Nodes();
  return Status;
}
