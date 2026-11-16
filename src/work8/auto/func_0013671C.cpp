#include "sead_string.h"

extern "C" {
void func_00150A84(void* self, const SafeString& s, int v);
void* func_002C11E8(void* buf, unsigned id, unsigned arg, unsigned flag);
void func_0016898C(void* anim, void* r);
}

static char* elemAt(char* a, unsigned i) {
  if (i < *(unsigned*)(a + 0xC)) return (char*)*(unsigned*)(a + 0x14) + i * 4;
  return (char*)*(unsigned*)(a + 0x14);
}

extern "C" void func_0013671C(char* self) {
  unsigned char req[0x5c];
  func_00150A84(self, SafeString("SE_Curtain_BURN"), 0);
  void* r = func_002C11E8(req, 1, 1, 0);
  func_0016898C(*(void**)(self + 0x484), r);
  *(float*)(elemAt(*(char**)(self + 0x484), 0) + 0x10) = 1.0f;
  r = func_002C11E8(req, 0, 1, 0);
  func_0016898C(*(void**)(self + 0x488), r);
  *(float*)(elemAt(*(char**)(self + 0x488), 0) + 0x10) = 1.0f;
}
