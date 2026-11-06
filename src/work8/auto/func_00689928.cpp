// func_00689928: BufferedSafeString::append(src, length), out of line. The body is sead's
// copyAt(-1, src, length) inlined: dst = mStringTop before the length, at = len + (-1) + 1, the
// clamp to mBufferSize - at - 1, the copy at dst + at and a terminator only when the string got
// longer.
#include "sead_string.h"

s32 func_00689928(sead::BufferedSafeString* s, const sead::SafeString& src, s32 length) {
    return s->append(src, length);
}
