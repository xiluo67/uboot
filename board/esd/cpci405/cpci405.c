/*
 * (C) Copyright 2001-2003
 * Stefan Roese, esd gmbh germany, stefan.roese@esd-electronics.com
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
#include <libfdt.h>
#include <fdt_support.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <command.h>
#include <malloc.h>
#include <net.h>
#include <pci.h>

DECLARE_GLOBAL_DATA_PTR;

extern void __ft_board_setup(void *blob, bd_t *bd);

#undef FPGA_DEBUG

/* fpga configuration data - generated by bin2cc */
const unsigned char fpgadata[] =
{
#if defined(CONFIG_CPCI405_VER2)
# if defined(CONFIG_CPCI405AB)
#  include "fpgadata_cpci405ab.c"
# else
#  include "fpgadata_cpci4052.c"
# endif
#else
# include "fpgadata_cpci405.c"
#endif
};

/*
 * include common fpga code (for esd boards)
 */
#include "../common/fpga.c"
#include "../common/auto_update.h"

#if defined(CONFIG_CPCI405AB)
au_image_t au_image[] = {
	{"cpci405ab/preinst.img", 0, -1, AU_SCRIPT},
	{"cpci405ab/pImage", 0xffc00000, 0x000c0000, AU_NOR},
	{"cpci405ab/pImage.initrd", 0xffcc0000, 0x00300000, AU_NOR},
	{"cpci405ab/u-boot.img", 0xfffc0000, 0x00040000, AU_FIRMWARE},
	{"cpci405ab/postinst.img", 0, 0, AU_SCRIPT},
};
#else
#if defined(CONFIG_CPCI405_VER2)
au_image_t au_image[] = {
	{"cpci4052/preinst.img", 0, -1, AU_SCRIPT},
	{"cpci4052/pImage", 0xffc00000, 0x000c0000, AU_NOR},
	{"cpci4052/pImage.initrd", 0xffcc0000, 0x00300000, AU_NOR},
	{"cpci4052/u-boot.img", 0xfffc0000, 0x00040000, AU_FIRMWARE},
	{"cpci4052/postinst.img", 0, 0, AU_SCRIPT},
};
#else
au_image_t au_image[] = {
	{"cpci405/preinst.img", 0, -1, AU_SCRIPT},
	{"cpci405/pImage", 0xffc00000, 0x000c0000, AU_NOR},
	{"cpci405/pImage.initrd", 0xffcc0000, 0x00310000, AU_NOR},
	{"cpci405/u-boot.img", 0xfffd0000, 0x00030000, AU_FIRMWARE},
	{"cpci405/postinst.img", 0, 0, AU_SCRIPT},
};
#endif
#endif

int N_AU_IMAGES = (sizeof(au_image) / sizeof(au_image[0]));

/* Prototypes */
int cpci405_version(void);
void lxt971_no_sleep(void);

int board_early_init_f(void)
{
#ifndef CONFIG_CPCI405_VER2
	int index, len, i;
	int status;
#endif

#ifdef FPGA_DEBUG
	/* set up serial port with default baudrate */
	(void)get_clocks();
	gd->baudrate = CONFIG_BAUDRATE;
	serial_init();
	console_init_f();
#endif

	/*
	 * First pull fpga-prg pin low,
	 * to disable fpga logic (on version 2 board)
	 */
	out_be32((void *)GPIO0_ODR, 0x00000000);	     /* no open drain pins	*/
	out_be32((void *)GPIO0_TCR, CONFIG_SYS_FPGA_PRG); /* setup for output	*/
	out_be32((void *)GPIO0_OR, CONFIG_SYS_FPGA_PRG); /* set output pins to high */
	out_be32((void *)GPIO0_OR, 0);		     /* pull prg low		*/

	/*
	 * Boot onboard FPGA
	 */
#ifndef CONFIG_CPCI405_VER2
	if (cpci405_version() == 1) {
		status = fpga_boot((unsigned char *)fpgadata, sizeof(fpgadata));
		if (status != 0) {
			/* booting FPGA failed */
#ifndef FPGA_DEBUG
			/* set up serial port with default baudrate */
			(void)get_clocks();
			gd->baudrate = CONFIG_BAUDRATE;
			serial_init();
			console_init_f();
#endif
			printf("\nFPGA: Booting failed ");
			switch (status) {
			case ERROR_FPGA_PRG_INIT_LOW:
				printf("(Timeout: INIT not low after "
				       "asserting PROGRAM*)\n ");
				break;
			case ERROR_FPGA_PRG_INIT_HIGH:
				printf("(Timeout: INIT not high after "
				       "deasserting PROGRAM*)\n ");
				break;
			case ERROR_FPGA_PRG_DONE:
				printf("(Timeout: DONE not high after "
				       "programming FPGA)\n ");
				break;
			}

			/* display infos on fpgaimage */
			index = 15;
			for (i = 0; i < 4; i++) {
				len = fpgadata[index];
				printf("FPGA: %s\n", &(fpgadata[index + 1]));
				index += len + 3;
			}
			putc('\n');
			/* delayed reboot */
			for (i = 20; i > 0; i--) {
				printf("Rebooting in %2d seconds \r",i);
				for (index = 0; index < 1000; index++)
					udelay(1000);
			}
			putc('\n');
			do_reset(NULL, 0, 0, NULL);
		}
	}
#endif /* !CONFIG_CPCI405_VER2 */

	/*
	 * IRQ 0-15  405GP internally generated; active high; level sensitive
	 * IRQ 16    405GP internally generated; active low; level sensitive
	 * IRQ 17-24 RESERVED
	 * IRQ 25 (EXT IRQ 0) CAN0; active low; level sensitive
	 * IRQ 26 (EXT IRQ 1) CAN1 (+FPGA on CPCI4052); active low; level sens.
	 * IRQ 27 (EXT IRQ 2) PCI SLOT 0; active low; level sensitive
	 * IRQ 28 (EXT IRQ 3) PCI SLOT 1; active low; level sensitive
	 * IRQ 29 (EXT IRQ 4) PCI SLOT 2; active low; level sensitive
	 * IRQ 30 (EXT IRQ 5) PCI SLOT 3; active low; level sensitive
	 * IRQ 31 (EXT IRQ 6) COMPACT FLASH; active high; level sensitive
	 */
	mtdcr(UIC0SR, 0xFFFFFFFF);	/* clear all ints */
	mtdcr(UIC0ER, 0x00000000);	/* disable all ints */
	mtdcr(UIC0CR, 0x00000000);	/* set all to be non-critical*/
#if defined(CONFIG_CPCI405_6U)
	if (cpci405_version() == 3) {
		mtdcr(UIC0PR, 0xFFFFFF99);	/* set int polarities */
	} else {
		mtdcr(UIC0PR, 0xFFFFFF81);	/* set int polarities */
	}
#else
	mtdcr(UIC0PR, 0xFFFFFF81);	/* set int polarities */
#endif
	mtdcr(UIC0TR, 0x10000000);	/* set int trigger levels */
	mtdcr(UIC0VCR, 0x00000001);	/* set vect base=0,
					 * INT0 highest priority */
	mtdcr(UIC0SR, 0xFFFFFFFF);	/* clear all ints */

	return 0;
}

int ctermm2(void)
{
#if defined(CONFIG_CPCI405_VER2)
	return 0;			/* no, board is cpci405 */
#else
	if ((in_8((void*)0xf0000400) == 0x00) &&
	    (in_8((void*)0xf0000401) == 0x01))
		return 0;		/* no, board is cpci405 */
	else
		return -1;		/* yes, board is cterm-m2 */
#endif
}

int cpci405_host(void)
{
	if (mfdcr(CPC0_PSR) & PSR_PCI_ARBIT_EN)
		return -1;		/* yes, board is cpci405 host */
	else
		return 0;		/* no, board is cpci405 adapter */
}

int cpci405_version(void)
{
	unsigned long CPC0_CR0Reg;
	unsigned long value;

	/*
	 * Setup GPIO pins (CS2/GPIO11 and CS3/GPIO12 as GPIO)
	 */
	CPC0_CR0Reg = mfdcr(CPC0_CR0);
	mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x03000000);
	out_be32((void*)GPIO0_ODR, in_be32((void*)GPIO0_ODR) & ~0x00180000);
	out_be32((void*)GPIO0_TCR, in_be32((void*)GPIO0_TCR) & ~0x00180000);
	udelay(1000); /* wait some time before reading input */
	value = in_be32((void*)GPIO0_IR) & 0x00180000; /* get config bits */

	/*
	 * Restore GPIO settings
	 */
	mtdcr(CPC0_CR0, CPC0_CR0Reg);

	switch (value) {
	case 0x00180000:
		/* CS2==1 && CS3==1 -> version 1 */
		return 1;
	case 0x00080000:
		/* CS2==0 && CS3==1 -> version 2 */
		return 2;
	case 0x00100000:
		/* CS2==1 && CS3==0 -> version 3 or 6U board */
		return 3;
	case 0x00000000:
		/* CS2==0 && CS3==0 -> version 4 */
		return 4;
	default:
		/* should not be reached! */
		return 2;
	}
}

int misc_init_r (void)
{
	unsigned long CPC0_CR0Reg;

	/* adjust flash start and offset */
	gd->bd->bi_flashstart = 0 - gd->bd->bi_flashsize;
	gd->bd->bi_flashoffset = 0;

#if defined(CONFIG_CPCI405_VER2)
	{
	unsigned char *dst;
	ulong len = sizeof(fpgadata);
	int status;
	int index;
	int i;

	/*
	 * On CPCI-405 version 2 the environment is saved in eeprom!
	 * FPGA can be gzip compressed (malloc) and booted this late.
	 */
	if (cpci405_version() >= 2) {
		/*
		 * Setup GPIO pins (CS6+CS7 as GPIO)
		 */
		CPC0_CR0Reg = mfdcr(CPC0_CR0);
		mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x00300000);

		dst = malloc(CONFIG_SYS_FPGA_MAX_SIZE);
		if (gunzip(dst, CONFIG_SYS_FPGA_MAX_SIZE,
			   (uchar *)fpgadata, &len) != 0) {
			printf("GUNZIP ERROR - must RESET board to recover\n");
			do_reset(NULL, 0, 0, NULL);
		}

		status = fpga_boot(dst, len);
		if (status != 0) {
			printf("\nFPGA: Booting failed ");
			switch (status) {
			case ERROR_FPGA_PRG_INIT_LOW:
				printf("(Timeout: INIT not low after "
				       "asserting PROGRAM*)\n ");
				break;
			case ERROR_FPGA_PRG_INIT_HIGH:
				printf("(Timeout: INIT not high after "
				       "deasserting PROGRAM*)\n ");
				break;
			case ERROR_FPGA_PRG_DONE:
				printf("(Timeout: DONE not high after "
				       "programming FPGA)\n ");
				break;
			}

			/* display infos on fpgaimage */
			index = 15;
			for (i = 0; i < 4; i++) {
				len = dst[index];
				printf("FPGA: %s\n", &(dst[index + 1]));
				index += len + 3;
			}
			putc('\n');
			/* delayed reboot */
			for (i = 20; i > 0; i--) {
				printf("Rebooting in %2d seconds \r", i);
				for (index = 0; index < 1000; index++)
					udelay(1000);
			}
			putc('\n');
			do_reset(NULL, 0, 0, NULL);
		}

		/* restore gpio/cs settings */
		mtdcr(CPC0_CR0, CPC0_CR0Reg);

		puts("FPGA:  ");

		/* display infos on fpgaimage */
		index = 15;
		for (i = 0; i < 4; i++) {
			len = dst[index];
			printf("%s ", &(dst[index + 1]));
			index += len + 3;
		}
		putc('\n');

		free(dst);

		/*
		 * Reset FPGA via FPGA_DATA pin
		 */
		SET_FPGA(FPGA_PRG | FPGA_CLK);
		udelay(1000); /* wait 1ms */
		SET_FPGA(FPGA_PRG | FPGA_CLK | FPGA_DATA);
		udelay(1000); /* wait 1ms */

#if defined(CONFIG_CPCI405_6U)
#error HIER GETH ES WEITER MIT IO ACCESSORS
		if (cpci405_version() == 3) {
			/*
			 * Enable outputs in fpga on version 3 board
			 */
			out_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR,
				 in_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR) |
				 CONFIG_SYS_FPGA_MODE_ENABLE_OUTPUT);

			/*
			 * Set outputs to 0
			 */
			out_8((void*)CONFIG_SYS_LED_ADDR, 0x00);

			/*
			 * Reset external DUART
			 */
			out_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR,
				 in_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR) |
				 CONFIG_SYS_FPGA_MODE_DUART_RESET);
			udelay(100);
			out_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR,
				 in_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR) &
				 ~CONFIG_SYS_FPGA_MODE_DUART_RESET);
		}
#endif
	}
	else {
		puts("\n*** U-Boot Version does not match Board Version!\n");
		puts("*** CPCI-405 Version 1.x detected!\n");
		puts("*** Please use correct U-Boot version "
		     "(CPCI405 instead of CPCI4052)!\n\n");
	}
	}
#else /* CONFIG_CPCI405_VER2 */
	if (cpci405_version() >= 2) {
		puts("\n*** U-Boot Version does not match Board Version!\n");
		puts("*** CPCI-405 Board Version 2.x detected!\n");
		puts("*** Please use correct U-Boot version "
		     "(CPCI4052 instead of CPCI405)!\n\n");
	}
#endif /* CONFIG_CPCI405_VER2 */

	/*
	 * Select cts (and not dsr) on uart1
	 */
	CPC0_CR0Reg = mfdcr(CPC0_CR0);
	mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x00001000);

	return 0;
}

/*
 * Check Board Identity:
 */

int checkboard(void)
{
#ifndef CONFIG_CPCI405_VER2
	int index;
	int len;
#endif
	char str[64];
	int i = getenv_f("serial#", str, sizeof(str));
	unsigned short ver;

	puts("Board: ");

	if (i == -1)
		puts("### No HW ID - assuming CPCI405");
	else
		puts(str);

	ver = cpci405_version();
	printf(" (Ver %d.x, ", ver);

	if (ctermm2()) {
		char str[4];

		/*
		 * Read board-id and save in env-variable
		 */
		sprintf(str, "%d", *(unsigned char *)0xf0000400);
		setenv("boardid", str);
		printf("CTERM-M2 - Id=%s)", str);
	} else {
		if (cpci405_host())
			puts("PCI Host Version)");
		else
			puts("PCI Adapter Version)");
	}

#ifndef CONFIG_CPCI405_VER2
	puts("\nFPGA:	");

	/* display infos on fpgaimage */
	index = 15;
	for (i = 0; i < 4; i++) {
		len = fpgadata[index];
		printf("%s ", &(fpgadata[index + 1]));
		index += len + 3;
	}
#endif

	putc('\n');
	return 0;
}

void reset_phy(void)
{
#if defined(CONFIG_LXT971_NO_SLEEP)

	/*
	 * Disable sleep mode in LXT971
	 */
	lxt971_no_sleep();
#endif
}

#if defined(CONFIG_CPCI405_VER2) && defined (CONFIG_IDE_RESET)
void ide_set_reset(int on)
{
	/*
	 * Assert or deassert CompactFlash Reset Pin
	 */
	if (on) {	/* assert RESET */
		out_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR,
			 in_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR) &
			 ~CONFIG_SYS_FPGA_MODE_CF_RESET);
	} else {	/* release RESET */
		out_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR,
			 in_be16((void*)CONFIG_SYS_FPGA_BASE_ADDR) |
			 CONFIG_SYS_FPGA_MODE_CF_RESET);
	}
}

#endif /* CONFIG_IDE_RESET && CONFIG_CPCI405_VER2 */

#if defined(CONFIG_PCI)
void cpci405_pci_fixup_irq(struct pci_controller *hose, pci_dev_t dev)
{
	unsigned char int_line = 0xff;

	/*
	 * Write pci interrupt line register (cpci405 specific)
	 */
	switch (PCI_DEV(dev) & 0x03) {
	case 0:
		int_line = 27 + 2;
		break;
	case 1:
		int_line = 27 + 3;
		break;
	case 2:
		int_line = 27 + 0;
		break;
	case 3:
		int_line = 27 + 1;
		break;
	}

	pci_hose_write_config_byte(hose, dev, PCI_INTERRUPT_LINE, int_line);
}

int pci_pre_init(struct pci_controller *hose)
{
	hose->fixup_irq = cpci405_pci_fixup_irq;
	return 1;
}
#endif /* defined(CONFIG_PCI) */

#if defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP)
void ft_board_setup(void *blob, bd_t *bd)
{
	int rc;

	__ft_board_setup(blob, bd);

	/*
	 * Disable PCI in adapter mode.
	 */
	if (!cpci405_host()) {
		rc = fdt_find_and_setprop(blob, "/plb/pci@ec000000", "status",
					  "disabled", sizeof("disabled"), 1);
		if (rc) {
			printf("Unable to update property status in PCI node, "
			       "err=%s\n",
			       fdt_strerror(rc));
		}
	}
}
#endif /* defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP) */

#if defined(CONFIG_CPCI405AB)
#define ONE_WIRE_CLEAR	 out_be16((void*)(CONFIG_SYS_FPGA_BASE_ADDR +	\
					  CONFIG_SYS_FPGA_MODE),	\
				  in_be16((void*)(CONFIG_SYS_FPGA_BASE_ADDR + \
						  CONFIG_SYS_FPGA_MODE)) | \
					  CONFIG_SYS_FPGA_MODE_1WIRE_DIR)

#define ONE_WIRE_SET	 out_be16((void*)(CONFIG_SYS_FPGA_BASE_ADDR +	\
					  CONFIG_SYS_FPGA_MODE),	\
				  in_be16((void*)(CONFIG_SYS_FPGA_BASE_ADDR + \
						  CONFIG_SYS_FPGA_MODE)) & \
					  ~CONFIG_SYS_FPGA_MODE_1WIRE_DIR)

#define ONE_WIRE_GET	 (in_be16((void*)(CONFIG_SYS_FPGA_BASE_ADDR + \
					  CONFIG_SYS_FPGA_STATUS)) &  \
			  CONFIG_SYS_FPGA_MODE_1WIRE)

/*
 * Generate a 1-wire reset, return 1 if no presence detect was found,
 * return 0 otherwise.
 * (NOTE: Does not handle alarm presence from DS2404/DS1994)
 */
int OWTouchReset(void)
{
	int result;

	ONE_WIRE_CLEAR;
	udelay(480);
	ONE_WIRE_SET;
	udelay(70);

	result = ONE_WIRE_GET;

	udelay(410);
	return result;
}

/*
 * Send 1 a 1-wire write bit.
 * Provide 10us recovery time.
 */
void OWWriteBit(int bit)
{
	if (bit) {
		/*
		 * write '1' bit
		 */
		ONE_WIRE_CLEAR;
		udelay(6);
		ONE_WIRE_SET;
		udelay(64);
	} else {
		/*
		 * write '0' bit
		 */
		ONE_WIRE_CLEAR;
		udelay(60);
		ONE_WIRE_SET;
		udelay(10);
	}
}

/*
 * Read a bit from the 1-wire bus and return it.
 * Provide 10us recovery time.
 */
int OWReadBit(void)
{
	int result;

	ONE_WIRE_CLEAR;
	udelay(6);
	ONE_WIRE_SET;
	udelay(9);

	result = ONE_WIRE_GET;

	udelay(55);
	return result;
}

void OWWriteByte(int data)
{
	int loop;

	for (loop = 0; loop < 8; loop++) {
		OWWriteBit(data & 0x01);
		data >>= 1;
	}
}

int OWReadByte(void)
{
	int loop, result = 0;

	for (loop = 0; loop < 8; loop++) {
		result >>= 1;
		if (OWReadBit())
			result |= 0x80;
	}

	return result;
}

int do_onewire(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned short val;
	int result;
	int i;
	unsigned char ow_id[6];
	char str[32];

	/*
	 * Clear 1-wire bit (open drain with pull-up)
	 */
	val = in_be16((void*)(CONFIG_SYS_FPGA_BASE_ADDR +
			      CONFIG_SYS_FPGA_MODE));
	val &= ~CONFIG_SYS_FPGA_MODE_1WIRE; /* clear 1-wire bit */
	out_be16((void*)(CONFIG_SYS_FPGA_BASE_ADDR +
			 CONFIG_SYS_FPGA_MODE), val);

	result = OWTouchReset();
	if (result != 0)
		puts("No 1-wire device detected!\n");

	OWWriteByte(0x33); /* send read rom command */
	OWReadByte(); /* skip family code ( == 0x01) */
	for (i = 0; i < 6; i++)
		ow_id[i] = OWReadByte();
	OWReadByte(); /* read crc */

	sprintf(str, "%02X%02X%02X%02X%02X%02X",
		ow_id[0], ow_id[1], ow_id[2], ow_id[3], ow_id[4], ow_id[5]);
	printf("Setting environment variable 'ow_id' to %s\n", str);
	setenv("ow_id", str);

	return 0;
}
U_BOOT_CMD(
	onewire,	1,	1,	do_onewire,
	"Read 1-write ID",
	""
);

#define CONFIG_SYS_I2C_EEPROM_ADDR_2 0x51 /* EEPROM CAT24WC32 */
#define CONFIG_ENV_SIZE_2 0x800 /* 2048 bytes may be used for env vars */

/*
 * Write backplane ip-address...
 */
int do_get_bpip(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *buf;
	ulong crc;
	char str[32];
	char *ptr;
	IPaddr_t ipaddr;

	buf = malloc(CONFIG_ENV_SIZE_2);
	if (eeprom_read(CONFIG_SYS_I2C_EEPROM_ADDR_2, 0,
			(uchar *)buf, CONFIG_ENV_SIZE_2))
		puts("\nError reading backplane EEPROM!\n");
	else {
		crc = crc32(0, (uchar *)(buf+4), CONFIG_ENV_SIZE_2 - 4);
		if (crc != *(ulong *)buf) {
			printf("ERROR: crc mismatch %08lx %08lx\n",
			       crc, *(ulong *)buf);
			return -1;
		}

		/*
		 * Find bp_ip
		 */
		ptr = strstr(buf+4, "bp_ip=");
		if (ptr == NULL) {
			printf("ERROR: bp_ip not found!\n");
			return -1;
		}
		ptr += 6;
		ipaddr = string_to_ip(ptr);

		/*
		 * Update whole ip-addr
		 */
		sprintf(str, "%pI4", &ipaddr);
		setenv("ipaddr", str);
		printf("Updated ip_addr from bp_eeprom to %s!\n", str);
	}

	free(buf);

	return 0;
}
U_BOOT_CMD(
	getbpip,	1,	1,	do_get_bpip,
	"Update IP-Address with Backplane IP-Address",
	""
);

/*
 * Set and print backplane ip...
 */
int do_set_bpip(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *buf;
	char str[32];
	ulong crc;

	if (argc < 2) {
		puts("ERROR!\n");
		return -1;
	}

	printf("Setting bp_ip to %s\n", argv[1]);
	buf = malloc(CONFIG_ENV_SIZE_2);
	memset(buf, 0, CONFIG_ENV_SIZE_2);
	sprintf(str, "bp_ip=%s", argv[1]);
	strcpy(buf+4, str);
	crc = crc32(0, (uchar *)(buf+4), CONFIG_ENV_SIZE_2 - 4);
	*(ulong *)buf = crc;

	if (eeprom_write(CONFIG_SYS_I2C_EEPROM_ADDR_2,
			 0, (uchar *)buf, CONFIG_ENV_SIZE_2))
		puts("\nError writing backplane EEPROM!\n");

	free(buf);

	return 0;
}
U_BOOT_CMD(
	setbpip,	2,	1,	do_set_bpip,
	"Write Backplane IP-Address",
	""
);

#endif /* CONFIG_CPCI405AB */
