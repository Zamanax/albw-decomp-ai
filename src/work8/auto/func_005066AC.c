typedef unsigned int u32;
typedef unsigned char u8;
extern void* data_00709D28;
extern void func_004CEA18(void*, u32, u32);
extern void func_004A8304(void*, void*);
extern void func_004A9120(void*, void*);
extern void func_002356D4(void*, u32);

void func_005066AC(u8* p, int idx) {
  u8* e;
  void* s;
  if (*(u32*)(p + 0x630) <= idx) {
    e = *(u8**)(p + 0x634);
  } else {
    e = *(u8**)(p + 0x634) + (idx + (idx << 6)) * 4;
  }
  s = *(void**)(e + 8);
  if (s) {
    func_004CEA18(s, 1, 0);
    func_004CEA18(s, 0, 1);
  }
  if (*(u32*)(p + 0x630) > idx) {
    e = *(u8**)(p + 0x634) + (idx + (idx << 6)) * 4;
  } else {
    e = *(u8**)(p + 0x634);
  }
  func_004A8304(data_00709D28, *(void**)(e + 0x88));
  if (*(u32*)(p + 0x630) > idx) {
    e = *(u8**)(p + 0x634) + 4 * (idx + (idx << 6));
  } else {
    e = *(u8**)(p + 0x634);
  }
  func_004A9120(data_00709D28, e + 0x20);
  func_002356D4(p, idx);
}
