#!/bin/sh
#===============================================================================
#
# Pack Compile Test All
#
# General Description
#    Call the pack_compile_test_all.py scripts
#
# Copyright (c) 2009-2011 by QUALCOMM, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
# $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/pack/pack_compile_test_all.sh#1 $
# $DateTime: 2024/04/01 02:51:58 $
# $Change: 53033171 $
#                      EDIT HISTORY FOR FILE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
#
#===============================================================================

# This isn't needed because we will already be in the right directory
# when this command executes.
#cd `dirname $0`

python pack_compile_test_all.py $*
build_result=$?
if [ "${build_result}" != "0" ] ; then
  exit ${build_result}
fi
