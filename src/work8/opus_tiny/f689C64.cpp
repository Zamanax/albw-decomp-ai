// 0x689C64: sead-style ListImpl ctor (vec_ctor element ctor): node ctor nulls, count 0, then self links
typedef int s32;

#include "sead_container.h"


ListImplOut::ListImplOut() : mStartEnd(), mCount(0) { mStartEnd.mNext = &mStartEnd; mStartEnd.mPrev = &mStartEnd; }
