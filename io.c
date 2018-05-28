#include "code16gcc.h"
#include "system.h"
#include "io.h"

int main()
{
	void graphics(void);
	unsigned char ch, i;
	for (;;) {
		print("Press 'q' to reboot system...\r\n"
			"Press 'e' to wipe CMOS!\r\n"
			"Press 'g' for graphics.\r\n");
		ch = getch();
		switch (ch) {
		case 'q':
		case 'Q':
			__asm__("jmp $0xFFFF, $0x0000;");
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
		default:
			print("Invalid key pressed\r\n");
			break;
		}
	}
}

void graphics(void)
{
	unsigned short x, y;

	init_graphics(0x0D);
	for (y = 0; y < 50; y+=2)
		for (x = 0; x <= 25; x+=5)
			draw_pixel(y, x, 0x0f);
	getch();
	init_graphics(0x02);
	reboot();
}
