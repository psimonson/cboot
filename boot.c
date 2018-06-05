#include "code16gcc.h"
#include "system.h"
#include "disk.h"
#include "fat.h"

void main (void);
__asm__ ("mov $main,%ax");
__asm__ ("jmp *%eax");
__asm__ ("nop");
fat_t table;

#define START_SECTOR 0x02
#define SECTOR_COUNT 0x0A
#define FLOPPY_DRIVE 0x00

void
main (void)
{
	init_fat(&table);
	boot_startup();
	print("Loading OS...\r\n");
	if (read_disk(START_SECTOR, SECTOR_COUNT, FLOPPY_DRIVE))
		setup_stack(0x1000);
	else
		print("Error: reading disk sector, no operating system found.\r\n"
				"Press a key to reboot...\r\n");
	getch();
	reboot();
}
