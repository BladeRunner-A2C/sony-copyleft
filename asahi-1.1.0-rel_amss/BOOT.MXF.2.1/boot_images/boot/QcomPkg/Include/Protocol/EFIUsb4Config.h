#ifndef __USB4CONFIG_H__
#define __USB4CONFIG_H__

/** @file     Usb4ConfigProtocol.h 
    @brief    USB4 Config Protocol
    @details  Platform specific APIs to configure USB4 host router.
    @note     
    @ref      Copyright (c) 2020 Qualcomm Technologies Incorporated.
              All Rights Reserved.
              Qualcomm Confidential and Proprietary.

    
**/

#include "Uefi.h"
#include <Protocol/EFIClock.h>
#include <Protocol/EFIHALIOMMUProtocol.h>

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/
/** @cond */
/*  
  Protocol declaration.
*/
typedef struct _USB4_CONFIG_PROTOCOL USB4_CONFIG_PROTOCOL;
/** @endcond */

/** @cond */
/*  
  Protocol version.
*/
#define EFI_USB4_CONFIG_PROTOCOL_REVISION   0x0000000000010000
#define EFI_USB4_CONFIG_PROTOCOL_REVISION_1 0x0000000000010000

/** @endcond */

/*  Protocol GUID definition */
/** @ingroup efi_usbConfig_protocol */
#define USB4_CONFIG_PROTOCOL_GUID \
  {0xa193bb96, 0x51c2, 0x4d82, {0x84, 0x5b, 0x23, 0xce, 0x82, 0xf6, 0x98, 0xac}}

// typedef struct _USB4_phyConfig USB4_phyConfig;


/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/**
  External reference to the USB4 Protocol GUID.
*/
extern EFI_GUID gUsb4ConfigProtocolGuid;

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

#define USB4_PD_MAX_OPTIONS (5)

typedef enum _USB4_HR_INST {
  USB4_HR_INVALID = -1,
  USB4_HR_0 = 0,
  USB4_HR_1 = 1,
  USB4_HR_MAX = 1, // Max Index
  USB4_HR_SIZE = 2,
} USB4_HR_INST;

#define USB4_HR_INVALID(idx) (((idx) <= USB4_HR_INVALID) || ((idx) >= USB4_HR_MAX))

typedef enum _USB4_HR_RING_INDEX {
  USB4_HR_RING_0,
  USB4_HR_RING_1,
  USB4_HR_RING_2,
  USB4_HR_RING_MAX
} USB4_HR_RING_INDEX;

typedef enum _USB4_RING_MODE {
  USB4_RING_MODE_RAW,
  USB4_RING_MODE_FRAME,
  USB4_RING_MODE_MAX
} USB4_RING_MODE;

typedef enum _USB4_RING_DIR {
  USB4_RING_TX,
  USB4_RING_RX,
  USB4_RING_DIR_INVALID,
} USB4_RING_DIR;

typedef enum _USB4_PHY_CFG_MODE {
  USB4_PHY_CFG_MODE_USB4,
  USB4_PHY_CFG_MODE_TBT3
} USB4_PHY_CFG_MODE;

typedef enum _USB4_LINK_OP_GEN {
  USB4_LINK_OP_GEN2 = 0x8,
  USB4_LINK_OP_GEN3 = 0xC
} USB4_LINK_OP_GEN;

typedef struct _USB4_UC_MSG_RING {
  UINT8* BuffPtr; // Array to store MaxEntries (strings) x EntrySizeBytes (bytes in each string)
  UINT32 SizeBytes;
  UINT32 EntrySizeBytes;
  UINT32 MaxEntries;
  UINT32 PrintIdx;  // deque index
  UINT32 PushIdx;   // enque index
  UINT32 NumMsgs;
} USB4_UC_MSG_RING;

typedef enum _USB4_UC_IOCTL_CMD {
  USB4_UC_IOCTL_CMD_BEGIN_HSE           = 0x1,
  USB4_UC_IOCTL_CMD_ENABLE_PHY_PRESETS  = 0x2,
  USB4_UC_IOCTL_CMD_LIMIT_VERBOSITY     = 0x3,
  USB4_UC_IOCTL_CMD_COMPLETE_SLEEP      = 0x4,
  USB4_UC_IOCTL_CMD_WAKE                = 0x5,
  USB4_UC_IOCTL_CMD_PHYSICAL_DISCONNECT = 0x6,
  USB4_UC_IOCTL_CMD_START_TEST          = 0x81,
  USB4_UC_IOCTL_CMD_STOP_TEST           = 0x82,
  USB4_UC_IOCTL_CMD_INVALID             = 0x92,
} USB4_UC_IOCTL_CMD;

typedef enum _USB4_UC_TEST {
  USB4_UC_TEST_SB_EXCHANGE          = 0,
  USB4_UC_TEST_ENTER_LOOPBACK_MODE  = 1,
  USB4_UC_TEST_GENERATE_ERRORS      = 2,
  USB4_UC_TEST_NOT_VALID_TEST       = 3,
} USB4_UC_TEST;

typedef enum _USB4_PD_POWER_ROLE {
  USB4_PD_POWER_ROLE_SRC_DFP,  // SRC + DFP
  USB4_PD_POWER_ROLE_SINK_UFP, // SINK + UFP
} USB4_PD_POWER_ROLE;

typedef enum _USB4_PD_ATTACH_MODE {
  USB4_PD_ATTACH_MODE_SVID0,   // The default SVID reported by the device 
  USB4_PD_ATTACH_MODE_TBT3,    // Finish with EnterMode TBT3 alt mode (if applicable) 
  USB4_PD_ATTACH_MODE_DP_ALT,  // Finish with EnterMode DP alt mode (if applicable) 
  USB4_PD_ATTACH_MODE_USB4,    // For PD3.0 finish with ENTER_USB = 4.0 
  USB4_PD_ATTACH_MODE_USB3,    // Nothing for PD2.0 devices, for PD3.0 ENTER_USB = 3.0 
  USB4_PD_ATTACH_MODE_USB2,    // Nothing for PD2.0 devices, for PD3.0 ENTER_USB = 2.0 
} USB4_PD_ATTACH_MODE;

typedef enum _USB4_PD_CC_ORIENTATION {
  USB4_PD_CC_ORIENTATION_CC1,  // Connectivty on CC1 lines, VCON on CC2 
  USB4_PD_CC_ORIENTATION_CC2,  // Connectivty on CC2 lines, VCON on CC1 
  USB4_PD_CC_ORIENTATION_OPEN, // Not connected   
} USB4_PD_CC_ORIENTATION;

typedef enum _USB4_PD_CABLE_TYPE {
  USB4_PD_CABLE_TYPE_PASSIVE        = 0x0,
  USB4_PD_CABLE_TYPE_ACTIVE_USB4    = 0x1,
  USB4_PD_CABLE_TYPE_ACTIVE_TBT3    = 0x3,
} USB4_PD_CABLE_TYPE;

typedef enum USB4_PD_CABLE_GEN {
  USB4_PD_CABLE_GEN_2 = 0x0,
  USB4_PD_CABLE_GEN_3 = 0x1,
} USB4_PD_CABLE_GEN;

typedef struct _USB4_PD_INFO {
  // TODO: AC duplicate definition until PD port resolved
  USB4_PD_CC_ORIENTATION cc_orientation;
  USB4_PD_ATTACH_MODE current_mode;
  USB4_PD_CABLE_TYPE cable_type; // Active / passive

  USB4_PD_CC_ORIENTATION CcOrientation;
  USB4_PD_ATTACH_MODE CurrentMode;
  USB4_PD_CABLE_TYPE CableType; // Active / passive
  USB4_PD_CABLE_GEN CableGen;   // G2/ G3
  UINT32 NumSupportedModes;     // Number of supported modes in the list
  USB4_PD_ATTACH_MODE Supported[USB4_PD_MAX_OPTIONS];
} USB4_PD_INFO;

#pragma pack(1)

typedef struct _USB4_UC_EVENT_RING {
  UINT32 NumOfEntries : 16;
  UINT32 EntrySize    : 16;
  UINT32 Next;
  UINT32 Rsvd[2];
  UINT8  EventsPtr[1];
} USB4_UC_EVENT_RING;

typedef union _USB4_UC_IOCTL {

  struct {
    UINT32 Cmd            : 8;
    UINT32 DeviceType     : 1;  // 0x1 USB4, 0x0 TBT3 
    UINT32 CCOrientation  : 1;  // 0x0 CC1, 0x1 CC2 (flipped) 
    UINT32 Rsvd0          : 1;
    UINT32 CableType      : 2;  // 0x0 passive, 0x1 usb4 active, 0x3 tbt3 active
    UINT32 CableGen       : 1;  // 0x0 gen2, 0x1 gen3 
    UINT32 Polarityl0tx   : 1;
    UINT32 Polarityl0rx   : 1;
    UINT32 Polarityl1tx   : 1;
    UINT32 Polarityl1rx   : 1;
    UINT32 Rsvd1          : 14;
  } BeginHSE;

  struct {
    UINT32 Cmd:8;
    UINT32 PresetBits:16;
    UINT32 Rsvd:8;
  } EnablePhyPresets;

  struct {
    UINT32 Cmd:8;
    UINT32 MinimumSeverityToOutput:8;
    UINT32 Rsvd:16;
  } LimitVerbosity;

  struct {
    UINT32 Cmd:8;
    UINT32 Rsvd:24;
  } CompleteSleep;

  struct {
    UINT32 Cmd:8;
    UINT32 WakeUpReason:8;
    UINT32 Rsvd:16;
  } Wake;

  struct {
    UINT32 Cmd:8;
    UINT32 Rsvd:24;
  } PhysicalDisconnect;

  struct {
    UINT32 Cmd:8;
    UINT32 TestIndex:8;
    UINT32 TestParams:16;
  } StartTest;

  UINT32 Raw;
}USB4_UC_IOCTL;

#pragma pack()


/*===========================================================================
  FUNCTION DECLARATIONS
===========================================================================*/
#if 0
EFI_STATUS
Usb4PlatformInit(
  IN OUT USB4_CONFIG_PROTOCOL  *This,
  IN USB4_HR_INST HrIdx
);
#endif

EFI_STATUS
Usb4PlatformUnInit(
  IN USB4_CONFIG_PROTOCOL*  This
);

/**
   Poll Host Router Micro-Controller Events
 
   @param[in]      This         - Instance of USB4_CONFIG_PROTOCOL
 
   @retval None.
 
 **/
typedef VOID (*USB4_UC_POLL_EVENTS) (
  IN USB4_CONFIG_PROTOCOL*  This
);

/**
   Set transmit or receive ring base address
 
   @param[in]      This         - Instance of USB4_CONFIG_PROTOCOL
   @param[in]      RingPhyAddr  - Physical address of transmit or receive ring buffer.
 
   @retval EFI_SUCCESS   Succesfully programmed physical base address of ring.
   @retval !EFI_SUCCESS  Failed to program base address of ring.
 
 **/
typedef EFI_STATUS (EFIAPI *USB4_RING_SET_BASE_SIZE)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT64 RingPhyAddr,
  IN UINT32 RingSize
);

/**
   Set transmit or receive ring control
 
   @param[in]      This         - Instance of USB4_CONFIG_PROTOCOL
   @param[in]      Value        - Value of ring control that needs to be programmed.
 
   @retval EFI_SUCCESS   Succesfully programmed ring control register of the ring.
   @retval !EFI_SUCCESS  Failed to program ring control register of ring.
 
 **/
typedef EFI_STATUS (EFIAPI *USB4_RING_SET_RING_CTRL)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT32 Value
);

typedef EFI_STATUS (EFIAPI* USB4_RING_GET_PROD_INDEX)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT16* Value
);

typedef EFI_STATUS (EFIAPI* USB4_RING_GET_CONS_INDEX)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT16* Value
);

typedef EFI_STATUS (EFIAPI* USB4_RING_SET_PROD_INDEX)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT16 Value
);

typedef EFI_STATUS (EFIAPI* USB4_RING_SET_CONS_INDEX)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT16 Value
);


/**
   Set ring PDF mask bits. 
   @param[in]      This         - Instance of USB4_CONFIG_PROTOCOL
   @param[in]      Value        - Value of EOF(higher-16) and SOF(lower-16) mask bits.
 
   @retval EFI_SUCCESS   Succesfully programmed PDF mask bits for ring.
   @retval !EFI_SUCCESS  Failed to program PDF mask bits for ring.
 
 **/
typedef EFI_STATUS (EFIAPI* USB4_RING_SET_PDF_MASK)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT32 Value
);

/**
   Sets 4-bit threshold in receive ring vacancy control register. 
   @param[in]      This         - Instance of USB4_CONFIG_PROTOCOL
   @param[in]      Value        - 4-bit threshold value of vacancy control bits.
 
   @retval EFI_SUCCESS   Succesfully programmed threshold bits in vacancy control register for a ring instance.
   @retval !EFI_SUCCESS  Failed to program threshold bits in vacancy control register for a ring instance.
 
 **/
typedef EFI_STATUS (EFIAPI* USB4_RING_SET_RX_RING_VAC_CTRL)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN UINT8 Thres
);

/**
   Get receive ring vacancy status bit. 
   @param[in]      This         - Instance of USB4_CONFIG_PROTOCOL
   @param[in]      Value        - Value of receive ring vacancy status bit for a ring instance.
 
   @retval EFI_SUCCESS   Succesfully read value of receive ring vacancy status bit for a ring instance.
   @retval !EFI_SUCCESS  Failed to reda value of receive ring vacancy status bit for a ring instance.
 
 **/
typedef EFI_STATUS(EFIAPI* USB4_RING_GET_RX_RING_VAC_STATUS)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  IN BOOLEAN* Value
);

typedef EFI_STATUS (EFIAPI* USB4_RING_GET_INT_STATUS)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  OUT BOOLEAN* State
);

typedef EFI_STATUS (EFIAPI* USB4_RING_GET_RX_VAC_INT_STATUS)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir,
  OUT BOOLEAN* State
);

typedef EFI_STATUS (EFIAPI* USB4_RING_ENABLE_INT)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir
  );

typedef EFI_STATUS (EFIAPI* USB4_RING_DISABLE_INT)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir
  );

typedef EFI_STATUS (EFIAPI* USB4_RING_CLEAR_INT)(
  IN USB4_CONFIG_PROTOCOL* This,
  IN USB4_HR_RING_INDEX RingIdx,
  IN USB4_RING_DIR Dir
  );


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/**
  Protocol declaration.
*/
struct _USB4_CONFIG_PROTOCOL {
  UINT64 Revision;
  
  USB4_HR_INST HrIdx;
  // -----------------------------------------------------------------------
  // Base addresses
  // -----------------------------------------------------------------------
  UINT8* HrBaseAddr;
  UINT8* HiBaseAddr;
  UINT8* UcPerBaseAddr;
  UINT8* UcRamBaseAddr;
  UINT8* PgPropBaseAddr;
  UINT8* UsbApCfgPropAddr;
  UINT8* Lane0BaseAddr;
  UINT8* Lane1BaseAddr;
  UINT8* SideBandBaseAddr;
  // -----------------------------------------------------------------------
  // Platform specific data structures
  // ----------------------------------------------------------------------- 
  USB4_PHY_CFG_MODE PhyMode;
  USB4_LINK_OP_GEN OpGen;  // Gen at which phy will be configured to operate.
  UINT8 NumLanes;
  EFI_CLOCK_PROTOCOL* ClockProtocol;
  EFI_HAL_IOMMU_PROTOCOL* IommuProtocol;
  HAL_IOMMU_fptable_t* SmmuTable;  
  VOID* Usb4SmmuDomain;
  // USB4_phyConfig* Usb4Phy;
  // -----------------------------------------------------------------------
  // Host router micro-controller specific data structures
  // -----------------------------------------------------------------------
  UINT32 UsbApRxTermSts;
  UINT32 CurrEvtIdx; // points to current index that needs servicing by SW.
  volatile USB4_UC_EVENT_RING* EventRingPtr; // AHB access needs to be volatile.
  UINT32 PropreietyErrCnt;
  UINT32 SleepDoneCnt;
  UINT32 TestResCnt;
  USB4_UC_MSG_RING MsgRing;
  USB4_UC_POLL_EVENTS Usb4UcPollEvents;
  // -----------------------------------------------------------------------
  // Platform specific ring interface
  // -----------------------------------------------------------------------
  USB4_RING_SET_BASE_SIZE Usb4RingSetBaseSize;
  USB4_RING_SET_RING_CTRL Usb4RingSetRingCtrl;
  USB4_RING_GET_PROD_INDEX Usb4RingGetProdIndex;
  USB4_RING_GET_CONS_INDEX Usb4RingGetConsIndex;
  USB4_RING_SET_PROD_INDEX Usb4RingSetProdIndex;
  USB4_RING_SET_CONS_INDEX Usb4RingSetConsIndex;  
  USB4_RING_SET_PDF_MASK Usb4RingSetPdfMask;
  USB4_RING_SET_RX_RING_VAC_CTRL Usb4RingSetRxRingVacCtrl;
  USB4_RING_GET_RX_RING_VAC_STATUS Usb4RingGetRxRingVacStatus;
  USB4_RING_GET_INT_STATUS Usb4RingGetIntStatus;
  USB4_RING_GET_RX_VAC_INT_STATUS Usb4RingGetRxVacIntStatus;
  USB4_RING_CLEAR_INT Usb4RingClearInt; 
  USB4_RING_CLEAR_INT Usb4RingClearRxVacInt;
  USB4_RING_ENABLE_INT Usb4RingEnableInt;
  USB4_RING_ENABLE_INT Usb4RingEnableRxVacInt;
  USB4_RING_DISABLE_INT Usb4RingDisableInt;
  USB4_RING_DISABLE_INT Usb4RingDisableRxVacInt;
};
/** @endcond */



#endif /* __EFIUSB4CONFIG_H__ */
