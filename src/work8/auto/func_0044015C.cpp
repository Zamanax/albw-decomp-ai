#include "../../work7/gpt19/range.h"
extern "C" void func_00231448(Ctrl231*);
extern "C" void func_002317C0(Ctrl231*,f32);
void Ctrl231::init(void*p,s16 i,s16 k){owner=p;index=i;kind=k;}
struct Owner { u8 data[0x1C]; void* context; u8 gap[0x134-0x20]; Ctrl231 c[3]; };
extern "C" void func_0044015C(Owner*s){
  s->c[0].init(s->context,5,2);
  func_002317C0(&s->c[0],1.f);
  s->c[1].init(s->context,6,2);
  func_002317C0(&s->c[1],1.f);
  func_00231448(&s->c[2]);
}
