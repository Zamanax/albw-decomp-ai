typedef unsigned int u32;
typedef unsigned short u16;

extern void* func_00100118(void*, void (*)(void*), u32, u32);
extern void func_00436438(void*);

void* func_00436444(char* p) {
  u32* s;
  u32 t;
  u32 c;
  u16 h;
  s = (u32*)p;
  s[0] = 0;
  s[1] = 0;
  s[2] = 0;
  *(float*)(p + 0x18) = 1.0f;
  *(u16*)&t = (u16)0x1f;
  t = 0x1f;
  h = *(u16*)&t;
  *(u16*)(p + 0x64) = h;
  p = p + 0xa4;
  c = (u32)p;
  c += 0xc;
  s = (u32*)p;
  s[0] = 0;
  s[1] = 2;
  s[2] = 0;
  if (c != 0)
    s[2] = c;
  return (char*)func_00100118(p + 0xc, func_00436438, 0x4c, 2) - 0xb0;
}
