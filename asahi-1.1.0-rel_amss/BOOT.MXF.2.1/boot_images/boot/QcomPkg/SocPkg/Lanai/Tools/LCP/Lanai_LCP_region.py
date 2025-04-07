#=============================================================================
# FILE:         SM8650_LCP_region.py
#
# OVERVIEW:     This LCP python script aims to help user configure LCP regions per needs if don't want use QDUTT tool, it can create a LCP 
#               configure JSON file, user can change varable "config" to change regions' start address, size and memory type
#
#               Copyright (c) 2018-2022 Qualcomm Technologies, Inc.
#               All Rights Reserved.
#               Qualcomm Technologies Proprietary and Confidential.
#=============================================================================

import json
import logging
import os
import argparse
import sys
import time
import xml.etree.ElementTree as ET

DEBUG = False

if sys.version_info < (3, 8, 2):
      print("Must use Python 3.8.2 or greater")
      sys.exit(1)

# LCP-DARE – DRAM Authentication Replay Protection with Encryption
# In varable "config", only 'DisableFDE' and 'regions' field can be changed to configure LCP regions per needs
# Field 'start', 'size',  'attr' and 'arc_en' can be edited by user, check comments of each region for configure rule
#   Configure start field, it is upper 20 bits (35:16) of region's starting address 
#   Configure size field, its unit is KB
#   Configure region memory type via "attr" and "arc_en" field.
# Memory type, only Encrypt, DARE, DAR and plain DDR type are supported on Hamoa
#   Encrypt:   'attr' bit0 = 1B, 'attr' value: 1
#   DARE:      'attr' bit4 = 1B and 'arc_en' bit0 = 1B, 'attr' value: 16, 'arc_en' value: 1
#   DAR:       'attr' bit4 = 1B and 'arc_en' bit0 = 0B, 'attr' value: 16, 'arc_en' value: 0
#   DDR Plain: 'attr' value: 0 and 'arc_en' value: 0
#
# Region 1(TA S1), only DARE type can be configured if size is not zero
# Region 1(TA S1) and Region 2(TA S2), start field can not be configured by user, it is configured in DSF LCP according to reserved regions addrss and size
# Region 2(TA S2) to Region 8(OEM 4) can be configured to any memory type(DARE, DAR, encrypt or plain DDR)
# Region 9(S2 PT), start and size can not be configured by user, only memory type(DARE, encrypt or plain DDR) is allowed

config = {
    'lcpRegions':
    [
        {
            'regions':
            [
                {
                    # Region 0 -- reserved for internel use only, user can not configure this region.
                    'name': "",
                    'regionData': {
                        'start': 0, 
                        'size': 0, # Size 0KB, Size unit is KB
                        'attr': 0,  # Region attributes (bit 0 - Encrypt, bit 1 - ECC, bit 2 - MTE, bit 3 - Meta Deta, bit 4 - DARE)
                        'arc_en': 0, # 1 --> DARE with ANTI-REPLY COUNTER, 0 --> DAR w/o ANTI-REPLY COUNTER
                    }
                },
                {
                    # Region 1 -- TA S1
                    'name': "TA S1",
                    'regionData': {
                        'start': 0,  # TA S1 start can not be edited by user
                        'size': 28672, # Size 28672KB, this region size can be edited by user
                        'attr': 16, # DARE type, region attributes(bit 0 - Encrypt, bit 1 - ECC, bit 2 - MTE, bit 3 - Meta Deta, bit 4 - DARE)
                        'arc_en': 1, # 1 --> DARE with ANTI-REPLY COUNTER, 0 --> DAR w/o ANTI-REPLY COUNTER
                    }
                },
                {
                    # Region 2 -- TA S2
                    'name': "TA S2",
                    'regionData': {
                        'start': 0, # TA S2 start can not be edited by user
                        'size': 112640, # Size 112640KB, this region size can be edited by user
                        'attr': 0, # Plain DDR Type, region attributes(bit 0 - Encrypt, bit 1 - ECC, bit 2 - MTE, bit 3 - Meta Deta, bit 4 - DARE)
                        'arc_en': 0, # 1 --> DARE with ANTI-REPLY COUNTER, 0 --> DAR w/o ANTI-REPLY COUNTER
                    }
                },
                {
                    # Region 3 -- TUI VM
                    'name': "TUI VM",
                    'regionData': {
                        'start': 62336,  # 0xF380, this region start address can be edited by user
                        'size': 69632, #Size 69632KB, this region size can be edited by user
                        'attr': 1, # Encrypt Type, region attributes(bit 0 - Encrypt, bit 1 - ECC, bit 2 - MTE, bit 3 - Meta Deta, bit 4 - DARE)
                        'arc_en': 0, # 1 --> DARE with ANTI-REPLY COUNTER, 0 --> DAR w/o ANTI-REPLY COUNTER
                    }
                },
                {
                    # Region 4 -- OEM VM
                    'name': "OEM VM",
                    'regionData': {
                        'start': 63424, # 0xF7C0, this region start address can be edited by user
                        'size': 77824, #Size 77824KB, this region size can be edited by user
                        'attr': 1, #  Encrypt Type, region attributes(bit 0 - Encrypt, bit 1 - ECC, bit 2 - MTE, bit 3 - Meta Deta, bit 4 - DARE)
                        'arc_en': 0, # 1 --> DARE with ANTI-REPLY COUNTER, 0 --> DAR w/o ANTI-REPLY COUNTER
                    }
                },
                {
                    # Region 5 -- OEM Configure1
                    'name': "OEM 1",
                    'regionData': {
                        'start': 0, #this region start address can be edited by user
                        'size': 0,  #this region size can be edited by user
                        'attr': 0,
                        'arc_en': 0,
                    }
                },
                {
                    # Region 6 -- OEM Configure2
                    'name': "OEM 2",
                    'regionData': {
                        'start': 0, #this region start address can be edited by user
                        'size': 0,  #this region size can be edited by user
                        'attr': 0,
                        'arc_en': 0,
                    }
                },
                {
                    # Region 7 -- OEM Configure3
                    'name': "OEM 3",
                    'regionData': {
                        'start': 0, #this region start address can be edited by user
                        'size': 0,  #this region size can be edited by user
                        'attr': 0,
                        'arc_en': 0,
                    }
                },
                {
                    # Region 8 -- OEM Configure4
                    'name': "OEM 4",
                    'regionData': {
                        'start': 0, #this region start address can be edited by user
                        'size': 0,  #this region size can be edited by user 
                        'attr': 0,
                        'arc_en': 0,
                    }
                },
                {
                    # Region 9 -- S2 PT, only 'attr' and 'arc_en' can be edited by user
                    'name': "S2 PT",
                    'regionData': {
                        'start': 0, #this region start address can not be edited by user
                        'size': 0,  #this region size can be edited by user
                        'attr': 1,
                        'arc_en': 0,
                    }
                },
            ],
        },
    ],
    'configName': '.dcb_config_SM8650.json',
    'description':'DCB LCP entry file',
    'name': 'SM8650_LCP_region.json',
    'platform': 'v5',
    'platformCode': '5',
    'version': '1.0',
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
        
class ConfigureLCPLib(object):
    
    total_dare_size = 0
    region_spaces = []
    def __init__(self, target=None, lcp_define_file=None):
        self.logger = logging.getLogger("ConfigureLCPLib")
        if target is None: #default
            target = "SM8650"
            self.logger.warning("no target specified, use default")
        self.target = target
        self.logger.info("LCP target: %s", self.target)
        self.lcp_define_file = lcp_define_file
        if lcp_define_file is not None:
            self.logger.info("lcp define json: %s", lcp_define_file)
            with open(lcp_define_file) as f_lc:
                lcp_config = json.load(f_lc)
                self.lcp_config = Dict2Obj(lcp_config)

        self.memmapxml_file = os.path.join(os.path.dirname(os.path.realpath(__file__)), "memmap.xml")
        if os.path.exists(self.memmapxml_file):
            self.logger.info("memmap file: %s", self.memmapxml_file)

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
                        ConfigureLCPLib.region_spaces.append(region_space)
                    elif "TA S2" in region_name:
                        TA_S1_exist = False
                        for index, value in enumerate(ConfigureLCPLib.region_spaces):
                            if "TA S1" in value["name"]:
                                TA_S1_exist = True
                                region_space["name"] = "TA S1 + TA S2"
                                region_end = ConfigureLCPLib.region_spaces[index]["size"] + region_end + 1
                                ConfigureLCPLib.region_spaces[index]["name"] = "TA S1 + TA S2" 
                                ConfigureLCPLib.region_spaces[index]["size"] = region_end 
                        if TA_S1_exist == False:
                            region_end = region_start + region_end
                            region_space["name"] = "TA S1 + TA S2"
                            region_space["start"] = region_start
                            region_space["size"] = region_end
                            region_space["type"] = region_type
                            ConfigureLCPLib.region_spaces.append(region_space)

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
                ConfigureLCPLib.region_spaces.append(region_space)
                
                for space in ConfigureLCPLib.region_spaces:
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

        if region_multiple["hexcode"] != 0 and size * 1024 % region_multiple["value"] != 0:
            self.logger.error("'%s' region's end(size) should be %s", region_name, region_multiple["name"])
            return False
        
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
            ConfigureLCPLib.total_dare_size += region_size

        self.logger.info("===Region '%s' restriction check--END!===", region["name"])

        return True

def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter, description='LCP helper library\r\n' + 
    'Example to generate a LCP region json file:\r\n' +
    r'   python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Lanai\Tools\LCP\SM8650_LCP_region.py -o <absolute_path>\output -d <absolute_path>\.dcb_config_SM8650.json ')
    
    parser.add_argument("-r", "--run_id", default="run_output", help="run_id, timestamp of current run")    
    parser.add_argument("-a", "--target", required=True, help="target device")
    parser.add_argument("-o", "--output_dir", required=True, help="output location to store LCP region json file")
    parser.add_argument("-d", "--lcp_define_file", required=True, help="lcp define file, .dcb_config_SM8650.json")

    args = parser.parse_args()
    if not args.output_dir is None and not os.path.isdir(args.output_dir):
            os.makedirs(args.output_dir)
    
    run_output = os.path.join(args.output_dir, args.run_id)
    if not os.path.isdir(run_output):
        os.makedirs(run_output)
    init_time = int(time.time())
    lcp_log = "lcp_configure_log_"+str(init_time)+".txt"
    logging.basicConfig(filename=os.path.join(run_output, lcp_log), level=DEBUG, filemode="w")
    rootlogger = logging.getLogger()
    ch = logging.StreamHandler()
    ch.setLevel(logging.getLevelName(DEBUG))
    rootlogger.addHandler(ch)
    logger = logging.getLogger("configure_lcp")

    configure_lcp = ConfigureLCPLib(args.target, args.lcp_define_file)
    configure_lcp.get_reservedRegions(configure_lcp.memmapxml_file)
    configure_lcp.get_availableAddressSpacess()
    
    NUM_LCP_ADDR_REGIONS = int(configure_lcp.lcp_config.lcp["NUM_LCP_ADDR_REGIONS"])
    NUM_RESERVED_FOR_INTERNAL_USE = int(configure_lcp.lcp_config.lcp["NUM_RESERVED_FOR_INTERNAL_USE"])
    logger.info("NUM_LCP_ADDR_REGIONS: %s", NUM_LCP_ADDR_REGIONS)
    logger.info("NUM_RESERVED_FOR_INTERNAL_USE: %s", NUM_RESERVED_FOR_INTERNAL_USE)
    config["configName"] = '.dcb_config_' + args.target + '.json'
    config["name"] = args.target + '_LCP_region.json'

    for lcpRegion in config["lcpRegions"]:
        if NUM_LCP_ADDR_REGIONS != len(lcpRegion["regions"]):
            logger.error("Total of LCP regions is %s, it shoud be %s", len(lcpRegion["regions"]), NUM_LCP_ADDR_REGIONS)
            sys.exit()
        
        region_index = 0
        for region in lcpRegion["regions"]:
            regionData = region["regionData"]
            #region_0 is reserved for internal, all field should be ZERO
            if region_index < NUM_RESERVED_FOR_INTERNAL_USE:
                if regionData["start"] != 0 or \
                    regionData["size"] != 0 or \
                    regionData["attr"] != 0 or \
                    regionData["arc_en"] != 0:
                    logger.error("The first %s region(s) is reserved for internal use, all fields should be kept to '0'!", NUM_RESERVED_FOR_INTERNAL_USE)
                    sys.exit()
                   
            if region_index >= NUM_RESERVED_FOR_INTERNAL_USE:
                if configure_lcp.region_restriction_check(region, region_index - NUM_RESERVED_FOR_INTERNAL_USE) == False:
                    sys.exit()
            
            #The sum of the sizes of all DARE regions shall be <= 512 MB
            if configure_lcp.total_dare_size > 512 * 1024:
                logger.error("Total DARE regions' size is %sMB, it can not exceed 512MB, please decrease DARE region's size!", configure_lcp.total_dare_size / 1024)
                sys.exit()

            region_index = region_index + 1
    
    try:
        if args.output_dir is not None:
            config_filename = os.path.join(args.output_dir, args.target + '_LCP_region.json')
            with open(config_filename, 'w') as configFile:
                json.dump(config, configFile, indent=4)
            logger.info("\n")
            logger.debug(" LCP configure JSON file is generated in the path %s", config_filename)    
    except Exception as e:
        logger.info("\n")
        logger.debug("could not generate a LCP configure JSON file path!")
        logger.debug(e)        

if __name__ == "__main__":
    main()        