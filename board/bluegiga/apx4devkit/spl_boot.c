/*
 * Bluegiga APX4 Development Kit
 *
 * Copyright (C) 2012 Bluegiga Technologies Oy
 *
 * Authors:
 * Veli-Pekka Peltola <veli-pekka.peltola@bluegiga.com>
 * Lauri Hintsala <lauri.hintsala@bluegiga.com>
 *
 * Based on spl_boot.c:
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
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
 */

#include <common.h>
#include <config.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/iomux-mx28.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/sys_proto.h>

#define	MUX_CONFIG_SSP0	(MXS_PAD_3V3 | MXS_PAD_8MA | MXS_PAD_PULLUP)
#define	MUX_CONFIG_GPMI	(MXS_PAD_3V3 | MXS_PAD_4MA | MXS_PAD_NOPULL)
#define	MUX_CONFIG_ENET	(MXS_PAD_3V3 | MXS_PAD_8MA | MXS_PAD_PULLUP)
#define	MUX_CONFIG_EMI	(MXS_PAD_3V3 | MXS_PAD_12MA | MXS_PAD_NOPULL)

const iomux_cfg_t iomux_setup[] = {
	/* DUART */
	MX28_PAD_PWM0__DUART_RX,
	MX28_PAD_PWM1__DUART_TX,

	/* LED */
	MX28_PAD_PWM3__GPIO_3_28,

	/* MMC0 */
	MX28_PAD_SSP0_DATA0__SSP0_D0 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA1__SSP0_D1 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA2__SSP0_D2 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA3__SSP0_D3 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_CMD__SSP0_CMD | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DETECT__SSP0_CARD_DETECT |
		(MXS_PAD_3V3 | MXS_PAD_8MA | MXS_PAD_NOPULL),
	MX28_PAD_SSP0_SCK__SSP0_SCK |
		(MXS_PAD_12MA | MXS_PAD_3V3 | MXS_PAD_NOPULL),

	/* GPMI NAND */
	MX28_PAD_GPMI_D00__GPMI_D0 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D01__GPMI_D1 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D02__GPMI_D2 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D03__GPMI_D3 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D04__GPMI_D4 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D05__GPMI_D5 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D06__GPMI_D6 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D07__GPMI_D7 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_CE0N__GPMI_CE0N | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_RDY0__GPMI_READY0 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_RDN__GPMI_RDN |
		(MXS_PAD_3V3 | MXS_PAD_8MA | MXS_PAD_PULLUP),
	MX28_PAD_GPMI_WRN__GPMI_WRN | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_ALE__GPMI_ALE | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_CLE__GPMI_CLE | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_RESETN__GPMI_RESETN | MUX_CONFIG_GPMI,

	/* FEC0 */
	MX28_PAD_ENET0_MDC__ENET0_MDC | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_MDIO__ENET0_MDIO | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RX_EN__ENET0_RX_EN | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TX_EN__ENET0_TX_EN | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RXD0__ENET0_RXD0 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RXD1__ENET0_RXD1 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TXD0__ENET0_TXD0 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TXD1__ENET0_TXD1 | MUX_CONFIG_ENET,
	MX28_PAD_ENET_CLK__CLKCTRL_ENET | MUX_CONFIG_ENET,

	/* I2C */
	MX28_PAD_I2C0_SCL__I2C0_SCL,
	MX28_PAD_I2C0_SDA__I2C0_SDA,

	/* EMI */
	MX28_PAD_EMI_D00__EMI_DATA0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D01__EMI_DATA1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D02__EMI_DATA2 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D03__EMI_DATA3 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D04__EMI_DATA4 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D05__EMI_DATA5 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D06__EMI_DATA6 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D07__EMI_DATA7 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D08__EMI_DATA8 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D09__EMI_DATA9 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D10__EMI_DATA10 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D11__EMI_DATA11 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D12__EMI_DATA12 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D13__EMI_DATA13 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D14__EMI_DATA14 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D15__EMI_DATA15 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_ODT0__EMI_ODT0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQM0__EMI_DQM0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_ODT1__EMI_ODT1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQM1__EMI_DQM1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DDR_OPEN_FB__EMI_DDR_OPEN_FEEDBACK | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CLK__EMI_CLK | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQS0__EMI_DQS0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQS1__EMI_DQS1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DDR_OPEN__EMI_DDR_OPEN | MUX_CONFIG_EMI,

	MX28_PAD_EMI_A00__EMI_ADDR0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A01__EMI_ADDR1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A02__EMI_ADDR2 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A03__EMI_ADDR3 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A04__EMI_ADDR4 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A05__EMI_ADDR5 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A06__EMI_ADDR6 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A07__EMI_ADDR7 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A08__EMI_ADDR8 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A09__EMI_ADDR9 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A10__EMI_ADDR10 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A11__EMI_ADDR11 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A12__EMI_ADDR12 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A13__EMI_ADDR13 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A14__EMI_ADDR14 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_BA0__EMI_BA0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_BA1__EMI_BA1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_BA2__EMI_BA2 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CASN__EMI_CASN | MUX_CONFIG_EMI,
	MX28_PAD_EMI_RASN__EMI_RASN | MUX_CONFIG_EMI,
	MX28_PAD_EMI_WEN__EMI_WEN | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CE0N__EMI_CE0N | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CE1N__EMI_CE1N | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CKE__EMI_CKE | MUX_CONFIG_EMI,
};

void board_init_ll(void)
{
	mxs_common_spl_init(iomux_setup, ARRAY_SIZE(iomux_setup));

	/* switch LED on */
	gpio_direction_output(MX28_PAD_PWM3__GPIO_3_28, 0);
}

void mxs_adjust_memory_params(uint32_t *dram_vals)
{
	/*
	 * All address lines are routed from CPU to memory chip.
	 * ADDR_PINS field is set to zero.
	 */
	dram_vals[0x74 >> 2] = 0x0f02000a;

	/* Used memory has 4 banks. EIGHT_BANK_MODE bit is disabled. */
	dram_vals[0x7c >> 2] = 0x00000101;
}
