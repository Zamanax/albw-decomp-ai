#include "sead_container.h"

struct Item;
struct Owner {
    u8 pad[0x58];
    OffsetList<Item> list;
};

extern "C" void func_0049F434(OffsetList<Item>* l, u32 off, u32 fn);

void func_004B9660(void* p0, u32 p1, u32 p2, u32 p3) {
    Owner* self = (Owner*)p0;
    OffsetList<Item>* l = &self->list;
    l->pushBack((Item*)p1);
    func_0049F434((OffsetList<Item>*)((char*)p0 + 0x58), self->list.mOffset, 0x002C0028u);
}
