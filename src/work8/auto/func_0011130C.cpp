#include "sead_string.h"

extern "C" void func_00111C58(void* p, u32 a, u32 b, const char* s);

// 0x0011130C: formats into a 256-byte stack string, then forwards the buffer to func_00111C58 when
// the object's +0x24 pointer is set. The field is read twice so `self` stays live in r4.
extern "C" void func_0011130C(char* self, u32 a, u32 b, const char* fmt, ...) {
    if (*(void**)(self + 0x24) != 0) {
        va_list args;
        va_start(args, fmt);
        sead::FixedSafeString<256> s;
        s.formatV(fmt, args);
        va_end(args);
        func_00111C58(*(void**)(self + 0x24), a, b, s.cstr());
    }
}
