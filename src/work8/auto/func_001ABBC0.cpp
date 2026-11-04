typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef short s16;typedef unsigned int u32;typedef int s32;typedef float f32;
struct Flag32{u32 v; void change(u32 mask,bool on){if(on)v|=mask;else v&=~mask;} void set(u32 m){change(m,true);} void reset(u32 m){change(m,false);}};
struct S158 { char pad[0x158]; f32 f158; };
struct S2FB9 { char pad[0x3dc]; f32 f3dc; f32 f3e0; f32 f3e4; char p3e8[0x40c-0x3e8]; S158* p40c; char p410[0x59c-0x410]; Flag32 m59C; char g[0x5a8-0x5a0]; char c5A8[0x20]; char p5c8[0x9b8-0x5c8]; f32 f9b8; };
extern "C" void func_004FCD5C(void*,bool);
extern "C" void func_004FCDF4(void*,bool);
extern "C" void func_004FD038(void*,bool);
void func_001ABBC0(S2FB9* p) {
    p->f3dc = 0.0f;
    p->f3e0 = 0.0f;
    p->f3e4 = 0.0f;
    p->m59C.change(1,false);
    func_004FCD5C(p->c5A8,false);
    p->m59C.change(2,false);
    func_004FCDF4(p->c5A8,false);
    p->m59C.change(4,false);
    func_004FD038(p->c5A8,false);
    if (p->p40c) p->p40c->f158 = 0.0f;
    p->f9b8 = 0.0f;
}
