/*
 * Copyright (C) 2004-2007 Freescale Semiconductor, Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*Main C file for multi-channel DMA API. */

#include <common.h>

#include <MCD_dma.h>
#include <MCD_tasksInit.h>
#include <MCD_progCheck.h>

/********************************************************************/
/* This is an API-internal pointer to the DMA's registers */
dmaRegs *MCD_dmaBar;

/*
 * These are the real and model task tables as generated by the
 * build process
 */
extern TaskTableEntry MCD_realTaskTableSrc[NCHANNELS];
extern TaskTableEntry MCD_modelTaskTableSrc[NUMOFVARIANTS];

/*
 * However, this (usually) gets relocated to on-chip SRAM, at which
 * point we access them as these tables
 */
volatile TaskTableEntry *MCD_taskTable;
TaskTableEntry *MCD_modelTaskTable;

/*
 * MCD_chStatus[] is an array of status indicators for remembering
 * whether a DMA has ever been attempted on each channel, pausing
 * status, etc.
 */
static int MCD_chStatus[NCHANNELS] = {
	MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA,
	MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA,
	MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA,
	MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA, MCD_NO_DMA
};

/* Prototypes for local functions */
static void MCD_memcpy(int *dest, int *src, u32 size);
static void MCD_resmActions(int channel);

/*
 * Buffer descriptors used for storage of progress info for single Dmas
 * Also used as storage for the DMA for CRCs for single DMAs
 * Otherwise, the DMA does not parse these buffer descriptors
 */
#ifdef MCD_INCLUDE_EU
extern MCD_bufDesc MCD_singleBufDescs[NCHANNELS];
#else
MCD_bufDesc MCD_singleBufDescs[NCHANNELS];
#endif
MCD_bufDesc *MCD_relocBuffDesc;

/* Defines for the debug control register's functions */
#define DBG_CTL_COMP1_TASK	(0x00002000)
#define DBG_CTL_ENABLE		(DBG_CTL_AUTO_ARM	| \
				 DBG_CTL_BREAK		| \
				 DBG_CTL_INT_BREAK	| \
				 DBG_CTL_COMP1_TASK)
#define DBG_CTL_DISABLE		(DBG_CTL_AUTO_ARM	| \
				 DBG_CTL_INT_BREAK	| \
				 DBG_CTL_COMP1_TASK)
#define DBG_KILL_ALL_STAT	(0xFFFFFFFF)

/* Offset to context save area where progress info is stored */
#define CSAVE_OFFSET		10

/* Defines for Byte Swapping */
#define MCD_BYTE_SWAP_KILLER	0xFFF8888F
#define MCD_NO_BYTE_SWAP_ATALL	0x00040000

/* Execution Unit Identifiers */
#define MAC			0	/* legacy - not used */
#define LUAC			1	/* legacy - not used */
#define CRC			2	/* legacy - not used */
#define LURC			3	/* Logic Unit with CRC */

/* Task Identifiers */
#define TASK_CHAINNOEU		0
#define TASK_SINGLENOEU		1
#ifdef MCD_INCLUDE_EU
#define TASK_CHAINEU		2
#define TASK_SINGLEEU		3
#define TASK_FECRX		4
#define TASK_FECTX		5
#else
#define TASK_CHAINEU		0
#define TASK_SINGLEEU		1
#define TASK_FECRX		2
#define TASK_FECTX		3
#endif

/*
 * Structure to remember which variant is on which channel
 * TBD- need this?
 */
typedef struct MCD_remVariants_struct MCD_remVariant;
struct MCD_remVariants_struct {
	int remDestRsdIncr[NCHANNELS];	/* -1,0,1 */
	int remSrcRsdIncr[NCHANNELS];	/* -1,0,1 */
	s16 remDestIncr[NCHANNELS];	/* DestIncr */
	s16 remSrcIncr[NCHANNELS];	/* srcIncr */
	u32 remXferSize[NCHANNELS];	/* xferSize */
};

/* Structure to remember the startDma parameters for each channel */
MCD_remVariant MCD_remVariants;
/********************************************************************/
/* Function: MCD_initDma
 * Purpose:  Initializes the DMA API by setting up a pointer to the DMA
 *           registers, relocating and creating the appropriate task
 *           structures, and setting up some global settings
 * Arguments:
 *  dmaBarAddr    - pointer to the multichannel DMA registers
 *  taskTableDest - location to move DMA task code and structs to
 *  flags         - operational parameters
 * Return Value:
 *  MCD_TABLE_UNALIGNED if taskTableDest is not 512-byte aligned
 *  MCD_OK otherwise
 */
extern u32 MCD_funcDescTab0[];

int MCD_initDma(dmaRegs * dmaBarAddr, void *taskTableDest, u32 flags)
{
	int i;
	TaskTableEntry *entryPtr;

	/* setup the local pointer to register set */
	MCD_dmaBar = dmaBarAddr;

	/* do we need to move/create a task table */
	if ((flags & MCD_RELOC_TASKS) != 0) {
		int fixedSize;
		u32 *fixedPtr;
		/*int *tablePtr = taskTableDest;TBD */
		int varTabsOffset, funcDescTabsOffset, contextSavesOffset;
		int taskDescTabsOffset;
		int taskTableSize, varTabsSize, funcDescTabsSize,
		    contextSavesSize;
		int taskDescTabSize;

		int i;

		/* check if physical address is aligned on 512 byte boundary */
		if (((u32) taskTableDest & 0x000001ff) != 0)
			return (MCD_TABLE_UNALIGNED);

		/* set up local pointer to task Table */
		MCD_taskTable = taskTableDest;

		/*
		 * Create a task table:
		 * - compute aligned base offsets for variable tables and
		 *   function descriptor tables, then
		 * - loop through the task table and setup the pointers
		 * - copy over model task table with the the actual task
		 *   descriptor tables
		 */

		taskTableSize = NCHANNELS * sizeof(TaskTableEntry);
		/* align variable tables to size */
		varTabsOffset = taskTableSize + (u32) taskTableDest;
		if ((varTabsOffset & (VAR_TAB_SIZE - 1)) != 0)
			varTabsOffset =
			    (varTabsOffset + VAR_TAB_SIZE) & (~VAR_TAB_SIZE);
		/* align function descriptor tables */
		varTabsSize = NCHANNELS * VAR_TAB_SIZE;
		funcDescTabsOffset = varTabsOffset + varTabsSize;

		if ((funcDescTabsOffset & (FUNCDESC_TAB_SIZE - 1)) != 0)
			funcDescTabsOffset =
			    (funcDescTabsOffset +
			     FUNCDESC_TAB_SIZE) & (~FUNCDESC_TAB_SIZE);

		funcDescTabsSize = FUNCDESC_TAB_NUM * FUNCDESC_TAB_SIZE;
		contextSavesOffset = funcDescTabsOffset + funcDescTabsSize;
		contextSavesSize = (NCHANNELS * CONTEXT_SAVE_SIZE);
		fixedSize =
		    taskTableSize + varTabsSize + funcDescTabsSize +
		    contextSavesSize;

		/* zero the thing out */
		fixedPtr = (u32 *) taskTableDest;
		for (i = 0; i < (fixedSize / 4); i++)
			fixedPtr[i] = 0;

		entryPtr = (TaskTableEntry *) MCD_taskTable;
		/* set up fixed pointers */
		for (i = 0; i < NCHANNELS; i++) {
			/* update ptr to local value */
			entryPtr[i].varTab = (u32) varTabsOffset;
			entryPtr[i].FDTandFlags =
			    (u32) funcDescTabsOffset | MCD_TT_FLAGS_DEF;
			entryPtr[i].contextSaveSpace = (u32) contextSavesOffset;
			varTabsOffset += VAR_TAB_SIZE;
#ifdef MCD_INCLUDE_EU
			/* if not there is only one, just point to the
			   same one */
			funcDescTabsOffset += FUNCDESC_TAB_SIZE;
#endif
			contextSavesOffset += CONTEXT_SAVE_SIZE;
		}
		/* copy over the function descriptor table */
		for (i = 0; i < FUNCDESC_TAB_NUM; i++) {
			MCD_memcpy((void *)(entryPtr[i].
					    FDTandFlags & ~MCD_TT_FLAGS_MASK),
				   (void *)MCD_funcDescTab0, FUNCDESC_TAB_SIZE);
		}

		/* copy model task table to where the context saves stuff
		   leaves off */
		MCD_modelTaskTable = (TaskTableEntry *) contextSavesOffset;

		MCD_memcpy((void *)MCD_modelTaskTable,
			   (void *)MCD_modelTaskTableSrc,
			   NUMOFVARIANTS * sizeof(TaskTableEntry));

		/* point to local version of model task table */
		entryPtr = MCD_modelTaskTable;
		taskDescTabsOffset = (u32) MCD_modelTaskTable +
		    (NUMOFVARIANTS * sizeof(TaskTableEntry));

		/* copy actual task code and update TDT ptrs in local
		   model task table */
		for (i = 0; i < NUMOFVARIANTS; i++) {
			taskDescTabSize =
			    entryPtr[i].TDTend - entryPtr[i].TDTstart + 4;
			MCD_memcpy((void *)taskDescTabsOffset,
				   (void *)entryPtr[i].TDTstart,
				   taskDescTabSize);
			entryPtr[i].TDTstart = (u32) taskDescTabsOffset;
			taskDescTabsOffset += taskDescTabSize;
			entryPtr[i].TDTend = (u32) taskDescTabsOffset - 4;
		}
#ifdef MCD_INCLUDE_EU
		/* Tack single DMA BDs onto end of code so API controls
		   where they are since DMA might write to them */
		MCD_relocBuffDesc =
		    (MCD_bufDesc *) (entryPtr[NUMOFVARIANTS - 1].TDTend + 4);
#else
		/* DMA does not touch them so they can be wherever and we
		   don't need to waste SRAM on them */
		MCD_relocBuffDesc = MCD_singleBufDescs;
#endif
	} else {
		/* point the would-be relocated task tables and the
		   buffer descriptors to the ones the linker generated */

		if (((u32) MCD_realTaskTableSrc & 0x000001ff) != 0)
			return (MCD_TABLE_UNALIGNED);

		/* need to add code to make sure that every thing else is
		   aligned properly TBD. this is problematic if we init
		   more than once or after running tasks, need to add
		   variable to see if we have aleady init'd */
		entryPtr = MCD_realTaskTableSrc;
		for (i = 0; i < NCHANNELS; i++) {
			if (((entryPtr[i].varTab & (VAR_TAB_SIZE - 1)) != 0) ||
			    ((entryPtr[i].
			      FDTandFlags & (FUNCDESC_TAB_SIZE - 1)) != 0))
				return (MCD_TABLE_UNALIGNED);
		}

		MCD_taskTable = MCD_realTaskTableSrc;
		MCD_modelTaskTable = MCD_modelTaskTableSrc;
		MCD_relocBuffDesc = MCD_singleBufDescs;
	}

	/* Make all channels as totally inactive, and remember them as such: */

	MCD_dmaBar->taskbar = (u32) MCD_taskTable;
	for (i = 0; i < NCHANNELS; i++) {
		MCD_dmaBar->taskControl[i] = 0x0;
		MCD_chStatus[i] = MCD_NO_DMA;
	}

	/* Set up pausing mechanism to inactive state: */
	/* no particular values yet for either comparator registers */
	MCD_dmaBar->debugComp1 = 0;
	MCD_dmaBar->debugComp2 = 0;
	MCD_dmaBar->debugControl = DBG_CTL_DISABLE;
	MCD_dmaBar->debugStatus = DBG_KILL_ALL_STAT;

	/* enable or disable commbus prefetch, really need an ifdef or
	   something to keep from trying to set this in the 8220 */
	if ((flags & MCD_COMM_PREFETCH_EN) != 0)
		MCD_dmaBar->ptdControl &= ~PTD_CTL_COMM_PREFETCH;
	else
		MCD_dmaBar->ptdControl |= PTD_CTL_COMM_PREFETCH;

	return (MCD_OK);
}

/*********************** End of MCD_initDma() ***********************/

/********************************************************************/
/* Function:   MCD_dmaStatus
 * Purpose:    Returns the status of the DMA on the requested channel
 * Arguments:  channel - channel number
 * Returns:    Predefined status indicators
 */
int MCD_dmaStatus(int channel)
{
	u16 tcrValue;

	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	tcrValue = MCD_dmaBar->taskControl[channel];
	if ((tcrValue & TASK_CTL_EN) == 0) {	/* nothing running */
		/* if last reported with task enabled */
		if (MCD_chStatus[channel] == MCD_RUNNING
		    || MCD_chStatus[channel] == MCD_IDLE)
			MCD_chStatus[channel] = MCD_DONE;
	} else {		/* something is running */

		/* There are three possibilities: paused, running or idle. */
		if (MCD_chStatus[channel] == MCD_RUNNING
		    || MCD_chStatus[channel] == MCD_IDLE) {
			MCD_dmaBar->ptdDebug = PTD_DBG_TSK_VLD_INIT;
			/* This register is selected to know which initiator is
			   actually asserted. */
			if ((MCD_dmaBar->ptdDebug >> channel) & 0x1)
				MCD_chStatus[channel] = MCD_RUNNING;
			else
				MCD_chStatus[channel] = MCD_IDLE;
			/* do not change the status if it is already paused. */
		}
	}
	return MCD_chStatus[channel];
}

/******************** End of MCD_dmaStatus() ************************/

/********************************************************************/
/* Function:    MCD_startDma
 * Ppurpose:    Starts a particular kind of DMA
 * Arguments:
 * srcAddr	- the channel on which to run the DMA
 * srcIncr	- the address to move data from, or buffer-descriptor address
 * destAddr	- the amount to increment the source address per transfer
 * destIncr	- the address to move data to
 * dmaSize	- the amount to increment the destination address per transfer
 * xferSize	- the number bytes in of each data movement (1, 2, or 4)
 * initiator	- what device initiates the DMA
 * priority	- priority of the DMA
 * flags	- flags describing the DMA
 * funcDesc	- description of byte swapping, bit swapping, and CRC actions
 * srcAddrVirt	- virtual buffer descriptor address TBD
 * Returns:     MCD_CHANNEL_INVALID if channel is invalid, else MCD_OK
 */

int MCD_startDma(int channel, s8 * srcAddr, s16 srcIncr, s8 * destAddr,
		 s16 destIncr, u32 dmaSize, u32 xferSize, u32 initiator,
		 int priority, u32 flags, u32 funcDesc
#ifdef MCD_NEED_ADDR_TRANS
		 s8 * srcAddrVirt
#endif
    )
{
	int srcRsdIncr, destRsdIncr;
	int *cSave;
	short xferSizeIncr;
	int tcrCount = 0;
#ifdef MCD_INCLUDE_EU
	u32 *realFuncArray;
#endif

	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	/* tbd - need to determine the proper response to a bad funcDesc when
	   not including EU functions, for now, assign a benign funcDesc, but
	   maybe should return an error */
#ifndef MCD_INCLUDE_EU
	funcDesc = MCD_FUNC_NOEU1;
#endif

#ifdef MCD_DEBUG
	printf("startDma:Setting up params\n");
#endif
	/* Set us up for task-wise priority.  We don't technically need to do
	   this on every start, but since the register involved is in the same
	   longword as other registers that users are in control of, setting
	   it more than once is probably preferable.  That since the
	   documentation doesn't seem to be completely consistent about the
	   nature of the PTD control register. */
	MCD_dmaBar->ptdControl |= (u16) 0x8000;

	/* Not sure what we need to keep here rtm TBD */
#if 1
	/* Calculate additional parameters to the regular DMA calls. */
	srcRsdIncr = srcIncr < 0 ? -1 : (srcIncr > 0 ? 1 : 0);
	destRsdIncr = destIncr < 0 ? -1 : (destIncr > 0 ? 1 : 0);

	xferSizeIncr = (xferSize & 0xffff) | 0x20000000;

	/* Remember for each channel which variant is running. */
	MCD_remVariants.remSrcRsdIncr[channel] = srcRsdIncr;
	MCD_remVariants.remDestRsdIncr[channel] = destRsdIncr;
	MCD_remVariants.remDestIncr[channel] = destIncr;
	MCD_remVariants.remSrcIncr[channel] = srcIncr;
	MCD_remVariants.remXferSize[channel] = xferSize;
#endif

	cSave =
	    (int *)(MCD_taskTable[channel].contextSaveSpace) + CSAVE_OFFSET +
	    CURRBD;

#ifdef MCD_INCLUDE_EU
	/* may move this to EU specific calls */
	realFuncArray =
	    (u32 *) (MCD_taskTable[channel].FDTandFlags & 0xffffff00);
	/* Modify the LURC's normal and byte-residue-loop functions according
	   to parameter. */
	realFuncArray[(LURC * 16)] = xferSize == 4 ?
	    funcDesc : xferSize == 2 ?
	    funcDesc & 0xfffff00f : funcDesc & 0xffff000f;
	realFuncArray[(LURC * 16 + 1)] =
	    (funcDesc & MCD_BYTE_SWAP_KILLER) | MCD_NO_BYTE_SWAP_ATALL;
#endif
	/* Write the initiator field in the TCR, and also set the
	   initiator-hold bit. Note that,due to a hardware quirk, this could
	   collide with an MDE access to the initiator-register file, so we
	   have to verify that the write reads back correctly. */

	MCD_dmaBar->taskControl[channel] =
	    (initiator << 8) | TASK_CTL_HIPRITSKEN | TASK_CTL_HLDINITNUM;

	while (((MCD_dmaBar->taskControl[channel] & 0x1fff) !=
		((initiator << 8) | TASK_CTL_HIPRITSKEN | TASK_CTL_HLDINITNUM))
	       && (tcrCount < 1000)) {
		tcrCount++;
		/*MCD_dmaBar->ptd_tcr[channel] = (initiator << 8) | 0x0020; */
		MCD_dmaBar->taskControl[channel] =
		    (initiator << 8) | TASK_CTL_HIPRITSKEN |
		    TASK_CTL_HLDINITNUM;
	}

	MCD_dmaBar->priority[channel] = (u8) priority & PRIORITY_PRI_MASK;
	/* should be albe to handle this stuff with only one write to ts reg
	   - tbd */
	if (channel < 8 && channel >= 0) {
		MCD_dmaBar->taskSize0 &= ~(0xf << (7 - channel) * 4);
		MCD_dmaBar->taskSize0 |=
		    (xferSize & 3) << (((7 - channel) * 4) + 2);
		MCD_dmaBar->taskSize0 |= (xferSize & 3) << ((7 - channel) * 4);
	} else {
		MCD_dmaBar->taskSize1 &= ~(0xf << (15 - channel) * 4);
		MCD_dmaBar->taskSize1 |=
		    (xferSize & 3) << (((15 - channel) * 4) + 2);
		MCD_dmaBar->taskSize1 |= (xferSize & 3) << ((15 - channel) * 4);
	}

	/* setup task table flags/options which mostly control the line
	   buffers */
	MCD_taskTable[channel].FDTandFlags &= ~MCD_TT_FLAGS_MASK;
	MCD_taskTable[channel].FDTandFlags |= (MCD_TT_FLAGS_MASK & flags);

	if (flags & MCD_FECTX_DMA) {
		/* TDTStart and TDTEnd */
		MCD_taskTable[channel].TDTstart =
		    MCD_modelTaskTable[TASK_FECTX].TDTstart;
		MCD_taskTable[channel].TDTend =
		    MCD_modelTaskTable[TASK_FECTX].TDTend;
		MCD_startDmaENetXmit((char *)srcAddr, (char *)srcAddr,
				     (char *)destAddr, MCD_taskTable,
				     channel);
	} else if (flags & MCD_FECRX_DMA) {
		/* TDTStart and TDTEnd */
		MCD_taskTable[channel].TDTstart =
		    MCD_modelTaskTable[TASK_FECRX].TDTstart;
		MCD_taskTable[channel].TDTend =
		    MCD_modelTaskTable[TASK_FECRX].TDTend;
		MCD_startDmaENetRcv((char *)srcAddr, (char *)srcAddr,
				    (char *)destAddr, MCD_taskTable,
				    channel);
	} else if (flags & MCD_SINGLE_DMA) {
		/* this buffer descriptor is used for storing off initial
		   parameters for later progress query calculation and for the
		   DMA to write the resulting checksum. The DMA does not use
		   this to determine how to operate, that info is passed with
		   the init routine */
		MCD_relocBuffDesc[channel].srcAddr = srcAddr;
		MCD_relocBuffDesc[channel].destAddr = destAddr;

		/* definitely not its final value */
		MCD_relocBuffDesc[channel].lastDestAddr = destAddr;

		MCD_relocBuffDesc[channel].dmaSize = dmaSize;
		MCD_relocBuffDesc[channel].flags = 0;	/* not used */
		MCD_relocBuffDesc[channel].csumResult = 0;	/* not used */
		MCD_relocBuffDesc[channel].next = 0;	/* not used */

		/* Initialize the progress-querying stuff to show no
		   progress: */
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[SRCPTR + CSAVE_OFFSET] = (int)srcAddr;
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[DESTPTR + CSAVE_OFFSET] = (int)destAddr;
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[DCOUNT + CSAVE_OFFSET] = 0;
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[CURRBD + CSAVE_OFFSET] =
(u32) & (MCD_relocBuffDesc[channel]);
		/* tbd - need to keep the user from trying to call the EU
		   routine when MCD_INCLUDE_EU is not defined */
		if (funcDesc == MCD_FUNC_NOEU1 || funcDesc == MCD_FUNC_NOEU2) {
			/* TDTStart and TDTEnd */
			MCD_taskTable[channel].TDTstart =
			    MCD_modelTaskTable[TASK_SINGLENOEU].TDTstart;
			MCD_taskTable[channel].TDTend =
			    MCD_modelTaskTable[TASK_SINGLENOEU].TDTend;
			MCD_startDmaSingleNoEu((char *)srcAddr, srcIncr,
					       (char *)destAddr, destIncr,
					       (int)dmaSize, xferSizeIncr,
					       flags, (int *)
					       &(MCD_relocBuffDesc[channel]),
					       cSave, MCD_taskTable, channel);
		} else {
			/* TDTStart and TDTEnd */
			MCD_taskTable[channel].TDTstart =
			    MCD_modelTaskTable[TASK_SINGLEEU].TDTstart;
			MCD_taskTable[channel].TDTend =
			    MCD_modelTaskTable[TASK_SINGLEEU].TDTend;
			MCD_startDmaSingleEu((char *)srcAddr, srcIncr,
					     (char *)destAddr, destIncr,
					     (int)dmaSize, xferSizeIncr,
					     flags, (int *)
					     &(MCD_relocBuffDesc[channel]),
					     cSave, MCD_taskTable, channel);
		}
	} else {		/* chained DMAS */
		/* Initialize the progress-querying stuff to show no
		   progress: */
#if 1
		/* (!defined(MCD_NEED_ADDR_TRANS)) */
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[SRCPTR + CSAVE_OFFSET]
		    = (int)((MCD_bufDesc *) srcAddr)->srcAddr;
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[DESTPTR + CSAVE_OFFSET]
		    = (int)((MCD_bufDesc *) srcAddr)->destAddr;
#else
		/* if using address translation, need the virtual addr of the
		   first buffdesc */
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[SRCPTR + CSAVE_OFFSET]
		    = (int)((MCD_bufDesc *) srcAddrVirt)->srcAddr;
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[DESTPTR + CSAVE_OFFSET]
		    = (int)((MCD_bufDesc *) srcAddrVirt)->destAddr;
#endif
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[DCOUNT + CSAVE_OFFSET] = 0;
		((volatile int *)MCD_taskTable[channel].
		 contextSaveSpace)[CURRBD + CSAVE_OFFSET] = (u32) srcAddr;

		if (funcDesc == MCD_FUNC_NOEU1 || funcDesc == MCD_FUNC_NOEU2) {
			/*TDTStart and TDTEnd */
			MCD_taskTable[channel].TDTstart =
			    MCD_modelTaskTable[TASK_CHAINNOEU].TDTstart;
			MCD_taskTable[channel].TDTend =
			    MCD_modelTaskTable[TASK_CHAINNOEU].TDTend;
			MCD_startDmaChainNoEu((int *)srcAddr, srcIncr,
					      destIncr, xferSize,
					      xferSizeIncr, cSave,
					      MCD_taskTable, channel);
		} else {
			/*TDTStart and TDTEnd */
			MCD_taskTable[channel].TDTstart =
			    MCD_modelTaskTable[TASK_CHAINEU].TDTstart;
			MCD_taskTable[channel].TDTend =
			    MCD_modelTaskTable[TASK_CHAINEU].TDTend;
			MCD_startDmaChainEu((int *)srcAddr, srcIncr, destIncr,
					    xferSize, xferSizeIncr, cSave,
					    MCD_taskTable, channel);
		}
	}
	MCD_chStatus[channel] = MCD_IDLE;
	return (MCD_OK);
}

/************************ End of MCD_startDma() *********************/

/********************************************************************/
/* Function:    MCD_XferProgrQuery
 * Purpose:     Returns progress of DMA on requested channel
 * Arguments:   channel - channel to retrieve progress for
 *              progRep - pointer to user supplied MCD_XferProg struct
 * Returns:     MCD_CHANNEL_INVALID if channel is invalid, else MCD_OK
 *
 * Notes:
 *  MCD_XferProgrQuery() upon completing or after aborting a DMA, or
 *  while the DMA is in progress, this function returns the first
 *  DMA-destination address not (or not yet) used in the DMA. When
 *  encountering a non-ready buffer descriptor, the information for
 *  the last completed descriptor is returned.
 *
 *  MCD_XferProgQuery() has to avoid the possibility of getting
 *  partially-updated information in the event that we should happen
 *  to query DMA progress just as the DMA is updating it. It does that
 *  by taking advantage of the fact context is not saved frequently for
 *  the most part. We therefore read it at least twice until we get the
 *  same information twice in a row.
 *
 *  Because a small, but not insignificant, amount of time is required
 *  to write out the progress-query information, especially upon
 *  completion of the DMA, it would be wise to guarantee some time lag
 *  between successive readings of the progress-query information.
 */

/* How many iterations of the loop below to execute to stabilize values */
#define STABTIME 0

int MCD_XferProgrQuery(int channel, MCD_XferProg * progRep)
{
	MCD_XferProg prevRep;
	int again;		/* true if we are to try again to ge
				   consistent results */
	int i;			/* used as a time-waste counter */
	int destDiffBytes;	/* Total no of bytes that we think actually
				   got xfered. */
	int numIterations;	/* number of iterations */
	int bytesNotXfered;	/* bytes that did not get xfered. */
	s8 *LWAlignedInitDestAddr, *LWAlignedCurrDestAddr;
	int subModVal, addModVal;	/* Mode values to added and subtracted
					   from the final destAddr */

	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	/* Read a trial value for the progress-reporting values */
	prevRep.lastSrcAddr =
	    (s8 *) ((volatile int *)MCD_taskTable[channel].
		    contextSaveSpace)[SRCPTR + CSAVE_OFFSET];
	prevRep.lastDestAddr =
	    (s8 *) ((volatile int *)MCD_taskTable[channel].
		    contextSaveSpace)[DESTPTR + CSAVE_OFFSET];
	prevRep.dmaSize =
	    ((volatile int *)MCD_taskTable[channel].contextSaveSpace)[DCOUNT +
								      CSAVE_OFFSET];
	prevRep.currBufDesc =
	    (MCD_bufDesc *) ((volatile int *)MCD_taskTable[channel].
			     contextSaveSpace)[CURRBD + CSAVE_OFFSET];
	/* Repeatedly reread those values until they match previous values: */
	do {
		/* Waste a little bit of time to ensure stability: */
		for (i = 0; i < STABTIME; i++) {
			/* make sure this loop does something so that it
			   doesn't get optimized out */
			i += i >> 2;
		}
		/* Check them again: */
		progRep->lastSrcAddr =
		    (s8 *) ((volatile int *)MCD_taskTable[channel].
			    contextSaveSpace)[SRCPTR + CSAVE_OFFSET];
		progRep->lastDestAddr =
		    (s8 *) ((volatile int *)MCD_taskTable[channel].
			    contextSaveSpace)[DESTPTR + CSAVE_OFFSET];
		progRep->dmaSize =
		    ((volatile int *)MCD_taskTable[channel].
		     contextSaveSpace)[DCOUNT + CSAVE_OFFSET];
		progRep->currBufDesc =
		    (MCD_bufDesc *) ((volatile int *)MCD_taskTable[channel].
				     contextSaveSpace)[CURRBD + CSAVE_OFFSET];
		/* See if they match: */
		if (prevRep.lastSrcAddr != progRep->lastSrcAddr
		    || prevRep.lastDestAddr != progRep->lastDestAddr
		    || prevRep.dmaSize != progRep->dmaSize
		    || prevRep.currBufDesc != progRep->currBufDesc) {
			/* If they don't match, remember previous values and
			   try again: */
			prevRep.lastSrcAddr = progRep->lastSrcAddr;
			prevRep.lastDestAddr = progRep->lastDestAddr;
			prevRep.dmaSize = progRep->dmaSize;
			prevRep.currBufDesc = progRep->currBufDesc;
			again = MCD_TRUE;
		} else
			again = MCD_FALSE;
	} while (again == MCD_TRUE);

	/* Update the dCount, srcAddr and destAddr */
	/* To calculate dmaCount, we consider destination address. C
	   overs M1,P1,Z for destination */
	switch (MCD_remVariants.remDestRsdIncr[channel]) {
	case MINUS1:
		subModVal =
		    ((int)progRep->
		     lastDestAddr) & ((MCD_remVariants.remXferSize[channel]) -
				      1);
		addModVal =
		    ((int)progRep->currBufDesc->
		     destAddr) & ((MCD_remVariants.remXferSize[channel]) - 1);
		LWAlignedInitDestAddr =
		    (progRep->currBufDesc->destAddr) - addModVal;
		LWAlignedCurrDestAddr = (progRep->lastDestAddr) - subModVal;
		destDiffBytes = LWAlignedInitDestAddr - LWAlignedCurrDestAddr;
		bytesNotXfered =
		    (destDiffBytes / MCD_remVariants.remDestIncr[channel]) *
		    (MCD_remVariants.remDestIncr[channel]
		     + MCD_remVariants.remXferSize[channel]);
		progRep->dmaSize =
		    destDiffBytes - bytesNotXfered + addModVal - subModVal;
		break;
	case ZERO:
		progRep->lastDestAddr = progRep->currBufDesc->destAddr;
		break;
	case PLUS1:
		/* This value has to be subtracted from the final
		   calculated dCount. */
		subModVal =
		    ((int)progRep->currBufDesc->
		     destAddr) & ((MCD_remVariants.remXferSize[channel]) - 1);
		/* These bytes are already in lastDestAddr. */
		addModVal =
		    ((int)progRep->
		     lastDestAddr) & ((MCD_remVariants.remXferSize[channel]) -
				      1);
		LWAlignedInitDestAddr =
		    (progRep->currBufDesc->destAddr) - subModVal;
		LWAlignedCurrDestAddr = (progRep->lastDestAddr) - addModVal;
		destDiffBytes = (progRep->lastDestAddr - LWAlignedInitDestAddr);
		numIterations =
		    (LWAlignedCurrDestAddr -
		     LWAlignedInitDestAddr) /
		    MCD_remVariants.remDestIncr[channel];
		bytesNotXfered =
		    numIterations * (MCD_remVariants.remDestIncr[channel]
				     - MCD_remVariants.remXferSize[channel]);
		progRep->dmaSize = destDiffBytes - bytesNotXfered - subModVal;
		break;
	default:
		break;
	}

	/* This covers M1,P1,Z for source */
	switch (MCD_remVariants.remSrcRsdIncr[channel]) {
	case MINUS1:
		progRep->lastSrcAddr =
		    progRep->currBufDesc->srcAddr +
		    (MCD_remVariants.remSrcIncr[channel] *
		     (progRep->dmaSize / MCD_remVariants.remXferSize[channel]));
		break;
	case ZERO:
		progRep->lastSrcAddr = progRep->currBufDesc->srcAddr;
		break;
	case PLUS1:
		progRep->lastSrcAddr =
		    progRep->currBufDesc->srcAddr +
		    (MCD_remVariants.remSrcIncr[channel] *
		     (progRep->dmaSize / MCD_remVariants.remXferSize[channel]));
		break;
	default:
		break;
	}

	return (MCD_OK);
}

/******************* End of MCD_XferProgrQuery() ********************/

/********************************************************************/
/* MCD_resmActions() does the majority of the actions of a DMA resume.
 * It is called from MCD_killDma() and MCD_resumeDma().  It has to be
 * a separate function because the kill function has to negate the task
 * enable before resuming it, but the resume function has to do nothing
 * if there is no DMA on that channel (i.e., if the enable bit is 0).
 */
static void MCD_resmActions(int channel)
{
	MCD_dmaBar->debugControl = DBG_CTL_DISABLE;
	MCD_dmaBar->debugStatus = MCD_dmaBar->debugStatus;
	/* This register is selected to know which initiator is
	   actually asserted. */
	MCD_dmaBar->ptdDebug = PTD_DBG_TSK_VLD_INIT;

	if ((MCD_dmaBar->ptdDebug >> channel) & 0x1)
		MCD_chStatus[channel] = MCD_RUNNING;
	else
		MCD_chStatus[channel] = MCD_IDLE;
}

/********************* End of MCD_resmActions() *********************/

/********************************************************************/
/* Function:    MCD_killDma
 * Purpose:     Halt the DMA on the requested channel, without any
 *              intention of resuming the DMA.
 * Arguments:   channel - requested channel
 * Returns:     MCD_CHANNEL_INVALID if channel is invalid, else MCD_OK
 *
 * Notes:
 *  A DMA may be killed from any state, including paused state, and it
 *  always goes to the MCD_HALTED state even if it is killed while in
 *  the MCD_NO_DMA or MCD_IDLE states.
 */
int MCD_killDma(int channel)
{
	/* MCD_XferProg progRep; */

	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	MCD_dmaBar->taskControl[channel] = 0x0;
	MCD_resumeDma(channel);
	/*
	 * This must be after the write to the TCR so that the task doesn't
	 * start up again momentarily, and before the status assignment so
	 * as to override whatever MCD_resumeDma() may do to the channel
	 * status.
	 */
	MCD_chStatus[channel] = MCD_HALTED;

	/*
	 * Update the current buffer descriptor's lastDestAddr field
	 *
	 * MCD_XferProgrQuery (channel, &progRep);
	 * progRep.currBufDesc->lastDestAddr = progRep.lastDestAddr;
	 */
	return (MCD_OK);
}

/************************ End of MCD_killDma() **********************/

/********************************************************************/
/* Function:    MCD_continDma
 * Purpose:     Continue a DMA which as stopped due to encountering an
 *              unready buffer descriptor.
 * Arguments:   channel - channel to continue the DMA on
 * Returns:     MCD_CHANNEL_INVALID if channel is invalid, else MCD_OK
 *
 * Notes:
 *  This routine does not check to see if there is a task which can
 *  be continued. Also this routine should not be used with single DMAs.
 */
int MCD_continDma(int channel)
{
	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	MCD_dmaBar->taskControl[channel] |= TASK_CTL_EN;
	MCD_chStatus[channel] = MCD_RUNNING;

	return (MCD_OK);
}

/********************** End of MCD_continDma() **********************/

/*********************************************************************
 * MCD_pauseDma() and MCD_resumeDma() below use the DMA's debug unit
 * to freeze a task and resume it.  We freeze a task by breakpointing
 * on the stated task.  That is, not any specific place in the task,
 * but any time that task executes.  In particular, when that task
 * executes, we want to freeze that task and only that task.
 *
 * The bits of the debug control register influence interrupts vs.
 * breakpoints as follows:
 * - Bits 14 and 0 enable or disable debug functions.  If enabled, you
 *   will get the interrupt but you may or may not get a breakpoint.
 * - Bits 2 and 1 decide whether you also get a breakpoint in addition
 *   to an interrupt.
 *
 * The debug unit can do these actions in response to either internally
 * detected breakpoint conditions from the comparators, or in response
 * to the external breakpoint pin, or both.
 * - Bits 14 and 1 perform the above-described functions for
 *   internally-generated conditions, i.e., the debug comparators.
 * - Bits 0 and 2 perform the above-described functions for external
 *   conditions, i.e., the breakpoint external pin.
 *
 * Note that, although you "always" get the interrupt when you turn
 * the debug functions, the interrupt can nevertheless, if desired, be
 * masked by the corresponding bit in the PTD's IMR. Note also that
 * this means that bits 14 and 0 must enable debug functions before
 * bits 1 and 2, respectively, have any effect.
 *
 * NOTE: It's extremely important to not pause more than one DMA channel
 *  at a time.
 ********************************************************************/

/********************************************************************/
/* Function:    MCD_pauseDma
 * Purpose:     Pauses the DMA on a given channel (if any DMA is running
 *              on that channel).
 * Arguments:   channel
 * Returns:     MCD_CHANNEL_INVALID if channel is invalid, else MCD_OK
 */
int MCD_pauseDma(int channel)
{
	/* MCD_XferProg progRep; */

	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	if (MCD_dmaBar->taskControl[channel] & TASK_CTL_EN) {
		MCD_dmaBar->debugComp1 = channel;
		MCD_dmaBar->debugControl =
		    DBG_CTL_ENABLE | (1 << (channel + 16));
		MCD_chStatus[channel] = MCD_PAUSED;

		/*
		 * Update the current buffer descriptor's lastDestAddr field
		 *
		 * MCD_XferProgrQuery (channel, &progRep);
		 * progRep.currBufDesc->lastDestAddr = progRep.lastDestAddr;
		 */
	}
	return (MCD_OK);
}

/************************* End of MCD_pauseDma() ********************/

/********************************************************************/
/* Function:    MCD_resumeDma
 * Purpose:     Resumes the DMA on a given channel (if any DMA is
 *              running on that channel).
 * Arguments:   channel - channel on which to resume DMA
 * Returns:     MCD_CHANNEL_INVALID if channel is invalid, else MCD_OK
 */
int MCD_resumeDma(int channel)
{
	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	if (MCD_dmaBar->taskControl[channel] & TASK_CTL_EN)
		MCD_resmActions(channel);

	return (MCD_OK);
}

/************************ End of MCD_resumeDma() ********************/

/********************************************************************/
/* Function:    MCD_csumQuery
 * Purpose:     Provide the checksum after performing a non-chained DMA
 * Arguments:   channel - channel to report on
 *              csum - pointer to where to write the checksum/CRC
 * Returns:     MCD_ERROR if the channel is invalid, else MCD_OK
 *
 * Notes:
 *
 */
int MCD_csumQuery(int channel, u32 * csum)
{
#ifdef MCD_INCLUDE_EU
	if ((channel < 0) || (channel >= NCHANNELS))
		return (MCD_CHANNEL_INVALID);

	*csum = MCD_relocBuffDesc[channel].csumResult;
	return (MCD_OK);
#else
	return (MCD_ERROR);
#endif
}

/*********************** End of MCD_resumeDma() *********************/

/********************************************************************/
/* Function:    MCD_getCodeSize
 * Purpose:     Provide the size requirements of the microcoded tasks
 * Returns:     Size in bytes
 */
int MCD_getCodeSize(void)
{
#ifdef MCD_INCLUDE_EU
	return (0x2b5c);
#else
	return (0x173c);
#endif
}

/********************** End of MCD_getCodeSize() ********************/

/********************************************************************/
/* Function:    MCD_getVersion
 * Purpose:     Provide the version string and number
 * Arguments:   longVersion - user supplied pointer to a pointer to a char
 *                    which points to the version string
 * Returns:     Version number and version string (by reference)
 */
char MCD_versionString[] = "Multi-channel DMA API Alpha v0.3 (2004-04-26)";
#define MCD_REV_MAJOR   0x00
#define MCD_REV_MINOR   0x03

int MCD_getVersion(char **longVersion)
{
	*longVersion = MCD_versionString;
	return ((MCD_REV_MAJOR << 8) | MCD_REV_MINOR);
}

/********************** End of MCD_getVersion() *********************/

/********************************************************************/
/* Private version of memcpy()
 * Note that everything this is used for is longword-aligned.
 */
static void MCD_memcpy(int *dest, int *src, u32 size)
{
	u32 i;

	for (i = 0; i < size; i += sizeof(int), dest++, src++)
		*dest = *src;
}
