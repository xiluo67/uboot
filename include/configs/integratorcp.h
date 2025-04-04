/*
 * (C) Copyright 2003
 * Texas Instruments.
 * Kshitij Gupta <kshitij@ti.com>
 * Configuation settings for the TI OMAP Innovator board.
 *
 * (C) Copyright 2004
 * ARM Ltd.
 * Philippe Robin, <philippe.robin@arm.com>
 * Configuration for Compact Integrator board.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "integrator-common.h"

/* Integrator CP-specific configuration */
#define CONFIG_ARCH_CINTEGRATOR
#define CONFIG_SYS_HZ_CLOCK		1000000	/* Timer 1 is clocked at 1Mhz */

/*
 * Hardware drivers
 */
#define CONFIG_SMC91111
#define CONFIG_SMC_USE_32_BIT
#define CONFIG_SMC91111_BASE    0xC8000000
#undef CONFIG_SMC91111_EXT_PHY

/* PL011 configuration */
#define CONFIG_PL011_SERIAL
#define CONFIG_PL011_CLOCK	14745600
#define CONFIG_PL01x_PORTS	{ (void *)CONFIG_SYS_SERIAL0, (void *)CONFIG_SYS_SERIAL1 }
#define CONFIG_CONS_INDEX	0
#define CONFIG_BAUDRATE		38400
#define CONFIG_SYS_SERIAL0		0x16000000
#define CONFIG_SYS_SERIAL1		0x17000000

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_BOOTDELAY	2
#define CONFIG_BOOTARGS	"root=/dev/mtdblock0 console=ttyAMA0 console=tty ip=dhcp netdev=27,0,0xfc800000,0xfc800010,eth0 video=clcdfb:0"
#define CONFIG_BOOTCOMMAND "tftpboot ; bootm"
#define CONFIG_SERVERIP 192.168.1.100
#define CONFIG_IPADDR 192.168.1.104
#define CONFIG_BOOTFILE "uImage"

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_PROMPT	"Integrator-CP # "	/* Monitor Command Prompt */

/*
 * FLASH and environment organization
 * Top varies according to amount fitted
 * Reserve top 4 blocks of flash
 * - ARM Boot Monitor
 * - Unused
 * - SIB block
 * - U-Boot environment
 *
 * Base is always 0x24000000
 */
#define CONFIG_SYS_FLASH_BASE		0x24000000
#define CONFIG_SYS_FLASH_CFI		1
#define CONFIG_FLASH_CFI_DRIVER		1
#define CONFIG_SYS_MAX_FLASH_SECT	64
#define CONFIG_SYS_MAX_FLASH_BANKS	1		/* max number of memory banks */
#define PHYS_FLASH_SIZE			0x01000000	/* 16MB */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(2*CONFIG_SYS_HZ)	/* Timeout for Flash Write */

#define CONFIG_SYS_MONITOR_LEN		0x00100000
#define CONFIG_ENV_IS_IN_FLASH	1

/*
 * Move up the U-Boot & monitor area if more flash is fitted.
 * If this U-Boot is to be run on Integrators with varying flash sizes,
 * drivers/mtd/cfi_flash.c::flash_init() can read the Integrator CP_FLASHPROG
 * register and dynamically assign CONFIG_ENV_ADDR & CONFIG_SYS_MONITOR_BASE
 * - CONFIG_SYS_MONITOR_BASE is set to indicate that the environment is not
 * embedded in the boot monitor(s) area
 */
#if ( PHYS_FLASH_SIZE == 0x04000000 )

#define CONFIG_ENV_ADDR		0x27F00000
#define CONFIG_SYS_MONITOR_BASE	0x27F40000

#elif (PHYS_FLASH_SIZE == 0x02000000 )

#define CONFIG_ENV_ADDR		0x25F00000
#define CONFIG_SYS_MONITOR_BASE	0x25F40000

#else

#define CONFIG_ENV_ADDR		0x24F00000
#define CONFIG_SYS_MONITOR_BASE	0x27F40000

#endif

#define CONFIG_ENV_SECT_SIZE	0x40000		/* 256KB */
#define CONFIG_ENV_SIZE		8192		/* 8KB */

#endif /* __CONFIG_H */
