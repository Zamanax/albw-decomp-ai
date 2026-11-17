#include "albw_types.h"

extern "C" s32 func_00588BF0(void* e, s32 a);
extern "C" f32 func_00521298(void* e);
extern "C" void func_0065F7E8(void* p, s32 n);

void func_0024B2F0(void* self) {
  char* p = static_cast<char*>(self);
  u16 h = *(u16*)(p + 0x36);
  char* q = p + 0x400;
  q = q + 0x1c;
  if (h != 0) {
    if (!func_00588BF0(self, 0)) return;
    *(f32*)(*(char**)(p + 0x40c) + 0x134) = 0.5f;
  } else {
    f32 d = func_00521298(self);
    if (*(s32*)&d >= 0x41100000) return;
  }
  func_0065F7E8(q, 2);
}
