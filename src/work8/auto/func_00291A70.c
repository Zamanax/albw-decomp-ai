extern char G_0070B728[];
extern char G_007111A8[];
extern int func_0052E8A0(int);
extern void* func_002D55D0(int, int);
extern int func_003406B8(int);
extern int func_00552FC0(int);

int func_00291A70(int param_1, int *param_2, char param_3)
{
  int iVar2;
  char cVar1;

  iVar2 = func_0052E8A0(*(int *)(param_1 + 0x10));
  if (iVar2 != 0) {
    return 0;
  }
  iVar2 = (int)*(short *)(param_1 + 0x42);
  cVar1 = *(char *)(((int)G_007111A8) + iVar2 * 0x10);
  if (cVar1 == '\x16') {
    return 0;
  }
  if (cVar1 == '\v') {
    if (iVar2 != 0x4c) {
      return 0;
    }
  }
  else {
    if ((iVar2 == 0x46) || (iVar2 == 0xa6)) {
      return 0;
    }
    if ((cVar1 == '\x0f') || (cVar1 == '\x17')) {
      return 0;
    }
  }
  {
    int *obj = *((int **)G_0070B728);
    int id = *(int *)(param_1 + 0x78);
    if (((*(int *)((char *)obj + 0x44) == 0) ||
         (*(int *)((char *)obj + 0x44) != id)) && (cVar1 != '\x13')) {
      iVar2 = *(int *)(param_1 + 0x1c);
      {
        int *b = (int *)(iVar2 + 0x68);
        b[0] = *(int *)(iVar2 + 0x74);
        b[1] = *(int *)(iVar2 + 0x78);
        b[2] = *(int *)(iVar2 + 0x7c);
      }
      iVar2 = (int)*(short *)(param_1 + 0x42);
      if ((iVar2 == 0x3c) || (iVar2 == 0x3b)) {
        void *sd = func_002D55D0(*(int *)(param_1 + 0x48), 0x3d);
        if (sd != 0) {
          *(char *)sd = param_3;
        }
        int *pp = *(int **)(param_1 + 0x1c);
        if (*(char *)((char *)pp + 0x16e) != '\0') {
          func_003406B8((int)pp);
        }
        return 1;
      }
      if ((iVar2 == 0x3d) || (iVar2 == 0x5e)) {
        if (func_00552FC0(*(int *)(param_1 + 0x1c)) != 0) {
          *(float *)(*(int *)(param_1 + 0x10) + 0x3e0) = 0.2f;
        }
        {
          int *pp = *(int **)(param_1 + 0x1c);
          *(char *)((char *)pp + 0x528) = 1;
          *(int *)((char *)pp + 0x510) = param_2[0];
          *(int *)((char *)pp + 0x514) = param_2[1];
          *(int *)((char *)pp + 0x518) = param_2[2];
        }
        return 1;
      }
      if (param_3 != 0) {
        *(float *)(*(int *)(param_1 + 0x10) + 0x3dc) = 0.0f;
        *(float *)(*(int *)(param_1 + 0x10) + 0x3e4) = 0.0f;
      }
      if (func_00552FC0(*(int *)(param_1 + 0x1c)) != 0) {
        *(float *)(*(int *)(param_1 + 0x10) + 0x3e0) = 0.2f;
      }
      {
        void *sd = func_002D55D0(*(int *)(param_1 + 0x48), 0x3d);
        if (sd != 0) {
          *(char *)sd = param_3;
        }
        int *pp = *(int **)(param_1 + 0x1c);
        if (*(char *)((char *)pp + 0x16e) != '\0') {
          func_003406B8((int)pp);
        }
      }
      return 1;
    }
  }
  return 0;
}
