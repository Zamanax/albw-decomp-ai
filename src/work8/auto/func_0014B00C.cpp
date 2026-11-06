#include "albw_types.h"
extern u8 ro_00694802[];
extern void* data_00712450;
extern "C" u32 func_0014A354(void* a, u32 b);
extern "C" void func_0049F7B8(void* a, void* b, u32 c);
extern "C" void func_0049F8F0(void* a, void* b);
extern "C" void func_006881E4();
struct Tmp { u8 kind; void* fn; };
struct Blk { u8 p0[0x5c]; void* m5c; u8 p1[4]; u32 m64; u32 m68; void* m6c; u8 p2[0x10]; };
struct Obj { u8 p0[0x10]; void* m10; };
extern "C" void func_0014B00C(Obj* self, void* a1, u32 a2, u32 a3) {
  Blk blk;
  Tmp tmp;
  u32 r6 = func_0014A354(data_00712450, ro_00694802[a2]);
  void* fp = (void*)func_006881E4;
  Tmp* tp = &tmp;
  tp->kind = 2;
  tp->fn = fp;
  func_0049F7B8(&blk, tp, 0);
  blk.m64 = r6;
  void* p = self->m10;
  if (p) p = *(void**)((char*)p + 0x10);
  blk.m6c = a1;
  blk.m5c = p;
  func_0049F8F0(self, &blk);
}
