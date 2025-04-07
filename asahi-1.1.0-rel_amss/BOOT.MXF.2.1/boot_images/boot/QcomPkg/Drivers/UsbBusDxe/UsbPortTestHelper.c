/** @file

  QCOM_USB_PORT_TEST_PROTOCOL implementation.

  Copyright (c) 2011, 2014, 2017-2022 Qualcomm Technologies, Inc. All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY

 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 04/20/21   sriramd  Updatd to support the info from connected devices
 02/01/17   pm       Port form Boot.xf.1.4
 02/05/14   amitg    Async USB Host Stack
 06/13/13   mliss    Updates to support multiple instances (1 per UsbBus).
 11/02/11   wufan    Initial implementation.
=============================================================================*/

//
// Includes
//
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EFIUsbPortTestHelper.h>
#include <Protocol/EFIUsbDevice.h>         /* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
#include "UsbBus.h"
#include "UsbDesc.h"
#include "UsbPortTestHelper.h"


#define _DBG(EfiD, Expression, ...)	DEBUG((EfiD, Expression, ##__VA_ARGS__))
#define DBG(EfiD, Str, ...) \
  _DBG(EfiD, "%a: " Str "\n", __FUNCTION__, ##__VA_ARGS__)


// Forward declarations
EFI_STATUS
UsbPortTestHelperGetDevInfo (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL    *This,
  OUT UINT8                                 *DeviceNumber,
  OUT UINT8                                 *ParentPort
  );

EFI_STATUS
UsbPortTestHelperGetDevDesc (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL        *This
  );


/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
EFI_STATUS
UsbPortTestHelperFindDevice (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT QCOM_USB_PORT_TEST_GET_CHILD_DATA   *GetChildData
  );

/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
EFI_STATUS
UsbPortTestHelperListConnectDevice (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT QUSB_USB_PORT_TEST_HELPER_LIST_DEVICE_TYPE **UsbDeviceList,
  OUT UINT32                               *NumDevice
  );

// Protocol template
STATIC QCOM_USB_PORT_TEST_HELPER_PROTOCOL gUsbPortTestHelperTemplate = {
  EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2,
  UsbPortTestHelperGetDevInfo,
  UsbPortTestHelperGetDevDesc,
  UsbPortTestHelperFindDevice,         /* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
  UsbPortTestHelperListConnectDevice,  /* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
};

/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
EFI_STATUS
ListChildDevice (
  IN  USB_DEVICE                          *Device,
  OUT QCOM_USB_PORT_TEST_GET_CHILD_DATA   *GetChildData
  )
{
  USB_BUS                     *Bus;
  USB_DEVICE                  *Child = NULL;
  EFI_STATUS                  Status = EFI_SUCCESS;
  UINTN                       Index;
  UINT8                       Index_c = 0;
  UINT8                       Index_i = 0;
  UINT8                       InterfaceClass = 0;
  EFI_USB_STRING_DESCRIPTOR   *StrDesc      = NULL;
  UINT32                      StrIndex      = 0;
  UINT32                      StrIterIndex  = 0;
  UINT32                      DataIndex     = 0;
 
  // Even if there is no device, return success. TotalChildCount will keep track of child devices.
  if (Device->Bus == NULL)
      return EFI_SUCCESS;

  Bus = Device->Bus;

  // check for all the devices except the root hub port.
  for (Index = 1; Index < Bus->MaxDevices; Index++) {
    if(Bus->Devices[Index] == NULL)
      break;
    //check for all the child devices currently connected.
    Child = Bus->Devices[Index];
    //if the bus is not immidiate parent of the child device, skip it. child device will be taken care by the parent itself.
    if ((Child->ParentAddr != Device->Address))
     continue;

    if (Child->DevDesc && (GetChildData->TotalChildCount < MAX_CHILD_DEVICES)) {
      // print vid pid
      GetChildData->VidPid[GetChildData->TotalChildCount] = ((Child->DevDesc->Desc.IdVendor) << 16 | (Child->DevDesc->Desc.IdProduct));
      // print string descriptor
      for (StrIndex = 1; StrIndex < 4; StrIndex++) {
        StrDesc = UsbGetOneString (Child, StrIndex, 0x409 /* English (US) */, FALSE, NULL);
        if (StrDesc) {
          for (StrIterIndex = 0; StrIterIndex < (UINT8)*((UINT8*)StrDesc); StrIterIndex+=2) {
            GetChildData->DataSize[GetChildData->TotalChildCount]++;
            GetChildData->Data[DataIndex++] = (UINT8)*((UINT8*)StrDesc + StrIterIndex);
          }
          GetChildData->DataSize[GetChildData->TotalChildCount]++;
          GetChildData->Data[DataIndex++] = (UINT8)*" ";
          FreePool (StrDesc);
        }
      }

      GetChildData->TotalChildCount++;

      for (Index_c = 0; Index_c < Child->DevDesc->Desc.NumConfigurations && Child->DevDesc->Configs[Index_c]; Index_c++) {
        for (Index_i = 0; Index_i < Child->DevDesc->Configs[Index_c]->Desc.NumInterfaces; Index_i++) {
          if (Child->DevDesc->Configs[Index_c]->Interfaces[Index_i] && Child->DevDesc->Configs[Index_c]->Interfaces[Index_i]->Settings[0]) {
            InterfaceClass = Child->DevDesc->Configs[Index_c]->Interfaces[Index_i]->Settings[0]->Desc.InterfaceClass;
            if (InterfaceClass == USB_HUB_CLASS_CODE) {
              Status = ListChildDevice (Child, GetChildData);
            }
          }
        }
      }
    } else if (GetChildData->TotalChildCount >= MAX_CHILD_DEVICES) {
		DBG (EFI_D_ERROR, "ListChildDevice: More than 20 devices connected to bus\n");
		return EFI_SUCCESS;
	}
	
  }
  return Status;
}

/**
  Find the first USB device in root hub.

  @param Bus            USB BUS
  @param DeviceNumber   the device number
  @param ParentPort     parent port number for the device

  @retval EFI_SUCCESS        success
  @retval EFI_DEVICE_ERROR   no device in root hub

**/
static
EFI_STATUS
FindUsbDevice (
  IN  USB_BUS  *Bus,
  OUT UINT8    *DeviceNumber,
  OUT UINT8    *ParentPort
  )
{
  USB_DEVICE   *dev;
  UINTN        i;

  if (Bus == NULL || DeviceNumber == NULL || ParentPort == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  for ( i = 1; i< Bus->MaxDevices; i++ ) {
    dev = Bus->Devices[i];

    if ((NULL != dev) && (0 != dev->Address) && (0 == dev->ParentAddr)) {
      *DeviceNumber = i;
      *ParentPort = dev->ParentPort;
      return EFI_SUCCESS;
    }
  }

  DBG(EFI_D_ERROR, "can't find any device in root hub");
  return EFI_DEVICE_ERROR;
}


/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
EFI_STATUS
UsbPortTestHelperListConnectDevice (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT QUSB_USB_PORT_TEST_HELPER_LIST_DEVICE_TYPE **UsbDeviceList,
  OUT UINT32                               *NumDevice
  )
{
  USB_DEVICE   *dev;
  QCOM_USB_PORT_TEST_HELPER_PRIVATE   *Priv;
  UINTN        i;
  UINTN        found_idx =0;
  UINTN        StrIndex, StrIterIndex;
  EFI_USB_STRING_DESCRIPTOR   *StrDesc      = NULL;
  UINTN        string_size =0;
  QUSB_USB_PORT_TEST_HELPER_LIST_DEVICE_TYPE* DeviceList;

  if (This == NULL || UsbDeviceList == NULL || NumDevice == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Priv = PORT_TEST_HELPER_FROM_THIS(This);
  DBG(EFI_D_INFO, "FindUsbDevice, max %d", Priv->UsbBus->MaxDevices);

  // allocate private structure containing protocol instance
  DeviceList = AllocateZeroPool (sizeof(QUSB_USB_PORT_TEST_HELPER_LIST_DEVICE_TYPE)*32);
  if (NULL == DeviceList)
  {
    DBG(EFI_D_ERROR, "allocate memory failed addr 0x%x", UsbDeviceList);    
    return EFI_OUT_OF_RESOURCES;
  }
  DBG(EFI_D_INFO, "Device list addr addr 0x%x", DeviceList);    
  
  for ( i = 1; i< Priv->UsbBus->MaxDevices; i++ ) {
    dev = Priv->UsbBus->Devices[i];
    if ((NULL != dev) && (0 != dev->Address) && (0 == dev->ParentAddr)) {
      DeviceList[found_idx].Addr = dev->Address;
      DeviceList[found_idx].Speed= dev->Speed;
      DeviceList[found_idx].Parent = dev->ParentAddr;
      DeviceList[found_idx].Pid = dev->DevDesc->Desc.IdVendor;
      DeviceList[found_idx].Vid = dev->DevDesc->Desc.IdProduct;



      // Print String Descriptor of the device
      for (StrIndex = 0; StrIndex < USB_STR_DESC_SIZE; StrIndex++)
      {
        StrDesc = UsbGetOneString (dev, StrIndex, 0x409 /* English (US) */, FALSE, NULL);
        if (StrDesc)
        {
          DEBUG (( EFI_D_ERROR, "StrDesc[%u] =  0x%X, size (%u)", 
            StrIndex, StrDesc, StrDesc->Length));
          
          string_size = (StrDesc->Length/2) - 1;
          for (StrIterIndex = 0; StrIterIndex < (UINT8)string_size; StrIterIndex+=1)
          {
            DEBUG ((EFI_D_WARN, "%c", (UINT8)(StrDesc->String[StrIterIndex])));
          }
          DEBUG ((EFI_D_WARN, "\n"));
          //FreePool (StrDesc);
          DeviceList[found_idx].StrDesc[StrIndex] = StrDesc;
        }
      }

      found_idx ++;
   	  DBG(EFI_D_INFO, "device %d, addr %d, speed %d", found_idx, dev->Address, dev->Speed);
    }
  }
  DBG(EFI_D_INFO, "Found total %d device", found_idx);  
  *NumDevice = found_idx;
  *UsbDeviceList =DeviceList;
  return EFI_SUCCESS;
}


EFI_STATUS
UsbPortTestHelperGetDevInfo (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT UINT8                               *DeviceNumber,
  OUT UINT8                               *ParentPort
  )
{
  QCOM_USB_PORT_TEST_HELPER_PRIVATE   *Priv;

  if (NULL == This || NULL == DeviceNumber || NULL == ParentPort) {
    return EFI_INVALID_PARAMETER;
  }

  Priv = PORT_TEST_HELPER_FROM_THIS(This);

  return FindUsbDevice (Priv->UsbBus, DeviceNumber, ParentPort);
}


EFI_STATUS
UsbPortTestHelperGetDevDesc (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL        *This
  )
{
  UINT8      DeviceNumber, ParentPort;
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_PORT_TEST_HELPER_PRIVATE  *Priv;

  if (NULL == This) {
    DBG(EFI_D_ERROR, "invalid parameter");
	return EFI_INVALID_PARAMETER;
  }

  Priv = PORT_TEST_HELPER_FROM_THIS(This);

  if (NULL == Priv) {
    DBG(EFI_D_ERROR, "Priv cannot be NULL");
	return EFI_DEVICE_ERROR;
  }

  Status = FindUsbDevice (Priv->UsbBus, &DeviceNumber, &ParentPort);

  if (EFI_ERROR (Status)) {
    DBG (EFI_D_ERROR, "failed to find USB device: %p", Status);
    return Status;
  }

  return UsbGetDevDesc (Priv->UsbBus->Devices[DeviceNumber], FALSE, NULL);
}

/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
EFI_STATUS
UsbPortTestHelperFindDevice (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT QCOM_USB_PORT_TEST_GET_CHILD_DATA   *GetChildData
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_PORT_TEST_HELPER_PRIVATE  *Priv;

  if (NULL == This) {
    DBG(EFI_D_ERROR, "invalid parameter");
	return EFI_INVALID_PARAMETER;
  }

  Priv = PORT_TEST_HELPER_FROM_THIS(This);

  if (NULL == Priv) {
    DBG(EFI_D_ERROR, "Priv cannot be NULL");
	return EFI_DEVICE_ERROR;
  }

  //find all the devices connected to the root port
  Status = ListChildDevice(Priv->UsbBus->Devices[0], GetChildData);
  if (EFI_ERROR (Status))
    DBG (EFI_D_ERROR, "failed to find USB device: %p", Status);

  return Status;
}

EFI_STATUS
UsbPortTestHelperBuildProtocol (
  IN  USB_BUS                             *UsbBus,
  OUT QCOM_USB_PORT_TEST_HELPER_PROTOCOL  **PortTestHelper
  )
{
  QCOM_USB_PORT_TEST_HELPER_PRIVATE   *PortTestPrivate;

  if (NULL == UsbBus || NULL == PortTestHelper) {
    return EFI_INVALID_PARAMETER;
  }

  // allocate private structure containing protocol instance
  PortTestPrivate = AllocateZeroPool (sizeof(QCOM_USB_PORT_TEST_HELPER_PRIVATE));

  if (NULL == PortTestPrivate) {
    DBG (EFI_D_ERROR, "Failed to allocate PortTestHelper private data");
    return EFI_OUT_OF_RESOURCES;
  }

  // initialize private data
  PortTestPrivate->Signature = USB_PORT_TEST_HELPER_SIGNATURE;
  PortTestPrivate->UsbBus = UsbBus;
  CopyMem(&PortTestPrivate->PortTestHelper, &gUsbPortTestHelperTemplate, sizeof(QCOM_USB_PORT_TEST_HELPER_PROTOCOL));

  // return protocol pointer
  *PortTestHelper = &PortTestPrivate->PortTestHelper;

  return EFI_SUCCESS;
}


