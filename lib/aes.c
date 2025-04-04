/*
 * Copyright (c) 2011 The Chromium OS Authors.
 * (C) Copyright 2011 NVIDIA Corporation www.nvidia.com
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

/*
 * advanced encryption standard
 * author: karl malbrain, malbrain@yahoo.com
 *
 * This work, including the source code, documentation
 * and related data, is placed into the public domain.
 *
 * The orginal author is Karl Malbrain.
 *
 * THIS SOFTWARE IS PROVIDED AS-IS WITHOUT WARRANTY
 * OF ANY KIND, NOT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY. THE AUTHOR OF THIS SOFTWARE,
 * ASSUMES _NO_ RESPONSIBILITY FOR ANY CONSEQUENCE
 * RESULTING FROM THE USE, MODIFICATION, OR
 * REDISTRIBUTION OF THIS SOFTWARE.
*/

#include <common.h>
#include "aes.h"

/* forward s-box */
static const u8 sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
	0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
	0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
	0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
	0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
	0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
	0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
	0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
	0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
	0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
	0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
	0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
	0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
	0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
	0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
	0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

/* inverse s-box */
static const u8 inv_sbox[256] = {
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
	0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
	0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
	0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
	0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
	0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
	0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
	0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
	0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
	0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
	0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
	0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
	0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
	0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
	0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
	0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
	0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

/* combined Xtimes2[Sbox[]] */
static const u8 x2_sbox[256] = {
	0xc6, 0xf8, 0xee, 0xf6, 0xff, 0xd6, 0xde, 0x91,
	0x60, 0x02, 0xce, 0x56, 0xe7, 0xb5, 0x4d, 0xec,
	0x8f, 0x1f, 0x89, 0xfa, 0xef, 0xb2, 0x8e, 0xfb,
	0x41, 0xb3, 0x5f, 0x45, 0x23, 0x53, 0xe4, 0x9b,
	0x75, 0xe1, 0x3d, 0x4c, 0x6c, 0x7e, 0xf5, 0x83,
	0x68, 0x51, 0xd1, 0xf9, 0xe2, 0xab, 0x62, 0x2a,
	0x08, 0x95, 0x46, 0x9d, 0x30, 0x37, 0x0a, 0x2f,
	0x0e, 0x24, 0x1b, 0xdf, 0xcd, 0x4e, 0x7f, 0xea,
	0x12, 0x1d, 0x58, 0x34, 0x36, 0xdc, 0xb4, 0x5b,
	0xa4, 0x76, 0xb7, 0x7d, 0x52, 0xdd, 0x5e, 0x13,
	0xa6, 0xb9, 0x00, 0xc1, 0x40, 0xe3, 0x79, 0xb6,
	0xd4, 0x8d, 0x67, 0x72, 0x94, 0x98, 0xb0, 0x85,
	0xbb, 0xc5, 0x4f, 0xed, 0x86, 0x9a, 0x66, 0x11,
	0x8a, 0xe9, 0x04, 0xfe, 0xa0, 0x78, 0x25, 0x4b,
	0xa2, 0x5d, 0x80, 0x05, 0x3f, 0x21, 0x70, 0xf1,
	0x63, 0x77, 0xaf, 0x42, 0x20, 0xe5, 0xfd, 0xbf,
	0x81, 0x18, 0x26, 0xc3, 0xbe, 0x35, 0x88, 0x2e,
	0x93, 0x55, 0xfc, 0x7a, 0xc8, 0xba, 0x32, 0xe6,
	0xc0, 0x19, 0x9e, 0xa3, 0x44, 0x54, 0x3b, 0x0b,
	0x8c, 0xc7, 0x6b, 0x28, 0xa7, 0xbc, 0x16, 0xad,
	0xdb, 0x64, 0x74, 0x14, 0x92, 0x0c, 0x48, 0xb8,
	0x9f, 0xbd, 0x43, 0xc4, 0x39, 0x31, 0xd3, 0xf2,
	0xd5, 0x8b, 0x6e, 0xda, 0x01, 0xb1, 0x9c, 0x49,
	0xd8, 0xac, 0xf3, 0xcf, 0xca, 0xf4, 0x47, 0x10,
	0x6f, 0xf0, 0x4a, 0x5c, 0x38, 0x57, 0x73, 0x97,
	0xcb, 0xa1, 0xe8, 0x3e, 0x96, 0x61, 0x0d, 0x0f,
	0xe0, 0x7c, 0x71, 0xcc, 0x90, 0x06, 0xf7, 0x1c,
	0xc2, 0x6a, 0xae, 0x69, 0x17, 0x99, 0x3a, 0x27,
	0xd9, 0xeb, 0x2b, 0x22, 0xd2, 0xa9, 0x07, 0x33,
	0x2d, 0x3c, 0x15, 0xc9, 0x87, 0xaa, 0x50, 0xa5,
	0x03, 0x59, 0x09, 0x1a, 0x65, 0xd7, 0x84, 0xd0,
	0x82, 0x29, 0x5a, 0x1e, 0x7b, 0xa8, 0x6d, 0x2c
};

/* combined Xtimes3[Sbox[]] */
static const u8 x3_sbox[256] = {
	0xa5, 0x84, 0x99, 0x8d, 0x0d, 0xbd, 0xb1, 0x54,
	0x50, 0x03, 0xa9, 0x7d, 0x19, 0x62, 0xe6, 0x9a,
	0x45, 0x9d, 0x40, 0x87, 0x15, 0xeb, 0xc9, 0x0b,
	0xec, 0x67, 0xfd, 0xea, 0xbf, 0xf7, 0x96, 0x5b,
	0xc2, 0x1c, 0xae, 0x6a, 0x5a, 0x41, 0x02, 0x4f,
	0x5c, 0xf4, 0x34, 0x08, 0x93, 0x73, 0x53, 0x3f,
	0x0c, 0x52, 0x65, 0x5e, 0x28, 0xa1, 0x0f, 0xb5,
	0x09, 0x36, 0x9b, 0x3d, 0x26, 0x69, 0xcd, 0x9f,
	0x1b, 0x9e, 0x74, 0x2e, 0x2d, 0xb2, 0xee, 0xfb,
	0xf6, 0x4d, 0x61, 0xce, 0x7b, 0x3e, 0x71, 0x97,
	0xf5, 0x68, 0x00, 0x2c, 0x60, 0x1f, 0xc8, 0xed,
	0xbe, 0x46, 0xd9, 0x4b, 0xde, 0xd4, 0xe8, 0x4a,
	0x6b, 0x2a, 0xe5, 0x16, 0xc5, 0xd7, 0x55, 0x94,
	0xcf, 0x10, 0x06, 0x81, 0xf0, 0x44, 0xba, 0xe3,
	0xf3, 0xfe, 0xc0, 0x8a, 0xad, 0xbc, 0x48, 0x04,
	0xdf, 0xc1, 0x75, 0x63, 0x30, 0x1a, 0x0e, 0x6d,
	0x4c, 0x14, 0x35, 0x2f, 0xe1, 0xa2, 0xcc, 0x39,
	0x57, 0xf2, 0x82, 0x47, 0xac, 0xe7, 0x2b, 0x95,
	0xa0, 0x98, 0xd1, 0x7f, 0x66, 0x7e, 0xab, 0x83,
	0xca, 0x29, 0xd3, 0x3c, 0x79, 0xe2, 0x1d, 0x76,
	0x3b, 0x56, 0x4e, 0x1e, 0xdb, 0x0a, 0x6c, 0xe4,
	0x5d, 0x6e, 0xef, 0xa6, 0xa8, 0xa4, 0x37, 0x8b,
	0x32, 0x43, 0x59, 0xb7, 0x8c, 0x64, 0xd2, 0xe0,
	0xb4, 0xfa, 0x07, 0x25, 0xaf, 0x8e, 0xe9, 0x18,
	0xd5, 0x88, 0x6f, 0x72, 0x24, 0xf1, 0xc7, 0x51,
	0x23, 0x7c, 0x9c, 0x21, 0xdd, 0xdc, 0x86, 0x85,
	0x90, 0x42, 0xc4, 0xaa, 0xd8, 0x05, 0x01, 0x12,
	0xa3, 0x5f, 0xf9, 0xd0, 0x91, 0x58, 0x27, 0xb9,
	0x38, 0x13, 0xb3, 0x33, 0xbb, 0x70, 0x89, 0xa7,
	0xb6, 0x22, 0x92, 0x20, 0x49, 0xff, 0x78, 0x7a,
	0x8f, 0xf8, 0x80, 0x17, 0xda, 0x31, 0xc6, 0xb8,
	0xc3, 0xb0, 0x77, 0x11, 0xcb, 0xfc, 0xd6, 0x3a
};

/*
 * modular multiplication tables based on:
 *
 * Xtime2[x] = (x & 0x80 ? 0x1b : 0) ^ (x + x)
 * Xtime3[x] = x^Xtime2[x];
 */
static const u8 x_time_9[256] = {
	0x00, 0x09, 0x12, 0x1b, 0x24, 0x2d, 0x36, 0x3f,
	0x48, 0x41, 0x5a, 0x53, 0x6c, 0x65, 0x7e, 0x77,
	0x90, 0x99, 0x82, 0x8b, 0xb4, 0xbd, 0xa6, 0xaf,
	0xd8, 0xd1, 0xca, 0xc3, 0xfc, 0xf5, 0xee, 0xe7,
	0x3b, 0x32, 0x29, 0x20, 0x1f, 0x16, 0x0d, 0x04,
	0x73, 0x7a, 0x61, 0x68, 0x57, 0x5e, 0x45, 0x4c,
	0xab, 0xa2, 0xb9, 0xb0, 0x8f, 0x86, 0x9d, 0x94,
	0xe3, 0xea, 0xf1, 0xf8, 0xc7, 0xce, 0xd5, 0xdc,
	0x76, 0x7f, 0x64, 0x6d, 0x52, 0x5b, 0x40, 0x49,
	0x3e, 0x37, 0x2c, 0x25, 0x1a, 0x13, 0x08, 0x01,
	0xe6, 0xef, 0xf4, 0xfd, 0xc2, 0xcb, 0xd0, 0xd9,
	0xae, 0xa7, 0xbc, 0xb5, 0x8a, 0x83, 0x98, 0x91,
	0x4d, 0x44, 0x5f, 0x56, 0x69, 0x60, 0x7b, 0x72,
	0x05, 0x0c, 0x17, 0x1e, 0x21, 0x28, 0x33, 0x3a,
	0xdd, 0xd4, 0xcf, 0xc6, 0xf9, 0xf0, 0xeb, 0xe2,
	0x95, 0x9c, 0x87, 0x8e, 0xb1, 0xb8, 0xa3, 0xaa,
	0xec, 0xe5, 0xfe, 0xf7, 0xc8, 0xc1, 0xda, 0xd3,
	0xa4, 0xad, 0xb6, 0xbf, 0x80, 0x89, 0x92, 0x9b,
	0x7c, 0x75, 0x6e, 0x67, 0x58, 0x51, 0x4a, 0x43,
	0x34, 0x3d, 0x26, 0x2f, 0x10, 0x19, 0x02, 0x0b,
	0xd7, 0xde, 0xc5, 0xcc, 0xf3, 0xfa, 0xe1, 0xe8,
	0x9f, 0x96, 0x8d, 0x84, 0xbb, 0xb2, 0xa9, 0xa0,
	0x47, 0x4e, 0x55, 0x5c, 0x63, 0x6a, 0x71, 0x78,
	0x0f, 0x06, 0x1d, 0x14, 0x2b, 0x22, 0x39, 0x30,
	0x9a, 0x93, 0x88, 0x81, 0xbe, 0xb7, 0xac, 0xa5,
	0xd2, 0xdb, 0xc0, 0xc9, 0xf6, 0xff, 0xe4, 0xed,
	0x0a, 0x03, 0x18, 0x11, 0x2e, 0x27, 0x3c, 0x35,
	0x42, 0x4b, 0x50, 0x59, 0x66, 0x6f, 0x74, 0x7d,
	0xa1, 0xa8, 0xb3, 0xba, 0x85, 0x8c, 0x97, 0x9e,
	0xe9, 0xe0, 0xfb, 0xf2, 0xcd, 0xc4, 0xdf, 0xd6,
	0x31, 0x38, 0x23, 0x2a, 0x15, 0x1c, 0x07, 0x0e,
	0x79, 0x70, 0x6b, 0x62, 0x5d, 0x54, 0x4f, 0x46
};

static const u8 x_time_b[256] = {
	0x00, 0x0b, 0x16, 0x1d, 0x2c, 0x27, 0x3a, 0x31,
	0x58, 0x53, 0x4e, 0x45, 0x74, 0x7f, 0x62, 0x69,
	0xb0, 0xbb, 0xa6, 0xad, 0x9c, 0x97, 0x8a, 0x81,
	0xe8, 0xe3, 0xfe, 0xf5, 0xc4, 0xcf, 0xd2, 0xd9,
	0x7b, 0x70, 0x6d, 0x66, 0x57, 0x5c, 0x41, 0x4a,
	0x23, 0x28, 0x35, 0x3e, 0x0f, 0x04, 0x19, 0x12,
	0xcb, 0xc0, 0xdd, 0xd6, 0xe7, 0xec, 0xf1, 0xfa,
	0x93, 0x98, 0x85, 0x8e, 0xbf, 0xb4, 0xa9, 0xa2,
	0xf6, 0xfd, 0xe0, 0xeb, 0xda, 0xd1, 0xcc, 0xc7,
	0xae, 0xa5, 0xb8, 0xb3, 0x82, 0x89, 0x94, 0x9f,
	0x46, 0x4d, 0x50, 0x5b, 0x6a, 0x61, 0x7c, 0x77,
	0x1e, 0x15, 0x08, 0x03, 0x32, 0x39, 0x24, 0x2f,
	0x8d, 0x86, 0x9b, 0x90, 0xa1, 0xaa, 0xb7, 0xbc,
	0xd5, 0xde, 0xc3, 0xc8, 0xf9, 0xf2, 0xef, 0xe4,
	0x3d, 0x36, 0x2b, 0x20, 0x11, 0x1a, 0x07, 0x0c,
	0x65, 0x6e, 0x73, 0x78, 0x49, 0x42, 0x5f, 0x54,
	0xf7, 0xfc, 0xe1, 0xea, 0xdb, 0xd0, 0xcd, 0xc6,
	0xaf, 0xa4, 0xb9, 0xb2, 0x83, 0x88, 0x95, 0x9e,
	0x47, 0x4c, 0x51, 0x5a, 0x6b, 0x60, 0x7d, 0x76,
	0x1f, 0x14, 0x09, 0x02, 0x33, 0x38, 0x25, 0x2e,
	0x8c, 0x87, 0x9a, 0x91, 0xa0, 0xab, 0xb6, 0xbd,
	0xd4, 0xdf, 0xc2, 0xc9, 0xf8, 0xf3, 0xee, 0xe5,
	0x3c, 0x37, 0x2a, 0x21, 0x10, 0x1b, 0x06, 0x0d,
	0x64, 0x6f, 0x72, 0x79, 0x48, 0x43, 0x5e, 0x55,
	0x01, 0x0a, 0x17, 0x1c, 0x2d, 0x26, 0x3b, 0x30,
	0x59, 0x52, 0x4f, 0x44, 0x75, 0x7e, 0x63, 0x68,
	0xb1, 0xba, 0xa7, 0xac, 0x9d, 0x96, 0x8b, 0x80,
	0xe9, 0xe2, 0xff, 0xf4, 0xc5, 0xce, 0xd3, 0xd8,
	0x7a, 0x71, 0x6c, 0x67, 0x56, 0x5d, 0x40, 0x4b,
	0x22, 0x29, 0x34, 0x3f, 0x0e, 0x05, 0x18, 0x13,
	0xca, 0xc1, 0xdc, 0xd7, 0xe6, 0xed, 0xf0, 0xfb,
	0x92, 0x99, 0x84, 0x8f, 0xbe, 0xb5, 0xa8, 0xa3
};

static const u8 x_time_d[256] = {
	0x00, 0x0d, 0x1a, 0x17, 0x34, 0x39, 0x2e, 0x23,
	0x68, 0x65, 0x72, 0x7f, 0x5c, 0x51, 0x46, 0x4b,
	0xd0, 0xdd, 0xca, 0xc7, 0xe4, 0xe9, 0xfe, 0xf3,
	0xb8, 0xb5, 0xa2, 0xaf, 0x8c, 0x81, 0x96, 0x9b,
	0xbb, 0xb6, 0xa1, 0xac, 0x8f, 0x82, 0x95, 0x98,
	0xd3, 0xde, 0xc9, 0xc4, 0xe7, 0xea, 0xfd, 0xf0,
	0x6b, 0x66, 0x71, 0x7c, 0x5f, 0x52, 0x45, 0x48,
	0x03, 0x0e, 0x19, 0x14, 0x37, 0x3a, 0x2d, 0x20,
	0x6d, 0x60, 0x77, 0x7a, 0x59, 0x54, 0x43, 0x4e,
	0x05, 0x08, 0x1f, 0x12, 0x31, 0x3c, 0x2b, 0x26,
	0xbd, 0xb0, 0xa7, 0xaa, 0x89, 0x84, 0x93, 0x9e,
	0xd5, 0xd8, 0xcf, 0xc2, 0xe1, 0xec, 0xfb, 0xf6,
	0xd6, 0xdb, 0xcc, 0xc1, 0xe2, 0xef, 0xf8, 0xf5,
	0xbe, 0xb3, 0xa4, 0xa9, 0x8a, 0x87, 0x90, 0x9d,
	0x06, 0x0b, 0x1c, 0x11, 0x32, 0x3f, 0x28, 0x25,
	0x6e, 0x63, 0x74, 0x79, 0x5a, 0x57, 0x40, 0x4d,
	0xda, 0xd7, 0xc0, 0xcd, 0xee, 0xe3, 0xf4, 0xf9,
	0xb2, 0xbf, 0xa8, 0xa5, 0x86, 0x8b, 0x9c, 0x91,
	0x0a, 0x07, 0x10, 0x1d, 0x3e, 0x33, 0x24, 0x29,
	0x62, 0x6f, 0x78, 0x75, 0x56, 0x5b, 0x4c, 0x41,
	0x61, 0x6c, 0x7b, 0x76, 0x55, 0x58, 0x4f, 0x42,
	0x09, 0x04, 0x13, 0x1e, 0x3d, 0x30, 0x27, 0x2a,
	0xb1, 0xbc, 0xab, 0xa6, 0x85, 0x88, 0x9f, 0x92,
	0xd9, 0xd4, 0xc3, 0xce, 0xed, 0xe0, 0xf7, 0xfa,
	0xb7, 0xba, 0xad, 0xa0, 0x83, 0x8e, 0x99, 0x94,
	0xdf, 0xd2, 0xc5, 0xc8, 0xeb, 0xe6, 0xf1, 0xfc,
	0x67, 0x6a, 0x7d, 0x70, 0x53, 0x5e, 0x49, 0x44,
	0x0f, 0x02, 0x15, 0x18, 0x3b, 0x36, 0x21, 0x2c,
	0x0c, 0x01, 0x16, 0x1b, 0x38, 0x35, 0x22, 0x2f,
	0x64, 0x69, 0x7e, 0x73, 0x50, 0x5d, 0x4a, 0x47,
	0xdc, 0xd1, 0xc6, 0xcb, 0xe8, 0xe5, 0xf2, 0xff,
	0xb4, 0xb9, 0xae, 0xa3, 0x80, 0x8d, 0x9a, 0x97
};

static const u8 x_time_e[256] = {
	0x00, 0x0e, 0x1c, 0x12, 0x38, 0x36, 0x24, 0x2a,
	0x70, 0x7e, 0x6c, 0x62, 0x48, 0x46, 0x54, 0x5a,
	0xe0, 0xee, 0xfc, 0xf2, 0xd8, 0xd6, 0xc4, 0xca,
	0x90, 0x9e, 0x8c, 0x82, 0xa8, 0xa6, 0xb4, 0xba,
	0xdb, 0xd5, 0xc7, 0xc9, 0xe3, 0xed, 0xff, 0xf1,
	0xab, 0xa5, 0xb7, 0xb9, 0x93, 0x9d, 0x8f, 0x81,
	0x3b, 0x35, 0x27, 0x29, 0x03, 0x0d, 0x1f, 0x11,
	0x4b, 0x45, 0x57, 0x59, 0x73, 0x7d, 0x6f, 0x61,
	0xad, 0xa3, 0xb1, 0xbf, 0x95, 0x9b, 0x89, 0x87,
	0xdd, 0xd3, 0xc1, 0xcf, 0xe5, 0xeb, 0xf9, 0xf7,
	0x4d, 0x43, 0x51, 0x5f, 0x75, 0x7b, 0x69, 0x67,
	0x3d, 0x33, 0x21, 0x2f, 0x05, 0x0b, 0x19, 0x17,
	0x76, 0x78, 0x6a, 0x64, 0x4e, 0x40, 0x52, 0x5c,
	0x06, 0x08, 0x1a, 0x14, 0x3e, 0x30, 0x22, 0x2c,
	0x96, 0x98, 0x8a, 0x84, 0xae, 0xa0, 0xb2, 0xbc,
	0xe6, 0xe8, 0xfa, 0xf4, 0xde, 0xd0, 0xc2, 0xcc,
	0x41, 0x4f, 0x5d, 0x53, 0x79, 0x77, 0x65, 0x6b,
	0x31, 0x3f, 0x2d, 0x23, 0x09, 0x07, 0x15, 0x1b,
	0xa1, 0xaf, 0xbd, 0xb3, 0x99, 0x97, 0x85, 0x8b,
	0xd1, 0xdf, 0xcd, 0xc3, 0xe9, 0xe7, 0xf5, 0xfb,
	0x9a, 0x94, 0x86, 0x88, 0xa2, 0xac, 0xbe, 0xb0,
	0xea, 0xe4, 0xf6, 0xf8, 0xd2, 0xdc, 0xce, 0xc0,
	0x7a, 0x74, 0x66, 0x68, 0x42, 0x4c, 0x5e, 0x50,
	0x0a, 0x04, 0x16, 0x18, 0x32, 0x3c, 0x2e, 0x20,
	0xec, 0xe2, 0xf0, 0xfe, 0xd4, 0xda, 0xc8, 0xc6,
	0x9c, 0x92, 0x80, 0x8e, 0xa4, 0xaa, 0xb8, 0xb6,
	0x0c, 0x02, 0x10, 0x1e, 0x34, 0x3a, 0x28, 0x26,
	0x7c, 0x72, 0x60, 0x6e, 0x44, 0x4a, 0x58, 0x56,
	0x37, 0x39, 0x2b, 0x25, 0x0f, 0x01, 0x13, 0x1d,
	0x47, 0x49, 0x5b, 0x55, 0x7f, 0x71, 0x63, 0x6d,
	0xd7, 0xd9, 0xcb, 0xc5, 0xef, 0xe1, 0xf3, 0xfd,
	0xa7, 0xa9, 0xbb, 0xb5, 0x9f, 0x91, 0x83, 0x8d
};

/*
 * Exchanges columns in each of 4 rows
 * row0 - unchanged, row1- shifted left 1,
 * row2 - shifted left 2 and row3 - shifted left 3
 */
static void shift_rows(u8 *state)
{
	u8 tmp;

	/* just substitute row 0 */
	state[0] = sbox[state[0]];
	state[4] = sbox[state[4]];
	state[8] = sbox[state[8]];
	state[12] = sbox[state[12]];

	/* rotate row 1 */
	tmp = sbox[state[1]];
	state[1] = sbox[state[5]];
	state[5] = sbox[state[9]];
	state[9] = sbox[state[13]];
	state[13] = tmp;

	/* rotate row 2 */
	tmp = sbox[state[2]];
	state[2] = sbox[state[10]];
	state[10] = tmp;
	tmp = sbox[state[6]];
	state[6] = sbox[state[14]];
	state[14] = tmp;

	/* rotate row 3 */
	tmp = sbox[state[15]];
	state[15] = sbox[state[11]];
	state[11] = sbox[state[7]];
	state[7] = sbox[state[3]];
	state[3] = tmp;
}

/*
 * restores columns in each of 4 rows
 * row0 - unchanged, row1- shifted right 1,
 * row2 - shifted right 2 and row3 - shifted right 3
 */
static void inv_shift_rows(u8 *state)
{
	u8 tmp;

	/* restore row 0 */
	state[0] = inv_sbox[state[0]];
	state[4] = inv_sbox[state[4]];
	state[8] = inv_sbox[state[8]];
	state[12] = inv_sbox[state[12]];

	/* restore row 1 */
	tmp = inv_sbox[state[13]];
	state[13] = inv_sbox[state[9]];
	state[9] = inv_sbox[state[5]];
	state[5] = inv_sbox[state[1]];
	state[1] = tmp;

	/* restore row 2 */
	tmp = inv_sbox[state[2]];
	state[2] = inv_sbox[state[10]];
	state[10] = tmp;
	tmp = inv_sbox[state[6]];
	state[6] = inv_sbox[state[14]];
	state[14] = tmp;

	/* restore row 3 */
	tmp = inv_sbox[state[3]];
	state[3] = inv_sbox[state[7]];
	state[7] = inv_sbox[state[11]];
	state[11] = inv_sbox[state[15]];
	state[15] = tmp;
}

/* recombine and mix each row in a column */
static void mix_sub_columns(u8 *state)
{
	u8 tmp[4 * AES_STATECOLS];

	/* mixing column 0 */
	tmp[0] = x2_sbox[state[0]] ^ x3_sbox[state[5]] ^
		 sbox[state[10]] ^ sbox[state[15]];
	tmp[1] = sbox[state[0]] ^ x2_sbox[state[5]] ^
		 x3_sbox[state[10]] ^ sbox[state[15]];
	tmp[2] = sbox[state[0]] ^ sbox[state[5]] ^
		 x2_sbox[state[10]] ^ x3_sbox[state[15]];
	tmp[3] = x3_sbox[state[0]] ^ sbox[state[5]] ^
		 sbox[state[10]] ^ x2_sbox[state[15]];

	/* mixing column 1 */
	tmp[4] = x2_sbox[state[4]] ^ x3_sbox[state[9]] ^
		 sbox[state[14]] ^ sbox[state[3]];
	tmp[5] = sbox[state[4]] ^ x2_sbox[state[9]] ^
		 x3_sbox[state[14]] ^ sbox[state[3]];
	tmp[6] = sbox[state[4]] ^ sbox[state[9]] ^
		 x2_sbox[state[14]] ^ x3_sbox[state[3]];
	tmp[7] = x3_sbox[state[4]] ^ sbox[state[9]] ^
		 sbox[state[14]] ^ x2_sbox[state[3]];

	/* mixing column 2 */
	tmp[8] = x2_sbox[state[8]] ^ x3_sbox[state[13]] ^
		 sbox[state[2]] ^ sbox[state[7]];
	tmp[9] = sbox[state[8]] ^ x2_sbox[state[13]] ^
		 x3_sbox[state[2]] ^ sbox[state[7]];
	tmp[10] = sbox[state[8]] ^ sbox[state[13]] ^
		  x2_sbox[state[2]] ^ x3_sbox[state[7]];
	tmp[11] = x3_sbox[state[8]] ^ sbox[state[13]] ^
		  sbox[state[2]] ^ x2_sbox[state[7]];

	/* mixing column 3 */
	tmp[12] = x2_sbox[state[12]] ^ x3_sbox[state[1]] ^
		  sbox[state[6]] ^ sbox[state[11]];
	tmp[13] = sbox[state[12]] ^ x2_sbox[state[1]] ^
		  x3_sbox[state[6]] ^ sbox[state[11]];
	tmp[14] = sbox[state[12]] ^ sbox[state[1]] ^
		  x2_sbox[state[6]] ^ x3_sbox[state[11]];
	tmp[15] = x3_sbox[state[12]] ^ sbox[state[1]] ^
		  sbox[state[6]] ^ x2_sbox[state[11]];

	memcpy(state, tmp, sizeof(tmp));
}

/* restore and un-mix each row in a column */
static void inv_mix_sub_columns(u8 *state)
{
	u8 tmp[4 * AES_STATECOLS];
	int  i;

	/* restore column 0 */
	tmp[0] = x_time_e[state[0]] ^ x_time_b[state[1]] ^
		 x_time_d[state[2]] ^ x_time_9[state[3]];
	tmp[5] = x_time_9[state[0]] ^ x_time_e[state[1]] ^
		 x_time_b[state[2]] ^ x_time_d[state[3]];
	tmp[10] = x_time_d[state[0]] ^ x_time_9[state[1]] ^
		  x_time_e[state[2]] ^ x_time_b[state[3]];
	tmp[15] = x_time_b[state[0]] ^ x_time_d[state[1]] ^
		  x_time_9[state[2]] ^ x_time_e[state[3]];

	/* restore column 1 */
	tmp[4] = x_time_e[state[4]] ^ x_time_b[state[5]] ^
		 x_time_d[state[6]] ^ x_time_9[state[7]];
	tmp[9] = x_time_9[state[4]] ^ x_time_e[state[5]] ^
		 x_time_b[state[6]] ^ x_time_d[state[7]];
	tmp[14] = x_time_d[state[4]] ^ x_time_9[state[5]] ^
		  x_time_e[state[6]] ^ x_time_b[state[7]];
	tmp[3] = x_time_b[state[4]] ^ x_time_d[state[5]] ^
		 x_time_9[state[6]] ^ x_time_e[state[7]];

	/* restore column 2 */
	tmp[8] = x_time_e[state[8]] ^ x_time_b[state[9]] ^
		 x_time_d[state[10]] ^ x_time_9[state[11]];
	tmp[13] = x_time_9[state[8]] ^ x_time_e[state[9]] ^
		  x_time_b[state[10]] ^ x_time_d[state[11]];
	tmp[2] = x_time_d[state[8]] ^ x_time_9[state[9]] ^
		 x_time_e[state[10]] ^ x_time_b[state[11]];
	tmp[7] = x_time_b[state[8]] ^ x_time_d[state[9]] ^
		 x_time_9[state[10]] ^ x_time_e[state[11]];

	/* restore column 3 */
	tmp[12] = x_time_e[state[12]] ^ x_time_b[state[13]] ^
		  x_time_d[state[14]] ^ x_time_9[state[15]];
	tmp[1] = x_time_9[state[12]] ^ x_time_e[state[13]] ^
		 x_time_b[state[14]] ^ x_time_d[state[15]];
	tmp[6] = x_time_d[state[12]] ^ x_time_9[state[13]] ^
		 x_time_e[state[14]] ^ x_time_b[state[15]];
	tmp[11] = x_time_b[state[12]] ^ x_time_d[state[13]] ^
		  x_time_9[state[14]] ^ x_time_e[state[15]];

	for (i = 0; i < 4 * AES_STATECOLS; i++)
		state[i] = inv_sbox[tmp[i]];
}

/*
 * encrypt/decrypt columns of the key
 * n.b. you can replace this with byte-wise xor if you wish.
 */
static void add_round_key(u32 *state, u32 *key)
{
	int idx;

	for (idx = 0; idx < 4; idx++)
		state[idx] ^= key[idx];
}

static u8 rcon[11] = {
	0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

/* produce AES_STATECOLS bytes for each round */
void aes_expand_key(u8 *key, u8 *expkey)
{
	u8 tmp0, tmp1, tmp2, tmp3, tmp4;
	u32 idx;

	memcpy(expkey, key, AES_KEYCOLS * 4);

	for (idx = AES_KEYCOLS; idx < AES_STATECOLS * (AES_ROUNDS + 1); idx++) {
		tmp0 = expkey[4*idx - 4];
		tmp1 = expkey[4*idx - 3];
		tmp2 = expkey[4*idx - 2];
		tmp3 = expkey[4*idx - 1];
		if (!(idx % AES_KEYCOLS)) {
			tmp4 = tmp3;
			tmp3 = sbox[tmp0];
			tmp0 = sbox[tmp1] ^ rcon[idx / AES_KEYCOLS];
			tmp1 = sbox[tmp2];
			tmp2 = sbox[tmp4];
		} else if ((AES_KEYCOLS > 6) && (idx % AES_KEYCOLS == 4)) {
			tmp0 = sbox[tmp0];
			tmp1 = sbox[tmp1];
			tmp2 = sbox[tmp2];
			tmp3 = sbox[tmp3];
		}

		expkey[4*idx+0] = expkey[4*idx - 4*AES_KEYCOLS + 0] ^ tmp0;
		expkey[4*idx+1] = expkey[4*idx - 4*AES_KEYCOLS + 1] ^ tmp1;
		expkey[4*idx+2] = expkey[4*idx - 4*AES_KEYCOLS + 2] ^ tmp2;
		expkey[4*idx+3] = expkey[4*idx - 4*AES_KEYCOLS + 3] ^ tmp3;
	}
}

/* encrypt one 128 bit block */
void aes_encrypt(u8 *in, u8 *expkey, u8 *out)
{
	u8 state[AES_STATECOLS * 4];
	u32 round;

	memcpy(state, in, AES_STATECOLS * 4);
	add_round_key((u32 *)state, (u32 *)expkey);

	for (round = 1; round < AES_ROUNDS + 1; round++) {
		if (round < AES_ROUNDS)
			mix_sub_columns(state);
		else
			shift_rows(state);

		add_round_key((u32 *)state,
			      (u32 *)expkey + round * AES_STATECOLS);
	}

	memcpy(out, state, sizeof(state));
}

void aes_decrypt(u8 *in, u8 *expkey, u8 *out)
{
	u8 state[AES_STATECOLS * 4];
	int round;

	memcpy(state, in, sizeof(state));

	add_round_key((u32 *)state,
		      (u32 *)expkey + AES_ROUNDS * AES_STATECOLS);
	inv_shift_rows(state);

	for (round = AES_ROUNDS; round--; ) {
		add_round_key((u32 *)state,
			      (u32 *)expkey + round * AES_STATECOLS);
		if (round)
			inv_mix_sub_columns(state);
	}

	memcpy(out, state, sizeof(state));
}
