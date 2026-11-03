typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
struct Obj15AD00;
struct Linked15AD00 { char pad[0x8bc]; u32 state; u8 mode; };
extern bool func_0058A8F0(Obj15AD00*);
extern Linked15AD00* func_00161178(Obj15AD00*);
extern void func_0065836C(u32*, s32);
extern void func_00160430(Obj15AD00*, s32);
void action15AD00(Linked15AD00* q, s32 state) { if (q->mode != 22) func_0065836C(&q->state, state); }
void phase15AD00(Obj15AD00* p, s32 state) { Linked15AD00* q = func_00161178(p); if (q) action15AD00(q, state); }
extern "C" void target(Obj15AD00* p) { if (!func_0058A8F0(p)) return; phase15AD00(p, 4); func_00160430(p, 4); }
