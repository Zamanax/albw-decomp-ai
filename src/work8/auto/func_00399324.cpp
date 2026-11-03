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
extern void* data_00709D28;
extern void* data_00711F50;
extern void func_004A8BFC(void*, void*, u32);
extern int func_004EABB8(void*, const SafeString_006F5980&, u32);
void func_00399324(unsigned a0)
{
  *(unsigned char*)((char*)a0 + 0x38) = 0;
  func_004A8BFC(data_00709D28, (char*)a0 + 0x98, 3);
  if ((int)*(signed char*)((char*)a0 + 0xC) < 2) goto L2;
  func_004EABB8(data_00711F50, SafeString_006F5980("SE_PL_Net_SWING_Lv2"), 0);
  return;
L2:;
  func_004EABB8(data_00711F50, SafeString_006F5980("SE_PL_Net_SWING"), 0);
  return;
}

}
