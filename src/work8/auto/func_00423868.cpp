typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
struct BitFlag16 {
 u16 v;
 BitFlag16(){}
 BitFlag16(u16 n):v(n){}
 void set(u16 mask){v|=mask;}
 void reset(u16 mask){*this=BitFlag16(v&~mask);}
};
struct Child {u8 pad[0x16];BitFlag16 flags;};
struct Control {u16 current,max;u32 other,param;};
struct Obj {u8 pad[0x14];Child*child;u8 pad18[0x1c-0x18];u32 param;u8 pad20[0x60-0x20];u8 x60[0xb0-0x60];Control ctl;u8 pad44[0x98-0x44];u8 m98;};
extern void func_002C00A8(Child*);
extern void func_0031B348(void*,u32);
extern void func_002317C0(Control*,f32);
void f_00423868(Obj*p){func_002C00A8(p->child);Child*c=p->child;c->flags.reset(0x40);func_0031B348(p->x60,0);Control*k=&p->ctl;k->param=p->param;k->max=7;k->current=0;func_002317C0(k,1.f);}
