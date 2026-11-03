#include "albw_types.h"
struct M { u8 p0[0x8d4]; void* m8d4; u8 p1[0x8f4 - 0x8d8]; u32 m8f4; };
struct T { u8 p0[4]; M* m4; u8 p1[0xc - 8]; s8 mc; u8 p2[0x34 - 0xd]; void* m34; u8 m38; u8 m39; };
extern "C" void func_003AB994(T*, void*);
extern "C" void func_003AB8DC(T*, void*);
extern "C" void func_001151EC(void*, void*);
extern "C" void func_004CEAF0(void*);
extern "C" u32 func_0018B874(void*, void*, u32, bool, u32);
extern "C" void func_0018AFD4(u32);
void f(T* self) {
  func_003AB994(self, self->m34);
  func_003AB8DC(self, self->m34);
  char* p = (char*)self->m34;
  char* q = p + 0x80;
  *(u32*)(p + 0x164) |= 0x40000000;
  M* m = self->m4;
  void* d = m->m8d4;
  u32 idx = m->m8f4;
  char* base = (char*)*(u32*)(*(u32*)((char*)d + 0x24) + 0x14);
  func_001151EC(q, base + idx * 0x30);
  func_004CEAF0(self->m34);
  if (self->m39 && self->m38) {
    self->m39 = 0;
    char* c = (char*)self->m4;
    u32 r = func_0018B874(c + 0x3d0, c + 0x3dc, *(u32*)(c + 0x3e8), (s8)self->mc > 1, *(u32*)(c + 0x2cc));
    if (r) func_0018AFD4(r);
  }
}
