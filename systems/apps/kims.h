#ifndef _KIMS_H_
#define _KIMS_H_

#include <depthos/stddef.h>

/**
 * Standard size of KIMS interrupts descriptors table
 */
#define KIMS_STD_INTR_DESCRIPTORS_TABLE_SIZE 256

/**
 * Standard size of KIMS interrupts handlers table
 */
#define KIMS_STD_INTR_HANDLERS_TABLE_SIZE 256

/**
 * Some overview:
 *  - KIMS is [K]ernel [I]nterrupts [M]anagement [S]ystem i.e KIMS manages interrupts in the kernel
 *  - If you don't know "What is IDT and PIC" please do not touch this file, without any
 *    understanding how it works you can break some things which can break the kernel
 *
 */

/**
 * kims_interrupt_descriptor_t is a type which represents a native interrupt descriptor in the IDT (interrupts descriptors table)
 */
typedef uint64_t kims_interrupt_descriptor_t;

/**
 * kims_interrupt_env is a structure which represents the environment of called interrupt
 */
typedef struct kims_interrupt_env {
	/**
	 * All registers which are needed in an interrupt environment */
	uint32_t fs, gs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t intr_num, error_code;
	uint32_t eip, cs, eflags, useresp, ss;
}kims_interrupt_env_t;

/**
 * kims_interrupt_descriptor_kind_t is a enumeration which represents a kind of an interrupt
 */
typedef enum kims_interrupt_descriptor_kind {
	KIMS_IDK_INTR16 = 0x6,
	KIMS_IDK_INTR32 = 0xE,
	KIMS_IDK_TRAP16 = 0x7,
	KIMS_IDK_TRAP32 = 0xF,
	KIMS_IDK_TASK32 = 0x5,
}kims_interrupt_descriptor_kind_t;

/**v =
 * kims_interrupt_descriptor_info_t is a structure which represents the info of an interrupt descriptor
 */
typedef struct kims_interrupt_descriptor_info {
	kims_interrupt_descriptor_kind_t kind;
	union {
		struct {
			/**
			 * base is an address of an interrupt handler (low-level) function
			 * Note: In standard configuration It's predefined interrupts low-level handlers (see kims_llhandlers.S)
			 */
			uint32_t base;
			/**
			 * ksel is an kernel code selector which is using by the interrupt
			 * Note: Usually It's 0x08
			 */
			uint16_t ksel;
			/**
			 * Storage segment flag
			 * Note: Just set it to false for interrupts
			 */
			bool storage_seg;
			/**
			 * Present flag
			 * Note: Indicates interrupt is enabled or disabled
			 */
			bool present;
			/**
			 * Descriptor privelege level i.e It controls the access to an interrupt
			 */
			uint8_t dpl;
		}intr32;
	}v;
}kims_interrupt_descriptor_info_t;


/**
 * kims_pic_config is a structure which describes config for the 8259 PIC
 */

typedef struct kims_pic_config {
  /**
   * Dirty old mask flag
   *  - If cleared then old mask will be cleared and will be replaced to new when config will load
   *  - If setted then new mask only does OR operations with old mask
   */
  bool dirty_mask;

  /**
   * IOwait mode flag
   *  - If setted then all PIC API functions will use iowait mode after every PIC command execution
   *  - If cleared then PIC API functions won't work in this mode
   * NOTE: It must be setted to true, if you machine is old
   */
  bool iowait_mode;
  /**
   * Speciall Fully Nested Mode (SFNM) flag
   *  - If setted then PIC will work in SFNM
   *  - If cleared then PIC won't work in this mode
   * NOTE: Recommended set it to false
   */
  bool sfn_mode;
  /**
   * Buffered mode
   *  - If setted then PIC will work in the buffered mode
   *  - If cleared then PIC won't work in this mode
   * NOTE: It must be setted to false for the Intel ICH4
   */
  bool bufmode;
  /**
   * Primary-secondary (master-slave) buffered mode
   *  - If setted then PIC will work in the primary-secondary buffered mode
   *  - If cleared then PIC won't work in this mode
   * NOTE: Should always be setted to false on the Intel architecture
   */
  bool ps_bufmode;
  /**
   * Auto EOI
   *  - If setted then PIC will send the EOI automatically after the interrupt call
   *  - If cleared then PIC won't send the EOI automatically after the interrupt call
   */
  bool auto_eoi;
  /**
   * Microprocessor mode
   *  - If setted then PIC will work in the microprocessor mode
   *  - If cleared then PIC won't work in this mode
   * NOTE: Must be be setted to true on the Intel architecture
   */
  bool mp_mode;

  /**
   * Offest of interrupts in the IDT, which controled by primary controller
   * NOTE: Recommended set it to 0x20 on the Intel architecture
   */
  uint8_t primary_offset;
  /**
   * Offeset of interrupts in the IDT, which controled by secondary controller
   * NOTE: Recommended set it to 0x28
   */
  uint8_t secondary_offset;
  /**
   * IRQ line number where secondary controller is connected
   * NOTE: Must be setted to 0x2 on the PC
   */
  uint8_t sec_irq_line_num;
  /**
   * IRQ lines where secondary controller(s) is connected
   * Must be setted to 0x4 on the PC
   */
  uint8_t sconn_irq_line;
  /**
   * Enabled IRQ's bitmask
   */
  uint16_t mask;
}kims_pic_config_t;


/*
 * kims_init_pic is a function which initialises 8259 PIC with given config
 * 
 * @param config Config for initialisation of 8259 PIC
 */

void kims_init_pic(struct kims_pic_config config);

/**
 * kims_interrupt_handler_t is a structure which represents an interrupt handler function in the IHT (interrupts handlers table)
 */
typedef struct kims_interrupt_handler {
	void (*handler)(kims_interrupt_env_t);
	uint8_t ipl;
}kims_interrupt_handler_t;

/**
 * kims_native_table is a structure which represents native (interrupts descriptors) table
 */
typedef struct kims_native_table {
	size_t size;
	kims_interrupt_descriptor_t *pointer;
}kims_native_table_t;

/**
 * kims_interrupts_table is a structure which represents interrupts (interrupts handlers) table
 */
typedef struct kims_interrupts_table {
	size_t size;
	kims_interrupt_handler_t *pointer;
}kims_interrupts_table_t;

/**
 * kims_table is a structure which represents KIMS tables configuration in once data structure
 */

typedef struct kims_table {
	kims_native_table_t native;
	kims_interrupts_table_t interrupts;
}kims_table_t;

/**
 * kims_std_init is a function which setups and loads the standard KIMS configuration
 */
void kims_std_init();

/**
 * kims_switch_tbl is a function which switches the current KIMS table to 'tbl' and returns old
 * @param  tbl     New table
 * @param  reload Indicates is needed to reload the table in the IDTR register
 * @return         Old table
 */
kims_table_t kims_switch_tbl(kims_table_t tbl, bool reload);

/**
 * kims_register_ihandler is a function which registers handler of an interrupt given by 'index'
 * @param index   An index of interrupt on which is needed to set the handler to
 * @param handler A handler which is needed to set to an interrupt by given 'index'
 * @param ipl     An interrupt privelege level, controls the access to an interrupt
 */
void kims_register_ihandler(uint32_t index, void (*handler)(kims_interrupt_env_t), uint8_t ipl);


/**
 * kims_get_native_entry is a function which gets an entry from the native subtable in current KIMS table
 * @param  index Index by which is an interrupt
 * @return        Native subtable entry by given 'index'
 */
kims_interrupt_descriptor_t kims_get_native_entry(uint32_t index);
/**
 * kims_set_native_entry is a function which sets an entry in the native subtable in current KIMS table by given index to new and returns old
 * @param  index Index by which is an "target" interrupt
 * @param  ev     New entry value
 * @return        Native subtable old entry by given 'index'
 */
kims_interrupt_descriptor_t kims_set_native_entry(uint32_t index, kims_interrupt_descriptor_t ev);


/**
 * kims_get_native_entry is a function which gets an entry from the interrupts subtable in current KIMS table
 * @param  index Index by which is an interrupt
 * @return        Interrupts subtable entry by given 'index'
 */
kims_interrupt_handler_t kims_get_interrupts_entry(uint32_t index);
/**
 * kims_set_native_entry is a function which sets an entry in the interrupts subtable in current KIMS table by given index to new and returns old
 * @param  index Index by which is an "target" interrupt
 * @param  ev     New entry value
 * @return        Interrupts subtable old entry by given 'index'
 */
kims_interrupt_handler_t kims_set_interrupts_entry(uint32_t index, kims_interrupt_handler_t ev);


/**
 * kims_std_pic_init is a function which setups the PIC with default configuration
 */
void kims_std_pic_init();
// void kims_pic_init(struct )

/**
 * kims_enable_hwinterrupts is a function which enables hardware interrupts in the CPU
 */
void kims_enable_hwinterrupts();
/**
 * kims_enable_hwinterrupts is a function which disables hardware interrupts in the CPU
 */
void kims_disable_hwinterrupts();

/**
 * kims_convert_dinfo_to_desc is a function which converts descriptor info to actual descriptor
 * @param  dinfo a descriptor info to converting
 * @return        a converted descriptor
 */
kims_interrupt_descriptor_t kims_convert_dinfo_to_desc(kims_interrupt_descriptor_info_t dinfo);
/**
 * kims_convert_dinfo_to_desc is a function which converts actual descriptor to descriptor info
 * @param  dinfo a descriptor to converting
 * @return        a converted descriptor info
 */
kims_interrupt_descriptor_info_t kims_convert_desc_to_dinfo(kims_interrupt_descriptor_t desc);


#endif /* end of include guard: _KIMS_H_ */
