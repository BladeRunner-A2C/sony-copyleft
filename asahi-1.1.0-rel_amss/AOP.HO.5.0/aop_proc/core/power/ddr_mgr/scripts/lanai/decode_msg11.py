import sys
import os
import struct
import collections
import socket

# Create the dictionary entries for the logfile
LogDict = collections.namedtuple("LogDict", "config_offset log_offset log_end")
LogConfig = collections.namedtuple("LogConfig",
        "test_info test_count op_info config_status alc_override_lo alc_override_hi ddr_cmd_timeout log_stop_time")
LogEvent = collections.namedtuple("LogEvent",
        "time_hi time_lo end_time mid_a mid_b seq_cp seq_type")
SeqStats = collections.namedtuple("SeqStats",
        "count last_hi last_lo worst_end mid_a mid_b")
McShub = collections.namedtuple("McShub",
        "mc_history shub_history " +
        "last_mc_hi_1 last_mc_hi_2 last_mc_lo_1 last_mc_lo_2 " +
        "last_shub_hi_1 last_shub_hi_2 last_shub_lo_1 last_shub_lo_2 ")
PathEvent = collections.namedtuple("PathEvent",
        "time_hi time_lo end_time mid_a mid_b seq_type br_ev pwr_hi pwr_lo wait_hi wait_lo")

#        Idle  SHUB        MC        Parallel   Restore     Colapse   Flush     Abort       SW_Seq
mid_a_str = [("Seq0",   "Voltage", "Voltage", "Voltage", "Voltage", "LLC Collapse", "QActive", "NA",       "NA", "Seq9","SeqA","SeqB","SeqC","SeqD","SeqE","SeqF"),
             ("Seq0",   "Seq1MidA", "Seq2MidA", "Seq3MidA", "Seq4MidA", "Seq5MidA", "Seq6MidA", "Seq7MidA", "Seq8MidA", "Seq9MidA","SeqAMidA","SeqBMidA","SeqCMidA","SeqDMidA","SeqEMidA","SeqFMidA")]
mid_b_str = [("",   "Cmds",    "Cmds",    "Cmds",    "Cmds",    "Cmds",    "",        "Aborted",  "NA", "Seq9","SeqA","SeqB","SeqC","SeqD","SeqE","SeqF"),
             ("Seq0",   "Seq1MidB", "Seq2MidB", "Seq3MidB", "Seq4MidB", "Seq5MidB", "Seq6MidB", "Seq7MidB", "Seq8MidB", "Seq9MidB","SeqAMidB","SeqBMidB","SeqCMidB","SeqDMidB","SeqEMidB","SeqFMidB")]

#checks if path is a directory
msg11_files = ("MSGRAM11.BIN", "aop_msg11_")

def get_type(evt):
    acv = (evt & 0x0F000000) >> 24
    alc = (evt & 0x00F00000) >> 20
    ps  = (evt & 0x000F0000) >> 16
    evt = (evt & 0x0000000F)
    if (evt == 0):
        seq_type = "Idle"
    elif (evt == 1):
        seq_type = "SHUB"
    elif (evt == 2):
        seq_type = "MC"
    elif (evt == 3):
        seq_type = "Parallel"
    elif (evt == 4):
        seq_type = "Restore"
    elif (evt == 5):
        seq_type = "Collapse"
    elif (evt == 6):
        seq_type = "Flush"
    elif (evt == 7):
        seq_type = "Abort"
    elif (evt == 8):
        seq_type = "SW_SEQ"
    elif (evt == 9):
        seq_type = "PATH_SEQ"
    elif (evt == 10):
        seq_type = "SEQ_10"
    elif (evt == 11):
        seq_type = "SEQ_11"
    elif (evt == 12):
        seq_type = "SEQ_12"
    elif (evt == 13):
        seq_type = "SEQ_13"
    elif (evt == 14):
        seq_type = "SEQ_14"
    elif (evt == 15):
        seq_type = "SEQ_15"
    else:
        seq_type = ("SubSeq:%d"%(evt))
    return (acv, alc, ps, evt, seq_type)

def get_cps(info):
    next_shub = (info & 0x0F000000) >> 24
    curr_shub = (info & 0x00F00000) >> 20
    bcm__shub = (info & 0x000F0000) >> 16

    next_mc = (info & 0x0F00) >> 8
    curr_mc = (info & 0x00F0) >> 4
    bcm__mc = (info & 0x000F) >> 0
    return(next_shub, curr_shub, bcm__shub, next_mc, curr_mc, bcm__mc)

def get_rel(a,b):
    if a == 0:
        return ("N/A")
    else:
        us = (b - a)/19.2   # Convert to us
        if (us > 1000000):
            return("%2.1fsec" % (us / 1000000))
        elif (us > 1000):
            return("%2.1fms" % (us / 1000))
        else:
            return("%d us" % (us))

def usage():
    print("Usage: %s [<filename>|<directory name>]" % (sys.argv[0]))
    exit(0)

def get_file(fpath, files):
    retval = None
    if os.path.isfile(fpath):
        retval = fpath
    elif os.path.isdir(fpath):
        for entry in os.listdir(fpath):
            for chkfile in files:
                if chkfile in entry:
                    print (entry, "matches", chkfile)
                    retval = os.path.join(fpath, entry)
                    break
    return (retval)

def get_ps(ps):
    val = ("0 (D4)",    "1 (D3)",    "2 (LL)",    "3 (D0)",      "4 (Col+1)",  "5 (Col+2)",   "6 (Col+3)",   "7 (Col+4)", 
           "8 (Col+5)", "9 (Col+6)", "10 (Col+7)", "11 (Col+8)", "12 (Col+9)", "13 (Col+10)", "14 (Col+11)", "15 (Max)")
    return (val[ps])

def print_ddrstats(data):
    dataconfig = data['config']
    #datastats = data['stats']
    event_array = data['events']
    print ("\nTestInfo:0x%08.8X, TestCount:%d, OpInfo:%08.8X, Status:%08.8X, ALC=%08.8X%08.8X, cmd_time=%4.3fus log_stop_time=%08.8X" %
                       (dataconfig.test_info, dataconfig.test_count, dataconfig.op_info, dataconfig.config_status,
                       dataconfig.alc_override_hi, dataconfig.alc_override_lo, (dataconfig.ddr_cmd_timeout/19.2),  dataconfig.log_stop_time))
    unknown = 0xFFFFFFFF
    # Bit masks Known, translation, and should we print warnings
    masks = [(0x0100000, "Perfmode Command", False),
             (0x0200000, "Floor Command", False),
             (0x0400000, "Capped Command", True),
             (0x0800000, "Fixed Command", True),
             (0x1000000, "Starc Command", True),
             (0x4000000, "Pair Command", True)]

    test_info = dataconfig.test_info
    for val in masks:
        if (test_info & val[0]):
            test_info &= ~val[0]
            if (val[2]):
                data['dangerous'] = True
                warning = " **** WARNING  This command may cause system instability."
            else:
                warning = ""
            print ("%s Seen%s"%(val[1],warning))
    if (test_info != 0):
        print("Remaining bits in TestInfo mask: 0x%X"%(test_info))
    print("")

    #print(datastats)
    last_time = 0
    last_idle = 0
    last_mc = -1
    last_shub = -1
    next_time = 0
    next_time_buffer = 48  # 2.5us of DDR_AUX overhead is allowed to not say "IDLE"
                           # Set small to study ddr-aux latencies
                           # Set very large to get rid of most IDLE's 

    print ("             |          |     Sub-  |   |   | DDR Power |      MC     |   SHUB    |")
    print ("   Timestamp | Rel Time |  Sequence |ALC|ACV| State ARC |BCM| Change  |BCM| Change| Relative Timestamp Notes and Info")
    print ("-------------+----------+-----------+---+---+-----------+---+---------+---+-------+----------------------------------")
    for event in event_array:
        new_time = (event.time_hi << 32) + event.time_lo
        if (new_time == 0):
            continue

        aux_overhead = 0
        overhead = ""
        # If DDR_AUX takes more than 2.5us between sequences, print the "IDLE" line
        if (next_time != 0):
            if (new_time > next_time + next_time_buffer):
                print (next_line)
                last_time = next_time
            else:
                aux_overhead = new_time - next_time

        next_time = 0

        rel = get_rel(last_time, new_time)

        (acv, alc, ps, seq_idx, seq_type) = get_type(event.seq_type)
        (to_shub, from_shub, bcm_shub, to_mc, from_mc, bcm_mc) = get_cps(event.seq_cp)

        mc_dir = " "
        shub_dir = " "
        ps = get_ps(ps)

        if (last_mc != -1):
            if (last_mc < bcm_mc):
                mc_dir = "^"
            elif (last_mc > bcm_mc):
                mc_dir = "."
            if (last_shub < bcm_shub):
                shub_dir = "^"
            elif (last_shub > bcm_shub):
                shub_dir = "."
        if (from_mc == to_mc):
            mc_change = "%2d | %2d"%(from_mc, to_mc)
        else:
            mc_change = "%2d +>%2d"%(from_mc, to_mc)

        if (from_shub == to_shub):
            shub_change = "%2d | %-2d"%(from_shub, to_shub)
        else:
            shub_change = "%2d +>%-2d"%(from_shub, to_shub)

        last_mc   = bcm_mc
        last_shub = bcm_shub
        last_time = new_time
        
        #"time_hi time_lo end_time mid_a mid_b seq_cp seq_type")
        mid_a = ""
        mid_b = ""
        elapsed = "ERROR! No End time"
        ref_time = new_time
        start = "Start"
        bar = "|"
        if (event.mid_a) != 0xDEADBEEF:
            mid_a = "%s->Mid A(%s)%s" % (start, mid_a_str[0][seq_idx], get_rel(ref_time, new_time+event.mid_a))
            ref_time = new_time+event.mid_a 
            start = ""
        if (event.mid_b) != 0xDEADBEEF:
            mid_b = "%s->Mid B(%s)%s" % (start, mid_b_str[0][seq_idx], get_rel(ref_time, new_time+event.mid_b))
            ref_time = new_time+event.mid_b 
        if (event.end_time != 0xDEADBEEF) and (event.end_time != 0xFFFFFFFF):
            elapsed  = "Total(%s) " % (get_rel(new_time, new_time+event.end_time))
            if event.end_time > 800*19.2:
              bar = ">"
        else:
            data['warnings'] = "********* WARNING a sequence did not end\n"

        #if (aux_overhead > 0):
        #    overhead = "%d cycles->"%(aux_overhead)

        print(" %11X %s %8s |%10s |%2s |%2s | %9s |%2s%s|%0s|%2s%s|%6s| %-15s %s%s%s"%
                (new_time, bar, rel, seq_type, alc, acv, ps, bcm_mc, mc_dir,
                 mc_change.center(9), bcm_shub, shub_dir, shub_change,
                 elapsed, overhead, mid_a, mid_b ))
        mc_change   = "%2d | %2d"%(to_mc, to_mc)
        shub_change = "%2d | %-2d"%(to_shub, to_shub)

        if ((event.end_time != 0xDEADBEEF) and (event.end_time != 0xFFFFFFFF)):
            next_line = " %11X %s %8s |%10s |%2s |%2s | %9s |%2s%s|%9s|%2s%s|%6s|" %\
                (new_time + event.end_time, bar, get_rel(new_time, new_time+event.end_time),
                 "IDLE", alc, acv, ps, bcm_mc, " ", mc_change.center(9), bcm_shub, " ", shub_change)
            next_time = new_time + event.end_time

    if (next_time != 0):
        print (next_line)
    print ("-------------+----------+-----------+---+---+-----------+---+---------+---+-------+----------------------------------")
    print ("   Timestamp | Rel Time |      Sub- |ALC|ACV| DDR Power |BCM| Change  |BCM| Change| Relative Timestamp Notes and Info")
    print ("             |          |  Sequence |   |   | State ARC |      MC     |   SHUB    |")

    if (data['warnings'] != None):
        print ("%s"%(data['warnings']))


def get_timestamp(arg):
    return ((arg.time_hi << 32) + arg.time_lo)

def print_seqstats(data, path):
    # "count last_hi last_lo worst_end mid_a mid_b")
    if (path == 0):
      sequence_array = data['sequences']
    else:
      sequence_array = data['path_sequences']

    if sequence_array == None:
      return

    print ("")
    names = [("SHUB", "MC", "PARALLEL", "RESTORE", "COLLAPSE", "LLC FLUSH",
              "FLUSH ABORT", "SW SEQUENCE", "PATH SEQ",
              "SEQ 10", "SEQ 11", "SEQ 12", "SEQ 13", "SEQ 14", "SEQ 15"),
              ("Special", "Normal", "LPINOC On", "LPINOC Off", "Reserved5",
               "Init", "Path7", "Path8", "Path9", "Path10", "Path11",
               "Path12", "Path13", "Path14", "Path15", "Path16")]
    max_needed = max(s.count for s in sequence_array)
    val_needed = "{:,}".format(max_needed)
    length_needed = 1+len(val_needed)
    count_str = "{:>%d}"%length_needed
    seq_idx = 0;
    for seq in sequence_array:
        name = names[path][seq_idx]
        seq_idx += 1
        time = seq.last_hi << 32 | seq.last_lo
        worst_end = get_rel(1, seq.worst_end)
        count_val = count_str.format("{:,}".format(seq.count))
        if path == 0:
          if (seq.mid_a == 0xDEADBEEF):
              mid_a = "..... "
          else:
              mid_a = "Mid_A(%s):%s " % (mid_a_str[path][seq_idx], get_rel(1, seq.mid_a))
          if (seq.mid_b == 0xDEADBEEF):
              mid_b = "..... "
          else:
              mid_b = "Mid_b(%s):%s " % (mid_b_str[path][seq_idx], get_rel(1, seq.mid_b))
          print ("Sequence %12s: Count:%s; Last Timestamp:%11X; Worstcase Times:%7s %26s %-25s" % (name, count_val, time, worst_end, mid_a, mid_b));
        else:
          print ("Sequence %12s: Count:%s; Last Timestamp:%11X; Worstcase Times:%7s" % (name, count_val, time, worst_end ));

def order(a,b):
    if (a < b):
        return [a,b]
    else:
        return [b,a]

def print_McShubstats(arg):
    #"mc_history shub_history " +
    #"last_mc_hi_1 last_mc_hi_2 last_mc_lo_1 last_mc_lo_2 " +
    #"last_shub_hi_1 last_shub_hi_2 last_shub_lo_1 last_shub_lo_2 ")
    data = arg['stats']
    mc_val =   order((  data.last_mc_hi_1 << 32 |   data.last_mc_lo_1), (  data.last_mc_hi_2 << 32 |   data.last_mc_lo_2))
    shub_val = order((data.last_shub_hi_1 << 32 | data.last_shub_lo_1), (data.last_shub_hi_2 << 32 | data.last_shub_lo_2))
    print ("")
    print (" MC  History OLDEST->%08.8X<-NEWEST" % (data.mc_history))
    print ("SHUB History OLDEST->%08.8X<-NEWEST" % (data.shub_history))
    print ("Last two  MC  changes: %11X and %11X" % (mc_val[0],mc_val[1]))
    print ("Last two SHUB changes: %11X and %11X" % (shub_val[0], shub_val[1]))

def process_stats(arg):
    import socket
    print ("V2.0 %s %s Arg is %s"%(socket.gethostname(), os.path.realpath(__file__),arg))
    filename = get_file(arg, msg11_files)
    data = None
    valid = True
    if filename != None:
        print ("Got the file %s" % filename)
        # The first 4 32 bit words is the dictionary
        try:
            with open(filename, mode='rb') as file:
                fileContent = file.read()
        except:
            print ("Could not open %s: %s", (filename, sys.exc_info()[0]))
            return None

        datadict = LogDict(*struct.unpack("III", fileContent[:12]))
        print ("Config Offset:0x%08.8X, Log_Offset:%08.8X, Log_End:0x%08.8X" %(datadict.config_offset, datadict.log_offset, datadict.log_end))
        log_size = datadict.log_end - datadict.log_offset
        cfg_offset = 16  # cfg_offset must be a multiple of 8
        if cfg_offset != datadict.config_offset:
            print("Config Offset Expected 0x%X, Got 0x%X"%(cfg_offset,datadict.config_offset))
            valid = False;
        dataconfig = LogConfig(*struct.unpack("IIIIIIII", fileContent[cfg_offset:cfg_offset+32]))

        current_offset = cfg_offset+32
        if current_offset != datadict.log_offset:
            print("Event Offset Expected 0x%X, Got 0x%X"%(current_offset,datadict.log_offset))
            valid = False;
        log_start = current_offset

        event_array = []
        event_offset = current_offset
        event_size = 7*4
        #for event_num in range(datadict.num_events):

        for event_num in range(20):
            offset = event_offset+event_num*event_size
            current_offset += event_size
            event = LogEvent(*struct.unpack("I"*7, fileContent[offset:offset+event_size]))
            #print("Event:%d Time %X MidA=%X MidB=%X offset=%X"%(event_num, event.time_lo, event.mid_a, event.mid_b, offset))
            event_array.append(event)

        event_array.sort(key=get_timestamp)

        sequence_array = []
        sequence_offset = current_offset
        sequence_size = 6*4

        for sequence_num in range(9):
            offset = sequence_offset+sequence_num*sequence_size
            current_offset += sequence_size
            sequence = SeqStats(*struct.unpack("I"*6, fileContent[offset:offset+sequence_size]))
            sequence_array.append(sequence)

        # Adjust if there are too many left
        if (log_start + log_size - current_offset == 64):
            print("Adjusting offset - Log went 0x%x to 0x%x, should be 40 left - %d left"%(log_start, current_offset, log_start + log_size - current_offset))
            current_offset += 24
            #valid = False
        elif (log_start + log_size - current_offset != 40):
            print("Bad offset - Log went 0x%x to 0x%x, should be 40 left - %d left"%(log_start, current_offset, log_start + log_size - current_offset))
            #valid = False
        #else:
            #print("Good offset - Log went 0x%x to 0x%x, should be 40 left - %d left"%(log_start, current_offset, log_start + log_size - current_offset))

        McShubStats = McShub(*struct.unpack("I"*10, fileContent[current_offset:current_offset+40]))
        current_offset += 40

        data = {
                'valid'     : valid,
                'dict'      : datadict,
                'config'    : dataconfig,
                'stats'     : McShubStats,
                'events'    : event_array,
                'sequences' : sequence_array,
                'warnings'  : None,
                'dangerous' : False,
               }

    return data

def print_info(info):
    if info == None:
        print ("Error returned from file")
    else:
        if info['valid'] == False:
            print("\n*WARNING, Data is not valid Waipio data\n");
        print_ddrstats(info)
        print_seqstats(info,0)
        print_McShubstats(info)
        if (info['dangerous']):
            print("\n********* WARNING: Test commands issued which may have made the system unstable *******")
        if (info['warnings'] != None):
            print ("%s"%(info['warnings']))

if __name__ == "__main__":
    if len(sys.argv) == 1:
        usage()

    for arg in sys.argv[1:]:
        info = process_stats(arg)
        if info == None:
            print ("Error returned from file")
        else:
            if info['valid'] == False:
                print("\n*WARNING, Data is not Waipio data\n");
            else:
                print_info(info)
