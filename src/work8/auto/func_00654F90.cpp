typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef int s32; typedef unsigned int u32; typedef float f32;
struct Vec3 { f32 x, y, z; };
struct StateControl { u32 count; };
struct Blk800 { u8 pad[0xe2]; u16 m8e2; u16 m8e4; u16 m8e6; u16 m8e8; };
extern "C" void* data_0070FB60;
extern "C" void func_0051D2F4(void*, s32, f32, s32, s32);
extern "C" s32 func_0058AB74(void*);
extern "C" s32 func_0058A8F0(void*);
extern "C" void func_004FABDC(void*, s32, s32, s32);
extern "C" Vec3* func_00520FC0(void*);
extern "C" void func_004D838C(void*, Vec3*, f32, f32, f32);
extern "C" void func_00219738(void*);
extern "C" s32 func_005568D4(void*);
extern "C" void func_00255AB4(void*, s32);
extern "C" u32 func_0055696C(void*, s32);
extern "C" void func_002918D8(void*);
extern "C" void func_0065DF0C(StateControl*, s32);
extern "C" void func_003931EC(StateControl*, s32);
extern "C" s32 func_0065DF78(StateControl*);

void target(u8* p) {
  func_0051D2F4(p + 0x3e8, 0, 0.5f, 0x16c16c1, 0x38e38e3);
  if (func_0058AB74(p) == 1 && func_0058A8F0(p)) {
    func_004FABDC(p, 2, -1, 0);
  }
  func_004D838C(p + 0x3d0, func_00520FC0(p), 0.5f, 0.1f, 1.0f);
  Blk800* b = (Blk800*)(p + 0x800);
  if (b->m8e8 != 0) {
    b->m8e8--;
  } else {
    b->m8e8 = 10;
    if (p[0x8ed] == 1) {
      void* q = data_0070FB60;
      if (q != 0 && func_005568D4(q) > 0) {
        func_00255AB4(q, -1);
      }
    }
  }
  func_00219738(p);
  u8 f = p[0x8ed];
  u16 v = b->m8e6;
  if (f == 0 ? v > 0x28 : v > 0x32) goto dflt;
  if (b->m8e2 != 0) {
    b->m8e2--;
    return;
  }
  if (f == 0) {
    void* q = data_0070FB60;
    if (q != 0) {
      u32 r = func_0055696C(q, 1);
      if (r == 0) goto dflt;
      if (r >= 3) goto dflt;
      if (func_0055696C(q, 1) < 3) {
        func_002918D8(q);
      }
    }
  }
  {
    u8 st = p[0x914];
    func_0065DF0C((StateControl*)(p + 0x8f0), st);
    func_003931EC((StateControl*)(p + 0x8f0), (s8)st);
    func_0065DF78((StateControl*)(p + 0x8f0));
  }
  return;
dflt:
  func_0065DF0C((StateControl*)(p + 0x8f0), 6);
  func_003931EC((StateControl*)(p + 0x8f0), 6);
  func_0065DF78((StateControl*)(p + 0x8f0));
}
