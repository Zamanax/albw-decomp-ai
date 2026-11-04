typedef unsigned int u32;
typedef unsigned long long u64;

struct A { char pad[0x78]; __packed u64 v; };
struct B { char pad[0x78]; u64 v; };
struct H { A* p; };
struct G { B* p; };

int f(H* a, G* b) {
  A* x = a->p;
  __packed u64* q = &x->v;
  u64 xv = *q;
  B* y = b->p;
  u64 yv = y->v;
  if (xv < yv) return -1;
  u64 d = yv ^ xv;
  return d ? 1 : 0;
}
