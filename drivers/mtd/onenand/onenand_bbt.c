/*
 *  linux/drivers/mtd/onenand/onenand_bbt.c
 *
 *  Bad Block Table support for the OneNAND driver
 *
 *  Copyright(c) 2005-2008 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 *  TODO:
 *    Split BBT core and chip specific BBT.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <common.h>
#include <linux/compat.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/onenand.h>
#include <malloc.h>

#include <asm/errno.h>

/**
 * check_short_pattern - [GENERIC] check if a pattern is in the buffer
 * @param buf		the buffer to search
 * @param len		the length of buffer to search
 * @param paglen	the pagelength
 * @param td		search pattern descriptor
 *
 * Check for a pattern at the given place. Used to search bad block
 * tables and good / bad block identifiers. Same as check_pattern, but
 * no optional empty check and the pattern is expected to start
 * at offset 0.
 */
static int check_short_pattern(uint8_t * buf, int len, int paglen,
			       struct nand_bbt_descr *td)
{
	int i;
	uint8_t *p = buf;

	/* Compare the pattern */
	for (i = 0; i < td->len; i++) {
		if (p[i] != td->pattern[i])
			return -1;
	}
	return 0;
}

/**
 * create_bbt - [GENERIC] Create a bad block table by scanning the device
 * @param mtd		MTD device structure
 * @param buf		temporary buffer
 * @param bd		descriptor for the good/bad block search pattern
 * @param chip		create the table for a specific chip, -1 read all chips.
 *              Applies only if NAND_BBT_PERCHIP option is set
 *
 * Create a bad block table by scanning the device
 * for the given good/bad block identify pattern
 */
static int create_bbt(struct mtd_info *mtd, uint8_t * buf,
		      struct nand_bbt_descr *bd, int chip)
{
	struct onenand_chip *this = mtd->priv;
	struct bbm_info *bbm = this->bbm;
	int i, j, numblocks, len, scanlen;
	int startblock;
	loff_t from;
	size_t readlen, ooblen;
	struct mtd_oob_ops ops;
	int rgn;

	printk(KERN_INFO "Scanning device for bad blocks\n");

	len = 1;

	/* We need only read few bytes from the OOB area */
	scanlen = ooblen = 0;
	readlen = bd->len;

	/* chip == -1 case only */
	/* Note that numblocks is 2 * (real numblocks) here;
	 * see i += 2 below as it makses shifting and masking less painful
	 */
	numblocks = this->chipsize >> (bbm->bbt_erase_shift - 1);
	startblock = 0;
	from = 0;

	ops.mode = MTD_OOB_PLACE;
	ops.ooblen = readlen;
	ops.oobbuf = buf;
	ops.len = ops.ooboffs = ops.retlen = ops.oobretlen = 0;

	for (i = startblock; i < numblocks;) {
		int ret;

		for (j = 0; j < len; j++) {
			/* No need to read pages fully,
			 * just read required OOB bytes */
			ret = onenand_bbt_read_oob(mtd,
					     from + j * mtd->writesize +
					     bd->offs, &ops);

			/* If it is a initial bad block, just ignore it */
			if (ret == ONENAND_BBT_READ_FATAL_ERROR)
				return -EIO;

			if (ret || check_short_pattern
			    (&buf[j * scanlen], scanlen, mtd->writesize, bd)) {
				bbm->bbt[i >> 3] |= 0x03 << (i & 0x6);
				printk(KERN_WARNING
				       "Bad eraseblock %d at 0x%08x\n", i >> 1,
				       (unsigned int)from);
				break;
			}
		}
		i += 2;

		if (FLEXONENAND(this)) {
			rgn = flexonenand_region(mtd, from);
			from += mtd->eraseregions[rgn].erasesize;
		} else
			from += (1 << bbm->bbt_erase_shift);
	}

	return 0;
}

/**
 * onenand_memory_bbt - [GENERIC] create a memory based bad block table
 * @param mtd		MTD device structure
 * @param bd		descriptor for the good/bad block search pattern
 *
 * The function creates a memory based bbt by scanning the device
 * for manufacturer / software marked good / bad blocks
 */
static inline int onenand_memory_bbt(struct mtd_info *mtd,
				     struct nand_bbt_descr *bd)
{
	unsigned char data_buf[MAX_ONENAND_PAGESIZE];

	bd->options &= ~NAND_BBT_SCANEMPTY;
	return create_bbt(mtd, data_buf, bd, -1);
}

/**
 * onenand_isbad_bbt - [OneNAND Interface] Check if a block is bad
 * @param mtd		MTD device structure
 * @param offs		offset in the device
 * @param allowbbt	allow access to bad block table region
 */
static int onenand_isbad_bbt(struct mtd_info *mtd, loff_t offs, int allowbbt)
{
	struct onenand_chip *this = mtd->priv;
	struct bbm_info *bbm = this->bbm;
	int block;
	uint8_t res;

	/* Get block number * 2 */
	block = (int) (onenand_block(this, offs) << 1);
	res = (bbm->bbt[block >> 3] >> (block & 0x06)) & 0x03;

	MTDDEBUG (MTD_DEBUG_LEVEL2,
		"onenand_isbad_bbt: bbt info for offs 0x%08x: (block %d) 0x%02x\n",
		(unsigned int)offs, block >> 1, res);

	switch ((int)res) {
	case 0x00:
		return 0;
	case 0x01:
		return 1;
	case 0x02:
		return allowbbt ? 0 : 1;
	}

	return 1;
}

/**
 * onenand_scan_bbt - [OneNAND Interface] scan, find, read and maybe create bad block table(s)
 * @param mtd		MTD device structure
 * @param bd		descriptor for the good/bad block search pattern
 *
 * The function checks, if a bad block table(s) is/are already
 * available. If not it scans the device for manufacturer
 * marked good / bad blocks and writes the bad block table(s) to
 * the selected place.
 *
 * The bad block table memory is allocated here. It must be freed
 * by calling the onenand_free_bbt function.
 *
 */
int onenand_scan_bbt(struct mtd_info *mtd, struct nand_bbt_descr *bd)
{
	struct onenand_chip *this = mtd->priv;
	struct bbm_info *bbm = this->bbm;
	int len, ret = 0;

	len = this->chipsize >> (this->erase_shift + 2);
	/* Allocate memory (2bit per block) */
	bbm->bbt = malloc(len);
	if (!bbm->bbt) {
		printk(KERN_ERR "onenand_scan_bbt: Out of memory\n");
		return -ENOMEM;
	}
	/* Clear the memory bad block table */
	memset(bbm->bbt, 0x00, len);

	/* Set the bad block position */
	bbm->badblockpos = ONENAND_BADBLOCK_POS;

	/* Set erase shift */
	bbm->bbt_erase_shift = this->erase_shift;

	if (!bbm->isbad_bbt)
		bbm->isbad_bbt = onenand_isbad_bbt;

	/* Scan the device to build a memory based bad block table */
	if ((ret = onenand_memory_bbt(mtd, bd))) {
		printk(KERN_ERR
		       "onenand_scan_bbt: Can't scan flash and build the RAM-based BBT\n");
		free(bbm->bbt);
		bbm->bbt = NULL;
	}

	return ret;
}

/*
 * Define some generic bad / good block scan pattern which are used
 * while scanning a device for factory marked good / bad blocks.
 */
static uint8_t scan_ff_pattern[] = { 0xff, 0xff };

static struct nand_bbt_descr largepage_memorybased = {
	.options = 0,
	.offs = 0,
	.len = 2,
	.pattern = scan_ff_pattern,
};

/**
 * onenand_default_bbt - [OneNAND Interface] Select a default bad block table for the device
 * @param mtd		MTD device structure
 *
 * This function selects the default bad block table
 * support for the device and calls the onenand_scan_bbt function
 */
int onenand_default_bbt(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;
	struct bbm_info *bbm;

	this->bbm = malloc(sizeof(struct bbm_info));
	if (!this->bbm)
		return -ENOMEM;

	bbm = this->bbm;

	memset(bbm, 0, sizeof(struct bbm_info));

	/* 1KB page has same configuration as 2KB page */
	if (!bbm->badblock_pattern)
		bbm->badblock_pattern = &largepage_memorybased;

	return onenand_scan_bbt(mtd, bbm->badblock_pattern);
}
