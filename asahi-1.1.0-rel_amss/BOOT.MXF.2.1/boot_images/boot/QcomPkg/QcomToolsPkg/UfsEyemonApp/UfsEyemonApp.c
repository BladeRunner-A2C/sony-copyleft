/** @file UfsEyemonApp.c

  UFS Eye Monitor Application

  Copyright (c) 2022-2023 Qualcomm Technologies, Inc. All rights reserved. 
  Confidential and Proprietary - Qualcomm Technologies, Inc.  

**/

/*=============================================================================
                              EDIT HISTORY


when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
2023-08-28   jt      Update SLT Left and Right failure step
2023-08-07   jt      Add eye width threshold and result buffer options
2023-07-12   jt      Remove QuantumDataVisualLib 
2023-04-21   jt      Add zero voltage and SLT options
2022-09-16   jt      Enable Host Side again  
2022-08-31   jt      Disable Host Side for now 
2022-04-18   jt      Initial revision

=============================================================================*/

#include <Library/BaseMemoryLib.h> 
#include <Library/DevicePathLib.h> 
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Protocol/BlockIo.h>
#include <Protocol/EFIQcomEnv.h>
#include <Protocol/EFIStorageDeviceMgmt.h>
#include <Protocol/EFIStorageEyemon.h>

/* Data Transfer Params */
#define UFS_EYEMON_TEST_START_LBA                  0
#define UFS_EYEMON_TEST_TRANSFER_SIZE_MB           1

#define UFS_EYEMON_DEFAULT_TARGET_COUNT            0x5D
#define UFS_EYEMON_TOTAL_LANES                     0x2
#define UFS_EYEMON_STEP_MASK                       0x3f
#define UFS_EYEMON_HOST_MAX_COARSE_CODE            0x6

/* SLT Params */
#define UFS_EYEMON_SLT_LEFT_FAILURE_STEP           0
#define UFS_EYEMON_SLT_RIGHT_FAILURE_STEP          0
#define UFS_EYEMON_SLT_INITIAL_LEFT_TIMING_STEP    -9
#define UFS_EYEMON_SLT_INITIAL_RIGHT_TIMING_STEP   6
#define UFS_EYEMON_SLT_GOOD_EYE_WIDTH              12
#define UFS_EYEMON_SLT_INITIAL_EYE_WIDTH           0x7F /* Set to maximum positive byte value */

extern EFI_GUID gEfiUfsLU0Guid;
extern EFI_GUID gEfiUfsDeviceWlunGuid;

/* UFS Device Path */
typedef struct {
   VENDOR_DEVICE_PATH  Ufs;
   EFI_DEVICE_PATH     End;
} QCUFS_DEVICE_PATH;

typedef struct {
   INT8  LeftEyeWidth;
   INT8  RightEyeWidth; 
   INT8  TimingStep;
   INT8  ErrorCount; 
   UINT8 TotalEyeWidth; 
} UFS_EYEMON_SLT_DATA; 

/* Protocol Handles */
static EFI_BLOCK_IO_PROTOCOL *BlkIo = NULL; 
static EFI_QCOMENV_PROTOCOL *QcomEnvProtocol = NULL;
static EFI_STORAGE_DEV_MGMT_PROTOCOL *DevMgmt = NULL; 
static EFI_STORAGE_EYEMON_PROTOCOL *Eyemon = NULL; 

#define TESTPARTI_LABEL       L"testparti"

EFI_STATUS UfsEyemonGetProtocols(UINT32 CoreId)
{
   EFI_GUID *RootGuid = &gEfiUfsLU0Guid;
   EFI_HANDLE *HandleList; 
   EFI_STATUS Status = EFI_SUCCESS; 
   HandleInfo BlkIoHandleList[4]; 
   PartiSelectFilter HandleFilter;
   QCUFS_DEVICE_PATH *DevicePath;
   UINTN HandleIndex, NumberHandles = 0; 
   UINT32 Attribs = 0; 

   if (CoreId == 0) {
      RootGuid = &gEfiUfsLU0Guid; 
   }
   else {
      AsciiPrint ("UFS Eye Monitor - CoreId %d not supported\n", CoreId); 
      return EFI_UNSUPPORTED; 
   }

   /* Find Eye Monitor Handle for UFS */
   Status = gBS->LocateProtocol(&gEfiStorageEyemonProtocolGuid, NULL, (void**)&Eyemon);
   if ((Status != EFI_SUCCESS) || (QcomEnvProtocol == NULL)) {
      AsciiPrint ("UFS Eye Monitor - Locate Eyemon Protocol failed, Status =  0x%x\n", Status);
      return Status;
   }

   /* Find Device Mgmt Handle for UFS */
   Status = gBS->LocateHandleBuffer(ByProtocol,
                                    &gEfiStorageDevMgmtProtocolGuid,
                                    NULL,
                                    &NumberHandles,
                                    &HandleList);
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("LocateHandleBuffer StorageDevMgmt failed, status 0x%x\n", Status);
      return Status; 
   }

   for (HandleIndex = 0; HandleIndex < NumberHandles; HandleIndex++) {	
      Status = gBS->HandleProtocol(HandleList[HandleIndex],
                                   &gEfiStorageDevMgmtProtocolGuid,
                                   (VOID**)&DevMgmt);
      if (Status != EFI_SUCCESS) {
         AsciiPrint ("HandleProtocol StorageDevMgmt failed, status 0x%x\n", Status);
         return Status; 
      }
	
      DevicePath = (QCUFS_DEVICE_PATH *) DevicePathFromHandle(HandleList[HandleIndex]); 
      if (CompareGuid(&DevicePath->Ufs.Guid, &gEfiUfsDeviceWlunGuid)) {
         break; 
      }
   }

   /* Find UFS BlkIo Handle to testparti partition in LUN 0 */
   Attribs |= BLK_IO_SEL_MATCH_PARTITION_LABEL;
   HandleFilter.PartitionLabel = TESTPARTI_LABEL;

   Attribs |= BLK_IO_SEL_MATCH_ROOT_DEVICE;
   HandleFilter.RootDeviceType = RootGuid;

   Status = QcomEnvProtocol->GetBlkIOHandles (QcomEnvProtocol, Attribs, &HandleFilter, BlkIoHandleList, (UINT32 *)&NumberHandles);
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("GetBlkIOHandles testparti partition failed, status 0x%x\n", Status);
      return Status;
   }

   if (NumberHandles > 1) {
      AsciiPrint ("GetBlkIOHandles testparti partition failed, more than one handle found\n");
      return EFI_INVALID_PARAMETER;
   }
   else if (NumberHandles == 0) {
      AsciiPrint ("GetBlkIOHandles testparti partition failed, no handles found\n");
      return EFI_NOT_FOUND;
   }

   BlkIo = BlkIoHandleList[0].BlkIo;

   return Status; 
}

EFI_STATUS UfsEyemonSLTGetNextTimingStep(UFS_EYEMON_SLT_DATA *Context)
{
   if (Context == NULL) {
      return EFI_INVALID_PARAMETER; 
   }

   /* For the negative TimingSteps, continue to move to the left until no
      errors are encountered or else move to the right. Once we have
      established a step with no errors, the step where errors are encountered
      ends the negative side sweep and the next TimingStep will be the initial
      positive side TimingStep. */
   if (Context->TimingStep < 0) {
      if (Context->ErrorCount == 0) {
         Context->LeftEyeWidth = Context->TimingStep; 

         if (Context->TimingStep > UFS_EYEMON_SLT_INITIAL_LEFT_TIMING_STEP) {
            Context->TimingStep = UFS_EYEMON_SLT_INITIAL_RIGHT_TIMING_STEP;
         } 
         else {
            Context->TimingStep -= 1; 
         }
      }
      else {
         if (Context->LeftEyeWidth != -UFS_EYEMON_SLT_INITIAL_EYE_WIDTH) {
            Context->TimingStep = UFS_EYEMON_SLT_INITIAL_RIGHT_TIMING_STEP; 
         }
         else {
            Context->TimingStep += 1;
         }
      }

      /* If there has not been a passing TimingStep and the left failure step
         is reached, return error */
      if ((Context->LeftEyeWidth == -UFS_EYEMON_SLT_INITIAL_EYE_WIDTH) && 
          (Context->TimingStep >= UFS_EYEMON_SLT_LEFT_FAILURE_STEP)) {
         AsciiPrint ("UFS Eye Monitor - SLT screen failed, reached TimingStep %d without a pass\n", 
                     UFS_EYEMON_SLT_LEFT_FAILURE_STEP);
         return EFI_DEVICE_ERROR;
      }
   }

   /* For the positive TimingSteps, continue to move to the right until no
      errors are encountered or else move to the left. Once we have
      established a step with no errors, the step where errors are encountered
      ends the positive side sweep. */
   else {
      if (Context->ErrorCount == 0) {
         Context->RightEyeWidth = Context->TimingStep; 

         if (Context->TimingStep < UFS_EYEMON_SLT_INITIAL_RIGHT_TIMING_STEP) {
            Context->TotalEyeWidth = Context->RightEyeWidth - Context->LeftEyeWidth + 1; 
         }
         else {
            Context->TimingStep += 1; 
         }
      }
      else {
         if (Context->RightEyeWidth != UFS_EYEMON_SLT_INITIAL_EYE_WIDTH) {
            Context->TotalEyeWidth = Context->RightEyeWidth - Context->LeftEyeWidth + 1; 
         }
         else
         {
            Context->TimingStep -= 1;
         }
      }

      /* If there has not been a passing TimingStep and the right failure step
         is reached, return error */
      if ((Context->RightEyeWidth == UFS_EYEMON_SLT_INITIAL_EYE_WIDTH) && 
          (Context->TimingStep <= UFS_EYEMON_SLT_RIGHT_FAILURE_STEP)) {
         AsciiPrint ("UFS Eye Monitor - SLT screen failed, reached TimingStep %d without a pass\n", 
                     UFS_EYEMON_SLT_RIGHT_FAILURE_STEP);
         return EFI_DEVICE_ERROR; 
      }
   }

   return EFI_SUCCESS; 
}

/**
 *The user Entry Point for UFS Eye Monitor Application. The user
 *code starts with this function as the real entry point for the  
 *application.  

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval EFI_NO_MEDIA      No memory card found
  @retval EFI_ABORTED       Some other errors occured.
**/
EFI_STATUS
EFIAPI
UfsEyemonMain (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
   BOOLEAN DeviceEyemon = FALSE, HostEyemon = FALSE, SLT = FALSE, ZeroVoltage = FALSE; 
   CHAR8 **Argv; 
   EFI_STORAGE_OP_MODE_CAPABILITIES OpModeCaps; 
   EFI_STORAGE_EYEMON_CAPS EyemonCaps; 
   EFI_STORAGE_EYEMON_CONFIG EyemonConfig; 
   EFI_STORAGE_EYEMON_MODE EyemonMode; 
   EFI_STORAGE_EYEMON_PARAMS EyemonParams; 
   EFI_STORAGE_EYEMON_RESULT EyemonResult; 
   EFI_STORAGE_LANE_NUM LaneNum = LANE_ALL; 
   EFI_STATUS Status = EFI_SUCCESS;
   INT8 TimingStep = 0, VoltStep = 0, VoltCoordinate = 0; 
   UFS_EYEMON_SLT_DATA EyemonSLTData; 
   UINT8 CoarseCode = 0, MaxCoarseCode = 0, VoltageMaxSteps = 0; 
   UINT8 CoreId = 0, Lane = 0, TargetCount = UFS_EYEMON_DEFAULT_TARGET_COUNT; 
   UINT8 EyeWidthThreshold = UFS_EYEMON_SLT_GOOD_EYE_WIDTH; 
   UINT8 *DataBuffer = NULL; 
   UINT64 *ResultBuffer = NULL; 
   UINT32 i = 0, VoltageSize = 0; 
   UINTN Argc, DataSize = 0; 

   /* Find Qcom Env Protocol Handle */
   Status = gBS->LocateProtocol(&gEfiQcomEnvProtocolGuid, NULL, (void**)&QcomEnvProtocol);
   if ((Status != EFI_SUCCESS) || (QcomEnvProtocol == NULL)) {
      AsciiPrint ("UFS Eye Monitor - Locate QcomEnv Protocol failed, Status =  0x%x\n", Status);
      return Status;
   }

   /* Get Command Line Arguments (if any) and parse them */
   Status = QcomEnvProtocol->GetCmdLineArgs (QcomEnvProtocol, ImageHandle, &Argc, &Argv);
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("UFS Eye Monitor - GetCmdLineArgs failed, Status =  0x%x\n", Status);
      return Status; 
   }

   for (i = 0; i < Argc; i++) {
      if (AsciiStrCmp (Argv[i], "-instance") == 0) {
         i++; 
         if (i < Argc) {
            CoreId = AsciiStrDecimalToUintn(Argv[i]); 
         }
      }

      else if (AsciiStrCmp (Argv[i], "-lane") == 0) {
         i++; 
         if (i < Argc) {
            LaneNum = AsciiStrDecimalToUintn(Argv[i]); 
            if ((LaneNum != 0) && (LaneNum != 1)) {
               AsciiPrint ("UFS Eye Monitor - Invalid LaneNum provided %d\n", LaneNum);
               return EFI_INVALID_PARAMETER; 
            }
         }
      }

      else if (AsciiStrCmp (Argv[i], "-count") == 0) {
         i++;
         if (i < Argc) {
            TargetCount = AsciiStrDecimalToUintn(Argv[i]); 
         }
      }

      else if (AsciiStrCmp (Argv[i], "-host") == 0) {
         HostEyemon = TRUE; 
      }

      else if (AsciiStrCmp (Argv[i], "-device") == 0) {
         DeviceEyemon = TRUE; 
      }

      else if (AsciiStrCmp (Argv[i], "-slt") == 0) {
         SLT = TRUE;  
         HostEyemon = TRUE; 
      }

      else if (AsciiStrCmp (Argv[i], "-zero_voltage") == 0) {
         ZeroVoltage = TRUE; 
      }

      else if (AsciiStrCmp (Argv[i], "-ew_threshold") == 0) {
         i++; 
         if (i < Argc) {
            EyeWidthThreshold = AsciiStrDecimalToUintn(Argv[i]);
         }
      }

      else if (AsciiStrCmp (Argv[i], "-result") == 0) {
         i++;
         if (i < Argc) {
            ResultBuffer = (UINT64 *)AsciiStrDecimalToUintn(Argv[i]); 
         }
      }
   }

   if ((HostEyemon == FALSE) && (DeviceEyemon == FALSE)) {
      AsciiPrint ("UFS Eye Monitor - Device or Host Eyemon not selected\n");
      return EFI_INVALID_PARAMETER; 
   }

   /* SLT is doing Host Eyemon only */
   if ((SLT == TRUE) && (DeviceEyemon == TRUE)) {
     AsciiPrint ("UFS Eye Monitor - Only Host Eyemon available for SLT option\n");
     DeviceEyemon = FALSE; 
     HostEyemon = TRUE; 
   }

   if (HostEyemon) {
      EyemonMode = HOST_EYEMON; 
      AsciiPrint ("\nUFS Host Side Eye Monitor Start \n\n");
   }

   if (DeviceEyemon) {
      EyemonMode = DEVICE_EYEMON; 
      AsciiPrint ("\nUFS Device Side Eye Monitor Start \n\n");
   }

   Status = UfsEyemonGetProtocols(CoreId);
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("UFS Eye Monitor - GetProtocols failed, status 0x%x \n", Status);
      return Status; 
   }

   if (EyemonMode == HOST_EYEMON) {
      MaxCoarseCode = UFS_EYEMON_HOST_MAX_COARSE_CODE; 
   }

   EyemonParams.Mode = EyemonMode; 
   EyemonParams.LaneNum = LaneNum; 

   /* Get EYEMON Capabilities */
   Status = Eyemon->GetCapabilities(Eyemon, &EyemonParams, &EyemonCaps); 
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("UFS Eye Monitor - GetCapabilities failed, status 0x%x \n", Status);
      return Status;  
   }

   if (EyemonCaps.Supported == 0) {
      AsciiPrint ("UFS Eye Monitor not supported, exiting\n");
      return EFI_UNSUPPORTED; 
   }

   AsciiPrint ("Capabilities: \nTimingMaxSteps %d, TimingMaxOffset %d\nVoltageMaxSteps %d, VoltageMaxOffset %d\n\n", 
              EyemonCaps.TimingMaxSteps, EyemonCaps.TimingMaxOffset, EyemonCaps.VoltageMaxSteps, EyemonCaps.VoltageMaxOffset); 

   /* Get max gear and Update Power Mode with Adapt Enabled */
   Status = DevMgmt->PowerMgmt.GetOpModeCaps(DevMgmt, &OpModeCaps); 
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("UFS Eye Monitor - GetOpModeCaps failed, status 0x%x\n", Status); 
      return Status; 
   }

   Status = Eyemon->PowerModeChange(Eyemon, &EyemonParams, OpModeCaps.NumSpeedLevels, 1); 
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("UFS Eye Monitor - PmUpdate failed, status 0x%x\n", Status);
      return Status; 
   }

   /* Allocate Buffer for Data Transfer, fill in data, and write the data for Host Side */
   DataSize = UFS_EYEMON_TEST_TRANSFER_SIZE_MB * 1024 * 1024; 
   DataBuffer = AllocatePool (DataSize);  
   if (DataBuffer == NULL) {
      AsciiPrint ("UFS Eye Monitor: Failed to allocate DataBuffer\n");
      return EFI_OUT_OF_RESOURCES; 
   }

   SetMem(DataBuffer, DataSize, 0xBC); 

   if (EyemonMode == HOST_EYEMON) {
      Status = BlkIo->WriteBlocks(BlkIo, BlkIo->Media->MediaId, UFS_EYEMON_TEST_START_LBA, DataSize, DataBuffer); 
      if (Status != EFI_SUCCESS) {
         AsciiPrint ("UFS Eye Monitor - DataTransfer Initial WriteBlocks failed 0x%x\n", Status); 
         return Status; 
      }
   }

   EyemonConfig.TargetTestCount = TargetCount; 

   VoltageSize = (2 * EyemonCaps.VoltageMaxSteps) + 1; 
   if (HostEyemon) {
      VoltageSize += ((MaxCoarseCode / 2) * ((2 * EyemonCaps.VoltageMaxSteps) + 2)); 
   }

   if (SLT == TRUE) {
      ZeroVoltage = TRUE;   
   }

   /* Adjust the VoltageMaxSteps and MaxCoarseCode if we are only interested in voltage = 0 */
   if (ZeroVoltage == TRUE) {
      VoltageMaxSteps = 0; 
      MaxCoarseCode = 0; 
   }
   else {
      VoltageMaxSteps = EyemonCaps.VoltageMaxSteps; 
   }

   for (Lane = 0; Lane < UFS_EYEMON_TOTAL_LANES; Lane++) {
      if ((LaneNum == Lane) || (LaneNum == LANE_ALL)) {
         for (CoarseCode = 0; CoarseCode <= MaxCoarseCode; CoarseCode += 2) {
            if (SLT) {
               SetMem (&EyemonSLTData, sizeof(UFS_EYEMON_SLT_DATA), 0x00);
               EyemonSLTData.TimingStep = UFS_EYEMON_SLT_INITIAL_LEFT_TIMING_STEP;
               EyemonSLTData.ErrorCount = 0xFF; 
               EyemonSLTData.TotalEyeWidth = 0; 
               EyemonSLTData.LeftEyeWidth = -UFS_EYEMON_SLT_INITIAL_EYE_WIDTH; 
               EyemonSLTData.RightEyeWidth = UFS_EYEMON_SLT_INITIAL_EYE_WIDTH;

               TimingStep = EyemonSLTData.TimingStep; 
            }
            else {
               TimingStep = 0 - EyemonCaps.TimingMaxSteps; 
            }

            while (TimingStep <= EyemonCaps.TimingMaxSteps) { 
               for (VoltStep = 0 - VoltageMaxSteps; VoltStep <= VoltageMaxSteps; VoltStep++) { 
                  EyemonParams.LaneNum = Lane;

                  Status = Eyemon->SetCoarseCode(Eyemon, &EyemonParams, CoarseCode); 
                  if (Status != EFI_SUCCESS) {
                     AsciiPrint ("UFS Eye Monitor - SetCoarseCode failed, status 0x%x\n", Status); 
                     goto EyemonEnd; 
                  }

                  if (TimingStep < 0) {
                     EyemonConfig.TimingDirection = 1; 
                     EyemonConfig.TimingSteps = -TimingStep & UFS_EYEMON_STEP_MASK; 
                  }
                  else {
                     EyemonConfig.TimingDirection = 0; 
                     EyemonConfig.TimingSteps = TimingStep & UFS_EYEMON_STEP_MASK; 
                  }

                  if (VoltStep < 0) {
                     EyemonConfig.VoltageDirection = 1; 
                     EyemonConfig.VoltageSteps = -VoltStep & UFS_EYEMON_STEP_MASK; 
                  }
                  else {
                     EyemonConfig.VoltageDirection = 0; 
                     EyemonConfig.VoltageSteps = VoltStep & UFS_EYEMON_STEP_MASK; 
                  }

                  /* Enable EYEMON function */
                  Status = Eyemon->Enable(Eyemon, &EyemonParams, TRUE); 
                  if (Status != EFI_SUCCESS) {
                     AsciiPrint ("UFS Eye Monitor - Enable failed, status 0x%x \n", Status);
                     goto EyemonEnd; 
                  }
                  
                  /* Configure Measurement Condition */
                  Status = Eyemon->Config(Eyemon, &EyemonParams, &EyemonConfig);
                  if (Status != EFI_SUCCESS) {
                     AsciiPrint ("UFS Eye Monitor - Configure failed, status 0x%x\n", Status);
                     goto EyemonEnd; 
                  }

                  /* Update Power Mode with Adapt disabled */
                  Status = Eyemon->PowerModeChange(Eyemon, &EyemonParams, OpModeCaps.NumSpeedLevels, 0); 
                  if (Status != EFI_SUCCESS) {
                     AsciiPrint ("UFS Eye Monitor - PmUpdate failed, status 0x%x\n", Status);
                     goto EyemonEnd; 
                  }

                  /* Start Data Transfer- read for Host and write for Device */
                  while (1) {
                     if (EyemonMode == HOST_EYEMON) {
                        Status = BlkIo->ReadBlocks(BlkIo, BlkIo->Media->MediaId, UFS_EYEMON_TEST_START_LBA, DataSize, DataBuffer); 
                        if (Status != EFI_SUCCESS) {
                           AsciiPrint ("UFS Eye Monitor - DataTransfer ReadBlocks failed 0x%x\n", Status); 
                           goto EyemonEnd;  
                        }
                     }
                     else {
                        Status = BlkIo->WriteBlocks(BlkIo, BlkIo->Media->MediaId, UFS_EYEMON_TEST_START_LBA, DataSize, DataBuffer);
                        if (Status != EFI_SUCCESS) {
                           AsciiPrint ("UFS Eye Monitor - DataTransfer WriteBlocks failed 0x%x\n", Status); 
                           goto EyemonEnd;  
                        }
                     }

                     Status = Eyemon->GetResult(Eyemon, &EyemonParams, &EyemonResult); 
                     if (Status == EFI_NOT_READY) {
                        ; 
                     }
                     else if (Status != EFI_SUCCESS) {
                        AsciiPrint ("UFS Eye Monitor - GetResult failed, status 0x%x\n", Status);
                        goto EyemonEnd; 
                     }
                     else {
                        VoltCoordinate = VoltStep; 

                        if (EyemonMode == HOST_EYEMON) {
                           if (VoltStep > 0) {
                              VoltCoordinate = VoltStep + ((VoltageMaxSteps + 1) * (CoarseCode / 2));
                           }
                           else if (VoltStep < 0) {
                              VoltCoordinate = VoltStep - ((VoltageMaxSteps + 1) * (CoarseCode / 2)); 
                           }
                           else {
                              VoltCoordinate = VoltStep - ((VoltageMaxSteps + 1) * (CoarseCode / 2)); 
                              if (CoarseCode != 0) {
                                 AsciiPrint ("lane %d timing: %d, voltage: %d, error count: %d\n", Lane, TimingStep, VoltCoordinate, EyemonResult.ErrorCount); 
                              }
                              VoltCoordinate = VoltStep + ((VoltageMaxSteps + 1) * (CoarseCode / 2));
                           }
                        }

                        AsciiPrint ("lane %d timing: %d, voltage: %d, error count: %d\n", Lane, TimingStep, VoltCoordinate, EyemonResult.ErrorCount); 

                        if (SLT) {
                           EyemonSLTData.ErrorCount = EyemonResult.ErrorCount; 
                        }

                        break; 
                     }
                  }
               }
               
               if (SLT) {
                  Status = UfsEyemonSLTGetNextTimingStep(&EyemonSLTData); 
                  if (Status != EFI_SUCCESS) {
                     AsciiPrint ("UFS Eye Monitor - SLT GetNextTimingStep failed, status 0x%x\n", Status); 
                     goto EyemonEnd; 
                  }

                  TimingStep = EyemonSLTData.TimingStep; 

                  /* If the Total Eye Width is updated from the initial value of 0,
                     then the SLT screen is complete. Check against expected good
                     eye width. */
                  if (EyemonSLTData.TotalEyeWidth > 0) {
                     if (EyemonSLTData.TotalEyeWidth < EyeWidthThreshold) {
                        AsciiPrint ("UFS Eye Monitor - Lane %d TotalEyeWidth length %d Fail\n", 
                                    Lane, EyemonSLTData.TotalEyeWidth); 
                        AsciiPrint ("UFS Eye Monitor - Pass length %d\n", EyeWidthThreshold);  

                        /* Fill in the Result Buffer if valid. 0x1 indicates failure.
                           1st 64 bytes for Lane 0. Next 64 bytes for Lane 1. */
                        if (ResultBuffer != NULL) {
                           *(ResultBuffer + Lane) = 0x1; 
                        }

                        Status = EFI_DEVICE_ERROR;
                        goto EyemonEnd; 
                     }
                     else {
                        AsciiPrint ("UFS Eye Monitor - Lane %d TotalEyeWidth length %d Pass\n", 
                                    Lane, EyemonSLTData.TotalEyeWidth);

                        /* Fill in the Result Buffer if valid. 0x0 indicates success.
                           1st 64 bytes for lane 0. Next 64 bytes for Lane 1. */
                        if (ResultBuffer != NULL) {
                           *(ResultBuffer + Lane) = 0x0; 
                        }
                     }
                     break;
                  }
               }
               else {
                  TimingStep++; 
               }
            }
         }
      }
   }

EyemonEnd: 
   if (((ZeroVoltage == TRUE) && (SLT == FALSE)) || (Status != EFI_SUCCESS)) {
      AsciiPrint ("\n\n"); 
      Status = DevMgmt->RegOps.RegDump(DevMgmt, STORAGE_REG_PHY);
      if (Status != EFI_SUCCESS) {
         AsciiPrint ("UFS Eye Monitor - CollectDumps failed, status 0x%x\n", Status); 
      }
   }

   /* Set Coarse Code back to 0 */
   Status = Eyemon->SetCoarseCode(Eyemon, &EyemonParams, 0); 
   if (Status != EFI_SUCCESS) {
     AsciiPrint ("UFS Eye Monitor - SetCoarseCode failed, status 0x%x\n", Status); 
   }

   /* Update Power Mode with Adapt enabled again */
   Status = Eyemon->PowerModeChange(Eyemon, &EyemonParams, OpModeCaps.NumSpeedLevels, 1); 
   if (Status != EFI_SUCCESS) {
     AsciiPrint ("UFS Eye Monitor - PmUpdate failed, status 0x%x\n", Status);
   }

   EyemonParams.LaneNum = LaneNum; 
   Status = Eyemon->Enable(Eyemon, &EyemonParams, FALSE);
   if (Status != EFI_SUCCESS) {
      AsciiPrint ("UFS Eye Monitor - Disable failed, status 0x%x\n", Status);
   }

   return Status;
} /* UfsEyemonMain */


