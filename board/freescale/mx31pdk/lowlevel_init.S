/*
 * (C) Copyright 2009 Magnus Lilja <lilja.magnus@gmail.com>
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

#include <config.h>
#include <asm/arch/imx-regs.h>
#include <asm/macro.h>

.globl lowlevel_init
lowlevel_init:
	/* Also setup the Peripheral Port Remap register inside the core */
	ldr	r0, =ARM_PPMRR      /* start from AIPS 2GB region */
	mcr	p15, 0, r0, c15, c2, 4

	write32	IPU_CONF, IPU_CONF_DI_EN
	write32	CCM_CCMR, CCM_CCMR_SETUP

	wait_timer	0x40000

	write32	CCM_CCMR, CCM_CCMR_SETUP | CCMR_MPE
	write32	CCM_CCMR, (CCM_CCMR_SETUP | CCMR_MPE) & ~CCMR_MDS

	/* Set up clock to 532MHz */
	write32	CCM_PDR0, CCM_PDR0_SETUP_532MHZ
	write32	CCM_MPCTL, CCM_MPCTL_SETUP_532MHZ

	write32	CCM_SPCTL, PLL_PD(1) | PLL_MFD(4) | PLL_MFI(12) | PLL_MFN(1)

	/* Set up MX31 DDR pins */
	write32	IOMUXC_SW_PAD_CTL_SDCKE1_SDCLK_SDCLK_B, 0
	write32	IOMUXC_SW_PAD_CTL_CAS_SDWE_SDCKE0, 0
	write32	IOMUXC_SW_PAD_CTL_BCLK_RW_RAS, 0
	write32	IOMUXC_SW_PAD_CTL_CS2_CS3_CS4, 0x1000
	write32	IOMUXC_SW_PAD_CTL_DQM3_EB0_EB1, 0
	write32	IOMUXC_SW_PAD_CTL_DQM0_DQM1_DQM2, 0
	write32	IOMUXC_SW_PAD_CTL_SD29_SD30_SD31, 0
	write32	IOMUXC_SW_PAD_CTL_SD26_SD27_SD28, 0
	write32	IOMUXC_SW_PAD_CTL_SD23_SD24_SD25, 0
	write32	IOMUXC_SW_PAD_CTL_SD20_SD21_SD22, 0
	write32	IOMUXC_SW_PAD_CTL_SD17_SD18_SD19, 0
	write32	IOMUXC_SW_PAD_CTL_SD14_SD15_SD16, 0
	write32	IOMUXC_SW_PAD_CTL_SD11_SD12_SD13, 0
	write32	IOMUXC_SW_PAD_CTL_SD8_SD9_SD10, 0
	write32	IOMUXC_SW_PAD_CTL_SD5_SD6_SD7, 0
	write32	IOMUXC_SW_PAD_CTL_SD2_SD3_SD4, 0
	write32	IOMUXC_SW_PAD_CTL_SDBA0_SD0_SD1, 0
	write32	IOMUXC_SW_PAD_CTL_A24_A25_SDBA1, 0
	write32	IOMUXC_SW_PAD_CTL_A21_A22_A23, 0
	write32	IOMUXC_SW_PAD_CTL_A18_A19_A20, 0
	write32	IOMUXC_SW_PAD_CTL_A15_A16_A17, 0
	write32	IOMUXC_SW_PAD_CTL_A12_A13_A14, 0
	write32	IOMUXC_SW_PAD_CTL_A10_MA10_A11, 0
	write32	IOMUXC_SW_PAD_CTL_A7_A8_A9, 0
	write32	IOMUXC_SW_PAD_CTL_A4_A5_A6, 0
	write32	IOMUXC_SW_PAD_CTL_A1_A2_A3, 0
	write32	IOMUXC_SW_PAD_CTL_VPG0_VPG1_A0, 0

	/* Set up MX31 DDR Memory Controller */
	write32	WEIM_ESDMISC, ESDMISC_MDDR_SETUP
	write32	WEIM_ESDCFG0, ESDCFG0_MDDR_SETUP

	/* Perform DDR init sequence */
	write32	WEIM_ESDCTL0, ESDCTL_PRECHARGE
	write32	CSD0_BASE | 0x0f00, 0x12344321
	write32	WEIM_ESDCTL0, ESDCTL_AUTOREFRESH
	write32	CSD0_BASE, 0x12344321
	write32	CSD0_BASE, 0x12344321
	write32	WEIM_ESDCTL0, ESDCTL_LOADMODEREG
	write8	CSD0_BASE | 0x00000033, 0xda
	write8	CSD0_BASE | 0x01000000, 0xff
	write32	WEIM_ESDCTL0, ESDCTL_RW
	write32	CSD0_BASE, 0xDEADBEEF
	write32	WEIM_ESDMISC, ESDMISC_MDDR_RESET_DL

	mov	pc, lr
