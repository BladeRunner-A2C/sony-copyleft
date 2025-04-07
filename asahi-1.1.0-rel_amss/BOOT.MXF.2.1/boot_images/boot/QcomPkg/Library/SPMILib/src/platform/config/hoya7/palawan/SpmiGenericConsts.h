#ifndef __SPMIGENERICCONSTS_H__
#define __SPMIGENERICCONSTS_H__

/* Auto-generated from SM8250 (Kona) [kona_v1.0_p3q1r17.1_M00_partitioned_rtl] */

#define SPMI0_MAX_CHANNELS_SUPPORTED 896
#define SPMI_MAX_OWNER_IDS 10

#define INIT_SPMI0_DEV_GENERICS { \
  .mNumChannels            = SPMI0_MAX_CHANNELS_SUPPORTED, \
  .mNumPortPriorities      = 7, \
  .mNumPvcPorts            = 6, \
  .mNumPvcPortPPIDs        = 8, \
  .mNumMasters             = SPMI_MAX_OWNER_IDS, \
  .mNumProgRamRegs         = 256, \
  .mNumPicAccStatusRegs    = 28, \
  .mNumVrmIds              = 256, \
  .mNumMgpiPorts           = 8, \
}


#endif /* __SPMIGENERICCONSTS_H__ */
