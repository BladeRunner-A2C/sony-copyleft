/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "WlanSupplicant.h"

STATIC
EFI_STATUS
EFIAPI
WlanSupplicantComponentNameGetDriverName(
    IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **DriverName
);

STATIC
EFI_STATUS
EFIAPI
WlanSupplicantComponentNameGetControllerName(
    IN  EFI_COMPONENT_NAME_PROTOCOL *This,
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  ChildHandle OPTIONAL,
    IN  CHAR8                       *Language,
    OUT CHAR16                      **ControllerName
);

GLOBAL_REMOVE_IF_UNREFERENCED EFI_UNICODE_STRING_TABLE mWlanSupplicantDriverNameTable[] = {
  { "eng;en", L"WLAN Supplicant Driver" },
  { NULL, NULL }
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_COMPONENT_NAME_PROTOCOL gWlanSupplicantComponentName = {
  WlanSupplicantComponentNameGetDriverName,
  WlanSupplicantComponentNameGetControllerName,
  "eng"
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_COMPONENT_NAME2_PROTOCOL gWlanSupplicantComponentName2 = {
  (EFI_COMPONENT_NAME2_GET_DRIVER_NAME)WlanSupplicantComponentNameGetDriverName,
  (EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME)WlanSupplicantComponentNameGetControllerName,
  "en"
};

STATIC
EFI_STATUS
EFIAPI
WlanSupplicantComponentNameGetDriverName(
    IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
    IN  CHAR8                        *Language,
    OUT CHAR16                       **DriverName
)
{
    return LookupUnicodeString2(
        Language,
        This->SupportedLanguages,
        mWlanSupplicantDriverNameTable,
        DriverName,
        (BOOLEAN)(This == &gWlanSupplicantComponentName)
    );
}

static
EFI_STATUS
EFIAPI
WlanSupplicantComponentNameGetControllerName(
    IN  EFI_COMPONENT_NAME_PROTOCOL *This,
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  ChildHandle OPTIONAL,
    IN  CHAR8                       *Language,
    OUT CHAR16                      **ControllerName
)
{
    return EFI_UNSUPPORTED;
}
