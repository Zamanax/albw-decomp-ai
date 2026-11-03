typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;

struct Obj {
    u8 pad0[0xe];
    u16 mE;
    u8 pad10[0x18 - 0x10];
    f32 m18;
    f32 m1c;
    void* m20;
};

void* func_0067D648(struct Obj* o, f32 t) {
    f32 d = o->m18;
    u8* tab = (u8*)o->m20;
    f32 q = t / d;
    q *= 32.0f;
    s32 idx = (s32)q;
    if ((u32)*(u16*)tab > (u32)idx) return tab;
    s32 off = (s32)(o->mE * 6) - 6;
    u8* p = tab + off;
    if ((u32)idx >= *(u16*)p) return p;
    u32 k = (u32)(o->m1c * ((f32)(o->mE - 1) * t));
    p = tab + k * 6;
    if ((u32)idx < *(u16*)p) {
        do { p -= 6; } while (*(u16*)p > (u32)idx);
        return p;
    }
    do { p += 6; } while (*(u16*)p <= (u32)idx);
    return p - 6;
}
