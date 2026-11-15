extern "C" char* data_007124F0;
extern "C" unsigned int func_00111A64(void*);
static inline unsigned int below(void* r, unsigned int n){
  return (unsigned int)(((unsigned long long)func_00111A64(r)*n)>>32);
}
extern "C" void func_00314B64(char* p){
  unsigned int a = below(data_007124F0+0x660, 0xb60b60u);
  *reinterpret_cast<unsigned int*>(p+0x990) = a + 0xb60b60u;
  unsigned int b = below(data_007124F0+0x660, 200u);
  *reinterpret_cast<unsigned short*>(p+0x994) = (unsigned short)(b + 200u);
}
