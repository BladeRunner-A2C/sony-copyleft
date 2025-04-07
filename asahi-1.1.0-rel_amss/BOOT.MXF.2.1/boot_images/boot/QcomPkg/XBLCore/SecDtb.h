/** @file SecDtb.h

  Header file for DTB function in UEFI SEC

  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 04/20/23   rbv      Initial revision
=============================================================================*/
#include <Library/DTBExtnLib.h>
#include <Library/DTBDefs.h>

#ifndef _SEC_DTB_H_
#define _SEC_DTB_H_

typedef fdt_node_handle  FdtNodeHandle;

INT32
SecFdtGetNodeHandle(
  FdtNodeHandle* Node,
  CHAR8* Name
  );

#endif /* _SEC_DTB_H_ */
