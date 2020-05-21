#ifndef _DEPTHOS_STDDEF_H_
#define _DEPTHOS_STDDEF_H_

#include <depthos/types.h>

#ifndef __GNUC__
#define __asm__ asm
#endif

#define __attr(...) __attribute__(__VA_ARGS__)
#define __packed __attr((packed))
#define __unsafefunc __attr((naked))
#define __cleanfunc __unsafefunc
#define __cleanf __cleanfunc
#define __noreturn __attr((noreturn))


#endif
