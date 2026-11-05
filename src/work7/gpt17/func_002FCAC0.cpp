#include "range.h"

#include "sead_math.h"

struct Obj2FCA {u8 pad[0x10c];Vec3 pos;void f(const Vec3&,const Matrix34&,s32);void func_00165E7C(const Vec3&,const Matrix34&,s32);};
void Obj2FCA::f(const Vec3& v,const Matrix34& m,s32 b){pos=v;func_00165E7C(v,m,b);}
