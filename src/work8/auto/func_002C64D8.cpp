typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;
struct Timer {
    u32 cur, max; f32 rate;
    void start(u32 n, u32 c = 0) { max = n; if (n) rate = 1.0f / (f32)n; else rate = 0.0f; cur = c; }
};
namespace sead {
class SafeString {
public:
    SafeString(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
}
struct Sub484 { char p0[0x44]; u8 m44; };
struct C {
    char pad0[0x484];
    Sub484* m484;
    char pad1[0x494 - 0x488];
    u8 m494;
    char pad2[0x4e4 - 0x495];
    Timer mTimer;
    void f();
};
void func_001E4090(C* self, s32 a);   // 0x1E4090
f32 func_0052F864(C* self);           // 0x52F864
void func_00150A84(C* self, const sead::SafeString& name, s32 v);   // 0x150A84
void C::f() {
    m494 = 1;
    Sub484* p = m484;
    p->m44 = 0;
    func_001E4090(this, 0);
    Timer* t = &mTimer;
    u32 n = (u32)func_0052F864(this);
    t->start(n);
    func_00150A84(this, sead::SafeString("SE_DoorWallHide_OPEN"), 0);
}
