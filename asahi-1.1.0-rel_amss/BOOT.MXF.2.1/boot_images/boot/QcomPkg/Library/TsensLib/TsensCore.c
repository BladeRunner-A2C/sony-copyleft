/*============================================================================
  FILE:         TsensCore.c

  OVERVIEW:     Implementation of TSENS supporting XBL core.

  DEPENDENCIES: None

                Copyright (c) 2014, 2016, 2019 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2023-03-14  pd   FR81674: Remove Non Mission mode  TSENS AP
  2019-04-30  ay   FR:43295 Filled the Tsens_MapHWIORegion function
  2016-03-08  jjo  Memory enhancements.
  2014-07-21  jjo  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "TsensLib.h"
#include "HALtsens.h"
#include "TsensBsp.h"
#include "DALSys.h"
#include "DDIChipInfo.h"
#include "DDIHWIO.h"
#include "DALDeviceId.h"
#include "Target_cust.h"
#include "DTBExtnLib.h"
#include "string.h"
#include "stdio.h"


#define DT_NODE_BUF_SIZE 100
#define TSENS_CFG_BUF_SIZE 32
#define Tsens_NODE_NAME       "/soc/TsensBspSettings"


/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct
{
   uint8 *pucTsensSROTAddr;
   uint8 *pucTsensTMAddr;
   uint32 uChannelEnableMask;
} TsensControllerType;

typedef struct
{
   const TsensBspType *pTsensBsp;
   TsensControllerType *paControllers;
   DalDeviceHandle *phHWIO;
} TsensDevCtxtType;

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
TsensDevCtxtType gTsensDevCtxt = {0};

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
#ifdef TSENS_DT_ENABLE

int tsens_read_controller_cfg(char *node, const TsensControllerCfgType *pCtlCfg)
{
  int ret_value = -1;
  fdt_node_handle hNode;

  ret_value = fdt_get_node_handle(&hNode, NULL, node); /* Getting the node handle for controller specific node */
  if(ret_value)
   {
      return TSENS_ERROR;
   }

  ret_value = fdt_get_prop_values_of_node(&hNode, "DDDWWWWWWWWWWHHBBBBBB", (void *)pCtlCfg, sizeof(TsensControllerCfgType)); /* Getting all the properties of the controller specific node */
  if(ret_value)
   {
      return TSENS_ERROR;
   }
  return TSENS_SUCCESS;
} 


int tsens_read_sensor_cfg(char *node, const TsensSensorCfgType *pSnsrCfg)
{
  int ret_value = -1;
  fdt_node_handle hNode;

  ret_value = fdt_get_node_handle(&hNode, NULL, node); /* Getting the node handle for sensor specific node */
  if(ret_value)
   {
      return TSENS_ERROR;
   }
   
   ret_value = fdt_get_prop_values_of_node(&hNode, "WHHHHHHHBBBB", (void *)pSnsrCfg, sizeof(TsensSensorCfgType)); /* Getting all the properties of the sensor specific node */
   if(ret_value)
   {
      return TSENS_ERROR;
   }
  
  return TSENS_SUCCESS;
}

void *tsens_mem_alloc (uint32 size)
{
	DALResult dalRes = TSENS_SUCCESS;
	void *pTmpBuffer = NULL;

	dalRes = DALSYS_Malloc(size , &pTmpBuffer);
	if ( (DAL_SUCCESS != dalRes) || (NULL == pTmpBuffer) ) {
		dalRes = FALSE;
		goto ON_EXIT;
	}

ON_EXIT:
	return pTmpBuffer;
}

TsensResultType  get_tsens_common_props(TsensBspType *pBsp)
{
	fdt_node_handle tsens_node;
	
	int flag_value = 1;
	
	/*Getting the node handle */
	flag_value = fdt_get_node_handle(&tsens_node, NULL, "/soc/TsensBspSettings/TsensBspType");
	
    if(flag_value)
    {
       return TSENS_ERROR;
    }
    
   
	/*Getting number of controllers */
    flag_value = fdt_get_uint32_prop(&tsens_node, "uNumControllers", (uint32 *)&pBsp->uNumControllers);
    if(flag_value)
    {
       return TSENS_ERROR;
    }
	/*Getting number of Sensors */
    flag_value = fdt_get_uint32_prop(&tsens_node, "uNumSensors", (uint32 *)&pBsp->uNumSensors);
    if(flag_value)
    {
       return TSENS_ERROR;
    }
	/*Getting Sensor Conversion time property */
    flag_value = fdt_get_uint32_prop(&tsens_node, "uSensorConvTime_us", (uint32 *)&pBsp->uSensorConvTime_us);
    if(flag_value)
    {
       return TSENS_ERROR;
    }
	/*Getting CalPoint1 property */
    flag_value = fdt_get_uint32_prop(&tsens_node, "nCalPoint1DeciDegC", (uint32 *)&pBsp->nCalPoint1DeciDegC);
    if(flag_value)
    {
       return TSENS_ERROR;
    }
	/*Getting CalPoint2 property */
    flag_value = fdt_get_uint32_prop(&tsens_node, "nCalPoint2DeciDegC", (uint32 *)&pBsp->nCalPoint2DeciDegC);
    if(flag_value)
    {
       return TSENS_ERROR;
    }
	/*Getting uShift property */
    flag_value = fdt_get_uint32_prop(&tsens_node, "uShift", (uint32 *)&pBsp->uShift);
    if(flag_value)
    {
       return TSENS_ERROR;
    }
	return TSENS_SUCCESS;
}

TsensResultType get_tsens_controller_props(TsensBspType *pBsp)
{
   fdt_node_handle cNode;
   char tsens_ctl_cfg[DT_NODE_BUF_SIZE]; /*To store the node handle of ControllerConfigs property*/
   char temp_buf[DT_NODE_BUF_SIZE]; /*To store the node name of controller specific property*/
   int ret_value = -1;
   uint32 nctls = pBsp->uNumControllers;
   snprintf(tsens_ctl_cfg, DT_NODE_BUF_SIZE, "%s/controllerconfigs", Tsens_NODE_NAME);
   ret_value = fdt_get_node_handle(&cNode, NULL, tsens_ctl_cfg); /*Getting the node handle for ControllerConfigs property in the device tree */
   if(ret_value)
   {
      return TSENS_ERROR;
   }
   
   pBsp->paControllerCfgs = tsens_mem_alloc(nctls* sizeof(TsensControllerCfgType));
   
   if(!pBsp->paControllerCfgs)
   {
       ret_value = -1;
       return TSENS_ERROR;
   }
   DALSYS_memset((void *)pBsp->paControllerCfgs, 0, (nctls * sizeof (TsensControllerCfgType)));
   
   /* Iterating through each of the controller specific device tree nodes */	   
   for(uint32 uController = 0; uController<nctls; uController++)
   {
	   const char* CtlNodeStr = "controllerconfigs_";
	   char walk[TSENS_CFG_BUF_SIZE];
   
	   snprintf(walk, TSENS_CFG_BUF_SIZE, "%s%d", CtlNodeStr, uController); /* Writing the name of the Controller subnode into walk */
   
       snprintf(temp_buf, DT_NODE_BUF_SIZE, "%s/%s", tsens_ctl_cfg, walk);  /* Creating each controller specific node name as per what's in the device tree */
   
       ret_value = tsens_read_controller_cfg(temp_buf, &pBsp->paControllerCfgs[uController]); /* Getting each controller specific node settings */
   if(ret_value)
   {
      return TSENS_ERROR;
   }
   }

   return TSENS_SUCCESS;
}

TsensResultType	 get_tsens_sensor_props(TsensBspType *pBsp)
{
   fdt_node_handle cNode;
   char tsens_sensor_cfg[DT_NODE_BUF_SIZE]; /*To store the node handle of SensorConfigs property*/
   char temp_buf[DT_NODE_BUF_SIZE]; /*To store the node name of sensor specific property*/
   int ret_value = -1;
   uint32 nsensors = pBsp->uNumSensors;
   memset(tsens_sensor_cfg, 0, DT_NODE_BUF_SIZE);
   
   snprintf(tsens_sensor_cfg, DT_NODE_BUF_SIZE, "%s/sensorconfigs", Tsens_NODE_NAME);
   ret_value = fdt_get_node_handle(&cNode, NULL, tsens_sensor_cfg); /*Getting the node handle of SensorConfigs property in the device tree */
   if(ret_value)
   {
      return TSENS_ERROR;
   }
   
   pBsp->paSensorCfgs = tsens_mem_alloc(nsensors * sizeof(TsensSensorCfgType));
   
   if(!pBsp->paSensorCfgs)
   {
       ret_value = -1;
       return TSENS_ERROR;
   }
   DALSYS_memset((void *)pBsp->paSensorCfgs, 0, (nsensors * sizeof (TsensSensorCfgType)));
   
   
   /* Iterating through each of the sensor specific device tree nodes */	
   for(int uSensor = 0; uSensor<nsensors; uSensor++)
   {   
       const char* SensorNodeStr = "sensorconfigs_";
	   char walk[TSENS_CFG_BUF_SIZE];
   
	   snprintf(walk, TSENS_CFG_BUF_SIZE, "%s%d", SensorNodeStr, uSensor); /* Writing the name of the Sensor subnode into walk */
   
       snprintf(temp_buf, DT_NODE_BUF_SIZE, "%s/%s", tsens_sensor_cfg, walk);  /* Creating each controller specific node name as per what's in the device tree */
   
       ret_value = tsens_read_sensor_cfg(temp_buf, &pBsp->paSensorCfgs[uSensor]); /* Getting each controller specific node settings */
	   if(ret_value)
   {
         return TSENS_ERROR;
      }
   }
   return TSENS_SUCCESS;
}


#endif

static uint8* Tsens_MapHWIORegion(uint8 *puPhysical)
{
   DALResult status;
   uint8 *puVirtAddr;

   status = DalHWIO_MapRegionByAddress(gTsensDevCtxt.phHWIO,
                              puPhysical,
                              &puVirtAddr);
   if (status != DAL_SUCCESS)
   {
      return NULL;
   }

   return puVirtAddr;
}

static void Tsens_GetTempInternal(uint32 uController, uint32 uChannel, int32 *pnDeciDegC)
{
   int32 nDeciDegC = 0;
   int32 nDeciDegCTry1;
   int32 nDeciDegCTry2;
   int32 nDeciDegCTry3;
   uint8 *pucTsensTMAddr;
   boolean bValid;

   pucTsensTMAddr = gTsensDevCtxt.paControllers[uController].pucTsensTMAddr;

   bValid = HAL_tsens_tm_GetChannelPrevTemp(pucTsensTMAddr, uChannel, &nDeciDegCTry1);
   if (bValid)
   {
      nDeciDegC = nDeciDegCTry1;
   }
   else
   {
      bValid = HAL_tsens_tm_GetChannelPrevTemp(pucTsensTMAddr, uChannel, &nDeciDegCTry2);
      if (bValid)
      {
         nDeciDegC = nDeciDegCTry2;
      }
      else
      {
         bValid = HAL_tsens_tm_GetChannelPrevTemp(pucTsensTMAddr, uChannel, &nDeciDegCTry3);
         if (bValid)
         {
            nDeciDegC = nDeciDegCTry3;
         }
         else if (nDeciDegCTry1 == nDeciDegCTry2)
         {
            nDeciDegC = nDeciDegCTry1;
         }
         else if (nDeciDegCTry2 == nDeciDegCTry3)
         {
            nDeciDegC = nDeciDegCTry2;
         }
         else
         {
            nDeciDegC = nDeciDegCTry1;
         }
      }
   }

   *pnDeciDegC = (int32)nDeciDegC;

   return;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
#ifdef TSENS_DEVCFG_DISABLE
extern TsensBspType TsensBsp[0];
#endif

TsensResultType Tsens_Init(void)
{
	
   const TsensControllerCfgType *pControllerCfg;
   TsensBspType *pBsp = NULL;
   TsensControllerType *pController;
   uint32 uController;
   DALResult status;
#ifdef TSENS_DEVCFG_DISABLE 
    pBsp = &TsensBsp[0];
	   
	DALSYS_InitMod(NULL);
#endif
#ifdef TSENS_DT_ENABLE
   TsensResultType result;
   DALSYS_InitMod(NULL);
  
   status = DALSYS_Malloc(sizeof(TsensBspType), (void **)&pBsp);

   if(status != DAL_SUCCESS)
   {
      return TSENS_ERROR;
   }
    
   DALSYS_memset((void *)pBsp, 0, sizeof(TsensBspType));
    
    /* Get the BSP */
    
   /* Get the tsens common properties */
   result = get_tsens_common_props(pBsp);
   
   if(result == TSENS_ERROR)
   {
	   return result;
   }
   
   /* Controller Config pulling */
   
   result = get_tsens_controller_props(pBsp);
   
   if(result == TSENS_ERROR)
    {
	   return result;
    }
    
   /* Sensor Config pulling */
   result = get_tsens_sensor_props(pBsp);
   
   if(result == TSENS_ERROR)
   {
	   return result;
   }
#endif

#ifdef TSENS_LEGACY_DEVCFG
   DALSYS_PROPERTY_HANDLE_DECLARE(hTsensBootProperties);
   const char *pszTsensBspPropName = "TSENS_BSP";
   DALSYSPropertyVar propertyVar;


   DALSYS_InitMod(NULL);

   /* Get the BSP */
    status = DALSYS_GetDALPropertyHandleStr("/core/hwengines/tsens", hTsensBootProperties);
    if (status != DAL_SUCCESS)
    {
    	return TSENS_ERROR;
    }
    
    status = DALSYS_GetPropertyValue(hTsensBootProperties,
    									pszTsensBspPropName,
    									0,
    									&propertyVar);
    if (status != DAL_SUCCESS)
    {
    	return TSENS_ERROR;
    }
    
    pBsp = (TsensBspType *)propertyVar.Val.pStruct;
#endif
   gTsensDevCtxt.pTsensBsp = pBsp;

   /* Allocate memory for controller context */
   status = DALSYS_Malloc((pBsp->uNumControllers * sizeof(TsensControllerType)),
                          (void **)&gTsensDevCtxt.paControllers);
   if (status != DAL_SUCCESS || gTsensDevCtxt.paControllers == NULL)
   {
      return TSENS_ERROR;
   }
   
   DALSYS_memset((void *)gTsensDevCtxt.paControllers, 0, (pBsp->uNumControllers * sizeof(TsensControllerType)));
   
   status = DAL_DeviceAttach(DALDEVICEID_HWIO, &gTsensDevCtxt.phHWIO);
 	 	   
   if (status != DAL_SUCCESS)
   {              
      return TSENS_ERROR;
   }

   /* Map physical to virtual addresses */
   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pControllerCfg = &pBsp->paControllerCfgs[uController];
      pController = &gTsensDevCtxt.paControllers[uController];

      pController->pucTsensSROTAddr = Tsens_MapHWIORegion(pControllerCfg->pucTsensSROTPhys);
      if (pController->pucTsensSROTAddr == NULL)
      {
         return TSENS_ERROR;
      }

      pController->pucTsensTMAddr = Tsens_MapHWIORegion(pControllerCfg->pucTsensTMPhys);
      if (pController->pucTsensSROTAddr == NULL)
      {
         return TSENS_ERROR;
      }
   }

   /* Check which sensors are actually enabled */
   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pController = &gTsensDevCtxt.paControllers[uController];

      pController->uChannelEnableMask = HAL_tsens_srot_GetEnabledChannels(pController->pucTsensSROTAddr);
   }

   return TSENS_SUCCESS;
}


TsensResultType Tsens_GetTemp(uint32 uSensor, int32 *pnDeciDegC)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   uint32 uController;
   uint32 uChannel;
   int32 nDeciDegC;

   if (uSensor >= pBsp->uNumSensors)
   {
      return TSENS_ERROR;
   }

   if (pnDeciDegC == NULL)
   {
      return TSENS_ERROR;
   }

   uController = pBsp->paSensorCfgs[uSensor].ucController;
   uChannel = pBsp->paSensorCfgs[uSensor].ucChannel;

   if (((1 << uChannel) & gTsensDevCtxt.paControllers[uController].uChannelEnableMask) == 0)
   {
      return TSENS_ERROR_SENSOR_NOT_AVAILABLE;
   }

   Tsens_GetTempInternal(uController, uChannel, &nDeciDegC);

   *pnDeciDegC = nDeciDegC;

   return TSENS_SUCCESS;
}

TsensResultType Tsens_GetMaxTemp(int32 *pnMaxDeciDegC)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   int32 nMaxDeciDegC = 0;
   DALBOOL bFirst = TRUE;
   uint8 *pucTsensTMAddr;
   uint32 uController;
   int32 nDeciDegC;
   uint32 uSensorID;

   if (pnMaxDeciDegC == NULL)
   {
      return TSENS_ERROR;
   }

   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pucTsensTMAddr = gTsensDevCtxt.paControllers[uController].pucTsensTMAddr;

      HAL_tsens_tm_GetMaxTemp(pucTsensTMAddr, &uSensorID, &nDeciDegC);

      if (bFirst)
      {
         nMaxDeciDegC = nDeciDegC;
         bFirst = FALSE;
      }
      else
      {
         if (nDeciDegC > nMaxDeciDegC)
         {
            nMaxDeciDegC = nDeciDegC;
         }
      }
   }

   *pnMaxDeciDegC = nMaxDeciDegC;

   return TSENS_SUCCESS;
}

