typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

struct Vec3 {
    f32 x, y, z;
};

struct StateMgr {
    u32 raw;
};

struct Timer {
    u32 cur;
    u32 max;
    f32 rate;
    bool step() {
        if (cur < max) { cur++; return true; }
        return false;
    }
};

class Obj1D6;
bool func_00392E48(const Vec3* pos, s32 a, s32 b, s32 c);
bool func_00520ED8(Obj1D6* self);
bool func_00520FF8(Obj1D6* self);
bool func_00521074(Obj1D6* self);
bool func_00521064(Obj1D6* self);
void func_00661480(StateMgr* mgr, s32 st);

class Obj1D6 {
public:
    void func_00288510();
    char pad000[0x0c];
    f32 m0c;
    char pad010[0x3d0 - 0x10];
    Vec3 m3d0;
    char pad3dc[0x4dc - 0x3dc];
    StateMgr m4dc;
    u8 m4e0;
    char pad4e1[0x534 - 0x4e1];
    Timer m534;
};

void Obj1D6::func_00288510() {
    if (m534.step())
        return;
    if (m3d0.y <= m0c && !func_00392E48(&m3d0, 1, 0, 0)) {
        func_00661480(&m4dc, 6);
    } else if (func_00520ED8(this)) {
        if (func_00520FF8(this))
            func_00661480(&m4dc, 5);
        else
            func_00661480(&m4dc, 3);
    } else if (func_00521074(this)) {
        func_00661480(&m4dc, 3);
    } else if (func_00521064(this)) {
        if (m4e0 != 6)
            func_00661480(&m4dc, 0);
    }
}
