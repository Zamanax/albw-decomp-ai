typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

#define VT(o, off) (*(void **)((char *)*(void **)(o) + (off)))

extern void *func_00404550(void *);
extern void func_003FE664(void *, u32, u32);

void *func_00569578(char *p5, void *a1, void **r8, s32 r3)
{
  char *sb = (char *)func_00404550(a1);
  u16 f38 = *(u16 *)(p5 + 0x38);
  u32 a4 = *(u32 *)(p5 + 4);
  ((void (*)(void *, u32, s32, u32))VT(sb, 0x24))(sb, a4, r3, f38);

  u32 cnt = *(u32 *)(p5 + 0x10);
  if (cnt) {
    u16 n = *(u16 *)(sb + 0x22);
    u16 m = *(u16 *)(sb + 0x20);
    if (n > m) {
      u16 next = (u16)(m + 1);
      void **arr = *(void ***)(sb + 0x1c);
      u32 *e = (u32 *)((char *)arr + m * 8);
      *(u16 *)(sb + 0x20) = next;
      e[1] = cnt;
      e[0] = (u32)r8;
    }
  }

  s32 r0v = ((s32 (*)(void *))VT(r8, 0x24))(r8);
  s32 cap = (s32)*(u8 *)(p5 + 0x3a);
  u8 lim = (u8)(cap <= r0v ? cap : r0v);

  for (u32 i = 0; i < lim; i++) {
    if (*(u32 *)(p5 + 0x14 + i * 4) != 0) {
      u32 v = ((u32 (*)(void *, u32))VT(r8, 0x28))(r8, i);
      func_003FE664(sb, v, *(u32 *)(p5 + 0x14 + i * 4));
    }
  }
  return sb;
}
