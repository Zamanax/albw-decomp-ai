typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

extern char* data_00706E20;
extern char* data_0070B728;
extern void func_001635F8(char*, f32);
extern void func_004F5BD8(char*, int, int);
extern char* func_0052FBA0(char*, u32);
extern void func_0028B008(char*, char*, char*, char*);
extern int func_004FB208(char*, int, int, int, int);
extern void func_00658604(char*, int);
extern void func_004F68AC(char*, int);

void func_00163210(char* self, int p1) {
  if (p1 == 0) {
    if (*(u32*)(data_0070B728 + 0x44) != 0) {
      u8 b = *(u8*)(self + 0x920);
      int z = 0;
      if (b != 0) {
        func_001635F8(self, 1.0f);
        func_004F5BD8(self, 0, 0);
        char* a = func_0052FBA0(data_00706E20 + 0x3d800 + 0x3bc, *(u32*)(self + 0x8f8));
        if (a != 0) {
          char* ex = *(char**)(self + 0x40c);
          u32 idx = *(u32*)(self + 0x900);
          char* y = *(char**)(ex + 0x24);
          char* base = *(char**)(y + 0x14);
          char* e = base + idx * 0x30;
          func_0028B008(a, e, self + 0x3d0, self + 0x3e8);
        }
      } else {
        int r = func_004FB208(self, 0, 0, 0, z);
        if (r != 0) {
          *(u32*)(self + 0x2e0) |= 2;
          func_00658604(self + 0x8bc, 11);
        }
      }
    }
  }
  func_004F68AC(self, p1);
}
