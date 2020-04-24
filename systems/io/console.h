#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <depthos/stddef.h>

// structure for storaging console interface and state
typedef struct kernel_console {
	uint8_t x,y;
	uint16_t sx, sy;
	uint8_t last_char;

	// output
	void (*put)(char);
	void (*print)(char*);

	// common
	void (*flush)();
	// void (*movec)(uint8_t, uint8_t);
	void (*clear)();

	// input
	char* (*readline)();
	char  (*readchar)();
	char* (*readstring)(int);

}console_t;
// default kernel console methods
void console_put_char(char ch);
void console_put_str(char* str);

char* console_readline();
char console_readchar();
char* console_readstring(int n);

void console_put_number(uint32_t v, uint8_t radix);

extern console_t kernel_console;
#endif
