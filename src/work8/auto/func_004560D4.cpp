typedef unsigned char u8; typedef short s16; typedef unsigned short u16; typedef unsigned int u32;
struct Ctrl231 {s16 kind,index;u32 frame;void* owner;void init(void*,s16,s16);};
struct Blk231 {u8 pad0[4];u32 f4;u8 pad8[0x16-8];u16 flags;};
struct Obj4895 {u8 pad[0x14];Blk231* blk;u8 pad18[0x1c-0x18];void* owner;u8 pad20[0x38-0x20];Ctrl231 ctrl;u8 pad48[0x9c-0x44];u32 f9c;};
extern "C" void func_00231448(Ctrl231*);extern "C" void func_002313DC(Ctrl231*);extern "C" void func_002C00A8(Blk231*);
void Ctrl231::init(void*p,s16 i,s16 k){owner=p;index=i;kind=k;}
static void change16(u16* f,u16 mask,bool on){ if(on) *f|=mask; else *f&=~mask; }
void func_004560D4(Obj4895*p){
 func_00231448(&p->ctrl);
 s16 kind=0; s16 idx=4;
 p->ctrl.init(p->owner,idx,kind);
 func_002313DC(&p->ctrl);
 Blk231* b=p->blk;
 u32 v=p->f9c;
 b->f4=v;
 bool on=v!=0;
 change16(&b->flags,0x40,on);
 func_002C00A8(p->blk);
}
