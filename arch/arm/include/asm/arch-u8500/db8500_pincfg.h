/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Code ported from Nomadik GPIO driver in ST-Ericsson Linux kernel code.
 * The purpose is that GPIO config found in kernel should work by simply
 * copy-paste it to U-boot. Ported 2010 to U-boot by:
 * Author: Joakim Axelsson <joakim.axelsson AT stericsson.com>
 *
 * License terms: GNU General Public License, version 2
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> for ST-Ericsson
 *
 *
 * Based on arch/arm/mach-pxa/include/mach/mfp.h:
 *   Copyright (C) 2007 Marvell International Ltd.
 *   eric miao <eric.miao@marvell.com>
 */

#ifndef __DB8500_PINCFG_H
#define __DB8500_PINCFG_H

#include "db8500_gpio.h"

/*
 * U-boot info:
 * SLPM (sleep mode) config will be ignored by U-boot but it is still
 * possible to configure it in order to keep cut-n-paste compability
 * with Linux kernel config.
 *
 * pin configurations are represented by 32-bit integers:
 *
 *	bit  0.. 8 - Pin Number (512 Pins Maximum)
 *	bit  9..10 - Alternate Function Selection
 *	bit 11..12 - Pull up/down state
 *	bit     13 - Sleep mode behaviour (not used in U-boot)
 *	bit     14 - Direction
 *	bit     15 - Value (if output)
 *	bit 16..18 - SLPM pull up/down state (not used in U-boot)
 *	bit 19..20 - SLPM direction (not used in U-boot)
 *	bit 21..22 - SLPM Value (if output) (not used in U-boot)
 *
 * to facilitate the definition, the following macros are provided
 *
 * PIN_CFG_DEFAULT - default config (0):
 *		     pull up/down = disabled
 *		     sleep mode = input/wakeup
 *		     direction = input
 *		     value = low
 *		     SLPM direction = same as normal
 *		     SLPM pull = same as normal
 *		     SLPM value = same as normal
 *
 * PIN_CFG	   - default config with alternate function
 * PIN_CFG_PULL	   - default config with alternate function and pull up/down
 */

/* Sleep mode */
enum db8500_gpio_slpm {
	DB8500_GPIO_SLPM_INPUT,
	DB8500_GPIO_SLPM_WAKEUP_ENABLE = DB8500_GPIO_SLPM_INPUT,
	DB8500_GPIO_SLPM_NOCHANGE,
	DB8500_GPIO_SLPM_WAKEUP_DISABLE = DB8500_GPIO_SLPM_NOCHANGE,
};

#define PIN_NUM_MASK		0x1ff
#define PIN_NUM(x)		((x) & PIN_NUM_MASK)

#define PIN_ALT_SHIFT		9
#define PIN_ALT_MASK		(0x3 << PIN_ALT_SHIFT)
#define PIN_ALT(x)		(((x) & PIN_ALT_MASK) >> PIN_ALT_SHIFT)
#define PIN_GPIO		(DB8500_GPIO_ALT_GPIO << PIN_ALT_SHIFT)
#define PIN_ALT_A		(DB8500_GPIO_ALT_A << PIN_ALT_SHIFT)
#define PIN_ALT_B		(DB8500_GPIO_ALT_B << PIN_ALT_SHIFT)
#define PIN_ALT_C		(DB8500_GPIO_ALT_C << PIN_ALT_SHIFT)

#define PIN_PULL_SHIFT		11
#define PIN_PULL_MASK		(0x3 << PIN_PULL_SHIFT)
#define PIN_PULL(x)		(((x) & PIN_PULL_MASK) >> PIN_PULL_SHIFT)
#define PIN_PULL_NONE		(DB8500_GPIO_PULL_NONE << PIN_PULL_SHIFT)
#define PIN_PULL_UP		(DB8500_GPIO_PULL_UP << PIN_PULL_SHIFT)
#define PIN_PULL_DOWN		(DB8500_GPIO_PULL_DOWN << PIN_PULL_SHIFT)

#define PIN_SLPM_SHIFT		13
#define PIN_SLPM_MASK		(0x1 << PIN_SLPM_SHIFT)
#define PIN_SLPM(x)		(((x) & PIN_SLPM_MASK) >> PIN_SLPM_SHIFT)
#define PIN_SLPM_MAKE_INPUT	(DB8500_GPIO_SLPM_INPUT << PIN_SLPM_SHIFT)
#define PIN_SLPM_NOCHANGE	(DB8500_GPIO_SLPM_NOCHANGE << PIN_SLPM_SHIFT)
/* These two replace the above in DB8500v2+ */
#define PIN_SLPM_WAKEUP_ENABLE \
	(DB8500_GPIO_SLPM_WAKEUP_ENABLE << PIN_SLPM_SHIFT)
#define PIN_SLPM_WAKEUP_DISABLE \
	(DB8500_GPIO_SLPM_WAKEUP_DISABLE << PIN_SLPM_SHIFT)

#define PIN_DIR_SHIFT		14
#define PIN_DIR_MASK		(0x1 << PIN_DIR_SHIFT)
#define PIN_DIR(x)		(((x) & PIN_DIR_MASK) >> PIN_DIR_SHIFT)
#define PIN_DIR_INPUT		(0 << PIN_DIR_SHIFT)
#define PIN_DIR_OUTPUT		(1 << PIN_DIR_SHIFT)

#define PIN_VAL_SHIFT		15
#define PIN_VAL_MASK		(0x1 << PIN_VAL_SHIFT)
#define PIN_VAL(x)		(((x) & PIN_VAL_MASK) >> PIN_VAL_SHIFT)
#define PIN_VAL_LOW		(0 << PIN_VAL_SHIFT)
#define PIN_VAL_HIGH		(1 << PIN_VAL_SHIFT)

#define PIN_SLPM_PULL_SHIFT	16
#define PIN_SLPM_PULL_MASK	(0x7 << PIN_SLPM_PULL_SHIFT)
#define PIN_SLPM_PULL(x)	\
	(((x) & PIN_SLPM_PULL_MASK) >> PIN_SLPM_PULL_SHIFT)
#define PIN_SLPM_PULL_NONE	\
	((1 + DB8500_GPIO_PULL_NONE) << PIN_SLPM_PULL_SHIFT)
#define PIN_SLPM_PULL_UP	\
	((1 + DB8500_GPIO_PULL_UP) << PIN_SLPM_PULL_SHIFT)
#define PIN_SLPM_PULL_DOWN	\
	((1 + DB8500_GPIO_PULL_DOWN) << PIN_SLPM_PULL_SHIFT)

#define PIN_SLPM_DIR_SHIFT	19
#define PIN_SLPM_DIR_MASK	(0x3 << PIN_SLPM_DIR_SHIFT)
#define PIN_SLPM_DIR(x)		\
	(((x) & PIN_SLPM_DIR_MASK) >> PIN_SLPM_DIR_SHIFT)
#define PIN_SLPM_DIR_INPUT	((1 + 0) << PIN_SLPM_DIR_SHIFT)
#define PIN_SLPM_DIR_OUTPUT	((1 + 1) << PIN_SLPM_DIR_SHIFT)

#define PIN_SLPM_VAL_SHIFT	21
#define PIN_SLPM_VAL_MASK	(0x3 << PIN_SLPM_VAL_SHIFT)
#define PIN_SLPM_VAL(x)		\
	(((x) & PIN_SLPM_VAL_MASK) >> PIN_SLPM_VAL_SHIFT)
#define PIN_SLPM_VAL_LOW	((1 + 0) << PIN_SLPM_VAL_SHIFT)
#define PIN_SLPM_VAL_HIGH	((1 + 1) << PIN_SLPM_VAL_SHIFT)

/* Shortcuts.  Use these instead of separate DIR, PULL, and VAL.  */
#define PIN_INPUT_PULLDOWN	(PIN_DIR_INPUT | PIN_PULL_DOWN)
#define PIN_INPUT_PULLUP	(PIN_DIR_INPUT | PIN_PULL_UP)
#define PIN_INPUT_NOPULL	(PIN_DIR_INPUT | PIN_PULL_NONE)
#define PIN_OUTPUT_LOW		(PIN_DIR_OUTPUT | PIN_VAL_LOW)
#define PIN_OUTPUT_HIGH		(PIN_DIR_OUTPUT | PIN_VAL_HIGH)

#define PIN_SLPM_INPUT_PULLDOWN	(PIN_SLPM_DIR_INPUT | PIN_SLPM_PULL_DOWN)
#define PIN_SLPM_INPUT_PULLUP	(PIN_SLPM_DIR_INPUT | PIN_SLPM_PULL_UP)
#define PIN_SLPM_INPUT_NOPULL	(PIN_SLPM_DIR_INPUT | PIN_SLPM_PULL_NONE)
#define PIN_SLPM_OUTPUT_LOW	(PIN_SLPM_DIR_OUTPUT | PIN_SLPM_VAL_LOW)
#define PIN_SLPM_OUTPUT_HIGH	(PIN_SLPM_DIR_OUTPUT | PIN_SLPM_VAL_HIGH)

#define PIN_CFG_DEFAULT		(0)

#define PIN_CFG(num, alt)		\
	(PIN_CFG_DEFAULT |\
	 (PIN_NUM(num) | PIN_##alt))

#define PIN_CFG_INPUT(num, alt, pull)		\
	(PIN_CFG_DEFAULT |\
	 (PIN_NUM(num) | PIN_##alt | PIN_INPUT_##pull))

#define PIN_CFG_OUTPUT(num, alt, val)		\
	(PIN_CFG_DEFAULT |\
	 (PIN_NUM(num) | PIN_##alt | PIN_OUTPUT_##val))

#define PIN_CFG_PULL(num, alt, pull)	\
	((PIN_CFG_DEFAULT & ~PIN_PULL_MASK) |\
	 (PIN_NUM(num) | PIN_##alt | PIN_PULL_##pull))

/**
 * db8500_gpio_config_pins - configure several pins at once
 * @cfgs: array of pin configurations
 * @num: number of elments in the array
 *
 * Configures several GPIO pins.
 */
void db8500_gpio_config_pins(unsigned long *cfgs, size_t num);

#endif
