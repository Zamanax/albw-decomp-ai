typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
struct Child{u8 pad[13];s8 state;u8 pending;};
struct S{u8 pad0[0x158];u8 m158[4];s8 m15c;u8 pad1[0xaf];struct Child*c0,*c1,*c2;};
extern int func_001B6CE4(void);
extern void func_0066CC58(void*,int);
extern void func_0012C718(struct Child*);
static inline int busy(struct Child*p){return p->state!=0||p->pending!=0;}
static inline void finish(struct Child*p){if(p->state==3&&p->pending==3)func_0012C718(p);}
u32 func_00446D0C(struct S*s){
u32 r=func_001B6CE4();
if(s->m15c==1){func_0066CC58(s->m158,2);r=0;}
else if(s->m15c==3){func_0066CC58(s->m158,0);r=0;}
if(busy(s->c0)){finish(s->c0);r=0;}
if(busy(s->c1)){finish(s->c1);r=0;}
if(busy(s->c2)){finish(s->c2);r=0;}
return r;
}
