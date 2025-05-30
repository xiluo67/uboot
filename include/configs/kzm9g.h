/*
 * Copyright (C) 2012 Nobuhiro Iwamatsu <nobuhiro.iwamatsu.yj@renesas.com>
 * Copyright (C) 2012 Renesas Solutions Corp.
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

#ifndef __KZM9G_H
#define __KZM9G_H

#undef DEBUG

#define CONFIG_RMOBILE
#define CONFIG_SH73A0
#define CONFIG_KZM_A9_GT
#define CONFIG_RMOBILE_BOARD_STRING	"KMC KZM-A9-GT"
#define CONFIG_MACH_TYPE MACH_TYPE_KZM9G

#include <asm/arch/rmobile.h>

#define CONFIG_ARCH_CPU_INIT
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_L2_OFF
#define CONFIG_OF_LIBFDT

#include <config_cmd_default.h>
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_DOS_PARTITION
#define CONFIG_CMD_FAT
#define CONFIG_CMD_BOOTZ

#define CONFIG_BAUDRATE		115200
#define CONFIG_BOOTARGS		"root=/dev/null console=ttySC4,115200"
#define CONFIG_BOOTDELAY 3

#define CONFIG_VERSION_VARIABLE
#undef  CONFIG_SHOW_BOOT_PROGRESS

/* MEMORY */
#define KZM_SDRAM_BASE	(0x40000000)
#define PHYS_SDRAM		KZM_SDRAM_BASE
#define PHYS_SDRAM_SIZE		(512 * 1024 * 1024)
#define CONFIG_NR_DRAM_BANKS	(1)

/* NOR Flash */
#define KZM_FLASH_BASE	(0x00000000)
#define CONFIG_SYS_FLASH_BASE		(KZM_FLASH_BASE)
#define CONFIG_SYS_FLASH_CFI_WIDTH	(FLASH_CFI_16BIT)
#define CONFIG_SYS_MAX_FLASH_BANKS	(1)
#define CONFIG_SYS_MAX_FLASH_SECT	(512)

/* prompt */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT		"KZM-A9-GT# "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		256
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		512
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200 }

/* SCIF */
#define CONFIG_SCIF_CONSOLE
#define CONFIG_CONS_SCIF4
#undef  CONFIG_SYS_CONSOLE_INFO_QUIET
#undef  CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#undef  CONFIG_SYS_CONSOLE_ENV_OVERWRITE

#define CONFIG_SYS_MEMTEST_START	(KZM_SDRAM_BASE)
#define CONFIG_SYS_MEMTEST_END \
	(CONFIG_SYS_MEMTEST_START + (60 * 1024 * 1024))
#undef  CONFIG_SYS_ALT_MEMTEST
#undef  CONFIG_SYS_MEMTEST_SCRATCH
#undef  CONFIG_SYS_LOADS_BAUD_CHANGE

#define CONFIG_SYS_INIT_RAM_ADDR	(0xE5600000) /* on MERAM */
#define CONFIG_SYS_INIT_RAM_SIZE	(0x10000)
#define LOW_LEVEL_MERAM_STACK		(CONFIG_SYS_INIT_RAM_ADDR - 4)
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					 CONFIG_SYS_INIT_RAM_SIZE - \
					 GENERATED_GBL_DATA_SIZE)
#define CONFIG_SDRAM_OFFSET_FOR_RT	(16 * 1024 * 1024)
#define CONFIG_SYS_SDRAM_BASE	(KZM_SDRAM_BASE + CONFIG_SDRAM_OFFSET_FOR_RT)
#define CONFIG_SYS_SDRAM_SIZE	(PHYS_SDRAM_SIZE - CONFIG_SDRAM_OFFSET_FOR_RT)
#define CONFIG_SYS_LOAD_ADDR	(CONFIG_SYS_SDRAM_BASE + 32 * 1024 * 1024)

#define CONFIG_SYS_MONITOR_BASE	(KZM_FLASH_BASE)
#define CONFIG_SYS_MALLOC_LEN	(CONFIG_ENV_SIZE + 128 * 1024)
#define CONFIG_SYS_GBL_DATA_SIZE	(256)
#define CONFIG_SYS_BOOTMAPSZ	(8 * 1024 * 1024)

#define CONFIG_SYS_TEXT_BASE		0x00000000
#define CONFIG_STANDALONE_LOAD_ADDR	0x41000000

/* FLASH */
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#undef  CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define FLASH_SECTOR_SIZE	(256 * 1024)	/* 256 KB sectors */
#define CONFIG_ENV_SIZE		FLASH_SECTOR_SIZE
#define CONFIG_ENV_OFFSET	FLASH_SECTOR_SIZE
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + CONFIG_ENV_OFFSET)

/* Timeout for Flash erase operations (in ms) */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(3 * 1000)
/* Timeout for Flash write operations (in ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(3 * 1000)
/* Timeout for Flash set sector lock bit operations (in ms) */
#define CONFIG_SYS_FLASH_LOCK_TOUT		(3 * 1000)
/* Timeout for Flash clear lock bit operations (in ms) */
#define CONFIG_SYS_FLASH_UNLOCK_TOUT	(3 * 1000)

#undef  CONFIG_SYS_FLASH_PROTECTION
#undef  CONFIG_SYS_DIRECT_FLASH_TFTP
#define CONFIG_ENV_IS_IN_FLASH

/* GPIO / PFC */
#define CONFIG_SH_GPIO_PFC

/* Clock */
#define CONFIG_GLOBAL_TIMER
#define CONFIG_SYS_CLK_FREQ	(48000000)
#define CONFIG_SYS_CPU_CLK	(1196000000)
#define TMU_CLK_DIVIDER		(4)	/* 4 (default), 16, 64, 256 or 1024 */
#define CFG_HZ              (1000)
#define CONFIG_SYS_HZ		CFG_HZ

/* Ether */
#define CONFIG_NET_MULTI
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_SMC911X
#define CONFIG_SMC911X_BASE	(0x10000000)
#define CONFIG_SMC911X_32_BIT
#define CONFIG_NFS_TIMEOUT 10000UL

/* I2C */
#define CONFIG_CMD_I2C
#define CONFIG_SH_I2C 1
#define CONFIG_HARD_I2C
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_MAX_I2C_BUS  (2)
#define CONFIG_SYS_I2C_MODULE
#define CONFIG_SYS_I2C_SPEED    (100000) /* 100 kHz */
#define CONFIG_SYS_I2C_SLAVE    (0x7F)
#define CONFIG_SH_I2C_DATA_HIGH (4)
#define CONFIG_SH_I2C_DATA_LOW  (5)
#define CONFIG_SH_I2C_CLOCK     (41666666)
#define CONFIG_SH_I2C_BASE0     (0xE6820000)
#define CONFIG_SH_I2C_BASE1     (0xE6822000)

#endif /* __KZM9G_H */
