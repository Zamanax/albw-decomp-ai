#include "albw_types.h"
#include "sead_container.h"

struct Elem14E670;

struct Owner14E670 {
  u8 pad0[0x3f4];
  void* mObj;
  OffsetList<Elem14E670> mList;
};

extern "C" {
extern void* data_00711F50;
void* func_00297674(void* d, Owner14E670* o);
void func_00297574(void* d, void* o);
u32 func_0019A014(void* p, u32 a);
void func_0019A4C4(void* p, void* b);
void func_001DF8F8(u32 a, u32 b);
void func_0025B6A8(u32 h, u32 o);
}

extern "C" u32 func_0014E670(Owner14E670* self, u32 a1, u32 a2, u32 a3, u32 a4) {
  u32 ret = 0;
  u32 fresh = 0;
  if (self->mObj == 0) {
    self->mObj = func_00297674(data_00711F50, self);
    if (self->mObj != 0) {
      func_0019A4C4(self->mObj, (char*)self + 0x3d0);
      fresh = 1;
    }
  }
  if (self->mObj != 0) {
    u32 r = func_0019A014(self->mObj, a1);
    if (r != 0) {
      if (fresh) {
        OffsetList<Elem14E670>* l = &self->mList;
        l->pushBack((Elem14E670*)self->mObj);
      }
      if (a3 != 0) func_001DF8F8(r, a2);
      if (a4 != 0) func_0025B6A8(a4, r);
      ret = 1;
    } else if (fresh) {
      func_00297574(data_00711F50, self->mObj);
      self->mObj = 0;
    }
  }
  return ret;
}
