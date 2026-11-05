// func_00689024: sead::FixedSafeString<64>::FixedSafeString() (out of line).
#include "sead_string.h"
#include "sead_heap.h"

sead::FixedSafeString<64>* mk(s32 n) { return new (0, 4) sead::FixedSafeString<64>[n]; }
