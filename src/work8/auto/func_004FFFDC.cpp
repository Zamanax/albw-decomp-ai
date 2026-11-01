#include "../../../src/work7/gpt15/range.h"
struct Child{u32 word;u8 active;};
struct Sub400{u8 pad[0x174];f32 f;};
struct Sub500{u8 pad[8];s16 life;u8 pad2[6];Child*child;};
struct Sub800{u8 pad[0xbc];u8 st;};
struct S{u8 pad0[0x500];Sub500 m500;u8 pad1[0x800-0x514];Sub800 m800;};
extern void func_0066B070(void*, s32);
void func_004FFFDC(S*p){
  if(p->m500.child->active){
    Sub400*s=(Sub400*)((u8*)p+0x400);
    f32 k=0.1f; f32 t=-s->f; s->f = s->f + t*k;
    return;
  }
  Sub500*q=&p->m500; Sub800*r=&p->m800;
  func_0066B070(&r->st, q->life<=0?3:0);
}
