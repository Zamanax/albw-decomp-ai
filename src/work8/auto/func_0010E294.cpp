#include "cp15.h"
// 0x10E294: thread-local slot get: TLS[key->index]
typedef unsigned int u32;
struct TlsKey { u32 index; };
u32 func_0010E294(const TlsKey* k) { u32* t; t = (u32*)tls_tp;return t[k->index]; }
