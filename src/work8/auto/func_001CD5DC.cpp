#define OBJ1D6_EXTRA void func_001CD5DC();
// agent4 (round 5): breakable/carryable object whose state functions live at 0x1D6000..0x1D8000
// (StateMgr PMF table in .constdata 0x6A27E4.., strings SE_Rupee_BOUND / SE_*_BREAK nearby).
// Base class methods live at 0x37Cxxx; StateMgr at +0x4D4 (changeState 0x65C988, weak: never tail-called).
#ifndef AGENT4_OBJ1D6_H
#define AGENT4_OBJ1D6_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

namespace sead {
template <typename T>
class SafeStringBase {
public:
    SafeStringBase(const T* s) : mStringTop(const_cast<T*>(s)) {}
    virtual ~SafeStringBase() {}
    virtual void assureTerminationImpl_() const {}
    T* mStringTop;
};
typedef SafeStringBase<char> SafeString;
}

struct SEHandle {               // 0x60-byte stack object, ctor 0x10A464, dtor 0x25B84C
    SEHandle();
    ~SEHandle();
    bool isValid();             // 0x539200
    void setVolume(f32 v, s32 a);  // 0x25B838
    u8 buf[0x60];
};


#include "vec3.h"


struct StateMgr4D4 {
    void func_0065C310(s32 st);   // 0x65C310 (StateMgr changeState; bl target in 001CD5DC)
};
struct Obj46C {
    bool test3929C4();        // 0x3929C4
    void f393164();           // 0x393164
};

struct Obj40C { void f4CF478(s32 a, s32 b); };   // 0x4CF478
struct Obj410 { void f151148(s32 a); };          // 0x151148
struct Eff;
struct EffHandle { Eff* p; u32 id; };
struct Anim344 {
    EffHandle start(const char* name);   // 0x4A1B9C (sret)
};
struct Sub4 { void f547514(); };                 // 0x547514 on this+4
struct Pos51C { u8 b; };
struct Mgr70FB60 {
    bool f556B94();                              // 0x556B94
    bool f36174C(s32 id, Pos51C* p);             // 0x36174C
    bool f255AB4(u32 id);                        // 0x255AB4
    s32 f255AB4i(u32 id);                        // 0x255AB4 (int-return experiment)
    s8 f255AB4s8(u32 id);
};
extern Mgr70FB60* data_0070FB60;


#include "timer.h"


bool func_00392E48(const Vec3* pos, s32 a, s32 b, s32 c);  // 0x392E48 (pos, 1, 0, 0)
void func_00115C54(Vec3* out, const Vec3* a, const Vec3* b);  // Vec3 setAdd

namespace sead {
struct SinCosSample { f32 sin_val, sin_delta, cos_val, cos_delta; };
}
extern const sead::SinCosSample ro_006C3AB8[];
inline f32 sinIdx(u32 a) {
    u32 idx = a >> 24;
    f32 frac = (a & 0xffffff) * (1.0f / 0x1000000);
    return ro_006C3AB8[idx].sin_val + ro_006C3AB8[idx].sin_delta * frac;
}

struct SoundMgr { void playSE(const sead::SafeString& name, s32 a); };  // 0x4EA104
extern SoundMgr* data_00711F50;

class Base37C {
public:
    bool f37C668();           // 0x37C668
    void f37CBE0();           // 0x37CBE0
    void f37C574(s32 a);      // 0x37C574
    void f37C6F0(s32 a);      // 0x37C6F0
    void f37D414();           // 0x37D414
    void f588C14(s32 a, s32 b);  // 0x588C14 (this, 0, 1)
    void playSE(const sead::SafeString& name, s32 a);  // 0x150A84 ActorBase::playSE
    const Vec3& f559B54();    // 0x559B54
    void playSE(const sead::SafeString& name, struct SEHandle* h);  // 0x150A84 with a handle out-param
    bool func_00521064();           // 0x521064
    bool func_00520EE4();           // 0x520EE4
    bool func_00520ED8();           // 0x520ED8
    bool func_00520FF8();           // 0x520FF8
    bool func_00521074();           // 0x521074
};

class Obj1D6 : public Base37C {
public:
#ifdef OBJ1D6_EXTRA
    OBJ1D6_EXTRA
#endif
    char pad000[4];
    Sub4 m4;
    char pad005[0xc - 5];
    f32 m0c;                 // ground height? compared with m3d0.y
    char pad010[0x2c - 0x10];
    u16 m2c;
    char pad02e[0x36 - 0x2e];
    u16 m36;
    char pad038[0x5a - 0x38];
    s16 m5a;
    char pad05c[0x2d7 - 0x5c];
    u8 m2d7;
    char pad2d8[0x344 - 0x2d8];
    Anim344* m344;
    char pad348[0x3b8 - 0x348];
    u32 m3b8;
    char pad3bc[0x3d0 - 0x3bc];
    Vec3 m3d0;               // position
    Vec3 m3dc;               // velocity? (x, y, z)
    char pad3e8[0x40c - 0x3e8];
    Obj40C* m40c;
    Obj410* m410;
    char pad414[0x424 - 0x414];
    u8 m424;
    u8 m425;
    u8 m426;
    u8 m427;
    char pad428[0x42c - 0x428];
    u16 m42c;
    char pad42e[0x46c - 0x42e];
    Obj46C m46c;
    char pad46d[0x479 - 0x46d];
    u8 m479;
    char pad47a[0x47c - 0x47a];
    u8 m47c;
    char pad47d[0x4d4 - 0x47d];
    StateMgr4D4 m4d4;
    char pad4d5[0x4d8 - 0x4d5];
    s8 m4d8;
    char pad4d9[0x4f8 - 0x4d9];
    Timer m4f8;
    char pad504[0x50c - 0x504];
    f32 m50c;
    u32 m510;                // item id? passed to 0x255AB4(*data_70FB60, m510)                 // s8: the ldrb+separate beq (no if-conversion) of 1D66C0 needs it (KB#46)
    u8 m514;
    u8 m515;
    u8 m516;
    char pad517[0x51c - 0x517];
    Pos51C m51c;
    char pad51d[0x52c - 0x51d];
    u8 m52c;
    u8 m52d;
    u8 m52e;
    char pad52f[0x530 - 0x52f];
    Vec3 m530;               // landing target (x,z used)
    u8 m53c;
    char pad53d[0x540 - 0x53d];
    f32 m540;                // = m3d0.y (start height)
    f32 m544;                // height drop
    Timer m548;
    u8 m554;
};

#endif
void Obj1D6::func_001CD5DC() {
    if (m3d0.y <= m0c && !func_00392E48(&m3d0, 1, 0, 0)) {
        m4d4.func_0065C310(5);
    } else if (func_00520ED8()) {
        if (func_00520FF8())
            m4d4.func_0065C310(4);
        else
            m4d4.func_0065C310(2);
    } else if (func_00521074()) {
        m42c = 2;
        m4d4.func_0065C310(9);
    } else if (func_00521064() && m4d8 != 5) {
        m4d4.func_0065C310(2);
    }
}
