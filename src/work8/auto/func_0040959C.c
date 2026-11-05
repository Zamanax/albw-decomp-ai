extern int FUN_00412a3c();
extern int FUN_00412bb4();
extern int FUN_00412c68();
extern int FUN_00412c8c();
extern int FUN_00412ef4();

static __inline void hlp0(int iVar2, int iVar1) { *(unsigned int *)(iVar2 + 0xc) = *(unsigned int *)(iVar1 + 0x184); }

void FUN_0040959C(int param_1)
{
  int iVar1 = FUN_00412bb4(param_1);
  int iVar1_c81 = iVar1;
  int iVar2 = FUN_00412a3c(iVar1_c81, 5);
  hlp0(iVar2, iVar1);
  *(unsigned char *)(iVar2 + 4) = 0x30;
  *(int *)(iVar2 + 0x10) = param_1;
  int iVar2_c82 = iVar2;
  FUN_00412c68(iVar1, iVar2_c82);
  int iVar3 = FUN_00412c8c(iVar1, 1);
  FUN_00412ef4(iVar1, iVar3);
  *(unsigned int *)(param_1 + 0x21c) = 0;
  *(unsigned int *)(param_1 + 0x218) = 0;
}
