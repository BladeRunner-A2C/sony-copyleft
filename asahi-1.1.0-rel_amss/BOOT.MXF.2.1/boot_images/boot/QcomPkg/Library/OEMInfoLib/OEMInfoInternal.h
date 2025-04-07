#ifndef __OEMINFOINTERNAL_H__
#define __OEMINFOINTERNAL_H__

/**
 *   @file OEMInfoInternal.h
 *   @brief Private interface include file for accessing the OEMInfo driver.
 **/

/*=============================================================================
 *   Copyright (c) 2022, 2024 Qualcomm Technologies, Inc. All rights reserved.
 *   Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*=========================================================================
 *   Include Files
=========================================================================*/
#include <OEMInfo.h>
#include <DTBExtnLib.h>

// Node name for ADC OEMDevices
#define OEMINFO_ADC_DEVICE_STR "ADC"

// Node name for PMICGpio OEMDevices
#define OEMINFO_PMICGPIO_DEVICE_STR "PMICGpio"

// Node name for SOC GPIO OEMDevices
#define OEMINFO_SOCGPIO_DEVICE_STR "SOCGpio"

#define OEMINFO_OEMDEVICES_NODE_PATH		"/soc/OEMInfo/OEMDevices"
#define OEMINFO_ADC_NODE_PATH				OEMINFO_OEMDEVICES_NODE_PATH "/" OEMINFO_ADC_DEVICE_STR
#define OEMINFO_PMICGPIO_NODE_PATH			OEMINFO_OEMDEVICES_NODE_PATH "/" OEMINFO_PMICGPIO_DEVICE_STR
#define OEMINFO_SOCGPIO_NODE_PATH			OEMINFO_OEMDEVICES_NODE_PATH "/" OEMINFO_SOCGPIO_DEVICE_STR

// Subnodes: IO devices (ADC, GPIO, etc.)
// strlen+1 of the longest allowed IO device's name (PMICGpio).
#define OEMINFO_MAX_IODEVICE_NAME_LEN 9U

// Number of IO devices
#define OEMINFO_MAX_DEVICES     3U

// Maximum expected length for all IO device names concatenated together,
// with null-terminators in between.
// e.g., if /soc/OEMInfo/OEMDevices has PMICGpio, SOCGpio, and ADC in
// that order, this macro should be long enough to hold
// "PMICGpio\0SOCGpio\0ADC\0", which is 21 characters.
#define OEMINFO_MAX_CONCATENATED_IODEVICE_NAME_LEN 21U
#define OEMINFO_ADC_PROP_STR			"ADCMsmt"
#define OEMINFO_PMIC_PROP_STR			"Pmic"
#define OEMINFO_GPIO_PROP_STR			"Gpio"
#define OEMINFO_OEMVARIANT_PROP_STR		"OEMVariant"

/*=========================================================================
 *   Type Definitions
=========================================================================*/

/**
 * Enumeration of potential IO devices used to determine OEM variant
 */
typedef enum
{
	OEMINFO_IOTYPE_UNKNOWN,
    ADC,			/**< Analog to Digital Converter */
    PMICGPIO,		/**< GPIO pins provided by PMIC */
    SOCGPIO,		/**< GPIO pins provided by SOC */
} OEMInfoIOType;

// A wrapper of /soc/OEMInfo/OEMDevices

typedef struct
{
    // Number of devices actually defined in DTB.
    uint32_t            nNumIODevices;

    // Parent node, i.e. /soc/OEMInfo
    fdt_node_handle		*phFDTParent;

    // Names of defined IO devices, indexed by OEMInfoIOType.
    // Array of `nNumIODevices` null-terminated strings.

    char				**szIODeviceNames;

} OEMFDTHandle;

typedef struct
{
    // Final mapped OEM Variant ID
    uint32_t            nOEMVariant;

    // Index, in the OEMVariant array for the IO device, which has a
    // valid OEM Variant ID mapping
    uint8_t             nOEMVariantIdx;

    // Number of mappings defined in the DTB for uOEMIODevice
    uint32_t            nNumOEMVariants;

    // Type of the IO device where the OEM variant ID mapping was found
    OEMInfoIOType       eOEMIOType;

    OEMFDTHandle        hOEMFDTHandle;
    bool                bCtxtInit;
} OEMInfoCtxtType;


/*=========================================================================
 *   Function Definitions
=========================================================================*/
void *OEMInfo_malloc(size_t size);
void OEMInfo_free(void *pMem);
void *OEMInfo_memset(void *str, int c, size_t n);

OEMInfoResult   OEMInfoInternal_Init        (void);
OEMInfoResult   OEMInfoInternal_DTInit      (OEMInfoCtxtType *pCtxt);
OEMInfoResult   OEMInfoInternal_GetIODeviceNamesFromDTBString    (OEMInfoCtxtType *pCtxt, char *sNames, uint32_t *anLengths, uint32_t nNumDevices);
OEMInfoResult   OEMInfoInternal_ADCInit     (OEMInfoCtxtType *pCtxt);
OEMInfoResult   OEMInfoInternal_PMICInit    (OEMInfoCtxtType *pCtxt);
OEMInfoResult   OEMInfoInternal_SOCInit     (OEMInfoCtxtType *pCtxt);
OEMInfoResult   OEMInfoInternal_SetVariant  (OEMInfoCtxtType *pCtxt);

void        OEMInfo_Init        (void);
uint32_t    OEMInfo_GetVarCt    (void);

#endif
