#include <depthos/stddef.h>
#include <io/console.h>



// unsigned short *videoMemory = (unsigned short*)0xB8000;
// void print_str(char* str) {

//   for (int i = 0; str[i] != '\0'; i++) {
//     videoMemory[i] = (videoMemory[i] & 0xFF00) | str[i];
//   }
// }

int kmain(int magic_number, void *multiboot_ptr) {

//	print_str("HELLO WORLD!");

	kernel_console.clear();
	kernel_console.put('1');
	kernel_console.print("\nhello world with my console!\n");
	kernel_console.print("\ttesting new line & tab\n");



	return 0;
}