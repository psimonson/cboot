#ifndef _IO_H_
#define _IO_H_

/* putch:  puts a character on the screen */
static void
putch (char c, unsigned char color)
{
	__asm__ __volatile__ ("int $0x10"::"a"(0x0e00 | c), "b"(0x0000 | color));
}
/* putchar:  puts a character on the screen; with color gray on black */
#define putchar(c) putch(c, 0x07)

/* move:  moves cursor to x,y position */
static void
move (unsigned char x, unsigned char y)
{
	__asm__ __volatile__ ("int $0x10"
			::"a"(0x0200), "b"(0x0007), "d"((y << 8) | x));
}

/* print_color:  prints a string in color */
static void
print_color (const char *s, unsigned char color)
{
	while (*s) {
		putch(*s++, color);
	}
}
/* print:  prints a string normal color */
#define print(msg) print_color(msg, 0x07)

/* strlen:  count length of string; to null terminator */
static int
strlen (const char *s)
{
	const char *p = s;
	while (*p++);
	return (p-s-1);
}

/* getch:  get character from keyboard */
static char
getch (void)
{
	char ch;
	__asm__ __volatile__ ("int $0x16":"=a"(ch):"a"(0x0000));
	__asm__ __volatile__ ("int $0x16"::"a"(0x0100));
	return ch;
}

/* getche_color:  get character from keyboard; put to screen in color */
static char
getche_color (unsigned char color)
{
	char ch;
	ch = getch();
	putch(ch, color);
	return ch;
}
#define getche() getche_color(0x07)

/* getline:  get string of characters; size of lim-1 */
static int
getline (char *s, int lim)
{
	char *p = s;
	char c;
	while (lim-- > 2 && (c = getche()) != '\r')
		switch (c) {
			case '\b':
				*--s = '\0';
				print(" \b");
				break;
			case '\r':
				putchar('\n');
				break;
			default:
				*s++ = c;
			break;
		}
	if (c == '\r') {
		*s++ = c;
		*s++ = '\n';
	}
	*s = '\0';
	return s-p;
}

/* trim:  trim new line off string s */
static void
trim(char *s)
{
	while (*s) {
		if (*s == '\r' || *s == '\n')
			break;
		s++;
	}
	*s = '\0';
}

/* strcpy:  copy t to s; returns length on success, if failed returns -1 */
static int
strcpy (char *s, char *t)
{
	char *p = s;
	while ((*s++ = *t++) != '\0');
	return s-p-1;
}

/* memcpy:  copy p2 to p1, n amount of bytes; returns void (nothing) */
static void
memcpy (void *p1, void *p2, int n)
{
	char *p = (char*)p2;
	while (((char*)p2)-p < n)
		*((char*)p1++) = *((char*)p2++);
}

/* strcmp:  compare t to s; returns 0 if match, anything else if false */
static int
strcmp (const char *s, const char *t)
{
	while (*s == *t++)
		if (*s++ == '\0')
			return 0;
	return *s-*t;
}

/* draw_pixel:  draws a pixel at specified location */
static void
draw_pixel (unsigned short x, unsigned short y, short unsigned int color)
{
	__asm__ __volatile__ ("int $0x10"::"a"(0x0c00 | color), "c"(y), "d"(x));
}

#endif
