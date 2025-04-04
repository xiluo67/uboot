/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 1999,2000,2001,2002,2003,2004  Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/*
 * Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#include <common.h>
#include <malloc.h>
#include <linux/stat.h>
#include <linux/time.h>
#include <linux/ctype.h>
#include <asm/byteorder.h>
#include "zfs_common.h"

#include <zfs/zfs.h>
#include <zfs/zio.h>
#include <zfs/dnode.h>
#include <zfs/uberblock_impl.h>
#include <zfs/vdev_impl.h>
#include <zfs/zio_checksum.h>
#include <zfs/zap_impl.h>
#include <zfs/zap_leaf.h>
#include <zfs/zfs_znode.h>
#include <zfs/dmu.h>
#include <zfs/dmu_objset.h>
#include <zfs/dsl_dir.h>
#include <zfs/dsl_dataset.h>

void
fletcher_2_endian(const void *buf, uint64_t size,
				  zfs_endian_t endian,
				  zio_cksum_t *zcp)
{
	const uint64_t *ip = buf;
	const uint64_t *ipend = ip + (size / sizeof(uint64_t));
	uint64_t a0, b0, a1, b1;

	for (a0 = b0 = a1 = b1 = 0; ip < ipend; ip += 2) {
		a0 += zfs_to_cpu64(ip[0], endian);
		a1 += zfs_to_cpu64(ip[1], endian);
		b0 += a0;
		b1 += a1;
	}

	zcp->zc_word[0] = cpu_to_zfs64(a0, endian);
	zcp->zc_word[1] = cpu_to_zfs64(a1, endian);
	zcp->zc_word[2] = cpu_to_zfs64(b0, endian);
	zcp->zc_word[3] = cpu_to_zfs64(b1, endian);
}

void
fletcher_4_endian(const void *buf, uint64_t size, zfs_endian_t endian,
				  zio_cksum_t *zcp)
{
	const uint32_t *ip = buf;
	const uint32_t *ipend = ip + (size / sizeof(uint32_t));
	uint64_t a, b, c, d;

	for (a = b = c = d = 0; ip < ipend; ip++) {
		a += zfs_to_cpu32(ip[0], endian);
		b += a;
		c += b;
		d += c;
	}

	zcp->zc_word[0] = cpu_to_zfs64(a, endian);
	zcp->zc_word[1] = cpu_to_zfs64(b, endian);
	zcp->zc_word[2] = cpu_to_zfs64(c, endian);
	zcp->zc_word[3] = cpu_to_zfs64(d, endian);
}
