// Timer {cur, max, rate}: frame counter with a 1/max rate.
//
// Toggle (define before including):
//   TIMER_CREF - start takes (const u32&, const u32&) instead of by value.
//                By-value start gave swapped r1/r2 at 0x1D6924.

#ifndef TIMER_H
#define TIMER_H

#include "albw_types.h"

struct Timer {
    u32 cur;
    u32 max;
    f32 rate;
#ifdef TIMER_CREF
    void start(const u32& n, const u32& c = 0) {
#else
    void start(u32 n, u32 c = 0) {
#endif
        max = n;
        if (n) rate = 1.0f / n;
        else rate = 0.0f;
        cur = c;
    }
    bool step() {
        Timer t = *this;
        if (t.cur < t.max) { cur = t.cur + 1; return true; }
        return false;
    }
    bool step2b() {
        if (cur < max) { cur++; return true; }
        return false;
    }
    bool step3() {
        Timer t = *this;
        if (t.max > t.cur) { cur = t.cur + 1; return true; }
        return false;
    }
    bool step2() {
        if (max > cur) { cur++; return true; }
        return false;
    }
};

#endif
