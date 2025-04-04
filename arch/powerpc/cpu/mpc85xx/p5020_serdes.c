/*
 * Copyright 2009-2011 Freescale Semiconductor, Inc.
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

#include <common.h>
#include <asm/fsl_serdes.h>
#include <asm/processor.h>
#include <asm/io.h>
#include "fsl_corenet_serdes.h"

static u8 serdes_cfg_tbl[][SRDS_MAX_LANES] = {
	[0x2] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2,
		PCIE4, AURORA, PCIE3, SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3,
		SGMII_FM1_DTSEC4, NONE, NONE, SATA1, SATA2, },
	[0x4] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		PCIE2, AURORA, PCIE3, SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3,
		SGMII_FM1_DTSEC4, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1, },
	[0xb] = {PCIE1, PCIE1, PCIE1, PCIE1, SRIO2, SRIO2, SRIO1, SRIO1,
		PCIE2, AURORA, PCIE3, SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3,
		SGMII_FM1_DTSEC4, NONE, NONE, SATA1, SATA2, },
	[0x10] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1,
		AURORA, AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1,
		NONE, NONE, SATA1, SATA2, },
	[0x11] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, NONE, NONE, SATA1, SATA2, },
	[0x13] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, XAUI_FM1, XAUI_FM1,
		XAUI_FM1, XAUI_FM1, },
	[0x14] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, PCIE3, PCIE3, PCIE3, PCIE3,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3,
		SGMII_FM1_DTSEC4, },
	[0x15] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1,
		NONE, NONE, SATA1, SATA2, },
	[0x16] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, SRIO1, SRIO1, SRIO1,
		SRIO1, },
	[0x17] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, NONE, NONE, SATA1, SATA2, },
	[0x18] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, SGMII_FM1_DTSEC5, NONE,
		NONE, NONE, },
	[0x1b] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1,
		NONE, NONE, SATA1, SATA2, },
	[0x1d] = {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, PCIE3, PCIE3, PCIE3, PCIE3, NONE, NONE,
		SATA1, SATA2, },
	[0x20] = {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, XAUI_FM1, XAUI_FM1,
		XAUI_FM1, XAUI_FM1, },
	[0x21] = {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, PCIE3, PCIE3, PCIE3, PCIE3,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3,
		SGMII_FM1_DTSEC4, },
	[0x22] = {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1,
		NONE, NONE, SATA1, SATA2, },
	[0x23] = {PCIE1, PCIE1, PCIE1, PCIE1, SRIO2, SRIO2, SRIO1, SRIO1,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, NONE, NONE, SATA1, SATA2, },
	[0x24] = {PCIE1, PCIE1, PCIE1, PCIE1, SRIO2, SRIO2, SRIO1, SRIO1,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, SGMII_FM1_DTSEC5, NONE,
		NONE, NONE, },
	[0x28] = {PCIE1, PCIE1, PCIE3, PCIE3, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, NONE, NONE, SATA1, SATA2, },
	[0x29] = {PCIE1, PCIE1, PCIE3, PCIE3, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, SGMII_FM1_DTSEC5, NONE,
		NONE, NONE, },
	[0x2a] = {PCIE1, PCIE1, PCIE3, PCIE3, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, XAUI_FM1, XAUI_FM1,
		XAUI_FM1, XAUI_FM1, },
	[0x2b] = {PCIE1, PCIE1, PCIE3, PCIE3, PCIE2, PCIE2, PCIE2, PCIE2,
		AURORA, AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1,
		NONE, NONE, SATA1, SATA2, },
	[0x2f] = {PCIE1, PCIE1, PCIE3, PCIE3, SRIO2, SRIO2, SRIO1, SRIO1,
		AURORA, AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1,
		NONE, NONE, SATA1, SATA2, },
	[0x31] = {PCIE1, PCIE1, PCIE3, PCIE3, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, SGMII_FM1_DTSEC5, NONE,
		NONE, NONE, },
	[0x33] = {PCIE1, PCIE1, PCIE3, PCIE3, SRIO1, SRIO1, SRIO1, SRIO1,
		AURORA, AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1,
		NONE, NONE, SATA1, SATA2, },
	[0x34] = {PCIE1, PCIE1, PCIE1, PCIE1, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, AURORA,
		AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1, NONE,
		NONE, SATA1, SATA2, },
	[0x35] = {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, AURORA, AURORA, XAUI_FM1,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, NONE, NONE, SATA1, SATA2, },
	[0x36] = {PCIE1, PCIE1, PCIE3, PCIE3, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, AURORA,
		AURORA, XAUI_FM1, XAUI_FM1, XAUI_FM1, XAUI_FM1, NONE,
		NONE, SATA1, SATA2, },
	[0x37] = {PCIE1, PCIE1, PCIE3, PCIE3, PCIE2, PCIE2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4, AURORA, AURORA, XAUI_FM1,
		XAUI_FM1, XAUI_FM1, XAUI_FM1, NONE, NONE, SATA1, SATA2, },
};

enum srds_prtcl serdes_get_prtcl(int cfg, int lane)
{
	if (!serdes_lane_enabled(lane))
		return NONE;

	return serdes_cfg_tbl[cfg][lane];
}

int is_serdes_prtcl_valid(u32 prtcl) {
	int i;

	if (prtcl > ARRAY_SIZE(serdes_cfg_tbl))
		return 0;

	for (i = 0; i < SRDS_MAX_LANES; i++) {
		if (serdes_cfg_tbl[prtcl][i] != NONE)
			return 1;
	}

	return 0;
}
