#include "cp15.h"
#include "../../range.h"
extern "C" u32 data_00715878;__svc(0x32)u32 send(u32);struct Cmd{u32 header,first,second,out1,out2;};extern "C" u32 func_00102FB4(u32 first,u32 second,u32*out1,u32*out2){u32 tls;tls = tls_tp;Cmd*c=(Cmd*)(tls+0x80);c->header=0x20080;c->first=first;c->second=second;u32 r=send(data_00715878);if((s32)(r&0x80000000u)>=0){*out1=c->out1;*out2=c->out2;r=c->first;}return r;}
