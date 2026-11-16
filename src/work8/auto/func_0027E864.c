typedef unsigned int u32;
typedef unsigned char u8;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

typedef struct EffRet12 { u32 w[3]; } EffRet12;
extern u32 func_00588BF0(void* self, int arg);
extern void func_0027E7E4(void* self, int arg);
extern EffRet12 func_004A1B9C(void* anim, const char* name);
extern void func_0014E138(void* self, int arg);

void func_0027E864(void* a0, int a1)
{
  char* p = (char*)a0;
  u32 st = *(u8*)(p + 0x418);
  void* m;
  const char* name;
  if (st == 1) {
    if (!func_00588BF0(a0, 0)) {
      func_0027E7E4(a0, 0);
      m = *(void**)(p + 0x344);
      name = "SwitchBlueOn";
      if (m != 0) goto call;
    }
    goto done;
  }
  if (!func_00588BF0(a0, 0)) goto done;
  func_0027E7E4(a0, 1);
  m = *(void**)(p + 0x344);
  name = "SwitchRedOn";
  if (m == 0) goto done;
call:
  func_004A1B9C(m, name);
done:
  func_0014E138(a0, a1);
}
