/**
 * @file:  SpmiPic.c
 *
 * Copyright (c) 2013-2020 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2022/06/08 10:24:24 $
 * $Header: 
 * $Change: 
 */


#include "SpmiPic.h"
#include "PmicArb.h"
#include "SpmiOs.h"
#include "SpmiLogs.h"
#include "SpmiBusInternal.h"

extern SpmiDrv spmiDrv;

void SpmiBus_ChannelIstDispatch(SpmiDevInfo *pDev, uint16 channel, uint8 mask)
{
    uint8 busId =  pDev->uDevIdx;
    uint64 tick = SpmiOs_GetTimeTick();
    SpmiBusIsrConfig* userIsr = NULL;
    
    spmiDrv.debug.isrIdx = (spmiDrv.debug.isrIdx + 1) % NUM_DEBUG_TRANSACTIONS;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].busId = busId;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].channel = channel;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].mask = mask;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].startTime = tick;
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].duration = 0;
    
    // This should never happen since we control the input to this
    if(channel >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)) {
        return;
    }
    
    if(spmiDrv.isrTable != NULL && spmiDrv.isrTable[busId] != NULL)
    {
      userIsr = spmiDrv.isrTable[busId][channel];
    }
    
    while(userIsr != NULL)
    {
        if(userIsr->isr != NULL) 
        {
            // Check if they want this particular interrupt
            uint8 userMask = mask & userIsr->mask;
            
            if(userMask)
            {
                uint64 usertick = SpmiOs_GetTimeTick();
                
                // added a dummy if check to suppress the compiler warning
                if(usertick) {} 
    
                userIsr->isr( (void*)userIsr->ctx, userMask );
            }
        }
        
        userIsr = userIsr->next;
    }
    
    spmiDrv.debug.isrTrans[spmiDrv.debug.isrIdx].duration = SpmiOs_GetTimeTick() - tick;
}



static boolean isInterruptOwner(SpmiDevInfo *pDev, uint8 owner, uint16 channel)
{
    ChannelMapEntry* entry = &pDev->channelMap[channel];

    if ((owner == entry->owner) && (entry->irqOwnerFlag == 0x1)) {

        return TRUE;
    }

    return FALSE;
}


Spmi_Result SpmiPic_SetInterruptEnabled(SpmiDevInfo *pDev, uint8 owner, uint16 channel, boolean enabled)
{
   uint8 * base_addr = pDev->baseAddrs;

    if(!isInterruptOwner( pDev, owner, channel )) {
        return SPMI_FAILURE_COMMAND_NOT_ALLOWED;
    }
    
    if(channel >= SPMI_NUM_CHANNELS_SUPPORTED(pDev)){
       return SPMI_FAILURE_INVALID_CHAN_NUM;
    }
    
    SPMI_LOG_VERBOSE( "ISR enabled: %d, Bus addr: 0x%p, Chan: %d, ", enabled, base_addr, channel );
    
    SPMI_HWIO_OUT_FIELD( HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, (channel + pDev->busChanStart )),
                         HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE, 
                         enabled );
    
    return SPMI_SUCCESS;
}

Spmi_Result SpmiPic_HandleIrq(SpmiDevInfo *pDev, uint8 owner)
{
    uint32 i, k;

    uint8 * base_addr = pDev->baseAddrs; 

    for(i = 0; i < SPMI_NUM_PIC_ACC_STATUS_REGS(pDev); i++) 
    {
        // Each bit in these registers represents a peripheral
        uint32 accStatus = SPMI_HWIO_IN( HWIO_SPMI_PIC_OWNERm_ACC_STATUSn_ADDR( base_addr, pDev->uDevIdx, owner, i ) );
        
        for(k = 0; (k < 32) && (accStatus != 0); k++) 
        {
            if((accStatus >> k) & 0x1) 
            {
                // This peripheral (channel) triggered the interrupt.  Check its individual mask
                uint16 channel = (i * 32) + k;
                uint32 accEnableStatus = SPMI_HWIO_IN_FIELD( HWIO_SPMI_PIC_ACC_ENABLEn_ADDR( base_addr, (channel + pDev->busChanStart ) ), 
                                                             HWIO_SPMI_PIC_ACC_ENABLEn_INT_ACC_ENABLE);
        
                if(accEnableStatus) 
                {
                    uint8 mask = SPMI_HWIO_IN_FIELD( HWIO_SPMI_PIC_IRQ_STATUSn_ADDR( base_addr, (channel + pDev->busChanStart ) ), 
                                                     HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS );
        
                    // Clear the status
                    SPMI_HWIO_OUT_FIELD( HWIO_SPMI_PIC_IRQ_CLEARn_ADDR( base_addr, (channel + pDev->busChanStart ) ),
                                         HWIO_SPMI_PIC_IRQ_CLEARn_INT_CLEAR, mask );
        
                    // wait for the status to clear
                    while((mask & SPMI_HWIO_IN_FIELD( HWIO_SPMI_PIC_IRQ_STATUSn_ADDR( base_addr, (channel + pDev->busChanStart ) ), HWIO_SPMI_PIC_IRQ_STATUSn_INT_STATUS )) != 0);
        
                    SpmiBus_ChannelIstDispatch(pDev, channel, mask);
                }
            }
        }
    }
    return SPMI_SUCCESS;
}
