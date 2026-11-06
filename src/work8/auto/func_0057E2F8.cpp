#include "sead_string.h"

struct Obj57E2F8 {
    char _pad[0x1c];
    void* m1c;
};

u32 func_0049B1BC(void* p, const SafeString& src);
u32 func_0057E254(void* self, const void* name);
void func_0049B2D0(void* p, const SafeString& src);

u32 func_0057E2F8(Obj57E2F8* self, const SafeString& src, void* dst) {
    sead::FixedSafeString<0x20> tmp;
    u32 r;
    if (func_0049B1BC(&tmp, src) != 0) {
        r = func_0057E254(self, &tmp);
    } else {
        r = (u32)self->m1c;
        if (r == 0) return 0;
    }
    if (dst != 0) {
        func_0049B2D0(dst, src);
    }
    return r;
}
