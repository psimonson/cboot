#include "code16gcc.h"
#include "system.h"
#include "disk.h"
#include "io.h"

void main(void)
{
	extern void graphics(void);
	extern void graphics2(void);
	unsigned char ch, i;
	for (;;) {
		print("Press 'q' to reboot system...\r\n"
			"Press 'e' to wipe CMOS!\r\n"
			"Press 'g' for graphics.\r\n"
			"Press 't' for more graphics.\r\n");
		ch = getch();
		switch (ch) {
		case 'q':
		case 'Q':
			reboot();
			break;
		case 'e':
		case 'E':
			print("Wiping CMOS...\r\n");
			for (i = 0; i < 255; i++)
				__asm__ __volatile__(
					"xor %ax, %ax;"
					"in $0x70, %ax;"
					"out %ax, $0x71;"
				);
			break;
		case 'g':
		case 'G':
			graphics();
			break;
		case 't':
		case 'T':
			graphics2();
			break;
		default:
			print("Invalid key pressed\r\n");
			break;
		}
	}
}

void graphics(void)
{
	unsigned short x, y;

	init_graphics(0x12);
	for (y = 130; y <= 200; y++)
		for (x = 25; x <= 277; x++)
			draw_pixel(y, x+3, 0xfb);
	move(9, 9);
	print_color(" By PRS (aka 5n4k3) ", 0xfb);
	move(10, 10);
	print_color(" Hello world ! ! ! ", 0xfb);
	move(3, 11);
	print_color(" What happens when you're good ? ", 0xfb);
	move(10, 13);
	print_color(" Press a key . . . ", 0x0f);
	getch();
	init_graphics(0x02);
	read_disk();
}

void graphics2(void)
{
	unsigned short x, y;

	init_graphics(0x12);
	for (y = 0; y <= 480; y += 2)
		for (x = 0; x <= 640; x += 2)
			draw_pixel(y, x, 0x5a);
	move(10, 10);
	print_color("  Hello ! ! !  ", 0x0A);
	getch();
	init_graphics(0x02);
	read_disk();
}
