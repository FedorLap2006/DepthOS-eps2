#ifndef _KDMS_H_
#define _KDMS_H_

#include <depthos/stddef.h>

/**
 * Some overview:
 * - KDMS is [K]ernel [D]escriptors [M]anagement [S]ystem i.e KDMS manages descriptors in the kernel
 * - If you don't know "What is GDT and why It required" please do not touch any code here, you can break something and won't undo it.
 * 
 */

/**
 * Standard size of table (+ 1, because null descriptor)
 */
#define KDMS_STD_TABLE_SIZE 2

/**
 * Descriptors table entry
 */
typedef uint64_t kdms_descriptor_t;

typedef struct kdms_desctbl {
  size_t size;
  kdms_descriptor_t* pointer;
}kdms_desctbl_t;

/**
 * Descriptors table entry info
 */
typedef struct kdms_descriptor_info {
  uint32_t base;
  uint32_t limit;

  bool present;

  uint8_t dpl;
  bool custom, exec, dirc, rw;

  bool pg_gran, bit32, kpayload;
}kdms_descriptor_info_t;

/**
 * Standart KDMS initialisation function
 */
void kdms_std_init();

/**
 * Function which is switching current KDMS descriptors table
 * @param  tbl  New table
 * @return      Old table
 */
kdms_desctbl_t kdms_switch_tbl(kdms_desctbl_t tbl);

/**
 * Macros for creating KDMS descriptor
 * @param  BASE   Base of a descriptor
 * @param  LIMIT  Limit of a descriptor
 * @param  ACCESS Access byte of a descriptor
 * @param  FLAGS  Flags of a descriptor
 */

#define make_kdms_descriptor(BASE, LIMIT, ACCESS, FLAGS)     \
    (                                                        \
      (uint64_t)(0x0                                         \
        | (uint64_t)(LIMIT & 0xFFFF)                         \
        | (uint64_t)((uint64_t)(BASE & 0xFFFF) << 0x10)      \
        | ((uint64_t)(                                       \
          (uint64_t)((BASE >> 0x10) & 0xFF)                  \
          | (uint64_t)((ACCESS & 0xFF) << 0x8)               \
          | (uint64_t)(LIMIT & 0xF0000)                      \
          | (uint64_t)((FLAGS & 0xF) << 0x14)                \
          | (uint64_t)(BASE & 0xFF000000)                    \
        ) << 0x20)                                           \
      )                                                      \
  )

/**
 * Macros for creating access byte of a KDMS descriptor
 * @param  PRESENT Present bit of descriptor access byte
 * @param  DPL     Prive
 * @param  NATIVE  Is this descriptor maked by system or it's data/code segment descriptor
 * @param  EXEC    Executable flag
 * @param  DC      Direction/conforming flag (For full info visit this article https://wiki.osdev.org/GDT)
 * @param  RW      Read write flag (For full info visit this article https://wiki.osdev.org/GDT)
 */
#define make_kdms_descriptor_access(PRESENT, DPL, NATIVE, EXEC, DC, RW) \
  ((uint64_t)(0x0                                                       \
    | (uint64_t)((RW & 0x1) << 0x1)                                     \
    | (uint64_t)((DC & 0x1) << 0x2)                                     \
    | (uint64_t)((EXEC & 0x1) << 0x3)                                   \
    | (uint64_t)((NATIVE & 0x1) << 0x4)                                 \
    | (uint64_t)((DPL & 0x2) << 0x5)                                    \
    | (uint64_t)((PRESENT & 0x1) << 0x7)                                \
  ))

/**
 * Macros for creating flags of a KDMS descriptor
 * @param  PGGRAN  Is this descriptor using page granularity or not
 * @param  BIT32   Is this descriptor 32 or 16 bit
 * @param  AVAIBLE This bit avaible for operating system, so it can include any payload
 */
#define make_kdms_descriptor_flags(PGGRAN, BIT32, AVAIBLE) \
  ((uint64_t)(0x0                                          \
    | (uint64_t)(AVAIBLE & 0x1)                            \
    | (uint64_t)((BIT32 & 0x1) << 0x2)                     \
    | (uint64_t)((PGGRAN & 0x1) << 0x3)                    \
  ))

/**
 * Function for converting KDMS descriptor info to a descriptor
 * @param  dinfo Descriptor info for converting
 * @return       Converted descriptor
 */
kdms_descriptor_t kdms_convert_dinfo_todesc(kdms_descriptor_info_t dinfo);

/**
 * Function for converting KDMS descriptor to a descriptor info
 * @param  desc Descriptor for converting
 * @return      Converted descriptor info
 */
kdms_descriptor_info_t kdms_convert_desc_todinfo(kdms_descriptor_t desc);

/**
 * Function for getting descriptor from current descriptors table
 * @param  index Index of element in current descriptors table
 * @return       Element by given index in current descriptors table
 */
kdms_descriptor_t kdms_get_desctbl_entry(uint32_t index);

/**
 * Function for setting descriptor in current descriptors table
 * @param  index   Index of element in current descriptors table
 * @param  newdesc New descriptor for replacing by given index in current descriptors table
 * @return         Old descriptor by given index in current descriptors table
 */
kdms_descriptor_t kdms_set_desctbl_entry(uint32_t index, kdms_descriptor_t newdesc);

#endif /* end of include guard: _KDMS_H_ */
