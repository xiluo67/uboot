/*
 * (C) Copyright 2002-2005
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002 Jun Gu <jung@artesyncp.com>
 * Add support for Am29F016D and dynamic switch setting.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
/*
 * Ported from Ebony flash support
 * Travis B. Sawyer
 * Sandburst Corporation
 */
#include <common.h>
#include <asm/ppc4xx.h>
#include <asm/processor.h>


#undef DEBUG
#ifdef DEBUG
#define DEBUGF(x...) printf(x)
#else
#define DEBUGF(x...)
#endif /* DEBUG */


flash_info_t flash_info[CONFIG_SYS_MAX_FLASH_BANKS]; /* info for FLASH chips	*/

static unsigned long flash_addr_table[8][CONFIG_SYS_MAX_FLASH_BANKS] = {
	{0xfff80000}	/* Boot Flash */
};

/*-----------------------------------------------------------------------
 * Functions
 */
static ulong flash_get_size (vu_long *addr, flash_info_t *info);
static int write_word (flash_info_t *info, ulong dest, ulong data);


#define ADDR0		0x5555
#define ADDR1		0x2aaa
#define FLASH_WORD_SIZE unsigned char


/*-----------------------------------------------------------------------
 */

unsigned long flash_init (void)
{
	unsigned long total_b = 0;
	unsigned long size_b[CONFIG_SYS_MAX_FLASH_BANKS];
	unsigned short index = 0;
	int i;


	DEBUGF("\n");
	DEBUGF("FLASH: Index: %d\n", index);

	/* Init: no FLASHes known */
	for (i=0; i<CONFIG_SYS_MAX_FLASH_BANKS; ++i) {
		flash_info[i].flash_id = FLASH_UNKNOWN;
		flash_info[i].sector_count = -1;
		flash_info[i].size = 0;

		/* check whether the address is 0 */
		if (flash_addr_table[index][i] == 0) {
			continue;
		}

		/* call flash_get_size() to initialize sector address */
		size_b[i] = flash_get_size(
			(vu_long *)flash_addr_table[index][i], &flash_info[i]);
		flash_info[i].size = size_b[i];
		if (flash_info[i].flash_id == FLASH_UNKNOWN) {
			printf ("## Unknown FLASH on Bank %d - Size = 0x%08lx = %ld MB\n",
				i, size_b[i], size_b[i]<<20);
			flash_info[i].sector_count = -1;
			flash_info[i].size = 0;
		}

		total_b += flash_info[i].size;
	}

	return total_b;
}


/*-----------------------------------------------------------------------
 */
void flash_print_info  (flash_info_t *info)
{
	int i;
	int k;
	int size;
	int erased;
	volatile unsigned long *flash;

	if (info->flash_id == FLASH_UNKNOWN) {
		printf ("missing or unknown FLASH type\n");
		return;
	}

	switch (info->flash_id & FLASH_VENDMASK) {
	case FLASH_MAN_AMD:	printf ("AMD ");		break;
	default:		printf ("Unknown Vendor ");	break;
	}

	switch (info->flash_id & FLASH_TYPEMASK) {
	case FLASH_AM040:	printf ("AM29F040 (512 Kbit, uniform sector size)\n");
		break;
	default:		printf ("Unknown Chip Type\n");
		break;
	}

	printf ("  Size: %ld KB in %d Sectors\n",
		info->size >> 10, info->sector_count);

	printf ("  Sector Start Addresses:");
	for (i=0; i<info->sector_count; ++i) {
		/*
		 * Check if whole sector is erased
		 */
		if (i != (info->sector_count-1))
			size = info->start[i+1] - info->start[i];
		else
			size = info->start[0] + info->size - info->start[i];
		erased = 1;
		flash = (volatile unsigned long *)info->start[i];
		size = size >> 2;	 /* divide by 4 for longword access */
		for (k=0; k<size; k++)
		{
			if (*flash++ != 0xffffffff)
			{
				erased = 0;
				break;
			}
		}

		if ((i % 5) == 0)
			printf ("\n   ");
			printf (" %08lX%s%s",
				info->start[i],
				erased ? " E" : "  ",
				info->protect[i] ? "RO " : "   "
				);
			}
		printf ("\n");
		return;
	}

/*-----------------------------------------------------------------------
 */


/*-----------------------------------------------------------------------
 */

/*
 * The following code cannot be run from FLASH!
 */
static ulong flash_get_size (vu_long *addr, flash_info_t *info)
{
	short i;
	FLASH_WORD_SIZE value;
	ulong base = (ulong)addr;
	volatile FLASH_WORD_SIZE *addr2 = (FLASH_WORD_SIZE *)addr;

	DEBUGF("FLASH ADDR: %08x\n", (unsigned)addr );

	/* Write auto select command: read Manufacturer ID */
	udelay(10000);
	addr2[ADDR0] = (FLASH_WORD_SIZE)0x00AA00AA;
	udelay(1000);
	addr2[ADDR1] = (FLASH_WORD_SIZE)0x00550055;
	udelay(1000);
	addr2[ADDR0] = (FLASH_WORD_SIZE)0x00900090;
	udelay(1000);

	value = addr2[0];

	DEBUGF("FLASH MANUFACT: %x\n", value);

	switch (value) {
	case (FLASH_WORD_SIZE)AMD_MANUFACT:
		info->flash_id = FLASH_MAN_AMD;
		break;
	default:
		info->flash_id = FLASH_UNKNOWN;
		info->sector_count = 0;
		info->size = 0;
		return (0);			/* no or unknown flash	*/
	}

	value = addr2[1];			/* device ID		*/

	DEBUGF("\nFLASH DEVICEID: %x\n", value);

	switch (value) {
	case (FLASH_WORD_SIZE)AMD_ID_LV040B:
		info->flash_id += FLASH_AM040;
		info->sector_count = 8;
		info->size = 0x00080000; /* => 512 kb */
		break;

	default:
		info->flash_id = FLASH_UNKNOWN;
		return (0);			/* => no or unknown flash */

	}

	/* set up sector start address table */
	if (info->flash_id  == FLASH_AM040) {
		for (i = 0; i < info->sector_count; i++)
			info->start[i] = base + (i * 0x00010000);
	} else {
		if (info->flash_id & FLASH_BTYPE) {
			/* set sector offsets for bottom boot block type	*/
			info->start[0] = base + 0x00000000;
			info->start[1] = base + 0x00004000;
			info->start[2] = base + 0x00006000;
			info->start[3] = base + 0x00008000;
			for (i = 4; i < info->sector_count; i++) {
				info->start[i] = base + (i * 0x00010000) - 0x00030000;
			}
		} else {
			/* set sector offsets for top boot block type		*/
			i = info->sector_count - 1;
			info->start[i--] = base + info->size - 0x00004000;
			info->start[i--] = base + info->size - 0x00006000;
			info->start[i--] = base + info->size - 0x00008000;
			for (; i >= 0; i--) {
				info->start[i] = base + i * 0x00010000;
			}
		}
	}

	/* check for protected sectors */
	for (i = 0; i < info->sector_count; i++) {
		/* read sector protection at sector address, (A7 .. A0) = 0x02 */
		/* D0 = 1 if protected */
		addr2 = (volatile FLASH_WORD_SIZE *)(info->start[i]);
		if ((info->flash_id & FLASH_VENDMASK) == FLASH_MAN_SST)
			info->protect[i] = 0;
		else
			info->protect[i] = addr2[2] & 1;
	}

	/* reset to return to reading data */
	addr2[0] = (FLASH_WORD_SIZE) 0x00F000F0;	/* reset bank */

	/*
	 * Prevent writes to uninitialized FLASH.
	 */
	if (info->flash_id != FLASH_UNKNOWN) {
		addr2 = (FLASH_WORD_SIZE *)info->start[0];
		*addr2 = (FLASH_WORD_SIZE)0x00F000F0;	/* reset bank */
	}

	return (info->size);
}

int wait_for_DQ7(flash_info_t *info, int sect)
{
	ulong start, now, last;
	volatile FLASH_WORD_SIZE *addr = (FLASH_WORD_SIZE *)(info->start[sect]);

	start = get_timer (0);
	last  = start;
	while ((addr[0] & (FLASH_WORD_SIZE)0x00800080) != (FLASH_WORD_SIZE)0x00800080) {
		if ((now = get_timer(start)) > CONFIG_SYS_FLASH_ERASE_TOUT) {
			printf ("Timeout\n");
			return -1;
		}
		/* show that we're waiting */
		if ((now - last) > 1000) {  /* every second */
			putc ('.');
			last = now;
		}
	}
	return 0;
}

/*-----------------------------------------------------------------------
 */

int flash_erase (flash_info_t *info, int s_first, int s_last)
{
	volatile FLASH_WORD_SIZE *addr = (FLASH_WORD_SIZE *)(info->start[0]);
	volatile FLASH_WORD_SIZE *addr2;
	int flag, prot, sect;
	int i;

	if ((s_first < 0) || (s_first > s_last)) {
		if (info->flash_id == FLASH_UNKNOWN) {
			printf ("- missing\n");
		} else {
			printf ("- no sectors to erase\n");
		}
		return 1;
	}

	if (info->flash_id == FLASH_UNKNOWN) {
		printf ("Can't erase unknown flash type - aborted\n");
		return 1;
	}

	prot = 0;
	for (sect=s_first; sect<=s_last; ++sect) {
		if (info->protect[sect]) {
			prot++;
		}
	}

	if (prot) {
		printf ("- Warning: %d protected sectors will not be erased!\n",
			prot);
	} else {
		printf ("\n");
	}

	/* Disable interrupts which might cause a timeout here */
	flag = disable_interrupts();

	/* Start erase on unprotected sectors */
	for (sect = s_first; sect<=s_last; sect++) {
		if (info->protect[sect] == 0) { /* not protected */
			addr2 = (FLASH_WORD_SIZE *)(info->start[sect]);
			DEBUGF("Erasing sector %p\n", addr2);

			if ((info->flash_id & FLASH_VENDMASK) == FLASH_MAN_SST) {
				addr[ADDR0] = (FLASH_WORD_SIZE)0x00AA00AA;
				addr[ADDR1] = (FLASH_WORD_SIZE)0x00550055;
				addr[ADDR0] = (FLASH_WORD_SIZE)0x00800080;
				addr[ADDR0] = (FLASH_WORD_SIZE)0x00AA00AA;
				addr[ADDR1] = (FLASH_WORD_SIZE)0x00550055;
				addr2[0] = (FLASH_WORD_SIZE)0x00500050;	 /* block erase */
				for (i=0; i<50; i++)
					udelay(1000);  /* wait 1 ms */
			} else {
				addr[ADDR0] = (FLASH_WORD_SIZE)0x00AA00AA;
				addr[ADDR1] = (FLASH_WORD_SIZE)0x00550055;
				addr[ADDR0] = (FLASH_WORD_SIZE)0x00800080;
				addr[ADDR0] = (FLASH_WORD_SIZE)0x00AA00AA;
				addr[ADDR1] = (FLASH_WORD_SIZE)0x00550055;
				addr2[0] = (FLASH_WORD_SIZE)0x00300030;	 /* sector erase */
			}
			/*
			 * Wait for each sector to complete, it's more
			 * reliable.  According to AMD Spec, you must
			 * issue all erase commands within a specified
			 * timeout.  This has been seen to fail, especially
			 * if printf()s are included (for debug)!!
			 */
			wait_for_DQ7(info, sect);
		}
	}

	/* re-enable interrupts if necessary */
	if (flag)
		enable_interrupts();

	/* wait at least 80us - let's wait 1 ms */
	udelay (1000);

	/* reset to read mode */
	addr = (FLASH_WORD_SIZE *)info->start[0];
	addr[0] = (FLASH_WORD_SIZE)0x00F000F0;	/* reset bank */

	printf (" done\n");
	return 0;
}

/*-----------------------------------------------------------------------
 * Copy memory to flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 */

int write_buff (flash_info_t *info, uchar *src, ulong addr, ulong cnt)
{
	ulong cp, wp, data;
	int i, l, rc;

	wp = (addr & ~3);	/* get lower word aligned address */

	/*
	 * handle unaligned start bytes
	 */
	if ((l = addr - wp) != 0) {
		data = 0;
		for (i=0, cp=wp; i<l; ++i, ++cp) {
			data = (data << 8) | (*(uchar *)cp);
		}
		for (; i<4 && cnt>0; ++i) {
			data = (data << 8) | *src++;
			--cnt;
			++cp;
		}
		for (; cnt==0 && i<4; ++i, ++cp) {
			data = (data << 8) | (*(uchar *)cp);
		}

		if ((rc = write_word(info, wp, data)) != 0) {
			return (rc);
		}
		wp += 4;
	}

	/*
	 * handle word aligned part
	 */
	while (cnt >= 4) {
		data = 0;
		for (i=0; i<4; ++i) {
			data = (data << 8) | *src++;
		}
		if ((rc = write_word(info, wp, data)) != 0) {
			return (rc);
		}
		wp  += 4;
		cnt -= 4;
	}

	if (cnt == 0) {
		return (0);
	}

	/*
	 * handle unaligned tail bytes
	 */
	data = 0;
	for (i=0, cp=wp; i<4 && cnt>0; ++i, ++cp) {
		data = (data << 8) | *src++;
		--cnt;
	}
	for (; i<4; ++i, ++cp) {
		data = (data << 8) | (*(uchar *)cp);
	}

	return (write_word(info, wp, data));
}

/*-----------------------------------------------------------------------
 * Write a word to Flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 */
static int write_word (flash_info_t * info, ulong dest, ulong data)
{
	volatile FLASH_WORD_SIZE *addr2 = (FLASH_WORD_SIZE *) (info->start[0]);
	volatile FLASH_WORD_SIZE *dest2 = (FLASH_WORD_SIZE *) dest;
	volatile FLASH_WORD_SIZE *data2 = (FLASH_WORD_SIZE *) & data;
	ulong start;
	int i;

	/* Check if Flash is (sufficiently) erased */
	if ((*((volatile FLASH_WORD_SIZE *) dest) &
	     (FLASH_WORD_SIZE) data) != (FLASH_WORD_SIZE) data) {
		return (2);
	}

	for (i = 0; i < 4 / sizeof (FLASH_WORD_SIZE); i++) {
		int flag;

		/* Disable interrupts which might cause a timeout here */
		flag = disable_interrupts ();

		addr2[ADDR0] = (FLASH_WORD_SIZE) 0x00AA00AA;
		addr2[ADDR1] = (FLASH_WORD_SIZE) 0x00550055;
		addr2[ADDR0] = (FLASH_WORD_SIZE) 0x00A000A0;

		dest2[i] = data2[i];

		/* re-enable interrupts if necessary */
		if (flag)
			enable_interrupts ();

		/* data polling for D7 */
		start = get_timer (0);
		while ((dest2[i] & (FLASH_WORD_SIZE) 0x00800080) !=
		       (data2[i] & (FLASH_WORD_SIZE) 0x00800080)) {

			if (get_timer (start) > CONFIG_SYS_FLASH_WRITE_TOUT) {
				return (1);
			}
		}
	}

	return (0);
}
