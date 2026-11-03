typedef unsigned int u32;
struct S0_10B6D4 { char pad[0x1fc]; u32 m1fc; u32 m200; u32 m204; };
void f_10B6D4(S0_10B6D4* p, u32 a, u32 b, u32 c) { p->m1fc = a; p->m200 = b; p->m204 = c; }
