/*
 * (C) Copyright 2011
 * Stefano Babic, DENX Software Engineering, sbabic@denx.de.
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

#ifndef __ASM_ARCH_CLOCK_H
#define __ASM_ARCH_CLOCK_H

#include <common.h>

#ifdef CONFIG_MX35_HCLK_FREQ
#define MXC_HCLK	CONFIG_MX35_HCLK_FREQ
#else
#define MXC_HCLK	24000000
#endif

#ifdef CONFIG_MX35_CLK32
#define MXC_CLK32	CONFIG_MX35_CLK32
#else
#define MXC_CLK32	32768
#endif

enum mxc_clock {
	MXC_ARM_CLK,
	MXC_AHB_CLK,
	MXC_IPG_CLK,
	MXC_IPG_PERCLK,
	MXC_UART_CLK,
	MXC_ESDHC_CLK,
	MXC_USB_CLK,
	MXC_CSPI_CLK,
	MXC_FEC_CLK,
};

enum mxc_main_clock {
	CPU_CLK,
	AHB_CLK,
	IPG_CLK,
	IPG_PER_CLK,
	NFC_CLK,
	USB_CLK,
	HSP_CLK,
};

enum mxc_peri_clock {
	UART1_BAUD,
	UART2_BAUD,
	UART3_BAUD,
	SSI1_BAUD,
	SSI2_BAUD,
	CSI_BAUD,
	MSHC_CLK,
	ESDHC1_CLK,
	ESDHC2_CLK,
	ESDHC3_CLK,
	SPDIF_CLK,
	SPI1_CLK,
	SPI2_CLK,
};

u32 imx_get_uartclk(void);
u32 imx_get_fecclk(void);
unsigned int mxc_get_clock(enum mxc_clock clk);

#endif /* __ASM_ARCH_CLOCK_H */
