typedef unsigned char undefined; typedef unsigned char u8;
typedef unsigned short u16; typedef short s16; typedef int s32; typedef unsigned int u32;
typedef int code();
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern u32 data_00725B44;
extern TypeInfo data_00725B48;
extern const char ro_006F64F4[];
extern int __cxa_guard_acquire(u32* g);
extern void __cxa_guard_release(u32* g);
extern char data_00706E20[];
extern void *func_0052FBA0(int mgr, u32 h);
void *func_004CADD8(int unused, u32 h)
{
  void **puVar1;
  void *ti;
  if (h != 0) {
    puVar1 = (void **)func_0052FBA0(*(int *)data_00706E20 + 0x3dbbc, h);
    if (!(data_00725B44 & 1) && __cxa_guard_acquire(&data_00725B44)) {
      { TypeInfo* t = &data_00725B48; t->vt = ro_006F64F4; }
      __cxa_guard_release(&data_00725B44);
    }
    ti = (void *)&data_00725B48;
    if ((puVar1 == (void **)0x0) || ((**(code **)*puVar1)(puVar1,ti) == 0)) {
      puVar1 = (void **)0x0;
    }
    return puVar1;
  }
  return 0;
}
