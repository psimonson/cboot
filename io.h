#ifndef _IO_H_
#define _IO_H_

#ifndef _CODE16GCC_H_
#include "code16gcc.h"
#endif

static void putch(char c, char color)
{
	asm volatile("int $0x10" : : "a"((0x0e << 8) | c), "b"((0x0e << 8) | color));
}
#define putchar(c) putch(c, 0x07)

static void print_color(const char *s, char color)
{
	while (*s) {
		putch(*s++, color);
	}
}
#define print(msg) print_color(msg, 0x07)

static char getch(void)
{
	char ch;
	__asm__ __volatile__(
		"int $0x16"
		: "=a"(ch)
		: "a"(0x0000)
	);
	return ch;
}

static void draw_pixel(unsigned short y, unsigned short x,
		unsigned char color)
{
	__asm__ __volatile__(
		"int $0x10"
		:
		: "a"(0x0c00 | color), "c"(x), "d"(y)
	);
}

#endif
