typedef unsigned char u8;
typedef float f32;
extern void func_0040D864(void*, u8);
extern void func_0040D8C0(void*, f32);
struct Obj2591 { u8 pad0[0xc]; void* child; u8 pad10[0x5a]; u8 flag; };
void enable(void* c, u8 n) { if (c) func_0040D864(c, n); }
void speed(void* c, f32 v) { if (c) func_0040D8C0(c, v); }
void func_00258ED4(Obj2591* p, f32 v) {
  if (!p->flag) { enable(p->child, 0); speed(p->child, v); }
}
