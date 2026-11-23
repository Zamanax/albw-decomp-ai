typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;

struct Elem462 { char pad0[0x14]; float f14; char pad1[0x8]; float f20; char pad2[0x14]; };
struct Arr462 { char pad[8]; u32 n; Elem462* d; };
struct Obj462 {
    char pad0[0x1c]; Arr462* arr; char pad1[2]; s16 idx;
    char pad2[0x5c]; u8 flagA; u8 flagB; char pad3[2]; float fl84; char pad4[8]; u32 cnt;
};
extern u32 func_001B6AFC(Obj462* p);
extern void func_00462924(Obj462* p);
extern void func_00462760(Obj462* p);
extern void func_00231524(void* p);
static inline Elem462& at462(Arr462* a, u32 i) { return i < a->n ? a->d[i] : a->d[0]; }

u32 func_00462590(Obj462* p) {
    u32 r = func_001B6AFC(p);
    if (p->flagB && p->flagA) {
        Arr462* ar = p->arr; s16 ix = p->idx;
        if (at462(ar, ix).f14 < at462(ar, ix).f20 - 5.0f) func_00462924(p);
    }
    if (at462(p->arr, p->idx).f14 >= at462(p->arr, p->idx).f20 - 1.0f) func_00462760(p);
    if (p->fl84 >= 0.0f) {
        u32 k = (u32)p->fl84;
        if (p->cnt >= k) {
            func_00231524((char*)p + 0x20);
            func_00462760(p);
            r = 1;
        }
    }
    p->cnt = p->cnt + 1;
    return r;
}
