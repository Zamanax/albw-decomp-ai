typedef unsigned char undefined; typedef unsigned char undefined1; typedef unsigned short undefined2;
typedef unsigned int undefined4; typedef signed char s8; typedef unsigned char u8;
typedef unsigned short u16; typedef short s16; typedef int s32; typedef unsigned int u32;
typedef unsigned char bool;
#define true 1
#define false 0
typedef int code();
/* L2C-SYMBOL __cxa_guard_acquire 00100174 */
/* L2C-NOP-SYMBOL __cxa_guard_release */
extern char data_00706E20[];
extern char data_00725B8C[];
extern char data_00725B90[];
extern const char ro_006F6500[];
extern int __cxa_guard_acquire(u32 *g);
extern void __cxa_guard_release(u32 *g);
extern void *func_0052FBDC(int, int, int);

void *func_0015B580(int param_1, u32 param_2)
{
  void **puVar1;
  int iVar2;
  void *ti;
  u32 *obj;

  if ((*(u16 *)(param_1 + 0x2e) & 0xff) == 0) return 0;
  if (param_2 < 2) {
    char *s = (char *)param_1 + 0xc00;
    int *tbl = (int *)(s + 0x1f4);
    iVar2 = tbl[param_2];
    if (iVar2 >= 0) {
      puVar1 = (void **)func_0052FBDC(*(int *)data_00706E20 + 0x3dbbc, iVar2, 0);
      if (((*(u32 *)data_00725B8C) & 1) == 0 && __cxa_guard_acquire((u32 *)data_00725B8C) != 0) {
        obj = (u32 *)data_00725B90;
        *obj = (u32)ro_006F6500;
        __cxa_guard_release((u32 *)data_00725B8C);
      }
      ti = (void *)data_00725B90;
      if (puVar1 == 0 || (**(code **)*puVar1)(puVar1, ti) == 0) puVar1 = 0;
      return puVar1;
    }
    return 0;
  }
  return func_0015B580(param_1, 0);
}
