#include "../../../shared/include/albw_types.h"
struct S{s32 a;s32 b;};
bool f(S*p,s32 x,s32 y){ if(x<0) return false; s32 a=p->a; return p->b>=a+y && a>=x; }
