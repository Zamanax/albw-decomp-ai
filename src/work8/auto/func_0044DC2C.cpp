typedef unsigned int u32;typedef unsigned short u16;typedef float f32;
extern "C" void func_00231448(void*);
extern "C" void func_002317C0(void*,f32);
extern "C" void func_002313DC(void*);
extern "C" void func_0044E4F8(void*,f32*);
void func_0044DC2C(char* p){
  func_00231448(p+0x98);
  u32* d=(u32*)(p+0x7c);
  u32* s=(u32*)(p+0x1c);
  *d=*s;
  *(u16*)(p+0x76)=8;
  *(u16*)(p+0x74)=0;
  func_002317C0(p+0x74,1.0f);
  char* q=*(char**)(p+0x12c);
  if(q!=0){
    func_00231448(q+0x128);
    func_002317C0(q+0x134,1.0f);
    func_002313DC(q+0x14c);
  }
  f32 arr[2];
  arr[0]=-134.0f;
  arr[1]=-41.0f;
  func_0044E4F8(p,arr);
}
