#include "sead_string.h"

struct Iface {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual s32 v4(void* a);
};

struct Owner {
    char pad[0x34];
    Iface* m34;
};

struct Named : SafeString {
    char pad[0x18];
    Iface* m20;
};

extern "C" s32 func_0049B570(void* dst, void* src);
extern "C" Iface* func_0048B814(Owner* p, void* s);

s32 func_0048BA30(Owner* p, Named* a) {
    Iface* obj = a->m20;
    if (obj == 0) {
        sead::FixedSafeString<0x20> s;
        if (func_0049B570(&s, a) == 0) {
            obj = p->m34;
        } else {
            obj = func_0048B814(p, &s);
        }
    }
    return obj->v4(a);
}
