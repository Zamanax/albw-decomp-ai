typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef float f32;
struct BaseB { BaseB(void*); virtual ~BaseB(); char p[0x20 - 4]; };
struct Rec { u16 a; s16 b; f32 c; u32 d; Rec() : a(0), b(-1), c(0), d(0) {} };
struct S : BaseB { Rec r0, r1; S(void*); };
S::S(void* p) : BaseB(p) {}
