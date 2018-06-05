#ifndef _DISK_H_
#define _DISK_H_

#ifndef _MYBOOL_H_
#include "mybool.h"
#endif

/* read_disk:  reads sectors from floppy drive (disk 0) */
static bool_t
read_disk (unsigned char start_sector,
		unsigned char sector_count, unsigned char drive)
{
	bool_t ret = true;
	__asm__ goto (
		"int $0x13; jc %l4" :
		: "a"(0x0200 | sector_count), "b"(0x1000),
		  "c"(0x0000 | start_sector), "d"(0x0000 | drive)
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

/* setup_stack: setup stack and jump to location */
static void
setup_stack (unsigned short int __offset)
{
		__asm__ ("cli");
		__asm__ __volatile__ (
			"mov %%ss, %%ax; \
			movw %1, %%sp; \
			jmpw $0x0000, %1"
			:
			: "a"(0x0000), "X"(__offset)
		);
		__asm__ ("sti");
}

#endif
