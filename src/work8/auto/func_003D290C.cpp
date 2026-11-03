typedef unsigned int u32;
struct G{u32 a,b;void*child;};
extern G data_007158E8;
extern const u32 ro_006B4788;
extern u32 func_003D2D40(void*,u32,void*,u32);
static u32 dispatch(const G*g,void*p,u32 n,u32 error){void*m=g->child;u32 r=error;if(m)r=func_003D2D40(m,ro_006B4788,p,n);return r;}
u32 f(void*p,u32 n){return dispatch(&data_007158E8,p,n,0xc8a0a7f8);}
