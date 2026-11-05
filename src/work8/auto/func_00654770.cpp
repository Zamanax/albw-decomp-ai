typedef unsigned char u8; typedef unsigned short u16;
typedef int s32; typedef unsigned int u32; typedef float f32;
struct Vec3 { f32 x, y, z; };
struct StateControl { u32 count; };
struct Blk { u8 pad[0xe2]; u16 m8e2; };
extern "C" void* data_0070FB60;
extern "C" u32 func_005401E0(void*);
extern "C" void func_0051D2F4(s32*, s32, f32, s32, s32);
extern "C" Vec3* func_00520FC0(void*);
extern "C" bool func_004D838C(Vec3*, const Vec3*, f32, f32, f32);
extern "C" bool func_005211BC(void*, f32, f32);
extern "C" f32 func_004F944C();
extern "C" void func_0065DF0C(StateControl*, s32);
extern "C" void func_003931EC(StateControl*, s32);
extern "C" __attribute__((notailcall)) void func_0065DF78(StateControl*);

static void setState0(u8* p) {
  func_0065DF0C((StateControl*)(p + 0x8f0), 0);
  func_003931EC((StateControl*)(p + 0x8f0), 0);
  func_0065DF78((StateControl*)(p + 0x8f0));
}

void target(u8* p) {
  if (!(data_0070FB60 && func_005401E0(data_0070FB60))) {
    setState0(p);
    return;
  }
  func_0051D2F4((s32*)(p + 0x3e8), 0, 0.5f, 0x16c16c1, 0x38e38e3);
  func_004D838C((Vec3*)(p + 0x3d0), func_00520FC0(p), 0.5f, 0.1f, 1.0f);
  if (func_005211BC(p, 0.5f, 0.0f)) {
    func_0065DF0C((StateControl*)(p + 0x8f0), 5);
    func_003931EC((StateControl*)(p + 0x8f0), 5);
    func_0065DF78((StateControl*)(p + 0x8f0));
    return;
  }
  Blk* b = (Blk*)(p + 0x800);
  if (b->m8e2 != 0) { b->m8e2--; return; }
  *(f32*)(p + 0x3e0) = func_004F944C();
  setState0(p);
}
