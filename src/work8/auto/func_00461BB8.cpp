#include "../../work7/gpt27/range.h"
extern "C" void func_00231448(void*);
extern "C" void func_002317C0(void*, float);
extern "C" void func_0051B698(void*);
extern void* data_007142C8;
struct Obj4895 {u8 pad[0x1c]; void* owner; u8 pad20[0x38-0x20]; Ctrl231 ctrl; u8 pad44[0x48-0x44]; };
void Ctrl231::init(void*p,s16 i,s16 k){owner=p;index=i;kind=k;}
extern "C" void func_00461BB8(Obj4895* p){
 func_00231448(&p->ctrl);
 p->ctrl.init(p->owner,6,0);
 func_002317C0(&p->ctrl,1.0f);
 func_002317C0(&p->pad44,1.0f);
 func_0051B698(data_007142C8);
}
