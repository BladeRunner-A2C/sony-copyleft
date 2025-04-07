@echo off
rem ==========================================================================
rem
rem  CBSP Buils system
rem
rem  General Description
rem     build batch file.
rem
rem Copyright (c) 2009-2011 by Qualcomm Technologies, Incorporated.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem
rem --------------------------------------------------------------------------
rem
rem $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/tools/build/scons/build/build.cmd#1 $
rem $DateTime: 2024/04/01 02:51:58 $
rem $Author: cirrusp4svc $
rem $Change: 53033171 $
rem
rem ==========================================================================

setlocal
set startdate=%date%
set starttime=%time%

@echo Start Date=%startdate%, Time=%starttime% > build-log.txt
@echo #------------------------------------------------------------------------------- >> build-log.txt
@echo # ENVIRONMENT BEGIN >> build-log.txt
@echo #------------------------------------------------------------------------------- >> build-log.txt
set >> build-log.txt
@echo #------------------------------------------------------------------------------- >> build-log.txt
@echo # ENVIRONMENT END >> build-log.txt
@echo #------------------------------------------------------------------------------- >> build-log.txt

@echo #------------------------------------------------------------------------------- >> build-log.txt
@echo # BUILD BEGIN >> build-log.txt
@echo #------------------------------------------------------------------------------- >> build-log.txt
@echo %~dp0..\SCons\scripts\scons.bat %* >> build-log.txt
set PYTHONPATH=%~dp0..\SCons\lib;%PYTHONPATH%
python %~dp0log_output.py build-log.txt -- %~dp0..\SCons\scripts\scons.bat %*
@set SCONS_ERRORLEVEL=%ERRORLEVEL%
@echo #------------------------------------------------------------------------------- >> build-log.txt
@echo # BUILD END >> build-log.txt
@echo #------------------------------------------------------------------------------- >> build-log.txt
set endtime=%time%
set enddate=%date%
@echo.
@echo Start Date=%startdate%, Time=%starttime% - End Date=%enddate%, Time=%endtime% >> build-log.txt
@echo Start Date=%startdate%, Time=%starttime% - End Date=%enddate%, Time=%endtime%
@exit /B %SCONS_ERRORLEVEL%
