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

// Defined at global scope on purpose: 447 matched sources name the class unqualified at file scope
// and one shared header (static_init.h, the Factory constructor's `const SafeString&` parameters)
// also forward-declares `struct SafeString;` there. A global-scope `using` of a namespaced class
// cannot be combined with that declaration, so the class lives at global scope and the namespace
// gets the alias instead.
namespace sead {

// sead::MemUtil, declared only. Its copy() is the game's out-of-line copy routine 0x0010E3C4
// (size switch, `cmp r2,#8` / ldrh/ldrb tails), which SafeString::copy inlines a call to.
class MemUtil {
public:
    static void* copy(void* dst, const void* src, u32 size);  // 0x0010E3C4
};

}  // namespace sead

// sead::SafeStringBase<char>::cNullChar (0x006C57E0, the one 0x00 byte the empty-string object
// points at). Written by `SafeString()`: 0x001097A4 stores ro_006C57E0 into the mStringTop of an
// embedded default-constructed SafeString. Named after its address so the identity check verifies
// the reference (the original name is a private static member of the class template). Declared at
// global scope because SafeString is a global-scope class here.
extern "C" const char ro_006C57E0[];

class SafeString {
public:
    static const s32 cMaximumLength = 0x40000;   // sead::SafeStringBase<char>::cMaximumLength

    // Default construction points at cNullChar, not at null (0x001097A4, 0x001BAABC, 0x001FEFBC).
    SafeString() : mStringTop(ro_006C57E0) {}
    SafeString(const char* s) : mStringTop(s) {}
    virtual ~SafeString() {}                     // 0x00688D9C (no-op); vtable slot +0x00
    virtual void assureTerminationImpl_() const;  // 0x006916EC (no-op); vtable slot +0x08

    // cstr(): assure, then the top pointer. calcLength(): assure, then the 0x40000-capped scan that
    // yields 0 when the cap is exceeded. Both are inlined by the game; 0x0010BEC4
    // (StateMgrBase::setStateName -> FixedSafeString<24>::copy) is their byte proof.
    const char* cstr() const {
        assureTerminationImpl_();
        return mStringTop;
    }
    s32 calcLength() const {
        assureTerminationImpl_();
        s32 n = 0;
        for (;;) {
            if (n > cMaximumLength || mStringTop[n] == 0) break;
            ++n;
        }
        if (n > cMaximumLength) return 0;
        return n;
    }

    const char* mStringTop;                      // +0x04
};

namespace sead {

using ::SafeString;

// BufferedSafeStringBase<char>: the string points into a caller-supplied buffer and knows its size.
// The base step of the FixedSafeString<24> constructor 0x0010BDF0 stores, in this order,
// mStringTop = mBuffer, mBufferSize = N, mBuffer[N-1] = 0 (as `sub r1,mStringTop,#1` then
// `strb 0,[r2,r1]` with r2 = N), and installs the derived vtable last.
//
// The constructor and assureTerminationImpl_() below are the reference class tree's bodies:
// 0x00689A2C (the out-of-line BufferedSafeString(char*, s32)) matches the constructor word for
// word, and the overload of assureTerminationImpl_ with the explicit `char* p` local is what the
// three FixedSafeString constructor sites (0x0010BDF0 / 0x00688F10 / 0x00689024) and the two
// inlined ones (0x0048D854 member, 0x0048D7DC stack local) reproduce. A body that calls
// getMutableStringTop_() inline instead compiles to the same bytes only in the out-of-line copy.
class BufferedSafeString : public SafeString {
public:
    BufferedSafeString() : mBufferSize(0) {}
    BufferedSafeString(char* buffer, s32 size) : SafeString(buffer), mBufferSize(size) {
        if (size <= 0) {
            mStringTop = 0;
            mBufferSize = 0;
            return;
        }
        assureTerminationImpl_();
    }
    virtual ~BufferedSafeString() {}
    virtual void assureTerminationImpl_() const {  // 0x00691BD0
        BufferedSafeString* self = const_cast<BufferedSafeString*>(this);
        char* p = const_cast<char*>(self->mStringTop);
        p[self->mBufferSize - 1] = 0;
    }

    s32 getBufferSize() const { return mBufferSize; }
    void clear() { getMutableStringTop_()[0] = 0; }
    // The reference copy(): the destination top first, then the 0x40000-capped length of src, the
    // clamp to the own buffer, MemUtil::copy and the terminator. 0x0010BEC4 is the byte proof.
    s32 copy(const SafeString& src, s32 size = -1) {
        char* dst = getMutableStringTop_();
        if (size < 0) size = src.calcLength();
        if (size >= mBufferSize) size = mBufferSize - 1;
        MemUtil::copy(dst, src.cstr(), size);
        dst[size] = 0;
        return size;
    }
    // 0x00689928 is append() with copyAt(-1, src, length) inlined: at = len + at + 1, the clamp to
    // mBufferSize - at - 1, the copy at dst + at and a terminator only when the string got longer.
    // The destination is fetched before the length, and dst + at is a local taken right before the
    // copy (that is what puts the add before the cstr call).
    s32 copyAt(s32 at, const SafeString& src, s32 size = -1) {
        char* dst = getMutableStringTop_();
        s32 len = calcLength();
        if (at < 0) {
            at = len + at + 1;
            if (at < 0) at = 0;
        }
        if (size < 0) size = src.calcLength();
        if (size >= mBufferSize - at) size = mBufferSize - at - 1;
        if (size <= 0) return 0;
        char* p = dst + at;
        MemUtil::copy(p, src.cstr(), size);
        if (at + size > len) dst[at + size] = 0;
        return size;
    }
    s32 append(const SafeString& src, s32 size = -1) { return copyAt(-1, src, size); }
    // 0x00111A20 takes the va_list by value (r2 = the ap word), so the parameter is not a reference.
    s32 formatV(const char* fmt, va_list args);
    // The variadic form lives here, in the non-template base: armcc 4.1 exits silently (code 5) on
    // a variadic member defined inside a class template.
    s32 format(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        s32 r = formatV(fmt, args);
        va_end(args);
        return r;
    }

    char* getMutableStringTop_() { return const_cast<char*>(mStringTop); }

    s32 mBufferSize;  // +0x08
};

// FixedSafeStringBase<N>: the buffer and the clear() a fixed-size string does after its own
// constructor ran. sizeof == 0x0C + N (0x24 for N = 24, which is what the state-name tables of
// StateMgr use: element size in the array cookie at 0x002072B4 and stride 0x24 in
// StateMgrBase::setStateName 0x0010BEC4). 0x0010BDF0 (N = 24), 0x00688F10 (N = 32) and
// 0x00689024 (N = 64) are the game's out-of-line constructors of FixedSafeString<N>.
template <int N>
class FixedSafeStringBase : public BufferedSafeString {
public:
    FixedSafeStringBase() : BufferedSafeString(mBuffer, N) { clear(); }
    // The copy-from-SafeString constructors do NOT clear (no strb of 0 at mBuffer[0]): they copy
    // straight into the buffer. 0x00688F58 (N = 64), 0x00688E10 (N = 256) and 0x00491188 (N = 32)
    // are the out-of-line instances; 0x0014E500 is the inlined proof (63/63).
    FixedSafeStringBase(const SafeString& src) : BufferedSafeString(mBuffer, N) { this->copy(src); }
    FixedSafeStringBase(const FixedSafeStringBase& src) : BufferedSafeString(mBuffer, N) { this->copy(src); }
    virtual ~FixedSafeStringBase() {}

private:
    char mBuffer[N];  // +0x0C
};

template <int N>
class FixedSafeString : public FixedSafeStringBase<N> {
public:
    FixedSafeString() : FixedSafeStringBase<N>() {}
    FixedSafeString(const SafeString& src) : FixedSafeStringBase<N>(src) {}
    FixedSafeString(const FixedSafeString& src) : FixedSafeStringBase<N>(src) {}
};

// FormatFixedSafeString<N>: construction formats into the buffer. The variadic constructor is a
// template member and armcc rejects it inside the class, but accepts this out-of-line definition;
// 0x00689650 (N = 256) matches it: the vtable chain, buffer 0xC + N, then formatV with sp+0x10 as
// the argument list. Same shape at 0x00689578 (0x80), 0x006896BC (0x20), 0x00689728 (0x24),
// 0x00689794 (0x40), 0x006895E4 (0x10).
template <int N>
class FormatFixedSafeString : public FixedSafeStringBase<N> {
public:
    FormatFixedSafeString(const char* fmt, ...);
};

template <int N>
FormatFixedSafeString<N>::FormatFixedSafeString(const char* fmt, ...) : FixedSafeStringBase<N>() {
    va_list args;
    va_start(args, fmt);
    this->formatV(fmt, args);
    va_end(args);
}

}  // namespace sead

// ---- wide strings: sead::SafeStringBase<char16> and BufferedSafeStringBase<char16> ----
// The 16-bit counterpart of the char family above: same layout, same inline bodies on 16-bit units,
// vptr +0x00, mStringTop +0x04 (WSafeString), mBufferSize +0x08 (WBufferedSafeString). The
// WSafeString vtable is ro_006F599C: +0x00 0x00688DA0 ~WSafeString() (bx lr), +0x08 0x00691B6C
// assureTerminationImpl_() (bx lr); WBufferedSafeString::assureTerminationImpl_() is 0x00691BE8
// (strh of 0 at mStringTop + 2*mBufferSize - 2) and 0x00689A64 is its out-of-line copy in the shape
// below. Proofs: 0x00584084 (copy, 51/51), 0x00370608 / 0x003706B0 (copyLocal, 42/42 and 41/41).
// sead's char16, the unit of the wide family. Global scope on purpose: the game's sources and the
// 16-bit string literals are named unqualified at file scope. armcc accepts a duplicate typedef of
// the same type, so a source that spells `typedef unsigned short char16;` itself still compiles.
typedef u16 char16;

namespace sead {

class WSafeString {
public:
    static const s32 cMaximumLength = 0x40000;

    WSafeString(const char16* s) : mStringTop(s) {}
    virtual ~WSafeString() {}                     // 0x00688DA0 (no-op); vtable slot +0x00
    virtual void assureTerminationImpl_() const;  // 0x00691B6C (no-op); vtable slot +0x08

    const char16* cstr() const {
        assureTerminationImpl_();
        return mStringTop;
    }
    s32 calcLength() const {
        assureTerminationImpl_();
        s32 n = 0;
        for (;;) {
            if (n > cMaximumLength || mStringTop[n] == 0) break;
            ++n;
        }
        if (n > cMaximumLength) return 0;
        return n;
    }

    const char16* mStringTop;                     // +0x04
};

class WBufferedSafeString : public WSafeString {
public:
    WBufferedSafeString(char16* buffer, s32 size) : WSafeString(buffer), mBufferSize(size) {
        if (size <= 0) {
            mStringTop = 0;
            mBufferSize = 0;
            return;
        }
        assureTerminationImpl_();
    }
    virtual ~WBufferedSafeString() {}
    virtual void assureTerminationImpl_() const {  // 0x00691BE8
        WBufferedSafeString* self = const_cast<WBufferedSafeString*>(this);
        char16* p = const_cast<char16*>(self->mStringTop);
        p[self->mBufferSize - 1] = 0;
    }

    s32 getBufferSize() const { return mBufferSize; }
    void clear() { getMutableStringTop_()[0] = 0; }
    // 0x00689A64 is this body out of line; 0x00584084 is the inlined proof (the destination
    // mStringTop is fetched before the source's calcLength/cstr calls).
    s32 copy(const WSafeString& src, s32 size = -1) {
        char16* dst = getMutableStringTop_();
        if (size < 0) size = src.calcLength();
        if (size >= mBufferSize) size = mBufferSize - 1;
        MemUtil::copy(dst, src.cstr(), size * sizeof(char16));
        dst[size] = 0;
        return size;
    }
    // copy() with the destination fetched *after* the clamp: same semantics, different register
    // allocation. This is what an inlined copy into a local string over a member array reduces to
    // (0x00370608, 0x003706B0) -- use it when the buffer is a member array and the string object is
    // a local.
    s32 copyLocal(const WSafeString& src, s32 size = -1) {
        if (size < 0) size = src.calcLength();
        if (size >= mBufferSize) size = mBufferSize - 1;
        char16* dst = getMutableStringTop_();
        MemUtil::copy(dst, src.cstr(), size * sizeof(char16));
        dst[size] = 0;
        return size;
    }
    // The 16-bit copyAt/append: same body as the char one above (0x00689928), on 16-bit units.
    s32 copyAt(s32 at, const WSafeString& src, s32 size = -1) {
        char16* dst = getMutableStringTop_();
        s32 len = calcLength();
        if (at < 0) {
            at = len + at + 1;
            if (at < 0) at = 0;
        }
        if (size < 0) size = src.calcLength();
        if (size >= mBufferSize - at) size = mBufferSize - at - 1;
        if (size <= 0) return 0;
        char16* p = dst + at;
        MemUtil::copy(p, src.cstr(), size * sizeof(char16));
        if (at + size > len) dst[at + size] = 0;
        return size;
    }
    s32 append(const WSafeString& src, s32 size = -1) { return copyAt(-1, src, size); }

    char16* getMutableStringTop_() { return const_cast<char16*>(mStringTop); }

    s32 mBufferSize;  // +0x08
};

template <int N>
class WFixedSafeStringBase : public WBufferedSafeString {
public:
    WFixedSafeStringBase() : WBufferedSafeString(mBuffer, N) { clear(); }
    virtual ~WFixedSafeStringBase() {}

private:
    char16 mBuffer[N];  // +0x0C
};

template <int N>
class WFixedSafeString : public WFixedSafeStringBase<N> {
public:
    WFixedSafeString() : WFixedSafeStringBase<N>() {}
};

}  // namespace sead

#endif
