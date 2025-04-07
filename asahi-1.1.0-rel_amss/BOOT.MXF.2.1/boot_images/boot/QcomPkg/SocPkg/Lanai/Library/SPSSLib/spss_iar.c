/** @file spss_iar.c

  Secure Processor SubSystem (SPSS) Insider Attack Resistance (IAR) support.

  Copyright (c) 2019 - 2023,  Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
 when         who     what, where, why
 --------     ---     -----------------------------------------------------------
 01/03/23     vp      Fix KW Warnings
 01/23/20     kv      Updates for Lahaina support
 08/29/19     db      load app cmacs to ddr fix
 08/27/19     db      load app cmacs to ddr
 08/15/19     as      reduce log messages
 07/25/19     as      read spu status registers
 06/16/19     as      Initial revision

=============================================================================*/

//-----------------------------------------------------------------------------
//  Include Files
//-----------------------------------------------------------------------------

// standard include files
#include <stdint.h>     // uint32_t
#include <stdbool.h>    // bool, true, false
#include <string.h>     // memset()
#include <errno.h>      // EFAULT

// UEFI basic include
#include <Uefi.h>       // EFI_STATUS
#include <DALSys.h>     // DALSYS_memscpy()
//#include "busywait.h"	// busywait(usec)

// Library includes
#include <Library/DebugLib.h>       // DEBUG()
#include <Library/QcomLib.h>        // ReadFile()
#include <Library/QcomBaseLib.h>    // AsciiStrCpyS()
#include <Library/BaseMemoryLib.h>  // CopyMem()
#include <Library/MemoryAllocationLib.h>    // AllocateZeroPool()
#include <Library/UefiBootServicesTableLib.h>   // gBS
#include <Library/UncachedMemoryAllocationLib.h>    // UncachedAllocatePool()

// Protocol includes
#include <Protocol/EFIPIL.h>        // PIL_SUBSYS_CFG_TYPE
#include <Protocol/EFIHWIO.h>       // MapRegionByAddress()
#include <Protocol/EFIScm.h>        // ScmSipSysCall()
#include <Protocol/EFIPILProxy.h>   // PilProxyHandleEvent

#include <HALbootHWIO.h>            // HWIO_QFPROM_RAW_OEM_CONFIG_ROW0_LSB_ADDR
#include <HALhwio.h>                // in_dword()
#include <scm_sip_interface.h>      // HYP_MEM_PROTECT_ASSIGN_PARAM_ID , hyp_memprot_assign_s

//-----------------------------------------------------------------------------
//  Defines , enums , types
//-----------------------------------------------------------------------------

// Uncommnt the following line to enable IAR UEFI *debug* messages
//#define IAR_DEBUG_ENABLE 1

#ifdef IAR_DEBUG_ENABLE
    #define LOGD(fmt, args...) DEBUG((EFI_D_VERBOSE, "SPSSDxe [%a] D: "fmt"\r\n", __FUNCTION__, ##args));
#else
    #define LOGD(fmt, args...) // don't print debug level messages, just error and info messages
#endif    
#define LOGE(fmt, args...) DEBUG((EFI_D_ERROR, "SPSSDxe [%a] E: "fmt"\r\n", __FUNCTION__, ##args));
#define LOGI(fmt, args...) DEBUG((EFI_D_WARN,  "SPSSDxe [%a] I: "fmt"\r\n", __FUNCTION__, ##args));

#define IAR_STATE_DISABLED  0
#define IAR_STATE_ACTIVATED 3

#ifndef BIT
    #define BIT(x) (1<<(x))
#endif    

// Just let me debug will you :-)
#ifdef DEBUG
    #pragma clang diagnostic ignored "-Wint-to-pointer-cast"
    #pragma clang diagnostic ignored "-Wunused-function"
    #pragma clang diagnostic ignored "-Wunused-variable"
    #pragma clang diagnostic ignored "-Wint-conversion"
#endif

#define PIL_SPSS_MAX_AREA_SIZE (1024*1024) // 1MB

// Maximum string length in chars
#define MAX_PATH_LEN 128

#define SP_CNOC_SP_SCSR_HW_VERSION	                0x1880000
#define SP_CNOC_SP_SCSR_RMB_ERR_STATUS	            0x188103C
#define SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(m)    (0x0188200C + (0x4*m))

#define SP_CNOC_SP_SCSR_BASE_ADDR                   0x1880000
#define SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS	    0x188101C

#define PBL_DONE        BIT(25)
#define SW_INIT_DONE    BIT(24)

#define SP_READY (PBL_DONE | SW_INIT_DONE)

// spss image (firmware and 3 apps) is padded to 960 KB before double-signed
#define PIL_MEM_SIZE    (960*1024)

// IAR-MEM *must* foloow the PIL-MEM
#define IAR_MEM_SIZE    (4*1024)

// 8.3 format xxxxxxxx.yyy
#define MAX_UEFI_FILE_NAME (8+1+3)

// "nvm", "asym","crypt","keym"
#define MAX_QCOM_UEFI_APPS  4

// Names unknown, we name them uefi0, uefi1, uefi2 ..
#define MAX_3RD_PARTY_UEFI_APPS  3

// qti + 3rd party uefi apps
#define MAX_SPU_UEFI_APPS   (MAX_QCOM_UEFI_APPS + MAX_3RD_PARTY_UEFI_APPS)

#define CMAC_SIZE_IN_BYTES  16
#define CMAC_SIZE_IN_DWORDS (CMAC_SIZE_IN_BYTES/sizeof(uint32_t))

#ifndef ARRAY_SIZE
    #define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif 

#ifndef SZ_4K
    #define SZ_4K (4 * 1024)
#endif 

//-----------------------------------------------------------------------------
//  private variables
//-----------------------------------------------------------------------------

static EFI_HWIO_PROTOCOL *m_pHWIOProtocol = NULL;
static QCOM_SCM_PROTOCOL *m_pQcomScmProtocol = NULL; 

static uint32_t *m_sp_regs_ptr = NULL;

static uint32_t m_fw_cmac[CMAC_SIZE_IN_DWORDS]  = {0}; // 16 bytes - saved cmac in IAR-DB

// There are 3 SPU applications that get loaded in UEFI - saved cmacs
static uint32_t m_apps_cmac[MAX_QCOM_UEFI_APPS][CMAC_SIZE_IN_DWORDS]  = {0};

// There might be 3rd party SPU applications that get loaded in UEFI - saved cmacs
static uint32_t m_3rd_party_apps_cmac[MAX_3RD_PARTY_UEFI_APPS][CMAC_SIZE_IN_DWORDS]  = {0};

// DOS name format "8.3" + null termination
// The file name version and type chars are set according to reading SOC fuses
// The name below is the default name.
static char m_fw_name[MAX_UEFI_FILE_NAME] = "spss1t";

static char m_app_names[MAX_QCOM_UEFI_APPS][MAX_UEFI_FILE_NAME] = {"nvm", "asym", "crypt", "keym"};

// The index 0/1/2/3 etc, is appended to the base name
// i.e. uefi0, uefi1, uefi2
static char m_3rd_party_app_base_name[MAX_UEFI_FILE_NAME] = "uefi";

static char m_soc_ver = 0;
static char m_fw_type = 0;

static uint64_t m_buf_addr = 0;
static size_t m_buf_size = 0;

static int m_iar_state = 0;

static EFI_STATUS SpssPilProxyHandleEvent (UINT32 PILEvent, VOID* PILEventCtxt);

static EFI_PIL_PROXY_PROTOCOL m_SpssPilProxyProtocol =
{
   EFI_PIL_PROXY_PROTOCOL_VERSION,
   SpssPilProxyHandleEvent
};

size_t m_spss_image_size = 0;

//-----------------------------------------------------------------------------
//  private functions
//-----------------------------------------------------------------------------

/**
    strerror()
    @brief convert errno to string 

    @param[in] errno

    @return string with description
*/
char *strerror(int err)
{
    if (err < 0)
        err = -err;
        
    switch(err) {
        case ENOENT:    return "ENOENT: No such file or directory";
        case EACCES:    return "EACCES: Permission denied";
        case ESRCH:     return "ESRCH:  No such process";
    }
    
    return "unknown";
}

/**
    iar_get_protocols()
    @brief use LocateProtocol() to get relevant protocols pointer to function table.
    
    @return 0 on success, negative value on failure
*/
static int iar_get_protocols(void) 
{
    EFI_STATUS ret;

    if (m_pHWIOProtocol == NULL)
    {
        ret = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&m_pHWIOProtocol);
        if ((EFI_ERROR(ret)) || (m_pHWIOProtocol == NULL))
        {
            LOGE("failed to get HWIO protocol, ret [0x%x]", ret);
            return -EFAULT;
        } else {
            LOGD("Get protocol HWIO completed successfully");
        }
    }

    if (m_pQcomScmProtocol == NULL)
    {
        ret = gBS->LocateProtocol(&gQcomScmProtocolGuid, NULL, (void**)&m_pQcomScmProtocol);
        if ((EFI_ERROR(ret)) || (m_pQcomScmProtocol == NULL))
        {
            LOGE("failed to get QcomScm protocol, ret [0x%x]", ret);
            return -EFAULT;
        } else {
            LOGD("Get protocol QcomScm completed successfully");
        }
    }

    return 0;
}


/**
    read_iar_db_file()
    @brief read file from "spunvm" partition IAR-DB

    @param[in] file_path - file name and path
    @param[in] buf - pointer to buffer to fill data
    @param[in] buf_size - buffer size

    @return 0 on success, negative value on failure
*/
static int read_iar_db_file(const char *file_path, void *buf, size_t buf_size)
{
    int ret;
    CHAR16 *path = NULL;
    UINTN read_size = 0; // IN/OUT
    EFI_GUID    *RootDeviceTypeGuid = NULL; // gEfiEmmcGppPartition1Guid
    EFI_GUID    *PartitionTypeGuid = NULL; // gEfiPlatPartitionTypeGuid
    CHAR16      *PartitionLabel = L"spunvm";
    UINT32 file_size = 0;
    
    if (file_path == NULL || buf == NULL || buf_size == 0) {
        return -EINVAL;
    }

    path = AllocateZeroPool(MAX_PATH_LEN*sizeof(CHAR16));
    if (path == NULL) {
        return -ENOMEM;
    }
    
    AsciiStrToUnicodeStrS(file_path, path, MAX_PATH_LEN);

    ret = MountFatPartition(L"spunvm");
    if (ret != EFI_SUCCESS) {
        LOGE("MountFatPartition(spunvm) failed, ret [0x%x]", ret);
        return -EFAULT;
    } else {
        LOGD("MountFatPartition(spunvm) ok");
    }
    
    read_size = buf_size;
    ret = GetFileSize(path, RootDeviceTypeGuid, PartitionTypeGuid, PartitionLabel , true, NULL, &file_size);
    if (ret != EFI_SUCCESS) {
        LOGD("GetFileSize(%a) failed, ret [0x%x] [%a]", file_path, ret, strerror(ret));
        return -EFAULT;
    } else {
        LOGD("GetFileSize(%a) OK , size [0x%x]", file_path, file_size);
    }
    
    read_size = file_size;

    ret = ReadFile(path, RootDeviceTypeGuid, PartitionTypeGuid, PartitionLabel , true, NULL, &read_size, 0, buf, buf_size);
    if (ret != EFI_SUCCESS) {
        LOGE("ReadFile() [%a] failed, ret [0x%x] [%a]", file_path, ret, strerror(ret));
        return -EFAULT;
    } else {
        LOGD("ReadFile() [%a] OK", file_path);
    }

    FreePool(path);
    
    return read_size;
}

/**
    write_iar_db_file()
    @brief write file at "spunvm" partition IAR-DB
    
    @param[in] file_path - file name and path
    @param[in] buf - pointer to buffer to fill data
    @param[in] buf_size - buffer size

    @return 0 on success, negative value on failure
*/
static int write_iar_db_file(const char *file_path, void *buf, size_t buf_size)
{
    int ret;
    CHAR16 *path = NULL;
    UINTN write_size = 0; // IN/OUT
    EFI_GUID    *RootDeviceTypeGuid = NULL; // gEfiEmmcGppPartition1Guid
    EFI_GUID    *PartitionTypeGuid = NULL; // gEfiPlatPartitionTypeGuid
    CHAR16      *PartitionLabel = L"spunvm";
    UINT32 file_size = 0;
    
    if (file_path == NULL || buf == NULL || buf_size == 0) {
        return -EINVAL;
    }

    path = AllocateZeroPool(MAX_PATH_LEN*sizeof(CHAR16));
    if (path == NULL) {
        return -ENOMEM;
    }
    
    AsciiStrToUnicodeStrS(file_path, path, MAX_PATH_LEN);
    
    ret = MountFatPartition(L"spunvm");
    if (ret != EFI_SUCCESS) {
        LOGE("MountFatPartition(spunvm) failed, ret [0x%x]", ret);
        return -EFAULT;
    } else {
        LOGD("MountFatPartition(spunvm) ok");
    }
    
    write_size = buf_size;

    ret = WriteFile(path, RootDeviceTypeGuid, PartitionTypeGuid, PartitionLabel , true, NULL, &write_size, 0, buf, buf_size);
    if (ret != EFI_SUCCESS) {
        LOGE("WriteFile() [%a] failed, ret [0x%x] [%a]", file_path, ret, strerror(ret));
        return -EFAULT;
    } else {
        LOGD("WriteFile() [%a] OK, write_size [0x%x]", file_path, write_size);
    }

    FreePool(path);
    
    return write_size;
}

/**
    read_firmware_cmac()
    @brief read spu firmware cmac file from "spunvm" partition IAR-DB
    
    @param[in] fw_name - firmware base name. i.e. spss1t
    @param[in] buf - pointer to buffer to fill data
    @param[in] buf_size - buffer size

    @return 0 on success, negative value on failure
*/
static int read_firmware_cmac(const char *fw_name, void *buf, size_t size)
{
    int ret;
    char *path = NULL;
  
    path = AllocateZeroPool(MAX_PATH_LEN*sizeof(char));
    if (path == NULL) {
        return -ENOMEM;
    }
    
    AsciiStrCpyS(path, MAX_PATH_LEN, "\\iar_db\\");
    AsciiStrCatS(path, MAX_PATH_LEN,  fw_name);
    AsciiStrCatS(path, MAX_PATH_LEN,  ".mac"); // file extension
    
    LOGD("cmac file path [%a]", path);
    
    ret = read_iar_db_file(path, buf, size);
    
    FreePool(path);
    
    return ret;
}

static int read_apps_cmac(void)
{
    int ret;
    char *path = NULL;

    path = AllocateZeroPool(MAX_PATH_LEN*sizeof(char));
    if (path == NULL) {
        return -ENOMEM;
    }

    for (uint32_t i = 0; i < sizeof(m_app_names)/sizeof(m_app_names[0]); ++i) {
        AsciiStrCpyS(path, MAX_PATH_LEN, "\\iar_db\\\\");
        AsciiStrCatS(path, MAX_PATH_LEN, m_app_names[i]);
        char ver_and_type[3];
        ver_and_type[0] = m_soc_ver;
        ver_and_type[1] = m_fw_type;
        ver_and_type[2] = '\0';

        AsciiStrCatS(path, MAX_PATH_LEN, ver_and_type); // version and type e.g 1t
        AsciiStrCatS(path, MAX_PATH_LEN, ".mac"); // file extension

        LOGD("cmac file path [%a]", path);

        ret = read_iar_db_file(path, m_apps_cmac[i], sizeof(m_apps_cmac[i]));
        if (ret < 0) {
            LOGE("failed to read apps cmac file %d", i);
            FreePool(path);
            return IAR_STATE_DISABLED;
        }

        LOGD("app mac: [0x%x] [0x%x] [0x%x] [0x%x]", 
            m_apps_cmac[i][0], m_apps_cmac[i][1], m_apps_cmac[i][2], m_apps_cmac[i][3]);

    }
    FreePool(path);

    return ret;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static int read_3rd_party_apps_cmac(void)
{
    int ret;
    char *path = NULL;

    path = AllocateZeroPool(MAX_PATH_LEN*sizeof(char));
    if (path == NULL) {
        return -ENOMEM;
    }

    memset(m_3rd_party_apps_cmac, 0, sizeof(m_3rd_party_apps_cmac));

    for (uint32_t i = 0; i < MAX_3RD_PARTY_UEFI_APPS ; ++i) {
        AsciiStrCpyS(path, MAX_PATH_LEN, "\\iar_db\\\\");
        AsciiStrCatS(path, MAX_PATH_LEN, m_3rd_party_app_base_name);
        // use a string rather than char as AsciiStrCatS() uses string
        char num[2]={0}; 
        num[0] = '0'+i; // uefi file index as string
        num[1] = 0; // null termination

        AsciiStrCatS(path, MAX_PATH_LEN, num); // app number 0/1/2/3...
        AsciiStrCatS(path, MAX_PATH_LEN, ".mac"); // file extension

        ret = read_iar_db_file(path, m_3rd_party_apps_cmac[i], sizeof(m_3rd_party_apps_cmac[i]));
        if (ret < 0) {
            FreePool(path);
            // number of files is unknown, so it is not an error
            return 0;
        }

        LOGI("found 3rd party cmac file path [%a]", path);

        LOGD("app mac: [0x%x] [0x%x] [0x%x] [0x%x]", 
            m_3rd_party_apps_cmac[i][0], 
            m_3rd_party_apps_cmac[i][1], 
            m_3rd_party_apps_cmac[i][2], 
            m_3rd_party_apps_cmac[i][3]);

    }
    FreePool(path);

    return 0;
}
//-----------------------------------------------------------------------------

/**
    write_pbl_firmware_cmac()
    @brief write spu firmware cmac, calculated by SPU PBL, to "spunvm" partition IAR-DB
    
    @param[in] fw_name - firmware base name. i.e. spss1t
    @param[in] buf - pointer to buffer to fill data
    @param[in] buf_size - buffer size

    @return 0 on success, negative value on failure
*/
static int write_pbl_firmware_cmac(const char *fw_name, void *buf, size_t size)
{
    int ret;
    char *path = NULL;
  
    path = AllocateZeroPool(MAX_PATH_LEN*sizeof(char));
    if (path == NULL) {
        return -ENOMEM;
    }
    
    AsciiStrCpyS(path, MAX_PATH_LEN, "\\iar_db\\");
    AsciiStrCatS(path, MAX_PATH_LEN, "pbl");
    AsciiStrCatS(path, MAX_PATH_LEN, ".mac"); // file extension
    
    LOGD("cmac file path [%a]", path);
    
    ret = write_iar_db_file(path, buf, size);
    if (ret < size) {
        LOGE("failed to write PBL cmac file [%a]", path);
    } else {
        LOGI("Write PBL cmac file [%a] completed successfully", path);
    }
    
    FreePool(path);
    
    return ret;
}

/**
    read_iar_state_from_file()
    @brief read iar state from iar_state.bin file at IAR-DB
    
    @return iar state
*/
static int read_iar_state_from_file(void)
{
    int ret;
    uint32_t state = 0;
    const char* iar_state_file_path = "\\iar_db\\iar_state.bin";
    
    ret = read_iar_db_file(iar_state_file_path, &state, sizeof(state));
    if (ret < 0)
        return IAR_STATE_DISABLED;

    return state;
}  

/**
    get_fw_name_from_path()
    @brief extract firmware base name from firmware file path

    @param[in] UnicodePath - firmware file path
    @param[out] fw_name - firmware base name. i.e. "spss1t"
    @param[in] size - max fw_name string size

    @return 0 on success, negative value on failure
*/
static int get_fw_name_from_path(CHAR16 *UnicodePath, char *fw_name, size_t size)
{
    char *path = NULL;
    int len = 0;
    char *p = NULL;

    path = AllocateZeroPool(MAX_PATH_LEN*sizeof(char));
    if (path == NULL) {
        return -ENOMEM;
    }

    UnicodeStrToAsciiStrS(UnicodePath, path, MAX_PATH_LEN);
    len = AsciiStrLen(path);

    p = path + len;

    // find the end of the dir path
    while ((*p != '/') && (*p != '\\') && (p != path))
        p--;

    LOGD("fw path [%a]", path);
    LOGD("fw name [%a]", p);

    AsciiStrCpyS(fw_name, size, p);

    FreePool(path);

    return 0; 
}

/**
    hyp_assign()
    @brief perform SCM call to TZ/HYP to allow access to shared buffer,
        to both HLOS and remote subsystem

    @param[in] buf_phys_addr - shared buffer physical address
    @param[in] buf_size - shared buffer size
    @param[in] subsys_vmid - VMID of the subsystem

    @return 0 on success, negative value on failure
*/
static int hyp_assign(uint64_t buf_phys_addr, size_t buf_size, uint32_t subsys_vmid)
{
    int ret = 0;
    hyp_memprot_assign_t *pScmParam = NULL;
    hyp_memprot_ipa_info_t *pIPAinfolist = NULL;
    UINT32 *pSourceVMlist = NULL;
    hyp_memprot_dstVM_perm_info_t *pDestVMlist = NULL;
    UINT32 SrcVM;
    hyp_memprot_dstVM_perm_info_t DstVM[2];
    // As SCM Expects in/out param
    UINT64  Parameters[SCM_MAX_NUM_PARAMETERS] = {0};
    UINT64  Results[SCM_MAX_NUM_RESULTS] = {0};
    tz_common_rsp_t *SysCallRsp = (tz_common_rsp_t*)Results;

    LOGD("subsys_vmid: [%d]", subsys_vmid);

    // Memory allocation in shared memory with TZ
    pScmParam = UncachedAllocateZeroPool(sizeof(*pScmParam));
    if (pScmParam == NULL) {
        LOGE("Error: pScmParas is NULL");
        goto exit_err;
    }

    pIPAinfolist = UncachedAllocateZeroPool(sizeof(*pIPAinfolist));
    if (pIPAinfolist == NULL) {
        LOGE("Error: pIPAinfolis is NULL");
        goto exit_err;
    }

    pSourceVMlist = UncachedAllocateZeroPool(sizeof(SrcVM));
    if (pSourceVMlist == NULL) {
        LOGE("Error: pSourceVMlist is NULL");
        goto exit_err;
    }

    pDestVMlist = UncachedAllocateZeroPool(sizeof(DstVM));
    if (pDestVMlist == NULL) {
        LOGE("Error: pDestVMlist is NULL");
        goto exit_err;
    }

    // Set shared buffer address and size
    pIPAinfolist->IPAaddr = buf_phys_addr;
    pIPAinfolist->IPAsize = buf_size;

    // Source VM
    SrcVM = AC_VM_HLOS;
    CopyMem(pSourceVMlist, &SrcVM, sizeof(SrcVM));

    // Destination VM
    DstVM[0].dstVM = AC_VM_HLOS;
    DstVM[1].dstVM = subsys_vmid;
    DstVM[0].dstVMperm = (VM_PERM_R|VM_PERM_W);
    DstVM[1].dstVMperm = (VM_PERM_R|VM_PERM_W);
    CopyMem(pDestVMlist, &DstVM, sizeof(DstVM));

    // Setup SCM parameters
    pScmParam->IPAinfolist = (UINT64) pIPAinfolist;
    pScmParam->IPAinfolistsize = sizeof(*pIPAinfolist);

    pScmParam->sourceVMlist = (UINT64) pSourceVMlist;
    pScmParam->srcVMlistsize = sizeof(SrcVM);

    pScmParam->destVMlist = (UINT64) pDestVMlist;
    pScmParam->destVMlistsize = sizeof(DstVM);

    pScmParam->spare = 0;

    // Do the SCM call to TZ/HYP
    memset(Parameters, 0, sizeof(Parameters));
    memset(Results, 0, sizeof(Results));
    CopyMem(Parameters,pScmParam, sizeof(*pScmParam));
    ret = m_pQcomScmProtocol->ScmSipSysCall(m_pQcomScmProtocol,
                                            HYP_MEM_PROTECT_ASSIGN,
                                            HYP_MEM_PROTECT_ASSIGN_PARAM_ID,
                                            Parameters, Results);
    if (EFI_ERROR(ret)) {
       LOGE("ScmSipSysCall() failed, ret [0x%x]", ret);
        goto exit_err;
    }

    if (SysCallRsp->common_rsp.status != 1) {
       LOGE("ScmSipSysCall() failed, common_rsp.status [0x%x]", SysCallRsp->common_rsp.status);
        goto exit_err;
    }

    if (SysCallRsp->ret != 0) {
       LOGE("ScmSipSysCall() failed, rsp.ret [0x%x]", SysCallRsp->ret);
       goto exit_err;
    }

    LOGD("ScmSipSysCall() completed successfully");

    // Free mem allocations
    UncachedFreePool(pScmParam);
    UncachedFreePool(pIPAinfolist);
    UncachedFreePool(pSourceVMlist);
    UncachedFreePool(pDestVMlist);

    return 0;

exit_err:
    if (pScmParam)
        UncachedFreePool(pScmParam);
    if (pIPAinfolist)
        UncachedFreePool(pIPAinfolist);
    if (pSourceVMlist)
        UncachedFreePool(pSourceVMlist);
    if (pDestVMlist)
        UncachedFreePool(pDestVMlist);
        
    return -EFAULT;    
}

/**
    spss_handle_pre_auth_and_reset()
    @brief put fw cmac in shared buffer before SPU is out of reset

    @param[in] RegionStart - PIL region address
    @param[in] RegionSize  - PIL region size

    @return EFI_SUCCESS on success, error value on failure
*/
static EFI_STATUS spss_handle_pre_auth_and_reset(uint64_t RegionStart, size_t RegionSize)
{
    EFI_STATUS status = EFI_SUCCESS;
    uint8_t *ptr = NULL;
    uint32_t val = 0;
//    uint32_t subsys_vmid = AC_VM_CP_SPSS_HLOS_SHARED; // sp_bit = 0; // Assign OK.
//    uint32_t subsys_vmid = AC_VM_CP_SPSS_SP_SHARED; // sp_bit = 1; // Assign Failed.
//    uint32_t subsys_vmid = AC_VM_CP_SPSS_SP; // sp_bit = 1;

    LOGD("Before AUTH_AND_RESET Event");
    LOGD("PIL RegionStart [0x%x]", RegionStart);
    LOGD("PIL RegionSize  [0x%x]", RegionSize);
    LOGD("m_spss_image_size  [0x%x]", m_spss_image_size);

    // IAR area starts immediately after spss image
    m_buf_addr = (RegionStart + m_spss_image_size);

    m_buf_size = IAR_MEM_SIZE; // 4 KB
    LOGI("IAR Buffer Addr  [0x%x]", m_buf_addr);
    LOGD("IAR Buffer Size  [0x%x]", m_buf_size);

    // No need to HYP-Assign as PIL reserved area includes the IAR-MEM
/*
    status = hyp_assign(m_buf_addr, m_buf_size, subsys_vmid);
    if (status != EFI_SUCCESS) {
        LOGE("hyp assign failed, status  [%d]", status);
        return status;
    }
*/

    LOGI("Write spss firmware and apps cmac to IAR-MEM");

    ptr = (uint8_t *) m_buf_addr;

    memset(ptr, 0xA5, m_buf_size);

    DALSYS_memscpy(ptr, sizeof(m_fw_cmac), m_fw_cmac, sizeof(m_fw_cmac));

    for (uint32_t i = 0; i < ARRAY_SIZE(m_apps_cmac); ++i) {
        // move 16 bytes forward to leave space to SPU to write calculated cmac there
        ptr += sizeof(m_apps_cmac[0])*2;
        DALSYS_memscpy(ptr, sizeof(m_apps_cmac), m_apps_cmac[i], sizeof(m_apps_cmac[0]));
    }

    for (uint32_t i = 0; i < ARRAY_SIZE(m_3rd_party_apps_cmac); ++i) {
        // When a pattern of 0xA5A5A5A5 or Zero is met, then it marks unused slot
        // so we alread read all valid cmacs.
        if (m_3rd_party_apps_cmac[i][0] == m_3rd_party_apps_cmac[i][1])
            break;
        // Each app has a pair of "saved" and "calculated" cmacs, so skip 2 cmacs for the next app.
        ptr += sizeof(m_3rd_party_apps_cmac[0])*2;
        DALSYS_memscpy(ptr, sizeof(m_3rd_party_apps_cmac), m_3rd_party_apps_cmac[i], sizeof(m_3rd_party_apps_cmac[0]));
    }

    return EFI_SUCCESS;
}

static uint32_t read_sp_reg(uint32_t addr)
{
    uint32_t val = 0;
    if (m_sp_regs_ptr == NULL)
	return 0xDEADBEEF;

    LOGD("phys addr", addr);

    addr = ((addr - SP_CNOC_SP_SCSR_BASE_ADDR) + (uint32_t)(uintptr_t)m_sp_regs_ptr);

    LOGD("virt addr", addr);

    val = in_dword(addr);

    LOGD("val", val);

    return val;
}

static int map_spu_regs(void)
{
    EFI_STATUS status = 0;
    uint32_t err_status = 0;
    uint32_t err_status_spare[3] = {0};
    uint32_t hw_ver = 0;

    // Map SP shared registers
    status = m_pHWIOProtocol->MapRegionByAddress(m_pHWIOProtocol, 
                (UINT8*) SP_CNOC_SP_SCSR_BASE_ADDR, (UINT8**) &m_sp_regs_ptr);
    if (status != EFI_SUCCESS) {
        LOGE("MapRegionByAddress() spu registers failed. ret [0x%x]", status);
        return -EFAULT;
    }

    LOGD("SP_CNOC_SP_SCSR_BASE_ADDR [0x%x]", (int) SP_CNOC_SP_SCSR_BASE_ADDR);
    LOGD("m_sp_regs_ptr [%p]", m_sp_regs_ptr);
    
    return 0;
}

static int check_spu_status_regs(void)
{
    uint32_t err_status = 0;
    uint32_t err_status_spare[3] = {0};
    uint32_t hw_ver = 0;

    hw_ver = read_sp_reg(SP_CNOC_SP_SCSR_HW_VERSION);
    LOGE("sp hw ver [0x%x]", (int) hw_ver);

    err_status = read_sp_reg(SP_CNOC_SP_SCSR_RMB_ERR_STATUS);

    if (err_status != 0) {
        err_status_spare[0] = read_sp_reg(SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(0));
        err_status_spare[1] = read_sp_reg(SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(1));
        err_status_spare[2] = read_sp_reg(SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm(2));

	LOGE("spss err_status [0x%x]", err_status);

        LOGE("spss err_status_spare[0] [0x%x]", err_status_spare[0]);
        LOGE("spss err_status_spare[1] [0x%x]", err_status_spare[1]);
        LOGE("spss err_status_spare[2] [0x%x]", err_status_spare[2]);
    }

    return 0;
}

/**
    spss_handle_post_load()
    @brief check SPU status after SPU is loaded

    !!! The SPU PBL CMAC is read by spss_utils HLOS kernel driver !!!
    !! SPU no longer set SW_INIT_DONE in UEFI time. !!

    @return EFI_SUCCESS on success, error value on failure
*/

static EFI_STATUS spss_handle_post_load(void)
{
    uint8_t *ptr = NULL;
    uint32_t val = 0;
    EFI_STATUS status = EFI_SUCCESS;
    int timeout_msec = 1000;
    int time = timeout_msec;

    LOGD("After POST_LOAD Event");
	ptr = (uint8_t *) m_buf_addr;
    if (ptr == 0) {
        LOGE("Invalid IAR buffer address");
        return EFI_INVALID_PARAMETER;
    }

    ptr += sizeof(m_fw_cmac);

    // check SPU status registers
    map_spu_regs();
    check_spu_status_regs();

    return EFI_SUCCESS;
}

static EFI_HANDLE m_Handle = NULL;

static int spss_register_iar_callback(void)
{
    int ret;
    
    ret = gBS->InstallMultipleProtocolInterfaces(
                    &m_Handle,
                    &gPILProxySPSSGuid,
                    (VOID **)&m_SpssPilProxyProtocol,
                    NULL );
    return ret;
}

//-----------------------------------------------------------------------------
//  callback functions
//-----------------------------------------------------------------------------

static EFI_STATUS SpssPilProxyHandleEvent (
   UINT32                           PILEvent,
   VOID*                            PILEventCtxt
   )
{
    EFI_STATUS Status = EFI_SUCCESS;
    PIL_EVENT_PRE_AUTH_AND_RESET_PARAM *param = (PIL_EVENT_PRE_AUTH_AND_RESET_PARAM*) PILEventCtxt;

    switch(PILEvent)
    {
    case PIL_EVENT_PRE_AUTH_AND_RESET:
        LOGD("PIL_EVENT_PRE_AUTH_AND_RESET");
        Status = spss_handle_pre_auth_and_reset(param->RegionStart, param->RegionSize);
        break;

    case PIL_EVENT_POST_AUTH_AND_RESET:
        LOGD("PIL_EVENT_POST_AUTH_AND_RESET");
        break;

    case PIL_EVENT_POST_LOAD:
        LOGD("PIL_EVENT_POST_LOAD");
        Status = spss_handle_post_load();
        break;

    default:
        LOGD("Unknown event");
        /* return success for unhandled events */
        break;
    }

    LOGD("EFI status: [%d]", Status);

    return Status;
}

//-----------------------------------------------------------------------------
//  exported functions
//-----------------------------------------------------------------------------

/**
    spss_iar_main()
    @brief main function to handle spss IAR functionality.
    
    @param[in] spss_cfg - spss PIL configuration
    
    @return EFI_SUCCESS on success, other value on failure
*/
EFI_STATUS spss_iar_main(PIL_SUBSYS_CFG_TYPE* spss_cfg)
{
    int ret = 0;
    bool is_iar_enabled = false;
    char fw_name[13] = "spss1t"; // 8.3 + null termination
    char image_path[20];
    char full_name_path[20];
    CHAR16 full_name_path_unicode[20];

    // Check IAR-STATE
    m_iar_state = read_iar_state_from_file();
    if (m_iar_state != IAR_STATE_ACTIVATED) {
        LOGI("IAR-STATE is NOT ACTIVATED [0x%x], Exit now", m_iar_state);
        return EFI_SUCCESS;    
    } else {
        LOGI("IAR-STATE is ACTIVATED");
    }

    // print current PIL region
    LOGD("spss pil addr [0x%x]", spss_cfg->ResvRegionStart);
    LOGD("spss pil size [0x%x]", spss_cfg->ResvRegionSize);
    
    // Get relevant protocols pointer
    ret = iar_get_protocols();
    if (ret < 0) {
        LOGE("get protocols failed");
        return ret;
    }

    if (m_iar_state == IAR_STATE_ACTIVATED) {
        UINT32 file_size = 0;
    
        // Read firmware cmac
        memset(m_fw_cmac, 0xB4, sizeof(m_fw_cmac));
        ret = get_fw_name_from_path(spss_cfg->ImagePath, fw_name, sizeof(fw_name));
        ret = read_firmware_cmac(fw_name, m_fw_cmac, sizeof(m_fw_cmac));
        if (ret < 0) {
            return EFI_NOT_FOUND;
        }
        LOGD("m_fw_cmac: [0x%x] [0x%x] [0x%x] [0x%x]", m_fw_cmac[0], m_fw_cmac[1], m_fw_cmac[2], m_fw_cmac[3]);
        DALSYS_memscpy(m_fw_name, sizeof(m_fw_name), fw_name, sizeof(fw_name));

        // extract the soc version and firmware type for later use(apps)
        m_soc_ver = m_fw_name[5]; // e.g. '1'
        m_fw_type = m_fw_name[6]; // e.g  't'

        // read from app files the cmacs of the applications loaded in uefi
        ret = read_apps_cmac();
        if (ret < 0) {
            return EFI_NOT_FOUND;
        }

        // read from 3rd party app files the cmacs of the applications loaded in uefi
        ret = read_3rd_party_apps_cmac();
        if (ret < 0) {
            return EFI_NOT_FOUND;
        }

        // build image path
        AsciiStrCpyS(image_path, sizeof(image_path), "\\iar_db\\");
        AsciiStrCatS(image_path, sizeof(image_path), fw_name);
        
        // Verify firmware file exist at spunvm
        AsciiStrCpyS(full_name_path, sizeof(full_name_path), image_path);
        AsciiStrCatS(full_name_path, sizeof(full_name_path), ".b01");
        AsciiStrToUnicodeStrS(full_name_path, full_name_path_unicode, sizeof(full_name_path_unicode));
        ret = GetFileSize(full_name_path_unicode, NULL, NULL, L"spunvm", true, NULL, &file_size);
        if (ret != EFI_SUCCESS) {
            LOGE("GetFileSize(%a) failed, ret [0x%x] [%a]", full_name_path, ret, strerror(ret));
            return EFI_NOT_FOUND;
        } else {
            LOGD("GetFileSize(%a) OK , size [0x%x]", full_name_path, file_size);
            m_spss_image_size = file_size;
        }

        if (m_spss_image_size % SZ_4K) {
            LOGE("spss image [%a] size [0x%08X] is not 4KB aligned", full_name_path, m_spss_image_size);
            return EFI_INVALID_PARAMETER;
        }

        // Load FW from "spunvm" partition, use label instead of GUID
        memset(&spss_cfg->PartiGuid, 0, sizeof(spss_cfg->PartiGuid));
        AsciiStrToUnicodeStrS("spunvm", spss_cfg->PartiLabel, NAME_MAX_LENGTH);
        AsciiStrToUnicodeStrS(image_path, spss_cfg->ImagePath, NAME_MAX_LENGTH);
        
        LOGI("Loading spu firmware from spunvm partition, image_path [%a]", image_path);
        
        // Register spss callback to PIL
        spss_cfg->ProxyGuid = gPILProxySPSSGuid;
        spss_register_iar_callback();
    }

    return EFI_SUCCESS;
}

