#include "vec3.h"

extern char* data_00708998;
extern "C" unsigned int func_004D838C(void*, float, float, float);
extern "C" void func_001E8268(void*, void*, void*, void*);

extern "C" unsigned int func_0030CBE4(char* self) {
    if (data_00708998 == 0) return 1;
    func_004D838C(self + 0x38, 0.05f, 0.02f, 3.4028235e38f);
    Vec3 v = *(Vec3*)(self + 0x38);
    v.x = v.x + *(float*)(self + 0x74);
    v.z = v.z + *(float*)(self + 0x78);
    char* o = *(char**)(data_00708998 + 0x18);
    func_001E8268(o, self + 0x30, (void*)&v, self + 0x44);
    return *(unsigned int*)(o + 0x10c) >> 31;
}
