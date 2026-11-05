typedef unsigned int u32;
typedef unsigned char u8;

struct Loc5610A8 {
    u32 w0;
    u8 b4;
    u8 p[7];
};
struct Pair5610A8 {
    u32 lo;
    u32 hi;
};
struct Obj5610A8 {
    u32 m0;
};

bool func_005611C0(Obj5610A8* self, Loc5610A8* l);

extern "C" bool func_005610A8(Obj5610A8* self, Pair5610A8* out) {
    u32 lo, hi;
    Loc5610A8 l;
    if (!(func_005611C0(self, &l))) {
        lo = 0;
        hi = 0;
    } else {
        u32 c = l.b4;
        if (0xc0 == c || c == 0xc1) {
             u32 t2 = l.w0;
             Obj5610A8 * t4 = self;
            lo = t4->m0;
            hi = t4->m0 + t2;
        } else if (c == 0xff) {
            hi = 0;
            lo = self->m0;
        } else {
            lo = 0;
            hi = 0;
        }
    }
    Pair5610A8 * t3 = out;
    t3->hi = hi;
    t3->lo = lo; 
    return 0 != lo;
}
