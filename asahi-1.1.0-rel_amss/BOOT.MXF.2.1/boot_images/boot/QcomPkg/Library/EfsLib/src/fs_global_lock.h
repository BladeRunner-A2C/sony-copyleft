/***********************************************************************
 * fs_global_lock.h
 *
 * FS_GLOBAL_LOCK critical section
 * Copyright (C) 2007, 2009 QUALCOMM Technologies, Inc.
 *
 * The FS_GLOBAL_LOCK is used to protect the file system data from
 * concurrent access.
 *
 ***********************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/EfsLib/src/fs_global_lock.h#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2009-04-01   ebb   Expose protect/unprotect memory fns for format/checkfat.
2007-08-19   rp    Create

===========================================================================*/

#ifndef __FS_GLOBAL_LOCK_H__
#define __FS_GLOBAL_LOCK_H__

void fs_global_lock_init (void);
void fs_global_lock (void);
void fs_global_unlock (void);

#define FS_GLOBAL_LOCK_INIT() fs_global_lock_init()
#define FS_GLOBAL_LOCK()     fs_global_lock ()
#define FS_GLOBAL_UNLOCK()   fs_global_unlock ()


#endif /* not __FS_GLOBAL_LOCK_H__ */

