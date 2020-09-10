

#ifndef _DEPTHOS_STDDEF_H_
#define _DEPTHOS_STDDEF_H_

#include <depthos/types.h>
#include <io/console.h>

#ifndef __GNUC__
#define __asm__ asm
#endif

#define __attr(...) __attribute__(__VA_ARGS__)
#define __packed __attr((packed))
#define __unsafefunc __attr((naked))
#define __cleanfunc __unsafefunc
#define __cleanf __cleanfunc
#define __noreturn __attr((noreturn))

#define debug(t, ...) debug_t##t(__VA_ARGS__)

// TODO: make 64 and negative support
#define debug_ti64(msg, v, r) {                         \
  kernel_console.print("DEBUG i64\n\tMessage: ");       \
  kernel_console.print(msg);                            \
  kernel_console.print("\n\tValue: \n\t\t| (1 - 32) "); \
  console_put_number((uint32_t)(v & 0xFFFFFFFF), r);    \
  kernel_console.print("\n\t\t| (32 - 64) ");           \
  console_put_number((uint32_t)(v >> 0x20), r);         \
  kernel_console.put('\n');                             \
}

#endif
