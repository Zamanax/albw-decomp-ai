typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
struct Pr2ACE { u32 a, b; };
extern "C" void func_002ADE0C(void*, u32);
extern "C" void func_002AD658(void*, s32, s32, s32, Pr2ACE);
struct Sub500 { char p0[8]; s16 s8; };
struct Inner { char p0[0x500]; Sub500 m500; };
struct Obj { char p0[0x34]; Inner* m34; u16 m38; };
void func_002AE0E8(void* p, u32 arg) {
    func_002ADE0C(p, arg);
    if (arg == 0) {
        Obj* o = (Obj*)p;
        if (o->m34->m500.s8 <= 0) { Obj* q = o; q->m38 |= 1; }
    }
    Pr2ACE t; t.b = 1; t.a = 0;
    func_002AD658(p, 0x20, (u8)arg, 8, t);
}
