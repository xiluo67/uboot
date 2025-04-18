#
# (C) Copyright 2008
# Stefan Roese, DENX Software Engineering, sr@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#
#
# AMCC 460EX Reference Platform (Canyonlands) board
#

#
# CONFIG_SYS_TEXT_BASE for SPL:
#
# On 460EX platforms the SPL is located at 0xfffff000...0xffffffff,
# in the last 4kBytes of memory space in cache.
# We will copy this SPL into internal SRAM in start.S. So we set
# CONFIG_SYS_TEXT_BASE to starting address in internal SRAM here.
#
CONFIG_SYS_TEXT_BASE = 0xE3003000

# PAD_TO used to generate a 128kByte binary needed for the combined image
# -> PAD_TO = CONFIG_SYS_TEXT_BASE + 0x20000
PAD_TO	= 0xE3023000

PLATFORM_CPPFLAGS += -DCONFIG_440=1

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG
endif

ifeq ($(dbcr),1)
PLATFORM_CPPFLAGS += -DCONFIG_SYS_INIT_DBCR=0x8cff0000
endif
