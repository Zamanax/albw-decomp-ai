typedef unsigned int u32;
typedef int s32;

#include "sead_container.h"

struct Item;
extern "C" bool func_0052EF6C(Item* it);
extern "C" void func_0010F1F8(void* node);

struct Owner {
    char pad0[0x28];
    sead::OffsetList<Item> mList;
};

void func_0019A2EC(Owner* self) {
    if (self->mList.mCount != 0) {
        for (sead::OffsetList<Item>::robustIterator it = self->mList.robustBegin(), end = self->mList.robustEnd(); it != end; ++it) {
            if (!func_0052EF6C(&*it)) {
                func_0010F1F8((char*)&*it + self->mList.mOffset);
                self->mList.mCount -= 1;
            }
        }
    }
}
