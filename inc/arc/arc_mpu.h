/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */
#ifndef _ARC_HAL_MPU_H_
#define _ARC_HAL_MPU_H_

#include "arc.h"
#include "arc_builtin.h"

#ifndef ARC_FEATURE_MPU_VERSION
#define ARC_FEATURE_MPU_VERSION 2
#endif

#define AUX_MPU_RDB_VALID_MASK (0x1)
#define AUX_MPU_EN_ENABLE   (0x40000000)
#define AUX_MPU_EN_DISABLE  (0xBFFFFFFF)

#define AUX_MPU_RDP_REGION_SIZE(bits)  \
			(((bits - 1) & 0x3) | (((bits - 1) & 0x1C) << 7))

#define AUX_MPU_RDP_ATTR_MASK (0xFFF)

#define AUX_MPU_RDP_UE  0x008    /* allow user execution */
#define AUX_MPU_RDP_UW  0x010    /* allow user write */
#define AUX_MPU_RDP_UR  0x020    /* allow user read */
#define AUX_MPU_RDP_KE  0x040    /* only allow kernel execution */
#define AUX_MPU_RDP_KW  0x080    /* only allow kernel write */
#define AUX_MPU_RDP_KR  0x100    /* only allow kernel read */
#define AUX_MPU_RDP_S   0x8000   /* secure */
#define AUX_MPU_RDP_N   0x0000   /* normal */

#define AUX_MPU_INDEX_DEFAULT	0x80000000
#define AUX_MPU_INDEX_MULT	0x40000000

#if ARC_FEATURE_MPU_VERSION == 2
#define ARC_FEATURE_MPU_ALIGNMENT_BITS 11
#elif ARC_FEATURE_MPU_VERSION == 3
#define ARC_FEATURE_MPU_ALIGNMENT_BITS 5
#endif

/* Some helper defines for common regions */
#define ARC_MPU_REGION_RAM_ATTR	\
			(AUX_MPU_RDP_UW | AUX_MPU_RDP_UR | \
			 AUX_MPU_RDP_KW | AUX_MPU_RDP_KR)

#define ARC_MPU_REGION_FLASH_ATTR \
			(AUX_MPU_RDP_UE | AUX_MPU_RDP_UR | \
			 AUX_MPU_RDP_KE | AUX_MPU_RDP_KR)

#define ARC_MPU_REGION_IO_ATTR \
			(AUX_MPU_RDP_UW | AUX_MPU_RDP_UR | \
			 AUX_MPU_RDP_KW | AUX_MPU_RDP_KR)

#define ARC_MPU_REGION_ALL_ATTR \
			(AUX_MPU_RDP_UW | AUX_MPU_RDP_UR | \
			 AUX_MPU_RDP_KW | AUX_MPU_RDP_KR | \
			 AUX_MPU_RDP_KE | AUX_MPU_RDP_UE)

#define REGION_32B      0x200
#define REGION_64B      0x201
#define REGION_128B     0x202
#define REGION_256B     0x203
#define REGION_512B     0x400
#define REGION_1K       0x401
#define REGION_2K       0x402
#define REGION_4K       0x403
#define REGION_8K       0x600
#define REGION_16K      0x601
#define REGION_32K      0x602
#define REGION_64K      0x603
#define REGION_128K     0x800
#define REGION_256K     0x801
#define REGION_512K     0x802
#define REGION_1M       0x803
#define REGION_2M       0xA00
#define REGION_4M       0xA01
#define REGION_8M       0xA02
#define REGION_16M      0xA03
#define REGION_32M      0xC00
#define REGION_64M      0xC01
#define REGION_128M     0xC02
#define REGION_256M     0xC03
#define REGION_512M     0xE00
#define REGION_1G       0xE01
#define REGION_2G       0xE02
#define REGION_4G       0xE03

/* Region definition data structure */
typedef struct arc_mpu_region {
	/* Region Name */
	const char *name;
	/* Region Base Address */
	uint32_t base;
	uint32_t size;
	/* Region Attributes */
	uint32_t attr;
} ARC_MPU_REGION;

#define ARC_MPU_REGION_ENTRY(_name, _base, _size, _attr) \
	{\
		.name = _name, \
		.base = _base, \
		.size = _size, \
		.attr = _attr, \
	}

Inline uint8_t arc_mpu_regions(void)
{
	uint32_t num = _arc_aux_read(AUX_BCR_MPU);

	num = (num & 0xFF00) >> 8;

	return (uint8_t)num;
}

extern void arc_mpu_enable(void);
extern void arc_mpu_disable(void);
extern void arc_mpu_region(uint32_t index, uint32_t base, uint32_t size,
			 uint32_t region_attr);
extern void arc_mpu_default(uint32_t region_attr);
extern int32_t arc_mpu_in_region(uint32_t index, uint32_t start, uint32_t size);
extern int32_t arc_mpu_probe(uint32_t addr);

#endif /* _ARC_HAL_MPU_H_ */


