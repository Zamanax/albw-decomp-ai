#include "sead_container.h"

struct Node2DEAD0 { void* m0; void* m4; };

struct Obj2DEAD0 {
    char _p[0x14];
    sead::OffsetList<Node2DEAD0> mB;
    sead::OffsetList<Node2DEAD0> mA;
};

extern "C" void func_001E01C4(void* p);

void func_002DEAD0(Obj2DEAD0* self, Node2DEAD0* n) {
    if (n->m4 == 0 && n->m0 == 0) {
        func_001E01C4(n);
        self->mA.erase(n);
        sead::OffsetList<Node2DEAD0>* b = &self->mB;
        b->pushBack(n);
    }
}
