#
# (C) Copyright 2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# (C) Copyright 2001
# Erik Theisen, Wave 7 Optics, etheisen@mindspring.com.
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

#CFLAGS += -DDEBUG

LIB	= $(obj)libhwmon.o

COBJS-$(CONFIG_DTT_ADM1021) += adm1021.o
COBJS-$(CONFIG_DTT_ADT7460) += adt7460.o
COBJS-$(CONFIG_DTT_DS1621) += ds1621.o
COBJS-$(CONFIG_DTT_DS1722) += ds1722.o
COBJS-$(CONFIG_DTT_DS1775) += ds1775.o
COBJS-$(CONFIG_DTT_LM63) += lm63.o
COBJS-$(CONFIG_DTT_LM73) += lm73.o
COBJS-$(CONFIG_DTT_LM75) += lm75.o
COBJS-$(CONFIG_DTT_LM81) += lm81.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
