#include "gdt.h"
#include <io/console.h>

gdt_entry_t __attribute__((aligned(16))) GDT[GDT_SIZE + 1]; // +1 - null segment

uint64_t make_gdtr(void* gdt, uint16_t size);

void _gdt_init() {
  gdt_einfo_t kernel_code_entry = {
    .base = 0x0,
    .limit = 0xFFFFFFFF,
    .present = true,
    .dpl = 0x0,
    .native = true,
    .exec = true,
    .dir_conform = false,
    .read_write = true,
    .page_gran = true,
    .bit32 = true,
    .avaible = 0,
  }, kernel_data_entry = {
    .base = 0x0,
    .limit = 0xFFFFFFFF,
    .present = true,
    .dpl = 0x0,
    .native = true,
    .exec = false,
    .dir_conform = false,
    .read_write = true,
    .page_gran = true,
    .bit32 = true,
    .avaible = 0,
  };
  gdt_einfo_t user_code_entry = {
    .base = 0x0,
    .limit = 0xFFFFFFFF,
    .present = true,
    .dpl = 0x3,
    .native = true,
    .exec = true,
    .dir_conform = true,
    .read_write = true,
    .page_gran = true,
    .bit32 = true,
    .avaible = 0,
  }, user_data_entry = {
    .base = 0x0,
    .limit = 0xFFFFFFFF,
    .present = true,
    .dpl = 0x3,
    .native = true,
    .exec = false,
    .dir_conform = false,
    .read_write = true,
    .page_gran = true,
    .bit32 = true,
    .avaible = 0,
  };

  gdt_set_entry(0, (gdt_entry_t)0);
  gdt_set_entry(1, gdt_einfo_toentry(kernel_code_entry));
  gdt_set_entry(2, gdt_einfo_toentry(kernel_data_entry));
  gdt_set_entry(3, gdt_einfo_toentry(user_code_entry));
  gdt_set_entry(4, gdt_einfo_toentry(user_data_entry));
//  set_gdt_entry_t(0x1, make_gdt_entry(1, 0x0, 1, 1, 0, 0));
//  set_gdt_entry_t(0x2, make_gdt_entry(1, 0x0, 1, 0, 0, 1));
  uint64_t gdtr;
  gdtr = make_gdtr(GDT, GDT_SIZE + 1);
  /*kernel_console.print("GDTR: (0 - 32) ");*/
  /*console_put_number(gdtr,0x10);*/
  /*kernel_console.print("\nGDTR: (32 - 64) ");*/
  /*console_put_number(gdtr >> 32,0x10);*/
  /*kernel_console.print("\n");*/
  /*kernel_console.print("GDT SIZE: ");*/
  /*console_put_number(GDT_SIZE, 0xA);*/
  /*kernel_console.print("\n*/
#define print_i64(n, radix) \
  kernel_console.print("{ [0 - 32] ("); \
  console_put_number(n & 0xFFFFFFFF, radix); \
  kernel_console.print(") [32 - 64] ("); \
  console_put_number(n >> 32, radix); \
  kernel_console.print(") }");


/*  kernel_console.print("GDTR: ");
  print_i64(gdtr, 0x10);
  kernel_console.put('\n');
  kernel_console.print("GDT SIZE: ");
  console_put_number(GDT_SIZE, 0xA);
  kernel_console.put('\n');
  kernel_console.print("[GDT ENTRIES]: \n");
#define print_entry(name, label) \
  kernel_console.print(#label ": "); \
  print_i64(gdt_einfo_toentry(name##_entry), 0x10); \
  kernel_console.put('\n');

  print_entry(kernel_code, kce);
  print_entry(kernel_data, kde);
  print_entry(user_code, uce);
  print_entry(user_data, ude);
#undef print_entry
#define print_entry(idx, label) \
  kernel_console.print(#label ": "); \
  print_i64(GDT[idx], 0x10);        \
  kernel_console.put('\n');

  print_entry(0, null);
  print_entry(1, kce);
  print_entry(2, kde);
  print_entry(3, uce);
  print_entry(4, ude);
#undef print_entry
*/
 __asm__ volatile("lgdt %0" : :"m"(gdtr));
}

uint64_t make_gdtr(void* gdt, uint16_t size) {
  if(size == 0) return - 1;
  size *= 64;
  size--;
/*  kernel_console.print("size: ");
  console_put_number(size, 0xA);
  kernel_console.put('\n');
  kernel_console.print("gdt base: ");
  console_put_number((uint32_t)gdt, 0x10);
  kernel_console.put('\n');*/
 // return (uint64_t)size | ((uint64_t) ((uint64_t)((uint32_t)gdt) << (uint64_t)16));
  return (uint64_t) (
      (uint64_t)size
      | (
        ((uint64_t)(uint32_t)gdt) << (uint64_t)16
      )
  );
}

void gdt_set_entry(uint32_t index, gdt_entry_t data) {
  if(index >= GDT_SIZE + 1) return;
  GDT[index] = data;
}

gdt_entry_t gdt_get_entry(uint32_t index) {
  if(index >= GDT_SIZE + 1) return -1;
  return GDT[index];
}


gdt_einfo_t gdt_entry_toeinfo(gdt_entry_t entry) {
  gdt_einfo_t einfo;
  uint32_t limit = entry & 0xFFFF;
  uint32_t base = entry & 0xFFFF0000;
  uint8_t access = 0x0, flags = 0x0;
  entry >>= 32;
  base |= (entry & 0xFF) << 16;
  base |= (entry & 0xFF000000);
  flags = (entry & 0xF00000) >> 20;
  access = (entry & 0xFF00) >> 8;
  limit |= (entry & 0xF0000);

  einfo.base = base;
  einfo.limit = limit;
  // access
  einfo.present = (access >> 7) & 0x1;
  einfo.dpl = (access >> 5) & 0x1;
  einfo.native = (access >> 4) & 0x1;
  einfo.exec = (access >> 3) & 0x1;
  einfo.dir_conform = (access >> 2) & 0x1;
  einfo.read_write = (access >> 1) & 0x1;
  // flags
  einfo.page_gran = (flags >> 3) & 0x1;
  einfo.bit32 = (flags >> 2) & 0x1;
  einfo.avaible = flags & 0x1;
  return einfo;
}

gdt_entry_t gdt_einfo_toentry(gdt_einfo_t einfo) {
  return (gdt_entry_t)(make_gdt_entry(einfo.base, einfo.limit, make_gdt_entry_access(einfo.present, einfo.dpl, einfo.native, einfo.exec, einfo.dir_conform, einfo.read_write), make_gdt_entry_flags(einfo.page_gran, einfo.bit32, einfo.avaible))
      );
}
