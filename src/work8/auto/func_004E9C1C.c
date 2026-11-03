typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern void* data_0070FB60;
extern unsigned func_0053F090(void*);
extern void func_002963D0(unsigned);
extern void func_002959E4(unsigned);
extern float func_00540A64(unsigned);
extern void func_00320E80(unsigned, unsigned, unsigned, float);

void func_004E9C1C(unsigned a0)
{
  unsigned t2;
  if (func_0053F090(data_0070FB60)) {
    func_002963D0(*(unsigned *)((char *)a0 + 0x4c));
  } else {
    func_002959E4(*(unsigned *)((char *)a0 + 0x4c));
  }
  t2 = (unsigned)func_00540A64(*(unsigned *)((char *)a0 + 0x4c));
  func_00320E80(*(unsigned *)((char *)a0 + 0x24), 0x4000004, t2, 0.0f);
  func_00320E80(*(unsigned *)((char *)a0 + 0x24), 0x4000008, t2, 0.0f);
  func_00320E80(*(unsigned *)((char *)a0 + 0x24), 0x4000009, t2, 0.0f);
  func_00320E80(*(unsigned *)((char *)a0 + 0x24), 0x400000A, t2, 0.0f);
  return;
}
