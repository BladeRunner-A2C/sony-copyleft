#============================================================================
#
#/** @file create_trdata.py
#
# GENERAL DESCRIPTION
#   Creates dummy (empty) ddr training mbn header with given inputs
#
# Copyright 2017, 2020, 2023 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#**/
#
#----------------------------------------------------------------------------
#
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who       what, where, why
# --------   ---       ------------------------------------------------------
# 07/17/23   ng        Updated mdmddr.mbn file to 80kb
# 03/24/23   ng        Updated mdmddr.mbn file to 40kb
# 08/20/20   ck        Ported from SBL 4.1
# 06/16/17   et        Initial version

#============================================================================
from __future__ import print_function
import os
import sys
import mbn_tools


if len(sys.argv) != 3:
   print("Incorrect Usage: create_trdata.py <DDR training data base address> <output file path>")
   raise RuntimeError("Usage: create_trdata.py <DDR training data base address> <output file path>")

def create_trdata_img(trdata_address, trdata_file_path, trdata_size):
   
    header = mbn_tools.Boot_Hdr(init_val = int('0x0',16))
      
    header.image_dest_ptr = int(trdata_address,16)
    header.image_size = trdata_size
    header.image_id = 34
      
    header.writePackedData(target = trdata_file_path,
                           write_full_hdr = False)
    return
  
def pad_trdata_img(trdata_file_path, pad_file_size):  
    trdata_fp = mbn_tools.OPEN(trdata_file_path, 'ab')
    trdata_fp.seek(mbn_tools.MI_BOOT_IMG_HDR_SIZE)
    mbn_tools.pad_file (trdata_fp, pad_file_size, mbn_tools.PAD_BYTE_0)
    trdata_fp.close()
    return

trdata_address = sys.argv[1]
trdata_file_path = sys.argv[2]
trdata_size = 80 * 1024  # 80KB
create_trdata_img(trdata_address, trdata_file_path, trdata_size)
pad_trdata_img(trdata_file_path, trdata_size)