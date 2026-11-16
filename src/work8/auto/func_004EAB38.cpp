typedef unsigned int u32;
typedef unsigned char u8;
#pragma diag_suppress 513,144,167,147,120,191,1293,174,177,550,940,1,186,111,68,1296,230,1295,2523
#pragma diag_warning 188

class SafeString_006F5988 {
public:
  SafeString_006F5988(const char* s) : mStringTop(s) {}
  virtual void assureTerminationImpl_() const;
  const char* mStringTop;
};

struct Self_004EAB38 {
  u8 pad0[0x40];
  void* m40;
  u8 pad1[8];
  void* m4c;
};

extern "C" {
void func_0025BDA4(void*, const SafeString_006F5988&);
void func_00295A8C(void*);

void func_004EAB38(Self_004EAB38* self, u32 a1)
{
  if (a1 != 0) {
    func_0025BDA4(self->m40, SafeString_006F5988("SE_S_READ_RIDDLE_S"));
  } else {
    func_0025BDA4(self->m40, SafeString_006F5988("SE_S_READ_RIDDLE"));
  }
  func_00295A8C(self->m4c);
}
}
