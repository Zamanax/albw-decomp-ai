#include "../../work4/agent5/a5.h"

// Loop index of class type: ARMCC fully unrolls every plain-int spelling of this loop,
// the original keeps it rolled (KB #58/#76).
struct Counter {
    int v;
    Counter(int x) : v(x) {}
    operator int() const { return v; }
    Counter& operator++() { ++v; return *this; }
};

struct Sub {
    char pad0[0x42];
    u16 h42;
};

class Cls {
public:
    int func();
    char pad0[0x614];
    Sub* mSub;
    char pad1[0x694 - 0x618];
    StateSlot mSlots[3];
    StateSlot* getSlot(int i) { return &mSlots[i]; }
    StateSlot* getSlotAt(int i) { StateSlot* s = mSlots; return s + i; }
    StateSlot* findSlot(s32 id) {
        for (Counter i(0); i < 3; ++i) {
            if (getSlot(i)->current == id)
                return getSlotAt(i);
        }
        return 0;
    }
};

int Cls::func() {
    s32 id = 12;
    StateSlot* s = findSlot(id);
    if (s) {
        if (mSub->h42 != 0x9c) return 1;
    }
    return 0;
}
