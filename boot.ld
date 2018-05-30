ENTRY (main)
OUTPUT_FORMAT (binary)
SECTIONS
{
  . = 0x7c00;

  .cseg :
  {
    *(.text);
  }

  .dseg :
  {
    *(.rodata);
  }

  .sig : AT(0x7dfe)
  {
    SHORT(0xAA55);
  }

  /DISCARD/ :
  {
    *(.eh_frame);
		*(.comment);
		*(.note.GNU-stack);
  }
}
