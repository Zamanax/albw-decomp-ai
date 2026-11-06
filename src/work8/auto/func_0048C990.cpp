typedef unsigned int u32;
typedef int s32;

#include "sead_container.h"

struct Item;

extern "C" void func_0048C91C(Item* it);
extern "C" void func_0049F5FC(sead::OffsetList<Item>* l);

extern "C" void func_0048C990(void* a0, sead::OffsetList<Item>* dst, sead::OffsetList<Item>* src, u32 flag) {
    if (src->mCount == 0) return;
    for (sead::OffsetList<Item>::robustIterator it = src->robustBegin(); it != src->robustEnd(); ++it) {
        Item* o = &*it;
        src->erase(o);
        if (flag != 0) func_0048C91C(o);
        dst->pushBack(o);
    }
    func_0049F5FC(src);
}
