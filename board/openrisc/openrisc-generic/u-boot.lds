#include <config.h>
OUTPUT_ARCH(or32)
__DYNAMIC  =  0;

MEMORY
{
	vectors	: ORIGIN = 0, LENGTH = 0x2000
	ram	: ORIGIN = CONFIG_SYS_MONITOR_BASE,
		  LENGTH = CONFIG_SYS_MONITOR_LEN
}

SECTIONS
{
	.vectors :
	{
		*(.vectors)
	} > vectors

	__start = .;
	.text : AT (__start) {
		_stext = .;
		*(.text)
		_etext = .;
		*(.lit)
		*(.shdata)
		_endtext = .;
	}  > ram

	 __u_boot_cmd_start = .;
	 .u_boot_cmd : { *(.u_boot_cmd) } > ram
	 __u_boot_cmd_end = .;

	.rodata : {
		*(.rodata);
		*(.rodata.*)
	} > ram

	.shbss :
	{
		*(.shbss)
	} > ram

	.talias :
	{
	}  > ram

	.data : {
		sdata = .;
		_sdata = .;
		*(.data)
		edata = .;
		_edata = .;
	} > ram

	.bss :
	{
		_bss_start = .;
		*(.bss)
		*(COMMON)
		_bss_end = .;
	} > ram
	__end = .;

	/* No stack specification - done manually */

	.stab  0 (NOLOAD) :
	{
		[ .stab ]
	}

	.stabstr  0 (NOLOAD) :
	{
		[ .stabstr ]
	}
}
