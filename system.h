#ifndef _SYSTEM_H_
#define _SYSTEM_H_

static void reboot(void)
{
	__asm__ __volatile__(
		"ljmpw $0xFFFF, $0x0000;"
	);
}

static void clear_cmos(void)
{
	int i = 0;
	while (i++ <= 255) {
		__asm__ __volatile__(
			"xor %ax, %ax; \
			in $0x70, %ax; \
			out %ax, $0x71;"
		);
	}
}

static void init_graphics(int mode)
{
	__asm__ __volatile__(
		"int $0x10"
		:
		: "a"(0x0000 | mode)
	);
}

#endif
