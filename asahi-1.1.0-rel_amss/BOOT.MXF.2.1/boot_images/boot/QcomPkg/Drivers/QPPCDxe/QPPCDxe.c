/**
  @file  QPPCDxe.c
  @brief QPPC Protocol for UEFI.
*/
/*==============================================================================
 Copyright 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
==============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 12/08/22   arajashe  Added QPPC device ID

=============================================================================*/

/*===========================================================================
  INCLUDE FILES
===========================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIQPPC.h>
#include <QPPCTypes.h>
#include "DALSys.h"

/*=========================================================================
      Function Prototypes
==========================================================================*/

EFI_STATUS EFI_RegisterCallback (
  IN  EFI_QPPC_PROTOCOL   *This,
  IN  PQPPC_CB             pfnCB,
  IN  QPPC_CBData          nData
);

EFI_STATUS EFI_GetConfig (
  IN  EFI_QPPC_PROTOCOL     *This,
  IN  QPPCQueryType          eQuery,
  IN  QppcQueryParam         Param,
  OUT QppcQueryResultType   *pnResult
);

EFI_STATUS EFI_SetConfig (
  IN  EFI_QPPC_PROTOCOL     *This,
  IN  QPPCConfigType         eConfig,
  IN  QppcConfigParam        Param,
  OUT uint32_t              *pnResult
);


/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the QPPC Protocol GUID.
*/
extern EFI_GUID gEfiQppcProtocolGuid;

extern QPPCResult QPPC_DriverInit( void );
extern void QPPC_BIST();
extern QPPCResult QPPC_SetConfig( QPPCConfigType eConfig, QppcConfigParam Param, uint32_t  *pnResult);
extern QPPCResult QPPC_GetConfig (QPPCQueryType         eQuery, QppcQueryParam        Param,  QppcQueryResultType   *pnResult);
extern QPPCResult QPPC_RegisterCallback (PQPPC_CB 				pfnCB, QPPC_CBData 			Data);

/*=========================================================================
      Data Declarations
==========================================================================*/

// QPPC Public Protocol
static EFI_QPPC_PROTOCOL QPPCProtocol =
{
   EFI_QPPC_PROTOCOL_VERSION_2,
   EFI_RegisterCallback, 
   EFI_GetConfig,
   EFI_SetConfig,
};

/*=========================================================================
      Functions
==========================================================================*/
static 
EFI_STATUS
QPPC_MAP_EFI_ERROR (
  QPPCResult eResult
)
{
	EFI_STATUS status;
	
	if (eResult == QPPC_SUCCESS)
	{
		status = EFI_SUCCESS;
	}
	else if (eResult != QPPC_ERROR_UNSUPPORTED)
	{
		status = EFI_UNSUPPORTED;
	}
	else
	{
		status = EFI_ERROR(QPPC_ERROR); 
	}
	
	return status;
}		
/**
  Description is at EFIQPPC.h
**/
EFI_STATUS EFI_RegisterCallback (
  IN  EFI_QPPC_PROTOCOL   *This,
  IN  PQPPC_CB             pfnCB,
  IN  QPPC_CBData          nData
)
{
	QPPCResult eResult;
	
	eResult = QPPC_RegisterCallback(pfnCB, nData);
	
	return QPPC_MAP_EFI_ERROR(eResult);
}

/**
  Description is at EFIQPPC.h
**/
EFI_STATUS EFI_GetConfig (
  IN  EFI_QPPC_PROTOCOL     *This,
  IN  QPPCQueryType          eQuery,
  IN  QppcQueryParam         Param,
  OUT QppcQueryResultType   *pnResult
)
{
	QPPCResult eResult;
	
	eResult = QPPC_GetConfig(eQuery, Param, pnResult);
	
	return QPPC_MAP_EFI_ERROR(eResult);
}

/**
  Description is at EFIQPPC.h
**/
EFI_STATUS EFI_SetConfig (
  IN  EFI_QPPC_PROTOCOL     *This,
  IN  QPPCConfigType         eConfig,
  IN  QppcConfigParam        Param,
  OUT uint32_t              *pnResult
)
{
	QPPCResult eResult;
	
	eResult = QPPC_SetConfig(eConfig, Param, pnResult);
	
	return QPPC_MAP_EFI_ERROR(eResult);
}

/**
  QPPC DXE driver entry point.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
QPPCDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_HANDLE  handle = NULL;
  EFI_STATUS  status;

  /*
    Init DALSys
    DALSYS_InitMod is needed to initlize the gpDALSYSFncPtr otherwise all DALSYS_* api (like  DALSYS_SyncCreate, DALSYS_LogEvent, etc) will stop working
    becouse of check DALMOD_CHECK_UNINIT(gpDALSYSFncPtr, DAL_ERROR) in QcomPkg/Library/DALModEnvLib/DALModEnv.c file
  */
  DALSYS_InitMod(NULL);
  
  /* Initialize QPPC Library */
  QPPC_DriverInit();

  /* Run BIST */
  //QPPC_BIST();

   // Publish the EFIQPPC Protocol
   status = gBS->InstallMultipleProtocolInterfaces(
				&handle,
				&gEfiQppcProtocolGuid,
				(void **)&QPPCProtocol,
				NULL );

  return status;
}