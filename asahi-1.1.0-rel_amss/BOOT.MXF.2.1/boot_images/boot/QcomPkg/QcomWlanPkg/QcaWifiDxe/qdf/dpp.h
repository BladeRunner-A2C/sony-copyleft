/*
 * Copyright (c) 2021-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 1/9/21    zxue     support read specific bdf from DPP
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_DPP_H
#define __QDF_DPP_H

#include <qdf/firmware.h>

UINT8 DppGetWlanMacAddress(UINT8 *MacAddr);
EFI_STATUS DppGetWlanBdf(struct firmware *FW, UINT32 BoardId, UINT32 ChipId);

static inline u8
dpp_get_wlan_mac_address(u8 *mac_addr)
{
    return DppGetWlanMacAddress(mac_addr);
}

static inline int
dpp_get_wlan_bdf(struct firmware *fw, u32 board_id, u32 chip_id)
{
    EFI_STATUS Status = DppGetWlanBdf(fw, board_id, chip_id);
    return efi_status_to_errno(Status);
}


#endif // !__QDF_DPP_H

