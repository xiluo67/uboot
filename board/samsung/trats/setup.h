/*
 * Machine Specific Values for TRATS board based on EXYNOS4210
 *
 * Copyright (C) 2011 Samsung Electronics
 * Heungjun Kim <riverful.kim@samsung.com>
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

#ifndef _TRATS_SETUP_H
#define _TRATS_SETUP_H

#include <config.h>
#include <version.h>
#include <asm/arch/cpu.h>

/* CLK_SRC_CPU: APLL(1), MPLL(1), CORE(0), HPM(0) */
#define MUX_HPM_SEL_MOUTAPLL		0x0
#define MUX_HPM_SEL_SCLKMPLL		0x1
#define MUX_CORE_SEL_MOUTAPLL		0x0
#define MUX_CORE_SEL_SCLKMPLL		0x1
#define MUX_MPLL_SEL_FILPLL		0x0
#define MUX_MPLL_SEL_MOUTMPLLFOUT	0x1
#define MUX_APLL_SEL_FILPLL		0x0
#define MUX_APLL_SEL_MOUTMPLLFOUT	0x1
#define CLK_SRC_CPU_VAL			((MUX_HPM_SEL_MOUTAPLL << 20) \
					| (MUX_CORE_SEL_MOUTAPLL << 16) \
					| (MUX_MPLL_SEL_MOUTMPLLFOUT << 8)\
					| (MUX_APLL_SEL_MOUTMPLLFOUT << 0))

/* CLK_DIV_CPU0 */
#define APLL_RATIO			0x0
#define PCLK_DBG_RATIO			0x1
#define ATB_RATIO			0x3
#define PERIPH_RATIO			0x3
#define COREM1_RATIO			0x7
#define COREM0_RATIO			0x3
#define CORE_RATIO			0x0
#define CLK_DIV_CPU0_VAL		((APLL_RATIO << 24) \
					| (PCLK_DBG_RATIO << 20) \
					| (ATB_RATIO << 16) \
					| (PERIPH_RATIO << 12) \
					| (COREM1_RATIO << 8) \
					| (COREM0_RATIO << 4) \
					| (CORE_RATIO << 0))

/* CLK_DIV_CPU1 */
#define HPM_RATIO			0x0
#define COPY_RATIO			0x3
#define CLK_DIV_CPU1_VAL		((HPM_RATIO << 4) | (COPY_RATIO))

/* CLK_DIV_DMC0 */
#define CORE_TIMERS_RATIO		0x1
#define COPY2_RATIO			0x3
#define DMCP_RATIO			0x1
#define DMCD_RATIO			0x1
#define DMC_RATIO			0x1
#define DPHY_RATIO			0x1
#define ACP_PCLK_RATIO			0x1
#define ACP_RATIO			0x3
#define CLK_DIV_DMC0_VAL		((CORE_TIMERS_RATIO << 28) \
					| (COPY2_RATIO << 24) \
					| (DMCP_RATIO << 20) \
					| (DMCD_RATIO << 16) \
					| (DMC_RATIO << 12) \
					| (DPHY_RATIO << 8) \
					| (ACP_PCLK_RATIO << 4)	\
					| (ACP_RATIO << 0))

/* CLK_DIV_DMC1 */
#define DPM_RATIO			0x1
#define DVSEM_RATIO			0x1
#define PWI_RATIO			0x1
#define CLK_DIV_DMC1_VAL		((DPM_RATIO << 24) \
					| (DVSEM_RATIO << 16) \
					| (PWI_RATIO << 8))

/* CLK_SRC_TOP0 */
#define MUX_ONENAND_SEL_ACLK_133	0x0
#define MUX_ONENAND_SEL_ACLK_160	0x1
#define MUX_ACLK_133_SEL_SCLKMPLL	0x0
#define MUX_ACLK_133_SEL_SCLKAPLL	0x1
#define MUX_ACLK_160_SEL_SCLKMPLL	0x0
#define MUX_ACLK_160_SEL_SCLKAPLL	0x1
#define MUX_ACLK_100_SEL_SCLKMPLL	0x0
#define MUX_ACLK_100_SEL_SCLKAPLL	0x1
#define MUX_ACLK_200_SEL_SCLKMPLL	0x0
#define MUX_ACLK_200_SEL_SCLKAPLL	0x1
#define MUX_VPLL_SEL_FINPLL		0x0
#define MUX_VPLL_SEL_FOUTVPLL		0x1
#define MUX_EPLL_SEL_FINPLL		0x0
#define MUX_EPLL_SEL_FOUTEPLL		0x1
#define MUX_ONENAND_1_SEL_MOUTONENAND	0x0
#define MUX_ONENAND_1_SEL_SCLKVPLL	0x1
#define CLK_SRC_TOP0_VAL		((MUX_ONENAND_SEL_ACLK_160 << 28) \
					| (MUX_ACLK_133_SEL_SCLKMPLL << 24) \
					| (MUX_ACLK_160_SEL_SCLKMPLL << 20) \
					| (MUX_ACLK_100_SEL_SCLKMPLL << 16) \
					| (MUX_ACLK_200_SEL_SCLKMPLL << 12) \
					| (MUX_VPLL_SEL_FOUTVPLL << 8) \
					| (MUX_EPLL_SEL_FOUTEPLL << 4) \
					| (MUX_ONENAND_1_SEL_MOUTONENAND << 0))

/* CLK_DIV_TOP */
#define ONENAND_RATIO			0x0
#define ACLK_133_RATIO			0x5
#define ACLK_160_RATIO			0x4
#define ACLK_100_RATIO			0x7
#define ACLK_200_RATIO			0x3
#define CLK_DIV_TOP_VAL			((ONENAND_RATIO << 16)	\
					| (ACLK_133_RATIO << 12)\
					| (ACLK_160_RATIO << 8)	\
					| (ACLK_100_RATIO << 4)	\
					| (ACLK_200_RATIO << 0))

/* CLK_DIV_LEFTBUS */
#define GPL_RATIO			0x1
#define GDL_RATIO			0x3
#define CLK_DIV_LEFTBUS_VAL		((GPL_RATIO << 4) | (GDL_RATIO))

/* CLK_DIV_RIGHTBUS */
#define GPR_RATIO			0x1
#define GDR_RATIO			0x3
#define CLK_DIV_RIGHTBUS_VAL		((GPR_RATIO << 4) | (GDR_RATIO))

/* CLK_SRS_FSYS: 6 = SCLKMPLL */
#define SATA_SEL_SCLKMPLL		0
#define SATA_SEL_SCLKAPLL		1

#define MMC_SEL_XXTI			0
#define MMC_SEL_XUSBXTI			1
#define MMC_SEL_SCLK_HDMI24M		2
#define MMC_SEL_SCLK_USBPHY0		3
#define MMC_SEL_SCLK_USBPHY1		4
#define MMC_SEL_SCLK_HDMIPHY		5
#define MMC_SEL_SCLKMPLL		6
#define MMC_SEL_SCLKEPLL		7
#define MMC_SEL_SCLKVPLL		8

#define MMCC0_SEL			MMC_SEL_SCLKMPLL
#define MMCC1_SEL			MMC_SEL_SCLKMPLL
#define MMCC2_SEL			MMC_SEL_SCLKMPLL
#define MMCC3_SEL			MMC_SEL_SCLKMPLL
#define MMCC4_SEL			MMC_SEL_SCLKMPLL
#define CLK_SRC_FSYS_VAL		((SATA_SEL_SCLKMPLL << 24) \
					| (MMCC4_SEL << 16) \
					| (MMCC3_SEL << 12) \
					| (MMCC2_SEL << 8) \
					| (MMCC1_SEL << 4) \
					| (MMCC0_SEL << 0))

/* SCLK_MMC[0-4] = MOUTMMC[0-4]/(MMC[0-4]_RATIO + 1)/(MMC[0-4]_PRE_RATIO +1) */
/* CLK_DIV_FSYS1: 800(MPLL) / (15 + 1) */
#define MMC0_RATIO			0xF
#define MMC0_PRE_RATIO			0x0
#define MMC1_RATIO			0xF
#define MMC1_PRE_RATIO			0x0
#define CLK_DIV_FSYS1_VAL		((MMC1_PRE_RATIO << 24) \
					| (MMC1_RATIO << 16) \
					| (MMC0_PRE_RATIO << 8) \
					| (MMC0_RATIO << 0))

/* CLK_DIV_FSYS2: 800(MPLL) / (15 + 1) */
#define MMC2_RATIO			0xF
#define MMC2_PRE_RATIO			0x0
#define MMC3_RATIO			0xF
#define MMC3_PRE_RATIO			0x0
#define CLK_DIV_FSYS2_VAL		((MMC3_PRE_RATIO << 24) \
					| (MMC3_RATIO << 16) \
					| (MMC2_PRE_RATIO << 8) \
					| (MMC2_RATIO << 0))

/* CLK_DIV_FSYS3: 800(MPLL) / (15 + 1) */
#define MMC4_RATIO			0xF
#define MMC4_PRE_RATIO			0x0
#define CLK_DIV_FSYS3_VAL		((MMC4_PRE_RATIO << 8) \
					| (MMC4_RATIO << 0))

/* CLK_SRC_PERIL0 */
#define UART_SEL_XXTI			0
#define UART_SEL_XUSBXTI		1
#define UART_SEL_SCLK_HDMI24M		2
#define UART_SEL_SCLK_USBPHY0		3
#define UART_SEL_SCLK_USBPHY1		4
#define UART_SEL_SCLK_HDMIPHY		5
#define UART_SEL_SCLKMPLL		6
#define UART_SEL_SCLKEPLL		7
#define UART_SEL_SCLKVPLL		8

#define UART0_SEL			UART_SEL_SCLKMPLL
#define UART1_SEL			UART_SEL_SCLKMPLL
#define UART2_SEL			UART_SEL_SCLKMPLL
#define UART3_SEL			UART_SEL_SCLKMPLL
#define UART4_SEL			UART_SEL_SCLKMPLL
#define UART5_SEL			UART_SEL_SCLKMPLL
#define CLK_SRC_PERIL0_VAL		((UART5_SEL << 16) \
					| (UART4_SEL << 12) \
					| (UART3_SEL << 12) \
					| (UART2_SEL << 8) \
					| (UART1_SEL << 4) \
					| (UART0_SEL << 0))

/* SCLK_UART[0-4] = MOUTUART[0-4] / (UART[0-4]_RATIO + 1) */
/* CLK_DIV_PERIL0 */
#define UART0_RATIO			7
#define UART1_RATIO			7
#define UART2_RATIO			7
#define UART3_RATIO			4
#define UART4_RATIO			7
#define UART5_RATIO			7
#define CLK_DIV_PERIL0_VAL		((UART5_RATIO << 16) \
					| (UART4_RATIO << 12) \
					| (UART3_RATIO << 12) \
					| (UART2_RATIO << 8) \
					| (UART1_RATIO << 4) \
					| (UART0_RATIO << 0))

/* CLK_DIV_PERIL3 */
#define SLIMBUS_RATIO			0x0
#define PWM_RATIO			0x8
#define CLK_DIV_PERIL3_VAL		((SLIMBUS_RATIO << 4) \
					| (PWM_RATIO << 0))

/* Required period to generate a stable clock output */
/* PLL_LOCK_TIME */
#define PLL_LOCKTIME			0x1C20

/* PLL Values */
#define DISABLE				0
#define ENABLE				1
#define SET_PLL(mdiv, pdiv, sdiv)	((ENABLE << 31)\
					| (mdiv << 16) \
					| (pdiv << 8) \
					| (sdiv << 0))

/* APLL_CON0: 800MHz */
#define APLL_MDIV			0xC8
#define APLL_PDIV			0x6
#define APLL_SDIV			0x1
#define APLL_CON0_VAL			SET_PLL(APLL_MDIV, APLL_PDIV, APLL_SDIV)

/* APLL_CON1 */
#define APLL_AFC_ENB			0x1
#define APLL_AFC			0x1C
#define APLL_CON1_VAL			((APLL_AFC_ENB << 31) | (APLL_AFC << 0))

/* MPLL_CON0: 800MHz */
#define MPLL_MDIV			0xC8
#define MPLL_PDIV			0x6
#define MPLL_SDIV			0x1
#define MPLL_CON0_VAL			SET_PLL(MPLL_MDIV, MPLL_PDIV, MPLL_SDIV)

/* MPLL_CON1 */
#define MPLL_AFC_ENB			0x1
#define MPLL_AFC			0x1C
#define MPLL_CON1_VAL			((MPLL_AFC_ENB << 31) | (MPLL_AFC << 0))

/* EPLL_CON0: 96MHz */
#define EPLL_MDIV			0x30
#define EPLL_PDIV			0x3
#define EPLL_SDIV			0x2
#define EPLL_CON0_VAL			SET_PLL(EPLL_MDIV, EPLL_PDIV, EPLL_SDIV)

/* EPLL_CON1 */
#define EPLL_K				0x0
#define EPLL_CON1_VAL			(EPLL_K >> 0)

/* VPLL_CON0: 108MHz */
#define VPLL_MDIV			0x35
#define VPLL_PDIV			0x3
#define VPLL_SDIV			0x2
#define VPLL_CON0_VAL			SET_PLL(VPLL_MDIV, VPLL_PDIV, VPLL_SDIV)

/* VPLL_CON1 */
#define VPLL_SSCG_EN			DISABLE
#define VPLL_SEL_PF_DN_SPREAD		0x0
#define VPLL_MRR			0x11
#define VPLL_MFR			0x0
#define VPLL_K				0x400
#define VPLL_CON1_VAL			((VPLL_SSCG_EN << 31)\
					| (VPLL_SEL_PF_DN_SPREAD << 29) \
					| (VPLL_MRR << 24) \
					| (VPLL_MFR << 16) \
					| (VPLL_K << 0))

/* CLOCK GATE */
#define CLK_DIS				0x0
#define CLK_EN				0x1

#define BIT_CAM_CLK_PIXELASYNCM1	18
#define BIT_CAM_CLK_PIXELASYNCM0	17
#define BIT_CAM_CLK_PPMUCAMIF		16
#define BIT_CAM_CLK_QEFIMC3		15
#define BIT_CAM_CLK_QEFIMC2		14
#define BIT_CAM_CLK_QEFIMC1		13
#define BIT_CAM_CLK_QEFIMC0		12
#define BIT_CAM_CLK_SMMUJPEG		11
#define BIT_CAM_CLK_SMMUFIMC3		10
#define BIT_CAM_CLK_SMMUFIMC2		9
#define BIT_CAM_CLK_SMMUFIMC1		8
#define BIT_CAM_CLK_SMMUFIMC0		7
#define BIT_CAM_CLK_JPEG		6
#define BIT_CAM_CLK_CSIS1		5
#define BIT_CAM_CLK_CSIS0		4
#define BIT_CAM_CLK_FIMC3		3
#define BIT_CAM_CLK_FIMC2		2
#define BIT_CAM_CLK_FIMC1		1
#define BIT_CAM_CLK_FIMC0		0
#define CLK_GATE_IP_CAM_ALL_EN		((CLK_EN << BIT_CAM_CLK_PIXELASYNCM1)\
					| (CLK_EN << BIT_CAM_CLK_PIXELASYNCM0)\
					| (CLK_EN << BIT_CAM_CLK_PPMUCAMIF)\
					| (CLK_EN << BIT_CAM_CLK_QEFIMC3)\
					| (CLK_EN << BIT_CAM_CLK_QEFIMC2)\
					| (CLK_EN << BIT_CAM_CLK_QEFIMC1)\
					| (CLK_EN << BIT_CAM_CLK_QEFIMC0)\
					| (CLK_EN << BIT_CAM_CLK_SMMUJPEG)\
					| (CLK_EN << BIT_CAM_CLK_SMMUFIMC3)\
					| (CLK_EN << BIT_CAM_CLK_SMMUFIMC2)\
					| (CLK_EN << BIT_CAM_CLK_SMMUFIMC1)\
					| (CLK_EN << BIT_CAM_CLK_SMMUFIMC0)\
					| (CLK_EN << BIT_CAM_CLK_JPEG)\
					| (CLK_EN << BIT_CAM_CLK_CSIS1)\
					| (CLK_EN << BIT_CAM_CLK_CSIS0)\
					| (CLK_EN << BIT_CAM_CLK_FIMC3)\
					| (CLK_EN << BIT_CAM_CLK_FIMC2)\
					| (CLK_EN << BIT_CAM_CLK_FIMC1)\
					| (CLK_EN << BIT_CAM_CLK_FIMC0))
#define CLK_GATE_IP_CAM_ALL_DIS		~CLK_GATE_IP_CAM_ALL_EN

#define BIT_VP_CLK_PPMUTV		5
#define BIT_VP_CLK_SMMUTV		4
#define BIT_VP_CLK_HDMI			3
#define BIT_VP_CLK_TVENC		2
#define BIT_VP_CLK_MIXER		1
#define BIT_VP_CLK_VP			0
#define CLK_GATE_IP_VP_ALL_EN		((CLK_EN << BIT_VP_CLK_PPMUTV)\
					| (CLK_EN << BIT_VP_CLK_SMMUTV)\
					| (CLK_EN << BIT_VP_CLK_HDMI)\
					| (CLK_EN << BIT_VP_CLK_TVENC)\
					| (CLK_EN << BIT_VP_CLK_MIXER)\
					| (CLK_EN << BIT_VP_CLK_VP))
#define CLK_GATE_IP_VP_ALL_DIS		~CLK_GATE_IP_VP_ALL_EN

#define BIT_MFC_CLK_PPMUMFC_R		4
#define BIT_MFC_CLK_PPMUMFC_L		3
#define BIT_MFC_CLK_SMMUMFC_R		2
#define BIT_MFC_CLK_SMMUMFC_L		1
#define BIT_MFC_CLK_MFC			0
#define CLK_GATE_IP_MFC_ALL_EN		((CLK_EN << BIT_MFC_CLK_PPMUMFC_R)\
					| (CLK_EN << BIT_MFC_CLK_PPMUMFC_L)\
					| (CLK_EN << BIT_MFC_CLK_SMMUMFC_R)\
					| (CLK_EN << BIT_MFC_CLK_SMMUMFC_L)\
					| (CLK_EN << BIT_MFC_CLK_MFC))
#define CLK_GATE_IP_MFC_ALL_DIS		~CLK_GATE_IP_MFC_ALL_EN

#define BIT_G3D_CLK_QEG3D		2
#define BIT_G3D_CLK_PPMUG3D		1
#define BIT_G3D_CLK_G3D			0
#define CLK_GATE_IP_G3D_ALL_EN		((CLK_EN << BIT_G3D_CLK_QEG3D)\
					| (CLK_EN << BIT_G3D_CLK_PPMUG3D)\
					| (CLK_EN << BIT_G3D_CLK_G3D))
#define CLK_GATE_IP_G3D_ALL_DIS		~CLK_GATE_IP_G3D_ALL_EN

#define BIT_IMAGE_CLK_PPMUIMAGE		9
#define BIT_IMAGE_CLK_QEMDMA		8
#define BIT_IMAGE_CLK_QEROTATOR		7
#define BIT_IMAGE_CLK_QEG2D		6
#define BIT_IMAGE_CLK_SMMUMDMA		5
#define BIT_IMAGE_CLK_SMMUROTATOR	4
#define BIT_IMAGE_CLK_SMMUG2D		3
#define BIT_IMAGE_CLK_MDMA		2
#define BIT_IMAGE_CLK_ROTATOR		1
#define BIT_IMAGE_CLK_G2D		0
#define CLK_GATE_IP_IMAGE_ALL_EN	((CLK_EN << BIT_IMAGE_CLK_PPMUIMAGE)\
					| (CLK_EN << BIT_IMAGE_CLK_QEMDMA)\
					| (CLK_EN << BIT_IMAGE_CLK_QEROTATOR)\
					| (CLK_EN << BIT_IMAGE_CLK_QEG2D)\
					| (CLK_EN << BIT_IMAGE_CLK_SMMUMDMA)\
					| (CLK_EN << BIT_IMAGE_CLK_SMMUROTATOR)\
					| (CLK_EN << BIT_IMAGE_CLK_SMMUG2D)\
					| (CLK_EN << BIT_IMAGE_CLK_MDMA)\
					| (CLK_EN << BIT_IMAGE_CLK_ROTATOR)\
					| (CLK_EN << BIT_IMAGE_CLK_G2D))
#define CLK_GATE_IP_IMAGE_ALL_DIS	~CLK_GATE_IP_IMAGE_ALL_EN

#define BIT_LCD0_CLK_PPMULCD0		5
#define BIT_LCD0_CLK_SMMUFIMD0		4
#define BIT_LCD0_CLK_DSIM0		3
#define BIT_LCD0_CLK_MDNIE0		2
#define BIT_LCD0_CLK_MIE0		1
#define BIT_LCD0_CLK_FIMD0		0
#define CLK_GATE_IP_LCD0_ALL_EN		((CLK_EN << BIT_LCD0_CLK_PPMULCD0)\
					| (CLK_EN << BIT_LCD0_CLK_SMMUFIMD0)\
					| (CLK_EN << BIT_LCD0_CLK_DSIM0)\
					| (CLK_EN << BIT_LCD0_CLK_MDNIE0)\
					| (CLK_EN << BIT_LCD0_CLK_MIE0)\
					| (CLK_EN << BIT_LCD0_CLK_FIMD0))
#define CLK_GATE_IP_LCD0_ALL_DIS	~CLK_GATE_IP_LCD0_ALL_EN

#define BIT_LCD1_CLK_PPMULCD1		5
#define BIT_LCD1_CLK_SMMUFIMD1		4
#define BIT_LCD1_CLK_DSIM1		3
#define BIT_LCD1_CLK_MDNIE1		2
#define BIT_LCD1_CLK_MIE1		1
#define BIT_LCD1_CLK_FIMD1		0
#define CLK_GATE_IP_LCD1_ALL_EN		((CLK_EN << BIT_LCD1_CLK_PPMULCD1)\
					| (CLK_EN << BIT_LCD1_CLK_SMMUFIMD1)\
					| (CLK_EN << BIT_LCD1_CLK_DSIM1)\
					| (CLK_EN << BIT_LCD1_CLK_MDNIE1)\
					| (CLK_EN << BIT_LCD1_CLK_MIE1)\
					| (CLK_EN << BIT_LCD1_CLK_FIMD1))
#define CLK_GATE_IP_LCD1_ALL_DIS	~CLK_GATE_IP_LCD1_ALL_EN

#define BIT_FSYS_CLK_SMMUPCIE		18
#define BIT_FSYS_CLK_PPMUFILE		17
#define BIT_FSYS_CLK_NFCON		16
#define BIT_FSYS_CLK_ONENAND		15
#define BIT_FSYS_CLK_PCIE		14
#define BIT_FSYS_CLK_USBDEVICE		13
#define BIT_FSYS_CLK_USBHOST		12
#define BIT_FSYS_CLK_SROMC		11
#define BIT_FSYS_CLK_SATA		10
#define BIT_FSYS_CLK_SDMMC4		9
#define BIT_FSYS_CLK_SDMMC3		8
#define BIT_FSYS_CLK_SDMMC2		7
#define BIT_FSYS_CLK_SDMMC1		6
#define BIT_FSYS_CLK_SDMMC0		5
#define BIT_FSYS_CLK_TSI		4
#define BIT_FSYS_CLK_SATAPHY		3
#define BIT_FSYS_CLK_PCIEPHY		2
#define BIT_FSYS_CLK_PDMA1		1
#define BIT_FSYS_CLK_PDMA0		0
#define CLK_GATE_IP_FSYS_ALL_EN		((CLK_EN << BIT_FSYS_CLK_SMMUPCIE)\
					| (CLK_EN << BIT_FSYS_CLK_PPMUFILE)\
					| (CLK_EN << BIT_FSYS_CLK_NFCON)\
					| (CLK_EN << BIT_FSYS_CLK_ONENAND)\
					| (CLK_EN << BIT_FSYS_CLK_PCIE)\
					| (CLK_EN << BIT_FSYS_CLK_USBDEVICE)\
					| (CLK_EN << BIT_FSYS_CLK_USBHOST)\
					| (CLK_EN << BIT_FSYS_CLK_SROMC)\
					| (CLK_EN << BIT_FSYS_CLK_SATA)\
					| (CLK_EN << BIT_FSYS_CLK_SDMMC4)\
					| (CLK_EN << BIT_FSYS_CLK_SDMMC3)\
					| (CLK_EN << BIT_FSYS_CLK_SDMMC2)\
					| (CLK_EN << BIT_FSYS_CLK_SDMMC1)\
					| (CLK_EN << BIT_FSYS_CLK_SDMMC0)\
					| (CLK_EN << BIT_FSYS_CLK_TSI)\
					| (CLK_EN << BIT_FSYS_CLK_SATAPHY)\
					| (CLK_EN << BIT_FSYS_CLK_PCIEPHY)\
					| (CLK_EN << BIT_FSYS_CLK_PDMA1)\
					| (CLK_EN << BIT_FSYS_CLK_PDMA0))
#define CLK_GATE_IP_FSYS_ALL_DIS	~CLK_GATE_IP_FSYS_ALL_EN

#define BIT_GPS_CLK_SMMUGPS		1
#define BIT_GPS_CLK_GPS			0
#define CLK_GATE_IP_GPS_ALL_EN		((CLK_EN << BIT_GPS_CLK_SMMUGPS)\
					| (CLK_EN << BIT_GPS_CLK_GPS))
#define CLK_GATE_IP_GPS_ALL_DIS		~CLK_GATE_IP_GPS_ALL_EN

#define BIT_PERIL_CLK_MODEMIF		28
#define BIT_PERIL_CLK_AC97		27
#define BIT_PERIL_CLK_SPDIF		26
#define BIT_PERIL_CLK_SLIMBUS		25
#define BIT_PERIL_CLK_PWM		24
#define BIT_PERIL_CLK_PCM2		23
#define BIT_PERIL_CLK_PCM1		22
#define BIT_PERIL_CLK_I2S2		21
#define BIT_PERIL_CLK_I2S1		20
#define BIT_PERIL_CLK_RESERVED0		19
#define BIT_PERIL_CLK_SPI2		18
#define BIT_PERIL_CLK_SPI1		17
#define BIT_PERIL_CLK_SPI0		16
#define BIT_PERIL_CLK_TSADC		15
#define BIT_PERIL_CLK_I2CHDMI		14
#define BIT_PERIL_CLK_I2C7		13
#define BIT_PERIL_CLK_I2C6		12
#define BIT_PERIL_CLK_I2C5		11
#define BIT_PERIL_CLK_I2C4		10
#define BIT_PERIL_CLK_I2C3		9
#define BIT_PERIL_CLK_I2C2		8
#define BIT_PERIL_CLK_I2C1		7
#define BIT_PERIL_CLK_I2C0		6
#define BIT_PERIL_CLK_RESERVED1		5
#define BIT_PERIL_CLK_UART4		4
#define BIT_PERIL_CLK_UART3		3
#define BIT_PERIL_CLK_UART2		2
#define BIT_PERIL_CLK_UART1		1
#define BIT_PERIL_CLK_UART0		0
#define CLK_GATE_IP_PERIL_ALL_EN	((CLK_EN << BIT_PERIL_CLK_MODEMIF)\
					| (CLK_EN << BIT_PERIL_CLK_AC97)\
					| (CLK_EN << BIT_PERIL_CLK_SPDIF)\
					| (CLK_EN << BIT_PERIL_CLK_SLIMBUS)\
					| (CLK_EN << BIT_PERIL_CLK_PWM)\
					| (CLK_EN << BIT_PERIL_CLK_PCM2)\
					| (CLK_EN << BIT_PERIL_CLK_PCM1)\
					| (CLK_EN << BIT_PERIL_CLK_I2S2)\
					| (CLK_EN << BIT_PERIL_CLK_I2S1)\
					| (CLK_EN << BIT_PERIL_CLK_RESERVED0)\
					| (CLK_EN << BIT_PERIL_CLK_SPI2)\
					| (CLK_EN << BIT_PERIL_CLK_SPI1)\
					| (CLK_EN << BIT_PERIL_CLK_SPI0)\
					| (CLK_EN << BIT_PERIL_CLK_TSADC)\
					| (CLK_EN << BIT_PERIL_CLK_I2CHDMI)\
					| (CLK_EN << BIT_PERIL_CLK_I2C7)\
					| (CLK_EN << BIT_PERIL_CLK_I2C6)\
					| (CLK_EN << BIT_PERIL_CLK_I2C5)\
					| (CLK_EN << BIT_PERIL_CLK_I2C4)\
					| (CLK_EN << BIT_PERIL_CLK_I2C3)\
					| (CLK_EN << BIT_PERIL_CLK_I2C2)\
					| (CLK_EN << BIT_PERIL_CLK_I2C1)\
					| (CLK_EN << BIT_PERIL_CLK_I2C0)\
					| (CLK_EN << BIT_PERIL_CLK_RESERVED1)\
					| (CLK_EN << BIT_PERIL_CLK_UART4)\
					| (CLK_EN << BIT_PERIL_CLK_UART3)\
					| (CLK_EN << BIT_PERIL_CLK_UART2)\
					| (CLK_EN << BIT_PERIL_CLK_UART1)\
					| (CLK_EN << BIT_PERIL_CLK_UART0))
#define CLK_GATE_IP_PERIL_ALL_DIS	~CLK_GATE_IP_PERIL_ALL_EN

#define BIT_PERIR_CLK_TMU_APBIF		17
#define BIT_PERIR_CLK_KEYIF		16
#define BIT_PERIR_CLK_RTC		15
#define BIT_PERIR_CLK_WDT		14
#define BIT_PERIR_CLK_MCT		13
#define BIT_PERIR_CLK_SECKEY		12
#define BIT_PERIR_CLK_HDMI_CEC		11
#define BIT_PERIR_CLK_TZPC5		10
#define BIT_PERIR_CLK_TZPC4		9
#define BIT_PERIR_CLK_TZPC3		8
#define BIT_PERIR_CLK_TZPC2		7
#define BIT_PERIR_CLK_TZPC1		6
#define BIT_PERIR_CLK_TZPC0		5
#define BIT_PERIR_CLK_CMU_DMCPART	4
#define BIT_PERIR_CLK_RESERVED		3
#define BIT_PERIR_CLK_CMU_APBIF		2
#define BIT_PERIR_CLK_SYSREG		1
#define BIT_PERIR_CLK_CHIP_ID		0
#define CLK_GATE_IP_PERIR_ALL_EN	((CLK_EN << BIT_PERIR_CLK_TMU_APBIF)\
					| (CLK_EN << BIT_PERIR_CLK_KEYIF)\
					| (CLK_EN << BIT_PERIR_CLK_RTC)\
					| (CLK_EN << BIT_PERIR_CLK_WDT)\
					| (CLK_EN << BIT_PERIR_CLK_MCT)\
					| (CLK_EN << BIT_PERIR_CLK_SECKEY)\
					| (CLK_EN << BIT_PERIR_CLK_HDMI_CEC)\
					| (CLK_EN << BIT_PERIR_CLK_TZPC5)\
					| (CLK_EN << BIT_PERIR_CLK_TZPC4)\
					| (CLK_EN << BIT_PERIR_CLK_TZPC3)\
					| (CLK_EN << BIT_PERIR_CLK_TZPC2)\
					| (CLK_EN << BIT_PERIR_CLK_TZPC1)\
					| (CLK_EN << BIT_PERIR_CLK_TZPC0)\
					| (CLK_EN << BIT_PERIR_CLK_CMU_DMCPART)\
					| (CLK_EN << BIT_PERIR_CLK_RESERVED)\
					| (CLK_EN << BIT_PERIR_CLK_CMU_APBIF)\
					| (CLK_EN << BIT_PERIR_CLK_SYSREG)\
					| (CLK_EN << BIT_PERIR_CLK_CHIP_ID))
#define CLK_GATE_IP_PERIR_ALL_DIS	~CLK_GATE_IP_PERIR_ALL_EN

#define BIT_BLOCK_CLK_GPS		7
#define BIT_BLOCK_CLK_RESERVED		6
#define BIT_BLOCK_CLK_LCD1		5
#define BIT_BLOCK_CLK_LCD0		4
#define BIT_BLOCK_CLK_G3D		3
#define BIT_BLOCK_CLK_MFC		2
#define BIT_BLOCK_CLK_TV		1
#define BIT_BLOCK_CLK_CAM		0
#define CLK_GATE_BLOCK_ALL_EN		((CLK_EN << BIT_BLOCK_CLK_GPS)\
					| (CLK_EN << BIT_BLOCK_CLK_RESERVED)\
					| (CLK_EN << BIT_BLOCK_CLK_LCD1)\
					| (CLK_EN << BIT_BLOCK_CLK_LCD0)\
					| (CLK_EN << BIT_BLOCK_CLK_G3D)\
					| (CLK_EN << BIT_BLOCK_CLK_MFC)\
					| (CLK_EN << BIT_BLOCK_CLK_TV)\
					| (CLK_EN << BIT_BLOCK_CLK_CAM))
#define CLK_GATE_BLOCK_ALL_DIS		~CLK_GATE_BLOCK_ALL_EN

/*
 * GATE CAM	: All block
 * GATE VP	: All block
 * GATE MFC	: All block
 * GATE G3D	: All block
 * GATE IMAGE	: All block
 * GATE LCD0	: All block
 * GATE LCD1	: All block
 * GATE FSYS	: Enable - PDMA0,1, SDMMC0,2, USBHOST, USBDEVICE, PPMUFILE
 * GATE GPS	: All block
 * GATE PERI Left	: All Enable, Block - SLIMBUS, SPDIF, AC97
 * GATE PERI Right	: All Enable, Block - KEYIF
 * GATE Block	: All block
 */
#define CLK_GATE_IP_CAM_VAL		CLK_GATE_IP_CAM_ALL_DIS
#define CLK_GATE_IP_VP_VAL		CLK_GATE_IP_VP_ALL_DIS
#define CLK_GATE_IP_MFC_VAL		CLK_GATE_IP_MFC_ALL_DIS
#define CLK_GATE_IP_G3D_VAL		CLK_GATE_IP_G3D_ALL_DIS
#define CLK_GATE_IP_IMAGE_VAL		CLK_GATE_IP_IMAGE_ALL_DIS
#define CLK_GATE_IP_LCD0_VAL		CLK_GATE_IP_LCD0_ALL_DIS
#define CLK_GATE_IP_LCD1_VAL		CLK_GATE_IP_LCD1_ALL_DIS
#define CLK_GATE_IP_FSYS_VAL		(CLK_GATE_IP_FSYS_ALL_DIS \
					| (CLK_EN << BIT_FSYS_CLK_PPMUFILE)\
					| (CLK_EN << BIT_FSYS_CLK_USBDEVICE)\
					| (CLK_EN << BIT_FSYS_CLK_USBHOST)\
					| (CLK_EN << BIT_FSYS_CLK_SROMC)\
					| (CLK_EN << BIT_FSYS_CLK_SDMMC2)\
					| (CLK_EN << BIT_FSYS_CLK_SDMMC0)\
					| (CLK_EN << BIT_FSYS_CLK_PDMA1)\
					| (CLK_EN << BIT_FSYS_CLK_PDMA0))
#define CLK_GATE_IP_GPS_VAL		CLK_GATE_IP_GPS_ALL_DIS
#define CLK_GATE_IP_PERIL_VAL		(CLK_GATE_IP_PERIL_ALL_DIS \
					| ~((CLK_EN << BIT_PERIL_CLK_AC97)\
					  | (CLK_EN << BIT_PERIL_CLK_SPDIF)\
					  | (CLK_EN << BIT_PERIL_CLK_I2C2)\
					  | (CLK_EN << BIT_PERIL_CLK_SLIMBUS)))
#define CLK_GATE_IP_PERIR_VAL		(CLK_GATE_IP_PERIR_ALL_DIS \
					| ~((CLK_EN << BIT_PERIR_CLK_KEYIF)))
#define CLK_GATE_BLOCK_VAL		CLK_GATE_BLOCK_ALL_DIS

/* PS_HOLD: Data Hight, Output En */
#define BIT_DAT				8
#define BIT_EN				9
#define EXYNOS4_PS_HOLD_CON_VAL		(0x1 << BIT_DAT | 0x1 << BIT_EN)

#endif
