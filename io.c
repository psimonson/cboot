#include "code16gcc.h"
#include "system.h"
#include "disk.h"
#include "io.h"

int main()
{
	extern void graphics(void);
	extern void graphics2(void);
	unsigned char ch, i;
	for (;;) {
		print("Press 'q' to reboot system...\r\n"
			"Press 'e' to wipe CMOS!\r\n"
			"Press 'g' for graphics.\r\n");
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
	for (y = 0; y <= 240; y += 2)
		for (x = 0; x <= 320; x += 2)
			draw_pixel(y, x, 0x2f);
	move(10, 10);
	print_color(" Hello world ! ! ! ", 0x0D);
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
