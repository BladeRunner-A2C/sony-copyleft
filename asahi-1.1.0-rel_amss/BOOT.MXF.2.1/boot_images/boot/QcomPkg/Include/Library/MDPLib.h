#ifndef __MDPLIB_H__
#define __MDPLIB_H__
/*=============================================================================
 
  File: MDPLib.h
 
  Header file for common MDP driver functions
  
 
  Copyright (c) 2011-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <Uefi.h>
#include "MDPTypes.h"

/*===========================================================================

                           Defines

===========================================================================*/

/* Maximum number of display modes supported by a single display */
#define MDP_DISPLAY_MAX_MODES                           16

/* Maximum backlight value */
#define MDP_DISPLAY_MAX_BRIGHTNESS                      100

/* Out of range default brightness value, MDPSetProperty() will enforce required default brightness */
#define MDP_DISPLAY_DEFAULT_BRIGHTNESS                  ((MDP_DISPLAY_MAX_BRIGHTNESS)+ 1)

/* Driver profiling macros */ 
#define MDP_LOG_FUNC_ENTRY(pFuncName, uParam1)          MDPProfiler((uint8*)pFuncName, (uint32)uParam1, TRUE)     
#define MDP_LOG_FUNC_ENTRY2(pFuncName, uParam1, uParam2) \
                                                        MDPProfiler((uint8*)pFuncName, (uint32)(uParam1 | (uParam2<<8)), TRUE)
#define MDP_LOG_FUNC_ENTRY_INFO(pFuncName, uParam1) 

#define MDP_LOG_FUNC_EXIT(pFuncName, uParam1)           MDPProfiler((uint8*)pFuncName, (uint32)uParam1, FALSE)
#define MDP_LOG_FUNC_EXIT2(pFuncName, uParam1, uParam2) \
                                                        MDPProfiler((uint8*)pFuncName, (uint32)(uParam1 | (uParam2<<8)), FALSE)
#define MDP_LOG_FUNC_EXIT_INFO(pFuncName, uParam1)   

/* Max number of display frame buffers */
#define FRAMEBUFFER_MAX_NUMBER                          2

/* Alignment of 256 should be 1 << 8 */
#define MDP_ALIGN_256                                   8
/* Display alignment */
#define MDP_DISPLAY_ALIGN(_value_, _power2_alignment_)  (((_value_) + ((1<<(_power2_alignment_)) - 1)) & ~((1<<(_power2_alignment_)) - 1))

/* Ceil function to round off to the nearest integer */
#define MDP_CEIL(_x_, _y_)                              (((_x_) + (_y_) - 1) / (_y_))

/*===========================================================================

                          Enumerations

===========================================================================*/
typedef enum {
  MDP_DISPLAY_PROPERTY_BACKLIGHT = 0,             /* Backlight level adjustments */
  MDP_DISPLAY_PROPERTY_TRIGGER_UPDATE,            /* Trigger a DSI transfer (smart panels) */
  MDP_DISPLAY_PROPERTY_FIRMWAREENV,               /* Populate the firmware system environment table */
  MDP_DISPLAY_PROPERTY_MODE_INFO,                 /* Populates the Active timing Information */
  MDP_DISPLAY_PROPERTY_POWER_STATE,               /* Display power state on/off */  
  MDP_DISPLAY_PROPERTY_DETECTION_INFO,            /* Display panel detection information */  
  MDP_DISPLAY_PROPERTY_DISPLAY_CONFIG,            /* Display info from the panel configuration file */
  MDP_DISPLAY_PROPERTY_ABL_INTERFACE_INIT,        /* Initialize display data partition & ABL interface */
  MDP_DISPLAY_PROPERTY_SURFACE_RECT,              /* Configure surface and source, dest rectangles for the display */
  MDP_DISPLAY_PROPERTY_MODE_INDEX,                /* Index of panel physical mode */
  MDP_DISPLAY_PROPERTY_FRAMEBUFFER_INFO,          /* Populates framebuffer format info */
  MDP_DISPLAY_PROPERTY_INTERFACE_AVAILABLE,       /* Check the availability of a display interface */
  MDP_DISPLAY_PROPERTY_SET_CONNECTION_STATUS,     /* Set the display connection status */
  MDP_DISPLAY_PROPERTY_GET_PANEL_EDID,            /* Populates Panel Edid Information */
  MDP_DISPLAY_PROPERTY_SET_CLOCK_REFCOUNT,        /* Set ref count for clocks */
  MDP_DISPLAY_PROPERTY_MAX,
  MDP_DISPLAY_PROPERTY_FORCE_32BIT = 0x7FFFFFFF
} MDP_Display_Property;




/*===========================================================================

                        Common Structures

===========================================================================*/



/*===========================================================================

                          API Structures

===========================================================================*/


/* 
 * MDPInit Parameters
 */
typedef struct
{
  uint32  uMDPVersionMajor;                        /* MDP Major version */
  uint32  uMDPVersionMinor;                        /* MDP Minor version */
  uint32  uMDPVersionRevision;                     /* MDP Revision */

  bool32  aSupportedDisplays[MDP_DISPLAY_MAX];     /* List of display supported on this platform */
  
} MDP_InitParamsType;



/* 
 * MDPPower Parameters
 */
typedef struct
{
  bool32  bPowerOn;                                /* Power up this display, FALSE=power down */
  
} MDP_PowerParamsType;


/* 
 * MDP Mode structure
 */
typedef struct
{
  uint32  uModeIndex;                             /* Mode index */
  uint32  uWidth;                                 /* Mode width in pixels */
  uint32  uHeight;                                /* Mode height in pixels */
  uint32  uRefreshRate;                           /* Mode refresh rate in Q16.16 */
  bool32  bInterlaced;                            /* Mode is interlaced */
} MDP_ModeInfo;


/* 
 * MDPDetect Parameters
 */
typedef struct
{
  uint32       bDisplayDetected;                   /* Indicates if the display was detected */
  uint32       uSupportedModes;                    /* List the number of supported modes */
  uint32       uModeSelected;                      /* Mode selected */
  MDP_ModeInfo aModeList[MDP_DISPLAY_MAX_MODES];   /* List of support display modes */
} MDP_DetectParamType;



/* 
 * MDPSetMode Parameters
 */
typedef struct
{
  uint32          uModeIndex;                      /* Mode index to select */
  MDPSurfaceInfo  sSurfaceInfo;                    /* Source surface */
  MDPRectType     sRectInfo;                       /* Source cropping rect */
} MDP_SetModeParamType;

/* 
 * MDPSetConnectionStatus Parameters
 */
typedef struct
{
  bool32                        bConnected;        /* TRUE = display plugged in, FALSE = display plugged out */
  MDP_HotPlugEventDataType     *pHotPlugData;      /* Pointer to additional HPD data */
} MDP_SetConnectionStatusParamType;

/*
 * MDPSetClockRefCountType
 */
typedef struct
{
  char *pClockName;
  int32 iRefCount;
} MDPSetClockRefCountType;
 
#pragma pack(push)
#pragma pack(4)

/* UEFI parameters passed to the system variable
*/
typedef struct
{
  uint32 uVersionInfo;                            /* Version info of this structure */
  uint32 uPlatformId;                             /* Identifies the current platform ID */
  uint32 uChipsetId;                              /* Identifies the current platform chipset ID */
  uint32 uPlatformVersion;                        /* Platform version */
  /* Frame buffer information */
  uint32 uFrameBufferAddress;                     /* Memory address of Frame buffer used by UEFI */
  uint32 uFrameBufferSize;                        /* Size in bytes of total carved out frame buffer */
  uint32 uFrameBufferPixelDepth;                  /* Image/source bit depth in bits (16, 24, etc) of Frame buffer used by UEFI */
  uint32 uFrameBufferImagePxWidth;                /* Image width on screen (in pixel) */
  uint32 uFrameBufferImagePxHeight;               /* Image height on screen (in pixel) */
  uint32 uFrameBufferImageStride;                 /* Image plane stride */
  /* Primary panel configuration */
  uint32 uPrimaryPanelId;                         /* Panel ID read from the primary panel */
  uint32 uPrimaryPanelFlags;                      /* Primary display flags */
  uint32 uPrimaryPanelBacklightLevel;             /* Primary panel backlight level in % */
  /* External panel configuration */
  uint32 uExternalPanelFlags;                     /* External display flags */
  /* DDR configuration: Highest bank bit */
  uint32 uHighestBankBit;                         /* Highest Bank Bit*/
  /* Display reserved memory information */
  uint64 uReservedMemoryAddress;                  /* Reserved memory address */
  uint64 uReservedMemorySize;                     /* Reserved memory size in bytes */
  /* DDR configuration: Max channels */
  uint32 uMaxDDRChannels;                         /* Max DDR Channels */
  /* Secondary panel configuration */
  uint32 uSecondaryPanelId;                       /* Panel ID read from the secondary panel */
  uint32 uSecondaryPanelFlags;                    /* Secondary display flags */
  uint32 uSecondaryPanelBacklightLevel;           /* Secondary panel backlight level in % */
  /* Reserved */
  uint32 uReserved[7];                            /* Reserved */
} MDP_FirmwareEnvVariableType;

#pragma pack(pop)

/*
 * Panel Edid Parameters
 */
typedef struct
{
  uint8           *pEdid;                            /* Panel Edid */
  uint32           uSize;                            /* Panel Edid size */
} MDP_PanelEdidParamType;

/* 
 * MDPProperty Parameters
 */
typedef union
{
  uint32                             uBacklightLevel;                            /* MDP_DISPLAY_PROPERTY_BACKLIGHT */
  bool32                             bDisplayPwrState;                           /* MDP_DISPLAY_PROPERTY_POWER_STATE */
  bool32                             bDisplayDetected;                           /* MDP_DISPLAY_PROPERTY_DETECTION_INFO, MDP_DISPLAY_PROPERTY_SURFACE_REC */ 
  MDP_SetModeParamType               sModeParams;                                /* MDP_DISPLAY_PROPERTY_MODE_INFO */
  bool32                             (*pSupportedDisplayList)[MDP_DISPLAY_MAX];  /* MDP_DISPLAY_PROPERTY_ABL_INTERFACE_INIT */
  uint32                             uIndex;                                     /* MDP_DISPLAY_PROPERTY_MODE_INDEX */
  MDP_SetConnectionStatusParamType   sConnectionStatus;                          /* MDP_DISPLAY_PROPERTY_SET_CONNECTION_STATUS */
  MDP_PanelEdidParamType             sEDID;                                      /* MDP_DISPLAY_PROPERTY_GET_PANEL_EDID */
  MDPSetClockRefCountType            sClockRefCount;                             /* MDP_DISPLAY_PROPERTY_SET_CLOCK_REFCOUNT */
  MDP_FirmwareEnvVariableType       *pFirmwareEnvInfo;                           /* MDP_DISPLAY_PROPERTY_FIRMWAREENV */
} MDP_PropertiesParamType;

/* 
 * Structure for DP Alt Mode HPD connection status
 */
typedef struct 
{
  MDP_DP_AltModeConnectionPolarityType       eConnectionPolarity;         /* Connection polarity */
  MDP_DP_AltModeConnectionPinAssignmentType  eConnectionPinAssignment;    /* Connection pin assignment */
} MDP_DP_AltModeHPDConnectionStatus;


/*===========================================================================

                        Public Functions

===========================================================================*/

/* Minimal init flag does minimal initialization of mdp which is required when we resume from power collapse */
#define MDP_INIT_FLAG_MINIMAL_INIT                   0x00000001
#define MDP_INIT_FLAG_MMU_INIT                       0x00000002

/* Partition handles are invalidated. Signal MDP to avoid using saved handles. Passed as a flag to MDPExitBoot call*/
#define MDP_EXIT_FLAG_INVALIDATE_GPT                 0x00000001

/****************************************************************************
*
** FUNCTION: MDPInit()
*/
/*!
* \brief
*   This function will initialize the MDP core and report information about the core.
*
* \param [out] pMDPInitParams   - Information regarding the hardware core
*        [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPInit(MDP_InitParamsType *pMDPInitParams, uint32 uFlags);


/****************************************************************************
*
** FUNCTION: MDPAcquireLockOrFail()
*/
/*!
* \brief
*   This function will try to get the specified lock.
*
* The function will acquire the lock if not already acquired
* It will return FAIL if lock is already acquired 
*
* \param  eLock              - Lock to acquire 
*
* \retval MDP_STATUS_OK      - Lock acquired successfully
* \retval MDP_STATUS_FAILED  - Failed to acquire Lock 
*
****************************************************************************/
MDP_Status  MDPAcquireLockOrFail(MDP_Lock_Type eLock);


/****************************************************************************
*
** FUNCTION: MDPReleaseLock()
*/
/*!
* \brief
*   This function will release the specified lock.
*
* \param  eLock          - Lock to release 
*
* \retval MDP_STATUS_OK  - Lock released successfully
*
****************************************************************************/
MDP_Status  MDPReleaseLock(MDP_Lock_Type eLock);


/****************************************************************************
*
** FUNCTION: MDPPower()
*/
/*!
* \brief
*   This function will power up and initialize the interface needed for a particular display.
*
* \param [in] eDisplayId       - The display to initialize
*        [in] pMDPPowerParams  - Power configuration
*        [in] uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPPower(MDP_Display_IDType eDisplayId, MDP_PowerParamsType *pMDPPowerParams, uint32 uFlags);


/****************************************************************************
*
** FUNCTION: MDPDetect()
*/
/*!
* \brief
*   This function will detect the presence of a display and supported modes.
*
* \param [in] eDisplayId       - The display to initialize
*        [in] pMDPDetectParams - Information regarding the hardware core
*        [in] uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPDetect(MDP_Display_IDType eDisplayId, MDP_DetectParamType *pMDPDetectParams, uint32 uFlags );



/****************************************************************************
*
** FUNCTION: MDPSetMode()
*/
/*!
* \brief
*   This function setup the display for a particular mode.
*
* \param [in] eDisplayId        - The display to initialize
*        [in] pMDPSetModeParams - Mode setup parameters
*        [in] uFlags            - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPSetMode(MDP_Display_IDType eDisplayId, MDP_SetModeParamType *pMDPSetModeParams, uint32 uFlags );


/****************************************************************************
*
** FUNCTION: MDPSetProperty()
*/
/*!
* \brief
*   This function will configure a specific property of the display
*
* \param [in] eDisplayId        - The display to initialize
*        [in] eProperty         - The particular property to set
*        [in] pMDPSetModeParams - Mode setup parameters
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPSetProperty(MDP_Display_IDType eDisplayId, MDP_Display_Property eProperty, MDP_PropertiesParamType *pMDPPropertiesParams);


/****************************************************************************
*
** FUNCTION: MDPGetProperty()
*/
/*!
* \brief
*   This function will retrieve a specific property of the display
*
* \param  [in] eDisplayId           - The display to initialize
*         [in] eProperty            - The particular property to set
*         [in] pMDPPropertiesParams - Property parameters
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPGetProperty(MDP_Display_IDType eDisplayId, MDP_Display_Property eProperty, MDP_PropertiesParamType *pMDPPropertiesParams);


/****************************************************************************
*
** FUNCTION: MDPDeInit()
*/
/*!
* \brief
*   This function will de-initializes the panel interfaces
*
* \param [in]  eDisplayId       - Display to de-initialize
* \param [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPDeInit(MDP_Display_IDType eDisplayId, uint32 uFlags);


/****************************************************************************
*
** FUNCTION: MDPSetCoreClock()
*/
/*!
* \brief
*   This function will setup the MDP core clock, enable footswitch, and restore TZ of register access
*
* \param [in]  uFlags           
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPSetCoreClock(uint32 uFlags);


/****************************************************************************
*
** FUNCTION: MDPTerm()
*/
/*!
* \brief
*   This function will deinitialize the MDP core and free all resources.
*
* \param [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPTerm(uint32 uFlags);


/****************************************************************************
*
** FUNCTION: MDPProfiler()
*/
/*!
* \brief
*   This function performs the profiling of functions 
*
* \param [in]  pFuncName    - Function name
* \param [in]  uParam1      - Display ID, Property or Mode info depending on the function 
* \param [in]  bEntry       - Function entry or exit. True - entry; False - exit;
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPProfiler(uint8 *pFuncName, uint32 uParam1, bool32 bEntry);


/****************************************************************************
*
** FUNCTION: MDPExitBoot()
*/
/*!
* \brief
*   This function performs house cleaning before UEFI exit
*
* \param [in]  uFlags           - Reserved
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPExitBoot(uint32 uFlags);

/****************************************************************************
*
** FUNCTION: MDPUpdateCoreClockAndBandwidth()
*/
/*!
* \brief
*   wrapper to update both bandwidth and core clock
*
* \param [in]  eDisplayId         -  the specific display device     
*        [in]  eSrcColorFormat    -  source color format
*        [in]  uSrcWidthPixels    -  source width in pixels
*        [in]  uSrcHeightPixels   -  source height in pixels
*        [in]  bPowerOn           -  flag to indicate whether it is in power process
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPUpdateCoreClockAndBandwidth(MDP_Display_IDType eDisplayId, MDP_PixelFormatType eSrcColorFormat, uint32 uSrcWidthPixels, uint32 uSrcHeightPixels, bool32 bPowerOn);

#endif // __MDPLIB_H__

