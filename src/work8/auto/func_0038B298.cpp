#include "../nm3/ds4.h"
struct G { u8 p[0x10]; void* m10; };
struct H { u8 p[0x1c]; u32 m1c; u32 m20; u32 m24; u32 m28; };
extern void* data_00711010;
extern "C" void func_002C2C9C(void*, u32);
extern "C" u32 func_002C2D00(void*);
extern "C" u32 func_00537B48(u32);
extern "C" void func_002D42E8(void*);
struct T { u32 m0; u32 m4; u32 m8; u8 p0c[0x1c - 0x0c]; u32 arr[4]; };
void f(T* self) {
  G* g = (G*)data_00711010;
  H* h = (H*)g->m10;
  {
    u8 buf[0x40];
    func_002C2C9C(buf, h->m1c);
    buf[0x1c] = 1;
    *(u32*)(buf + 0x18) |= 1;
    self->arr[0] = func_002C2D00(buf);
    func_002C2C9C(buf, h->m20);
    buf[0x1c] = 1;
    *(u32*)(buf + 0x18) |= 1;
    self->arr[1] = func_002C2D00(buf);
    func_002C2C9C(buf, h->m24);
    buf[0x1c] = 1;
    *(u32*)(buf + 0x18) |= 1;
    self->arr[2] = func_002C2D00(buf);
    func_002C2C9C(buf, h->m28);
    buf[0x1c] = 1;
    *(u32*)(buf + 0x18) |= 1;
    self->arr[3] = func_002C2D00(buf);
  }
  u32 idx = func_00537B48(self->m8);
  self->m4 = self->arr[idx == 4 ? 0 : idx];
  func_002D42E8(self);
}
