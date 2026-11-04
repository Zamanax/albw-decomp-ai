#pragma once
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef float f32;
typedef double f64;
typedef unsigned long ulong;

struct BitFlag32 {
    u32 v;
    void change(u32 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u32 m) { change(m, true); }
    void reset(u32 m) { change(m, false); }
};

struct BitFlag16 {
    u16 v;
    void change(u16 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u16 m) { change(m, true); }
    void reset(u16 m) { change(m, false); }
};

extern bool func_0058A8F0(void*);
__attribute__((notailcall)) extern void func_00657BD4(void*, int);
extern void func_00153230(void*);

struct Obj1531E0 {
    char pad0[0x8fc];
    u32 m8FC;
};

void func_001531E0(Obj1531E0* self) {
    if (!func_0058A8F0(self)) {
        func_00153230(self);
        return;
    }
    if (self->m8FC < 0x1e) {
        self->m8FC = self->m8FC + 1;
        return;
    }
    func_00657BD4((char*)self + 0x90c, 3);
}
