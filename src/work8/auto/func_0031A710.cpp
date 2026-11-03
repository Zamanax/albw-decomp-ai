#include "shared/include/albw_types.h"

// element of the array owned by self->m444 (count at 0xc, data at 0x14)
struct Elem31A { char pad[8]; f32 f8; f32 fC; f32 f10; f32 f14; char pad2[0x1c - 0x18]; u8 b1c; };
struct Arr31A {
    char pad[0xc];
    u32 count;
    u32 max;
    Elem31A* data;
    Elem31A& at(u32 i) { if (i < count) return data[i]; return data[0]; }
};
struct S31A { char pad[0x444]; Arr31A* m444; };

// move v a fraction k of the way towards t
static inline void app(f32& v, f32 t, f32 k) { v += (t - v) * k; }

extern "C" void func_006652A4(void*, int);

extern "C" void func_0031A710(S31A* self) {
    char* p = (char*)self;
    app(*(f32*)(p + 0x3d0), *(f32*)(p + 0x458), 0.05f);
    app(*(f32*)(p + 0x3d8), *(f32*)(p + 0x460), 0.05f);

    Arr31A* arr = self->m444;
    Elem31A& o = arr->at(0);
    if (o.b1c != 0) return;
    f32 z = 0.0f;
    if (o.f10 >= z) {
        if (o.f8 == o.f14) goto doCall;
        return;
    } else {
        if (o.f8 <= z) {} else return;
    }
doCall:
    func_006652A4(p + 0x420, 4);
}
