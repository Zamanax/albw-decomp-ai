#include "../../work7/ds4/ds4.h"

struct Pair64 { u32 a; u32 b; };
struct T { u8 p0[0x10d]; u8 cnt; u8 flag; };

void func_0040D0F0(T* self) {
  if (!self->flag) return;
  self->flag = 0;
  u8* base = (u8*)self;
  T * t0 = self;
  for (s32 i = 0; i < t0->cnt; i++) {
    *(u32*)(base + 0x44 + i * 4) = 0;
    *(u32*)(base + 0x54 + i * 4) = 0;
    *(u32*)(base + 0x64 + i * 8) = 0;
    *(u32*)(base + 0x68 + i * 8) = 0;
    *(u32*)(base + 0x84 + i * 4) = 0;
  }
}
