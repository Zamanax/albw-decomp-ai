typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef long long s64;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

typedef void* (*VCall3)(void*, u32, u32);

extern f32* data_007162C0;
extern f32 ro_006BE07C[];

void func_003ECB98(void* a0)
{
  VCall3 fn = *(VCall3*)(*(char**)a0 + 8);
  f32* buf = (f32*)fn(a0, 0x200, 0x80);
  data_007162C0 = buf;
  f32 c = 0.0078125f;
  f32 k = 5.9604645e-8f;
  for (s32 i = 0; i < 0x80; i++) {
    f32 x = (f32)i * c * 2.0f * 3.1415901f * 683565248.0f;
    u32 t = (u32)(s64)x;
    f32 frac = (f32)(t & 0x00ffffff);
    f32* e = (f32*)((char*)ro_006BE07C + ((t >> 24) << 4));
    f32 s = e[2] + e[3] * (frac * k);
    buf[i] = 0.5f + s * 0.5f;
  }
}
