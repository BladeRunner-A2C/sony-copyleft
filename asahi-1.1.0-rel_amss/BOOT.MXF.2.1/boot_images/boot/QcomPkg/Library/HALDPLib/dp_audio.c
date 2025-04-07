/*=============================================================================================
  Copyright (c) 2019-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "dp_audio.h"

/*---------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------*/
#define DP_AUDIO_CODING_TYPE_DEFAULT          0
#define DP_AUDIO_CODING_TYPE_ONE_BIT_AUDIO    3

#define DP_AUDIO_NUMBER_OF_CHANNELS_2         2
#define DP_AUDIO_NUMBER_OF_CHANNELS_4         4
#define DP_AUDIO_NUMBER_OF_CHANNELS_6         6
#define DP_AUDIO_NUMBER_OF_CHANNELS_8         8

#define DP_AUDIO_BASE_SAMPLE_RATE_32_KHZ      32
#define DP_AUDIO_BASE_SAMPLE_RATE_44_KHZ      44
#define DP_AUDIO_BASE_SAMPLE_RATE_48_KHZ      48
                                              
#define DP_AUDIO_SAMPLE_RATE_MULTIPLIER_1     1
#define DP_AUDIO_SAMPLE_RATE_MULTIPLIER_2     2
#define DP_AUDIO_SAMPLE_RATE_MULTIPLIER_4     4
/*---------------------------------------------------------------------------------------------
 * Local Prototypes
 *-------------------------------------------------------------------------------------------*/
static bool32 dp_app_audio_filter(double  i_lclk,
                                  double  i_pclk,
                                  int     i_nlanes,
                                  int     i_hblank,
                                  int     i_htotal,
                                  int     i_fec_en,
                                  int     i_mst_en,
                                  int     i_mst_cf_en,
                                  double  i_mst_target_sc,
                                  int     i_mst_ts_int_plus1,  
                                  double  i_mst_dsc_factor,
                                  int     i_aud_ct,
                                  int     i_aud_chLayout,
                                  int     i_aud_multi,
                                  int     i_aud_bRate,
                                  int     i_dsc_en,
                                  int     i_dsc_dto_num,
                                  int     i_dsc_dto_den);

/*---------------------------------------------------------------------------------------------
 * Public Functions
 *-------------------------------------------------------------------------------------------*/

/**********************************************************************************************
*
** FUNCTION: DP_Audio_FilterModes()
*/
/*!
* \DESCRIPTION
*     Filter audio modes based on the current link configuration
*
* \param [in]   pDisplayCtx        - Pointer to display context
* \param [in]   psPanelInfo        - Pointer to panel parameters for current display mode
* \param [in]   pHALRgConfig       - Pointer to the current MST RG configuration
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Audio_FilterModes(DP_DisplayCtxType    *pDisplayCtx,
                                DP_PanelInfoType     *psPanelInfo,
                                HAL_DP_RGConfigType  *pHALRgConfig)
{
  DP_Status            eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType    *pDeviceCtx;
  DP_StreamCtxType    *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    DP_LOG_MESSAGE_ERROR("DP_Audio_FilterModes: unexpected null handle ");
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else if ((0 == pStreamCtx->uPixelClkInKhz) ||
           (0 == pDeviceCtx->uLinkRateInKhz) ||
           (0 == pDeviceCtx->uNumLanes))
  {
    DP_LOG_MESSAGE_ERROR("DP_Audio_FilterModes: Invalid Input(s) eDisplayID: %d, uPixelClkInKhz: %d, uLinkRateInKhz: %d, uNumLanes: %d", 
                          pStreamCtx->eDisplayID,
                          pStreamCtx->uPixelClkInKhz,
                          pDeviceCtx->uLinkRateInKhz, 
                          pDeviceCtx->uNumLanes);
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (pStreamCtx->uNumberOfAudioModes > 0)
  {
    uint32                    uNumLanes           = pDeviceCtx->uNumLanes;
    uint32                    uHblank             = psPanelInfo->uHsyncBackPorchInPixels +
                                                    psPanelInfo->uHsyncPulseInPixels +
                                                    psPanelInfo->uHsyncFrontPorchInPixels;
    bool32                    bFECEnabled         = pDeviceCtx->bFECEnabled;
    bool32                    bMSTEnabled         = pDeviceCtx->bMSTEnabled;
    bool32                    bDSCEnabled         = pStreamCtx->sDSCInfo.bDSCEnabled;
    DP_AudioSampleRateType    uCurrentSampleRate  = DP_AUDIO_SAMPLE_RATE_NONE;
    double                    dLinkClockInMhz;
    double                    dPixelClockInMhz;
    uint32                    uHTotal;
    bool32                    bMSTConstantFill;
    double                    dChosenSlotCount;
    uint32                    uTS_INT_PLUS1;
    uint32                    uDSCDTONumerator;
    uint32                    uDSCDTODenominator;
    uint32                    uAudioStreamIndex;
    DP_AudioChannelType       uCurrentChannelLayout;
    DP_AudioModeInfoPropType *pAudioModeInfo;
    double                    dMSTDscOverhead;
    
    dLinkClockInMhz       = (double)pDeviceCtx->uLinkRateInKhz / 1000;
    dPixelClockInMhz      = (double)pStreamCtx->uPixelClkInKhz / 1000;

    /* HTotal = HBlank + HActive */
    uHTotal = uHblank + 
              psPanelInfo->uVisibleWidthInPixels +
              psPanelInfo->uHLeftBorderInPixels +
              psPanelInfo->uHRightBorderInPixels;

    if (TRUE == pDeviceCtx->bMSTEnabled)
    {
      bMSTConstantFill = TRUE; /* TRUE if MST enabled */
      dChosenSlotCount = pHALRgConfig->dChosenSlotCount;
      uTS_INT_PLUS1    = pHALRgConfig->uTS_INT_PLUS1;
      dMSTDscOverhead  = (TRUE == pStreamCtx->sDSCInfo.bDSCEnabled)? pStreamCtx->sDSCInfo.fDSCOverheadRatio : 1;
    }
    else
    {
      bMSTConstantFill = FALSE; /* FALSE if MST disabled */
      dChosenSlotCount = 0;     /* 0 if MST disabled */
      uTS_INT_PLUS1    = 0;     /* 0 if MST disabled */
      dMSTDscOverhead  = 1;     /* 1 if MST disabled */
    }

    if (TRUE == bDSCEnabled)
    {
      uDSCDTONumerator   = pStreamCtx->sDSCInfo.uDSCDTONumerator;
      uDSCDTODenominator = pStreamCtx->sDSCInfo.uDSCDTODenominator;
    }
    else
    {
      uDSCDTONumerator   = 0;  /* 0 if DSC disabled */
      uDSCDTODenominator = 0;  /* 0 if DSC disabled */
    }
    
    /* Filter out invalid audio mode configurations for each audio mode */
    for (uAudioStreamIndex = 0; uAudioStreamIndex < pStreamCtx->uNumberOfAudioModes; uAudioStreamIndex++)
    {
      /* Update the current mode info with all supported sample rates and bit depths
         so that we can filter from them according to the display mode selected now */
      pAudioModeInfo                                = &pStreamCtx->sAudioModeInfo[uAudioStreamIndex];
      pAudioModeInfo->uSupportedAudioChannelMask    = pStreamCtx->sAudioModeInfo[uAudioStreamIndex].uSupportedAudioChannelMask;
      pAudioModeInfo->uSupportedAudioSampleRateMask = pStreamCtx->sAudioModeInfo[uAudioStreamIndex].uSupportedAudioSampleRateMask;

      uint32 uAudioCodingType;
      uint16 uSupportedAudioChannelMask    = pAudioModeInfo->uSupportedAudioChannelMask;
      uint16 uSupportedAudioSampleRateMask = pAudioModeInfo->uSupportedAudioSampleRateMask;
      bool32 bFoundValidConfig             = FALSE;
      uint32 uAudioChannelLayout           = 0;
      uint32 uAudioSampleRateMultiplier    = 0;
      uint32 uAudioBaseSampleRate          = 0;

      /* Coding type = 3 for one bit audio, coding type = 2 for 3D LPCM audio,
       * and coding type = don't care for other supported audio types */
      if (MDP_HDMI_AUDIO_FORMAT_ONE_BIT_AUDIO == pAudioModeInfo->eAudioFormat)
      {
        uAudioCodingType = DP_AUDIO_CODING_TYPE_ONE_BIT_AUDIO;
      }
      else
      {
        uAudioCodingType = DP_AUDIO_CODING_TYPE_DEFAULT;
      }

      /* Search for the maximum valid bandwidth configuration within the audio mode (prioritizing the number of channels) */
      for (uCurrentChannelLayout = DP_AUDIO_CHANNEL_8; uCurrentChannelLayout > DP_AUDIO_CHANNEL_NONE; uCurrentChannelLayout >>= 1)
      {
        if (0 != (uSupportedAudioChannelMask & uCurrentChannelLayout))
        {
          for (uCurrentSampleRate = DP_AUDIO_SAMPLE_RATE_192KHZ; uCurrentSampleRate > DP_AUDIO_SAMPLE_RATE_NONE; uCurrentSampleRate >>= 1)
          {
            if (0 != (uSupportedAudioSampleRateMask & uCurrentSampleRate))
            {
              switch (uCurrentChannelLayout)
              {
                case DP_AUDIO_CHANNEL_2:
                  uAudioChannelLayout = DP_AUDIO_NUMBER_OF_CHANNELS_2;
                  break;
                case DP_AUDIO_CHANNEL_4:
                  uAudioChannelLayout = DP_AUDIO_NUMBER_OF_CHANNELS_4;
                  break;
                case DP_AUDIO_CHANNEL_6:
                  uAudioChannelLayout = DP_AUDIO_NUMBER_OF_CHANNELS_6;
                  break;
                case DP_AUDIO_CHANNEL_8:
                  uAudioChannelLayout = DP_AUDIO_NUMBER_OF_CHANNELS_8;
                  break;
                default:
                  DP_LOG_MESSAGE_ERROR("DP_Audio_FilterModes: Unexpected channel layout");
                  eStatus = DP_STATUS_FAIL;
                  goto exit;
              }

              switch (uCurrentSampleRate)
              {
                case DP_AUDIO_SAMPLE_RATE_32KHZ:
                  uAudioBaseSampleRate       = DP_AUDIO_BASE_SAMPLE_RATE_32_KHZ;
                  uAudioSampleRateMultiplier = DP_AUDIO_SAMPLE_RATE_MULTIPLIER_1;
                  break;
                case DP_AUDIO_SAMPLE_RATE_44_1KHZ:
                  uAudioBaseSampleRate       = DP_AUDIO_BASE_SAMPLE_RATE_44_KHZ;
                  uAudioSampleRateMultiplier = DP_AUDIO_SAMPLE_RATE_MULTIPLIER_1;
                  break;
                case DP_AUDIO_SAMPLE_RATE_48KHZ:
                  uAudioBaseSampleRate       = DP_AUDIO_BASE_SAMPLE_RATE_48_KHZ;
                  uAudioSampleRateMultiplier = DP_AUDIO_SAMPLE_RATE_MULTIPLIER_1;
                  break;
                case DP_AUDIO_SAMPLE_RATE_88_2KHZ:
                  uAudioBaseSampleRate       = DP_AUDIO_BASE_SAMPLE_RATE_44_KHZ;
                  uAudioSampleRateMultiplier = DP_AUDIO_SAMPLE_RATE_MULTIPLIER_2;
                  break;
                case DP_AUDIO_SAMPLE_RATE_96KHZ:
                  uAudioBaseSampleRate       = DP_AUDIO_BASE_SAMPLE_RATE_48_KHZ;
                  uAudioSampleRateMultiplier = DP_AUDIO_SAMPLE_RATE_MULTIPLIER_2;
                  break;
                case DP_AUDIO_SAMPLE_RATE_176_4KHZ:
                  uAudioBaseSampleRate       = DP_AUDIO_BASE_SAMPLE_RATE_44_KHZ;
                  uAudioSampleRateMultiplier = DP_AUDIO_SAMPLE_RATE_MULTIPLIER_4;
                  break;
                case DP_AUDIO_SAMPLE_RATE_192KHZ:
                  uAudioBaseSampleRate       = DP_AUDIO_BASE_SAMPLE_RATE_48_KHZ;
                  uAudioSampleRateMultiplier = DP_AUDIO_SAMPLE_RATE_MULTIPLIER_4;
                  break;
                default:
                  DP_LOG_MESSAGE_ERROR("DP_Audio_FilterModes: Unexpected sample rate");
                  eStatus = DP_STATUS_FAIL;
                  goto exit;
              }

              /* Check if current audio mode configuration is valid with the active display configuration */
              if (TRUE == dp_app_audio_filter(dLinkClockInMhz,
                                              dPixelClockInMhz,
                                              uNumLanes,
                                              uHblank,
                                              uHTotal,
                                              bFECEnabled,
                                              bMSTEnabled,
                                              bMSTConstantFill,
                                              dChosenSlotCount,
                                              uTS_INT_PLUS1,
                                              dMSTDscOverhead,
                                              uAudioCodingType,
                                              uAudioChannelLayout,
                                              uAudioSampleRateMultiplier,
                                              uAudioBaseSampleRate,
                                              bDSCEnabled,
                                              uDSCDTONumerator,
                                              uDSCDTODenominator))
              {
                /* Stop search, max audio mode configuration found */
                bFoundValidConfig = TRUE;
                break;
              }
              else
              {
                TraceInfo(QdiTraceDP,
                          "DP%i: filtering uAudioBaseSampleRate :0x%x uAudioSampleRateMultiplier :0x%x uAudioChannelLayout :0x%x for following parameters",
                          pStreamCtx->eDisplayID,
                          uAudioBaseSampleRate,
                          uAudioSampleRateMultiplier,
                          uAudioChannelLayout);

                TraceInfo(QdiTraceDP,
                          "DP%i: dp_app_audio_filter : dLinkClockInMhz:%f , dPixelClockInMhz:%f, uNumLanes:0x%x, uHblank:0x%x, uHTotal:0x%x, bFECEnabled :0x%x dMSTDscOverhead: %f",
                          pStreamCtx->eDisplayID,
                          dLinkClockInMhz,
                          dPixelClockInMhz,
                          uNumLanes,
                          uHblank,
                          uHTotal,
                          bFECEnabled,
                          dMSTDscOverhead);
                TraceInfo(QdiTraceDP,
                          "DP%i: dp_app_audio_filter : bMSTEnabled::0x%x, bMSTConstantFill:0x%x, dChosenSlotCount:%f, uTS_INT_PLUS1:0x%x, bDSCEnabled:0x%x,uDSCDTONumerator:0x%x, uDSCDTODenominator:0x%x",
                          pStreamCtx->eDisplayID,
                          bMSTEnabled,
                          bMSTConstantFill,
                          dChosenSlotCount,
                          uTS_INT_PLUS1,
                          bDSCEnabled,
                          uDSCDTONumerator,
                          uDSCDTODenominator);

              }
            }
          }

          if (TRUE == bFoundValidConfig)
          {
            break;
          }
        }
      }
      
      if ((DP_AUDIO_CHANNEL_NONE != uCurrentChannelLayout) &&
          (DP_AUDIO_SAMPLE_RATE_NONE != uCurrentSampleRate))
      {
        /* If a maximum valid bandwidth configuration is found, filter out configurations that 
         * have bandwidths greater than the maximum valid configuration */
        pAudioModeInfo->uSupportedAudioChannelMask    &= (uCurrentChannelLayout | (uCurrentChannelLayout - 1));
        pAudioModeInfo->uSupportedAudioSampleRateMask &= (uCurrentSampleRate | (uCurrentSampleRate - 1));
        
        /* If any configurations within the audio mode were filtered out */
        if ((uSupportedAudioChannelMask    != pAudioModeInfo->uSupportedAudioChannelMask) ||
            (uSupportedAudioSampleRateMask != pAudioModeInfo->uSupportedAudioSampleRateMask))
        {
          TraceInfo(QdiTraceDP,
                    "DP%i: Filtered configurations higher in sample rate: %d KHz and channel layout: %d for audio mode with eFormat: %d at index: %d",
                    pStreamCtx->eDisplayID,
                    uAudioBaseSampleRate * uAudioSampleRateMultiplier,
                    uAudioChannelLayout,
                    pAudioModeInfo->eAudioFormat,
                    uAudioStreamIndex);
        }
      }
      else
      {
        /* If no maximum valid bandwidth configuration is found, then the audio mode is marked
         * as to-be-discarded by clearing the sample rate and channel masks to 0 */
        pAudioModeInfo->uSupportedAudioChannelMask    = 0;
        pAudioModeInfo->uSupportedAudioSampleRateMask = 0;

        TraceInfo(QdiTraceDP,
                  "DP%i: Filtered out audio mode with eFormat: %d at index: %d",
                  pStreamCtx->eDisplayID,
                  pAudioModeInfo->eAudioFormat,
                  uAudioStreamIndex);
      }
    }
  }
exit:
    return eStatus;

}

/*---------------------------------------------------------------------------------------------
 * Private Functions
 *-------------------------------------------------------------------------------------------*/

/**********************************************************************************************
*
** FUNCTION: dp_app_audio_filter()
*/
/*!
* \DESCRIPTION
*     Check if audio mode configuration will have sufficient bandwidth over link based on the
*     active display mode configuration.
*
* \param [in]   i_lclk              - Link clock in MHz
* \param [in]   i_pclk              - Pixel clock in MHz
* \param [in]   i_nlanes            - Number of lanes
* \param [in]   i_hblank            - Horizontal blanking
* \param [in]   i_htotal            - Total horizontal timing
* \param [in]   i_fec_en            - FEC enable
* \param [in]   i_mst_en            - MST enable
* \param [in]   i_mst_cf_en         - MST constant fill enable
* \param [in]   i_mst_target_sc     - Chosen MST target slot count
* \param [in]   i_mst_ts_int_plus1  - Ceiling of chosen MST target slot count
* \param [in]   i_mst_dsc_factor    - DSC over head for MST scenarios, set to 1 for SST
* \param [in]   i_aud_ct            - Audio coding type
* \param [in]   i_aud_chLayout      - Audio channel layout
* \param [in]   i_aud_multi         - Audio sample rate multiplication factor
* \param [in]   i_aud_bRate         - Audio sample rate base rate
* \param [in]   i_dsc_en            - DSC enable
* \param [in]   i_dsc_dto_num       - DSC DTO numerator
* \param [in]   i_dsc_dto_den       - DSC DTO denominator
*
* \retval bool32
*
**********************************************************************************************/
static bool32 dp_app_audio_filter(// INPUTS
                                  double  i_lclk,
                                  double  i_pclk,    // not div2
                                  int     i_nlanes,  
                                  int     i_hblank,  // not div2
                                  int     i_htotal,  // not div2
                                  int     i_fec_en,
                                  // INPUTS: mst
                                  int     i_mst_en,
                                  int     i_mst_cf_en,
                                  double  i_mst_target_sc,
                                  int     i_mst_ts_int_plus1,
                                  double  i_mst_dsc_factor,
                                  // INPUTS: audio
                                  int     i_aud_ct,
                                  int     i_aud_chLayout,
                                  int     i_aud_multi,
                                  int     i_aud_bRate,
                                  // INPUTS: dsc
                                  int     i_dsc_en,
                                  int     i_dsc_dto_num,
                                  int     i_dsc_dto_den)
{
  int     hblank_sym_total;
  int     hblank_sym_avail;
  double  mst_hblank_bw_alloc;
  int     hblank_sym_avail_floor;
  int     hblank_sym_avail_data;
  int     hblank_layout_avail_data;
  int     hblank_layout_avail;

  double  aud_fs;
  int     aspl_layout_req;
  int     mst_per_line_sym_jitter;
  int     mst_hblank_sym_jitter      = 0;
  int     mst_nslot                  = 0;
  int     mst_vblank_fall_pix_early  = 0;

  int     hblank                     = i_hblank;
  int     htotal                     = i_htotal;
  double  lclk                       = i_lclk;
  double  pclk                       = i_pclk;
  int     nlanes                     = i_mst_en == 1 ? 4 : i_nlanes;
  int     bs_sym_cnt                 = i_mst_en == 1 ? 4 : i_nlanes * 4;
  int     vbid_sym_cnt               = 4;
  int     mvid_sym_cnt               = 4;
  int     maud_sym_cnt               = 4;
  int     sdp_entry_sym_cnt          = nlanes;
  int     sdp_exit_sym_cnt           = nlanes;
  int     sdp_margin_sym_cnt         = 4;
  int     be_sym_cnt                 = nlanes;
  int     dto_hblank_rise_pix_skew   = 0;

  int sample_per_layout = 0;

  int aud_ct       = i_aud_ct;
  int aud_chLayout = i_aud_chLayout;
  int aud_multi    = i_aud_multi;
  int aud_bRate    = i_aud_bRate;

  int     max_layout_cnt_sdp  = aud_chLayout == 2 ? 16 : 32;
  int     ss_sym_cnt          = nlanes;
  int     sdp_hd_sym_cnt      = 8;
  int     se_sym_cnt          = nlanes;
  int     sym_cnt_per_layout  = aud_chLayout == 2 ? 20 : aud_chLayout * 5;
  int     max_sym_cnt_sdp     = ss_sym_cnt + sdp_hd_sym_cnt + se_sym_cnt + (max_layout_cnt_sdp * sym_cnt_per_layout);
  double  fec_bw_alloc        = 1537.0 / 65537.0;
  double  fec_pm_bw_alloc     = 1.0 / 65537.0;
  double  fec_sym             = 0;
  double  fec_pm_sym          = 0;
  int     fec_sym_cnt         = 0;

  double mst_dsc_factor      = i_mst_dsc_factor;
  double mst_fec_factor      = (i_fec_en) ? (1 / 0.97582) : 1.0;
  double mst_factors         = (i_mst_en &&  i_mst_cf_en) ? (mst_dsc_factor * mst_fec_factor) : 1 ;
  int sst_bs_line_sym_jitter = 3;
  int fec_lane_factor        = 0;
    
  if ((0 != i_dsc_en) && 
      (0 != i_dsc_dto_num))
  {
    dto_hblank_rise_pix_skew = (int)(DP_Ceil((float)i_dsc_dto_den / i_dsc_dto_num) - 1) * 2;
  }
  else if (0 != i_mst_en)
  {
    mst_vblank_fall_pix_early = 1;
  }

  hblank_sym_total = ((int)(((double)hblank - dto_hblank_rise_pix_skew - mst_vblank_fall_pix_early)  * lclk / pclk)) * i_nlanes;

  if (i_mst_en != 0)
  {
    mst_hblank_bw_alloc = i_mst_target_sc / 64.0;
    hblank_sym_total = (int)(hblank_sym_total * mst_hblank_bw_alloc);

    if (i_mst_cf_en != 0)
    {
      // mst_hblank_sym_jitter = 19;
      mst_hblank_sym_jitter = 28;
    }
    else
    {
      mst_nslot = i_mst_ts_int_plus1;
      mst_hblank_sym_jitter = 12 + (int)DP_Ceil((mst_nslot * (64 - (double)mst_nslot) / 64.0) * i_nlanes);
    }
  }

  if (i_fec_en != 0)
  {
    fec_sym = hblank_sym_total * fec_bw_alloc / i_nlanes;
    fec_pm_sym = hblank_sym_total * fec_pm_bw_alloc / i_nlanes;

    if (i_mst_en != 0 && i_mst_cf_en != 0)
    {
      // No penalty since the extra symbols/BW required for FEC
      // has been compensated in MST with constant fill
      // fec_sym_cnt = (int)DP_Ceil(fec_sym) *  dp_cfg->num_lanes;
    }
    else
    {
      if (i_nlanes == 1)
      {
        fec_sym_cnt = ((12 * (int)DP_Ceil(fec_sym / 12.0) + 1) + (int)DP_Ceil(fec_pm_sym)) * i_nlanes;
      }
      else
      {
        fec_sym_cnt = ((6 * (int)DP_Ceil(fec_sym / 6.0) + 1) + (int)DP_Ceil(fec_pm_sym)) * i_nlanes;
      }
    }

    fec_lane_factor = ( (12/i_nlanes) < 6) ? 6 : (12/i_nlanes);
  }


  hblank_sym_avail         = ((int)(floor(hblank_sym_total/mst_factors))) - fec_sym_cnt - bs_sym_cnt - vbid_sym_cnt
                             - mvid_sym_cnt - maud_sym_cnt - sdp_entry_sym_cnt - sdp_exit_sym_cnt - sdp_margin_sym_cnt
                             - be_sym_cnt - mst_hblank_sym_jitter - dto_hblank_rise_pix_skew;
  hblank_sym_avail_floor   = hblank_sym_avail / max_sym_cnt_sdp * max_sym_cnt_sdp;
  hblank_sym_avail_data    = hblank_sym_avail - hblank_sym_avail_floor - ss_sym_cnt - sdp_hd_sym_cnt - se_sym_cnt;
  hblank_layout_avail_data = hblank_sym_avail_data < 0 ? 0 : hblank_sym_avail_data / sym_cnt_per_layout;

  hblank_layout_avail = hblank_sym_avail_floor * max_layout_cnt_sdp / max_sym_cnt_sdp + hblank_layout_avail_data;

  if (aud_ct == 3)
  {
    sample_per_layout = 28;
  }
  else
  {
    if (aud_chLayout == 2)
    {
      sample_per_layout = 2;
    }
    else
    {
      if (aud_multi > 4)
      {
        sample_per_layout = 4;
      }
      else
      {
        sample_per_layout = 1;
      }
    }
  }

  aud_fs = aud_bRate == 44 ? 44.1 * aud_multi : (double)aud_bRate * aud_multi;

  if (aud_ct == 3)
  {
    aud_fs *= 64;
  }

  mst_per_line_sym_jitter = i_mst_en != 0 ? 128 : 0;
  aspl_layout_req = (int)((aud_fs / sample_per_layout) * (htotal / (pclk * 1000) +(((double)mst_per_line_sym_jitter) + sst_bs_line_sym_jitter + (((double)fec_lane_factor+ fec_pm_sym )*i_fec_en) ) / (lclk * 1000)));
 
  return ((aspl_layout_req + 1) <= hblank_layout_avail);
}

#ifdef __cplusplus
}
#endif

