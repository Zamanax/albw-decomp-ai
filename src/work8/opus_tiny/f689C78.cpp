// 0x689C78: sead-style ListImpl2 ctor (vec_ctor element ctor): node ctor nulls, count 0, then self links
typedef int s32;

#include "sead_container.h"

struct ListImpl2 { ListNode mStartEnd; s32 mCount; ListImpl2(); };
ListImpl2::ListImpl2() : mStartEnd(), mCount(0) { mStartEnd.mNext = &mStartEnd; mStartEnd.mPrev = &mStartEnd; }
