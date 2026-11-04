typedef unsigned int u32; typedef unsigned short u16; typedef unsigned char u8;
struct Obj { u32 a; u32 b; u32 c; u8 p0[0x18-12]; float f; u8 p1[0x64-0x1c]; u16 s; };
void func_004355D4(Obj* o) {
    o->a = 0; o->b = 0; o->c = 0;
    o->f = 1.0f;
    u32 t = 0x1f;
    o->s = *(u16*)&t;
}
