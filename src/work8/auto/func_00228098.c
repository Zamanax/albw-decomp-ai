typedef unsigned char undefined; typedef unsigned char undefined1; typedef unsigned int undefined4;
extern int FUN_0016898c();
extern int FUN_002c11e8();
extern int FUN_0036C45C();
extern int FUN_004CF478();
extern int FUN_00151148();

void FUN_00228098(int param_1)
{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_68[96];

  iVar1 = *(int *)(*(int *)(param_1 + 0x68c) + 0x14);
  if (*(char *)(iVar1 + 0x1c) == '\0' &&
      ((((float)0.0f) <= *(float *)(iVar1 + 0x10)) ?
         (*(float *)(iVar1 + 8) == *(float *)(iVar1 + 0x14)) :
         (*(float *)(iVar1 + 8) <= ((float)0.0f)))) {
    uVar2 = FUN_002c11e8(auStack_68, 0x11, 0xa, 0);
    FUN_0016898c(*(undefined4 *)(param_1 + 0x68c), uVar2);
  }
  FUN_0036C45C(param_1 + 0x48c);
  if (*(unsigned int *)(param_1 + 0x550) < *(unsigned int *)(param_1 + 0x554)) {
  } else {
    FUN_004CF478(*(undefined4 *)(param_1 + 0x594), 0, 0);
    FUN_00151148(*(undefined4 *)(param_1 + 0x698), 0);
  }
  if (*(int *)(param_1 + 0x578) == 6) {
    *(undefined1 *)(param_1 + 0x2d7) = 1;
  }
  return;
}
