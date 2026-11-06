#include "sead_string.h"

struct Ent12 {
    void* p;
    u32 b;
    u32 c;
};

extern void* data_00711F50;
extern Ent12 data_007120E4[];
extern u32 func_00539000(void* p, const SafeString& s);
extern void func_004994B0(const SafeString* s, void* e);
extern void func_00297138(void* p, const SafeString& s);

void func_0032140C(void*, u32 a) {
    if (a >= 0xd) return;
    sead::FixedSafeString<0x40> s;
    if (a == 0) {
        if (func_00539000(data_00711F50, s) == 0) return;
    } else {
        Ent12* e = &data_007120E4[a];
        func_004994B0(&s, e->p);
    }
    func_00297138(data_00711F50, s);
}
