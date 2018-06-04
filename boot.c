#include "code16gcc.h"
#include "system.h"
#include "disk.h"
#include "fat.h"


#define START_SECTOR 0x02
#define SECTOR_COUNT 0x07
#define FLOPPY_DRIVE 0x00

void
main(void)
{
	fat_t table;
	init_fat(&table);
	boot_startup();
	print("Loading OS...\r\n");
	read_disk(START_SECTOR, SECTOR_COUNT, FLOPPY_DRIVE);
	getch();
	reboot();
}
