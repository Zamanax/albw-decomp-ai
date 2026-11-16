extern void* data_0070B960;
extern void* func_0051E5B8(void*);
extern void func_005801EC(void*, float*, unsigned);
extern void* func_0051E5D8(void*);
extern void func_0057D2C4(void*, float*, float*);

unsigned func_00588F28(unsigned a0, unsigned a1, float fa0, float fa1)
{
  float v[3];
  float r[3];
  unsigned res;
  func_005801EC(func_0051E5B8(data_0070B960), v, a1);
  func_0057D2C4(func_0051E5D8(data_0070B960), r, v);
  res = (r[0] < -fa0) ? 4u : 0u;
  res |= (r[0] > fa0) ? 8u : 0u;
  res |= (r[1] > fa1) ? 1u : 0u;
  res |= (r[1] < -fa1) ? 2u : 0u;
  return res;
}
