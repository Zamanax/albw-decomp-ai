typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned long long u64;
struct Node41 { void* m0; struct Node41* next; u64 v; void (*fn)(u64, u32); u32 arg; };
struct Inner41 { u32 m0; u32 m4; u32 m8; struct Node41* first; struct Node41* head_next; u8 flag; };
struct Outer41 { u32 m0; u32 cnt; u32 m8; struct Inner41* inner; };
extern u32 func_0041D9A0(struct Outer41*, u32);
extern void func_003E69B8(void*, void*, void*);
extern void func_00111EF0(void*, void*);
void func_0041D908(struct Outer41* o) {
  u32 r7 = func_0041D9A0(o, 0);
  u8 z = 0;
  for (;;) {
    struct Inner41* in;
    if (o->cnt == 0) break;
    in = o->inner;
    if (r7 != 0) in->flag = z;
    if (in->flag != 0) {
      struct Node41* p = (struct Node41*)&in->first;
      for (;;) {
        struct Node41* f = in->first;
        if (p == f) break;
        p = p->next;
        if (p->fn) p->fn(p->v, p->arg);
      }
    }
    func_003E69B8(&in->m8, in->first, &in->first);
    func_00111EF0(&o->cnt, in);
  }
}
