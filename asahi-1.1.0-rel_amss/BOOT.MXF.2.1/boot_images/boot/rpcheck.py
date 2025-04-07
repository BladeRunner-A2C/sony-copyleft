#!/usr/bin/env python

#============================================================================
#
# @file rpcheck.py
#
# GENERAL DESCRIPTION
#   check reletive path in *.inf and general report
#
# Copyright 2021 by Qualcomm Technologies, Inc.
#                 All Rights Reserved.
#               QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 08/30/22   bxr     Add conditional expressions
# 10/21/21   bxr     Initial release
# --------   ---     ----------------------------------------------------------

import os
import glob
import sys
import platform
import configparser
from pathlib import PurePath
import subprocess


#Relative path flag
relative_path_match_str = ".."

# platform
cur_platform = platform.system()
  
#Figure out root path
cur_path = os.path.dirname(os.path.realpath(__file__))
if "boot_images" in cur_path:
  root_path = cur_path.split("boot_images")[0]
else:
  sys.exit("ERROR. Failed to figure out the correct path")


#################################################################
# file_detete
#################################################################
def file_detete(file_path):

  if cur_platform == "Windows":
    delete_command = "rd" + r" /s " + r"/q " + file_path
  else:
    delete_command = "rm" + " -rf " + file_path
  
  try:
    subprocess.run(delete_command, shell = True)
  except Exception as err:
    print(err)
    print("ERROR. Failed to delete %s" % file_path)

  return


#################################################################
# get_absolute_checking_path
#################################################################
def get_absolute_checking_path(evaluation_dir):

  #check the input checking directory
  if evaluation_dir == "":
    evaluation_dir = "boot_images/boot/QcomPkg"
  elif not evaluation_dir.startswith("boot_images"):
      sys.exit("ERROR. Please input the correct checking directory which starts with 'boot_images'")
    
  #figure out the absolute checking path
  absolute_checking_path = ''
  if cur_platform == "Windows":
    absolute_checking_path = os.path.join(root_path, evaluation_dir).replace("/", os.sep, 100)
  else:
    absolute_checking_path = os.path.join(root_path, evaluation_dir).replace("\\", os.sep, 100)

  return absolute_checking_path


#################################################################
# relative_path_check
#################################################################
def relative_path_check(evaluation_dir, rpcheck_threshold):
  
  #Ensure threshold is greater than or equal to 0
  if (rpcheck_threshold < 0):
    raise NameError("\nERROR: watchit::reletive_path_check: " + \
                    "Threshold supplied is invalid: %d" \
                    % rpcheck_threshold)
  
  #delete the output file from last time and create a new one
  out_file_path = os.path.join(cur_path, "relative_path_check_output.txt")
  if os.path.exists(out_file_path):
    file_detete(out_file_path)
  
  out_file = open(out_file_path, "w+")

  #figure out the absolute checking path
  checking_path = get_absolute_checking_path(evaluation_dir)
  if not checking_path:
    sys.exit("ERROR. Failed to get the absolute checking path.")
  
  #go through the INF file and check if there are relative paths in "Sources" section
  offending_file_count = 0
  for (root, dirs, files) in os.walk(checking_path):
    for current_file in glob.glob(root+ os.sep + "*.inf"):
      src_tag = ''
      current_line = 0
      source_section_match_flag = 0
      header_print_toggle_flag = 1
      try:
        with open(current_file, "r") as inf_file:
          for line in inf_file:
            current_line += 1
            line = line.strip()
            if line and (line.startswith('#') == False):
              #figure out the "Sources" section, ex - "[Sources.common]"
              if line.startswith("["):
                if line.startswith("[Sources"):
                  source_section_match_flag = 1
                  src_tag = line
                else:
                  source_section_match_flag = 0
              elif (source_section_match_flag == 1):
                #check if relative path flag ".." under "Sources" section, ex - "../src/smem.c"
                if relative_path_match_str in (PurePath(line).parts):
                  #write the inf file path into output file
                  if header_print_toggle_flag:
                    header_print_toggle_flag = 0
                    offending_file_count += 1
                    out_file.write("\rFile %d\n\t%s\n" % (offending_file_count, current_file))
                  #write the "Sources" section name into output file
                  if src_tag:
                    out_file.write("\t%s\n" % src_tag)
                    src_tag = ''
                  out_file.write("\tline %d: %s\n" % (current_line, line))
          inf_file.close()
      except Exception as err:
        print(err)
        print("ERROR. Failed to read %s" % current_file)
  out_file.close() 

  return offending_file_count