#include "cp15.h"
#include "../../range.h"
__svc(0x32) u32 svcCall(u32);
u32 func_0010AEA8(const u32*p){u32 tls;tls = tls_tp;IpcCommand*c=(IpcCommand*)(tls+0x80);c->header=0x1a0000;u32 r=svcCall(*p);if((s32)(r&0x80000000u)>=0)r=c->result;return r;}
