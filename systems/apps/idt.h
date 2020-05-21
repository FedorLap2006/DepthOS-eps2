#ifndef _IDT_H_
#define _IDT_H_

#include <depthos/stddef.h>

// #define IDT_SIZE 129
#define IDT_SIZE 256

typedef uint64_t idt_entry_t;

typedef enum {
  IDTEK_INTR16 = 0x6,
  IDTEK_INTR32 = 0xE,
  IDTEK_TRAP16 = 0x7,
  IDTEK_TRAP32 = 0xF,
  IDTEK_TASK32 = 0x5
}idt_entry_kind_t;

typedef struct idt_entry_info {
  idt_entry_kind_t kind;
  union {
    struct {
      uint32_t base;
      uint16_t ksel;
      bool storage_seg;
      bool present;
      uint8_t dpl;
    }intr32;
  }value;
}idt_entry_info_t, idt_einfo_t;

#define make_idt_entry(P, BASE, DPL, S, TYPE, KSEL)                               \
  ((uint64_t)((uint64_t)0x0UL                                                     \
    | ((uint64_t)(BASE & 0xFFFF))                                                 \
    | ((uint64_t)(((uint64_t)KSEL & 0xFFFF) << (uint64_t)16))                     \
    | ((uint64_t)((uint64_t)(TYPE & 0xF) << (uint64_t)40))                        \
    | ((uint64_t)((uint64_t)(S & 0x1) << (uint64_t)44))                           \
    | ((uint64_t)(((uint64_t)DPL & 0x3) << (uint64_t)45))                         \
    | ((uint64_t)((uint64_t)(P & 0x1) << (uint64_t)47))                           \
    | ((uint64_t)((uint64_t)(BASE >> 0x10) << (uint64_t)48))                      \
    ))

#define make_intr_idt_entry(BASE, DPL) \
  make_idt_entry(1, BASE, DPL, 0, IDTEK_INTR32, 0x8)
// 'idt_einfo_toentry' makes from native IDT entry to info of IDT entry
idt_einfo_t idt_entry_toeinfo(idt_entry_t entry);
// 'idt_entry_toeinfo' makes from info of IDT entry to native IDT entry
idt_entry_t idt_einfo_toentry(idt_einfo_t einfo);


void idt_set_entry(uint8_t index, idt_entry_t data);
idt_entry_t idt_get_entry(uint8_t index);


typedef struct interrupt_env {
  uint32_t fs, gs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t intr_num, error_code;
  uint32_t eip, cs, eflags, useresp, ss;
}interrupt_env_t;

typedef void(*interrupt_handler_t)(interrupt_env_t);
void register_interrupt(uint8_t index, interrupt_handler_t h);
#endif
