.. -*- coding: utf-8 -*-

.. FILE: README.txt (for DTBExtnLib)


.. _DTBExtnLib:

==========
DTBExtnLib
==========

This is the base library for all DTB support within QC Boot FW::

  core.boot.6.0.xyz/
      .../QcomPkg/Include/Library/
        DTBExtnLib.h (APIs defined here, includes DTBDefs.h)
        DTBDefs.h (I/F defined here, split out because of UEFI)
        DTBExtnUEFILib.h (UEFI Wrapper APIs)
      
      .../QcomPkg/Include/Protocol/
        EFIDtbExtn.h (UEFI Protocol definition for DTBExtnLib)
      
      .../QcomPkg/Library/DTBExtnLib/
        *.c (source code)
        DTBExtnLib_env.h
            Handle slight platform build variants: PORT_ARMv8 & PORT_Q6
      
      .../QcomPkg/Library/DTBExtnUEFILib/
        DTBExtnUEFILib.c (Wrap Protocol Library to look like normal API calls)
        DTBuefiWrapper.c (Wrap Protocol Wrapper Library to have identical API)
      
      .../QcomPkg/XBLCore/SecDtb.c (UEFI Protocol implementation)


WHEN ADDING A NEW API, THE FOLLOWING CHANGES ARE REQUIRED:

1) New prototype in DTBExtnLib.h
2) New prototype in DTBExtnUEFILib.h
3) New typedef in EFIDtbExtn.h (added to struct as well)
4) New API in .../QcomPkg/Library/DTBExtnLib/\*.c
5) New Protocol API in DTBExtnUEFILib.c
6) New Protocol Wrapper in DTBuefiWrapper.c

Blow away whole Build/ folder and rebuild from scratch


WHEN PORTING TO OTHER ENVIRONMENTS::

  Only Base library code needs to be ported to other environments, e.g. qdsp6.
  	.../QcomPkg/Library/DTBExtnLib/
  	.../QcomPkg/Include/Library/DTBExtnLib.h
  	.../QcomPkg/Include/Library/DTBDefs.h

Actual DeviceTree Source files are found under .../Settings/

