#include "../../work7/gpt19/range.h"
struct B{char pad[0x18];u32 a,b,c;f32 value;u8 yes,no;};
extern "C" void* func_0041D840(void*);
static B* init(B* p){p->a=0;p->b=0;p->c=0;p->value=.5f;p->yes=1;p->no=0;return p;}
static B* g3(u32* q){ B* p = (B*)func_0041D840(&q[2]); if (p == 0) return 0; return init(p); }
extern "C" void* f_0058E99C(u32* s, u32 kind){ u32* q = s - 1; return kind == 0x2c ? g3(q) : 0; }
