#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#ifndef _CODE16GCC_H_
#include "code16gcc.h"
#endif

static void reboot(void)
{
	__asm__ __volatile__(
		"ljmpw $0xFFFF, $0x0000;"
	);
}

static void clear_cmos(void)
{
	unsigned char i = 0;
	while (i++ <= 255) {
		__asm__ __volatile__(
			"xor %ax, %ax; \
			in $0x70, %ax; \
			out %ax, $0x71;"
		);
	}
}

static void init_graphics(char mode)
{
	__asm__ __volatile__(
		"int $0x10"
		:
		: "a"(0x0000 | mode)
	);
}

#endif
