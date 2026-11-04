#include "cp15.h"
#include "range.h"
u32 func_003D2D08(const u32* handle,u32 value) {
    u32 tls;
    tls = tls_tp;IpcHalf26* command=(IpcHalf26*)(tls+0x80);
    command->header=0x70040;
    command->input=*(const u16*)&value;
    u32 result=sendSyncRequest26(*handle);
    if((s32)(result&0x80000000u)>=0)result=command->result;
    return result;
}
