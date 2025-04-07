#!/afs/localcell/cm/GV2/sysname/pkg.@sys/qct/software/python/3.6.4/bin/python3
"""/*******************************************************************************
  Qualcomm Proprietary Design Data
  Copyright (c) 2019, Qualcomm Technologies Incorporated.
  All rights reserved.
*******************************************************************************/
/*==============================================================================
$Header: //source/qcom/qct/core/boot/ddr/hw_sequence/DDRSS_SNS_V4/target/Palawan/mainline/ddr_fw/host/scripts/dsf.py#5 $
$DateTime: 2022/01/26 11:15:59 $
$Author: aastley $
==============================================================================*/
"""
# This script converts buffer_e and buffer_i binary to CSV

filter = "*buffer_*.bin"

ps_value_multiplier = 4

trainings_dict = {}
names_dict = {}
names_to_units_dict = {}
names_to_size_dict = {}

trainings_dict[0] = "WRITE"
trainings_dict[1] = "READ"
trainings_dict[2] = "DCC"
trainings_dict[3] = "RCW"
trainings_dict[4] = "RX_IO_CAL"
trainings_dict[5] = "DRAM"
trainings_dict[6] = "VOLTAGE"
trainings_dict[7] = "PLL"
trainings_dict[8] = "WRLVL"
trainings_dict[9] = "DIT"
trainings_dict[10] = "CBT"
trainings_dict[11] = "MSM"
trainings_dict[12] = "CDCM_CAL"
trainings_dict[13] = "CDCS_CAL"
trainings_dict[14] = "FUSE"

names_dict[0] = "EYE_WIDTH"
names_to_units_dict[0] = "ps"
names_to_size_dict[0] = 9

names_dict[1] = "EYE_HEIGHT"
names_to_units_dict[1] = "mV"
names_to_size_dict[1] = 9

names_dict[2] = "EYE_WIDTH_MASK_TOP"
names_to_units_dict[2] = "ps"
names_to_size_dict[2] = 9

names_dict[3] = "EYE_WIDTH_MASK_BOT"
names_to_units_dict[3] = "ps"
names_to_size_dict[3] = 9

names_dict[4] = "RXCAL"
names_to_units_dict[4] = "na"
names_to_size_dict[4] = 9

names_dict[5] = "PCNT_DQ"
names_to_units_dict[5] = "na"
names_to_size_dict[5] = 9

names_dict[6] = "PCNT_DQS"
names_to_units_dict[6] = "na"
names_to_size_dict[6] = 9

names_dict[7] = "NCNT_DQ"
names_to_units_dict[7] = "na"
names_to_size_dict[7] = 9

names_dict[8] = "NCNT_DQS"
names_to_units_dict[8] = "na"
names_to_size_dict[8] = 9

names_dict[9] = "RD_OPCODE"
names_to_units_dict[9] = "na"
names_to_size_dict[9] = 9

names_dict[10] = "IE_PRE"
names_to_units_dict[10] = "na"
names_to_size_dict[10] = 9

names_dict[11] = "QFI_PHASE"
names_to_units_dict[11] = "na"
names_to_size_dict[11] = 9

names_dict[12] = "DP_PHASE"
names_to_units_dict[12] = "na"
names_to_size_dict[12] = 9

names_dict[13] = "FULL_CYCLE"
names_to_units_dict[13] = "na"
names_to_size_dict[13] = 9

names_dict[14] = "TRAINED_VREF"
names_to_units_dict[14] = "mV"
names_to_size_dict[14] = 9

names_dict[15] = "TRAINED_DQDCC"
names_to_units_dict[15] = "na"
names_to_size_dict[15] = 9

names_dict[16] = "OFFSET_VREF"
names_to_units_dict[16] = "na"
names_to_size_dict[16] = 9

names_dict[17] = "EYE_WIDTH_SETUP"
names_to_units_dict[17] = "ps"
names_to_size_dict[17] = 9

names_dict[18] = "EYE_WIDTH_HOLD"
names_to_units_dict[18] = "ps"
names_to_size_dict[18] = 9

names_dict[19] = "EYE_WIDTH_SIPI_p60mv"
names_to_units_dict[19] = "ps"
names_to_size_dict[19] = 9

names_dict[20] = "EYE_WIDTH_SIPI_p60mv_VREF"
names_to_units_dict[20] = "mV"
names_to_size_dict[20] = 9

names_dict[21] = "EYE_WIDTH_SIPI_m60mv"
names_to_units_dict[21] = "ps"
names_to_size_dict[21] = 9

names_dict[22] = "EYE_WIDTH_SIPI_m60mv_VREF"
names_to_units_dict[22] = "mV"
names_to_size_dict[22] = 9

names_dict[23] = "EYE_WIDTH_MASK_TOP_VREF"
names_to_units_dict[23] = "mV"
names_to_size_dict[23] = 9

names_dict[24] = "EYE_WIDTH_MASK_BOT_VREF"
names_to_units_dict[24] = "mV"
names_to_size_dict[24] = 9

names_dict[25] = "EYE_HEIGHT_MID_TOP"
names_to_units_dict[25] = "mV"
names_to_size_dict[25] = 9

names_dict[26] = "EYE_HEIGHT_MID_BOT"
names_to_units_dict[26] = "mV"
names_to_size_dict[26] = 9

names_dict[27] = "BAND_SEL"
names_to_units_dict[27] = "na"
names_to_size_dict[27] = 9

names_dict[28] = "WRLVL_CK_DQS_DELTA"
names_to_units_dict[28] = "ps"
names_to_size_dict[28] = 16

names_dict[29] = "WRLVL_CK_VALUE"
names_to_units_dict[29] = "na"
names_to_size_dict[29] = 9

names_dict[30] = "WRLVL_WCK_VALUE"
names_to_units_dict[30] = "na"
names_to_size_dict[30] = 9

names_dict[31] = "MANUFACTURER_ID"
names_to_units_dict[31] = "na"
names_to_size_dict[31] = 9

names_dict[32] = "TYPE"
names_to_units_dict[32] = "na"
names_to_size_dict[32] = 9

names_dict[33] = "IO_WIDTH"
names_to_units_dict[33] = "na"
names_to_size_dict[33] = 9

names_dict[34] = "DENSITY"
names_to_units_dict[34] = "na"
names_to_size_dict[34] = 9

names_dict[35] = "REVISION_ID_1"
names_to_units_dict[35] = "na"
names_to_size_dict[35] = 9

names_dict[36] = "REVISION_ID_2"
names_to_units_dict[36] = "na"
names_to_size_dict[36] = 9

names_dict[37] = "CAPACITY_GB"
names_to_units_dict[37] = "na"
names_to_size_dict[37] = 9

names_dict[38] = "NUM_RANKS"
names_to_units_dict[38] = "na"
names_to_size_dict[38] = 9

names_dict[39] = "MAJOR_VERSION"
names_to_units_dict[39] = "na"
names_to_size_dict[39] = 9

names_dict[40] = "MINOR_VERSION"
names_to_units_dict[40] = "na"
names_to_size_dict[40] = 9

names_dict[41] = "DFE_BYTE"
names_to_units_dict[41] = "na"
names_to_size_dict[41] = 8

names_dict[42] = "DFE_BIT"
names_to_units_dict[42] = "na"
names_to_size_dict[42] = 8

names_dict[43] = "DQ_DCD"
names_to_units_dict[43] = "ps"
names_to_size_dict[43] = 8

names_dict[44] = "PLL"
names_to_units_dict[44] = "ps"
names_to_size_dict[44] = 8

names_dict[45] = "CLK"
names_to_units_dict[45] = "ps"
names_to_size_dict[45] = 8

names_dict[46] = "IO_CK"
names_to_units_dict[46] = "ps"
names_to_size_dict[46] = 8

names_dict[47] = "IO_WCK"
names_to_units_dict[47] = "ps"
names_to_size_dict[47] = 8

names_dict[48] = "IO_DQS"
names_to_units_dict[48] = "ps"
names_to_size_dict[48] = 8

names_dict[49] = "RDT4"
names_to_units_dict[49] = "ps"
names_to_size_dict[49] = 8

names_dict[50] = "DCC_DRAM"
names_to_units_dict[50] = "na"
names_to_size_dict[50] = 8

names_dict[51] = "IOQ_VREF"
names_to_units_dict[51] = "na"
names_to_size_dict[51] = 9

names_dict[52] = "DIT_RUNTIME"
names_to_units_dict[52] = "na"
names_to_size_dict[52] = 16

names_dict[53] = "tDQS2DQ"
names_to_units_dict[53] = "ps"
names_to_size_dict[53] = 16

names_dict[54] = "tDQSCK"
names_to_units_dict[54] = "ps"
names_to_size_dict[54] = 16

names_dict[55] = "tWCK2CK"
names_to_units_dict[55] = "ps"
names_to_size_dict[55] = 16

names_dict[56] = "CDC_C_F"
names_to_units_dict[56] = "ps"
names_to_size_dict[56] = 16

names_dict[57] = "LOCKTIME"
names_to_units_dict[57] = "us"
names_to_size_dict[57] = 16

names_dict[58] = "VDDA_CPR"
names_to_units_dict[58] = "mV"
names_to_size_dict[58] = 16

names_dict[59] = "VDDCX_CPR"
names_to_units_dict[59] = "mV"
names_to_size_dict[59] = 16

names_dict[60] = "VDDQ"
names_to_units_dict[60] = "mV"
names_to_size_dict[60] = 16

names_dict[61] = "VDD2"
names_to_units_dict[61] = "mV"
names_to_size_dict[61] = 16

names_dict[62] = "VDD1"
names_to_units_dict[62] = "mV"
names_to_size_dict[62] = 16

names_dict[63] = "P_N_TUNE"
names_to_units_dict[63] = "na"
names_to_size_dict[63] = 8

def parse_file(input_file_name, output_file, line_prefix):
    prev_byte = ~0
    curr_byte = ~0
    
    if os.stat(input_file_name).st_size == 0:
        return
    
    with open(input_file_name, "rb") as inFile:
        while not (prev_byte == 0 and curr_byte == 0):
            curr_byte = inFile.read(1)[0]
            prev_byte = curr_byte
            
            # Packet with 00b prefix
            if (curr_byte & 0xC0) == 0x00:
                packet = curr_byte << 8
                ch = curr_byte & 0xF
                cs = (curr_byte >> 4) & 0xF
                curr_byte = inFile.read(1)[0]
                packet |= curr_byte
                training = curr_byte & 0xF
                freq = (curr_byte >> 4) & 0xF
                #print("Packet 00b prefix: {:04X}".format(packet))
            # Packet with 01b prefix
            elif (curr_byte & 0xC0) == 0x40:
                byte = curr_byte & 0x3
                bit = (curr_byte >> 2) & 0xF
                #print("Packet 01b prefix: {:02X}".format(curr_byte))
            # Packet with 1Xb prefix
            elif (curr_byte & 0x80) == 0x80:
                name = curr_byte & 0x3F
                sign = (curr_byte >> 6) & 0x1
                #print("Packet 1Xb prefix: {:02X}".format(curr_byte))
                
                # Lower 8 bits of data
                curr_byte = inFile.read(1)[0]
                value = curr_byte
                
                # Upper 8 bits of data
                if names_to_size_dict[name] == 16:
                    curr_byte = inFile.read(1)[0]
                    value |= curr_byte << 8
                
                # 9 bit data
                if names_to_size_dict[name] == 9:
                    value |= sign << 8
                # Signed data
                else:
                    if sign == 1:
                        value *= -1
                
                # prefix
                line = line_prefix
                
                # training
                line += "{:s}".format(trainings_dict[training])
                
                # name
                line += ",{:s}".format(names_dict[name])
                
                # value
                if names_to_size_dict[name] < 16 and names_to_units_dict[name] == "ps":
                    value *= ps_value_multiplier
                line += ",{:d}".format(value)
                
                # units
                line += ",{:s}".format(names_to_units_dict[name])
                
                # freq
                if freq == 0xF:
                    line += ",DC"
                else:
                    line += ",{:d}".format(freq)
                
                # ch
                if ch == 0xF:
                    line += ",DC"
                else:
                    line += ",{:d}".format(ch)
                
                # cs
                if cs == 0x3:
                    line += ",DC"
                else:
                    line += ",{:d}".format(cs)
                
                # byte
                if byte == 0x3:
                    line += ",DC"
                else:
                    line += ",{:d}".format(byte)
                
                # bit
                if bit == 0xF:
                    line += ",DC"
                else:
                    line += ",{:d}".format(bit)
                
                line += "\n"
                
                output_file.write(line)
            # Error
            else:
                break
            
            # Fuses
            if trainings_dict[training] == "FUSE":
                import struct
                address = struct.unpack("<I", inFile.read(4))[0]
                value = struct.unpack("<I", inFile.read(4))[0]
                
                # prefix
                line = line_prefix
                
                # training, name, value
                line += "{:s},na,0".format(trainings_dict[training])
                
                # units, freq, ch, cs
                line += ",na,DC,DC,DC"
                
                # byte, bit
                line += ",0x{:08X},0x{:08X}\n".format(address, value)
                
                output_file.write(line)

if __name__ == "__main__":
    import sys, os, fnmatch
    
    output_file_name = "output.csv"
    with open(output_file_name, "w") as output_file:
        output_file.write("BUFFER,SN,DSF,BOOT_NUM,TRAINING,NAME,VALUE,UNITS,FREQ,CHANNEL,RANK,BYTE,BIT\n")
        if (len(sys.argv) > 1 ):
            path = sys.argv[1]
        else:
            path = "."
        if os.path.isdir(path):
            for root, dirs, files in os.walk(path, topdown=True):
                print("Traversing: " + root)
                parent_root = os.path.dirname(root)
                buffer_files = fnmatch.filter(files, filter)
                for file in buffer_files:
                    # buffer, serial, dsf, boot_num
                    import re
                    
                    file_name_re = re.compile(r'VVDRV_ddr_buffer_([ei])_.*?_SN(.*?)_DSF_V(.*?).bin')
                    match = file_name_re.match(file)
                    if match:
                        line_prefix = "{:s},{:s},{:s},NA,".format(match.group(1), match.group(2), match.group(3))
                    
                    file_name_re_bi = re.compile(r'VVDRV_ddr_buffer_([ei])_.*?_SN(.*?)_DSF_V(.*?)_(.*?).bin')
                    match = file_name_re_bi.match(file)
                    if match:
                        line_prefix = "{:s},{:s},{:s},{:s},".format(match.group(1), match.group(2), match.group(3), match.group(4))
                    
                    file_name_slt = re.compile(r'buffer_([ei])_(.*?).bin')
                    match = file_name_slt.match(file)
                    if match:
                        line_prefix = "{:s},{:s},NA,NA,".format(match.group(1), match.group(2))
                    
                    file_name = re.compile(r'buffer_([ei]).bin')
                    match = file_name.match(file)
                    if match:
                        line_prefix = "{:s},NA,NA,NA,".format(match.group(1))
                    
                    file_name_dsf = re.compile(r'buffer_([ei])_DSF_V(.*?).bin')
                    match = file_name_dsf.match(file)
                    if match:
                        line_prefix = "{:s},{:s},NA,NA,".format(match.group(1), match.group(2))
                    
                    file_name_dsf_bn = re.compile(r'buffer_([ei])_DSF_V(.*?)_(.*?).bin')
                    match = file_name_dsf_bn.match(file)
                    if match:
                        line_prefix = "{:s},NA,{:s},{:s},".format(match.group(1), match.group(2), match.group(3))
                    
                    file_path = root + "/" + file
                    print("   Parsing: " + file_path)
                    parse_file(file_path, output_file, line_prefix)
        elif ((sys.argv[1]=="--help") or (sys.argv[1]=="-h")):
            print('''
            Please create a directory containing all the bin files.
            As an example, content of sample "bin_directory" and supported bin file naming format is shown below:
            ls bin_directory/
            1) buffer_e.bin
            2) buffer_i.bin
            3) buffer_e_041DFA695707.bin                           // Populates SN column
            4) buffer_i_041DFA695707.bin                           // Populates SN column
            5) buffer_e_Lahaina_DSF_V212p00p00.bin                 // Populates DSF column
            6) buffer_i_Lahaina_DSF_V212p00p00.bin                 // Populates DSF column
            7) buffer_e_Lahaina_DSF_V212p00p00_1.bin               // Populates DSF & BOOT_NUM column
            8) buffer_i_Lahaina_DSF_V212p00p00_1.bin               // Populates DSF & BOOT_NUM column
            9) buffer_e_Lahaina_0691E033_DSF_V212p00p00.bin        // Populates SN & DSF column
            10) buffer_i_Lahaina_0691E033_DSF_V212p00p00.bin        // Populates SN & DSF column
            11) buffer_e_Lahaina_0691E033_DSF_V212p00p00_1.bin      // Populates SN, DSF & BOOT_NUM column
            12) buffer_i_Lahaina_0691E033_DSF_V212p00p00_1.bin      // Populates SN, DSF & BOOT_NUM column
            
            Run script:
            ./buffer_e_i_binary_parser.py                          // by default it takes current working diretory as "path"
            ./buffer_e_i_binary_parser.py <path of directory>
            e.g.:   ./buffer_e_i_binary_parser.py  bin_directory
            Corresponding "output.csv" is generated in the current working directory
            ''')
            exit()
