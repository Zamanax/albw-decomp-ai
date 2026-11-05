#include "sead_rtti.h"
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed char s8;
typedef int s32;

class ActorBase;
typedef void (ActorBase::*Pmf)();

struct StateSub {
    u32 frame;
    s8 current, previous;
    u8 pad[2];
    void func_0065AE94(s32);
    void func_003931EC(s32);
    void func_0065AF00() __attribute__((notailcall));
    void change(s32 n) { func_0065AE94(n); func_003931EC(n); func_0065AF00(); }
};

class ActorBase {
    SEAD_RTTI_BASE(ActorBase)
    u8 pad0[0x90c - 4];
    StateSub state;
    u8 pad1[0x96c - 0x90c - sizeof(StateSub)];
public:
    Pmf pmf;
    void func_00672588();
};

class Target : public ActorBase {
    SEAD_RTTI_OVERRIDE(Target, ActorBase)
};

template <typename T, typename S> inline bool IsDerivedFrom(const S* o) {
    const sead::RuntimeTypeInfo::Interface* ti = T::getRuntimeTypeInfoStatic();
    return o != 0 && o->checkDerivedRuntimeTypeInfo(ti);
}
template <typename T, typename S> inline T* DynamicCast(S* o) {
    return IsDerivedFrom<T, S>(o) ? static_cast<T*>(o) : 0;
}

struct Game { u8 pad[0x44]; u32 m44; };
extern Game* data_0070B728;

void ActorBase::func_00672588()
{
    if (data_0070B728->m44) return;
    if (pmf) {
        Target* t = DynamicCast<Target>(this);
        if (t != 0) {
            (t->*pmf)();
            return;
        }
    }
    state.change(3);
}
