#include "cp15.h"
#include "range.h"
__svc(0x32)u32 sendSync(u32);struct Cmd{u32 header,result;};extern u32 data_00716784;u32 f(u32 n){u32 tls;tls = tls_tp;Cmd*c=(Cmd*)(tls+0x80);c->header=0xb0040;c->result=n;u32 r=sendSync(data_00716784);if((s32)(r&0x80000000u)>=0)r=c->result;return r;}
