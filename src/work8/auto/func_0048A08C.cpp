#pragma O2
#pragma Otime
typedef unsigned char u8;
typedef unsigned int u32;
struct Self0048A08C { void** vt; char _4[0x48]; u8 m4c; };
struct Other0048A08C { char _0[0x10]; void* m10; void* m14; };
typedef u32 (*VFa0048A08C)(Self0048A08C* s, Other0048A08C* o);
typedef u32 (*VFb0048A08C)(Self0048A08C* s, Other0048A08C* o);

u32 func_0048A08C(Self0048A08C* self, Other0048A08C* other) {
    if (self->m4c == 0) return 0;
    if (other == 0) return 0;
    VFa0048A08C f = (VFa0048A08C)self->vt[8];
    if (f(self, other) == 0) return 0;
    VFb0048A08C g = (VFb0048A08C)self->vt[12];
    u32 r = g(self, other);
    if (r == 0) return 0;
    other->m10 = 0;
    other->m14 = 0;
    return r;
}
