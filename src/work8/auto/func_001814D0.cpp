typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

struct VB {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(u32, s32);
};


#include "vec3.h"

struct Timer3 {
    u32 cur, max; f32 rate;
    void start(u32 n, u32 c = 0) { max = n; if (n) rate = 1.0f / n; else rate = 0; cur = c; }
};

struct Obj : VB {
    u8 pad0[0x2e0 - 4];
    u32 flags;
    u8 pad2e4[0x3dc - 0x2e4];
    Vec3 velocity;
    u8 pad3e8[0x9a4 - 0x3e8];
    Timer3 timer;
};

void f1814D0(Obj* p) {
    p->flags |= 2;
    p->v43(4, -1);
    p->timer.start(90);
    p->velocity.x = 0;
    p->velocity.y = 0;
    p->velocity.z = 0;
}
