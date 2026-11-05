/* Variable arguments for armcc 4.1 b1049, written for this project (the compiler's own include
 * tree is not in the repository). armcc implements va_start/va_arg as compiler intrinsics taking
 * the va_list itself; verified with --asm: a `...` function gets `push {r0-r3}` and
 * va_start(ap, last) yields the address of the first variadic slot.
 */
#ifndef ALBW_STDARG_H
#define ALBW_STDARG_H

typedef struct __va_list { void* __ap; } va_list;

#define va_start(ap, parmN) __va_start(ap, parmN)
#define va_arg(ap, type) __va_arg(ap, type)
#define va_copy(dest, src) ((void)((dest) = (src)))
#define va_end(ap) ((void)(ap))

#endif
