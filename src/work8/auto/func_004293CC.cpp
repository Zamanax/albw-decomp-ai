#include "../../work7/ds6/ds6.h"

struct AEntry {
    u32 m0, m4;
    f32 m8;
    u32 mC;
    f32 m10;
    f32 m14;
    u32 m18;
    u8 m1c;
    bool isEnd() const {
        if (m10 >= 0.0f) return m8 == m14;
        return m8 <= 0.0f;
    }
};
struct AArr {
    u32 pad[3];
    s32 mNum;
    s32 mMax;
    AEntry* mData;
    AEntry* at(s32 i) { if (i < mNum) return &mData[i]; return &mData[0]; }
};
struct Mgr { char _pad[4]; void* m4; };
struct Mid {
    char _p0[0x8dc];
    AArr* m8dc;
    char _p1[0x5c];
    Mgr* m93c;
};
struct Obj { char _pad[0x48]; Mid* m48; };
extern "C" void func_002B8AFC(Mid*);
extern "C" bool func_003ABB24(Mgr*, int, bool);
extern "C" void func_003B147C(void*, int, int);

void func_004293CC(Obj* self) {
    func_002B8AFC(self->m48);
    AEntry* e = self->m48->m8dc->at(0);
    if (e->m1c == 0 && e->isEnd()) {
        Mgr* mgr = self->m48->m93c;
        int one = 1;
        if (func_003ABB24(mgr, one, true)) {
            func_003B147C(mgr->m4, one, 1);
        }
    }
}
