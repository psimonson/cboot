CFLAGS=-std=gnu89 -Wall -Werror -Wno-unused-function -march=i386 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -nostdinc -m16 -c
LDFLAGS=--nmagic -m elf_i386

.PHONY: all clean disk boot.bin io.sys deploy run
all: deploy

clean:
	rm -f *~ *.o *.out boot boot.bin io io.sys c.img

boot.o: boot.c
	$(CC) $(CFLAGS) -Os -o $@ $^

io.o: io.c
	$(CC) $(CFLAGS) -Os -o $@ $^

boot: boot.o
	$(LD) $(LDFLAGS) -T boot.ld -o $@ $^

io: io.o
	$(LD) $(LDFLAGS) -T io.ld -o $@ $^

boot.bin: boot
	objcopy -O binary $< $@

io.sys: io
	objcopy -O binary $< $@

disk:
	dd if=/dev/zero of=c.img bs=512 count=2880
	sudo losetup /dev/loop0 c.img
	sudo mkfs.vfat /dev/loop0
	sudo losetup -d /dev/loop0

deploy: boot io boot.bin io.sys disk
	dd if=boot.bin of=c.img bs=1 count=512 conv=notrunc
	dd if=io.sys of=c.img bs=1 seek=512 conv=notrunc

run: deploy
	qemu-system-i386 -fda c.img -boot a

