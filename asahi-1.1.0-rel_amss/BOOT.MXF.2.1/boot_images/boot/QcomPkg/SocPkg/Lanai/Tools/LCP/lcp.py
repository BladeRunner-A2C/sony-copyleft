#=============================================================================
# FILE:         lcp.py
#
# OVERVIEW:     LCP automation script, generate a new xbl_config.elf, convert a LCP configure 
#               JSON to LCP bin, update DCB bin to inlcude new LCP bin
#
#               Copyright (c) 2018-2023 Qualcomm Technologies, Inc.
#               All Rights Reserved.
#               Qualcomm Technologies Proprietary and Confidential.
#=============================================================================

import argparse
import os
import json
import struct
import shutil
import tempfile
import subprocess
import sys
import re
import time
import glob
import fnmatch
import platform
import json
import logging
import xml.etree.ElementTree as ET

if sys.version_info < (3, 8, 2):
      print("Must use Python 3.8.2 or greater")
      sys.exit(1)

DEBUG = False

def onerror(func, path, exc_info):
    """
    Error handler for ``shutil.rmtree``.

    If the error is due to an access error (read only file)
    it attempts to add write permission and then retries.

    If the error is for another reason it re-raises the error.

    Usage : ``shutil.rmtree(path, onerror=onerror)``
    """
    import stat
    if not os.access(path, os.W_OK):
        # Is the error an access error ?
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        raise Exception

def genremove(logger, rmpath):
    try:
        if os.path.isdir(rmpath):
            shutil.rmtree(rmpath, onerror=onerror)
        else:
            if os.path.isfile(rmpath):
                os.remove(rmpath)
            else:
                logger.debug(" %s is not present , skip delete", rmpath)
        time.sleep(1)
    except Exception as e:
        logger.debug(" could not remove path %s", rmpath)
        logger.debug(e)

def run_command(logger, cmd, errorkey=None, failonerror=True, Dly=0):
    errorcheck = False
    logger.info(" Running cmd: %s", cmd)
    logger.debug(cmd.split(" "))
    p = subprocess.Popen(cmd.split(" "), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    for c in iter(p.stdout.readline, b''):
        if errorkey is not None and errorkey in c:
            errorcheck = True
        logger.debug(c.decode('utf-8'))

    time.sleep(Dly)
    logger.debug(" popo1: %s", cmd)
    logger.debug(" popo2: %s", cmd)        
    logger.debug(" popo3: %s", cmd)

    for c in iter(p.stderr.readline, b''):
        if errorkey is not None and errorkey in c:
            errorcheck = True
        logger.debug(c.decode('utf-8'))

    if errorcheck:
        if failonerror:
            logger.error("[ERROR] found when running command, system_exit")
            sys.exit()
        logger.warning("[WARNING] Run command end with errorcheck=True")
        return False
    else:
        logger.debug(" Run command successfully")
        return True

#TODO: run-time auto-detect
LCPLibTargetSettings = {
    "SM8650" : {
        "ProfilePkg" : os.path.join("profiles","lanai","lanai_tme_security_profile.xml"),
        "OSPathDSFPkg" : os.path.join("SocPkg","Lanai"),
    },
}

class Dict2Obj(dict):

    def __getattr__(self, key):
        #print('getattr is called')
        if key not in self:
            return None
        else:
            value = self[key]
            if isinstance(value,dict):
                value = Dict2Obj(value)
            return value

class MemMap(object):
    def __init__(self, name, addr, size):
        self.regionName = name
        self.addr = addr
        self.size = size

class RegionSpace(object):
    def __init__(self, name, addr, end):
        self.name = name
        self.start = addr
        self.end = end

class LCPLib(object):
    
    """
    typedef struct
    {
        uint32 start;                   // Upper 20 bits (35:16) of region's starting address 
        uint32 end;                     // Upper 20 bits (35:16) of regino's ending address
        uint32 metadata;                // Upper 20 bits (35:16) of starting address of associated metadata region
        uint32 metadata_size_in_kb;     // metadata region size round up to 64KB for DARE only
        uint8  attr;                    // Region attributes (bit 0 - Encrypt, bit 1 - ECC, bit 2 - MTE, bit 3 - Meta Deta, bit 4 - DARE)
        uint8  arc_en;                  // 1 --> DARE with ANTI-REPLY COUNTER, 0 --> DARE w/o ANTI-REPLY COUNTER
        uint8  reserved1;               // Reserved for future use
        uint8  reserved2;               // Reserved for future use
    }
    LCP_ADDR_REGIONS_STRUCT;
    """
    # class globals
    BIN_NAMES = ["LCP"]
    LCP_ADDR_REGIONS_STRUCT_SIZE = 20
    LCP_HEADER_SIZE = 0 #Means no header
    total_dare_size = 0
    region_spaces = []

    def __init__(self, output_dir, boot_build=None, sectool_path=None, target=None, lcp_define_file=None):
        self.logger = logging.getLogger("lcp.LCPLib")
        if target is None: #default
            target = "SM8650"
            self.logger.warning("no target specified, use default")
        self.target = target
        self.logger.info("LCP target: %s", self.target)

        if boot_build is None:
            boot_build = os.path.dirname(os.path.realpath(__file__)).split("boot_images")[-2]
        self.boot_build = boot_build

        self.output_dir = output_dir
        self.xblconfig_tools_loaded = False
        self.force_copy = False
        self.sectools = sectool_path
        self.lcp_define_file = lcp_define_file
        if lcp_define_file is not None:
            self.logger.info("lcp define file: %s", lcp_define_file)
            with open(lcp_define_file) as f_lc:
                lcp_config = json.load(f_lc)
                self.lcp_config = Dict2Obj(lcp_config)
                #self.logger.info("LCP config %s", self.lcp_config)
        
        self.memmapxml_file = os.path.join(os.path.dirname(os.path.realpath(__file__)), "memmap.xml")
        if os.path.exists(self.memmapxml_file):
            self.logger.info("memmap file: %s", self.memmapxml_file)

    def __get_xblconfig_tools(self):
        # TODO: import tools
        try:
            self.logger.debug("__get_xbl_config_tools, init")
            tools_path = os.path.join(self.boot_build, "boot_images", "boot_tools", "XBLConfig")
            dest_path =os.path.join(self.output_dir, "xblconfig")
            if(self.force_copy or (not os.path.exists(dest_path))):
                if(not os.path.exists(tools_path)):
                    self.logger.error("%s is missed in boot build, please use a correct boot build!", tools_path)
                    sys.exit()
                genremove(self.logger, dest_path)
                shutil.copytree(tools_path, dest_path)
                self.logger.info("XBLConfig tools copied to: %s", dest_path)
            else:
                self.logger.info("NOT COPY XBLConfig tools to: %s", dest_path)
                self.logger.info("reason: folder exist: " + str(os.path.exists(dest_path)) + ", force_copy: " + str(self.force_copy))
                
            tools_path = self.sectools
            dest_path =os.path.join(self.output_dir, "sectools")
            if(self.force_copy or (not os.path.exists(dest_path))):
                if(not os.path.exists(tools_path)):
                    self.logger.error("%s is missed in boot build, please use a correct boot build!", tools_path)
                    sys.exit()
                genremove(self.logger, dest_path)
                shutil.copytree(tools_path, dest_path)
                self.logger.info("sectools copied to: %s", dest_path)
            else:
                self.logger.info("NOT COPY sectools to: %s", dest_path)
                self.logger.info("reason: folder exist: " + str(os.path.exists(dest_path)) + ", force_copy: " + str(self.force_copy))
        except Exception as e:
            self.logger.debug(e)
            self.logger.debug("__get_xbl_config_tools, exception on copy tool.")
        
        try:        
            genremove(self.logger, os.path.join(self.output_dir, "decompose"))
            os.makedirs(os.path.join(self.output_dir, "decompose"))
            genremove(self.logger, os.path.join(self.output_dir, "compose"))
            os.makedirs(os.path.join(self.output_dir, "compose"))
            self.xblconfig_tools_loaded = True
            self.logger.debug("__get_xbl_config_tools, end")
        except Exception as e:
            self.logger.debug(e)
            self.logger.debug("__get_xbl_config_tools, exception on removing decompose or compose")
            return False

    def decompose_xblconfig(self, xbl_config):

        if not self.xblconfig_tools_loaded:
            self.__get_xblconfig_tools()
        
        os.chdir(os.path.join(self.output_dir, "xblconfig"))
        cmd = "python GenXBLConfig.py -d %s -f ELF -o %s" %(xbl_config, os.path.join(self.output_dir, "decompose"))
        self.logger.debug(cmd)
        run_command(self.logger, cmd)
        return os.path.join(self.output_dir, "decompose")

    def __compose_xblconfig(self, name_tag=None):
        xbl_name = "xbl_config"

        if not self.xblconfig_tools_loaded:
            self.__get_xblconfig_tools()

        os.chdir(os.path.join(self.output_dir, "xblconfig"))
        input_json = os.path.join(self.output_dir, "decompose", "create_xbl_config.json")
        bin_path = os.path.join(self.output_dir, "decompose")

        if(name_tag is not None):
            xbl_name = xbl_name+name_tag
        output = os.path.join(self.output_dir, "compose", xbl_name)
        sectools_path = os.path.join(self.output_dir, "sectools", platform.system())
        sec_prof = os.path.join(self.boot_build, "boot_images", "ssg_tmefwrel", LCPLibTargetSettings[self.target]["ProfilePkg"])
        if os.path.exists(sec_prof):
            cmd = "python GenXBLConfig.py -i %s -b %s -f ELF -o %s --sectools_directory %s --sectools_version v2 --sign_id XBL-CONFIG --security_profile %s --signing_mode %s" %(input_json, bin_path, output, sectools_path, sec_prof, "TEST")
            run_command(self.logger, cmd, Dly=25)

            xbl_name = xbl_name + ".elf"
        else:
            self.logger.debug("file %s doesn't exist, please make sure you are using a correct boot build!", sec_prof)
            sys.exit()

        return os.path.join(self.output_dir, "compose", xbl_name)

    @staticmethod
    def bytes_crc32(bytes):
        CRC_POLYNOMIAL = 0x04C11DB7
        CRC_INITVAL = 0xFFFFFFFF
        CRC_XOROUT = 0xFFFFFFFF

        result = CRC_INITVAL
        for octet in bytes:
            if type(octet) is str:
                octet = struct.unpack("B", octet)[0]
            for bit in range(0,8):
                if (octet >> 7) ^ (result >> 31):
                    result = ((result << 1) & 0xFFFFFFFF) ^ CRC_POLYNOMIAL
                else:
                    result = (result << 1) & 0xFFFFFFFF
                octet = (octet << 1) & 0xFF

        result = result ^ CRC_XOROUT
        return result

    def GenDcbBin(self, header_file, dcb_file, bin_files, output_path, output_file):
        binaries_ordered_by_header_index = []
        DCB_MAX_SIZE = 0

        if os.path.exists(header_file):
            define_re = re.compile(r'^#define[ \t]+([A-Z_]+)[ \t]+([\(\)\+\-\*\/0-9 xA-F]+)$')
            first = re.compile(r'^\s+DDI_INPUT_IDX.*?')
            reclaim = re.compile(r'^\s+RECLAIM_IDX.*?$')
            max = re.compile(r'^\s+DCB_IDX_MAX.*?$')
            cfg = re.compile(r'^\s+([A-Z0-9_]+)_CFG_IDX.*?$')
            idx = re.compile(r'^\s+([A-Z0-9_]+)_IDX.*?$')
            with open(header_file,"r") as dcb_header_fp:
                ignore = True
                for line in dcb_header_fp:
                    # Remove comments
                    line = line.split("//")[0]
                    # Check for a macro defined as a value or formula
                    m = define_re.match(line)
                    if m:
                        if m.group(1) == "DCB_MAX_SIZE":
                            DCB_MAX_SIZE = eval(m.group(2))
                        continue

                    # DDI_INPUT_IDX
                    match = first.match(line)
                    if match:
                        ignore = False
                
                    if ignore == False:
                        # RECLAIM_IDX
                        match = reclaim.match(line)
                        if match:
                            continue
                                
                        # DCB_IDX_MAX
                        match = max.match(line)
                        if match:
                            break
                            
                        # _CFG_IDX
                        match = cfg.match(line)
                        if match:
                            binaries_ordered_by_header_index.append(match.group(1))
                            continue
                            
                        # _IDX
                        match = idx.match(line)
                        if match:
                            if match.group(1) not in ["DCB_CRC", "DCB_SIZE", "DSF_MAINLINE_VERSION", "DSF_MAJOR_VERSION", "DSF_MINOR_VERSION"]:
                                binaries_ordered_by_header_index.append(match.group(1))
                            continue
        else:
            if self.target == 'SM8650':
                binaries_ordered_by_header_index = [#'DCB_CRC',
                                                    #'DCB_SIZE',
                                                    #'DSF_MAINLINE_VERSION',
                                                    #'DSF_MAJOR_VERSION',
                                                    #'DSF_MINOR_VERSION',
                                                    'DDI_INPUT',
                                                    'RUNTIME',
                                                    'LCP_INPUT_STRUCT',
                                                    'MC_PXI_PRE_TRAINING',
                                                    'MC_PXI_RD',
                                                    'MC_PXI_WR',
                                                    'MC_PXI_RCW',
                                                    'MC_PXI_WRLVL',
                                                    'MC_PXI_CBT',
                                                    'SAVE_RESTORE',
                                                    'TRAINING_PARAMS',
                                                    'LCP',
                                                    'MC_STATES',
                                                    'SHUB_STATES',
                                                    'SHRM_STATES',
                                                    'DEFAULT_ALC_POLICY',
                                                    'ALC_TIMINGS',
                                                    'ALC_POLICY_INDEX',
                                                    'PERF_MODE_ALC_POLICY',
                                                    'PMIC_SETTINGS',
                                                    'MIN_DDR_SHUB_RATIO',
                                                    'MIN_SHUB_CP',
                                                    'ECDT_PRE_DEVICE_INIT',
                                                    'ECDT_POST_DEVICE_INIT',
                                                    'DDRSS',
                                                    'NOC',
                                                    'SHRM',
                                                    'SHRM2',
                                                    'MCCC_MSTR',
                                                    'MCCC_SLV',
                                                    'DDRPHY',
                                                    'MC',
                                                    'LLCC',
                                                    'AHB2PHY',
                                                    'SHRM_DUMP']

                DCB_MAX_SIZE = ((1024*50)+4)

        self.logger.info("DCB_MAX_SIZE: %d", DCB_MAX_SIZE)
        self.logger.info("binaries_ordered_by_header_index: %s", binaries_ordered_by_header_index)

        import struct
        dcbBinDict = {}
        DCB_CRC = 0
        DCB_SIZE = 0
        DSF_MINOR_VERSION = 0
        DSF_MAJOR_VERSION = 0
        DSF_MAINLINE_VERSION = 0
        with open(dcb_file, "rb") as dcb_fp:
            DCB_CRC = struct.unpack("<I", dcb_fp.read(4))[0]
            DCB_SIZE = struct.unpack("<I", dcb_fp.read(4))[0]
            DSF_MAINLINE_VERSION = struct.unpack("<I", dcb_fp.read(4))[0]
            DSF_MAJOR_VERSION = struct.unpack("<I", dcb_fp.read(4))[0]
            DSF_MINOR_VERSION = struct.unpack("<I", dcb_fp.read(4))[0]
            header_offset = 20
            for bin in binaries_ordered_by_header_index:
                bin_off = struct.unpack("<H", dcb_fp.read(2))[0]
                bin_size = struct.unpack("<H", dcb_fp.read(2))[0]
                header_offset += 4
                
                self.logger.info("bin_off: %d", bin_off)
                self.logger.info("bin_size: %d", bin_size)
                self.logger.info("header_offset: %d", header_offset)

                if bin in bin_files:
                    with open(bin_files[bin], "rb") as bin_f:
                        dcbBinDict[bin] = bin_f.read()
                else:
                    if bin_off != 0:
                        dcb_fp.seek(bin_off)
                        dcbBinDict[bin] = dcb_fp.read(bin_size)
                        dcb_fp.seek(header_offset)
        
        output = ""
        
        # Calculate header size
        # len(DSF.binaries_ordered_by_header_index) 
        # + 3 for DCB_CRC_IDX, DCB_SIZE_IDX, DSF_MAINLINE_VERSION_IDX, DSF_MAJOR_VERSION_IDX, & DSF_MINOR_VERSION_IDX
        # which are not part of DSF.binaries_ordered_by_header_index array
        header_max_size = (len(binaries_ordered_by_header_index) + 5) * 4

        # Make header a multiple of 8 bytes for proper pointer alignment
        remainder = header_max_size % 8
        if remainder != 0:
            header_max_size += (8 - remainder)

        # Header bytes object
        header = bytes()

        # Data bytes object
        data = bytes()

        # Data starts at end of header
        offset = header_max_size

        # Loop through each binary section of DCB
        for bin in binaries_ordered_by_header_index:
            # Check if DCB sub-block exists
            if bin in dcbBinDict:
                # Update header
                size = len(dcbBinDict[bin])
                header += struct.pack("<H", offset)
                header += struct.pack("<H", size)
                offset += size

                # Update data
                data += dcbBinDict[bin]
                
                # Align each section of DCB to 8 byte boundary
                remainder = offset % 8
                if remainder != 0:
                    remainder = 8 - remainder
                for _ in range(remainder):
                    data += struct.pack("<B", 0)
                offset += remainder
            else:
                header += struct.pack("<H", 0)
                header += struct.pack("<H", 0)
                self.logger.warning("[WARNING] {:s} DCB sub-block not populated".format(bin))

        # DSF Version
        header = struct.pack("<I", DSF_MINOR_VERSION) + header
        header = struct.pack("<I", DSF_MAJOR_VERSION) + header
        header = struct.pack("<I", DSF_MAINLINE_VERSION) + header
        # Size of DCB including header
        size = len(data) + header_max_size
        header = struct.pack("<I", size) + header

        # CRC set to zero as placeholder for CRC calculation
        header = struct.pack("<I",0) + header

        # Pad header with zeros
        header = header.ljust(header_max_size, b'\0')

        # Combine header and data
        binary = header + data

        # Pad binary with zeros
        binary = binary.ljust(DCB_MAX_SIZE, b'\0')

        # Calculate CRC on entire DCB binary
        crc = self.bytes_crc32(binary)

        # Replace placeholder CRC
        binary = struct.pack("<I", crc) + binary[4:]

        # Print information on which XL file is being processed and resulting binary
        # Print CRC and size information
        self.logger.info("[INFO] DCB {:s}, CRC 0x{:08X}, {:d}B free ({:d}/{:d} used)".format(
            os.path.basename(output_file),
            crc,
            DCB_MAX_SIZE - size,
            size,
            DCB_MAX_SIZE))

        # Write to file
        with open(os.path.join(output_path, output_file), "wb") as f:
            f.write(binary)

    def gen_xbl_config(self, dcb_input, lcp_input=None, name_tag=None):
        # create new dcb based on old dcb, lcp input
        header_file =os.path.join(self.boot_build, "boot_images", "boot", "QcomPkg", LCPLibTargetSettings[self.target]["OSPathDSFPkg"], "Library", "DSFTargetLib", "interface","header","api","ddr_shared_interface.h")
        binpaths = {}
        if lcp_input is not None:
            try:
                self.logger.debug("name: %s", os.path.basename(lcp_input))
                if ".bin" in os.path.basename(lcp_input):
                    for bin in LCPLib.BIN_NAMES:
                        if bin in os.path.basename(lcp_input):
                            index = LCPLib.BIN_NAMES.index(bin)
                            binpaths[LCPLib.BIN_NAMES[index]] = lcp_input
                            self.logger.debug("Matched bin to LCPLib BIN_NAMES name:%s path:%s", LCPLib.BIN_NAMES[index], lcp_input)
                            break
                else:
                    self.logger.error("Could not match LCPLib BIN_NAMES with: " + lcp_input + ", please provide a correct LCP.bin file!")
                    sys.exit()    
            except ValueError:
                self.logger.error("Could not match LCPLib BIN_NAMES with: " + lcp_input + ", please provide a correct LCP.bin file!")
                sys.exit()

         
        for dcb_bin in glob.glob(dcb_input + '/*_dcb.bin'):
            # save off the input DCB for debug, new DCB will be generated in its place
            if (os.path.exists(dcb_input)):
                original_dcb = os.path.join(dcb_input, "orig_"+os.path.basename(dcb_bin))
                shutil.move(dcb_bin,original_dcb)
                self.GenDcbBin(header_file, original_dcb, binpaths, os.path.join(self.output_dir, "decompose"), dcb_bin)

        if(name_tag is not None):
            return self.__compose_xblconfig(name_tag)
        return self.__compose_xblconfig()

    def update_dcb_bin(self, dcb_path, lcp_input=None):
        # create new dcb based on old dcb, lcp input
        header_file =os.path.join(self.boot_build, "boot_images", "boot", "QcomPkg", LCPLibTargetSettings[self.target]["OSPathDSFPkg"], "Library", "DSFTargetLib", "interface","header","api","ddr_shared_interface.h")
        binpaths = {}
        if lcp_input is not None:
            try:
                self.logger.debug("name: %s", os.path.basename(lcp_input))
                if ".bin" in os.path.basename(lcp_input):
                    for bin in LCPLib.BIN_NAMES:
                        if bin in os.path.basename(lcp_input):
                            index = LCPLib.BIN_NAMES.index(bin)
                            binpaths[LCPLib.BIN_NAMES[index]] = lcp_input
                            self.logger.debug("Matched bin to LCPLib BIN_NAMES name:%s path:%s", LCPLib.BIN_NAMES[index], lcp_input)
                            break
                else:
                    self.logger.debug("Could not match LCPLib BIN_NAMES with: " + lcp_input + ", please provide a correct LCP.bin file!")
                    sys.exit()
            except ValueError:
                self.logger.debug("Could not match LCPLib BIN_NAMES with: " + lcp_input + ", please provide a correct LCP.bin file!")
                sys.exit()
                    
        for dcb_bin in glob.glob(dcb_path + '/*_dcb.bin'):
            # save off the input DCB for debug, new DCB will be generated in its place
            if (os.path.exists(dcb_path)):
                original_dcb = os.path.join(dcb_path, "orig_"+os.path.basename(dcb_bin))
                shutil.move(dcb_bin,original_dcb)
                self.GenDcbBin(header_file, original_dcb, binpaths, os.path.join(self.output_dir, "decompose"), dcb_bin)

    def get_reservedRegions(self, memmap_xml):
        self.ReservedRegionSpaces = [] 
        if os.path.exists(self.memmapxml_file) == False:
            return
        
        self.memap = []
        memmap = []
        memmap_xml_tree = ET.parse(memmap_xml)
        memmap_xml_root = memmap_xml_tree.getroot()
        for Region in memmap_xml_root.findall("./Product/Software/Variant/Region"):
            addr = int(Region.attrib["addr"].replace("0x", ""), 16) 
            if "K" in Region.attrib["size"]:
                size = float(Region.attrib["size"].replace("K", "")) * 1024
            elif "M" in Region.attrib["size"]:
                size = float(Region.attrib["size"].replace("M", "")) * 1024 * 1024
            elif "0x" in Region.attrib["size"]:
                size = int(Region.attrib["size"].replace("0x", ""), 16) 
            map = MemMap(Region.attrib["name"], addr, int(size))    
            memmap.append(map)    

        memmap.sort(key=lambda x: x.addr)

        i = 0
        print(len(memmap))
        while i < len(memmap):
            region = memmap[i]
            addr = region.addr
            endAddr = region.addr + region.size
            if "Reserved" in region.regionName or \
                "VM_KERNEL_MEM" in region.regionName or \
                "DARE-TZ" in region.regionName or \
                r'TA/Tags' in region.regionName :
                i = i + 1
                continue
            
            if r'TA' in region.regionName and r'Tags' in memmap[i + 1].regionName :
                i = i + 2
                continue

            j = i + 1
            while j < len(memmap):
                if memmap[j].addr >= addr and memmap[j].addr + memmap[j].size <= endAddr:
                    j = j + 1
                    continue
                else:
                    self.memap.append(region) 
                    i = j - 1
                    break

            if i + 1 == len(memmap):
                self.memap.append(region) 
                
            i = i + 1
        
        for map in self.memap:
            region = RegionSpace(map.regionName, map.addr, map.addr + map.size - 1) 
            self.ReservedRegionSpaces.append(region)
            #self.logger.info("name: '%s', start: '0x%X', end:'0x%X'", region.name, region.start, region.end)

    def get_availableAddressSpacess(self):
        self.AvailableRegionSpaces = []
        for space in self.lcp_config.ddr_spaces:
            spaceStartTemp = space["start"]
            spaceEndTemp = space["end"]
            
            for regionReserved in self.ReservedRegionSpaces:
                if regionReserved.start < space["start"] or regionReserved.start > space["end"]:
                    continue
                
                validSpace = []
                if regionReserved.start > spaceStartTemp and regionReserved.end < spaceEndTemp:
                    validSpace = RegionSpace("", spaceStartTemp, regionReserved.start - 1)
                    spaceStartTemp = regionReserved.end + 1
                    self.AvailableRegionSpaces.append(validSpace)
                else:
                    spaceStartTemp = regionReserved.end + 1
            
            if spaceStartTemp >= space["start"] and spaceStartTemp < space["end"]:
                validSpace = RegionSpace("", spaceStartTemp, space["end"] -1)
                self.AvailableRegionSpaces.append(validSpace)

        #for validSpace in self.AvailableRegionSpaces:
        #    self.logger.info("name: '%s', start: '0x%X', end:'0x%X'", validSpace.name, validSpace.start, validSpace.end)
      
    def GetLCPRegionDefaultStart(self, regionName):
        for region in self.lcp_config.lcp_regions:
            if region["name"] == regionName:
                if len(region["default_start"]) != 0:
                    return int(region["default_start"].replace("0x", ""), 16) 
                else:
                    return 0x0
        return 0x0
                   
    def region_address_check(self, region_name, region_start, region_size, region_type):
        region_space={}
        if region_start == 0 and region_size == 0:
            return True

        region_alignment={}
        for alignment in self.lcp_config.lcp["alignments"]:
            if alignment["hexcode"] ==  region_type["alignment"]:
                region_alignment = alignment.copy()
                break
        
        if region_alignment["hexcode"] != 0 and (region_start << 16) % region_alignment["value"] != 0:
            self.logger.error("'%s' region's start should be %s", region_name, region_alignment["name"])
            return False
        
        region_end = (((region_start << 16) + region_size * 1024) - 1) >> 16
              
        if region_type["name"] == "DARE": #DARE Tag Size(in bytes) = ROUND_UP(region_size_in_bytes / 8 + region_size_in_bytes / 8 + region_size_in_bytes / 64 + region_size_in_bytes / 512 + region_size_in_bytes / 4096 + 2048, 64KB)  
            tagSize =  (((region_size * 1024) >> 10) * 1097 // 4096 + 2) << 10 #bytes
            if tagSize % (64 * 1024) != 0: 
                tagSize = (tagSize // (64 * 1024) + 1) * (64 * 1024)
            region_end = ((region_end << 16) + tagSize) >> 16
        elif region_type["name"] == "DAE": #DAE Tag Size(in bytes) =  ROUND_UP(region_size_in_bytes / 8, 64KB)  
            tagSize =  (region_size * 1024) / 8 #bytes
            if tagSize % (64 * 1024) != 0: 
                tagSize = (tagSize // (64 * 1024) + 1) * (64 * 1024)
            region_end = ((region_end << 16) + int(tagSize)) >> 16

        if "TA" in region_name and region_start != 0:
                self.logger.error("'%s' region's start should always be '0', it cannot be configured by user!", region_name)
                return False
        elif "S2 SPT" in region_name and (region_start != 0 or region_size != 0):
                self.logger.error("'%s' region's start and end should always be '0', it cannot be configured by user!", region_name)
                return False
        else:
            if "TA" in region_name:
                region_start = self.GetLCPRegionDefaultStart("TA S1")
                if region_start != 0x0:
                    region_start = region_start >> 16
                    if "TA S1" in region_name:
                        region_end = region_start + region_end
                        region_space["name"] = region_name
                        region_space["start"] = region_start
                        region_space["size"] = region_end
                        region_space["type"] = region_type
                        LCPLib.region_spaces.append(region_space)                    
                    elif "TA S2" in region_name:
                        TA_S1_exist = False
                        for index, value in enumerate(LCPLib.region_spaces):
                            if "TA S1" in value["name"]:
                                TA_S1_exist = True
                                region_space["name"] = "TA S1 + TA S2"
                                region_end = LCPLib.region_spaces[index]["size"] + region_end + 1
                                LCPLib.region_spaces[index]["name"] = "TA S1 + TA S2" 
                                LCPLib.region_spaces[index]["size"] = region_end 
                              
                        if TA_S1_exist == False:
                            region_end = region_start + region_end
                            region_space["name"] = "TA S1 + TA S2"
                            region_space["start"] = region_start
                            region_space["size"] = region_end
                            region_space["type"] = region_type
                            LCPLib.region_spaces.append(region_space)

            available = False
            address_range = ""
            for ddr_space in self.AvailableRegionSpaces:
                if region_start < (ddr_space.start >> 16) or region_start > (ddr_space.end >> 16):
                    available |= False
                elif region_end < (ddr_space.start >> 16) or region_end > (ddr_space.end  >> 16):
                    available |= False
                else:
                    available |= True
                address_range += ("0x{:X} - 0x{:X}").format(ddr_space.start>> 16, ddr_space.end  >> 16) + "\n"

            if  available == False:
                error_string = ("'{}' region's address range: 0x{:X} - 0x{:X}").format(region_name, region_start, region_end)
                self.logger.error(error_string)
                error_string = "Address must reside in the DDR space: \n" + address_range + "please configure correct region start or size(end)!"
                self.logger.error(error_string)
                return False
            
            if "TA" not in region_name and "S2 PT" not in region_name:
                region_space["name"] = region_name
                region_space["start"] = region_start
                region_space["size"] = region_end
                region_space["type"] = region_type
                LCPLib.region_spaces.append(region_space)
                
                for space in LCPLib.region_spaces:
                    if space["name"] != region_name:
                        if (region_end < space["size"] and region_end > space["start"]) or \
                            (region_start < space["size"] and region_start > space["start"]) or \
                            (region_start < space["start"] and region_end > space["size"]) or \
                            (region_start < space["size"] and region_end > space["start"]):  
                            self.logger.error("\n***ERROR***")
                            
                            if space["type"] == "DARE" or space["type"] == "DAE":
                                self.logger.error("'%s' region start: '0x%X' end(with tags): '0x%X'", space["name"], space["start"], space["size"])
                            else:
                                self.logger.error("'%s' region start: '0x%X' end: '0x%X'", space["name"], space["start"], space["size"])
    
                            if region_type == "DARE" or region_type == "DAE":
                                self.logger.error("'%s' region start: '0x%X' end: '0x%X'", region_name, region_start, region_end)
                            else:
                                self.logger.error("'%s' region start: '0x%X' end: '0x%X'", region_name, region_start, region_end) 
                            
                            self.logger.error("'%s' region overlaps '%s' region, please decrease its size(end) or change start address!", region_name, space["name"])
                            self.logger.error("***ERROR***\n")
                            available = False
                            return False
                    else:
                        continue
            
            return True

    def region_type_check(self, region_name, region_size, region_types, region_attr, region_arc_en):    
        region_type = {}
        available_type = True
        for type in self.lcp_config.lcp["TYPE"]:
            if type["enable"] == 1 and region_attr == (0x1 << type["hexcode"]):  
                available_type = True
                break
            else:
                available_type = False
        
        if region_name == "TA S1" and available_type == False and region_size != 0:
            for type in self.lcp_config.lcp["TYPE"]:
                if type["name"] == "DARE":
                    #region_type = type.copy()
                    self.logger.error("'%s' region's type must be %s(attr:%s, arc_en:%s)", region_name, type["name"], 0x1<<type["hexcode"], type["anti-reply"])
                    break
            return region_type
        
        if region_attr == 0 and region_arc_en == 0:
            for type in self.lcp_config.lcp["TYPE"]:
                if type["name"] == "Encrypt":
                    region_type = type.copy()
                    region_type["name"] = "DDR plain"
                    break
        elif region_attr == 0 and region_arc_en > 0:
            self.logger.error("'%s' region's arc_en is non-zero value %s, but its attr is %s, please configure a correct attr and arc_en for this LCP region", region_name, region_attr, region_arc_en)
        else:
            if available_type == True:
                if region_arc_en == 0 or region_arc_en == 1:
                    for type in self.lcp_config.lcp["TYPE"]:
                        if type["enable"] == 1 and (region_attr & (0x1 << type["hexcode"])) == 0x1 << type["hexcode"]:
                            region_type = type.copy()
                            if(region_arc_en == 1) and type["anti-reply"] == 1:
                                break
                elif region_arc_en > 1:
                    self.logger.error("'%s' region's arc_en should be '0' or '1', please configure a correct attribute for this LCP region", region_name)
            else:
                type_string = ""
                for type_name in region_types:
                    for type in self.lcp_config.lcp["TYPE"]:
                        if type_name == type["name"] and type["enable"] == 1:
                            type_string += str(0x1<<type["hexcode"]) +"(" +type["name"]  + ")" + " or "
                type_string = type_string.strip().rstrip('or')
                self.logger.error("'%s' region's attr is configured as %s, it is not %s, please configure a correct attribute for this LCP region", region_name, region_attr, type_string)    

        return region_type
 
    def region_size_check(self, region_name, size, region_type):
        for multiple in self.lcp_config.lcp["multiples"]:
            if multiple["hexcode"] ==  region_type["multiple"]:
                region_multiple = multiple.copy()
                break
          
        # for alignment in self.lcp_config.lcp["alignment"]:
        #     if alignment["hexcode"] ==  region_type["alignment"]:
        #         region_alignment = alignment.copy()
        #         break

        if region_multiple["hexcode"] != 0 and size * 1024 % region_multiple["value"] != 0:
            self.logger.error("'%s' region's end(size) should be %s", region_name, region_multiple["name"])
            return False
        
        # if region_alignment["hexcode"] != 0 and size * 1024 % region_alignment["value"] != 0:
        #     self.logger.error("Region %s should be %s", region_name, region_alignment["name"])
        #     return False
        
        return True
    
    def region_restriction_check(self, region, region_index):
        self.logger.info("\n")
        self.logger.info("===Region '%s' restriction check--START!===", region["name"])
        region_description = self.lcp_config.lcp_regions[region_index]["description"]
        
        #region_size's unit is "KB"
        region_max_size = self.lcp_config.lcp_regions[region_index]["max_size"]
        if len(region_max_size) == 0:
            region_max_size = "no restriction"
        else:
            region_max_size = int(self.lcp_config.lcp_regions[region_index]["max_size"].replace('KB',''))
        region_name = region["name"] #self.lcp_config.lcp_regions[region_index]["name"]
        region_start = region["regionData"]["start"]
        region_size = region["regionData"]["size"]
        region_attr = region["regionData"]["attr"]
        region_arc_en = region["regionData"]["arc_en"]
        region_types = self.lcp_config.lcp_regions[region_index]["valid_types"].split("+")
        
        self.logger.info("region_index: %s", region_index + 1)
        self.logger.info("region_name: %s", region_name)
        self.logger.info("region_description: %s", region_description)
        self.logger.info("region_start: 0x%X", region_start)
        self.logger.info("region_size: 0x%X", region_size)
        self.logger.info("region_attr: 0x%X", region_attr)
        self.logger.info("region_arc_en: 0x%X", region_arc_en)
        self.logger.info("region_max_size: %s", region_max_size)
        
        region_type = self.region_type_check(region_name, region_size, region_types, region_attr, region_arc_en)
        
        if len(region_type) == 0:
            return False
        
        self.logger.info("region_type: %s", region_type["name"])
        self.logger.info("region_types: %s", region_types)

        if region_name != self.lcp_config.lcp_regions[region_index]["name"]:
            self.logger.error("'%s' region is not supported, please check if this region is defined in the file %s", region_name, self.lcp_define_file)
            return False
        
        if region_name == "S2 PT":
            if region_start != 0 or region_size != 0:
                self.logger.error("'%s' region, its start and size(end) is not permitted for user to configure, please leave them to '0'", region_name)
                return False

        if region_max_size != "no restriction" and region_size > region_max_size:
            self.logger.error("'%s' region's size(end) can not exceed %s", region_name, region_max_size)
            return False
        
        if False == self.region_size_check(region_name, region_size, region_type):
            return False
        
        if False == self.region_address_check(region_name, region_start, region_size, region_type):
            return False
        
        for type in self.lcp_config.lcp["TYPE"]:
            if type["name"] == "DARE":
                dare_hexCode = type["hexcode"]

        if region_type["name"] == "DARE":
            LCPLib.total_dare_size += region_size

        self.logger.info("===Region '%s' restriction check--END!===", region["name"])

        return True

    def convert_json2bin(self, lcp_json_file):
        self.get_reservedRegions(self.memmapxml_file)
        self.get_availableAddressSpacess()
        self.logger.info("====Convert a LCP JSON file to a bin file====")
        self.logger.info("lcp_json_file: %s", lcp_json_file)
        lcp_file = Dict2Obj(json.load(open(lcp_json_file)))

        NUM_LCP_ADDR_REGIONS = int(self.lcp_config.lcp["NUM_LCP_ADDR_REGIONS"])
        NUM_RESERVED_FOR_INTERNAL_USE = int(self.lcp_config.lcp["NUM_RESERVED_FOR_INTERNAL_USE"])
        
        self.logger.info("NUM_LCP_ADDR_REGIONS: %s", NUM_LCP_ADDR_REGIONS)
        self.logger.info("NUM_RESERVED_FOR_INTERNAL_USE: %s", NUM_RESERVED_FOR_INTERNAL_USE)
        
        lcp_bin_file = os.path.basename(lcp_json_file).replace(".json", ".bin")
        lcp_bin_file = os.path.join(self.output_dir, lcp_bin_file)
        self.logger.info("lcp_bin_file: %s", lcp_bin_file)
        with open(os.path.join(self.output_dir, lcp_bin_file), "wb") as f:
            region_index = 0
            for lcpRegion in lcp_file.lcpRegions:
                if NUM_LCP_ADDR_REGIONS != len(lcpRegion["regions"]):
                    self.logger.error("The number of lcp regions in JSON file %s is %s", lcp_json_file, len(lcpRegion["regions"]))
                    self.logger.error("Please provide a correct LCP JSON file!")
                    f.close()
                    if os.path.exists(lcp_bin_file):
                        os.remove(lcp_bin_file)
                    return

                for region in lcpRegion["regions"]:
                    regionData = region["regionData"]
                    if region_index < NUM_RESERVED_FOR_INTERNAL_USE:
                        if regionData["start"] != 0 or \
                            regionData["size"] != 0 or \
                            regionData["attr"] != 0 or \
                            regionData["arc_en"] != 0:
                            self.logger.error("The first %s region(s) is reserved for internal use, all fields should be kept to '0'!", NUM_RESERVED_FOR_INTERNAL_USE)
                            
                            f.close()
                            if os.path.exists(lcp_bin_file):
                                os.remove(lcp_bin_file)
                            return

                    if region_index >= NUM_RESERVED_FOR_INTERNAL_USE:
                        if self.region_restriction_check(region, region_index - NUM_RESERVED_FOR_INTERNAL_USE) == False:
                            f.close()
                            if os.path.exists(lcp_bin_file):
                                os.remove(lcp_bin_file)
                            return
                    
                    #The sum of the sizes of all DARE regions shall be <= 512 MB
                    if LCPLib.total_dare_size > 512 * 1024:
                        self.logger.error("Total DARE regions' size is %sMB, it can not exceed 512MB, please decrease DARE region's size!", LCPLib.total_dare_size / 1024)
                        f.close()
                        if os.path.exists(lcp_bin_file):
                            os.remove(lcp_bin_file)
                        return

                    start = struct.pack("<I", regionData["start"])
                    f.write(start)
                    end = struct.pack("<I", regionData["size"])
                    f.write(end)
                    metadata = struct.pack("<I", 0)
                    f.write(metadata)
                    metadata_size_in_kb = struct.pack("<I", 0)
                    f.write(metadata_size_in_kb)
                    attr = struct.pack("<B", regionData["attr"])
                    f.write(attr)
                    arc_en = struct.pack("<B", regionData["arc_en"])
                    f.write(arc_en)
                    reserved1 = struct.pack("<B", 0)
                    f.write(reserved1)
                    reserved2 = struct.pack("<B", 0)
                    f.write(reserved2)
                    region_index = region_index + 1
        
        f.close()
        return lcp_bin_file

    def convert_bin2json(self, lcp_bin_file):
        self.logger.info("====Convert a LCP Bin file to a JSON file====")
        NUM_LCP_ADDR_REGIONS = int(self.lcp_config.lcp["NUM_LCP_ADDR_REGIONS"])
        NUM_RESERVED_FOR_INTERNAL_USE = int(self.lcp_config.lcp["NUM_RESERVED_FOR_INTERNAL_USE"])
        
        self.logger.info("NUM_LCP_ADDR_REGIONS: %s", NUM_LCP_ADDR_REGIONS)
        self.logger.info("NUM_RESERVED_FOR_INTERNAL_USE: %s", NUM_RESERVED_FOR_INTERNAL_USE)
        
        lcpBinFile = open(lcp_bin_file, 'rb')
        size = os.path.getsize(lcp_bin_file)
        lcpRegion_size = self.LCP_HEADER_SIZE + self.LCP_ADDR_REGIONS_STRUCT_SIZE * NUM_LCP_ADDR_REGIONS
        
        print("Bin file size:", size)
        if size % (self.LCP_HEADER_SIZE + self.LCP_ADDR_REGIONS_STRUCT_SIZE * NUM_LCP_ADDR_REGIONS) != 0:
            self.logger.error("LCP bin file is broken, please provide a correct LCP bin file!")

        lcpRegions = []
        for lcpRegions_index in range(int(size / (self.LCP_HEADER_SIZE + self.LCP_ADDR_REGIONS_STRUCT_SIZE * NUM_LCP_ADDR_REGIONS))):
            lcpRegion = dict()
            #lcpRegion["header"] = NULL
            
            regions = []
            for region_index in range(int(NUM_LCP_ADDR_REGIONS)):
                print("region_index: ", region_index)
                lcpBinFile.seek(lcpRegions_index * lcpRegion_size + self.LCP_HEADER_SIZE + region_index * self.LCP_ADDR_REGIONS_STRUCT_SIZE, 0)
                start = int.from_bytes(lcpBinFile.read(4), byteorder='little', signed=False)
                end = int.from_bytes(lcpBinFile.read(4), byteorder='little', signed=False) 
                metadata = int.from_bytes(lcpBinFile.read(4), byteorder='little', signed=False) 
                metadata_size_in_kb = int.from_bytes(lcpBinFile.read(4), byteorder='little', signed=False) 
                attr = int.from_bytes(lcpBinFile.read(1), byteorder='little', signed=False) 
                arc_en = int.from_bytes(lcpBinFile.read(1), byteorder='little', signed=False) 
                reserved1 = int.from_bytes(lcpBinFile.read(1), byteorder='little', signed=False)  
                reserved2 = int.from_bytes(lcpBinFile.read(1), byteorder='little', signed=False)  

                region = dict()
                if region_index < NUM_RESERVED_FOR_INTERNAL_USE:
                    region["name"] = ""
                else:
                    region["name"] = self.lcp_config.lcp_regions[region_index - NUM_RESERVED_FOR_INTERNAL_USE]["name"]
                
                self.logger.info("name: %s", region["name"])
                self.logger.info("start: %d", start)
                self.logger.info("end: %d", end)
                self.logger.info("metadata: %d", metadata)
                self.logger.info("metadata_size_in_kb: %d", metadata_size_in_kb)
                self.logger.info("attr: %d", attr)
                self.logger.info("arc_en: %d", arc_en)
                self.logger.info("reserved1: %d", reserved1)
                self.logger.info("reserved2: %d", reserved2)

                region["regionData"] = dict()
                region["regionData"]["start"] = start
                region["regionData"]["size"] = end
                region["regionData"]["attr"] = attr
                region["regionData"]["arc_en"] = arc_en

                regions.append(region)
            lcpRegion["regions"] = regions
        lcpRegions.append(lcpRegion)

        lcp_json_file = os.path.basename(lcp_bin_file).replace(".bin", ".json")
        self.logger.info("lcp_json_file: %s", lcp_json_file)

        lcp = dict()
        lcp["configName"] = os.path.basename(self.lcp_define_file)
        lcp["description"] = "DCB LCP entry file"
        lcp["lcpRegions"] = lcpRegions
        lcp["name"] = lcp_json_file
        lcp["platform"] = "v5"
        lcp["platformCode"] = "5"
        lcp["version"] = "1.0"

        with open(os.path.join(self.output_dir, lcp_json_file), "w") as f:
            json_str = json.dump(lcp, f, indent=4)

def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter, description='LCP helper library\r\n' + 
    '1, example to update xbl_config.elf to include LCP bin:\r\n' +
    r'   python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Lanai\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -s <meta_build_path>\common\sectoolsv2\ext -o <absolute_path>\output in -l <absolute_path>\LCP.bin -x <absolute_path>\xbl_config.elf'
    '\r\n' +
    '2, example to update DCB bins to include LCP bin:\r\n' +
    r'   python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Lanai\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -o <absolute_path>\output  in -l <absolute_path>\LCP.bin -x <absolute_path>\<dcb_bin_path>'
    '\r\n' +
    '3, example to convert lcp josn file to LCP region bin file:\r\n' +
    r'   python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Lanai\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -o <absolute_path>\output convert -d <absolute_path>\.dcb_config_SM8650.json -l <absolute_path>\SM8650_LCP_region.json'
    '\r\n' +
    '4, example to convert lcp bin file to LCP region json file:\r\n' +
    r'   python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Lanai\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -o <absolute_path>\output convert -d <absolute_path>\.dcb_config_SM8650.json -l <absolute_path>\SM8650_LCP_region.bin')

    parser.add_argument("-b", "--boot_build", help="path to boot CRM build base")
    parser.add_argument("-o", "--output_dir", default=tempfile.mkdtemp(prefix="lcp_"), help="output location to store debug logs and output files. If not supplied, a OS temporary directory will be created")
    parser.add_argument("-r", "--run_id", default="run_output", help="run_id, timestamp of current run")    
    parser.add_argument("-v", "--verbose", default="DEBUG", choices=["DEBUG", "INFO", "WARNING" ,"ERROR"], help="logging verbosity to be send to the cmd window. By default, all debug logs will be sent to a file")
    parser.add_argument("-a", "--target", required=True, help="target device")
    parser.add_argument("-s", "--sec_tool", help="path to sec tools")

    subparsers = parser.add_subparsers(help="sub-command help")
    parser_input = subparsers.add_parser("in", help="Command to generate a new xbl_config.elf based on an original xbl_config.elf file or update original DCB bins to inlcude LCP.bin")
    parser_input.add_argument("-l", "--lcp_file", required=True, help="LCP bin file")
    parser_input.add_argument("-x", "--xbl_config", required=True, help="1)If providing an original xbl_config.elf file, will update it to include lcp.bin; 2) If providing DCB bin path, will update DCB bin to include lcp.bin.")
    #parser_input.add_argument("-s", "--sec_tool", help="path to sec tools")
    parser_input.set_defaults(which="in")

    parser_convert = subparsers.add_parser("convert", help="Command to convert a LCP JSON or Bin file to a LCP bin or JSON file")
    parser_convert.add_argument("-d", "--lcp_define_file", required=True, help="lcp define file, .dcb_config_SM8650.json")
    parser_convert.add_argument("-l", "--lcp_file", required=True, help="lcp json file or LCP bin file")
    parser_convert.set_defaults(which="convert")

    args = parser.parse_args()

    if not args.output_dir is None and not os.path.isdir(args.output_dir):
        os.makedirs(args.output_dir)
    
    run_output = os.path.join(args.output_dir, args.run_id)
    if not os.path.isdir(run_output):
        os.makedirs(run_output)
    init_time = int(time.time())
    lcp_log = "lcp_debug_log_"+str(init_time)+".txt"
    logging.basicConfig(filename=os.path.join(run_output, lcp_log), level=logging.getLevelName(args.verbose), filemode="w")
    rootlogger = logging.getLogger()
    ch = logging.StreamHandler()
    ch.setLevel(logging.getLevelName(args.verbose))
    rootlogger.addHandler(ch)
    logger = logging.getLogger("lcp")

    if args.which == "in":
        lcplib = LCPLib(args.output_dir, boot_build=args.boot_build, sectool_path= args.sec_tool, target=args.target)
    else:
        lcplib = LCPLib(args.output_dir, boot_build=args.boot_build, target=args.target, lcp_define_file=args.lcp_define_file)          
    
    if args.which == "in":
        os.chdir(args.output_dir)
        logger.info("current working dir: %s:", os.getcwd())

        # Generate xbl_config.elf with new LCP
        if fnmatch.fnmatch(os.path.basename(args.xbl_config), "xbl_config.elf"):
            shutil.copy(args.xbl_config, os.path.join(args.output_dir, "ori_xbl_config.elf"))
            decompose_path = lcplib.decompose_xblconfig(args.xbl_config)    
            xbl_config = lcplib.gen_xbl_config(decompose_path, lcp_input=args.lcp_file)
            logger.info("")
            if os.path.exists(xbl_config):
                logger.info("new xbl_config.elf is generated at: %s !", xbl_config)
            else:
                logger.info("New xbl_config.elf cannot be generated at: %s due to errors!", xbl_config)
                logger.info("Please check errors in the running log to get failure reason!")
                sys.exit()

        # Generate DCB binary
        elif os.path.isdir(args.xbl_config):
            lcplib.update_dcb_bin(args.xbl_config, lcp_input=args.lcp_file)
            num_dcb_processed=0
            for dcb_bin in glob.glob(args.xbl_config + '/orig_*_dcb.bin'):
                if os.path.exists(os.path.dirname(dcb_bin)+ os.path.basename(dcb_bin).replace('orig_','/')):
                    num_dcb_processed = num_dcb_processed + 1
                    logger.info("DCB %s is processed", dcb_bin)
                else:
                    logger.info("DCB %s is not processed", dcb_bin)
            logger.info("%d DCB generated at: %s", num_dcb_processed, args.xbl_config)
        else:
            logger.info("")
            logger.info("Unrecognized input: %s", args.xbl_config)

    if args.which == "convert":
        if args.lcp_file is not None:
            if args.lcp_file.endswith(".bin"):
                logger.info("Convert a LCP bin file to a LCP JSON file")
                lcplib.convert_bin2json(args.lcp_file)
            elif args.lcp_file.endswith(".json"):           
                logger.info("Convert a LCP JSON file to a bin file")
                lcplib.convert_json2bin(args.lcp_file)
            else:
                logger.info("Please provide a correct LCP JSON file or a LCP Bin file, exit!")
        else:
            logger.info("LCP json file or LCP Bin file is not provided. exit!")    

    logger.info("")
    logger.info("----------  Finish LCP command")    

if __name__ == "__main__":
    main()
