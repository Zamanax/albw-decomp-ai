#include "sead_container.h"

typedef unsigned int u32;
struct Ev;
struct Obj;

extern Ev* data_00711F50;
extern u32 func_00297674(Ev* d, u32 p);
extern u32 func_0019A4C4(u32 obj, u32 p);
extern u32 func_0019AA88(u32 obj, u32 a1, u32 a2);
extern void func_00297574(Ev* d, u32 obj);
extern void func_0025B6A8(u32 handle, u32 object);

u32 func_001508C0(u32 a0, u32 a1, u32 a2)
{
    u32 ret = 0;
    u32 created = 0;
    u32 obj;
    if (*(u32*)(a0 + 0x3F4) == 0) {
        obj = func_00297674(data_00711F50, a0);
        *(u32*)(a0 + 0x3F4) = obj;
        if (obj == 0) return ret;
        func_0019A4C4(obj, a0 + 0x3D0);
        created = 1;
    }
    if (*(u32*)(a0 + 0x3F4) != 0) {
        obj = func_0019AA88(*(u32*)(a0 + 0x3F4), a1, a2);
        if (obj != 0) {
            if (created != 0) {
                OffsetList<Obj>* l = (OffsetList<Obj>*)(a0 + 0x3F8);
                l->pushBack((Obj*)*(u32*)(a0 + 0x3F4));
            }
            if (a2 != 0) {
                func_0025B6A8(a2, obj);
            }
            ret = 1;
        } else if (created != 0) {
            func_00297574(data_00711F50, *(u32*)(a0 + 0x3F4));
            *(u32*)(a0 + 0x3F4) = 0;
        }
    }
    return ret;
}
