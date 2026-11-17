extern unsigned char* data_007142C8;
extern "C" void func_0066BFFC(void* p, unsigned int v);
extern "C" void func_0066E7A0(void* p, signed char s) __attribute__((notailcall));
extern "C" void func_0045FCA4(void* p);

extern "C" void func_0047A1E0(unsigned char* self) {
  unsigned char** po = (unsigned char**)(self + 0x1f8);
  unsigned char* o = *po;
  unsigned char* cur = *(unsigned char**)((unsigned char*)data_007142C8 + 0xe8);
  if (cur == 0 || cur[0x78] == 3) {
    if (o[0x3c] == 3) {
      func_0066BFFC(o + 0x38, 5);
    }
    func_0066E7A0(self + 0xf0, 9);
    return;
  }
  if ((*(unsigned short*)(*(unsigned char**)(self + 0x14) + 0x16) & 4) != 0 || o[0x3c] == 5) {
    func_0045FCA4(cur);
  }
}
