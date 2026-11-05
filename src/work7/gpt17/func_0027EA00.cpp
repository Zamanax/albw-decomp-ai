#include "range.h"

#include "timer.h"

struct Obj {u8 pad[0x40c];Timer timer;};extern void func_0027EA34(Obj*,void*);
void f_0027EA00(Obj*p,void*arg){func_0027EA34(p,arg);p->timer.start(15);}
