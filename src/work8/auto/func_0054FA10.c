typedef unsigned int u32;
typedef unsigned char u8;

extern u32 data_0070A848;
extern float data_0073B704[3];
extern int func_00100174(u32* g);
extern void func_00100178(u32* g);

u8* func_0054FA10(u8* self, u32 idx) {
  if (*(u32*)(self + 0xc) > idx) {
    u8* base = self + 0x10;
    if (idx < 0x14) base += 52 * idx;
    return base + 0x24;
  }
  if ((data_0070A848 & 1) == 0 && func_00100174(&data_0070A848)) {
    data_0073B704[0] = 0.0f;
    data_0073B704[1] = 0.0f;
    data_0073B704[2] = 1.0f;
    func_00100178(&data_0070A848);
  }
  return (u8*)data_0073B704;
}
