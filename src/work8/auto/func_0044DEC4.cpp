typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
struct Control {u16 current,max;u32 other,param;};
struct Obj {u8 pad[0x1c];u32 param;u8 pad20[0x74-0x20];Control ctl;u8 pad80[0x8c-0x80];Control sub[3];};
extern void func_00231448(Control*);
extern void func_002317C0(Control*,f32);
void configure(Control*c,u16 max,u16 current,u32 param){c->param=param;c->max=max;c->current=current;func_002317C0(c,1.f);}
void f_0044DEC4(Obj*p){
 func_00231448(&p->sub[1]);
 func_00231448(&p->sub[2]);
 func_00231448(&p->sub[0]);
 configure(&p->ctl,6,0,p->param);
}
