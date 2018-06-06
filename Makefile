CC=cc
CFLAGS=-std=c89 -Wall -Werror -Wno-unused-function -march=i386 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -nostdinc -m16 -c
LDFLAGS=-static -nostdlib --nmagic -m elf_i386

.PHONY: all clean disk boot.bin io.sys deploy run
all: boot io

clean:
	rm -f *~ *.o *.elf boot.bin io.sys c.img

%.o: %.c
	$(CC) $(CFLAGS) -Os -o $@ $^

boot: boot.o
	$(LD) $(LDFLAGS) -T boot.ld -o $@.elf $^
	objcopy -O binary $@.elf $@.bin

io: io.o
	$(LD) $(LDFLAGS) -T io.ld -o $@.elf $^
	objcopy -O binary $@.elf $@.sys

disk:
	dd if=/dev/zero of=c.img bs=512 count=2880

deploy: disk boot io
	dd if=boot.bin of=c.img bs=1 count=512 conv=notrunc
	dd if=io.sys of=c.img bs=1 seek=512 conv=notrunc

run: deploy
	qemu-system-i386 -fda c.img -boot a
