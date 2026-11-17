typedef unsigned char u8;

struct Tail { u8 pad[0x14]; u8 m514; u8 pad2[4]; u8 m519; };
struct Obj {
  u8 a[0x494];
  u8 m494;
  u8 b[0x514 - 0x495];
  u8 m514;
  u8 c[0x519 - 0x515];
  u8 m519;
};

extern void func_00332AB8(struct Obj *p);
extern int func_001E4044(struct Obj *p, int n);

void func_0033276C(struct Obj *p)
{
  struct Tail *t = (struct Tail *)((u8 *)p + 0x500);
  if (t->m514) {
    func_00332AB8(p);
    if (p->m494) {
      if (func_001E4044(p, 0x28)) {
        p->m514 = 0;
      }
    } else if (t->m519) {
      if (func_001E4044(p, 0x5a)) {
        p->m514 = 0;
      }
    } else {
      if (func_001E4044(p, 0x14)) {
        p->m514 = 0;
      }
    }
  }
}
