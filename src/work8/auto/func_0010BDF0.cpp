// func_0010BDF0: sead::FixedSafeString<24>::FixedSafeString() (out of line; the constructor the
// state-name tables are built with). Proves the three-level string tree of sead_string.h.
#include "sead_string.h"
#include "sead_heap.h"

sead::FixedSafeString<24>* mk(s32 n) { return new (0, 4) sead::FixedSafeString<24>[n]; }
