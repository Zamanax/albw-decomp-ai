// func_0029757C: OffsetList::erase(obj) followed by OffsetList::pushBack(obj).
// Proves the list's inline erase (node = obj + mOffset, erase_ 0x0010F1F8, --mCount) and the
// pushBack form added to sead_container.h (sentinel insertFront_ 0x0010F1DC, ++mCount).
// Both lists are reached through a pointer local: that is what makes the original adjust the list
// base register (`add r4,r4,#0x14`) before loading the offset (`ldr r0,[r4,#0xc]`).
#include "sead_container.h"

extern "C" void func_0019A848(void*);

struct Elem2975 {
    u32 v;
    sead::ListNode node;
};

struct Owner2975 {
    u8 pad[0x14];
    sead::OffsetList<Elem2975> listB;
    sead::OffsetList<Elem2975> listA;
    void f(Elem2975* e);
};

void Owner2975::f(Elem2975* e) {
    func_0019A848(e);
    listA.erase(e);
    sead::OffsetList<Elem2975>* l = &listB;
    l->pushBack(e);
}
