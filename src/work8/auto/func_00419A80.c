typedef unsigned int u32;
typedef int s32;
extern void func_00111EF0(void*, void*);
extern void func_00112364(void*, void*, void*);
extern void func_0041998C(void*, void*);
extern void func_00414570(void*);
void func_00419A80(char* p, char* q)
{
  char* pp = p;
  char* qq = q;
  char* a1 = pp + 4;
  func_00111EF0(a1, qq + 0x58);
  char* x = pp + 0x10;
  char* y = pp + 0x14;
  func_00112364(x, y, qq + 0x58);
  func_0041998C(pp, qq);
  char* it = qq + 0x58;
  char* end = pp + 8;
  while (it != end) {
    s32 c = *(s32*)(it - 0x18);
    if (c <= 1) return;
    if (c != 0x7fff) {
      func_00414570(it - 0x58);
    }
    it = *(char**)it;
  }
}
