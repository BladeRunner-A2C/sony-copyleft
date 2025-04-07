/** @file SerialPortShLibEnhanced.c
   
  Contains Serial IO Shared Library loader and access functions.

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
  03/30/23   cg     enhanced lib initial revision
=============================================================================*/
#include "Library/SerialPortShLib.h"

VOID
DisableSynchronousSerialPortIO (VOID)
{
  SerialPortControl (SIO_CONTROL_SYNCHRONOUS_IO, FALSE);
}

VOID
EnableSerialOut (VOID)
{
  SerialPortControl (SIO_CONTROL_PORTOUT, TRUE);
}