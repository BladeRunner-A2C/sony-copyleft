#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021-2023 Qualcomm Technologies, Inc.  All Rights Reserved.

# -z : Workspace path
# -y : Path to your YAML tree
# -u : DTS file path
# -f : force output

"""Dt-schema interactive script.

This script is used to validate both YAML and DTS/DTSI files.

This script has two required arguments that are needed for the script to execute:
	* -s <target>. This argument is required for the script to determine which target's DTS files need to be validated.
	* -w <workspace>. This argument is required for the script to differentiate between different families. The supported values are: "boot" (for core.boot) and "Q6" (for core.qdsp, core.mpss)

There is an optional argument for Q6 as well:
	* -c <config>. This argument is used when running the script in Q6 families to allow the engineer to specify which config tree of DTS files they wish to validate. If the argument isn't given,
	then every DTS file is processed. The values for this argument are: "adsp", "cdsp", "gpdsp", "mpss".

"""

import argparse
import json
import os
import sys
import platform
import subprocess as sp
import shutil
from pathlib import Path
from qc_get_paths import PATH_DICT, print_paths


PROJECT_SCHEMA_FILE_NAME = "project-schema"
YAMLFILE_EXTN = ".yaml"
DTS_EXTN = ".dts"
INCLUDE_OPTION = "-I"
VERBOSE_OPTION = "-v"

RETURN_SUCCESS = 0
RETURN_ERROR = 1
INCLUDE_DIRECTORY = "include"

OUTPUT_GENDTB_FOLDER = "gendtb_output_dtb"
OUTPUT_TOOL_FOLDER = "OUTPUT_TOOL"
OUTPUT_QC_DT_SCHEMA_CHECK_FOLDER = "qc_dt_schema_check"
OUTPUT_QC_DT_CHECK_FOLDER = "qc_dt_check"
OUTPUT_PLATFORM_FOLDER = "platform"

COMPILE_OVERLAY_FLAG = True

def update_workspace_path(dict, path_key, pathname_string):
	input_path = input("Enter the path for %s: " % (pathname_string))
	if os.path.exists(input_path) != True:
		error_msg = "WARNING: Workspace path [" + input_path + "] does not exist"
		print(error_msg)
	else:
		print("Updating %s" % (pathname_string))
		dict[path_key] = input_path


def common_path_define(dict):
	global toolchain_data
	retval = RETURN_ERROR
	
	qcdtschemacheckpath = PATH_DICT['qc_dt_schema_check_path']
	qcdtcheckpath = PATH_DICT['qc_dt_check_path']
	dtcpath = PATH_DICT['dtcpath']
	dtschematoolspath = PATH_DICT['dt_schema_tools_path']
	cpppath = PATH_DICT['cpppath']
	gendtbpath = PATH_DICT['gendtbpath']
		
	if os.path.exists(dict['workspacepath']) != True:
		error_msg = "Error: Workspace Path [" + dict['workspacepath'] + "] does not exist"
		print(error_msg)
	elif os.path.exists(qcdtschemacheckpath) != True:
		error_msg = "Error: Tool qc_dt_schema_check Path [" + qcdtschemacheckpath + "] does not exist"
		print(error_msg)
	elif os.path.exists(qcdtcheckpath) != True:
		error_msg = "Error: Tool qc_dt_check Path [" + qcdtcheckpath + "] does not exist"
		print(error_msg)
	elif os.path.exists(dtcpath) != True:
		error_msg = "Error: DTC tool Path [" + dtcpath + "] does not exist"
		print(error_msg)
	elif os.path.exists(dtschematoolspath) != True:
		error_msg = "Error: DTSchematools Path [" + dtschematoolspath + "] does not exist"
		print(error_msg)
	elif os.path.exists(cpppath) != True:
		error_msg = "Error: CPP tool Path [" + cpppath + "] does not exist"
		print(error_msg)
	elif os.path.exists(gendtbpath) != True:
		error_msg = "Error: gendtb tool Path [" + gendtbpath + "] does not exist"
		print(error_msg)
	else:
		retval = RETURN_SUCCESS
		dict['qcdtschemacheckpath'] = qcdtschemacheckpath
		dict['qcdtcheckpath'] = qcdtcheckpath
		dict['dtcpath'] = dtcpath
		dict['dtschematoolspath'] = dtschematoolspath
		dict['cpppath'] = cpppath
		dict['gendtbpath'] = gendtbpath
	return retval

def handle_clean(dict, clean_directory):
	if os.path.exists(clean_directory) != True:
		return
	
	if dict['verbose']:
		print("Clean folder ", clean_directory)
	
	shutil.rmtree(clean_directory)
	
def exec_qc_dt_schema_check(dict):
	

	if common_path_define(dict) == RETURN_ERROR:
		return
	
	output_qc_dt_schema_check_directory = os.path.join(dict['output_directory'], OUTPUT_QC_DT_SCHEMA_CHECK_FOLDER)
	
	if os.path.exists(output_qc_dt_schema_check_directory) != True:
		os.mkdir(output_qc_dt_schema_check_directory)
	
	print("qc_dt_schema_check output directory exists: \t<workspace>%s" % (output_qc_dt_schema_check_directory.removeprefix(dict['workspacepath'])))
	
	command_qcdtschemacheck = ""
	if platform.system() == "Windows":
		command_qcdtschemacheck="python %s -d %s -y %s -t %s -p %s -o %s -r %s -w -c" % (dict['qcdtschemacheckpath'],
																				dict['dtcpath'], 
																				dict['yamlpath'], 
																				dict['dtschematoolspath'], 
																				dict['cpppath'],
																				output_qc_dt_schema_check_directory,
																				PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)
		if dict['workspace'] == "boot":
			command_qcdtschemacheck += append_all_params_json(
													toolchain_data['ToolChain']['qc_dt_schema_check']['Windows'], 
													"Params")
	
	else:
		command_qcdtschemacheck="chmod +x %s && python %s -d %s -y %s -t %s -p %s -o %s -r %s -c" % (dict['qcdtschemacheckpath'],
																								dict['qcdtschemacheckpath'], 
																								dict['dtcpath'], 
																								dict['yamlpath'], 
																								dict['dtschematoolspath'], 
																								dict['cpppath'],
																								output_qc_dt_schema_check_directory,
																								PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)
		
	# Append arch for the tools
	if PATH_DICT["arch"] == "hexagon":
		command_qcdtschemacheck = command_qcdtschemacheck + " -m " + PATH_DICT["arch"]
	
	if dict['verbose']:
		command_qcdtschemacheck = command_qcdtschemacheck + " " + VERBOSE_OPTION

	print ("\n========================================================")
	print ("========================================================")
	print ("\t   SCRIPT 1 : RUNNING QC_DT_SCHEMA_CHECK")
	print ("========================================================")
	print ("========================================================")
	if dict['verbose']:
		print ("Running ", command_qcdtschemacheck)
	
	return_code = os.system(command_qcdtschemacheck)
	
	if return_code != 0:
		print("\nError : SCRIPT 1 failed for [%s]" % (command_qcdtschemacheck))
		print("YAML File validation FAILED")
	
	print ("========================================================")
	print ("========================================================")
	print ("\t   END OF QC_DT_SCHEMA_CHECK")
	print ("========================================================")
	print ("========================================================\n\n\n")


def exec_qc_dt_check(dict):
	
	if common_path_define(dict) == RETURN_ERROR:
		return
	
	# Create hash for gendtb and qc_dt_check outputs directories
	output_directories_dict = {}
	overlay_files_paths_list = []
	error_logs_folders = []
	
	output_gendtb_directory = os.path.join(dict['output_directory'], OUTPUT_GENDTB_FOLDER)
	output_qc_dt_check_directory = os.path.join(dict['output_directory'], OUTPUT_QC_DT_CHECK_FOLDER)
	
	if os.path.exists(output_gendtb_directory) == True:
		handle_clean(dict, output_gendtb_directory)
	os.mkdir(output_gendtb_directory)
	print("gendtb output directory: \t<workspace>%s" % (output_gendtb_directory.removeprefix(dict['workspacepath'])))
	
	if os.path.exists(output_qc_dt_check_directory) == True:
		handle_clean(dict, output_qc_dt_check_directory)
	os.mkdir(output_qc_dt_check_directory)
	print("qc_dt_check output directory: \t<workspace>%s" % (output_qc_dt_check_directory.removeprefix(dict['workspacepath'])))
	
	#Perform all the compilation after the clean
	# Get all overlay files from Platform folder
	for root, dirs, files in os.walk(dict['platform_directory_path']):
		for dir in dirs:
			if dict['target'] in dir:
				if dict['workspace'] == "Q6":
					# In Q6/MPSS, OS.WALK is required as it will have multiple {config}
					# It will list all the dts files in all {config}
					inner_platform_path = os.path.join(root,dir)
					for root2, dirs2, files2 in os.walk(inner_platform_path):
						for dir2 in dirs2:
							for file in os.listdir(os.path.join(root2,dir2)):
								if(file.endswith(DTS_EXTN)):
									overlay_files_paths_list.append(os.path.join(root2, dir2, file))
				else:
					# overlay list for core boot
					for file in os.listdir(os.path.join(root,dir)):
						if(file.endswith(DTS_EXTN)):
							overlay_files_paths_list.append(os.path.join(root, dir, file))
	
	if dts_files_paths_list:
		files = dts_files_paths_list
	else:	
		# no dts files are found, exit out
		return
	
	# gendtb for overlay files
	for file in overlay_files_paths_list:
		dirs = (os.path.split(file.removeprefix(dict['platform_directory_path'])[1:])[0]).split(os.path.sep)
		platform_target_name = dirs[0]
		dirs.pop(0)
		output_gendtb_path = os.path.abspath(os.path.join(output_gendtb_directory, os.path.sep.join(dirs)))
		
		# Make directory (and subdirectories) for gendtb
		if not os.path.exists(output_gendtb_path):
			os.makedirs(output_gendtb_path)
		
		includeArg = os.path.join(dict['workspacepath'], PATH_DICT["dtspath"], INCLUDE_DIRECTORY)
		includeArg = includeArg + " " + os.path.join(dict['platform_directory_path'], platform_target_name, INCLUDE_DIRECTORY)
		
		return_code = run_gendtb(dict, file, output_gendtb_path, PATH_DICT["arch"], includeArg, COMPILE_OVERLAY_FLAG)
			
		if return_code != 0:
			return
	
	# move mkdir to for loop & check for config
	for file in files:
		# Generate output directory extension from [Image] (i.e. "config") and [PD]. Remove the slash as first character
		# And remove the filename from it.
		
		output_variant_directory = (str(file)).removeprefix(dict['soc_target_directory_path'])[1:]
		output_variant_directory = os.path.split(output_variant_directory)[0]
		
		if(file.endswith(DTS_EXTN)):
			if dict['workspace'] == "boot":
				output_qc_dt_check_path = output_qc_dt_check_directory
				output_gendtb_path = output_gendtb_directory
			elif dict['workspace'] == "Q6":
				#if config_arg:
				#	config = config_arg
				#else:
				#	config = Path(file).parent.name
				
				output_gendtb_path = os.path.abspath(os.path.join(output_gendtb_directory , output_variant_directory))
				
				output_qc_dt_check_path = os.path.abspath(os.path.join(output_qc_dt_check_directory, output_variant_directory))
				#print(output_qc_dt_check_path)
				# Make directory (and subdirectories) for gendtb
				if not os.path.exists(output_gendtb_path):
					os.makedirs(output_gendtb_path)
				
				# Make directory (and subdirectories) for qc_dt_check
				if not os.path.exists(output_qc_dt_check_path):
					os.makedirs(output_qc_dt_check_path)
			
			# Assign qc_dt_check output values to gendtb output's key (Dictionary)
			output_directories_dict[output_gendtb_path] = output_qc_dt_check_path

			# Call gendtb
			return_code = run_gendtb(dict, file, output_gendtb_path, PATH_DICT["arch"], dict['includeArg'])
			
			if return_code != 0:
				return
	
	projectschemapath = os.path.join(dict['output_directory'], OUTPUT_QC_DT_SCHEMA_CHECK_FOLDER)	
	projectschemapath = os.path.join(projectschemapath, PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)	
	
	if os.path.exists(projectschemapath) != True:
		error_msg = "Error: Project_schema.yaml Path [" + projectschemapath + "] does not exist"
		print(error_msg)

	command_qcdtcheck = ""

	print ("\n========================================================")
	print ("========================================================")
	print ("\t   SCRIPT 2 : RUNNING QC_DT_CHECK")
	print ("========================================================")
	print ("========================================================\n")
	
	validation_index = 1
	# FOR loop for every dts.pp generated images. Iterate through every items in the dict
	for output_gendtb_directory, output_qc_dt_check_directory in output_directories_dict.items():
		print_buffer = ("\n--------------------------------------------------------------------------")
		print_buffer += ("\nVALIDATING FILES in: %s" % (str(output_qc_dt_check_directory)))
		print(print_buffer)
		validation_index+=1
		
		if platform.system() == "Windows":
			command_qcdtcheck="python %s -d %s -u %s -r %s -t %s -p %s -o %s -w" % (dict['qcdtcheckpath'], 
																					dict['dtcpath'], 
																					output_gendtb_directory, 
																					projectschemapath, 
																					dict['dtschematoolspath'], 
																					dict['cpppath'],
																					output_qc_dt_check_directory)
			if dict['workspace'] == "boot":
				command_qcdtcheck += append_all_params_json(
														toolchain_data['ToolChain']['qc_dt_check']['Windows'], 
														"Params")
		else:
			command_qcdtcheck="chmod +x %s && python %s -d %s -u %s -r %s -t %s -p %s -o %s" % (dict['qcdtcheckpath'], 
																									dict['qcdtcheckpath'],
																									dict['dtcpath'], 
																									output_gendtb_directory, 
																									projectschemapath,
																									dict['dtschematoolspath'], 
																									dict['cpppath'],
																									output_qc_dt_check_directory)
	
		# Append arch for the tools
		if PATH_DICT["arch"] == "hexagon":
			command_qcdtcheck = command_qcdtcheck + " -m " + PATH_DICT["arch"]
	
		if dict['verbose']:
			command_qcdtcheck = command_qcdtcheck + " " + VERBOSE_OPTION
		
		if dict['verbose']:
			print ("Running ", command_qcdtcheck)
		
		return_code = os.system(command_qcdtcheck)

		if return_code != 0:
			error_logs_folders.append(output_gendtb_directory)
			if dict['verbose']:
				print("Error : SCRIPT 2 failed for [%s]" % (command_qcdtcheck))

	# FOR LOOP END


	print ("\n========================================================")
	print ("========================================================")
	print ("\t   END OF QC_DT_CHECK")
	print ("========================================================")
	print ("========================================================\n\n\n")

	if error_logs_folders:
		print("\n\nError: Validation failed for *.dts.pp files in following location (scroll above for failure logs):")
		for file in error_logs_folders:
			print("-  %s" % (file))
	
##############################################################################
# remove_json_comments
##############################################################################
def remove_json_comments(source_json_file,dest_json_file):
	dest_json = ""
	source_file_handle = open(source_json_file,"r")
	for line in source_file_handle:
		if line.lstrip().startswith("#"):
			dest_json += "\n"
			continue
		temp=line.split()
		if len(temp)==0:
			dest_json += "\n"
			continue
		else:
			dest_json += line.split("#")[0].strip("\n")
			dest_json += "\n"
	source_file_handle.close()
	return dest_json

def append_all_params_json(loaded_json_data, check_for):
	append_string = " "
	
	
	if check_for in loaded_json_data:
		for f in loaded_json_data[check_for]:
			append_string += f + " "
	
	return append_string
	
##############################################################################
# run_gendtb
##############################################################################
def run_gendtb(dict,file,output_gendtb_path, arch_local, inc_arg, compile_dtbo = False):
	command_gendtb = ["python"] 
	command_gendtb.append(dict['gendtbpath'])
	command_gendtb.append("-f")
	command_gendtb.append(file)
	command_gendtb.append("-o")
	command_gendtb.append(output_gendtb_path)
	command_gendtb.append("-c")
	command_gendtb.append(dict['cpppath'])
	command_gendtb.append("-d")
	command_gendtb.append(dict['dtcpath'])
	command_gendtb.append("-i")
	command_gendtb.append(inc_arg)
	
	if arch_local:
		command_gendtb.append("-a")
		command_gendtb.append(arch_local)
	
	if compile_dtbo == True:
		command_gendtb.append("-e")
		command_gendtb.append("dtbo")
	
	if dict['verbose']:
		print ("\nRunning [%s]\n" % (command_gendtb))
	
	return_code = sp.Popen(command_gendtb, stdout=sp.PIPE)
	stdout, stderr = return_code.communicate()
	
	if dict['verbose']:
		print("\n")
		for output_line in stdout.decode().splitlines():
			print(output_line)
	
	
	if return_code.returncode != 0:
		print("\n")
		print("Gendtb failed for %s" %(file))
		for output_line in stdout.decode().splitlines():
			print(output_line)
		
	return return_code.returncode

##############################################################################
# main
##############################################################################
def main():
	global Platform
	global toolchain_data
	Platform = sys.platform
	
	parser = argparse.ArgumentParser(description='Command-Line Tool to validate YAML and DT files')
	
	parser.add_argument("-s", "--target", help="SOC/Target name.")
	parser.add_argument("-i", "--include", help="Include Path(s) for DTSI files (include -I).", nargs='+')
	parser.add_argument("-v", "--verbose", action='store_true', help="Enable Verbose Output. Will print out paths.")
	# for future options
	parser.add_argument("-f", "--forceoutput", action='store_true', help="Print the forced output")
	parser.add_argument("-c", "--config", help="Optional filter to filter specific trees of dts/dtsi files", choices={"adsp", "cdsp", "gpdsp", "mpss"})
	# choices here as an array, for config
	
	args = parser.parse_args()
	# Create a dictionary
	#######################################################################
	dict = {'workspacepath' : '',
			'yamlpath' : '',
			'dtsfilespath' : '',
			'verbose' : '',
			'target' : '',
			'workspace': ''}
	
	print ("\n")
	
	dict['workspacepath'] = PATH_DICT["workspacepath"]		
	
	# Step 1: Handle Command-Line Arguments
	#######################################################################

	if args.target:
		dict['target'] = args.target
	else:
		error_msg = "Error: TARGET/SOC required using -s option. Exiting"
		sys.exit(error_msg)
	
	if PATH_DICT["arch"] == "arm":
		dict['workspace'] = "boot"
	elif PATH_DICT["arch"] == "hexagon":
		dict['workspace'] = "Q6"

	if dict['workspace'] == "boot":
		toolchain_json_file = PATH_DICT["toolchainpath"]

		if os.path.exists(toolchain_json_file) != True:
			error_msg = "WARNING: JSON [" + toolchain_json_file + "] does not exist"
			print(error_msg)

		toolchain_data = json.loads(remove_json_comments(toolchain_json_file, None))
	
	yamlpath = PATH_DICT["yamlpath"]
	
	if os.path.exists(yamlpath) != True:
		error_msg = "WARNING: YAML path [" + yamlpath + "] does not exist"
		print(error_msg)
		yamlpath = ""
	
	dict['yamlpath'] = yamlpath
	dts_path = Path(PATH_DICT['dtspath'])
	target = Path(dict['target'])
	
	global dts_files_paths_list, config_arg
	dts_files_paths_list = []
	config_arg = ""
	
	# TODO: Once new layout is generated, add "soc" folder before target.
	dtsfilespath = os.path.join(dict['workspacepath'], dts_path, target)
	
	# TODO: Check for Target without "soc" folder. If this does not exist, add "soc" folder
	# before target folder. if both does not exist, return an error
	if os.path.exists(dtsfilespath) != True:
		soc_directory = "soc"
		platform_directory = "platform"
		platform_default_directory = dict['target'] + "_default"
		if dict['workspace'] != "Q6":
			soc_directory = "Soc"
			platform_directory = "Platform"
			platform_default_directory = dict['target'] + "_Default"
		
		dtsfilespath = os.path.join(dict['workspacepath'], dts_path, soc_directory, target)
		if os.path.exists(dtsfilespath) != True:
			error_msg = "WARNING: Device tree path [" + dtsfilespath + "] does not exist"
			sys.exit(error_msg)
	
	soc_target_directory_path = dtsfilespath
	platform_directory_path = os.path.join(dict['workspacepath'], dts_path, platform_directory)
	platform_target_default_directory_path = os.path.join(platform_directory_path, platform_default_directory)
		
	if dict['workspace'] == "Q6" and args.config:
		config_arg = args.config
		dtsfilespath = os.path.join(dtsfilespath, config_arg)

	# Fetch all DTS files. Ignore OUTPUT_TOOL folder
	for root, dirs, files in os.walk(dtsfilespath):
		for file in files:
			if file.endswith(DTS_EXTN) and OUTPUT_TOOL_FOLDER not in root:
				dts_files_paths_list.append(os.path.join(root, file))
	
	dict['dtsfilespath'] = dtsfilespath
	dict['platform_directory_path'] = platform_directory_path
	
	if args.forceoutput:
		forceoutput = 1
	else:
		forceoutput = 0
	
	verbose = args.verbose
	
	dict['verbose'] = verbose
	if dict['verbose']:
		print_paths()
	includeArg = ""
	
	# Output Folder will be right at Target folder regarless of <config>
	dict['output_directory'] = os.path.join(soc_target_directory_path, OUTPUT_TOOL_FOLDER)
	dict['soc_target_directory_path'] = soc_target_directory_path
	
	if os.path.exists(dict['output_directory']) != True:
		os.mkdir(dict['output_directory'])
	print("OUTPUT Tool directory %s" % (dict['output_directory']))
	
	if dict['workspacepath'] != "":
		global INCLUDE_DIRECTORY
		if dict['workspace'] == "boot":
			INCLUDE_DIRECTORY = INCLUDE_DIRECTORY.capitalize()
		if args.include:
			includeArg = args.include
		else:
			includeArg = os.path.join(soc_target_directory_path, INCLUDE_DIRECTORY)
			includeArg = includeArg + " " + os.path.join(dict['workspacepath'], PATH_DICT["dtspath"], INCLUDE_DIRECTORY)
			includeArg = includeArg + " " + os.path.join(soc_target_directory_path)
			includeArg = includeArg + " " + os.path.join(platform_target_default_directory_path, INCLUDE_DIRECTORY)

	dict['includeArg'] = includeArg
	
	while True:
		print("\n========================================")
		print("\nCURRENT CONFIGURATION:")
		print("- TARGET/SOC: \t\t%s" %(dict['target']))
		print("- WORKSPACE: \t\t%s" % (dict['workspacepath']))
		print("- YAML FILE PATH: \t%s" % (dict['yamlpath']))
		print("- DTS FILE PATH: \t%s" % (dict['dtsfilespath']))
		print("- VERBOSE: \t\t%s" % (dict['verbose']))
		
		print("\n\n  ****** MENU ****** ")
		print("  1. Validate YAML file (create project-schema file)")
		print("  2. Validate DTSI file against project-schema (created in #1)")
		print("  0. Exit")
		try:
			choice = int(input("  Enter your choice: "))
		except ValueError:
			print("\n  Wrong Option. Enter Again")
			continue
		
		if choice == 1:
			exec_qc_dt_schema_check(dict)
		elif choice == 2:
			exec_qc_dt_check(dict)
		elif choice == 0:
			break
		else:
			print("\n  Invalid choice")
	
	print("\n\n****** End of qc_run_qc_dt_schema_check ******\n")

main()