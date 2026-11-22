#include "statemgr.h"
#include "vec3.h"
struct T002C8348 { u8 pad[0x20]; u32 m20; u8 pad2[0x3d0-0x24]; Vec3 m3d0; u8 pad3[0x3e8-0x3dc]; u32 m3e8; u8 pad4[0x410-0x3ec]; s8 m410; u8 pad5[0x430-0x411]; u8* m430; u8 pad6[0x480-0x434]; u8* m480; u8 pad7[0x488-0x484]; u32 m488; };
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004D7EB0(void*, u32, u32, Vec3*);
extern "C" void func_004CEAF0(void*);
extern "C" void* func_004CF478(void*, u32, u32);
extern "C" void* func_002C83FC(T002C8348*);
extern "C" void* func_002C8348(T002C8348* o) {
  u8** pm480 = &o->m480;
  func_00169A80(o->m480);
  u8** pa = &o->m430;
  func_00168E9C(*pm480, o->m430, 0);
  u8* a = *pa;
  *(u32*)(a + 0x164) |= 0x40000000;
  func_004D7EB0(a + 0x80, o->m20, o->m3e8, &o->m3d0);
  func_004CEAF0(*pa);
  u8* b = *pa;
  u32 t0 = o->m488;
  u32 v = t0;
  u32 w = *(u32*)(b + 0x164) | 0x40000000;
  *(u32*)(b + 0x74) = v;
  *(u32*)(b + 0x164) = w;
  *(u32*)(b + 0x78) = v;
  *(u32*)(b + 0x7c) = v;
  s8* k = (s8*)((u8*)o + 0x410);
  if (*k == 0 || *k == 2 || *k == 3) { func_004CF478(o->m430, 1, 0); return func_002C83FC(o); }
  return func_004CF478(o->m430, 0, 0);
}
