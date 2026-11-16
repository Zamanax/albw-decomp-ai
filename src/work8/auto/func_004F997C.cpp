#include "sead_string.h"

extern "C" void func_001509A4(void* p, const sead::SafeString& s, u32 x);

extern "C" void func_004F997C(void* a0)
{
  func_001509A4(a0, sead::SafeString("SE_EN_REFLECT_SWORD"), 0);
  func_001509A4(a0, sead::SafeString("SE_EN_REFLECT_HAMMER"), 0);
  func_001509A4(a0, sead::SafeString("SE_EN_REFLECT_NET"), 0);
}
