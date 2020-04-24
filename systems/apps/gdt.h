#ifndef _GDT_H_
#define _GDT_H_


#include <depthos/stddef.h>

#define GDT_SIZE 4

typedef uint64_t gdt_entry_t;

typedef struct gdt_entry_info {
  // base & limit
  uint32_t base;
  uint32_t limit;
  // access
  bool present;
  uint8_t dpl;
  bool native;
  bool exec;
  bool dir_conform;
  bool read_write;
  // flags
  bool page_gran;
  bool bit32;
  bool avaible;
}gdt_entry_info_t, gdt_einfo_t;

// gdt_entry_info gdt_entry_get_info(gdt_entry entry);
// gdt_entry gdt_entry_make_byinfo(gdt_entry_info info);

// 'gdt_einfo_toentry' makes from info of GDT entry to native GDT entry.
gdt_entry_t gdt_einfo_toentry(gdt_einfo_t einfo);
// 'gdt_entry_toeinfo' makes from native GDT entry to info of GDT entry.
gdt_einfo_t gdt_entry_toeinfo(gdt_entry_t entry); 

#define make_gdt_entry(BASE, LIMIT, ACCESS, FLAGS)  \
  ((uint64_t)(0x0                                   \
  |(LIMIT & 0xFFFF)                                 \
  |(BASE << 16)                                     \
  |(((uint64_t)                                     \
    (                                               \
        ((BASE >> 16) & 0xFF)                       \
        | ((ACCESS & 0xFF) << 0x8)                  \
        | ((LIMIT & 0xF0000))                       \
        | ((FLAGS & 0xF) << 20)                     \
        | (BASE & 0xFF000000)                       \
    )) << 32                                        \
  )))

#define make_gdt_entry_flags(GRAN, SIZE, A) \
  ((uint64_t)(0x0                           \
  |make_gdt_entry_field(gran, GRAN)         \
  |make_gdt_entry_field(size, SIZE)         \
  |make_gdt_entry_field(avl, A)             \
  ))

#define make_gdt_entry_access(P, DPL, N, EX, DC, RW) \
  ((uint64_t)(0x0                           \
  |make_gdt_entry_field(present, P)         \
  |make_gdt_entry_field(rpl, DPL)           \
  |make_gdt_entry_field(type, N)            \
  |make_gdt_entry_field(exec, EX)           \
  |make_gdt_entry_field(dc, DC)             \
  |make_gdt_entry_field(rw, RW)             \
  |make_gdt_entry_field(ac)                 \
  ))

#define make_gdt_entry_field(FIELD, ...) make_gdt_entry_f##FIELD(__VA_ARGS__)

#define make_gdt_entry_fpresent(P) ((uint64_t)(P & 0x1) << 7)
#define make_gdt_entry_frpl(RPL) ((uint64_t)(RPL & 0x2) << 5)
#define make_gdt_entry_ftype(T) ((uint64_t)(T & 0x1) << 4)
#define make_gdt_entry_fexec(EX) ((uint64_t)(EX & 0x1) << 3)
#define make_gdt_entry_fdc(DC) ((uint64_t)(DC & 0x1) << 2)
#define make_gdt_entry_frw(RW) ((uint64_t)(RW & 0x1) << 1)
#define make_gdt_entry_fac() ((uint64_t)0 << 0)
#define make_gdt_entry_fgran(G) ((uint64_t)(G & 0x1) << 3)
#define make_gdt_entry_fsize(S) ((uint64_t)(S & 0x1) << 2)
#define make_gdt_entry_favl(A) ((uint64_t)(A & 0x1) << 0)
#undef mbc

// initialize GDT
// void gdt_init();

// sets GDT[index] entry data
void gdt_set_entry(uint32_t index, gdt_entry_t data);
// gets GDT[index] entry data
gdt_entry_t gdt_get_entry(uint32_t index);

#endif
