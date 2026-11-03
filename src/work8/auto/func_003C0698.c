typedef unsigned char undefined;
typedef int code();

extern int func_003ABB24(void *obj, int a, int b);
extern void func_00669EB8(void *dst, int value);

/* Bounds-checked element access; inlined at index 0, so the compare folds away
   while the element-count load at 0xc is still emitted (cf. func_003C080C). */
typedef struct Arr {
  int p0[3];
  int mNum;
  int mMax;
  int *mData;
} Arr;

static inline int *arrAt(Arr *a, int i)
{
  if (i < a->mNum) return &a->mData[i];
  return &a->mData[0];
}

void func_003C0698(int *param_1)

{
  int *pObj;
  int *piVar2;
  int iVar3;
  int iVar4;

  *(undefined *)((char *)param_1 + 0x63) = 0;
  pObj = arrAt((Arr *)*(int *)(param_1[0x12] + 0x8dc), 0);
  if (*(signed char *)((char *)pObj + 0x1c) != 0) {
    return;
  }
  if (*(float *)((char *)pObj + 0x10) >= ((float)0.0f)) {
    if (!(*(float *)((char *)pObj + 8) != *(float *)((char *)pObj + 0x14))) { } else {
      return;
    }
  }
  else if (!(*(float *)((char *)pObj + 8) > ((float)0.0f))) { } else {
    return;
  }
  piVar2 = *(int **)(param_1[0x12] + 0xbcc);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x14))(piVar2);
  }
  func_00669EB8((char *)param_1 + 0x6c,0);
  iVar3 = *(int *)(param_1[0x12] + 0x93c);
  iVar4 = func_003ABB24((void *)iVar3,1,1);
  if (iVar4 != 0) {
    piVar2 = *(int **)(iVar3 + 4);
    (**(code **)(*piVar2 + 0x138))(piVar2,2,1);
  }
  return;
}
