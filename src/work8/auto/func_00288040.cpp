#include "../../work7/gpt16/range.h"
struct Obj1D68 : ActorMotion { u8 pad3e8[0x44]; u16 id; u8 pad42e[0x534 - 0x42e]; Timer3 timer; };
void func_00288040(Obj1D68*p){p->velocity.x=0.0f;p->velocity.z=0.0f;p->velocity.y=-0.175f;p->id=0;p->timer.start(3);}
