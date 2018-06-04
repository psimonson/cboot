ENTRY(main);
SECTIONS
{
  . = 0x7C00;
	.text : AT(0x7C00)
	{
		*(.text);
	}
	.data :
	{
		*(.bss);
		*(.data);
		*(.rodata);
	}
	. = 0x7DFE;
	.sig : AT(0x7DFE)
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
