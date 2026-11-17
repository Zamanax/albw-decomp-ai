typedef unsigned short u16;
typedef unsigned int u32;
extern "C" void func_00656CA4(void*, int) __attribute__((notailcall));
extern "C" void func_00231448(void*);
extern "C" void func_002317C0(void*, float);
struct Ctl { u32 a0; u32 a4; u32 a8; char pad[0xa]; u16 h16; };
struct Obj { char pad[0x14]; struct Ctl* ctl; };
extern "C" void func_0012CAD8(struct Obj* o) {
    struct Ctl* c = o->ctl;
    u16 f = c->h16;
    if (f & 4) {
        func_00656CA4((char*)o + 0x68, 2);
        return;
    }
    if (f & 0x10) {
        func_00656CA4((char*)o + 0x68, 2);
        return;
    }
    if ((f & 8) && c->a8 == 0) {
        func_002317C0((char*)o + 0x44, 1.0f);
        return;
    }
    if (!(f & 0x20)) {
        if (f & 2) return;
    }
    f &= ~2;
    c->h16 = f;
    func_00231448((char*)o + 0x50);
    func_00656CA4((char*)o + 0x68, 0);
}
