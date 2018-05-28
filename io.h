#ifndef _IO_H_
#define _IO_H_

#ifndef _CODE16GCC_H_
#include "code16gcc.h"
#endif

/* putch:  puts a character on the screen */
static void putch(char c, char color)
{
	__asm__ __volatile__(
		"int $0x10"
		:
		: "a"(0x0e00 | c), "b"(color)
	);
}
#define putchar(c) putch(c, 0x07)

/* move:  moves cursor to x,y position */
static void move(unsigned char x, unsigned char y)
{
	__asm__ __volatile__(
		"int $0x10"
		:
		: "a"(0x0200), "b"(0x0007), "d"((y << 8) | x)
	);
}

/* print_color:  prints a string in color */
static void print_color(const char *s, char color)
{
	while (*s) {
		putch(*s++, color);
	}
}
#define print(msg) print_color(msg, 0x07)

/* getch:  get character from keyboard */
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

/* getche:  get character from input; put character on screen */
static char getche(void)
{
	char ch;
	ch = getch();
	putchar(ch);
	return ch;
}

/* draw_pixel:  draws a pixel at specified location */
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
