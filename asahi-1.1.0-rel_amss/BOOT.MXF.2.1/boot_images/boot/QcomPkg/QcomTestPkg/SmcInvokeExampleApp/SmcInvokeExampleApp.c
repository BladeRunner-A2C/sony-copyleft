/***********************************************************
  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
************************************************************/
/*=============================================================================
                               EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/18/23   shl     Initial revision
=============================================================================*/
#include <Uefi.h>
#include <stdio.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/TestInterface.h>
#include <Library/QcomBaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/EFIScm.h>
#include <Protocol/EFIShmBridge.h>
#include <Include/scm_qsee_interface.h>
#include <Library/EfiFileLib.h>
#include <Library/QcomLib.h>

#include <object.h>
#include "IClientEnv.h"
#include "CAppLoader.h"
#include "IAppLoader.h"
#include "IAppController.h"

#include "ISMCIExampleApp.h"

#include "ICallbackObjectExample.h"
#include "CCallbackObjectExample_open.h"


#define IF_NOT_ZERO_EXIT(xx)                                              \
  do                                                                      \
  {                                                                       \
    if ((xx) != 0 )                                                       \
    {                                                                     \
      AsciiPrint("........ %a:%d Failed!  ret = 0x%x  \n", __FUNCTION__, __LINE__, (xx));   \
      goto Exit;                                                          \
    }                                                                     \
  } while(0)


#define IF_TRUE_EXIT(xx)                                                  \
  do                                                                      \
  {                                                                       \
    if ((xx))                                                             \
    {                                                                     \
      AsciiPrint("........ %a:%d Failed!\n", __FUNCTION__, __LINE__);     \
      goto Exit;                                                          \
    }                                                                     \
  } while(0)


#define MAX_PATH_SIZE   64
#define MAX_FVS         6

STATIC  CHAR8  TaFileName[]    = "smcinvoke_example_ta64.mbn";
STATIC  CHAR8  SvcTaFileName[] = "smcinvoke_example_svc_ta64.mbn"; 

STATIC  QCOM_SCM_PROTOCOL       *ScmProtocol       = NULL;
STATIC  EFI_SHMBRIDGE_PROTOCOL  *ShmBridgeProtocol = NULL;


/**
 *  load image from FV
**/
static EFI_STATUS ReadImage( VOID **image, UINTN *imageSize, CHAR8 *fileNmae )
{
   EFI_STATUS      Status       = EFI_LOAD_ERROR;
   EFI_OPEN_FILE  *File         = NULL;
   VOID           *Buf          = NULL;
   UINTN           BufSize      = 0;
   UINT32          i; 
   CHAR8           FilePath[MAX_PATH_SIZE] = {0};

   //searching the file from FVs
   for( i = 0; i <= MAX_PATH_SIZE; i++ )
   {
      snprintf( FilePath, sizeof(FilePath), "fv%d:\\%s", i, fileNmae );

      File = EfiOpen( FilePath, EFI_FILE_MODE_READ, EFI_SECTION_RAW );
      if( File != NULL )
      {
         AsciiPrint("TA file %a  is found.\r\n", FilePath );
         break;
      }
   }

   IF_TRUE_EXIT( File == NULL);

   Status = EfiReadAllocatePool (File, (VOID**)&Buf, &BufSize);

   EfiClose( File );

   IF_NOT_ZERO_EXIT( Status );

   Status = EFI_LOAD_ERROR;

   IF_TRUE_EXIT( Buf == NULL );
   IF_TRUE_EXIT( BufSize == 0 );

   AsciiPrint( "BufSize =%d \n", BufSize );

   *image = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &BufSize, ShmBridgeBootSvcData);
   IF_TRUE_EXIT( *image == NULL );

   *imageSize = BufSize;
   CopyMem( *image, Buf, BufSize);

   FreePool( Buf );

   return EFI_SUCCESS;

Exit:

   return Status;
}


/**
 *  Free image from shared bridge pool
**/
void FreeImage( VOID **image, UINTN *imageSize )
{ 
   if( *image != NULL )
      ShmBridgeProtocol->ShmBridgeFree(ShmBridgeProtocol, *image);

   *image     = NULL;  
   *imageSize = 0;

   return;
}


static const char *stringFromHash(const uint8_t *inHash, size_t inHashLen)
{
  static char outString[(2 * ISMCIExampleApp_HASH_SHA256_SIZE) + 1];
  size_t index = 0;

  for (size_t i = 0; i < inHashLen; i++) {
    index += snprintf(outString + index, sizeof(outString) - index, "%02X", inHash[i]);
  }

  return outString;
}


/* The implementation for this example resides primarily in CSMCIExampleApp and
 * CAdder. This example demonstrates the usage of TA services. Services allow a
 * caling TA to use an interface exposed by a service TA, so long as the calling
 * TA has the privilege to access it defined in its SConscript. */
static int32_t run_service_example(Object appObj)
{
   int32_t ret = Object_OK;
  
   ret = ISMCIExampleApp_serviceExample(appObj);
   return ret;
}


static int32_t run_hash_example(Object appObj)
{
   int32_t ret = Object_OK;

   const char stringToHash[] = "String to hash";

   /* We use -1 for the size, since we don't want to hash the trailing '\0' character. */
   const size_t strLen = sizeof(stringToHash) - 1;

   uint8_t digest[ISMCIExampleApp_HASH_SHA256_SIZE];
   const size_t digestLen = sizeof(digest);
   size_t digestLenOut = 0;
   const char *printHashString;

   ret = ISMCIExampleApp_computeHash(  appObj, 
                                      &stringToHash, 
                                       strLen, 
                                       ISMCIExampleApp_HASH_SHA256, 
                                      &digest, 
                                       digestLen, 
                                      &digestLenOut );

   IF_TRUE_EXIT( Object_isERROR(ret));
   IF_TRUE_EXIT( digestLenOut == 0);

   printHashString = stringFromHash( digest, digestLenOut );
   AsciiPrint( "Hash: %a\n", printHashString );

Exit:

   return ret;
}

static int32_t run_shared_memory_example(Object appObj)
{
   int32_t  ret          = Object_OK;
   void    *buf          = NULL;
   size_t   bufSize      = 0;
   char     c[]          = "A random number from the CA ";
   Object   sharedMemObj = Object_NULL;

   bufSize = sizeof(c);

   buf = ShmBridgeProtocol->ShmBridgeAllocate(ShmBridgeProtocol, &bufSize, ShmBridgeBootSvcData);
   IF_TRUE_EXIT( buf == NULL );
  
   /* Put a string into this memory. Generate a "random" number for the message. */
   snprintf( (char *)buf, bufSize, " %s ", c );

   /* Print the original buffer content */
   AsciiPrint( " Original buffer %a \n ", (char *)buf );

   /* Call MemObj_new which will create a memory object that represents our dma buffer, with
    * read/write permission - allowing the TA-side to write data to the shared memory.
    */
   ret = ScmProtocol->ScmCreateMemObj( ScmProtocol, (void *)buf, bufSize, 6, (void *)&sharedMemObj );
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT( Object_isNull(sharedMemObj)); 

   AsciiPrint( "Calling ISMCIExampleApp_sharedMemoryExample \n" );
 
   /* Call into ISMCIExampleApp and pass it our memory object. */
   ret = ISMCIExampleApp_sharedMemoryExample( appObj, sharedMemObj );
   if (Object_isERROR(ret)) {
      AsciiPrint("ISMCIExampleApp_sharedMemoryExample failed with error: %d!\n", ret);
   }

   /* Ensure that the last character of what we're about to print is \0. */
   ((char *)buf)[bufSize - 1] = '\0';

   /* Print the buffer to show that the TA has modified it. */
   AsciiPrint( " Modified buffer %a \n ", (char *)buf );

Exit:

   if( buf )
      ShmBridgeProtocol->ShmBridgeFree( ShmBridgeProtocol, buf );
 
   Object_ASSIGN_NULL( sharedMemObj );

   return ret;
}


static int32_t run_callback_object_example( Object appObj )
{
  int32_t  ret         = Object_OK;
  Object   callbackObj = Object_NULL;

  ret = CCallbackObjectExample_open( &callbackObj );
  IF_TRUE_EXIT( Object_isERROR(ret));

  static const char msg[] = "Local object invocation.";

  /* callbackObj resides in the client side. Invoke it locally first. */
  ret = ICallbackObjectExample_print(callbackObj, msg, sizeof(msg));
  IF_TRUE_EXIT( Object_isERROR(ret));

  /*
   * Now pass the local object as an argument in an ISMCIExampleApp invocation. 
   * The TA will make an invocation on the callback object.
   */
  ret = ISMCIExampleApp_callbackObjectExample(appObj, callbackObj);
  IF_TRUE_EXIT( Object_isERROR(ret));

Exit:

  Object_ASSIGN_NULL(callbackObj);
  return ret;
}


/**
 *  This function demonstrates how to open a TA using SMCInvoke APIs.
**/
int32_t run_smcinvoke_ta_example()
{
   EFI_STATUS   Status    = EFI_SUCCESS;
   VOID        *image     = NULL;
   UINTN        imageSize = 0;

   int32_t      ret             = Object_OK;    
   Object       clientEnv       = Object_NULL;
   Object       appLoader       = Object_NULL;
   Object       appController   = Object_NULL;
   Object       appController_1 = Object_NULL;
   Object       appObj          = Object_NULL;
                                                                                                                                              
   Status = ScmProtocol->ScmGetClientEnv(ScmProtocol, &clientEnv);
   IF_NOT_ZERO_EXIT( Status );
   IF_TRUE_EXIT( Object_isNull(clientEnv)); 
                                                                                         
   ret = IClientEnv_open(clientEnv, CAppLoader_UID, &appLoader);
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT(Object_isNull(appLoader));
  
   // read main TA from Firmware Volume
   Status = ReadImage( (VOID**)&image, &imageSize, TaFileName );
   IF_NOT_ZERO_EXIT( Status ); 

   // load main TA in TZ
   ret = IAppLoader_loadFromBuffer(appLoader, image, imageSize, &appController);
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT(Object_isNull(appController));

   FreeImage( (VOID**)&image, &imageSize );
 
   // read service TA from Firmware Volume, this service TA will be called by main TA inside TZ
   Status = ReadImage( (VOID**)&image, &imageSize, SvcTaFileName );
   IF_NOT_ZERO_EXIT( Status ); 
            
   // load service TA in TZ                                                                      
   ret = IAppLoader_loadFromBuffer(appLoader, image, imageSize, &appController_1);
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT(Object_isNull(appController_1));

   FreeImage( (VOID**)&image, &imageSize );

   // get main TA object
   ret = IAppController_getAppObject(appController, &appObj);
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT( Object_isNull(appObj));

   // no need to get service TA object, because there is no service TA API call from UEFI
   // in this example. Service TA API call is made inside TZ from main TA.

   /* Run our examples. */
   ret = run_service_example(appObj);
   if( ret == 0 )
      AsciiPrint("\n run_service_example passes \n\n");
   else
      AsciiPrint("\n run_service_example fails %d \n\n", ret );

   ret = run_hash_example( appObj);
   if( ret == 0 )
      AsciiPrint("\n run_hash_example passes \n\n");
   else
      AsciiPrint("\n run_hash_example fails %d \n\n", ret );

   ret = run_callback_object_example( appObj);
   if( ret == 0 )
      AsciiPrint("\n run_callback_object_example passes \n\n");
   else
      AsciiPrint("\n run_callback_object_example fails %d \n\n", ret );

   ret = run_shared_memory_example( appObj);
   if( ret == 0 )
      AsciiPrint("\n run_shared_memory_example passes \n\n");
   else
      AsciiPrint("\n run_shared_memory_example fails %d \n\n", ret );

Exit:

   // unload tz app
   ret = IAppController_unload(appController);
   if( ret != 0 )
      AsciiPrint("\n IAppController_unload() fails %d \n\n", ret);

   ret = IAppController_unload(appController_1);
   if( ret != 0 )
      AsciiPrint("\n IAppController_unload() fails %d \n\n", ret);

   Object_release( appController );
   Object_release( appController_1 );
   Object_release( appLoader );
   Object_release( clientEnv );

   appController   = Object_NULL;
   appController_1 = Object_NULL;
   appLoader       = Object_NULL;
   clientEnv       = Object_NULL;

   return ret;
}


EFI_STATUS
EFIAPI
UefiMain (
   IN EFI_HANDLE        ImageHandle,
   IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
   EFI_STATUS  Status = EFI_LOAD_ERROR;

   Status = gBS->LocateProtocol (&gQcomScmProtocolGuid, NULL, (VOID**)&ScmProtocol);
   IF_NOT_ZERO_EXIT(Status);

   Status = gBS->LocateProtocol(&gEfiShmBridgeProtocolGuid, NULL, (VOID **)&ShmBridgeProtocol);
   IF_NOT_ZERO_EXIT(Status);
   
   // load commonlib, just in case it is not loaded
   ScmProtocol->ScmSendCommand( ScmProtocol,
                                APP_QUERY_EMBEDDED_IMAGES_SUPPORT_CMD,
                                NULL,
                                NULL,
                                0,
                                NULL,
                                0);

   TEST_START("SmcInvokeExampleApp");
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");
   run_smcinvoke_ta_example();
   AsciiPrint("\n ------------------------------------------------------------------------  \n\n");

   TEST_STOP("SmcInvokeExampleApp");

Exit:

   return Status;
}


