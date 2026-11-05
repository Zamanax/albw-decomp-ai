#include "albw_types.h"

// Destructor of the class with vtables ro_006E632C (own) and ro_006D7880 (base level), whose
// base-level members sit at +0x10 (0x58), +0x68 (0x128), +0x190 (0x64), +0x1F4 (4 bytes); the
// own sub-object at +0x528 is destroyed first by func_003E2E68 (plain call, result discarded so
// the pointer is kept in r4) and func_004940D0 (returns this). The member dtors are bx-lr leaves
// (func_001E6CE8) that armlink NOPs; the last call is the tail call to ~IDisposer.
extern "C" u8 ro_006E632C[];
extern "C" u8 ro_006D7880[];
extern "C" void func_003E2E68(u8* p);
extern "C" u8* func_004940D0(u8* p);
extern "C" u8* func_001E6CE8(u8* p);
extern "C" void func_004A1520(u8* p);

extern "C" void func_003882C0(u8* self) {
    u8* s = self;
    *(u8**)s = ro_006E632C;
    s += 0x528;
    func_003E2E68(s);
    u8* b = func_004940D0(s);
    *(u8**)(b - 0x528) = ro_006D7880;
    u8* p = func_001E6CE8(b - 0x334);
    p = func_001E6CE8(p - 0x64);
    p = func_001E6CE8(p - 0x128);
    p = func_001E6CE8(p - 0x58);
    func_004A1520(p - 0x10);
}
