typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct Ctl { u8 pad[0xc]; };
extern "C" void func_00231448(void* c);
extern "C" void func_002317C0(void* c, f32 v);
struct Obj20C;
extern "C" void func_004727B8(Obj20C* o, s32 v);
struct Obj210 { u8 pad[0x5d]; u8 m5D; };
extern "C" void func_0047E8C4(Obj210* o, s32 a, s32 b);
struct Obj14 {
    u8 pad[4];
    s32 m4;
    u8 pad8[0x16 - 8];
    void setM4(s32 p) { u32 b = (u32)p; if (b) b = 1; m4 = p; u16* pf = &m16.v; u16 fl = *pf; if (b) fl |= 0x40; else fl &= (u16)~0x40; *pf = fl; }
    struct BF { u16 v; void change(u16 m, bool on) { if (on) v |= m; else v &= ~m; } } m16;
};
extern "C" void func_002C00A8(Obj14* o);
struct Obj214;
extern "C" void func_0012C790(u32 v);
extern "C" void func_00448FD0(void* self);

struct Arr188 { u32 d[4]; u32& at(u32 i) { if (i < 4) return d[i]; return d[0]; } };

struct Self {
    u8 pad0[0x14];
    Obj14* m14;
    u8 pad18[0xf8 - 0x18];
    Ctl mF8;
    Ctl m104;
    Ctl m110;
    Ctl m11C;
    u8 pad128[0x188 - 0x128];
    Arr188 m188;
    u8 pad198[0x208 - 0x198];
    u8 m208;
    u8 pad209[3];
    Obj20C* m20C;
    Obj210* m210;
    Obj214* m214;
    u8 pad218[0x284 - 0x218];
    u8 m284;
    u8 pad285[0x292 - 0x285];
    u8 m292;
    void update();
};

void Self::update()
{
    m292 = 1;
    f32 one = 1.0f;
    s32 zero = 0;
    s32* pz = &zero;
    if (m210->m5D == 0) {
        func_00231448(&mF8);
        func_002317C0(&m104, one);
        func_004727B8(m20C, 0);
        func_002C00A8(m14);
        Obj14* o = m14;
        o->setM4(*pz);
        func_0012C790((u32)m214);
        if (m208 != 0) func_00448FD0(this);
        for (s32 i = 0; i < 4; i++) func_0012C790(m188.at((u32)i));
    }
    func_00231448(&m110);
    func_002317C0(&m11C, one);
    func_0047E8C4(m210, 0, 0);
    m284 = (u8)*pz;
}
