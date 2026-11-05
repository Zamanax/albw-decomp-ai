typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef float f32;
extern "C" void func_00169A80(void*);
extern "C" void func_00168E9C(void*, void*, u32);
extern "C" void func_004CEAF0(void*);
struct SmOwner_; typedef void (SmOwner_::*SmFunc)();
struct SmTimeline { void func_00352210(bool b, float frame); };

#include "statemgr.h"
typedef StateMgrT<SmOwner_> StateMgr;

struct Obj30 { u8 p0[0x30]; u8 b30; };
struct T {
  u8 p0[0x40c];
  Obj30* m40c; void* m410; void* m414; u8 p418[4];
  StateMgr sm;
};
void func_0024E934(T* self) {
  if (self->m40c && self->m40c->b30) {
    if (self->m410) { func_00169A80(self->m410); func_00168E9C(self->m410, self->m40c, 0); }
    if (self->m414) { func_00169A80(self->m414); func_00168E9C(self->m414, self->m40c, 0); }
    func_004CEAF0(self->m40c);
  }
  self->sm.execute();
}
