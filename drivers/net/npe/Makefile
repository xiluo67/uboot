#
# (C) Copyright 2006
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

LIB := $(obj)libnpe.o

LOCAL_CFLAGS  += -I$(TOPDIR)/drivers/net/npe/include -DCONFIG_IXP425_COMPONENT_ETHDB -D__linux
CFLAGS  += $(LOCAL_CFLAGS)
CPPFLAGS  += $(LOCAL_CFLAGS) # needed for depend
HOSTCFLAGS  += $(LOCAL_CFLAGS)

COBJS-$(CONFIG_IXP4XX_NPE) := npe.o \
	miiphy.o \
	IxOsalBufferMgt.o \
	IxOsalIoMem.o \
	IxOsalOsCacheMMU.o \
	IxOsalOsMsgQ.o \
	IxOsalOsSemaphore.o \
	IxOsalOsServices.o \
	IxOsalOsThread.o \
	IxEthAcc.o \
	IxEthAccCommon.o \
	IxEthAccControlInterface.o \
	IxEthAccDataPlane.o \
	IxEthAccMac.o \
	IxEthAccMii.o \
	IxEthDBAPI.o \
	IxEthDBAPISupport.o \
	IxEthDBCore.o \
	IxEthDBEvents.o \
	IxEthDBFeatures.o \
	IxEthDBFirewall.o \
	IxEthDBHashtable.o \
	IxEthDBLearning.o \
	IxEthDBMem.o \
	IxEthDBNPEAdaptor.o \
	IxEthDBPortUpdate.o \
	IxEthDBReports.o \
	IxEthDBSearch.o \
	IxEthDBSpanningTree.o \
	IxEthDBUtil.o \
	IxEthDBVlan.o \
	IxEthDBWiFi.o \
	IxEthMii.o \
	IxQMgrAqmIf.o \
	IxQMgrDispatcher.o \
	IxQMgrInit.o \
	IxQMgrQAccess.o \
	IxQMgrQCfg.o \
	IxFeatureCtrl.o \
	IxNpeDl.o \
	IxNpeDlImageMgr.o \
	IxNpeDlNpeMgr.o \
	IxNpeDlNpeMgrUtils.o \
	IxNpeMh.o \
	IxNpeMhConfig.o \
	IxNpeMhReceive.o \
	IxNpeMhSend.o \
	IxNpeMhSolicitedCbMgr.o \
	IxNpeMhUnsolicitedCbMgr.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS-y))
SOBJS	:= $(addprefix $(obj),$(SOBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
