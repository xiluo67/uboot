/*
 * (C) Copyright 2011
 * Joe Hershberger, National Instruments, joe.hershberger@ni.com
 *
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
#include <command.h>
#include <u-boot/md5.h>

/*
 * Store the resulting sum to an address or variable
 */
static void store_result(const u8 *sum, const char *dest)
{
	unsigned int i;

	if (*dest == '*') {
		u8 *ptr;

		ptr = (u8 *)simple_strtoul(dest + 1, NULL, 16);
		for (i = 0; i < 16; i++)
			*ptr++ = sum[i];
	} else {
		char str_output[33];
		char *str_ptr = str_output;

		for (i = 0; i < 16; i++) {
			sprintf(str_ptr, "%02x", sum[i]);
			str_ptr += 2;
		}
		str_ptr = '\0';
		setenv(dest, str_output);
	}
}

#ifdef CONFIG_MD5SUM_VERIFY
static int parse_verify_sum(char *verify_str, u8 *vsum)
{
	if (*verify_str == '*') {
		u8 *ptr;

		ptr = (u8 *)simple_strtoul(verify_str + 1, NULL, 16);
		memcpy(vsum, ptr, 16);
	} else {
		unsigned int i;
		char *vsum_str;

		if (strlen(verify_str) == 32)
			vsum_str = verify_str;
		else {
			vsum_str = getenv(verify_str);
			if (vsum_str == NULL || strlen(vsum_str) != 32)
				return 1;
		}

		for (i = 0; i < 16; i++) {
			char *nullp = vsum_str + (i + 1) * 2;
			char end = *nullp;

			*nullp = '\0';
			*(u8 *)(vsum + i) =
				simple_strtoul(vsum_str + (i * 2), NULL, 16);
			*nullp = end;
		}
	}
	return 0;
}

int do_md5sum(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong addr, len;
	unsigned int i;
	u8 output[16];
	u8 vsum[16];
	int verify = 0;
	int ac;
	char * const *av;

	if (argc < 3)
		return CMD_RET_USAGE;

	av = argv + 1;
	ac = argc - 1;
	if (strcmp(*av, "-v") == 0) {
		verify = 1;
		av++;
		ac--;
		if (ac < 3)
			return CMD_RET_USAGE;
	}

	addr = simple_strtoul(*av++, NULL, 16);
	len = simple_strtoul(*av++, NULL, 16);

	md5_wd((unsigned char *) addr, len, output, CHUNKSZ_MD5);

	if (!verify) {
		printf("md5 for %08lx ... %08lx ==> ", addr, addr + len - 1);
		for (i = 0; i < 16; i++)
			printf("%02x", output[i]);
		printf("\n");

		if (ac > 2)
			store_result(output, *av);
	} else {
		char *verify_str = *av++;

		if (parse_verify_sum(verify_str, vsum)) {
			printf("ERROR: %s does not contain a valid md5 sum\n",
				verify_str);
			return 1;
		}
		if (memcmp(output, vsum, 16) != 0) {
			printf("md5 for %08lx ... %08lx ==> ", addr,
				addr + len - 1);
			for (i = 0; i < 16; i++)
				printf("%02x", output[i]);
			printf(" != ");
			for (i = 0; i < 16; i++)
				printf("%02x", vsum[i]);
			printf(" ** ERROR **\n");
			return 1;
		}
	}

	return 0;
}
#else
static int do_md5sum(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned long addr, len;
	unsigned int i;
	u8 output[16];

	if (argc < 3)
		return CMD_RET_USAGE;

	addr = simple_strtoul(argv[1], NULL, 16);
	len = simple_strtoul(argv[2], NULL, 16);

	md5_wd((unsigned char *) addr, len, output, CHUNKSZ_MD5);
	printf("md5 for %08lx ... %08lx ==> ", addr, addr + len - 1);
	for (i = 0; i < 16; i++)
		printf("%02x", output[i]);
	printf("\n");

	if (argc > 3)
		store_result(output, argv[3]);

	return 0;
}
#endif

#ifdef CONFIG_MD5SUM_VERIFY
U_BOOT_CMD(
	md5sum,	5,	1,	do_md5sum,
	"compute MD5 message digest",
	"address count [[*]sum]\n"
		"    - compute MD5 message digest [save to sum]\n"
	"md5sum -v address count [*]sum\n"
		"    - verify md5sum of memory area"
);
#else
U_BOOT_CMD(
	md5sum,	4,	1,	do_md5sum,
	"compute MD5 message digest",
	"address count [[*]sum]\n"
		"    - compute MD5 message digest [save to sum]"
);
#endif
