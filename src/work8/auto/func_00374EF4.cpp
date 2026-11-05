typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32; typedef float f32;
extern "C" void func_00290320(u32 g, s32 v);
extern "C" void func_004FA8A0(void* m);
extern "C" void func_00291A38(u32 g, void* p, f32 f);
extern "C" void func_00291FE0(u32 g, void* p, f32 f);
struct P { u8 pad[0x2c]; void* m2c; };
bool f(char* self, P* p) {
  void* t = p->m2c;
  if (t) {
    u32 g = *(u32*)0x70FB60;
    switch (*(s8*)((char*)t + 1)) {
      case 9:
        func_004FA8A0(p);
        __nop();
        __nop();
        break;
      case 5: {
        s16 v = *(s16*)(*(char**)(self + 0x3a0));
        func_00290320(g, -v);
        __nop();
        __nop();
        break;
      }
      case 8:
        func_00291A38(g, self + 0x3d0, 0.3f);
        __nop();
        __nop();
        break;
      case 0xE:
        func_00291FE0(g, self + 0x3d0, 0.3f);
        break;
    }
  }
  return false;
}
