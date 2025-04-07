#                                EDIT HISTORY
#
# This section contains comments describing changes made to the module.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 11/16/22   fi      Added functionality to start in deeper folder than manifest. e.g. boot_images\boot even though the manifest file started higher
# 11/07/22   fi      Ability to skip comments that are added to manifest files. Target folder is found dynamically now
# 10/10/22   fi      Reworked entire functionality of target manifest support and added whitespace removal
# 09/12/22   fi      Fixed logical errors for opposite check (found in list, not in build)
# 08/22/22   fi      Added logic for printing files not found in build, doesn't stop at first error
# 08/12/22   fi      Added support for custom manifest location and creation
# 07/22/22   fi      Initial Revision


from email.policy import default
from optparse import OptionParser
import os
import sys
from unicodedata import name


# Helper function to parse args from user and check for errors
def parse_arguements():
    parser = OptionParser()

    parser.add_option("-b", "--base-directory",
                      action="store", type="string", dest="base_directory",
                      help="Base directory name.")

    parser.add_option("-c", "--create-manifest",
                      action="store", type="string", dest="create_manifest",
                      help="Create manifest file in specified location. E.g C:\\Manifest.txt")

    parser.add_option("-f", "--manifest-location",
                      action="store", type="string", dest="manifest_location",
                      help="Existing common manifest file path. Not used for creation. For multiple, delimit with comma")
    
    parser.add_option("-t", "--target-name",
                      action="store", type="string", dest="target_name",
                      help="Existing target name. E.g. \"Pinnacles\".")
    
    parser.add_option("-l", "--create-log-file",
                      action="store", type="string", dest="log_file_path",
                      help="Create log file in specified location")


    (options, args) = parser.parse_args()


    # File or base directory must be supplied
    if not options.base_directory:
        parser.error("A base directory must be supplied.")

    if (not options.manifest_location and 
        not options.create_manifest):
        parser.error("A manifest file location must be supplied.")


    return options, parser


# Helper function to write manifest file to specified location
def create_manifest(options):
    # Create Manifest in specified location
    f=open(options.create_manifest, "w+")

    # Walk entire base directory and write each file path to manifest
    for root, dir_names, file_names in os.walk(options.base_directory):
        for file in file_names:
            # Remove path before base folder (e.g. "C:\JoeBob's_Folder\..."") resulting in relative path
            f.write(os.path.join(root, file).replace(options.base_directory + os.path.sep, ""))
            f.write('\n')

    f.close()


    # If no Target is specified, return
    if not options.target_name:
        return

    # Otherwise we create a target-specific manifest file
    # Get path to Target
    target_path = convert_target_name_to_path(options)

    os.chdir(target_path)

    f=open(options.target_name + "_Manifest.txt", "w+")

    for root, dir_names, file_names in os.walk(target_path):
        for file in file_names:
            # Remove path before base folder (e.g. "C:\JoeBob's_Folder\..."") resulting in relative path
            f.write(os.path.join(root, file).replace(options.base_directory + os.path.sep, ""))
            f.write('\n')

    f.close()
    

    return


# Log all errors to specified location or default filename
def create_log(options, manifest_list, files_not_found):
    f=open(options.log_file_path, "w+")
    if files_not_found:
        f.write("The following files exist in the base directory but NOT in the manifest file:\n")
        [f.write(i + "\n") for i in files_not_found]
        f.write("\n")

    if manifest_list:
        f.write("The following manifest entries were not found in the directory provided:\n")
        [f.write(i + "\n") for i in manifest_list]
    

    f.close()
    return


# Helper function to read a file and return as python list
def read_files_into_list(options):
    # Manifest_location could potentially have multiple entries. Delimit on comma
    manifest_file_paths = options.manifest_location.split(",")
    manifest_list = []


    # Find out how deep we are in a build folder.
    extraPath = ""
    if "boot_images" in options.base_directory:
        extraPath = options.base_directory.split("boot_images")
        extraPath ="boot_images" + extraPath[1] + os.path.sep


    # Read all manifest files into manifest_list
    for i in manifest_file_paths:
        f = open(i, "r")
        data = f.read()
        f.close

        # Convert string to use appropriate OS separator
        data = data.replace("\\", os.path.sep)
        data = data.replace("/", os.path.sep)
        
        manifest_list += data.split("\n")


    # Remove all trailing & leading whitespaces
    manifest_list = [i.strip() for i in manifest_list]

    # Remove all duplicates from manifest_list
    manifest_list = list(set(manifest_list))

    # Remove all empty strings caused from newlines in manifest files
    manifest_list[:] = [i for i in manifest_list if not i.startswith('\n')]
    
    # Remove all comments
    manifest_list[:] = [i for i in manifest_list if not i.startswith('#')]
    # manifest_list[:] = [i.split('#')[0] for i in manifest_list] TODO

    # Remove files found above base directory
    manifest_list[:] = [i for i in manifest_list if i.startswith(extraPath)]

    # Remove beginning of path to match user's base path
    manifest_list[:] = [i.replace(extraPath, "") for i in manifest_list]


    return manifest_list


# Helper function to convert target name input to a usable path
def convert_target_name_to_path(options):
    path_to_target = ""


    # Find folder with name of target. Double check that it has the correct path (.../QcomPkg/SocPkg)
    for root, dir_names, file_names in os.walk(options.base_directory):
        for dir in dir_names:
            if dir == options.target_name.capitalize():
                if os.path.join(root, dir).endswith("boot_images" + os.path.sep +
                                                    "boot" + os.path.sep +
                                                    "QcomPkg" + os.path.sep +
                                                    "SocPkg" + os.path.sep + 
                                                    options.target_name.capitalize()):
                    path_to_target = os.path.join(root,dir)
                    break
    
    # If no correct folder is found, exit
    if not path_to_target:
        print("Target folder not found. Please make sure your base directory is above the target folder hierarchically. Exiting...")
        exit(1)

    
    return path_to_target


# Walks the packed build and checks that each file exists in manifest and checks mismatches is found.
def compare_manifest(options, manifest_list, files_not_found):
    for root, dir_names, file_names in os.walk(options.base_directory):
        for file in file_names:
            # Remove path before base folder (e.g. "C:\JoeBob's_Folder\..."") resulting in relative path 
            # and check if file is in logged in manifest_list. If not, add to files_not_found.
            if os.path.join(root, file).replace(options.base_directory + os.path.sep, "") not in manifest_list:
                files_not_found.append(os.path.join(root, file).replace(options.base_directory + os.path.sep, ""))
            else:
                manifest_list.remove(os.path.join(root, file).replace(options.base_directory + os.path.sep, ""))


    # Any leftover files in manifest_list are files that are entered into the list that the os did not encounter during its walk
    if not manifest_list:
        print("\n1) All items from manifest list were found in the base directory.\n")
    else:
        print("\n1) The following manifest entries were not found in the directory provided:")
        [print(i) for i in manifest_list]

    # If files_not_found list is empty, all files were found in the manifest list
    if not files_not_found:
        print("2) Successfully verified that all files in base directory are recorded in the manifest files")
    else:
        print("\n2) The following files exist in the base directory but NOT in the manifest file:")
        [print(i) for i in files_not_found]
        print("\n\n")
        return 1 

    
    return 0


def main():
    manifest_list = []
    files_not_found = []
    flag = 0

    # Parse arguments
    options, parser = parse_arguements()


    # Create manifest file if specified by user
    if options.create_manifest:
        create_manifest(options)
        sys.exit("Successfully created manifest file(s)")


    # Populate python list with all files from manifest lists
    manifest_list = read_files_into_list(options)

    # Check manifest against base directory.
    flag = compare_manifest(options, manifest_list, files_not_found)

    # Create log if specified
    if (options.log_file_path):
        create_log(options, manifest_list, files_not_found)


    if flag:
        sys.exit(1)
    else:
         return 0


if __name__ == "__main__":
    main()