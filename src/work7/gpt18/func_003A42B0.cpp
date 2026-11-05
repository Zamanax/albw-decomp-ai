#include "range.h"

#include "timer.h"
struct O{char pad[0x20];Timer timer;u32 reserved;u32 state;};void f(O*p,u32 n){switch(n){case 0:break;case 1:p->timer.start(120);break;default:break;}p->state=n;}
