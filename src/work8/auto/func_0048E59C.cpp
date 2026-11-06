#include "sead_string.h"
void* func_0057E2F8(void*, void*, void*);
void func_00489F28(void*, void*, void*, void*, float);
void func_0048E59C(void* self, void* a, void* key, void* c, float s) {
    sead::FixedSafeString<0x100> buf;
    void* r = func_0057E2F8(self, key, &buf);
    if (r) func_00489F28(r, a, &buf, c, s);
}
