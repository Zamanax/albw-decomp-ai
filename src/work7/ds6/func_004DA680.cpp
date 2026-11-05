typedef unsigned char u8;
typedef unsigned int u32;


#include "sead_string.h"
namespace sead {

}

struct Res7A0 {
  u32 find(const sead::SafeString& name) const;
};

struct Obj {
  u8 p0[0x7a0];
  Res7A0* m7a0;
  u8 p1[0x840 - 0x7a4];
  u32 m840;
  u32 m844;
};

void func_004DA680(Obj* self) {
  self->m840 = self->m7a0->find("head");
  self->m844 = self->m7a0->find("chest");
}
