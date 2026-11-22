#include "vec3.h"

// Position = velocity * rate + base, written with sead's vector operators (SeadVec3): the
// setMul result is copied out of the operator's own slot before setAdd reads it.
struct Obj003879AC {
    char pad0[0x58];
    SeadVec3 m58;
    char pad64[0x7c - 0x64];
    float m7c;
    char pad80[0x94 - 0x80];
    SeadVec3 m94;
};

void func_003879AC(Obj003879AC* self, const SeadVec3* base) {
    self->m58 = self->m94 * self->m7c + *base;
}
