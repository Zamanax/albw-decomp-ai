// func_0048D854: object constructor with an embedded sead::FixedSafeString<64> (inlined).
#include "sead_string.h"

struct Obj48D854 {
    Obj48D854();
    virtual ~Obj48D854();
    s32 m4;
    s32 m8;
    s32 mC;
    sead::FixedSafeString<64> mStr;
};

Obj48D854::Obj48D854() : m4(-1), m8(-1), mC(0) {}
