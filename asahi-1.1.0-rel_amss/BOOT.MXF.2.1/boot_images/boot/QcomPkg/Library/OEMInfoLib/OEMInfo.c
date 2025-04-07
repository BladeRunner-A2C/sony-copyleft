/**
 *   @file OEMInfo.c
 *
 *   Interface implementation file for the OEMInfo driver.
 **/

/*
 *====================================================================
 *
 *     Copyright (c) 2022, 2024 Qualcomm Technologies, Inc. All rights reserved.
 *     Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 *====================================================================
 *
 *
 *====================================================================
 */


/*=========================================================================
 *   Include Files
==========================================================================*/
#include "OEMInfo.h"
#include "OEMInfoDefs.h"
#include "OEMInfoInternal.h"
#include "adc.h"
#include "DTBExtnLib.h"
#include "DALSys.h"
#include "GPIO.h"
#include "GPIOTypes.h"
#include "pm_gpio.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <boot_logger_if.h>
#include <stdio.h>
/*========================================================================
 *   Global Data
=========================================================================*/

// String used to query the ADC driver for the OEMVariantID
#define OEMINFO_ADC_INPUT_OEM_ID "OEM_VID"

/*
 * TODO: These handles are declared at the module level because they're
 * stored in OEMInfoCtxt. This isn't necessary because they don't have
 * any useful debugging information, but making them local variables
 * requires some reworking of the logic.
 */

// Handle to /soc/OEMInfo
static fdt_node_handle			hSocOEMInfoNode;

// Handle to /soc/OEMInfo/OEMDevices
static OEMFDTHandle				hOEMDeviceNode;

// OEMInfo driver context
static OEMInfoCtxtType OEMInfoCtxt;

GPIOClientHandleType   OEM_GPIO_HANDLE;


/* =============================================================================
 *  Function : OEMInfo_Init
 * ===========================================================================*/
/**
 * @brief           Wrapper for internal initialization function for the OEM structure.
 *
 * @param           N/A
 * @return          N/A
 */
void
OEMInfo_Init(void)
{
    OEMInfoInternal_Init();
}

/* =============================================================================
 *  Function : OEMInfoInternal_Init
 * ===========================================================================*/
/**
 * @brief       Internal initialization function that parses DT and builds OEM
 *              the OEM structure.
 *
 * @param[in]   N/A
 * @return
 * OEMINFO_SUCCESS         -- Function succeeded \n
 * OEMINFO_FAILURE         -- Function failed \n
 * OEMINFO_DTB_FAILURE      -- DTB function failure \n
 * OEMINFO_READ_FAILURE     -- IO device read failure \n
 * OEMINFO_ATTACH_FAILURE   -- IO device attach/enable failure \n
 * OEMINFO_SETVAR_FAILURE   -- Failure to set OEM variant \n
 * OEMINFO_SUCCESS_NO_DT     -- Could not find DT node \n
 */
OEMInfoResult
OEMInfoInternal_Init(void)
{
    OEMInfoResult eOEM;
	char buf[32];

    // If context is already initialized, nothing to do
    if (OEMInfoCtxt.bCtxtInit)
    {
        return OEMINFO_SUCCESS;
    }

    eOEM = OEMInfoInternal_DTInit(&OEMInfoCtxt);
    if (eOEM != OEMINFO_SUCCESS && eOEM != OEMINFO_SUCCESS_NO_DT)
    {
		snprintf(buf, sizeof(buf), "OEMInfo: OEMInfoIOType %d, error 0x%08x", OEMInfoCtxt.eOEMIOType, eOEM);
		boot_log_message(buf);
        return eOEM;
    }
	
	snprintf(buf, sizeof(buf), "OEMInfo: variant %d", OEMInfoCtxt.nOEMVariant);
	boot_log_message(buf);
    OEMInfoCtxt.bCtxtInit = true;

    return eOEM;
}

/* =============================================================================
 *  Function : OEMInfoInternal_DTInit
 * ===========================================================================*/
/**
 * @brief       Initializes the OEM DT and Context in memory.
 *
 * @param[in]   pCtxt   Pointer to the OEMInfo context data structure
 * @return
 * OEM_INFO_SUCCESS     -- Function succeeded \n
 * OEM_INFO_FAILURE     -- Function failed \n
 */
OEMInfoResult
OEMInfoInternal_DTInit(OEMInfoCtxtType *pCtxt)
{
    int                 nDTResult   = 0;
    uint32_t            i;
    uint32_t            *anIODeviceNameLengths = NULL;
    char                *sIODeviceName;
    char                *szIODeviceNames = NULL;
    uint32_t			nNumIODevices = 0;
	OEMInfoResult		eResult;
	uint32_t			nMaxConcatenatedIODeviceNameLen;
	char				buf[80];
	
    // Start by initializing Context pointers
    pCtxt->hOEMFDTHandle                = hOEMDeviceNode;
    pCtxt->hOEMFDTHandle.phFDTParent    = &hSocOEMInfoNode;

    // Get the handle to the OEMInfo DT node, /soc/OEMInfo/OEMDevices
    nDTResult = fdt_get_node_handle(pCtxt->hOEMFDTHandle.phFDTParent,
                                        NULL, OEMINFO_OEMDEVICES_NODE_PATH);
    if (nDTResult)
    {
        return OEMINFO_SUCCESS_NO_DT;
    }

    // Get the number of IO devices defined in the DT
    nDTResult = fdt_get_count_of_subnodes(pCtxt->hOEMFDTHandle.phFDTParent,
                                        &nNumIODevices);
    if (nDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    // TODO: Since we don't support more than one IO device, should we
	// return an error if more than 1 is specified, or should we
	// pick the last one? The released doc says "only one is supported".
	// TODO: Does this even matter? Why can't we loop through IO devices
	// until the first matching OEM variant ID? We'd want to place a
	// limit on the number of devices to avoid DoS with thousands of
	// OEMDevices, but there's no practical limit otherwise.
	if (nNumIODevices >= OEMINFO_MAX_DEVICES)
	{
		return OEMINFO_DTB_FAILURE;
	}
	
	pCtxt->hOEMFDTHandle.nNumIODevices = nNumIODevices;
	
	if (!nNumIODevices)
	{
		return OEMINFO_SUCCESS_NO_DT;
	}
	
	anIODeviceNameLengths = OEMInfo_malloc(nNumIODevices * sizeof(uint32_t));
	if (!anIODeviceNameLengths)
	{
		eResult = OEMINFO_FAILURE;
		goto ErrorExit;
	}
	
	// Get the names of each IO Device under /soc/OEMInfo/OEMDevices
	// These names are returned as a concatenated string up to the size
	// specified in the 3rd parameter. FDTLib requires an expected
	// maximum size for szIODeviceNames, and returns an error if
	// the size isn't large enough to hold all the \0-terminated names.
	nMaxConcatenatedIODeviceNameLen = nNumIODevices * OEMINFO_MAX_IODEVICE_NAME_LEN;
	szIODeviceNames = OEMInfo_malloc(nMaxConcatenatedIODeviceNameLen);
	if (!szIODeviceNames)
	{
		eResult = OEMINFO_FAILURE;
		goto ErrorExit;
	}
    nDTResult = fdt_get_subnode_names(pCtxt->hOEMFDTHandle.phFDTParent,
                                        szIODeviceNames,
                                        nMaxConcatenatedIODeviceNameLen);

    if (nDTResult)
    {
        eResult = OEMINFO_DTB_FAILURE;
		goto ErrorExit;
    }

    // Get the string lengths of each of the IO device names.
	// The entries in anIODeviceNameLengths are in the same order as the
	// names in szIODeviceNames.
    nDTResult = fdt_get_size_of_subnode_names(pCtxt->hOEMFDTHandle.phFDTParent,
                                                anIODeviceNameLengths,
                                                nNumIODevices);
    if (nDTResult)
    {
        eResult = OEMINFO_DTB_FAILURE;
		goto ErrorExit;
    }

    // Convert the concatenated string to a more useful array of strings
    eResult = OEMInfoInternal_GetIODeviceNamesFromDTBString(pCtxt,
												szIODeviceNames,
												anIODeviceNameLengths,
												nNumIODevices);
    if (OEMINFO_SUCCESS != eResult)
    {
        goto ErrorExit;
    }
	
	// The concatenated string is no longer needed, so free it.
	// Set pointers to NULL to avoid a double free in ErrorExit
	OEMInfo_free(szIODeviceNames);
	szIODeviceNames = NULL;
	OEMInfo_free(anIODeviceNameLengths);
	anIODeviceNameLengths = NULL;

    for (i = 0; i < pCtxt->hOEMFDTHandle.nNumIODevices; i++)
    {
        sIODeviceName = pCtxt->hOEMFDTHandle.szIODeviceNames[i];
		
		if (!strcmp(sIODeviceName, OEMINFO_ADC_DEVICE_STR))
        {
            pCtxt->eOEMIOType = ADC;
            eResult = OEMInfoInternal_ADCInit(pCtxt);
			if (OEMINFO_SUCCESS != eResult)
			{
				goto ErrorExit;
			}
        }
        else if (!strcmp(sIODeviceName, OEMINFO_PMICGPIO_DEVICE_STR))
        {
            pCtxt->eOEMIOType = PMICGPIO;
			eResult = OEMInfoInternal_PMICInit(pCtxt);
			if (OEMINFO_SUCCESS != eResult)
			{
				goto ErrorExit;
			}
        }
        else if (!strcmp(sIODeviceName, OEMINFO_SOCGPIO_DEVICE_STR))
        {
            pCtxt->eOEMIOType = SOCGPIO;
            eResult = OEMInfoInternal_SOCInit(pCtxt);

           if (OEMINFO_SUCCESS != eResult)
		   {
			   goto ErrorExit;
		   }
        }
        else
        {
            pCtxt->eOEMIOType = OEMINFO_IOTYPE_UNKNOWN;
			snprintf(buf, sizeof(buf), "OEMInfo: unknown OEMDevice: %s", sIODeviceName);
			boot_log_message(buf);
			eResult = OEMINFO_FAILURE;
			goto ErrorExit;
        }
    }

    return OEMINFO_SUCCESS;
	
	ErrorExit:
		if (anIODeviceNameLengths) OEMInfo_free(anIODeviceNameLengths);
		if (szIODeviceNames) OEMInfo_free(szIODeviceNames);
		return eResult;
}

/*
 * Convert a 1D array of several concatenated strings, with each string's length
 * defined in anLengths, into an array of pointers-to-strings.
 * String lengths in anLengths include the null terminator.
 *
 * The parsed array of null-terminated strings is stored in pCtxt->hOEMFDTHandle.szIODeviceNames
 *
 * This function allocates pCtxt->hOEMFDTHandle.szIODeviceNames.
 *
 * e.g.
 *      sNames = "ADCPMICGpio"
 *      anLengths = {3, 8}
 *
 * becomes:
 *      [0]: "ADC"
 *      [1]: "PMICGpio"
 */
OEMInfoResult
OEMInfoInternal_GetIODeviceNamesFromDTBString(OEMInfoCtxtType *pCtxt, char *sNames, uint32_t *anLengths, uint32_t nNumDevices)
{
    int i, start = 0;
	OEMInfoResult eResult = OEMINFO_FAILURE;

	// TODO Why enforce this limit?
    if (pCtxt->hOEMFDTHandle.nNumIODevices > OEMINFO_MAX_DEVICES)
    {
        return OEMINFO_FAILURE;
    }

    if (!nNumDevices)
    {
        // No strings to process => successfully processed all (0) strings.
        return OEMINFO_SUCCESS;
    }
	
	// Allocate enough space for the pointers to strings
	char **pStrings = OEMInfo_malloc(nNumDevices * sizeof(char *));
	if (!pStrings)
	{
		return OEMINFO_FAILURE;
	}
	OEMInfo_memset(pStrings, 0, nNumDevices * sizeof(char *));
	
	// Allocate space for each string
	for (i = 0; i < nNumDevices; i++)
	{
		pStrings[i] = OEMInfo_malloc(anLengths[i]);
		if (!pStrings[i])
		{
			eResult = OEMINFO_FAILURE;
			goto ErrorExit;
		}
	}
	
	// Populate the 2d array
	for (i = 0; i < nNumDevices; i++)
	{
		strlcpy(pStrings[i], &sNames[start], anLengths[i]);
		start += anLengths[i];
	}
	
	pCtxt->hOEMFDTHandle.szIODeviceNames = pStrings;

    return OEMINFO_SUCCESS;
	
	ErrorExit:
		if (pStrings)
		{
			for (int i = 0; i < nNumDevices; i++)
			{
				if (pStrings[i]) OEMInfo_free(pStrings[i]);
			}
			OEMInfo_free(pStrings);
		}
		return eResult;
}

OEMInfoResult
OEMInfoInternal_ADCInit(OEMInfoCtxtType *pCtxt)
{
    int                 i, bFDTResult = 0;
    uint32_t            nNumADCMeasurements, nBuffSize = 0;
    uint32_t            nUvolts, nUvoltsErr;
    fdt_node_handle     hADCNode;
    adc_status_type     eADCStatus = ADC_STATUS_SUCCESS;
    adc_result_type     ADCResult;
    uint32_t nMeasurement = 0, nVariant = 0;

    bFDTResult = fdt_get_node_handle(&hADCNode, NULL, OEMINFO_ADC_NODE_PATH);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    bFDTResult = fdt_get_prop_size(&hADCNode, OEMINFO_ADC_PROP_STR, &nBuffSize);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    nNumADCMeasurements = (uint32_t) nBuffSize/sizeof(uint32_t);

    if (!nNumADCMeasurements)
    {
        return OEMINFO_DTB_FAILURE;
    }

    bFDTResult = fdt_get_prop_size(&hADCNode, OEMINFO_OEMVARIANT_PROP_STR, &nBuffSize);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    pCtxt->nNumOEMVariants = (uint32_t) nBuffSize/sizeof(uint32_t);

    if (!pCtxt->nNumOEMVariants)
    {
        return OEMINFO_DTB_FAILURE;
    }

    if (nNumADCMeasurements != pCtxt->nNumOEMVariants)
    {
		// The cause for most of the other DTB_FAILURE errors should be
		// immediately obvious upon inspecting the DTSI (something was
		// empty). This error is less obvious, so log it.
		boot_log_message("OEMInfo: Error: len(ADCMsmt) != len(OEMVariant)");
		return OEMINFO_DTB_FAILURE;
    }

    eADCStatus = adc_read(OEMINFO_ADC_INPUT_OEM_ID, &ADCResult);
    if (ADC_STATUS_SUCCESS != eADCStatus)
    {
        return OEMINFO_READ_FAILURE;
    }

    // Check if the ADC reading matches any of the known ADC measurement
    // values from the DT. A value matches if the reading is within
    // 3.125% on either side of an ADCMsmt value, for a total error
    // band of 6.25%.
    nUvolts = (uint32_t) ADCResult.microvolts;

    for(i = 0; i < nNumADCMeasurements; i++)
    {
        bFDTResult = fdt_get_uint32_prop_list_slice(&hADCNode, 
													OEMINFO_ADC_PROP_STR, &nMeasurement, i, 1);
        if (bFDTResult)
        {
            return OEMINFO_DTB_FAILURE;
        }
		
		bFDTResult = fdt_get_uint32_prop_list_slice(&hADCNode, 
													OEMINFO_OEMVARIANT_PROP_STR, &nVariant, i, 1);
		if (bFDTResult)
		{
			return OEMINFO_DTB_FAILURE;
		}
		
		nUvoltsErr = nMeasurement >> 5;
		if ((nUvolts >= (nMeasurement - nUvoltsErr)) &&
			(nUvolts <= (nMeasurement + nUvoltsErr)))
		{
			pCtxt->nOEMVariantIdx = i;
			break;
		}
    }

    if (i == nNumADCMeasurements)
    {
        return OEMINFO_SETVAR_FAILURE;
    }

	pCtxt->nOEMVariant = nVariant;
    return OEMINFO_SUCCESS;
}

OEMInfoResult
OEMInfoInternal_PMICInit(OEMInfoCtxtType *pCtxt)
{
    int                 i, bFDTResult = 0;
    uint32_t            nNumGPIOs = 0, nNumPMICs = 0, nBuffSize = 0;
    fdt_node_handle		hPMICNode;
    pm_err_flag_type	bPMIC		= PM_ERR_FLAG_SUCCESS;
    pm_gpio_perph_index nPMICGpio	= PM_GPIO_INVALID;
    uint32_t			nPMICID = 0, nGPIOPin = 0;
    pm_gpio_level_type	nGPIOValue;

    bFDTResult = fdt_get_node_handle(&hPMICNode, NULL, OEMINFO_PMICGPIO_NODE_PATH);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    bFDTResult = fdt_get_prop_size(&hPMICNode, OEMINFO_PMIC_PROP_STR, &nBuffSize);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    nNumPMICs = (uint32_t) nBuffSize/sizeof(uint32_t);
    if (!nNumPMICs)
    {
        return OEMINFO_DTB_FAILURE;
    }

    bFDTResult = fdt_get_prop_size(&hPMICNode, OEMINFO_GPIO_PROP_STR, &nBuffSize);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    nNumGPIOs = (uint32_t) nBuffSize/sizeof(uint32_t);
    if (!nNumGPIOs)
    {
        return OEMINFO_DTB_FAILURE;
    }

    bFDTResult = fdt_get_prop_size(&hPMICNode, OEMINFO_OEMVARIANT_PROP_STR, &nBuffSize);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    pCtxt->nNumOEMVariants = (uint32_t)nBuffSize/sizeof(uint32_t);
    if (!pCtxt->nNumOEMVariants)
    {
        return OEMINFO_DTB_FAILURE;
    }

    if (nNumPMICs != nNumGPIOs)
    {
		// The requirement for nNumGPIOs >= ceil(log2(nNumOEMVariants))
		// is enforced in the for loop below.
		boot_log_message("OEMInfo: Error: #PMICIDs != #GPIOPins");
        return OEMINFO_DTB_FAILURE;
    }
	
	pCtxt->nOEMVariantIdx = 0;
	for (i = 0; i < nNumGPIOs; i++)
	{
		bFDTResult = fdt_get_uint32_prop_list_slice(&hPMICNode,
														OEMINFO_PMIC_PROP_STR, &nPMICID, i, 1);
		if (bFDTResult)
		{
			return OEMINFO_DTB_FAILURE;
		}
		
		bFDTResult = fdt_get_uint32_prop_list_slice(&hPMICNode,
														OEMINFO_GPIO_PROP_STR, &nGPIOPin, i, 1);
		if (bFDTResult)
		{
			return OEMINFO_DTB_FAILURE;
		}
		
		// PMIC GPIO enums are 1-indexed
		// e.g. PM_GPIO_1 = 0
		// PM_GPIO_2 = 1
		// OEMs will write 1 in OEMInfo.dtsi to select PMIC_GPIO_1.
		// Subtract 1 when casting to the enum.
		nPMICGpio = (pm_gpio_perph_index) (nGPIOPin - 1);
		bPMIC = pm_gpio_enable(nPMICID, nPMICGpio, true);
		
		if (PM_ERR_FLAG_SUCCESS != bPMIC)
		{
			return OEMINFO_ATTACH_FAILURE;
		}
		
		bPMIC = pm_gpio_input_level_status(nPMICID, nPMICGpio, &nGPIOValue);
		
		if (PM_ERR_FLAG_SUCCESS != bPMIC)
		{
			return OEMINFO_READ_FAILURE;
		}
		
		if (PM_GPIO_LEVEL_HIGH == nGPIOValue)
		{
			pCtxt->nOEMVariantIdx |= (1 << i);
			
			// Guard against buffer overflows when reading the
			// OEMVariant array. This only needs to be checked if the
			// extra GPIOs are HIGH; extra GPIOs that are all LOW will
			// add 0s to the MSB, which doesn't change the index.
			if (pCtxt->nOEMVariantIdx >= pCtxt->nNumOEMVariants)
			{
				boot_log_message("OEMInfo: Error: Mapped PMICGpio index out of range");
				return OEMINFO_DTB_FAILURE;
			}
		}
		// TODO: This disables the GPIO even if it was enabled before
		// we asked. Leaving it for now because OEM variants will
		// probably come from dedicated GPIOs.
		bPMIC = pm_gpio_enable(nPMICID, nPMICGpio, false);
	}
	bFDTResult = fdt_get_uint32_prop_list_slice(&hPMICNode,
												OEMINFO_OEMVARIANT_PROP_STR, &pCtxt->nOEMVariant, pCtxt->nOEMVariantIdx, 1);
	if (bFDTResult)
	{
		return OEMINFO_SETVAR_FAILURE;
	}
	
	return OEMINFO_SUCCESS;
}

OEMInfoResult
OEMInfoInternal_SOCInit(OEMInfoCtxtType *pCtxt)
{
    fdt_node_handle		hSOCNode;
    GPIOResult			eGPIOResult = GPIO_SUCCESS;
    uint32_t			nGPIOPin;
    GPIOKeyType			nGPIOID;
    GPIOValueType		nGPIOReading;
    uint32_t            nBuffSize     = 0;
    uint32_t            nNumGPIOs     = 0;
    int                 i, bFDTResult = 0;

    bFDTResult = fdt_get_node_handle(&hSOCNode, NULL, OEMINFO_SOCGPIO_NODE_PATH);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    bFDTResult = fdt_get_prop_size(&hSOCNode, OEMINFO_GPIO_PROP_STR, &nBuffSize);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    nNumGPIOs = (uint32_t) nBuffSize/sizeof(uint32_t);
	if (!nNumGPIOs)
    {
        return OEMINFO_DTB_FAILURE;
    }

    nBuffSize = 0;

    bFDTResult = fdt_get_prop_size(&hSOCNode, OEMINFO_OEMVARIANT_PROP_STR, &nBuffSize);
    if (bFDTResult)
    {
        return OEMINFO_DTB_FAILURE;
    }

    pCtxt->nNumOEMVariants = (uint32_t) nBuffSize/sizeof(uint32_t);
    if (!pCtxt->nNumOEMVariants)
    {
        return OEMINFO_DTB_FAILURE;
    }

    eGPIOResult = GPIO_Attach(GPIO_DEVICE_TLMM, &OEM_GPIO_HANDLE);
    if (GPIO_SUCCESS != eGPIOResult)
    {
        return OEMINFO_ATTACH_FAILURE;
    }

	pCtxt->nOEMVariantIdx = 0;
    for (i = 0; i < nNumGPIOs; i++)
    {
        bFDTResult = fdt_get_uint32_prop_list_slice(&hSOCNode,
														OEMINFO_GPIO_PROP_STR, &nGPIOPin, i, 1);
        if (bFDTResult)
        {
            return OEMINFO_DTB_FAILURE;
        }

        eGPIOResult = GPIO_RegisterPinExplicit(OEM_GPIO_HANDLE, nGPIOPin,
											GPIO_ACCESS_SHARED, &nGPIOID);
        if (GPIO_SUCCESS != eGPIOResult)
        {
            return OEMINFO_READ_FAILURE;
        }
		
		eGPIOResult = GPIO_ReadPin(OEM_GPIO_HANDLE, nGPIOID, &nGPIOReading);
		if (GPIO_SUCCESS != eGPIOResult)
		{
			return OEMINFO_READ_FAILURE;
		}

        if (nGPIOReading == GPIO_HIGH)
        {
            pCtxt->nOEMVariantIdx |= (1 << i);
			if (pCtxt->nOEMVariantIdx >= pCtxt->nNumOEMVariants)
			{
				boot_log_message("OEMInfo: Error: Mapped SOCGpio index out of range");
				return OEMINFO_DTB_FAILURE;
			}
        }
    }
	
	bFDTResult = fdt_get_uint32_prop_list_slice(&hSOCNode,
													OEMINFO_OEMVARIANT_PROP_STR, &pCtxt->nOEMVariant, pCtxt->nOEMVariantIdx, 1);
	if (bFDTResult)
    {
        return OEMINFO_SETVAR_FAILURE;
    }

    return OEMINFO_SUCCESS;
}

/* =============================================================================
 *  Function : OEMInfoInternal_GetVarCt
 * ===========================================================================*/
/**
 * @brief       Get the count of all potential OEM variants.
 *
 * @param[in]   N/A
 * @return      uint32_t -- Count of all OEM variants in the structure
 */
uint32_t
OEMInfo_GetVarCt(void)
{
    return (uint32_t) OEMInfoCtxt.nNumOEMVariants;
}

/* =============================================================================
 *  Function : OEMInfo_GetVariant
 * ===========================================================================*/
/**
 * @brief       Getter function to retrieve OEM variant value.
 *
 * TODO: Extend to uint32_t. uint8_t supports 1-255, but some OEMs
 * said they might need thousands of variants.
 *
 * @param[in]   N/A
 * @return      Value of the unique OEM variant
 */
uint32_t
OEMInfo_GetVariant(void)
{
    if (!OEMInfoCtxt.bCtxtInit)
    {
        OEMInfoInternal_Init();
    }
    return OEMInfoCtxt.nOEMVariant;
}
