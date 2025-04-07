@echo off
rem ===============================================================================
rem 
rem  Pack Compile Test All
rem 
rem  GENERAL DESCRIPTION
rem     Call pack_compile_test_all.py
rem 
rem  Copyright (c) 2011-2012 by QUALCOMM, Incorporated.
rem  All Rights Reserved.
rem  QUALCOMM Proprietary/GTDR
rem 
rem -------------------------------------------------------------------------------
rem 
rem   $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/pack/pack_compile_test_all.cmd#1 $
rem   $DateTime: 2024/04/01 02:51:58 $
rem   $Change: 53033171 $
rem 
rem ===============================================================================

python pack_compile_test_all.py %*
set BUILD_ERRORLEVEL=%ERRORLEVEL%
exit /B %BUILD_ERRORLEVEL%
