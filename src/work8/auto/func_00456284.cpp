typedef unsigned char u8;
typedef int s32;
struct S { u8 pad0[0xd]; u8 d; u8 e; u8 pad1[0x68 - 0xf]; u8 sub[0x90 - 0x68]; float v[2]; };
extern "C" void func_001B6A48(void*);
extern "C" void func_0066D2AC(void*, s32);
extern "C" void func_00456284(S* p, float a, float b) {
  float* q = p->v;
  q[0] = a;
  q[1] = b;
  if (p->d == 0 && p->e == 0) {
    p->e = 1;
    func_001B6A48(p);
  }
  func_0066D2AC(p->sub, 1);
}
