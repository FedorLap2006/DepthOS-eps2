ENTRY(_os_entry_point)

SECTIONS {
	. = 1M;

	.text : {
		_text_section_space_beg = .;
		*(.boot);
		*(.text*);
		_text_section_space_end = .;
	}

	.data : {
		_data_section_space_beg = .;
		*(.data);
    *(.rdata*);
    *(.rodata*);
    _data_section_space_end = .;
	}

	.bss : {
		_bss_section_space_beg = .;
		*(.bss);
		_bss_section_space_end = .;
	}
	_kernel_end = .;

  /DISCARD/ : {
    *(.eh_frame);
    *(.comment*);
  }
}