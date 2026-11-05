typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;


#include "vec3.h"



#include "timer.h"


class Obj1D6 {
public:
    char pad000[0x3dc];
    Vec3 m3dc;
    char pad3e8[0x427 - 0x3e8];
    u8 m427;
    char pad428[0x500 - 0x428];
    Timer m500;
    char pad50c[0x514 - 0x50c];
    f32 m514;
    char pad518[0x530 - 0x518];
    u8 m530;
    void func_002880F0();
};

void Obj1D6::func_002880F0() {
    m427 = 1;
    f32 z = 0.0f;
    m3dc.x = z;
    m3dc.y = z;
    m3dc.z = z;
    m500.startRef(80);
    m514 = z;
    m530 = 1;
}
