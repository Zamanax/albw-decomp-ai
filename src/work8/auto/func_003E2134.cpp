// 0x3E2134: function-local static 3x4 identity matrix (guarded init)
#include "sead_math.h"

struct IdentityMtx34 {
    Mtx34 m;
    IdentityMtx34() {
        m.m[0][0] = 1.0f; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f; m.m[0][3] = 0.0f;
        m.m[1][0] = 0.0f; m.m[1][1] = 1.0f; m.m[1][2] = 0.0f; m.m[1][3] = 0.0f;
        m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f; m.m[2][3] = 0.0f;
    }
};

Mtx34* func_003E2134() {
    static IdentityMtx34 o;
    return &o.m;
}
