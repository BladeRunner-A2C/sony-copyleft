#ifndef __USB4UTILS_H__
#define __USB4UTILS_H__

/** @file     Usb4Utils.h 
    @brief    USB4 Common Utility Functions and Macros
    @details  
    @note     
    @ref      Copyright (c) 2020 Qualcomm Technologies Incorporated.
              All Rights Reserved.
              Qualcomm Confidential and Proprietary.
**/

#include <CoreVerify.h>

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/

/** Return low 16-bits value from pointer (either 16 or 32) */
#define USB4_LOW16(x) ((UINT16)(((UINT32)(x)) & 0xFFFF))

/** Return high 16-bits value from pointer (either 16 or 32 bit) */
#define USB4_HIGH16(x) ((UINT16)(((UINT32)(x)) >> 16))

/** Return low 32-bits value from pointer (either 32 or 64 bit) */
#define USB4_LOW32(x) ((UINT32)(((UINT64)(x)) & 0xFFFFFFFF))

/** Return high 32-bits value from pointer (either 32 or 64 bit) */
#define USB4_HIGH32(x) ((UINT32)(((UINT64)(x)) >> 32))

/** Return UINT16 from high and low bytes (uint8 each)  */
#define USB4_UINT16(high, low) ((UINT16)((((UINT16) (high)) << 8) | (UINT16)(low)))

/** Return UINT32 from high and low words (uint16 each)  */
#define USB4_UINT32(high, low) ((UINT32)((((UINT32) (high)) << 16) | (UINT32)(low)))

/** Return uint64 from high and low dwords (uint32 each)  */
#define USB4_UINT64(high, low) ((UINT64)((((UINT64) (high)) << 32) | (UINT64)(low)))

#define USB4_MIN(a,b)  ((a) < (b)) ? (a) : (b)

#define USB4_ARR_NUM_ELM(a)  (sizeof(a)/sizeof(a[0]))

#define LE_TO_BE_UINT32(x) \
     ((((x) & 0xFF000000) >> 24) | (((x) & 0x00FF0000) >>  8) |                      \
      (((x) & 0x0000FF00) <<  8) | (((x) & 0x000000FF) << 24))


#ifndef ARR_SIZE
#define  ARR_SIZE( a )  ( sizeof( (a) ) / sizeof( (a[0]) ) )
#endif /* ARR_SIZE */



// Avoid silent failures
#define USB4_ASSERT(COND) \
    if(!(COND))\
    {\
      ERR_FATAL("usb4 err", 0, 0, 0);\
    }
#define USB4_ASSERT_MSG(COND, MSG) \
    if(!(COND))\
    {\
      ERR_FATAL("usb4 err w msg", 0, 0, 0);\
    }

#define USB4_ERR_FATAL(str, A, B, C) \
  ERR_FATAL(str, A, B, C);

#define USB4_ERROR_STACK(VAL) \
  ERR_FATAL("usb4 err stack %d", VAL, 0, 0);


#define USB4_ERROR_STACK_MSG(VAL, MSG) \
  (void)MSG; \
  ERR_FATAL("usb4 err stack w msg %d", VAL, 0, 0);


/** Return low 32-bits value from pointer (either 32 or 64 bit) */
#define USB4_LOWER32(ptr) ((UINT32)(((UINT64)(ptr)) & 0xFFFFFFFF))

/** Return high 32-bits value from pointer (either 32 or 64 bit) */
#define USB4_UPPER32(ptr) ((UINT32)((((UINT64)(ptr)) >> 31) >> 1))

/** Return uint64 from high and low dwords (UINT32 each)  */
#define USB4_GET_UINT64(high, low) ((UINT64)((((UINT64)high) << 32) | (UINT64)low))


enum usb4_utils_timer_source
{
    USB4_TIMER_SOURCE_QTIMER = 0,
};

/**
 * @brief       Provide time service

 */

typedef struct 
{
    UINT32 last_time_ms;
    UINT32 last_time_us;
    enum usb4_utils_timer_source m_source;
} usb4_utils_timer;


int usb4_timer_Sleep_us(usb4_utils_timer *This, UINT32 sleep_us);

int usb4_timer_Sleep_ms(usb4_utils_timer *This, UINT32 sleep_ms);

int usb4_timer_Start(usb4_utils_timer *This);

int usb4_timer_GetElapsed_us(usb4_utils_timer *This, UINT32 *elapsed_us);

int usb4_timer_GetElapsed_ms(usb4_utils_timer *This, UINT32 *elapsed_ms);

/**
  * @brief Calculate router depth from topology ID
  * @param[in] topologyID - ID of the router
  * @return depth value
  */
UINT32 usb4_get_depth_from_topology(UINT64 topologyID);


 /**
   * @brief Calculate next router topology from topology ID and port number
   * @param[in] topologyID - ID of the router
   * @param[in] port       - DFP number
   * @return New topology ID
   */
UINT64 usb4_next_router_topology(UINT64 topologyID, UINT32 port);


/**
  * @brief Split topology ID into parent topology id and a parent port number
  * @param[in] topologyID - ID of the router
  * @param[out] router - ID of the parent router
  * @param[out] port - port of the parent router
  * @return depth value
  */
int usb4_get_router_and_port(UINT64 topologyID, UINT64* router, UINT32* port);

int usb4_utils_rand_uint8(UINT8 min, UINT8 max, UINT8* pRand);

int usb4_utils_rand_true_false(BOOLEAN* pRand);

int usb4_utils_rand(UINT32 min, UINT32 max, UINT32* pRand);

int usb4_utils_rand_range(UINT32 min, 
                          UINT32 max,
                          UINT32* pStart,
                          UINT32* pEnd);

UINT32 Usb4UtilGetRandomNumber(UINT32 max);

#define USB4_WHILE_WITH_TIMEOUT(COND, TIMEOUT_MS, RC) \
{\
    UINT32 timeout = 0;\
    UINT32 step = 0;\
    usb4_utils_timer timer; \
    timer.m_source = USB4_TIMER_SOURCE_QTIMER; \
    RC = 0; \
    step = MAX(1,(TIMEOUT_MS + 9)/10); \
    while((COND) && (timeout<TIMEOUT_MS))\
    {\
        usb4_timer_Sleep_ms(&timer, step);\
        timeout = timeout + step;\
    }\
    if (timeout >=TIMEOUT_MS)\
    {\
        RC = -1; \
    }\
}

#endif /* __USB4UTILS_H__ */
