/*
 * (C) Copyright 2010
 * Stefan Roese, DENX Software Engineering, sr@denx.de.
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

/*
 * t3corp.h - configuration for T3CORP (460GT)
 */
#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 */
#define CONFIG_460GT		1	/* Specific PPC460GT	*/
#define CONFIG_440		1
#define CONFIG_4xx		1	/* ... PPC4xx family */

#ifndef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE	0xFFFA0000
#endif

#define CONFIG_HOSTNAME		t3corp

/*
 * Include common defines/options for all AMCC/APM eval boards
 */
#include "amcc-common.h"

#define CONFIG_SYS_CLK_FREQ	66666667	/* external freq to pll	*/

#define CONFIG_BOARD_EARLY_INIT_F	1	/* Call board_early_init_f */
#define CONFIG_BOARD_EARLY_INIT_R	1	/* Call board_early_init_r */
#define CONFIG_MISC_INIT_R		1	/* Call misc_init_r */
#define CONFIG_BOARD_TYPES		1	/* support board types */
#define CONFIG_FIT
#define CFG_ALT_MEMTEST

/*
 * Base addresses -- Note these are effective addresses where the
 * actual resources get mapped (not physical addresses)
 */
#define CONFIG_SYS_PCI_MEMBASE		0x80000000	/* mapped PCI memory */
#define CONFIG_SYS_PCI_BASE		0xd0000000	/* internal PCI regs */
#define CONFIG_SYS_PCI_TARGBASE	CONFIG_SYS_PCI_MEMBASE

#define CONFIG_SYS_PCIE_MEMBASE		0xb0000000	/* mapped PCIe mem */
#define CONFIG_SYS_PCIE_MEMSIZE		0x08000000	/* incr for PCIe */
#define CONFIG_SYS_PCIE_BASE		0xc4000000	/* PCIe UTL regs */

#define CONFIG_SYS_PCIE0_CFGBASE	0xc0000000
#define CONFIG_SYS_PCIE1_CFGBASE	0xc1000000
#define CONFIG_SYS_PCIE0_XCFGBASE	0xc3000000
#define CONFIG_SYS_PCIE1_XCFGBASE	0xc3001000

#define	CONFIG_SYS_PCIE0_UTLBASE	0xc08010000ULL	/* 36bit phys addr */

/* base address of inbound PCIe window */
#define CONFIG_SYS_PCIE_INBOUND_BASE	0x000000000ULL	/* 36bit phys addr */

/* EBC stuff */
#define CONFIG_SYS_FLASH_BASE		0xFC000000	/* later mapped here */
#define CONFIG_SYS_FLASH_SIZE		(64 << 20)

#define CONFIG_SYS_FPGA1_BASE		0xe0000000
#define CONFIG_SYS_FPGA2_BASE		0xe2000000
#define CONFIG_SYS_FPGA3_BASE		0xe4000000

#define CONFIG_SYS_BOOT_BASE_ADDR	0xFF000000	/* EBC Boot Space */
#define CONFIG_SYS_FLASH_BASE_PHYS_H	0x4
#define CONFIG_SYS_FLASH_BASE_PHYS_L	0xCC000000
#define CONFIG_SYS_FLASH_BASE_PHYS \
	(((u64)CONFIG_SYS_FLASH_BASE_PHYS_H << 32) \
	| (u64)CONFIG_SYS_FLASH_BASE_PHYS_L)

#define CONFIG_SYS_OCM_BASE		0xE7000000	/* OCM: 64k */
#define CONFIG_SYS_SRAM_BASE		0xE8000000	/* SRAM: 256k */
#define CONFIG_SYS_SRAM_SIZE		(256 << 10)
#define CONFIG_SYS_LOCAL_CONF_REGS	0xEF000000

/*
 * Initial RAM & stack pointer (placed in OCM)
 */
#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_OCM_BASE	/* OCM */
#define CONFIG_SYS_INIT_RAM_SIZE	(4 << 10)
#define CONFIG_SYS_GBL_DATA_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

/*
 * Serial Port
 */
#define CONFIG_CONS_INDEX	1	/* Use UART0			*/

/*
 * Environment
 */
/*
 * Define here the location of the environment variables (flash).
 */
#define	CONFIG_ENV_IS_IN_FLASH		/* use flash for environment vars */

/*
 * Flash related
 */
#define CONFIG_SYS_FLASH_CFI		/* The flash is CFI compatible	*/
#define CONFIG_FLASH_CFI_DRIVER		/* Use common CFI driver	*/
#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT
#define CONFIG_CFI_FLASH_USE_WEAK_ACCESSORS
#define CONFIG_SYS_CFI_FLASH_STATUS_POLL /* use status poll method	*/
#define CONFIG_SYS_FLASH_PROTECTION	/* use hardware flash protection */

#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE, \
			(CONFIG_SYS_FPGA1_BASE + 0x01000000) }
#define CONFIG_SYS_CFI_FLASH_CONFIG_REGS { 0xffff,	/* don't set	*/ \
			0xbddf }		/* set async read mode	*/
#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* max num of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT	512	/* max num of sectors p. chip*/

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000	/* Timeout for Flash Erase/ms*/
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Timeout for Flash Write/ms*/

#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE	/* buff'd writes (20x faster)*/
#define CONFIG_SYS_FLASH_EMPTY_INFO	/* 'E' for empty sector on flinfo */

#define CONFIG_ENV_SECT_SIZE		0x20000	/* sector size */
#define CONFIG_ENV_ADDR			(CONFIG_SYS_MONITOR_BASE - \
					 CONFIG_ENV_SECT_SIZE)
#define	CONFIG_ENV_SIZE			0x4000	/* env sector size */

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_ADDR_REDUND	(CONFIG_ENV_ADDR - CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)

/*
 * DDR2 SDRAM
 */
#define CONFIG_SYS_MBYTES_SDRAM		256
#define CONFIG_DDR_ECC
#define CONFIG_AUTOCALIB	"silent\0"	/* default is non-verbose    */
#define CONFIG_PPC4xx_DDR_AUTOCALIBRATION	/* IBM DDR autocalibration   */
#define DEBUG_PPC4xx_DDR_AUTOCALIBRATION	/* dynamic DDR autocal debug */
#undef CONFIG_PPC4xx_DDR_METHOD_A
#define CONFIG_DDR_RFDC_FIXED		0x000001D7 /* optimal value */

/* DDR1/2 SDRAM Device Control Register Data Values */
/* Memory Queue */
#define CONFIG_SYS_SDRAM_R0BAS		(SDRAM_RXBAS_SDBA_ENCODE(0) | \
					 SDRAM_RXBAS_SDSZ_256)
#define CONFIG_SYS_SDRAM_R1BAS		0x00000000
#define CONFIG_SYS_SDRAM_R2BAS		0x00000000
#define CONFIG_SYS_SDRAM_R3BAS		0x00000000
#define CONFIG_SYS_SDRAM_PLBADDULL	0x00000000
#define CONFIG_SYS_SDRAM_PLBADDUHB	0x00000008
#define CONFIG_SYS_SDRAM_CONF1LL	0x80001C00
#define CONFIG_SYS_SDRAM_CONF1HB	0x80001C80
#define CONFIG_SYS_SDRAM_CONFPATHB	0x10a68000

#define CAS_LATENCY			JEDEC_MA_MR_CL_DDR2_5_0_CLK

/* DDR1/2 SDRAM Device Control Register Data Values */
#define CONFIG_SYS_SDRAM0_MB0CF		(SDRAM_RXBAS_SDAM_MODE7		| \
					 SDRAM_RXBAS_SDBE_ENABLE)
#define CONFIG_SYS_SDRAM0_MB1CF		SDRAM_RXBAS_SDBE_DISABLE
#define CONFIG_SYS_SDRAM0_MB2CF		SDRAM_RXBAS_SDBE_DISABLE
#define CONFIG_SYS_SDRAM0_MB3CF		SDRAM_RXBAS_SDBE_DISABLE
#define CONFIG_SYS_SDRAM0_MCOPT1	(SDRAM_MCOPT1_MCHK_GEN		| \
					 SDRAM_MCOPT1_PMU_OPEN		| \
					 SDRAM_MCOPT1_DMWD_32		| \
					 SDRAM_MCOPT1_8_BANKS		| \
					 SDRAM_MCOPT1_DDR2_TYPE		| \
					 SDRAM_MCOPT1_QDEP		| \
					 SDRAM_MCOPT1_RWOO_DISABLED	| \
					 SDRAM_MCOPT1_WOOO_DISABLED	| \
					 SDRAM_MCOPT1_DREF_NORMAL)
#define CONFIG_SYS_SDRAM0_MCOPT2	0x00000000
#define CONFIG_SYS_SDRAM0_MODT0		SDRAM_MODT_EB0W_ENABLE
#define CONFIG_SYS_SDRAM0_MODT1		0x00000000
#define CONFIG_SYS_SDRAM0_MODT2		0x00000000
#define CONFIG_SYS_SDRAM0_MODT3		0x00000000
#define CONFIG_SYS_SDRAM0_CODT		(SDRAM_CODT_RK0R_ON		| \
					 SDRAM_CODT_DQS_1_8_V_DDR2	| \
					 SDRAM_CODT_IO_NMODE)
#define CONFIG_SYS_SDRAM0_RTR		SDRAM_RTR_RINT_ENCODE(1560)
#define CONFIG_SYS_SDRAM0_INITPLR0					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(80)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_NOP))
#define CONFIG_SYS_SDRAM0_INITPLR1					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(3)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_PRECHARGE)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_MR)				| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_PRECHARGE_ALL))
#define CONFIG_SYS_SDRAM0_INITPLR2					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(2)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_EMR)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_EMR2)			| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_EMR2_TEMP_COMMERCIAL))
#define CONFIG_SYS_SDRAM0_INITPLR3					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(2)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_EMR)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_EMR3)			| \
	 SDRAM_INITPLR_IMA_ENCODE(0))
#define CONFIG_SYS_SDRAM0_INITPLR4					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(2)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_EMR)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_EMR)				| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_EMR_DQS_ENABLE		| \
				  JEDEC_MA_EMR_RTT_150OHM))
#define CONFIG_SYS_SDRAM0_INITPLR5					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(200)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_EMR)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_MR)				| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_MR_WR_DDR2_3_CYC		| \
				  CAS_LATENCY				| \
				  JEDEC_MA_MR_BLEN_4			| \
				  JEDEC_MA_MR_DLL_RESET))
#define CONFIG_SYS_SDRAM0_INITPLR6					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(3)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_PRECHARGE)			| \
	 SDRAM_INITPLR_IBA_ENCODE(0x0)					| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_PRECHARGE_ALL))
#define CONFIG_SYS_SDRAM0_INITPLR7					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(26)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_REFRESH))
#define CONFIG_SYS_SDRAM0_INITPLR8					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(26)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_REFRESH))
#define CONFIG_SYS_SDRAM0_INITPLR9					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(26)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_REFRESH))
#define CONFIG_SYS_SDRAM0_INITPLR10					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(26)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_REFRESH))
#define CONFIG_SYS_SDRAM0_INITPLR11					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(2)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_EMR)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_MR)				| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_MR_WR_DDR2_3_CYC		| \
				  CAS_LATENCY				| \
				  JEDEC_MA_MR_BLEN_4))
#define CONFIG_SYS_SDRAM0_INITPLR12					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(2)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_EMR)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_EMR)				| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_EMR_OCD_ENTER		| \
				  JEDEC_MA_EMR_RDQS_DISABLE		| \
				  JEDEC_MA_EMR_DQS_ENABLE		| \
				  JEDEC_MA_EMR_RTT_150OHM		| \
				  JEDEC_MA_EMR_ODS_NORMAL))
#define CONFIG_SYS_SDRAM0_INITPLR13					\
	(SDRAM_INITPLR_ENABLE						| \
	 SDRAM_INITPLR_IMWT_ENCODE(2)					| \
	 SDRAM_INITPLR_ICMD_ENCODE(JEDEC_CMD_EMR)			| \
	 SDRAM_INITPLR_IBA_ENCODE(JEDEC_BA_EMR)				| \
	 SDRAM_INITPLR_IMA_ENCODE(JEDEC_MA_EMR_OCD_EXIT			| \
				  JEDEC_MA_EMR_RDQS_DISABLE		| \
				  JEDEC_MA_EMR_DQS_ENABLE		| \
				  JEDEC_MA_EMR_RTT_150OHM		| \
				  JEDEC_MA_EMR_ODS_NORMAL))
#define CONFIG_SYS_SDRAM0_INITPLR14	SDRAM_INITPLR_DISABLE
#define CONFIG_SYS_SDRAM0_INITPLR15	SDRAM_INITPLR_DISABLE
#define CONFIG_SYS_SDRAM0_RQDC		(SDRAM_RQDC_RQDE_ENABLE		| \
					 SDRAM_RQDC_RQFD_ENCODE(56))
#define CONFIG_SYS_SDRAM0_RFDC		SDRAM_RFDC_RFFD_ENCODE(599)
#define CONFIG_SYS_SDRAM0_RDCC		(SDRAM_RDCC_RDSS_T2)
#define CONFIG_SYS_SDRAM0_DLCR		(SDRAM_DLCR_DCLM_AUTO		| \
					 SDRAM_DLCR_DLCS_CONT_DONE	| \
					 SDRAM_DLCR_DLCV_ENCODE(155))
#define CONFIG_SYS_SDRAM0_CLKTR		SDRAM_CLKTR_CLKP_90_DEG_ADV
#define CONFIG_SYS_SDRAM0_WRDTR		SDRAM_WRDTR_WTR_90_DEG_ADV
#define CONFIG_SYS_SDRAM0_SDTR1		(SDRAM_SDTR1_LDOF_2_CLK		| \
					 SDRAM_SDTR1_RTW_2_CLK		| \
					 SDRAM_SDTR1_RTRO_1_CLK)
#define CONFIG_SYS_SDRAM0_SDTR2		(SDRAM_SDTR2_RCD_3_CLK		| \
					 SDRAM_SDTR2_WTR_2_CLK		| \
					 SDRAM_SDTR2_XSNR_32_CLK	| \
					 SDRAM_SDTR2_WPC_4_CLK		| \
					 SDRAM_SDTR2_RPC_2_CLK		| \
					 SDRAM_SDTR2_RP_3_CLK		| \
					 SDRAM_SDTR2_RRD_2_CLK)
#define CONFIG_SYS_SDRAM0_SDTR3		(SDRAM_SDTR3_RAS_ENCODE(8)	| \
					 SDRAM_SDTR3_RC_ENCODE(11)	| \
					 SDRAM_SDTR3_XCS		| \
					 SDRAM_SDTR3_RFC_ENCODE(26))
#define CONFIG_SYS_SDRAM0_MMODE		(SDRAM_MMODE_WR_DDR2_3_CYC	| \
					 CAS_LATENCY			| \
					 SDRAM_MMODE_BLEN_4)
#define CONFIG_SYS_SDRAM0_MEMODE	(SDRAM_MEMODE_DQS_ENABLE	| \
					 SDRAM_MEMODE_RTT_150OHM)

/*
 * I2C
 */
#define CONFIG_SYS_I2C_SPEED			400000	/* I2C speed */

#define CONFIG_SYS_I2C_MULTI_EEPROMS
#define CONFIG_SYS_I2C_EEPROM_ADDR		(0xa8>>1)
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	3
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10

/* I2C bootstrap EEPROM */
#define CONFIG_4xx_CONFIG_I2C_EEPROM_ADDR	0x52
#define CONFIG_4xx_CONFIG_I2C_EEPROM_OFFSET	0
#define CONFIG_4xx_CONFIG_BLOCKSIZE		16

/*
 * Ethernet
 */
#define CONFIG_IBM_EMAC4_V4	1

#define CONFIG_HAS_ETH0

#define CONFIG_PHY_ADDR		1	/* PHY address, See schematics	*/
#define CONFIG_M88E1111_PHY
/* Disable fiber since fiber/copper auto-selection doesn't seem to work */
#define CONFIG_M88E1111_DISABLE_FIBER

#define CONFIG_PHY_RESET	1	/* reset phy upon startup	*/
#define CONFIG_PHY_GIGE		1	/* Include GbE speed/duplex detection */
#define CONFIG_PHY_DYNAMIC_ANEG	1

/*
 * Default environment variables
 */
#define CONFIG_EXTRA_ENV_SETTINGS					\
	CONFIG_AMCC_DEF_ENV						\
	CONFIG_AMCC_DEF_ENV_POWERPC					\
	CONFIG_AMCC_DEF_ENV_NOR_UPD					\
	"kernel_addr=fc000000\0"					\
	"fdt_addr=fc1e0000\0"						\
	"ramdisk_addr=fc200000\0"					\
	"pciconfighost=1\0"						\
	"pcie_mode=RP:RP\0"						\
	"unlock=yes\0"							\
	""

/*
 * Commands additional to the ones defined in amcc-common.h
 */
#define CONFIG_CMD_CHIP_CONFIG
#define CONFIG_CMD_ECCTEST
#define CONFIG_CMD_PCI
#define CONFIG_CMD_SDRAM

/*
 * PCI stuff
 */
/* General PCI */
#define CONFIG_PCI			/* include pci support	        */
#define CONFIG_PCI_PNP			/* do pci plug-and-play   */
#define CONFIG_PCI_SCAN_SHOW		/* show pci devices on startup  */
#define CONFIG_PCI_CONFIG_HOST_BRIDGE

/* Board-specific PCI, no PCI support, only PCIe */
#undef CONFIG_SYS_PCI_TARGET_INIT
#undef CONFIG_SYS_PCI_MASTER_INIT

#define CONFIG_SYS_PCI_SUBSYS_VENDORID 0x1014	/* IBM */
#define CONFIG_SYS_PCI_SUBSYS_DEVICEID 0xcafe	/* Whatever */


/*
 * External Bus Controller (EBC) Setup
 */

/*
 * T3CORP has 64MBytes of NOR flash (Spansion 29GL512), but the
 * boot EBC mapping only supports a maximum of 16MBytes
 * (4.ff00.0000 - 4.ffff.ffff).
 * To solve this problem, the flash has to get remapped to another
 * EBC address which accepts bigger regions:
 *
 * 0xfc00.0000 -> 4.cc00.0000
 */

/* Memory Bank 0 (NOR-flash) */
#define CONFIG_SYS_EBC_PB0AP	(EBC_BXAP_BME_DISABLED		|	\
				 EBC_BXAP_TWT_ENCODE(16)	|	\
				 EBC_BXAP_BCE_DISABLE		|	\
				 EBC_BXAP_BCT_2TRANS		|	\
				 EBC_BXAP_CSN_ENCODE(1)		|	\
				 EBC_BXAP_OEN_ENCODE(1)		|	\
				 EBC_BXAP_WBN_ENCODE(1)		|	\
				 EBC_BXAP_WBF_ENCODE(1)		|	\
				 EBC_BXAP_TH_ENCODE(7)		|	\
				 EBC_BXAP_RE_DISABLED		|	\
				 EBC_BXAP_SOR_DELAYED		|	\
				 EBC_BXAP_BEM_WRITEONLY		|	\
				 EBC_BXAP_PEN_DISABLED)
#define CONFIG_SYS_EBC_PB0CR	(EBC_BXCR_BAS_ENCODE(CONFIG_SYS_BOOT_BASE_ADDR) | \
				 EBC_BXCR_BS_16MB		|	\
				 EBC_BXCR_BU_RW			|	\
				 EBC_BXCR_BW_16BIT)

/* Memory Bank 1 (FPGA 1) */
#define CONFIG_SYS_EBC_PB1AP	(EBC_BXAP_BME_DISABLED		|	\
				 EBC_BXAP_TWT_ENCODE(5)		|	\
				 EBC_BXAP_CSN_ENCODE(0)		|	\
				 EBC_BXAP_OEN_ENCODE(3)		|	\
				 EBC_BXAP_WBN_ENCODE(0)		|	\
				 EBC_BXAP_WBF_ENCODE(0)		|	\
				 EBC_BXAP_TH_ENCODE(1)		|	\
				 EBC_BXAP_RE_ENABLED		|	\
				 EBC_BXAP_SOR_DELAYED		|	\
				 EBC_BXAP_BEM_RW		|	\
				 EBC_BXAP_PEN_DISABLED)
#define CONFIG_SYS_EBC_PB1CR	(EBC_BXCR_BAS_ENCODE(CONFIG_SYS_FPGA1_BASE) | \
				 EBC_BXCR_BS_32MB		|	\
				 EBC_BXCR_BU_RW			|	\
				 EBC_BXCR_BW_32BIT)

/* Memory Bank 2 (FPGA 2) */
#define CONFIG_SYS_EBC_PB2AP	(EBC_BXAP_BME_DISABLED		|	\
				 EBC_BXAP_TWT_ENCODE(5)		|	\
				 EBC_BXAP_CSN_ENCODE(0)		|	\
				 EBC_BXAP_OEN_ENCODE(3)		|	\
				 EBC_BXAP_WBN_ENCODE(0)		|	\
				 EBC_BXAP_WBF_ENCODE(0)		|	\
				 EBC_BXAP_TH_ENCODE(1)		|	\
				 EBC_BXAP_RE_ENABLED		|	\
				 EBC_BXAP_SOR_DELAYED		|	\
				 EBC_BXAP_BEM_RW		|	\
				 EBC_BXAP_PEN_DISABLED)
#define CONFIG_SYS_EBC_PB2CR	(EBC_BXCR_BAS_ENCODE(CONFIG_SYS_FPGA2_BASE) | \
				 EBC_BXCR_BS_16MB		|	\
				 EBC_BXCR_BU_RW			|	\
				 EBC_BXCR_BW_32BIT)

/* Memory Bank 3 (FPGA 3) */
#define CONFIG_SYS_EBC_PB3AP	(EBC_BXAP_BME_DISABLED		|	\
				 EBC_BXAP_TWT_ENCODE(5)		|	\
				 EBC_BXAP_CSN_ENCODE(0)		|	\
				 EBC_BXAP_OEN_ENCODE(3)		|	\
				 EBC_BXAP_WBN_ENCODE(0)		|	\
				 EBC_BXAP_WBF_ENCODE(0)		|	\
				 EBC_BXAP_TH_ENCODE(1)		|	\
				 EBC_BXAP_RE_ENABLED		|	\
				 EBC_BXAP_SOR_DELAYED		|	\
				 EBC_BXAP_BEM_RW		|	\
				 EBC_BXAP_PEN_DISABLED)
#define CONFIG_SYS_EBC_PB3CR	(EBC_BXCR_BAS_ENCODE(CONFIG_SYS_FPGA3_BASE) | \
				 EBC_BXCR_BS_16MB		|	\
				 EBC_BXCR_BU_RW			|	\
				 EBC_BXCR_BW_32BIT)

/*
 * PPC4xx GPIO Configuration
 */

#define CONFIG_SYS_4xx_GPIO_TABLE { /*		  GPIO	Alternate1	Alternate2	Alternate3 */ \
{											\
/* GPIO Core 0 */									\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO0	GMC1TxD(0)	USB2HostD(0)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO1	GMC1TxD(1)	USB2HostD(1)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO2	GMC1TxD(2)	USB2HostD(2)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO3	GMC1TxD(3)	USB2HostD(3)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO4	GMC1TxD(4)	USB2HostD(4)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO5	GMC1TxD(5)	USB2HostD(5)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO6	GMC1TxD(6)	USB2HostD(6)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO7	GMC1TxD(7)	USB2HostD(7)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO8	GMC1RxD(0)	USB2OTGD(0)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO9	GMC1RxD(1)	USB2OTGD(1)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO10 GMC1RxD(2)	USB2OTGD(2)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO11 GMC1RxD(3)	USB2OTGD(3)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO12 GMC1RxD(4)	USB2OTGD(4)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO13 GMC1RxD(5)	USB2OTGD(5)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO14 GMC1RxD(6)	USB2OTGD(6)	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO15 GMC1RxD(7)	USB2OTGD(7)	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO16 GMC1TxER	USB2HostStop	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO17 GMC1CD		USB2HostNext	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO18 GMC1RxER	USB2HostDir	*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO19 GMC1TxEN	USB2OTGStop	*/	\
{GPIO0_BASE, GPIO_BI , GPIO_ALT1, GPIO_OUT_0}, /* GPIO20 GMC1CRS	USB2OTGNext	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO21 GMC1RxDV	USB2OTGDir	*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO22 NFRDY				*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO23 NFREN				*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO24 NFWEN				*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO25 NFCLE				*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO26 NFALE				*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO27 IRQ(0)				*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO28 IRQ(1)				*/	\
{GPIO0_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO29 IRQ(2)				*/	\
{GPIO0_BASE, GPIO_OUT, GPIO_SEL , GPIO_OUT_1}, /* GPIO30 PerPar0	DMAReq2		IRQ(7)*/ \
{GPIO0_BASE, GPIO_OUT, GPIO_SEL , GPIO_OUT_1}, /* GPIO31 PerPar1	DMAAck2		IRQ(8)*/ \
},											\
{											\
/* GPIO Core 1 */									\
{GPIO1_BASE, GPIO_OUT, GPIO_SEL , GPIO_OUT_1}, /* GPIO32 PerPar2	EOT2/TC2	IRQ(9)*/ \
{GPIO1_BASE, GPIO_OUT, GPIO_SEL , GPIO_OUT_1}, /* GPIO33 PerPar3	DMAReq3		IRQ(4)*/ \
{GPIO1_BASE, GPIO_OUT, GPIO_ALT3, GPIO_OUT_1}, /* GPIO34 UART0_DCD_N	UART1_DSR_CTS_N	UART2_SOUT*/ \
{GPIO1_BASE, GPIO_IN , GPIO_ALT3, GPIO_OUT_0}, /* GPIO35 UART0_8PIN_DSR_N UART1_RTS_DTR_N UART2_SIN*/ \
{GPIO1_BASE, GPIO_IN , GPIO_ALT3, GPIO_OUT_0}, /* GPIO36 UART0_8PIN_CTS_N DMAAck3	UART3_SIN*/ \
{GPIO1_BASE, GPIO_BI , GPIO_ALT2, GPIO_OUT_0}, /* GPIO37 UART0_RTS_N	EOT3/TC3	UART3_SOUT*/ \
{GPIO1_BASE, GPIO_OUT, GPIO_ALT2, GPIO_OUT_1}, /* GPIO38 UART0_DTR_N	UART1_SOUT	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_ALT2, GPIO_OUT_0}, /* GPIO39 UART0_RI_N	UART1_SIN	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_ALT1, GPIO_OUT_0}, /* GPIO40 IRQ(3)				*/	\
{GPIO1_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO41 CS(1)				*/	\
{GPIO1_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO42 CS(2)				*/	\
{GPIO1_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO43 CS(3)		DMAReq1		IRQ(10)*/ \
{GPIO1_BASE, GPIO_IN , GPIO_ALT3, GPIO_OUT_0}, /* GPIO44 CS(4)		DMAAck1		IRQ(11)*/ \
{GPIO1_BASE, GPIO_IN , GPIO_ALT3, GPIO_OUT_0}, /* GPIO45 CS(5)		EOT/TC1		IRQ(12)*/ \
{GPIO1_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO46 PerAddr(5)	DMAReq0		IRQ(13)*/ \
{GPIO1_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO47 PerAddr(6)	DMAAck0		IRQ(14)*/ \
{GPIO1_BASE, GPIO_OUT, GPIO_ALT1, GPIO_OUT_0}, /* GPIO48 PerAddr(7)	EOT/TC0		IRQ(15)*/ \
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO49  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO50  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO51  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO52  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO53  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO54  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO55  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO56  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO57  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO58  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO59  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO60  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO61  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO62  Unselect via TraceSelect Bit	*/	\
{GPIO1_BASE, GPIO_IN , GPIO_SEL , GPIO_OUT_0}, /* GPIO63  Unselect via TraceSelect Bit	*/	\
}											\
}

#endif	/* __CONFIG_H */
