typedef unsigned int u32;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

class SafeString_006F5980 {
public:
    SafeString_006F5980(const char* s) : mStringTop(s) {}
    virtual void assureTerminationImpl_() const;
    const char* mStringTop;
};
extern "C" {
extern void func_00150A84(void*, const SafeString_006F5980&, u32);
void func_0012B87C(char* a0)
{
  if (*(u32*)(a0 + 0x3a0) == *(u32*)(a0 + 0x8e0)) {
    func_00150A84(a0, SafeString_006F5980("SE_Pamet_LAND_SHELL"), 0);
  } else {
    func_00150A84(a0, SafeString_006F5980("SE_Pamet_LAND_FOOTS"), 0);
  }
}

}
