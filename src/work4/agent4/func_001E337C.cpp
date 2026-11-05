typedef unsigned char u8;
typedef int s32;



#include "sead_container.h"


struct Item {
    char pad[0xe];
    u8 m0e;
};
void func_00369E80(Item* it);

class X {
public:
    void func_001E337C();
    char pad[0x34];
    PtrArray<Item> mArr34;
    char pad40[0x50 - 0x40];
    PtrArray<Item> mArr50;
    char pad5c[0x70 - 0x5c];
    Item* m70;
};

void X::func_001E337C() {
    Item* it = m70;
    if (it) {
    s32 idx = mArr50.indexOf(it);
    if (idx != -1) {
        if (idx == 0)
            func_00369E80(it);
        return;
    }
    if (mArr50.isEmpty())
        it->m0e = 1;
    mArr50.pushBack(m70);
    mArr34.erase(mArr34.indexOf(m70));
    }
}
