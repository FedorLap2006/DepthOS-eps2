#include "idt.h"
#include <depthos/string.h>
#include <io/console.h>


__cleanfunc void ll_isr_handler() {
	__asm__ volatile (
		"pusha\n"
		"push %ds\n"
		"push %es\n"
		"push %gs\n"
		"push %fs\n"
		"mov $0x10, %ax\n"
		"mov %ax, %ds\n"
		"mov %ax, %es\n"
		"mov %ax, %fs\n"
		"mov %ax, %gs\n"
		"call isr_handler\n"
		"pop %fs\n"
		"pop %gs\n"
		"pop %es\n"
		"pop %ds\n"
		"popa\n"
		"add $8, %esp\n"
		"iret"
	);
}
__cleanfunc void ll_irq_handler() {
	__asm__ volatile (
		"pusha\n"
		"push %ds\n"
		"push %es\n"
		"push %gs\n"
		"push %fs\n"
		"mov $0x10, %ax\n"
		"mov %ax, %ds\n"
		"mov %ax, %es\n"
		"mov %ax, %fs\n"
		"mov %ax, %gs\n"
		"call irq_handler\n"
		"pop %fs\n"
		"pop %gs\n"
		"pop %es\n"
		"pop %ds\n"
		"popa\n"
		"add $8, %esp\n"
		"iret"
	);
}

#define defi(n, h) 										\
	__cleanfunc void intr_##n(void)  {	\
		__asm__ volatile (								\
			"pushl $0x0\n"									\
			"pushl $"#n"\n"									\
			"jmp "#h"\n"										\
		); 																\
	}
#define defie(n, h) 									\
	__cleanfunc void intr_##n(void)  { 	\
		__asm__ volatile ( 								\
			"pushl $"#n"\n" 								\
			"jmp "#h"\n" 										\
		);																\
	}
//
// #define defi(n, h)                        \
// __cleanfunc void intr_##n(void) { 				\
// 	__asm__ volatile ("cli");               \
// 	kernel_console.print("OH YES");		      \
//   	__asm__ volatile ("pushl $0x0");      \
//   	__asm__ volatile ("pushl $" #n);      \
//   	__asm__ volatile ("pusha");           \
//   	__asm__ volatile ("push %ds");        \
//   	__asm__ volatile ("push %es");        \
//   	__asm__ volatile ("push %gs");        \
//   	__asm__ volatile ("push %fs");        \
//   	__asm__ volatile ("mov $0x10, %ax");  \
//   	__asm__ volatile ("mov %ax, %ds");    \
//   	__asm__ volatile ("mov %ax, %es");    \
//   	__asm__ volatile ("mov %ax, %fs");    \
//   	__asm__ volatile ("mov %ax, %gs");    \
//   	__asm__ volatile ("call " #h);        \
//   	__asm__ volatile ("pop %fs");         \
//   	__asm__ volatile ("pop %gs");         \
//   	__asm__ volatile ("pop %es");         \
//   	__asm__ volatile ("pop %ds");         \
//   	__asm__ volatile ("popa");            \
//   	__asm__ volatile ("add $8, %esp");    \
//   	__asm__ volatile ("sti");             \
//   	__asm__ volatile ("iret");            \
// }
//
// #define defie(n, h)                       \
// __cleanfunc void intr_##n(void) { \
//   	__asm__ volatile ("cli");             \
//   	kernel_console.print("OH YES 2");	    \
//   	__asm__ volatile ("pushl $" #n);      \
//   	__asm__ volatile ("pusha");           \
//   	__asm__ volatile ("push %ds");        \
//   	__asm__ volatile ("push %es");        \
//   	__asm__ volatile ("push %gs");        \
//   	__asm__ volatile ("push %fs");        \
//   	__asm__ volatile ("mov $0x10, %ax");  \
//   	__asm__ volatile ("mov %ax, %ds");    \
//   	__asm__ volatile ("mov %ax, %es");    \
//   	__asm__ volatile ("mov %ax, %fs");    \
//   	__asm__ volatile ("mov %ax, %gs");    \
//   	__asm__ volatile ("call " #h);        \
//   	__asm__ volatile ("pop %fs");         \
//   	__asm__ volatile ("pop %gs");         \
//   	__asm__ volatile ("pop %es");         \
//   	__asm__ volatile ("pop %ds");         \
//   	__asm__ volatile ("popa");            \
//   	__asm__ volatile ("add $8, %esp");    \
//   	__asm__ volatile ("sti");             \
//   	__asm__ volatile ("iret");            \
// }

void isr_handler(interrupt_env_t env);
void irq_handler(interrupt_env_t env);

#define i(n) defi(n, ll_isr_handler)
#define ie(n) defie(n, ll_isr_handler)

#define i10(n)    \
  	i(n##1)       \
  	i(n##2)       \
  	i(n##3)       \
  	i(n##4)       \
  	i(n##5)       \
  	i(n##6)       \
  	i(n##7)       \
  	i(n##8)       \
		i(n##9)
#define ie10(n)    \
  	ie(n##1)       \
  	ie(n##2)       \
  	ie(n##3)       \
  	ie(n##4)       \
  	ie(n##5)       \
  	ie(n##6)       \
  	ie(n##7)       \
  	ie(n##8)       \
  	ie(n##9)
// 32 - 47
		i (0)
	  i10 ()
  	i10 (1)
  	i10 (2)
  	i   (30)
  	i   (31)
  	i   (48)
  	i   (49)
  	i10 (5)
  	i10 (6)
  	i10 (7)
  	i10 (8)
  	i10 (9)
  	i10 (10)
  	i10 (11)
		i10 (12)
		i10 (13)
		i10 (14)
		i10 (15)
		i10 (16)
		i10 (17)
		i10 (18)
		i10 (19)
		i10 (20)
		i10 (21)
		i10 (22)
		i10 (23)
		i10 (24)
		i		(250)
		i 	(251)
		i		(252)
		i 	(253)
		i 	(254)
		i		(255)
  	// i   (120)
  	// i   (121)
  	// i  (122)
  	// i   (123)
  	// i   (124)
  	// i   (125)
  	// i   (126)
  	// i   (127)
	  // i	(128)
#undef i
#undef ie
#undef i10
#undef ie10

#define i(n) defi(n, ll_irq_handler)
#define ie(n) defie(n, ll_irq_handler)
  	i   (32)
  	i   (33)
  	i   (34)
  	i   (35)
  	i   (36)
  	i   (37)
  	i   (38)
  	i   (39)
  	i   (40)
  	i   (41)
  	i   (42)
  	i   (43)
  	i   (44)
  	i   (45)
  	i   (46)
  	i   (47)
#undef i
#undef ie

#undef defi
#undef defie

idt_entry_t IDT[IDT_SIZE];
static interrupt_handler_t IDT_ihandlers[IDT_SIZE];

uint64_t make_idtr(void* base, uint16_t size);

void isr_handler(interrupt_env_t env) {
	// kernel_console.print("Recieved interrupt: ");
	// console_put_number(env.intr_num, 0x10);
	// if(env.intr_num >= )
	if(IDT_ihandlers[env.intr_num]) {
		IDT_ihandlers[env.intr_num](env);
		return;
	}
	// kernel_console.print("\n");
}
void irq_handler(interrupt_env_t env) {}

void __interrupt_default_handler(interrupt_env_t env) {}

void _idt_init() {
	memset(IDT, 0, sizeof(IDT));
	memset(IDT_ihandlers, 0, sizeof(IDT_ihandlers));
#define i(n) \
	idt_set_entry(n, idt_einfo_toentry((idt_einfo_t){ .kind = IDTEK_INTR32, .value = { .intr32 = { .base = (uint32_t)intr_##n, .ksel = 0x8, .present = true, .storage_seg = false, .dpl = 0x0 }  } }));
	//	idt_einfo_t idt_entry_##n##_inst = { .kind = IDTEK_INTR32, .value = { .intr32 = { .base = (uint32_t)intr_##n, .ksel = 0x8, .present = true, .storage_seg = false, .dpl = 0x0 }  } };
/*#define i(n) \
	idt_einfo_t idt_entry_##n##_inst;
	idt_entry##n##_inst.kind = IDTEK_INT32;
	idt_entry##n##_inst.value.intr32.base = (uint32_t)int32*/
#define i10(n)     	\
	i (n##1);      		\
	i (n##2);      		\
	i	(n##3);       	\
  i	(n##4);       	\
  i	(n##5);       	\
  i	(n##6);       	\
 	i	(n##7);      		\
  i	(n##8);		     	\
  i	(n##9)
		i (0);
  	i10	();
  	i10	(1);
  	i10	(2);
  	i10	(3);
  	i10	(4);
  	i10	(5);
  	i10	(6);
  	i10	(7);
  	i10	(8);
  	i10	(9);
  	i10	(10);
  	i10	(11);
		i10 (12);
		i10 (13);
		i10 (14);
		i10 (15);
		i10 (16);
		i10 (17);
		i10 (18);
		i10 (19);
		i10 (20);
		i10 (21);
		i10 (22);
		i10 (23);
		i10 (24);
		i		(250);
		i 	(251);
		i		(252);
		i 	(253);
		i 	(254);
		i		(255);
#undef i
#undef ie
// #define print_i64(n, radix) \
//   kernel_console.print("{ [0 - 32] ("); \
//   console_put_number((uint64_t)((uint64_t)n & (uint64_t)0xFFFFFFFF), radix); \
//   kernel_console.print(") [32 - 64] ("); \
//   console_put_number((uint64_t)((uint64_t)n >> (uint64_t)32), radix); \
//   kernel_console.print(") }");
//   // 	kernel_console.print("IDT 0x80 ADDR: ");
// 	// console_put_number((uint32_t)intr_127, 0x10);
// 	// kernel_console.print("\nIDT 0x80 EINFO: ");
// 	//
// 	// print_i64(idt_einfo_toentry((idt_einfo_t){ .kind = IDTEK_INTR32, .value = { .intr32 = { .base = (uint32_t)intr_127, .ksel = 0x8, .present = true, .storage_seg = false, .dpl = 0x0 }  } }), 0x10);
// 	// kernel_console.print("\n");
//   // 	for (int i = 0; i < IDT_SIZE; i++) {
//   // 		register_interrupt(i, __interrupt_default_handler);
//   // 	}
// 	// uint64_t idtr = 0;
// 	// idtr = make_idtr(IDT, IDT_SIZE);
// 	// kernel_console.print("IDT base: ");
// 	// console_put_number((uint32_t)IDT, 16);
// 	// kernel_console.print("\nIDTR: ");
// 	// print_i64(idtr, 10);
// 	// kernel_console.put('\n');
// 	//	__asm__ volatile("lidt %0" : :"m"(idtr));
//
// 	kernel_console.print("IDT Initialization...\n");
//
// 	kernel_console.print("IDT 0x80 [");
// 	console_put_number((uint32_t)intr_128, 0x10);
// 	kernel_console.print("] -> ");
// 	// kernel_console.print("")
// 	print_i64(idt_einfo_toentry((idt_einfo_t){
// 		.kind = IDTEK_INTR32,
// 		.value = {
// 			.intr32 = {
// 				.base = (uint32_t)intr_128,
// 				.ksel = 0x8,
// 				.present = true,
// 				.storage_seg = false,
// 				.dpl = 0,
// 			}
// 		}
// 	}), 0x10);
// 	kernel_console.print("\n");
// 	kernel_console.print("Actual IDT 0x80: [");
// 	print_i64(idt_get_entry(128), 0x10);
// 	kernel_console.print("]\n");
	for (int i = 0; i < IDT_SIZE; i++) {
		register_interrupt(i, __interrupt_default_handler);
	}

	uint64_t idtr = make_idtr(IDT, IDT_SIZE);
	if(idtr == 0) {
		kernel_console.print("[ERROR] IDT IS NULL");
		return;
	}
	__asm__ volatile("lidt %0" : :"m"(idtr));
	// kernel_console.print("")
// #undef print_i64
	kernel_console.print("IDT initialized\n");
}

idt_einfo_t idt_entry_toeinfo(idt_entry_t entry) {
	idt_einfo_t info;

	switch(entry & 0xF0000000000) { /* idt entry kind */
	case IDTEK_INTR16:
		break;
	case IDTEK_INTR32:
		info.kind = IDTEK_INTR32;
#define v info.value.intr32
		v.base = (uint32_t)(entry & 0x10);
		v.base |= (uint32_t)((entry >> 0x30) << 16);
		v.ksel = (uint16_t)((entry >> 0x10) & 0x10);
		v.storage_seg = (uint8_t)((entry >> 0x2C) & 0x1);
		v.present = (uint8_t)((entry >> 0x2F) & 0x1);
		v.dpl = (uint8_t)((entry >> 0x2D) & 0x3);
#undef v
		break;
	case IDTEK_TRAP16:
		info.kind = IDTEK_TRAP16;
		break;
	case IDTEK_TRAP32:
		info.kind = IDTEK_TRAP32;
		break;
	case IDTEK_TASK32:
		info.kind = IDTEK_TASK32;
		break;
	}
	return info;
}
idt_entry_t idt_einfo_toentry(idt_einfo_t einfo) {
	idt_entry_t entry;
	entry = 0;
	switch(einfo.kind) {
	case IDTEK_INTR32:
    entry = make_idt_entry(einfo.value.intr32.present, einfo.value.intr32.base, einfo.value.intr32.dpl, einfo.value.intr32.storage_seg, (int)einfo.kind, einfo.value.intr32.ksel);
		/*entry |= einfo.value.intr32.base & 0xFFFF;*/
      /*entry |= (uint64_t)((uint64_t)(einfo.value.intr32.ksel) << (uint64_t)16);*/
      /*entry |= (uint64_t)((uint64_t)(einfo.kind) << (uint64_t)40);*/
      /*entry |= (uint64_t)((uint64_t)(einfo.value.intr32.storage_seg & 0x1) << (uint64_t)44);*/
      /*entry |= (uint64_t)((uint64_t)(einfo.value.intr32.dpl & 0x3) << (uint64_t)45);*/
      /*entry |= (uint64_t)((uint64_t)(einfo.value.intr32.present & 0x1) << (uint64_t)47);*/
      /*entry |= (uint64_t)((uint64_t)((einfo.value.intr32.base & 0xFFFF0000) >> 16) << (uint64_t)48);*/
  		break;
  	default:
  		break;
  	}
	return entry;
}

void idt_set_entry(uint8_t index, idt_entry_t data) {
	if(index >= IDT_SIZE) return;
	IDT[index] = data;
}

idt_entry_t idt_get_entry(uint8_t index) {
	if(index >= IDT_SIZE) return 0;
	return IDT[index];
}

uint64_t make_idtr(void* idt, uint16_t size) {
  if(size == 0) return 0;
  size *= sizeof(idt_entry_t);
  size--;
  return (uint64_t)(
      (uint64_t)size
      | (
        ((uint64_t)(uint32_t)idt) << (uint64_t)16
      )
  );
}
void register_interrupt(uint8_t index, interrupt_handler_t h) {
	if(index >= IDT_SIZE) return;
	IDT_ihandlers[index] = h;
}
