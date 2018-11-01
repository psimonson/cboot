/*******************************************************
 * io.c - Simple program for my boot loader.           *
 *******************************************************
 * Create by Philip R. Simonson (aka 5n4k3)     (2018) *
 *******************************************************
 */

#include "code16gcc.h"
#include "system.h"
#include "disk.h"

/* program for my boot loader to run */
void
main (void)
{
	extern void graphics(void);
	extern void graphics2(void);
	extern void typing(void);
	extern void test_getline(void);
	extern void test_getline2(void);
	extern void test_getch(void);
	unsigned char ch;

	for (;;) {
		print("Press 'q' to reboot system...\r\n"
			"Press 'e' to wipe CMOS!\r\n"
			"Press 'g' for graphics.\r\n"
			"Press 't' for more graphics.\r\n"
			"Press 'h' for timed typing.\r\n"
			"Press 'o' for testing my getline.\r\n"
			"Press 'p' for testing my getline again.\r\n"
			"Press 'm' for testing my getchar.\r\n");
		ch = getch();
		switch (ch) {
		case 'q':
		case 'Q':
			reboot();
			break;
		case 'e':
		case 'E':
			print("Wiping CMOS...\r\n");
			clear_cmos();
			break;
		case 'g':
		case 'G':
			graphics();
			break;
		case 't':
		case 'T':
			graphics2();
			break;
		case 'h':
		case 'H':
			typing();
			break;
		case 'o':
		case 'O':
			test_getline();
			break;
		case 'p':
		case 'P':
			test_getline2();
			break;
		case 'm':
		case 'M':
			test_getch();
			break;
		default:
			print("Invalid key pressed\r\n");
			break;
		}
	}
}

/* graphics:  testing simple graphics */
void
graphics (void)
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
}

/* graphics2:  testing simple graphics */
void
graphics2 (void)
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
}

/* test_getline: function to test my getline function */
void
test_getline (void)
{
	char buf[64];
	init_graphics(0x02);
	print("Enter your name: ");
	getline(buf, sizeof(buf));
	trim(buf);
	init_graphics(0x02);
	if (!strcmp(buf, "Philip Simonson"))
		print("Hello, master.\r\n");
	else
		print("I don't know you.\r\n");
	print("Press any key to quit...");
	getch();
	init_graphics(0x02);
}

void
test_getline2 (void)
{
	char buf[64];
	print("Enter your name: ");
	getline(buf, sizeof buf);
	trim(buf);
	print("\r\n");
	if (!strcmp(buf, ""))
		print("Please enter your name.\r\n");
	else {
		print("Hello, ");
		print(buf);
		print(".");
	}
	print("\r\nPress any key to quit...\r\n");
	getch();
}

void
test_getch (void)
{
	int i;

	init_graphics(0x03);
	print("Password: ");
	i = 8;
	while (i > 0) {
		char ch = getchar();
		if (ch == '\r' || ch == '\n') {
			ungetch(ch);
			break;
		}
	}
	if (bufcmp("pass") == 0)
		print("\r\nAccess granted!\r\n");
	else
		print("\r\nAccess denied!\r\n");
	getch();
	init_graphics(0x03);
}

#define TYPING_MESSAGE \
"This is going to be typed on the screen...\r\n"\
"\r\n"\
"It's pretty cool that you can make a bootloader and program almost\r\n"\
"all in C, using just a bit of assembler to start off the bootloader.\r\n"\
"All the rest is in C, but all standard functions in libraries have\r\n"\
"to be written in inline assembler. Then the actual main functions\r\n"\
"and what not, all in C. That is the only way you can write any boot\r\n"\
"code in C. Unfortunately, you have to have assembler mixed with C.\r\n"\
"Just plain C alone will NOT work!\r\n"

/* typing:  simple function to type text on the screen */
void
typing (void)
{
	int i;
	init_graphics(0x02);
	for (i = 0; i < strlen(TYPING_MESSAGE); i++) {
		putchar(TYPING_MESSAGE[i]);
		play_sound(0x13fb);
		timer(0x0001, 0x8040);
		stop_sound();
	}
	move(34, 15);
	print("- Philip R. Simonson (aka 5n4k3)");
	move(0, 24);
	print("Press any key to continue . . .");
	getch();
	init_graphics(0x02);
}
