#include "sead_string.h"

extern "C" void func_00150A84(void*, const SafeString&, u32);

extern "C" void func_00392ACC(void* self)
{
  unsigned char* b = (unsigned char*)self;
  if (*(void**)b != 0) {
    if (b[0xd] != 0) {
      if (b[0xf] != 0) {
        func_00150A84(*(void**)b, SafeString("SE_OBJ_FALL_WATER_L"), 0);
      } else {
        func_00150A84(*(void**)b, SafeString("SE_OBJ_FALL_WATER"), 0);
      }
    }
  }
  b[0xc] = 0;
  *(float*)(*(unsigned char**)(b + 8) + 4) = 0.0f;
}
