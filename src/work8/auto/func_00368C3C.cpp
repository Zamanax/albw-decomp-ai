#include "albw_types.h"
struct Elem148 { char pad[0x145]; u8 flag; char tail[0x148 - 0x146]; };
struct Owner148 { char pad[0xa4]; s32 count; Elem148* items; };
extern "C" void func_00368C3C(Owner148* p, u8 v) {
    Owner148 * t3 = p;
    s32 t2 = t3->count;
    s32 t1 = t2;
    s32 n = t1;
    s32 i = 0;
    Elem148* b = t3->items;
    if (0 == n) return;
    do {
        Elem148* t4 = &b[i];
        t4->flag = v;
        i++;
    } while (i != n);
}
