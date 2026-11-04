#include "../../work7/gpt17/range.h"
struct Cnt{u32 num,capacity;};
struct Sub{u8 pad[0x68];Cnt counts;u8 pad2[8];u32 a;};
struct Obj{u8 pad[0x200];Sub s;u32 b;};
bool f_00542AB4(Obj*p,u32*o1,u32*o2){Cnt c=p->s.counts;if(c.num<c.capacity){Sub*s=&p->s;*o1=p->b;*o2=s->a;return true;}return false;}
