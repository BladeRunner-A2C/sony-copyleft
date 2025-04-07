/** 
  @file  HypDtbo.h
  @brief HypBootInfo struct defines.
*/
/*=============================================================================
Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------

=============================================================================*/

#define HYP_BOOTINFO_MAGIC  0xC06B0071
#define RMVM_DTBO           0x0

typedef struct _HypBootInfoStruct {
    UINT32 HypBootInfoMagic;
    UINT32 HypBootInfoVersion;

    /*Size of this structure, in Bytes*/
    UINT32 HypBootInfoSize;
    UINT32 PilEnable;
    struct {
        UINT32 VmType;
        UINT32 NumDtbos;
        union {
            struct {
                UINT64 DtboBase;
                UINT64 DtboSize;
            } LinuxAarch64[4];
            
            /*union padding*/
            UINT32 VmInfo[16];
        } Info;
        UINT32 VirqBase;
    } HlosInfo;
} __attribute__ ((packed)) HypBootInfoStruct;

typedef struct _DtboInfoStruct {
    UINT64 DtboAddress;
    UINT64 DtboSize;
}DtboInfoStruct;

