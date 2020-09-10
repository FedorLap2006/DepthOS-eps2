#include <apps/kims.h>
#include <depthos/stddef.h>
#include <io/console.h>
#include <io/ports.h>

static kims_table_t kims_default_table;
kims_interrupt_handler_t kims_default_table_interrupts_data[KIMS_STD_INTR_HANDLERS_TABLE_SIZE];
kims_interrupt_descriptor_t kims_default_table_native_data[KIMS_STD_INTR_DESCRIPTORS_TABLE_SIZE];

kims_table_t kims_current_table = { .native = { .pointer = NULL }, .interrupts = { .pointer = NULL } };
static kims_pic_config_t kims_current_pic_config;

void kims_default_ihandler(kims_interrupt_env_t env) {

}

void kims_interrupt_handler(kims_interrupt_env_t env) {
	if (env.intr_num >= kims_current_table.interrupts.size) return;
	// kernel_console.print("kims_interrupt_handler: ");
	// console_put_number(env.intr_num, 10);
	// kernel_console.print("\n");
	kims_current_table.interrupts.pointer[env.intr_num].handler(env);
}

void kims_hwinterrupt_handler(kims_interrupt_env_t env) {
	if(env.intr_num < 0x20 || env.intr_num > 0x2F) return;
	kims_interrupt_handler(env);
	// kernel_console.print("kims_hwinterrupt_handler: ");
	// console_put_number(env.intr_num, 10);
	// kernel_console.print("\n");
	if(env.intr_num >= 0x28) {
		if(!kims_current_pic_config.auto_eoi) port_sendb(0xA0, 0x20);
		// port_sendb(0xA0, 0x20);
	}
	if(!kims_current_pic_config.auto_eoi) port_sendb(0x20, 0x20);
	// port_sendb(0x20, 0x20);
}

void kims_enable_hwinterrupts() {
	__asm__ volatile ("sti");
}

void kims_disable_hwinterrupts() {
	__asm__ volatile ("cli");
}


static void pic_iowait() { __asm__ volatile("outb %%al, $0x80" : :"a"(0)); }


#define PIC_PRIMARY_CMD_PORT 0x20
#define PIC_SECONDARY_CMD_PORT 0x20
#define PIC_PRIMARY_DATA_PORT 0x21
#define PIC_SECONDARY_DATA_PORT 0xA1

void kims_init_pic(struct kims_pic_config cfg) {
	uint8_t primary_mask, secondary_mask;
	/**
	 * Saving old IRQs mask
	 */

	if(cfg.dirty_mask) {
		primary_mask = port_readb(PIC_PRIMARY_DATA_PORT) | (~(cfg.mask) & 0xFF);
		secondary_mask = port_readb(PIC_SECONDARY_DATA_PORT) | (~(cfg.mask) >> 0x8);

	} else {
		primary_mask = ~(cfg.mask & 0xFF);
		secondary_mask = ~(cfg.mask >> 0x8);
	}

	/**
	 * Remaping interrupts table
	 */

	port_sendb(PIC_PRIMARY_CMD_PORT, 0x11); /* Initialisation signal + ICW4 mode [primary] */
	if(cfg.iowait_mode) pic_iowait();
	port_sendb(PIC_SECONDARY_CMD_PORT, 0x11); /* Initialisation signal + ICW4 mode [secondary] */
	if(cfg.iowait_mode) pic_iowait();

	port_sendb(PIC_PRIMARY_DATA_PORT, cfg.primary_offset); /* Interrupts offset [primary] */
	if(cfg.iowait_mode) pic_iowait();
	port_sendb(PIC_SECONDARY_DATA_PORT, cfg.secondary_offset); /* Interrupts offset [secondary] */
	if(cfg.iowait_mode) pic_iowait();

	port_sendb(PIC_PRIMARY_DATA_PORT, cfg.sconn_irq_line); /* IRQ lines where secondary controller is connected [primary] */
	if(cfg.iowait_mode) pic_iowait();
	port_sendb(PIC_SECONDARY_DATA_PORT, cfg.sec_irq_line_num); /* IRQ line number where secondary controller is connected [secondary] */
	if(cfg.iowait_mode) pic_iowait();

	port_sendb(PIC_PRIMARY_DATA_PORT, (uint8_t)(0
		| ((cfg.mp_mode & 0x1) << 0)
		| ((cfg.auto_eoi & 0x1) << 1)
		| ((cfg.bufmode & 0x1) << 2)
		| ((cfg.ps_bufmode & 0x1) << 3)
		| ((cfg.sfn_mode & 0x1) << 4)));
	if(cfg.iowait_mode) pic_iowait();
	port_sendb(PIC_SECONDARY_DATA_PORT, (uint8_t)(0
		| ((cfg.mp_mode & 0x1) << 0)
		| ((cfg.auto_eoi & 0x1) << 1)
		| ((cfg.bufmode & 0x1) << 2)
		| ((cfg.ps_bufmode & 0x1) << 3)
		| ((cfg.sfn_mode & 0x1) << 4)));
	if(cfg.iowait_mode) pic_iowait();

	port_sendb(PIC_PRIMARY_DATA_PORT, primary_mask);
	if(cfg.iowait_mode) pic_iowait();
	port_sendb(PIC_SECONDARY_DATA_PORT, secondary_mask);
	if(cfg.iowait_mode) pic_iowait();

	kims_current_pic_config = cfg;
}

static struct kims_pic_config default_pic_config = {
	.dirty_mask = false,
	.iowait_mode = true,
	.sfn_mode = false,
	.bufmode = false,
	.ps_bufmode = false,
	.auto_eoi = false,
	.mp_mode = true,
	.primary_offset = 0x20,
	.secondary_offset = 0x28,
	.sec_irq_line_num = 0x2,
	.sconn_irq_line = 0x4,
	.mask = (uint16_t)0x1, // IRQ0 (PIT)
};

/*
void init_pic() {
	port_sendb(0x21, 0xff);
	port_sendb(0xA1, 0xff);

	port_sendb(0x20, 0x11);
	port_sendb(0x21, 0x20);
	port_sendb(0x21, 0x04);
	port_sendb(0x21, 0x03);

	port_sendb(0xA0, 0x11);
	port_sendb(0xA1, 0x28);
	port_sendb(0xA1, 0x02);
	port_sendb(0x21, 0x03);

	port_sendb(0x21, 0xfe);
	port_sendb(0xA1, 0xff);
}*/

void kims_std_init() {
	kims_default_table.interrupts.pointer = kims_default_table_interrupts_data;
	kims_default_table.native.pointer = kims_default_table_native_data;
	kims_default_table.interrupts.size = KIMS_STD_INTR_HANDLERS_TABLE_SIZE;
	kims_default_table.native.size = KIMS_STD_INTR_DESCRIPTORS_TABLE_SIZE;
	kims_switch_tbl(kims_default_table, false);
	kims_init_pic(default_pic_config);
#include "hbkims.h"
	for(int i = 0; i < 255; i++) {
		kims_set_interrupts_entry(i, (kims_interrupt_handler_t){
			.handler = kims_default_ihandler,
			.ipl = 0x0
		});
	}
	kims_switch_tbl(kims_default_table, true);
	kernel_console.print("[KERNEL] KIMS is initialised\n");
}

kims_table_t kims_switch_tbl(kims_table_t tbl, bool reload) {

	static kims_table_t tmp;
	static uint64_t idtr_v;
	tmp = kims_current_table;
	kims_current_table = tbl;
	if (reload) {
		idtr_v = (uint64_t)(0x0ull
			| (uint16_t)(
				tbl.native.size > 0 ?
					tbl.native.size * sizeof(kims_interrupt_descriptor_t) - 1
					: 0
			)
			| (uint64_t)((uint64_t)(uint32_t)tbl.native.pointer << 0x10)
		);

		__asm__ volatile ("lidt %0" : :"m"(idtr_v));
	}
	return tmp;
}

void kims_register_ihandler(uint32_t index, void (*handler)(kims_interrupt_env_t), uint8_t ipl) {
	kims_current_table.interrupts.pointer[index] = (kims_interrupt_handler_t) {
		.handler = handler,
		.ipl = ipl,
	};
	return;
}

kims_interrupt_descriptor_t kims_get_native_entry(uint32_t index) {
	if(!kims_current_table.native.pointer || index >= kims_current_table.native.size) return 0;
	return kims_current_table.native.pointer[index];
}
kims_interrupt_descriptor_t kims_set_native_entry(uint32_t index, kims_interrupt_descriptor_t ev) {
	if(!kims_current_table.native.pointer || index >= kims_current_table.native.size) return 0;
	static kims_interrupt_descriptor_t tmp;
	tmp = kims_current_table.native.pointer[index];
	kims_current_table.native.pointer[index] = ev;
	return tmp;
}


kims_interrupt_handler_t kims_get_interrupts_entry(uint32_t index) {
	if(!kims_current_table.interrupts.pointer || index >= kims_current_table.interrupts.size) return (kims_interrupt_handler_t){};
	return kims_current_table.interrupts.pointer[index];
}

kims_interrupt_handler_t kims_set_interrupts_entry(uint32_t index, kims_interrupt_handler_t ev) {
	if(!kims_current_table.interrupts.pointer || index >= kims_current_table.interrupts.size) return (kims_interrupt_handler_t){};
	static kims_interrupt_handler_t tmp;
	tmp = kims_current_table.interrupts.pointer[index];
	kims_current_table.interrupts.pointer[index] = ev;
	return tmp;
}

/*
kims_native_entry_info_t kims_nentry_toeinfo(kims_native_table_entry_t entry) {
	kims_native_entry_info_t einfo = { .values = { .intr32 = { .base = 0x0, .ksel = 0x0, .storage_seg = false, .present = false, .ipl = 0x0 } } };
	kernel_console.print("");
	// console_put_number(entry & 0xF0000000000, 0x16);
	switch((entry & 0xF0000000000) >> 0x28) {
	case KIMS_TEK_INTR16: case KIMS_TEK_TASK32: case KIMS_TEK_TRAP16: case KIMS_TEK_TRAP32:
		break;
	case KIMS_TEK_INTR32:
		kernel_console.print("intr32\n");
		einfo.values.intr32.base = (uint32_t)(entry & 0x10) | (uint32_t)((entry >> 0x30) << 0x10);
		einfo.values.intr32.ksel = (uint16_t)((entry >> 0x10) & 0x10);
		einfo.values.intr32.storage_seg = (uint8_t)((entry >> 0x2C) & 0x1);
		einfo.values.intr32.present = (uint8_t)((entry >> 0x2F) & 0x1);
		einfo.values.intr32.ipl = (uint8_t)((entry >> 0x2D) & 0x3);
		break;
	}
	return einfo;
}

 */

/*
 * #define make_kims_native_table_entry(P, BASE, IPL, S, TYPE, KSEL)		             \
 ( (uint64_t)(0x0ULL		                                             *             \
 | ((uint64_t)((uint64_t)BASE & 0xFFFF))		                                   \
 | ((uint64_t)(((uint64_t)KSEL & 0xFFFF) << (uint64_t)16))		                 \
 | ((uint64_t)((uint64_t)(TYPE & 0xF) << (uint64_t)40))		                    \
 | ((uint64_t)((uint64_t)(S & 0x1) << (uint64_t)44))		                       \
 | ((uint64_t)((uint64_t)(IPL & 0x3) << (uint64_t)45))		                     \
 | ((uint64_t)((uint64_t)(P & 0x1) << (uint64_t)47))		                       \
 | ((uint64_t)((uint64_t)(BASE >> 16) << (uint64_t)48))		                    \
 ))
 #define make_kims_native_table_intr32_entry(BASE, IPL) \
 make_kims_native_table_entry(1, BASE, IPL, 0, KIMS_TEK_INTR32, 0x8)*/

kims_interrupt_descriptor_t kims_convert_dinfo_to_desc(kims_interrupt_descriptor_info_t dinfo) {
	switch (dinfo.kind) {
		case KIMS_IDK_INTR16:
		case KIMS_IDK_TRAP16:
		case KIMS_IDK_TRAP32:
		case KIMS_IDK_TASK32:
			break;
		case KIMS_IDK_INTR32:
#define dival dinfo.v.intr32
			return (kims_interrupt_descriptor_t)(0x0ull
				| (uint64_t)(uint16_t)dival.base
				| (uint64_t)((uint64_t)(uint16_t)dival.ksel << 0x10)
				| (uint64_t)((uint64_t)(uint64_t)dinfo.kind << 0x28)
				| (uint64_t)((uint64_t)(dival.storage_seg & 0x1) << 0x2C)
				| (uint64_t)((uint64_t)(uint8_t)(dival.dpl & 0x3) << 0x2D)
				| (uint64_t)((uint64_t)(dival.present & 0x1) << 0x2F)
				| (uint64_t)((uint64_t)(uint16_t)(dival.base >> 0x10) << 0x30)
			);
#undef dival
		default:
			return 0;
	}
}
kims_interrupt_descriptor_info_t kims_convert_desc_to_dinfo(kims_interrupt_descriptor_t desc) {
	kims_interrupt_descriptor_kind_t kind = (kims_interrupt_descriptor_kind_t)((desc & 0xF0000000000) >> 0x28);
	switch(kind) {
		case KIMS_IDK_INTR16:
		case KIMS_IDK_TRAP16:
		case KIMS_IDK_TRAP32:
		case KIMS_IDK_TASK32:
			break;
		case KIMS_IDK_INTR32:
			return (kims_interrupt_descriptor_info_t){
				.kind = KIMS_IDK_INTR32,
				.v = {
					.intr32 = {
						.base = (uint32_t)(desc & 0x10) | (uint32_t)((desc >> 0x30) << 0x10),
						.ksel = (uint16_t)((desc >> 0x10) & 0x10),
						.storage_seg = (uint8_t)((desc >> 0x2C) & 0x1),
						.present = (uint8_t)((desc >> 0x2F) & 0x1),
						.dpl = (uint8_t)((desc >> 0x2D) & 0x3)
					}
				}
			};
		default:
			return (kims_interrupt_descriptor_info_t){};
	}
}
