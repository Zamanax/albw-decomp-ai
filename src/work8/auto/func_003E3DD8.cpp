#include "cp15.h"
#include "range.h"
struct IpcCommand {u32 header,result;};
__svc(0x32) s32 send(u32);
s32 f_003E3DD8(const u32*p){u32 tls;tls = tls_tp;IpcCommand*c=(IpcCommand*)(tls+0x80);c->header=786432;s32 r=send(*p);if((s32)((u32)r&0x80000000u)>=0)r=c->result;return r;}
