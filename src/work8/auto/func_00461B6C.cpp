#include "../../work7/gpt17/range.h"
struct Control {u16 current,max;u32 other,param;};
struct Obj {u8 pad[0xf];u8 m0f;u8 pad10[0x1c-0x10];u32 param;u8 pad20[0x38-0x20];Control ctl;u8 pad44[0x99-0x44];u8 m99;u8 m9a;u8 pad9b[0x9c-0x9b];u32 m9c;};
extern void func_00231448(Control*);extern void func_00231524(Control*);
void configure(Control*c,u16 current,u16 max,u32 param){c->param=param;c->max=max;c->current=current;}
void f_00461B6C(Obj*p){p->m0f=0x69;func_00231448(&p->ctl);configure(&p->ctl,0,2,p->param);func_00231524(&p->ctl);p->m9c=0;p->m99=0;p->m9a=0;}
