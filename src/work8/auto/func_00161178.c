typedef unsigned char undefined; typedef unsigned char u8;
typedef unsigned short u16; typedef short s16; typedef int s32; typedef unsigned int u32;
typedef int code();
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00725B8C;
extern TypeInfo data_00725B90;
extern const char ro_006F6500[];
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
extern char data_00706E20[];
extern void *func_0052FBDC(int mgr, u32 id, u32 skip);
void *func_00161178(int param_1)
{
  void **puVar1;
  int iVar2;
  void *ti;
  u32 *obj;

  if ((*(u16 *)(param_1 + 0x2e) & 0xff) != 0) {
    if (*(int *)(param_1 + 0xdfc) >= 0) {
      puVar1 = (void **)func_0052FBDC(*(int *)data_00706E20 + 0x3dbbc, *(int *)(param_1 + 0xdfc), 0);
      if (!(data_00725B8C & 1) && __cxa_guard_acquire(&data_00725B8C)) {
        { TypeInfo* t = &data_00725B90; t->vt = ro_006F6500; }
        __cxa_guard_release(&data_00725B8C);
      }
      ti = (void *)&data_00725B90;
      if ((puVar1 == (void **)0x0) || ((**(code **)*puVar1)(puVar1,ti) == 0)) {
        puVar1 = (void **)0x0;
      }
      return puVar1;
    }
    return 0;
  }
  return (void *)param_1;
}
