#include "vec3.h"
extern "C" void func_004BC7BC(char* p);
extern Vec3 data_00775FD4;
extern "C" void func_004DB824(char* p) {
    *(float*)(p + 0x3ac) = -1.0f;
    Vec3* d1 = (Vec3*)(p + 0x368);
    d1->setCopy(data_00775FD4);
    Vec3* d2 = (Vec3*)(p + 0x3d0);
    d2->setCopy(data_00775FD4);
    *(float*)(p + 0x834) = 0.0f;
    func_004BC7BC(p);
}
