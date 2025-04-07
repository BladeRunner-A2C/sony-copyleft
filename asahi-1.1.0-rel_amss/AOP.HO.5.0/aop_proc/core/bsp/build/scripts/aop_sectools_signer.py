import os
import subprocess
import string
import re
import shutil
import struct
import sys
from re import search, IGNORECASE
from subprocess import check_output, CalledProcessError
import xml.etree.cElementTree as ET
#------------------------------------------------------------------------------
# Globals
#------------------------------------------------------------------------------
DBG_LOG_TAG = 'SECTOOLS FATAL ERROR: '

HOSTS = [
"sundae",     # San Diego
"selma",      # Santa Clara
"titanic",    # Boulder
"blrsweng1",  # Bangalore
"swayam"      # Hyderabad
]
TIMEOUT = "1000"
NUM_PINGS = "3"

def fatal_signer_err(env, err_msg):
    env.PrintError(err_msg)
    raise Exception('%s: %s' %(DBG_LOG_TAG,err_msg))


def get_sectools_windows_host():
    selected_host = None
    min_ping_time = None
    for host in HOSTS:
        try:
            # This ping command only works on Windows because the ping command requires different arguments on Linux and macOS
            output = check_output(["ping", "-n", NUM_PINGS, "-w", TIMEOUT, host])
            match = search("Average[ ]*=[ ]*([0-9][0-9]*)", output.decode(), IGNORECASE)
            if match:
                ping_time = int(match.group(1))
                if min_ping_time is None or ping_time < min_ping_time:
                    min_ping_time = ping_time
                    selected_host = host
        except CalledProcessError:
            pass
    return selected_host

def sectools_remote_find(version="latest"):
    location = None
    if sys.platform.startswith("win32"):
        server = get_sectools_windows_host()
        if server is not None:
            location = "\\\\{}\\sectools\\v2\\{}\\Windows\sectools.exe".format(server, version)
        else:
            location = os.getenv('SECTOOLS', None)
            if location is None:
              fatal_signer_err("Unable to find a windows server")
    elif sys.platform.startswith("linux"):
        location = os.getenv('SECTOOLS', None)
        if location is None:
          location = "/pkg/sectools/v2/{}/Linux/sectools".format(version)
    else:
        fatal_signer_err("sectools does not support {} OS.".format(sys.platform))
    return location

#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return True

def generate(env):
   #sets up an interface to sign aop elfs with. currently there is a limitation with the signing tool to support
   #mbn. So need to sign the elf and then generate mbn later (if needed).
  target = env['MSM_ID']
  env.PrintDebugInfo('generate', target)
  aop_sectools_generate(env)

def aop_qc_sign_emitter(target, source, env):
   # here one can also add dependencies for say aexe.exe (if it needs to be build)
   # env.Depends(target, propgen_tool)
   return (target, source)

def aop_test_sign_emitter(target, source, env):
   # here one can also add dependencies for say aexe.exe (if it needs to be build)
   # env.Depends(target, propgen_tool)
   return (target, source)

def aop_oem_sign_emitter(target, source, env):
   return (target, source)

def aop_hash_unsign_emitter(target, source, env):
   return (target, source)

def aop_sectools_generate (env):
  env.AddMethod(aop_img_sign_wrapper, "AOPImageSigner")
  env.AddMethod(aop_img_unsign_wrapper, "AOPImageUnsigner")
  env.AddMethod(aop_devcfg_sign_wrapper, "AOPDevCfgSigner")
  env.AddMethod(aop_devcfg_unsign_wrapper, "AOPDevCfgUnsigner")
  env.AddMethod(gen_signing_manifest_wrapper, "AOPSignXMLGen")
  #get a custom builder registered with the environment
  sectools_qc_bldr = env.Builder(action= env.GetBuilderAction (aop_qc_sign, action_source=None),
                              emitter=aop_qc_sign_emitter,
                              suffix= '.mbn' )
  sectools_test_bldr = env.Builder(action= env.GetBuilderAction (aop_test_sign, action_source=None),
                              emitter=aop_test_sign_emitter,
                              suffix= '.mbn' )
  sectools_oem_bldr = env.Builder(action= env.GetBuilderAction (aop_oem_sign, action_source=None),
                              emitter=aop_oem_sign_emitter,
                              suffix= '.mbn' )
  sectools_hash_unsign_bldr = env.Builder(action= env.GetBuilderAction (aop_hash_unsign, action_source=None),
                              emitter=aop_hash_unsign_emitter,
                              suffix= '.mbn' )

  env.Append(BUILDERS = {'AOPQCSigner' : sectools_qc_bldr})
  env.Append(BUILDERS = {'AOPTestSigner' : sectools_test_bldr})
  env.Append(BUILDERS = {'AOPOEMSigner' : sectools_oem_bldr})
  env.Append(BUILDERS = {'AOPHashUnsigner' : sectools_hash_unsign_bldr})
  return

authenticator_map = {'waipio': '${BUILD_ROOT}/core/bsp/build/authenticators/waipio/waipio_tme_security_profile.xml',
    'fillmore': '${BUILD_ROOT}/core/bsp/build/authenticators/fillmore/fillmore_tme_security_profile.xml',
    'aurora': '${BUILD_ROOT}/core/bsp/build/authenticators/aurora/aurora_tme_security_profile.xml',
    'kailua': '${BUILD_ROOT}/core/bsp/build/authenticators/kailua/kailua_tme_security_profile.xml',
    'kapiti': '${BUILD_ROOT}/core/bsp/build/authenticators/kapiti/kapiti_tme_security_profile.xml',
    'lassen': '${BUILD_ROOT}/core/bsp/build/authenticators/lassen/lassen_tme_security_profile.xml',
    'netrani': '${BUILD_ROOT}/core/bsp/build/authenticators/netrani/netrani_tme_security_profile.xml',
    'palima': '${BUILD_ROOT}/core/bsp/build/authenticators/palima/palima_tme_security_profile.xml',
    'lanai': '${BUILD_ROOT}/core/bsp/build/authenticators/lanai/lanai_tme_security_profile.xml',
    'pakala': '${BUILD_ROOT}/core/bsp/build/authenticators/pakala/pakala_tme_security_profile.xml',
    'hamoa': '${BUILD_ROOT}/core/bsp/build/authenticators/hamoa/hamoa_tme_security_profile.xml',
    'pinnacle': '${BUILD_ROOT}/core/bsp/build/authenticators/pinnacle/pinnacle_tme_security_profile.xml',
    'kuno': '${BUILD_ROOT}/core/bsp/build/authenticators/kuno/kuno_tme_security_profile.xml',
    'camano': '${BUILD_ROOT}/core/bsp/build/authenticators/camano/camano_tme_security_profile.xml',
    'palawan': '${BUILD_ROOT}/core/bsp/build/authenticators/palawan/palawan_tme_security_profile.xml',
    'matrix': '${BUILD_ROOT}/core/bsp/build/authenticators/matrix/matrix_tme_security_profile.xml',
    'milos': '${BUILD_ROOT}/core/bsp/build/authenticators/milos/milos_tme_security_profile.xml',
    'kaanapali': '${BUILD_ROOT}/core/bsp/build/authenticators/kaanapali/kaanapali_tme_security_profile.xml',
}

cass_cap_map = {'waipio': 'srot_prod_v6_waipio_srot_release',
    'kailua': 'srot_prod_v6_kailua_srot_release',
    'kapiti': 'srot_test_v6_srot_release',  #kapiti_todo
    'lassen': 'srot_test_v6_srot_release',
    'lanai': 'srot_prod_v6_lanai_srot_release',
    'pakala': 'srot_prod_v6_pakala_srot_release',
    'hamoa': 'srot_prod_v6_hamoa_srot_release', 
    'pinnacle': 'srot_prod_v6_pinnacles_srot_release',
    'kuno': 'srot_prod_v6_kuno_com0.0_ent3.0_srot_release', 
    'camano': 'srot_prod_v6_camano_srot_release',
    'palawan': 'srot_prod_v6_palawan_srot_release',
    'matrix': 'srot_test_v6_com0.0_ent3.0_srot_release', #MATRIX_TODO
    'milos': 'srot_test_v6_com0.0_ent3.0_srot_release', #MILOS TODO
    'kaanapali': 'srot_test_v6_com0.0_ent3.0_srot_release', #KAANAPALI TODO
}

def sectools_find_authenticator(env):
  #Finds the authenticator per target and returns. Else fatals
  auth_xml = env.RealPath(authenticator_map[env['MSM_ID']])
  if not os.path.exists(auth_xml) or not os.path.isfile(auth_xml):
    fatal_signer_err(env, 'Auth xml not found for {}'.format(env['MSM_ID']))
  return auth_xml


def aop_qc_sign(target, source, env):
  #builder action, rules to build target from source
  source_str = os.path.abspath(str(source[0]))
  target_str = os.path.abspath(str(target[0]))
  
  print('qc signing source: ', source_str)
  print('qc signing target: ', target_str)

  if not os.path.exists(source_str) or not os.path.isfile(source_str):
    fatal_signer_err(env, 'SOURCE FILES: ' + source_str + ' Not found')

  closest_server = sectools_remote_find()
  print('Will use ', closest_server, ' instance to sign')

  target_authenticator = sectools_find_authenticator(env)
  #print('Authenticator: ', target_authenticator)

  common_sign_cmd = closest_server + ' secure-image  {_source}  --outfile {_target} --image-id AOP --security-profile ' + target_authenticator + ' --sign '
  if env['MSM_ID'] in  ['lanai', 'pakala', 'pinnacle', 'palawan', 'matrix','kuno', 'milos']:
    qti_sign_cmd = common_sign_cmd.format(_source=source_str, _target=target_str) + ' --qti --signing-mode QTI-REMOTE --cass-capability srot_test_v6_com0.0_ent3.0_srot_release --qti-remote-signing-server-url https://crm-sign.qualcomm.com --qti-remote-signing-server-port 50110 '
  else:
    qti_sign_cmd = common_sign_cmd.format(_source=source_str, _target=target_str) + ' --qti --signing-mode QTI-REMOTE --cass-capability srot_test_v6_srot_release --qti-remote-signing-server-url https://crm-sign.qualcomm.com --qti-remote-signing-server-port 50110 '

  #print('QTI sign cmd'+qti_sign_cmd)

  _stdout, _stderr, _retval = env.ExecCmds(cmds=qti_sign_cmd, target=target_str, shell=True)

  return

def aop_test_sign(target, source, env):
  #builder action, rules to build target from source
  source_str = os.path.abspath(str(source[0]))
  target_str = os.path.abspath(str(target[0]))

  print('Test Sign source: ', source_str)
  print('Test Sign target: ', target_str)

  if not os.path.exists(source_str) or not os.path.isfile(source_str):
    fatal_signer_err(env, 'SOURCE FILES: ' + source_str + 'Not found')

  closest_server = sectools_remote_find()
  print('Will use ', closest_server, ' instance to sign')

  target_authenticator = sectools_find_authenticator(env)
  #print('Authenticator: ', target_authenticator)

  if 'CREATE_COMPRESSED_MBN' in env:
    compressed_target_str = target_str[:-3] + 'xz'
    common_sign_cmd = closest_server + ' secure-image  {_source}  --outfile {_target} --compressed-outfile ' + compressed_target_str + ' --image-id AOP --security-profile ' + target_authenticator + ' --sign --compress'
  else:
    common_sign_cmd = closest_server + ' secure-image  {_source}  --outfile {_target} --image-id AOP --security-profile ' + target_authenticator + ' --sign '

  oem_sign_cmd = common_sign_cmd.format(_source=source_str, _target=target_str) + ' --signing-mode TEST '

  #print('TEST sign cmd'+oem_sign_cmd)

  _stdout, _stderr, _retval = env.ExecCmds(cmds=oem_sign_cmd, target=target_str, shell=True)

  return

def aop_oem_sign(target, source, env):
  #builder action, rules to build target from source
  source_str = os.path.abspath(str(source[0]))
  target_str = os.path.abspath(str(target[0]))

  print('OEM Sign source: ', source_str)
  print('OEM Sign target: ', target_str)

  if not os.path.exists(source_str) or not os.path.isfile(source_str):
    fatal_signer_err(env, 'SOURCE FILES: ' + source_str + 'Not found')

  closest_server = sectools_remote_find()
  print('Will use ', closest_server, ' instance to sign')

  target_authenticator = sectools_find_authenticator(env)
  #print('Authenticator: ', target_authenticator)

  if 'CREATE_COMPRESSED_MBN' in env:
    compressed_target_str = target_str[:-3] + 'xz'
    common_sign_cmd = closest_server + ' secure-image  {_source}  --outfile {_target} --compressed-outfile ' + compressed_target_str + ' --image-id AOP-CONFIG --security-profile ' + target_authenticator + ' --sign --compress'
  else:
    common_sign_cmd = closest_server + ' secure-image  {_source}  --outfile {_target} --image-id AOP-CONFIG --security-profile ' + target_authenticator + ' --sign '

  oem_sign_cmd = common_sign_cmd.format(_source=source_str, _target=target_str) + ' --signing-mode TEST '

  #print('OEM sign cmd'+oem_sign_cmd)

  _stdout, _stderr, _retval = env.ExecCmds(cmds=oem_sign_cmd, target=target_str, shell=True)

  return

def aop_hash_unsign(target, source, env):
  #builder action, rules to build target from source
  source_str = os.path.abspath(str(source[0]))
  target_str = os.path.abspath(str(target[0]))
  print('Hash UnSign source: ', source_str)
  print('Hash Unsign target: ', target_str)

  if not os.path.exists(source_str) or not os.path.isfile(source_str):
    fatal_signer_err(env, 'SOURCE FILES: ' + source_str + 'Not found')

  closest_server = sectools_remote_find()
  print('Will use ', closest_server, ' instance to sign')

  target_authenticator = sectools_find_authenticator(env)
  #print('Authenticator: ', target_authenticator)

  if ("devcfg_unsigned" in re.search('AOP_.*mbn',target_str).group()):
    hash_unsign_cmd = closest_server + ' secure-image  {_source}  --outfile {_target} --image-id AOP-CONFIG --security-profile ' + target_authenticator + ' --hash --platform-binding INDEPENDENT'
  else:
    hash_unsign_cmd = closest_server + ' secure-image  {_source}  --outfile {_target} --image-id AOP --security-profile ' + target_authenticator + ' --hash --platform-binding INDEPENDENT'

  hash_unsign_cmd = hash_unsign_cmd.format(_source=source_str, _target=target_str)

  #print(hash_unsign_cmd)

  _stdout, _stderr, _retval = env.ExecCmds(cmds=hash_unsign_cmd, target=target_str, shell=True)

  return

def aop_img_sign_wrapper(env, target, source, **kwargs):
  if ('OUTPATH') in kwargs:
    install_base_dir = kwargs.get('OUTPATH')
    env['SECTOOLS_OUTPATH'] = install_base_dir
  else:
    raise RuntimeError("OUTPATH is not defined")

  env.AOPSignXMLGen(env['MSM_ID']) #signing manifest
  qc_signed_aop_image = env.AOPQCSigner(str(target)+'_qconly', source)
  qc_test_signed_aop_image = env.AOPTestSigner(target, qc_signed_aop_image)
  install_aop_mbn = env.InstallAs(os.path.join(install_base_dir, 'aop.mbn'), qc_test_signed_aop_image)
  return install_aop_mbn

def aop_img_unsign_wrapper(env, target, source, **kwargs):
  if ('OUTPATH') in kwargs:
    install_base_dir = kwargs.get('OUTPATH')
    env['SECTOOLS_OUTPATH'] = install_base_dir
  else:
    raise RuntimeError("OUTPATH is not defined")

  env.AOPSignXMLGen(env['MSM_ID']) #signing manifest
  unsigned_aop_image = env.AOPHashUnsigner(str(target)+'_unsigned', source)
  install_aop_mbn = env.InstallAs(os.path.join(install_base_dir, 'aop.mbn'), unsigned_aop_image)
  return install_aop_mbn


def aop_devcfg_sign_wrapper(env, target, source, **kwargs):
  if ('OUTPATH') in kwargs:
    install_base_dir = kwargs.get('OUTPATH')
    env['SECTOOLS_OUTPATH'] = install_base_dir
  else:
    raise RuntimeError("OUTPATH is not defined")

  env.AOPSignXMLGen(env['MSM_ID'])
  qc_test_signed_devcfg_image = env.AOPOEMSigner(target, source)
  install_devcfg_mbn = env.InstallAs(os.path.join(install_base_dir, 'aop_devcfg.mbn'), qc_test_signed_devcfg_image)
  return install_devcfg_mbn

def aop_devcfg_unsign_wrapper(env, target, source, **kwargs):
  if ('OUTPATH') in kwargs:
    install_base_dir = kwargs.get('OUTPATH')
    env['SECTOOLS_OUTPATH'] = install_base_dir
  else:
    raise RuntimeError("OUTPATH is not defined")

  env.AOPSignXMLGen(env['MSM_ID'])
  unsigned_devcfg_image = env.AOPHashUnsigner(target, source)
  install_devcfg_mbn = env.InstallAs(os.path.join(install_base_dir, 'aop_devcfg.mbn'), unsigned_devcfg_image)
  return install_devcfg_mbn

def gen_signing_manifest_wrapper(env, msm_id):
  spf_supported = 0
  if not (((msm_id) in authenticator_map) and ((msm_id) in cass_cap_map)):
    raise RuntimeError("ERROR:: MSM_ID: {_msm_id} not found in authenticator map.".format(_msm_id=msm_id))
  if ("SPF") in os.environ:
    if (os.environ['SPF'] == 'true'):
      supported_targets = ['kailua','camano']
      spf_supported = 1
      
  if("SPF_RISCV") in os.environ:
    if(os.environ['SPF_RISCV'] == 'true'):
      supported_targets = ['lanai','palawan']
      spf_supported = 1
      
  signing_xml_path = '${BUILD_ROOT}/core/bsp/build/authenticators/signing_manifest.xml'
  root = ET.Element("tns:signing_manifest")
  root.set("xmlns:tns", "http://www.qualcomm.com/sectools")
  root.set("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance")
  root.set("schema_version", "1.0")
  root.set("xsi:schemaLocation", "http://www.qualcomm.com/sectools ../signing_manifest/signing_manifest.xsd")

  if 'CREATE_COMPRESSED_MBN' in env:
    int_compress_args = " --compress --compressed-outfile ./../../aop/build/{_msm_id}/AOP_AAAAANAAO_prod.xz"
    ext_compress_args = " --compress --compressed-outfile ./../../../../../HY11_1/aop_proc/core/bsp/aop/build/{_msm_id}/AOP_AAAAANAZO_prod.xz"
  else:
    int_compress_args = ""
    ext_compress_args = ""

  if (spf_supported == 1):
    for msm_id in supported_targets:
      ET.SubElement(root, "secure_image_command").text = ("./../../aop/build/{_msm_id}/AOP_AAAAANAAO.mbn " \
                                                          "--security-profile ./{_msm_id}/{_msm_id}_tme_security_profile.xml "\
                                                          "--image-id AOP --outfile ./../../aop/build/{_msm_id}/AOP_AAAAANAAO_prod.mbn "\
                                                          "--sign --qti --cass-capability {_target_cass_cap}"+int_compress_args).format(_msm_id=msm_id, _target_cass_cap=cass_cap_map[msm_id])
      ET.SubElement(root, "secure_image_command").text = ("./../../../../../HY11_1/aop_proc/core/bsp/aop/build/{_msm_id}/AOP_AAAAANAZO.mbn"\
                                                          " --security-profile ./{_msm_id}/{_msm_id}_tme_security_profile.xml --image-id AOP "\
                                                          "--outfile ./../../../../../HY11_1/aop_proc/core/bsp/aop/build/{_msm_id}/AOP_AAAAANAZO_prod.mbn "\
                                                          "--sign --qti --cass-capability {_target_cass_cap}"+ext_compress_args).format(_msm_id=msm_id, _target_cass_cap=cass_cap_map[msm_id])
  elif msm_id in ['pinnacle'] and os.environ.get('BIN_FOLDER_NAME') is not None:
    bin_folder_name = os.environ['BIN_FOLDER_NAME']
    ET.SubElement(root, "secure_image_command").text = ("./../../aop/build/{_bin_folder_name}/AOP_AAAAANAAO.mbn " \
                                                        "--security-profile ./{_msm_id}/{_msm_id}_tme_security_profile.xml "\
                                                        "--image-id AOP --outfile ./../../aop/build/{_bin_folder_name}/AOP_AAAAANAAO_prod.mbn "\
                                                        "--sign --qti --cass-capability {_target_cass_cap}"+int_compress_args).format(_msm_id=msm_id, _bin_folder_name=bin_folder_name, _target_cass_cap=cass_cap_map[msm_id])
    ET.SubElement(root, "secure_image_command").text = ("./../../../../../HY11_1/aop_proc/core/bsp/aop/build/{_bin_folder_name}/AOP_AAAAANAZO.mbn"\
                                                        " --security-profile ./{_msm_id}/{_msm_id}_tme_security_profile.xml --image-id AOP "\
                                                        "--outfile ./../../../../../HY11_1/aop_proc/core/bsp/aop/build/{_bin_folder_name}/AOP_AAAAANAZO_prod.mbn "\
                                                        "--sign --qti --cass-capability {_target_cass_cap}"+ext_compress_args).format(_msm_id=msm_id, _bin_folder_name=bin_folder_name, _target_cass_cap=cass_cap_map[msm_id])

  else:
    ET.SubElement(root, "secure_image_command").text = ("./../../aop/build/{_msm_id}/AOP_AAAAANAAO.mbn " \
                                                        "--security-profile ./{_msm_id}/{_msm_id}_tme_security_profile.xml "\
                                                        "--image-id AOP --outfile ./../../aop/build/{_msm_id}/AOP_AAAAANAAO_prod.mbn "\
                                                        "--sign --qti --cass-capability {_target_cass_cap}"+int_compress_args).format(_msm_id=msm_id, _target_cass_cap=cass_cap_map[msm_id])
    ET.SubElement(root, "secure_image_command").text = ("./../../../../../HY11_1/aop_proc/core/bsp/aop/build/{_msm_id}/AOP_AAAAANAZO.mbn"\
                                                        " --security-profile ./{_msm_id}/{_msm_id}_tme_security_profile.xml --image-id AOP "\
                                                        "--outfile ./../../../../../HY11_1/aop_proc/core/bsp/aop/build/{_msm_id}/AOP_AAAAANAZO_prod.mbn "\
                                                        "--sign --qti --cass-capability {_target_cass_cap}"+ext_compress_args).format(_msm_id=msm_id, _target_cass_cap=cass_cap_map[msm_id])

  tree = ET.ElementTree(root)
  tree.write(env.RealPath(signing_xml_path), encoding='UTF-8', xml_declaration=True)
  return

