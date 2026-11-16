typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_006F5988[];
extern char ro_0069AE70[];
extern char ro_0069AE68[];
extern char ro_0069AE60[];
extern char ro_0069AE58[];
extern char ro_0069AE50[];
extern char ro_0069AE48[];
extern char ro_0069AE40[];
extern u32 func_00564A78(u32, u32);

typedef struct { void* vt; const char* s; } SafeStr;

void func_002251F4(char* p)
{
  SafeStr n;
  n.s = ro_0069AE70;
  SafeStr* t1 = &n;
  t1->vt = ro_006F5988;
  *(u32*)(p + 0x6d8) = func_00564A78(*(u32*)(p + 0x594), (u32)t1);
  n.s = ro_0069AE68;
  n.vt = ro_006F5988;
  *(u32*)(p + 0x6dc) = func_00564A78(*(u32*)(p + 0x594), (u32)&n);
  SafeStr* t0 = &n;
  t0->s = ro_0069AE60;
  t0->vt = ro_006F5988;
  *(u32*)(p + 0x6e0) = func_00564A78(*(u32*)(p + 0x594), (u32)&n);
  n.s = ro_0069AE58;
  n.vt = ro_006F5988;
  *(u32*)(p + 0x6e4) = func_00564A78(*(u32*)(p + 0x594), (u32)&n);
  n.s = ro_0069AE50;
  n.vt = ro_006F5988;
  *(u32*)(p + 0x6e8) = func_00564A78(*(u32*)(p + 0x594), (u32)&n);
  n.s = ro_0069AE48;
  n.vt = ro_006F5988;
  *(u32*)(p + 0x6ec) = func_00564A78(*(u32*)(p + 0x594), (u32)&n);
  n.s = ro_0069AE40;
  n.vt = ro_006F5988;
  *(u32*)(p + 0x6f0) = func_00564A78(*(u32*)(p + 0x594), (u32)&n);
}
