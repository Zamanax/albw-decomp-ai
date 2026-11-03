typedef unsigned char u8;
typedef int s32;
typedef float f32;
struct CurveHeader22{u8 unknown[3];u8 count;};
f32 func_0068A244(CurveHeader22*h,const f32*p,f32 t){
s32 n=(s32)h->count/3;
s32 last=(n-1)*3;
if(p[0]>=t)return p[1];
if(p[last]<=t)return p[last+1];
for(s32 i=0;i<n;++i){
s32 k=i*3;
if(p[k+3]>t){
f32 dx=p[k+3]-p[k];
f32 u=(t-p[k])/dx;
f32 h00=2.0f*u*u*u - 3.0f*u*u + 1.0f;
f32 h01=-2.0f*u*u*u + 3.0f*u*u;
f32 h10=(u*u*u - 2.0f*u*u + u)*dx;
f32 h11=(u*u*u - u*u)*dx;
return p[k+1]*h00 + p[k+4]*h01 + p[k+2]*h10 + p[k+5]*h11;
}
}
return 0.0f;
}
