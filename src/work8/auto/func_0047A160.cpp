#include "albw_types.h"
extern "C" u8* data_007142C8;
extern "C" void func_0066BFFC(void* p, u32 v);
extern "C" void func_0066E7A0(void* p, u32 v) __attribute__((notailcall));
extern "C" void func_0045FCA4(void* p);

extern "C" void func_0047A160(u8* self) {
  u8* o = *(u8**)(self + 0x1f4);
  u8* e8 = *(u8**)(data_007142C8 + 0xe8);
  if (e8 == 0 || e8[0x78] == 3) {
    if (o[0x3c] == 3) func_0066BFFC(o + 0x38, 5);
    func_0066E7A0(self + 0xf0, 9);
    return;
  }
  if (*(u16*)(*(u8**)(self + 0x14) + 0x16) & 4) {
    func_0045FCA4(e8);
    return;
  }
  if (o[0x3c] == 5) func_0045FCA4(e8);
}
