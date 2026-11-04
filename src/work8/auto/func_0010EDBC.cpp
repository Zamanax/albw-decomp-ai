#include "cp15.h"
// 0x10EDBC: thread-local slot set: TLS[key->index] = v
typedef unsigned int u32;
struct TlsKey { u32 index; };
void func_0010EDBC(const TlsKey* k, u32 v) { u32* t; t = (u32*)tls_tp;t[k->index] = v; }
