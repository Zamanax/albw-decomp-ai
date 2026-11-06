#include "albw_types.h"

struct WorldMgr652FBC;
extern WorldMgr652FBC* data_007142C8;
extern "C" bool func_0058D6D0(WorldMgr652FBC*);
extern "C" void func_0051C8D0(WorldMgr652FBC*);

struct Obj652FBC {
    u8 pad0[0x9d4];
    u8 m9d4;
};

u32 func_00652FBC(Obj652FBC* self) {
    if (func_0058D6D0(data_007142C8)) return 1;
    if (self->m9d4 == 0) {
        self->m9d4 = 1;
        func_0051C8D0(data_007142C8);
    }
    return 0;
}
