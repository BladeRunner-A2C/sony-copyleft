/*=============================================================================
 
  File: DisplayDxe.h
 
  Display driver for UEFI
  
 
    Copyright (c) 2011-2023 Qualcomm Technologies, Inc.
    All Rights Reserved
    Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
#ifndef __DISPLAYDXE_H__
#define __DISPLAYDXE_H__
  
#include <Uefi.h>
#include <Library/KernelLib.h>
#include <Protocol/EdidActive.h>
#include <Protocol/EdidDiscovered.h>
#include "MDPLib.h"

/**********************************************************************************************************************
 * Defines
 **/

#define GRAPHICS_OUTPUT_PROTOCOL_REVISION  0x0001000

#define DISPLAYDXE_MAX_MODES               8

#define DISPLAYDXE_DEFAULT_MDP_FORMAT      MDP_PIXEL_FORMAT_ARGB_8888_32BPP
#define DISPLAYDXE_FSD_MDP_FORMAT          MDP_PIXEL_FORMAT_RGB_PLANAR_888_8BPP

#define DISPLAYDXE_DEFAULT_PIXEL_FORMAT    PixelBlueGreenRedReserved8BitPerColor
#define DISPLAYDXE_DEFAULT_BYTES_PER_PIXEL 4
#define DISPLAYDXE_RED_MASK                0xFF0000
#define DISPLAYDXE_GREEN_MASK              0x00FF00
#define DISPLAYDXE_BLUE_MASK               0x0000FF
#define DISPLAYDXE_ALPHA_MASK              0x000000


/**********************************************************************************************************************
 * Macros
 **/
#define DISPLAYDXE_PHYSICALADDRESS32(_x_) (UINTN)((_x_) & 0xFFFFFFFF)


/* Display Init Event */
extern EFI_EVENT gDisplayInitEvent;

/**********************************************************************************************************************
 *   Function Prototypes.
 **/


// EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE Handler
EFI_STATUS
DisplayDxe_SetMode (
  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
  UINT32                       ModeNumber);

// EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE_EXT Handler
EFI_STATUS
DisplayDxe_SetModeExt (
  UINT32                       DisplayId,
  UINT32                       ModeNumber,
  UINT32                       Flags);
  
// EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE Handler
EFI_STATUS
DisplayDxe_QueryMode (
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  UINT32                                ModeNumber,
  UINTN                                 *SizeOfInfo,
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info);

// EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT  Handler
EFI_STATUS
DisplayDxe_Blt (
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
    IN  MDP_Display_IDType                      eDisplayId,
    IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,
    IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
    IN  UINTN                                   SourceX,
    IN  UINTN                                   SourceY,
    IN  UINTN                                   DestinationX,
    IN  UINTN                                   DestinationY,
    IN  UINTN                                   Width,
    IN  UINTN                                   Height,
    IN  UINTN                                   Delta);

//  Memory map update
EFI_STATUS
DisplayDxeMemmapUpdate (void);

// Register LPM Call back 
EFI_STATUS DisplayPwr_InitLPMSupport(BOOLEAN InitLpm);

/**********************************************************************************************************************
 *   Structures
 **/


/* EFI_DISPLAY_DEVICE_PATH */
typedef struct {
  VENDOR_DEVICE_PATH        DisplayDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  EndDevicePath;
} EFI_DISPLAY_DEVICE_PATH;

/* FrameBufferOffsetType */
typedef struct 
{
     UINT32    uFrameWidth;
     UINT32    uFrameHeight;
     UINT32    uFrameBytesPerPixel;
     UINT64   *pFrameBufferStart;
     UINT64    uFrameBufferLength;
     UINT32    uStride;
} FrameBufferOffsetType;

/* Panel EDID Info */
typedef struct
{
  UINT8                                *pEdidBuffer;                                          /* EDID buffer used for EDID Protocols                         */
  UINT32                                uEdidSize;                                            /* EDID buffer size                                            */
  EFI_EDID_ACTIVE_PROTOCOL              sEdidActiveProtocol;                                  /* EDID Active Protocol Info                                   */
  EFI_EDID_DISCOVERED_PROTOCOL          sEdidDiscoveredProtocol;                              /* EDID Discovered Protocol Info                               */
} EDIDInfoType;


/* DisplayDxe_CurrentMode */
typedef struct 
{
  BOOLEAN                               bModeSet;                                             /* Indicants if a mode has been configured yet                 */
  EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE     sProtocolInfo;                                        /* Information returned from EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE */
  UINT32                                uVirtualModeIndex;                                    /* indicates the current virtual mode                          */
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  sCurrentModeInfo;                                     /* Structure information about each mode                       */
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  aDxeModeList[MDP_DISPLAY_MAX][DISPLAYDXE_MAX_MODES];  /* List of all of the Dxe modes (including virtual)            */
  UINT32                                uNumModes[MDP_DISPLAY_MAX];                           /* Total number of supported modes per display                 */
  UINT32                                uSelectedModeIndex[MDP_DISPLAY_MAX];                  /* Selected Mode Index                                         */
  BOOLEAN                               bExtSupported;                                        /* Is external display supported                               */
  EFI_EVENT                             UIActiveEvent;                                        /* Event handle for UI_Active                                  */
  EFI_EVENT                             UIIdleEvent;                                          /* Event handle for UI_Idle                                    */
  UINT32                                uExitFlags;                                           /* Flags to be used while shutting down                        */
  UINT32                                eDisplayFBAttrib;                                     /* Display frame buffer memory attributes                      */
  UINT32                                uMultiThreadded;                                      /* MultiThreadding is enabled                                  */
  LockHandle                           *hModeLock;                                            /* Mode set lock for thread synchronization                    */
  Thread                               *hDispThread;                                          /* Set mode thread handle                                      */
  UINT32                                uDisplayFBWidth;                                      /* Default frame buffer width, regardless of the virtual mode  */
  UINT32                                uDisplayFBHeight;                                     /* Default Frame buffer height, regardless of the virtual mode */
  UINT32                                uBytesPerPixel;                                       /* Default frame buffer bytes per pixel                        */
  UINT32                                uNumPlanes;                                           /* Default format num of planes                                */
  MDP_PixelFormatType                   uFBPixelFormat;                                       /* Frame Buffer Pixel format                                   */	
  FrameBufferOffsetType                 aFrameBuffers[FRAMEBUFFER_MAX_NUMBER];                /* Display frame buffer info                                   */
  UINT64                                uSplashBufferBase;                                    /* Splash buffer DDR memory base, from Display Reserved region */
  UINT64                                uSplashBufferSize;                                    /* Splash buffer DDR memory Size (in bytes), from Display 
                                                                                                 Reserved region                                             */
  EDIDInfoType                          sEdidInfo;                                            /* Contains info about panel EDID and EDID protocols           */
} DisplayDxe_ModeInfo;


#endif // __DISPLAYDXE_H__
