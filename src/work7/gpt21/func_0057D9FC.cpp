#include "range.h"

#include "sead_math.h"

struct S57D { char pad[0x34]; Mtx34 matrix; };
void func_001151EC(Mtx34*,const Mtx34*);
void f_57D9FC(const S57D* p,Mtx34* out) { Mtx34* d=out; const Mtx34* s=&p->matrix; func_001151EC(d,s); }
