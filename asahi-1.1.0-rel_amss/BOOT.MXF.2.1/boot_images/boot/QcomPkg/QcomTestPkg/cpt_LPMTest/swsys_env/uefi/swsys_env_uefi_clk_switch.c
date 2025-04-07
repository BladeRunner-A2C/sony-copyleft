/*
===========================================================================
*/
/**
  @file swsys_env_uefi_clk_switch.c

*/
/*
  ===================================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Technologies Proprietary and Confidential.
  ===================================================================================
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  01/11/19   ly      Initial revision.

  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include <api/systemdrivers/icbarb.h>
#include <api/systemdrivers/busywait.h>
#include <npa_resource.h>
#include <ClockDefs.h>
#include "swsys_env_uefi_clk_switch.h"
#include "../swsys_logger/swsys_logger.h"
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SerialPortShLib.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFIDDRGetConfig.h>
#include <Protocol/EFIHWIO.h>
#include <Protocol/EFIQcomEnv.h>
#include "target/target.h"

#include "swsys_env_uefi.h"

/*=========================================================================
      Variables
==========================================================================*/
npa_client_handle reqClientDDR = NULL;
npa_client_handle reqClientshub = NULL;
EFI_NPA_PROTOCOL *EnvNpaProtocol = NULL;
static EFI_CLOCK_PROTOCOL *EfiClockProtocol = NULL;
static EFI_DDRGETINFO_PROTOCOL *DDRINFOProtocol = NULL;
static EFI_HWIO_PROTOCOL        *HWIOProtocol = NULL;
ddr_freq_plan_entry          *pDDRFreqTbl = NULL;
shub_freq_plan_entry        *pSHUBFreqTbl = NULL;
static volatile void* mccc_mstr_base = NULL;

static swsys_ddrinfo_t ddr_info = {0, 0, 0, 0};

ICBArb_MasterSlaveType ddrMasterSlave[] =
    {{ICBID_MASTER_APPSS_PROC, ICBID_SLAVE_EBI1}};

ICBArb_MasterSlaveType shubMasterSlave[] =
    {{ICBID_MASTER_APPSS_PROC, ICBID_SLAVE_LLCC}};

freq_info ddr_freq_info, shub_freq_info;
key_val* freq_table = NULL;
uint32_t freq_table_size = 0;

ICBArb_RequestType uefi_Quest_request[2] =
{
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 =
    {
      .uIb = 1,                 /**< Instantaneous bandwidth in Bytes/second */
      .uAb = 1,                 /**< Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0           /**< Latency requirement in nanoseconds */
    }
  },
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 =
    {
      .uIb = 1,                 /**< Instantaneous bandwidth in Bytes/second */
      .uAb = 1,                 /**< Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0           /**< Latency requirement in nanoseconds */
    }
  }
};

npa_client_handle reqClientQuestUART = NULL;
ICBArb_MasterSlaveType uartMasterSlave[] =
    {{ICBID_MASTER_QUP_0, ICBID_SLAVE_EBI1},
     {ICBID_MASTER_QUP_CORE_0, ICBID_SLAVE_QUP_CORE_0}};

npa_client_handle reqClientQuestClock = NULL;
ICBArb_MasterSlaveType clockMasterSlave[] =
    {{ICBID_MASTER_APPSS_PROC, ICBID_SLAVE_CLK_CTL}};
void init_ddr_info(){
	ddr_freq_info = GetDDRFreqInfo();
	freq_table = ddr_freq_info.freq_table;
	freq_table_size = ddr_freq_info.freq_table_size;		
}
void init_shub_info(){
	shub_freq_info = GetSHUBFreqInfo();
	freq_table = shub_freq_info.freq_table;
	freq_table_size = shub_freq_info.freq_table_size;		
}

/**
  Vote for Quest 
**/
void swsys_vote_for_quest(void)
{
  if (reqClientQuestUART == NULL)
  {
    // Init the npa request nodes for UART
    reqClientQuestUART = swsys_npa_request_node("Quest uart req client",
                                                sizeof(uartMasterSlave),
                                                &uartMasterSlave);
  }

  swsys_npa_issue_vector_request(reqClientQuestUART,
                           sizeof(uefi_Quest_request) / (sizeof(npa_resource_state)),
                           (npa_resource_state *)uefi_Quest_request);

  if (reqClientQuestClock == NULL)
  {
    reqClientQuestClock = swsys_npa_request_node("Quest clock req client",
                                                 sizeof(clockMasterSlave),
                                                 &clockMasterSlave);
  }

  swsys_npa_issue_vector_request(reqClientQuestClock,
                           sizeof(uefi_Quest_request[0]) / (sizeof(npa_resource_state)),
                           (npa_resource_state *)uefi_Quest_request);

}

void swsys_remove_vote_for_quest(void)
{
  swsys_npa_destroy_node(reqClientQuestUART);
  swsys_npa_destroy_node(reqClientQuestClock);
}

/* =========================================================================
**  Functions
** =========================================================================*/

/*
   Function: Get NPA protocol
*/
EFI_STATUS swsys_npa_init(void)
{
  EFI_STATUS Status = EFI_SUCCESS;
  if (!EnvNpaProtocol) {
  Status = gBS->LocateProtocol(&gEfiNpaProtocolGuid, NULL, (void**)&EnvNpaProtocol);
  if (EFI_ERROR(Status))
  {
    swsys_error("Cannot locate NPA protocol\n");
    return EFI_NOT_FOUND;
  }
  else
  {
    swsys_debug("EnvNpaProtocol handle created successfully\n");
  }
  }

  return Status;
}

/*
   Function: Create NPA request handle
*/
npa_client_handle swsys_npa_request_node(const char *client_name, unsigned int client_value, void *client_ref)
{
  EFI_STATUS Status = EFI_SUCCESS;
  npa_client_handle reqClientLocal = NULL;
  if (!EnvNpaProtocol) {
    swsys_debug("Init NPA\n");
    Status = swsys_npa_init();
    if (EFI_ERROR(Status)) {
      swsys_error("NPA protocol not found\n");
      return NULL;
    }else{
      swsys_debug("NPA init done\n");
    }
  }
  Status = EnvNpaProtocol->CreateSyncClientEx("/icb/arbiter", client_name, NPA_CLIENT_SUPPRESSIBLE_VECTOR, client_value, client_ref, &reqClientLocal);
  if (EFI_ERROR(Status))
  {
    swsys_error("EFI_NPA_CREATE_SYNC_CLIENT_EX failed with status: %r\r\n", Status);
  }
  else
  {
    swsys_debug("EFI_NPA_CREATE_SYNC_CLIENT_EX SUCCESS \r\n");
  }

  return reqClientLocal;
}

/*
   Function: Destroy created NPA node
*/
void swsys_npa_destroy_node(npa_client_handle client)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (!EnvNpaProtocol) {
    swsys_debug("Init NPA\n");
    Status = swsys_npa_init();
    if (EFI_ERROR(Status)) {
      swsys_error("NPA protocol not found\n");
      return;
    }else{
      swsys_debug("NPA init done\n");
    }
  }

  Status = EnvNpaProtocol->DestroyClient(client);
  if (EFI_ERROR(Status))
  {
    swsys_error("EFI_NPA_DESTROY_CLIENT failed with status: %r\r\n", Status);
  }
  else
  {
    swsys_debug("EFI_NPA_DESTROY_CLIENT SUCCESS \r\n");
  }
}

/*
   Function: issue NPA vector request
*/
void swsys_npa_issue_vector_request(npa_client_handle client, unsigned int num_elems, npa_resource_state *vector)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (!EnvNpaProtocol) {
    swsys_debug("Init NPA\n");
    Status = swsys_npa_init();
    if (EFI_ERROR(Status)) {
      swsys_error("NPA protocol not found\n");
      return;
    }else{
      swsys_debug("NPA init done\n");
    }
  }
  Status = EnvNpaProtocol->IssueVectorRequest(client, num_elems, vector);
  if (EFI_ERROR(Status))
  {
    swsys_error("EFI_NPA_ISSUE_VECTOR_REQUEST  failed with status: %r\r\n", Status);
  }
  else
  {
    swsys_debug("EFI_NPA_ISSUE_VECTOR_REQUEST  SUCCESS \r\n");
  }
}

/*
   Function: Set DDR low band width vote EnvProtocol
 */

EFI_STATUS swsys_ddr_setlowbandwidth(void)
{
  EFI_STATUS Status;
  EFI_QCOMENV_PROTOCOL  *EnvProtocol = NULL;    
    
  Status = gBS->LocateProtocol(&gEfiQcomEnvProtocolGuid, NULL, (void**)&EnvProtocol);
  if(Status == EFI_SUCCESS)
  {
    if (EFI_SUCCESS != (Status = EnvProtocol->SetDdrThroughputLow(EnvProtocol)))
    {
      swsys_error("SetDdrThroughLow failed with status: %r\r\n", Status);
    }
    else
    {
      swsys_debug("SetDdrThroughLow SUCCESS \r\n");
    }
  }
  return Status;
}

//This is to set DDR to nominal freq
EFI_STATUS swsys_ddr_setnominalbandwidth(void)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (!DDRINFOProtocol) {
    Status = gBS->LocateProtocol(&gEfiDDRGetInfoProtocolGuid, NULL, (void**)&DDRINFOProtocol);
    if(Status != EFI_SUCCESS){
	return EFI_PROTOCOL_ERROR;
  } else {
	swsys_debug("Locate DDRINFOProtocol SUCCESS \r\n");
    }
  }

  //DDRINFOProtocol present
  if (EFI_SUCCESS != (Status = DDRINFOProtocol->SetMaxNominalDDRFreq(DDRINFOProtocol)))	{
    swsys_error("SetMaxNominalDDRFreq failed with status: %r\r\n", Status);
  }else{
    swsys_debug("SetMaxNominalDDRFreq SUCCESS \r\n");
  }

  return Status;
}

uint64_t MB = 1000000;
uint64_t search_freq_band(uint32_t freq_khz, uint32_t* set_freq_khz)
{
  uint8_t i;
  uint8_t freq_band_size = freq_table_size;

  for (i = 0; i < freq_band_size; i++)
  {
    if (freq_khz <= freq_table[i].key)
    {
      *set_freq_khz = freq_table[i].key;
      return freq_table[i].val * MB;
    }
  }

  swsys_error("could not find a matching bandwidth entry for %d. Returning %d\n", freq_khz, freq_table[freq_band_size - 1].key);
  *set_freq_khz = freq_table[freq_band_size - 1].key;
  return freq_table[freq_band_size - 1].val * MB;
}

uint64_t search_shub_freq_band(uint32_t freq_khz, uint32_t* set_freq_khz)
{
  uint8_t i;
  uint8_t freq_band_size = freq_table_size;

  for (i = 0; i < freq_band_size; i++)
  {
    if (freq_khz <= freq_table[i].key)
    {
      *set_freq_khz = freq_table[i].key;
      return freq_table[i].val * MB;
    }
  }

  swsys_error("could not find a matching bandwidth entry for %d. Returning %d\n", freq_khz, freq_table[freq_band_size - 1].key);
  *set_freq_khz = freq_table[freq_band_size - 1].key;
  return freq_table[freq_band_size - 1].val * MB;
}

uint32_t swsys_get_DDR_type(void)
{
  ddr_details_entry DDRDetails;
  //EFI_STATUS Status;
  uint32_t uDDRType = 0;

  if (DDRINFOProtocol) {
    DDRINFOProtocol->GetDDRDetails(DDRINFOProtocol, &DDRDetails);
    if (DDRDetails.device_type == DDR_TYPE_LPDDR1)
    {
         uDDRType = 1;
    }
    else if ((DDRDetails.device_type == DDR_TYPE_LPDDR2) ||
             (DDRDetails.device_type == DDR_TYPE_PCDDR2))
    {
         uDDRType = 2;
    }
    else if ((DDRDetails.device_type == DDR_TYPE_LPDDR3) ||
             (DDRDetails.device_type == DDR_TYPE_PCDDR3))
    {
        uDDRType = 3;
    }
    else if ((DDRDetails.device_type == DDR_TYPE_LPDDR4) ||
             (DDRDetails.device_type == DDR_TYPE_LPDDR4X))
    {
        uDDRType = 4;
    }
    else if ((DDRDetails.device_type == DDR_TYPE_LPDDR5) ||
             (DDRDetails.device_type == DDR_TYPE_LPDDR5X))
    {
        uDDRType = 5;
    }
  }else{
    swsys_error("DDRInfoProtocol not available\n"); 
    uDDRType = 0;
  }
  return uDDRType;
}

void swsys_get_DDR_info(swsys_ddrinfo_t *ddr_info)
{
  ddr_details_entry DDRDetails;
  uint8_t i, j;
  EFI_STATUS Status;

  if (!DDRINFOProtocol) {
    Status = gBS->LocateProtocol(&gEfiDDRGetInfoProtocolGuid, NULL, (void**)&DDRINFOProtocol);

    if(Status != EFI_SUCCESS){
		swsys_error("DDRInfoProtocol not available\n"); 
		return;
	}
  }

  swsys_debug("Locate DDRInfoProtocol\n");
  Status = DDRINFOProtocol->GetDDRDetails(DDRINFOProtocol, &DDRDetails);
  if (Status == EFI_SUCCESS) {
	  if (DDRDetails.device_type == DDR_TYPE_LPDDR1){
		  ddr_info->Type = 1;
	  }
	  else if ((DDRDetails.device_type == DDR_TYPE_LPDDR2) ||
			   (DDRDetails.device_type == DDR_TYPE_PCDDR2)){
		  ddr_info->Type = 2;
	  }
	  else if ((DDRDetails.device_type == DDR_TYPE_LPDDR3) ||
			   (DDRDetails.device_type == DDR_TYPE_PCDDR3)){
		  ddr_info->Type = 3;
	  }
	  else if ((DDRDetails.device_type == DDR_TYPE_LPDDR4) ||
			   (DDRDetails.device_type == DDR_TYPE_LPDDR4X)){
		  ddr_info->Type = 4;
	  }else if ((DDRDetails.device_type == DDR_TYPE_LPDDR5) ||
				(DDRDetails.device_type == DDR_TYPE_LPDDR5X)){
		  ddr_info->Type = 5;
	  }else{
		  ddr_info->Type = 0; 
	  }
	  ddr_info->Manufacturer = DDRDetails.manufacturer_id;
	  ddr_info->NumChannels = DDRDetails.num_channels;
    for (j = 0; j < 2; j++)  //j is num of ranks - 2
    {
      for (i = 0; i < ddr_info->NumChannels; i++)
      {
        if (DDRDetails.ddr_params[i].density[j] == 0)
          ddr_info->Density += 2;         //2Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 1)
          ddr_info->Density += 3;         //3Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 2)
          ddr_info->Density += 4;         //4Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 3)
          ddr_info->Density += 6;         //6Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 4)
          ddr_info->Density += 8;         //8Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 5)
          ddr_info->Density += 12;         //12Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 6)
          ddr_info->Density += 16;         //16Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 7)
          ddr_info->Density += 24;         //24Gigabits
        else if (DDRDetails.ddr_params[i].density[j] == 8)
          ddr_info->Density += 32;         //32Gigabits
        else
          ddr_info->Density += 0;    //reserved memory
      }
      ddr_info->Density = ddr_info->Density << 7;  //convert from Gigabits to MB
      swsys_info("[DDR INFO]: Rank %d Size: %d MB\n", j , ddr_info->Density);
      ddr_info->Density = 0;  //restart the calculation for rank 1
    }

  } else {
    swsys_error("Failed to get detailed DDR info\n");
  }
  return;
}

void * swsys_get_MCCC_MSTR_base(void)
{
  EFI_STATUS Status;
  void* addr = NULL;

  //Locate HWIOProtocol
  if(!HWIOProtocol){
     Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&HWIOProtocol);
     if (Status != EFI_SUCCESS) {
       swsys_error("Failed to locate HWIOProtocol\n");
       return NULL; 
     }
  }
  Status = HWIOProtocol->MapRegion(HWIOProtocol, "+MCCC_MCCC_MSTR", (UINT8**)&addr);
  if(Status == EFI_SUCCESS){
     swsys_debug("MCCC_MCCC_MSTR base is 0x%lx\n",addr);
     return addr;
  }
  else{
     swsys_error("Failed to map MCCC_MCCC_MSTR region\n"); 
     return NULL;
  }
}

void * swsys_map_hw_block(char* hw_block_name)
{
  EFI_STATUS Status;
  void* addr = NULL;

  //Locate HWIOProtocol
  if(!HWIOProtocol){
     Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&HWIOProtocol);
     if (Status != EFI_SUCCESS) {
       swsys_error("Failed to locate HWIOProtocol\n");
       return NULL; 
     }
  }
  Status = HWIOProtocol->MapRegion(HWIOProtocol, hw_block_name, (UINT8**)&addr);
  if(Status == EFI_SUCCESS){
     swsys_debug("%s base is 0x%lx\n",hw_block_name);
     return addr;
  }
  else{
     swsys_error("Failed to map %s region\n",hw_block_name); 
     return NULL;
  }
}

void swsys_init_ddr_clk_uefi(uint32_t init_freq_khz, uint32_t display_mode) 
{
    EFI_STATUS Status;

    swsys_debug("init ddr clk\n");

    //Init display
    swsys_init_dispctrl();

    if (display_mode != KEEP_DISPLAY_ON) {
        swsys_dispctrl_off();
    }

  //Get MCCC_MCCC_MSTR base address
  mccc_mstr_base = swsys_get_MCCC_MSTR_base();
  if (!mccc_mstr_base) {
    swsys_error("Failed to get MCCC_MSTR base address\n"); 
  }

  //Locate DDRInfoProtocol
  if (!DDRINFOProtocol) {
    Status = gBS->LocateProtocol(&gEfiDDRGetInfoProtocolGuid, NULL, (void**)&DDRINFOProtocol);

    if(Status == EFI_SUCCESS){
		swsys_debug("Locate DDRInfoProtocol\n");
        //swsys_info("DDR type is %d\n",swsys_get_DDR_type());
		swsys_get_DDR_info(&ddr_info);
		swsys_info("[DDR INFO]: Type[%d] Manufacturer[%d] NumChannels[%d]\n",ddr_info.Type,ddr_info.Manufacturer,ddr_info.NumChannels);
    }
    else{
        swsys_error("Failed to locate DDRInfoProtocol\n"); 
    }
  }

  /* Set DDR low bandwidth vote to allow DDR clk switch to all supported freqs */
  if (swsys_ddr_setlowbandwidth()!=EFI_SUCCESS) {
      swsys_error("Fail to set ddr to low bandwidth\n");
  }
  else
  {
      swsys_info("Set DDR to low bandwidth\n");
  }

  // Init the npa request nodes
  if (reqClientDDR == NULL)
  {
    Status = swsys_npa_init();
    if (Status == EFI_SUCCESS)
    {
      // init the npa request nodes
      reqClientDDR = swsys_npa_request_node("DDR QUEST req client", sizeof(ddrMasterSlave), &ddrMasterSlave);
      if (reqClientDDR == NULL)
      {
        swsys_error("Fail to init NPA request node for DDR\n");
      }
    }
  }

  //Switch to requested intial DDR clk
  swsys_switch_ddr_clk(init_freq_khz);
  swsys_debug("done init ddr clk\n");
}

void swsys_deinit_ddr_clk_uefi() 
{
  swsys_debug("deinit ddr clk\n");

  swsys_ddr_setnominalbandwidth();

  // Turn on display first so that it will vote for proper bandsidth before Quest npa client is released
  swsys_dispctrl_on();

  swsys_npa_destroy_node(reqClientDDR);
  swsys_debug("done deinit ddr clk\n");
}

/* 
   Function: Get system supported DDR freq table using DDRGetInfoProtocol
 */
uint8_t swsys_get_ddr_freq_table_uefi(uint32_t *freq_list)
{
  EFI_STATUS Status;
  uint32_t i, freq_khz;
  uint8_t valid_freq_count =0;
  uint8_t freq_enable;
 
  pDDRFreqTbl = AllocatePool (sizeof (ddr_freq_plan_entry));
  if (pDDRFreqTbl == NULL){
      swsys_error("Failed to allocate memory for DDR freq table\n");
      return 0;
  }
    
  //DDRINFOProtocol should be located in swsys_init_ddr_clk  
  if (DDRINFOProtocol) {
    if (EFI_SUCCESS != (Status = DDRINFOProtocol->GetDDRFreqTable(DDRINFOProtocol,pDDRFreqTbl)))
    {
      swsys_error("Get DDR freq table failed with status: %r\r\n", Status);
      return 0;
    }
    else{
      swsys_debug("Get DDR freq table SUCCESS, size = %d\n", pDDRFreqTbl->num_ddr_freqs);
      for (i=0; i < pDDRFreqTbl->num_ddr_freqs; i++) {
          freq_khz = pDDRFreqTbl->ddr_freq[i].freq_khz;
          freq_enable = pDDRFreqTbl->ddr_freq[i].enable;
          swsys_debug("DDR_freq[%2d] = %8d, Valid = %d\n",i,freq_khz,freq_enable);
          if (freq_enable && (freq_khz != 0)) {
              //This is a valid DDR freq supported by system
              freq_list[valid_freq_count] = freq_khz;
              valid_freq_count++;
          }
      }
      for (i=0; i < valid_freq_count; i++) {
          swsys_info("Valid DDR_freq[%2d] = %8d\n",i,freq_list[i]);
      }
      return valid_freq_count;
    }
  }
  else{
    swsys_error("DDRInfoProtocol not available\n"); 
    return 0;
  } 
}

/* 
   Function: Get system supported DDR freq table using DDRGetInfoProtocol
 */
uint32_t swsys_get_max_enabled_ddr_freq(void)
{
  EFI_STATUS Status;
  uint32_t max_ddr_enabled_freq;
 
  //DDRINFOProtocol should be located in swsys_init_ddr_clk  
  if (DDRINFOProtocol) {
    if (EFI_SUCCESS != (Status = DDRINFOProtocol->GetDDRMaxEnabledFreq(DDRINFOProtocol,&max_ddr_enabled_freq)))
    {
      swsys_error("Get max enabled DDR freq failed: %r\r\n", Status);
      return 0;
    }
    else{
      swsys_debug("Max enabled DDR freq = %d\n", max_ddr_enabled_freq);
      return max_ddr_enabled_freq;
    }
  }
  else{
    swsys_error("DDRInfoProtocol not available\n"); 
    return 0;
  } 
}

uint32_t swsys_switch_ddr_clk_uefi(uint32_t freq_khz)
{
  EFI_STATUS Status = EFI_SUCCESS;
  uint32_t set_freq_khz = 0;
  swsys_debug("switch ddr clk\n");
  ICBArb_RequestType aRequest[1];
  ICBArb_Request2Type type2;
  aRequest[0].arbType = ICBARB_REQUEST_TYPE_2;
  type2.uUsagePercentage = 100;
  type2.uLatencyNs = 0;

  type2.uThroughPut = search_freq_band(freq_khz, &set_freq_khz);
  swsys_debug("voting bandwidth: 0x%08x%08x\n", type2.uThroughPut >> 32, type2.uThroughPut & 0xFFFFFFFF);

  aRequest[0].arbData = (ICBArb_RequestUnionType)type2;

  Status = swsys_npa_init();
  if (Status == EFI_SUCCESS)
  {
    swsys_npa_issue_vector_request(reqClientDDR, sizeof(aRequest) / (sizeof(npa_resource_state)),
                                   (npa_resource_state *)aRequest);
    
  }
  //npa_issue_vector_request(reqClientDDR,
  //                         sizeof(aRequest) / (sizeof(npa_resource_state)),
  //                         (npa_resource_state *)aRequest);
  return set_freq_khz;
}

bool swsys_read_ddr_clk_uefi(uint32_t* freq_khz) {
  
  if (!mccc_mstr_base) {
    mccc_mstr_base = swsys_get_MCCC_MSTR_base();
    if (!mccc_mstr_base) {
      swsys_error("Fail to get MCCC_MSTR base address\n");
      return 0;
    }
  }

  *freq_khz = *((uint32_t*)(mccc_mstr_base + MCCC_CLK_PERIOD_PERIOD_OFFSET));
  *freq_khz = (uint32_t) 1000000000/(*freq_khz);
  
  return true;	
}

void swsys_init_shub_clk_uefi(uint32_t init_freq_khz, uint32_t display_mode)
{
  swsys_debug("init shub clk\n");

  //Init display
  swsys_init_dispctrl();

  if (display_mode != KEEP_DISPLAY_ON) {
  swsys_dispctrl_off();
  }

  EFI_STATUS Status = EFI_SUCCESS;

  //Locate DDRInfoProtocol
  if (!DDRINFOProtocol) {
    Status = gBS->LocateProtocol(&gEfiDDRGetInfoProtocolGuid, NULL, (void**)&DDRINFOProtocol);

    if(Status == EFI_SUCCESS){
		swsys_debug("Locate DDRInfoProtocol\n");
    }
    else{
        swsys_error("Failed to locate DDRInfoProtocol\n"); 
    }
  }

  /* Set DDR low bandwidth vote to allow DDR clk switch to all supported freqs */
  if (swsys_ddr_setlowbandwidth()!=EFI_SUCCESS) {
      swsys_error("Fail to set ddr to low bandwidth\n");
  }
  else
  {
      swsys_info("Set DDR to low bandwidth\n");
  }

  if (reqClientshub == NULL)
  {
    Status = swsys_npa_init();
    if (Status == EFI_SUCCESS)
    {
      // init the npa request nodes
      reqClientshub = swsys_npa_request_node("shub QUEST req client", sizeof(shubMasterSlave), &shubMasterSlave);
      if (reqClientshub == NULL)
      {
        swsys_error("Fail to init NPA request node for shub\n");
      }
    }
    // init the npa request nodes
    //reqClientshub = npa_create_sync_client_ex("/icb/arbiter",
    //                "shub QUEST req client",
    //                NPA_CLIENT_VECTOR,
    //                sizeof(shubMasterSlave),
    //                &shubMasterSlave);
  }

  swsys_switch_shub_clk(init_freq_khz);
  swsys_debug("done init shub clk\n");
}

void swsys_deinit_shub_clk_uefi()
{
  swsys_debug("deinit shub clk\n");
  EFI_STATUS Status = EFI_SUCCESS;

  swsys_ddr_setnominalbandwidth();

  // Turn on display first so that it will vote for proper bandsidth before Quest npa client is released
  swsys_dispctrl_on();

  // destroy the npa clients
  Status = swsys_npa_init();
  if (Status == EFI_SUCCESS)
  {
    // init the npa request nodes
    swsys_npa_destroy_node(reqClientshub);

  }
  //npa_complete_request(reqClientshub);
  swsys_debug("done deinit shub clk\n");
}


/* 
   Function: Get system supported DDR freq table using DDRGetInfoProtocol
 */
uint8_t swsys_get_shub_freq_table_uefi(uint32_t *freq_list)
{
  EFI_STATUS Status;
  uint32_t i, freq_khz;
  uint8_t valid_freq_count =0;
  uint8_t freq_enable;
 
  pSHUBFreqTbl = AllocatePool (sizeof (shub_freq_plan_entry));
  if (pSHUBFreqTbl == NULL){
      swsys_error("Failed to allocate memory for SHUB freq table\n");
      return 0;
  }
    
  //DDRINFOProtocol should be located in swsys_init_ddr_clk  
  if (DDRINFOProtocol) {
    if (EFI_SUCCESS != (Status = DDRINFOProtocol->GetSHUBFreqTable(DDRINFOProtocol,pSHUBFreqTbl)))
    {
      swsys_error("Get SHUB freq table failed with status: %r\r\n", Status);
      return 0;
    }
    else{
      swsys_debug("Get SHUB freq table SUCCESS, size = %d\n", pSHUBFreqTbl->num_shub_freqs);
      for (i=0; i < pSHUBFreqTbl->num_shub_freqs; i++) {
          freq_khz = pSHUBFreqTbl->shub_freq[i].freq_khz;
          freq_enable = pSHUBFreqTbl->shub_freq[i].enable;
          swsys_debug("SHUB_freq[%2d] = %8d, Valid = %d\n",i,freq_khz,freq_enable);
          if (freq_enable && (freq_khz != 0)) {
              //This is a valid DDR freq supported by system
              freq_list[valid_freq_count] = freq_khz;
              valid_freq_count++;
          }
      }
      for (i=0; i < valid_freq_count; i++) {
          swsys_info("Valid SHUB_freq[%2d] = %8d\n",i,freq_list[i]);
      }
      return valid_freq_count;
    }
  }
  else{
    swsys_error("DDRInfoProtocol not available\n"); 
    return 0;
  } 
}

uint32_t swsys_switch_shub_clk_uefi(uint32_t freq_khz)
{
  EFI_STATUS Status = EFI_SUCCESS;
  uint32_t set_freq_khz = 0;
  swsys_debug("switch shub clk\n");
  ICBArb_RequestType aRequest[1];
  ICBArb_Request2Type type2;
  aRequest[0].arbType = ICBARB_REQUEST_TYPE_2;
  type2.uUsagePercentage = 100;
  type2.uLatencyNs = 0;

  type2.uThroughPut = search_shub_freq_band(freq_khz, &set_freq_khz);
  swsys_debug("voting bandwidth: 0x%08x%08x\n", type2.uThroughPut >> 32, type2.uThroughPut & 0xFFFFFFFF);

  aRequest[0].arbData = (ICBArb_RequestUnionType)type2;

  Status = swsys_npa_init();
  if (Status == EFI_SUCCESS)
  {
    swsys_npa_issue_vector_request(reqClientshub, sizeof(aRequest) / (sizeof(npa_resource_state)),
                                   (npa_resource_state *)aRequest);
    
  }

  //npa_issue_vector_request(reqClientshub,
  //                         sizeof(aRequest) / (sizeof(npa_resource_state)),
  //                         (npa_resource_state *)aRequest);

  return set_freq_khz;
}
#if 1
bool swsys_read_shub_clk_uefi(uint32_t* freq_khz) {

   EFI_STATUS Status;
    
	if(!DDRINFOProtocol){
		swsys_error("DDRINFOProtocol not available\n");
        return false;
	}
	else{
		Status = DDRINFOProtocol->GetSHUBFreq(DDRINFOProtocol,freq_khz);
        if (Status == EFI_SUCCESS) {
            return  true;
        }else{
            return false;
        }
	}
}

#else
bool swsys_read_shub_clk_uefi(uint32_t* freq_khz) {
    EFI_CLOCK_PROTOCOL *mClockProtocol = NULL;
    uint32_t  uClockFreq = 0;
    UINTN  uClockId;
    uint32_t     nMuxSel = 0xCF; // 0xCF - gcc_memnoc_clk
    char* szName = "gcc";
  
    if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&mClockProtocol)) {
        swsys_error("Clock protocol failed!\n");
        return false;
    }
  
  
    if (EFI_SUCCESS != mClockProtocol->GetID(mClockProtocol, szName, &uClockId)) {
        swsys_error("GetID: block %s is not found!\n", szName);
        return false;
    }
  
  
    if (EFI_SUCCESS != mClockProtocol->MeasureFreqHz(mClockProtocol, uClockId, nMuxSel, &uClockFreq)) {
 			  swsys_error("MeasureFreqHz: Can't query frequency of %s with Mux 0x%x\n", szName, nMuxSel);
  			  return false;
    }
    else {
  			  swsys_debug("MeasureFreqHz: %s with Mux 0x%x and freqency: %u Hz\n", szName, nMuxSel, uClockFreq);
  			  *freq_khz = uClockFreq/1000; //Transform from Hz to kHz
    }
  
    return true;
 }
#endif
#if 0
//
//Using DDR API to switch and read DDR freq
//
uint32_t swsys_switch_ddr_clk_uefi(uint32_t freq_khz) 
{ 
	EFI_STATUS Status;
        uint32_t set_freq_khz = 0;

	if(!DDRINFOProtocol)
	{
		swsys_error("DDRINFOProtocol not available\n");
	}
	else
	{
		Status = DDRINFOProtocol->SetDDRFreq(DDRINFOProtocol,freq_khz);
		if(Status == EFI_SUCCESS)
		{
            //If pass, read DDR freq
			swsys_read_ddr_clk(&set_freq_khz);
		}
		else
		{
			swsys_error("Fail to set DDR freq to %d\n",freq_khz);
		}
	}
	return set_freq_khz;
}

bool swsys_read_ddr_clk_uefi(uint32_t* freq_khz) 
{
    EFI_STATUS Status;
    
	if(!DDRINFOProtocol)
	{
		swsys_error("DDRINFOProtocol not available\n");
		return -1;
	}
	else
	{
		Status = DDRINFOProtocol->GetDDRFreq(DDRINFOProtocol,freq_khz);
		if(Status == EFI_SUCCESS)
		{
            return true;
		}
		else
		{
			return false;
		}
	}
}
#endif
void swsys_icb_post_init(void)
{
  /* Check if clock protocol is there*/
  if (EfiClockProtocol == NULL) {
    swsys_debug("Get clock protocol\n");
    if (gBS->LocateProtocol(&gEfiClockProtocolGuid,NULL,(VOID **)&EfiClockProtocol ) != EFI_SUCCESS) {
      swsys_error("Could not locate clock protocol\n");
    }
  }

  if(EfiClockProtocol->PostInit(EfiClockProtocol) != EFI_SUCCESS){
    swsys_error("ICB post-init failed\n");
  } else{
    swsys_debug("ICB post-init done\n");
  }
 
}


void swsys_init_cpu_clk_uefi() 
{
  /* Create clock handle and get the current frequency. */
  if (EfiClockProtocol == NULL) {
    swsys_debug("init cpu\n");
    if (gBS->LocateProtocol(&gEfiClockProtocolGuid,
                        NULL,
                        (VOID **)&EfiClockProtocol ) != EFI_SUCCESS) {
      swsys_error("could not locate protocol\n");
    }
    swsys_debug("done init cpu\n");
  }
}

void swsys_deinit_cpu_clk_uefi() {}

uint32_t swsys_cpu_available_clks_uefi(uint32_t cluster, uint32_t* cpu_freq_tbl )
{ 

   uint32_t *freq_tbl = cpu_freq_tbl;

  uint32_t nfrequencies = 0;
  uint32_t max_perf_level, perf_freq_hz, voltage_mv;

  if (EfiClockProtocol->GetMaxPerfLevel(EfiClockProtocol, cluster, &max_perf_level) != EFI_SUCCESS) {
    swsys_error("Failed to get max_perf_level\n");
    return 0;
  }
  if (!max_perf_level) {
	  swsys_error("\n[CPU_INFO] Max perf level is 0 for Cluster[%d]",cluster);
  }else{
  nfrequencies = max_perf_level + 1;
  }

  if(!freq_tbl) {
      return nfrequencies;
  }

  nfrequencies = 0;
  for (uint32_t i = 0; i <= max_perf_level; i++) {
    if (EfiClockProtocol->GetCpuPerfLevelFrequency(EfiClockProtocol, cluster, i, &perf_freq_hz, &voltage_mv) !=  EFI_SUCCESS) {
      swsys_error("Failed to get cpu perf_level %d\n", i);
    } else {
      freq_tbl[i] = perf_freq_hz / 1000;
      //swsys_debug("freq:%d, volt:%d \n", freq_tbl[i], voltage_mv);;
      swsys_info("freq(kHz):%d, volt:%d \n", freq_tbl[i], voltage_mv);;
      nfrequencies++;
    }
  }
  return nfrequencies;
}


uint32_t swsys_switch_cpu_clk_uefi(uint32_t cluster, uint32_t freq_khz)
{ 
   uint32_t ret_freq = 0;
  bool perf_level_found = false;
  uint32_t perf_level, max_perf_level, perf_freq_hz, voltage_mv;
  if (EfiClockProtocol->GetMaxPerfLevel(EfiClockProtocol, cluster, &max_perf_level) != EFI_SUCCESS) {
    swsys_error("Failed to get max_perf_level\n");
    return 0;
  }

  for (uint32_t i = 0; i <= max_perf_level; i++) {
    if (EfiClockProtocol->GetCpuPerfLevelFrequency(EfiClockProtocol, cluster, i, &perf_freq_hz, &voltage_mv) != EFI_SUCCESS) {
      swsys_error("Failed to get cpu perf_level %d\n", i);
    } else {
      if (perf_freq_hz / 1000 >= freq_khz) {
        perf_level = i;
        perf_level_found = true;
        break;
      }
    }
  }

  if (!perf_level_found) {
    if(max_perf_level >= 1) {
      perf_level = max_perf_level;
    } else {
      perf_level = 0;
    }
  }

  if (EfiClockProtocol->SetCpuPerfLevel(EfiClockProtocol, cluster,perf_level, &ret_freq) != EFI_SUCCESS)
  {
      swsys_error("CPU Frequency set failed %d\n", perf_level);
  }
  return ret_freq;
}

bool swsys_read_cpu_clk_uefi(uint32_t cluster, uint32_t* freq_khz)
{
  uint32_t perf_level, freq_hz, voltage_mv;

  swsys_debug("reading cpu freq\n");

  if (EfiClockProtocol == NULL) {
      swsys_init_cpu_clk();
			if (!EfiClockProtocol) {
				swsys_error("Failed to locate clock protocol\n");
				return false;
			}
  }

  if (EfiClockProtocol->GetCpuPerfLevel(EfiClockProtocol, cluster, &perf_level) != EFI_SUCCESS) 
    return false;

  if (EfiClockProtocol->GetCpuPerfLevelFrequency(EfiClockProtocol, cluster, perf_level, &freq_hz, &voltage_mv) != EFI_SUCCESS) {
    return false;
  }

  *freq_khz = freq_hz / 1000;

  swsys_debug("done reading cpu freq %d\n", *freq_khz);

  return true;
}
