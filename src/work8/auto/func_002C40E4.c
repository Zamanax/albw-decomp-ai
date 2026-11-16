typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;

extern void func_003529A0(void* self, void* a, void* b);
extern s32 func_00588BE4(void* actor);
extern void* func_0019B504(u32 i);
extern void func_003525AC(void* self, void* req, u32 x);

void func_002C40E4(void* a0, void* a1)
{
  u32 req[9];
  void* p;
  u32 t8;
  u32 t16;
  u32 id;
  void* q;
  if (*(u32*)((char*)a0 + 0x24) != 0) return;
  void* p0 = ((void*(*)(void*))*(void**)((char*)*(void**)a0 + 0x24))(a0);
  if (*(u8*)*(void**)((char*)p0 + 4) == 0) return;
  p = p0;
  ((void(*)(void*))*(void**)((char*)*(void**)p + 8))(p);
  func_003529A0(req, *(void**)((char*)p + 4), a0);
  t8 = ((u32(*)(void*))*(void**)((char*)*(void**)a0 + 0x28))(a0);
  req[2] = t8;
  t16 = ((u32(*)(void*))*(void**)((char*)*(void**)a0 + 0x2c))(a0);
  req[4] = t16;
  if (req[2] == 0) req[3] = (u32)((char*)a1 + 0x3d0);
  if (req[4] == 0) req[4] = (u32)((char*)a1 + 0x14);
  id = (u32)func_00588BE4(a1);
  q = func_0019B504(id);
  if (q != 0) *(u16*)((char*)a0 + 0x3c) = (u16)*(u32*)q;
  func_003525AC((char*)a0 + 4, req, *(u32*)((char*)a1 + 0x408));
}
