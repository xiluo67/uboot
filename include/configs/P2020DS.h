/*
 * Copyright 2007-2012 Freescale Semiconductor, Inc.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * p2020ds board configuration file
 *
 */
#ifndef __CONFIG_H
#define __CONFIG_H

#include "../board/freescale/common/ics307_clk.h"

#ifdef CONFIG_36BIT
#define CONFIG_PHYS_64BIT
#endif

#ifdef CONFIG_SDCARD
#define CONFIG_SYS_RAMBOOT
#define CONFIG_SYS_EXTRA_ENV_RELOC
#define CONFIG_SYS_TEXT_BASE		0xf8f80000
#define CONFIG_RESET_VECTOR_ADDRESS	0xf8fffffc
#endif

#ifdef CONFIG_SPIFLASH
#define CONFIG_SYS_RAMBOOT
#define CONFIG_SYS_EXTRA_ENV_RELOC
#define CONFIG_SYS_TEXT_BASE		0xf8f80000
#define CONFIG_RESET_VECTOR_ADDRESS	0xf8fffffc
#endif

/* High Level Configuration Options */
#define CONFIG_BOOKE		1	/* BOOKE */
#define CONFIG_E500		1	/* BOOKE e500 family */
#define CONFIG_MPC85xx		1	/* MPC8540/60/55/41/48 */
#define CONFIG_P2020		1
#define CONFIG_P2020DS		1
#define CONFIG_MP		1	/* support multiple processors */

#ifndef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE	0xeff80000
#endif

#ifndef CONFIG_RESET_VECTOR_ADDRESS
#define CONFIG_RESET_VECTOR_ADDRESS	0xeffffffc
#endif

#define CONFIG_SYS_SRIO
#define CONFIG_SRIO1			/* SRIO port 1 */
#define CONFIG_SRIO2			/* SRIO port 2 */

#define CONFIG_FSL_ELBC		1	/* Has Enhanced localbus controller */
#define CONFIG_PCI		1	/* Enable PCI/PCIE */
#define CONFIG_PCIE1		1	/* PCIE controler 1 (slot 1) */
#define CONFIG_PCIE2		1	/* PCIE controler 2 (slot 2) */
#define CONFIG_PCIE3		1	/* PCIE controler 3 (ULI bridge) */
#define CONFIG_FSL_PCI_INIT	1	/* Use common FSL init code */
#define CONFIG_FSL_PCIE_RESET	1	/* need PCIe reset errata */
#define CONFIG_SYS_PCI_64BIT	1	/* enable 64-bit PCI resources */

#define CONFIG_FSL_LAW		1	/* Use common FSL init code */
#define CONFIG_E1000		1	/* Defind e1000 pci Ethernet card*/

#define CONFIG_TSEC_ENET		/* tsec ethernet support */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_SYS_CLK_FREQ	get_board_sys_clk() /* sysclk for MPC85xx */
#define CONFIG_DDR_CLK_FREQ	get_board_ddr_clk() /* ddrclk for MPC85xx */
#define CONFIG_ICS307_REFCLK_HZ	33333000  /* ICS307 clock chip ref freq */

/*
 * These can be toggled for performance analysis, otherwise use default.
 */
#define CONFIG_L2_CACHE			/* toggle L2 cache */
#define CONFIG_BTB			/* toggle branch predition */

#define CONFIG_BOARD_EARLY_INIT_F	/* Call board_pre_init */

#define CONFIG_ENABLE_36BIT_PHYS	1

#ifdef CONFIG_PHYS_64BIT
#define CONFIG_ADDR_MAP			1
#define CONFIG_SYS_NUM_ADDR_MAP		16	/* number of TLB1 entries */
#endif

#define CONFIG_POST CONFIG_SYS_POST_MEMORY	/* test POST memory test */
#define CONFIG_SYS_MEMTEST_START	0x00200000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x00400000
#define CONFIG_PANIC_HANG	/* do not reset board on panic */

/*
 * Config the L2 Cache
 */
#define CONFIG_SYS_INIT_L2_ADDR		0xf8f80000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_INIT_L2_ADDR_PHYS	0xff8f80000ull
#else
#define CONFIG_SYS_INIT_L2_ADDR_PHYS	CONFIG_SYS_INIT_L2_ADDR
#endif
#define CONFIG_SYS_L2_SIZE		(512 << 10)
#define CONFIG_SYS_INIT_L2_END	(CONFIG_SYS_INIT_L2_ADDR + CONFIG_SYS_L2_SIZE)

#define CONFIG_SYS_CCSRBAR		0xffe00000
#define CONFIG_SYS_CCSRBAR_PHYS_LOW	CONFIG_SYS_CCSRBAR

/* DDR Setup */
#define CONFIG_VERY_BIG_RAM
#ifdef CONFIG_DDR2
#define CONFIG_FSL_DDR2
#else
#define CONFIG_FSL_DDR3		1
#endif

/* ECC will be enabled based on perf_mode environment variable */
/* #define	CONFIG_DDR_ECC */

#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER
#define CONFIG_MEM_INIT_VALUE	0xDeadBeef

#define CONFIG_SYS_DDR_SDRAM_BASE	0x00000000
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE

#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	2

/* I2C addresses of SPD EEPROMs */
#define CONFIG_DDR_SPD
#define CONFIG_SYS_SPD_BUS_NUM		0	/* SPD EEPROM located on I2C bus 0 */
#define SPD_EEPROM_ADDRESS	0x51	/* CTLR 0 DIMM 0 */

/* These are used when DDR doesn't use SPD.  */
#define CONFIG_SYS_SDRAM_SIZE		1024		/* DDR is 1GB */

/* Default settings for "stable" mode */
#define CONFIG_SYS_DDR_CS0_BNDS		0x0000003F
#define CONFIG_SYS_DDR_CS1_BNDS		0x00000000
#define CONFIG_SYS_DDR_CS0_CONFIG	0x80014202
#define CONFIG_SYS_DDR_CS1_CONFIG	0x00000000
#define CONFIG_SYS_DDR_TIMING_3		0x00020000
#define CONFIG_SYS_DDR_TIMING_0		0x00330804
#define CONFIG_SYS_DDR_TIMING_1		0x6f6b4846
#define CONFIG_SYS_DDR_TIMING_2		0x0fa890d4
#define CONFIG_SYS_DDR_MODE_1		0x00421422
#define CONFIG_SYS_DDR_MODE_2		0x00000000
#define CONFIG_SYS_DDR_MODE_CTRL	0x00000000
#define CONFIG_SYS_DDR_INTERVAL		0x61800100
#define CONFIG_SYS_DDR_DATA_INIT	0xdeadbeef
#define CONFIG_SYS_DDR_CLK_CTRL		0x02000000
#define CONFIG_SYS_DDR_TIMING_4		0x00220001
#define CONFIG_SYS_DDR_TIMING_5		0x03402400
#define CONFIG_SYS_DDR_ZQ_CNTL		0x89080600
#define CONFIG_SYS_DDR_WRLVL_CNTL	0x8655A608
#define CONFIG_SYS_DDR_CONTROL		0xE7000000 /* Type = DDR3: ECC enabled, No Interleaving */
#define CONFIG_SYS_DDR_CONTROL2		0x24400011
#define CONFIG_SYS_DDR_CDR1		0x00040000
#define CONFIG_SYS_DDR_CDR2		0x00000000

#define CONFIG_SYS_DDR_ERR_INT_EN	0x0000000d
#define CONFIG_SYS_DDR_ERR_DIS		0x00000000
#define CONFIG_SYS_DDR_SBE		0x00010000

/* Settings that differ for "performance" mode */
#define CONFIG_SYS_DDR_CS0_BNDS_PERF		0x0000007F /* Interleaving Enabled */
#define CONFIG_SYS_DDR_CS1_BNDS_PERF		0x00000000 /* Interleaving Enabled */
#define CONFIG_SYS_DDR_CS1_CONFIG_PERF	0x80014202
#define CONFIG_SYS_DDR_TIMING_1_PERF		0x5d5b4543
#define CONFIG_SYS_DDR_TIMING_2_PERF		0x0fa890ce
#define CONFIG_SYS_DDR_CONTROL_PERF		0xC7004000 /* Type = DDR3: ECC disabled, cs0-cs1 interleaving */

/*
 * The following set of values were tested for DDR2
 * with a DDR3 to DDR2 interposer
 *
#define CONFIG_SYS_DDR_TIMING_3		0x00000000
#define CONFIG_SYS_DDR_TIMING_0		0x00260802
#define CONFIG_SYS_DDR_TIMING_1		0x3935d322
#define CONFIG_SYS_DDR_TIMING_2		0x14904cc8
#define CONFIG_SYS_DDR_MODE_1		0x00480432
#define CONFIG_SYS_DDR_MODE_2		0x00000000
#define CONFIG_SYS_DDR_INTERVAL		0x06180100
#define CONFIG_SYS_DDR_DATA_INIT	0xdeadbeef
#define CONFIG_SYS_DDR_CLK_CTRL		0x03800000
#define CONFIG_SYS_DDR_OCD_CTRL		0x00000000
#define CONFIG_SYS_DDR_OCD_STATUS	0x00000000
#define CONFIG_SYS_DDR_CONTROL		0xC3008000
#define CONFIG_SYS_DDR_CONTROL2		0x04400010
 *
 */

/*
 * Memory map
 *
 * 0x0000_0000	0x7fff_ffff	DDR			2G Cacheable
 * 0x8000_0000	0xbfff_ffff	PCI Express Mem		1G non-cacheable
 * 0xc000_0000	0xdfff_ffff	PCI			512M non-cacheable
 * 0xe100_0000	0xe3ff_ffff	PCI IO range		4M non-cacheable
 *
 * Localbus cacheable (TBD)
 * 0xXXXX_XXXX	0xXXXX_XXXX	SRAM			YZ M Cacheable
 *
 * Localbus non-cacheable
 * 0xe000_0000	0xe80f_ffff	Promjet/free		128M non-cacheable
 * 0xe800_0000	0xefff_ffff	FLASH			128M non-cacheable
 * 0xffa0_0000	0xffaf_ffff	NAND			1M non-cacheable
 * 0xffdf_0000	0xffdf_7fff	PIXIS			32K non-cacheable TLB0
 * 0xffd0_0000	0xffd0_3fff	L1 for stack		16K Cacheable TLB0
 * 0xffe0_0000	0xffef_ffff	CCSR			1M non-cacheable
 */

/*
 * Local Bus Definitions
 */
#define CONFIG_SYS_FLASH_BASE		0xe0000000	/* start of FLASH 128M */
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_FLASH_BASE_PHYS	0xfe0000000ull
#else
#define CONFIG_SYS_FLASH_BASE_PHYS	CONFIG_SYS_FLASH_BASE
#endif

#define CONFIG_FLASH_BR_PRELIM  \
	(BR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE_PHYS + 0x8000000) | BR_PS_16 | BR_V)
#define CONFIG_FLASH_OR_PRELIM	0xf8000ff7

#define CONFIG_SYS_BR1_PRELIM  (BR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE_PHYS) | BR_PS_16 | BR_V)
#define CONFIG_SYS_OR1_PRELIM	0xf8000ff7

#define CONFIG_SYS_FLASH_BANKS_LIST	{CONFIG_SYS_FLASH_BASE_PHYS + 0x8000000, CONFIG_SYS_FLASH_BASE_PHYS}
#define CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_FLASH_SHOW_PROGRESS 45 /* count down from 45/5: 9..1 */

#define CONFIG_SYS_MAX_FLASH_BANKS	2		/* number of banks */
#define CONFIG_SYS_MAX_FLASH_SECT	1024		/* sectors per device */
#define CONFIG_SYS_FLASH_ERASE_TOUT	60000		/* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500		/* Flash Write Timeout (ms) */

#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_TEXT_BASE	/* start of monitor */

#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_AMD_CHECK_DQ7

#define CONFIG_BOARD_EARLY_INIT_R	/* call board_early_init_r function */

#define CONFIG_HWCONFIG			/* enable hwconfig */
#define CONFIG_FSL_NGPIXIS		/* use common ngPIXIS code */

#ifdef CONFIG_FSL_NGPIXIS
#define PIXIS_BASE	0xffdf0000	/* PIXIS registers */
#ifdef CONFIG_PHYS_64BIT
#define PIXIS_BASE_PHYS	0xfffdf0000ull
#else
#define PIXIS_BASE_PHYS	PIXIS_BASE
#endif

#define CONFIG_SYS_BR3_PRELIM	(BR_PHYS_ADDR(PIXIS_BASE_PHYS) | BR_PS_8 | BR_V)
#define CONFIG_SYS_OR3_PRELIM		0xffffeff7	/* 32KB but only 4k mapped */

#define PIXIS_LBMAP_SWITCH	7
#define PIXIS_LBMAP_MASK	0xf0
#define PIXIS_LBMAP_SHIFT	4
#define PIXIS_LBMAP_ALTBANK	0x20
#endif

#define CONFIG_SYS_INIT_RAM_LOCK	1
#define CONFIG_SYS_INIT_RAM_ADDR	0xffd00000	/* Initial L1 address */
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH 0xf
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW CONFIG_SYS_INIT_RAM_ADDR
/* The assembler doesn't like typecast */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS \
	((CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH * 1ull << 32) | \
	  CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW)
#else
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS	CONFIG_SYS_INIT_RAM_ADDR /* Initial L1 address */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH 0
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW CONFIG_SYS_INIT_RAM_ADDR_PHYS
#endif
#define CONFIG_SYS_INIT_RAM_SIZE	0x00004000	/* Size of used area in RAM */

#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_MONITOR_LEN		(256 * 1024) /* Reserve 256 kB for Mon */
#define CONFIG_SYS_MALLOC_LEN		(1024 * 1024)	/* Reserved for malloc */

#define CONFIG_SYS_NAND_BASE		0xffa00000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_NAND_BASE_PHYS	0xfffa00000ull
#else
#define CONFIG_SYS_NAND_BASE_PHYS	CONFIG_SYS_NAND_BASE
#endif
#define CONFIG_SYS_NAND_BASE_LIST	{ CONFIG_SYS_NAND_BASE,\
				CONFIG_SYS_NAND_BASE + 0x40000, \
				CONFIG_SYS_NAND_BASE + 0x80000,\
				CONFIG_SYS_NAND_BASE + 0xC0000}
#define CONFIG_SYS_MAX_NAND_DEVICE	4
#define CONFIG_MTD_NAND_VERIFY_WRITE
#define CONFIG_CMD_NAND			1
#define CONFIG_NAND_FSL_ELBC		1
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128 * 1024)

/* NAND flash config */
#define CONFIG_SYS_NAND_BR_PRELIM  (BR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS) \
				| (2<<BR_DECC_SHIFT)	/* Use HW ECC */ \
				| BR_PS_8		/* Port Size = 8bit */ \
				| BR_MS_FCM		/* MSEL = FCM */ \
				| BR_V)			/* valid */
#define CONFIG_SYS_NAND_OR_PRELIM  (0xFFFC0000		/* length 256K */ \
				| OR_FCM_PGS		/* Large Page*/ \
				| OR_FCM_CSCT \
				| OR_FCM_CST \
				| OR_FCM_CHT \
				| OR_FCM_SCY_1 \
				| OR_FCM_TRLX \
				| OR_FCM_EHTR)

#define CONFIG_SYS_BR0_PRELIM  CONFIG_FLASH_BR_PRELIM  /* NOR Base Address */
#define CONFIG_SYS_OR0_PRELIM  CONFIG_FLASH_OR_PRELIM  /* NOR Options */
#define CONFIG_SYS_BR2_PRELIM  CONFIG_SYS_NAND_BR_PRELIM  /* NAND Base Address */
#define CONFIG_SYS_OR2_PRELIM  CONFIG_SYS_NAND_OR_PRELIM  /* NAND Options */

#define CONFIG_SYS_BR4_PRELIM  (BR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS + 0x40000) \
				| (2<<BR_DECC_SHIFT)	/* Use HW ECC */ \
				| BR_PS_8		/* Port Size = 8bit */ \
				| BR_MS_FCM		/* MSEL = FCM */ \
				| BR_V)			/* valid */
#define CONFIG_SYS_OR4_PRELIM  CONFIG_SYS_NAND_OR_PRELIM	/* NAND Options */
#define CONFIG_SYS_BR5_PRELIM  (BR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS + 0x80000) \
				| (2<<BR_DECC_SHIFT)	/* Use HW ECC */ \
				| BR_PS_8		/* Port Size = 8bit */ \
				| BR_MS_FCM		/* MSEL = FCM */ \
				| BR_V)			/* valid */
#define CONFIG_SYS_OR5_PRELIM  CONFIG_SYS_NAND_OR_PRELIM	/* NAND Options */

#define CONFIG_SYS_BR6_PRELIM  (BR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS + 0xc0000) \
				| (2<<BR_DECC_SHIFT)	/* Use HW ECC */ \
				| BR_PS_8		/* Port Size = 8bit */ \
				| BR_MS_FCM		/* MSEL = FCM */ \
				| BR_V)			/* valid */
#define CONFIG_SYS_OR6_PRELIM  CONFIG_SYS_NAND_OR_PRELIM	/* NAND Options */

/* Serial Port - controlled on board with jumper J8
 * open - index 2
 * shorted - index 1
 */
#define CONFIG_CONS_INDEX	1
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	1
#define CONFIG_SYS_NS16550_CLK		get_bus_freq(0)

#define CONFIG_SYS_BAUDRATE_TABLE	\
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}

#define CONFIG_SYS_NS16550_COM1	(CONFIG_SYS_CCSRBAR+0x4500)
#define CONFIG_SYS_NS16550_COM2	(CONFIG_SYS_CCSRBAR+0x4600)

/* Use the HUSH parser */
#define CONFIG_SYS_HUSH_PARSER

/*
 * Pass open firmware flat tree
 */
#define CONFIG_OF_LIBFDT		1
#define CONFIG_OF_BOARD_SETUP		1
#define CONFIG_OF_STDOUT_VIA_ALIAS	1

/* I2C */
#define CONFIG_FSL_I2C		/* Use FSL common I2C driver */
#define CONFIG_HARD_I2C		/* I2C with hardware support */
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_I2C_SPEED		400000	/* I2C speed and slave address */
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x57
#define CONFIG_SYS_I2C_SLAVE		0x7F
#define CONFIG_SYS_I2C_NOPROBES	{{0,0x29}}/* Don't probe these addrs */
#define CONFIG_SYS_I2C_OFFSET		0x3000
#define CONFIG_SYS_I2C2_OFFSET		0x3100

/*
 * I2C2 EEPROM
 */
#define CONFIG_ID_EEPROM
#ifdef CONFIG_ID_EEPROM
#define CONFIG_SYS_I2C_EEPROM_NXID
#endif
#define CONFIG_SYS_I2C_EEPROM_ADDR	0x57
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 1
#define CONFIG_SYS_EEPROM_BUS_NUM	0

/*
 * eSPI - Enhanced SPI
 */
#define CONFIG_FSL_ESPI

#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_SPANSION

#define CONFIG_CMD_SF
#define CONFIG_SF_DEFAULT_SPEED		10000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0

/*
 * General PCI
 * Memory space is mapped 1-1, but I/O space must start from 0.
 */

/* controller 3, Slot 1, tgtid 3, Base address b000 */
#define CONFIG_SYS_PCIE3_NAME		"Slot 1"
#define CONFIG_SYS_PCIE3_MEM_VIRT	0x80000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_PCIE3_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE3_MEM_PHYS	0xc00000000ull
#else
#define CONFIG_SYS_PCIE3_MEM_BUS	0x80000000
#define CONFIG_SYS_PCIE3_MEM_PHYS	0x80000000
#endif
#define CONFIG_SYS_PCIE3_MEM_SIZE	0x20000000	/* 512M */
#define CONFIG_SYS_PCIE3_IO_VIRT	0xffc00000
#define CONFIG_SYS_PCIE3_IO_BUS		0x00000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_PCIE3_IO_PHYS	0xfffc00000ull
#else
#define CONFIG_SYS_PCIE3_IO_PHYS	0xffc00000
#endif
#define CONFIG_SYS_PCIE3_IO_SIZE	0x00010000	/* 64k */

/* controller 2, direct to uli, tgtid 2, Base address 9000 */
#define CONFIG_SYS_PCIE2_NAME		"ULI"
#define CONFIG_SYS_PCIE2_MEM_VIRT	0xa0000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_PCIE2_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE2_MEM_PHYS	0xc20000000ull
#else
#define CONFIG_SYS_PCIE2_MEM_BUS	0xa0000000
#define CONFIG_SYS_PCIE2_MEM_PHYS	0xa0000000
#endif
#define CONFIG_SYS_PCIE2_MEM_SIZE	0x20000000	/* 512M */
#define CONFIG_SYS_PCIE2_IO_VIRT	0xffc10000
#define CONFIG_SYS_PCIE2_IO_BUS		0x00000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_PCIE2_IO_PHYS	0xfffc10000ull
#else
#define CONFIG_SYS_PCIE2_IO_PHYS	0xffc10000
#endif
#define CONFIG_SYS_PCIE2_IO_SIZE	0x00010000	/* 64k */

/* controller 1, Slot 2, tgtid 1, Base address a000 */
#define CONFIG_SYS_PCIE1_NAME		"Slot 2"
#define CONFIG_SYS_PCIE1_MEM_VIRT	0xc0000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_PCIE1_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE1_MEM_PHYS	0xc40000000ull
#else
#define CONFIG_SYS_PCIE1_MEM_BUS	0xc0000000
#define CONFIG_SYS_PCIE1_MEM_PHYS	0xc0000000
#endif
#define CONFIG_SYS_PCIE1_MEM_SIZE	0x20000000	/* 512M */
#define CONFIG_SYS_PCIE1_IO_VIRT	0xffc20000
#define CONFIG_SYS_PCIE1_IO_BUS		0x00000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_PCIE1_IO_PHYS	0xfffc20000ull
#else
#define CONFIG_SYS_PCIE1_IO_PHYS	0xffc20000
#endif
#define CONFIG_SYS_PCIE1_IO_SIZE	0x00010000	/* 64k */

#if defined(CONFIG_PCI)

/*PCIE video card used*/
#define VIDEO_IO_OFFSET		CONFIG_SYS_PCIE1_IO_VIRT

/* video */
#define CONFIG_VIDEO

#if defined(CONFIG_VIDEO)
#define CONFIG_BIOSEMU
#define CONFIG_CFB_CONSOLE
#define CONFIG_VIDEO_SW_CURSOR
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_ATI_RADEON_FB
#define CONFIG_VIDEO_LOGO
/*#define CONFIG_CONSOLE_CURSOR*/
#define CONFIG_SYS_ISA_IO_BASE_ADDRESS VIDEO_IO_OFFSET
#endif

/* SRIO1 uses the same window as PCIE2 mem window */
#define CONFIG_SYS_SRIO1_MEM_VIRT	0xa0000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_SRIO1_MEM_PHYS	0xc20000000ull
#else
#define CONFIG_SYS_SRIO1_MEM_PHYS	0xa0000000
#endif
#define CONFIG_SYS_SRIO1_MEM_SIZE	0x20000000	/* 512M */

/* SRIO2 uses the same window as PCIE1 mem window */
#define CONFIG_SYS_SRIO2_MEM_VIRT	0xc0000000
#ifdef CONFIG_PHYS_64BIT
#define CONFIG_SYS_SRIO2_MEM_PHYS	0xc40000000ull
#else
#define CONFIG_SYS_SRIO2_MEM_PHYS	0xc0000000
#endif
#define CONFIG_SYS_SRIO2_MEM_SIZE	0x20000000	/* 512M */

#define CONFIG_PCI_PNP			/* do pci plug-and-play */
#define CONFIG_PCI_SCAN_SHOW		/* show pci devices on startup */
#define CONFIG_DOS_PARTITION
#define CONFIG_SCSI_AHCI

#ifdef CONFIG_SCSI_AHCI
#define CONFIG_SATA_ULI5288
#define CONFIG_SYS_SCSI_MAX_SCSI_ID	4
#define CONFIG_SYS_SCSI_MAX_LUN	1
#define CONFIG_SYS_SCSI_MAX_DEVICE	(CONFIG_SYS_SCSI_MAX_SCSI_ID * CONFIG_SYS_SCSI_MAX_LUN)
#define CONFIG_SYS_SCSI_MAXDEVICE	CONFIG_SYS_SCSI_MAX_DEVICE
#endif /* SCSI */

#endif	/* CONFIG_PCI */


#if defined(CONFIG_TSEC_ENET)

#define CONFIG_MII		1	/* MII PHY management */
#define CONFIG_MII_DEFAULT_TSEC	1	/* Allow unregistered phys */
#define CONFIG_TSEC1	1
#define CONFIG_TSEC1_NAME	"eTSEC1"
#define CONFIG_TSEC2	1
#define CONFIG_TSEC2_NAME	"eTSEC2"
#define CONFIG_TSEC3	1
#define CONFIG_TSEC3_NAME	"eTSEC3"

#define CONFIG_FSL_SGMII_RISER	1
#define SGMII_RISER_PHY_OFFSET	0x1b

#ifdef CONFIG_FSL_SGMII_RISER
#define CONFIG_SYS_TBIPA_VALUE		0x10 /* avoid conflict with eTSEC4 paddr */
#endif

#define TSEC1_PHY_ADDR		0
#define TSEC2_PHY_ADDR		1
#define TSEC3_PHY_ADDR		2

#define TSEC1_FLAGS		(TSEC_GIGABIT | TSEC_REDUCED)
#define TSEC2_FLAGS		(TSEC_GIGABIT | TSEC_REDUCED)
#define TSEC3_FLAGS		(TSEC_GIGABIT | TSEC_REDUCED)

#define TSEC1_PHYIDX		0
#define TSEC2_PHYIDX		0
#define TSEC3_PHYIDX		0

#define CONFIG_ETHPRIME		"eTSEC1"

#define CONFIG_PHY_GIGE		1	/* Include GbE speed/duplex detection */
#endif	/* CONFIG_TSEC_ENET */

/*
 * Environment
 */
#if defined(CONFIG_SDCARD)
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_FSL_FIXED_MMC_LOCATION
#define CONFIG_ENV_SIZE			0x2000
#define CONFIG_SYS_MMC_ENV_DEV		0
#elif defined(CONFIG_SPIFLASH)
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SPI_BUS		0
#define CONFIG_ENV_SPI_CS		0
#define CONFIG_ENV_SPI_MAX_HZ		10000000
#define CONFIG_ENV_SPI_MODE		0
#define CONFIG_ENV_SIZE			0x2000		/* 8KB */
#define CONFIG_ENV_OFFSET		0x100000	/* 1MB */
#define CONFIG_ENV_SECT_SIZE		0x10000
#else
#define CONFIG_ENV_IS_IN_FLASH	1
#if CONFIG_SYS_MONITOR_BASE > 0xfff80000
#define CONFIG_ENV_ADDR		0xfff80000
#else
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SECT_SIZE)
#endif
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_SECT_SIZE	0x20000 /* 128K (one sector) */
#endif

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download */
#define CONFIG_SYS_LOADS_BAUD_CHANGE	1	/* allow baudrate change */

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_IRQ
#define CONFIG_CMD_PING
#define CONFIG_CMD_I2C
#define CONFIG_CMD_MII
#define CONFIG_CMD_ELF
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_SETEXPR
#define CONFIG_CMD_REGINFO

#if defined(CONFIG_PCI)
#define CONFIG_CMD_PCI
#define CONFIG_CMD_NET
#define CONFIG_CMD_SCSI
#define CONFIG_CMD_EXT2
#endif

/*
 * USB
 */
#define CONFIG_HAS_FSL_DR_USB
#ifdef CONFIG_HAS_FSL_DR_USB
#define CONFIG_USB_EHCI

#ifdef CONFIG_USB_EHCI
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI_FSL
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#endif
#endif

/*
 * SDHC/MMC
 */
#define CONFIG_MMC

#ifdef CONFIG_MMC
#define CONFIG_FSL_ESDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	CONFIG_SYS_MPC85xx_ESDHC_ADDR
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#endif

#if defined(CONFIG_MMC) || defined(CONFIG_USB_EHCI)
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP			/* undef to save memory	*/
#define CONFIG_CMDLINE_EDITING			/* Command-line editing */
#define CONFIG_AUTO_COMPLETE			/* add autocompletion support */
#define CONFIG_SYS_LOAD_ADDR	0x2000000	/* default load address */
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt */
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size */
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size */
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16		/* max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size */
#define CONFIG_SYS_HZ		1000		/* decrementer freq: 1ms ticks */

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 64 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_SYS_BOOTMAPSZ	(64 << 20)	/* Initial Memory map for Linux*/
#define CONFIG_SYS_BOOTM_LEN	(64 << 20)	/* Increase max gunzip size */

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	230400	/* speed to run kgdb serial port */
#define CONFIG_KGDB_SER_INDEX	2	/* which serial port to use */
#endif

/*
 * Environment Configuration
 */

/* The mac addresses for all ethernet interface */
#if defined(CONFIG_TSEC_ENET)
#define CONFIG_HAS_ETH0
#define CONFIG_HAS_ETH1
#define CONFIG_HAS_ETH2
#endif

#define CONFIG_IPADDR		192.168.1.254

#define CONFIG_HOSTNAME		unknown
#define CONFIG_ROOTPATH		"/opt/nfsroot"
#define CONFIG_BOOTFILE		"uImage"
#define CONFIG_UBOOTPATH	u-boot.bin	/* U-Boot image on TFTP server */

#define CONFIG_SERVERIP		192.168.1.1
#define CONFIG_GATEWAYIP	192.168.1.1
#define CONFIG_NETMASK		255.255.255.0

/* default location for tftp and bootm */
#define CONFIG_LOADADDR		1000000

#define CONFIG_BOOTDELAY 10	/* -1 disables auto-boot */

#define CONFIG_BAUDRATE	115200

#define	CONFIG_EXTRA_ENV_SETTINGS				\
 "perf_mode=performance\0"			\
	"hwconfig=fsl_ddr:ctlr_intlv=bank,bank_intlv=cs0_cs1;"	\
	"usb1:dr_mode=host,phy_type=ulpi\0"			\
 "netdev=eth0\0"						\
 "uboot=" MK_STR(CONFIG_UBOOTPATH) "\0"				\
 "tftpflash=tftpboot $loadaddr $uboot; "			\
	"protect off " MK_STR(CONFIG_SYS_TEXT_BASE) " +$filesize; "	\
	"erase " MK_STR(CONFIG_SYS_TEXT_BASE) " +$filesize; "		\
	"cp.b $loadaddr " MK_STR(CONFIG_SYS_TEXT_BASE) " $filesize; "	\
	"protect on " MK_STR(CONFIG_SYS_TEXT_BASE) " +$filesize; "		\
	"cmp.b $loadaddr " MK_STR(CONFIG_SYS_TEXT_BASE) " $filesize\0"	\
 "satabootcmd=setenv bootargs root=/dev/$bdev rw "	\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"tftp $loadaddr $bootfile;"			\
	"tftp $fdtaddr $fdtfile;"			\
	"bootm $loadaddr - $fdtaddr"			\
 "consoledev=ttyS0\0"				\
 "ramdiskaddr=2000000\0"			\
 "ramdiskfile=p2020ds/ramdisk.uboot\0"		\
 "fdtaddr=c00000\0"				\
 "othbootargs=cache-sram-size=0x10000\0"	\
 "fdtfile=p2020ds/p2020ds.dtb\0"		\
 "bdev=sda3\0"					\
 "partition=scsi 0:0\0"

#define CONFIG_HDBOOT				\
 "setenv bootargs root=/dev/$bdev rw "		\
 "console=$consoledev,$baudrate $othbootargs;"	\
 "ext2load $partition $loadaddr $bootfile;"	\
 "ext2load $partition $fdtaddr $fdtfile;"	\
 "bootm $loadaddr - $fdtaddr"

#define CONFIG_NFSBOOTCOMMAND		\
 "setenv bootargs root=/dev/nfs rw "	\
 "nfsroot=$serverip:$rootpath "		\
 "ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname:$netdev:off " \
 "console=$consoledev,$baudrate $othbootargs;"	\
 "tftp $loadaddr $bootfile;"		\
 "tftp $fdtaddr $fdtfile;"		\
 "bootm $loadaddr - $fdtaddr"

#define CONFIG_RAMBOOTCOMMAND		\
 "setenv bootargs root=/dev/ram rw "	\
 "console=$consoledev,$baudrate $othbootargs;"	\
 "tftp $ramdiskaddr $ramdiskfile;"	\
 "tftp $loadaddr $bootfile;"		\
 "tftp $fdtaddr $fdtfile;"		\
 "bootm $loadaddr $ramdiskaddr $fdtaddr"

#define CONFIG_BOOTCOMMAND		CONFIG_HDBOOT

#endif	/* __CONFIG_H */
