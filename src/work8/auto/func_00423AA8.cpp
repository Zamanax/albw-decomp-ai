#include "../../work7/gpt27/range.h"
extern void func_002317C0(void*,f32);
extern void func_0051B6D0(void*);
extern void* data_007142C8;
struct Obj{u8 pad[28];void* owner;u8 pad2[144];Ctrl231 ctrl;};
void Ctrl231::init(void*o,s16 i,s16 k){owner=o;index=i;kind=k;}
void func_00423AA8(Obj*p){p->ctrl.init(p->owner,5,0);func_002317C0(&p->ctrl,1.0f);func_0051B6D0(data_007142C8);}
