// sead strings (stand-in reconstruction of sead::SafeString and friends).
// Every inline member reproduced its bytes in at least one matched function.

#ifndef SEAD_STRING_H
#define SEAD_STRING_H

#include "albw_types.h"

namespace sead {
class SafeString {
public:
    SafeString(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
}

#endif
