// func_001097A4: constructor with an embedded default-constructed sead::SafeString: its
// mStringTop is set to cNullChar (ro_006C57E0), not to null.
#include "sead_string.h"

struct S1097A4 {
    S1097A4();
    virtual ~S1097A4();
    u8 m4;
    u32 m8;
    u32 mC;
    u32 m10;
    f32 m14;
    u32 m18;
    u32 m1C;
    sead::SafeString m20;
    u32 m28;
    u32 m2C;
};

S1097A4::S1097A4() : m4(0), m8(0), mC(0), m10(0), m14(1.0f), m18(0), m1C(0), m28(0), m2C(0) {}
