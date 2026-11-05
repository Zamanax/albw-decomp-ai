typedef int s32;

#include "sead_container.h"


struct OL : ListImpl { s32 offset; OL(); };
OL::OL() : offset(-1) {}
struct LI2 { ListNode head; s32 count; LI2(); };
LI2::LI2() { head.mNext = &head; count = 0; head.mPrev = &head; }
struct Wrap { ListImpl l; Wrap(); };
Wrap::Wrap() {}
