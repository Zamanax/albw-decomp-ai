typedef unsigned int u32;
typedef unsigned char u8;
extern char* data_00706E20;
extern u32 func_00588BF0(char*, u32);
extern char* func_0052FBA0(char*, u32);
extern u32 func_00547B48(char*, u32);
extern void func_00588C14(char*, u32, u32);

void func_003677EC(char* self)
{
  char* n;
  char* a;
  char* b;
  if (func_00588BF0(self, 0)) {
    n = *(char**)(self + 0x324) - 8;
    while (n != self + 0x318) {
      a = func_0052FBA0(data_00706E20 + 0x3dbbc, *(u32*)n);
      if (a != 0) {
        b = a + 4;
        if (func_00547B48(b, 0) == 0) {
          func_00588C14(self, 0, 0);
          *(u8*)(self + 0x93d) = 0;
        }
      }
      n = *(char**)(n + 0xc) - 8;
    }
    return;
  }
  n = *(char**)(self + 0x324) - 8;
  while (n != self + 0x318) {
    a = func_0052FBA0(data_00706E20 + 0x3dbbc, *(u32*)n);
    if (a != 0) {
      b = a + 4;
      if (func_00547B48(b, 0) == 0) return;
    }
    n = *(char**)(n + 0xc) - 8;
  }
  *(u8*)(self + 0x93d) = 1;
}
