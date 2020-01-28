#include "console.h"
#include <depthos/stddef.h>
#include <io/ports.h>

#define calc_position(x, y, sx) (x + y * sx)

#define calc_color(bgc, fgc) ((bgc << 4) | (fgc & 0x0F))

unsigned short *video_memory_ptr = (unsigned short*)0xB8000;

void console_flush_cursor() {
	uint16_t pos = calc_position(kernel_console.x, kernel_console.y, kernel_console.sx);
	port_sendb(0x3D4, 14);
	port_sendb(0x3D5, pos >> 8);
	port_sendb(0x3D4, 15);
	port_sendb(0x3D5, pos);
}

void console_flush_screen() {
	if(kernel_console.x >= kernel_console.sx) {
		kernel_console.y++;
		kernel_console.x = 0;
	}

	if(kernel_console.y >= kernel_console.sy) {
		for(int i = 0; i < (kernel_console.sy - 1) * kernel_console.sx; i++) {
			video_memory_ptr[i] = video_memory_ptr[i + kernel_console.sx];
		}

		for(int i = (kernel_console.sy - 1) * kernel_console.sx; i < kernel_console.sy * kernel_console.sx; i++) {
			video_memory_ptr[i] = 0x20 | calc_color(0, 15);
		}

		kernel_console.y--;
		//kernel_console.x = 0;	
	}

	console_flush_cursor();
}

void console_clear() {
	uint8_t ch = 0x20 | calc_color(0, 15);

	for(int i = 0; i < kernel_console.sx * kernel_console.sy; i++) {
		video_memory_ptr[i] = ch;
	}

	kernel_console.x = 0;
	kernel_console.y = 0;
	console_flush_cursor();
}

void console_put_char(char ch) {

	switch (ch) {
	case '\n':
		kernel_console.y++;
		kernel_console.x = 0;
		break;
	case '\r':
		kernel_console.x = 0;
		break;
	case (char)0x08:
		if(kernel_console.x) kernel_console.x--;
		else {
			kernel_console.y--;
			kernel_console.x = kernel_console.sx - 1;
		}
		break;
	case (char)0x09:
		kernel_console.x += 4;
		kernel_console.x &= ~(4 - 1);
		break;
	default:
		if(ch < ' ') break;
		video_memory_ptr[calc_position(kernel_console.x, kernel_console.y, kernel_console.sx)] = ch | (calc_color(0, 15) << 8);
		kernel_console.x++;
		break;
	}

	kernel_console.flush();
}

void console_put_str(char *str) {
	int i = 0;
	while(str[i])
		console_put_char(str[i++]);
}

console_t kernel_console = {
	// state
	.x = 0, .y = 0,
	.sx = 80, .sy = 25,
	.last_char = '\0',

	// methods

	.put = console_put_char,
	.print = console_put_str,

	.flush = console_flush_screen,
	.clear = console_clear
};