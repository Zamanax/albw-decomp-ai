#include "albw_types.h"
#include "vec3.h"

extern char* data_00706E20;
extern void func_004F500C(char* self);
extern u32 func_0028AEF8(char* a, char* b);
extern char* func_0052FBA0(char* mgr, u32 handle);
extern void func_0028B008(char* a, char* m, char* b, char* c);

void func_00163054(char* self) {
  func_004F500C(self);
  s16 k = *(s16*)(self + 0x2e);
  if (k == 1 || k == 2) {
    Vec3 t = *(Vec3*)(self + 0x3d0);
    f32 c = 3.0f;
    f32 x = t.x;
    if (*(u16*)(self + 0x2e) == 1) {
      x = x + c;
    } else {
      x = x - c;
    }
    t.x = x;
    t.y = t.y + 0.1f;
    *(u32*)(self + 0x8f8) = func_0028AEF8((char*)&t, self);
    return;
  }
  u32 h = func_0028AEF8(self + 0x3d0, self);
  *(u32*)(self + 0x8f8) = h;
  u32 p = (u32)data_00706E20;
  char* a = func_0052FBA0((char*)(p + 0x3d800 + 0x3bc), h);
  if (a != 0) {
    char* m = *(char**)(*(char**)(*(char**)(self + 0x40c) + 0x24) + 0x14) + *(s32*)(self + 0x900) * 48;
    func_0028B008(a, m, self + 0x3d0, self + 0x3e8);
  }
}
