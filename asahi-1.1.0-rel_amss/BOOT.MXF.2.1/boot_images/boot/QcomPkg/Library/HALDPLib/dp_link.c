/*==========================================================================================================
 
  File: dp_link.c
 
  Source file for DP main link related functionality 
   
  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================================================*/

/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "hal_dp_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/
#define MAX_LINK_TRAINING_LOOP                    5

#define DP_MST_SLOTS_PER_MTP                      64.0              // Number of slots in one MTP
#define DP_MST_PBN_UNIT_NUMERATOR                 54.0              // PBN is in 54/64MBps units
#define DP_MST_PBN_MARGIN                         1.006             // 0.6% margin used while calculating PBN

#define DP_SET_LINK_STATE_WAIT_TIME_US            1000              // Sleep/stall after setting link state patterns during link training.

#define DP_LINK_NVID_THRESHOLD                    0x8000            // Nvid need to be scaled up to threshold for better interop with all monitors

#ifndef MAX
#define MAX(a,b)                                  (a > b ? a : b)
#endif

#ifndef ABS
#define ABS(a)                                    (a > 0 ? a : -a)
#endif

#define MAX_16BITS_VALUE                          ((1 << 16) - 1)   // 16 bits value

#define DP_PREEMPH_VOLSWING_VALUE_LIST_NUM         9                // Num of value pairs of Pre-emph and swing volt                     
#define DP_PREEMPH_VOLSWING_MULTIPLIER_LIST_NUM    2                // Num of multiplier values for Pre-emph and swing volt

/* DP Nvid value factor */
typedef enum
{
  DP_NVID_FACTOR_1_62G = 1,
  DP_NVID_FACTOR_2_70G = 1,
  DP_NVID_FACTOR_5_40G = 2,
  DP_NVID_FACTOR_8_10G = 3,
  DP_NVID_FACTOR_MAX,
  DP_NVID_FACTOR_32BIT = 0x7FFFFFFF
} DP_NvidFactorType;

/* Clock MND divider info */
typedef struct
{
  uint64    uSrcRate;           /* Input clock frequency    */
  uint64    uTargetRate;        /* Divided clock frequency  */
  uint32    uMVal;              /* Divider M value          */
  uint32    uNVal;              /* Divider N value          */
  uint32    uDVal;              /* Divider D value          */
  uint32    uNotNMinusM;        /* Divider NOT(N - M) value */
  uint32    uNot2D;             /* Divider NOT(N) value     */
} DP_MNDType;

/* DP Link rate settings */
typedef struct
{
  uint32 uLinkRateInKhz;        /* Link symbol rate in KHz      */
  uint32 uInputClkMhz;          /* PLL input clock in MHz       */
} DP_LinkRateSettings;

/*---------------------------------------------------------------------------------------------------------------------
 * Global Data Definitions
 *-------------------------------------------------------------------------------------------------------------------*/
DP_PixelFormat_Info       gsDPPixelFormatInfo[DP_PIXEL_FORMAT_MAX] = 
{
  /*uBitsPerPixel   uBitsPerComponent*/
  {  0,             0  },       /*DP_PIXEL_FORMAT_NONE          */
  { 18,             6  },       /*DP_PIXEL_FORMAT_RGB_666_18BPP */
  { 24,             8  },       /*DP_PIXEL_FORMAT_RGB_888_24BPP */
};

/*---------------------------------------------------------------------------------------------------------------------
 * Function pre-declarations
 *-------------------------------------------------------------------------------------------------------------------*/
static int32 Round(double dNumber);

//-------------------------------------------------------------------------------------------------
//  DP_MNExhaustiveSearch
//
//  @brief
//      perform exhaustive search for m and n value.
//
//  @params
//      [IN/OUT] puMVal
//          M value.
//      [IN/OUT] puNVal
//          N value.
//      [OUT] pfError
//          Error.
//
//  @return
//      void.
//-------------------------------------------------------------------------------------------------
//

void DP_MNExhaustiveSearch(uint32 *puMVal, uint32 *puNVal, double *pfError)
{
  uint32 uLMGbl    = *puMVal;
  uint32 uLNGbl    = *puNVal;
  uint32 uLMVal    = *puMVal;
  uint32 uLNVal    = *puNVal;
  uint32 uBestM    = 0;
  uint32 uBestN    = 0;
  float fLMinError = 3.402823466e+38F;
  float fLError    = fLMinError;

  uLNVal = (uint32)(uLNGbl / uLMGbl);
  uLMVal = 0;
  uBestM = uLMVal;
  uBestN = uLNVal;

  // Performing Exhaustive search;
  while (1)
  {
    fLError = (float)uLMGbl - ((float)uLNGbl * (float)uLMVal / (float)uLNVal);

    if (ABS(fLError) < ABS(fLMinError))
    {
      //Found a new Min, Check bit-width limits.
      if (((uLMVal)          <= MAX_16BITS_VALUE) && 
          ((uLNVal - uLMVal) <= MAX_16BITS_VALUE) && 
           (uLNVal           <= MAX_16BITS_VALUE))
      {
        // Update uBestM/uBestN to the values obtained from previous iteration before checking if answer is exact and breaking so function returns with best values 
        fLMinError  = fLError;
        uBestM      = uLMVal;
        uBestN      = uLNVal;
      }
    }

    // If the answer is exact, break out, else, update M/N accordingly. 
    if (0.0 == fLError)
    {
      break;
    }
    else 
    {
      if (0 < fLError)
      {
        uLNVal++;
        uLMVal = (uint32)(uLMGbl * uLNVal / uLNGbl);
      }
      else
      {
        uLMVal++;
      }
    }

    // If we run out of bits then don't continue to search
    if (((uLMVal)           > MAX_16BITS_VALUE) ||
        ((uLNVal - uLMVal)  > MAX_16BITS_VALUE) || 
        ((uLNVal)           > MAX_16BITS_VALUE))
    {
      break;
    }
  }

  *puMVal   = uBestM;
  *puNVal   = uBestN;
  *pfError  = (double)fLMinError;
}

//-------------------------------------------------------------------------------------------------
//  DP_MNReduceBits
//
//  @brief
//      prevent both M and N not greater than  16 BIts value.
//
//  @params
//      [IN/OUT] puMVal
//          M value.
//      [IN/OUT] puNVal
//          N value.
//      [IN] fLRatio
//          Ratio.
//
//  @return
//      void.
//-------------------------------------------------------------------------------------------------
//
void DP_MNReduceBits(uint32 *puMVal, uint32 *puNVal, float fLRatio)
{
  uint32 uLMVal = *puMVal;
  uint32 uLNVal = *puNVal;
  uint32 uLMTmp0;
  uint32 uLMTmp1;
  uint32 uLNTmp0;
  uint32 uLNTmp1;
  uint32 uLNMminusM0;
  uint32 uLNMminusM1;
  float fLErrD;
  float fLErrU;

  /* Round Down */
  uLMTmp0 = (uint32)(uLMVal / 2);                                   /* right shit one bit   */
  fLErrD  = ((float)uLMTmp0) / ((float)uLMVal / 2.0F);              /* Error by truncating  */
  uLNTmp0 = (uint32)(((float)uLNVal) / 2.0 * fLErrD + 0.5);


  /* Round Up */
  uLMTmp1 = (uint32)((float)(uLMVal) / 2.0) + 1;                    /* right shit one bit             */
  fLErrU  = ((float)uLMTmp1) / ((float)uLMVal / 2.0F);               /* Error by truncation and round  */
  uLNTmp1 = (uint32)(((float)uLNVal) / 2.0 * fLErrU + 0.5);

  if ((uLMTmp0 <= MAX_16BITS_VALUE) &&
      (uLMTmp1 >  MAX_16BITS_VALUE))  /* less than 16 bits */
  {
    *puMVal = uLMTmp0;
    *puNVal = uLNTmp0;
  }
  else
  {
    // Do the checking for n-m
    uLNMminusM0 = uLNTmp0 - uLMTmp0;
    uLNMminusM1 = uLNTmp1 - uLMTmp1;
    if ((uLNMminusM0 <= MAX_16BITS_VALUE) && 
        (uLNMminusM1 >  MAX_16BITS_VALUE))
    {
      *puMVal = uLMTmp0;
      *puNVal = uLNTmp0;
    }
    else if (ABS((float)fLRatio - ((float)uLMTmp0 / (float)uLNTmp0)) < ABS((float)fLRatio - ((float)uLMTmp1 / (float)uLNTmp1)))
    {
      *puMVal = uLMTmp0;
      *puNVal = uLNTmp0;
    }
    else
    {
      *puMVal = uLMTmp1;
      *puNVal = uLNTmp1;
    }
  }

  return;
}

//-------------------------------------------------------------------------------------------------
//  DP_MNValueSearch
//
//  @brief
//      M, N finder.
//
//  @params
//      [IN/OUT] puMVal
//          M value.
//      [IN/OUT] puNVal
//          N value.
//
//  @return
//      void.
//-------------------------------------------------------------------------------------------------
//
void DP_MNValueSearch(uint32 *puMVal, uint32 *puNVal)
{
  uint32 uLMVal = *puMVal;
  uint32 uLNVal = *puNVal;
  uint32 uLNTmp;
  float  fLRatio = (float)*puMVal / (float)*puNVal;

  while (uLMVal > MAX_16BITS_VALUE)    /* more than 16 bits */
  {
    DP_MNReduceBits(&uLMVal, &uLNVal, fLRatio);
  }

  // Check N for overflow.
  // N is programmed as ~(N-M)
  uLNTmp = (uLNVal - uLMVal);
  while (uLNTmp > MAX_16BITS_VALUE)
  {
    DP_MNReduceBits(&uLMVal, &uLNVal, fLRatio);
    uLNTmp = (uLNVal - uLMVal);
  }

  *puMVal = uLMVal;
  *puNVal = uLNVal;
}

//-------------------------------------------------------------------------------------------------
//  DP_MNValueGcd
//
//  @brief
//      GCD calculation.
//
//  @params
//      [IN] uNumerator
//          Numerator.
//      [IN] uDenominator
//          Denominator.
//
//  @return
//      int32.
//-------------------------------------------------------------------------------------------------
//
uint64 DP_MNValueGcd(uint64 uNumerator, uint64 uDenominator)
{
  uint64 num1, num2, tmp;

  num1 = uNumerator;
  num2 = uDenominator;
  tmp  = 0;

  while (num2 != 0)
  {
    tmp  = num2;
    num2 = num1 % num2;
    num1 = tmp;
  }

  return num1;
}

//-------------------------------------------------------------------------------------------------
//  DP_MNValueFinder
//
//  @brief
//      Calculates MN Value.
//
//  @params
//      [IN] uSrcRate
//          Source frequency.
//      [IN] Target frequency
//          Source frequency.
//      [OUT] uNumerator
//          Numerator.
//      [OUT] uDenominator
//          Denominator.
//
//  @return
//      int32.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_MNValueFinder(uint64 uSrcRate, uint64 uTargetRate, uint32 *uNumerator, uint32 *uDenominator)
{
  DP_Status eStatus     = DP_STATUS_SUCCESS;
  uint32    num         = 1;
  uint32    den         = 1;
  uint64    gcd;
  uint64    uSrcFreq;
  uint64    uTargetFreq;
  double    error       = 0;

  if ((float)uTargetRate > (2.0 / 3.0*(float)uSrcRate))
  {
    DP_LOG_MESSAGE_ERROR("DP_MNValueFinder: Target Clock frequency (%lu) must be less than 2/3 Source clock frequency (%lu) in Dual-edge mode\n", (uint32)uTargetRate, (uint32)uSrcRate);
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    uSrcFreq    = (uint64)(uSrcRate    * 1000000);
    uTargetFreq = (uint64)(uTargetRate * 1000000);

    gcd         = DP_MNValueGcd(uTargetFreq, uSrcFreq);
    num         = (uint32)(uTargetFreq / gcd);
    den         = (uint32)(uSrcFreq / gcd);

    DP_MNValueSearch(&num, &den);
    
    // Ensure we M/N is within 16bits, force an exhaustive search if it is not.
    if ((num > MAX_16BITS_VALUE) || 
        (den > MAX_16BITS_VALUE))
    {
      error = 1.0e100;
    }
    else
    {
      error = (double)uTargetFreq - ((double)uSrcFreq * (double)num / (double)den);
    }
    
    if (error != 0)
    {
      DP_MNExhaustiveSearch(&num, &den, &error);
    }
    
    DP_LOG_MESSAGE_INFO("DP_MNValueFinder: M=%d N=%d Error = %d\n", num, den, Round(error));

    *uNumerator   = num;
    *uDenominator = den;
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_MNDFinder
//
//  @brief
//      only support 16 bits of M, N and D.
//
//  @params
//      [IN/OUT] sMNDCfg
//          MND config.
//
//  @return
//      int32.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_MNDFinder(DP_MNDType *sMNDCfg)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;
  uint32    uNVal;
  uint32    uMVal;

  if (DP_STATUS_SUCCESS != (eStatus = DP_MNValueFinder(sMNDCfg->uSrcRate, sMNDCfg->uTargetRate, &uMVal, &uNVal)))
  {
    DP_LOG_MESSAGE_ERROR("DP_MNDFinder: Can NOT find correct M,N and D\n");
  }
  else
  {
    sMNDCfg->uMVal       = uMVal;
    sMNDCfg->uNVal       = uNVal;
    sMNDCfg->uDVal       = uNVal / 2;
    sMNDCfg->uNotNMinusM = (~(uNVal - uMVal)) & 0xffff;
    sMNDCfg->uNot2D      = (~uNVal) & 0xffff;
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  dp_app_sst_tu_calc
//
//  @brief
//      function to calculate TU taken from VI code
//
//  @params
//         [in] i_lclk                    - link clock freq in MHz - if fec is enabled scale this accordingly
//         [in] i_pclk                    - pixel clock freq in MHz (not div2)
//         [in] i_dwidth                  - display width (not div2)
//         [in] i_hbp                     - horizontal blanking (not div2)
//         [in] i_nlanes                  - number of lanes (1/2/4)
//         [in] i_bpp                     - bpp (18/24/30). Always 24bpp for DSC.
//         [in] i_pixel_enc               - pixel encoding (420/422/444)
//         [in] i_dsc_en                  - dsc enabled (0/1)
//         [in] i_async_en                - async mode enabled (0/1)
//         [in] i_rb2                     - is RB2 resolution (0/1)
//         [in] i_fec_en                  - is FEC enabled(0/1)
//         [in] actual_pclk               - orig_pclk_with_ssc real hw freq
//         [in] actual_lclk               - with ssc but no fec
//         [in] orig_lwidth               - original width of the mode without DSC adjustment
//         [in] orig_hbp                  - original horizontal blanking period of the mode without DSC adjustment
//        [out] o_valid_boundary_link     - valid boundarylink
//        [out] o_delay_start_link        - delay start link
//        [out] o_tu_size_minus1          - TU Size minus 1 value
//        [out] o_boundary_moderation_en  - boundary moderation enabled
//        [out] o_upper_boundary_count    - upper boundary count
//        [out] o_lower_boundary_count    - lower boundary count
//        [out] o_valid_lower_boundary_link - valid lower boundary link
//        [out] o_be_bs_tol               
//        [out] o_tu_size_desired          - TU size
//        [out] o_ratio_by_tu
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
//
DP_Status dp_app_sst_tu_calc(
                             double  i_lclk,      // link clock freq in MHz - if fec is enabled, scale this accordingly
                             double  i_pclk,      // pixel clock freq in MHz (not div2)
                             double  i_dwidth,    // display width (not div2)
                             double  i_hbp,       // horizontal blanking (not div2)
                             int     i_nlanes,    // number of lanes (1/2/4)
                             int     i_bpp,       // bpp (18/24/30). Always 24bpp for DSC.
                             int     i_pixel_enc, // pixel encoding (420/422/444)
                             int     i_dsc_en,    // dsc enabled (0/1)
                             int     i_async_en,  // async mode enabled (0/1)
                             int     i_rb2,       // is RB2 resolution? (0/1)
                             int     i_fec_en,
                             double  actual_pclk, /*orig_pclk_with_ssc, real hw freq*/
                             double  actual_lclk,  /*with ssc, but no fec */
                             int     orig_lwidth,
                             int     orig_hbp,
                             int*    o_valid_boundary_link,
                             int*    o_delay_start_link,
                             int*    o_tu_size_minus1,
                             int*    o_boundary_moderation_en,
                             int*    o_upper_boundary_count,
                             int*    o_lower_boundary_count,
                             int*    o_valid_lower_boundary_link,
                             int*    o_be_bs_tol,
                             int*    o_tu_size_desired,
                             double* o_ratio_by_tu)
{
  DP_Status eStatus           = DP_STATUS_SUCCESS;
  double lclk                 = i_lclk;
  double pclk                 = i_pclk;
  double dwidth               = i_dwidth;
  double hbp_relative_to_pclk = i_hbp;
  int    nlanes               = i_nlanes;
  int    bpp                  = i_bpp;
  int    pixelEnc             = i_pixel_enc;
  int    dsc_en               = i_dsc_en;
  int    async_en             = i_async_en;

  // new inputs
  int    DP_BRUTE_FORCE             = 1;
  //int DP_FEATURE_MODERATION_ALLOWED=1;
  double BRUTE_FORCE_THRESHOLD      = 0.1;  
  int    EXTRA_PIXCLK_CYCLE_DELAY   = 4;
  double HBLANK_MARGIN              = 4.0;
  double HBLANK_MARGIN_EXTRA        = 0;  
  double RATIO_SCALE                = 1.001;

  int delay_start_link_extra_pixclk;

  int    extra_buffer_margin        = 0;
  double ratio                      = 0;
  double original_ratio             = 0;
  double err                        = 1000;
  double n_err                      = 0;
  double n_n_err                    = 0;

  int    tu_size                    = 0;
  int    tu_size_desired            = 0;
  int    tu_size_minus1             = 0;
  int    valid_boundary_link        = 0;
  double resulting_valid            = 0;
  double total_valid                = 0;
  double effective_valid            = 0;
  int    n_tus;
  int    n_tus_per_lane;
  int    paired_tus;
  int    remainder_tus;
  int    remainder_tus_upper;
  int    remainder_tus_lower;
  int    extra_bytes;
  int    filler_size;
  //  int lower_filler_size;
  int    delay_start_link;

  int    extra_pclk_cycles;
  int    extra_pclk_cycles_in_link_clk;
  //  int extra_required_bytes_new;
  double ratio_by_tu;
  double average_valid2;
  int    new_valid_boundary_link;
  int    remainder_symbols_exist;
  int    n_symbols;
  double n_remainder_symbols_per_lane;
  double last_partial_tu;

  int    n_tus_incl_last_incomplete_tu;
  int    extra_pclk_cycles_tmp;
  int    extra_pclk_cycles_in_link_clk_tmp;
  int    extra_required_bytes_new_tmp;
  int    filler_size_tmp;
  int    lower_filler_size_tmp;
  int    delay_start_link_tmp;

  int    boundary_moderation_en    = 0;
  int    boundary_mod_lower_err    = 0;
  int    upper_boundary_count      = 0;
  int    lower_boundary_count      = 0;
  int    i_upper_boundary_count    = 0;
  int    i_lower_boundary_count    = 0;
  int    valid_lower_boundary_link = 0;
  int    even_distribution_BF      = 0;
  int    even_distribution_legacy  = 0;
  int    even_distribution         = 0;
  int    hbp_delayStartCheck       = 0;
  int    pre_tu_hw_pipe_delay      = 0;
  int    post_tu_hw_pipe_delay     = 0;
  int    link_config_hactive_time  = 0;
  int    delay_start_link_lclk     = 0;
  int    tu_active_cycles          = 0;
  double parity_symbols            = 0.0;
  int    resolution_line_time      = 0;
  double temp                      = 0.0;
  double last_partial_lclk         = 0.0;
  int    min_hblank_violated       = 0;
  double delay_start_time          = 0;
  double hbp_time                  = 0;
  double hdisplay_time             = 0;
  int    be_bs_tol;
  double diff_abs;
  int    second_loop_set           = 0;
  
  double LCLK_FAST_SKEW            = 0.0006; // 600ppm

  if (pixelEnc == 420)
  {
    pclk                 /= 2;
    dwidth               /= 2;
    hbp_relative_to_pclk /= 2;
  }

  if (pixelEnc == 422)
  {
    switch (bpp)
    {
    case 24: bpp = 16; break;
    case 30: bpp = 20; break;
    default: bpp = 16; break;
    }
  }

  extra_buffer_margin = (int)DP_Ceil(EXTRA_PIXCLK_CYCLE_DELAY * lclk / pclk);
  ratio               = pclk * bpp / 8 / nlanes / lclk;
  original_ratio      = ratio;

  boundary_moderation_en    = 0;
  upper_boundary_count      = 0;
  lower_boundary_count      = 0;
  i_upper_boundary_count    = 0;
  i_lower_boundary_count    = 0;
  valid_lower_boundary_link = 0;
  even_distribution_BF      = 0;
  even_distribution_legacy  = 0;
  even_distribution         = 0;
  hbp_delayStartCheck       = 0;
  delay_start_time          = 0;

  err     = 1000;
  n_err   = 0;
  n_n_err = 0;

  // To deal with cases where lines are not distributable, no need to deal with it for DSC since pclk used to derive ratio has already accounted for evenly distributed "dsc_bytes per line" from dp_app_get_dsc_timing
  if ((((int)dwidth % nlanes) != 0) && ratio < 1 && dsc_en == 0)
  {
    ratio = ratio * RATIO_SCALE;
    ratio = ratio < 1 ? ratio : 1;
  }

  if (ratio > 1)
  {
    ratio = 1;
  }

  // adjust margin
  if (HBLANK_MARGIN_EXTRA != 0)
  {
    HBLANK_MARGIN += HBLANK_MARGIN_EXTRA;
  }

  for (tu_size = 32; tu_size <= 64; tu_size++)
  {
    n_err = DP_Ceil(ratio * tu_size) - ratio * tu_size;
    //printf("Info (dp_app_export.c): ratio=%f, err=%f, n_err=%f\n", ratio, err, n_err);
    if (n_err < err)
    {
      err = n_err;
      tu_size_desired = tu_size;
    }
  }

  tu_size_minus1 = tu_size_desired - 1;

  // valid symbols per TU
  valid_boundary_link      = (int)DP_Ceil(ratio * tu_size_desired);
  n_tus                    = (int)floor(((double)dwidth * (double)bpp / 8) / (double)valid_boundary_link);
  even_distribution_legacy = n_tus % nlanes == 0 ? 1 : 0;

  extra_bytes                   = (int)DP_Ceil(((double)n_tus + 1) * (valid_boundary_link - original_ratio * tu_size_desired));
  extra_pclk_cycles             = (int)DP_Ceil((double)extra_bytes * 8 / bpp);
  extra_pclk_cycles_in_link_clk = (int)DP_Ceil(extra_pclk_cycles * lclk / pclk);
  filler_size                   = (int)DP_Ceil((double)tu_size_desired - (double)valid_boundary_link);
  // Some tests will have invalid filler size here, but will be reprogrammed later
  //if (filler_size < 0)
  //{
  //    api_mdss_error("ERROR:(dp_app_export.c): Invalid filler_size of %d.\n\n", filler_size);
  //}
  ratio_by_tu                   = ratio * tu_size_desired;
  //delay_start_link = ((extra_bytes > extra_pclk_cycles_in_link_clk)?extra_bytes:extra_pclk_cycles_in_link_clk) + filler_size + extra_buffer_margin;
  delay_start_link              = extra_pclk_cycles_in_link_clk + filler_size + extra_buffer_margin;
  resulting_valid               = valid_boundary_link;

  //*****check if hblank is sufficiently large for tu settings
  hbp_time                      = (hbp_relative_to_pclk - HBLANK_MARGIN) / pclk;
  delay_start_time              = (double)delay_start_link / lclk;

  if (hbp_time < delay_start_time)
  {
    min_hblank_violated = 1;
  }
  hdisplay_time = (double)(dwidth) / pclk;
  if (hdisplay_time < delay_start_time)
  {
    min_hblank_violated = 1;
  }

  //**********************************************************

  // brute force
  delay_start_link_extra_pixclk = EXTRA_PIXCLK_CYCLE_DELAY;
  diff_abs                      = resulting_valid - ratio_by_tu;

  if (diff_abs < 0)
  {
    diff_abs *= -1; //diff_abs and err should be same value... we should never had diff_abs being negative
  }

  boundary_mod_lower_err = 0;


  //terms for line time compare - break point method
  /* LHS */
  resolution_line_time  = (int)((orig_lwidth + orig_hbp) / 2 * actual_lclk / actual_pclk);
  //i. pre_tu_hw_pipe_delay
  pre_tu_hw_pipe_delay  = (int)(DP_Ceil(1 * actual_lclk / actual_pclk) + 2)/*cdc fifo write jitter+2*/ + 3 /*pre-delay start cycles*/ + 3 /*post-delay start cycles*/ + 1 /*BE on the link*/;
  //iv. post_tu_hw_pipe_delay
  post_tu_hw_pipe_delay = 4 /*BS_on_the_link*/ + 1 /*BE_next_ren*/;
  n_symbols             = (int)DP_Ceil((double)dwidth * (double)bpp / 8);

  //for the case of no error, check the line time here     
  if (i_rb2 == 1)
  {
    //ii. delay_start_link
    delay_start_link_lclk   = (int)(DP_Ceil(delay_start_time * lclk)); /*in lclk*/
        //iii. tu_active_cycles
    new_valid_boundary_link = valid_boundary_link; // changed this from (int) DP_Ceil(ratio*tu_size) for zero error case
    i_upper_boundary_count  = 1;
    i_lower_boundary_count  = 0;
    average_valid2          = (double)((double)i_upper_boundary_count * new_valid_boundary_link + i_lower_boundary_count * ((double)new_valid_boundary_link - 1)) / ((double)i_upper_boundary_count + i_lower_boundary_count);
    n_tus                   = (int)floor(((double)dwidth * (double)bpp / 8) / (double)average_valid2);
    n_tus_per_lane          = (int)floor(n_tus / nlanes);
    paired_tus              = (int)floor((n_tus_per_lane) / (i_upper_boundary_count + i_lower_boundary_count));
    remainder_tus           = n_tus_per_lane - paired_tus * (i_upper_boundary_count + i_lower_boundary_count); // this should evaluate to 0 for cases with no modulation
    
    if (remainder_tus > i_upper_boundary_count)
    {
      temp = nlanes * ((double)i_upper_boundary_count * new_valid_boundary_link + ((double)remainder_tus - i_upper_boundary_count) * ((double)new_valid_boundary_link - 1));
    }
    else
    {
      temp = (double)nlanes * remainder_tus * new_valid_boundary_link;
    }

    // temp would evaluate to 0 for cases with no modulation
    last_partial_lclk = DP_Ceil(((double)n_symbols - (double)nlanes * paired_tus * ((double)i_upper_boundary_count * new_valid_boundary_link + i_lower_boundary_count * ((double)new_valid_boundary_link - 1)) - temp) / nlanes);

    tu_active_cycles = (int)((n_tus_per_lane * tu_size) + last_partial_lclk);
    //v. partiy_symbols
    if (i_fec_en == 1)
    {
      if (nlanes == 1)
      {
        parity_symbols = DP_Ceil((pre_tu_hw_pipe_delay + delay_start_link_lclk + tu_active_cycles + post_tu_hw_pipe_delay) / 500) * 12 + 1 /*PM*/;
      }
      else
      {
        parity_symbols = DP_Ceil((pre_tu_hw_pipe_delay + delay_start_link_lclk + tu_active_cycles + post_tu_hw_pipe_delay) / 250) * 6 + 1 /*PM*/;
      }
    }
    else  //no fec BW impact
    {
      parity_symbols = 0;
    }

    link_config_hactive_time = (int)(pre_tu_hw_pipe_delay + delay_start_link_lclk + tu_active_cycles + post_tu_hw_pipe_delay + parity_symbols);

    //compare terms  
    if (link_config_hactive_time + 4 /*margin*/ >= resolution_line_time)
    {
      min_hblank_violated = 1;
    }
  }
  delay_start_time = 0;

  if ((diff_abs != 0 && ((diff_abs > BRUTE_FORCE_THRESHOLD) || (even_distribution_legacy == 0) || (DP_BRUTE_FORCE == 1))) || (min_hblank_violated == 1))
    //if ((diff_abs > BRUTE_FORCE_THRESHOLD) || (even_distribution_legacy == 0) || (DP_BRUTE_FORCE ==1))
  {
    do
    {
      err                 = 1000;
      extra_buffer_margin = (int)DP_Ceil(delay_start_link_extra_pixclk * lclk / pclk);
      n_symbols           = (int)DP_Ceil((double)dwidth * (double)bpp / 8);

      for (tu_size = 32; tu_size <= 64; tu_size++)
      {
        for (i_upper_boundary_count = 1; i_upper_boundary_count <= 15; i_upper_boundary_count++)
        {
          for (i_lower_boundary_count = 1; i_lower_boundary_count <= 15; i_lower_boundary_count++)
          {
            new_valid_boundary_link      = (int)DP_Ceil(ratio * tu_size);
            average_valid2               = (double)((double)i_upper_boundary_count * new_valid_boundary_link + i_lower_boundary_count * ((double)new_valid_boundary_link - 1)) / ((double)i_upper_boundary_count + i_lower_boundary_count);
            n_tus                        = (int)floor(((double)dwidth * (double)bpp / 8) / (double)average_valid2);
            n_remainder_symbols_per_lane = (n_symbols - n_tus * average_valid2) / nlanes;
            last_partial_tu              = ((double)n_remainder_symbols_per_lane) / tu_size;

            if (n_remainder_symbols_per_lane != 0)
            {
              remainder_symbols_exist = 1;
            }
            else 
            {
              remainder_symbols_exist = 0;
            }

            n_tus_per_lane = (int)floor(n_tus / nlanes);
            paired_tus     = (int)floor((n_tus_per_lane) / (i_upper_boundary_count + i_lower_boundary_count));
            remainder_tus  = n_tus_per_lane - paired_tus * (i_upper_boundary_count + i_lower_boundary_count);

            if ((remainder_tus - i_upper_boundary_count) > 0)
            {
              remainder_tus_upper = i_upper_boundary_count;
              remainder_tus_lower = remainder_tus - i_upper_boundary_count;
            }
            else
            {
              remainder_tus_upper = remainder_tus;
              remainder_tus_lower = 0;
            }

            total_valid       = (double)paired_tus * ((double)i_upper_boundary_count * new_valid_boundary_link + i_lower_boundary_count * ((double)new_valid_boundary_link - 1)) + ((double)remainder_tus_upper * new_valid_boundary_link) + (remainder_tus_lower * ((double)new_valid_boundary_link - 1));
            effective_valid   = remainder_symbols_exist ? (total_valid + n_remainder_symbols_per_lane) / (n_tus_per_lane + last_partial_tu) : total_valid / n_tus_per_lane;
            n_n_err           = effective_valid - ratio * tu_size;
            n_err             = average_valid2 - ratio * tu_size;
            even_distribution = n_tus % nlanes == 0 ? 1 : 0;
            ///////////////////////////////////////////////
            //check if hporch is < delay_start
            ///////////////////////////////////////////////
            n_tus_incl_last_incomplete_tu     = (int)DP_Ceil(((double)dwidth * (double)bpp / 8) / (double)average_valid2);
            // err from 1st set for upper TUs + the rest of the lower+upper seq of TU which share average_valid2. 
            // the 1st set of upper TUs have not prior lower set of TU to reduce the extra required bytes
            extra_required_bytes_new_tmp      = (int)DP_Ceil(n_tus_incl_last_incomplete_tu * (average_valid2 - original_ratio * tu_size)) +
                                                (int)DP_Ceil(i_upper_boundary_count * (new_valid_boundary_link - original_ratio * tu_size) * nlanes); 
            extra_pclk_cycles_tmp             = (int)DP_Ceil((double)extra_required_bytes_new_tmp * 8 / bpp);
            extra_pclk_cycles_in_link_clk_tmp = (int)DP_Ceil(extra_pclk_cycles_tmp * lclk / pclk);
            filler_size_tmp                   = (int)DP_Ceil((double)tu_size - new_valid_boundary_link);
            lower_filler_size_tmp             = filler_size_tmp + 1;
            //delay_start_link_tmp = (extra_required_bytes_new_tmp>extra_pclk_cycles_in_link_clk_tmp?extra_required_bytes_new_tmp:extra_pclk_cycles_in_link_clk_tmp)+ lower_filler_size_tmp + extra_buffer_margin;
            delay_start_link_tmp              = extra_pclk_cycles_in_link_clk_tmp + lower_filler_size_tmp + extra_buffer_margin;
            delay_start_time                  = (double)delay_start_link_tmp / lclk;
         
            // for rb2, use this check
            if (i_rb2 != 0)
            {
              //i. pre_tu_hw_pipe_delay
              pre_tu_hw_pipe_delay  = (int)((DP_Ceil(1 * actual_lclk / actual_pclk) + 2)/*cdc fifo write jitter+2*/ + 3 /*pre-delay start cycles*/ + 3 /*post-delay start cycles*/ + 1 /*BE on the link*/);
              //ii. delay_start_link
              delay_start_link_lclk = (int)(DP_Ceil(delay_start_time * lclk)); /*in lclk*/
                                  //iii. tu_active_cycles
              if (remainder_tus > i_upper_boundary_count)
              {
                temp = (double)nlanes * ((double)i_upper_boundary_count * new_valid_boundary_link + ((double)remainder_tus - i_upper_boundary_count) * ((double)new_valid_boundary_link - 1));
              }
              else
              {
                temp = (double)nlanes * remainder_tus * new_valid_boundary_link;
              }

              last_partial_lclk     = DP_Ceil(((double)n_symbols - (double)nlanes * (double)paired_tus * ((double)i_upper_boundary_count * new_valid_boundary_link + i_lower_boundary_count * ((double)new_valid_boundary_link - 1)) - temp) / nlanes);
              tu_active_cycles      = (int)((n_tus_per_lane * tu_size) + last_partial_lclk);
              //iv. post_tu_hw_pipe_delay
              post_tu_hw_pipe_delay = 4 /*BS_on_the_link*/ + 1 /*BE_next_ren*/;
              //v. partiy_symbols
              if (i_fec_en == 1)
              {
                if (nlanes == 1)
                {
                  parity_symbols = DP_Ceil((pre_tu_hw_pipe_delay + delay_start_link_lclk + tu_active_cycles + post_tu_hw_pipe_delay) / 500) * 12 + 1 /*PM*/;
                }
                else
                {
                  parity_symbols = DP_Ceil((pre_tu_hw_pipe_delay + delay_start_link_lclk + tu_active_cycles + post_tu_hw_pipe_delay) / 250) * 6 + 1 /*PM*/;
                }
              }
              else  //no fec BW impact
              {
                parity_symbols = 0;
              }

              link_config_hactive_time = (int)(pre_tu_hw_pipe_delay + delay_start_link_lclk + tu_active_cycles + post_tu_hw_pipe_delay + parity_symbols);

              /* LHS */
              resolution_line_time = (int)((orig_lwidth + orig_hbp) / 2 * actual_lclk / actual_pclk);

              //compare terms  
              if (resolution_line_time >= link_config_hactive_time + 1 /*margin*/)
              {
                hbp_delayStartCheck = 1;
              }
              else
              {
                hbp_delayStartCheck = 0;
              }
            }
            else   //non rb2 cases
            {
              if (hbp_time >= delay_start_time)
              {
                hbp_delayStartCheck = 1;
              }
              else
              {
                hbp_delayStartCheck = 0;
              }
            }

            if (((even_distribution == 1) || ((even_distribution_BF == 0) && (even_distribution_legacy == 0))) && n_err >= 0 && n_n_err >= 0 && n_n_err < err && (n_n_err < diff_abs || (min_hblank_violated == 1)) && (new_valid_boundary_link - 1) > 0 && (hbp_delayStartCheck == 1) && (delay_start_link_tmp <= 1023))
            {
              upper_boundary_count     = i_upper_boundary_count;
              lower_boundary_count     = i_lower_boundary_count;
              err                      = n_n_err;
              boundary_moderation_en   = 1;
              tu_size_desired          = tu_size;
              valid_boundary_link      = new_valid_boundary_link;
              even_distribution_BF     = 1;
              delay_start_link         = delay_start_link_tmp;
              second_loop_set          = 1;
            }
            else if (boundary_mod_lower_err == 0 && n_n_err < diff_abs)
            {
              boundary_mod_lower_err = 1;
            }
          }
        }
      }
      delay_start_link_extra_pixclk--;
    } while (boundary_moderation_en != 1 && boundary_mod_lower_err == 1 && delay_start_link_extra_pixclk != 0 && ((second_loop_set == 0 && i_rb2 == 1) || i_rb2 == 0)); // dont do this step for RB2 go back and redo BRUTE FORCE with smaller delay margin
    
    if (boundary_moderation_en == 1)
    {
      resulting_valid           = (double)((double)upper_boundary_count * valid_boundary_link + lower_boundary_count * ((double)valid_boundary_link - 1)) / ((double)upper_boundary_count + lower_boundary_count);
      ratio_by_tu               = original_ratio * tu_size_desired;
      valid_lower_boundary_link = valid_boundary_link - 1;
      n_tus                     = (int)floor(((double)dwidth * (double)bpp / 8) / (double)resulting_valid);
      tu_size_minus1            = tu_size_desired - 1;
      even_distribution_BF      = 1;
    }
  }

  delay_start_link += async_en == 1 ? (int)(DP_Ceil(LCLK_FAST_SKEW * dwidth) * ((bpp / 8) / (original_ratio * nlanes))) : 0; // New late change for async mode in PoipuV2.
  delay_start_time = (double)delay_start_link / lclk;

  if (hbp_time < delay_start_time)
  {
    DP_LOG_MESSAGE_WARN("MIN_HBLANK_VIOLATION Programmed h_back_porch is smaller than the delay_start\n");
  }

  if (hdisplay_time < delay_start_time)
  {
    DP_LOG_MESSAGE_ERROR("MIN_HACTIVE_VIOLATION Programmed h_display time is smaller than the delay_start\n");    
    eStatus = DP_STATUS_FAIL;
  }

  be_bs_tol = (int)(n_tus / nlanes * 0.1);

  // OUTPUTS

  *o_valid_boundary_link       = valid_boundary_link;
  *o_delay_start_link          = delay_start_link;
  *o_tu_size_minus1            = tu_size_minus1;
  *o_boundary_moderation_en    = boundary_moderation_en;
  *o_upper_boundary_count      = upper_boundary_count;
  *o_lower_boundary_count      = lower_boundary_count;
  *o_valid_lower_boundary_link = valid_lower_boundary_link;
  *o_be_bs_tol                 = be_bs_tol;
  *o_tu_size_desired           = tu_size_desired;
  *o_ratio_by_tu               = ratio_by_tu;

  return eStatus;
}


//-------------------------------------------------------------------------------------------------
//  DP_CalculateTU
//
//  @brief
//      This function will calculate the TU based the the lane #, link clock, 
//      pixel clock, color format.
//
//  @params
//      [IN] psDisplayInfo
//          Display config parameters.
//      [OUT] psTUConfig
//          Calculated TU parameters.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_CalculateTU(DP_TUSizeCalcParamType          *psDisplayInfo,
                          HAL_DP_TUConfigType             *psTUConfig)
{
  DP_Status eStatus     = DP_STATUS_SUCCESS;
  double    lclk        = psDisplayInfo->dLinkClockInMhz;
  double    pclk        = psDisplayInfo->dPixelClockInMhz;
  double    actual_pclk = psDisplayInfo->dActualPixelClk;
  double    dwidth      = psDisplayInfo->uWidth;
  int       nlanes      = psDisplayInfo->uNumberOfLanes;
  int       bpp         = psDisplayInfo->uBPP;

  if ((0 == lclk)        ||
      (0 == pclk)        ||
      (0 == actual_pclk) ||
      (0 == dwidth)      ||
      (0 == nlanes)      ||
      (0 == bpp))
  {
    TraceInfo(QdiTraceDP, "DP_CalculateTU: Invalid Input(s) lclk: %f, pclk: %f, actual_pclk: %f, dwidth: %f, nlanes: %d, bpp: %d", 
                          lclk, 
                          pclk, 
                          actual_pclk, 
                          dwidth, 
                          nlanes, 
                          bpp);
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    double    actual_lclk               = psDisplayInfo->dActualLinkClk;
    double    hbp_relative_to_pclk      = psDisplayInfo->dHBlankPeriod;
    int       i_rb2                     = psDisplayInfo->bRB2Timing ? 1 : 0;
    int       orig_lwidth               = psDisplayInfo->uOriginalWidth;
    int       orig_hbp                  = psDisplayInfo->uOriginalhbp;
    int       dsc_en                    = psDisplayInfo->bDSCEnabled? 1 : 0;
    int       async_en                  = psDisplayInfo->bSynchronousClk ? 0 : 1;
    int       i_fec_en                  = psDisplayInfo->bFECEnabled ? 1 : 0;
    int       pixelEnc                  = 0;
    int       tu_size_desired           = 0;
    int       tu_size_minus1            = 0;
    int       valid_boundary_link       = 0;
    int       boundary_moderation_en    = 0;
    int       upper_boundary_count      = 0;
    int       lower_boundary_count      = 0;
    int       valid_lower_boundary_link = 0;
    int       delay_start_link          = 0;
    int       be_bs_tol                 = 0;
    double    ratio_by_tu               = 0;

    if (HAL_DP_PIXELFORMAT_TYPE_YUV420 == psDisplayInfo->ePixelFormat)
    {
      pixelEnc = 420;
    }
    else if (HAL_DP_PIXELFORMAT_TYPE_YUV422 == psDisplayInfo->ePixelFormat)
    {
      pixelEnc = 422;
    }
    
    eStatus = dp_app_sst_tu_calc(lclk,
                                pclk, 
                                dwidth,
                                hbp_relative_to_pclk,
                                nlanes,
                                bpp,
                                pixelEnc,
                                dsc_en,
                                async_en,
                                i_rb2,
                                i_fec_en,
                                actual_pclk,
                                actual_lclk,
                                orig_lwidth,
                                orig_hbp,
                                &valid_boundary_link,
                                &delay_start_link,
                                &tu_size_minus1,
                                &boundary_moderation_en,    
                                &upper_boundary_count,
                                &lower_boundary_count,
                                &valid_lower_boundary_link,
                                &be_bs_tol,
                                &tu_size_desired,
                                &ratio_by_tu);

    // Low bandwidth consumption scenarios may result in SST TU transport having to run with empty TUs, which DP controller cannot support / not recommended
    // This check will be absorbed by TU calulator in the future, so remove this check then (WINDISPLAY-420)
    if ((0 != tu_size_desired) &&
        (ratio_by_tu / tu_size_desired) < 0.015625)
    {
      DP_LOG_MESSAGE_WARN("DP_CalculateTU: Empty TU / low link bandwidth consumption scenario!\n");
    }

    psTUConfig->uTuSize             = (uint32)tu_size_desired;
    psTUConfig->uDelayStartLink     = (uint32)delay_start_link;
    psTUConfig->bBoundaryModEnable  = boundary_moderation_en != 0 ? TRUE : FALSE;
    psTUConfig->uValidBoundaryLink  = (uint32)valid_boundary_link;
    psTUConfig->uValidLowerBoundary = (uint32)valid_lower_boundary_link;
    psTUConfig->uLowerBoundaryCount = (uint32)lower_boundary_count;
    psTUConfig->uUpperBoundaryCount = (uint32)upper_boundary_count;
    psTUConfig->dRatioByTU          = ratio_by_tu;

    TraceInfo(QdiTraceDP,
              "DP%i: TU input parameters uWidth: %d, dPixelClockInMhz: %f, dLinkClockInMhz: %f, dHBlankPeriod: %f, uNumberOfLanes: %d",
              psDisplayInfo->eDisplayId,
              psDisplayInfo->uWidth,
              psDisplayInfo->dPixelClockInMhz,
              psDisplayInfo->dLinkClockInMhz,
              psDisplayInfo->dHBlankPeriod,
              psDisplayInfo->uNumberOfLanes);
    TraceInfo(QdiTraceDP,
              "DP%i: TU input parameters uBPP: %d, ePixelFormat: %d, bSynchronousClk: %d, bDSCEnabled: %d, bFECEnabled: %d, bRB2Timing: %d",
              psDisplayInfo->eDisplayId,
              psDisplayInfo->uBPP,
              psDisplayInfo->ePixelFormat,
              psDisplayInfo->bSynchronousClk,
              psDisplayInfo->bDSCEnabled,
              psDisplayInfo->bFECEnabled,
              psDisplayInfo->bRB2Timing);
    TraceInfo(QdiTraceDP,
              "DP%i: TU input parameters dActualPixelClk: %f, dActualLinkClk: %f, uOriginalWidth: %d, uOriginalhbp: %d",
              psDisplayInfo->eDisplayId,
              psDisplayInfo->dActualPixelClk,
              psDisplayInfo->dActualLinkClk,
              psDisplayInfo->uOriginalWidth,
              psDisplayInfo->uOriginalhbp);
    TraceInfo(QdiTraceDP,
              "DP%i: TU output parameters uTuSize: %d uDelayStartLink: %d bBoundaryModEnable:%d uValidBoundaryLink:%d",
              psDisplayInfo->eDisplayId,
              psTUConfig->uTuSize,
              psTUConfig->uDelayStartLink,
              psTUConfig->bBoundaryModEnable,
              psTUConfig->uValidBoundaryLink);
    TraceInfo(QdiTraceDP,
              "DP%i: TU output parameters uValidLowerBoundary: %d uLowerBoundaryCount: %d uUpperBoundaryCount: %d dRatioByTU: %f",
              psDisplayInfo->eDisplayId,
              psTUConfig->uValidLowerBoundary,
              psTUConfig->uLowerBoundaryCount,
              psTUConfig->uUpperBoundaryCount,
              psTUConfig->dRatioByTU);
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_CalculateRG
//
//  @brief
//      Use link rate, pclk, link count to calculate rate governor for MST.
//
//  @params
//      [IN] psDisplayInfo
//          Display config parameters.
//      [OUT] psRGConfig
//          Calculated RG parameters.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_CalculateRG(DP_RGCalcParamType *psDisplayInfo,
                          HAL_DP_RGConfigType *psRGConfig)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if ((NULL == psDisplayInfo) || 
      (NULL == psRGConfig))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if ((0   == psDisplayInfo->uNumberOfLanes) || 
           (0.0 == psDisplayInfo->dLinkClockInMhz))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    double dLanes              = psDisplayInfo->uNumberOfLanes;
    double dLinkRate           = dLanes * psDisplayInfo->dLinkClockInMhz; // in MHz
    double dPeakPixelBW        = ((double)(psDisplayInfo->uPixelClockInKhz) * (double)(psDisplayInfo->uBPP)) / (8.0 * 1000.0); // in MBps
    double dPBN                = 0;
    double dRawTargetSlotCount = 0;
    double dDSCOverhead        = 0;

    if (TRUE == psDisplayInfo->bYUV420)
    {
      // For YUV420 formats the pixel clock is halved.
      // But RG calculation requires full pixel clk
      // dPeakPixelBW = uPixelClk * BPP * 2 / (8 * 1000)
      dPeakPixelBW = dPeakPixelBW * 2.0;
    }

    // Minimum number of time slots per MTP for this pclk in floating point
    psRGConfig->dMinSlotCount = (dPeakPixelBW * DP_MST_SLOTS_PER_MTP) / (dLinkRate);
    // PBN in floating point
    dPBN                      = dPeakPixelBW * DP_MST_SLOTS_PER_MTP * DP_MST_PBN_MARGIN / DP_MST_PBN_UNIT_NUMERATOR;
    psRGConfig->uPBN          = DP_Ceil(dPBN);
    // Maximum number of time slots the stream could use
    psRGConfig->dMaxSlotCount = (double)psRGConfig->uPBN * DP_MST_PBN_UNIT_NUMERATOR / dLinkRate;
    // Raw chosen target slot
    dRawTargetSlotCount       = (psRGConfig->dMinSlotCount + psRGConfig->dMaxSlotCount) / 2.0;

    dPBN                      = psRGConfig->uPBN;
    
    if (TRUE == psDisplayInfo->bDSCEnabled)
    {
      dDSCOverhead         = psDisplayInfo->fDSCOverHead;
      dPBN                 = dPBN * dDSCOverhead;
      dRawTargetSlotCount  = dRawTargetSlotCount * dDSCOverhead;
    }

    if (TRUE == psDisplayInfo->bFECEnabled)
    {
      dPBN                 = dPBN / DP_LINKRATE_FEC_OVERHEAD_RATIO;
      dRawTargetSlotCount  = dRawTargetSlotCount / DP_LINKRATE_FEC_OVERHEAD_RATIO;
    }


    // FP representation of chosen target slot count
    psRGConfig->dChosenSlotCount = Round(dRawTargetSlotCount * 256.0 * dLanes) / (256.0 * dLanes);
    // Integer representation of chosen target slot count
    psRGConfig->uTS_INT_PLUS1    = DP_Ceil(psRGConfig->dChosenSlotCount);
    // Total target average time slots per MTP (integer part)
    psRGConfig->uX_INT           = (uint32)(dLanes * psRGConfig->dChosenSlotCount);
    // Total target average time slots per MTP (fraction part)
    psRGConfig->uY_FRAC_ENUM     = (uint32)(256*((dLanes * psRGConfig->dChosenSlotCount) - psRGConfig->uX_INT));

    psRGConfig->uPBN             = DP_Ceil(dPBN);

    // Calculate number of time slots
    psRGConfig->uSlotCount       = psRGConfig->uTS_INT_PLUS1;

    TraceInfo(QdiTraceDP,
              "DP%i: RG input parameters uVisWidth: %d, uPixelClockInKhz: %u, dLinkClockInMhz: %f, uNumberOfLanes: %d",
              psDisplayInfo->eDisplayId,
              psDisplayInfo->uVisWidth,
              psDisplayInfo->uPixelClockInKhz,
              psDisplayInfo->dLinkClockInMhz,
              psDisplayInfo->uNumberOfLanes);
    TraceInfo(QdiTraceDP,
              "DP%i: RG input parameters uBPP: %d, bYUV420: %d, bSynchronousClk:%d, bDSCEnabled: %d, bFECEnabled: %d fDSCOverHead: %f",
              psDisplayInfo->eDisplayId,
              psDisplayInfo->uBPP,
              psDisplayInfo->bYUV420,
              psDisplayInfo->bSynchronousClk,
              psDisplayInfo->bDSCEnabled,
              psDisplayInfo->bFECEnabled,
              psDisplayInfo->fDSCOverHead);
    TraceInfo(QdiTraceDP,
              "DP%i: RG output parameters dMinSlotCount: %f uPBN: %d dMaxSlotCount: %f dChosenSlotCount: %f",
              psDisplayInfo->eDisplayId,
              psRGConfig->dMinSlotCount,
              psRGConfig->uPBN,
              psRGConfig->dMaxSlotCount,
              psRGConfig->dChosenSlotCount);
    TraceInfo(QdiTraceDP,
              "DP%i: RG output parameters uTS_INT_PLUS1: %d uY_FRAC_ENUM: %d uX_INT: %d uSlotCount: %d",
              psDisplayInfo->eDisplayId,
              psRGConfig->uTS_INT_PLUS1,
              psRGConfig->uY_FRAC_ENUM,
              psRGConfig->uX_INT,
              psRGConfig->uSlotCount);    
  }

  return eStatus;
}
                          
//-------------------------------------------------------------------------------------------------
//  DP_CalculateLink
//
//  @brief
//      This function will Calculate the Link settings, such as clock freq, number of lane needed.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] psDPCDSinkCap
//          Pointer to sink DPCD capabilitess.
//      [IN] psPanelInfo
//          Pointer to panel info corresponding to current mode.
//      [OUT] pPixClkInfo
//          Pointer to pixel clock info (dividers, etc.).
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_CalculateLink(DP_DisplayCtxType        *pDisplayCtx,
                            DP_DPCDSinkCapType       *psDPCDSinkCap,
                            DP_PanelInfoType         *psPanelInfo,
                            DP_PixelClk_Info         *pPixClkInfo)
{
  DP_Status             eStatus         = DP_STATUS_SUCCESS;
  DP_DeviceCtxType     *pDeviceCtx      = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType     *pStreamCtx      = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  uint32                uLinkRate       = 0;
  uint32                uInputClk       = 0;
  uint32                uNvidFactor     = 1;
  uint32                uPclkRate;
  DP_MNDType            sMNDCfg;

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_CalculateLink: unexpected null context.");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    HAL_DP_PhyClksFreqCalcParams sPhyClkCalcParams;

    /* Convert from Khz to Mbps */
    sPhyClkCalcParams.uLinkRateMbps = (pDeviceCtx->uLinkRateInKhz / 1000) * DP_LINK_SYMBOL_SIZE;

    if (HAL_MDSS_STATUS_SUCCESS != HAL_DP_PHY_GetCalcPhyClksFreq(pDeviceCtx->eDeviceID, &sPhyClkCalcParams))
    {
      DP_LOG_MESSAGE_ERROR("Invalid link rate %d KHz", pDeviceCtx->uLinkRateInKhz);
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
      goto exit;
    }

    uLinkRate = pDeviceCtx->uLinkRateInKhz;
    uInputClk = sPhyClkCalcParams.uVcoDivClkFreqMHz;

    DP_LOG_MESSAGE_INFO("uLinkRate=%d uInputClk=%d uNvidFactor=%d\n", uLinkRate, uInputClk, uNvidFactor);

    /* Use pixel clock from EDID, standard pixel clock should give 0-error MND value*/
    uPclkRate = psPanelInfo->uPclkFreq;

    if (pDeviceCtx->bDualPixelMode)
    {
      /* Use 2 pixels per clock mode for all DP interfaces */
      uPclkRate >>= 1;
    }

    sMNDCfg.uSrcRate    = (uint64)uInputClk * 1000000;
    sMNDCfg.uTargetRate = uPclkRate;

    if ((DP_STATUS_SUCCESS != (eStatus = DP_MNDFinder(&sMNDCfg))) &&
        (0 != sMNDCfg.uNVal))
    {
      DP_LOG_MESSAGE_ERROR("Cannot find the correct frequency!, expecting %d%d Hz",(uint32)(sMNDCfg.uTargetRate>>32), (uint32)(sMNDCfg.uTargetRate & 0xFFFFFFFF));
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    }
    else
    {
      /* If lane number is not set by set_property call, use the max lane number from DPCD, 
      so that there is enough bandwidth left to reduce link rate if link training failed. */
      pDeviceCtx->uNumLanes                  = (0 == pDeviceCtx->uNumLanes) ? psDPCDSinkCap->uMaxLaneCount : pDeviceCtx->uNumLanes;;
      pDeviceCtx->uLinkRateInKhz             =  uLinkRate;
      pStreamCtx->uPixelClkInKhz             =  psPanelInfo->uPclkFreq / 1000;

      pPixClkInfo->uPixelClkMNDInputMhz      =  uInputClk;
      pPixClkInfo->uPixelClk_M               =  sMNDCfg.uMVal;
      pPixClkInfo->uPixelClk_N               =  sMNDCfg.uNVal;
      pPixClkInfo->uPixelClk_2D              =  sMNDCfg.uDVal;
      pPixClkInfo->uPixelDivider             =  1;
      pPixClkInfo->dActualPixelClkMHz        =  (uInputClk * sMNDCfg.uMVal) / sMNDCfg.uNVal;
      pPixClkInfo->dActualLinkClkMHz         =  pDeviceCtx->uLinkRateInKhz / 1000;

      if (pDeviceCtx->bDualPixelMode)
      {
        pPixClkInfo->dActualPixelClkMHz     *= 2;
      }

      if (pDeviceCtx->bSynchronousClk)
      {
        /* Mvid/Nvid = PixelClk/LinkFreq . In sync mode, we have pixel_clk = (link * 5 * M)/ (uPreDiv * N) */
        uint32 uSWMvid = sMNDCfg.uMVal * 5;
        uint32 uSWNvid;

        /* Coefficient from VI to simplify SW_NVID calculation:
         * SW_MVID / SW_NVID   = pclk_freq/lclk_freq
         * SW_NVID             = SW_MVID * lclk_freq / pclk_freq
         * pclk_freq           = M * pclk_src_freq / N
         * SW_MVID             = 5 * M;
         * SW_NVID             = (5 * lclk_freq / pclk_src_freq) * N
         * SW_NVID             = uNvidFactor * N
         * TODO: WINDISPLAY-398 - Update calculation / comment for this
         * coefficient based on HW team HPG update.
         */
        uNvidFactor = DPHOST_ROUND(((float)(5 * uLinkRate)) / ((float)(uInputClk * 1000))); 
        uSWNvid     = sMNDCfg.uNVal * uNvidFactor;

        /* Scale up SW_Nvid to 0x8000 for better interop with all monitors(including VGA dongles), without lose of accuracy 
           Formula from system team:
            If (Old_SW_NVID < 0x8000)
            {
              new SW_NVID = Floor(0x8000/Old_SW_NVID) * Old_SW_NVID;
              new SW_MVID = Floor(0x8000/Old_SW_NVID) * Old_SW_MVID;
            }
            Else
            {
              new SW_NVID = Old_SW_NVID;
              new SW_MVID = Old_SW_MVID;
            } 
        */

        if (uSWNvid < DP_LINK_NVID_THRESHOLD)
        {
          pPixClkInfo->uSWMvid = ((uint32)(DP_LINK_NVID_THRESHOLD / uSWNvid)) * uSWMvid;
          pPixClkInfo->uSWNvid = ((uint32)(DP_LINK_NVID_THRESHOLD / uSWNvid)) * uSWNvid;
        }
        else
        {
          pPixClkInfo->uSWMvid = uSWMvid;
          pPixClkInfo->uSWNvid = uSWNvid;
        }

      }
      else
      {
        // MVID Should be set dynamically from HW when clock is sourced asynchronously
        pPixClkInfo->uSWNvid = DP_LINK_NVID_THRESHOLD;
        pPixClkInfo->uSWMvid = 0;
      }

      TraceInfo(QdiTraceDP, "DP%d: Link Settings - uLinkRate=%d, VCODivClk=%d\n",
                             pDeviceCtx->eDisplayID,
                             uLinkRate,
                             uInputClk);

      TraceInfo(QdiTraceDP, "DP%d: Link Settings - uMVal=%d, uNVal=%d, uDVal=%d\n",
                             pDeviceCtx->eDisplayID,
                             pPixClkInfo->uPixelClk_M,
                             pPixClkInfo->uPixelClk_N,
                             pPixClkInfo->uPixelClk_2D);

      TraceInfo(QdiTraceDP, "DP%d: Link Settings - bSynchronousClk=%d, uSWMvid=%d, uSWNvid=%d, uNvidFactor=%d\n",
                             pDeviceCtx->eDisplayID,
                             pDeviceCtx->bSynchronousClk,
                             pPixClkInfo->uSWMvid,
                             pPixClkInfo->uSWNvid,
                             uNvidFactor);
    }
  }

exit:
  return eStatus;
}            

//-------------------------------------------------------------------------------------------------
//  DP_CheckTrainingResult
//
//  @brief
//      This function will get the max (among all lanes) drive setting requested by the sink.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] psDPCDSinkStatus
//          Pointer to DPCP sink status.
//      [IN] eTrainingType
//          type of link training done.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
bool32  DP_CheckTrainingResult(DP_DisplayCtxType           *pDisplayCtx,
                               DP_DPCDSinkStatusType       *psDPCDSinkStatus,
                               DP_LinkTrainingStatusType    eTrainingType)
{  
  bool32            bDone       = TRUE;
  DP_DeviceCtxType *pDeviceCtx  = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  uint32            i           = 0;
  
  if (NULL == pDeviceCtx)
  { 
    DP_LOG_MESSAGE_ERROR("DP_CheckTrainingResult: unexpected null context.");
  }
  else
  {
    // 0 lane number means DP link has not been setup yet, no need to check the DPCD status.
    if (0 == pDeviceCtx->uNumLanes)
    {
      bDone = FALSE;
      goto exit;
    }

    if (DP_LINK_TRAINING_STATUS_CLK_RECOVERY_DONE & eTrainingType)
    {
      for (i = 0; i< pDeviceCtx->uNumLanes; ++i)
      {
        if (0 == (psDPCDSinkStatus->eLaneStatus[i] & DP_DPCD_LANE_STATUS_CR_DONE))
        {
          bDone = FALSE;
          goto exit;
        }
      }
    }

    if (DP_LINK_TRAINING_STATUS_CHANNEL_EQ_DONE & eTrainingType)
    {
      for (i = 0; i< pDeviceCtx->uNumLanes; ++i)
      {
        if (0 == (psDPCDSinkStatus->eLaneStatus[i] & DP_DPCD_LANE_STATUS_CHANNEL_EQ_DONE))
        {
          bDone = FALSE;
          goto exit;
        }
      }
    }

    if (DP_LINK_TRAINING_STATUS_SYMBOL_LOCKED & eTrainingType)
    {
      for (i = 0; i< pDeviceCtx->uNumLanes; ++i)
      {
        if (0 == (psDPCDSinkStatus->eLaneStatus[i] & DP_DPCD_LANE_STATUS_SYMBOL_LOCKED))
        {
          bDone = FALSE;
          goto exit;
        }
      }
    }

    if (DP_LINK_TRAINING_STATUS_INTERLANE_ALIGN_DONE & eTrainingType)
    {  
      if (0 == (psDPCDSinkStatus->eLinkStatusBitArray & DP_DPCD_BIT_STATUS_INTERLANE_ALIGN_DONE))
      {
        bDone = FALSE;
        goto exit;
      }
    }
  } 

exit:

  return bDone;
}

//-------------------------------------------------------------------------------------------------
//  DP_GetMaxSinkPeSwRequest
//
//  @brief
//      This function will get the max (among all lanes) drive setting requested by the sink.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] psDPCDSinkStatus
//          Pointer to DPCP sink status.
//      [OUT] uVoltSwingLvl
//          max Voltage swing level requested.
//      [OUT] uPreemphLvl
//          max Pre-emphasis level requested.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
static void DP_GetMaxSinkPeSwRequest(DP_DisplayCtxType               *pDisplayCtx,
                                     DP_DPCDSinkStatusType           *psDPCDSinkStatus, 
                                     uint32                          *uVoltSwingLvl,
                                     uint32                          *uPreemphLvl)
{
  DP_DeviceCtxType  *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    DP_LOG_MESSAGE_ERROR("DP_GetMaxSinkPeSwRequest: Unexpected null context.");
  }
  else
  {
    uint32             i           = 0;
    uint32             uSwLvl      = 0;
    uint32             uPeLvl      = 0;

    /*  We do not support per-lane drive settings.
     *  If sink makes such a request, pick the highest pre-emphasis and swing of all lanes
     */
    
    uSwLvl  = DPCD_SPEC_MIN_VOLTAGE_SWING_LEVEL;
    for (i = 0; i < pDeviceCtx->uNumLanes; i++)
    {
      if (uSwLvl < psDPCDSinkStatus->uVoltageSwingLevel[i])
      {
        uSwLvl = psDPCDSinkStatus->uVoltageSwingLevel[i];
      }
    }
    
    uPeLvl  = DPCD_SPEC_MIN_PRE_EMPHASIS_LEVEL;
    for (i = 0; i< pDeviceCtx->uNumLanes; i++)
    {
      if (uPeLvl < psDPCDSinkStatus->uPreEmphasisLevel[i])
      {
        uPeLvl = psDPCDSinkStatus->uPreEmphasisLevel[i];
      }
    }
    
    *uVoltSwingLvl = uSwLvl;
    *uPreemphLvl   = uPeLvl;
  }
}

//-------------------------------------------------------------------------------------------------
//  DP_LinkSetupPreemphSwing
//
//  @brief
//      This function will set up the nearest possible pre-emphasis / 
//      voltage swing to the requested level .
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] uVoltSwingLvl
//          Voltage swing level to set.
//      [IN] uPreemphasisLvl
//          Pre-emphasis level to set.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
static DP_Status DP_LinkSetupPreemphSwing(DP_DisplayCtxType *pDisplayCtx,
                                          uint32             uVoltSwingLvl,
                                          uint32             uPreemphasisLvl)
{
  DP_Status              eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType      *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_LinkSetupPreemphSwing: Unexpected null context.");
  }
  else
  {
    HAL_DP_PeSwConfigType  sPeSwConfig;

    /* Check if request is outside the limits of DP spec*/
    if (DPCD_SPEC_MAX_VOLTAGE_SWING_LEVEL < uVoltSwingLvl)
    {
      uVoltSwingLvl = DPCD_SPEC_MAX_VOLTAGE_SWING_LEVEL;
    }
    if (DPCD_SPEC_MAX_PRE_EMPHASIS_LEVEL < uPreemphasisLvl)
    {
      uPreemphasisLvl = DPCD_SPEC_MAX_PRE_EMPHASIS_LEVEL;
    }

    sPeSwConfig.uLaneSwingLevel           = uVoltSwingLvl;
    sPeSwConfig.uPreemphasisLevel         = uPreemphasisLvl;
    sPeSwConfig.bPreemphNotSupported      = FALSE;
    sPeSwConfig.bSwingNotsupported        = FALSE;
    sPeSwConfig.uConfigDataLength         = 0;
    sPeSwConfig.uLinkRateKhz              = pDeviceCtx->uLinkRateInKhz;
    
    // uConfigDataLength tells us how to interpret the list 
    if (DP_PREEMPH_VOLSWING_VALUE_LIST_NUM == pDeviceCtx->sPreEmphSwingConfigType.uLength)
    {
      sPeSwConfig.uConfigDataLength = DP_PREEMPH_VOLSWING_VALUE_LIST_NUM;
      DP_OSAL_MemCpy(&sPeSwConfig.aOverrideValueLUT, &pDeviceCtx->sPreEmphSwingConfigType.aValueLUT, sizeof(sPeSwConfig.aOverrideValueLUT));
    }
    else if (DP_PREEMPH_VOLSWING_MULTIPLIER_LIST_NUM == pDeviceCtx->sPreEmphSwingConfigType.uLength)
    {
      sPeSwConfig.uConfigDataLength = DP_PREEMPH_VOLSWING_MULTIPLIER_LIST_NUM;
      DP_OSAL_MemCpy(&sPeSwConfig.aValueMultiplierList, &pDeviceCtx->sPreEmphSwingConfigType.aMultiplierList, sizeof(sPeSwConfig.aValueMultiplierList));
    }

    /* Set the requested or closest possible settings */
    
    while (HAL_MDSS_STATUS_SUCCESS != HAL_DP_SetupPHYPeSwLevel(pDeviceCtx->eDeviceID, pDeviceCtx->eDeviceDPMode, &sPeSwConfig))
    {    
      if ((DPCD_SPEC_MIN_PRE_EMPHASIS_LEVEL  == sPeSwConfig.uPreemphasisLevel) &&
          (DPCD_SPEC_MIN_VOLTAGE_SWING_LEVEL == sPeSwConfig.uLaneSwingLevel))
      {
        // We should never hit this in practice
        DP_LOG_MESSAGE_ERROR("Failed to set lane drv settings\n");
        eStatus = DP_STATUS_FAIL;
        break;
      }
      
      if (sPeSwConfig.bPreemphNotSupported)
      {
       /* pre-emphasis level exceeds our capability - choose the next highest level we support */
        --(sPeSwConfig.uPreemphasisLevel);
      }
      else if (sPeSwConfig.bSwingNotsupported)
      {      
        /* voltage swing level exceeds our capability for this pre-emphasis 
         *     - choose the highest swing we can support at this pre-emphasis level 
         */
        --(sPeSwConfig.uLaneSwingLevel);
      }
      else
      {
        // We should never hit this in practice
        DP_LOG_MESSAGE_ERROR("Hardware failed to set lane drv settings\n");
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
        break;
      }
    }
    
    if (DP_STATUS_SUCCESS == eStatus)
    {
      pDeviceCtx->uVoltageSwingLevel = sPeSwConfig.uLaneSwingLevel;
      pDeviceCtx->uPreEmphasisLevel  = sPeSwConfig.uPreemphasisLevel;
    }
  
    TraceInfo(QdiTraceDP, "DP%i: Lane config - voltage swing:%d(req:%d), pre-emphasis:%d(req:%d), status:0x%x", 
                           pDeviceCtx->eDisplayID,
                           pDeviceCtx->uVoltageSwingLevel, 
                           uVoltSwingLvl,              
                           pDeviceCtx->uPreEmphasisLevel,
                           uPreemphasisLvl,
                           eStatus);
  }
  
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_LinkTraining_ClockRecovery
//
//  @brief
//      This function will do link training with pattern TPS1.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] uFlags
//          Reserved.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_LinkTraining_ClockRecovery(DP_DisplayCtxType  *pDisplayCtx,
                                         DP_FlagsType        uFlags)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ClockRecovery: Unexpected null context.");
  }
  else
  {
    uint32                          uRetries           = MAX_LINK_TRAINING_LOOP;
    uint32                          uVoltSwingLvl      = 0;
    uint32                          uPreemphLvl        = 0;
    uint32                          uPrevVoltSwingLvl  = 0;
    uint32                          uPrevPreemphLvl    = 0;
    DP_DPCDSinkStatusType           sSinkDPCDStatus; 
    
    UNREFERENCED_PARAMETER(uFlags);

    if (DP_STATUS_SUCCESS == eStatus)
    {
      // Start sending Training Pattern 1
      HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN1);
    
      // Inform sink about the Training Pattern we are using
      eStatus  = DP_WriteSinkDPCDTrainingPattern(pDisplayCtx, DP_DPCD_TRAININGPATTERNSET_PATTERN1);
    
      // Start with minimum pre-emphasis & voltage swing  
      DP_LinkSetupPreemphSwing(pDisplayCtx, DPCD_SPEC_MIN_VOLTAGE_SWING_LEVEL, DPCD_SPEC_MIN_PRE_EMPHASIS_LEVEL);
      eStatus = DP_WriteSinkDPCDLevels(pDisplayCtx, DPCD_SPEC_MIN_VOLTAGE_SWING_LEVEL, DPCD_SPEC_MIN_PRE_EMPHASIS_LEVEL);
    }

    if ((DP_STATUS_SUCCESS == eStatus) &&
        (DP_CUSTOM_SINKID_NONE != pDeviceCtx->eCustomSinkType))
    {
      // Disable custom LTTPR intercept for remainder of link training 
      if (DP_STATUS_SUCCESS != (eStatus = DP_EnableCustomLTTPRIntercept(pDisplayCtx, FALSE, pDeviceCtx->eCustomSinkType)))
      {
        DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ClockRecovery: Disable custom LTTPR Intercept failed, eStatus =%d", eStatus);
      }
    }
        
    if (DP_STATUS_SUCCESS == eStatus)
    {
      for(;;)
      {
        /* Wait for a period defined by the DPCD
         * Use Stall for Us order values instead of sleep as some monitors are sensitive to timing
         */
        if (pDeviceCtx->sSinkDPCDCap.uCRTrainingIntervalInUs < 1000)
        {
          DP_OSAL_StallUs(pDeviceCtx->sSinkDPCDCap.uCRTrainingIntervalInUs); 
        }
        else
        {
          DP_OSAL_SleepUs(pDeviceCtx->sSinkDPCDCap.uCRTrainingIntervalInUs);
        }
    
        /* Use stall based read as link training is timing sensitive */
        eStatus = DP_ReadSinkDPCDStatus(pDisplayCtx, &sSinkDPCDStatus, DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG);
        if (DP_STATUS_SUCCESS != eStatus)
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ClockRecovery: Failed to read sink status from DPCD");
          break;
        }
              
        if (TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_CLK_RECOVERY_DONE))
        {       
          // Link Training successful
          TraceInfo(QdiTraceDP, "DP%i: Link training clock recovery successful", pDeviceCtx->eDisplayID);
          break;
        }

        // Get Sink requested pre-emphasis and voltage swing
        DP_GetMaxSinkPeSwRequest(pDisplayCtx, &sSinkDPCDStatus, &uVoltSwingLvl, &uPreemphLvl);

        if (uPrevVoltSwingLvl == pDeviceCtx->uMaxVoltSwingLvl)
        {
          eStatus = DP_STATUS_FAILED_LINK_TRAINING;
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ClockRecovery: DP_LinkSetupPreemphSwing failed, eStatus =%d", eStatus);
          TraceInfo(QdiTraceDP, "DP%i: Link training clock recovery failed: max voltage swing reached", pDeviceCtx->eDisplayID);
          break;
        }
    
        if ((uPrevVoltSwingLvl == uVoltSwingLvl) &&
            (uPrevPreemphLvl   == uPreemphLvl))
        {
          if (--uRetries == 0)
          {
            eStatus = DP_STATUS_FAILED_LINK_TRAINING;
            DP_LOG_MESSAGE_ERROR("Link Training (clock recovery) failed (5 attempts)");
            TraceInfo(QdiTraceDP, "DP%i: Link training clock recovery failed: max attempts with same drive settings", pDeviceCtx->eDisplayID);
            break;
          }
        }
        else
        {
          // Reset loop count
          uRetries = MAX_LINK_TRAINING_LOOP;
          uPrevVoltSwingLvl = uVoltSwingLvl;
          uPrevPreemphLvl   = uPreemphLvl;
        }
    
        // Apply newly requested settings
        if (DP_STATUS_SUCCESS != (eStatus = DP_LinkSetupPreemphSwing(pDisplayCtx, uVoltSwingLvl, uPreemphLvl)))
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ClockRecovery: DP_LinkSetupPreemphSwing failed, eStatus =%d", eStatus);
          break;
        }
        else if ((DP_CUSTOM_SINKID_NONE != pDeviceCtx->eCustomSinkType) &&
                 (DP_STATUS_SUCCESS != (eStatus = DP_WriteCustomLTTPRDPCDLevels(pDisplayCtx,
                                                                                pDeviceCtx->uVoltageSwingLevel,
                                                                                pDeviceCtx->uPreEmphasisLevel,
                                                                                pDeviceCtx->eCustomSinkType))))
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ClockRecovery: DP_WriteCustomLTTPRDPCDLevels failed, eStatus =%d", eStatus);
          break;
        }
        else if(DP_STATUS_SUCCESS != (eStatus = DP_WriteSinkDPCDLevels(pDisplayCtx, pDeviceCtx->uVoltageSwingLevel, pDeviceCtx->uPreEmphasisLevel)))
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ClockRecovery: DP_WriteSinkDPCDLevels failed, eStatus =%d", eStatus);
          break;
        }
      }
    }
    
    if(DP_STATUS_SUCCESS != eStatus)
    {
      DP_LOG_MESSAGE_ERROR("Link training 1 failed with eStatus=0x%x",eStatus);
      TraceInfo(QdiTraceDP, "DP%i: Link training clock recovery Failed (eStatus=%i)", pDeviceCtx->eDisplayID, eStatus);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_LinkTraining_ChannelEqualization
//
//  @brief
//      This function will do link training with pattern TPS2 or TPS3.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] uFlags
//          Reserved.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_LinkTraining_ChannelEqualization(DP_DisplayCtxType   *pDisplayCtx,
                                               DP_FlagsType         uFlags)
{
  DP_Status                     eStatus            = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType             *pDeviceCtx         = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType             *pStreamCtx         = DPHOST_GET_STREAM_CTX(pDisplayCtx); 

  UNREFERENCED_PARAMETER(uFlags);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: input is NULL pointer");
  }
  else
  { 
    DP_DPCDTrainingPatternSetType eTrainingPattern;

    /* DP1.4a spec says TPS1 for CR and TPS4 for Channel EQ on LTTPR repeaters. */
    if ((pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_SUPPORT_TRAININGPATTERN4) ||
         DPHOST_CHECK_IS_LTTPR_REPEATER(pDeviceCtx))
    {
      // Start sending Training Pattern 4
      HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN4);
      eTrainingPattern = DP_DPCD_TRAININGPATTERNSET_PATTERN4;
    }
    else if (pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_SUPPORT_TRAININGPATTERN3)
    {
      // Start sending Training Pattern 3
      HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN3);
      eTrainingPattern = DP_DPCD_TRAININGPATTERNSET_PATTERN3;
    }
    else
    {
      // Start sending Training Pattern 2
      HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN2);
      eTrainingPattern = DP_DPCD_TRAININGPATTERNSET_PATTERN2;
    }

    // Inform sink about the Training Pattern we are using
    if (DP_STATUS_SUCCESS != (eStatus = DP_WriteSinkDPCDTrainingPattern(pDisplayCtx, eTrainingPattern)))
    {
      DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: DP_WriteSinkDPCDTrainingPattern failed, eStatus = %d", eStatus);
    }
    else if (DP_STATUS_SUCCESS != (eStatus = DP_LinkSetupPreemphSwing(pDisplayCtx, pDeviceCtx->uVoltageSwingLevel, pDeviceCtx->uPreEmphasisLevel)))
    {
      DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: DP_LinkSetupPreemphSwing failed, eStatus = %d", eStatus);
    }
    else if (DP_STATUS_SUCCESS != (eStatus = DP_WriteSinkDPCDLevels(pDisplayCtx, pDeviceCtx->uVoltageSwingLevel, pDeviceCtx->uPreEmphasisLevel)))
    {
      DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: DP_WriteSinkDPCDLevels failed, eStatus = %d", eStatus);
    }
    else
    {
      DP_DPCDSinkStatusType   sSinkDPCDStatus;
      uint32                  uVoltSwingLvl           = 0;
      uint32                  uPreemphLvl             = 0;
      uint32                  uRetries                = 0;
      uint32                  uCETrainingIntervalInUs = (DPHOST_CHECK_IS_LTTPR_REPEATER(pDeviceCtx)? pDeviceCtx->uLTTPRCETrainingIntervalInUs : 
                                                                                                     pDeviceCtx->sSinkDPCDCap.uCETrainingIntervalInUs);

      for (uRetries = 0; uRetries < MAX_LINK_TRAINING_LOOP; uRetries++)
      {
        /* Wait for a period defined by the DPCD
         * Use Stall for Us order values instead of sleep as some monitors are sensitive to timing
         */
        if (uCETrainingIntervalInUs < 1000)
        {
          DP_OSAL_StallUs(uCETrainingIntervalInUs); 
        }
        else
        {
          DP_OSAL_SleepUs(uCETrainingIntervalInUs);
        }

        /* Use stall based read as link training is timing sensitive */
        eStatus  = DP_ReadSinkDPCDStatus(pDisplayCtx, &sSinkDPCDStatus, DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG);
        if(DP_STATUS_SUCCESS != eStatus)
        {    
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: Failed to read sink status from DPCD\n");
          break;
        }

        if(FALSE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_CLK_RECOVERY_DONE))
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: Clock Recovery Failed\n");
          TraceInfo(QdiTraceDP, "DP%i: Link training channel equalization: clock recovery failed", pDeviceCtx->eDisplayID);
          eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
          break;
        }

        if((TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_CHANNEL_EQ_DONE)) &&
           (TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_SYMBOL_LOCKED))   &&
           (TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_INTERLANE_ALIGN_DONE)))
        {
          /* Link Training 2/3 done successfully */
          TraceInfo(QdiTraceDP, "DP%i: Link training Channel EQ , Symbol Lock and Inter-lane align Done", pDeviceCtx->eDisplayID);
          pDeviceCtx->bLinkLost = FALSE;
          break;
        }

        // Get Sink requested pre-emphasis and voltage swing
        DP_GetMaxSinkPeSwRequest(pDisplayCtx, &sSinkDPCDStatus, &uVoltSwingLvl, &uPreemphLvl);

        // Apply newly requested settings
        if (DP_STATUS_SUCCESS != (eStatus = DP_LinkSetupPreemphSwing(pDisplayCtx, uVoltSwingLvl, uPreemphLvl)))
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: DP_LinkSetupPreemphSwing failed, eStatus =%d", eStatus);
          break;
        }
        else if ((DP_CUSTOM_SINKID_NONE != pDeviceCtx->eCustomSinkType) &&
                 (DP_STATUS_SUCCESS != (eStatus = DP_WriteCustomLTTPRDPCDLevels(pDisplayCtx,
                                                                                pDeviceCtx->uVoltageSwingLevel,
                                                                                pDeviceCtx->uPreEmphasisLevel,
                                                                                pDeviceCtx->eCustomSinkType))))
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: DP_WriteCustomLTTPRDPCDLevels failed, eStatus =%d", eStatus);
          break;
        }
        else if (DP_STATUS_SUCCESS != (eStatus = DP_WriteSinkDPCDLevels(pDisplayCtx, pDeviceCtx->uVoltageSwingLevel, pDeviceCtx->uPreEmphasisLevel)))
        {
          DP_LOG_MESSAGE_ERROR("DP_LinkTraining_ChannelEqualization: DP_WriteSinkDPCDLevels failed, eStatus =%d", eStatus);
          break;
        }
      }

      if (uRetries >= MAX_LINK_TRAINING_LOOP)
      {
        DP_LOG_MESSAGE_ERROR("Link Training (channel Eq) failed (%d attempts)", MAX_LINK_TRAINING_LOOP);
        TraceInfo(QdiTraceDP, "DP%i: Link training channel equalization failed : max attempts with same drive settings", pDeviceCtx->eDisplayID);
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
    }

    if (DP_STATUS_SUCCESS != eStatus)
    { 
      DP_LOG_MESSAGE_ERROR("Link training 2 failed with eStatus=0x%x",eStatus);
      TraceInfo(QdiTraceDP, "DP%i: Link training channel equalization Failed (eStatus=%i)", pDeviceCtx->eDisplayID, eStatus);
    }
  } 
  
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_LinkTraining
//
//  @brief
//      API does DP link training
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] eLinkTrainingType
//          Calculated RG parameters.
//      [IN] uFlags
//          Reserved.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_LinkTraining(DP_DisplayCtxType        *pDisplayCtx,
                          DP_LinkTrainingType       eLinkTrainingType,
                          DP_FlagsType              uFlags)
{
  DP_Status             eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType     *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_LinkTraining: Unexpected null context.");
  }
  else if (DP_LINK_TRAINING_TYPE_FULL_TRAINING == eLinkTrainingType)
  {
    
    // TPS1
    if (eStatus == DP_STATUS_SUCCESS)
    {
      eStatus = DP_LinkTraining_ClockRecovery(pDisplayCtx, uFlags);
    }
    
    // TPS2 or TPS3
    if (eStatus == DP_STATUS_SUCCESS)
    {
      eStatus = DP_LinkTraining_ChannelEqualization(pDisplayCtx, uFlags);      
    }

    // Stop training
    HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_NONE);
    DP_WriteSinkDPCDTrainingPattern(pDisplayCtx, DP_DPCD_TRAININGPATTERNSET_NONE);

  }
  else if (DP_LINK_TRAINING_TYPE_FAST_TRAINING == eLinkTrainingType)
  {
    /* In the fast training approach, we send each training pattern for a certain amount of time.
     * We do not do any AUX transactions in this training mode
     */
     
    // TPS 1
    HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN1);
    DP_OSAL_SleepUs(DP_SET_LINK_STATE_WAIT_TIME_US);

    // TPS2
    HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN2);
    DP_OSAL_SleepUs(DP_SET_LINK_STATE_WAIT_TIME_US);

    // Stop training
    HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_NONE);    
  }
  else if (DP_LINK_TRAINING_TYPE_NO_TRAINING == eLinkTrainingType)
  {
    if (DP_TEST_PHY_PATTERN == pDeviceCtx->ePendingTestRequest)
    {
      // PHY CTS test does not need link training, but will need to setup the pre-emphasis and swing levels.
      if (DP_STATUS_SUCCESS != (eStatus = DP_LinkSetupPreemphSwing(pDisplayCtx, pDeviceCtx->uVoltageSwingLevel, pDeviceCtx->uPreEmphasisLevel)))
      {
        DP_LOG_MESSAGE_ERROR("DP_LinkTraining: DP_LinkSetupPreemphSwing failed, eStatus =%d", eStatus);
      }

      // Send levels to sink as some redriver hardware will snoop for this AUX command to set up the link 
      if (DP_STATUS_SUCCESS != DP_WriteSinkDPCDLevels(pDisplayCtx, pDeviceCtx->uVoltageSwingLevel, pDeviceCtx->uPreEmphasisLevel))
      {
        DP_LOG_MESSAGE_ERROR("DP_LinkTraining: Failed to send Tx levels");
      }
    }
  }
  else
  {
    DP_LOG_MESSAGE_ERROR("DP_LinkTraining: invalid training type = %d\n", (uint32)eLinkTrainingType);
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }

  if (DP_STATUS_SUCCESS == eStatus)
  {
    // Read symbol errors to clear them, if there were any during channel equalization or clock recovery.
    DP_ReadSinkSymbolStatus(pDisplayCtx, NULL);
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_CalculateMisc0
//
//  @brief
//      This function will calculate the MISCO value according to DP Spec.
//
//  @params
//      [IN] eColorFormat
//          Sink color format.
//
//  @return
//      uint8.
//-------------------------------------------------------------------------------------------------
//
uint8  DP_CalculateMisc0(DP_PixelFormatType eColorFormat )
{
  uint8 uMisc0;
  
  if (DP_PIXEL_FORMAT_RGB_666_18BPP == eColorFormat )
  {
    uMisc0 = 0;
  }
  else
  {
    uMisc0 = DP_SPEC_MSA_MISCO_COLOR_8BPC_BMSK;
  }
  
  return uMisc0;
}

//-------------------------------------------------------------------------------------------------
//  Round
//
//  @brief
//      Round double to nearest integer.
//
//  @params
//      [IN] dNumber
//          Number to be rounded.
//
//  @return
//      int32.
//-------------------------------------------------------------------------------------------------
//
static int32 Round(double dNumber)
{
    int32 iRound = 0;

    if (dNumber < 0.0)
    {
        iRound = (int32)(dNumber - 0.5);
    }
    else
    {
        iRound = (int32)(dNumber + 0.5);
    }

    return iRound;
}

#ifdef __cplusplus
}
#endif

