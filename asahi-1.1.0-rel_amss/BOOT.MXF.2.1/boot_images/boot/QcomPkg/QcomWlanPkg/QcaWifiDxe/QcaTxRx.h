/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 19/10/21  zxue     refine code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QCA_TXRX_H
#define __QCA_TXRX_H

#include <qdf/sk_buff.h>
#include "Dev.h"
#include "QcaWlan.h"

/* types */
enum QcWlanEapolKeyAction {
    QCWLAN_EAPOL_KEY_NONE = 0x00,
    QCWLAN_EAPOL_KEY_PAIRWISE = 0x01,
    QCWLAN_EAPOL_KEY_GROUP = 0x02,
    QCWLAN_EAPOL_KEY_ALL = 0x03,
};

/* RX */
BOOLEAN
QcWlanProcessRxPacket(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN struct sk_buff *skb,
    OUT VOID* OutBuffer,
    OUT UINTN *BufferSize
);

VOID
QcWlanRxEapol(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    IN struct sk_buff *skb
);

/* TX */
EFI_STATUS
QcWlanTxPacket(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    IN struct sk_buff *skb
);

#endif //!__QCA_TXRX_H

