#include "albw_types.h"
extern void func_00409BC8(void*, void*);
extern void* func_0056A1C0(void*);
extern void func_002589F8(void*, void*, int);
extern void func_0010CF7C(void*, int);
extern void func_00409B8C(void*);
void func_002587A8(char* self) {
  void* tmp;
  func_00409BC8(&tmp, self + 0xc);
  if (tmp) {
    void* r = func_0056A1C0(tmp);
    func_002589F8(self, r, 1);
    if (self[0x6b]) {
      u32 a = *(u32*)(self + 0x58);
      u32 b = *(u32*)(self + 0x50);
      if (a >= b && a > (u32)r) func_0010CF7C(self + 0x14, 0);
    }
    *(void**)(self + 0x58) = r;
  } else {
    func_0010CF7C(self + 0x14, 0);
  }
  func_00409B8C(&tmp);
}
