#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "mybool.h"

/* play_sound:  plays sound at frequency freq */
static void
play_sound (unsigned short freq)
{
	__asm__ __volatile__ ("mov $0xB6, %%al;"
			"out %%al, $0x43;"
			"mov %0, %%ax;"
			"out %%al, $0x42;" /* output low byte */
			"mov %%ah, %%al;" /* move high byte to low */
			"out %%al, $0x42;" /* output high byte */
			"in $0x61, %%al;" /* turn on note */
			"or $0x03, %%al;"
			"out %%al, $0x61;"
			:
			: "r"(freq)
			);
}

/* stop_sound:  stops pc buzzer; internal pc speaker */
static void
stop_sound (void)
{
	__asm__ __volatile__ ("in $0x61, %al;and $0xFC, %al;out %al, $0x61;");
}

/* is_timer_active:  checks if a timer is already active; returns bool */
static bool_t
is_timer_active (void)
{
	bool_t ret = true;
	__asm__ goto ("int $0x15; jc %l1"
			:
			: "a"(0x8600)
			:
			: carry_set
			);
quit:
	return ret;
carry_set:
	__asm__ ("clc");
	ret = false;
	goto quit;
}

/* async_timer:  creates a timer that does not halt code execution */
static bool_t
async_timer (short hbits, short lbits)
{
	bool_t ret = true;
	__asm__ goto ("int $0x15; jc %l3"
			:
			: "a"(0x8300), "c"(hbits), "d"(lbits)
			:
			: carry_set
			);
quit:
	return ret;
carry_set:
	__asm__ ("clc");
	ret = false;
	goto quit;
}

/* timer:  creates a timer; halts program execution until time expires */
static bool_t
timer (short hbits, short lbits)
{
	bool_t ret = true;
	__asm__ goto ("int $0x15; jc %l3"
			:
			: "a"(0x8600), "c"(hbits), "d"(lbits)
			:
			: carry_set
			);
quit:
	return ret;
carry_set:
	__asm__ ("clc");
	ret = false;
	goto quit;
}

/* reboot:  warm reboot; restarts the computer */
static void reboot(void);
#define reboot() __asm__ __volatile__ ("ljmpw $0xFFFF, $0x0000")

/* inb:  get __port value */
static unsigned char
inb (unsigned short int __port)
{
	unsigned char _v;
	__asm__ __volatile__ ("inb %1,%0":"=a" (_v):"Nd" (__port));
	return _v;
}

/* outb:  output __value to __port */
static void
outb (unsigned char __value, unsigned short int __port)
{
	__asm__ __volatile__ ("outb %0,%1"::"a" (__value), "Nd" (__port));
}

/* read_cmos:  read __index of CMOS memory; returns byte */
static unsigned char
read_cmos (unsigned char __index)
{
	unsigned char _byte;
	__asm__ ("cli");
	outb (__index, 0x70);
	_byte = inb (__index);
	__asm__ ("sti");
	return _byte;
}

/* write_cmos:  write __byte to __index of CMOS memory */
static void
write_cmos (unsigned char __index)
{
	unsigned char byte;
	__asm__ ("cli");
	while (__index) {
		outb (__index, 0x70);
		byte = inb (0x71);
		outb (byte | 0x00, 0x71);
		--__index;
	}
	__asm__ ("sti");
}

/* clear_cmos:  wipe cmos; resetting back to factory */
static void
clear_cmos (void)
{
	write_cmos(0xff);
}

/* init_graphics:  clear screen and set graphics mode */
static void
init_graphics (unsigned short int __mode)
{
	__asm__ __volatile__("int $0x10"::"a"(0x0000 | __mode));
}

/* boot_startup:  initalize stack */
static void
boot_startup (void)
{
	__asm__ __volatile__ (
		"xor %ax,%ax;"
		"mov %ax,%ds;"
		"mov %ax,%es;"
		"mov %ax,%fs;"
		"mov $0x8000,%esp;"
		);
}

#endif
