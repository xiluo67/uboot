/*
 * Copied from Linux:
 * commit 37487a56523d402e25650da16c337acf4cecd13d
 * Author: Christoph Lameter <clameter@sgi.com>
 */
#ifndef __LINUX_KBUILD_H
#define __LINUX_KBUILD_H

#define DEFINE(sym, val) \
	asm volatile("\n->" #sym " %0 " #val : : "i" (val))

#define BLANK() asm volatile("\n->" : : )

#define OFFSET(sym, str, mem) \
	DEFINE(sym, offsetof(struct str, mem))

#define COMMENT(x) \
	asm volatile("\n->#" x)

#endif
