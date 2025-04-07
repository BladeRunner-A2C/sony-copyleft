#ifndef _MFGMODEMGMT_APP_H
#define _MFGMODEMGMT_APP_H

/*===========================================================================
  Copyright (c) 2023 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  ========================================================================= */
/*===========================================================================
                      EDIT HISTORY FOR FILE

# when       who         what, where, why
# --------   ---         -----------------------------------------------------
# 04/04/23   sg          Initial revision
===========================================================================*/

#define TZEXEC_SVC_MFG_MODE_ID             0x0080000
#define RESILIENCY_SRV_CREATE_CMD(x)       (TZEXEC_SVC_MFG_MODE_ID | x)
#define CMD_ENTER_MFG_MODE                 RESILIENCY_SRV_CREATE_CMD(1)
#define CMD_EXIT_MFG_MODE                  RESILIENCY_SRV_CREATE_CMD(2)
#define CMD_STORAGE_WRITE_PROTECT          RESILIENCY_SRV_CREATE_CMD(3)
//#define CMD_FACTORY_FUSE_RD                RESILIENCY_SRV_CREATE_CMD(4) //commented out so that no uefi module can call this command
//#define CMD_FACTORY_FUSE_WR                RESILIENCY_SRV_CREATE_CMD(5) //commented out so that no uefi module can call this command
#define CMD_GET_MFG_MODE                   RESILIENCY_SRV_CREATE_CMD(6)

/* Status codes */
#define MFG_SUCCESS                         0
#define MFG_DEVICE_IN_MFG_MODE             -10
#define MFG_MODE_EOF_NOT_BLOWN             -11

#define MFGMODEMGMT_APP_NAME "qcom.tz.mfgmodemgmt"

/* Structure for handling MFG Service cases */
typedef struct MFG_SVC_REQ_S
{
    uint64 commandId;     /* Command ID */
}MFG_SVC_REQ_T ,*PMFG_SVC_REQ_T;

typedef struct MFG_SVC_RSP_S
{
    int status;         /* error return */
}MFG_SVC_RSP_T, *PMFG_SVC_RSP_T;

#endif // #ifndef _MFGMODEMGMT_APP_H
