typedef unsigned int u32;
typedef int s32;
typedef short s16;

#include "sead_container.h"

struct Item;
struct Owner {
    char pad0[0x24];
    sead::OffsetList<Item> mList;
};
extern "C" bool func_0052EF6C(Item* it);
extern "C" bool func_0052EF04(Item* it, s32 id);
extern "C" void func_00110DB8(Item* it, s16 v);
extern "C" void func_002DEAD0(Owner* self, Item* it);

extern "C" void func_002DF17C(Owner* self, s32 v, s16 w) {
    sead::OffsetList<Item>* t2 = &self->mList;
    if (t2->mCount == 0) return;
    for (sead::OffsetList<Item>::robustIterator it = self->mList.robustBegin(), end = self->mList.robustEnd(); it != end; ++it) {
        if (!func_0052EF6C(&*it)) {
            func_002DEAD0(self, &*it);
        } else if (func_0052EF04(&*it, v)) {
            func_00110DB8(&*it, w);
            if (w == 0) func_002DEAD0(self, &*it);
        }
    }
}
