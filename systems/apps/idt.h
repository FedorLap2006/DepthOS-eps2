#pragma once

#include <depthos/stddef.h>

typedef uint64_t idt_entry_t;

typedef enum {
  IDTEK_INTERRUPT,
  IDTEK_TRAP,
  IDTEK_TASK,
}idt_entry_kind_t;

typedef struct idt_entry_info {
  idt_entry_kind_t kind;
  union {
    struct {
      uint32_t base;
      uint8_t ksel;
      bool storage_seg;
      uint8_t type;
      uint8_t dpl;
    }interrupt;
  }value;
}idt_entry_info_t, idt_einfo_t;

#define make_idt_entry(P, BASE, DPL, S, Type, KSEL) \
  ((uint64_t)(0x0UL                                           \
    | ((uint64_t)(BASE & 0xFFFF))                             \
    | ((uint64_t)((KSEL & 0xFFFF) << 16))                     \
    | ((uint64_t)((TYPE & 0x3) << 40))                        \
    | ((uint64_t)((S & 0x1) << 44))                           \
    | ((uint64_t)((DPL & 0x3) << 45))                          \
    | ((uint64_t)((P & 0x1) << 47))                           \
    | ((uint64_t)((BASE & 0xFFFF0000) << 48))                 \
    ))

#define make_intr_idt_entry(BASE, DPL) \
  make_idt_entry(1, BASE, DPL, 0, 0xE, 0x08)
// 'idt_einfo_toentry' makes from native IDT entry to info of IDT entry
idt_einfo_t idt_entry_toeinfo(uint32_t index);
// 'idt_entry_toeinfo' makes from info of IDT entry to native IDT entry
idt_einfo_t idt_einfo_toentry(idt_einfo_t einfo);


void idt_set_entry(uint32_t index, idt_entry_t data);
idt_entry_t idt_get_entry(uint32_t index);
