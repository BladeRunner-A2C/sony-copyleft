.. -*- coding: utf-8 -*-

.. /*=============================================================================
     Readme file for UEFI Scheduler Unsafe Stack support
   
     Copyright (c) 2019 Qualcomm Technologies, Inc. All rights reserved.
   
                                 EDIT HISTORY
   
   when       who     what, where, why
   --------   ---     -----------------------------------------------------------
   11/08/19   md      Initial version
   =============================================================================*/


.. _UEFISchedulerUnsafeStackSupport:

===============================
UEFISchedulerUnsafeStackSupport
===============================


Introduction
------------

UEFI scheduler will allocate unsafe stack for each thread created by client. 


Unsafe stack Introduction
-------------------------

SafeStack is an instrumentation pass that protects programs against attacks 
based on stack buffer overflows, without introducing any measurable performance 
overhead. It works by separating the program stack into two distinct regions: 
the safe stack and the unsafe stack. The safe stack stores return addresses, 
register spills, and local variables that are always accessed in a safe way, 
while the unsafe stack stores everything else. This separation ensures that 
buffer overflows on the unsafe stack cannot be used to overwrite anything on 
the safe stack.

Currently UEFI does not have safe stack support for overall UEFI core. 
It only provides API's for client to use for implementing safe stack in their 
code when using Scheduler/Multithreading.

Client should provide the memory for unsafe stack and it is the
responsibility of client to free up that space.


APIs provided to support unsafe stack
-------------------------------------

Clients that implements safe stack feature should call following API's to implement 
builtin safe stack API's::

  __builtin___get_unsafe_stack_ptr():

  VOID** ThreadGetUnsafeSPCurrent (Thread *Thr)  
  This returns Unsafe stack current/top of SP for a particular thread.

  __builtin___get_unsafe_stack_bottom():

  VOID* ThreadGetUnsafeSPBase (Thread *Thr)
  This returns base/start of unsafe stack for a particular thread.

  __builtin___get_unsafe_stack_top():

  API for this is not implemented. The client can get this info through base + size. 

                          
   __________________unsafe_stack_top     
  |           |                           | 
  |           |                           | unsafe stack size
  |           |                           |
  |___________|                           |
  |Padding    |                           |
  |___________|_____unsafe_stack_base-----|
   

For bound check, allocate unsafe stack of size =  required stack size + Padding size

Get Padding size by calling ``ThreadGetUnsafeStackPaddingSize ()``

In Size parameter pass allocated unsafe stack size.

``UINT64 ThreadGetUnsafeStackPaddingSize (VOID)``

This Returns size of the padding that will be used in unsafe stack for bound 
check.

``KStatus ThreadSetUnsafeSP (Thread *Thr, ThrUnsafeStackIntf *)``

This sets thread unsafe stack related information which includes::

  i.   Base
  ii.  Top of the stack.
  iii. Size.
  iv.  Callback function to be called at the time of thread termination. 
  v.   Callback function params.  

.. note::

   Callback function implemented by API should ONLY be used to free up unsafe stack.
   It should not be used for anything else. 


Limitations
-----------

Currently UEFI core will be setting up unsafe stack for DXE and Timer Thread only.
Other threads (Shutdown, idle threads) created by UEFI core will not have unsafe stack. 

 
