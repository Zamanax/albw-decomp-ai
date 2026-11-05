// Bit-flag words: Flag32 / Flag16 / BitFlag8.
//
// BitFlag32 and BitFlag16 are the same types as Flag32 / Flag16 (same 4- and 2-byte layout, same
// helper forms, no source defines both), so they are aliases here; Flag8 aliases BitFlag8.
//
// Two forms of `set`/`reset` occur in the matched sources and are distinguishable in the bytes when
// they are not inlined together:
//   set/reset   -> `change(mask, true/false)`; after constant folding one orr or one bic per call
//                  (Flag32: 0x003214AC, 0x00265454; Flag16: 0x0015E4BC, 0x0017D38C)
//   set2        -> plain `v |= mask` (0x00105374 wrote `set` this way; same single orr)
//   setB/resetB -> explicit `change(mask, ..)` calls (0x00105374's names for the same body)
//   Flag16 set/reset -> `*this = Flag16((u16)(v | mask))`, the wrapped form (0x0015E4BC);
//                  `clr` is the same body as reset under the name one source used (0x004761F8).
// Changing only the spelling of an unused inline member emits no code, so all forms live here.
//
// Toggle (define before including):
//   BF_OOL - Flag32::set/reset are declared out-of-line (define the bodies via BF_OOL_DEFS in
//            the TU) so consecutive bic/orr are not merged by armcc.
//
// Members are C++-only: C sources see the bare layout, which is what they use.

#ifndef FLAGS_H
#define FLAGS_H

#include "albw_types.h"

struct Flag32 {
    u32 v;
#ifdef __cplusplus
#ifdef BF_OOL
    void set(u32 m);      // define non-inline in the TU (BF_OOL_DEFS) -> no bic merging
    void reset(u32 m);
#else
    // the if is resolved after constant combining -> separate orr/bic per call
    void change(u32 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u32 m) { change(m, true); }
    void reset(u32 m) { change(m, false); }
#endif
    void setB(u32 m) { change(m, true); }
    void resetB(u32 m) { change(m, false); }
    void set2(u32 m) { v |= m; }
    bool isOn(u32 m) const { return (v & m) != 0; }
#endif
};
typedef struct Flag32 Flag32;
typedef struct Flag32 BitFlag32;

#ifdef BF_OOL
#define BF_OOL_DEFS void Flag32::set(u32 m) { v |= m; } void Flag32::reset(u32 m) { v &= ~m; }
#endif

struct Flag16 {
    u16 v;
#ifdef __cplusplus
    Flag16() {}
    Flag16(u16 n) : v(n) {}
    void change(u16 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u16 m) { *this = Flag16((u16)(v | m)); }
    void reset(u16 m) { *this = Flag16((u16)(v & ~m)); }
    void clr(u16 m) { *this = Flag16((u16)(v & ~m)); }
    void setB(u16 m) { change(m, true); }
    void resetB(u16 m) { change(m, false); }
    void set2(u16 m) { v |= m; }
    bool isOn(u16 m) const { return (v & m) != 0; }
#endif
};
typedef struct Flag16 Flag16;
typedef struct Flag16 BitFlag16;

struct BitFlag8 {
    u8 v;
#ifdef __cplusplus
    void change(u8 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u8 m) { v |= m; }
    void reset(u8 m) { v &= ~m; }
    bool isOn(u8 m) const { return (v & m) != 0; }
#endif
};
typedef struct BitFlag8 BitFlag8;
typedef struct BitFlag8 Flag8;

#endif
