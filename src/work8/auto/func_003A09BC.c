typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
extern void func_002317C0(void* control, float value);
extern void func_00231340(void* p);
extern void func_003A0C04(void* p);
void func_003A09BC(u8* p) {
  u8* c = p + 0x30;
  u16* h = (u16*)c;
  u16 one = 1;
  *(u32*)(c + 8) = *(u32*)(p + 0x20);
  h[1] = one;
  h[0] = 0;
  func_002317C0(c, 1.0f);
  func_00231340(p + 0x30);
  func_003A0C04(p);
}
