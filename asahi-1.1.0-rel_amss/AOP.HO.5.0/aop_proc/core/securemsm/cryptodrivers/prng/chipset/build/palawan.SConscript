#===============================================================================
#
# Crypto Driver Chipset Library
#
# GENERAL DESCRIPTION
#    build script
#
# Copyright (c) 2023 by QUALCOMM, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#===============================================================================
import os
Import('env')
env = env.Clone()

# kuno interface redirection
CHIPSETREDIRECTION = 'palawan'

script_sconfname = None
if os.path.exists('../' + CHIPSETREDIRECTION + '/build/SConscript') :
   script_sconfname = '../' + CHIPSETREDIRECTION + '/build/SConscript'
else :
   print ("Directory: [%s] doesnot exist"%script_sconfname)
   raise RuntimeError("palawan  [%s] does not exist"%script_sconfname)

#-------------------------------------------------------------------------------
# Load sub scripts
#-------------------------------------------------------------------------------
script_scon = None
script_scon = '../' + CHIPSETREDIRECTION + '/build'

env.SConscript(dirs=[script_scon], exports='env')
