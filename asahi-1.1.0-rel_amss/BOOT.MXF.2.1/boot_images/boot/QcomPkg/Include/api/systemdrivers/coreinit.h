#ifndef COREINIT_H
#define COREINIT_H
/**
@file coreinit.h

@brief Core default resource voting driver.

===========================================================================
                             Edit History
$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/api/systemdrivers/coreinit.h#1 $

when         who     what, where, why
----------   ---     --------------------------------------------------------
2020/03/27   sds     Initial revision

===========================================================================
           Copyright 2020 QUALCOMM Technologies, Incorporated.
                       All Rights Reserved.
                     QUALCOMM Proprietary/GTDR
===========================================================================
*/

/*=============================================================================

                           FUNCTION DEFINITIONS

=============================================================================*/


/* ============================================================================
**  Function : coreinit_init
** ============================================================================
*/
/*!
    @brief
    Initializes and issues any core system default resource votes.
*/
void coreinit_init (void);

#endif /* COREINIT_H */

