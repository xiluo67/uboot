/*
 * Configuation settings for the Renesas Technology R0P7785LC0011RL board
 *
 * Copyright (C) 2008 Yoshihiro Shimoda <shimoda.yoshihiro@renesas.com>
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

#ifndef __SH7785LCR_H
#define __SH7785LCR_H

#undef DEBUG
#define CONFIG_SH		1
#define CONFIG_SH4A		1
#define CONFIG_CPU_SH7785	1
#define CONFIG_SH7785LCR	1

#define CONFIG_CMD_FLASH
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_PCI
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_NFS
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_RUN
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_SH_ZIMAGEBOOT

#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#define CONFIG_MAC_PARTITION

#define CONFIG_BAUDRATE		115200
#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTARGS		"console=ttySC1,115200 root=/dev/nfs ip=dhcp"

#define CONFIG_EXTRA_ENV_SETTINGS					\
	"bootdevice=0:1\0"						\
	"usbload=usb reset;usbboot;usb stop;bootm\0"

#define CONFIG_VERSION_VARIABLE
#undef	CONFIG_SHOW_BOOT_PROGRESS

/* MEMORY */
#if defined(CONFIG_SH_32BIT)
#define CONFIG_SYS_TEXT_BASE		0x8FF80000
/* 0x40000000 - 0x47FFFFFF does not use */
#define CONFIG_SH_SDRAM_OFFSET		(0x8000000)
#define SH7785LCR_SDRAM_PHYS_BASE	(0x40000000 + CONFIG_SH_SDRAM_OFFSET)
#define SH7785LCR_SDRAM_BASE		(0x80000000 + CONFIG_SH_SDRAM_OFFSET)
#define SH7785LCR_SDRAM_SIZE		(384 * 1024 * 1024)
#define SH7785LCR_FLASH_BASE_1		(0xa0000000)
#define SH7785LCR_FLASH_BANK_SIZE	(64 * 1024 * 1024)
#define SH7785LCR_USB_BASE		(0xa6000000)
#else
#define CONFIG_SYS_TEXT_BASE		0x0FF80000
#define SH7785LCR_SDRAM_BASE		(0x08000000)
#define SH7785LCR_SDRAM_SIZE		(128 * 1024 * 1024)
#define SH7785LCR_FLASH_BASE_1		(0xa0000000)
#define SH7785LCR_FLASH_BANK_SIZE	(64 * 1024 * 1024)
#define SH7785LCR_USB_BASE		(0xb4000000)
#endif

#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT		"=> "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		256
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		512
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200 }

/* SCIF */
#define CONFIG_SCIF_CONSOLE	1
#define CONFIG_CONS_SCIF1	1
#define CONFIG_SCIF_EXT_CLOCK	1
#undef	CONFIG_SYS_CONSOLE_INFO_QUIET
#undef	CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#undef	CONFIG_SYS_CONSOLE_ENV_OVERWRITE


#define CONFIG_SYS_MEMTEST_START	(SH7785LCR_SDRAM_BASE)
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + \
					(SH7785LCR_SDRAM_SIZE) - \
					 4 * 1024 * 1024)
#undef	CONFIG_SYS_ALT_MEMTEST
#undef	CONFIG_SYS_MEMTEST_SCRATCH
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE

#define CONFIG_SYS_SDRAM_BASE	(SH7785LCR_SDRAM_BASE)
#define CONFIG_SYS_SDRAM_SIZE	(SH7785LCR_SDRAM_SIZE)
#define CONFIG_SYS_LOAD_ADDR	(CONFIG_SYS_SDRAM_BASE + 16 * 1024 * 1024)

#define CONFIG_SYS_MONITOR_BASE	(SH7785LCR_FLASH_BASE_1)
#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(512 * 1024)
#define CONFIG_SYS_BOOTMAPSZ		(8 * 1024 * 1024)

/* FLASH */
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#undef	CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_BASE		(SH7785LCR_FLASH_BASE_1)
#define CONFIG_SYS_MAX_FLASH_SECT	512

#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE + \
				 (0 * SH7785LCR_FLASH_BANK_SIZE) }

#define CONFIG_SYS_FLASH_ERASE_TOUT	(3 * 1000)
#define CONFIG_SYS_FLASH_WRITE_TOUT	(3 * 1000)
#define CONFIG_SYS_FLASH_LOCK_TOUT	(3 * 1000)
#define CONFIG_SYS_FLASH_UNLOCK_TOUT	(3 * 1000)

#undef	CONFIG_SYS_FLASH_PROTECTION
#undef	CONFIG_SYS_DIRECT_FLASH_TFTP

/* R8A66597 */
#define CONFIG_USB_R8A66597_HCD
#define CONFIG_R8A66597_BASE_ADDR	SH7785LCR_USB_BASE
#define CONFIG_R8A66597_XTAL		0x0000	/* 12MHz */
#define CONFIG_R8A66597_LDRV		0x8000	/* 3.3V */
#define CONFIG_R8A66597_ENDIAN		0x0000	/* little */

/* PCI Controller */
#define CONFIG_PCI
#define CONFIG_SH4_PCI
#define CONFIG_SH7780_PCI
#if defined(CONFIG_SH_32BIT)
#define CONFIG_SH7780_PCI_LSR	0x1ff00001
#define CONFIG_SH7780_PCI_LAR	0x5f000000
#define CONFIG_SH7780_PCI_BAR	0x5f000000
#else
#define CONFIG_SH7780_PCI_LSR	0x07f00001
#define CONFIG_SH7780_PCI_LAR	CONFIG_SYS_SDRAM_SIZE
#define CONFIG_SH7780_PCI_BAR	CONFIG_SYS_SDRAM_SIZE
#endif
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW	1

#define CONFIG_PCI_MEM_BUS	0xFD000000	/* Memory space base addr */
#define CONFIG_PCI_MEM_PHYS	CONFIG_PCI_MEM_BUS
#define CONFIG_PCI_MEM_SIZE	0x01000000	/* Size of Memory window */

#define CONFIG_PCI_IO_BUS	0xFE200000	/* IO space base address */
#define CONFIG_PCI_IO_PHYS	CONFIG_PCI_IO_BUS
#define CONFIG_PCI_IO_SIZE	0x00200000	/* Size of IO window */

#if defined(CONFIG_SH_32BIT)
#define CONFIG_PCI_SYS_PHYS	SH7785LCR_SDRAM_PHYS_BASE
#else
#define CONFIG_PCI_SYS_PHYS	CONFIG_SYS_SDRAM_BASE
#endif
#define CONFIG_PCI_SYS_BUS	CONFIG_SYS_SDRAM_BASE
#define CONFIG_PCI_SYS_SIZE	CONFIG_SYS_SDRAM_SIZE

/* Network device (RTL8169) support */
#define CONFIG_RTL8169

/* ENV setting */
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_OVERWRITE	1
#define CONFIG_ENV_SECT_SIZE	(256 * 1024)
#define CONFIG_ENV_SIZE		(CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + CONFIG_SYS_MONITOR_LEN)
#define CONFIG_ENV_OFFSET		(CONFIG_ENV_ADDR - CONFIG_SYS_FLASH_BASE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SECT_SIZE)

/* Board Clock */
/* The SCIF used external clock. system clock only used timer. */
#define CONFIG_SYS_CLK_FREQ	50000000
#define CONFIG_SYS_TMU_CLK_DIV		4
#define CONFIG_SYS_HZ		1000

#endif	/* __SH7785LCR_H */
