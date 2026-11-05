// Timer {cur, max, rate}: frame counter with a 1/max rate.
//
// The step forms below are not interchangeable: armcc emits a different compare order / copy
// depending on how the source reads the fields, and the matched functions distinguish them.
//   step   - copies the Timer to a local and tests `t.cur < t.max`  -> cmp cur,max (0x001573C8)
//   step3  - copies the Timer to a local and tests `t.max > t.cur`  -> cmp max,cur; addhi
//            (0x0021A59C); same body is spelled stepReverse in 0x00216C60 and stepC2 in 0x004FF430
//   step2b - tests the members directly, `cur < max`, increment in place (0x00212B5C)
//   step2  - tests the members directly, `max > cur` (KB #153 "cmp max,cur; addhi", 0x001CD5DC)
//   stepC  - Timer copy named `c` instead of `t`, `c.cur < c.max` (0x004FF430)
//   done/isEnd - `cur >= max`, lazily (done copies first, isEnd reads through this)
//   progress - fraction elapsed: 0 before the first tick, 1 once cur reaches max, else cur*rate
//   start  - `if (n == 0) rate = 0.0f; else rate = 1.0f / n;` then `cur = c` (0x001573C8,
//            0x00159A94). The same test spelled `if (n) .. else ..` matches 43 of the 54 sources
//            with a local Timer, the `rate = n ? 1.0f/n : 0.0f` ternary 32, this spelling 44.
//
// Two starts: `start` takes the count by value (r1 = n, r2 = c), `startRef` by const& (the two
// arguments travel as stack addresses) - distinguishable in the bytes, so both are kept.
// Toggle (define before including):
//   TIMER_CREF - start takes (const u32&, const u32&) like startRef. By-value start gave swapped
//                r1/r2 at 0x1D6924.
//
// Members are C++-only: C sources see the bare {cur, max, rate} layout.

#ifndef TIMER_H
#define TIMER_H

#include "albw_types.h"

struct Timer {
    u32 cur;
    u32 max;
    f32 rate;
#ifdef __cplusplus
#ifdef TIMER_CREF
    void start(const u32& n, const u32& c = 0) {
#else
    void start(u32 n, u32 c = 0) {
#endif
        max = n;
        if (n == 0) rate = 0.0f;
        else rate = 1.0f / n;
        cur = c;
    }
    // Same body with const& parameters: the arguments are set up through two stack addresses
    // instead of r1/r2, which is what 0x001D575C, 0x001810F4, 0x002880F0 and 0x001A04C0 need.
    void startRef(const u32& n, const u32& c = 0) {
        max = n;
        if (n == 0) rate = 0.0f;
        else rate = 1.0f / n;
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
    bool stepReverse() {
        Timer t = *this;
        if (t.max > t.cur) { cur = t.cur + 1; return true; }
        return false;
    }
    bool stepC() {
        Timer c = *this;
        if (c.cur < c.max) { cur = c.cur + 1; return true; }
        return false;
    }
    bool stepC2() {
        Timer c = *this;
        if (c.max > c.cur) { cur = c.cur + 1; return true; }
        return false;
    }
    bool isEnd() const { return cur >= max; }
    bool done() const {
        Timer t = *this;
        return t.cur >= t.max;
    }
    f32 progress() const {
        f32 r;
        if (max == 0 || cur == 0) r = 0.0f;
        else if (max <= cur) r = 1.0f;
        else r = cur * rate;
        return r;
    }
#endif
};
typedef struct Timer Timer;

#endif
