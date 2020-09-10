#include <depthos/stddef.h>
#include <io/console.h>
#include <io/ports.h>
#include <apps/kdms.h>
#include <apps/kims.h>

void jump_protected() {
	kdms_std_init(); 	
	__asm__ volatile("jmp $0x8, $protected_mode_begin");
	__asm__ volatile("protected_mode_begin:");
	return;
}

static unsigned long int _pit_ticks = 0;
#define PIT_TPS 1000 // ticks per second
void timer_interrupt(kims_interrupt_env_t env) {
	// kernel_console.print("IRQ timer");
	
	// kernel_console.print("oh hello");

	// if(_pit_ticks % 1000000000 == 0) {
	// if(_pit_ticks % 1000000 == 0) {
	if(_pit_ticks % PIT_TPS == 0) { /* Do something */ }
	_pit_ticks++;
}

void initialise_pit(uint32_t freq) {
	uint16_t div = (uint16_t)(1193182 / (uint16_t)freq);
	// uint16_t div = (7159090 + 6/2) / (6 * freq);
	port_sendb(0x43, 0x36);

	port_sendb(0x40, div & 0xff);
	port_sendb(0x40, (div >> 8) & 0xff);
	kernel_console.print("[KERNEL] PIT is initialised\n");
}


/**
 * Kernel main
 * @param	magic_number  Magic number of the bootloader, helps get a kind of the bootloader
 * @param	multiboot_ptr Pointer to the multiboot bootloader payload
 */
void kmain(int magic_number, void *multiboot_ptr) {
	kernel_console.clear();
	kernel_console.print("Welcome to the DepthOS v2.0 VGA text-mode terminal\n");
	jump_protected();

	kims_disable_hwinterrupts();

	kims_std_init();

	// initialise_pit(1000000000); // - picosec
	// initialise_pit(1000000); // - microsec
	initialise_pit(1000);
	kims_register_ihandler(0x20, timer_interrupt, 0x0);
	
	kims_enable_hwinterrupts();

	while(1) {}
}
