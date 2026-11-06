#include "albw_types.h"
#include "sead_container.h"

struct Elem4A0988 {
    u8 pad0[0x20];
    void* owner;
    u8 pad24[0x34 - 0x24];
    u32 v34;
};

struct Owner4A0988 {
    u8 pad0[4];
    OffsetList<Elem4A0988> list;
    u8 pad14[0x1c4 - 0x14];
    u32 f1c4;
};

void func_004A0988(Owner4A0988* self, Elem4A0988* o) {
    Elem4A0988* p = o;
    OffsetList<Elem4A0988>* l = &self->list;
    l->pushBack(p);
    p->owner = self;
    p->v34 = self->f1c4;
}
