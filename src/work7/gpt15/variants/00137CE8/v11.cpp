#include "../../range.h"

#include "timer.h"
struct S{u8 pad30[0x30];s16 frames;u8 pad32[0x43c-0x32];Timer timer;};extern "C" void func_00137CE8(S*p){Timer*t=&p->timer;t->start((u32)p->frames);}
