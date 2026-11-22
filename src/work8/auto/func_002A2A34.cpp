#include "vec3.h"

extern "C" int func_00556E64(char* singleton);
extern "C" void func_001E8440(char* obj, const Vec3* pos, unsigned int flag);
extern "C" int func_004F68AC(char* self, unsigned int flag);
extern "C" char* data_00708998;
extern "C" char* data_0070FB60;
extern "C" Vec3 g_0073D038;

extern "C" int func_002A2A34(char* self, unsigned int flag)
{
    int st = *(signed char*)(self + 0x900 + 0xe4);
    if (!(st == 0 || st == 0xe) && !(st == 0xf || st == 0x12)) {
        if (data_0070FB60 != 0) {
            if (func_00556E64(data_0070FB60) == 0) {
                char* d = data_00708998;
                unsigned int r5 = 0;
                if (d != 0) {
                    r5 = *(unsigned int*)(d + 0x18);
                }
                if (r5 != 0) {
                    Vec3 t = *(Vec3*)(self + 0x3d0);
                    t += g_0073D038;
                    func_001E8440((char*)r5, &t, 1);
                }
            }
        }
    }
    return func_004F68AC(self, flag);
}
