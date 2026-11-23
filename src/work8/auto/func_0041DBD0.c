#include "albw_types.h"
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern void func_0041D908(void*);
extern u32 func_0041D9A0(void*, u32);
extern void func_003E67D8(void*, s32);
extern void func_0041D87C(void*);
extern void func_003E69B8(void*, void*, void*);
extern void func_00111EF0(void*, void*);
extern void func_003E6AD4(void*, u32);
extern void func_003E6B78(void*, void*);


void func_0041DBD0(void* p, u32 n)
{
  u32 r8;
  u8 z;
  void* r5;
  void* r4;
  if (n == 0) {
    func_0041D908(p);
    func_003E67D8(*(void**)p, 3);
    func_0041D87C(p);
    return;
  }
  r8 = func_0041D9A0(p, n);
  z = 0;
  for (;;) {
    if (!(*(s32*)((char*)p + 4) > (s32)n)) break;
    r5 = *(void**)((char*)p + 0xc);
    if (r8 != 0) *((u8*)r5 + 0x14) = z;
    if (*((u8*)r5 + 0x14) != 0) {
      r4 = (char*)r5 + 0xc;
      for (;;) {
        void (*fn)(u64, u32);
        void* h = *(void**)((char*)r5 + 0xc); if (r4 == h) break;
        r4 = *(void**)((char*)r4 + 4);
        fn = *(void (**)(u64, u32))((char*)r4 + 0x10);
        if (fn == 0) continue;
        fn(*(u64*)((char*)r4 + 8), *(u32*)((char*)r4 + 0x14));
        continue;
      }
    }
    func_003E69B8((char*)r5 + 8, *(void**)((char*)r5 + 0xc), (char*)r5 + 0xc);
    func_00111EF0((char*)p + 4, r5);
  }
  func_003E6AD4(*(void**)p, n);
  func_003E6B78(*(void**)p, *(void**)((char*)p + 4));
  func_0041D87C(p);
}
