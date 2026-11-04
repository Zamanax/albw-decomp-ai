#include "cp15.h"
#include "range.h"
u32 func_003C9B68(const u32* handle,u64* out) {
    u32 tls;
    tls = tls_tp;IpcOutput64_26* command=(IpcOutput64_26*)(tls+0x80);
    command->header=0x08040000;
    u32 result=sendSyncRequest26(*handle);
    if((s32)(result&0x80000000u)>=0) {
        *out=command->value;
        result=command->result;
    }
    return result;
}
