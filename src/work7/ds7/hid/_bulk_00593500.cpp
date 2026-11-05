#pragma pack(4)

#include "static_init.h"

struct Pair { long long v; Pair() : v(0) {} };
long long data_hi = Id64().v;
Pair data_lo;
