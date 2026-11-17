// Proof for StateMgrT::init (shared/include/statemgr.h), plus the owner-TU dependence of its
// member-pointer constants. Not a registered match:
//   0066D8D0 / 0066739C are the game's out-of-line copies; both reach OP=10 REG=0 MOVED=7 (85.7 %
//   similarity) with every remaining difference located at the null member-pointer constants, which
//   load from ro_006A5E3C+0xB8 / +0x10 and ro_0069F4F8+0x6C / +0x14 (the owner TU's table, built
//   from every other function of that TU). Substituting a table entry (use_table below) moves ours
//   from +0x0 to +0x20, so the offset is set by the TU, not by the source.
#include "statemgr.h"

struct Actor_0045E644 { void m(); };
typedef StateMgrT<Actor_0045E644> SM;

// Three calls keep init out of line, as the game's callers do.
void build(SM* a, SM* b, SM* c, Actor_0045E644* o) {
    u8 n = 3; a->init(o, n);
    u8 k = 4; b->init(o, k);
    u8 j = 5; c->init(o, j);
}

void use_table(void (Actor_0045E644::**t)()) {
    t[0] = &Actor_0045E644::m;
    t[1] = 0;
}
