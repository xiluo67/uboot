/* mv_gen_reg.h - Internal registers definition file */
/* Copyright - Galileo technology. */


/*******************************************************************************
*		    Copyright 2002, GALILEO TECHNOLOGY, LTD.		       *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL.		       *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE	       *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*									       *
* MARVELL COMPRISES MARVELL TECHNOLOGY GROUP LTD. (MTGL) AND ITS SUBSIDIARIES, *
* MARVELL INTERNATIONAL LTD. (MIL), MARVELL TECHNOLOGY, INC. (MTI), MARVELL    *
* SEMICONDUCTOR, INC. (MSI), MARVELL ASIA PTE LTD. (MAPL), MARVELL JAPAN K.K.  *
* (MJKK), GALILEO TECHNOLOGY LTD. (GTL) AND GALILEO TECHNOLOGY, INC. (GTI).    *
********************************************************************************
* mv_gen_reg.h - Marvell 64360 and 64460 Internal registers definition file.
*
* DESCRIPTION:
*	None.
*
* DEPENDENCIES:
*	None.
*
*******************************************************************************/

#ifndef __INCmv_gen_regh
#define __INCmv_gen_regh


/* Supported by the Atlantis */
#define INCLUDE_PCI_1
#define INCLUDE_PCI_0_ARBITER
#define INCLUDE_PCI_1_ARBITER
#define INCLUDE_SNOOP_SUPPORT
#define INCLUDE_P2P
#define INCLUDE_ETH_PORT_2
#define INCLUDE_CPU_MAPPING
#define INCLUDE_MPSC

/* Not supported features */
#undef	INCLUDE_CNTMR_4_7
#undef	INCLUDE_DMA_4_7


/****************************************/
/* Processor Address Space				*/
/****************************************/
/* DDR SDRAM BAR and size registers */

/* Sdram's BAR'S */
#define SCS_0_LOW_DECODE_ADDRESS			0x008
#define SCS_0_HIGH_DECODE_ADDRESS			0x010
#define SCS_1_LOW_DECODE_ADDRESS			0x208
#define SCS_1_HIGH_DECODE_ADDRESS			0x210
#define SCS_2_LOW_DECODE_ADDRESS			0x018
#define SCS_2_HIGH_DECODE_ADDRESS			0x020
#define SCS_3_LOW_DECODE_ADDRESS			0x218
#define SCS_3_HIGH_DECODE_ADDRESS			0x220

/* Make it fit the MV64360 and MV64460 Lowlevel driver */
#define CS_0_BASE_ADDR			SCS_0_LOW_DECODE_ADDRESS
#define CS_0_SIZE			SCS_0_HIGH_DECODE_ADDRESS
#define CS_1_BASE_ADDR		SCS_1_LOW_DECODE_ADDRESS
#define CS_1_SIZE			SCS_1_HIGH_DECODE_ADDRESS
#define CS_2_BASE_ADDR		SCS_2_LOW_DECODE_ADDRESS
#define CS_2_SIZE			SCS_2_HIGH_DECODE_ADDRESS
#define CS_3_BASE_ADDR		SCS_3_LOW_DECODE_ADDRESS
#define CS_3_SIZE			SCS_3_HIGH_DECODE_ADDRESS

/* Devices BAR'S */
#define CS_0_LOW_DECODE_ADDRESS			0x028
#define CS_0_HIGH_DECODE_ADDRESS			0x030
#define CS_1_LOW_DECODE_ADDRESS			0x228
#define CS_1_HIGH_DECODE_ADDRESS			0x230
#define CS_2_LOW_DECODE_ADDRESS			0x248
#define CS_2_HIGH_DECODE_ADDRESS			0x250
#define CS_3_LOW_DECODE_ADDRESS			0x038
#define CS_3_HIGH_DECODE_ADDRESS			0x040
#define BOOTCS_LOW_DECODE_ADDRESS			0x238
#define BOOTCS_HIGH_DECODE_ADDRESS			0x240

/* Make it fit the MV64360 and MV64460 Lowlevel driver */
/* Devices BAR and size registers */

#define DEV_CS0_BASE_ADDR	CS_0_LOW_DECODE_ADDRESS
#define DEV_CS0_SIZE			CS_0_HIGH_DECODE_ADDRESS
#define DEV_CS1_BASE_ADDR	CS_1_LOW_DECODE_ADDRESS
#define DEV_CS1_SIZE		CS_1_HIGH_DECODE_ADDRESS
#define DEV_CS2_BASE_ADDR	CS_2_LOW_DECODE_ADDRESS
#define DEV_CS2_SIZE			CS_2_HIGH_DECODE_ADDRESS
#define DEV_CS3_BASE_ADDR		CS_3_LOW_DECODE_ADDRESS
#define DEV_CS3_SIZE		CS_3_HIGH_DECODE_ADDRESS
#define BOOTCS_BASE_ADDR	BOOTCS_LOW_DECODE_ADDRESS
#define BOOTCS_SIZE		BOOTCS_HIGH_DECODE_ADDRESS

/* PCI 0 BAR and size registers	 old names of evb64260*/

#define PCI_0I_O_LOW_DECODE_ADDRESS			0x048
#define PCI_0I_O_HIGH_DECODE_ADDRESS			0x050
#define PCI_0MEMORY0_LOW_DECODE_ADDRESS		0x058
#define PCI_0MEMORY0_HIGH_DECODE_ADDRESS		0x060
#define PCI_0MEMORY1_LOW_DECODE_ADDRESS		0x080
#define PCI_0MEMORY1_HIGH_DECODE_ADDRESS		0x088
#define PCI_0MEMORY2_LOW_DECODE_ADDRESS		0x258
#define PCI_0MEMORY2_HIGH_DECODE_ADDRESS		0x260
#define PCI_0MEMORY3_LOW_DECODE_ADDRESS		0x280
#define PCI_0MEMORY3_HIGH_DECODE_ADDRESS		0x288

/* Make it fit the MV64360 and MV64460 Lowlevel driver */
#define PCI_0_IO_BASE_ADDR						0x048
#define PCI_0_IO_SIZE							0x050
#define PCI_0_MEMORY0_BASE_ADDR					0x058
#define PCI_0_MEMORY0_SIZE						0x060
#define PCI_0_MEMORY1_BASE_ADDR					0x080
#define PCI_0_MEMORY1_SIZE						0x088
#define PCI_0_MEMORY2_BASE_ADDR					0x258
#define PCI_0_MEMORY2_SIZE						0x260
#define PCI_0_MEMORY3_BASE_ADDR					0x280
#define PCI_0_MEMORY3_SIZE						0x288

/* PCI 1 BAR and size registers	 old names of evb64260*/
#define PCI_1I_O_LOW_DECODE_ADDRESS			0x090
#define PCI_1I_O_HIGH_DECODE_ADDRESS			0x098
#define PCI_1MEMORY0_LOW_DECODE_ADDRESS		0x0a0
#define PCI_1MEMORY0_HIGH_DECODE_ADDRESS		0x0a8
#define PCI_1MEMORY1_LOW_DECODE_ADDRESS		0x0b0
#define PCI_1MEMORY1_HIGH_DECODE_ADDRESS		0x0b8
#define PCI_1MEMORY2_LOW_DECODE_ADDRESS		0x2a0
#define PCI_1MEMORY2_HIGH_DECODE_ADDRESS		0x2a8
#define PCI_1MEMORY3_LOW_DECODE_ADDRESS		0x2b0
#define PCI_1MEMORY3_HIGH_DECODE_ADDRESS		0x2b8

/* Make it fit the MV64360 and MV64460 Lowlevel driver */
#define PCI_1_IO_BASE_ADDR						0x090
#define PCI_1_IO_SIZE							0x098
#define PCI_1_MEMORY0_BASE_ADDR					0x0a0
#define PCI_1_MEMORY0_SIZE						0x0a8
#define PCI_1_MEMORY1_BASE_ADDR					0x0b0
#define PCI_1_MEMORY1_SIZE						0x0b8
#define PCI_1_MEMORY2_BASE_ADDR					0x2a0
#define PCI_1_MEMORY2_SIZE						0x2a8
#define PCI_1_MEMORY3_BASE_ADDR					0x2b0
#define PCI_1_MEMORY3_SIZE						0x2b8

/* internal registers space base address */
#define INTERNAL_SPACE_DECODE				0x068
#define INTERNAL_SPACE_BASE_ADDR				INTERNAL_SPACE_DECODE

/* SRAM base address */
#define INTEGRATED_SRAM_BASE_ADDR				0x268

/* Enables the CS , DEV_CS , PCI 0 and PCI 1
   windows above */
#define BASE_ADDR_ENABLE						0x278


#define CPU_0_LOW_DECODE_ADDRESS				0x290
#define CPU_0_HIGH_DECODE_ADDRESS				0x298
#define CPU_1_LOW_DECODE_ADDRESS				0x2c0
#define CPU_1_HIGH_DECODE_ADDRESS				0x2c8

/****************************************/
/* PCI remap registers			*/
/****************************************/
/*****************************************************************************************/
      /* PCI 0 */
/* old fashion evb 64260 */
#define PCI_0I_O_ADDRESS_REMAP				0x0f0
#define PCI_0MEMORY0_ADDRESS_REMAP			0x0f8
#define PCI_0MEMORY0_HIGH_ADDRESS_REMAP		0x320
#define PCI_0MEMORY1_ADDRESS_REMAP			0x100
#define PCI_0MEMORY1_HIGH_ADDRESS_REMAP		0x328
#define PCI_0MEMORY2_ADDRESS_REMAP			0x2f8
#define PCI_0MEMORY2_HIGH_ADDRESS_REMAP		0x330
#define PCI_0MEMORY3_ADDRESS_REMAP			0x300
#define PCI_0MEMORY3_HIGH_ADDRESS_REMAP		0x338

#define PCI_0_IO_ADDR_REMAP						PCI_0I_O_ADDRESS_REMAP
#define PCI_0_MEMORY0_LOW_ADDR_REMAP				PCI_0MEMORY0_ADDRESS_REMAP
#define PCI_0_MEMORY0_HIGH_ADDR_REMAP				PCI_0MEMORY0_HIGH_ADDRESS_REMAP
#define PCI_0_MEMORY1_LOW_ADDR_REMAP				PCI_0MEMORY1_ADDRESS_REMAP
#define PCI_0_MEMORY1_HIGH_ADDR_REMAP				PCI_0MEMORY1_HIGH_ADDRESS_REMAP
#define PCI_0_MEMORY2_LOW_ADDR_REMAP				PCI_0MEMORY2_ADDRESS_REMAP
#define PCI_0_MEMORY2_HIGH_ADDR_REMAP				PCI_0MEMORY2_HIGH_ADDRESS_REMAP
#define PCI_0_MEMORY3_LOW_ADDR_REMAP				PCI_0MEMORY3_ADDRESS_REMAP
#define PCI_0_MEMORY3_HIGH_ADDR_REMAP				PCI_0MEMORY3_HIGH_ADDRESS_REMAP

       /* PCI 1 */
/* old fashion evb 64260 */
#define PCI_1I_O_ADDRESS_REMAP				0x108
#define PCI_1MEMORY0_ADDRESS_REMAP			0x110
#define PCI_1MEMORY0_HIGH_ADDRESS_REMAP		0x340
#define PCI_1MEMORY1_ADDRESS_REMAP			0x118
#define PCI_1MEMORY1_HIGH_ADDRESS_REMAP		0x348
#define PCI_1MEMORY2_ADDRESS_REMAP			0x310
#define PCI_1MEMORY2_HIGH_ADDRESS_REMAP		0x350
#define PCI_1MEMORY3_ADDRESS_REMAP			0x318
#define PCI_1MEMORY3_HIGH_ADDRESS_REMAP		0x358

#define PCI_1_IO_ADDR_REMAP						PCI_1I_O_ADDRESS_REMAP
#define PCI_1_MEMORY0_LOW_ADDR_REMAP				PCI_1MEMORY0_ADDRESS_REMAP
#define PCI_1_MEMORY0_HIGH_ADDR_REMAP				PCI_1MEMORY0_HIGH_ADDRESS_REMAP
#define PCI_1_MEMORY1_LOW_ADDR_REMAP				PCI_1MEMORY1_ADDRESS_REMAP
#define PCI_1_MEMORY1_HIGH_ADDR_REMAP				PCI_1MEMORY1_HIGH_ADDRESS_REMAP
#define PCI_1_MEMORY2_LOW_ADDR_REMAP				PCI_1MEMORY2_ADDRESS_REMAP
#define PCI_1_MEMORY2_HIGH_ADDR_REMAP				PCI_1MEMORY2_HIGH_ADDRESS_REMAP
#define PCI_1_MEMORY3_LOW_ADDR_REMAP				PCI_1MEMORY3_ADDRESS_REMAP
#define PCI_1_MEMORY3_HIGH_ADDR_REMAP				PCI_1MEMORY3_HIGH_ADDRESS_REMAP

/* old fashion evb 64260 */
#define CPU_PCI_0_HEADERS_RETARGET_CONTROL			0x3b0
#define CPU_PCI_0_HEADERS_RETARGET_BASE				0x3b8
#define CPU_PCI_1_HEADERS_RETARGET_CONTROL			0x3c0
#define CPU_PCI_1_HEADERS_RETARGET_BASE				0x3c8
#define CPU_GE_HEADERS_RETARGET_CONTROL				0x3d0
#define CPU_GE_HEADERS_RETARGET_BASE				0x3d8

/* MV64360 and MV64460 no changes needed*/
/*****************************************************************************************/

/****************************************/
/*	   CPU Control Registers	*/
/****************************************/
/* CPU MASTER CONTROL REGISTER */
#define CPU_CONFIGURATION				0x000
#define CPU_MASTER_CONTROL				0x160

#define CPU_CONFIG							0x000
#define CPU_MODE							0x120
#define CPU_MASTER_CONTROL						0x160
/* new in MV64360 and MV64460 */
#define CPU_CROSS_BAR_CONTROL_LOW				0x150
#define CPU_CROSS_BAR_CONTROL_HIGH				0x158
#define CPU_CROSS_BAR_TIMEOUT					0x168

/****************************************/
/* SMP RegisterS			*/
/****************************************/

#define SMP_WHO_AM_I							0x200
#define SMP_CPU0_DOORBELL						0x214
#define SMP_CPU0_DOORBELL_CLEAR					0x21C
#define SMP_CPU1_DOORBELL						0x224
#define SMP_CPU1_DOORBELL_CLEAR					0x22C
#define SMP_CPU0_DOORBELL_MASK					0x234
#define SMP_CPU1_DOORBELL_MASK					0x23C
#define SMP_SEMAPHOR0							0x244
#define SMP_SEMAPHOR1							0x24c
#define SMP_SEMAPHOR2							0x254
#define SMP_SEMAPHOR3							0x25c
#define SMP_SEMAPHOR4							0x264
#define SMP_SEMAPHOR5							0x26c
#define SMP_SEMAPHOR6							0x274
#define SMP_SEMAPHOR7							0x27c


/****************************************/
/* CPU Sync Barrier				*/
/****************************************/
#define CPU_0_SYNC_BARRIER_TRIGGER				0x0c0
#define CPU_0_SYNC_BARRIER_VIRTUAL				0x0c8
#define CPU_1_SYNC_BARRIER_TRIGGER				0x0d0
#define CPU_1_SYNC_BARRIER_VIRTUAL				0x0d8


/****************************************/
/* CPU Access Protect			*/
/****************************************/

#define CPU_LOW_PROTECT_ADDRESS_0			    0x180
#define CPU_HIGH_PROTECT_ADDRESS_0			    0x188
#define CPU_LOW_PROTECT_ADDRESS_1			    0x190
#define CPU_HIGH_PROTECT_ADDRESS_1			    0x198
#define CPU_LOW_PROTECT_ADDRESS_2			    0x1a0
#define CPU_HIGH_PROTECT_ADDRESS_2			    0x1a8
#define CPU_LOW_PROTECT_ADDRESS_3			    0x1b0
#define CPU_HIGH_PROTECT_ADDRESS_3			    0x1b8
/*#define CPU_LOW_PROTECT_ADDRESS_4			      0x1c0
#define CPU_HIGH_PROTECT_ADDRESS_4			    0x1c8
#define CPU_LOW_PROTECT_ADDRESS_5			    0x1d0
#define CPU_HIGH_PROTECT_ADDRESS_5			    0x1d8
#define CPU_LOW_PROTECT_ADDRESS_6			    0x1e0
#define CPU_HIGH_PROTECT_ADDRESS_6			    0x1e8
#define CPU_LOW_PROTECT_ADDRESS_7			    0x1f0
#define CPU_HIGH_PROTECT_ADDRESS_7			    0x1f8
*/

#define CPU_PROTECT_WINDOW_0_BASE_ADDR		     CPU_LOW_PROTECT_ADDRESS_0 /* 0x180 */
#define CPU_PROTECT_WINDOW_0_SIZE			    CPU_HIGH_PROTECT_ADDRESS_0 /* 0x188 */
#define CPU_PROTECT_WINDOW_1_BASE_ADDR		     CPU_LOW_PROTECT_ADDRESS_1 /* 0x190 */
#define CPU_PROTECT_WINDOW_1_SIZE			    CPU_HIGH_PROTECT_ADDRESS_1 /* 0x198 */
#define CPU_PROTECT_WINDOW_2_BASE_ADDR		     CPU_LOW_PROTECT_ADDRESS_2 /*0x1a0 */
#define CPU_PROTECT_WINDOW_2_SIZE			    CPU_HIGH_PROTECT_ADDRESS_2 /* 0x1a8 */
#define CPU_PROTECT_WINDOW_3_BASE_ADDR		     CPU_LOW_PROTECT_ADDRESS_3 /* 0x1b0 */
#define CPU_PROTECT_WINDOW_3_SIZE			    CPU_HIGH_PROTECT_ADDRESS_3 /* 0x1b8 */


/****************************************/
/*	    Snoop Control			*/
/****************************************/

/*#define SNOOP_BASE_ADDRESS_0				      0x380
#define SNOOP_TOP_ADDRESS_0				    0x388
#define SNOOP_BASE_ADDRESS_1				    0x390
#define SNOOP_TOP_ADDRESS_1				    0x398
#define SNOOP_BASE_ADDRESS_2				    0x3a0
#define SNOOP_TOP_ADDRESS_2				    0x3a8
#define SNOOP_BASE_ADDRESS_3				    0x3b0
#define SNOOP_TOP_ADDRESS_3				    0x3b8
*/

/****************************************/
/*  Integrated SRAM Registers		*/
/****************************************/

#define SRAM_CONFIG						0x380
#define SRAM_TEST_MODE						0x3F4
#define SRAM_ERROR_CAUSE					0x388
#define SRAM_ERROR_ADDR						0x390
#define SRAM_ERROR_ADDR_HIGH					0x3F8
#define SRAM_ERROR_DATA_LOW					0x398
#define SRAM_ERROR_DATA_HIGH					0x3a0
#define SRAM_ERROR_DATA_PARITY					0x3a8

/****************************************/
/*	    CPU Error Report			*/
/****************************************/

#define CPU_ERROR_ADDRESS_LOW		0x070
#define CPU_ERROR_ADDRESS_HIGH		0x078
#define CPU_ERROR_DATA_LOW					0x128
#define CPU_ERROR_DATA_HIGH					0x130
#define CPU_ERROR_PARITY					0x138
#define CPU_ERROR_CAUSE						0x140
#define CPU_ERROR_MASK						0x148

#define CPU_ERROR_ADDR_LOW					CPU_ERROR_ADDRESS_LOW  /* 0x0701 */
#define CPU_ERROR_ADDR_HIGH					CPU_ERROR_ADDRESS_HIGH	/* 0x0781 */

/****************************************/
/*	    Pslave Debug			*/
/*	CPU Interface Debug Registers	*/
/****************************************/

#define X_0_ADDRESS						0x360
#define X_0_COMMAND_ID						0x368
#define X_1_ADDRESS						0x370
#define X_1_COMMAND_ID						0x378
 /*#define WRITE_DATA_LOW					0x3c01 */
 /*#define WRITE_DATA_HIGH					0x3c81 */
 /*#define WRITE_BYTE_ENABLE					0x3e01 */
 /*#define READ_DATA_LOW					0x3d01 */
 /*#define READ_DATA_HIGH					0x3d81 */
 /*#define READ_ID						0x3e81 */

#define PUNIT_SLAVE_DEBUG_LOW					X_0_ADDRESS  /* 0x3601 */
#define PUNIT_SLAVE_DEBUG_HIGH					X_0_COMMAND_ID	/* 0x3681 */
#define PUNIT_MASTER_DEBUG_LOW					X_1_ADDRESS  /* 0x3701 */
#define PUNIT_MASTER_DEBUG_HIGH				   X_1_COMMAND_ID  /* 0x3781 */
#define PUNIT_MMASK						0x3e4


/****************************************/
/* SDRAM and Device Address Space		*/
/****************************************/

/****************************************/
/* SDRAM Configuration			*/
/****************************************/
#define SDRAM_CONFIG						0x1400	/* MV64260 0x448 some changes*/
#define D_UNIT_CONTROL_LOW					0x1404	/* NEW in MV64360 and MV64460 */
#define D_UNIT_CONTROL_HIGH					0x1424	/* NEW in MV64360 and MV64460 */
#define SDRAM_TIMING_CONTROL_LOW			0x1408	/* MV64260 0x4b4 new SDRAM TIMING REGISTER */
#define SDRAM_TIMING_CONTROL_HIGH			0x140c	/* MV64260 0x4b4 new SDRAM TIMING REGISTER */
#define SDRAM_ADDR_CONTROL				    0x1410	/* MV64260 0x47c some changes*/
#define SDRAM_OPEN_PAGES_CONTROL			0x1414	/* NEW in MV64360 and MV64460 */
#define SDRAM_OPERATION						0x1418	/* MV64260 0x474 some changes*/
#define SDRAM_MODE						0x141c	/* NEW in MV64360 and MV64460 */
#define EXTENDED_DRAM_MODE					0x1420	/* NEW in MV64360 and MV64460 */
#define SDRAM_CROSS_BAR_CONTROL_LOW			0x1430	/* MV64260 0x4a8 NO changes*/
#define SDRAM_CROSS_BAR_CONTROL_HIGH			0x1434	/* MV64260 0x4ac NO changes*/
#define SDRAM_CROSS_BAR_TIMEOUT				0x1438	/* MV64260 0x4b0 NO changes*/
#define SDRAM_ADDR_CTRL_PADS_CALIBRATION	0x14c0	/* what is this ??? */
#define SDRAM_DATA_PADS_CALIBRATION			0x14c4	/* what is this ??? */
/****************************************/
/* SDRAM Configuration MV64260			*/
/****************************************/
 /*#define SDRAM_CONFIGURATION			0x4481 */
 /*#define SDRAM_OPERATION_MODE			0x4741 */
 /*#define SDRAM_ADDRESS_DECODE		0x47c1 */
 /*#define SDRAM_UMA_CONTROL			0x4a4	eliminated in MV64360 and MV64460 */
 /*#define SDRAM_CROSS_BAR_CONTROL_LOW	0x4a81 */
 /*#define SDRAM_CROSS_BAR_CONTROL_HIGH 0x4ac1 */
 /*#define SDRAM_CROSS_BAR_TIMEOUT		0x4b01 */
 /*#define SDRAM_TIMING				0x4b41 */


/****************************************/
/* SDRAM Error Report			*/
/****************************************/
#define SDRAM_ERROR_DATA_LOW				0x1444	/* MV64260 0x484 NO changes*/
#define SDRAM_ERROR_DATA_HIGH					0x1440	/* MV64260 0x480 NO changes*/
#define SDRAM_ERROR_ADDR					0x1450	/* MV64260 0x490 NO changes*/
#define SDRAM_RECEIVED_ECC					0x1448	/* MV64260 0x488 NO changes*/
#define SDRAM_CALCULATED_ECC					0x144c	/* MV64260 0x48c NO changes*/
#define SDRAM_ECC_CONTROL					0x1454	/* MV64260 0x494 NO changes*/
#define SDRAM_ECC_ERROR_COUNTER				0x1458	/* MV64260 0x498 NO changes*/
#define SDRAM_MMASK					0x1B40	/* NEW Register in MV64360 and MV64460 DO NOT USE !!!*/
/****************************************/
/* SDRAM Error Report MV64260			*/
/****************************************/
 /*#define SDRAM_ERROR_DATA_LOW					0x4841 */
 /*#define SDRAM_ERROR_DATA_HIGH				0x4801 */
 /*#define SDRAM_AND_DEVICE_ERROR_ADDRESS		0x4901 */
 /*#define SDRAM_RECEIVED_ECC				       0x4881 */
 /*#define SDRAM_CALCULATED_ECC					0x48c1 */
 /*#define SDRAM_ECC_CONTROL					0x4941 */
 /*#define SDRAM_ECC_ERROR_COUNTER			0x4981 */

/******************************************/
/*  Controlled Delay Line (CDL) Registers */
/******************************************/
#define DFCDL_CONFIG0						0x1480
#define DFCDL_CONFIG1						0x1484
#define DLL_WRITE						0x1488
#define DLL_READ						0x148c
#define SRAM_ADDR						0x1490
#define SRAM_DATA0						0x1494
#define SRAM_DATA1						0x1498
#define SRAM_DATA2						0x149c
#define DFCL_PROBE						0x14a0


/****************************************/
/* SDRAM Parameters only in MV64260			*/
/****************************************/

 /*#define SDRAM_BANK0PARAMETERS				0x44C	eliminated in MV64360 and MV64460 */
 /*#define SDRAM_BANK1PARAMETERS				0x450	eliminated in MV64360 and MV64460 */
 /*#define SDRAM_BANK2PARAMETERS				0x454	eliminated in MV64360 and MV64460 */
 /*#define SDRAM_BANK3PARAMETERS				0x458	eliminated in MV64360 and MV64460 */

/******************************************/
/*   Debug Registers			  */
/******************************************/

#define DUNIT_DEBUG_LOW						0x1460
#define DUNIT_DEBUG_HIGH					0x1464
#define DUNIT_MMASK						0x1b40

/****************************************/
/* SDunit Debug (for internal use)	*/
/****************************************/

#define X0_ADDRESS					    0x500
#define X0_COMMAND_AND_ID				    0x504
#define X0_WRITE_DATA_LOW				    0x508
#define X0_WRITE_DATA_HIGH				    0x50c
#define X0_WRITE_BYTE_ENABLE				    0x518
#define X0_READ_DATA_LOW				    0x510
#define X0_READ_DATA_HIGH				    0x514
#define X0_READ_ID					    0x51c
#define X1_ADDRESS					    0x520
#define X1_COMMAND_AND_ID				    0x524
#define X1_WRITE_DATA_LOW				    0x528
#define X1_WRITE_DATA_HIGH				    0x52c
#define X1_WRITE_BYTE_ENABLE				    0x538
#define X1_READ_DATA_LOW				    0x530
#define X1_READ_DATA_HIGH				    0x534
#define X1_READ_ID					    0x53c
#define X0_SNOOP_ADDRESS				    0x540
#define X0_SNOOP_COMMAND				    0x544
#define X1_SNOOP_ADDRESS				    0x548
#define X1_SNOOP_COMMAND				    0x54c

/****************************************/
/* Device Parameters					*/
/****************************************/

#define DEVICE_BANK0PARAMETERS				0x45c
#define DEVICE_BANK1PARAMETERS				0x460
#define DEVICE_BANK2PARAMETERS				0x464
#define DEVICE_BANK3PARAMETERS				0x468
#define DEVICE_BOOT_BANK_PARAMETERS			0x46c
#define DEVICE_CONTROL							0x4c0
#define DEVICE_CROSS_BAR_CONTROL_LOW				0x4c8
#define DEVICE_CROSS_BAR_CONTROL_HIGH				0x4cc
#define DEVICE_CROSS_BAR_TIMEOUT				0x4c4

/****************************************/
/* Device Parameters					*/
/****************************************/

#define DEVICE_BANK0_PARAMETERS			DEVICE_BANK0PARAMETERS	/* 0x45c1 */
#define DEVICE_BANK1_PARAMETERS			DEVICE_BANK1PARAMETERS	/* 0x4601 */
#define DEVICE_BANK2_PARAMETERS			DEVICE_BANK2PARAMETERS	/* 0x4641 */
#define DEVICE_BANK3_PARAMETERS			DEVICE_BANK3PARAMETERS	/* 0x4681 */
/*#define DEVICE_BOOT_BANK_PARAMETERS			 0x46c1 */
#define DEVICE_INTERFACE_CONTROL				DEVICE_CONTROL	/* 0x4c01 */
#define DEVICE_INTERFACE_CROSS_BAR_CONTROL_LOW		DEVICE_CROSS_BAR_CONTROL_LOW  /* 0x4c81 */
#define DEVICE_INTERFACE_CROSS_BAR_CONTROL_HIGH		DEVICE_CROSS_BAR_CONTROL_HIGH  /* 0x4cc1 */
#define DEVICE_INTERFACE_CROSS_BAR_TIMEOUT			DEVICE_CROSS_BAR_TIMEOUT  /* 0x4c41 */


/****************************************/
/* Device Interrupt					*/
/****************************************/

#define DEVICE_INTERRUPT_CAUSE						0x4d0
#define DEVICE_INTERRUPT_MASK						0x4d4
#define DEVICE_ERROR_ADDRESS						0x4d8
 /*#define DEVICE_INTERRUPT_CAUSE				0x4d01 */
 /*#define DEVICE_INTERRUPT_MASK				0x4d41 */
#define DEVICE_ERROR_ADDR				DEVICE_ERROR_ADDRESS  /*0x4d81 */
#define DEVICE_ERROR_DATA				0x4dc
#define DEVICE_ERROR_PARITY					0x4e0

/****************************************/
/* Device debug registers			*/
/****************************************/

#define DEVICE_DEBUG_LOW					0x4e4
#define DEVICE_DEBUG_HIGH				0x4e8
#define RUNIT_MMASK							0x4f0

/****************************************/
/* DMA Record							*/
/****************************************/

 /*#define CHANNEL4_DMA_BYTE_COUNT			0x9001 */
 /*#define CHANNEL5_DMA_BYTE_COUNT			0x9041 */
 /*#define CHANNEL6_DMA_BYTE_COUNT			0x9081 */
 /*#define CHANNEL7_DMA_BYTE_COUNT			0x90C1 */
 /*#define CHANNEL4_DMA_SOURCE_ADDRESS		0x9101 */
 /*#define CHANNEL5_DMA_SOURCE_ADDRESS		0x9141 */
 /*#define CHANNEL6_DMA_SOURCE_ADDRESS		0x9181 */
 /*#define CHANNEL7_DMA_SOURCE_ADDRESS		0x91C1 */
 /*#define CHANNEL4_DMA_DESTINATION_ADDRESS		0x9201 */
 /*#define CHANNEL5_DMA_DESTINATION_ADDRESS		0x9241 */
 /*#define CHANNEL6_DMA_DESTINATION_ADDRESS		0x9281 */
 /*#define CHANNEL7_DMA_DESTINATION_ADDRESS		0x92C1 */
 /*#define CHANNEL4NEXT_RECORD_POINTER			0x9301 */
 /*#define CHANNEL5NEXT_RECORD_POINTER			0x9341 */
 /*#define CHANNEL6NEXT_RECORD_POINTER			0x9381 */
 /*#define CHANNEL7NEXT_RECORD_POINTER			0x93C1 */
 /*#define CHANNEL4CURRENT_DESCRIPTOR_POINTER		0x9701 */
 /*#define CHANNEL5CURRENT_DESCRIPTOR_POINTER		0x9741 */
 /*#define CHANNEL6CURRENT_DESCRIPTOR_POINTER		0x9781 */
 /*#define CHANNEL7CURRENT_DESCRIPTOR_POINTER		0x97C1 */
 /*#define CHANNEL0_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x8901 */
 /*#define CHANNEL1_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x8941 */
 /*#define CHANNEL2_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x8981 */
 /*#define CHANNEL3_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x89c1 */
 /*#define CHANNEL4_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x9901 */
 /*#define CHANNEL5_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x9941 */
 /*#define CHANNEL6_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x9981 */
 /*#define CHANNEL7_DMA_SOURCE_HIGH_PCI_ADDRESS		       0x99c1 */
 /*#define CHANNEL0_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x8a01 */
 /*#define CHANNEL1_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x8a41 */
 /*#define CHANNEL2_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x8a81 */
 /*#define CHANNEL3_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x8ac1 */
 /*#define CHANNEL4_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x9a01 */
 /*#define CHANNEL5_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x9a41 */
 /*#define CHANNEL6_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x9a81 */
 /*#define CHANNEL7_DMA_DESTINATION_HIGH_PCI_ADDRESS	       0x9ac1 */
 /*#define CHANNEL0_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x8b01 */
 /*#define CHANNEL1_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x8b41 */
 /*#define CHANNEL2_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x8b81 */
 /*#define CHANNEL3_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x8bc1 */
 /*#define CHANNEL4_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x9b01 */
 /*#define CHANNEL5_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x9b41 */
 /*#define CHANNEL6_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x9b81 */
 /*#define CHANNEL7_DMA_NEXT_RECORD_POINTER_HIGH_PCI_ADDRESS   0x9bc1 */

/****************************************/
/* DMA Channel Control					*/
/****************************************/

#define CHANNEL0CONTROL					0x840
#define CHANNEL0CONTROL_HIGH				0x880
#define CHANNEL1CONTROL					0x844
#define CHANNEL1CONTROL_HIGH				0x884
#define CHANNEL2CONTROL					0x848
#define CHANNEL2CONTROL_HIGH				0x888
#define CHANNEL3CONTROL					0x84C
#define CHANNEL3CONTROL_HIGH				0x88C

#define DMA_CHANNEL0_CONTROL				CHANNEL0CONTROL	 /*0x8401 */
#define DMA_CHANNEL0_CONTROL_HIGH			CHANNEL0CONTROL_HIGH  /*0x8801 */
#define DMA_CHANNEL1_CONTROL				CHANNEL1CONTROL	 /* 0x8441 */
#define DMA_CHANNEL1_CONTROL_HIGH			CHANNEL1CONTROL_HIGH  /*0x8841 */
#define DMA_CHANNEL2_CONTROL				CHANNEL2CONTROL	 /*0x8481 */
#define DMA_CHANNEL2_CONTROL_HIGH			CHANNEL2CONTROL_HIGH  /*0x8881 */
#define DMA_CHANNEL3_CONTROL				CHANNEL3CONTROL	 /*0x84C1 */
#define DMA_CHANNEL3_CONTROL_HIGH			CHANNEL3CONTROL_HIGH  /*0x88C1 */

 /*#define CHANNEL4CONTROL				0x9401 */
 /*#define CHANNEL4CONTROL_HIGH				0x9801 */
 /*#define CHANNEL5CONTROL				0x9441 */
 /*#define CHANNEL5CONTROL_HIGH				0x9841 */
 /*#define CHANNEL6CONTROL				0x9481 */
 /*#define CHANNEL6CONTROL_HIGH				0x9881 */
 /*#define CHANNEL7CONTROL				0x94C1 */
 /*#define CHANNEL7CONTROL_HIGH				0x98C1 */


/****************************************/
/* DMA Arbiter							*/
/****************************************/

 /*#define ARBITER_CONTROL_0_3				0x8601 */
#define ARBITER_CONTROL_4_7				0x960
/****************************************/
/*	     IDMA Registers		*/
/****************************************/

#define DMA_CHANNEL0_BYTE_COUNT					CHANNEL0_DMA_BYTE_COUNT	 /*0x8001 */
#define DMA_CHANNEL1_BYTE_COUNT					CHANNEL1_DMA_BYTE_COUNT	 /*0x8041 */
#define DMA_CHANNEL2_BYTE_COUNT					CHANNEL2_DMA_BYTE_COUNT	 /*0x8081 */
#define DMA_CHANNEL3_BYTE_COUNT					CHANNEL3_DMA_BYTE_COUNT	 /*0x80C1 */
#define DMA_CHANNEL0_SOURCE_ADDR				CHANNEL0_DMA_SOURCE_ADDRESS  /*0x8101 */
#define DMA_CHANNEL1_SOURCE_ADDR				CHANNEL1_DMA_SOURCE_ADDRESS  /*0x8141 */
#define DMA_CHANNEL2_SOURCE_ADDR				CHANNEL2_DMA_SOURCE_ADDRESS  /*0x8181 */
#define DMA_CHANNEL3_SOURCE_ADDR				CHANNEL3_DMA_SOURCE_ADDRESS  /*0x81c1 */
#define DMA_CHANNEL0_DESTINATION_ADDR				CHANNEL0_DMA_DESTINATION_ADDRESS  /*0x8201 */
#define DMA_CHANNEL1_DESTINATION_ADDR				CHANNEL1_DMA_DESTINATION_ADDRESS  /*0x8241 */
#define DMA_CHANNEL2_DESTINATION_ADDR				CHANNEL2_DMA_DESTINATION_ADDRESS  /*0x8281 */
#define DMA_CHANNEL3_DESTINATION_ADDR				CHANNEL3_DMA_DESTINATION_ADDRESS  /*0x82C1 */
#define DMA_CHANNEL0_NEXT_DESCRIPTOR_POINTER		CHANNEL0NEXT_RECORD_POINTER  /*0x8301 */
#define DMA_CHANNEL1_NEXT_DESCRIPTOR_POINTER		CHANNEL1NEXT_RECORD_POINTER  /*0x8341 */
#define DMA_CHANNEL2_NEXT_DESCRIPTOR_POINTER		CHANNEL2NEXT_RECORD_POINTER  /*0x8381 */
#define DMA_CHANNEL3_NEXT_DESCRIPTOR_POINTER		CHANNEL3NEXT_RECORD_POINTER  /*0x83C1 */
#define DMA_CHANNEL0_CURRENT_DESCRIPTOR_POINTER		CHANNEL0CURRENT_DESCRIPTOR_POINTER  /*0x8701 */
#define DMA_CHANNEL1_CURRENT_DESCRIPTOR_POINTER		CHANNEL1CURRENT_DESCRIPTOR_POINTER  /*0x8741 */
#define DMA_CHANNEL2_CURRENT_DESCRIPTOR_POINTER		CHANNEL2CURRENT_DESCRIPTOR_POINTER  /*0x8781 */
#define DMA_CHANNEL3_CURRENT_DESCRIPTOR_POINTER		CHANNEL3CURRENT_DESCRIPTOR_POINTER  /*0x87C1 */

#define CHANNEL3CURRENT_DESCRIPTOR_POINTER		0x87C
#define CHANNEL2CURRENT_DESCRIPTOR_POINTER		0x878
#define CHANNEL1CURRENT_DESCRIPTOR_POINTER		0x874
#define CHANNEL0CURRENT_DESCRIPTOR_POINTER		0x870
#define CHANNEL0NEXT_RECORD_POINTER			0x830
#define CHANNEL1NEXT_RECORD_POINTER			0x834
#define CHANNEL2NEXT_RECORD_POINTER			0x838
#define CHANNEL3NEXT_RECORD_POINTER			0x83C
#define CHANNEL0_DMA_DESTINATION_ADDRESS		0x820
#define CHANNEL1_DMA_DESTINATION_ADDRESS		0x824
#define CHANNEL2_DMA_DESTINATION_ADDRESS		0x828
#define CHANNEL3_DMA_DESTINATION_ADDRESS		0x82C
#define CHANNEL0_DMA_SOURCE_ADDRESS			0x810
#define CHANNEL1_DMA_SOURCE_ADDRESS			0x814
#define CHANNEL2_DMA_SOURCE_ADDRESS			0x818
#define CHANNEL3_DMA_SOURCE_ADDRESS			0x81C
#define CHANNEL0_DMA_BYTE_COUNT			0x800
#define CHANNEL1_DMA_BYTE_COUNT			0x804
#define CHANNEL2_DMA_BYTE_COUNT			0x808
#define CHANNEL3_DMA_BYTE_COUNT			0x80C

 /*  IDMA Address Decoding Base Address Registers  */

#define DMA_BASE_ADDR_REG0						0xa00
#define DMA_BASE_ADDR_REG1						0xa08
#define DMA_BASE_ADDR_REG2						0xa10
#define DMA_BASE_ADDR_REG3						0xa18
#define DMA_BASE_ADDR_REG4						0xa20
#define DMA_BASE_ADDR_REG5						0xa28
#define DMA_BASE_ADDR_REG6						0xa30
#define DMA_BASE_ADDR_REG7						0xa38

 /*  IDMA Address Decoding Size Address Register   */

#define DMA_SIZE_REG0							0xa04
#define DMA_SIZE_REG1							0xa0c
#define DMA_SIZE_REG2							0xa14
#define DMA_SIZE_REG3							0xa1c
#define DMA_SIZE_REG4							0xa24
#define DMA_SIZE_REG5							0xa2c
#define DMA_SIZE_REG6							0xa34
#define DMA_SIZE_REG7							0xa3C

    /* IDMA Address Decoding High Address Remap and Access
		  Protection Registers			  */

#define DMA_HIGH_ADDR_REMAP_REG0				0xa60
#define DMA_HIGH_ADDR_REMAP_REG1				0xa64
#define DMA_HIGH_ADDR_REMAP_REG2				0xa68
#define DMA_HIGH_ADDR_REMAP_REG3				0xa6C
#define DMA_BASE_ADDR_ENABLE_REG				0xa80
#define DMA_CHANNEL0_ACCESS_PROTECTION_REG		0xa70
#define DMA_CHANNEL1_ACCESS_PROTECTION_REG		   0xa74
#define DMA_CHANNEL2_ACCESS_PROTECTION_REG		   0xa78
#define DMA_CHANNEL3_ACCESS_PROTECTION_REG		   0xa7c
#define DMA_ARBITER_CONTROL						0x860
#define DMA_CROSS_BAR_TIMEOUT					0x8d0

 /*  IDMA Headers Retarget Registers   */

 /*#define CPU_IDMA_HEADERS_RETARGET_CONTROL			0x3e01 */
 /*#define CPU_IDMA_HEADERS_RETARGET_BASE			 0x3e81 */

#define DMA_HEADERS_RETARGET_CONTROL			0xa84
#define DMA_HEADERS_RETARGET_BASE			0xa88

/****************************************/
/* DMA Interrupt						*/
/****************************************/

#define CHANELS0_3_INTERRUPT_CAUSE			0x8c0
#define CHANELS0_3_INTERRUPT_MASK			0x8c4
#define CHANELS0_3_ERROR_ADDRESS			0x8c8
#define CHANELS0_3_ERROR_SELECT				0x8cc
 /*#define CHANELS4_7_INTERRUPT_CAUSE			0x9c01 */
 /*#define CHANELS4_7_INTERRUPT_MASK			0x9c41 */
 /*#define CHANELS4_7_ERROR_ADDRESS			0x9c81 */
 /*#define CHANELS4_7_ERROR_SELECT			0x9cc1 */

#define DMA_INTERRUPT_CAUSE_REG				CHANELS0_3_INTERRUPT_CAUSE  /*0x8c01 */
#define DMA_INTERRUPT_CAUSE_MASK			CHANELS0_3_INTERRUPT_MASK  /*0x8c41 */
#define DMA_ERROR_ADDR						CHANELS0_3_ERROR_ADDRESS  /*0x8c81 */
#define DMA_ERROR_SELECT					CHANELS0_3_ERROR_SELECT	 /*0x8cc1 */


/****************************************/
/* DMA Debug (for internal use)		*/
/****************************************/

#define DMA_X0_ADDRESS						0x8e0
#define DMA_X0_COMMAND_AND_ID				0x8e4
 /*#define DMA_X0_WRITE_DATA_LOW				0x8e81 */
 /*#define DMA_X0_WRITE_DATA_HIGH				0x8ec1 */
 /*#define DMA_X0_WRITE_BYTE_ENABLE				0x8f81 */
 /*#define DMA_X0_READ_DATA_LOW					0x8f01 */
 /*#define DMA_X0_READ_DATA_HIGH				0x8f41 */
 /*#define DMA_X0_READ_ID					0x8fc1 */
 /*#define DMA_X1_ADDRESS					0x9e01 */
 /*#define DMA_X1_COMMAND_AND_ID			0x9e41 */
 /*#define DMA_X1_WRITE_DATA_LOW				0x9e81 */
 /*#define DMA_X1_WRITE_DATA_HIGH				0x9ec1 */
 /*#define DMA_X1_WRITE_BYTE_ENABLE				0x9f81 */
 /*#define DMA_X1_READ_DATA_LOW					0x9f01 */
 /*#define DMA_X1_READ_DATA_HIGH				0x9f41 */
 /*#define DMA_X1_READ_ID					0x9fc1 */

 /*  IDMA Debug Register ( for internal use )	 */

#define DMA_DEBUG_LOW						DMA_X0_ADDRESS	/* 0x8e01 */
#define DMA_DEBUG_HIGH						DMA_X0_COMMAND_AND_ID  /*0x8e41 */
#define DMA_SPARE						0xA8C


/****************************************/
/* Timer_Counter						*/
/****************************************/

#define TIMER_COUNTER0					0x850
#define TIMER_COUNTER1					0x854
#define TIMER_COUNTER2					0x858
#define TIMER_COUNTER3					0x85C
#define TIMER_COUNTER_0_3_CONTROL			0x864
#define TIMER_COUNTER_0_3_INTERRUPT_CAUSE		0x868
#define TIMER_COUNTER_0_3_INTERRUPT_MASK		0x86c
 /*#define TIMER_COUNTER4					0x9501 */
 /*#define TIMER_COUNTER5					0x9541 */
 /*#define TIMER_COUNTER6					0x9581 */
 /*#define TIMER_COUNTER7					0x95C1 */
 /*#define TIMER_COUNTER_4_7_CONTROL			0x9641 */
 /*#define TIMER_COUNTER_4_7_INTERRUPT_CAUSE		0x9681 */
 /*#define TIMER_COUNTER_4_7_INTERRUPT_MASK			0x96c1 */

/****************************************/
/* PCI Slave Address Decoding		*/
/****************************************/
/****************************************/
/* PCI Slave Address Decoding registers */
/****************************************/
#define PCI_0_CS_0_BANK_SIZE					PCI_0SCS_0_BANK_SIZE  /*0xc081 */
#define PCI_1_CS_0_BANK_SIZE					PCI_1SCS_0_BANK_SIZE  /* 0xc881 */
#define PCI_0_CS_1_BANK_SIZE					PCI_0SCS_1_BANK_SIZE  /*0xd081 */
#define PCI_1_CS_1_BANK_SIZE					PCI_1SCS_1_BANK_SIZE  /* 0xd881 */
#define PCI_0_CS_2_BANK_SIZE					PCI_0SCS_2_BANK_SIZE  /*0xc0c1 */
#define PCI_1_CS_2_BANK_SIZE					PCI_1SCS_2_BANK_SIZE  /*0xc8c1 */
#define PCI_0_CS_3_BANK_SIZE					PCI_0SCS_3_BANK_SIZE  /*0xd0c1 */
#define PCI_1_CS_3_BANK_SIZE					PCI_1SCS_3_BANK_SIZE  /*0xd8c1 */
#define PCI_0_DEVCS_0_BANK_SIZE					PCI_0CS_0_BANK_SIZE  /*0xc101 */
#define PCI_1_DEVCS_0_BANK_SIZE				    PCI_1CS_0_BANK_SIZE	 /*0xc901 */
#define PCI_0_DEVCS_1_BANK_SIZE				    PCI_0CS_1_BANK_SIZE	 /*0xd101 */
#define PCI_1_DEVCS_1_BANK_SIZE				    PCI_1CS_1_BANK_SIZE	 /* 0xd901 */
#define PCI_0_DEVCS_2_BANK_SIZE				    PCI_0CS_2_BANK_SIZE	 /* 0xd181 */
#define PCI_1_DEVCS_2_BANK_SIZE				    PCI_1CS_2_BANK_SIZE	 /*0xd981 */
#define PCI_0_DEVCS_3_BANK_SIZE				    PCI_0CS_3_BANK_SIZE	 /* 0xc141 */
#define PCI_1_DEVCS_3_BANK_SIZE				    PCI_1CS_3_BANK_SIZE	 /*0xc941 */
#define PCI_0_DEVCS_BOOT_BANK_SIZE			PCI_0CS_BOOT_BANK_SIZE	/*0xd141 */
#define PCI_1_DEVCS_BOOT_BANK_SIZE			PCI_1CS_BOOT_BANK_SIZE	/* 0xd941 */
#define PCI_0_P2P_MEM0_BAR_SIZE				    PCI_0P2P_MEM0_BAR_SIZE  /*0xd1c1 */
#define PCI_1_P2P_MEM0_BAR_SIZE				    PCI_1P2P_MEM0_BAR_SIZE  /*0xd9c1 */
#define PCI_0_P2P_MEM1_BAR_SIZE				    PCI_0P2P_MEM1_BAR_SIZE  /*0xd201 */
#define PCI_1_P2P_MEM1_BAR_SIZE				    PCI_1P2P_MEM1_BAR_SIZE  /*0xda01 */
#define PCI_0_P2P_I_O_BAR_SIZE					PCI_0P2P_I_O_BAR_SIZE  /*0xd241 */
#define PCI_1_P2P_I_O_BAR_SIZE					PCI_1P2P_I_O_BAR_SIZE  /*0xda41 */
#define PCI_0_CPU_BAR_SIZE					PCI_0CPU_BAR_SIZE  /*0xd281 */
#define PCI_1_CPU_BAR_SIZE					PCI_1CPU_BAR_SIZE  /*0xda81 */
#define PCI_0_INTERNAL_SRAM_BAR_SIZE			PCI_0DAC_SCS_0_BANK_SIZE  /*0xe001 */
#define PCI_1_INTERNAL_SRAM_BAR_SIZE			PCI_1DAC_SCS_0_BANK_SIZE  /*0xe801 */
#define PCI_0_EXPANSION_ROM_BAR_SIZE			PCI_0EXPANSION_ROM_BAR_SIZE  /*0xd2c1 */
#define PCI_1_EXPANSION_ROM_BAR_SIZE		       PCI_1EXPANSION_ROM_BAR_SIZE  /*0xd9c1 */
#define PCI_0_BASE_ADDR_REG_ENABLE			PCI_0BASE_ADDRESS_REGISTERS_ENABLE  /*0xc3c1 */
#define PCI_1_BASE_ADDR_REG_ENABLE			PCI_1BASE_ADDRESS_REGISTERS_ENABLE  /*0xcbc1 */
#define PCI_0_CS_0_BASE_ADDR_REMAP		PCI_0SCS_0_BASE_ADDRESS_REMAP  /*0xc481 */
#define PCI_1_CS_0_BASE_ADDR_REMAP		PCI_1SCS_0_BASE_ADDRESS_REMAP  /*0xcc81 */
#define PCI_0_CS_1_BASE_ADDR_REMAP		PCI_0SCS_1_BASE_ADDRESS_REMAP  /*0xd481 */
#define PCI_1_CS_1_BASE_ADDR_REMAP		PCI_1SCS_1_BASE_ADDRESS_REMAP  /*0xdc81 */
#define PCI_0_CS_2_BASE_ADDR_REMAP		PCI_0SCS_2_BASE_ADDRESS_REMAP  /*0xc4c1 */
#define PCI_1_CS_2_BASE_ADDR_REMAP		PCI_1SCS_2_BASE_ADDRESS_REMAP  /*0xccc1 */
#define PCI_0_CS_3_BASE_ADDR_REMAP		PCI_0SCS_3_BASE_ADDRESS_REMAP  /*0xd4c1 */
#define PCI_1_CS_3_BASE_ADDR_REMAP		PCI_1SCS_3_BASE_ADDRESS_REMAP /* 0xdcc1 */
#define PCI_0_CS_0_BASE_HIGH_ADDR_REMAP PCI_0DAC_SCS_0_BASE_ADDRESS_REMAP
#define PCI_1_CS_0_BASE_HIGH_ADDR_REMAP PCI_1DAC_SCS_0_BASE_ADDRESS_REMAP
#define PCI_0_CS_1_BASE_HIGH_ADDR_REMAP PCI_0DAC_SCS_1_BASE_ADDRESS_REMAP
#define PCI_1_CS_1_BASE_HIGH_ADDR_REMAP PCI_1DAC_SCS_1_BASE_ADDRESS_REMAP
#define PCI_0_CS_2_BASE_HIGH_ADDR_REMAP PCI_0DAC_SCS_2_BASE_ADDRESS_REMAP
#define PCI_1_CS_2_BASE_HIGH_ADDR_REMAP PCI_1DAC_SCS_2_BASE_ADDRESS_REMAP
#define PCI_0_CS_3_BASE_HIGH_ADDR_REMAP PCI_0DAC_SCS_3_BASE_ADDRESS_REMAP
#define PCI_1_CS_3_BASE_HIGH_ADDR_REMAP PCI_1DAC_SCS_3_BASE_ADDRESS_REMAP
#define PCI_0_DEVCS_0_BASE_ADDR_REMAP		PCI_0CS_0_BASE_ADDRESS_REMAP  /*0xc501 */
#define PCI_1_DEVCS_0_BASE_ADDR_REMAP		PCI_1CS_0_BASE_ADDRESS_REMAP  /*0xcd01 */
#define PCI_0_DEVCS_1_BASE_ADDR_REMAP		PCI_0CS_1_BASE_ADDRESS_REMAP  /*0xd501 */
#define PCI_1_DEVCS_1_BASE_ADDR_REMAP		PCI_1CS_1_BASE_ADDRESS_REMAP  /*0xdd01 */
#define PCI_0_DEVCS_2_BASE_ADDR_REMAP		PCI_0CS_2_BASE_ADDRESS_REMAP  /*0xd581 */
#define PCI_1_DEVCS_2_BASE_ADDR_REMAP		PCI_1CS_2_BASE_ADDRESS_REMAP  /*0xdd81 */
#define PCI_0_DEVCS_3_BASE_ADDR_REMAP			PCI_0CS_3_BASE_ADDRESS_REMAP  /*0xc541 */
#define PCI_1_DEVCS_3_BASE_ADDR_REMAP			PCI_1CS_3_BASE_ADDRESS_REMAP  /*0xcd41 */
#define PCI_0_DEVCS_BOOTCS_BASE_ADDR_REMAP    PCI_0CS_BOOTCS_BASE_ADDRESS_REMAP	 /*0xd541 */
#define PCI_1_DEVCS_BOOTCS_BASE_ADDR_REMAP    PCI_1CS_BOOTCS_BASE_ADDRESS_REMAP	 /*0xdd41 */
#define PCI_0_P2P_MEM0_BASE_ADDR_REMAP_LOW    PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_LOW  /*0xd5c1 */
#define PCI_1_P2P_MEM0_BASE_ADDR_REMAP_LOW    PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_LOW  /*0xddc1 */
#define PCI_0_P2P_MEM0_BASE_ADDR_REMAP_HIGH   PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_HIGH  /*0xd601 */
#define PCI_1_P2P_MEM0_BASE_ADDR_REMAP_HIGH   PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_HIGH  /*0xde01 */
#define PCI_0_P2P_MEM1_BASE_ADDR_REMAP_LOW	PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_LOW  /*0xd641 */
#define PCI_1_P2P_MEM1_BASE_ADDR_REMAP_LOW	PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_LOW  /*0xde41 */
#define PCI_0_P2P_MEM1_BASE_ADDR_REMAP_HIGH	PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_HIGH  /*0xd681 */
#define PCI_1_P2P_MEM1_BASE_ADDR_REMAP_HIGH	PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_HIGH  /*0xde81 */
#define PCI_0_P2P_I_O_BASE_ADDR_REMAP			PCI_0P2P_I_O_BASE_ADDRESS_REMAP	 /*0xd6c1 */
#define PCI_1_P2P_I_O_BASE_ADDR_REMAP			PCI_1P2P_I_O_BASE_ADDRESS_REMAP	 /*0xdec 1 */
#define PCI_0_CPU_BASE_ADDR_REMAP_LOW			PCI_0CPU_BASE_ADDRESS_REMAP  /*0xd701 */
#define PCI_1_CPU_BASE_ADDR_REMAP_LOW			PCI_1CPU_BASE_ADDRESS_REMAP  /*0xdf01 */
#define PCI_0_CPU_BASE_ADDR_REMAP_HIGH			0xd74
#define PCI_1_CPU_BASE_ADDR_REMAP_HIGH			0xdf4
#define PCI_0_INTEGRATED_SRAM_BASE_ADDR_REMAP		  PCI_0DAC_SCS_0_BASE_ADDRESS_REMAP  /*0xf001 */
#define PCI_1_INTEGRATED_SRAM_BASE_ADDR_REMAP		  0xf80
#define PCI_0_EXPANSION_ROM_BASE_ADDR_REMAP		   PCI_0EXPANSION_ROM_BASE_ADDRESS_REMAP  /*0xf381 */
#define PCI_1_EXPANSION_ROM_BASE_ADDR_REMAP		   PCI_1EXPANSION_ROM_BASE_ADDRESS_REMAP  /*0xfb81 */
#define PCI_0_ADDR_DECODE_CONTROL				PCI_0ADDRESS_DECODE_CONTROL  /*0xd3c1 */
#define PCI_1_ADDR_DECODE_CONTROL				PCI_1ADDRESS_DECODE_CONTROL  /*0xdbc1 */
#define PCI_0_HEADERS_RETARGET_CONTROL			0xF40
#define PCI_1_HEADERS_RETARGET_CONTROL				0xFc0
#define PCI_0_HEADERS_RETARGET_BASE				0xF44
#define PCI_1_HEADERS_RETARGET_BASE				0xFc4
#define PCI_0_HEADERS_RETARGET_HIGH				0xF48
#define PCI_1_HEADERS_RETARGET_HIGH				0xFc8

#define PCI_0SCS_0_BANK_SIZE				0xc08
#define PCI_1SCS_0_BANK_SIZE				0xc88
#define PCI_0SCS_1_BANK_SIZE				0xd08
#define PCI_1SCS_1_BANK_SIZE				0xd88
#define PCI_0SCS_2_BANK_SIZE				0xc0c
#define PCI_1SCS_2_BANK_SIZE				0xc8c
#define PCI_0SCS_3_BANK_SIZE				0xd0c
#define PCI_1SCS_3_BANK_SIZE				0xd8c
#define PCI_0CS_0_BANK_SIZE				0xc10
#define PCI_1CS_0_BANK_SIZE				0xc90
#define PCI_0CS_1_BANK_SIZE				0xd10
#define PCI_1CS_1_BANK_SIZE				0xd90
#define PCI_0CS_2_BANK_SIZE				0xd18
#define PCI_1CS_2_BANK_SIZE				0xd98
#define PCI_0CS_3_BANK_SIZE				0xc14
#define PCI_1CS_3_BANK_SIZE				0xc94
#define PCI_0CS_BOOT_BANK_SIZE				0xd14
#define PCI_1CS_BOOT_BANK_SIZE				0xd94
#define PCI_0P2P_MEM0_BAR_SIZE						0xd1c
#define PCI_1P2P_MEM0_BAR_SIZE						0xd9c
#define PCI_0P2P_MEM1_BAR_SIZE						0xd20
#define PCI_1P2P_MEM1_BAR_SIZE						0xda0
#define PCI_0P2P_I_O_BAR_SIZE						0xd24
#define PCI_1P2P_I_O_BAR_SIZE						0xda4
#define PCI_0CPU_BAR_SIZE						0xd28
#define PCI_1CPU_BAR_SIZE						0xda8
#define PCI_0DAC_SCS_0_BANK_SIZE				0xe00
#define PCI_1DAC_SCS_0_BANK_SIZE				0xe80
#define PCI_0DAC_SCS_1_BANK_SIZE				0xe04
#define PCI_1DAC_SCS_1_BANK_SIZE				0xe84
#define PCI_0DAC_SCS_2_BANK_SIZE				0xe08
#define PCI_1DAC_SCS_2_BANK_SIZE				0xe88
#define PCI_0DAC_SCS_3_BANK_SIZE				0xe0c
#define PCI_1DAC_SCS_3_BANK_SIZE				0xe8c
#define PCI_0DAC_CS_0_BANK_SIZE					0xe10
#define PCI_1DAC_CS_0_BANK_SIZE					0xe90
#define PCI_0DAC_CS_1_BANK_SIZE					0xe14
#define PCI_1DAC_CS_1_BANK_SIZE					0xe94
#define PCI_0DAC_CS_2_BANK_SIZE					0xe18
#define PCI_1DAC_CS_2_BANK_SIZE					0xe98
#define PCI_0DAC_CS_3_BANK_SIZE					0xe1c
#define PCI_1DAC_CS_3_BANK_SIZE					0xe9c
#define PCI_0DAC_BOOTCS_BANK_SIZE				0xe20
#define PCI_1DAC_BOOTCS_BANK_SIZE				0xea0

#define PCI_0DAC_P2P_MEM0_BAR_SIZE				0xe24
#define PCI_1DAC_P2P_MEM0_BAR_SIZE				0xea4
#define PCI_0DAC_P2P_MEM1_BAR_SIZE				0xe28
#define PCI_1DAC_P2P_MEM1_BAR_SIZE				0xea8
#define PCI_0DAC_CPU_BAR_SIZE						0xe2c
#define PCI_1DAC_CPU_BAR_SIZE						0xeac
#define PCI_0EXPANSION_ROM_BAR_SIZE				0xd2c
#define PCI_1EXPANSION_ROM_BAR_SIZE				0xdac
#define PCI_0BASE_ADDRESS_REGISTERS_ENABLE		0xc3c
#define PCI_1BASE_ADDRESS_REGISTERS_ENABLE		0xcbc
#define PCI_0SCS_0_BASE_ADDRESS_REMAP			0xc48
#define PCI_1SCS_0_BASE_ADDRESS_REMAP			0xcc8
#define PCI_0SCS_1_BASE_ADDRESS_REMAP			0xd48
#define PCI_1SCS_1_BASE_ADDRESS_REMAP			0xdc8
#define PCI_0SCS_2_BASE_ADDRESS_REMAP			0xc4c
#define PCI_1SCS_2_BASE_ADDRESS_REMAP			0xccc
#define PCI_0SCS_3_BASE_ADDRESS_REMAP			0xd4c
#define PCI_1SCS_3_BASE_ADDRESS_REMAP			0xdcc
#define PCI_0CS_0_BASE_ADDRESS_REMAP			0xc50
#define PCI_1CS_0_BASE_ADDRESS_REMAP			0xcd0
#define PCI_0CS_1_BASE_ADDRESS_REMAP			0xd50
#define PCI_1CS_1_BASE_ADDRESS_REMAP			0xdd0
#define PCI_0CS_2_BASE_ADDRESS_REMAP			0xd58
#define PCI_1CS_2_BASE_ADDRESS_REMAP			0xdd8
#define PCI_0CS_3_BASE_ADDRESS_REMAP			0xc54
#define PCI_1CS_3_BASE_ADDRESS_REMAP			0xcd4
#define PCI_0CS_BOOTCS_BASE_ADDRESS_REMAP	0xd54
#define PCI_1CS_BOOTCS_BASE_ADDRESS_REMAP	0xdd4
#define PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_LOW			0xd5c
#define PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_LOW		  0xddc
#define PCI_0P2P_MEM0_BASE_ADDRESS_REMAP_HIGH		  0xd60
#define PCI_1P2P_MEM0_BASE_ADDRESS_REMAP_HIGH		  0xde0
#define PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_LOW		 0xd64
#define PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_LOW		 0xde4
#define PCI_0P2P_MEM1_BASE_ADDRESS_REMAP_HIGH		 0xd68
#define PCI_1P2P_MEM1_BASE_ADDRESS_REMAP_HIGH		 0xde8
#define PCI_0P2P_I_O_BASE_ADDRESS_REMAP				0xd6c
#define PCI_1P2P_I_O_BASE_ADDRESS_REMAP				0xdec
#define PCI_0CPU_BASE_ADDRESS_REMAP				0xd70
#define PCI_1CPU_BASE_ADDRESS_REMAP				0xdf0
#define PCI_0DAC_SCS_0_BASE_ADDRESS_REMAP			0xf00
#define PCI_1DAC_SCS_0_BASE_ADDRESS_REMAP			0xff0
#define PCI_0DAC_SCS_1_BASE_ADDRESS_REMAP			0xf04
#define PCI_1DAC_SCS_1_BASE_ADDRESS_REMAP			0xf84
#define PCI_0DAC_SCS_2_BASE_ADDRESS_REMAP			0xf08
#define PCI_1DAC_SCS_2_BASE_ADDRESS_REMAP			0xf88
#define PCI_0DAC_SCS_3_BASE_ADDRESS_REMAP			0xf0c
#define PCI_1DAC_SCS_3_BASE_ADDRESS_REMAP			0xf8c
#define PCI_0DAC_CS_0_BASE_ADDRESS_REMAP			0xf10
#define PCI_1DAC_CS_0_BASE_ADDRESS_REMAP			0xf90
#define PCI_0DAC_CS_1_BASE_ADDRESS_REMAP			0xf14
#define PCI_1DAC_CS_1_BASE_ADDRESS_REMAP			0xf94
#define PCI_0DAC_CS_2_BASE_ADDRESS_REMAP			0xf18
#define PCI_1DAC_CS_2_BASE_ADDRESS_REMAP			0xf98
#define PCI_0DAC_CS_3_BASE_ADDRESS_REMAP			0xf1c
#define PCI_1DAC_CS_3_BASE_ADDRESS_REMAP			0xf9c
#define PCI_0DAC_BOOTCS_BASE_ADDRESS_REMAP			0xf20
#define PCI_1DAC_BOOTCS_BASE_ADDRESS_REMAP		    0xfa0
#define PCI_0DAC_P2P_MEM0_BASE_ADDRESS_REMAP_LOW     0xf24
#define PCI_1DAC_P2P_MEM0_BASE_ADDRESS_REMAP_LOW     0xfa4
#define PCI_0DAC_P2P_MEM0_BASE_ADDRESS_REMAP_HIGH    0xf28
#define PCI_1DAC_P2P_MEM0_BASE_ADDRESS_REMAP_HIGH    0xfa8
#define PCI_0DAC_P2P_MEM1_BASE_ADDRESS_REMAP_LOW	0xf2c
#define PCI_1DAC_P2P_MEM1_BASE_ADDRESS_REMAP_LOW     0xfac
#define PCI_0DAC_P2P_MEM1_BASE_ADDRESS_REMAP_HIGH    0xf30
#define PCI_1DAC_P2P_MEM1_BASE_ADDRESS_REMAP_HIGH    0xfb0
#define PCI_0DAC_CPU_BASE_ADDRESS_REMAP				0xf34
#define PCI_1DAC_CPU_BASE_ADDRESS_REMAP				0xfb4
#define PCI_0EXPANSION_ROM_BASE_ADDRESS_REMAP			0xf38
#define PCI_1EXPANSION_ROM_BASE_ADDRESS_REMAP			0xfb8
#define PCI_0ADDRESS_DECODE_CONTROL				0xd3c
#define PCI_1ADDRESS_DECODE_CONTROL				0xdbc

/****************************************/
/* PCI Control				*/
/****************************************/

#define PCI_0COMMAND										0xc00
#define PCI_1COMMAND										0xc80
#define PCI_0MODE					    0xd00
#define PCI_1MODE					    0xd80
#define PCI_0TIMEOUT_RETRY									0xc04
#define PCI_1TIMEOUT_RETRY									0xc84
#define PCI_0READ_BUFFER_DISCARD_TIMER			    0xd04
#define PCI_1READ_BUFFER_DISCARD_TIMER			    0xd84
#define MSI_0TRIGGER_TIMER				    0xc38
#define MSI_1TRIGGER_TIMER				    0xcb8
#define PCI_0ARBITER_CONTROL				    0x1d00
#define PCI_1ARBITER_CONTROL				    0x1d80
/* changing untill here */
#define PCI_0CROSS_BAR_CONTROL_LOW			     0x1d08
#define PCI_0CROSS_BAR_CONTROL_HIGH			     0x1d0c
#define PCI_0CROSS_BAR_TIMEOUT				     0x1d04
#define PCI_0READ_RESPONSE_CROSS_BAR_CONTROL_LOW	     0x1d18
#define PCI_0READ_RESPONSE_CROSS_BAR_CONTROL_HIGH	     0x1d1c
#define PCI_0SYNC_BARRIER_VIRTUAL_REGISTER		     0x1d10
#define PCI_0P2P_CONFIGURATION				     0x1d14
#define PCI_0ACCESS_CONTROL_BASE_0_LOW			     0x1e00
#define PCI_0ACCESS_CONTROL_BASE_0_HIGH			     0x1e04
#define PCI_0ACCESS_CONTROL_TOP_0			     0x1e08
#define PCI_0ACCESS_CONTROL_BASE_1_LOW			     0x1e10
#define PCI_0ACCESS_CONTROL_BASE_1_HIGH			     0x1e14
#define PCI_0ACCESS_CONTROL_TOP_1			     0x1e18
#define PCI_0ACCESS_CONTROL_BASE_2_LOW			     0x1e20
#define PCI_0ACCESS_CONTROL_BASE_2_HIGH			     0x1e24
#define PCI_0ACCESS_CONTROL_TOP_2			     0x1e28
#define PCI_0ACCESS_CONTROL_BASE_3_LOW			     0x1e30
#define PCI_0ACCESS_CONTROL_BASE_3_HIGH			     0x1e34
#define PCI_0ACCESS_CONTROL_TOP_3			     0x1e38
#define PCI_0ACCESS_CONTROL_BASE_4_LOW			     0x1e40
#define PCI_0ACCESS_CONTROL_BASE_4_HIGH			     0x1e44
#define PCI_0ACCESS_CONTROL_TOP_4			     0x1e48
#define PCI_0ACCESS_CONTROL_BASE_5_LOW			     0x1e50
#define PCI_0ACCESS_CONTROL_BASE_5_HIGH			     0x1e54
#define PCI_0ACCESS_CONTROL_TOP_5			     0x1e58
#define PCI_0ACCESS_CONTROL_BASE_6_LOW			     0x1e60
#define PCI_0ACCESS_CONTROL_BASE_6_HIGH			     0x1e64
#define PCI_0ACCESS_CONTROL_TOP_6			     0x1e68
#define PCI_0ACCESS_CONTROL_BASE_7_LOW			     0x1e70
#define PCI_0ACCESS_CONTROL_BASE_7_HIGH			     0x1e74
#define PCI_0ACCESS_CONTROL_TOP_7			     0x1e78
#define PCI_1CROSS_BAR_CONTROL_LOW			     0x1d88
#define PCI_1CROSS_BAR_CONTROL_HIGH			     0x1d8c
#define PCI_1CROSS_BAR_TIMEOUT				     0x1d84
#define PCI_1READ_RESPONSE_CROSS_BAR_CONTROL_LOW	     0x1d98
#define PCI_1READ_RESPONSE_CROSS_BAR_CONTROL_HIGH	     0x1d9c
#define PCI_1SYNC_BARRIER_VIRTUAL_REGISTER		     0x1d90
#define PCI_1P2P_CONFIGURATION				     0x1d94
#define PCI_1ACCESS_CONTROL_BASE_0_LOW			     0x1e80
#define PCI_1ACCESS_CONTROL_BASE_0_HIGH			     0x1e84
#define PCI_1ACCESS_CONTROL_TOP_0			     0x1e88
#define PCI_1ACCESS_CONTROL_BASE_1_LOW			     0x1e90
#define PCI_1ACCESS_CONTROL_BASE_1_HIGH			     0x1e94
#define PCI_1ACCESS_CONTROL_TOP_1			     0x1e98
#define PCI_1ACCESS_CONTROL_BASE_2_LOW			     0x1ea0
#define PCI_1ACCESS_CONTROL_BASE_2_HIGH			     0x1ea4
#define PCI_1ACCESS_CONTROL_TOP_2			     0x1ea8
#define PCI_1ACCESS_CONTROL_BASE_3_LOW			     0x1eb0
#define PCI_1ACCESS_CONTROL_BASE_3_HIGH			     0x1eb4
#define PCI_1ACCESS_CONTROL_TOP_3			     0x1eb8
#define PCI_1ACCESS_CONTROL_BASE_4_LOW			     0x1ec0
#define PCI_1ACCESS_CONTROL_BASE_4_HIGH			     0x1ec4
#define PCI_1ACCESS_CONTROL_TOP_4			     0x1ec8
#define PCI_1ACCESS_CONTROL_BASE_5_LOW			     0x1ed0
#define PCI_1ACCESS_CONTROL_BASE_5_HIGH			     0x1ed4
#define PCI_1ACCESS_CONTROL_TOP_5			     0x1ed8
#define PCI_1ACCESS_CONTROL_BASE_6_LOW			     0x1ee0
#define PCI_1ACCESS_CONTROL_BASE_6_HIGH			     0x1ee4
#define PCI_1ACCESS_CONTROL_TOP_6			     0x1ee8
#define PCI_1ACCESS_CONTROL_BASE_7_LOW			     0x1ef0
#define PCI_1ACCESS_CONTROL_BASE_7_HIGH			     0x1ef4
#define PCI_1ACCESS_CONTROL_TOP_7			     0x1ef8

/****************************************/
/* PCI Snoop Control			*/
/****************************************/

#define PCI_0SNOOP_CONTROL_BASE_0_LOW			     0x1f00
#define PCI_0SNOOP_CONTROL_BASE_0_HIGH			     0x1f04
#define PCI_0SNOOP_CONTROL_TOP_0			     0x1f08
#define PCI_0SNOOP_CONTROL_BASE_1_0_LOW			     0x1f10
#define PCI_0SNOOP_CONTROL_BASE_1_0_HIGH		     0x1f14
#define PCI_0SNOOP_CONTROL_TOP_1			     0x1f18
#define PCI_0SNOOP_CONTROL_BASE_2_0_LOW			     0x1f20
#define PCI_0SNOOP_CONTROL_BASE_2_0_HIGH		     0x1f24
#define PCI_0SNOOP_CONTROL_TOP_2			     0x1f28
#define PCI_0SNOOP_CONTROL_BASE_3_0_LOW			     0x1f30
#define PCI_0SNOOP_CONTROL_BASE_3_0_HIGH		     0x1f34
#define PCI_0SNOOP_CONTROL_TOP_3			     0x1f38
#define PCI_1SNOOP_CONTROL_BASE_0_LOW			     0x1f80
#define PCI_1SNOOP_CONTROL_BASE_0_HIGH			     0x1f84
#define PCI_1SNOOP_CONTROL_TOP_0			     0x1f88
#define PCI_1SNOOP_CONTROL_BASE_1_0_LOW			     0x1f90
#define PCI_1SNOOP_CONTROL_BASE_1_0_HIGH		     0x1f94
#define PCI_1SNOOP_CONTROL_TOP_1			     0x1f98
#define PCI_1SNOOP_CONTROL_BASE_2_0_LOW			     0x1fa0
#define PCI_1SNOOP_CONTROL_BASE_2_0_HIGH		     0x1fa4
#define PCI_1SNOOP_CONTROL_TOP_2			     0x1fa8
#define PCI_1SNOOP_CONTROL_BASE_3_0_LOW			     0x1fb0
#define PCI_1SNOOP_CONTROL_BASE_3_0_HIGH		     0x1fb4
#define PCI_1SNOOP_CONTROL_TOP_3			     0x1fb8

/****************************************/
/* PCI Configuration Address		*/
/****************************************/

#define PCI_0CONFIGURATION_ADDRESS							0xcf8
#define PCI_0CONFIGURATION_DATA_VIRTUAL_REGISTER		0xcfc
#define PCI_1CONFIGURATION_ADDRESS							0xc78
#define PCI_1CONFIGURATION_DATA_VIRTUAL_REGISTER		0xc7c
#define PCI_0INTERRUPT_ACKNOWLEDGE_VIRTUAL_REGISTER			0xc34
#define PCI_1INTERRUPT_ACKNOWLEDGE_VIRTUAL_REGISTER			0xcb4

/****************************************/
/* PCI Error Report			*/
/****************************************/

#define PCI_0SERR_MASK										 0xc28
#define PCI_0ERROR_ADDRESS_LOW				     0x1d40
#define PCI_0ERROR_ADDRESS_HIGH				     0x1d44
#define PCI_0ERROR_DATA_LOW				     0x1d48
#define PCI_0ERROR_DATA_HIGH				     0x1d4c
#define PCI_0ERROR_COMMAND				     0x1d50
#define PCI_0ERROR_CAUSE				     0x1d58
#define PCI_0ERROR_MASK					     0x1d5c
#define PCI_1SERR_MASK										 0xca8
#define PCI_1ERROR_ADDRESS_LOW				     0x1dc0
#define PCI_1ERROR_ADDRESS_HIGH				     0x1dc4
#define PCI_1ERROR_DATA_LOW				     0x1dc8
#define PCI_1ERROR_DATA_HIGH				     0x1dcc
#define PCI_1ERROR_COMMAND				     0x1dd0
#define PCI_1ERROR_CAUSE				     0x1dd8
#define PCI_1ERROR_MASK					     0x1ddc


/****************************************/
/* Lslave Debug	 (for internal use)	*/
/****************************************/

#define L_SLAVE_X0_ADDRESS				    0x1d20
#define L_SLAVE_X0_COMMAND_AND_ID			    0x1d24
#define L_SLAVE_X1_ADDRESS				    0x1d28
#define L_SLAVE_X1_COMMAND_AND_ID			    0x1d2c
#define L_SLAVE_WRITE_DATA_LOW				    0x1d30
#define L_SLAVE_WRITE_DATA_HIGH				    0x1d34
#define L_SLAVE_WRITE_BYTE_ENABLE			    0x1d60
#define L_SLAVE_READ_DATA_LOW				    0x1d38
#define L_SLAVE_READ_DATA_HIGH				    0x1d3c
#define L_SLAVE_READ_ID					    0x1d64

/****************************************/
/* PCI Configuration Function 0		*/
/****************************************/

#define PCI_DEVICE_AND_VENDOR_ID							0x000
#define PCI_STATUS_AND_COMMAND								0x004
#define PCI_CLASS_CODE_AND_REVISION_ID					0x008
#define PCI_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE		0x00C
#define PCI_SCS_0_BASE_ADDRESS							0x010
#define PCI_SCS_1_BASE_ADDRESS							    0x014
#define PCI_SCS_2_BASE_ADDRESS							    0x018
#define PCI_SCS_3_BASE_ADDRESS							0x01C
#define PCI_INTERNAL_REGISTERS_MEMORY_MAPPED_BASE_ADDRESS	0x020
#define PCI_INTERNAL_REGISTERS_I_OMAPPED_BASE_ADDRESS		0x024
#define PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOR_ID			0x02C
#define PCI_EXPANSION_ROM_BASE_ADDRESS_REGISTER				0x030
#define PCI_CAPABILTY_LIST_POINTER			    0x034
#define PCI_INTERRUPT_PIN_AND_LINE						    0x03C
#define PCI_POWER_MANAGEMENT_CAPABILITY			    0x040
#define PCI_POWER_MANAGEMENT_STATUS_AND_CONTROL		    0x044
#define PCI_VPD_ADDRESS					    0x048
#define PCI_VPD_DATA					    0x04c
#define PCI_MSI_MESSAGE_CONTROL				    0x050
#define PCI_MSI_MESSAGE_ADDRESS				    0x054
#define PCI_MSI_MESSAGE_UPPER_ADDRESS			    0x058
#define PCI_MSI_MESSAGE_DATA				    0x05c
#define PCI_COMPACT_PCI_HOT_SWAP_CAPABILITY		    0x058

/****************************************/
/* PCI Configuration Function 1		*/
/****************************************/

#define PCI_CS_0_BASE_ADDRESS							0x110
#define PCI_CS_1_BASE_ADDRESS							    0x114
#define PCI_CS_2_BASE_ADDRESS							    0x118
#define PCI_CS_3_BASE_ADDRESS							0x11c
#define PCI_BOOTCS_BASE_ADDRESS				    0x120

/****************************************/
/* PCI Configuration Function 2		*/
/****************************************/

#define PCI_P2P_MEM0_BASE_ADDRESS						0x210
 /*#define PCI_P2P_MEM1_BASE_ADDRESS							0x2141 */
#define PCI_P2P_I_O_BASE_ADDRESS							0x218
 /*#define PCI_CPU_BASE_ADDRESS							    0x21c1 */

/****************************************/
/* PCI Configuration Function 4		*/
/****************************************/

#define PCI_DAC_SCS_0_BASE_ADDRESS_LOW						0x410
#define PCI_DAC_SCS_0_BASE_ADDRESS_HIGH					    0x414
#define PCI_DAC_SCS_1_BASE_ADDRESS_LOW					    0x418
#define PCI_DAC_SCS_1_BASE_ADDRESS_HIGH					    0x41c
#define PCI_DAC_P2P_MEM0_BASE_ADDRESS_LOW		    0x420
#define PCI_DAC_P2P_MEM0_BASE_ADDRESS_HIGH		    0x424


/****************************************/
/* PCI Configuration Function 5		*/
/****************************************/

#define PCI_DAC_SCS_2_BASE_ADDRESS_LOW						0x510
#define PCI_DAC_SCS_2_BASE_ADDRESS_HIGH					    0x514
#define PCI_DAC_SCS_3_BASE_ADDRESS_LOW					    0x518
#define PCI_DAC_SCS_3_BASE_ADDRESS_HIGH					    0x51c
#define PCI_DAC_P2P_MEM1_BASE_ADDRESS_LOW		    0x520
#define PCI_DAC_P2P_MEM1_BASE_ADDRESS_HIGH		    0x524


/****************************************/
/* PCI Configuration Function 6		*/
/****************************************/

#define PCI_DAC_CS_0_BASE_ADDRESS_LOW						0x610
#define PCI_DAC_CS_0_BASE_ADDRESS_HIGH					    0x614
#define PCI_DAC_CS_1_BASE_ADDRESS_LOW					    0x618
#define PCI_DAC_CS_1_BASE_ADDRESS_HIGH					    0x61c
#define PCI_DAC_CS_2_BASE_ADDRESS_LOW				0x620
#define PCI_DAC_CS_2_BASE_ADDRESS_HIGH				0x624

/****************************************/
/* PCI Configuration Function 7		*/
/****************************************/

#define PCI_DAC_CS_3_BASE_ADDRESS_LOW						0x710
#define PCI_DAC_CS_3_BASE_ADDRESS_HIGH					    0x714
#define PCI_DAC_BOOTCS_BASE_ADDRESS_LOW					    0x718
#define PCI_DAC_BOOTCS_BASE_ADDRESS_HIGH				    0x71c
#define PCI_DAC_CPU_BASE_ADDRESS_LOW				0x720
#define PCI_DAC_CPU_BASE_ADDRESS_HIGH				0x724

/****************************** MV64360 and MV64460 PCI ***************************/
/***********************************/
/*   PCI Control Register Map	   */
/***********************************/

#define PCI_0_DLL_STATUS_AND_COMMAND				0x1d20
#define PCI_1_DLL_STATUS_AND_COMMAND				0x1da0
#define PCI_0_MPP_PADS_DRIVE_CONTROL				0x1d1C
#define PCI_1_MPP_PADS_DRIVE_CONTROL				0x1d9C
#define PCI_0_COMMAND					0xc00
#define PCI_1_COMMAND					0xc80
#define PCI_0_MODE							0xd00
#define PCI_1_MODE							0xd80
#define PCI_0_RETRY						0xc04
#define PCI_1_RETRY						0xc84
#define PCI_0_READ_BUFFER_DISCARD_TIMER				0xd04
#define PCI_1_READ_BUFFER_DISCARD_TIMER				0xd84
#define PCI_0_MSI_TRIGGER_TIMER						0xc38
#define PCI_1_MSI_TRIGGER_TIMER						0xcb8
#define PCI_0_ARBITER_CONTROL						0x1d00
#define PCI_1_ARBITER_CONTROL						0x1d80
#define PCI_0_CROSS_BAR_CONTROL_LOW				0x1d08
#define PCI_1_CROSS_BAR_CONTROL_LOW				0x1d88
#define PCI_0_CROSS_BAR_CONTROL_HIGH				0x1d0c
#define PCI_1_CROSS_BAR_CONTROL_HIGH				0x1d8c
#define PCI_0_CROSS_BAR_TIMEOUT					0x1d04
#define PCI_1_CROSS_BAR_TIMEOUT					0x1d84
#define PCI_0_SYNC_BARRIER_TRIGGER_REG				0x1D18
#define PCI_1_SYNC_BARRIER_TRIGGER_REG				0x1D98
#define PCI_0_SYNC_BARRIER_VIRTUAL_REG				0x1d10
#define PCI_1_SYNC_BARRIER_VIRTUAL_REG				0x1d90
#define PCI_0_P2P_CONFIG						0x1d14
#define PCI_1_P2P_CONFIG						0x1d94

#define PCI_0_ACCESS_CONTROL_BASE_0_LOW				0x1e00
#define PCI_0_ACCESS_CONTROL_BASE_0_HIGH			0x1e04
#define PCI_0_ACCESS_CONTROL_SIZE_0				0x1e08
#define PCI_0_ACCESS_CONTROL_BASE_1_LOW				0x1e10
#define PCI_0_ACCESS_CONTROL_BASE_1_HIGH			0x1e14
#define PCI_0_ACCESS_CONTROL_SIZE_1				0x1e18
#define PCI_0_ACCESS_CONTROL_BASE_2_LOW				0x1e20
#define PCI_0_ACCESS_CONTROL_BASE_2_HIGH			0x1e24
#define PCI_0_ACCESS_CONTROL_SIZE_2				0x1e28
#define PCI_0_ACCESS_CONTROL_BASE_3_LOW				0x1e30
#define PCI_0_ACCESS_CONTROL_BASE_3_HIGH			0x1e34
#define PCI_0_ACCESS_CONTROL_SIZE_3				0x1e38
#define PCI_0_ACCESS_CONTROL_BASE_4_LOW				0x1e40
#define PCI_0_ACCESS_CONTROL_BASE_4_HIGH			0x1e44
#define PCI_0_ACCESS_CONTROL_SIZE_4				0x1e48
#define PCI_0_ACCESS_CONTROL_BASE_5_LOW				0x1e50
#define PCI_0_ACCESS_CONTROL_BASE_5_HIGH			0x1e54
#define PCI_0_ACCESS_CONTROL_SIZE_5				0x1e58

#define PCI_1_ACCESS_CONTROL_BASE_0_LOW				0x1e80
#define PCI_1_ACCESS_CONTROL_BASE_0_HIGH			0x1e84
#define PCI_1_ACCESS_CONTROL_SIZE_0				0x1e88
#define PCI_1_ACCESS_CONTROL_BASE_1_LOW				0x1e90
#define PCI_1_ACCESS_CONTROL_BASE_1_HIGH			0x1e94
#define PCI_1_ACCESS_CONTROL_SIZE_1				0x1e98
#define PCI_1_ACCESS_CONTROL_BASE_2_LOW				0x1ea0
#define PCI_1_ACCESS_CONTROL_BASE_2_HIGH			0x1ea4
#define PCI_1_ACCESS_CONTROL_SIZE_2				0x1ea8
#define PCI_1_ACCESS_CONTROL_BASE_3_LOW				0x1eb0
#define PCI_1_ACCESS_CONTROL_BASE_3_HIGH			0x1eb4
#define PCI_1_ACCESS_CONTROL_SIZE_3				0x1eb8
#define PCI_1_ACCESS_CONTROL_BASE_4_LOW				0x1ec0
#define PCI_1_ACCESS_CONTROL_BASE_4_HIGH			0x1ec4
#define PCI_1_ACCESS_CONTROL_SIZE_4				0x1ec8
#define PCI_1_ACCESS_CONTROL_BASE_5_LOW				0x1ed0
#define PCI_1_ACCESS_CONTROL_BASE_5_HIGH			0x1ed4
#define PCI_1_ACCESS_CONTROL_SIZE_5				0x1ed8

/****************************************/
/*   PCI Configuration Access Registers */
/****************************************/

#define PCI_0_CONFIG_ADDR				0xcf8
#define PCI_0_CONFIG_DATA_VIRTUAL_REG				0xcfc
#define PCI_1_CONFIG_ADDR				0xc78
#define PCI_1_CONFIG_DATA_VIRTUAL_REG				0xc7c
#define PCI_0_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG 0xc34
#define PCI_1_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG 0xcb4

/****************************************/
/*   PCI Error Report Registers		*/
/****************************************/

#define PCI_0_SERR_MASK					0xc28
#define PCI_1_SERR_MASK					0xca8
#define PCI_0_ERROR_ADDR_LOW						0x1d40
#define PCI_1_ERROR_ADDR_LOW						0x1dc0
#define PCI_0_ERROR_ADDR_HIGH						0x1d44
#define PCI_1_ERROR_ADDR_HIGH						0x1dc4
#define PCI_0_ERROR_ATTRIBUTE						0x1d48
#define PCI_1_ERROR_ATTRIBUTE						0x1dc8
#define PCI_0_ERROR_COMMAND						0x1d50
#define PCI_1_ERROR_COMMAND						0x1dd0
#define PCI_0_ERROR_CAUSE						0x1d58
#define PCI_1_ERROR_CAUSE						0x1dd8
#define PCI_0_ERROR_MASK						0x1d5c
#define PCI_1_ERROR_MASK						0x1ddc

/****************************************/
/*   PCI Debug Registers		*/
/****************************************/

#define PCI_0_MMASK							0X1D24
#define PCI_1_MMASK							0X1DA4

/*********************************************/
/* PCI Configuration, Function 0, Registers  */
/*********************************************/

#define PCI_DEVICE_AND_VENDOR_ID			0x000
#define PCI_STATUS_AND_COMMAND			0x004
#define PCI_CLASS_CODE_AND_REVISION_ID			0x008
#define PCI_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE		0x00C

#define PCI_SCS_0_BASE_ADDR_LOW				0x010
#define PCI_SCS_0_BASE_ADDR_HIGH			0x014
#define PCI_SCS_1_BASE_ADDR_LOW				0x018
#define PCI_SCS_1_BASE_ADDR_HIGH			0x01C
#define PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_LOW    0x020
#define PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_HIGH   0x024
 /*#define PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOR_ID	0x02c1 */
#define PCI_EXPANSION_ROM_BASE_ADDR_REG		0x030
#define PCI_CAPABILTY_LIST_POINTER				0x034
#define PCI_INTERRUPT_PIN_AND_LINE			0x03C
       /* capability list */
#define PCI_POWER_MANAGEMENT_CAPABILITY				0x040
#define PCI_POWER_MANAGEMENT_STATUS_AND_CONTROL	     0x044
#define PCI_VPD_ADDR							0x048
#define PCI_VPD_DATA							0x04c
#define PCI_MSI_MESSAGE_CONTROL					0x050
#define PCI_MSI_MESSAGE_ADDR						0x054
#define PCI_MSI_MESSAGE_UPPER_ADDR				0x058
#define PCI_MSI_MESSAGE_DATA						0x05c
#define PCI_X_COMMAND							0x060
#define PCI_X_STATUS							0x064
#define PCI_COMPACT_PCI_HOT_SWAP				0x068

/***********************************************/
/*   PCI Configuration, Function 1, Registers  */
/***********************************************/

#define PCI_SCS_2_BASE_ADDR_LOW				0x110
#define PCI_SCS_2_BASE_ADDR_HIGH			0x114
#define PCI_SCS_3_BASE_ADDR_LOW				0x118
#define PCI_SCS_3_BASE_ADDR_HIGH			0x11c
#define PCI_INTERNAL_SRAM_BASE_ADDR_LOW					0x120
#define PCI_INTERNAL_SRAM_BASE_ADDR_HIGH				0x124

/***********************************************/
/*  PCI Configuration, Function 2, Registers   */
/***********************************************/

#define PCI_DEVCS_0_BASE_ADDR_LOW			0x210
#define PCI_DEVCS_0_BASE_ADDR_HIGH			0x214
#define PCI_DEVCS_1_BASE_ADDR_LOW			0x218
#define PCI_DEVCS_1_BASE_ADDR_HIGH				0x21c
#define PCI_DEVCS_2_BASE_ADDR_LOW			0x220
#define PCI_DEVCS_2_BASE_ADDR_HIGH				0x224

/***********************************************/
/*  PCI Configuration, Function 3, Registers   */
/***********************************************/

#define PCI_DEVCS_3_BASE_ADDR_LOW			0x310
#define PCI_DEVCS_3_BASE_ADDR_HIGH			0x314
#define PCI_BOOT_CS_BASE_ADDR_LOW			0x318
#define PCI_BOOT_CS_BASE_ADDR_HIGH				0x31c
#define PCI_CPU_BASE_ADDR_LOW				0x220
#define PCI_CPU_BASE_ADDR_HIGH				0x224

/***********************************************/
/*  PCI Configuration, Function 4, Registers   */
/***********************************************/

#define PCI_P2P_MEM0_BASE_ADDR_LOW			0x410
#define PCI_P2P_MEM0_BASE_ADDR_HIGH			0x414
#define PCI_P2P_MEM1_BASE_ADDR_LOW			0x418
#define PCI_P2P_MEM1_BASE_ADDR_HIGH			0x41c
#define PCI_P2P_I_O_BASE_ADDR						0x420
#define PCI_INTERNAL_REGS_I_O_MAPPED_BASE_ADDR		  0x424

/****************************** MV64360 and MV64460 PCI End ***************************/
/****************************************/
/* I20 Support registers				*/
/****************************************/

#define INBOUND_MESSAGE_REGISTER0_PCI_SIDE		0x010
#define INBOUND_MESSAGE_REGISTER1_PCI_SIDE		0x014
#define OUTBOUND_MESSAGE_REGISTER0_PCI_SIDE		0x018
#define OUTBOUND_MESSAGE_REGISTER1_PCI_SIDE		0x01C
#define INBOUND_DOORBELL_REGISTER_PCI_SIDE		0x020
#define INBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE	0x024
#define INBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE	0x028
#define OUTBOUND_DOORBELL_REGISTER_PCI_SIDE		0x02C
#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_PCI_SIDE	0x030
#define OUTBOUND_INTERRUPT_MASK_REGISTER_PCI_SIDE	0x034
#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE	0x040
#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_PCI_SIDE	0x044
#define QUEUE_CONTROL_REGISTER_PCI_SIDE			0x050
#define QUEUE_BASE_ADDRESS_REGISTER_PCI_SIDE		0x054
#define INBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE	0x060
#define INBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE	0x064
#define INBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE	0x068
#define INBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE	0x06C
#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_PCI_SIDE	0x070
#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_PCI_SIDE	0x074
#define OUTBOUND_POST_HEAD_POINTER_REGISTER_PCI_SIDE	0x078
#define OUTBOUND_POST_TAIL_POINTER_REGISTER_PCI_SIDE	0x07C

#define INBOUND_MESSAGE_REGISTER0_CPU_SIDE		0x1C10
#define INBOUND_MESSAGE_REGISTER1_CPU_SIDE		0x1C14
#define OUTBOUND_MESSAGE_REGISTER0_CPU_SIDE		0x1C18
#define OUTBOUND_MESSAGE_REGISTER1_CPU_SIDE		0x1C1C
#define INBOUND_DOORBELL_REGISTER_CPU_SIDE		0x1C20
#define INBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE	0x1C24
#define INBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE	0x1C28
#define OUTBOUND_DOORBELL_REGISTER_CPU_SIDE		0x1C2C
#define OUTBOUND_INTERRUPT_CAUSE_REGISTER_CPU_SIDE	0x1C30
#define OUTBOUND_INTERRUPT_MASK_REGISTER_CPU_SIDE	0x1C34
#define INBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE		0x1C40
#define OUTBOUND_QUEUE_PORT_VIRTUAL_REGISTER_CPU_SIDE		0x1C44
#define QUEUE_CONTROL_REGISTER_CPU_SIDE				0x1C50
#define QUEUE_BASE_ADDRESS_REGISTER_CPU_SIDE			0x1C54
#define INBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE		0x1C60
#define INBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE		0x1C64
#define INBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE		0x1C68
#define INBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE		0x1C6C
#define OUTBOUND_FREE_HEAD_POINTER_REGISTER_CPU_SIDE		0x1C70
#define OUTBOUND_FREE_TAIL_POINTER_REGISTER_CPU_SIDE		0x1C74
#define OUTBOUND_POST_HEAD_POINTER_REGISTER_CPU_SIDE		0x1C78
#define OUTBOUND_POST_TAIL_POINTER_REGISTER_CPU_SIDE		0x1C7C


/****************************************/
/* Messaging Unit Registers (I20)	*/
/****************************************/

#define I2O_INBOUND_MESSAGE_REG0_PCI_0_SIDE			0x010
#define I2O_INBOUND_MESSAGE_REG1_PCI_0_SIDE				0x014
#define I2O_OUTBOUND_MESSAGE_REG0_PCI_0_SIDE				0x018
#define I2O_OUTBOUND_MESSAGE_REG1_PCI_0_SIDE				0x01C
#define I2O_INBOUND_DOORBELL_REG_PCI_0_SIDE				0x020
#define I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE		0x024
#define I2O_INBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE			0x028
#define I2O_OUTBOUND_DOORBELL_REG_PCI_0_SIDE				0x02C
#define I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE		0x030
#define I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE		0x034
#define I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE		0x040
#define I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_0_SIDE		0x044
#define I2O_QUEUE_CONTROL_REG_PCI_0_SIDE			0x050
#define I2O_QUEUE_BASE_ADDR_REG_PCI_0_SIDE			0x054
#define I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE		0x060
#define I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE		0x064
#define I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE		0x068
#define I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE		0x06C
#define I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_0_SIDE		0x070
#define I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_0_SIDE		0x074
#define I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_0_SIDE		0x0F8
#define I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_0_SIDE		0x0FC

#define I2O_INBOUND_MESSAGE_REG0_PCI_1_SIDE			0x090
#define I2O_INBOUND_MESSAGE_REG1_PCI_1_SIDE				0x094
#define I2O_OUTBOUND_MESSAGE_REG0_PCI_1_SIDE				0x098
#define I2O_OUTBOUND_MESSAGE_REG1_PCI_1_SIDE				0x09C
#define I2O_INBOUND_DOORBELL_REG_PCI_1_SIDE				0x0A0
#define I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE		0x0A4
#define I2O_INBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE			0x0A8
#define I2O_OUTBOUND_DOORBELL_REG_PCI_1_SIDE				0x0AC
#define I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_1_SIDE		0x0B0
#define I2O_OUTBOUND_INTERRUPT_MASK_REG_PCI_1_SIDE		0x0B4
#define I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE		0x0C0
#define I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_PCI_1_SIDE		0x0C4
#define I2O_QUEUE_CONTROL_REG_PCI_1_SIDE			0x0D0
#define I2O_QUEUE_BASE_ADDR_REG_PCI_1_SIDE			0x0D4
#define I2O_INBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE		0x0E0
#define I2O_INBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE		0x0E4
#define I2O_INBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE		0x0E8
#define I2O_INBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE		0x0EC
#define I2O_OUTBOUND_FREE_HEAD_POINTER_REG_PCI_1_SIDE		0x0F0
#define I2O_OUTBOUND_FREE_TAIL_POINTER_REG_PCI_1_SIDE		0x0F4
#define I2O_OUTBOUND_POST_HEAD_POINTER_REG_PCI_1_SIDE		0x078
#define I2O_OUTBOUND_POST_TAIL_POINTER_REG_PCI_1_SIDE		0x07C

#define I2O_INBOUND_MESSAGE_REG0_CPU0_SIDE			0x1C10
#define I2O_INBOUND_MESSAGE_REG1_CPU0_SIDE				0x1C14
#define I2O_OUTBOUND_MESSAGE_REG0_CPU0_SIDE				0x1C18
#define I2O_OUTBOUND_MESSAGE_REG1_CPU0_SIDE				0x1C1C
#define I2O_INBOUND_DOORBELL_REG_CPU0_SIDE				0x1C20
#define I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE			0x1C24
#define I2O_INBOUND_INTERRUPT_MASK_REG_CPU0_SIDE			0x1C28
#define I2O_OUTBOUND_DOORBELL_REG_CPU0_SIDE				0x1C2C
#define I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU0_SIDE		0x1C30
#define I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU0_SIDE		0x1C34
#define I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE		0x1C40
#define I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU0_SIDE		0x1C44
#define I2O_QUEUE_CONTROL_REG_CPU0_SIDE				0x1C50
#define I2O_QUEUE_BASE_ADDR_REG_CPU0_SIDE				0x1C54
#define I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE		0x1C60
#define I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE		0x1C64
#define I2O_INBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE		0x1C68
#define I2O_INBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE		0x1C6C
#define I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU0_SIDE		0x1C70
#define I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU0_SIDE		0x1C74
#define I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU0_SIDE		0x1CF8
#define I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU0_SIDE		0x1CFC
#define I2O_INBOUND_MESSAGE_REG0_CPU1_SIDE			0x1C90
#define I2O_INBOUND_MESSAGE_REG1_CPU1_SIDE				0x1C94
#define I2O_OUTBOUND_MESSAGE_REG0_CPU1_SIDE				0x1C98
#define I2O_OUTBOUND_MESSAGE_REG1_CPU1_SIDE				0x1C9C
#define I2O_INBOUND_DOORBELL_REG_CPU1_SIDE				0x1CA0
#define I2O_INBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE			0x1CA4
#define I2O_INBOUND_INTERRUPT_MASK_REG_CPU1_SIDE			0x1CA8
#define I2O_OUTBOUND_DOORBELL_REG_CPU1_SIDE				0x1CAC
#define I2O_OUTBOUND_INTERRUPT_CAUSE_REG_CPU1_SIDE		0x1CB0
#define I2O_OUTBOUND_INTERRUPT_MASK_REG_CPU1_SIDE		0x1CB4
#define I2O_INBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE		0x1CC0
#define I2O_OUTBOUND_QUEUE_PORT_VIRTUAL_REG_CPU1_SIDE		0x1CC4
#define I2O_QUEUE_CONTROL_REG_CPU1_SIDE				0x1CD0
#define I2O_QUEUE_BASE_ADDR_REG_CPU1_SIDE				0x1CD4
#define I2O_INBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE		0x1CE0
#define I2O_INBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE		0x1CE4
#define I2O_INBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE		0x1CE8
#define I2O_INBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE		0x1CEC
#define I2O_OUTBOUND_FREE_HEAD_POINTER_REG_CPU1_SIDE		0x1CF0
#define I2O_OUTBOUND_FREE_TAIL_POINTER_REG_CPU1_SIDE		0x1CF4
#define I2O_OUTBOUND_POST_HEAD_POINTER_REG_CPU1_SIDE		0x1C78
#define I2O_OUTBOUND_POST_TAIL_POINTER_REG_CPU1_SIDE		0x1C7C


/****************************************/
/* Communication Unit Registers		*/
/****************************************/
/*
#define ETHERNET_0_ADDRESS_CONTROL_LOW						0xf200
#define ETHERNET_0_ADDRESS_CONTROL_HIGH			    0xf204
#define ETHERNET_0_RECEIVE_BUFFER_PCI_HIGH_ADDRESS	    0xf208
#define ETHERNET_0_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS	    0xf20c
#define ETHERNET_0_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf210
#define ETHERNET_0_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf214
#define ETHERNET_0_HASH_TABLE_PCI_HIGH_ADDRESS		    0xf218
#define ETHERNET_1_ADDRESS_CONTROL_LOW			    0xf220
#define ETHERNET_1_ADDRESS_CONTROL_HIGH			    0xf224
#define ETHERNET_1_RECEIVE_BUFFER_PCI_HIGH_ADDRESS	    0xf228
#define ETHERNET_1_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS	    0xf22c
#define ETHERNET_1_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf230
#define ETHERNET_1_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf234
#define ETHERNET_1_HASH_TABLE_PCI_HIGH_ADDRESS		    0xf238
#define ETHERNET_2_ADDRESS_CONTROL_LOW			    0xf240
#define ETHERNET_2_ADDRESS_CONTROL_HIGH			    0xf244
#define ETHERNET_2_RECEIVE_BUFFER_PCI_HIGH_ADDRESS	    0xf248
#define ETHERNET_2_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS	    0xf24c
#define ETHERNET_2_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf250
#define ETHERNET_2_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf254
#define ETHERNET_2_HASH_TABLE_PCI_HIGH_ADDRESS		    0xf258
 */
#define MPSC_0_ADDRESS_CONTROL_LOW			    0xf280
#define MPSC_0_ADDRESS_CONTROL_HIGH			    0xf284
#define MPSC_0_RECEIVE_BUFFER_PCI_HIGH_ADDRESS		    0xf288
#define MPSC_0_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS		    0xf28c
#define MPSC_0_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf290
#define MPSC_0_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf294
#define MPSC_1_ADDRESS_CONTROL_LOW			    0xf2c0
#define MPSC_1_ADDRESS_CONTROL_HIGH			    0xf2c4
#define MPSC_1_RECEIVE_BUFFER_PCI_HIGH_ADDRESS		    0xf2c8
#define MPSC_1_TRANSMIT_BUFFER_PCI_HIGH_ADDRESS		    0xf2cc
#define MPSC_1_RECEIVE_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf2d0
#define MPSC_1_TRANSMIT_DESCRIPTOR_PCI_HIGH_ADDRESS	    0xf2d4
 /*#define SERIAL_INIT_PCI_HIGH_ADDRESS			       0xf3201 */
#define COMM_UNIT_ARBITER_CONTROL			    0xf300
#define COMM_UNIT_CROSS_BAR_TIMEOUT			    0xf304
#define COMM_UNIT_INTERRUPT_CAUSE			    0xf310
#define COMM_UNIT_INTERRUPT_MASK			    0xf314
#define COMM_UNIT_ERROR_ADDRESS				    0xf314
/****************************************/
/*    Serial Initialization registers	*/
/****************************************/

 /*#define SERIAL_INIT_LAST_DATA					0xf3241 */
 /*#define SERIAL_INIT_STATUS_AND_CONTROL			0xf3281 */
#define SERIAL_INIT_LAST_DATA						0xf324
#define SERIAL_INIT_CONTROL						0xf328
#define SERIAL_INIT_STATUS						0xf32c


/****************************************/
/*	  Ethernet Unit Registers		*/
/****************************************/

#define ETH_PHY_ADDR_REG			0x2000
#define ETH_SMI_REG					0x2004
#define ETH_UNIT_DEFAULT_ADDR_REG		0x2008
#define ETH_UNIT_DEFAULTID_REG			0x200c
#define ETH_UNIT_INTERRUPT_CAUSE_REG	0x2080
#define ETH_UNIT_INTERRUPT_MASK_REG	0x2084
#define ETH_UNIT_INTERNAL_USE_REG		0x24fc
#define ETH_UNIT_ERROR_ADDR_REG			0x2094
#define ETH_BAR_0					0x2200
#define ETH_BAR_1					0x2208
#define ETH_BAR_2					0x2210
#define ETH_BAR_3					0x2218
#define ETH_BAR_4					0x2220
#define ETH_BAR_5					0x2228
#define ETH_SIZE_REG_0				0x2204
#define ETH_SIZE_REG_1				0x220c
#define ETH_SIZE_REG_2				0x2214
#define ETH_SIZE_REG_3				0x221c
#define ETH_SIZE_REG_4				0x2224
#define ETH_SIZE_REG_5					0x222c
#define ETH_HEADERS_RETARGET_BASE_REG			0x2230
#define ETH_HEADERS_RETARGET_CONTROL_REG	0x2234
#define ETH_HIGH_ADDR_REMAP_REG_0		0x2280
#define ETH_HIGH_ADDR_REMAP_REG_1		0x2284
#define ETH_HIGH_ADDR_REMAP_REG_2		0x2288
#define ETH_HIGH_ADDR_REMAP_REG_3			0x228c
#define ETH_BASE_ADDR_ENABLE_REG			0x2290
#define ETH_ACCESS_PROTECTION_REG(port)			(0x2294 + (port<<2))
#define ETH_MIB_COUNTERS_BASE(port)			(0x3000 + (port<<7))
#define ETH_PORT_CONFIG_REG(port)				(0x2400 + (port<<10))
#define ETH_PORT_CONFIG_EXTEND_REG(port)		(0x2404 + (port<<10))
#define ETH_MII_SERIAL_PARAMETRS_REG(port)		(0x2408 + (port<<10))
#define ETH_GMII_SERIAL_PARAMETRS_REG(port)		(0x240c + (port<<10))
#define ETH_VLAN_ETHERTYPE_REG(port)			(0x2410 + (port<<10))
#define ETH_MAC_ADDR_LOW(port)					(0x2414 + (port<<10))
#define ETH_MAC_ADDR_HIGH(port)					(0x2418 + (port<<10))
#define ETH_SDMA_CONFIG_REG(port)				(0x241c + (port<<10))
#define ETH_DSCP_0(port)					(0x2420 + (port<<10))
#define ETH_DSCP_1(port)					(0x2424 + (port<<10))
#define ETH_DSCP_2(port)					(0x2428 + (port<<10))
#define ETH_DSCP_3(port)					(0x242c + (port<<10))
#define ETH_DSCP_4(port)					(0x2430 + (port<<10))
#define ETH_DSCP_5(port)					(0x2434 + (port<<10))
#define ETH_DSCP_6(port)					(0x2438 + (port<<10))
#define ETH_PORT_SERIAL_CONTROL_REG(port)		(0x243c + (port<<10))
#define ETH_VLAN_PRIORITY_TAG_TO_PRIORITY(port)		(0x2440 + (port<<10))
#define ETH_PORT_STATUS_REG(port)				(0x2444 + (port<<10))
#define ETH_TRANSMIT_QUEUE_COMMAND_REG(port)	(0x2448 + (port<<10))
#define ETH_TX_QUEUE_FIXED_PRIORITY(port)		(0x244c + (port<<10))
#define ETH_PORT_TX_TOKEN_BUCKET_RATE_CONFIG(port)		(0x2450 + (port<<10))
#define ETH_MAXIMUM_TRANSMIT_UNIT(port)				(0x2458 + (port<<10))
#define ETH_PORT_MAXIMUM_TOKEN_BUCKET_SIZE(port)		(0x245c + (port<<10))
#define ETH_INTERRUPT_CAUSE_REG(port)				(0x2460 + (port<<10))
#define ETH_INTERRUPT_CAUSE_EXTEND_REG(port)			(0x2464 + (port<<10))
#define ETH_INTERRUPT_MASK_REG(port)				(0x2468 + (port<<10))
#define ETH_INTERRUPT_EXTEND_MASK_REG(port)			(0x246c + (port<<10))
#define ETH_RX_FIFO_URGENT_THRESHOLD_REG(port)			(0x2470 + (port<<10))
#define ETH_TX_FIFO_URGENT_THRESHOLD_REG(port)			(0x2474 + (port<<10))
#define ETH_RX_MINIMAL_FRAME_SIZE_REG(port)			(0x247c + (port<<10))
#define ETH_RX_DISCARDED_FRAMES_COUNTER(port)			(0x2484 + (port<<10)
#define ETH_PORT_DEBUG_0_REG(port)					(0x248c + (port<<10))
#define ETH_PORT_DEBUG_1_REG(port)					(0x2490 + (port<<10))
#define ETH_PORT_INTERNAL_ADDR_ERROR_REG(port)			(0x2494 + (port<<10))
#define ETH_INTERNAL_USE_REG(port)					(0x24fc + (port<<10))
#define ETH_RECEIVE_QUEUE_COMMAND_REG(port)			(0x2680 + (port<<10))
#define ETH_CURRENT_SERVED_TX_DESC_PTR(port)			(0x2684 + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_0(port)			(0x260c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_1(port)			(0x261c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_2(port)			(0x262c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_3(port)			(0x263c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_4(port)			(0x264c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_5(port)			(0x265c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_6(port)			(0x266c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_7(port)			(0x267c + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_0(port)			(0x26c0 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_1(port)			(0x26c4 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_2(port)			(0x26c8 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_3(port)			(0x26cc + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_4(port)			(0x26d0 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_5(port)			(0x26d4 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_6(port)			(0x26d8 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_7(port)			(0x26dc + (port<<10))
#define ETH_TX_QUEUE_0_TOKEN_BUCKET_COUNT(port)			(0x2700 + (port<<10))
#define ETH_TX_QUEUE_1_TOKEN_BUCKET_COUNT(port)			(0x2710 + (port<<10))
#define ETH_TX_QUEUE_2_TOKEN_BUCKET_COUNT(port)			(0x2720 + (port<<10))
#define ETH_TX_QUEUE_3_TOKEN_BUCKET_COUNT(port)			(0x2730 + (port<<10))
#define ETH_TX_QUEUE_4_TOKEN_BUCKET_COUNT(port)			(0x2740 + (port<<10))
#define ETH_TX_QUEUE_5_TOKEN_BUCKET_COUNT(port)			(0x2750 + (port<<10))
#define ETH_TX_QUEUE_6_TOKEN_BUCKET_COUNT(port)			(0x2760 + (port<<10))
#define ETH_TX_QUEUE_7_TOKEN_BUCKET_COUNT(port)			(0x2770 + (port<<10))
#define ETH_TX_QUEUE_0_TOKEN_BUCKET_CONFIG(port)		(0x2704 + (port<<10))
#define ETH_TX_QUEUE_1_TOKEN_BUCKET_CONFIG(port)		(0x2714 + (port<<10))
#define ETH_TX_QUEUE_2_TOKEN_BUCKET_CONFIG(port)		(0x2724 + (port<<10))
#define ETH_TX_QUEUE_3_TOKEN_BUCKET_CONFIG(port)		(0x2734 + (port<<10))
#define ETH_TX_QUEUE_4_TOKEN_BUCKET_CONFIG(port)		(0x2744 + (port<<10))
#define ETH_TX_QUEUE_5_TOKEN_BUCKET_CONFIG(port)		(0x2754 + (port<<10))
#define ETH_TX_QUEUE_6_TOKEN_BUCKET_CONFIG(port)		(0x2764 + (port<<10))
#define ETH_TX_QUEUE_7_TOKEN_BUCKET_CONFIG(port)		(0x2774 + (port<<10))
#define ETH_TX_QUEUE_0_ARBITER_CONFIG(port)			(0x2708 + (port<<10))
#define ETH_TX_QUEUE_1_ARBITER_CONFIG(port)			(0x2718 + (port<<10))
#define ETH_TX_QUEUE_2_ARBITER_CONFIG(port)			(0x2728 + (port<<10))
#define ETH_TX_QUEUE_3_ARBITER_CONFIG(port)			(0x2738 + (port<<10))
#define ETH_TX_QUEUE_4_ARBITER_CONFIG(port)			(0x2748 + (port<<10))
#define ETH_TX_QUEUE_5_ARBITER_CONFIG(port)			(0x2758 + (port<<10))
#define ETH_TX_QUEUE_6_ARBITER_CONFIG(port)			(0x2768 + (port<<10))
#define ETH_TX_QUEUE_7_ARBITER_CONFIG(port)			(0x2778 + (port<<10))
#define ETH_PORT_TX_TOKEN_BUCKET_COUNT(port)			(0x2780 + (port<<10))
#define ETH_DA_FILTER_SPECIAL_MULTICAST_TABLE_BASE(port)	(0x3400 + (port<<10))
#define ETH_DA_FILTER_OTHER_MULTICAST_TABLE_BASE(port)		(0x3500 + (port<<10))
#define ETH_DA_FILTER_UNICAST_TABLE_BASE(port)			(0x3600 + (port<<10))

/****************************************/
/* Cunit Debug	(for internal use)     */
/****************************************/

#define CUNIT_ADDRESS					    0xf340
#define CUNIT_COMMAND_AND_ID				    0xf344
#define CUNIT_WRITE_DATA_LOW				    0xf348
#define CUNIT_WRITE_DATA_HIGH				    0xf34c
#define CUNIT_WRITE_BYTE_ENABLE				    0xf358
#define CUNIT_READ_DATA_LOW				    0xf350
#define CUNIT_READ_DATA_HIGH				    0xf354
#define CUNIT_READ_ID					    0xf35c

/****************************************/
/* Fast Ethernet Unit Registers		*/
/****************************************/

/****************************************/
/*	  Ethernet Unit Registers		*/
/****************************************/

#define ETH_PHY_ADDR_REG				0x2000
#define ETH_SMI_REG						0x2004
#define ETH_UNIT_DEFAULT_ADDR_REG			0x2008
#define ETH_UNIT_DEFAULTID_REG				0x200c
#define ETH_UNIT_INTERRUPT_CAUSE_REG			0x2080
#define ETH_UNIT_INTERRUPT_MASK_REG		0x2084
#define ETH_UNIT_INTERNAL_USE_REG			0x24fc
#define ETH_UNIT_ERROR_ADDR_REG				0x2094
#define ETH_BAR_0						0x2200
#define ETH_BAR_1						0x2208
#define ETH_BAR_2						0x2210
#define ETH_BAR_3						0x2218
#define ETH_BAR_4						0x2220
#define ETH_BAR_5						0x2228
#define ETH_SIZE_REG_0						0x2204
#define ETH_SIZE_REG_1						0x220c
#define ETH_SIZE_REG_2						0x2214
#define ETH_SIZE_REG_3						0x221c
#define ETH_SIZE_REG_4						0x2224
#define ETH_SIZE_REG_5						0x222c
#define ETH_HEADERS_RETARGET_BASE_REG			0x2230
#define ETH_HEADERS_RETARGET_CONTROL_REG	0x2234
#define ETH_HIGH_ADDR_REMAP_REG_0			0x2280
#define ETH_HIGH_ADDR_REMAP_REG_1		0x2284
#define ETH_HIGH_ADDR_REMAP_REG_2		0x2288
#define ETH_HIGH_ADDR_REMAP_REG_3			0x228c
#define ETH_BASE_ADDR_ENABLE_REG			0x2290
#define ETH_ACCESS_PROTECTION_REG(port)			(0x2294 + (port<<2))
#define ETH_MIB_COUNTERS_BASE(port)			(0x3000 + (port<<7))
#define ETH_PORT_CONFIG_REG(port)			(0x2400 + (port<<10))
#define ETH_PORT_CONFIG_EXTEND_REG(port)		(0x2404 + (port<<10))
#define ETH_MII_SERIAL_PARAMETRS_REG(port)		(0x2408 + (port<<10))
#define ETH_GMII_SERIAL_PARAMETRS_REG(port)		(0x240c + (port<<10))
#define ETH_VLAN_ETHERTYPE_REG(port)			(0x2410 + (port<<10))
#define ETH_MAC_ADDR_LOW(port)					(0x2414 + (port<<10))
#define ETH_MAC_ADDR_HIGH(port)					(0x2418 + (port<<10))
#define ETH_SDMA_CONFIG_REG(port)			(0x241c + (port<<10))
#define ETH_DSCP_0(port)					(0x2420 + (port<<10))
#define ETH_DSCP_1(port)					(0x2424 + (port<<10))
#define ETH_DSCP_2(port)					(0x2428 + (port<<10))
#define ETH_DSCP_3(port)					(0x242c + (port<<10))
#define ETH_DSCP_4(port)					(0x2430 + (port<<10))
#define ETH_DSCP_5(port)					(0x2434 + (port<<10))
#define ETH_DSCP_6(port)					(0x2438 + (port<<10))
#define ETH_PORT_SERIAL_CONTROL_REG(port)	(0x243c + (port<<10))
#define ETH_VLAN_PRIORITY_TAG_TO_PRIORITY(port)		(0x2440 + (port<<10))
#define ETH_PORT_STATUS_REG(port)				(0x2444 + (port<<10))
#define ETH_TRANSMIT_QUEUE_COMMAND_REG(port)	(0x2448 + (port<<10))
#define ETH_TX_QUEUE_FIXED_PRIORITY(port)		(0x244c + (port<<10))
#define ETH_PORT_TX_TOKEN_BUCKET_RATE_CONFIG(port)	   (0x2450 + (port<<10))
#define ETH_MAXIMUM_TRANSMIT_UNIT(port)			(0x2458 + (port<<10))
#define ETH_PORT_MAXIMUM_TOKEN_BUCKET_SIZE(port)	   (0x245c + (port<<10))
#define ETH_INTERRUPT_CAUSE_REG(port)			(0x2460 + (port<<10))
#define ETH_INTERRUPT_CAUSE_EXTEND_REG(port)		(0x2464 + (port<<10))
#define ETH_INTERRUPT_MASK_REG(port)			(0x2468 + (port<<10))
#define ETH_INTERRUPT_EXTEND_MASK_REG(port)		(0x246c + (port<<10))
#define ETH_RX_FIFO_URGENT_THRESHOLD_REG(port)	(0x2470 + (port<<10))
#define ETH_TX_FIFO_URGENT_THRESHOLD_REG(port)	(0x2474 + (port<<10))
#define ETH_RX_MINIMAL_FRAME_SIZE_REG(port)		(0x247c + (port<<10))
#define ETH_RX_DISCARDED_FRAMES_COUNTER(port)	(0x2484 + (port<<10)
#define ETH_PORT_DEBUG_0_REG(port)				(0x248c + (port<<10))
#define ETH_PORT_DEBUG_1_REG(port)				(0x2490 + (port<<10))
#define ETH_PORT_INTERNAL_ADDR_ERROR_REG(port)	(0x2494 + (port<<10))
#define ETH_INTERNAL_USE_REG(port)				(0x24fc + (port<<10))
#define ETH_RECEIVE_QUEUE_COMMAND_REG(port)	(0x2680 + (port<<10))
#define ETH_CURRENT_SERVED_TX_DESC_PTR(port)		(0x2684 + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_0(port)		(0x260c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_1(port)	(0x261c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_2(port)		(0x262c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_3(port)		(0x263c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_4(port)		(0x264c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_5(port)		(0x265c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_6(port)		(0x266c + (port<<10))
#define ETH_RX_CURRENT_QUEUE_DESC_PTR_7(port)		(0x267c + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_0(port)	(0x26c0 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_1(port)	(0x26c4 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_2(port)	(0x26c8 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_3(port)		(0x26cc + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_4(port)		(0x26d0 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_5(port)		(0x26d4 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_6(port)		(0x26d8 + (port<<10))
#define ETH_TX_CURRENT_QUEUE_DESC_PTR_7(port)		(0x26dc + (port<<10))
#define ETH_TX_QUEUE_0_TOKEN_BUCKET_COUNT(port)		   (0x2700 + (port<<10))
#define ETH_TX_QUEUE_1_TOKEN_BUCKET_COUNT(port)		   (0x2710 + (port<<10))
#define ETH_TX_QUEUE_2_TOKEN_BUCKET_COUNT(port)		   (0x2720 + (port<<10))
#define ETH_TX_QUEUE_3_TOKEN_BUCKET_COUNT(port)		   (0x2730 + (port<<10))
#define ETH_TX_QUEUE_4_TOKEN_BUCKET_COUNT(port)		   (0x2740 + (port<<10))
#define ETH_TX_QUEUE_5_TOKEN_BUCKET_COUNT(port)		   (0x2750 + (port<<10))
#define ETH_TX_QUEUE_6_TOKEN_BUCKET_COUNT(port)		   (0x2760 + (port<<10))
#define ETH_TX_QUEUE_7_TOKEN_BUCKET_COUNT(port)		   (0x2770 + (port<<10))
#define ETH_TX_QUEUE_0_TOKEN_BUCKET_CONFIG(port)	   (0x2704 + (port<<10))
#define ETH_TX_QUEUE_1_TOKEN_BUCKET_CONFIG(port)	   (0x2714 + (port<<10))
#define ETH_TX_QUEUE_2_TOKEN_BUCKET_CONFIG(port)	   (0x2724 + (port<<10))
#define ETH_TX_QUEUE_3_TOKEN_BUCKET_CONFIG(port)	   (0x2734 + (port<<10))
#define ETH_TX_QUEUE_4_TOKEN_BUCKET_CONFIG(port)	   (0x2744 + (port<<10))
#define ETH_TX_QUEUE_5_TOKEN_BUCKET_CONFIG(port)	   (0x2754 + (port<<10))
#define ETH_TX_QUEUE_6_TOKEN_BUCKET_CONFIG(port)	   (0x2764 + (port<<10))
#define ETH_TX_QUEUE_7_TOKEN_BUCKET_CONFIG(port)	   (0x2774 + (port<<10))
#define ETH_TX_QUEUE_0_ARBITER_CONFIG(port)		(0x2708 + (port<<10))
#define ETH_TX_QUEUE_1_ARBITER_CONFIG(port)		(0x2718 + (port<<10))
#define ETH_TX_QUEUE_2_ARBITER_CONFIG(port)		(0x2728 + (port<<10))
#define ETH_TX_QUEUE_3_ARBITER_CONFIG(port)		(0x2738 + (port<<10))
#define ETH_TX_QUEUE_4_ARBITER_CONFIG(port)		(0x2748 + (port<<10))
#define ETH_TX_QUEUE_5_ARBITER_CONFIG(port)		(0x2758 + (port<<10))
#define ETH_TX_QUEUE_6_ARBITER_CONFIG(port)		(0x2768 + (port<<10))
#define ETH_TX_QUEUE_7_ARBITER_CONFIG(port)		(0x2778 + (port<<10))
#define ETH_PORT_TX_TOKEN_BUCKET_COUNT(port)		(0x2780 + (port<<10))
#define ETH_DA_FILTER_SPECIAL_MULTICAST_TABLE_BASE(port)   (0x3400 + (port<<10))
#define ETH_DA_FILTER_OTHER_MULTICAST_TABLE_BASE(port)	   (0x3500 + (port<<10))
#define ETH_DA_FILTER_UNICAST_TABLE_BASE(port)		(0x3600 + (port<<10))

/* Compat with interrupts.c */
#define ETHERNET0_INTERRUPT_CAUSE_REGISTER      ETH_INTERRUPT_CAUSE_REG(0)
#define ETHERNET1_INTERRUPT_CAUSE_REGISTER      ETH_INTERRUPT_CAUSE_REG(1)
#define ETHERNET2_INTERRUPT_CAUSE_REGISTER      ETH_INTERRUPT_CAUSE_REG(2)

#define ETHERNET0_INTERRUPT_MASK_REGISTER       ETH_INTERRUPT_MASK_REG(0)
#define ETHERNET1_INTERRUPT_MASK_REGISTER       ETH_INTERRUPT_MASK_REG(1)
#define ETHERNET2_INTERRUPT_MASK_REGISTER       ETH_INTERRUPT_MASK_REG(2)

/* Ethernet GT64260 */
/*
#define ETHERNET_PHY_ADDRESS_REGISTER					0x2000
#define ETHERNET_SMI_REGISTER							0x2010
*/
/* Ethernet 0 */
/*
#define ETHERNET0_PORT_CONFIGURATION_REGISTER				0x2400
#define ETHERNET0_PORT_CONFIGURATION_EXTEND_REGISTER		0x2408
#define ETHERNET0_PORT_COMMAND_REGISTER					0x2410
#define ETHERNET0_PORT_STATUS_REGISTER					0x2418
#define ETHERNET0_SERIAL_PARAMETRS_REGISTER				0x2420
#define ETHERNET0_HASH_TABLE_POINTER_REGISTER				0x2428
#define ETHERNET0_FLOW_CONTROL_SOURCE_ADDRESS_LOW		0x2430
#define ETHERNET0_FLOW_CONTROL_SOURCE_ADDRESS_HIGH		0x2438
#define ETHERNET0_SDMA_CONFIGURATION_REGISTER			0x2440
#define ETHERNET0_SDMA_COMMAND_REGISTER					0x2448
#define ETHERNET0_INTERRUPT_CAUSE_REGISTER				0x2450
#define ETHERNET0_INTERRUPT_MASK_REGISTER				0x2458
#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER0				0x2480
#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER1				0x2484
#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER2				0x2488
#define ETHERNET0_FIRST_RX_DESCRIPTOR_POINTER3				0x248c
#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER0		0x24a0
#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER1		0x24a4
#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER2		0x24a8
#define ETHERNET0_CURRENT_RX_DESCRIPTOR_POINTER3		0x24ac
#define ETHERNET0_CURRENT_TX_DESCRIPTOR_POINTER0		0x24e0
#define ETHERNET0_CURRENT_TX_DESCRIPTOR_POINTER1		0x24e4
#define ETHERNET0_MIB_COUNTER_BASE					0x2500
*/
/* Ethernet 1 */
/*
#define ETHERNET1_PORT_CONFIGURATION_REGISTER				0x2800
#define ETHERNET1_PORT_CONFIGURATION_EXTEND_REGISTER		0x2808
#define ETHERNET1_PORT_COMMAND_REGISTER					0x2810
#define ETHERNET1_PORT_STATUS_REGISTER					0x2818
#define ETHERNET1_SERIAL_PARAMETRS_REGISTER				0x2820
#define ETHERNET1_HASH_TABLE_POINTER_REGISTER				0x2828
#define ETHERNET1_FLOW_CONTROL_SOURCE_ADDRESS_LOW		0x2830
#define ETHERNET1_FLOW_CONTROL_SOURCE_ADDRESS_HIGH		0x2838
#define ETHERNET1_SDMA_CONFIGURATION_REGISTER			0x2840
#define ETHERNET1_SDMA_COMMAND_REGISTER					0x2848
#define ETHERNET1_INTERRUPT_CAUSE_REGISTER				0x2850
#define ETHERNET1_INTERRUPT_MASK_REGISTER				0x2858
#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER0				0x2880
#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER1				0x2884
#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER2				0x2888
#define ETHERNET1_FIRST_RX_DESCRIPTOR_POINTER3				0x288c
#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER0		0x28a0
#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER1		0x28a4
#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER2		0x28a8
#define ETHERNET1_CURRENT_RX_DESCRIPTOR_POINTER3		0x28ac
#define ETHERNET1_CURRENT_TX_DESCRIPTOR_POINTER0		0x28e0
#define ETHERNET1_CURRENT_TX_DESCRIPTOR_POINTER1		0x28e4
#define ETHERNET1_MIB_COUNTER_BASE					0x2900
*/
/* Ethernet 2 */
/*
#define ETHERNET2_PORT_CONFIGURATION_REGISTER				0x2c00
#define ETHERNET2_PORT_CONFIGURATION_EXTEND_REGISTER		0x2c08
#define ETHERNET2_PORT_COMMAND_REGISTER					0x2c10
#define ETHERNET2_PORT_STATUS_REGISTER					0x2c18
#define ETHERNET2_SERIAL_PARAMETRS_REGISTER				0x2c20
#define ETHERNET2_HASH_TABLE_POINTER_REGISTER				0x2c28
#define ETHERNET2_FLOW_CONTROL_SOURCE_ADDRESS_LOW		0x2c30
#define ETHERNET2_FLOW_CONTROL_SOURCE_ADDRESS_HIGH		0x2c38
#define ETHERNET2_SDMA_CONFIGURATION_REGISTER			0x2c40
#define ETHERNET2_SDMA_COMMAND_REGISTER					0x2c48
#define ETHERNET2_INTERRUPT_CAUSE_REGISTER				0x2c50
#define ETHERNET2_INTERRUPT_MASK_REGISTER				0x2c58
#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER0				0x2c80
#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER1				0x2c84
#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER2				0x2c88
#define ETHERNET2_FIRST_RX_DESCRIPTOR_POINTER3				0x2c8c
#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER0		0x2ca0
#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER1		0x2ca4
#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER2		0x2ca8
#define ETHERNET2_CURRENT_RX_DESCRIPTOR_POINTER3		0x2cac
#define ETHERNET2_CURRENT_TX_DESCRIPTOR_POINTER0		0x2ce0
#define ETHERNET2_CURRENT_TX_DESCRIPTOR_POINTER1		0x2ce4
#define ETHERNET2_MIB_COUNTER_BASE					0x2d00
*/

/****************************************/
/* SDMA Registers			*/
/****************************************/

#define SDMA_GROUP_CONFIGURATION_REGISTER			0xb1f0
#define CHANNEL0_CONFIGURATION_REGISTER				0x4000
#define CHANNEL0_COMMAND_REGISTER				0x4008
#define CHANNEL0_RX_CMD_STATUS					0x4800
#define CHANNEL0_RX_PACKET_AND_BUFFER_SIZES		    0x4804
#define CHANNEL0_RX_BUFFER_POINTER				0x4808
#define CHANNEL0_RX_NEXT_POINTER				0x480c
#define CHANNEL0_CURRENT_RX_DESCRIPTOR_POINTER		0x4810
#define CHANNEL0_TX_CMD_STATUS					0x4C00
#define CHANNEL0_TX_PACKET_SIZE					0x4C04
#define CHANNEL0_TX_BUFFER_POINTER				0x4C08
#define CHANNEL0_TX_NEXT_POINTER				0x4C0c
#define CHANNEL0_CURRENT_TX_DESCRIPTOR_POINTER		0x4c10
#define CHANNEL0_FIRST_TX_DESCRIPTOR_POINTER			0x4c14
/*
#define CHANNEL1_CONFIGURATION_REGISTER				0x5000
#define CHANNEL1_COMMAND_REGISTER				0x5008
#define CHANNEL1_RX_CMD_STATUS					0x5800
#define CHANNEL1_RX_PACKET_AND_BUFFER_SIZES		    0x5804
#define CHANNEL1_RX_BUFFER_POINTER				0x5808
#define CHANNEL1_RX_NEXT_POINTER				0x580c
#define CHANNEL1_TX_CMD_STATUS					0x5C00
#define CHANNEL1_TX_PACKET_SIZE					0x5C04
#define CHANNEL1_TX_BUFFER_POINTER				0x5C08
#define CHANNEL1_TX_NEXT_POINTER				0x5C0c
#define CHANNEL1_CURRENT_RX_DESCRIPTOR_POINTER		0x5810
#define CHANNEL1_CURRENT_TX_DESCRIPTOR_POINTER		0x5c10
#define CHANNEL1_FIRST_TX_DESCRIPTOR_POINTER			0x5c14
#define CHANNEL2_CONFIGURATION_REGISTER				0x6000
#define CHANNEL2_COMMAND_REGISTER				0x6008
#define CHANNEL2_RX_CMD_STATUS					0x6800
#define CHANNEL2_RX_PACKET_AND_BUFFER_SIZES		    0x6804
#define CHANNEL2_RX_BUFFER_POINTER				0x6808
#define CHANNEL2_RX_NEXT_POINTER				0x680c
#define CHANNEL2_CURRENT_RX_DESCRIPTOR_POINTER		0x6810
#define CHANNEL2_TX_CMD_STATUS					0x6C00
#define CHANNEL2_TX_PACKET_SIZE					0x6C04
#define CHANNEL2_TX_BUFFER_POINTER				0x6C08
#define CHANNEL2_TX_NEXT_POINTER				0x6C0c
#define CHANNEL2_CURRENT_RX_DESCRIPTOR_POINTER		0x6810
#define CHANNEL2_CURRENT_TX_DESCRIPTOR_POINTER			0x6c10
#define CHANNEL2_FIRST_TX_DESCRIPTOR_POINTER			0x6c14
*/
/* SDMA Interrupt */
/*
#define SDMA_CAUSE							0xb820
#define SDMA_MASK							0xb8a0
*/
/***************************************/
/*	    SDMA Registers	       */
/***************************************/

#define SDMA_CONFIG_REG(channel)					(0x4000 + (channel<<13))
#define SDMA_COMMAND_REG(channel)					(0x4008 + (channel<<13))
#define SDMA_CURRENT_RX_DESCRIPTOR_POINTER(channel)		(0x4810 + (channel<<13))
#define SDMA_CURRENT_TX_DESCRIPTOR_POINTER(channel)	(0x4c10 + (channel<<13))
#define SDMA_FIRST_TX_DESCRIPTOR_POINTER(channel)	(0x4c14 + (channel<<13))

#define SDMA_CAUSE_REG							0xb800
#define SDMA_MASK_REG							0xb880

/****************************************/
/* Baude Rate Generators Registers	*/
/****************************************/

/* BRG 0 */
#define BRG0_CONFIGURATION_REGISTER		0xb200
#define BRG0_BAUDE_TUNING_REGISTER			 0xb204

/* BRG 1 */
#define BRG1_CONFIGURATION_REGISTER			0xb208
#define BRG1_BAUDE_TUNING_REGISTER			 0xb20c

/* BRG 2 */
#define BRG2_CONFIGURATION_REGISTER			0xb210
#define BRG2_BAUDE_TUNING_REGISTER			 0xb214

/* BRG Interrupts */
#define BRG_CAUSE_REGISTER					0xb834
#define BRG_MASK_REGISTER					0xb8b4
#define BRG_CONFIG_REG(brg)					(0xb200 + (brg<<3))
#define BRG_BAUDE_TUNING_REG(brg)				(0xb208 + (brg<<3))
#define BRG_CAUSE_REG						BRG_CAUSE_REGISTER  /*0xb8341 */
#define BRG_MASK_REG						BRG_MASK_REGISTER  /*0xb8b41 */

/* MISC */

#define MAIN_ROUTING_REGISTER						0xb400
#define RECEIVE_CLOCK_ROUTING_REGISTER				0xb404
#define TRANSMIT_CLOCK_ROUTING_REGISTER				0xb408
#define COMM_UNIT_ARBITER_CONFIGURATION_REGISTER	0xb40c

/****************************************/
/*	   Watchdog registers			*/
/****************************************/
#define WATCHDOG_CONFIGURATION_REGISTER			0xb410
#define WATCHDOG_VALUE_REGISTER					0xb414
#define WATCHDOG_CONFIG_REG					WATCHDOG_CONFIGURATION_REGISTER	 /*0xb4101 */
#define WATCHDOG_VALUE_REG						WATCHDOG_VALUE_REGISTER	 /*0xb4141 */


/****************************************/
/* Flex TDM Registers			*/
/****************************************/

/* FTDM Port */

#define FLEXTDM_TRANSMIT_READ_POINTER			    0xa800
#define FLEXTDM_RECEIVE_READ_POINTER			    0xa804
#define FLEXTDM_CONFIGURATION_REGISTER			    0xa808
#define FLEXTDM_AUX_CHANNELA_TX_REGISTER		    0xa80c
#define FLEXTDM_AUX_CHANNELA_RX_REGISTER		    0xa810
#define FLEXTDM_AUX_CHANNELB_TX_REGISTER		    0xa814
#define FLEXTDM_AUX_CHANNELB_RX_REGISTER		    0xa818

/* FTDM Interrupts */

#define FTDM_CAUSE_REGISTER				    0xb830
#define FTDM_MASK_REGISTER				    0xb8b0


/****************************************/
/* GPP Interface Registers		*/
/****************************************/

#define GPP_IO_CONTROL						0xf100
#define GPP_LEVEL_CONTROL					0xf110
#define GPP_VALUE						0xf104
#define GPP_INTERRUPT_CAUSE					0xf108
#define GPP_INTERRUPT_MASK					0xf10c
#define GPP_INTERRUPT_MASK0					GPP_INTERRUPT_MASK  /* 0xf10c1 */
#define GPP_INTERRUPT_MASK1					0xf114
#define GPP_VALUE_SET						0xf118
#define GPP_VALUE_CLEAR						0xf11c

/****************************************/
/*	MPP Interface Registers		*/
/****************************************/
#define MPP_CONTROL0						0xf000
#define MPP_CONTROL1						0xf004
#define MPP_CONTROL2						0xf008
#define MPP_CONTROL3						0xf00c
#define DEBUG_PORT_MULTIPLEX					0xf014
 /*#define SERIAL_PORT_MULTIPLEX			       0xf0101 */

/****************************************/
/* Interrupt Controller Registers	*/
/****************************************/

/****************************************/
/* Interrupts							*/
/****************************************/
/****************************************/
/* Interrupts (checked I.A. 14.10.02)				*/
/****************************************/

#define LOW_INTERRUPT_CAUSE_REGISTER			0x004  /* gt64260: 0xc181 */
#define HIGH_INTERRUPT_CAUSE_REGISTER			0x00c  /* gt64260: 0xc681 */
#define CPU_INTERRUPT_MASK_REGISTER_LOW		0x014  /* gt64260: 0xc1c1 */
#define CPU_INTERRUPT_MASK_REGISTER_HIGH		0x01c  /* gt64260: 0xc6c1 */
#define CPU_SELECT_CAUSE_REGISTER			0x024  /* gt64260: 0xc701 */
#define CPU_INTERRUPT_1_MASK_REGISTER_LOW		0x034  /* new in the MV64360 and MV64460 */
#define CPU_INTERRUPT_1_MASK_REGISTER_HIGH		0x03c  /* new in the MV64360 and MV64460 */
#define CPU_SELECT_1_CAUSE_REGISTER			0x044  /* new in the MV64360 and MV64460 */
#define PCI_0INTERRUPT_CAUSE_MASK_REGISTER_LOW	0x054  /* gt64260: 0xc241 */
#define PCI_0INTERRUPT_CAUSE_MASK_REGISTER_HIGH 0x05c  /* gt64260: 0xc641 */
#define PCI_0SELECT_CAUSE						0x064  /* gt64260: 0xc741 */
#define PCI_1INTERRUPT_CAUSE_MASK_REGISTER_LOW	0x074  /* gt64260: 0xca41 */
#define PCI_1INTERRUPT_CAUSE_MASK_REGISTER_HIGH 0x07c  /* gt64260: 0xce41 */
#define PCI_1SELECT_CAUSE						0x084  /* gt64260: 0xcf41 */
/*#define CPU_INT_0_MASK						0xe60 signal is not multiplexed on MPP in the MV64360 and MV64460 */
/*#define CPU_INT_1_MASK						0xe64 signal is not multiplexed on MPP in the MV64360 and MV64460 */
/*#define CPU_INT_2_MASK						0xe68 signal is not multiplexed on MPP in the MV64360 and MV64460 */
/*#define CPU_INT_3_MASK						0xe6c signal is not multiplexed on MPP in the MV64360 and MV64460 */

#define MAIN_INTERRUPT_CAUSE_LOW				LOW_INTERRUPT_CAUSE_REGISTER  /* 0x0041 */
#define MAIN_INTERRUPT_CAUSE_HIGH				HIGH_INTERRUPT_CAUSE_REGISTER  /* 0x00c1 */
#define CPU_INTERRUPT0_MASK_LOW				CPU_INTERRUPT_MASK_REGISTER_LOW	 /* 0x0141 */
#define CPU_INTERRUPT0_MASK_HIGH			CPU_INTERRUPT_MASK_REGISTER_HIGH  /*0x01c1 */
#define CPU_INTERRUPT0_SELECT_CAUSE			CPU_SELECT_CAUSE_REGISTER  /* 0x0241 */
#define CPU_INTERRUPT1_MASK_LOW				CPU_INTERRUPT_1_MASK_REGISTER_LOW  /* 0x0341 */
#define CPU_INTERRUPT1_MASK_HIGH			CPU_INTERRUPT_1_MASK_REGISTER_HIGH  /* 0x03c1 */
#define CPU_INTERRUPT1_SELECT_CAUSE			CPU_SELECT_1_CAUSE_REGISTER  /* 0x0441 */
#define INTERRUPT0_MASK_0_LOW				PCI_0INTERRUPT_CAUSE_MASK_REGISTER_LOW /* 0x0541 */
#define INTERRUPT0_MASK_0_HIGH					PCI_0INTERRUPT_CAUSE_MASK_REGISTER_HIGH	 /* 0x05c1 */
#define INTERRUPT0_SELECT_CAUSE				PCI_0SELECT_CAUSE  /* 0x0641 */
#define INTERRUPT1_MASK_0_LOW					PCI_1INTERRUPT_CAUSE_MASK_REGISTER_LOW	/* 0x0741 */
#define INTERRUPT1_MASK_0_HIGH					PCI_1INTERRUPT_CAUSE_MASK_REGISTER_HIGH	 /* 0x07c1 */
#define INTERRUPT1_SELECT_CAUSE				PCI_1SELECT_CAUSE  /* 0x0841 */

/****************************************/
/* I2C Registers			*/
/****************************************/

#define I2C_SLAVE_ADDRESS					0xc000
#define I2C_EXTENDED_SLAVE_ADDRESS			0xc040
#define I2C_DATA						0xc004
#define I2C_CONTROL						0xc008
#define I2C_STATUS_BAUDE_RATE					0xc00C
#define I2C_SOFT_RESET						0xc01c
#define I2C_SLAVE_ADDR						I2C_SLAVE_ADDRESS  /* 0xc0001 */
#define I2C_EXTENDED_SLAVE_ADDR					I2C_EXTENDED_SLAVE_ADDRESS  /*0xc0101 */

/****************************************/
/* MPSC Registers			*/
/****************************************/

	/*  MPSCs Clocks Routing Registers  */

#define MPSC_ROUTING_REG					0xb400
#define MPSC_RX_CLOCK_ROUTING_REG			0xb404
#define MPSC_TX_CLOCK_ROUTING_REG			0xb408

	/*  MPSCs Interrupts Registers	  */

#define MPSC_CAUSE_REG(port)					(0xb804 + (port<<3))
#define MPSC_MASK_REG(port)					(0xb884 + (port<<3))

#define MPSC_MAIN_CONFIG_LOW(port)			(0x8000 + (port<<12))
#define MPSC_MAIN_CONFIG_HIGH(port)			(0x8004 + (port<<12))
#define MPSC_PROTOCOL_CONFIG(port)			(0x8008 + (port<<12))
#define MPSC_CHANNEL_REG1(port)					(0x800c + (port<<12))
#define MPSC_CHANNEL_REG2(port)					(0x8010 + (port<<12))
#define MPSC_CHANNEL_REG3(port)					(0x8014 + (port<<12))
#define MPSC_CHANNEL_REG4(port)					(0x8018 + (port<<12))
#define MPSC_CHANNEL_REG5(port)					(0x801c + (port<<12))
#define MPSC_CHANNEL_REG6(port)					(0x8020 + (port<<12))
#define MPSC_CHANNEL_REG7(port)					(0x8024 + (port<<12))
#define MPSC_CHANNEL_REG8(port)					(0x8028 + (port<<12))
#define MPSC_CHANNEL_REG9(port)					(0x802c + (port<<12))
#define MPSC_CHANNEL_REG10(port)				(0x8030 + (port<<12))


/* MPSC0  */

#define MPSC0_MAIN_CONFIGURATION_LOW			    0x8000
#define MPSC0_MAIN_CONFIGURATION_HIGH			    0x8004
#define MPSC0_PROTOCOL_CONFIGURATION			    0x8008
#define CHANNEL0_REGISTER1				    0x800c
#define CHANNEL0_REGISTER2				    0x8010
#define CHANNEL0_REGISTER3				    0x8014
#define CHANNEL0_REGISTER4				    0x8018
#define CHANNEL0_REGISTER5				    0x801c
#define CHANNEL0_REGISTER6				    0x8020
#define CHANNEL0_REGISTER7				    0x8024
#define CHANNEL0_REGISTER8				    0x8028
#define CHANNEL0_REGISTER9				    0x802c
#define CHANNEL0_REGISTER10				    0x8030
#define CHANNEL0_REGISTER11				    0x8034

/* MPSC1  */

#define MPSC1_MAIN_CONFIGURATION_LOW			    0x8840
#define MPSC1_MAIN_CONFIGURATION_HIGH			    0x8844
#define MPSC1_PROTOCOL_CONFIGURATION			    0x8848
#define CHANNEL1_REGISTER1				    0x884c
#define CHANNEL1_REGISTER2				    0x8850
#define CHANNEL1_REGISTER3				    0x8854
#define CHANNEL1_REGISTER4				    0x8858
#define CHANNEL1_REGISTER5				    0x885c
#define CHANNEL1_REGISTER6				    0x8860
#define CHANNEL1_REGISTER7				    0x8864
#define CHANNEL1_REGISTER8				    0x8868
#define CHANNEL1_REGISTER9				    0x886c
#define CHANNEL1_REGISTER10				    0x8870
#define CHANNEL1_REGISTER11				    0x8874

/* MPSC2  */

#define MPSC2_MAIN_CONFIGURATION_LOW			    0x9040
#define MPSC2_MAIN_CONFIGURATION_HIGH			    0x9044
#define MPSC2_PROTOCOL_CONFIGURATION			    0x9048
#define CHANNEL2_REGISTER1				    0x904c
#define CHANNEL2_REGISTER2				    0x9050
#define CHANNEL2_REGISTER3				    0x9054
#define CHANNEL2_REGISTER4				    0x9058
#define CHANNEL2_REGISTER5				    0x905c
#define CHANNEL2_REGISTER6				    0x9060
#define CHANNEL2_REGISTER7				    0x9064
#define CHANNEL2_REGISTER8				    0x9068
#define CHANNEL2_REGISTER9				    0x906c
#define CHANNEL2_REGISTER10				    0x9070
#define CHANNEL2_REGISTER11				    0x9074

/* MPSCs Interrupts  */

#define MPSC0_CAUSE						0xb824
#define MPSC0_MASK						0xb8a4
#define MPSC1_CAUSE						0xb828
#define MPSC1_MASK						0xb8a8
#define MPSC2_CAUSE						0xb82c
#define MPSC2_MASK						 0xb8ac

/*******************************************/
/*	    CUNIT  Registers		   */
/*******************************************/

	 /* Address Decoding Register Map */

#define CUNIT_BASE_ADDR_REG0					0xf200
#define CUNIT_BASE_ADDR_REG1					0xf208
#define CUNIT_BASE_ADDR_REG2					0xf210
#define CUNIT_BASE_ADDR_REG3					0xf218
#define CUNIT_SIZE0						0xf204
#define CUNIT_SIZE1						0xf20c
#define CUNIT_SIZE2						0xf214
#define CUNIT_SIZE3						0xf21c
#define CUNIT_HIGH_ADDR_REMAP_REG0			0xf240
#define CUNIT_HIGH_ADDR_REMAP_REG1			0xf244
#define CUNIT_BASE_ADDR_ENABLE_REG			0xf250
#define MPSC0_ACCESS_PROTECTION_REG			0xf254
#define MPSC1_ACCESS_PROTECTION_REG			0xf258
#define CUNIT_INTERNAL_SPACE_BASE_ADDR_REG	0xf25C

	/*  Error Report Registers  */

#define CUNIT_INTERRUPT_CAUSE_REG			0xf310
#define CUNIT_INTERRUPT_MASK_REG			0xf314
#define CUNIT_ERROR_ADDR					0xf318

	/*  Cunit Control Registers */

#define CUNIT_ARBITER_CONTROL_REG			0xf300
#define CUNIT_CONFIG_REG					0xb40c
#define CUNIT_CRROSBAR_TIMEOUT_REG			0xf304

	/*  Cunit Debug Registers   */

#define CUNIT_DEBUG_LOW						0xf340
#define CUNIT_DEBUG_HIGH					0xf344
#define CUNIT_MMASK						0xf380

#endif /* __INCmv_gen_regh */
