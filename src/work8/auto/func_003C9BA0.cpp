#include "cp15.h"
#include "range.h"
u32 func_003C9BA0(const u32* handle) {
    u32 tls;
    tls = tls_tp;IpcRequest26* command=(IpcRequest26*)(tls+0x80);
    command->header=0x08020000;
    u32 result=sendSyncRequest26(*handle);
    if((s32)(result&0x80000000u)>=0)result=command->result;
    return result;
}
