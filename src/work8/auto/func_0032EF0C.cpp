#include "albw_types.h"
#include "vec3.h"
extern void func_00115C70(Vec3*,const Vec3&,const Vec3&);
extern s32 func_0068C690(const Vec3&);
extern void func_004D80A4(Vec3*,f32,u32);
Vec3 func_0032EF0C(const Vec3& a,const Vec3& b){Vec3 v;func_00115C70(&v,b,a);f32 x=v.x;f32 z=v.z;Vec3 t;t.x=x;t.z=z;t.y=0.f;s32 ang=func_0068C690(t);func_004D80A4(&t,1.0f,ang+0x40000000);return Vec3(t.x,0.f,t.z);}
