#include "flags.h"
extern "C" void func_004FABDC(void*, s32, s32, u32);
extern "C" void func_004FB4E0(void*, f32);
struct En0022 { char pad[0x59c]; Flag32 fl; };
extern "C" void func_0022A0E4(char* p)
{
  En0022* e = (En0022*)p;
  e->fl.reset(1);
  e->fl.reset(2);
  e->fl.reset(0xc);
  Flag32* t0 = &e->fl;
  t0->reset(0x80);
  func_004FABDC(p, 9, 0, 0);
  f32 z = 0.0f;
  func_004FB4E0(p, z);
  *(f32*)(p + 0x3dc) = z;
  *(f32*)(p + 0x3e0) = z;
  *(f32*)(p + 0x3e4) = z;
  *(u8*)(p + 0xd08) = 0;
}
