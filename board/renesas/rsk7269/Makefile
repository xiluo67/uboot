#
# Copyright (C) 2012 Renesas Electronics Europe Ltd.
# Copyright (C) 2012 Phil Edworthy
#
# This file is released under the terms of GPL v2 and any later version.
# See the file COPYING in the root directory of the source tree for details.

include $(TOPDIR)/config.mk

LIB	= lib$(BOARD).o

OBJS	:= rsk7269.o
SOBJS	:= lowlevel_init.o

LIB	:= $(addprefix $(obj),$(LIB))
OBJS	:= $(addprefix $(obj),$(OBJS))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

$(LIB):	$(obj).depend $(OBJS) $(SOBJS)
	$(call cmd_link_o_target, $(OBJS) $(SOBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend
