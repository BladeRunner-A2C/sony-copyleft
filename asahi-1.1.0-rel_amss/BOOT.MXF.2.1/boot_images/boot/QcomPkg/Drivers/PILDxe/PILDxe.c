/*===============================================================================
  Copyright (c) 2017-2018,2021-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         PILDxe.c
  DESCRIPTION:    
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  03/30/23   cm         Allow Non Fatal configs in Auto to not Assert nor Panic
  01/10/23   rk         Updated EFI_PIL_PROTOCOL to have PIL_PROTOCOL_VERSION_V5.
  08/08/22   cm         Added change to detemernine PilConfigIndex
                        added api to return pil cfg struct, PilInitCfgByUnicodeName
                        Version V3 should be the API - PilInitCfgByUnicodeName
                        Added Protocol version V4
  12/08/21   cm         Added Version 3
  09/10/20   yw         add two APIS, ShutdownPilImage and GetSubsysCfgCpyById
  06/14/17   yw         initial version

================================================================================*/

#include <Uefi.h>
#include <pil_tz.h>
#include <pil_loader.h>
#include <BootConfig.h>
#include <Protocol/EFIPIL.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <ImageLoadInfo.h>
#include <Library/QcomLib.h>
#include <Library/DebugLib.h>
#include <Library/ParserLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TargetResetLib.h>
#include <Protocol/EFIDALSYSProtocol.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>

/*
    the last error code of EFI and PIL status
*/
EFI_STATUS  gLastEfiError;
PIL_STATUS  gLastPilError;
/*
    AutoStartList[] contains the list of SubsysID which is processed/loaded
    at PIL loading
*/
extern UINT32     AutoStartImageNum;
extern PIL_SUBSYS_CFG_TYPE*  AutoStartList[];

extern UINT32 RetailImageNum;
extern UINT32 AutoStartImageNum;

/**
  process/load images in AutoStartList.

  @param                          none

  @return EFI_SUCCESS           The function completed successfully.
  @return other                    Some error occurred.
**/
STATIC EFI_STATUS ProcessAutoImages()
{
    EFI_STATUS Status = EFI_SUCCESS; 
    PIL_STATUS Ret;
    UINT32 Idx;
    
    for(Idx=0; Idx<AutoStartImageNum; Idx++)
    {
        PIL_SUBSYS_CFG_TYPE *Cfg = AutoStartList[Idx];
        Ret = PilProcessImageExt(Cfg);
        if (Ret != PIL_SUCCESS)
        {
		   if((Cfg->Version >= PIL_SUBSYS_CFG_VERSION_V5) &&
               (Cfg->NonFatal == TRUE))
             continue;
           else {
             Status = EFI_LOAD_ERROR;
             break;
           }
        }
    }
    
    return Status;
}

/**
  read cfg (i.e. ImageLoadInfoBase & ImageLoadInfoSize) of image load info 
  from cfg file.

  @param                          none

  @return EFI_SUCCESS           The function completed successfully.
  @return other                    Some error occurred.
**/

STATIC EFI_STATUS InitImageLoadInfoRegion()
{
    return InitImageList("IMAGE_LOAD_INFO_REGION");
}

/**
  process/load subsys image of given configure

  @param  cfg     [in]          configure infomation of the subsys to be processed

  @return EFI_SUCCESS           The function completed successfully.
  @return other                    Some error occurred.
**/

STATIC EFI_STATUS EFI_PIL_ProcessPilImageExt(
    IN PIL_SUBSYS_CFG_TYPE* cfg
    )
{
    PIL_STATUS PilRet = PilProcessImageExt(cfg);
    if (PilRet == PIL_SUCCESS) {
        PIL_WARN_CFG(cfg, "Boot subsys, Done\n");
    }
    else {
        PIL_WARN_CFG(cfg, "Failed to boot subsys\n");
    }
    
    return (PIL_SUCCESS == PilRet)? EFI_SUCCESS: EFI_LOAD_ERROR;
}

/**
  process/load subsys image of given name

  @param  subsys_name [in]      name of the subsys to be processed

  @return EFI_SUCCESS           The function completed successfully.
  @return other                    Some error occurred.
**/

STATIC EFI_STATUS EFI_PIL_ProcessPilImage(
    IN CHAR16 *subsys_name
    )
{    
    PIL_STATUS PilRet = PilProcessImage(subsys_name);
    return (PilRet == PIL_SUCCESS || PilRet == PIL_SUBSYS_RUNNING)? EFI_SUCCESS: EFI_LOAD_ERROR;

}

STATIC EFI_STATUS EFI_PIL_AuthELFFVImageFromBuffer(
   VOID *Buffer,
   VOID** FvImageBase
   )
{
   return (PIL_SUCCESS == PilLoadAndAuthELFFVImagefromBuffer(Buffer, FvImageBase))? EFI_SUCCESS: EFI_LOAD_ERROR;
}

STATIC EFI_STATUS EFI_PIL_ShutdownPilImage(
    IN UINT32 SubsysId
    )
{
    return (PIL_SUCCESS == PilShutdownImage(SubsysId))? EFI_SUCCESS: EFI_LOAD_ERROR;
}

STATIC EFI_STATUS EFI_PIL_GetLoadedImageCfgCpyById(
    IN UINT32 SubsysId,
    OUT PIL_SUBSYS_CFG_TYPE* CfgPtr
    )
{
    PIL_STATUS PilStatus;
    PIL_SUBSYS_CFG_TYPE* Cfg;
    
    if (CfgPtr==NULL)
        return EFI_INVALID_PARAMETER;
    
    PilStatus = GetLoadedSubsysCfgById(SubsysId, &Cfg);
    if (PilStatus==PIL_SUCCESS)
        CopyMem(CfgPtr, Cfg, sizeof(*Cfg));
    
    return (PIL_SUCCESS == PilStatus)?EFI_SUCCESS:EFI_NOT_FOUND;
}

/**
  find the cfg in cfg file and return pil cfg struct.

  @param  cfg     [in]          unique FwName of the subsys
  @param  cfg     [out]         return pil cfg struct
  
  @retval NULL                  fail to add the cfg
  @return EFI_SUCCESS           The function completed successfully.

**/


STATIC EFI_STATUS EFI_PIL_PilInitCfgByUnicodeName(
    IN CHAR16 *subsys_name,
    OUT PIL_SUBSYS_CFG_TYPE* CfgOut
    )
{
    PIL_SUBSYS_CFG_TYPE* Cfg;
    
    if (CfgOut==NULL)
        return EFI_INVALID_PARAMETER;
    
    Cfg = PilInitCfgByUnicodeName(subsys_name);
	if (Cfg == NULL) {
		PIL_WARN("No configuration found for %s\n", subsys_name);
		return PIL_SUBSYS_NOT_SUPPORTED;
	}
	else
		CopyMem(CfgOut, Cfg, sizeof(*Cfg));
    
    return (Cfg != NULL)?EFI_SUCCESS:EFI_NOT_FOUND;
	
}


/**
  PIL protocol defination
  
**/
static EFI_PIL_PROTOCOL PILProtocol =
{
   EFI_PIL_PROTOCOL_VERSION_V5,
   EFI_PIL_ProcessPilImage,
   EFI_PIL_ProcessPilImageExt,
   EFI_PIL_AuthELFFVImageFromBuffer,
   EFI_PIL_ShutdownPilImage,
   EFI_PIL_GetLoadedImageCfgCpyById,
   EFI_PIL_PilInitCfgByUnicodeName,
};


/**
  The Entry Point for PIL module. 

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurred when executing this entry point.

**/
 
EFI_STATUS EFIAPI 
PILDxeEntryPoint
(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
)
{
    
    EFI_HANDLE handle = NULL;
    EFI_STATUS Status;
    
    if (boot_from_flashless() == TRUE)
        return EFI_UNSUPPORTED;
    
    /*helps determine the uefipil file in PIL_CONFIG_FILES*/
    UINT8 index = boot_from_network()?1:0;
  	SetPilConfigIndex(index);
    Status = InitImageLoadInfoRegion();
    if (EFI_ERROR(Status)) {
        PIL_ERROR("Failed to get info of image load info region in IMEM\n");
        return Status;
    }
                    
    /* initiate retail list which contains subsys allowed to 
       be processed by PIL in RETAIL product  */
    Status = InitImageList("RETAIL");
    if (EFI_ERROR(Status)) {
        PIL_ERROR("Failed to initiate retail list\n");
        return Status;
    }
    else
        PIL_INFO("Retail list added %d images\n", RetailImageNum);
    
    
    /* initiate auto_boot list which contains subsys processed 
       by PIL by default */ 
    Status = InitImageList("AUTO");
    if (EFI_ERROR(Status)) {
        PIL_ERROR("Failed to initiate auto list\n");
        return Status;
    }
    else
        PIL_INFO("Auto list added %d images\n", AutoStartImageNum);

    Status = InitializeImageLoadInfoTable();
    if (EFI_ERROR(Status)) {
        PIL_ERROR("Failed to Initialize Image Load info Table, reason :%r\n", Status);
        return Status;
    }
    
    Status = ProcessAutoImages();
    // assert if auto start image is failed to load in retail
    if (EFI_ERROR(Status)) {
        if (RETAIL) {
            PIL_ERROR("Auto processing of uefipil.cfg failed. Calling target panic\n");
            TargetPanic();
        }
        else {
            ASSERT_EFI_ERROR(Status);
            ASSERT_FAIL_EFI_RETURN(0, EFI_DEVICE_ERROR, EFI_DEVICE_ERROR);
        }
    }
	Status = UpdateImageLoadInfoVar();
	if (EFI_ERROR(Status)) {
	  PIL_ERROR("UpdateImageLoadInfoVar failed, reason: %r\n", Status);
	}    
    Status = gBS->InstallMultipleProtocolInterfaces(
                    &handle,
                    &gEfiPilProtocolGuid,
                    (VOID **)&PILProtocol,
                    NULL );
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        ASSERT_FAIL_EFI_RETURN(0, EFI_DEVICE_ERROR, EFI_DEVICE_ERROR);
    }
    
    return Status;
}
