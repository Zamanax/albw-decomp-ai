#include "flags.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct TypeInfo { const void* vt; };
extern u32 data_00725ED4;
extern TypeInfo data_00725ED8;
extern const char ro_006F6428[];
extern "C" int __cxa_guard_acquire(u32* g);
extern "C" void __cxa_guard_release(u32* g);

struct Actor;
struct ActorVt { int (*checkDerived)(Actor* a, const TypeInfo* ti); };
struct Actor { const ActorVt* vt; };

extern "C" void func_0051D2F4(s32* cur, s32 target, f32 rate, s32 a, s32 b);

// The state machine at +0x90C: its three calls are per-owner instantiations of the state
// manager's callExit / callStep / callEnter.  The game never tail-calls func_0065AF00 (0 b / 15 bl
// in the image), so its declaration carries the no-tail-call attribute.
struct StateSoldier {
    u32 frame;
    s8 current, previous;
    u8 pad6[0x24 - 6];
    void func_0065AE94(s32 n);
    void func_003931EC(s32 n);
    void func_0065AF00() __attribute__((notailcall));
    void change(s32 n) { func_0065AE94(n); func_003931EC(n); func_0065AF00(); }
};

struct Soldier {
    u8 pad0[0x59c];
    Flag32 m59C;
    u8 pad5a0[0x8cc - 0x5a0];
    s32 m8CC;
    u8 pad8d0[0x8dc - 0x8d0];
    s32 m8DC;
    u8 pad8e0[0x90c - 0x8e0];
    StateSoldier m90C;
    u8 pad930[0x96c - 0x930];
    void (Actor::*mFunc)();
    u8 pad974[0x97c - 0x974];
    u32 m97C;
};

static const TypeInfo* getTI(void)
{
    if (!(data_00725ED4 & 1) && __cxa_guard_acquire(&data_00725ED4)) {
        { TypeInfo* t = &data_00725ED8; t->vt = ro_006F6428; }
        __cxa_guard_release(&data_00725ED4);
    }
    return &data_00725ED8;
}

static bool isDerived(Actor* a)
{
    const TypeInfo* ti = getTI();
    return a->vt->checkDerived(a, ti) != 0;
}

static Actor* dynCast(Actor* a) { return isDerived(a) ? a : 0; }

void func_006730D4(Soldier* self)
{
    func_0051D2F4(&self->m8CC, self->m8DC, 0.4f, 0xb60b60, 0x38e38e3);
    if (self->m97C != 0) return;
    self->m59C.set(0x100);
    if (self->mFunc) {
        Actor* a = dynCast((Actor*)self);
        if (a != 0) {
            (a->*self->mFunc)();
            return;
        }
    }
    self->m90C.change(1);
}
