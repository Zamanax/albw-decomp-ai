#include "albw_types.h"

struct Entry340 { u16 flags; u8 pad[338]; };
struct Table { Entry340* data; u32 count; };
struct Obj { u8 pad[0x20]; Table* tab; };

void func_004D02E8(Obj* self, u32 set) {
    for (u32 i = 0; i < self->tab->count; i++) {
        Entry340* t1 = &self->tab->data[i];
        u16* f = &t1->flags;
        if (set) *f |= 0x400;
        else *f &= ~0x400;
    }
}
