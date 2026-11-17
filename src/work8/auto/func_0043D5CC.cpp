#include "../../work7/gpt27/range.h"
struct Obj43D5{u8 pad[0x1c];void*owner;u8 pad20[0xc8-0x20];Ctrl231 ctrl;u8 pad_d4[0x176-0xd4];u8 flags;};extern "C" void func_00231448(Ctrl231*);extern "C" void func_002317C0(Ctrl231*,f32);
void Ctrl231::init(void*p,s16 i,s16 k){owner=p;index=i;kind=k;}
void func_0043D5CC(Obj43D5*p){if((s32)(p->flags<<29)>=0){func_00231448(&p->ctrl);p->ctrl.init(p->owner,5,0);func_002317C0(&p->ctrl,1.0f);p->flags|=4;}}
