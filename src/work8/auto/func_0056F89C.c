typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef unsigned char u8;

struct Out { u32 a; __packed u64 b; };
struct RoBlk { u8 pad[0x18]; u64 v; };
extern struct RoBlk ro_006BB310;
typedef s32 (*VFn)(void*);
void func_0056F89C(struct Out* d, void* c) {
  u32 z = 0;
  u64 v = 0;
  void** vt = *(void***)c;
  VFn f = (VFn)vt[0x14];
  s32 r = f(c);
  if (r == 1) {
    struct RoBlk* ro = &ro_006BB310;
    v = ro->v;
  }
  d->a = z;
  d->b = v;
}
