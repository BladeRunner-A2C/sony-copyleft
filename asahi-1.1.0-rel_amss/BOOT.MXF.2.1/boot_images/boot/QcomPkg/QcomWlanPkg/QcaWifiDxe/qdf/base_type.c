/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */


#include "base_type.h"
#include "errno.h"

int efi_status_to_errno(EFI_STATUS Status)
{
    switch (Status)
    {
    case EFI_SUCCESS:
        return 0;
    case EFI_UNSUPPORTED:
        return -ENOTSUPP;
    case EFI_NO_MEDIA:
        return -ENOENT;
    case EFI_DEVICE_ERROR:
        return -ENODEV;
    case EFI_WRITE_PROTECTED:
    case EFI_ACCESS_DENIED:
        return -EACCES;
    case EFI_VOLUME_FULL:
    case EFI_OUT_OF_RESOURCES:
        return -ENOSPC;
    default:
        return -EFAULT;
    }
}