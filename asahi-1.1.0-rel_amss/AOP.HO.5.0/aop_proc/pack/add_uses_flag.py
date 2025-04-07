'''
#===============================================================================
#
# add_uses_flag.py
#
# GENERAL DESCRIPTION
#    Add the specified USES flag to the specified tcfg_*.py script.
#
# USAGE
#
#    add_uses_flag.py <tcfg_file> <uses_flag>
#
# Copyright (c) 2011-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/pack/add_uses_flag.py#1 $
#  $DateTime: 2024/04/01 02:51:58 $
#  $Change: 53033171 $
#
#===============================================================================
'''

import sys
import os
import shutil
from glob import glob

import logger
lg=logger.Logger('add_uses_flag', 'add_uses_flag.py: ')

if len(sys.argv) != 3:
   lg.log("Error: Illegal number of parameters: " + str(sys.argv))
   exit(1)

tcfg_fn   = sys.argv[1]
uses_flag = sys.argv[2]

lg.log("Adding " + uses_flag + " to " + tcfg_fn)

tcfg = open(tcfg_fn, 'r')
tcfg_contents = tcfg.read()
tcfg.close()

if uses_flag == "USES_NO_STRIP_NO_ODM":
   tcfg_contents = tcfg_contents.replace("   env.AddUsesFlags('USES_STRIP_NO_ODM', from_builds_file = True)", "")
tcfg_contents += "   env.AddUsesFlags('%s', from_builds_file = True)\n" % uses_flag

tcfg = open(tcfg_fn, 'w')
tcfg.write(tcfg_contents)
tcfg.close()


