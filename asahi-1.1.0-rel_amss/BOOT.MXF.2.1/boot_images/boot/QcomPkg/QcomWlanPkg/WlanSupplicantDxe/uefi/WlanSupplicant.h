/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __EFI_WLAN_SUPPLICANT_H
#define __EFI_WLAN_SUPPLICANT_H

#include <Protocol/WiFi2.h>
#include <Protocol/Supplicant.h>
#include <Protocol/EapConfiguration.h>
#include <Protocol/ServiceBinding.h>
#include <Protocol/LoadedImage.h>

#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include "wpas_glue.h"

// User define EFI_SUPPLICANT_DATA_TYPE to set MFP
#define EfiSupplicant80211UserMfp           (EfiSupplicantDataTypeMaximum + 1)
#define EfiSupplicant80211RsnxeCapability   (EfiSupplicantDataTypeMaximum + 2)

#define SUPPLICANT_SERVICE_SIGNATURE    SIGNATURE_32('S', 'U', 'P', 'S')
#define SUPPLICANT_INSTANCE_SIGNATURE   SIGNATURE_32('S', 'U', 'P', 'I')

typedef struct _SUPPLICANT_SERVICE {
    UINT32                           Signature;
    EFI_HANDLE                       ImageHandle;
    EFI_SERVICE_BINDING_PROTOCOL     ServiceBinding;

    // The supplicant instance list
    UINTN                            ChildrenNumber;
    LIST_ENTRY                       ChildrenList;

    EFI_LOADED_IMAGE_PROTOCOL        *Image;
} SUPPLICANT_SERVICE;

typedef struct {
    UINT32                           Signature;

    // Link to parent
    SUPPLICANT_SERVICE               *SupplicantService;
    EFI_HANDLE                       Handle;

    // Link the list
    LIST_ENTRY                       Node;

    // Protocols
    EFI_SUPPLICANT_PROTOCOL          SupplicantProtocol;
    EFI_EAP_CONFIGURATION_PROTOCOL   EapCfgProtocol;

    EFI_80211_AKM_SUITE_SELECTOR     *SupportedAKMSuites;
    EFI_80211_CIPHER_SUITE_SELECTOR  *SupportedSWCipherSuites;
    EFI_80211_CIPHER_SUITE_SELECTOR  *SupportedHWCipherSuites;

    // LinkState
    EFI_80211_LINK_STATE              LinkState;

    struct wpas                       wpas;
    bool                              SaeAkm;
    struct wpas_glue_cbs              wpa_cbs;
    u32                               SuiteType;
    u8                                Mfp;
    u8                                GroupCipher;
    u8                                PairwiseCipher;
    u8                                IsOneXCompleted;
} SUPPLICANT_INSTANCE;

#define SUPPLICANT_SERVICE_FROM_THIS(_x) \
  CR ((_x),                              \
      SUPPLICANT_SERVICE,                \
      ServiceBinding,                    \
      SUPPLICANT_SERVICE_SIGNATURE)

#define SUPPLICANT_INSTANCE_FROM_SUPP_PROTO(_x) \
  CR ((_x),                                     \
      SUPPLICANT_INSTANCE,                      \
      SupplicantProtocol,                       \
      SUPPLICANT_INSTANCE_SIGNATURE)

#define SUPPLICANT_INSTANCE_FROM_EAP_PROTO(_x)  \
  CR ((_x),                                     \
      SUPPLICANT_INSTANCE,                      \
      EapCfgProtocol,                           \
      SUPPLICANT_INSTANCE_SIGNATURE)

EFI_STATUS
SupplicantServiceInitInstance(
    IN  SUPPLICANT_SERVICE   *SupplicantService,
    OUT SUPPLICANT_INSTANCE  *Instance
);

VOID
SupplicantServiceDeinitInstance(
    IN  SUPPLICANT_SERVICE   *SupplicantService,
    OUT SUPPLICANT_INSTANCE  *Instance
);

extern SUPPLICANT_SERVICE gSupplicantService;

STATIC inline EFI_LOADED_IMAGE_PROTOCOL *GetDriverLoadedImage() {
    return gSupplicantService.Image;
}

#endif // !__EFI_WLAN_SUPPLICANT_H
