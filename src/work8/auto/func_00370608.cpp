// func_00370608: sets an 11-character wide name and the flag right after it. The buffered string
// over the member array is a local, so its copy() is WBufferedSafeString::copyLocal (destination
// fetched after the clamp); the m3e = 0 store comes first, as in the original.
#include "sead_string.h"

struct Obj370608 {
    u8 pad[0x28];
    char16 mName[11];  // +0x28
    u8 m3e;            // +0x3e
    void setName(const char16* name);
};

void Obj370608::setName(const char16* name) {
    m3e = 0;
    sead::WBufferedSafeString s(mName, 11);
    s.copyLocal(name);
}
