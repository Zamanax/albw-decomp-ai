typedef unsigned char u8; typedef signed char s8;
typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;
extern "C" void func_00231448(void*);
extern "C" void func_002317C0(void*, f32);
extern "C" void func_002C00A8(void*);
struct Flag16{u16 v;Flag16(){}Flag16(u16 n):v(n){}void clr(u16 mask){*this=Flag16(v & ~mask);}};
struct Rec{u8 pad0[0x16];Flag16 m16;};
struct Obj {
    u8 pad0[0x14];
    Rec* m14;
    u8 pad1[0xb4 - 0x18];
    u8 mb4;
    void f();
};
void Obj::f() {
    func_00231448((char*)this + 0x38);
    func_00231448((char*)this + 0x44);
    func_00231448((char*)this + 0x50);
    if (mb4 != 0) {
        func_00231448((char*)this + 0x20);
        func_002317C0((char*)this + 0x2c, 1.0f);
    } else {
        func_00231448((char*)this + 0x2c);
        func_002317C0((char*)this + 0x20, 1.0f);
    }
    Rec* r = m14;
    mb4 = 0;
    {Flag16*f=&r->m16;f->clr(0x40);}
    func_002C00A8(m14);
    {Flag16*f=&m14->m16;f->clr(2);}
}
