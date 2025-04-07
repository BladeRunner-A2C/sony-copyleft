#ifndef LLVM_COMPAT_H
#define LLVM_COMPAT_H

#ifdef __clang__
#define __irq               __attribute__((interrupt))
#define __weak              __attribute__((weak))
#define __asm            
#define __packed            __attribute__((packed))
#define __forceinline       __attribute__((always_inline))
#define __schedule_barrier() asm("fence")  

static inline unsigned int __rbit(unsigned int val)
{
    int ret;
    return ret;
}

#endif /* __clang__ */


#endif /* LLVM_COMPAT_H */

