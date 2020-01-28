ENTRY(_os_entry_point)

SECTIONS {
	. = 1M;

	.text : {
		*(.boot);
		*(.text*);
	}

	.data : {
		*(.data);
    *(.rdata*);
    *(.rodata*);
	}

	.bss : {
		*(.bss);
	}

  /DISCARD/ : {
    *(.eh_frame);
    *(.comment*);
  }
}