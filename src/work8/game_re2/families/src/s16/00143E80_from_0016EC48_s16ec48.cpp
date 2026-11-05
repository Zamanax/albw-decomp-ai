typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef float f32;
struct SmOwner_; typedef void (SmOwner_::*SmFunc)();
struct SmTimeline { void func_00352210(bool b, float frame); };

#include "statemgr.h"
typedef StateMgrT<SmOwner_> StateMgr;

struct T { u8 p0[0x424]; StateMgr sm; };
void func_00143E80(T* self) { self->sm.execute(); }
