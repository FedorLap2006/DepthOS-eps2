#include <apps/kdms.h>
#include <io/console.h>


static kdms_desctbl_t kdms_current_table;
static kdms_desctbl_t kdms_std_table;
kdms_descriptor_t kdms_std_table_data[KDMS_STD_TABLE_SIZE + 1];

void kdms_std_init() {

  kdms_descriptor_info_t kcode = {
		.base = 0x0,
		.limit = 0xFFFFFFFF,
		.present = true,
		.dpl = 0x0,
		.custom = false,
		.exec = true,
		.dirc = false,
		.rw = false,
		.pg_gran = true,
		.bit32 = true,
		.kpayload = 0
	}, kdata = {
		.base = 0x0,
		.limit = 0xFFFFFFFF,
		.present = true,
		.dpl = 0x0,
		.custom = false,
		.exec = false,
		.dirc = false,
		.rw = false,
		.pg_gran = true,
		.bit32 = true,
		.kpayload = 0
	};
	kdms_std_table_data[0x0] = 0x0;
	kdms_std_table_data[0x1] = kdms_convert_dinfo_todesc(kcode);
	kdms_std_table_data[0x2] = kdms_convert_dinfo_todesc(kdata);
	kdms_std_table.pointer = kdms_std_table_data;
	kdms_std_table.size = KDMS_STD_TABLE_SIZE + 1;
	kdms_switch_tbl(kdms_std_table);
	kernel_console.print("[KERNEL] KDMS is initialised\n");
}

#define make_gdt_ptr(base, size) \
    (uint64_t)(uint64_t)((size*sizeof(kdms_descriptor_t))==0?0:size*sizeof(kdms_descriptor_t)-1)|((uint64_t)(uint32_t)base<<0x10)

kdms_desctbl_t kdms_switch_tbl(kdms_desctbl_t tbl) {
  static kdms_desctbl_t temp;
  temp = kdms_current_table;
  kdms_current_table = tbl;

  static uint64_t gdt_ptr;
  gdt_ptr = make_gdt_ptr(kdms_current_table.pointer, kdms_current_table.size);
  __asm__ volatile ("lgdt %0" ::"m"(gdt_ptr));
  return temp;
}

kdms_descriptor_t kdms_convert_dinfo_todesc(kdms_descriptor_info_t dinfo) {
  return (kdms_descriptor_t)make_kdms_descriptor(dinfo.base, dinfo.limit,
    make_kdms_descriptor_access(dinfo.present,dinfo.dpl,dinfo.custom == true ? false : true,dinfo.exec,dinfo.dirc, dinfo.rw),
    make_kdms_descriptor_flags(
      dinfo.pg_gran,
      dinfo.bit32,
      dinfo.kpayload
    )
  );
}

kdms_descriptor_info_t kdms_convert_desc_todinfo(kdms_descriptor_t desc) {
  static kdms_descriptor_info_t dinfo;
  uint32_t limit = desc & 0xFFFF, base = desc & 0xFFFF0000;
  uint8_t access = 0x0, flags = 0x0;

  desc >>= 0x20;
  base |= (desc & 0xFF) << 16 | (desc & 0xFF000000); limit |= desc & 0xF0000;
  flags = (desc & 0xF00000) >> 0x14; access = (desc & 0xFF00) >> 0x8;


  dinfo.base = base; dinfo.limit = limit;

  dinfo.present = (access >> 7) & 0x1;
  dinfo.dpl = (access >> 5) & 0x1;
  dinfo.custom = ((access >> 4) & 0x1) == 1 ? false : true;
  dinfo.exec = (access >> 3) & 0x1;
  dinfo.dirc = (access >> 2) & 0x1;
  dinfo.rw = (access >> 1) & 0x1;

  dinfo.pg_gran = (flags >> 3) & 0x1;
  dinfo.bit32 = (flags >> 2) & 0x1;
  dinfo.kpayload = flags & 0x1;
  return dinfo;
}

kdms_descriptor_t kdms_get_desctbl_entry(uint32_t index) {
  if(index >= kdms_current_table.size) return (kdms_descriptor_t)0x0;
  return kdms_current_table.pointer[index];
}

kdms_descriptor_t kdms_set_desctbl_entry(uint32_t index, kdms_descriptor_t newdesc) {
  static kdms_descriptor_t temp;

  if(index >= kdms_current_table.size) return (kdms_descriptor_t)0x0;

  temp = kdms_current_table.pointer[index];
  kdms_current_table.pointer[index] = newdesc;

  return temp;
}
