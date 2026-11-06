// func_003706B0: same setter as 00370608 for the first name (11 wide characters at +0x10), without
// the trailing flag store. Same WBufferedSafeString::copyLocal form.
#include "sead_string.h"

struct Obj3706B0 {
    u8 pad[0x10];
    char16 mName[11];  // +0x10
    void setName(const char16* name);
};

void Obj3706B0::setName(const char16* name) {
    sead::WBufferedSafeString s(mName, 11);
    s.copyLocal(name);
}
