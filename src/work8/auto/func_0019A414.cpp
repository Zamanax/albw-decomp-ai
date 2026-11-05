typedef unsigned int u32;
typedef int s32;
typedef short s16;

#include "sead_container.h"

struct Item;
struct Target { char pad0[0x1a]; s16 m1a; };
struct Req { char pad0[8]; Target* t; s32 id; };
extern "C" bool func_0052EF04(Item* it, s32 id);
extern "C" void func_00110DB8(Item* it, s16 v);
extern "C" void func_0010F1F8(void* node);

struct Owner {
    char pad0[0x28];
    sead::OffsetList<Item> mList;
};

void func_0019A414(Owner* self, Req* arg) {
    int id = arg->id;
    if (-1 == id) return;
    s16 sb = 0;
    Target* t = arg->t;
    if (t) sb = t->m1a;
    Owner * t1 = self;
    s32 t0 = t1->mList.mCount;
    if (t0 == 0) return;
    for (sead::OffsetList<Item>::robustIterator it = t1->mList.robustBegin(), end = t1->mList.robustEnd(); it != end; ++it) {
        bool t2 = func_0052EF04(&*it, id);
        if (t2) {
            func_00110DB8(&*it, sb);
            if (sb == 0) {
                func_0010F1F8((char*)&*it + t1->mList.mOffset);
                t1->mList.mCount -= 1;
            }
        }
    }
}
