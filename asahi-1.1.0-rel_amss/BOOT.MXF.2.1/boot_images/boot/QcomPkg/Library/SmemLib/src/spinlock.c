/*=============================================================================

                          SMEM SPINLOCK STUBS

 Copyright (c)  2023 Qualcomm Technologies, Inc. 
 All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1/QcomPkg/Library/SmemLib/src/spinlock_stubs.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "smem_os.h"
#include "spinlock.h"
#include "smem_target.h"
#include <Uefi.h>
#include <Library/KernelLib.h>
#include <Library/BaseLib.h>
/*=============================================================================

                         MACRO DEFINITIONS

=============================================================================*/
#define SMEM_UNUSED_ARGUEMENT(arg) \
  do { \
    arg = arg; \
  } while(0)

#define SMEM_LOCK_ID "SMEMLOCK"

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/

/*=============================================================================

                         FORWARD DECLARATIONS

=============================================================================*/

/*=============================================================================

                       PUBLIC/GLOBAL DATA DEFINITIONS

=============================================================================*/
static uint32 spinlock_count[SPINLOCK_NUM_LOCKS] = {0};
LockHandle *handle;

/*=============================================================================

                       LOCAL DATA DEFINITIONS

=============================================================================*/
/*=============================================================================

                      LOCAL FUNCTION DEFINITIONS

=============================================================================*/


/*=============================================================================
  FUNCTION  <function>
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/

/*=============================================================================

                     PUBLIC FUNCTION DEFINITIONS

=============================================================================*/

void smem_os_init(void)
{
  EFI_STATUS status = InitRecursiveLock(SMEM_LOCK_ID,  &handle);
  SMEM_UNUSED_ARGUEMENT(status);
}

void smem_os_intlock(void) 
{
  if(handle)
  {
    AcquireLock(handle);
  }
  else
  {
    SMEM_OS_LOG_FATAL(0, "Lock handle not initialized");    
  }
}

void smem_os_intfree(void) 
{
  if(handle)
  {
    ReleaseLock(handle);
  }
  else
  {
    SMEM_OS_LOG_FATAL(0, "Lock handle not initialized");   
  }
}


/*===========================================================================
FUNCTION      smem_spin_lock_init
===========================================================================*/
/**
  Initializes spinlocks.
 
  Spinlocks are used to acquire exclusive access to resources shared by
  all processors in the system.
 
  @return
  NA.
 
  @dependencies
  None.

  @sideeffects
  Initializes OS specific mutual exclusion mechanisms.
*/
/*=========================================================================*/
void smem_spin_lock_init(void)
{
  /* Nothing to do */
}

/*===========================================================================
FUNCTION      smem_spin_lock
===========================================================================*/
/**
  Acquires a spinlock as indicated by input integer, protected by non-
  preemtable critical section (effectively locking interrupts).
 
  @param[in] lock    Spinlock identifier.

  @return
  NA.
 
  @dependencies
  None.

  @sideeffects
  Prevents context switch (via critical section) and causes remote
  processors to spin if they try to use the same resource (via spinlock).
*/
/*=========================================================================*/
void smem_spin_lock(uint8 lock)
{
  if (lock >= SPINLOCK_NUM_LOCKS)
  {
    SMEM_OS_LOG_FATAL(2, "Invalid argument to spin_lock!, lock=%d, "
        "max=%d.", lock, SPINLOCK_NUM_LOCKS);
  }
  
  /* Lock the non-preemtable critical section */
  smem_os_intlock();
  
  /* Increment count.  This allows us to track how many unlocks to wait for. */
  spinlock_count[lock]++;

  /* Acquire spinlock */
  smem_targ_spin_lock(lock);
}

/*===========================================================================
FUNCTION      smem_spin_unlock
===========================================================================*/
/**
  Releases a spin lock as indicated by input integer, protected by non-
  preemtable critical section (effectively unlocking interrupts).
 
  @param[in] lock    Spinlock identifier.

  @return
  NA.
 
  @dependencies
  None.

  @sideeffects
  Allows other threads (via critical section) and remote processors (via
  spinlock) to acquire the shared resource.
*/
/*=========================================================================*/
void smem_spin_unlock(uint8 lock)
{
  if (lock >= SPINLOCK_NUM_LOCKS)
  {
    SMEM_OS_LOG_FATAL(2, "Invalid argument to spin_unlock!, lock=%d, "
        "max=%d.", lock, SPINLOCK_NUM_LOCKS);
  }
  
  /* If not locked, just return */
  if (0 == spinlock_count[lock])
  {
    /* Unlock the non-preemptable critical section */
    smem_os_intfree();
    return;
  }

  /* Decrement lock count */
  spinlock_count[lock]--;

  /* Check if there are additional outstanding locks. */
  if (!spinlock_count[lock])
  {
    smem_targ_spin_unlock(lock);
  }

  /* Unlock the non-preemptable critical section */
  smem_os_intfree();
}

/*===========================================================================
  FUNCTION  smem_clear_spin_locks
===========================================================================*/
/**
  This function unlocks all spinlocks held by the specified host.
 
  Mutex characteristics:
   - Each Mutex has a separate read/write Mutex-register
   - Each Mutex-register can hold an integer value
   - '0' value = Mutex is free/unlocked
   - Non-zero value = Mutex is locked
 
  A more detailed description can be found in System FPB (80-VR139-1A Rev. A)
  documentation.

  @param[in] host      Host identifier.

  @return
  None

  @dependencies 
  None.

  @sideeffects
  None.
*/
/*==========================================================================*/
void smem_spin_locks_clear(smem_host_type host)
{
  /* Lock the critical section */
  smem_os_intlock();

  /* Clear the spinlocks hold by the specified processor */
  smem_spin_locks_clear_nolock( host );

  /* Unlock the critical section */
  smem_os_intfree();
}


/*===========================================================================
  FUNCTION  smem_spin_locks_clear_nolock
===========================================================================*/
/**
  This function unlocks all spinlocks held by the specified host without 
  acquiring local critical section(lock)
 
  Mutex characteristics:
   - Each Mutex has a separate read/write Mutex-register
   - Each Mutex-register can hold an integer value
   - '0' value = Mutex is free/unlocked
   - Non-zero value = Mutex is locked
 
  @param[in] host      Host identifier.

  @return
  None

  @dependencies 
  None.

  @sideeffects
  None.
*/
/*==========================================================================*/
void smem_spin_locks_clear_nolock( smem_host_type host )
{
  uint8 i;

  /* Clear the spinlocks hold by the specified processor.
     Avoid the TCSR Mutex Register 0 access.           */
  for( i = 1; i < SPINLOCK_NUM_LOCKS; i++ )
  {
    /* Check if spinlock is held by the host  */
    /* (host + 1) is the spinlock id */
    if( (host + 1) == smem_targ_spin_lock_get( i ) )
    {
      /* Release the spinlock */
      smem_targ_spin_unlock( i );
    }
  }
}