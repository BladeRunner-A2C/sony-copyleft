/*=============================================================================

  File: MDPClocksBoot.c

  Source file for MDP/Panel clock configuration


  Copyright (c) 2011-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "MDPLib_i.h"
#include "MDSSPlatform_9xx.h"
#include "MDSSPlatform_10xx.h"
#include "MDPSystem.h"
#include "com_dtypes.h"
#include "Clock.h"
/*=========================================================================
      Defines
==========================================================================*/
#define MDP_CLOCK_HZ_TO_KHZ(rate)       (rate/1000)

/* MDP resource list  based on MDP major version.
*/
const MDP_HwMajorFamilyResourceList asHardwareFamilyMajor[RES_MAX_FAMILY_MAJOR] = {
    {NULL},                                                           /* MDSS Family 0xx                      */
    {NULL},                                                           /* MDSS Family 1xx (Badger Family)      */
    {NULL},                                                           /* MDSS Family 2xx                      */
    {NULL},                                                           /* MDSS Family 3xx                      */
    {NULL},                                                           /* MDSS Family 4xx (Napali Family)      */
    {NULL},                                                           /* MDSS Family 5xx (Hana/Poipu Family)  */
    {NULL},                                                           /* MDSS Family 6xx (Kona Family)        */
    {NULL},                                                           /* MDSS Family 7xx (Lahaina Family)     */
    {NULL},                                                           /* MDSS Family 8xx (Waipio Family)      */
    {(MDP_HwMinorFamilyResourceList*)&asHardwareFamilyMinor9xx},      /* MDSS Family 9xx (Kailua Family)      */
    {(MDP_HwMinorFamilyResourceList*)&asHardwareFamilyMinor10xx},     /* MDSS Family 10xx (Lanai Family)      */
};

extern HAL_HW_VersionType  gsVersionInfo;
static ClockHandle gClockHandle;

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetMDPVersionIndex()
**
** DESCRIPTION:
**   Validates the MDP Version
**
** ---------------------------------------------------------------------- */
static MDP_Status GetMDPVersionIndex(MDP_HwPrivateInfo  *psMDPHwPrivateInfo)
{
  MDP_Status   eStatus = MDP_STATUS_OK;

  if (psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion == 0)
  {
    // Default, set SM8650 family i.e MDSS 10.0
    psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion = 10;
    psMDPHwPrivateInfo->sMDPVersionInfo.uMinorVersion = 0;
  }
  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: SetupClock()
**
** DESCRIPTION:
**   Setup a specific clock
**
** ---------------------------------------------------------------------- */
static MDP_Status SetupClock( MDPClockEntry *pClock, UINT32 uFlags)
{
  MDP_Status eStatus = MDP_STATUS_OK;

  if (!gClockHandle)
  {
    if (CLOCK_SUCCESS != Clock_Attach(&gClockHandle, "MDPLib"))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : Clock_Attach failed.");
    }
  }

  if (NULL == pClock)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    ClockIdType uClockId = 0;

    if (pClock->uFlags & MDP_CLOCKFLAG_CDIV)
    {
      if (pClock->pExtSrc)
      {
        MDPExternalClockEntry *pExtSrc = pClock->pExtSrc;

        if (pExtSrc->nSourceDiv)
        {
          if (CLOCK_SUCCESS != Clock_GetId(gClockHandle, pExtSrc->szName, &uClockId))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : Clock(\"%a\") Clock_GetId failed.", pExtSrc->szName);
          }
          else if (CLOCK_SUCCESS != Clock_SetDivider(gClockHandle, uClockId, pExtSrc->nSourceDiv))
          {
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : Clock(\"%a\") Clock_SetDivider failed.", pExtSrc->szName);
          }
        }
      }
    }
    else if (CLOCK_SUCCESS != Clock_GetId(gClockHandle, pClock->szName, &uClockId))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : Clock_GetId failed.");

      eStatus = MDP_STATUS_FAILED;
    }
    else
    {
      // Is this clock an external source?
      if (NULL != pClock->pExtSrc)
      {
        //Setup clock as an external source.
        if (CLOCK_SUCCESS != Clock_SelectExternalSource(gClockHandle,
                                                        uClockId,
                                                        0,                               // FreqHz: 0 -- No voltage control
                                                        pClock->pExtSrc->uClkSource,
                                                        pClock->pExtSrc->nClkDiv,
                                                        pClock->pExtSrc->uClkPLL_M,      // M
                                                        pClock->pExtSrc->uClkPLL_N,      // N
                                                        pClock->pExtSrc->uClkPLL_2D))    // 2*D
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : SelectExternalSource: Clock \"%a\" returned an error!\n", pClock->szName);
        }
      }
      else if (pClock->nFreqHz > 0)
      {
        // Request a specific clock frequency
        if (CLOCK_SUCCESS != Clock_SetFrequency(gClockHandle,
                                                uClockId,
                                                MDP_CLOCK_HZ_TO_KHZ(pClock->nFreqHz),
                                                CLOCK_FREQUENCY_KHZ_AT_LEAST,
                                                NULL))
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : SetFrequency: Clock \"%a\" to %dHz returned an error!\n", pClock->szName, pClock->nFreqHz);
        }
      }

      // Finally enable the clock (regardless of any errors above)
      if(CLOCK_SUCCESS != Clock_Enable(gClockHandle, uClockId))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Clock \"%a\" cannot be enabled!\n", pClock->szName);
      }
    }
  }

  return eStatus;
}
/* ---------------------------------------------------------------------- */
/**
** FUNCTION: StrCompare()
**
** DESCRIPTION:
**   String compare helper function
**
** ---------------------------------------------------------------------- */
static INT32 StrCompare(CHAR8 *szSrc, CHAR8 *szDest)
{
  UINT32 uCount;
  INT32 nResult = 1;

  if ((NULL != szSrc) && (NULL != szDest))
  {
    for (uCount = 0;uCount < MDPLIB_MAX_CLOCK_NAME;uCount++)
    {
      if (szSrc[uCount] != szDest[uCount])
      {
        break;
      }
      else if (('\0' == szSrc[uCount]) && ('\0' == szDest[uCount]))
      {
        nResult = 0;
        break;
      }
      else if (('\0' == szSrc[uCount]) || ('\0' == szDest[uCount]))
      {
        break;
      }
    }
  }

  return nResult;
}
/* ---------------------------------------------------------------------- */
/**
** FUNCTION: FindExtClock()
**
** DESCRIPTION:
**   Find an external clock configuration that matches the current clock
**
** ---------------------------------------------------------------------- */
static MDPExternalClockEntry *FindExtClock(CHAR8 *szClockName, MDPExternalClockEntry *pExtClockList)
{
  UINT32 uCount = 0;
  MDPExternalClockEntry *pExtClock = NULL;

  // If we have an external clock list, search for a matching clock
  if (pExtClockList)
  {
    while ((pExtClockList[uCount].szName[0] != '\0'))
    {
      if (StrCompare(szClockName, (CHAR8*)pExtClockList[uCount].szName) == 0)
      {
        pExtClock = (MDPExternalClockEntry*)&pExtClockList[uCount];
        break;
      }
      uCount++;
    }
  }

  return pExtClock;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ConfigurePowerDomain()
**
** DESCRIPTION:
**   Enabled/disable a specific power domain
**
** ---------------------------------------------------------------------- */
static MDP_Status ConfigurePowerDomain(BOOLEAN bEnable, CHAR8 *szDomain)
{
  MDP_Status   eStatus = MDP_STATUS_OK;
  ClockIdType  uClockPowerDomainId;

  if (!gClockHandle)
  {
    if (CLOCK_SUCCESS != Clock_Attach(&gClockHandle, "MDPLib"))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : Clock_Attach failed.");

      return MDP_STATUS_FAILED;
    }
  }

  if (CLOCK_SUCCESS != Clock_GetId(gClockHandle, szDomain, &uClockPowerDomainId))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib : Clock_GetId failed.");

    return MDP_STATUS_FAILED;
  }

  if (TRUE == bEnable)
  {
    if (CLOCK_SUCCESS != Clock_Enable(gClockHandle, uClockPowerDomainId))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Clock_Enable failed = %a!\n", szDomain);
      eStatus = MDP_STATUS_NO_RESOURCES;
    }
  }
  else if (FALSE == bEnable)
  {
    if (CLOCK_SUCCESS != Clock_Disable(gClockHandle, uClockPowerDomainId))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: Clock_Disable failed = %s!\n",szDomain);
      eStatus = MDP_STATUS_NO_RESOURCES;
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPSetupClocks()
**
** DESCRIPTION:
**   Display Clock configuration.
**
** ---------------------------------------------------------------------- */
MDP_Status MDPSetupClocks(MDPClockTypes eClockType, MDPExternalClockEntry *pExtClockList)
{
  MDP_Status           eStatus = MDP_STATUS_OK;
  MDP_HwPrivateInfo   *psMDPHwPrivateInfo = MDP_GETPRIVATEINFO();

  if ((EFI_PLATFORMINFO_TYPE_VIRTIO  == psMDPHwPrivateInfo->eEFIPlatformInfo) ||
      (EFI_PLATFORMINFO_TYPE_RUMI    == psMDPHwPrivateInfo->eEFIPlatformInfo) ||
      (EFI_PLATFORMINFO_TYPE_UNKNOWN == psMDPHwPrivateInfo->eEFIPlatformInfo))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayLib: For VIRTIO or RUMI, ignore this error and continue\n");
    eStatus = MDP_STATUS_OK;
  }
  else
  {
    MDPClockEntry                  *pClockList = NULL;
    MDP_ResourceList               *pClkResList;

    if (MDP_STATUS_OK !=  MDPGetMDPResourceList(&pClkResList))
    {
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPSetupClocks: MDPGetMDPResourceList failed!\n");
      eStatus = MDP_STATUS_NO_RESOURCES;
    }
    else
    {
      // if we have a valid resource list
      if (NULL != pClkResList)
      {
        // Handle pre-clock events
        switch (eClockType)
        {
        case MDP_CLOCKTYPE_CORE:

          if(NULL != pClkResList->pDispCCXOClk)
          {
            pClockList = (MDPClockEntry*)(pClkResList->pDispCCXOClk);
            while (pClockList->szName[0] != '\0')
            {
              SetupClock(pClockList, 0);
              pClockList++;
            }
          }

          pClockList = (MDPClockEntry*)(pClkResList->pMDPClocks);

          /* Enable the power domain for access in to the MDSS clocks */
          if (NULL != pClkResList->pPowerDomain)
          {
            UINT32                    uCount = 0;

            /* go through the power domain list to enable it in order */
            while (pClkResList->pPowerDomain[uCount].szName[0] != '\0')
            {
              ConfigurePowerDomain(TRUE, (CHAR8*)pClkResList->pPowerDomain[uCount].szName);
              uCount++;
            }
          }
          break;
        case MDP_CLOCKTYPE_DSI0:
          pClockList = (MDPClockEntry*)(pClkResList->pDSI0Clocks);
          break;
        case MDP_CLOCKTYPE_DSI1:
          pClockList = (MDPClockEntry*)(pClkResList->pDSI1Clocks);
          break;
        case MDP_CLOCKTYPE_DP0:
          pClockList = (MDPClockEntry*)(pClkResList->pDP0Clocks);
          break;
        case MDP_CLOCKTYPE_DP1:
          pClockList = (MDPClockEntry*)(pClkResList->pDP1Clocks);
          break;
        case MDP_CLOCKTYPE_DP3:
          pClockList = (MDPClockEntry*)(pClkResList->pEDPClocks);
          break;
	      case MDP_CLOCKTYPE_DP2:
          pClockList = (MDPClockEntry*)(pClkResList->pDP2Clocks);
          break;
        default:
          break;
        }
      }
      // if we have a valid clock list
      if (NULL != pClockList)
      {
        UINT32 uCount = 0;

        while ((pClockList[uCount].szName[0] != '\0'))
        {
          // Override with external clock list (if it is not configured already)
          if (NULL == pClockList[uCount].pExtSrc)
          {
            pClockList[uCount].pExtSrc = FindExtClock((CHAR8*)&pClockList[uCount].szName, pExtClockList);
          }

          // Setup the clock (ignore failures)
          SetupClock(&pClockList[uCount], 0);

          // Go to the next clock
          uCount++;
        }
      }
    }
  }

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPDisableClocks()
**
** DESCRIPTION:
**   Display Clock configuration
**
** ---------------------------------------------------------------------- */
MDP_Status MDPDisableClocks(MDPClockTypes eClockType)
{
  /*Stub function, XBL RAM dump mode won't turn off the display only*/ 
  return MDP_STATUS_OK;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPSetupClockList()
**
** DESCRIPTION:
**   Setup clocks in list.
**
** ---------------------------------------------------------------------- */
MDP_Status MDPSetupClockList(MDPClockEntry *pClockList)
{
  MDP_Status           eStatus             = MDP_STATUS_OK;
  MDP_HwPrivateInfo   *psMDPHwPrivateInfo  = MDP_GETPRIVATEINFO();

  if((EFI_PLATFORMINFO_TYPE_VIRTIO  == psMDPHwPrivateInfo->eEFIPlatformInfo) ||
     (EFI_PLATFORMINFO_TYPE_UNKNOWN == psMDPHwPrivateInfo->eEFIPlatformInfo))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: For VIRTIO, ignore this error and continue\n");
    eStatus = MDP_STATUS_OK;
  }
  else
  {
    if (MDP_STATUS_OK !=  GetMDPVersionIndex(psMDPHwPrivateInfo))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib:GetMDPVersionIndex  failed!\n");
    }
    else if (NULL == pClockList)
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib:MDPSetupClockList  Invalid clock entry list!\n");
    }
    else
    {
      UINT32 uCount = 0;

      while ((pClockList[uCount].szName[0] != '\0'))
      {
        // Create a local copy of the clock entry
        MDPClockEntry sClockEntry = pClockList[uCount];

        if (sClockEntry.pExtSrc)
        {
            MDPExternalClockEntry *pExtSrc = sClockEntry.pExtSrc;

            if (pExtSrc->nSourceDiv)
            {
                /*
                 * SourceDiv start from 0 (divided by 1) at mmss_cc.
                 * Therefore nSourceDiv need to be minus one to match mmss_cc specification
                 */
                // TODO: API not available in boot.xf.2.0 clock driver yet.
                // (void)mClockProtocol->SetExternalSourceDiv(mClockProtocol,  pExtSrc->szName, pExtSrc->nSourceDiv-1);
            }

        }

        // Setup the clock (ignore failures)
        (void)SetupClock(&sClockEntry, 0);

        // Go to the next clock
        uCount++;
      }      
    }
  }

  return MDP_STATUS_OK;
}



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPGetExternalClockList()
**
** DESCRIPTION:
**   Return list of external clocks for this chipset
**
** ---------------------------------------------------------------------- */
MDP_ExtClockResourceList *MDPGetExternalClockList(void)
{
  MDP_HwPrivateInfo               *psMDPHwPrivateInfo  = MDP_GETPRIVATEINFO();
  MDP_HwMajorFamilyResourceList   *pResListMajor;
  MDP_HwMinorFamilyResourceList   *pResListMinor;
  MDP_ExtClockResourceList        *pExtClockResList;
  
  pResListMajor      = (MDP_HwMajorFamilyResourceList*)&(asHardwareFamilyMajor[psMDPHwPrivateInfo->sMDPVersionInfo.uMajorVersion]);
  pResListMinor      = (MDP_HwMinorFamilyResourceList*)&(pResListMajor->pMinorFamily[psMDPHwPrivateInfo->sMDPVersionInfo.uMinorVersion]);
  pExtClockResList   = (MDP_ExtClockResourceList*)pResListMinor->pDisplayPlatfromResources->pExtClockResList;

  return pExtClockResList;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPUpdateDynamicClocks()
** 
** DESCRIPTION:
**   Dynamically change the frequency of a specific clock in case of 
**   resolutoin or refresh rate changes, targeting to minimize the 
**   power consupmtion while meeting the display requirement at the same time
**
** ---------------------------------------------------------------------- */
MDP_Status MDPUpdateDynamicClocks(MDPDynamicClockTypes eClockType, uint32 uNewClkValue)
{
  return MDP_STATUS_OK;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPUpdateDynamicBandwidth()
**
** DESCRIPTION:
**   Update bandwidth value, in case of resolution or refresh rate changes,
**   bandwidth value should be updated.
**
** ---------------------------------------------------------------------- */
MDP_Status MDPUpdateDynamicBandwidth(uint64 uNewBandwidth)
{
  return MDP_STATUS_OK;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPGetMinCoreClock()
**
** DESCRIPTION:
**   Return minimal core clock value
**
** ---------------------------------------------------------------------- */
uint32 MDPGetMinCoreClock(void)
{
  return MDP_MIN_CORE_CLOCK;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPGetExternalClockEntry()
**
** DESCRIPTION:
**   Return list of external clocks for the specified clock type
**
** ---------------------------------------------------------------------- */
MDPExternalClockEntry *MDPGetExternalClockEntry(MDPClockTypes eClockType, bool32 bShared)
{
  MDP_ExtClockResourceList  *pExtClockResList = MDPGetExternalClockList();
  MDPExternalClockEntry     *pExtClockEntry   = NULL;

  if (NULL != pExtClockResList)
  {
    switch (eClockType)
    {
      case MDP_CLOCKTYPE_DSI0:
        pExtClockEntry = pExtClockResList->pDSI0ExtClocks;
        break;
      case MDP_CLOCKTYPE_DSI1:
        if (bShared)
        {
          pExtClockEntry = pExtClockResList->pSharedSourceExtClocks;
        }
        else
        {
          pExtClockEntry = pExtClockResList->pDSI1ExtClocks;
        }
        break;
      case MDP_CLOCKTYPE_DP0:
        pExtClockEntry = pExtClockResList->pDP0ExtClocks;
        break;
      case MDP_CLOCKTYPE_DP1:
        pExtClockEntry = pExtClockResList->pDP1ExtClocks;
        break;
      case MDP_CLOCKTYPE_DP3:
        pExtClockEntry = pExtClockResList->pEDPExtClocks;
        break;
      case MDP_CLOCKTYPE_DP2:
        pExtClockEntry = pExtClockResList->pDP2ExtClocks;
        break;
      default:
        break;
    }
  }

  return pExtClockEntry;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPClockStatus()
**
** DESCRIPTION:
**   Return clock status
**
** ---------------------------------------------------------------------- */
bool32 MDPClockStatus(MDPClockTypes eClockType)
{
  return TRUE;
}
