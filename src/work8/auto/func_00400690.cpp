#include "albw_types.h"
struct Item;
struct Container {
  virtual void vfn0();
  virtual void vfn1();
  virtual void vfn2();
  virtual void vfn3();
  virtual void vfn4();
  virtual void vfn5();
  virtual void vfn6();
  virtual void vfn7();
  virtual void vfn8();
  virtual u32 count();
  virtual Item* at(u32 i);
};
static inline bool nameEq(const s8* p, const s8* b) {
  for (s32 j = 0; j < 0x1c; ++j) {
    s8 x = p[j];
    s8 y = b[j];
    if (x != y) return false;
    if (x == 0) return true;
  }
  return true;
}
Item* target(Container* a, const s8* b) {
  u32 n = a->count();
  for (u32 i = 0; i < n; ++i) {
    Item* e = a->at(i);
    if (e) {
      const s8* p = (const s8*)e + 0x81;
      if (nameEq(p, b)) return e;
    }
  }
  return 0;
}
