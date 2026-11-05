#include "range.h"
struct Flag{u32 v;void change();};void Flag::change(){v&=~2u;}
#include "timer.h"
struct O{char pad[0x2e0];Flag flags;char gap[0x474-0x2e4];Timer timer;};bool f(O*p){p->flags.change();p->timer.start(30);return true;}

