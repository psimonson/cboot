ENTRY(main);
SECTIONS
{
  . = 0x7C00;
  .text : AT(0x7C00)
  {
    *(.text);
  }
	.rodata :
	{
		*(.rodata);
	}
	.data :
	{
		*(.data);
	}
	.bss :
	{
		*(.bss);
	}
	. = 0x7dfe;
	.sig :
	{
		SHORT(0xaa55);
	}
  /DISCARD/ :
  {
		*(.note*);
		*(.iplt*);
		*(.igot*);
		*(.rel*);
		*(.comment);
		*(.note.GNU.stack);
		*(.eh_frame);
  }
}
