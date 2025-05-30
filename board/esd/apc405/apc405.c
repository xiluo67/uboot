/*
 * (C) Copyright 2005-2008
 * Matthias Fuchs, esd gmbh germany, matthias.fuchs@esd-electronics.com
 *
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
#include <asm/processor.h>
#include <asm/io.h>
#include <command.h>
#include <malloc.h>
#include <flash.h>
#include <mtd/cfi_flash.h>
#include <asm/4xx_pci.h>
#include <pci.h>

DECLARE_GLOBAL_DATA_PTR;

#undef FPGA_DEBUG

extern void lxt971_no_sleep(void);

/* fpga configuration data - gzip compressed and generated by bin2c */
const unsigned char fpgadata[] =
{
#include "fpgadata.c"
};

/*
 * include common fpga code (for esd boards)
 */
#include "../common/fpga.c"

#ifdef CONFIG_LCD_USED
/* logo bitmap data - gzip compressed and generated by bin2c */
unsigned char logo_bmp[] =
{
#include "logo_640_480_24bpp.c"
};

/*
 * include common lcd code (for esd boards)
 */
#include "../common/lcd.c"
#include "../common/s1d13505_640_480_16bpp.h"
#include "../common/s1d13806_640_480_16bpp.h"
#endif /* CONFIG_LCD_USED */

/*
 * include common auto-update code (for esd boards)
 */
#include "../common/auto_update.h"

au_image_t au_image[] = {
	{"preinst.img", 0, -1, AU_SCRIPT},
	{"u-boot.img", 0xfff80000, 0x00080000, AU_FIRMWARE | AU_PROTECT},
	{"pImage", 0xfe000000, 0x00100000, AU_NOR | AU_PROTECT},
	{"pImage.initrd", 0xfe100000, 0x00400000, AU_NOR | AU_PROTECT},
	{"work.img", 0xfe500000, 0x01400000, AU_NOR},
	{"data.img", 0xff900000, 0x00580000, AU_NOR},
	{"logo.img", 0xffe80000, 0x00100000, AU_NOR | AU_PROTECT},
	{"postinst.img", 0, 0, AU_SCRIPT},
};

int N_AU_IMAGES = (sizeof(au_image) / sizeof(au_image[0]));

int board_revision(void)
{
	unsigned long CPC0_CR0Reg;
	unsigned long value;

	/*
	 * Get version of APC405 board from GPIO's
	 */

	/* Setup GPIO pins (CS2/GPIO11, CS3/GPIO12 and CS4/GPIO13 as GPIO) */
	CPC0_CR0Reg = mfdcr(CPC0_CR0);
	mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x03800000);
	out_be32((void*)GPIO0_ODR, in_be32((void*)GPIO0_ODR) & ~0x001c0000);
	out_be32((void*)GPIO0_TCR, in_be32((void*)GPIO0_TCR) & ~0x001c0000);

	/* wait some time before reading input */
	udelay(1000);

	/* get config bits */
	value = in_be32((void*)GPIO0_IR) & 0x001c0000;
	/*
	 * Restore GPIO settings
	 */
	mtdcr(CPC0_CR0, CPC0_CR0Reg);

	switch (value) {
	case 0x001c0000:
		/* CS2==1 && CS3==1 && CS4==1 -> version <= 1.2 */
		return 2;
	case 0x000c0000:
		/* CS2==0 && CS3==1 && CS4==1 -> version 1.3 */
		return 3;
	case 0x00180000:
		/* CS2==1 && CS3==1 && CS4==0 -> version 1.6 */
		return 6;
	case 0x00140000:
		/* CS2==1 && CS3==0 && CS4==1 -> version 1.8 */
		return 8;
	default:
		/* should not be reached! */
		return 0;
	}
}

int board_early_init_f (void)
{
	/*
	 * First pull fpga-prg pin low, to disable fpga logic
	 */
	out_be32((void*)GPIO0_ODR, 0x00000000);        /* no open drain pins */
	out_be32((void*)GPIO0_TCR, CONFIG_SYS_FPGA_PRG);      /* setup for output   */
	out_be32((void*)GPIO0_OR, 0);                  /* pull prg low       */

	/*
	 * IRQ 0-15  405GP internally generated; active high; level sensitive
	 * IRQ 16    405GP internally generated; active low; level sensitive
	 * IRQ 17-24 RESERVED
	 * IRQ 25 (EXT IRQ 0) CAN0; active low; level sensitive
	 * IRQ 26 (EXT IRQ 1) SER0 ; active low; level sensitive
	 * IRQ 27 (EXT IRQ 2) SER1; active low; level sensitive
	 * IRQ 28 (EXT IRQ 3) FPGA 0; active low; level sensitive
	 * IRQ 29 (EXT IRQ 4) FPGA 1; active low; level sensitive
	 * IRQ 30 (EXT IRQ 5) PCI INTA; active low; level sensitive
	 * IRQ 31 (EXT IRQ 6) COMPACT FLASH; active high; level sensitive
	 */
	mtdcr(UIC0SR, 0xFFFFFFFF);       /* clear all ints */
	mtdcr(UIC0ER, 0x00000000);       /* disable all ints */
	mtdcr(UIC0CR, 0x00000000);       /* set all to be non-critical*/
	mtdcr(UIC0PR, 0xFFFFFF81);       /* set int polarities */
	mtdcr(UIC0TR, 0x10000000);       /* set int trigger levels */
	mtdcr(UIC0VCR, 0x00000001);      /* set vect base=0 */
	mtdcr(UIC0SR, 0xFFFFFFFF);       /* clear all ints */

	/*
	 * EBC Configuration Register: set ready timeout to 512 ebc-clks
	 */
	mtebc(EBC0_CFG, 0xa8400000); /* ebc always driven */

	/*
	 * New boards have a single 32MB flash connected to CS0
	 * instead of two 16MB flashes on CS0+1.
	 */
	if (board_revision() >= 8) {
		/* disable CS1 */
		mtebc(PB1AP, 0);
		mtebc(PB1CR, 0);

		/* resize CS0 to 32MB */
		mtebc(PB0AP, CONFIG_SYS_EBC_PB0AP_HWREV8);
		mtebc(PB0CR, CONFIG_SYS_EBC_PB0CR_HWREV8);
	}

	return 0;
}

int board_early_init_r(void)
{
	if (gd->board_type >= 8)
		cfi_flash_num_flash_banks = 1;

	return 0;
}

#define FUJI_BASE    0xf0100200
#define LCDBL_PWM    0xa0
#define LCDBL_PWMMIN 0xa4
#define LCDBL_PWMMAX 0xa8

int misc_init_r(void)
{
	u16 *fpga_mode = (u16 *)(CONFIG_SYS_FPGA_BASE_ADDR + CONFIG_SYS_FPGA_CTRL);
	u16 *fpga_ctrl2 =(u16 *)(CONFIG_SYS_FPGA_BASE_ADDR + CONFIG_SYS_FPGA_CTRL2);
	u8 *duart0_mcr = (u8 *)(DUART0_BA + 4);
	u8 *duart1_mcr = (u8 *)(DUART1_BA + 4);
	unsigned char *dst;
	ulong len = sizeof(fpgadata);
	int status;
	int index;
	int i;
	unsigned long CPC0_CR0Reg;
	char *str;
	uchar *logo_addr;
	ulong logo_size;
	ushort minb, maxb;
	int result;

	/*
	 * Setup GPIO pins (CS6+CS7 as GPIO)
	 */
	CPC0_CR0Reg = mfdcr(CPC0_CR0);
	mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x00300000);

	dst = malloc(CONFIG_SYS_FPGA_MAX_SIZE);
	if (gunzip(dst, CONFIG_SYS_FPGA_MAX_SIZE, (uchar *)fpgadata, &len) != 0) {
		printf("GUNZIP ERROR - must RESET board to recover\n");
		do_reset(NULL, 0, 0, NULL);
	}

	status = fpga_boot(dst, len);
	if (status != 0) {
		printf("\nFPGA: Booting failed ");
		switch (status) {
		case ERROR_FPGA_PRG_INIT_LOW:
			printf("(Timeout: "
			       "INIT not low after asserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_INIT_HIGH:
			printf("(Timeout: "
			       "INIT not high after deasserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_DONE:
			printf("(Timeout: "
			       "DONE not high after programming FPGA)\n ");
			break;
		}

		/* display infos on fpgaimage */
		index = 15;
		for (i = 0; i < 4; i++) {
			len = dst[index];
			printf("FPGA: %s\n", &(dst[index+1]));
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

	/*
	 * Write board revision in FPGA
	 */
	out_be16(fpga_ctrl2,
		 (in_be16(fpga_ctrl2) & 0xfff0) | (gd->board_type & 0x000f));

	/*
	 * Enable power on PS/2 interface (with reset)
	 */
	out_be16(fpga_mode, in_be16(fpga_mode) | CONFIG_SYS_FPGA_CTRL_PS2_RESET);
	for (i=0;i<100;i++)
		udelay(1000);
	udelay(1000);
	out_be16(fpga_mode, in_be16(fpga_mode) & ~CONFIG_SYS_FPGA_CTRL_PS2_RESET);

	/*
	 * Enable interrupts in exar duart mcr[3]
	 */
	out_8(duart0_mcr, 0x08);
	out_8(duart1_mcr, 0x08);

	/*
	 * Init lcd interface and display logo
	 */
	str = getenv("splashimage");
	if (str) {
		logo_addr = (uchar *)simple_strtoul(str, NULL, 16);
		logo_size = CONFIG_SYS_VIDEO_LOGO_MAX_SIZE;
	} else {
		logo_addr = logo_bmp;
		logo_size = sizeof(logo_bmp);
	}

	if (gd->board_type >= 6) {
		result = lcd_init((uchar *)CONFIG_SYS_LCD_BIG_REG,
				  (uchar *)CONFIG_SYS_LCD_BIG_MEM,
				  regs_13505_640_480_16bpp,
				  sizeof(regs_13505_640_480_16bpp) /
				  sizeof(regs_13505_640_480_16bpp[0]),
				  logo_addr, logo_size);
		if (result && str) {
			/* retry with internal image */
			logo_addr = logo_bmp;
			logo_size = sizeof(logo_bmp);
			lcd_init((uchar *)CONFIG_SYS_LCD_BIG_REG,
				 (uchar *)CONFIG_SYS_LCD_BIG_MEM,
				 regs_13505_640_480_16bpp,
				 sizeof(regs_13505_640_480_16bpp) /
				 sizeof(regs_13505_640_480_16bpp[0]),
				 logo_addr, logo_size);
		}
	} else {
		result = lcd_init((uchar *)CONFIG_SYS_LCD_BIG_REG,
				  (uchar *)CONFIG_SYS_LCD_BIG_MEM,
				  regs_13806_640_480_16bpp,
				  sizeof(regs_13806_640_480_16bpp) /
				  sizeof(regs_13806_640_480_16bpp[0]),
				  logo_addr, logo_size);
		if (result && str) {
			/* retry with internal image */
			logo_addr = logo_bmp;
			logo_size = sizeof(logo_bmp);
			lcd_init((uchar *)CONFIG_SYS_LCD_BIG_REG,
				 (uchar *)CONFIG_SYS_LCD_BIG_MEM,
				 regs_13806_640_480_16bpp,
				 sizeof(regs_13806_640_480_16bpp) /
				 sizeof(regs_13806_640_480_16bpp[0]),
				 logo_addr, logo_size);
		}
	}

	/*
	 * Reset microcontroller and setup backlight PWM controller
	 */
	out_be16(fpga_mode, in_be16(fpga_mode) | 0x0014);
	for (i=0;i<10;i++)
		udelay(1000);
	out_be16(fpga_mode, in_be16(fpga_mode) | 0x001c);

	minb = 0;
	maxb = 0xff;
	str = getenv("lcdbl");
	if (str) {
		minb = (ushort)simple_strtoul(str, &str, 16) & 0x00ff;
		if (str && (*str=',')) {
			str++;
			maxb = (ushort)simple_strtoul(str, NULL, 16) & 0x00ff;
		} else
			minb = 0;

		out_be16((u16 *)(FUJI_BASE + LCDBL_PWMMIN), minb);
		out_be16((u16 *)(FUJI_BASE + LCDBL_PWMMAX), maxb);

		printf("LCDBL: min=0x%02x, max=0x%02x\n", minb, maxb);
	}
	out_be16((u16 *)(FUJI_BASE + LCDBL_PWM), 0xff);

	/*
	 * fix environment for field updated units
	 */
	if (getenv("altbootcmd") == NULL) {
		setenv("usb_load", CONFIG_SYS_USB_LOAD_COMMAND);
		setenv("usbargs", CONFIG_SYS_USB_ARGS);
		setenv("bootcmd", CONFIG_BOOTCOMMAND);
		setenv("usb_self", CONFIG_SYS_USB_SELF_COMMAND);
		setenv("bootlimit", CONFIG_SYS_BOOTLIMIT);
		setenv("altbootcmd", CONFIG_SYS_ALT_BOOTCOMMAND);
		saveenv();
	}

	return (0);
}

/*
 * Check Board Identity:
 */
int checkboard (void)
{
	char str[64];
	int i = getenv_f("serial#", str, sizeof(str));

	puts ("Board: ");

	if (i == -1) {
		puts ("### No HW ID - assuming APC405");
	} else {
		puts(str);
	}

	gd->board_type = board_revision();
	printf(", Rev. 1.%ld\n", gd->board_type);

	return 0;
}

#ifdef CONFIG_IDE_RESET
void ide_set_reset(int on)
{
	u16 *fpga_mode = (u16 *)(CONFIG_SYS_FPGA_BASE_ADDR + CONFIG_SYS_FPGA_CTRL);

	/*
	 * Assert or deassert CompactFlash Reset Pin
	 */
	if (on) {
		out_be16(fpga_mode,
			 in_be16(fpga_mode) & ~CONFIG_SYS_FPGA_CTRL_CF_RESET);
	} else {
		out_be16(fpga_mode,
			 in_be16(fpga_mode) | CONFIG_SYS_FPGA_CTRL_CF_RESET);
	}
}
#endif /* CONFIG_IDE_RESET */

void reset_phy(void)
{
	/*
	 * Disable sleep mode in LXT971
	 */
	lxt971_no_sleep();
}

#if defined(CONFIG_USB_OHCI_NEW) && defined(CONFIG_SYS_USB_OHCI_BOARD_INIT)
int usb_board_init(void)
{
	return 0;
}

int usb_board_stop(void)
{
	unsigned short tmp;
	int i;

	/*
	 * reset PCI bus
	 * This is required to make some very old Linux OHCI driver
	 * work after U-Boot has used the OHCI controller.
	 */
	pci_read_config_word(PCIDEVID_405GP, PCIBRDGOPT2, &tmp);
	pci_write_config_word(PCIDEVID_405GP, PCIBRDGOPT2, (tmp | 0x1000));

	for (i = 0; i < 100; i++)
		udelay(1000);

	pci_write_config_word(PCIDEVID_405GP, PCIBRDGOPT2, tmp);
	return 0;
}

int usb_board_init_fail(void)
{
	usb_board_stop();
	return 0;
}
#endif /* defined(CONFIG_USB_OHCI) && defined(CONFIG_SYS_USB_OHCI_BOARD_INIT) */
