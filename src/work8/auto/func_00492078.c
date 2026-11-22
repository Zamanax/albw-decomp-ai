typedef float f32;

void func_00492078(f32* out, const f32* a, const f32* b)
{
  f32 r0 = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
  f32 r1 = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
  f32 r2 = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];
  f32 r4 = a[4] * b[0] + a[5] * b[3] + a[6] * b[6];
  f32 r5 = a[4] * b[1] + a[5] * b[4] + a[6] * b[7];
  f32 r6 = a[4] * b[2] + a[5] * b[5] + a[6] * b[8];
  f32 r8 = a[8] * b[0] + a[9] * b[3] + a[10] * b[6];
  f32 r9 = a[8] * b[1] + a[9] * b[4] + a[10] * b[7];
  f32 r10 = a[8] * b[2] + a[9] * b[5] + a[10] * b[8];
  f32 a3 = a[3];
  f32 a7 = a[7];
  f32 a11 = a[11];
  out[0] = r0;
  out[1] = r1;
  out[2] = r2;
  out[3] = a3;
  out[4] = r4;
  out[5] = r5;
  out[6] = r6;
  out[7] = a7;
  out[8] = r8;
  out[9] = r9;
  out[10] = r10;
  out[11] = a11;
}
