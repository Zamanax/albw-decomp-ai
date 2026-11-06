#include "sead_string.h"
extern "C" {
extern char ro_006EF69C[];
extern char ro_00694E94[];
extern char ro_006D7118[];
extern char data_0070A1A8[];
extern unsigned func_0010CEE0(unsigned, unsigned, unsigned);
extern unsigned func_0010DA7C(unsigned, unsigned, unsigned);
extern unsigned func_0019CE50(unsigned, const SafeString&);
unsigned func_002615BC(unsigned a0)
{
  unsigned t2, t3, r0, h901;
  if (*(unsigned*)(data_0070A1A8) == 0) {
    t2 = func_0010CEE0(0x514, a0, 4);
    t3 = t2 + 0x504;
    r0 = t3;
    if (t3 != 0) {
      h901 = a0;
      r0 = func_0010DA7C(t3, h901, 3);
      *(unsigned*)r0 = (unsigned)ro_006EF69C;
    }
    *(unsigned*)(data_0070A1A8 + 4) = r0;
    if (t2 != 0) {
      unsigned* pp = (unsigned*)t2;
      const SafeString& tp = SafeString(ro_00694E94);
      r0 = func_0019CE50((unsigned)pp, tp);
      *(unsigned*)r0 = (unsigned)ro_006D7118;
    } else {
      r0 = 0;
    }
    *(unsigned*)(data_0070A1A8) = r0;
  }
  return *(unsigned*)(data_0070A1A8);
}
}
