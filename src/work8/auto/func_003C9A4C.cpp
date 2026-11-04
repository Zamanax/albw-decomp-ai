#include "cp15.h"
#include "range.h"
u32 func_003C9A4C(const u32* handle,u32* out) {
    u32 tls;
    tls = tls_tp;IpcOutput26* command=(IpcOutput26*)(tls+0x80);
    command->header=0x080C0000;
    u32 result=sendSyncRequest26(*handle);
    if((s32)(result&0x80000000u)>=0) {
        *out=command->value;
        result=command->result;
    }
    return result;
}
