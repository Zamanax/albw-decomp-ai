/* Variable arguments for armcc 4.1 b1049, written for this project (the compiler's own include
 * tree is not in the repository). armcc implements va_start/va_arg as compiler intrinsics taking
 * the va_list itself. In C++ the intrinsics require the type to be std::__va_list (a plain
 * global struct gives "#928 incorrect use of va_start"). Verified with --asm in C and C++: a `...`
 * function gets `push {r0-r3}` and va_start(ap, last) yields the first variadic slot.
 * armcc 4.1 exits silently (code 5) on a variadic member defined inside a class template; define
 * such members in a non-template base class.
 */
#ifndef ALBW_STDARG_H
#define ALBW_STDARG_H

#ifdef __cplusplus
namespace std {
typedef struct __va_list { void* __ap; } va_list;
}
using std::va_list;
#else
typedef struct __va_list { void* __ap; } va_list;
#endif

#define va_start(ap, parmN) __va_start(ap, parmN)
#define va_arg(ap, type) __va_arg(ap, type)
#define va_copy(dest, src) ((void)((dest) = (src)))
#define va_end(ap) ((void)(ap))

#endif
