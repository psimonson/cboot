#include "code16gcc.h"
#include "system.h"
#include "disk.h"

#define START_SECTOR 0x02
#define SECTOR_COUNT 0x05
#define FLOPPY_DRIVE 0x00

void
main(void)
{
	boot_startup();
	print("Loading sector from floppy.\r\n");
	if (read_disk(START_SECTOR, SECTOR_COUNT, FLOPPY_DRIVE) == CFLAG_SET) {
		print("Error: Press a key to reboot.\r\n");
		reboot();
	} else {
		play_sound(0x1a5b);
		timer(0x001e, 0x8040);
		stop_sound();
		jump_sector(0x1000);
	}
}
