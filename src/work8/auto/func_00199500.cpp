#include "../../work7/gpt27/range.h"
struct Obj199500{u8 pad[0x1c];void*owner;u8 pad20[0x68-0x20];Ctrl231 ctrl;u8 pad74[0x79-0x74];u8 flags;};
extern "C" void func_00231448(Ctrl231*);extern "C" void func_002317C0(Ctrl231*,f32);
void func_00199500(Obj199500*p){
 if(p->flags & 2) return;
 func_00231448(&p->ctrl);
 Ctrl231* c=&p->ctrl;
 c->owner=p->owner;
 c->index=3;
 c->kind=0;
 func_002317C0(&p->ctrl,1.0f);
 p->flags |= 2;
}
