typedef unsigned char byte;

void func_003B62F0(int param_1, unsigned int param_2)
{
  int iVar3;
  int *piVar2;
  byte bVar1;
  unsigned int uVar4;

  piVar2 = *(int **)(param_1 + 0x1c);
  iVar3 = *(int *)(*piVar2 + 0x10);
  if (iVar3 != 0) {
    bVar1 = *(byte *)(iVar3 + 0x44);
    if ((bVar1 & 1) != 0) {
      uVar4 = 1;
    }
    else {
      uVar4 = 0;
    }
    if (uVar4 != param_2) {
      *(byte *)(iVar3 + 0x44) = bVar1 & 0xfe | (byte)param_2;
      if (param_2 != 0) {
        *(byte *)(piVar2 + 0x1c) = *(byte *)(piVar2 + 0x1c) | 2;
      }
    }
  }
}
