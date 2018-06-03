#!/bin/sh

write_disk()
{
	if [ -b /dev/$1 ]; then
		if grep "/dev/$1" /etc/mtab > /dev/null 2>&1; then
			echo "Please unmount the drive first." && exit 1
		else
			sudo dd if=boot.bin of=/dev/$1 bs=1 count=512 seek=0 skip=0 || exit 1
			sudo dd if=io.sys of=/dev/$1 bs=1 seek=512 skip=0 || exit 1
		fi
	else
		echo "Block device /dev/$1 doesn't exist." && exit 1
	fi
	echo "Block device successfully written to /dev/$1!"
	exit 0
}

case "$1" in
	write)
		write_disk "$2"
		;;
	*)
		echo "Usage: %s write <device>"
		;;
esac
