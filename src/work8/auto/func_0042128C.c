typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern u32 func_001139F8(u32);

struct Rec {
    u32 w0;
    u32 w4;
    u16 h8;
    u16 ha;
    u16 hc;
    u8 be;
    u8 bf;
    u32 w10;
};

void func_0042128C(struct Rec* p, u32 v, u32 a, u8 sl, u16 r5, u16 r6, u16 r7, u32 r8, u8 sb) {
    u32 t;
    p->w0 = v;
    if (a) {
        t = func_001139F8(a) >> 3;
    } else {
        t = 0;
    }
    p->be = sl;
    p->w4 = t;
    p->w10 = r8 >> 3;
    p->ha = r5;
    p->h8 = r6;
    p->hc = r7;
    p->bf = sb;
}
