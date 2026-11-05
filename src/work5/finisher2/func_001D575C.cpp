// MATCH (finisher2): update the by-value Vec3 member in place (p.x = ..; p.x += 8) instead of a separate f32 x copied into p.x -> vadd into s16 in place.
typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef unsigned int u32; typedef int s32; typedef float f32;

#include "vec3.h"

inline void copyVec(Vec3* d, const Vec3& s) { *d = s; }

#include "timer.h"

struct Mgr708998;
extern Mgr708998* data_00708998;
Vec3* func_00588F08(Mgr708998* m);
struct A3 {
    char pad0[0x3d0];
    Vec3 m3d0;
    char pad3dc[0x468 - 0x3dc];
    Vec3 m468;
    char pad474[0x4a8 - 0x474];
    Timer m4a8;
    char pad4b4[2];
    u16 m4b6;
    char pad4b8[0x4c1 - 0x4b8];
    u8 m4c1;
    u8 m4c2;
    char pad4c3[3];
    u8 m4c6;
    bool func_001D47B4(Vec3 end);
    void func_001D575C();
};
void A3::func_001D575C() {
    Vec3 p = m468;
    p.x = func_00588F08(data_00708998)->x;
    if (func_00588F08(data_00708998)->x < m3d0.x) p.x += 8.0f;
    else p.x -= 8.0f;
    p.z = m3d0.z;
    if (func_001D47B4(p)) {
        p.x = func_00588F08(data_00708998)->x;
        if (func_00588F08(data_00708998)->x < m3d0.x) p.x -= 8.0f;
        else p.x += 8.0f;
        if (func_001D47B4(p)) m4c6 = 1;
    }
    copyVec(&m468, p);
    m4c2 = 0;
    m4a8.startRef(0x23);
    m4b6 = 0;
    m4c1 = 2;
}
