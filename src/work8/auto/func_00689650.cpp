// func_00689650: sead::FormatFixedSafeString<256>'s variadic constructor (formats into its own buffer).
#include "sead_string.h"

void* operator new(u32 size, void* p) throw();

void mk(char* p, const char* fmt, s32 a) { new (p) sead::FormatFixedSafeString<256>(fmt, a); }
