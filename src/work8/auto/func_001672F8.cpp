#include "albw_types.h"

struct Ctrl { char pad[0x10]; f32 m10; };
struct Elem {
    char pad[0x10];
    Ctrl* mCtrl;
    f32 m14;
    f32 m18;
    f32 m1c;
    u32 m20;
    u32 m24;
    char pad2[0xc];
    u8 m34;
    u8 m35;
};
struct Arr {
    char pad[8];
    u32 mNum;
    Elem* mData;
};

void func_001672F8(Arr* arr, u32 index, f32 a, f32 b) {
    Elem* e = (index < arr->mNum) ? arr->mData + index : arr->mData;
    if (e->m35 && e->m14 == a && e->m1c == b) return;
    f32 c = a;
    if (b >= 0.0f || c != 0.0f) {
        e->m18 = c;
        e->m14 = c;
    } else {
        u32 t = e->m20;
        *(u32*)&e->m18 = t;
        *(u32*)&e->m14 = t;
    }
    e->m1c = b;
    e->m24 = 0;
    Ctrl* k = e->mCtrl;
    k->m10 = a;
    e->m34 = 1;
    e->m35 = 1;
}
