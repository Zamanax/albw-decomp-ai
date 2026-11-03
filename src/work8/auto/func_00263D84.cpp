typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef int s32; typedef unsigned int u32; typedef float f32;
extern "C" s32 func_0058A204(void*, s32);
extern "C" void func_004FBA18(void*, s32, s32, s32, f32, f32, s32, s32, s32);
u32 target(void* pv, u32 ev, void* a3){
  u8* p = (u8*)pv;
  s16 v = *(s16*)(p + 0x508);
  if (v <= 0) {
    u32 id = ev & 0xff;
    if (id == 0x1e || (u32)(id - 0xe) <= 3) {
      if (func_0058A204(a3, 0)) {
        func_004FBA18(p, 9, 10, -1, 0.4f, 0.0f, 0x10, 1, 0x7fff);
      } else {
        func_004FBA18(p, 11, 12, -1, 0.4f, 0.0f, 0x10, 0, 0x7fff);
      }
    }
  }
  u32 id = ev & 0xff;
  if (id == 0x1e || (u32)(id - 0xe) <= 3) return 0xf;
  return ev;
}
