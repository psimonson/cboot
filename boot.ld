ENTRY(main);
SECTIONS
{
  . = 0x7C00;
	.data :
	{
		*(.bss);
		*(.data);
		*(.rodata);
	}
	.text :
	{
		*(.text);
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
