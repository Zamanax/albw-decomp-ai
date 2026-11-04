#include "cp15.h"
#include "../../range.h"
__svc(0x32) u32 svcCall(u32);extern u32 data_0071618C;struct Request{u32 header,result,reserved,output;};u32 func_001029DC(u32*out){u32 tls;tls = tls_tp;Request*c=(Request*)(tls+0x80);c->header=0x20000;u32 r=svcCall(data_0071618C);if((s32)(r&0x80000000u)>=0){*out=c->output;r=c->result;}return r;}
