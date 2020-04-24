#include <depthos/stddef.h>
#include <io/console.h>
#include <apps/gdt.h>
//#include <apps/idt.h>

// extern void idt_init();
extern void _gdt_init();
// extern void _idt_init();

// unsigned short *videoMemory = (unsigned short*)0xB8000;
// void print_str(char* str) {

//   for (int i = 0; str[i] != '\0'; i++) {
//     videoMemory[i] = (videoMemory[i] & 0xFF00) | str[i];
//   }
// }


/*
void test_syscall(struct kernel_interrupt_environment env) {
	kernel_console.print("IDT WOOOOORKING NORMALLY!!!\n");
//  while(1) {}
}

__attribute__((noreturn)) void gprot_fault(struct kernel_interrupt_environment env) {
  kernel_console.print("\n[Panic at ");
  console_put_number(env.eip, 16);
  kernel_console.print("]\n\tReason: General Protection Fault");
  kernel_console.print("\n\tError code: ");
  console_put_number(env.interrupt_err_code, 16);
  while(1) {}
}*/

void jump_protected() {
  _gdt_init();
  __asm__ volatile("jmp $0x8, $protected_mode_begin");
  __asm__ volatile("protected_mode_begin:");
  return;
}

int kmain(int magic_number, void *multiboot_ptr) {
  kernel_console.clear();
/*
//	print_str("HELLO WORLD!");
  kernel_console.clear();
	kernel_console.print("Welcome to the DepthOS v2.0 shell\n");
	kernel_console.print("[INFO] Initialising GDT...\n");
	//_gdt_init();
	kernel_console.print("[OK] GDT Initialised\n");

	kernel_console.print("[INFO] Initialising IDT...\n");
	_idt_init();
	kernel_console.print("[OK] IDT Initialised\n");

	register_interrupt_handler(0xD, gprot_fault);
	register_interrupt_handler(15, test_syscall);
  register_interrupt_handler(16, test_syscall);
  kernel_console.print("hello!");
	__asm__ volatile("int $15");
  __asm__ volatile("int $16");
	kernel_console.print("If you read this, then IDT works\n");

	return 0;*/
  
  jump_protected();

  kernel_console.print("Hello world after GDT load");

}
