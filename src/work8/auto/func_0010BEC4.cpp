// func_0010BEC4: StateMgrBase::setStateName. Inlines SafeString::cstr() and calcLength() and
// BufferedSafeString::copy() (which calls MemUtil::copy 0x0010E3C4).
#include "sead_string.h"
#include "statemgr.h"

void StateMgrBase::setStateName(s32 idx, const sead::SafeString& name) {
    sead::FixedSafeString<24>* n = (u32)idx < (u32)mNameCount ? &mNames[idx] : &mNames[0];
    const sead::SafeString* s = &name;
    n->copy(*s);
}
