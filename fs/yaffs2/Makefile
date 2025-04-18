# Makefile for YAFFS direct test
#
#
# YAFFS: Yet another Flash File System. A NAND-flash specific file system.
#
# Copyright (C) 2003 Aleph One Ltd.
#
#
# Created by Charles Manning <charles@aleph1.co.uk>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# NB Warning this Makefile does not include header dependencies.
#
# $Id: Makefile,v 1.15 2007/07/18 19:40:38 charles Exp $

include $(TOPDIR)/config.mk

LIB = $(obj)libyaffs2.o

COBJS-$(CONFIG_YAFFS2) := \
	yaffs_allocator.o yaffs_attribs.o yaffs_bitmap.o yaffs_uboot_glue.o\
	yaffs_checkptrw.o yaffs_ecc.o yaffs_error.o \
	yaffsfs.o yaffs_guts.o yaffs_nameval.o yaffs_nand.o\
	yaffs_packedtags1.o yaffs_packedtags2.o yaffs_qsort.o \
	yaffs_summary.o yaffs_tagscompat.o yaffs_verify.o yaffs_yaffs1.o \
	yaffs_yaffs2.o yaffs_mtdif.o yaffs_mtdif2.o

SRCS    := $(COBJS-y:.o=.c)
OBJS    := $(addprefix $(obj),$(COBJS-y))

YCFLAGS =  -DCONFIG_YAFFS_DIRECT -DCONFIG_YAFFS_SHORT_NAMES_IN_RAM
YCFLAGS += -DCONFIG_YAFFS_YAFFS2 -DNO_Y_INLINE
YCFLAGS += -DCONFIG_YAFFS_PROVIDE_DEFS -DCONFIG_YAFFSFS_PROVIDE_VALUES

CFLAGS += $(YCFLAGS)
CPPFLAGS +=  $(YCFLAGS)

all:  $(LIB)

$(obj)libyaffs2.a: $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(obj)libyaffs2.o: $(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

.PHONY: clean distclean
clean:
	rm -f $(OBJS)

distclean:  clean
	rm -f $(LIB) core *.bak .depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
