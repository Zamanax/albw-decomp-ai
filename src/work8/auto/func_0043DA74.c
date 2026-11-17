typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

extern void* data_007142C8;
extern void func_0051B1E4(void*);
extern void func_002BEE00(void*);
extern void func_0047A5B4(void*, f32*, u32);

void func_0043DA74(u8* self) {
  f32 v[2];
  func_0051B1E4(data_007142C8);
  func_002BEE00(*(void**)(self + 0x130));
  v[0] = 94.0f;
  v[1] = -108.0f;
  u32 b;
  if (self[0x176] & 1) { b = 1; } else { b = 0; }
  func_0047A5B4(*(void**)(self + 0x158), v, b);
}
