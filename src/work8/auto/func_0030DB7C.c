typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 func_0054B260(void* self, u32 k);
extern u32 func_0058DA24(void* g);
extern void func_00290240(void* a, u8 b, float c, u32 d);
extern void func_0030C144(void* self);
extern void* data_007142C8;
extern void* data_0070FB60;

void func_0030DB7C(void* p) {
  u8* q = *(u8**)((char*)p + 0xf0);
  if (q[0] == 3 && *(u16*)(q + 0xa) == 8) {
    if (func_0054B260(p, 3) == 0) {
      void* g = data_007142C8;
      if (g != 0 && func_0058DA24(g) == 0) {
        void (*fp)(void*) = *(void (**)(void*))((char*)*(void**)p + 0x30);
        fp(p);
      }
    }
    if (func_0054B260(p, 2) == 0x64) {
      u32 b = func_0054B260(p, 1) != 0;
      func_00290240(data_0070FB60, (u8)func_0054B260(p, 0), *(float*)((char*)p + 0x84), b);
    }
  }
  func_0030C144(p);
}
