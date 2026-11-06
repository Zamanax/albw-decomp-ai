#include "sead_string.h"

struct Obj48E4 {
    SafeString s;
    u32 m8;
    u32 mC;
    u32 m10;
    u32 m14;
    u32 m18;
    u32 m1c;
    u32 m20;
    u8 m24;
};

extern "C" u32 func_0057E2F8(void* self, const SafeString& src, void* dst);
extern "C" void func_00489F08(void* r, void* tmp);

void func_0048E4B4(void* self, Obj48E4* a1) {
    sead::FixedSafeString<0x100> buf;
    Obj48E4 * t5 = a1;
    int r = func_0057E2F8(self, t5->s, &buf);
    if (r) {
        Obj48E4 tmp = *t5;
        (&tmp.s)->mStringTop = (buf.cstr());
        func_00489F08((void*)r, &tmp);
        t5->m1c = tmp.m1c;
        Obj48E4 * t3 = a1;
        t3->m20 = tmp.m20;
        Obj48E4 * t0 = a1;
        t0->m24 = tmp.m24;
    }
}
