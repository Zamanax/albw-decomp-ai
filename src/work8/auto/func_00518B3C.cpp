#include "albw_types.h"
extern u8 ro_00694802[];
extern void* data_00712450;
extern "C" u32 func_0014A354(void* a, u32 b);
extern "C" void func_0049F7B8(void* a, void* b, u32 c);
extern "C" void func_0049F8F0(void* a, void* b);
extern "C" void func_00688770(void);
struct Mid518 { u8 pad[0x10]; void* m10; };
struct Self518 { u8 pad[0x10]; Mid518* m10; };
extern "C" void func_00518B3C(Self518* self, u32 b, u32 idx) {
  u8 blk[0x88];
  u32 r6 = func_0014A354(data_00712450, ro_00694802[idx]);
  void* fp = (void*)func_00688770;
  u8* s = blk + 0x80;
  *s = 2;
  *(void**)(blk + 0x84) = fp;
  func_0049F7B8(blk, s, 0);
  *(u32*)(blk + 0x64) = r6;
  Mid518* q = self->m10;
  void* d = q ? q->m10 : 0;
  *(u32*)(blk + 0x6c) = b;
  *(void**)(blk + 0x5c) = d;
  func_0049F8F0(self, blk);
}
