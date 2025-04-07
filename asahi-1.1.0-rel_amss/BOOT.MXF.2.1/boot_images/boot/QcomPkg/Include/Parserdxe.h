/** @file Parserdxe.h
 
  UEFI Environment Dxe code for registering FBPT event handlers
  For all Qualcomm specific initializations
 
  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All rights reserved.
 
**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
 
 
 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 03/14/23   sj       Initial revision
=============================================================================*/

#include <Protocol/EFIParser.h>

/* Open Parser for the buffer passed in
 * If ParseOptions pointer is NULL then default values are used (ie # is comment char)
 *
 * @param
 * @param[IN]  Buffer     : Buffer containing the data to be parsed
 * @param[IN]  BufferSize : Size of the data in buffer
 * @param[IN]  Popt       : ParseOptions (Only comment char is supported now)
 * @param[OUT] Pd         : Ptr to parser descriptor
 *
 * @retval EFI_SUCCESS      Parser opened successfully.
 * */
EFI_STATUS
EFI_Parser_OpenParser(
    IN  UINT8*             Buffer,
    IN  UINT32             BufferSize,
    IN  ParseOptionsType*  Popt OPTIONAL,
    OUT INTN*              Pd
   );
   
/*
 * Close the parser context and release the resources.
 *
 * @param[IN] Pd  : Parser Descriptor
 *
 * @retval EFI_SUCCESS      Parser closed successfully.
 * */
EFI_STATUS
EFI_Parser_CloseParser (
    IN  INTN            Pd
    );
    
/*
 * Enumerate the key values by getting callback for each item. Optional Section string can
 * be specified to get the values only for the specified section. If the Section pointer is
 * NULL then all values with their Section string is returned.
 *
 * @param[IN] Pd            : Parser Descriptor
 * @param[IN] Section       : Optional Section, if specified, only key-value pairs for the specified section are returned.
 * @param[IN] CallBackFunc  : Callback function to get the callback with all the enumerated values.
 *
 * @retval EFI_SUCCESS      
 * */
EFI_STATUS
EFI_Parser_EnumKeyValues(
    IN  INTN                      Pd,
    IN  UINT8*                    Section   OPTIONAL,
    IN  KeyValueCallBackFuncType  CallBackFunc
    );
    
/*
 * Re-open parser for repeated further processing
 *
 * @param[IN] Pd            : Parser Descriptor
 *
 * @retval EFI_SUCCESS      Parser re-opened successfully.
 * */
EFI_STATUS
EFI_Parser_ReopenParser(
	IN INTN Pd
	);