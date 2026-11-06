// func_00584084: copies the owner's wide name (16-bit units) into a caller-supplied buffered
// string. sead::WBufferedSafeString::copy from sead_string.h: the destination mStringTop is fetched
// first, then the source's calcLength/cstr (the two vtable +8 calls), the clamp to mBufferSize-1,
// MemUtil::copy of n*2 bytes and the 16-bit terminator.
#include "sead_string.h"

struct Data584084 {
    u8 pad[0xd60];
    char16 mName[1];  // +0xd60
};

struct Obj584084 {
    u8 pad[0x14];
    Data584084* mData;  // +0x14
    void getName(sead::WBufferedSafeString* out) const;
};

void Obj584084::getName(sead::WBufferedSafeString* out) const {
    if (out == 0) return;
    if (mData == 0) return;
    if (mData->mName[0] == 0) return;
    out->copy(mData->mName);
}
