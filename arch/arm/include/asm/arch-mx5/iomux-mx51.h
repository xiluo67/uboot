/*
 * Copyright (C) 2009-2010 Amit Kucheria <amit.kucheria@canonical.com>
 * Copyright (C) 2010 Freescale Semiconductor, Inc.
 * Copyright (C) 2009-2012 Genesi USA, Inc.
 *
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

/*
 * The vast majority of this file is taken from the Linux kernel at
 * commit 5d23b39
 */

#ifndef __IOMUX_MX51_H__
#define __IOMUX_MX51_H__

#include <asm/imx-common/iomux-v3.h>

#define PAD_CTL_DVS			(1 << 13)
#define PAD_CTL_INPUT_DDR		(1 << 9)
#define PAD_CTL_HYS			(1 << 8)

#define PAD_CTL_PKE			(1 << 7)
#define PAD_CTL_PUE			(1 << 6 | PAD_CTL_PKE)
#define PAD_CTL_PUS_100K_DOWN		(0 << 4 | PAD_CTL_PUE)
#define PAD_CTL_PUS_47K_UP		(1 << 4 | PAD_CTL_PUE)
#define PAD_CTL_PUS_100K_UP		(2 << 4 | PAD_CTL_PUE)
#define PAD_CTL_PUS_22K_UP		(3 << 4 | PAD_CTL_PUE)

#define PAD_CTL_ODE			(1 << 3)

#define PAD_CTL_DSE_LOW			(0 << 1)
#define PAD_CTL_DSE_MED			(1 << 1)
#define PAD_CTL_DSE_HIGH		(2 << 1)
#define PAD_CTL_DSE_MAX			(3 << 1)

#define PAD_CTL_SRE_FAST		(1 << 0)
#define PAD_CTL_SRE_SLOW		(0 << 0)

/* Pad control groupings */
#define MX51_UART_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_PUE | PAD_CTL_DSE_HIGH | \
				PAD_CTL_HYS | PAD_CTL_SRE_FAST)
#define MX51_I2C_PAD_CTRL	(PAD_CTL_SRE_FAST | PAD_CTL_ODE | \
				PAD_CTL_DSE_HIGH | PAD_CTL_PUS_100K_UP | \
				PAD_CTL_HYS)
#define MX51_ESDHC_PAD_CTRL	(PAD_CTL_SRE_FAST | PAD_CTL_ODE | \
				PAD_CTL_DSE_HIGH | PAD_CTL_PUS_100K_UP | \
				PAD_CTL_HYS)
#define MX51_USBH1_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_SRE_FAST | \
				PAD_CTL_DSE_HIGH | PAD_CTL_PUS_100K_UP | \
				PAD_CTL_HYS | PAD_CTL_PUE)
#define MX51_ECSPI_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_HYS | \
				PAD_CTL_DSE_HIGH | PAD_CTL_SRE_FAST)
#define MX51_SDHCI_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_DSE_HIGH | \
				PAD_CTL_PUS_47K_UP | PAD_CTL_PUE | \
				PAD_CTL_SRE_FAST | PAD_CTL_DVS)
#define MX51_GPIO_PAD_CTRL	(PAD_CTL_DSE_HIGH | PAD_CTL_PKE | PAD_CTL_SRE_FAST)

#define __NA_ 0x000

/*
 * The naming convention for the pad modes is MX51_PAD_<padname>__<padmode>
 * If <padname> or <padmode> refers to a GPIO, it is named GPIO<unit>_<num>
 * See also iomux-v3.h
 */

/*								PAD    MUX   ALT INPSE PATH PADCTRL */
enum {
	MX51_PAD_EIM_D16__USBH2_DATA0		= IOMUX_PAD(0x3f0, 0x05c, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D17__USBH2_DATA1		= IOMUX_PAD(0x3f4, 0x060, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D18__USBH2_DATA2		= IOMUX_PAD(0x3f8, 0x064, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D19__USBH2_DATA3		= IOMUX_PAD(0x3fc, 0x068, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D20__USBH2_DATA4		= IOMUX_PAD(0x400, 0x06c, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D21__USBH2_DATA5		= IOMUX_PAD(0x404, 0x070, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D22__USBH2_DATA6		= IOMUX_PAD(0x408, 0x074, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D23__USBH2_DATA7		= IOMUX_PAD(0x40c, 0x078, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_D27__GPIO2_9		= IOMUX_PAD(0x41c, 0x088, 1, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_EIM_A24__USBH2_CLK		= IOMUX_PAD(0x450, 0x0bc, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_A25__USBH2_DIR		= IOMUX_PAD(0x454, 0x0c0, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_A26__GPIO2_20		= IOMUX_PAD(0x458, 0x0c4, 1, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_EIM_A26__USBH2_STP		= IOMUX_PAD(0x458, 0x0c4, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_A27__USBH2_NXT		= IOMUX_PAD(0x45c, 0x0c8, 2, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_EIM_CS0__GPIO2_25		= IOMUX_PAD(0x474, 0x0e0, 1, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_EIM_CS2__SD1_CD		= IOMUX_PAD(0x47c, 0x0e8, 1, __NA_, 0, MX51_ESDHC_PAD_CTRL),
	MX51_PAD_EIM_CS3__GPIO2_28		= IOMUX_PAD(0x480, 0x0ec, 1, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_EIM_CS4__GPIO2_29		= IOMUX_PAD(0x484, 0x0f0, 1, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_NANDF_WE_B__PATA_DIOW		= IOMUX_PAD(0x4e4, 0x108, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_RE_B__PATA_DIOR		= IOMUX_PAD(0x4e8, 0x10c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_ALE__PATA_BUFFER_EN	= IOMUX_PAD(0x4ec, 0x110, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_CLE__PATA_RESET_B	= IOMUX_PAD(0x4f0, 0x114, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_WP_B__PATA_DMACK		= IOMUX_PAD(0x4f4, 0x118, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_RB0__PATA_DMARQ		= IOMUX_PAD(0x4f8, 0x11c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_RB1__PATA_IORDY		= IOMUX_PAD(0x4fc, 0x120, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_GPIO_NAND__PATA_INTRQ		= IOMUX_PAD(0x514, 0x12c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_CS2__PATA_CS_0		= IOMUX_PAD(0x520, 0x138, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_CS3__PATA_CS_1		= IOMUX_PAD(0x524, 0x13c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_CS4__PATA_DA_0		= IOMUX_PAD(0x528, 0x140, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_CS5__PATA_DA_1		= IOMUX_PAD(0x52c, 0x144, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_CS6__PATA_DA_2		= IOMUX_PAD(0x530, 0x148, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D15__PATA_DATA15		= IOMUX_PAD(0x53c, 0x154, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D14__PATA_DATA14		= IOMUX_PAD(0x540, 0x158, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D13__PATA_DATA13		= IOMUX_PAD(0x544, 0x15c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D12__PATA_DATA12		= IOMUX_PAD(0x548, 0x160, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D11__PATA_DATA11		= IOMUX_PAD(0x54c, 0x164, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D10__PATA_DATA10		= IOMUX_PAD(0x550, 0x168, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D9__PATA_DATA9		= IOMUX_PAD(0x554, 0x16c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D8__PATA_DATA8		= IOMUX_PAD(0x558, 0x170, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D7__PATA_DATA7		= IOMUX_PAD(0x55c, 0x174, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D6__PATA_DATA6		= IOMUX_PAD(0x560, 0x178, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D5__PATA_DATA5		= IOMUX_PAD(0x564, 0x17c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D4__PATA_DATA4		= IOMUX_PAD(0x568, 0x180, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D3__PATA_DATA3		= IOMUX_PAD(0x56c, 0x184, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D2__PATA_DATA2		= IOMUX_PAD(0x570, 0x188, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D1__PATA_DATA1		= IOMUX_PAD(0x574, 0x18c, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_NANDF_D0__PATA_DATA0		= IOMUX_PAD(0x578, 0x190, 1, __NA_, 0, NO_PAD_CTRL),
	MX51_PAD_CSPI1_MOSI__ECSPI1_MOSI	= IOMUX_PAD(0x600, 0x210, 0, __NA_, 0, MX51_ECSPI_PAD_CTRL),
	MX51_PAD_CSPI1_MISO__ECSPI1_MISO	= IOMUX_PAD(0x604, 0x214, 0, __NA_, 0, MX51_ECSPI_PAD_CTRL),
	MX51_PAD_CSPI1_SS0__GPIO4_24		= IOMUX_PAD(0x608, 0x218, 3, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_CSPI1_SS1__GPIO4_25		= IOMUX_PAD(0x60c, 0x21c, 3, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_CSPI1_SCLK__ECSPI1_SCLK	= IOMUX_PAD(0x614, 0x224, 0, __NA_, 0, MX51_ECSPI_PAD_CTRL),
	MX51_PAD_UART1_RXD__UART1_RXD		= IOMUX_PAD(0x618, 0x228, 0, 0x9e4, 0, MX51_UART_PAD_CTRL),
	MX51_PAD_UART1_TXD__UART1_TXD		= IOMUX_PAD(0x61c, 0x22c, 0, __NA_, 0, MX51_UART_PAD_CTRL),
	MX51_PAD_UART1_RTS__UART1_RTS		= IOMUX_PAD(0x620, 0x230, 0, 0x9e0, 0, MX51_UART_PAD_CTRL),
	MX51_PAD_UART1_CTS__UART1_CTS		= IOMUX_PAD(0x624, 0x234, 0, __NA_, 0, MX51_UART_PAD_CTRL),
	MX51_PAD_USBH1_CLK__USBH1_CLK		= IOMUX_PAD(0x678, 0x278, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DIR__USBH1_DIR		= IOMUX_PAD(0x67c, 0x27c, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_STP__USBH1_STP		= IOMUX_PAD(0x680, 0x280, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_STP__GPIO1_27		= IOMUX_PAD(0x680, 0x280, 2, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_USBH1_NXT__USBH1_NXT		= IOMUX_PAD(0x684, 0x284, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA0__USBH1_DATA0	= IOMUX_PAD(0x688, 0x288, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA1__USBH1_DATA1	= IOMUX_PAD(0x68c, 0x28c, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA2__USBH1_DATA2	= IOMUX_PAD(0x690, 0x290, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA3__USBH1_DATA3	= IOMUX_PAD(0x694, 0x294, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA4__USBH1_DATA4	= IOMUX_PAD(0x698, 0x298, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA5__USBH1_DATA5	= IOMUX_PAD(0x69c, 0x29c, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA6__USBH1_DATA6	= IOMUX_PAD(0x6a0, 0x2a0, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_USBH1_DATA7__USBH1_DATA7	= IOMUX_PAD(0x6a4, 0x2a4, 0, __NA_, 0, MX51_USBH1_PAD_CTRL),
	MX51_PAD_SD1_CMD__SD1_CMD		= IOMUX_PAD(0x79c, 0x394, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD1_CLK__SD1_CLK		= IOMUX_PAD(0x7a0, 0x398, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL | PAD_CTL_HYS),
	MX51_PAD_SD1_DATA0__SD1_DATA0		= IOMUX_PAD(0x7a4, 0x39c, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD1_DATA1__SD1_DATA1		= IOMUX_PAD(0x7a8, 0x3a0, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD1_DATA2__SD1_DATA2		= IOMUX_PAD(0x7ac, 0x3a4, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD1_DATA3__SD1_DATA3		= IOMUX_PAD(0x7b0, 0x3a8, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_GPIO1_0__SD1_CD		= IOMUX_PAD(0x7b4, 0x3ac, 0, __NA_, 0, MX51_ESDHC_PAD_CTRL),
	MX51_PAD_GPIO1_1__SD1_WP		= IOMUX_PAD(0x7b8, 0x3b0, 0, __NA_, 0, MX51_ESDHC_PAD_CTRL),
	MX51_PAD_SD2_CMD__SD2_CMD		= IOMUX_PAD(0x7bc, 0x3b4, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD2_CLK__SD2_CLK		= IOMUX_PAD(0x7c0, 0x3b8, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL | PAD_CTL_HYS),
	MX51_PAD_SD2_DATA0__SD2_DATA0		= IOMUX_PAD(0x7c4, 0x3bc, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD2_DATA1__SD2_DATA1		= IOMUX_PAD(0x7c8, 0x3c0, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD2_DATA2__SD2_DATA2		= IOMUX_PAD(0x7cc, 0x3c4, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_SD2_DATA3__SD2_DATA3		= IOMUX_PAD(0x7d0, 0x3c8, 0x10, __NA_, 0, MX51_SDHCI_PAD_CTRL),
	MX51_PAD_GPIO1_3__GPIO1_3		= IOMUX_PAD(0x7d8, 0x3d0, 0, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_GPIO1_5__GPIO1_5		= IOMUX_PAD(0x808, 0x3dc, 0, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_GPIO1_6__GPIO1_6		= IOMUX_PAD(0x80c, 0x3e0, 0, __NA_, 0, MX51_GPIO_PAD_CTRL),
	MX51_PAD_GPIO1_7__SD2_WP		= IOMUX_PAD(0x810, 0x3e4, 6, __NA_, 0, MX51_ESDHC_PAD_CTRL),
	MX51_PAD_GPIO1_8__SD2_CD		= IOMUX_PAD(0x814, 0x3e8, 6, __NA_, 0, MX51_ESDHC_PAD_CTRL),
};

#endif /* __IOMUX_MX51_H__ */
