typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

class SafeString_006F5988 {
public:
    SafeString_006F5988(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
struct Ctr2 { u32 cur; u32 max; };
extern "C" {
extern void func_001507D8(unsigned, const SafeString_006F5988&, unsigned);
extern unsigned func_004CA984(unsigned);
extern void func_0066A284(unsigned, unsigned);
extern unsigned func_00520FC0(unsigned);
extern void func_004C9AFC(unsigned, unsigned);
void func_004CAAD0(unsigned a0)
{
  func_001507D8(a0, SafeString_006F5988("SE_Bee_FLY_ATTACK"), 0);
  if (func_004CA984(a0) != 0) {
    func_0066A284(a0 + 0x8BC, 9);
    return;
  }
  Ctr2 c = *(Ctr2*)((char*)a0 + 0x9C8);
  if (c.cur < c.max) {
    c.cur = c.cur + 1;
    *(u32*)((char*)a0 + 0x9C8) = c.cur;
  } else {
    func_0066A284(a0 + 0x8BC, 4);
  }
  func_004C9AFC(a0, func_00520FC0(a0));
}

}
