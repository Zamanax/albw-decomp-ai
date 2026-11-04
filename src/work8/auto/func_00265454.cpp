#ifndef DS3_H
#define DS3_H
#include "albw_types.h"

struct Control2317 { u16 current, max; u32 pad4, param; };

struct Flag16 {
    u16 v;
    Flag16(){}
    Flag16(u16 n):v(n){}
    void reset(u16 mask){*this = Flag16((u16)(v & ~mask));}
    void set(u16 mask){*this = Flag16((u16)(v | mask));}
};


#include "vec3.h"


struct Flag32 {
    u32 v;
    void change(u32 mask, bool on) { if (on) v |= mask; else v &= ~mask; }
    void set(u32 mask) { change(mask, true); }
    void reset(u32 mask) { change(mask, false); }
};
#endif
struct S265454 { char pad[0x90c]; u8 m90C; char pad2[0x918-0x90d]; u32 m918; };
extern "C" void* func_0058A8F0(void*);
extern "C" void func_006605D4(void*, int) __attribute__((notailcall));
extern "C" void func_002654A4(void*);
void func_00265454(S265454* self) {
    if (func_0058A8F0(self) == 0) return func_002654A4(self);
    if (self->m90C < 0x1e) {
        self->m90C = self->m90C + 1;
    } else {
        func_006605D4(&self->m918, 3);
    }
}
