#ifndef _FAT_H_
#define _FAT_H_

#ifndef _IO_H_
#include "io.h"
#endif

/* fat12 and fat16 extended boot data */
typedef struct fat_ext {
	unsigned char      drive_num;     /* drive number (0x80) */
	unsigned char      reserved1;     /* reserved */
	unsigned char      boot_sig;      /* ext. boot signature (0x29) */
	unsigned char      vol_id[4];     /* volume ID number */
	unsigned char      vol_label[11]; /* volume label */
	unsigned char      fs_type[8];    /* fs type (FAT12 or FAT16) */
}__attribute__((packed)) fat_ext_t;

/* fat boot sector data */
typedef struct fat {
	unsigned char oem_name[8];    /* OEM name and version */
	unsigned char bpb[19];        /* BIOS parameter block */
	unsigned char drive_num;      /* drive number (0x80) */
	unsigned char boot_code[479]; /* pad to 512b */
	unsigned char sig0;           /* sig0 55 */
	unsigned char sig1;           /* sig1 aa */
#define BOOTSIG0 0x55
#define BOOTSIG1 0xaa
}__attribute__((packed)) fat_t;

/* init_fat:  initialize the fat disk */
static void
init_fat(fat_t *fat)
{
	fat_ext_t bpb;

	/* initialize bpb */
	bpb.drive_num = 0x00;
	bpb.reserved1 = 0x00;
	bpb.boot_sig = 0x29;
	strcpy((char*)bpb.vol_id, "ABCD");
	strcpy((char*)bpb.vol_label, "PHILOS 1.0 ");
	strcpy((char*)bpb.fs_type, "FAT12   ");

	/* initialize fat */
	strcpy((char*)fat->oem_name, "mkdosfs ");
	memcpy(fat->bpb, &bpb, sizeof bpb);
	fat->drive_num = 0x00;
}

#endif
