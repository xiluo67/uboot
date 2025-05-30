#
# (C) Copyright 2002-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(ARCH).o

SOBJS-$(CONFIG_SYS_PC_BIOS)	+= bios.o
SOBJS-$(CONFIG_SYS_PCI_BIOS)	+= bios_pci.o
SOBJS-$(CONFIG_SYS_X86_REALMODE)	+= realmode_switch.o

COBJS-$(CONFIG_SYS_PC_BIOS)	+= bios_setup.o
COBJS-y	+= board.o
COBJS-y	+= bootm.o
COBJS-y	+= cmd_boot.o
COBJS-y	+= gcc.o
COBJS-y	+= init_helpers.o
COBJS-y	+= init_wrappers.o
COBJS-y	+= interrupts.o
COBJS-$(CONFIG_SYS_PCAT_INTERRUPTS) += pcat_interrupts.o
COBJS-$(CONFIG_SYS_GENERIC_TIMER) += pcat_timer.o
COBJS-$(CONFIG_PCI) += pci.o
COBJS-$(CONFIG_PCI) += pci_type1.o
COBJS-$(CONFIG_SYS_X86_REALMODE)	+= realmode.o
COBJS-y	+= relocate.o
COBJS-y	+= string.o
COBJS-$(CONFIG_SYS_X86_ISR_TIMER)	+= timer.o
COBJS-$(CONFIG_VIDEO)	+= video_bios.o
COBJS-$(CONFIG_VIDEO)	+= video.o
COBJS-$(CONFIG_CMD_ZBOOT)	+= zimage.o

SRCS	:= $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

$(PREFIXED_LIBGCC): $(NORMAL_LIBGCC)
	$(OBJCOPY) $< $@ --prefix-symbols=__normal_

$(LIB): $(PREFIXED_LIBGCC)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
