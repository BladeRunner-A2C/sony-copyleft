/*=============================================================================
 
  File: DisplaySystem.c
 
  Source file for Display System

   
  Copyright (c) 2019-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
#include <Protocol/EFIChipInfoTypes.h>
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIClock.h>
#include "MDPSystem.h"
#include "api/systemdrivers/busywait.h"
#include "HALhwio.h"
#include "DisplaySystem.h"

/*
 * NOTE: gcc_disp_ahb_clk need be enabled before any other clocks be enabled
 */
char *mdss_rscc_clk[] =
{
   "gcc_disp_ahb_clk",        
   "disp_cc_mdss_rscc_ahb_clk",
   "disp_cc_mdss_rscc_vsync_clk",
   NULL
};

#define DISPLAY_DGPU_BOOT_ENV         L"EnableDGPUBoot"
#define DGPU_SKU_ID                   EFICHIPINFO_FEATURE_CODE_AC

/**
MDSS_RSCC_ClkEnable()

Enable MDSS RSCC clocks 

@retval None

**/
static void MDSS_RSCC_ClkEnable(void)
{
  EFI_CLOCK_PROTOCOL              *mClockProtocol;
  UINTN                            uClockId;
  UINTN                            uCount               = 0;

  if (EFI_SUCCESS == gBS->LocateProtocol(&gEfiClockProtocolGuid,
                                         NULL,
                                         (VOID **)&mClockProtocol))
  {
    while (mdss_rscc_clk[uCount] != NULL)
    {
      if (EFI_SUCCESS == mClockProtocol->GetClockID(mClockProtocol,  mdss_rscc_clk[uCount], &uClockId))
      {
        if (EFI_SUCCESS != mClockProtocol->EnableClock(mClockProtocol, uClockId))
        {
          DEBUG ((EFI_D_WARN, "MDSS_RSCC_ClkEnable: Clock=%a cannot be enabled!\n", mdss_rscc_clk[uCount]));
        }
      }
      else
      {
        DEBUG ((EFI_D_ERROR, "MDSS_RSCC_ClkEnable: Clock=%a  not found!\n", mdss_rscc_clk[uCount]));
      }
      uCount++;
    }
  }
}


/**
DisplaySubsystemInitialization

Do initialization for display subsystem.

@retval EFI_STATUS

**/
EFI_STATUS DisplaySubsystemInitialization(void)
{
  EFI_CHIPINFO_PROTOCOL  *hChipInfoProtocol;
  EFIChipInfoFamilyType   sEFIChipSetFamily;
  EFI_STATUS              eStatus            = EFI_SUCCESS;
  EFI_STATUS              eLocalStatus       = EFI_SUCCESS;

  MDP_OSAL_MEMZERO(&sEFIChipSetFamily, sizeof(sEFIChipSetFamily));
 
  if (EFI_SUCCESS != (eLocalStatus = gBS->LocateProtocol(&gEfiChipInfoProtocolGuid,
                                                         NULL,
                                                         (VOID **)&hChipInfoProtocol)))
  {
    DEBUG((EFI_D_WARN, "DisplaySubsystemInitialization: Failed to locate chip info protocol!\n"));
  }
  else if (EFI_SUCCESS != hChipInfoProtocol->GetChipFamily(hChipInfoProtocol, &sEFIChipSetFamily))
  {
    DEBUG((EFI_D_WARN, "DisplaySubsystemInitialization: Failed to retrieve chip family information!\n"));
  }

  switch (sEFIChipSetFamily)
  {
    case EFICHIPINFO_FAMILY_HAMOA:
    {
      UINT8              uEnableDGPU = 0;
      EFIChipInfoSKUType sEFISKU;

      MDP_OSAL_MEMZERO(&sEFISKU, sizeof(sEFISKU));

      if (MDP_STATUS_OK != MDP_GetEnvironmentVariable((CHAR16*)DISPLAY_DGPU_BOOT_ENV, (uint8*)&uEnableDGPU, sizeof(uint8)))
      {
        DEBUG((EFI_D_INFO, "DisplaySubsystemInitialization: Failed to read dGPU environment variable!\n"));
      }

      if ((EFI_SUCCESS == eLocalStatus) &&
          (EFI_SUCCESS != hChipInfoProtocol->GetSKU(hChipInfoProtocol, &sEFISKU)))
      {
        DEBUG((EFI_D_INFO, "DisplaySubsystemInitialization: Failed to retrieve SKU information!\n"));
      }
      
      /* Disable DisplayDxe if it is a dGPU chip */
      if ((DGPU_SKU_ID == sEFISKU.eFeatureCode) ||
          (1           == uEnableDGPU))
      {
        DEBUG((EFI_D_WARN, "DisplaySubsystemInitialization: SKU is of dGPU type. Disabling DisplayDxe!\n"));
        eStatus = EFI_UNSUPPORTED;
      }
      else
      {
        MDSS_RSCC_ClkEnable();
      }
      break;
    }
    
    case EFICHIPINFO_FAMILY_LANAI:
    case EFICHIPINFO_FAMILY_PALAWAN:
    {
      MDSS_RSCC_ClkEnable();
      break;
    }
      
    default:
      DEBUG((EFI_D_ERROR, "DisplaySubsystemInitialization: Unrecognised chip!\n"));
      eStatus = EFI_UNSUPPORTED;
      break;
  }

  return eStatus;
}
