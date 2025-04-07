/*
* Copyright (c) 2022-2023 Qualcomm Technologies, Inc. All rights reserved.
*/
#ifndef __ETH_INIT_LIB__H__
#define __ETH_INIT_LIB__H__

#include <Uefi.h>
#include <Uefi/UefiSpec.h>
#include <Base.h>

#include <Library/BaseLib.h>
#include <Library/TestInterface.h>
#include <Protocol/EFIHWIO.h>
#include <Protocol/EFIClock.h>

// Protocols used by this driver
#include <Protocol/SimpleNetwork.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/PxeBaseCode.h>
#include <Protocol/DevicePath.h>

// Libraries used by this driver
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/NetLib.h>
#include <Library/DevicePathLib.h>
#include <Library/npa.h>
#include <Library/eth_phy_iface.h>
#include <api/systemdrivers/icbarb.h>

#define BUFFER_SIZE 3500
#define ETHERNET_TX_RING_NUM_ENTRIES 32

#define ETHSS_FH0_PCS0 0x22500000

#define ETHSS_FH0_RSFEC           0x22405000
#define ETHSS_FH0_MACWRAPPER_CSR  0x22400000
#define ETHSS_FH0_MAC0_128        0x22401000
#define MAC_BASE_ADDR_FH0         0x22900000

//#define ETH_DEBUG(fmt, args...) \
//	DEBUG(( EFI_D_WARN, " %a:%d " fmt, __func__, __LINE__, ## args));
#define ETH_DEBUG(fmt, args...) \
do {\
	DEBUG(( EFI_D_INFO, " %a:%d " fmt, __func__, __LINE__, ## args));\
} while (0)
#define ETH_DEBUG_ERR(fmt, args...) \
	DEBUG(( EFI_D_ERROR, " %a:%d " fmt, __func__, __LINE__, ## args));

#define ETH_DEBUG_WARN(fmt, args...) \
	DEBUG(( EFI_D_WARN, " %a:%d " fmt, __func__, __LINE__, ## args));

/*
 * ECPRI hardware register
 */
#define ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT        0x9220000
#define ECPRI_XBAR_XBAR_LUT_STATUS           	0x9220030
#define ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT    0x9220800

#define ECPRISS_HAL_SETFIELD(val, shift, mask) (((val) << (shift)) & (mask))
#define ECPRISS_HAL_SETFIELD_IN_REG(reg, val, shift, mask) \
        (reg |= ((val) << (shift)) & (mask))
#define ECPRISS_HAL_GETFIELD_FROM_REG(reg, shift, mask) \
        (((reg) & (mask)) >> (shift))

#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_BMSK                            0xe00
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_SHFT                                9
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_BMSK                        0x1c0
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_SHFT                            6
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_BMSK                         0x38
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_SHFT                            3
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_BMSK                              0x7
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_BMSK                      0xff000000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_SHFT                              24
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_BMSK                        0xff0000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_BMSK                          0xff00
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_SHFT                               8
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_BMSK                            0xff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_SHFT                               0

// PHY ID for AR8031 PHY instances
#define PHY_ID0_MASK     0x4  // Addr 0x4

#define AT803X_DEBUG_REG_0			0x00
//#define AT803X_DEBUG_RX_CLK_DLY_EN		BIT(15)
#define AT803X_DEBUG_RX_CLK_DLY_EN		1 << 15

#define AT803X_DEBUG_REG_5			0x05
#define AT803X_DEBUG_TX_CLK_DLY_EN		1 << 8
//#define AT803X_DEBUG_TX_CLK_DLY_EN		BIT(8)


#define AT803X_DEBUG_ADDR			0x1D
#define AT803X_DEBUG_DATA			0x1E

// Command register offset and bit masks for register content
#define ETHSS_FH0_MAC0_MDIO_COMMAND         0x22401034
#define ETHSS_FH0_MAC0_MDIO_DATA			0x22401038
#define MTIP_MDIO_CFG_STATUS_REG   0x22401030

#define MTIP_MDIO_PHY_ADDR_SHIFT   5
//#define MTIP_MDIO_PHY_ADDR_MASK    GENMASK(9, 5)
#define MTIP_MDIO_PHY_ADDR_MASK        ( (1<<5)-1 ) << 5
#define MTIP_MDIO_REG_ADDR_SHIFT   0
//#define MTIP_MDIO_REG_ADDR_MASK    GENMASK(4, 0)
#define MTIP_MDIO_REG_ADDR_MASK          (1<<5)-1
#define GENMASK(pos1,pos2) ( (1<< (pos1-pos2+1) )-1 ) << pos2

#define MTIP_MDIO_CLK_DIV_SHIFT    7
//#define MTIP_MDIO_CLK_DIV_MASK     GENMASK(15, 7)
#define MTIP_MDIO_CLK_DIV_MASK      ( (1<<9) -1) << 7

#define MII_READ_MASK              0x00008000  //BIT(15)

#define CLK_FREQ(x) (x * 1000 * 1000UL)

/* MTIP clocks */
#define MTIP_GCC_APB_CLK_MAX_NOM (CLK_FREQ(100))
#define MTIP_GCC_SNOC_AXI_CLK_MAX_NOM (CLK_FREQ(200))
#define MTIP_ECPRI_FF_CLK_MAX_NOM (CLK_FREQ(466.5))
#define MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM (CLK_FREQ(806))

/* ECPRI clock */	
#define ECPRI_CG_CLK_NOM_MAX (CLK_FREQ(466.50))	
#define ECPRI_MSS_ORAN_NOM_MAX (CLK_FREQ(500))

/* MACSEC clock */
#define MACSEC_CLK_FREQ(x) (x * 1000 * 1000UL)
#define MACSEC_CLK_NOM_MAX (MACSEC_CLK_FREQ(200.0))

#define CSMLOGINFO(fmt, args...) \
do {\
	DEBUG(( EFI_D_INFO, " %a:%d " fmt, __func__, __LINE__, ## args));\
} while (0)
	
#define CSMLOGERR(fmt, args...) \
do {\
	DEBUG(( EFI_D_ERROR, " %a:%d " fmt, __func__, __LINE__, ## args));\
} while (0)

int ecpriss_config_init();

int at803x_config_init();

VOID ETHMapRegions(VOID);

EFI_STATUS enable_clock(EFI_CLOCK_PROTOCOL *pClockProtocol, const char* id, UINT32 Freq);
int mtip_clocks_setup_gcc_clocks(void);
int mtip_clocks_setup_c2c_clocks(void);
int mtip_clocks_setup_dbg_clocks(void);
int mtip_clocks_setup_fh0_clocks(void);
int mtip_clocks_setup_fh1_clocks(void);
int mtip_clocks_setup_fh2_clocks(void);
int ecpriss_clock_init(void);
void mtip_clocks_setup_clocks(void);


int mac_config_init(UINT32 mac_base_addr);

void mtip_mac_wrapper_init(UINT32 wrapper_base_addr);

int mtip_pcs_config_pcs(UINT32 pcs_ioaddr);

int mtip_pcs_enable_loopback(UINT32 pcs_ioaddr);

int mtip_rsfec_initialize(UINT32 rsfec_base_addr, struct eth_phy_iface_phy_lane_config lane_config[PHY_LANE_MAX]);

void mtip_mac_wrapper_pcs_mode_control(UINT32 wrapper_base_addr,enum eth_phy_iface_phy_lane_speed_enum lane_speed);

void mtip_mac_set_mac_address_by_device(UINT32 port_device_index, UINT32 link_device_index, UINT8 sa_data[],UINT32 mac_ioaddr);

void mtip_platform_set_mac_addresses(UINT32 mac_ioaddr);

void set_snp_interface_mac_address(UINT32 mac_ioaddr, EFI_MAC_ADDRESS *MacAddr);

void mtip_mac_enable_tx_rx(UINT32 mac_ioaddr);

bool mtip_mac_wrapper_get_link_status(UINT32 wrapper_base_addr, UINT32 link_index);

int qcom_aw_phy_inst_probe(UINT32 phy_inst_type);

int qcom_aw_phy_init(void);

int macsec_platform_set_bypass(UINT32 base_address);

int macsec_clock_enablement(void);

int aw_phy_bringup();

void aw_phy_teardown();

void mtip_rsfec_init();
#endif
