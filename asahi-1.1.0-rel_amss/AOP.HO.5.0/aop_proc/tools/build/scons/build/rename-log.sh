#===============================================================================
#
# CBSP Buils system
#
# General Description
#    build rename log file.
#
# Copyright (c) 2009-2009 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
# $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/tools/build/scons/build/rename-log.sh#1 $
# $DateTime: 2024/04/01 02:51:58 $
# $Author: cirrusp4svc $
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
#!/bin/bash
log_file_name="build-log"
log_file_ext=".txt"
log_file="$log_file_name$log_file_ext"

if [ -f $log_file ]; then
   for i in {001..999}; do
      old_log_file="$log_file_name-$i$log_file_ext"
      
      if [ ! -f $old_log_file ]; then
         break
      fi
   done

   mv $log_file $old_log_file
fi 
