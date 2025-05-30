/*
 * Copyright (C) 2011 Nobuhiro Iwamatsu <nobuhiro.iwamatsu.yj@renesas.com>
 * Copyright (C) 2011 Renesas Solutions Corp.
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
#include <version.h>
#include <asm/processor.h>
#include <asm/macro.h>

#include <asm/processor.h>

	.global	lowlevel_init

	.text
	.align	2

lowlevel_init:

	/* WDT */
	write32 WDTCSR_A, WDTCSR_D

	/* MMU */
	write32 MMUCR_A, MMUCR_D

	write32 FRQCR2_A, FRQCR2_D
	write32 FRQCR0_A, FRQCR0_D

	write32 CS0CTRL_A, CS0CTRL_D
	write32 CS1CTRL_A, CS1CTRL_D
	write32 CS0CTRL2_A, CS0CTRL2_D

	write32 CSPWCR0_A, CSPWCR0_D
	write32 CSPWCR1_A, CSPWCR1_D
	write32 CS1GDST_A, CS1GDST_D

	# clock mode check
	mov.l   MODEMR, r1
	mov.l   @r1, r0
	and		#6, r0 /* Check 1 and 2 bit.*/
	cmp/eq  #2, r0 /* 0x02 is 533Mhz mode */
	bt      init_lbsc_533

init_lbsc_400:

	write32 CSWCR0_A, CSWCR0_D_400
	write32 CSWCR1_A, CSWCR1_D

	bra	init_dbsc3_400_pad
	nop

	.align 2

MODEMR:		.long	0xFFCC0020
WDTCSR_A:	.long	0xFFCC0004
WDTCSR_D:	.long	0xA5000000
MMUCR_A:	.long	0xFF000010
MMUCR_D:	.long	0x00000004

FRQCR2_A:	.long	0xFFC80008
FRQCR2_D:	.long	0x00000000
FRQCR0_A:	.long	0xFFC80000
FRQCR0_D:	.long	0xCF000001

CS0CTRL_A:	.long	0xFF800200
CS0CTRL_D:	.long	0x00000020
CS1CTRL_A:	.long	0xFF800204
CS1CTRL_D:	.long	0x00000020

CS0CTRL2_A:	.long	0xFF800220
CS0CTRL2_D:	.long	0x00004000

CSPWCR0_A:	.long	0xFF800280
CSPWCR0_D:	.long	0x00000000
CSPWCR1_A:	.long	0xFF800284
CSPWCR1_D:	.long	0x00000000
CS1GDST_A:	.long	0xFF8002C0
CS1GDST_D:	.long	0x00000011

init_lbsc_533:

	write32 CSWCR0_A, CSWCR0_D_533
	write32 CSWCR1_A, CSWCR1_D

	bra	init_dbsc3_533_pad
	nop

	.align 2

CSWCR0_A:	.long	0xFF800230
CSWCR0_D_533:	.long	0x01120104
CSWCR0_D_400:	.long	0x02120114
/* CSWCR0_D_400:	.long	0x01160116 */
CSWCR1_A:	.long	0xFF800234
CSWCR1_D:	.long	0x077F077F
/* CSWCR1_D_400:	.long	0x00120012 */

init_dbsc3_400_pad:

	write32	DBPDCNT3_A,	DBPDCNT3_D
	wait_timer	WAIT_200US_400

	write32 DBPDCNT0_A,	DBPDCNT0_D_400
	write32 DBPDCNT3_A,	DBPDCNT3_D0
	write32 DBPDCNT1_A,	DBPDCNT1_D

	write32 DBPDCNT3_A,	DBPDCNT3_D1
	wait_timer WAIT_32MCLK

	write32	DBPDCNT3_A,	DBPDCNT3_D2
	wait_timer WAIT_100US_400

	write32	DBPDCNT3_A,	DBPDCNT3_D3
	wait_timer WAIT_16MCLK

	write32	DBPDCNT3_A,	DBPDCNT3_D4
	wait_timer WAIT_200US_400

	write32	DBPDCNT3_A,	DBPDCNT3_D5
	wait_timer WAIT_1MCLK

	write32	DBPDCNT3_A,	DBPDCNT3_D6
	wait_timer WAIT_10KMCLK

	bra init_dbsc3_ctrl_400
	nop

	.align 2

init_dbsc3_533_pad:

	write32	DBPDCNT3_A,	DBPDCNT3_D
	wait_timer	WAIT_200US_533

	write32 DBPDCNT0_A,	DBPDCNT0_D_533
	write32 DBPDCNT3_A,	DBPDCNT3_D0
	write32 DBPDCNT1_A,	DBPDCNT1_D

	write32 DBPDCNT3_A,	DBPDCNT3_D1
	wait_timer WAIT_32MCLK

	write32	DBPDCNT3_A,	DBPDCNT3_D2
	wait_timer WAIT_100US_533

	write32	DBPDCNT3_A,	DBPDCNT3_D3
	wait_timer WAIT_16MCLK

	write32	DBPDCNT3_A,	DBPDCNT3_D4
	wait_timer WAIT_200US_533

	write32	DBPDCNT3_A,	DBPDCNT3_D5
	wait_timer WAIT_1MCLK

	write32	DBPDCNT3_A,	DBPDCNT3_D6
	wait_timer	WAIT_10KMCLK

	bra init_dbsc3_ctrl_533
	nop

	.align 2

WAIT_200US_400:	.long	40000
WAIT_200US_533:	.long	53300
WAIT_100US_400:	.long	20000
WAIT_100US_533:	.long	26650
WAIT_32MCLK:	.long	32
WAIT_16MCLK:	.long	16
WAIT_1MCLK:		.long	1
WAIT_10KMCLK:	.long	10000

DBPDCNT0_A:		.long	0xFE800200
DBPDCNT0_D_533:	.long	0x00010245
DBPDCNT0_D_400:	.long	0x00010235
DBPDCNT1_A:		.long	0xFE800204
DBPDCNT1_D:		.long	0x00000014
DBPDCNT3_A:		.long	0xFE80020C
DBPDCNT3_D:		.long	0x80000000
DBPDCNT3_D0:	.long	0x800F0000
DBPDCNT3_D1:	.long	0x800F1000
DBPDCNT3_D2:	.long	0x820F1000
DBPDCNT3_D3:	.long	0x860F1000
DBPDCNT3_D4:	.long	0x870F1000
DBPDCNT3_D5:	.long	0x870F3000
DBPDCNT3_D6:	.long	0x870F7000

init_dbsc3_ctrl_400:

	write32 DBKIND_A, DBKIND_D
	write32 DBCONF_A, DBCONF_D

	write32 DBTR0_A,	DBTR0_D_400
	write32 DBTR1_A,	DBTR1_D_400
	write32 DBTR2_A,	DBTR2_D
	write32 DBTR3_A,	DBTR3_D_400
	write32 DBTR4_A,	DBTR4_D_400
	write32 DBTR5_A,	DBTR5_D_400
	write32 DBTR6_A,	DBTR6_D_400
	write32 DBTR7_A,	DBTR7_D
	write32 DBTR8_A,	DBTR8_D_400
	write32 DBTR9_A,	DBTR9_D
	write32 DBTR10_A,	DBTR10_D_400
	write32 DBTR11_A,	DBTR11_D
	write32 DBTR12_A,	DBTR12_D_400
	write32 DBTR13_A,	DBTR13_D_400
	write32 DBTR14_A,	DBTR14_D
	write32 DBTR15_A,	DBTR15_D
	write32 DBTR16_A,	DBTR16_D_400
	write32 DBTR17_A,	DBTR17_D_400
	write32 DBTR18_A,	DBTR18_D_400

	write32	DBBL_A,	DBBL_D
	write32	DBRNK0_A,	DBRNK0_D

	write32 DBCMD_A,	DBCMD_D0_400
	write32 DBCMD_A,	DBCMD_D1
	write32 DBCMD_A,	DBCMD_D2
	write32 DBCMD_A,	DBCMD_D3
	write32 DBCMD_A,	DBCMD_D4
	write32 DBCMD_A,	DBCMD_D5_400
	write32 DBCMD_A,	DBCMD_D6
	write32 DBCMD_A,	DBCMD_D7
	write32 DBCMD_A,	DBCMD_D8
	write32 DBCMD_A,	DBCMD_D9_400
	write32 DBCMD_A,	DBCMD_D10
	write32 DBCMD_A,	DBCMD_D11
	write32 DBCMD_A,	DBCMD_D12

	write32 DBBS0CNT1_A,	DBBS0CNT1_D
	write32 DBPDNCNF_A,		DBPDNCNF_D

	write32	DBRFCNF0_A,	DBRFCNF0_D
	write32	DBRFCNF1_A,	DBRFCNF1_D_400
	write32	DBRFCNF2_A,	DBRFCNF2_D
	write32	DBRFEN_A,	DBRFEN_D
	write32	DBACEN_A,	DBACEN_D
	write32	DBACEN_A,	DBACEN_D

	/* Dummy read */
	mov.l DBWAIT_A, r1
	synco
	mov.l @r1, r0
	synco

	/* Dummy read */
	mov.l SDRAM_A, r1
	synco
	mov.l @r1, r0
	synco

	/* need sleep 186A0 */

	bra	init_pfc_sh7734
	nop

	.align 2

init_dbsc3_ctrl_533:

	write32 DBKIND_A, DBKIND_D
	write32 DBCONF_A, DBCONF_D

	write32 DBTR0_A,	DBTR0_D_533
	write32 DBTR1_A,	DBTR1_D_533
	write32 DBTR2_A,	DBTR2_D
	write32 DBTR3_A,	DBTR3_D_533
	write32 DBTR4_A,	DBTR4_D_533
	write32 DBTR5_A,	DBTR5_D_533
	write32 DBTR6_A,	DBTR6_D_533
	write32 DBTR7_A,	DBTR7_D
	write32 DBTR8_A,	DBTR8_D_533
	write32 DBTR9_A,	DBTR9_D
	write32 DBTR10_A,	DBTR10_D_533
	write32 DBTR11_A,	DBTR11_D
	write32 DBTR12_A,	DBTR12_D_533
	write32 DBTR13_A,	DBTR13_D_533
	write32 DBTR14_A,	DBTR14_D
	write32 DBTR15_A,	DBTR15_D
	write32 DBTR16_A,	DBTR16_D_533
	write32 DBTR17_A,	DBTR17_D_533
	write32 DBTR18_A,	DBTR18_D_533

	write32	DBBL_A,	DBBL_D
	write32	DBRNK0_A,	DBRNK0_D

	write32 DBCMD_A,	DBCMD_D0_533
	write32 DBCMD_A,	DBCMD_D1
	write32 DBCMD_A,	DBCMD_D2
	write32 DBCMD_A,	DBCMD_D3
	write32 DBCMD_A,	DBCMD_D4
	write32 DBCMD_A,	DBCMD_D5_533
	write32 DBCMD_A,	DBCMD_D6
	write32 DBCMD_A,	DBCMD_D7
	write32 DBCMD_A,	DBCMD_D8
	write32 DBCMD_A,	DBCMD_D9_533
	write32 DBCMD_A,	DBCMD_D10
	write32 DBCMD_A,	DBCMD_D11
	write32 DBCMD_A,	DBCMD_D12

	write32 DBBS0CNT1_A,	DBBS0CNT1_D
	write32 DBPDNCNF_A,		DBPDNCNF_D

	write32	DBRFCNF0_A,	DBRFCNF0_D
	write32	DBRFCNF1_A,	DBRFCNF1_D_533
	write32	DBRFCNF2_A,	DBRFCNF2_D
	write32	DBRFEN_A,	DBRFEN_D
	write32	DBACEN_A,	DBACEN_D
	write32	DBACEN_A,	DBACEN_D

	/* Dummy read */
	mov.l DBWAIT_A, r1
	synco
	mov.l @r1, r0
	synco

	/* Dummy read */
	mov.l SDRAM_A, r1
	synco
	mov.l @r1, r0
	synco

	/* need sleep 186A0 */

	bra	init_pfc_sh7734
	nop

	.align 2

DBKIND_A:	.long	0xFE800020
DBKIND_D:	.long	0x00000005
DBCONF_A:	.long	0xFE800024
DBCONF_D:	.long	0x0D030A01

DBTR0_A:	.long	0xFE800040
DBTR0_D_533:.long	0x00000004
DBTR0_D_400:.long	0x00000003
DBTR1_A:	.long	0xFE800044
DBTR1_D_533:.long	0x00000003
DBTR1_D_400:.long	0x00000002
DBTR2_A:	.long	0xFE800048
DBTR2_D:	.long	0x00000000
DBTR3_A:	.long	0xFE800050
DBTR3_D_533:.long	0x00000004
DBTR3_D_400:.long	0x00000003

DBTR4_A:	.long	0xFE800054
DBTR4_D_533:.long	0x00050004
DBTR4_D_400:.long	0x00050003

DBTR5_A:	.long	0xFE800058
DBTR5_D_533:.long	0x0000000F
DBTR5_D_400:.long	0x0000000B

DBTR6_A:	.long	0xFE80005C
DBTR6_D_533:.long	0x0000000B
DBTR6_D_400:.long	0x00000008

DBTR7_A:	.long	0xFE800060
DBTR7_D:	.long	0x00000002 /* common value */

DBTR8_A:	.long	0xFE800064
DBTR8_D_533:.long	0x0000000D
DBTR8_D_400:.long	0x0000000A

DBTR9_A:	.long	0xFE800068
DBTR9_D:	.long	0x00000002 /* common value */

DBTR10_A:	.long	0xFE80006C
DBTR10_D_533:.long	0x00000004
DBTR10_D_400:.long	0x00000003

DBTR11_A:	.long	0xFE800070
DBTR11_D:	.long	0x00000008 /* common value */

DBTR12_A:	.long	0xFE800074
DBTR12_D_533:.long	0x00000009
DBTR12_D_400:.long	0x00000008

DBTR13_A:	.long	0xFE800078
DBTR13_D_533:.long	0x00000022
DBTR13_D_400:.long	0x0000001A

DBTR14_A:	.long	0xFE80007C
DBTR14_D:	.long	0x00070002 /* common value */

DBTR15_A:	.long	0xFE800080
DBTR15_D:	.long	0x00000003 /* common value */

DBTR16_A:	.long	0xFE800084
DBTR16_D_533:.long	0x120A1001
DBTR16_D_400:.long	0x12091001

DBTR17_A:	.long	0xFE800088
DBTR17_D_533:.long	0x00040000
DBTR17_D_400:.long	0x00030000

DBTR18_A:	.long	0xFE80008C
DBTR18_D_533:.long	0x02010200
DBTR18_D_400:.long	0x02000207

DBBL_A:	.long	0xFE8000B0
DBBL_D:	.long	0x00000000

DBRNK0_A:		.long	0xFE800100
DBRNK0_D:		.long	0x00000001

DBCMD_A:		.long	0xFE800018
DBCMD_D0_533:	.long	0x1100006B
DBCMD_D0_400:	.long	0x11000050
DBCMD_D1:		.long	0x0B000000 /* common value */
DBCMD_D2:		.long	0x2A004000 /* common value */
DBCMD_D3:		.long	0x2B006000 /* common value */
DBCMD_D4:		.long	0x29002004 /* common value */
DBCMD_D5_533:	.long	0x28000743
DBCMD_D5_400:	.long	0x28000533
DBCMD_D6:		.long	0x0B000000 /* common value */
DBCMD_D7:		.long	0x0C000000 /* common value */
DBCMD_D8:		.long	0x0C000000 /* common value */
DBCMD_D9_533:	.long	0x28000643
DBCMD_D9_400:	.long	0x28000433
DBCMD_D10:		.long	0x000000C8 /* common value */
DBCMD_D11:		.long	0x29002384 /* common value */
DBCMD_D12:		.long	0x29002004 /* common value */

DBBS0CNT1_A:	.long	0xFE800304
DBBS0CNT1_D:	.long	0x00000000
DBPDNCNF_A:		.long	0xFE800180
DBPDNCNF_D:		.long	0x00000200

DBRFCNF0_A:		.long	0xFE8000E0
DBRFCNF0_D:		.long	0x000001FF
DBRFCNF1_A:		.long	0xFE8000E4
DBRFCNF1_D_533:	.long	0x00000805
DBRFCNF1_D_400:	.long	0x00000618

DBRFCNF2_A:		.long	0xFE8000E8
DBRFCNF2_D:		.long	0x00000000

DBRFEN_A:		.long	0xFE800014
DBRFEN_D:		.long	0x00000001

DBACEN_A:		.long	0xFE800010
DBACEN_D:		.long	0x00000001

DBWAIT_A:		.long	0xFE80001C
SDRAM_A:		.long	0x0C000000

init_pfc_sh7734:
	write32	PFC_PMMR_A, PFC_PMMR_MODESEL1
	write32 PFC_MODESEL1_A, PFC_MODESEL1_D

	write32	PFC_PMMR_A, PFC_PMMR_MODESEL2
	write32 PFC_MODESEL2_A, PFC_MODESEL2_D

	write32	PFC_PMMR_A, PFC_PMMR_IPSR3
	write32 PFC_IPSR3_A, PFC_IPSR3_D

	write32	PFC_PMMR_A, PFC_PMMR_IPSR4
	write32 PFC_IPSR4_A, PFC_IPSR4_D

	write32	PFC_PMMR_A, PFC_PMMR_IPSR11
	write32 PFC_IPSR11_A, PFC_IPSR11_D

	write32	PFC_PMMR_A, PFC_PMMR_GPSR0
	write32 PFC_GPSR0_A, PFC_GPSR0_D

	write32	PFC_PMMR_A, PFC_PMMR_GPSR1
	write32 PFC_GPSR1_A, PFC_GPSR1_D

	write32	PFC_PMMR_A, PFC_PMMR_GPSR2
	write32 PFC_GPSR2_A, PFC_GPSR2_D

	write32	PFC_PMMR_A, PFC_PMMR_GPSR3
	write32 PFC_GPSR3_A, PFC_GPSR3_D

	write32	PFC_PMMR_A, PFC_PMMR_GPSR4
	write32 PFC_GPSR4_A, PFC_GPSR4_D

	write32	PFC_PMMR_A, PFC_PMMR_GPSR5
	write32 PFC_GPSR5_A, PFC_GPSR5_D

	/* sleep 186A0 */

	write32 GPIO2_INOUTSEL1_A, GPIO2_INOUTSEL1_D
	write32 GPIO1_OUTDT1_A,	GPIO1_OUTDT1_D
	write32	GPIO2_INOUTSEL2_A, GPIO2_INOUTSEL2_D
	write32 GPIO2_OUTDT2_A, GPIO2_OUTDT2_D
	write32 GPIO4_INOUTSEL4_A,	GPIO4_INOUTSEL4_D
	write32 GPIO4_OUTDT4_A,	GPIO4_OUTDT4_D

	write32 CCR_A,  CCR_D

	stc sr, r0
	mov.l  SR_MASK_D, r1
	and r1, r0
	ldc r0, sr

	rts
	nop

	.align  2

PFC_PMMR_A:		.long	0xFFFC0000

/* MODESEL
 * 28: Select IEBUS Group B
 */
PFC_MODESEL1_A:	.long	0xFFFC004C
PFC_MODESEL1_D:	.long	0x10000000
PFC_PMMR_MODESEL1:	.long	0xEFFFFFFF

/* MODESEL
 * 9: Select SCIF3 Group B
 * 7: Select SCIF2 Group B
 * 4: Select SCIF1 Group B
 */
PFC_MODESEL2_A:	.long	0xFFFC0050
PFC_MODESEL2_D:	.long	0x00000290
PFC_PMMR_MODESEL2:	.long	0xFFFFFD6F

# Enable functios
# SD1_DAT2_A SD1_DAT1_A, SD1_DAT0_A,
# EXWAIT0, RDW/RW, SD1_CMD_A, SD1_WP_A,
# SD1_CD_A, TX3_B, RX3_B, CS1, D15
PFC_IPSR3_A:	.long	0xFFFC0028
PFC_IPSR3_D:	.long	0x09209248
PFC_PMMR_IPSR3:	.long	0xF6DF6DB7

# Enable functios
# RMII0_MDIO_A , RMII0_MDC_A,
# RMII0_CRS_DV_A, RMII0_RX_ER_A,
# RMII0_TXD_EN_A, MII0_RXD1_A
PFC_IPSR4_A:	.long	0xFFFC002C
PFC_IPSR4_D:	.long	0x0001B6DB
PFC_PMMR_IPSR4:	.long	0xFFFE4924

# Enable functios
# DACK1, DREQ1, SD1_DAT3_A, SD1_CLK_A, IERX_B,
# IETX_B, TX0_A, RMII0_TXD0_A,
# RMII0_TXD1_A, RMII0_TXD0_A, SDSEL, SDA0, SDA1, SCL1
PFC_IPSR11_A:	.long	0xFFFC0048
PFC_IPSR11_D:	.long	0x002C89B0
PFC_PMMR_IPSR11:.long	0xFFD3764F

PFC_GPSR0_A:	.long	0xFFFC0004
PFC_GPSR0_D:	.long	0xFFFFFFFF
PFC_PMMR_GPSR0:	.long	0x00000000

PFC_GPSR1_A:	.long	0xFFFC0008
PFC_GPSR1_D:	.long	0x7FBF7FFF
PFC_PMMR_GPSR1:	.long	0x80408000

PFC_GPSR2_A:	.long	0xFFFC000C
PFC_GPSR2_D:	.long	0xBFC07EDF
PFC_PMMR_GPSR2:	.long	0x403F8120

PFC_GPSR3_A:	.long	0xFFFC0010
PFC_GPSR3_D:	.long	0xFFFFFFFF
PFC_PMMR_GPSR3:	.long	0x00000000

PFC_GPSR4_A:	.long	0xFFFC0014
#if 0 /* orig */
PFC_GPSR4_D:	.long	0xFFFFFFFF
PFC_PMMR_GPSR4:	.long	0x00000000
#else
PFC_GPSR4_D:	.long	0xFBFFFFFF
PFC_PMMR_GPSR4:	.long	0x04000000
#endif

PFC_GPSR5_A:	.long	0xFFFC0018
PFC_GPSR5_D:	.long	0x00000C01
PFC_PMMR_GPSR5:	.long	0xFFFFF3FE

I2C_ICCR2_A: .long	0xFFC70001
I2C_ICCR2_D: .long	0x00
I2C_ICCR2_D1: .long	0x20

GPIO2_INOUTSEL1_A:	.long	0xFFC41004
GPIO2_INOUTSEL1_D:	.long	0x80408000
GPIO1_OUTDT1_A:		.long	0xFFC41008	/* bit15: LED4, bit22: LED5 */
GPIO1_OUTDT1_D:		.long	0x80408000
GPIO2_INOUTSEL2_A:	.long	0xFFC42004
GPIO2_INOUTSEL2_D:	.long	0x40000120
GPIO2_OUTDT2_A:		.long	0xFFC42008
GPIO2_OUTDT2_D:		.long	0x40000120
GPIO4_INOUTSEL4_A:	.long	0xFFC44004
GPIO4_INOUTSEL4_D:	.long	0x04000000
GPIO4_OUTDT4_A:		.long	0xFFC44008
GPIO4_OUTDT4_D:		.long	0x04000000

CCR_A:	.long	0xFF00001C
CCR_D:	.long	0x0000090B
SR_MASK_D:	.long	0xEFFFFF0F
