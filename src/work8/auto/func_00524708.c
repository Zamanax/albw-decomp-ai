typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
struct T { char pad0[8]; u16* arr; char pad1[0x22 - 0x0c]; u16 cnt; char pad2[0x3f - 0x24]; u8 flag; };

u16 func_00524708(struct T* p) {
  if (p->flag != 0) return p->cnt;
  s16 i = (s16)(p->cnt - 1);
  if (i < 0) return p->cnt;
  if (p->arr[i] != 10) return p->cnt;
  for (s32 j = i - 1; j > -1; j--) {
    if (p->arr[j] == 10) i = (s16)j;
    else break;
  }
  return (u16)i;
}
