#include "../../work7/ds2/ds2.h"
extern void* data_0070FB60;
extern void* data_0070B728;
void func_00292460(void*, s32);
void func_004CDF40(void*, s32, s32);
struct Pair36DAF4 { u32 cur; u32 max; };
struct Sub36DAF4 { char pad[0x318]; Pair36DAF4 pr; };
struct Obj36DAF4 { char pad[0x800]; Sub36DAF4 sub; };
u32 func_0036DAF4(void* self, s32 k) {
    Obj36DAF4* o = (Obj36DAF4*)self;
    if (k != 0) return 1;
    if (o->sub.pr.cur == 0x0) {
        func_00292460(data_0070FB60, 0);
    } else if (o->sub.pr.cur == 0x4b) {
        func_004CDF40(data_0070B728, 0x186, 1);
    }
    Pair36DAF4 t = o->sub.pr;
    if (t.cur < t.max) {
        o->sub.pr.cur = t.cur + 1;
        return 0;
    }
    return 1;
}
