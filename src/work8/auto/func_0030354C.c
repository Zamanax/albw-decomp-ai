typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
extern void* data_00711F50;
extern u8 data_00708C84[];
extern void* data_0070C8E0;
extern void func_004EAB38(void*, u32);
extern void func_00165E28(void*, u32);
extern u16 func_00581D60(void*);

void func_0030354C(u8* p)
{
  if (*(u32*)(p + 0x498) == 0xf) {
    func_004EAB38(data_00711F50, 0);
  }
  if (*(u32*)(p + 0x498) == 0x7d) {
    func_00165E28(*(void**)(p + 0x4cc), *(u16*)(data_00708C84 + 0x2a));
  }
  u16 v = func_00581D60(data_0070C8E0);
  if (*(u32*)(p + 0x4e4) != v) {
    u32 cur = *(u32*)(p + 0x4d8);
    u32 max = *(u32*)(p + 0x4dc);
    if (cur < max) {
      *(u32*)(p + 0x4d8) = cur + 1;
    } else {
      *(u8*)(p + 0x2d7) = 1;
    }
  }
}
