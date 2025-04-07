#!/usr/bin/env python

#============================================================================
#
# @file file_encoding_format_check.py
#
# GENERAL DESCRIPTION
#   check file encoding format
#
# Copyright 2023 by Qualcomm Technologies, Inc.
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
# 05/31/23   bxr     Initial release
# --------   ---     ----------------------------------------------------------

from optparse import OptionParser
import os
import sys
import platform
import subprocess
import struct
import stat
import time
import threading
import json
from datetime import datetime
try:
  import chardet
except ImportError:
  sys.exit("ERROR: Not found chardet. Please try with command 'pip install chardet'")

# platform
cur_platform = platform.system()

#file encoding format flag
ISO_8859_1_ENCODFING = "ISO-8859-1"
WINDOWS_1252_ENCODFING = "Windows-1252"
WINDOWS_1254_ENCODFING = "Windows-1254"
UTF_8_SIG_ENCODFING = "UTF-8-SIG"
UTF_8_ENCODFING = "utf-8"
ASCII_ENCODFING = "ascii"
File_Encoding_Format_list = [UTF_8_ENCODFING, UTF_8_SIG_ENCODFING, ISO_8859_1_ENCODFING, WINDOWS_1252_ENCODFING, WINDOWS_1254_ENCODFING]

#match the non-ascii characters with the correct ascii character for each file encoding format
WINDOWS_1254_map_list = []

UTF_8_SIG_map_list = [[b'\xef\xbb\xbf', b'']]

UTF_8_map_list = [[b'\xe2\x80\x9c', b'\x22'],
                  [b'\xe2\x80\x9d', b'\x22'],
                  [b'\xe2\x80\x98', b'\x27'],
                  [b'\xe2\x80\x99', b'\x27'],
                  [b'\xe2\x80\x93', b'\x2d'],
                  [b'\xe2\x80\x8b', b'\x20'],
                  [b'\xef\xbf\xbd', b'\x20'],
                  [b'\xc2\xa0',     b'\x20']]

ISO_8859_1_map_list = [[b'\xe2\x80\x8b', b'\x20'],
                       [b'\xef\xbf\xbd', b'\x20'],
                       [b'\xc2\xa0',     b'\x20'],
                       [b'\xc2\xa9',     b'\x20'],
                       [b'\xc2\xa9',     b'\x28\x63\x29'],
                       [b'\xa0',         b'\x20'],
                       [b'\xa9',         b'\x28\x63\x29']]

Windows_1252_map_list = [[b'\xe2\x80\x8b', b'\x20'],
                         [b'\xe2\x80\x99', b'\x27'],
                         [b'\xe2\x80\x93', b'\x2d'],
                         [b'\x95'          b'\x2e'],
                         [b'\x97',         b'\x2d'],
                         [b'\x96',         b'\x2d'],
                         [b'\x93',         b'\x22'],
                         [b'\x94',         b'\x22'],
                         [b'\x92',         b'\x27'],
                         [b'\x91',         b'\x27']]

map_list = {UTF_8_ENCODFING       : UTF_8_map_list,
            ISO_8859_1_ENCODFING  : ISO_8859_1_map_list,
            WINDOWS_1252_ENCODFING: Windows_1252_map_list,
            UTF_8_SIG_ENCODFING   : UTF_8_SIG_map_list,
            WINDOWS_1254_ENCODFING: WINDOWS_1254_map_list}


# filename extension list for detecting
filename_extension = [".c", ".h", ".inf", ".dsc", ".inc", ".dec", ".fdf"]

#Figure out root path
cur_path = os.path.dirname(os.path.realpath(__file__))
if "boot_images" in cur_path:
  root_path = cur_path.split("boot_images")[0]
else:
  sys.exit("ERROR. Failed to figure out the correct path")


#####################################################################
# json_file_load
#####################################################################
def json_file_load(src_file):
  
  dst_json = ""
  json_load_params = {}
  try:
    #remove comments in json file
    with open(src_file, 'r') as src_json_file:
      for line in src_json_file:
        if line.lstrip().startswith("#"):
          continue
        if len(line.strip()) > 0:
          dst_json += line.split("#")[0].strip()
          dst_json += '\n'
      src_json_file.close()
  except Exception as error:
    print(error)
    sys.exit("ERROR. Failed to read %s" % src_file)
  
  try:
    #read data from json file
    json_load_params = json.loads(dst_json)
  except Exception as error:
    print(error)
    sys.exit("ERROR. Failed to load json params.")
  
  return json_load_params


#####################################################################
# get_json_file_data
#####################################################################
def get_json_file_data(json_file_name):
  #get uefi variables structure definition from character_mapping.json
  json_file_path =  os.path.join(cur_path, json_file_name)
  if not os.path.isfile(json_file_path):
    sys.exit("ERR. Failed to find %s" % json_file_name)
    
  json_data = json_file_load(json_file_path)
  
  return json_data


#################################################################
# get_absolute_checking_path
#################################################################
def get_absolute_checking_path(evaluation_dir):

  #check the input path
  if evaluation_dir == "":
    evaluation_dir = "boot_images/boot/QcomPkg"
  elif not evaluation_dir.startswith("boot_images"):
      sys.exit("ERROR. Please input the correct check directory starting with 'boot_images'")
  
  #figure out the absolute checking path
  absolute_checking_path = ''
  if cur_platform == "Windows":
    absolute_checking_path = os.path.join(root_path, evaluation_dir).replace("/", os.sep, 100)
  else:
    absolute_checking_path = os.path.join(root_path, evaluation_dir).replace("\\", os.sep, 100)

  return absolute_checking_path


#################################################################
# file_encoding_format_change
#################################################################
def file_encoding_format_change(file_to_be_fixed, coded_format):

  if coded_format in map_list.keys():
    current_map_list = map_list[coded_format]
    if not current_map_list:
      print("Please fix %s manually." % file_to_be_fixed)
      return False
  else:
    print("WARNING. File encoding format %s is not included." % coded_format)
    return False
    
  try:
    with open(file_to_be_fixed, 'rb') as rd_file:
      read_value = rd_file.read()
      for i in range(len(current_map_list)):
        if current_map_list[i][0] in read_value:
          read_value = read_value.replace(current_map_list[i][0], current_map_list[i][1])
      rd_file.close()
      
    #change file mode back to write
    os.chmod(file_to_be_fixed, stat.S_IWRITE)
    with open(file_to_be_fixed, 'wb') as wr_file:
      wr_file.write(read_value)
      wr_file.close()
    #change file mode back to read-only
    os.chmod(file_to_be_fixed, stat.S_IREAD)

  except Exception as err:
    print(err)
    sys.exit()

  return


#################################################################
# parse_illegal_character
#################################################################
def parse_illegal_character(current_file, code_file, checking_list):

  err_file_flag = 0
  accumulated_size = 0
  current_file_size = os.path.getsize(current_file)
  #check the character in one byte, 
  #if the value is not in 0~127, it's not the stanstard ascii code
  error_positions = ""
  error_line = 1
  error_column = 0
  code_file.seek(0)
  while(accumulated_size < current_file_size):
    read_value = struct.unpack("B", code_file.read(1))
    #ascii value(10) is line feed(LF)
    if (read_value[0] == 10):
      error_line += 1
      error_column = 0
    #ascii value(13) is carriage return(CR)
    elif (read_value[0] == 13):
      error_column = 0
    else:
      error_column += 1
    if (read_value[0] > 127):
      error_positions += ("  error: line:%d, column:%d, position:%d, value:%d(0x%02x)\n" % (error_line, error_column, accumulated_size, read_value[0], read_value[0]))
      if (read_value[0] not in checking_list["Err character list"]):
        checking_list["Err character list"].append(read_value[0])
    accumulated_size += 1
  if error_positions:
    checking_list["File list"][current_file] = error_positions
    err_file_flag = 1

  return err_file_flag


#################################################################
# create_whitlelist
#################################################################
def create_whitlelist():

  #create json file
  bypass_list_path = os.path.join(cur_path, "bypass_list.json")
  if os.path.exists(bypass_list_path):
    os.remove(bypass_list_path)
  bypass_list_file = open(bypass_list_path, "w+")
  bypass_list_file.write("{\n")
  
  return bypass_list_file


#################################################################
# parse_file
#################################################################
class parse_file(object):
  #global
  total_file_nums = 0
  ascii_file_nums = 0
  empty_file_nums = 0
  empty_file_list = []
  illegal_file_count = 0
  
  def __init__(self, python_options, output):
    self.python_options = python_options
    self.output = output

  def print_detail_errs(self, check_list) -> None:
    self.output.write("Error Details:" + "\n" + "-"*20 + "\n")
    for encoded_format, details in check_list.items():
      if details["File nums"] > 0:
        file_list = details["File list"]
        self.output.write("[" + encoded_format + "] ")
        self.output.write("files(%d)\n" % (details["File nums"]))
        num = 0
        for file_name, error_position in file_list.items():
          self.output.write("file%d: %s\n" % (num, file_name))
          self.output.write("%s" % (error_position))
          num += 1
        self.output.write("\n")

  def print_summary_errs(self, check_list) -> None:
    for encoded_format, details in check_list.items():
      if details["File nums"] > 0:
        error_character_list = details["Err character list"]
        self.output.write("  [" + encoded_format + "] ")
        self.output.write("files(%d)\n" % (details["File nums"]))
        self.output.write("  Error characters(%d): " % len(error_character_list))
        for i in range(len(error_character_list)):
          self.output.write("%d(0x%02x), " % (error_character_list[i], error_character_list[i]))
        self.output.write("\n")
    self.output.write("#"*100 + "\n\n")
  
  def print_empty_files(self) -> None:
    if len(parse_file.empty_file_list) > 0:
      self.output.write("\nEmpty files(%d)\n" % len(parse_file.empty_file_list))
      for i in range(len(parse_file.empty_file_list)):
        self.output.write("file %d : %s\n\n" %(i, parse_file.empty_file_list[i]))

  def file_encoding_format_check(self, current_file, summary_dic):
    #go through *.c, *.h, *.inf, *.dsc, *.inc, *.dec, *.fdf files, check the file encoding format
    if os.path.splitext(current_file)[1] in filename_extension:
      parse_file.total_file_nums += 1
      try:
        with open(current_file, "rb") as code_file:
          filecontents = code_file.read()
          coded_format = chardet.detect(filecontents)['encoding']
          if coded_format is not None:
            if coded_format != ASCII_ENCODFING:
              #print(current_file, coded_format)
              summary_dic[coded_format]["File nums"] += 1
              return_flag = parse_illegal_character(current_file, code_file, summary_dic[coded_format])
              parse_file.illegal_file_count += 1
              if self.python_options.file_encoding_format_fix_enable:
                file_encoding_format_change(current_file, coded_format)
            else:
              parse_file.ascii_file_nums += 1
          else:
            parse_file.empty_file_nums += 1
            parse_file.empty_file_list.append(current_file)
      except Exception as err:
        print(err)
        print("ERROR. Failed to handle %s" % current_file)
    return summary_dic
  
  def print_report(self, checking_path, summary_dic):
    print("total_file_nums: ", parse_file.total_file_nums, "\nillegal_file_count: ", parse_file.illegal_file_count)
    self.output.write("#"*100 + "\n")
    self.output.write("Checking path = %s\n\n" % checking_path)
    self.output.write("Total scanned files: %d\n\n" % parse_file.total_file_nums)
    self.output.write("Ascii files: %d\n\n" % parse_file.ascii_file_nums)
    self.output.write("Empty files: %d\n\n" % parse_file.empty_file_nums)
    self.output.write("Error(Non-ascii) files: %d\n" % parse_file.illegal_file_count)
    self.print_summary_errs(summary_dic)
    self.print_detail_errs(summary_dic)
    self.print_empty_files()
  
  
  def file_check_and_report(self):
    #figure out the absolute checking path
    checking_path = get_absolute_checking_path(self.python_options.check_dir)
    if not checking_path:
      sys.exit("ERROR. Failed to get the absolute checking path.")
      
    #give a list to store error report
    summary_dic = {}
    for i in range(len(File_Encoding_Format_list)):
      summary_dic[File_Encoding_Format_list[i]] = {}
      summary_dic[File_Encoding_Format_list[i]]["Err character list"] = []
      summary_dic[File_Encoding_Format_list[i]]["File list"] = {}
      summary_dic[File_Encoding_Format_list[i]]["File nums"] = 0
    
    #do file encoding format check
    if os.path.isfile(checking_path):
      #input is single file
      summary_dic = self.file_encoding_format_check(checking_path, summary_dic)
    else:
      #input is a directory
      for (root, dirs, files) in os.walk(checking_path):
        if "edk2" not in root:
          for file in files:
            current_file = os.path.join(root, file)
            summary_dic = self.file_encoding_format_check(current_file, summary_dic)
    
    #store check report
    self.print_report(checking_path, summary_dic)


#################################################################
# main
#################################################################
def main():

  time_start = time.time()
  parser = OptionParser()
  
  parser.add_option("--file-check-dir",
                    action="store",
                    type="string",
                    dest="check_dir",
                    default="",
                    help="Base directory of where to start check. " + \
                         "Default is boot_images/boot/QcomPkg")

  parser.add_option("--file-encoding-format-check",
                    action="store_true",
                    dest="file_encoding_format_check_enable",
                    default=True,
                    help="Enables file encoding format check.")

  parser.add_option("--file-encoding-format-fix",
                    action="store_true",
                    dest="file_encoding_format_fix_enable",
                    default=False,
                    help="Enables file encoding format fix.")

  (options, args) = parser.parse_args()
  
  if (options.file_encoding_format_check_enable):
    #delete the output file of last time and create a new one
    try:
      output_path = os.path.join(cur_path, "file_encoding_format_check_output.txt")
      if os.path.exists(output_path):
        os.remove(output_path)
      output_file = open(output_path, "w+")
    except Exception as err:
      print(err)
      print("ERROR. Failed to create a new output file.")
    
  #initial settings
  Parse_File = parse_file(python_options = options, output = output_file)
  
  #check file encoding format
  Parse_File.file_check_and_report()
  print("Please check output file %s " % output_path)
  
  #total time
  time_end = time.time()
  total_time = time_end - time_start
  print("Running time is ",int((total_time) * 1000), "msecs")
  output_file.write("-"*20 + "\nTotal time: %d msecs\n" % int((total_time) * 1000))
  output_file.close()
  
  return


if __name__ == "__main__":
  main()