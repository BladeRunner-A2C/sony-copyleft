/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         ParserEnhancedDxe.c
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  03/15/23   sc         Created Enhanced version for non mission mode APIs-initial rev
================================================================================*/
#include <Protocol/EFIParser.h>
#include <Library/KernelLib.h>
#include <Library/ParserLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Parserdxe.h>
extern LockHandle* ParserLockPtr;
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
    OUT INTN*			  Pd
   )
{
	INTN Desc = -1;
	if (Pd==NULL)
		return EFI_INVALID_PARAMETER;
	
	AcquireLock(ParserLockPtr);
	Desc = OpenParser(Buffer, BufferSize, Popt);
	ReleaseLock(ParserLockPtr);
	*Pd = Desc;
	
	return (Desc>=0)?EFI_SUCCESS:EFI_UNSUPPORTED;
}

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
	)
{
	INTN Ret = -1;
	
	AcquireLock(ParserLockPtr);
	Ret = CloseParser(Pd);
	ReleaseLock(ParserLockPtr);
	
	return (Ret>=0)?EFI_SUCCESS:EFI_UNSUPPORTED; 
}

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
	)
{
	INTN Ret = EnumKeyValues(Pd, Section, CallBackFunc);
	return (Ret>=0)?EFI_SUCCESS:EFI_UNSUPPORTED; 
}

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
	)
{
	INTN Ret = ReopenParser(Pd);
	return (Ret>=0)?EFI_SUCCESS:EFI_UNSUPPORTED; 
}

