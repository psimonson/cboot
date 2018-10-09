#ifndef _DISK_H_
#define _DISK_H_

#ifndef _IO_H_
#include "io.h"
#endif

#define CFLAG_SET 0x01
#define CFLAG_NOT 0x00

/* read_disk:  reads sectors from floppy drive (disk 0) */
static char
read_disk(unsigned char start_sector,
		unsigned char sector_count, unsigned char drive)
{
	unsigned char cf, reset;
	cf = 0;
	__asm__ __volatile__ (
		"int $0x13; \
		setc %0;"
		: "=r"(cf)
		: "a"(0x0200 | sector_count), "b"(0x1000),
		  "c"(0x0000 | start_sector), "d"(0x0000 | drive)
	);
	if (cf) {
		reset = 1;
		print("Could not read the disk"
			" sector.\r\n");
		while (reset)
			__asm__ __volatile__(
				"mov $0x00, %%ah;"
				"int $0x13;"
				"or %%ah, %%ah;"
				"mov %%ah, %0;"
				: "=r"(reset)
				:
			);
	} else {
		print("Sector read.\r\n");
		__asm__ ("cli");
		__asm__ __volatile__ (
			"mov %%ss, %%ax; \
			mov $0x1000, %%sp; \
			jmp $0x0000, $0x1000;"
			:
			: "a"(0x0000)
		);
		__asm__ ("sti");
	}
	return cf;
}

#endif
