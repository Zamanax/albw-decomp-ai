#include "vec3.h"
#include "flags.h"
#include "albw_types.h"

extern "C" void func_002F8DE4(void* p, s32 a, s32 b, s32 c);
extern "C" void func_004FAD10(void* p);
extern "C" void func_004D80A4(Vec3* out, u32 angle, f32 scale);
extern "C" void func_00115C54(Vec3* out, const Vec3* a, const Vec3* b);
extern "C" void* func_0054D884(void* base, u32 idx);

struct En {
    u8 pad00[0x30];
    u16 m30;        // 0x30
    u8 pad32[0x2d0 - 0x32];
    u8* m2d0;       // 0x2d0
    u8 pad2d4[0x368 - 0x2d4];
    Vec3 m368;      // 0x368
    u8 pad374[0x3d0 - 0x374];
    Vec3 m3d0;      // 0x3d0
    Vec3 m3dc;      // 0x3dc
    u32 m3e8;       // 0x3e8
    u8 pad3ec[0x59c - 0x3ec];
    Flag32 m59c;    // 0x59c
    u8 pad5a0[0x909 - 0x5a0];
    u8 m909;        // 0x909
    u8 pad90a[0x97c - 0x90a];
    u32 m97c;       // 0x97c
    u8 pad980[0x98e - 0x980];
    u8 m98e;        // 0x98e
};

inline void copyVec2(Vec3* a, Vec3* b, const Vec3& s) { *a = s; *b = s; }
void func_00672404(En* p) {
    En * t5 = p;
    if (t5->m30 == 1) {
        Vec3 tmp;
        func_004D80A4(&tmp, t5->m3e8, -2.0f);
        func_00115C54(&tmp, &tmp, &p->m3d0);
        copyVec2(&p->m368, &p->m3d0, tmp);
        En * t6 = p;
        t6->m97c = 0x1e;
        f32* yp = (f32*)func_0054D884(0x18 + t6->m2d0, 0);
        f32 y = yp[1];
        f32 h = 0.5f * y;
        u32 t9 = p->m3e8;
        s32 t8 = t9;
        func_004D80A4(&p->m3dc, t8, 0.033333335f * (2.0f + h));
    } else {
        p->m97c = 0;
        Vec3* t7 = &p->m3dc;
        t7->y = t7->x = 0.0f;
        p->m3dc.z = 0.0f;
    }
    func_002F8DE4(p, 2, 0, 0);
    func_004FAD10(p);
    p->m59c.reset(0x100);
    p->m59c.reset(0x30);
    p->m59c.reset(0x80);
    p->m909 = 0;
    p->m98e = 1;
}
