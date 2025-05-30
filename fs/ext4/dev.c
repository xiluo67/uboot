/*
 * (C) Copyright 2011 - 2012 Samsung Electronics
 * EXT4 filesystem implementation in Uboot by
 * Uma Shankar <uma.shankar@samsung.com>
 * Manjunatha C Achar <a.manjunatha@samsung.com>
 *
 * made from existing ext2/dev.c file of Uboot
 * (C) Copyright 2004
 * esd gmbh <www.esd-electronics.com>
 * Reinhard Arlt <reinhard.arlt@esd-electronics.com>
 *
 * based on code of fs/reiserfs/dev.c by
 *
 * (C) Copyright 2003 - 2004
 * Sysgo AG, <www.elinos.com>, Pavel Bartusek <pba@sysgo.com>
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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/*
 * Changelog:
 *	0.1 - Newly created file for ext4fs support. Taken from
 *		fs/ext2/dev.c file in uboot.
 */

#include <common.h>
#include <config.h>
#include <ext4fs.h>
#include <ext_common.h>

unsigned long part_offset;

static block_dev_desc_t *ext4fs_block_dev_desc;
static disk_partition_t *part_info;

void ext4fs_set_blk_dev(block_dev_desc_t *rbdd, disk_partition_t *info)
{
	ext4fs_block_dev_desc = rbdd;
	part_info = info;
	part_offset = info->start;
	get_fs()->total_sect = (info->size * info->blksz) / SECTOR_SIZE;
}

int ext4fs_devread(int sector, int byte_offset, int byte_len, char *buf)
{
	ALLOC_CACHE_ALIGN_BUFFER(char, sec_buf, SECTOR_SIZE);
	unsigned block_len;

	/* Check partition boundaries */
	if ((sector < 0)
	    || ((sector + ((byte_offset + byte_len - 1) >> SECTOR_BITS)) >=
		part_info->size)) {
		printf("%s read outside partition %d\n", __func__, sector);
		return 0;
	}

	/* Get the read to the beginning of a partition */
	sector += byte_offset >> SECTOR_BITS;
	byte_offset &= SECTOR_SIZE - 1;

	debug(" <%d, %d, %d>\n", sector, byte_offset, byte_len);

	if (ext4fs_block_dev_desc == NULL) {
		printf("** Invalid Block Device Descriptor (NULL)\n");
		return 0;
	}

	if (byte_offset != 0) {
		/* read first part which isn't aligned with start of sector */
		if (ext4fs_block_dev_desc->
		    block_read(ext4fs_block_dev_desc->dev,
				part_info->start + sector, 1,
				(unsigned long *) sec_buf) != 1) {
			printf(" ** ext2fs_devread() read error **\n");
			return 0;
		}
		memcpy(buf, sec_buf + byte_offset,
			min(SECTOR_SIZE - byte_offset, byte_len));
		buf += min(SECTOR_SIZE - byte_offset, byte_len);
		byte_len -= min(SECTOR_SIZE - byte_offset, byte_len);
		sector++;
	}

	if (byte_len == 0)
		return 1;

	/* read sector aligned part */
	block_len = byte_len & ~(SECTOR_SIZE - 1);

	if (block_len == 0) {
		ALLOC_CACHE_ALIGN_BUFFER(u8, p, SECTOR_SIZE);

		block_len = SECTOR_SIZE;
		ext4fs_block_dev_desc->block_read(ext4fs_block_dev_desc->dev,
						  part_info->start + sector,
						  1, (unsigned long *)p);
		memcpy(buf, p, byte_len);
		return 1;
	}

	if (ext4fs_block_dev_desc->block_read(ext4fs_block_dev_desc->dev,
					       part_info->start + sector,
					       block_len / SECTOR_SIZE,
					       (unsigned long *) buf) !=
					       block_len / SECTOR_SIZE) {
		printf(" ** %s read error - block\n", __func__);
		return 0;
	}
	block_len = byte_len & ~(SECTOR_SIZE - 1);
	buf += block_len;
	byte_len -= block_len;
	sector += block_len / SECTOR_SIZE;

	if (byte_len != 0) {
		/* read rest of data which are not in whole sector */
		if (ext4fs_block_dev_desc->
		    block_read(ext4fs_block_dev_desc->dev,
				part_info->start + sector, 1,
				(unsigned long *) sec_buf) != 1) {
			printf("* %s read error - last part\n", __func__);
			return 0;
		}
		memcpy(buf, sec_buf, byte_len);
	}
	return 1;
}
