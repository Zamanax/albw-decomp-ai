// sead string family: SafeString, BufferedSafeString and FixedSafeString<N>.
//
// One definition for every matched source that used to carry its own copy: 531 local definitions of
// SafeString (19 distinct spellings after normalising whitespace, 5 member names: text 454,
// mStringTop 59, str 12, mStr 4, c 2), all of which
// describe this one object. 530 of the 531 files accept this header unchanged
// (tools/headermigrate.py, logs/headermigrate/LIB_strings_SafeString.jsonl). The layout and the
// virtual functions below are read from the game image:
//
//   vptr +0x00, mStringTop +0x04          (0x0059C094 str r4,[r0] / str r1,[r0,#4] on a static
//                                          SafeString[4] built from literals; the same two stores
//                                          are the whole constructor)
//   vtable ro_006F5988                    (SafeString, slots read by BufferedSafeString::copy)
//     +0x00 0x00688D9C  ~SafeString()      bx lr, does nothing
//     +0x08 0x006916EC  assureTerminationImpl_()  bx lr: the base class has no buffer
//   vtable ro_006F5BBC                    (FixedSafeString<24>: ctor 0x0010BDF0 installs it last)
//     +0x08 0x00691BD0  assureTerminationImpl_()  writes mStringTop[mBufferSize-1] = 0
//
// 0x00691BD0 is the byte-for-byte body of
//     char* p = const_cast<char*>(mStringTop); p[mBufferSize - 1] = '\0';
// (add r0,r0,#4 / ldm r0,{r0,r2} / sub r0,r0,#1 / strb r1,[r2,r0]); 0x00691BE8 is the same for
// wchar_t (strh of 0 at mStringTop + 2*mBufferSize - 2).
//
// SafeString must keep BOTH the virtual destructor and the virtual assureTerminationImpl_():
// the destructor fixes sizeof(SafeString) == 8, which is what the static name tables in 447 matched
// sources are laid out with (`SafeString strs[] = {"N_ArrowT_00", ...}`), and a class without it
// shrinks to 4 bytes and stops matching (verified: 18/103 words). Declaring the second virtual on
// top does not disturb those files (103/103), and adding the destructor to the sources that only
// declared assureTerminationImpl_ does not disturb them either (63/63).

#ifndef SEAD_STRING_H
#define SEAD_STRING_H

#include "albw_types.h"
#include <stdarg.h>

namespace sead {

class SafeString {
public:
    SafeString() : mStringTop(0) {}
    SafeString(const char* s) : mStringTop(s) {}
    virtual ~SafeString() {}                     // 0x00688D9C (no-op); vtable slot +0x00
    virtual void assureTerminationImpl_() const;  // 0x006916EC (no-op); vtable slot +0x08
    const char* mStringTop;                      // +0x04
};

// BufferedSafeStringBase<char>: the string points into a caller-supplied buffer and knows its size.
// The base step of the FixedSafeString<24> constructor 0x0010BDF0 stores, in this order,
// mStringTop = mBuffer, mBufferSize = N, mBuffer[N-1] = 0 (as `sub r1,mStringTop,#1` then
// `strb 0,[r2,r1]` with r2 = N), and installs the derived vtable last.
class BufferedSafeString : public SafeString {
public:
    BufferedSafeString() : mBufferSize(0) {}
    BufferedSafeString(char* buffer, s32 size) : SafeString(buffer), mBufferSize(size) {
        if (size <= 0) {
            mStringTop = 0;
            mBufferSize = 0;
        } else {
            buffer[size - 1] = 0;
        }
    }
    virtual void assureTerminationImpl_() const;  // 0x00691BD0
    void formatV(const char* fmt, va_list& args);  // 0x00111A20: vsnprintf into the own buffer
    // The variadic form lives here, in the non-template base: armcc 4.1 exits silently (code 5) on
    // a variadic member defined inside a class template.
    void format(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        formatV(fmt, args);
        va_end(args);
    }
    s32 mBufferSize;  // +0x08
};

// FixedSafeString<N>: sizeof == 0x0C + N (0x24 for N = 24, which is what the state-name tables of
// StateMgr use: element size in the array cookie at 0x002072B4 and stride 0x24 in
// StateMgrBase::setStateName 0x0010BEC4). The constructor is 0x0010BDF0.
template <int N>
class FixedSafeString : public BufferedSafeString {
public:
    FixedSafeString() : BufferedSafeString(mBuffer, N) { mBuffer[0] = 0; }

private:
    char mBuffer[N];  // +0x0C
};

}  // namespace sead

// Most matched sources name the class unqualified at file scope.
using sead::SafeString;

#endif
