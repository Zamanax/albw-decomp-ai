#include "albw_types.h"

struct Obj18 {
    char pad0[0x18];
    void* m;
};

extern void* data_00711F50;
extern "C" void* func_00297674(void* d, void* o);
extern "C" void func_0014E640(void* a, void* b);

extern "C" void* func_0029788C(void* p) {
    void* r;
    Obj18* s = static_cast<Obj18*>(p);
    if (s->m != 0) {
        Obj18 * t1 = s;
        r = func_00297674(data_00711F50, t1->m);
        if (r) {
            void * t0 = t1->m;
            func_0014E640(t0, r);
        }
    } else {
        r = func_00297674(data_00711F50, 0);
    }
    if (r) {
        ((u8*)r)[0x4d] = 1;
    }
    return r;
}
