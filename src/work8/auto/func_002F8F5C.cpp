typedef unsigned int u32;
typedef unsigned short u16;

struct Vec3 { u32 x, y, z; };
struct Global { u16 func_00581D60(); };
struct Game;
struct SpawnParam;

extern u32 g_0074B6DC[];
extern Global* data_0070C8E0;
extern Game* data_00706E20;
extern void func_002DFF7C(SpawnParam*);
extern u32 func_0019B04C(u32);
extern void func_004C43E0(Game*, const SpawnParam*);

struct SpawnParam {
    SpawnParam() : m1c(0), m20(0), m24(0), m48(0), m4c(0), m2c0(0) { func_002DFF7C(this); }
    u32 m0;
    Vec3 m4;
    u32 m10[3];
    u32 m1c, m20, m24;
    u16 m28, m2a, m2c, m2e;
    char p30[0x44 - 0x30];
    float m44;
    u32 m48, m4c;
    u16 m50;
    char p52[0x2c0 - 0x52];
    u32 m2c0;
};

void func_002F8F5C(const Vec3& pos, u32 idx)
{
    SpawnParam p;
    p.m0 = func_0019B04C(g_0074B6DC[idx]);
    p.m50 = data_0070C8E0->func_00581D60();
    p.m20 = 0;
    p.m4.x = pos.x;
    p.m4.y = pos.y;
    p.m4.z = pos.z;
    p.m2a = 0xffff;
    p.m2c = 2;
    p.m2e = 1;
    func_004C43E0(data_00706E20, &p);
}
