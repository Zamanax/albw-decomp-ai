typedef unsigned int u32;

#include "flags.h"

struct En { char p[0x59c]; BitFlag32 m59c; void f(); };
void En::f() { m59c.set(0x100); }
