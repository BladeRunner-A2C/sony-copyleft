# SPDX-License-Identifier: GPL-2.0-only
################################################################################
#
# r8168 is the Linux device driver released for Realtek Gigabit Ethernet
# controllers with PCI-Express interface.
#
# Copyright(c) 2022 Realtek Semiconductor Corp. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, see <http://www.gnu.org/licenses/>.
#
# Author:
# Realtek NIC software team <nicfae@realtek.com>
# No. 2, Innovation Road II, Hsinchu Science Park, Hsinchu 300, Taiwan
#
################################################################################

################################################################################
#  This product is covered by one or more of the following patents:
#  US6,570,884, US6,115,776, and US6,327,625.
################################################################################
################################################################################
#  Sony imported version:
#   r8168-8.051.02
#
#   add r8168_sony_ext.c
################################################################################

ccflags-y += -DCONFIG_ASPM=y -DCONFIG_DYNAMIC_ASPM=y
ccflags-y += -DENABLE_S5WOL -DENABLE_EEE
ccflags-y += -DR8168_SONY_EXT

obj-$(CONFIG_R8168) += r8168.o
r8168-objs := r8168_n.o r8168_asf.o rtl_eeprom.o rtltool.o
r8168-objs += r8168_sony_ext.o r8168_sony_ext_dmy_eth.o
