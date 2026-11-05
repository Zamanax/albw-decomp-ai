// func_00688F10: sead::FixedSafeString<32>::FixedSafeString() (out of line).
#include "sead_string.h"
#include "sead_heap.h"

sead::FixedSafeString<32>* mk(s32 n) { return new (0, 4) sead::FixedSafeString<32>[n]; }
