#include "sead_container.h"

extern char data_0070BCD0[];

typedef unsigned int u32;
typedef signed char s8;

void func_002C34A4(char* a0, s32 a1)
{
  if (*(s8*)(a0 + 0xa1) == a1) return;
  char* base = *(char**)data_0070BCD0;
  s32 i = *(s8*)(a0 + 0xa2);
  OffsetList<char>* l = (OffsetList<char>*)(base + 0x118);
  if (a1 != 0) {
    if ((u32)i < 2) l += i;
    l->pushBack(a0);
  } else {
    if ((u32)i < 2) l += i;
    sead::OffsetList<char> * t0 = l;
    t0->erase(a0);
  }
  *(s8*)(a0 + 0xa1) = (s8)a1;
}
