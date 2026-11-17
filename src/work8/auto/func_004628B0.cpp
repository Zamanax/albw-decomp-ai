typedef unsigned int u32; typedef int s32; typedef short s16; typedef float f32;
struct Elem { char p0[0x1c]; f32 a; f32 b; };
struct Tbl {
  u32 a0; u32 a4; u32 count; char* base;
  Elem& at(u32 i) {
    if (i < count) return *(Elem*)(base + i * 0x38);
    return *(Elem*)base;
  }
};
struct Obj { char p0[0x1c]; Tbl* tbl; char p1[0x0e]; s16 idx; char p2[0x5c]; f32 f8c; u32 u90; };

extern "C" void func_001B6D40(void*);
extern "C" void func_00231448(void*);

extern "C" void func_004628B0(Obj* o) {
  func_001B6D40(o);
  if (o->f8c > 0.0f) {
    Tbl* t = o->tbl;
    u32 i = (u32)(s32)o->idx;
    f32 b = t->at(i).b;
    f32 q = b / o->f8c;
    t->at(i).a = q;
  }
  func_00231448((char*)o + 0x20);
  o->u90 = 0;
}
