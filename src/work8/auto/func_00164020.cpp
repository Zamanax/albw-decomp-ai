typedef unsigned int u32; typedef unsigned char u8; typedef signed char s8; typedef float f32;
struct Pair { u32 a, b; };
struct Actor;
struct Timeline { void func_00352210(bool, f32); };
struct SM {
  typedef void (Actor::*Func)();
  u32 counter; s8 cur, next; u8 num; char pad[9];
  Timeline* timeline; Actor* owner; Func* enter; Func* exec; Func* exit;
  void func_00658604(int);
  void execute() { (owner->*exec[cur])(); ++counter; if (timeline) timeline->func_00352210(true, (f32)counter); }
};
struct Elt { char p[0x30]; };
struct Y { char p[0x14]; Elt* base; };
struct X { char p[0x24]; Y* y; };
struct Actor {
  char p0[0x3d0]; u32 m3d0; char p3d4[0xc];
  f32 m3e0; u32 m3e4; u32 m3e8;
  char p3ec[0x40c - 0x3ec]; X* m40c;
  char p410[0x8bc - 0x410]; SM state;
  char p8e0[0x8f8 - 0x8e0]; u32 m8f8;
  char p8fc[0x900 - 0x8fc]; u32 m900;
  char p904[0x914 - 0x904]; u32 m914; u32 m918;
  char p91c[0x920 - 0x91c]; u8 m920;
};
extern char* data_00706E20;
f32 func_004F898C();
void func_004F8964(f32*, bool, f32);
void func_004FB0D8(Actor*, f32*);
bool func_004F70A8(Actor*);
bool func_004F8998(Actor*, int, int);
void func_004F48F0(Actor*);
void func_004F5588(Actor*);
void func_004F5BD8(Actor*, int, int);
Actor* func_0052FBA0(char*, u32);
void func_0028B008(void*, void*, void*, void*);

void func_00164020(Actor* o) {
  Pair pr = *(Pair*)&o->m914;
  if (pr.a < pr.b) o->m914 = pr.a + 1;
  if (func_004F70A8(o)) {
    if (o->state.cur != 11 && o->state.cur != 12 && func_004F8998(o, 0, 0)) o->state.func_00658604(11);
    o->state.execute();
    s8 c = o->state.cur;
    if (c != 0 && c != 1 && c != 2 && c != 3 && c != 4) {
      func_004F8964(&o->m3e0, true, func_004F898C());
      func_004FB0D8(o, &o->m3e0);
    } else {
      o->m3e0 = 0.0f;
    }
    func_004F48F0(o);
    func_004F5588(o);
    func_004F5BD8(o, 0, 0);
    if (o->m920) {
      Actor* a = func_0052FBA0(data_00706E20 + 0x3d800 + 0x3bc, o->m8f8);
      if (a) {
        Elt* e = &o->m40c->y->base[o->m900];
        func_0028B008(a, e, &o->m3d0, &o->m3e8);
      }
    }
  }
}
