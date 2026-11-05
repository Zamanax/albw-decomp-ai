#include "flags.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef int s32;

struct TypeInfo { const void* vt; };
extern u32 data_00725ED4;
extern TypeInfo data_00725ED8;
extern const char ro_006F6428[];
extern "C" int __cxa_guard_acquire(u32* g);
extern "C" void __cxa_guard_release(u32* g);

struct Actor;
struct ActorVt { int (*checkDerived)(Actor* a, const TypeInfo* ti); };
struct Actor { const ActorVt* vt; };

extern "C" int func_0058A8F0(void* self);

// State machine at +0x90C. change(3) is the three-call sequence the image makes at that offset.
// func_0065AF00 is called and then returns (bl followed by pop), so it is declared notailcall.
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
    u8 pad0[0x90C];
    StateSoldier m90C;
    u8 pad930[0x96C - 0x930];
    void (Actor::*mFunc)();
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

void func_00672688(Soldier* self)
{
    if (func_0058A8F0(self) != 0) {
        if (self->mFunc) {
            Actor* a = dynCast((Actor*)self);
            if (a != 0) {
                (a->*self->mFunc)();
                return;
            }
        }
        self->m90C.change(3);
    }
}
