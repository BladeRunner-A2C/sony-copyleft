/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 26/9/21   zxue     handle irq with budget
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_INTERRUPT_H
#define __QDF_INTERRUPT_H

struct napi_struct {
    void* napi;
};

typedef int(*irq_handler_t)(int, int, void *);

int __request_poll_irq(unsigned int irq, irq_handler_t handler,
    const char *name, void *dev);
const void *__free_poll_irq(unsigned int irq, void *dev_id);
void __enable_poll_irq(unsigned int irq);
void __disable_poll_irq(unsigned int irq);
void __synchronize_poll_irq(unsigned int irq);
int __global_poll_irqs(int budget);

static inline int request_irq(unsigned int irq, irq_handler_t handler,
    const char *name, void *dev)
{
    return __request_poll_irq(irq, handler, name, dev);
}

static inline const void *free_irq(unsigned int irq, void *dev_id)
{
    return __free_poll_irq(irq, dev_id);
}

static inline void enable_irq(unsigned int irq)
{
    __enable_poll_irq(irq);
}

static inline void disable_irq(unsigned int irq)
{
    __disable_poll_irq(irq);
}

static inline void disable_irq_nosync(unsigned int irq)
{
    __disable_poll_irq(irq);
}

static inline void synchronize_irq(unsigned int irq)
{
    __synchronize_poll_irq(irq);
}

static inline int poll_irqs(int budget)
{
    return __global_poll_irqs(budget);
}

#endif // !__QDF_INTERRUPT_H

