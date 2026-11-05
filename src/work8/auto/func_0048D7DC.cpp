// func_0048D7DC: stack-local sead::FixedSafeString<128>, then two virtual calls that receive it.
#include "sead_string.h"

struct B48D7DC {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34();
    virtual void v38(s32 a, sead::BufferedSafeString* s);
};

struct A48D7DC {
    virtual void v00(); virtual void v04();
    virtual void get(sead::BufferedSafeString* s);
    void f(B48D7DC* b, s32 c);
};

void A48D7DC::f(B48D7DC* b, s32 c) {
    sead::FixedSafeString<128> s;
    get(&s);
    b->v38(c, &s);
}
