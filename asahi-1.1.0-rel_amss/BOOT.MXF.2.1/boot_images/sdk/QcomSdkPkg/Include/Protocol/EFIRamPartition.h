/** 
  @file  EFIRamPartition.h
  @brief RamPartition EFI protocol interface.
*/
/*=============================================================================
  Copyright (c) 2015,2018-2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/15/20   cm      Preload ram partitions changes
 07/20/20   cm      Add preload region support
 03/18/20   am      Added GetInstalledPhysicalMemory module in rampartition protocol
 06/05/18   daisond Added GetMinPasrSize module in rampartition protocol
 09/30/15   vk      Initial Revision
=============================================================================*/

#ifndef __EFIRAMPARTITION_H__
#define __EFIRAMPARTITION_H__

/** @defgroup EFI_RAMPARTITION_PROTOCOL  EFI_RAMPARTITION_PROTOCOL
 *  @ingroup PERIPHERALS 
 */
 /** @defgroup  EFI_RAMPARTITION_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_RAMPARTITION_PROTOCOL 
 */ 
 /** @defgroup  EFI_RAMPARTITION_PROTOCOL_apis APIs
 *  @ingroup EFI_RAMPARTITION_PROTOCOL 
 */ 

/** @defgroup  EFI_RAMPARTITION_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_RAMPARTITION_PROTOCOL 
 */ 

/** @cond */
typedef struct _EFI_RAMPARTITION_PROTOCOL EFI_RAMPARTITION_PROTOCOL;
/** @endcond */

/** @addtogroup EFI_RAMPARTITION_PROTOCOL_data 
@{ */
/**
  Protocol version. 
*/
#define EFI_RAMPARTITION_PROTOCOL_REVISION 0x0000000000010002
/** @} */ /* end_addtogroup EFI_RAMPARTITION_PROTOCOL_data */

/*  Protocol GUID definition */
/** @ingroup EFI_RAMPARTITION_PROTOCOL_prot */
#define EFI_RAMPARTITION_PROTOCOL_GUID \
   { 0x5172FFB5, 0x4253, 0x7D51, { 0xC6, 0x41, 0xA7, 0x01, 0xF9, 0x73, 0x10, 0x3C } }
  
/** @cond */
/**
  External reference to the RAMPARTITION Protocol GUID defined 
  in the .dec file. 
*/
extern EFI_GUID gEfiRamPartitionProtocolGuid;
/** @endcond */

/**@ingroup EFI_RAMPARTITION_PROTOCOL_data
* @{ */
typedef struct _RamPartition
{
  UINT64 Base;
  UINT64 AvailableLength;
}RamPartitionEntry;

#define MAX_NAME_SZ 32

typedef struct _PreLoadedRamPartition
{
  UINT64 Base;
  UINT64 Size;
  UINT32 partition_type; //ram_partition_type_t
}PreLoadedRamPartition;

/** @} */ /* end_addtogroup EFI_RAMPARTITION_PROTOCOL_data */

/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/


/* ============================================================================
**  Function : EFI_RamPartition_GetRamPartitionVersion
** ============================================================================
*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_apis 
  @par Summary
  Gets the RAM Partition table version.
    
  @param[in]   This            Pointer to the EFI_RAMPARTITION_PROTOCOL instance.
  @param[out]  MajorVersion    Pointer to UINT32 which returns RAM partition table version  
  @param[out]  MinorVersion    Pointer to UINT32 which returns RAM partition table version  
                        
                       

  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_RAMPARTITION_GETRAMPARTITIONVERSION)(
   IN EFI_RAMPARTITION_PROTOCOL *This,
   OUT UINT32                   *MajorVersion,
   OUT UINT32                   *MinorVersion
   );

/* ============================================================================
**  Function : EFI_RamPartition_GetHighestBankBit
** ============================================================================
*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_apis
  @par Summary
  Gets the RAM Partition table version.
    
  @param[in]   This            Pointer to the EFI_RAMPARTITION_PROTOCOL instance.
  @param[out]  HighestBankBit  Pointer to Highest Bank Bit   
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_RAMPARTITION_GETHIGHESTBANKBIT)(
   IN EFI_RAMPARTITION_PROTOCOL *This,
   OUT UINT32                   *HighestBankBit
   );

/* ============================================================================
**  Function : EFI_RamPartition_GetMinPasrSize
** ============================================================================
*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_apis
  @par Summary
  Gets the MinPasrSize
    
  @param[in]   This            Pointer to the EFI_RAMPARTITION_PROTOCOL instance.
  @param[out]  MinPasrSize     Pointer to MinPasrSize   
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_RAMPARTITION_GETMINPASRSIZE)(
   IN EFI_RAMPARTITION_PROTOCOL *This,
   OUT UINT32                   *MinPasrSize
   );


/* ============================================================================
**  Function : EFI_RamPartition_GetRamPartitions
** ============================================================================
*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_apis
  @par Summary
  Gets the Ram version as read from the hardware register.
    
  @param[in]   This       Pointer to the EFI_RAMPARTITION_PROTOCOL instance.
  @param[out]  pnVersion  Pointer to a UINT32 passed by the caller that
                          will be populated by the driver.

  @return
  EFI_SUCCESS          -- Function completed successfully. \n
  EFI_BUFFER_TOO_SMALL -- Returns number of partitions available
  EFI_PROTOCOL_ERROR   -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_RAMPARTITION_GETRAMPARTITIONS)(
   IN EFI_RAMPARTITION_PROTOCOL* This,
   OUT RamPartitionEntry         *RamPartitions,
   IN OUT UINT32                 *NumPartition
   );
   
/* ============================================================================
**  Function : EFI_RamPartition_GetInstalledPhysicalMemory
** ============================================================================
*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_apis
  @par Summary
  Gets the MemoryCapacity
    
  @param[in]   This               Pointer to the EFI_RAMPARTITION_PROTOCOL instance.
  @param[out]  MemoryCapacity     Pointer to MemoryCapacity   
                        
  @return
  EFI_SUCCESS        -- Function completed successfully. \n
  EFI_PROTOCOL_ERROR -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_RAMPARTITION_GETINSTALLEDPHYSICALMEMORY)(
   IN EFI_RAMPARTITION_PROTOCOL *This,
   OUT UINTN                    *MemoryCapacity
   );
   

/* ============================================================================
**  Function : EFI_RamPartition_GetPreLoadedImageTable
** ============================================================================
*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_apis
  @par Summary
  Gets the Ram version as read from the hardware register.
    
  @param[in]   This       Pointer to the EFI_RAMPARTITION_PROTOCOL instance.
  @param[out]  pnVersion  Pointer to a UINT32 passed by the caller that
                          will be populated by the driver.

  @return
  EFI_SUCCESS          -- Function completed successfully. \n
  EFI_BUFFER_TOO_SMALL -- Returns number of partitions available
  EFI_PROTOCOL_ERROR   -- Error occurred during the operation.
*/

/* ============================================================================
**  Function : EFI_RamPartition_GetPreLoadedRampartitions
** ============================================================================
*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_apis
  @par Summary
  Gets the Pre loaded Rampartitions.
    
  @param[out]      PreLoadedRamPartitions       Pointer to PreloadedRamPartition table.
  @param[in out]   NumPartition                 Pointer to Number of partitions.

  @return
  EFI_SUCCESS          -- Function completed successfully. \n
  EFI_BUFFER_TOO_SMALL -- Returns number of partitions available
  EFI_PROTOCOL_ERROR   -- Error occurred during the operation.
*/
typedef 
EFI_STATUS
(EFIAPI *EFI_RAMPARTITION_GETPRELOADEDRAMPARTITIONS)(
   IN EFI_RAMPARTITION_PROTOCOL* This,
   OUT PreLoadedRamPartition     *PreLoadedRamPartitions,
   IN OUT UINTN                  *NumPartition
   );



/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup EFI_RAMPARTITION_PROTOCOL_prot 
  @par Summary
  Ram Information Protocol interface.

  @par Parameters
*/
struct _EFI_RAMPARTITION_PROTOCOL {
   UINT64                                      Revision;
   EFI_RAMPARTITION_GETRAMPARTITIONVERSION     GetRamPartitionVersion;
   EFI_RAMPARTITION_GETHIGHESTBANKBIT          GetHighestBankBit;
   EFI_RAMPARTITION_GETRAMPARTITIONS           GetRamPartitions;
   EFI_RAMPARTITION_GETMINPASRSIZE             GetMinPasrSize;
   EFI_RAMPARTITION_GETINSTALLEDPHYSICALMEMORY GetInstalledPhysicalMemory;
   EFI_RAMPARTITION_GETPRELOADEDRAMPARTITIONS  GetPreLoadedRamPartitions;
}; 

#endif /* __EFIRAMPARTITION_H__ */

