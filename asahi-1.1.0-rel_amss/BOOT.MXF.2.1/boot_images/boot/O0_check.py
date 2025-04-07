#!/usr/bin/env python

#============================================================================
#
# @file rpcheck.py
#
# GENERAL DESCRIPTION
#   check buildoption -O0 in INF/DSC and general report
#
# Copyright 2022 by Qualcomm Technologies, Inc.
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
# 08/30/22   bxr      Add conditional expressions
# 02/28/22    bxr     Initial release
# --------   ---     ----------------------------------------------------------


from __future__  import print_function
import sys
import os
import platform
import subprocess

#build command "-O0" flag
O0_match_str = r"-O0"

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
# buildoption_O0_check
#################################################################
def buildoption_O0_check(check_path, O0_check_threshold):
  
  #Ensure threshold is greater than or equal to 0
  if (O0_check_threshold < 0):
    sys.exit("\nERROR: watchit::buildoption_O0_check: " + \
                    "Threshold supplied is invalid: %d" \
                    % O0_check_threshold)

  #delete the output file from last time and create a new one
  out_file_path = os.path.join(cur_path, "O0_check_output.txt")
  if os.path.exists(out_file_path):
    file_detete(out_file_path)
  
  #figure out the absolute checking path
  checking_path = get_absolute_checking_path(check_path)
  if not checking_path:
    sys.exit("ERROR. Failed to get the absolute checking path.")
  
  #check buildoption -O0 in INF and DSC files under input folder recursively
  #count INF/DSC files which contain "-O0" and store them in a file for check
  offending_file_count = 0
  with open(out_file_path, 'w') as output_file:
    for (root, dirs, files) in os.walk(checking_path):
      for cur_file in files:
        if cur_file.endswith(".inf") or cur_file.endswith(".dsc"):
          src_tag = ''
          current_line = 0
          header_print_toggle_flag = 1
          buildoption_section_match_flag = 0
          current_file = os.path.join(root, cur_file)
          try:
            with open(current_file, "r") as inf_file:
              for line in inf_file:
                current_line += 1
                line = line.strip()
                if line and (line.startswith('#') == False):
                  #figure out the "BuildOptions" section, ex - "[BuildOptions.AARCH64]"
                  if line.startswith("["):
                    if line.startswith("[BuildOptions"):
                      buildoption_section_match_flag = 1
                      src_tag = line
                    else:
                      buildoption_section_match_flag = 0
                  elif (buildoption_section_match_flag == 1):
                    #check if build command "-O0" under "BuildOptions" section, ex - "GCC:*_*_*_CC_FLAGS = -O0"
                    if O0_match_str in line:
                      #write the inf file path into output file
                      if (header_print_toggle_flag == 1):
                        header_print_toggle_flag = 0
                        offending_file_count += 1
                        output_file.write("\rFile %d\n\t%s\n" % (offending_file_count, current_file))
                      #write the "BuildOptions" section name into output file
                      if src_tag:
                        output_file.write("\t%s\n" % src_tag)
                        src_tag = ''
                      output_file.write("\tline %d: %s\n" % (current_line, line))
              inf_file.close()
          except Exception as err:
            print(err)
            print("ERROR. Failed to read %s" % current_file)
    output_file.close()
  
  return offending_file_count

