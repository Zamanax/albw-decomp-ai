#include "sead_string.h"
#include "albw_types.h"

struct Inner { u8 pad[0x20]; const char* text; };
struct Outer { u8 pad[0xac]; Inner* inner; };
struct Obj {
    Inner* f0;
    void* const* f4;
    u8 pad[0x20];
    char* buf;
    s32 cap;
    u8 pad2[0x40];
    u8 flags;
};
extern "C" void* func_0040449C(void*, const char*);
extern "C" void* func_0010E3C4(void*, const void*, u32);

Outer* target(Obj* p, void* const* a1, const SafeString& src) {
    Obj * t2 = p;
    t2->f4 = a1;
    const char * t3 = ((&src)->cstr());
    Outer* x = (Outer*)func_0040449C(*a1, t3);
    Outer * t12 = x;
    t2->flags &= ~4;
    Inner* in = t12->inner;
    t2->f0 = in;
    SafeString s(in->text);
    SafeString* ps = &s;
    char * t5 = p->buf;
    char * t0 = t5;
    char* buf = t0;
    s32 n = ps->calcLength();
    s32 t10 = p->cap;
    if (t10 <= n) n = t10 - 1;
    func_0010E3C4(buf, ps->cstr(), n);
    buf[n] = 0;
    return x;
}
