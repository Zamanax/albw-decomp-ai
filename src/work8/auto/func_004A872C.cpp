#include "sead_container.h"

extern "C" void func_004A8610(void*, u32);

void func_004A872C(u8* self, u32 p1) {
    u8* base = self + 0xbc00;
    s32 t = *(s16*)((char*)0x00015B40 + p1);
    OffsetList<u8>* l = (OffsetList<u8>*)(base + 0x33c);
    u8* o = self + 0x10;
    ListNode* n = l->objToListNode(o);
    if (n->mNext == 0 && n->mPrev == 0) {
        l->pushBack(o);
    }
    if (t >= 0) {
        func_004A8610(self, p1);
    }
}
