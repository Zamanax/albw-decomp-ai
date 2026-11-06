// func_0014E500: builds a stack sead::FixedSafeString<64> *from a SafeString* and passes it on.
// The constructor is the copy-from-SafeString one from sead_string.h: BufferedSafeString(mBuffer, 64)
// (buffer terminator, no clear() store) then copy(src) -- the buffered vtable store is dead and the
// only vtable stores left are FixedSafeStringBase<64> and FixedSafeString<64>.
#include "sead_string.h"

struct A14E500;

extern "C" s32 func_0014F0F8(A14E500* self, sead::FixedSafeString<64>* s, s8* out);
extern "C" void func_0014E670(A14E500* self, const sead::FixedSafeString<64>* s,
                              const sead::SafeString& src, s8 c, u32 a2);

void func_0014E500(A14E500* self, const sead::SafeString& src, u32 a2) {
    sead::FixedSafeString<64> s(src);
    s8 c = 0;
    if (func_0014F0F8(self, &s, &c)) {
        func_0014E670(self, &s, src, c, a2);
    }
}
