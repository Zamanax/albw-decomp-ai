#pragma pack(4)

#include "static_init.h"

struct Pair { long long v; Pair() : v(0) {} };
struct Big { char pad[24]; long long v; };
Big data_hi = { {0}, Id64().v };
Pair data_lo;
