typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef unsigned long long u64;

struct Tmp {
    u32 w0;
    u8 kind;
    u8 pad1[3];
    u32 w8;
};
struct Obj { u32 m0; };
struct Pair64 { u32 lo; u32 hi; };

u32 func_00560FDC(Obj* self, Tmp* t);

bool func_00560EF8(Obj* self, Pair64* out) {
    Tmp t;
    u32 hi;
    u32 lo;
    u32 t1 = func_00560FDC(self, &t);
    if (t1 == 0) {
        hi = lo = 0;
    } else if (0xc0 == t.kind || t.kind == 0xc1) {
         Obj * t3 = self;
         u32 t0 = t.w0;
        lo = t3->m0;
        hi = t0 + t3->m0;
    } else if (0xff == t.kind) {
        hi = 0;
        lo = self->m0;
    } else {
        hi = lo = 0;
    }
    Pair64 * t4 = out;
    t4->lo = lo;
    t4->hi = hi; 
    return lo != 0;
}
