#ifndef _STDARG_H_
#define _STDARG_H_

#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4)

#define va_list			        __builtin_va_list
#define va_start(ap, last)	__builtin_va_start(ap, last)
#define va_arg(ap, type)	__builtin_va_arg(ap, type)
#define va_end(ap)		__builtin_va_end(ap)
#define va_copy(dest, src)	__builtin_va_copy(dest, src)
#else

#error Implement va_* for the compiler that you use

#endif

#endif /* end of include guard: _STDARG_H_ */
