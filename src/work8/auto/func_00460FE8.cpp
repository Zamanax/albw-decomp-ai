#include "albw_types.h"

struct Obj { u8 pad[0xc]; u16 a; u16 b; f32 c; u32 d; };

extern "C" void func_00460FE8(Obj* o) {
    u16* h = &o->a;
    h[0] = 0;
    h[1] = 0xffff;
    o->c = 0.0f;
    o->d = 0;
}
