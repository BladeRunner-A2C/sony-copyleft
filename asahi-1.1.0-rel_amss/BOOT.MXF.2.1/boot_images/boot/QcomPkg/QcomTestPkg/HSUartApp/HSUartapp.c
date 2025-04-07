/** @file HSUartapp.c

  HSUART Application

             Copyright 2023 Qualcomm Technologies, Inc. All rights reserved

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/05/23   RK      Created

=============================================================================*/
#include "HSUartapp.h"
#include <Protocol/EFIHSUart.h>


/* HSUART Transfer Context */
#define TRANSFER_DIRECTION_READ  1
#define TRANSFER_DIRECTION_WRITE 0

#define DATA_SIZE 128 

static UINT8 wbuf[DATA_SIZE];
static UINT8 rbuf[DATA_SIZE];

/* Command Line Types */
 typedef enum
{
  HSUART_CORE_NUMBER,
  BAUD_RATE,
  TRANSFER_DIRECTION,
  XFER_COUNT,
  BAUD_SWITCH,
  LOOP_COUNT,
  AUTO_TESTS,
  CMD_INVALID,
} command_option;

/* Command Parameters */
typedef struct
{
  UINT16 core_instance;
  UINT32 baud_rate;
  UINT16 transfer_length;
  boolean baud_change;
  UINT16 loop_count;
  UINT32 transfer_direction;
} slave_context;

static slave_context sctxt;
boolean xfer_flag;
boolean auto_t;

unsigned int baud_table_test[] =
{
	   300,
      1200,
      2400,
      4800,
      9600,
     19200,
     38400,
     57600,
    115200,
    230400,
    460800,
    921600,
   2000000,
   3000000,
   4000000
};


slave_context *get_slave_context (UINTN argc, CHAR8 **argv);
VOID hsuart_test_hex_stream_to_buf (UINT8 *buffer, const CHAR8 *stream, UINT16 *length);
VOID hsuart_test_hex_dump (IN UINT8 *buffer, IN UINT32 length);

static void hsuart_test_cmd_help (void)
{
  /* EFI_D_ERROR will print always */

  DEBUG((EFI_D_ERROR,"\nhsuarttest v1.0\n"));

  DEBUG((EFI_D_ERROR,"Copyright (c) 2020 Qualcomm Technologies, Inc.\n"));
  DEBUG((EFI_D_ERROR,"             All Rights Reserved.\n"));
  DEBUG((EFI_D_ERROR,"     Qualcomm Confidential and Proprietary\n"));

  DEBUG((EFI_D_ERROR,"\nUsage:\n"));
  DEBUG((EFI_D_ERROR,"  start hsuarttest.efi \"[OPTIONS]\"\n"));

  DEBUG((EFI_D_ERROR,"\nDescription:\n"));
  DEBUG((EFI_D_ERROR,"  Read or Write from an HSUART slave on a particular HSUART core. If\n"));
  DEBUG((EFI_D_ERROR,"  a generic test, the maximum data that can be written or read\n"));
  DEBUG((EFI_D_ERROR,"  is limited to 256 bytes.\n"));

  DEBUG((EFI_D_ERROR,"\nOPTIONS:\n"));
  DEBUG((EFI_D_ERROR,"  -h, --help                 Print this help text\n"));
  DEBUG((EFI_D_ERROR,"  -a, --auto                 to test auto specific extended apis\n"));
  DEBUG((EFI_D_ERROR,"  -c, --core <core_num>      Core number for the enabled instance\n"));
  DEBUG((EFI_D_ERROR,"  -r, --read <length>        Length of bytes to be read\n"));
  DEBUG((EFI_D_ERROR,"  -b, --baudrate <baud>      Baudrate\n"));
  DEBUG((EFI_D_ERROR,"  -s, --baudswitch           Baudrate switch test\n"));
  DEBUG((EFI_D_ERROR,"  -w, --write <hex_stream>   Hex stream: no spaces and no 0x\n"));
  DEBUG((EFI_D_ERROR,"  -l, --loop <iterations>    Number of iterations to run the test for\n"));

  DEBUG((EFI_D_ERROR,"\nExamples:\n"));
  DEBUG((EFI_D_ERROR,"  // Write 5 bytes to HSUart for WP\n"));
  DEBUG((EFI_D_ERROR,"  start HSUartTest \"-w 0000C0FFEE\"\n\n"));
  DEBUG((EFI_D_ERROR,"  // Write 5 bytes to HSUart for AU\n"));
  DEBUG((EFI_D_ERROR,"  start HSUartTest \"-a -c 18 -b 115200 -w 0000C0FFEE\"\n\n"));
  DEBUG((EFI_D_ERROR,"  // Read 10 bytes from HSUart AU.\n"));
  DEBUG((EFI_D_ERROR,"  start HSUartTest \"-a -c 18 -b 115200 -r 10\"\n\n"));

}

slave_context *get_slave_context (UINTN argc, CHAR8 **argv)
{
  UINT32 index = 0;

  while (index < argc)
  {
    command_option CmdOp = CMD_INVALID;

    if ((AsciiStriCmp (*(argv + index), "--read") == 0)  ||
             (AsciiStriCmp (*(argv + index), "--write") == 0) ||
             (AsciiStriCmp (*(argv + index), "-r") == 0)      ||
             (AsciiStriCmp (*(argv + index), "-w") == 0))
    {
      CmdOp = TRANSFER_DIRECTION;
    }
    else if ((AsciiStriCmp (*(argv + index), "--loop") == 0) ||
             (AsciiStriCmp (*(argv + index), "-l") == 0))
    {
      CmdOp = LOOP_COUNT;
    }
	
	else if ((AsciiStriCmp (*(argv + index), "--xfer") == 0) ||
             (AsciiStriCmp (*(argv + index), "-x") == 0))
    {
      CmdOp = XFER_COUNT;
    }

    else if ((AsciiStriCmp (*(argv + index), "--core") == 0) ||
        (AsciiStriCmp (*(argv + index), "-c") == 0))
    {
      CmdOp = HSUART_CORE_NUMBER;
    }
	else if ((AsciiStriCmp (*(argv + index), "--auto") == 0) ||
        (AsciiStriCmp (*(argv + index), "-a") == 0))
    {
      CmdOp = AUTO_TESTS;
    }
    else if ((AsciiStriCmp (*(argv + index), "--baudrate") == 0) ||
        (AsciiStriCmp (*(argv + index), "-b") == 0))
    {
      CmdOp = BAUD_RATE;
    }
	else if ((AsciiStriCmp (*(argv + index), "--baudswitch") == 0) ||
        (AsciiStriCmp (*(argv + index), "-s") == 0))
    {
      CmdOp = BAUD_SWITCH;
    }

    switch (CmdOp)
    {

      case TRANSFER_DIRECTION:
        if ((AsciiStriCmp (*(argv + index), "--read") == 0) ||
            (AsciiStriCmp (*(argv + index), "-r") == 0))
        {
          sctxt.transfer_direction = TRANSFER_DIRECTION_READ;
        }
        else
        {
          sctxt.transfer_direction = TRANSFER_DIRECTION_WRITE;
        }

        index++;

        if (sctxt.transfer_direction == TRANSFER_DIRECTION_READ)
        {
          sctxt.transfer_length = (UINT16) AsciiStrDecimalToUintn (*(argv + index));
          if (sctxt.transfer_length > DATA_SIZE)
          {
            sctxt.transfer_length = DATA_SIZE;
          }
        }
        else
        {
          hsuart_test_hex_stream_to_buf (wbuf, *(argv + index), &sctxt.transfer_length);
        }
        break;
      
	  case XFER_COUNT:
		xfer_flag = TRUE;
		index++;
        sctxt.transfer_length = (UINT16) AsciiStrDecimalToUintn (*(argv + index));
		if (sctxt.transfer_length > DATA_SIZE)
        {
          sctxt.transfer_length = DATA_SIZE;
        }
        break;
		
	  case BAUD_SWITCH:
        sctxt.baud_change = TRUE;
        break;
	
	  case AUTO_TESTS:
        auto_t = TRUE;
        break;
		
      case LOOP_COUNT:
        index++;
        sctxt.loop_count = (UINT16) AsciiStrDecimalToUintn (*(argv + index));
        break;
       
      case HSUART_CORE_NUMBER:
    	  index++;
    	  sctxt.core_instance = (UINT16) AsciiStrDecimalToUintn (*(argv + index));
    	  break;

      case BAUD_RATE:
    	  index++;
          sctxt.baud_rate = (UINT32) AsciiStrDecimalToUintn(*(argv + index));
    	  break;

      case CMD_INVALID:
      default:
        DEBUG((EFI_D_ERROR,"Invalid command line option: %a\n", *(argv + index)));
        break;
    }

    if (CmdOp == CMD_INVALID)
    {
      return NULL;
    }

    index++;
  }

  return &sctxt;
}

UINT32 perform_transfers(EFI_QCOM_HSUART_PROTOCOL *HSUartIo, void *handle)
{
	UINT32 istatus = EFI_SUCCESS;
    UINT32 length_to_read = sctxt.transfer_length;
    UINT32 length_read = 0;
    UINT32 timeout = 1000;
	istatus = auto_t ? HSUartIo->write_ex(handle, wbuf, sctxt.transfer_length) : HSUartIo->write(wbuf, sctxt.transfer_length);
    if (sctxt.transfer_length != istatus)
    {
      DEBUG((EFI_D_ERROR, "UART Write Failed %d\n", (uint32) istatus));
      return -1;
    }
    else
    {
      DEBUG((EFI_D_ERROR, "Data written\n"));
      hsuart_test_hex_dump (wbuf, sctxt.transfer_length);
      istatus = 0;
    }

    do {
		  length_read = auto_t ? HSUartIo->read_ex(handle, rbuf + istatus, length_to_read) : HSUartIo->read(rbuf + istatus, length_to_read);
          if(length_read == 0)
            busywait(10000); // 10ms delay 
          length_to_read -= length_read;
          istatus += length_read;
          timeout--;
    }while(length_to_read && timeout);
    if(timeout <= 0)
    {
		DEBUG((EFI_D_ERROR, "Read timed out\n"));
    }
    /*istatus = HSUartIo->read(handle, rbuf, sctxt.transfer_length);*/
    if (sctxt.transfer_length != istatus)
    {
        DEBUG((EFI_D_ERROR, "Generic Read Failed, transfer_length:%d status:%d\n", sctxt.transfer_length, istatus));
        hsuart_test_hex_dump (rbuf, sctxt.transfer_length);
        return -1;
    }
    else
    {
		if(memcmp(wbuf, rbuf, sctxt.transfer_length) != 0) {
			DEBUG((EFI_D_ERROR, "Data missmatched\n"));
			hsuart_test_hex_dump (rbuf, sctxt.transfer_length);
			return -1;
		} else {
			istatus = EFI_SUCCESS;
			DEBUG((EFI_D_ERROR, "Data read\n"));
			hsuart_test_hex_dump (rbuf, sctxt.transfer_length);
		}
    }
	return istatus;
}

UINT32 hsuart_test_slave(slave_context * cntxt)
{
  UINT32 istatus;
  UINT32    i                = 0;
  UINT32 baud_table_size = sizeof(baud_table_test)/sizeof(baud_table_test[0]);
  EFI_QCOM_HSUART_PROTOCOL *HSUartIo = NULL;
  void * hsuart_handle = NULL;
  hsuart_open_config config;

 istatus = gBS->LocateProtocol(&gQcomHSUartProtocolGuid, NULL, (VOID **) &HSUartIo);
 if (EFI_SUCCESS != istatus)
 {
   DEBUG((EFI_D_ERROR, "HSUartTest Protocol not found %d\n", istatus));
   TestStatus("HSUartTest",istatus);
   TEST_STOP("HSUartTest");
   return istatus;
 }
   DEBUG((EFI_D_ERROR, "HSUartTest Protocol found %d\n", istatus));
 if (NULL == HSUartIo)
 {
   DEBUG((EFI_D_ERROR, "HSUartTest Io NULL\n"));
   TestStatus("HSUartTest",EFI_DEVICE_ERROR);
   TEST_STOP("HSUartTest");
   return (UINT32)EFI_DEVICE_ERROR;
 }

 //Fill the config
 DEBUG((EFI_D_ERROR, "HSUartTest before filling configL\n"));
 config.baud_rate = cntxt->baud_rate;

 config.bits_per_char = HSUART_8_BITS_PER_CHAR ;
 config.enable_loopback = 1;
 config.num_stop_bits = HSUART_1_0_STOP_BITS;
 config.parity_mode =  HSUART_NO_PARITY;
 config.tx_cb_isr = NULL;
 config.rx_cb_isr = NULL;

 if(auto_t)
	DEBUG((EFI_D_ERROR, "HSUartTest config baud:%d core:%d before open\n",config.baud_rate, cntxt->core_instance ));
   //DEBUG((EFI_D_ERROR, "HSUartTest Io not NULL\n"));
  /* Initialize the HSUart Core */
  istatus = auto_t ? HSUartIo->open_ex(cntxt->core_instance, &config, &hsuart_handle ) : HSUartIo->open();
    DEBUG((EFI_D_ERROR, "Open status to initialize HSUart %d\n", istatus));
  if (EFI_SUCCESS != istatus)
  {
    DEBUG((EFI_D_ERROR, "Failed to initialize HSUart %d\n", istatus));
    goto error;
  }
  
  /* Initialize Buffers */
  for (i = 0; i < DATA_SIZE; i++)
  {
    rbuf[i] = 0;
  }
  
  if(xfer_flag)
	for(i = 0; i < sctxt.transfer_length; i++)
	{
		wbuf[i] = i&0xffff;
	}

  if (sctxt.loop_count == 0)
  {
    sctxt.loop_count = 1;
  }

  for (i = 0; i < sctxt.loop_count; i++)
  {
	DEBUG((EFI_D_ERROR, "Running iteration : %d\n", i + 1));
	if (sctxt.transfer_direction == TRANSFER_DIRECTION_READ)
    {
      istatus = auto_t ? HSUartIo->read_ex(hsuart_handle, rbuf, sctxt.transfer_length) : HSUartIo->read(rbuf, sctxt.transfer_length);
      if (sctxt.transfer_length != istatus)
      {
        DEBUG((EFI_D_ERROR, "Generic Read Failed %d transfer_length status %d %d\n", (uint32) istatus, sctxt.transfer_length, istatus));
        hsuart_test_hex_dump (rbuf, sctxt.transfer_length);
        istatus = 1;
        goto error;
      }
      else
      {
        DEBUG((EFI_D_ERROR, "Data read\n"));
        hsuart_test_hex_dump (rbuf, sctxt.transfer_length);
        istatus = EFI_SUCCESS;
      }
    }
    else
    {
      /* Loopback enabled */
      if(sctxt.baud_change) 
	  {
	  	for(int j = 0; j < baud_table_size; j++)
	  	{
			DEBUG((EFI_D_ERROR, " set_baud rate to : %d \n",baud_table_test[j]));
            sctxt.baud_rate = baud_table_test[j];
			istatus = auto_t ? HSUartIo->set_baudrate_ex(hsuart_handle, sctxt.baud_rate) : HSUartIo->set_baudrate(sctxt.baud_rate);
			if (EFI_SUCCESS != istatus)
  			{
    			DEBUG((EFI_D_ERROR, "Failed to change baudrate, status: %d\n", istatus));
    			goto error;
  			}
			istatus = perform_transfers(HSUartIo, hsuart_handle);
			if(EFI_SUCCESS != istatus)
				goto error;
	  	}
	  } 
	  else
	  {
	  	istatus = perform_transfers(HSUartIo, hsuart_handle);
		if(EFI_SUCCESS != istatus)
			goto error;
	  }
    }
  }

error:
DEBUG((EFI_D_ERROR, "closing to DeInitialize HSUart %d\n", istatus));

  if (EFI_SUCCESS != (auto_t ? HSUartIo->close_ex(hsuart_handle) : HSUartIo->close()))
  {
    DEBUG((EFI_D_ERROR, "Failed to DeInitialize HSUart %d\n", istatus));
  }

  return istatus;
}


UINT32 hsuart_test_generic(UINTN argc, CHAR8 **argv)
{
  UINT32 istatus = 1;


  if ((argc > 0) && ((AsciiStriCmp (*argv, "--help") == 0) ||
      (AsciiStriCmp (*argv, "-h")     == 0)))
  {
    hsuart_test_cmd_help ();
  }
  else if (NULL != get_slave_context (argc, argv))
  {
   
    istatus = hsuart_test_slave(&sctxt);
  }
  else
  {
    DEBUG((EFI_D_ERROR, "Invalid Command Line options. Available Options are:\n"));
    hsuart_test_cmd_help ();
  }

  return istatus;
}

VOID hsuart_test_hex_dump (IN UINT8 *buffer, IN UINT32 length)
{
  UINT32 i = 0;

  DEBUG((EFI_D_ERROR, "\n"));
  for (i = 0; i < length && i < DATA_SIZE; i++)
  {
    if (!(i & 7))
    {
      DEBUG((EFI_D_ERROR, "\n"));
    }
    DEBUG((EFI_D_ERROR, "%02x ", buffer[i]));
  }
  DEBUG((EFI_D_ERROR, "\n\n"));
}

VOID hsuart_test_hex_stream_to_buf (UINT8 *buffer, const CHAR8 *stream, UINT16 *length)
{
  UINT16 i = 0;
  CHAR8 hex_chars[5];

  *length = AsciiStrLen (stream) >> 1;
  if (*length > DATA_SIZE)
  {
    *length = DATA_SIZE;
  }
  hex_chars[0] = '0';
  hex_chars[1] = 'x';
  hex_chars[4] = '\0';

  for (i = 0; i < *length; i++)
  {
    hex_chars[2] = *(stream + (i << 1));
    hex_chars[3] = *(stream + (i << 1) + 1);
    buffer[i] = (UINT8) AsciiStrHexToUintn(hex_chars);
  }
}

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

 **/
EFI_STATUS
EFIAPI HSUARTTestMain (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  UINTN  argc;
  CHAR8  **argv = NULL;

  EFI_STATUS  status = EFI_DEVICE_ERROR;
  UINT32 istatus = 1;

  TEST_START("HSUART Test");

  status = GetCmdLineArgs (ImageHandle, &argc, &argv);
  if (status != EFI_SUCCESS)
  {
    goto error;
  }

  istatus = hsuart_test_generic (argc, argv);

error:

  if (istatus != EFI_SUCCESS)
  {
     status = EFI_DEVICE_ERROR;
  }

  TestStatus("HSUART TEST", status);
  TEST_STOP ("HSUART Test");

  return status;
}
