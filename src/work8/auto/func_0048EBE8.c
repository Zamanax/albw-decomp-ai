typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef struct { u32 f[9]; } Pack;

extern u32 func_00569F3C(u8* p, void* a, u32 n);
extern void* func_0010CEE0(u32 size, void* heap, s32 align);
extern u32 func_0056A0A0(u8* p, void* a, u32 n);
extern void func_00409DE4(u8* p, Pack* s);

void func_0048EBE8(u8* p, void* sb, u32 n2, u32 n3, u32 r8, void* sl) {
    u32 r7 = func_00569F3C(p + 4, sb, r8);
    *(void**)(p + 0x120) = func_0010CEE0(r7, sl, 0x20);
    if (n2 == 0) {
        *(void**)(p + 0x128) = 0;
    } else {
        *(void**)(p + 0x128) = func_0010CEE0(n2, sl, 0x20);
        if (n3 != 0) {
            u32 al = (n3 + 0x1f) & ~0x1fu;
            u32 v = func_0056A0A0(p + 4, sb, al);
            *(u32*)(p + 0x13c) = v;
            *(void**)(p + 0x138) = func_0010CEE0(v, sl, 0x20);
        }
    }
    Pack s = {{0}};
    s.f[0] = (u32)sb;
    s.f[1] = *(u32*)(p + 0x140);
    s.f[2] = *(u32*)(p + 0x120);
    s.f[3] = r7;
    s.f[4] = *(u32*)(p + 0x128);
    s.f[5] = n2;
    s.f[6] = *(u32*)(p + 0x138);
    s.f[7] = *(u32*)(p + 0x13c);
    s.f[8] = r8;
    func_00409DE4(p + 4, &s);
    *(u32*)(p + 0x124) = r7;
    *(u32*)(p + 0x12c) = n2;
}
