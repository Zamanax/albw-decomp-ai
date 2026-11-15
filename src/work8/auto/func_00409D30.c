typedef unsigned int u32;
typedef unsigned char u8;

typedef struct Buf {
    u8 m0[0x14];
    u8* m14;
    u32 m18;
    u32 m1C;
} Buf;

extern void func_001163A0(void* d, const void* s, u32 n);

u32 func_00409D30(Buf* self, void* dst, u32 n) {
    Buf* p = self;
    u32 avail = p->m18 - p->m1C;
    u32 c = avail < n ? avail : n;
    func_001163A0(dst, self->m14 + self->m1C, c);
    return c;
}
