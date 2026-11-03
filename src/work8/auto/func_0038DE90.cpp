typedef unsigned int u32;
typedef unsigned short u16;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

class SafeString_006F5980 {
public:
    SafeString_006F5980() {}
    SafeString_006F5980(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
extern "C" {
extern void func_001509A4(unsigned, const SafeString_006F5980&, unsigned);
void func_0038DE90(unsigned a0)
{
  char* self = (char*)a0;
  char* p = *(char**)(self + 0x2c);
  if (*(u16*)(p + 0x42) == 0x9d) {
    if (*(u32*)(*(char**)(self + 0x28) + 0x468) >= 3) {
      func_001509A4(*(unsigned*)(self + 0x28), SafeString_006F5980("SE_PL_Net_SWING_Lv2"), 0);
    } else {
      func_001509A4(*(unsigned*)(self + 0x28), SafeString_006F5980("SE_PL_Net_SWING"), 0);
    }
  }
}
}
