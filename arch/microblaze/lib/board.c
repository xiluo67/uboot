/*
 * (C) Copyright 2007 Michal Simek
 * (C) Copyright 2004 Atmark Techno, Inc.
 *
 * Michal  SIMEK <monstr@monstr.eu>
 * Yasushi SHOJI <yashi@atmark-techno.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <version.h>
#include <watchdog.h>
#include <stdio_dev.h>
#include <serial.h>
#include <net.h>
#include <linux/compiler.h>
#include <asm/processor.h>
#include <asm/microblaze_intc.h>
#include <fdtdec.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependend #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */
typedef int (init_fnc_t) (void);

init_fnc_t *init_sequence[] = {
	env_init,
#ifdef CONFIG_OF_CONTROL
	fdtdec_check_fdt,
#endif
	serial_init,
	console_init_f,
	interrupts_init,
	timer_init,
	NULL,
};

unsigned long monitor_flash_len;

void board_init_f(ulong not_used)
{
	bd_t *bd;
	init_fnc_t **init_fnc_ptr;
	gd = (gd_t *) (CONFIG_SYS_SDRAM_BASE + CONFIG_SYS_GBL_DATA_OFFSET);
	bd = (bd_t *) (CONFIG_SYS_SDRAM_BASE + CONFIG_SYS_GBL_DATA_OFFSET \
						- GENERATED_BD_INFO_SIZE);
	__maybe_unused char *s;
#if defined(CONFIG_CMD_FLASH)
	ulong flash_size = 0;
#endif
	asm ("nop");	/* FIXME gd is not initialize - wait */
	memset ((void *)gd, 0, GENERATED_GBL_DATA_SIZE);
	memset ((void *)bd, 0, GENERATED_BD_INFO_SIZE);
	gd->bd = bd;
	gd->baudrate = CONFIG_BAUDRATE;
	bd->bi_baudrate = CONFIG_BAUDRATE;
	bd->bi_memstart = CONFIG_SYS_SDRAM_BASE;
	bd->bi_memsize = CONFIG_SYS_SDRAM_SIZE;
	gd->flags |= GD_FLG_RELOC;      /* tell others: relocation done */

	monitor_flash_len = __end - __text_start;

#ifdef CONFIG_OF_EMBED
	/* Get a pointer to the FDT */
	gd->fdt_blob = _binary_dt_dtb_start;
#elif defined CONFIG_OF_SEPARATE
	/* FDT is at end of image */
	gd->fdt_blob = (void *)__end;
#endif
	/* Allow the early environment to override the fdt address */
	gd->fdt_blob = (void *)getenv_ulong("fdtcontroladdr", 16,
						(uintptr_t)gd->fdt_blob);

	/*
	 * The Malloc area is immediately below the monitor copy in DRAM
	 * aka CONFIG_SYS_MONITOR_BASE - Note there is no need for reloc_off
	 * as our monitory code is run from SDRAM
	 */
	mem_malloc_init (CONFIG_SYS_MALLOC_BASE, CONFIG_SYS_MALLOC_LEN);

#ifdef CONFIG_SERIAL_MULTI
	serial_initialize();
#endif

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		WATCHDOG_RESET ();
		if ((*init_fnc_ptr) () != 0) {
			hang ();
		}
	}

#ifdef CONFIG_OF_CONTROL
	/* For now, put this check after the console is ready */
	if (fdtdec_prepare_fdt()) {
		panic("** CONFIG_OF_CONTROL defined but no FDT - please see "
			"doc/README.fdt-control");
	} else
		printf("DTB: 0x%x\n", (u32)gd->fdt_blob);
#endif

	puts ("SDRAM :\n");
	printf ("\t\tIcache:%s\n", icache_status() ? "ON" : "OFF");
	printf ("\t\tDcache:%s\n", dcache_status() ? "ON" : "OFF");
	printf ("\tU-Boot Start:0x%08x\n", CONFIG_SYS_TEXT_BASE);

#if defined(CONFIG_CMD_FLASH)
	puts ("Flash: ");
	bd->bi_flashstart = CONFIG_SYS_FLASH_BASE;
	flash_size = flash_init();
	if (bd->bi_flashstart && flash_size > 0) {
# ifdef CONFIG_SYS_FLASH_CHECKSUM
		print_size (flash_size, "");
		/*
		 * Compute and print flash CRC if flashchecksum is set to 'y'
		 *
		 * NOTE: Maybe we should add some WATCHDOG_RESET()? XXX
		 */
		s = getenv ("flashchecksum");
		if (s && (*s == 'y')) {
			printf ("  CRC: %08X",
				crc32(0, (const u8 *)bd->bi_flashstart,
							flash_size)
			);
		}
		putc ('\n');
# else	/* !CONFIG_SYS_FLASH_CHECKSUM */
		print_size (flash_size, "\n");
# endif /* CONFIG_SYS_FLASH_CHECKSUM */
		bd->bi_flashsize = flash_size;
		bd->bi_flashoffset = bd->bi_flashstart + flash_size;
	} else {
		puts ("Flash init FAILED");
		bd->bi_flashstart = 0;
		bd->bi_flashsize = 0;
		bd->bi_flashoffset = 0;
	}
#endif

	/* relocate environment function pointers etc. */
	env_relocate ();

	/* Initialize stdio devices */
	stdio_init ();

	/* Initialize the jump table for applications */
	jumptable_init();

	/* Initialize the console (after the relocation and devices init) */
	console_init_r();

	board_init();

	/* Initialize from environment */
	load_addr = getenv_ulong("loadaddr", 16, load_addr);

#if defined(CONFIG_CMD_NET)
	printf("Net:   ");
	eth_initialize(gd->bd);

	uchar enetaddr[6];
	eth_getenv_enetaddr("ethaddr", enetaddr);
	printf("MAC:   %pM\n", enetaddr);
#endif

	/* main_loop */
	for (;;) {
		WATCHDOG_RESET ();
		main_loop ();
	}
}

void hang (void)
{
	puts ("### ERROR ### Please RESET the board ###\n");
	for (;;) ;
}
