//============================================================================
//
//                 RM VM ASM FUNCTIONS
//
// Copyright (c) 2023 Copyright Qualcomm Technologies, Inc.  All Rights Reserved.
// Qualcomm Technologies Proprietary and Confidential.
//   
//============================================================================

//============================================================================
//
//                           EDIT HISTORY FOR FILE
//
// This section contains comments describing changes made to the module.
// Notice that changes are listed in reverse chronological order.
//
//
// when       who     what, where, why
// --------   ---     --------------------------------------------------------
// 02/27/23   kpa     Initial revision.
//============================================================================

.text
.align 3

//============================================================================
//                             MODULE EXPORTS
//============================================================================

  GCC_ASM_EXPORT(GynhMsgQueueSendAsm)
  GCC_ASM_EXPORT(GynhMsgQueueReceiveAsm)

//============================================================================
//
//                        MACROS AND FUNCTIONS
//
//============================================================================

#define func_prologue()                     \
    stp           x29, x30, [sp, #-0x10]!;  \
    mov           x29,sp


#define func_epilogue()                     \
    ldp           x29, x30, [sp], #0x10  ;  \
    ret

//============================================================================
//
//  extern EFI_STATUS GynhMsgQueueSendAsm (UINT64 MsgQCapID, UINT64 BuffSize,
//                                         UINT64 BuffAddr, UINT64 MsgQSendFlags,
//                                         UINT64 MsgQResv, UINT64 Result0, UINT64 Result1);
//
//============================================================================
GynhMsgQueueSendAsm:
    func_prologue()
    stp     x19, x20, [sp, #-0x10]!    
    mov     x19, x5                // x19 = &Result0
    mov     x20, x6                // x20 = &Result1
    hvc     0x601B
    str     x0, [x19]             // Result0 = x0
    str     x1, [x20]             // Result1 = x1
    ldp     x19, x20, [sp], #0x10
    func_epilogue()


//============================================================================
//
//  EFI_STATUS GynhMsgQueueReceiveAsm (UINT64 MsgQCapID, UINT64 BuffAddr,
//                                     UINT64 MaxBuffSize, UINT64 MsgQResv,
//                                     UINT64 Result0, UINT64 Result1);
//
//============================================================================
GynhMsgQueueReceiveAsm:
    func_prologue()
    stp     x19, x20, [sp, #-0x10]!    
    mov     x19, x4                // x19 = &Result0
    mov     x20, x5                // x20 = &Result1
    hvc     0x601C
    str     x0, [x19]             // Result0 = x0
    str     x1, [x20]             // Result1 = x1
    ldp     x19, x20, [sp], #0x10
    func_epilogue()
    
