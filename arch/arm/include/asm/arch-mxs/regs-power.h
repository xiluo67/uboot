/*
 * Freescale i.MX28 Power Controller Register Definitions
 *
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __MX28_REGS_POWER_H__
#define __MX28_REGS_POWER_H__

#include <asm/arch/regs-common.h>

#ifndef	__ASSEMBLY__
struct mxs_power_regs {
	mxs_reg_32(hw_power_ctrl)
	mxs_reg_32(hw_power_5vctrl)
	mxs_reg_32(hw_power_minpwr)
	mxs_reg_32(hw_power_charge)
	uint32_t	hw_power_vdddctrl;
	uint32_t	reserved_vddd[3];
	uint32_t	hw_power_vddactrl;
	uint32_t	reserved_vdda[3];
	uint32_t	hw_power_vddioctrl;
	uint32_t	reserved_vddio[3];
	uint32_t	hw_power_vddmemctrl;
	uint32_t	reserved_vddmem[3];
	uint32_t	hw_power_dcdc4p2;
	uint32_t	reserved_dcdc4p2[3];
	uint32_t	hw_power_misc;
	uint32_t	reserved_misc[3];
	uint32_t	hw_power_dclimits;
	uint32_t	reserved_dclimits[3];
	mxs_reg_32(hw_power_loopctrl)
	uint32_t	hw_power_sts;
	uint32_t	reserved_sts[3];
	mxs_reg_32(hw_power_speed)
	uint32_t	hw_power_battmonitor;
	uint32_t	reserved_battmonitor[3];

	uint32_t	reserved[4];

	mxs_reg_32(hw_power_reset)
	mxs_reg_32(hw_power_debug)
	mxs_reg_32(hw_power_thermal)
	mxs_reg_32(hw_power_usb1ctrl)
	mxs_reg_32(hw_power_special)
	mxs_reg_32(hw_power_version)
	mxs_reg_32(hw_power_anaclkctrl)
	mxs_reg_32(hw_power_refctrl)
};
#endif

#define	POWER_CTRL_PSWITCH_MID_TRAN			(1 << 27)
#define	POWER_CTRL_DCDC4P2_BO_IRQ			(1 << 24)
#define	POWER_CTRL_ENIRQ_DCDC4P2_BO			(1 << 23)
#define	POWER_CTRL_VDD5V_DROOP_IRQ			(1 << 22)
#define	POWER_CTRL_ENIRQ_VDD5V_DROOP			(1 << 21)
#define	POWER_CTRL_PSWITCH_IRQ				(1 << 20)
#define	POWER_CTRL_PSWITCH_IRQ_SRC			(1 << 19)
#define	POWER_CTRL_POLARITY_PSWITCH			(1 << 18)
#define	POWER_CTRL_ENIRQ_PSWITCH			(1 << 17)
#define	POWER_CTRL_POLARITY_DC_OK			(1 << 16)
#define	POWER_CTRL_DC_OK_IRQ				(1 << 15)
#define	POWER_CTRL_ENIRQ_DC_OK				(1 << 14)
#define	POWER_CTRL_BATT_BO_IRQ				(1 << 13)
#define	POWER_CTRL_ENIRQ_BATT_BO			(1 << 12)
#define	POWER_CTRL_VDDIO_BO_IRQ				(1 << 11)
#define	POWER_CTRL_ENIRQ_VDDIO_BO			(1 << 10)
#define	POWER_CTRL_VDDA_BO_IRQ				(1 << 9)
#define	POWER_CTRL_ENIRQ_VDDA_BO			(1 << 8)
#define	POWER_CTRL_VDDD_BO_IRQ				(1 << 7)
#define	POWER_CTRL_ENIRQ_VDDD_BO			(1 << 6)
#define	POWER_CTRL_POLARITY_VBUSVALID			(1 << 5)
#define	POWER_CTRL_VBUS_VALID_IRQ			(1 << 4)
#define	POWER_CTRL_ENIRQ_VBUS_VALID			(1 << 3)
#define	POWER_CTRL_POLARITY_VDD5V_GT_VDDIO		(1 << 2)
#define	POWER_CTRL_VDD5V_GT_VDDIO_IRQ			(1 << 1)
#define	POWER_CTRL_ENIRQ_VDD5V_GT_VDDIO			(1 << 0)

#define	POWER_5VCTRL_VBUSDROOP_TRSH_MASK		(0x3 << 30)
#define	POWER_5VCTRL_VBUSDROOP_TRSH_OFFSET		30
#define	POWER_5VCTRL_VBUSDROOP_TRSH_4V3			(0x0 << 30)
#define	POWER_5VCTRL_VBUSDROOP_TRSH_4V4			(0x1 << 30)
#define	POWER_5VCTRL_VBUSDROOP_TRSH_4V5			(0x2 << 30)
#define	POWER_5VCTRL_VBUSDROOP_TRSH_4V7			(0x3 << 30)
#define	POWER_5VCTRL_HEADROOM_ADJ_MASK			(0x7 << 24)
#define	POWER_5VCTRL_HEADROOM_ADJ_OFFSET		24
#define	POWER_5VCTRL_PWD_CHARGE_4P2_MASK		(0x3 << 20)
#define	POWER_5VCTRL_PWD_CHARGE_4P2_OFFSET		20
#define	POWER_5VCTRL_CHARGE_4P2_ILIMIT_MASK		(0x3f << 12)
#define	POWER_5VCTRL_CHARGE_4P2_ILIMIT_OFFSET		12
#define	POWER_5VCTRL_VBUSVALID_TRSH_MASK		(0x7 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_OFFSET		8
#define	POWER_5VCTRL_VBUSVALID_TRSH_2V9			(0x0 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_4V0			(0x1 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_4V1			(0x2 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_4V2			(0x3 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_4V3			(0x4 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_4V4			(0x5 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_4V5			(0x6 << 8)
#define	POWER_5VCTRL_VBUSVALID_TRSH_4V6			(0x7 << 8)
#define	POWER_5VCTRL_PWDN_5VBRNOUT			(1 << 7)
#define	POWER_5VCTRL_ENABLE_LINREG_ILIMIT		(1 << 6)
#define	POWER_5VCTRL_DCDC_XFER				(1 << 5)
#define	POWER_5VCTRL_VBUSVALID_5VDETECT			(1 << 4)
#define	POWER_5VCTRL_VBUSVALID_TO_B			(1 << 3)
#define	POWER_5VCTRL_ILIMIT_EQ_ZERO			(1 << 2)
#define	POWER_5VCTRL_PWRUP_VBUS_CMPS			(1 << 1)
#define	POWER_5VCTRL_ENABLE_DCDC			(1 << 0)

#define	POWER_MINPWR_LOWPWR_4P2				(1 << 14)
#define	POWER_MINPWR_PWD_BO				(1 << 12)
#define	POWER_MINPWR_USE_VDDXTAL_VBG			(1 << 11)
#define	POWER_MINPWR_PWD_ANA_CMPS			(1 << 10)
#define	POWER_MINPWR_ENABLE_OSC				(1 << 9)
#define	POWER_MINPWR_SELECT_OSC				(1 << 8)
#define	POWER_MINPWR_FBG_OFF				(1 << 7)
#define	POWER_MINPWR_DOUBLE_FETS			(1 << 6)
#define	POWER_MINPWR_HALFFETS				(1 << 5)
#define	POWER_MINPWR_LESSANA_I				(1 << 4)
#define	POWER_MINPWR_PWD_XTAL24				(1 << 3)
#define	POWER_MINPWR_DC_STOPCLK				(1 << 2)
#define	POWER_MINPWR_EN_DC_PFM				(1 << 1)
#define	POWER_MINPWR_DC_HALFCLK				(1 << 0)

#define	POWER_CHARGE_ADJ_VOLT_MASK			(0x7 << 24)
#define	POWER_CHARGE_ADJ_VOLT_OFFSET			24
#define	POWER_CHARGE_ADJ_VOLT_M025P			(0x1 << 24)
#define	POWER_CHARGE_ADJ_VOLT_P050P			(0x2 << 24)
#define	POWER_CHARGE_ADJ_VOLT_M075P			(0x3 << 24)
#define	POWER_CHARGE_ADJ_VOLT_P025P			(0x4 << 24)
#define	POWER_CHARGE_ADJ_VOLT_M050P			(0x5 << 24)
#define	POWER_CHARGE_ADJ_VOLT_P075P			(0x6 << 24)
#define	POWER_CHARGE_ADJ_VOLT_M100P			(0x7 << 24)
#define	POWER_CHARGE_ENABLE_LOAD			(1 << 22)
#define	POWER_CHARGE_ENABLE_FAULT_DETECT		(1 << 20)
#define	POWER_CHARGE_CHRG_STS_OFF			(1 << 19)
#define	POWER_CHARGE_LIION_4P1				(1 << 18)
#define	POWER_CHARGE_PWD_BATTCHRG			(1 << 16)
#define	POWER_CHARGE_ENABLE_CHARGER_USB1		(1 << 13)
#define	POWER_CHARGE_ENABLE_CHARGER_USB0		(1 << 12)
#define	POWER_CHARGE_STOP_ILIMIT_MASK			(0xf << 8)
#define	POWER_CHARGE_STOP_ILIMIT_OFFSET			8
#define	POWER_CHARGE_STOP_ILIMIT_10MA			(0x1 << 8)
#define	POWER_CHARGE_STOP_ILIMIT_20MA			(0x2 << 8)
#define	POWER_CHARGE_STOP_ILIMIT_50MA			(0x4 << 8)
#define	POWER_CHARGE_STOP_ILIMIT_100MA			(0x8 << 8)
#define	POWER_CHARGE_BATTCHRG_I_MASK			0x3f
#define	POWER_CHARGE_BATTCHRG_I_OFFSET			0
#define	POWER_CHARGE_BATTCHRG_I_10MA			0x01
#define	POWER_CHARGE_BATTCHRG_I_20MA			0x02
#define	POWER_CHARGE_BATTCHRG_I_50MA			0x04
#define	POWER_CHARGE_BATTCHRG_I_100MA			0x08
#define	POWER_CHARGE_BATTCHRG_I_200MA			0x10
#define	POWER_CHARGE_BATTCHRG_I_400MA			0x20

#define	POWER_VDDDCTRL_ADJTN_MASK			(0xf << 28)
#define	POWER_VDDDCTRL_ADJTN_OFFSET			28
#define	POWER_VDDDCTRL_PWDN_BRNOUT			(1 << 23)
#define	POWER_VDDDCTRL_DISABLE_STEPPING			(1 << 22)
#define	POWER_VDDDCTRL_ENABLE_LINREG			(1 << 21)
#define	POWER_VDDDCTRL_DISABLE_FET			(1 << 20)
#define	POWER_VDDDCTRL_LINREG_OFFSET_MASK		(0x3 << 16)
#define	POWER_VDDDCTRL_LINREG_OFFSET_OFFSET		16
#define	POWER_VDDDCTRL_LINREG_OFFSET_0STEPS		(0x0 << 16)
#define	POWER_VDDDCTRL_LINREG_OFFSET_1STEPS_ABOVE	(0x1 << 16)
#define	POWER_VDDDCTRL_LINREG_OFFSET_1STEPS_BELOW	(0x2 << 16)
#define	POWER_VDDDCTRL_LINREG_OFFSET_2STEPS_BELOW	(0x3 << 16)
#define	POWER_VDDDCTRL_BO_OFFSET_MASK			(0x7 << 8)
#define	POWER_VDDDCTRL_BO_OFFSET_OFFSET			8
#define	POWER_VDDDCTRL_TRG_MASK				0x1f
#define	POWER_VDDDCTRL_TRG_OFFSET			0

#define	POWER_VDDACTRL_PWDN_BRNOUT			(1 << 19)
#define	POWER_VDDACTRL_DISABLE_STEPPING			(1 << 18)
#define	POWER_VDDACTRL_ENABLE_LINREG			(1 << 17)
#define	POWER_VDDACTRL_DISABLE_FET			(1 << 16)
#define	POWER_VDDACTRL_LINREG_OFFSET_MASK		(0x3 << 12)
#define	POWER_VDDACTRL_LINREG_OFFSET_OFFSET		12
#define	POWER_VDDACTRL_LINREG_OFFSET_0STEPS		(0x0 << 12)
#define	POWER_VDDACTRL_LINREG_OFFSET_1STEPS_ABOVE	(0x1 << 12)
#define	POWER_VDDACTRL_LINREG_OFFSET_1STEPS_BELOW	(0x2 << 12)
#define	POWER_VDDACTRL_LINREG_OFFSET_2STEPS_BELOW	(0x3 << 12)
#define	POWER_VDDACTRL_BO_OFFSET_MASK			(0x7 << 8)
#define	POWER_VDDACTRL_BO_OFFSET_OFFSET			8
#define	POWER_VDDACTRL_TRG_MASK				0x1f
#define	POWER_VDDACTRL_TRG_OFFSET			0

#define	POWER_VDDIOCTRL_ADJTN_MASK			(0xf << 20)
#define	POWER_VDDIOCTRL_ADJTN_OFFSET			20
#define	POWER_VDDIOCTRL_PWDN_BRNOUT			(1 << 18)
#define	POWER_VDDIOCTRL_DISABLE_STEPPING		(1 << 17)
#define	POWER_VDDIOCTRL_DISABLE_FET			(1 << 16)
#define	POWER_VDDIOCTRL_LINREG_OFFSET_MASK		(0x3 << 12)
#define	POWER_VDDIOCTRL_LINREG_OFFSET_OFFSET		12
#define	POWER_VDDIOCTRL_LINREG_OFFSET_0STEPS		(0x0 << 12)
#define	POWER_VDDIOCTRL_LINREG_OFFSET_1STEPS_ABOVE	(0x1 << 12)
#define	POWER_VDDIOCTRL_LINREG_OFFSET_1STEPS_BELOW	(0x2 << 12)
#define	POWER_VDDIOCTRL_LINREG_OFFSET_2STEPS_BELOW	(0x3 << 12)
#define	POWER_VDDIOCTRL_BO_OFFSET_MASK			(0x7 << 8)
#define	POWER_VDDIOCTRL_BO_OFFSET_OFFSET		8
#define	POWER_VDDIOCTRL_TRG_MASK			0x1f
#define	POWER_VDDIOCTRL_TRG_OFFSET			0

#define	POWER_VDDMEMCTRL_PULLDOWN_ACTIVE		(1 << 10)
#define	POWER_VDDMEMCTRL_ENABLE_ILIMIT			(1 << 9)
#define	POWER_VDDMEMCTRL_ENABLE_LINREG			(1 << 8)
#define	POWER_VDDMEMCTRL_BO_OFFSET_MASK			(0x7 << 5)
#define	POWER_VDDMEMCTRL_BO_OFFSET_OFFSET		5
#define	POWER_VDDMEMCTRL_TRG_MASK			0x1f
#define	POWER_VDDMEMCTRL_TRG_OFFSET			0

#define	POWER_DCDC4P2_DROPOUT_CTRL_MASK			(0xf << 28)
#define	POWER_DCDC4P2_DROPOUT_CTRL_OFFSET		28
#define	POWER_DCDC4P2_DROPOUT_CTRL_200MV		(0x3 << 30)
#define	POWER_DCDC4P2_DROPOUT_CTRL_100MV		(0x2 << 30)
#define	POWER_DCDC4P2_DROPOUT_CTRL_50MV			(0x1 << 30)
#define	POWER_DCDC4P2_DROPOUT_CTRL_25MV			(0x0 << 30)
#define	POWER_DCDC4P2_DROPOUT_CTRL_SRC_4P2		(0x0 << 28)
#define	POWER_DCDC4P2_DROPOUT_CTRL_SRC_4P2_LT_BATT	(0x1 << 28)
#define	POWER_DCDC4P2_DROPOUT_CTRL_SRC_SEL		(0x2 << 28)
#define	POWER_DCDC4P2_ISTEAL_THRESH_MASK		(0x3 << 24)
#define	POWER_DCDC4P2_ISTEAL_THRESH_OFFSET		24
#define	POWER_DCDC4P2_ENABLE_4P2			(1 << 23)
#define	POWER_DCDC4P2_ENABLE_DCDC			(1 << 22)
#define	POWER_DCDC4P2_HYST_DIR				(1 << 21)
#define	POWER_DCDC4P2_HYST_THRESH			(1 << 20)
#define	POWER_DCDC4P2_TRG_MASK				(0x7 << 16)
#define	POWER_DCDC4P2_TRG_OFFSET			16
#define	POWER_DCDC4P2_TRG_4V2				(0x0 << 16)
#define	POWER_DCDC4P2_TRG_4V1				(0x1 << 16)
#define	POWER_DCDC4P2_TRG_4V0				(0x2 << 16)
#define	POWER_DCDC4P2_TRG_3V9				(0x3 << 16)
#define	POWER_DCDC4P2_TRG_BATT				(0x4 << 16)
#define	POWER_DCDC4P2_BO_MASK				(0x1f << 8)
#define	POWER_DCDC4P2_BO_OFFSET				8
#define	POWER_DCDC4P2_CMPTRIP_MASK			0x1f
#define	POWER_DCDC4P2_CMPTRIP_OFFSET			0

#define	POWER_MISC_FREQSEL_MASK				(0x7 << 4)
#define	POWER_MISC_FREQSEL_OFFSET			4
#define	POWER_MISC_FREQSEL_20MHZ			(0x1 << 4)
#define	POWER_MISC_FREQSEL_24MHZ			(0x2 << 4)
#define	POWER_MISC_FREQSEL_19MHZ			(0x3 << 4)
#define	POWER_MISC_FREQSEL_14MHZ			(0x4 << 4)
#define	POWER_MISC_FREQSEL_18MHZ			(0x5 << 4)
#define	POWER_MISC_FREQSEL_21MHZ			(0x6 << 4)
#define	POWER_MISC_FREQSEL_17MHZ			(0x7 << 4)
#define	POWER_MISC_DISABLE_FET_BO_LOGIC			(1 << 3)
#define	POWER_MISC_DELAY_TIMING				(1 << 2)
#define	POWER_MISC_TEST					(1 << 1)
#define	POWER_MISC_SEL_PLLCLK				(1 << 0)

#define	POWER_DCLIMITS_POSLIMIT_BUCK_MASK		(0x7f << 8)
#define	POWER_DCLIMITS_POSLIMIT_BUCK_OFFSET		8
#define	POWER_DCLIMITS_NEGLIMIT_MASK			0x7f
#define	POWER_DCLIMITS_NETLIMIT_OFFSET			0

#define	POWER_LOOPCTRL_TOGGLE_DIF			(1 << 20)
#define	POWER_LOOPCTRL_HYST_SIGN			(1 << 19)
#define	POWER_LOOPCTRL_EN_CM_HYST			(1 << 18)
#define	POWER_LOOPCTRL_EN_DF_HYST			(1 << 17)
#define	POWER_LOOPCTRL_CM_HYST_THRESH			(1 << 16)
#define	POWER_LOOPCTRL_DF_HYST_THRESH			(1 << 15)
#define	POWER_LOOPCTRL_RCSCALE_THRESH			(1 << 14)
#define	POWER_LOOPCTRL_EN_RCSCALE_MASK			(0x3 << 12)
#define	POWER_LOOPCTRL_EN_RCSCALE_OFFSET		12
#define	POWER_LOOPCTRL_EN_RCSCALE_DIS			(0x0 << 12)
#define	POWER_LOOPCTRL_EN_RCSCALE_2X			(0x1 << 12)
#define	POWER_LOOPCTRL_EN_RCSCALE_4X			(0x2 << 12)
#define	POWER_LOOPCTRL_EN_RCSCALE_8X			(0x3 << 12)
#define	POWER_LOOPCTRL_DC_FF_MASK			(0x7 << 8)
#define	POWER_LOOPCTRL_DC_FF_OFFSET			8
#define	POWER_LOOPCTRL_DC_R_MASK			(0xf << 4)
#define	POWER_LOOPCTRL_DC_R_OFFSET			4
#define	POWER_LOOPCTRL_DC_C_MASK			0x3
#define	POWER_LOOPCTRL_DC_C_OFFSET			0
#define	POWER_LOOPCTRL_DC_C_MAX				0x0
#define	POWER_LOOPCTRL_DC_C_2X				0x1
#define	POWER_LOOPCTRL_DC_C_4X				0x2
#define	POWER_LOOPCTRL_DC_C_MIN				0x3

#define	POWER_STS_PWRUP_SOURCE_MASK			(0x3f << 24)
#define	POWER_STS_PWRUP_SOURCE_OFFSET			24
#define	POWER_STS_PWRUP_SOURCE_5V			(0x20 << 24)
#define	POWER_STS_PWRUP_SOURCE_RTC			(0x10 << 24)
#define	POWER_STS_PWRUP_SOURCE_PSWITCH_HIGH		(0x02 << 24)
#define	POWER_STS_PWRUP_SOURCE_PSWITCH_MID		(0x01 << 24)
#define	POWER_STS_PSWITCH_MASK				(0x3 << 20)
#define	POWER_STS_PSWITCH_OFFSET			20
#define	POWER_STS_THERMAL_WARNING			(1 << 19)
#define	POWER_STS_VDDMEM_BO				(1 << 18)
#define	POWER_STS_AVALID0_STATUS			(1 << 17)
#define	POWER_STS_BVALID0_STATUS			(1 << 16)
#define	POWER_STS_VBUSVALID0_STATUS			(1 << 15)
#define	POWER_STS_SESSEND0_STATUS			(1 << 14)
#define	POWER_STS_BATT_BO				(1 << 13)
#define	POWER_STS_VDD5V_FAULT				(1 << 12)
#define	POWER_STS_CHRGSTS				(1 << 11)
#define	POWER_STS_DCDC_4P2_BO				(1 << 10)
#define	POWER_STS_DC_OK					(1 << 9)
#define	POWER_STS_VDDIO_BO				(1 << 8)
#define	POWER_STS_VDDA_BO				(1 << 7)
#define	POWER_STS_VDDD_BO				(1 << 6)
#define	POWER_STS_VDD5V_GT_VDDIO			(1 << 5)
#define	POWER_STS_VDD5V_DROOP				(1 << 4)
#define	POWER_STS_AVALID0				(1 << 3)
#define	POWER_STS_BVALID0				(1 << 2)
#define	POWER_STS_VBUSVALID0				(1 << 1)
#define	POWER_STS_SESSEND0				(1 << 0)

#define	POWER_SPEED_STATUS_MASK				(0xffff << 8)
#define	POWER_SPEED_STATUS_OFFSET			8
#define	POWER_SPEED_STATUS_SEL_MASK			(0x3 << 6)
#define	POWER_SPEED_STATUS_SEL_OFFSET			6
#define	POWER_SPEED_STATUS_SEL_DCDC_STAT		(0x0 << 6)
#define	POWER_SPEED_STATUS_SEL_CORE_STAT		(0x1 << 6)
#define	POWER_SPEED_STATUS_SEL_ARM_STAT			(0x2 << 6)
#define	POWER_SPEED_CTRL_MASK				0x3
#define	POWER_SPEED_CTRL_OFFSET				0
#define	POWER_SPEED_CTRL_SS_OFF				0x0
#define	POWER_SPEED_CTRL_SS_ON				0x1
#define	POWER_SPEED_CTRL_SS_ENABLE			0x3

#define	POWER_BATTMONITOR_BATT_VAL_MASK			(0x3ff << 16)
#define	POWER_BATTMONITOR_BATT_VAL_OFFSET		16
#define	POWER_BATTMONITOR_PWDN_BATTBRNOUT_5VDETECT_EN	(1 << 11)
#define	POWER_BATTMONITOR_EN_BATADJ			(1 << 10)
#define	POWER_BATTMONITOR_PWDN_BATTBRNOUT		(1 << 9)
#define	POWER_BATTMONITOR_BRWNOUT_PWD			(1 << 8)
#define	POWER_BATTMONITOR_BRWNOUT_LVL_MASK		0x1f
#define	POWER_BATTMONITOR_BRWNOUT_LVL_OFFSET		0

#define	POWER_RESET_UNLOCK_MASK				(0xffff << 16)
#define	POWER_RESET_UNLOCK_OFFSET			16
#define	POWER_RESET_UNLOCK_KEY				(0x3e77 << 16)
#define	POWER_RESET_FASTFALL_PSWITCH_OFF		(1 << 2)
#define	POWER_RESET_PWD_OFF				(1 << 1)
#define	POWER_RESET_PWD					(1 << 0)

#define	POWER_DEBUG_VBUSVALIDPIOLOCK			(1 << 3)
#define	POWER_DEBUG_AVALIDPIOLOCK			(1 << 2)
#define	POWER_DEBUG_BVALIDPIOLOCK			(1 << 1)
#define	POWER_DEBUG_SESSENDPIOLOCK			(1 << 0)

#define	POWER_THERMAL_TEST				(1 << 8)
#define	POWER_THERMAL_PWD				(1 << 7)
#define	POWER_THERMAL_LOW_POWER				(1 << 6)
#define	POWER_THERMAL_OFFSET_ADJ_MASK			(0x3 << 4)
#define	POWER_THERMAL_OFFSET_ADJ_OFFSET			4
#define	POWER_THERMAL_OFFSET_ADJ_ENABLE			(1 << 3)
#define	POWER_THERMAL_TEMP_THRESHOLD_MASK		0x7
#define	POWER_THERMAL_TEMP_THRESHOLD_OFFSET		0

#define	POWER_USB1CTRL_AVALID1				(1 << 3)
#define	POWER_USB1CTRL_BVALID1				(1 << 2)
#define	POWER_USB1CTRL_VBUSVALID1			(1 << 1)
#define	POWER_USB1CTRL_SESSEND1				(1 << 0)

#define	POWER_SPECIAL_TEST_MASK				0xffffffff
#define	POWER_SPECIAL_TEST_OFFSET			0

#define	POWER_VERSION_MAJOR_MASK			(0xff << 24)
#define	POWER_VERSION_MAJOR_OFFSET			24
#define	POWER_VERSION_MINOR_MASK			(0xff << 16)
#define	POWER_VERSION_MINOR_OFFSET			16
#define	POWER_VERSION_STEP_MASK				0xffff
#define	POWER_VERSION_STEP_OFFSET			0

#define	POWER_ANACLKCTRL_CLKGATE_0			(1 << 31)
#define	POWER_ANACLKCTRL_OUTDIV_MASK			(0x7 << 28)
#define	POWER_ANACLKCTRL_OUTDIV_OFFSET			28
#define	POWER_ANACLKCTRL_INVERT_OUTCLK			(1 << 27)
#define	POWER_ANACLKCTRL_CLKGATE_I			(1 << 26)
#define	POWER_ANACLKCTRL_DITHER_OFF			(1 << 10)
#define	POWER_ANACLKCTRL_SLOW_DITHER			(1 << 9)
#define	POWER_ANACLKCTRL_INVERT_INCLK			(1 << 8)
#define	POWER_ANACLKCTRL_INCLK_SHIFT_MASK		(0x3 << 4)
#define	POWER_ANACLKCTRL_INCLK_SHIFT_OFFSET		4
#define	POWER_ANACLKCTRL_INDIV_MASK			0x7
#define	POWER_ANACLKCTRL_INDIV_OFFSET			0

#define	POWER_REFCTRL_FASTSETTLING			(1 << 26)
#define	POWER_REFCTRL_RAISE_REF				(1 << 25)
#define	POWER_REFCTRL_XTAL_BGR_BIAS			(1 << 24)
#define	POWER_REFCTRL_VBG_ADJ_MASK			(0x7 << 20)
#define	POWER_REFCTRL_VBG_ADJ_OFFSET			20
#define	POWER_REFCTRL_LOW_PWR				(1 << 19)
#define	POWER_REFCTRL_BIAS_CTRL_MASK			(0x3 << 16)
#define	POWER_REFCTRL_BIAS_CTRL_OFFSET			16
#define	POWER_REFCTRL_VDDXTAL_TO_VDDD			(1 << 14)
#define	POWER_REFCTRL_ADJ_ANA				(1 << 13)
#define	POWER_REFCTRL_ADJ_VAG				(1 << 12)
#define	POWER_REFCTRL_ANA_REFVAL_MASK			(0xf << 8)
#define	POWER_REFCTRL_ANA_REFVAL_OFFSET			8
#define	POWER_REFCTRL_VAG_VAL_MASK			(0xf << 4)
#define	POWER_REFCTRL_VAG_VAL_OFFSET			4

#endif	/* __MX28_REGS_POWER_H__ */
