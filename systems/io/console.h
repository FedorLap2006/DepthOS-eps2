#pragma once

#include <depthos/stddef.h>

typedef struct kernel_console {
	uint8_t x,y;
	uint16_t sx, sy;
	uint8_t last_char;

	// ------ methods ------


	// input

	void (*put)(char);
	void (*print)(char*);

	// common

	void (*flush)();
	// void (*movec)(uint8_t, uint8_t);
	void (*clear)();

	// output

	char* (*readline)();
	char  (*readchar)();
	char* (*readstring)(int);

}console_t;

void console_put_char(char ch);
void console_put_str(char* str);

char* console_readline();
char console_readchar();
char* console_readstring(int n);

extern console_t kernel_console;