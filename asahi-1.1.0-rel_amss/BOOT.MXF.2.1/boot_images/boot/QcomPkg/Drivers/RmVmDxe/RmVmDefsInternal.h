/** 
  @file  RmVmDefs.h
  @brief RM VM struct defines.
*/
/*=============================================================================
Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/25/23   kedara  Added RM_STATUS_SUCCESS, RmStdResp
 02/16/13   kedara  Initial Revision

=============================================================================*/
#ifndef __RM_VM_DEFS_H__
#define __RM_VM_DEFS_H__

/****************************** RM HEADER DEFINE *****************************/

/*According to RM Spec API Version must be 0x21 or 0x22. 
  Other values are reserved 
  ++TODO++ : Resolve RM spec : no version 2 seen
*/
#define RM_VERSION_ONE                    0x1
#define RM_VERSION_THREE                  0x3
#define RM_HEADER_API_VERSION             RM_VERSION_ONE

/*
  Header size is always a multiple of 4 bytes (1 word). 
  encoded as "(Header_Bytes / 4)". 
*/
#define RM_HEADER_WORDS                   0x2
#define RM_HEADER_WORDS_MASK_BIT_SHIFT    0x4

#define RM_HEADER_MESSAGE_TYPE_CONT_FRAG  0x0
#define RM_HEADER_MESSAGE_TYPE_REQ        0x1
#define RM_HEADER_MESSAGE_TYPE_REPLY      0x2
#define RM_HEADER_MESSAGE_TYPE_NOTIFY     0x3

#define RM_STATUS_SUCCESS                 0x0

/******************* RM MEMORY MGMT MESSAGE DEFINE ***************************/

#define RM_GET_IDENT_ID                   0x00000001
#define RM_MEM_DONATE_ID                  0x51000010
#define RM_MEM_LEND_ID                    0x51000012
#define RM_FW_MILESTONE_ID                0x51000020
#define RM_FW_SET_VM_FIRMWARE_ID          0x51000021
#define RM_VM_GET_ID                      0x56000010


//##############################################
//Message Queue Flags
#define RM_MESG_QUEUE_SEND_FLAG_PUSH      0x1
#define RM_MESG_QUEUE_RESERVED_FIELD      0x0


/*! \enum 
 *  \brief Type definition for different RM VM structures
 */

typedef struct  __attribute__((packed)) _RmMsgHeader{
  UINT8  Version      :4;
  UINT8  HeaderWords  :4;
  UINT8  MessageType  :2;
  UINT8  Fragments    :6;
  UINT16 SeqNo;
  UINT32 MessageId;
}RmMsgHeader;

/************************************************************************************
  Generic data struct defines to help decode common RM message types
*/

typedef struct  __attribute__((packed)) _RmHdrAndShortData1{
  RmMsgHeader RmHdr;
  UINT16  Data1;
  UINT16  Reserved0;
}RmHdrAndShortData1;

typedef struct __attribute__((packed)) _RmStdResp 
{
  RmMsgHeader RmHdr;
  UINT32 ErrorCode;
} RmStdResp;

//*************************** Structures for Memory Mgmt Messages **********************

typedef struct __attribute__((packed)) _RmMemShare 
{
  RmMsgHeader RmHdr;
  UINT8     MemType;
  UINT8     Reserved0;
  UINT8     Flags;
  UINT8     Reserved1;  
  UINT32    Label;
  RmMemAcl  AcList;
} RmMemShareDescPartial;

typedef struct __attribute__((packed)) _RmMemShareResp 
{
  RmStdResp StdResp;
  UINT32 MemHandle;
} RmMemShareResp;



typedef struct __attribute__((packed)) _FwSetVmFirmware 
{
  RmMsgHeader RmHdr;
  UINT16  AuthMechanism;
  UINT16  Reserved0;
  UINT32  MemHandle;
  UINT64  FwOffset;
  UINT64  FwSize;
} FwSetVmFirmware;

#endif /*__RM_VM_DEFS_H__*/

