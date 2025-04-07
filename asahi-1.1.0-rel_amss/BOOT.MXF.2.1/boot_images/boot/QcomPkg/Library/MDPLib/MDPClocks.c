/*=============================================================================

  File: MDPClocks.c

  Source file for MDP/Panel clock configuration


  Copyright (c) 2011-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFIChipInfo.h>
#include <Library/PcdLib.h>
#include <api/systemdrivers/icbarb.h>
#include "MDPLib_i.h"
#include "MDSSPlatform_9xx.h"
#include "MDSSPlatform_10xx.h"
#include "MDPSystem.h"

extern HAL_HW_VersionType  gsVersionInfo;

/*=========================================================================
      Defines
==========================================================================*/

#define MDP_CLOCK_DEFAULT_CLOCK_LIST_LENGTH 8

/*=========================================================================
      Local Tables
==========================================================================*/

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

/* Generic list of clocks that are active before the DisplayDxe is loaded but must be managed
*/
static uint32 uDefaultClockListEntries = 0;

static MDP_ClockRefCount aDefaultClockList[MDP_CLOCK_DEFAULT_CLOCK_LIST_LENGTH];

/*=========================================================================
AXI Bus bandwidth:
4K panel:  2160 x 3840 x 60 x 4 = 1990 MB
==========================================================================*/

ICBArb_MasterSlaveType aMasterSlave[] =
 { { ICBID_MASTER_MDP0, ICBID_SLAVE_EBI1 } ,    /* mdp + dsi */
 };

ICBArb_RequestType aRequest[] =
{
 { ICBARB_REQUEST_TYPE_3, { {5000000000, 4000000000} } } ,
};

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: mdss_bus_bandwidth_request(void)
**
** DESCRIPTION:
**      Create ICBArb client handle and request AXI bus IB/AB bus bandwidth accordingly
**
** NOTE: this function only allow to call one time
** ---------------------------------------------------------------------- */
static void mdss_bus_bandwidth_request(BOOLEAN bEnable)
{

   static npa_client_handle hArb;

   if (hArb == NULL)
   {
       hArb = npa_create_sync_client_ex( "/icb/arbiter",
                                  "display",
                                  NPA_CLIENT_VECTOR,
                                  sizeof(aMasterSlave),
                                  &aMasterSlave);
   }

   if (hArb == NULL)
   {
      DEBUG ((EFI_D_ERROR, "mdss_bus_bandwidth_request : Error, hArb == NULL\n"));
   }
   else
   {
      if (TRUE == bEnable)
      {
         npa_issue_vector_request(hArb, sizeof(aRequest)/(sizeof(npa_resource_state)),
                          (npa_resource_state *)aRequest );
      }
      else 
      {
          npa_complete_request(hArb);
      }
   }
}

/****************************************************************************
*
** FUNCTION: resourceRefCount()
*/
/*!
* \brief
*   This funciton will manage the reference count for a specific resource
*
* \param [in]      bVoteOn     - Add or remove a vote on a resource
*        [in/out]  pRefCount   - Value of the reference count
*
* \retval TRUE if vote changed the state of the resource, FALSE otherwise.
*
****************************************************************************/
static bool32 resourceRefCount(bool32 bVoteOn, INT32 *pRefCount)
{
  bool32 bRet = FALSE;

  if ((NULL == pRefCount) ||
      (*pRefCount < 0))
  {
    bRet = FALSE;
  }
  else if (bVoteOn)
  {
    // Vote on case
    if (*pRefCount == 0)
    {
       bRet      = TRUE;
      *pRefCount = 1;
    }
    else if (*pRefCount < MAX_INT32)
    {
      (*pRefCount)++;
    }
  }
  else
  {
    // Vote off case
    if (*pRefCount == 1)
    {
       bRet      = TRUE;
      *pRefCount = 0;
    }
    else if (*pRefCount > 1)
    {
      (*pRefCount)--;
    }
  }

  return bRet;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ExternalPLLSupported()
**
** DESCRIPTION:
**   Check whether external PLL source is supported , in case of virtual/unknown platforms
**   clocks source are not valid thus cannot be changed to.
**
** ---------------------------------------------------------------------- */
static bool32 ExternalPLLSupported()
{
  bool32             bExternalPLLSupported = TRUE;
  MDP_HwPrivateInfo *psMDPHwPrivateInfo    = MDP_GETPRIVATEINFO();

  if (EFI_PLATFORMINFO_NUM_TYPES <= psMDPHwPrivateInfo->eEFIPlatformInfo)
  {
    bExternalPLLSupported = FALSE;
  }
  else if((EFI_PLATFORMINFO_TYPE_VIRTIO  == psMDPHwPrivateInfo->eEFIPlatformInfo) ||
          (EFI_PLATFORMINFO_TYPE_RUMI    == psMDPHwPrivateInfo->eEFIPlatformInfo) ||
          (EFI_PLATFORMINFO_TYPE_UNKNOWN == psMDPHwPrivateInfo->eEFIPlatformInfo))
  {
    bExternalPLLSupported = FALSE;
  }

  return bExternalPLLSupported;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: SetupClock()
**
** DESCRIPTION:
**   Setup a specific clock
**
** ---------------------------------------------------------------------- */
static MDP_Status SetupClock(EFI_CLOCK_PROTOCOL  *mClockProtocol, MDPClockEntry *pClock, UINT32 uFlags)
{
    MDP_Status eStatus = MDP_STATUS_OK;

    if ((NULL != mClockProtocol) && (NULL != pClock))
    {
        UINTN    uClockId;

        if (pClock->uFlags & MDP_CLOCKFLAG_CDIV)
        {
          if (pClock->pExtSrc)
          {
              MDPExternalClockEntry *pExtSrc = pClock->pExtSrc;

              if (pExtSrc->nSourceDiv)
              {
                if (EFI_SUCCESS != mClockProtocol->GetClockDividerID(mClockProtocol, pExtSrc->szName, &uClockId))
                {
                   DEBUG ((EFI_D_ERROR, "SetupClock: Clock \"%a\" not found!\n", pExtSrc->szName));
                }
                else if (EFI_SUCCESS != mClockProtocol->SetClockDivider(mClockProtocol,  uClockId, pExtSrc->nSourceDiv))
                {
                   /* SourceDiv start from 1 (divided by 1) at mmss_cc  */
                   DEBUG ((EFI_D_ERROR, "SetupClock: Clock \"%a\" failed to set divider!\n", pExtSrc->szName));
                }
              }
          }
        }
        else if (EFI_SUCCESS != mClockProtocol->GetClockID(mClockProtocol,  pClock->szName, &uClockId))
        {
             DEBUG ((EFI_D_ERROR, "SetupClock: Clock \"%a\" not found!\n", pClock->szName));

             eStatus = MDP_STATUS_NO_RESOURCES;
        }
        else
        {
            // Is this clock an external source?
            if ((NULL != pClock->pExtSrc) &&
                (TRUE == ExternalPLLSupported()))
            {
                // Setup clock as an external source.
                if (EFI_SUCCESS != mClockProtocol->SelectExternalSource(mClockProtocol,
                                                                        uClockId,
                                                                        0,                               // FreqHz: 0 -- No voltage control
                                                                        pClock->pExtSrc->uClkSource,
                                                                        pClock->pExtSrc->nClkDiv,
                                                                        pClock->pExtSrc->uClkPLL_M,      // M
                                                                        pClock->pExtSrc->uClkPLL_N,      // N
                                                                        pClock->pExtSrc->uClkPLL_2D))    // 2*D
                {
                    DEBUG ((EFI_D_VERBOSE, "MDPLib : SelectExternalSource: Clock \"%a\" returned an error!\n", pClock->szName));
                    eStatus = MDP_STATUS_FAILED;
                }
            }
            else if ((pClock->nFreqHz > 0) &&
                   !(pClock->uFlags & MDP_CLOCKFLAG_BUS)) /* do not direct vote for bus shared clocks as ICB driver do */
            {
                UINT32  uClockFreq = 0;
            
                // Request a specific clock frequency
                if (EFI_SUCCESS != mClockProtocol->SetClockFreqHz(mClockProtocol,
                                                                  uClockId,
                                                                  pClock->nFreqHz,
                                                                  EFI_CLOCK_FREQUENCY_HZ_CLOSEST,
                                                                  (UINT32 *)&uClockFreq))
                {
                    DEBUG ((EFI_D_INFO, "MDPLib : SetClockFreqHz: Clock \"%a\" to %dHz returned an error!\n", pClock->szName, pClock->nFreqHz));
                    eStatus = MDP_STATUS_FAILED;
                }
            }
            
            // Dynamic clocks are frequency changes, don't reference count them.
            if (0 == (pClock->uFlags & MDP_CLOCKFLAG_DYNAMIC))
            {
              if (TRUE == resourceRefCount(TRUE, &pClock->iRefCount))
              {
                if (EFI_SUCCESS != mClockProtocol->EnableClock(mClockProtocol, uClockId))
                {
                   DEBUG ((EFI_D_WARN, "MDPLib: Clock \"%a\" cannot be enabled!\n", pClock->szName));

                   // Decrease reference count if fail to enable the clock
                   resourceRefCount(FALSE, &pClock->iRefCount);
                   eStatus = MDP_STATUS_FAILED;
                }
              }
            }
        }
    }
    else
    {
      eStatus = MDP_STATUS_BAD_PARAM;
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
        for (uCount=0;uCount<MDPLIB_MAX_CLOCK_NAME;uCount++)
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
static MDP_Status ConfigurePowerDomain(BOOLEAN bEnable, EFI_CLOCK_PROTOCOL  *mClockProtocol, CHAR8 *szDomain, uint32 uFlags)
{
  MDP_Status   eStatus = MDP_STATUS_OK;
  UINTN        uClockPowerDomainId;

  if (EFI_SUCCESS != mClockProtocol->GetClockPowerDomainID(mClockProtocol, szDomain, &uClockPowerDomainId))
  {
    DEBUG ((EFI_D_WARN, "MDPLib: GetClockPowerDomainID failed!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (TRUE == bEnable)
  {
    if (EFI_SUCCESS != mClockProtocol->EnableClockPowerDomain(mClockProtocol, uClockPowerDomainId))
    {
      DEBUG ((EFI_D_WARN, "MDPLib: EnableClockPowerDomain failed!\n"));
      eStatus = MDP_STATUS_NO_RESOURCES;
    }
  }
  else if (FALSE == bEnable)
  {
    /* Don't turn off domains that are marked as common (shared across IP cores) */
    if (0 == (MDP_CLOCKFLAG_SHARED & uFlags))
    {
      if (EFI_SUCCESS != mClockProtocol->DisableClockPowerDomain(mClockProtocol, uClockPowerDomainId))
      {
        DEBUG ((EFI_D_WARN, "MDPLib: DisableClockPowerDomain failed!\n"));
        eStatus = MDP_STATUS_NO_RESOURCES;
      }
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: GetMaxClockIndex()
**
** DESCRIPTION:
**   Return the highest valid clock index in a list
**
** ---------------------------------------------------------------------- */
static uint32 GetMaxClockIndex(MDPClockEntry *pClockList)
{
    UINT32         uCount = 0;

    // If we have an external clock list, search for a matching clock
    if (pClockList)
    {
        while ((pClockList[uCount].szName[0] != '\0'))
        {
            uCount++;
        }
    }

    return uCount;
}



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ConfigureClockSourceXO()
**
** DESCRIPTION:
**   Configure the clock source to XO
**
** ---------------------------------------------------------------------- */
static EFI_STATUS ConfigureClockSourceXO(EFI_CLOCK_PROTOCOL *mClockProtocol, UINTN uClockId)
{
    EFI_STATUS   eStatus = EFI_SUCCESS;
    UINT32       uFreq   = 0;

    // Set clock frequency to 19.2Mhz will configure the clock source to XO
    if(EFI_SUCCESS != (eStatus = mClockProtocol->SetClockFreqHz(mClockProtocol, 
                                                                uClockId, 
                                                                XO_DEFAULT_FREQ_IN_HZ, 
                                                                EFI_CLOCK_FREQUENCY_HZ_EXACT, 
                                                                &uFreq)))
    {
        DEBUG ((EFI_D_VERBOSE, "MDPLib: Failed to set clock %d source to CXO!\n", uClockId));
    }
    return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPClockManagementSupported()
**
** DESCRIPTION:
**   Check whether clocks can be managed, in case of virtual/unkonw platforms
**   clocks are not valid thus cannot be managed
**
** ---------------------------------------------------------------------- */
static bool32 MDPClockManagementSupported(EFI_PLATFORMINFO_PLATFORM_TYPE ePlatformType)
{ 
  bool32 bClockManagementSupported = TRUE;

  if (EFI_PLATFORMINFO_NUM_TYPES <= ePlatformType)
  {
    bClockManagementSupported = FALSE;
  }
  else if((EFI_PLATFORMINFO_TYPE_VIRTIO  == ePlatformType) ||
          (EFI_PLATFORMINFO_TYPE_UNKNOWN == ePlatformType))
  {
    bClockManagementSupported = FALSE;
  }

  return bClockManagementSupported;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPGetMDPDynamicResourceList()
**
** DESCRIPTION:
**   Helper function to get mdp dynamic resource list
**
** ---------------------------------------------------------------------- */
static MDP_Status MDPGetMDPDynamicResourceList(MDP_DynamicClockList **pMDPDynamicResourceList)
{
  MDP_Status                      eStatus               = MDP_STATUS_OK;
  MDP_ResourceList               *pClkResList           = NULL;
  MDP_DynamicClockList           *pMDPDynamicClockList  = NULL;

  if (MDP_STATUS_OK != MDPGetMDPResourceList(&pClkResList))
  {
    DEBUG ((EFI_D_ERROR, "MDPGetMDPDynamicResourceList: MDPGetMDPResourceList failed!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (NULL == (pMDPDynamicClockList = pClkResList->pMDPDynamicClocks))
  {
    DEBUG ((EFI_D_ERROR, "MDPGetMDPDynamicResourceList: pMDPDynamicClockList is NULL!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;  
  }
  else
  {
    *pMDPDynamicResourceList = pMDPDynamicClockList;
  }
  
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DisableRefCountedClocksList()
**
** DESCRIPTION:
**   Disable list of default resources
**
** ---------------------------------------------------------------------- */
static MDP_Status DisableRefCountedClocksList(EFI_CLOCK_PROTOCOL  *mClockProtocol, MDP_ClockRefCount *pClock, uint32 *pNumEntries)
{
  MDP_Status eStatus = MDP_STATUS_OK;
  UINTN      uClockId;
  UINT32     uIndex;
  UINT32     uNumEntries = *pNumEntries;

  for (uIndex=0; uIndex < uNumEntries; uIndex++)
  {
    if (EFI_SUCCESS != mClockProtocol->GetClockID(mClockProtocol,  pClock->sName, &uClockId))
    {
       DEBUG ((EFI_D_WARN, "DisableRefCountedClocksList: Clock \"%a\" not found!\n", pClock->sName));

       eStatus = MDP_STATUS_NO_RESOURCES;
    }
    else
    {
      while (pClock->iRefCount > 0)
      {
        if (EFI_SUCCESS != mClockProtocol->DisableClock(mClockProtocol, uClockId))
        {
           DEBUG ((EFI_D_WARN, "DisableRefCountedClocksList: Clock \"%a\" cannot be enabled!\n", pClock->sName));
           eStatus = MDP_STATUS_FAILED;
        }    
        pClock->iRefCount--;
      }
    }
    pClock++;
  }

  // Clean up the number of entries since all have been disabled
  *pNumEntries = 0;

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
  MDP_Status           eStatus             = MDP_STATUS_OK;
  MDP_HwPrivateInfo   *psMDPHwPrivateInfo  = MDP_GETPRIVATEINFO();
  EFI_CLOCK_PROTOCOL  *mClockProtocol;

  if (TRUE == psMDPHwPrivateInfo->bSWRender)
  {
     DEBUG ((EFI_D_WARN, "MDPSetupClocks: SW Render enabled, ignore this error and continue\n"));
     eStatus = MDP_STATUS_OK;
  }
  else if (FALSE == MDPClockManagementSupported(psMDPHwPrivateInfo->eEFIPlatformInfo))
  {
    DEBUG ((EFI_D_WARN, "MDPSetupClocks: MDP Clock Management not Supported\n"));
    eStatus = MDP_STATUS_OK;
  }
  // Grab the clock protocol
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiClockProtocolGuid,
                                         NULL,
                                         (VOID **)&mClockProtocol))
  {
    DEBUG ((EFI_D_WARN, "MDPLib: Clock protocol failed!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    MDPClockEntry     *pClockList     = NULL;
    MDP_ResourceList  *pClkResList    = NULL;
    
    if (MDP_STATUS_OK !=  MDPGetMDPResourceList(&pClkResList))
    {
      DEBUG ((EFI_D_ERROR, "MDPSetupClocks: MDPGetMDPResourceList failed!\n"));
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

            if (NULL != pClkResList->pRsccClocks)
            {
              pClockList = (MDPClockEntry*)(pClkResList->pRsccClocks);
              while (pClockList->szName[0] != '\0')
              {
                SetupClock(mClockProtocol, pClockList, 0);
                pClockList++;
              }
            }

            if(NULL != pClkResList->pDispCCXOClk)
            {
              pClockList = (MDPClockEntry*)(pClkResList->pDispCCXOClk);
              while (pClockList->szName[0] != '\0')
              {
                SetupClock(mClockProtocol, pClockList, 0);
                pClockList++;
              }
            }

            mdss_bus_bandwidth_request(TRUE);

            pClockList = (MDPClockEntry*)(pClkResList->pMDPClocks);

            /* Enable the power domain for access in to the MDSS clocks */
            if(NULL != pClkResList->pPowerDomain)
            {
              UINT32                    uCount = 0;

              /* go through the power domain list to enable it in order */
              while(pClkResList->pPowerDomain[uCount].szName[0] != '\0')
              {
                  ConfigurePowerDomain(TRUE, mClockProtocol, (CHAR8*)pClkResList->pPowerDomain[uCount].szName, pClkResList->pPowerDomain[uCount].uFlags);
                  uCount++;
              }
            }
            break;
          case MDP_CLOCKTYPE_DSI0:
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_DSI0))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            else
            {
              pClockList = (MDPClockEntry*)(pClkResList->pDSI0Clocks);
            }
            break;
          case MDP_CLOCKTYPE_DSI1:
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_DSI1))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }

            else
            {
              pClockList = (MDPClockEntry*)(pClkResList->pDSI1Clocks);
            }
            break;
          case MDP_CLOCKTYPE_DP0:
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_DP0))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            else
            {
              pClockList = (MDPClockEntry*)(pClkResList->pDP0Clocks);
            }
            break;
          case MDP_CLOCKTYPE_DP1:
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_DP1))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            else
            {
              pClockList = (MDPClockEntry*)(pClkResList->pDP1Clocks);
            }
            break;
          case MDP_CLOCKTYPE_DP2:
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_DP2))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            else
            {
              pClockList = (MDPClockEntry*)(pClkResList->pDP2Clocks);
            }
            break;
          case MDP_CLOCKTYPE_DP3:
            if (FALSE == MDP_CheckInterfaceAvailable(psMDPHwPrivateInfo->sEFIChipSetFamily, MDP_DISPLAY_PERIPHERAL_EDP0))
            {
              eStatus = MDP_STATUS_NOT_SUPPORTED;
            }
            else
            {
              pClockList = (MDPClockEntry*)(pClkResList->pEDPClocks);
            }
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
          SetupClock(mClockProtocol, &pClockList[uCount], 0);

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
  MDP_Status            eStatus                      = MDP_STATUS_OK;
  MDP_DynamicClockList *pMDPDynamicResourceList      = NULL;
  MDP_HwPrivateInfo    *psMDPHwPrivateInfo           = MDP_GETPRIVATEINFO();

  if (NULL == psMDPHwPrivateInfo)
  {
    DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicClocks: psMDPHwPrivateInfo is NULL!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (FALSE == MDPClockManagementSupported(psMDPHwPrivateInfo->eEFIPlatformInfo))
  {
    DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicClocks: Clock management not supported!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (MDP_STATUS_OK != MDPGetMDPDynamicResourceList(&pMDPDynamicResourceList))
  {
    DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicClocks: MDPGetMDPDynamicResourceList failed!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    switch(eClockType)
    {
      case MDP_DYNAMIC_CLOCKTYPE_CORE:
      {
        EFI_CLOCK_PROTOCOL   *mClockProtocol = NULL;
        MDPDynamicClockEntry *pCoreClock     = (MDPDynamicClockEntry *)pMDPDynamicResourceList->pMDPCoreClock;

        if (NULL == pCoreClock)
        {
          DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicClocks: pCoreClock is NULL\n"));
          eStatus = MDP_STATUS_NO_RESOURCES;
        }
        else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiClockProtocolGuid,
                                                     NULL,
                                                     (VOID **) &mClockProtocol))
        {
          DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicClocks: Clock protocol failed!\n"));
          eStatus = MDP_STATUS_NO_RESOURCES;
        }
        else if (NULL == mClockProtocol)
        {
          DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicClocks: mClockProtocol is NULL\n"));
          eStatus = MDP_STATUS_NO_RESOURCES;
        }
        else
        {
          MDPClockEntry sTmpCoreClock;
          
          MDP_OSAL_MEMSET(&sTmpCoreClock, 0, sizeof(MDPClockEntry));

          /* Update MDP Core Clocks dynamically */
          pCoreClock->nFreqHz = uNewClkValue;

          /* Initialize  sTmpCoreClock*/
          AsciiStrCpyS(sTmpCoreClock.szName, MDPLIB_MAX_CLOCK_NAME, pCoreClock->szName);
          sTmpCoreClock.nFreqHz = pCoreClock->nFreqHz;
          sTmpCoreClock.pExtSrc = NULL;
          sTmpCoreClock.uFlags  = MDP_CLOCKFLAG_DYNAMIC;

          /* Update Clock with new frequency */
          eStatus = SetupClock(mClockProtocol, &sTmpCoreClock, 0);
        }
        break;
      }

      default:
        DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicClocks: eClockType=%d not supported\n", eClockType));
        eStatus = MDP_STATUS_NO_RESOURCES;
        break;
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPUpdateDynamicBandwidth()
**
** DESCRIPTION:
**   Update core bandwidth value, in case of resolution or refresh rate 
**   changes, bandwidth value should be updated.
**
** ---------------------------------------------------------------------- */
MDP_Status MDPUpdateDynamicBandwidth(uint64 uNewBandwidth)
{
  MDP_Status               eStatus            = MDP_STATUS_OK;
  static npa_client_handle hArbCore           = NULL;
  ICBArb_MasterSlaveType   aMasterSlaveCore[] = {{ICBID_MASTER_MDP0, ICBID_SLAVE_EBI1}};    /* mdp + dsi */
  
  if (hArbCore == NULL)
  {
     hArbCore = npa_create_sync_client_ex("/icb/arbiter",
                                          "display",
                                          NPA_CLIENT_VECTOR,
                                          sizeof(aMasterSlaveCore),
                                          &aMasterSlaveCore);
  }
  if (hArbCore == NULL)
  {
    DEBUG ((EFI_D_ERROR, "MDPUpdateDynamicBandwidth : Error, hArb == NULL\n"));
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (0 == uNewBandwidth)
  {
    npa_complete_request(hArbCore);
  }
  else
  {     
    ICBArb_RequestType aDynamicRequest[1];
    uint32             i;

    MDP_OSAL_MEMZERO(aDynamicRequest, sizeof(aDynamicRequest));

    /* Update bandwidth info */
    for (i = 0; i < sizeof(aDynamicRequest)/sizeof(ICBArb_RequestType); i++)
    {
      aDynamicRequest[i].arbType           = ICBARB_REQUEST_TYPE_3;
      aDynamicRequest[i].arbData.type3.uIb = (uint64)MDP_CORE_BANDWIDTH_VOTE_IB;
      aDynamicRequest[i].arbData.type3.uAb = (uint64)(uNewBandwidth / 2);
    }
    
    npa_issue_vector_request(hArbCore, sizeof(aDynamicRequest)/(sizeof(npa_resource_state)),
                      (npa_resource_state *)aDynamicRequest);
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
  MDP_Status           eStatus             = MDP_STATUS_OK;
  MDP_HwPrivateInfo   *psMDPHwPrivateInfo  = MDP_GETPRIVATEINFO();
  EFI_CLOCK_PROTOCOL  *mClockProtocol;

  if (TRUE == psMDPHwPrivateInfo->bSWRender)
  {
     DEBUG ((EFI_D_WARN, "MDPLib: SW Render enabled, no Clocks disabled need\n"));
  }
  // Grab the clock protocol
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiClockProtocolGuid,
                                            NULL,
                                            (VOID **) &mClockProtocol))
  {
    DEBUG ((EFI_D_ERROR, "MDPLib: Clock protocol failed!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    MDPClockEntry                  *pClockList          = NULL;
    MDP_ResourceList               *pClkResList;

    if (MDP_STATUS_OK !=  MDPGetMDPResourceList(&pClkResList))
    {
      DEBUG ((EFI_D_ERROR, "MDPDisableClocks: MDPGetMDPResourceList failed!\n"));
      eStatus = MDP_STATUS_NO_RESOURCES;
    }
    else
    {
      if(NULL != pClkResList)
      {
        switch (eClockType)
        {
          case MDP_CLOCKTYPE_CORE:
            /* MDP Core Clocks */
            pClockList = (MDPClockEntry*)(pClkResList->pMDPClocks);
            break;
          case MDP_CLOCKTYPE_DSI0:
            /* MDP Core Clocks */
            pClockList = (MDPClockEntry*)(pClkResList->pDSI0Clocks);
            break;
          case MDP_CLOCKTYPE_DSI1:
            /* MDP Core Clocks */
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
          case MDP_CLOCKTYPE_RSCC:
            pClockList = (MDPClockEntry*)(pClkResList->pRsccClocks);
            break;
          default:
            break;
        }
      }

      // if we have a valid clock list
      if (NULL != pClockList)
      {
        INT32  uCount     = 0;
        INT32  uLastClock = (INT32)GetMaxClockIndex(pClockList);

        // Walk the clock list backwards when disabling
        for (uCount=uLastClock;uCount>=0;uCount--)
        {
          UINTN    uClockId;

          if (MDP_CLOCKFLAG_SHARED & pClockList[uCount].uFlags)
          {
            // Don't touch shared clocks, jump to the next
            continue;
          }
          else if (EFI_SUCCESS != mClockProtocol->GetClockID(mClockProtocol,  pClockList[uCount].szName, &uClockId))
          {
             DEBUG ((EFI_D_VERBOSE, "MDPLib: Clock \"%a\" not found!\n", pClockList[uCount].szName));
          }
          else
          {
            /* For externally sourced clocks, try to set the source back to CXO */
            if ((MDP_CLOCKTYPE_DSI0 == eClockType) ||
                (MDP_CLOCKTYPE_DSI1 == eClockType)) 
            {
              if (EFI_SUCCESS != ConfigureClockSourceXO(mClockProtocol, uClockId))
              {
                DEBUG ((EFI_D_VERBOSE, "MDPLib: Clock \"%a\" cannot set source to XO!\n", pClockList[uCount].szName));
              } 
            }

            if (TRUE == resourceRefCount(FALSE, &pClockList[uCount].iRefCount))
            {
              if (EFI_SUCCESS != mClockProtocol->DisableClock(mClockProtocol, uClockId))
              {
                DEBUG ((EFI_D_VERBOSE, "MDPLib: Clock \"%a\" cannot be disabled!\n", pClockList[uCount].szName));

                //Add back the reference count if fail to disable the clock
                resourceRefCount(TRUE, &pClockList[uCount].iRefCount);
              }
            }
          }
        }
      }


      /* Disable the power domain after core clocks are off */
      if ((MDP_CLOCKTYPE_CORE == eClockType) &&
          (NULL != pClkResList))
      {
        // Disable list of clocks that were enabled before the DisplayDxe was loaded
        DisableRefCountedClocksList(mClockProtocol, aDefaultClockList, &uDefaultClockListEntries);
         
        if (NULL != pClkResList->pPowerDomain)
        {
           INT32          iCount = 0;
           INT32          iTotalPowerDomains = 0;

           /* Get total number of power domains on the list */
           while (pClkResList->pPowerDomain[iCount++].szName[0] != '\0')
           {
             iTotalPowerDomains++;
           }

           /* Turn off power domains in the reserve order */
           for (iCount = (iTotalPowerDomains - 1); iCount >= 0; iCount--)
           {
             ConfigurePowerDomain(FALSE, mClockProtocol, (CHAR8*)pClkResList->pPowerDomain[iCount].szName, pClkResList->pPowerDomain[iCount].uFlags);
           }

           pClockList = (MDPClockEntry*)(pClkResList->pDispCCXOClk);
           if(NULL != pClockList)
           {
                UINTN    uClockId;
                INT32    uCount     = 0;
                INT32    uLastClock = (INT32)GetMaxClockIndex(pClockList);

                // Walk the clock list backwards when disabling
                for (uCount=uLastClock;uCount>=0;uCount--)
                {
                   if (MDP_CLOCKFLAG_SHARED & pClockList[uCount].uFlags)
                   {
                      // Don't touch shared clocks, jump to the next
                     continue;
                   }
                   else if (EFI_SUCCESS != mClockProtocol->GetClockID(mClockProtocol,  pClockList[uCount].szName, &uClockId))
                   {
                      DEBUG ((EFI_D_VERBOSE, "MDPLib: Clock \"%a\" not found!\n", pClockList[uCount].szName));
                   }
                   else
                   {
                      if (TRUE == resourceRefCount(FALSE, &pClockList[uCount].iRefCount))
                      {
                        if (EFI_SUCCESS != mClockProtocol->DisableClock(mClockProtocol, uClockId))
                        {
                           DEBUG ((EFI_D_ERROR, "MDPLib: Clock \"%a\" cannot be disabled!\n", pClockList[uCount].szName));

                           // Add back the reference count if fail to disable the clock
                           resourceRefCount(TRUE, &pClockList[uCount].iRefCount);
                        }
                      }
                   }
                }
           }
        }

        mdss_bus_bandwidth_request(FALSE);
      }
    }
  }

  return eStatus;
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
  MDP_ResourceList* pClkResList = NULL;
  bool32            bClockOn    = FALSE;

  if (MDP_STATUS_OK == MDPGetMDPResourceList(&pClkResList))
  {
    MDPClockEntry *pClockList = NULL;

    switch (eClockType)
    {
      case MDP_CLOCKTYPE_CORE:
      { 
        pClockList = (MDPClockEntry*)(pClkResList->pMDPClocks);
        break;
      }
      case MDP_CLOCKTYPE_DSI0:
      {
        pClockList = (MDPClockEntry*)(pClkResList->pDSI0Clocks);
        break;
      }
      case MDP_CLOCKTYPE_DSI1:
      {
        pClockList = (MDPClockEntry*)(pClkResList->pDSI1Clocks);
        break;
      }
      case MDP_CLOCKTYPE_DP0:
      {
        pClockList = (MDPClockEntry*)(pClkResList->pDP0Clocks);
        break;
      }
      case MDP_CLOCKTYPE_DP1:
      {
        pClockList = (MDPClockEntry*)(pClkResList->pDP1Clocks);
        break;
      }
      case MDP_CLOCKTYPE_DP3:
      {
        pClockList = (MDPClockEntry*)(pClkResList->pEDPClocks);
        break;
      }
	  case MDP_CLOCKTYPE_DP2:
      {
        pClockList = (MDPClockEntry*)(pClkResList->pDP2Clocks);
        break;
      }
      default:
        break;
    }

    if ((NULL != pClockList) &&
        (0    != pClockList[0].iRefCount))
    {
      bClockOn = TRUE;
    }
  }

  return bClockOn;
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
  EFI_CLOCK_PROTOCOL  *mClockProtocol;

  if((EFI_PLATFORMINFO_TYPE_VIRTIO  == psMDPHwPrivateInfo->eEFIPlatformInfo) ||
     (EFI_PLATFORMINFO_TYPE_UNKNOWN == psMDPHwPrivateInfo->eEFIPlatformInfo))
   {
     DEBUG ((EFI_D_WARN, "MDPLib: For VIRTIO, ignore this error and continue\n"));
     eStatus = MDP_STATUS_OK;
   }
  // Grab the clock protocol
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiClockProtocolGuid,
                                         NULL,
                                         (VOID **)&mClockProtocol))
  {
    DEBUG ((EFI_D_WARN, "MDPLib: Clock protocol failed!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    if (MDP_STATUS_OK != MDPValidateVersion(psMDPHwPrivateInfo))
    {
      DEBUG ((EFI_D_WARN, "MDPLib:GetMDPVersionIndex  failed!\n"));
    }
    else if (NULL == pClockList)
    {
      DEBUG ((EFI_D_WARN, "MDPLib:MDPSetupClockList  Invalid clock entry list!\n"));
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
        (void)SetupClock(mClockProtocol, &sClockEntry, 0);

        // Go to the next clock
        uCount++;
      }      
    }
  }

  return eStatus;
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
** FUNCTION: MDPGetMinCoreClock()
**
** DESCRIPTION:
**   Return minimal core clock value
**
** ---------------------------------------------------------------------- */
uint32 MDPGetMinCoreClock(void)
{
  MDP_Status            eStatus                      = MDP_STATUS_OK;
  uint32                uMinCoreClock                = MDP_MIN_CORE_CLOCK;
  MDP_DynamicClockList *pMDPDynamicResourceList      = NULL;
  MDPDynamicClockEntry *pMDPDynamicCoreClock         = NULL;
  
  if (MDP_STATUS_OK != MDPGetMDPDynamicResourceList(&pMDPDynamicResourceList))
  {
    DEBUG ((EFI_D_ERROR, "MDPGetMinCoreClock: MDPGetMDPDynamicResourceList failed!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else if (NULL == (pMDPDynamicCoreClock = pMDPDynamicResourceList->pMDPCoreClock))
  {
    DEBUG ((EFI_D_ERROR, "MDPGetMinCoreClock: pMDPDynamicCoreClock is NULL!\n"));
    eStatus = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    uMinCoreClock = pMDPDynamicCoreClock->uMinFreqHz;
  }

  return uMinCoreClock;
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
** FUNCTION: MDPClocksRefCount()
**
** DESCRIPTION:
**   Add a clock to the list of default clocks active before the displayDxe is loaded
**
** ---------------------------------------------------------------------- */
void MDPClocksRefCount(char *pClockName, UINT32 iRefCount)
{
  // Populate list of clocks that need to be managed.
  if (uDefaultClockListEntries < MDP_CLOCK_DEFAULT_CLOCK_LIST_LENGTH)
  {
    AsciiStrCpyS(aDefaultClockList[uDefaultClockListEntries].sName, MDPLIB_MAX_CLOCK_NAME, pClockName);
    aDefaultClockList[uDefaultClockListEntries].iRefCount = iRefCount;
    uDefaultClockListEntries++;
  }
}