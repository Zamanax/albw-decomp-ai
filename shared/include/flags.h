// Bit-flag words.
//
// Toggle (define before including):
//   BF_OOL - BitFlag32::set/reset are declared out-of-line (define the bodies via BF_OOL_DEFS in
//            the TU) so consecutive bic/orr are not merged by armcc.

#ifndef FLAGS_H
#define FLAGS_H

#include "albw_types.h"

struct BitFlag32 {
    u32 v;
#ifdef BF_OOL
    void set(u32 m);      // define non-inline in the TU (BF_OOL_DEFS) -> no bic merging
    void reset(u32 m);
#else
    // the if is resolved after constant combining -> separate orr/bic per call
    void change(u32 m, bool on) { if (on) v |= m; else v &= ~m; }
    void set(u32 m) { change(m, true); }
    void reset(u32 m) { change(m, false); }
#endif
    bool isOn(u32 m) const { return (v & m) != 0; }
};
#ifdef BF_OOL
#define BF_OOL_DEFS void BitFlag32::set(u32 m) { v |= m; } void BitFlag32::reset(u32 m) { v &= ~m; }
#endif

#endif
