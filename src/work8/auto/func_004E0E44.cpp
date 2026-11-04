typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

extern char ro_006930F4[];
extern char ro_006930F0[];
extern char ro_006F5988[];
extern char data_0070FB60[];
extern char data_00711F50[];
extern unsigned func_00588BE4(unsigned);
extern unsigned func_001DE128(unsigned, unsigned, unsigned);
extern unsigned func_004EA104(unsigned, unsigned, unsigned);
struct C_006F5980 {
    virtual void G7_vf();
    unsigned f4;
    C_006F5980(unsigned a0) { f4 = a0; }
};
template <class T> static inline unsigned G7_ref(const T& t) { return (unsigned)&t; }
void func_004E0E44(unsigned a0)
{
  unsigned t5, t2;
  t5 = (func_00588BE4(a0) == *(unsigned *)ro_006930F4) ? 12 : 4;
  t2 = func_00588BE4(a0) == *(unsigned *)ro_006930F0;
  if (func_001DE128(*(unsigned *)data_0070FB60, t5, t2) == 0) {
    return;
  }
  func_004EA104(*(unsigned *)data_00711F50, (unsigned)G7_ref(C_006F5980((unsigned)"SE_PL_HEART_GET")), 0);
  *(unsigned char *)((char *)a0 + 0x2D7) = 1;
}
