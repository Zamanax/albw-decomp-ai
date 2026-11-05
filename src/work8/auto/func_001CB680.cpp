typedef unsigned int u32;typedef signed char s8;typedef unsigned char u8;typedef int s32;typedef float f32;
struct ExecOwner30;
typedef void(ExecOwner30::*ExecMethod30)();
struct Timeline30 {void func_00352210(bool,f32);};
struct NpcExecState30 {
    u32 frame;s8 current,previous;u8 pad6[2];u32 count;void* names;
    Timeline30* timeline;ExecOwner30*owner;ExecMethod30*enter;ExecMethod30*exec;ExecMethod30*exit;
    void execute(){
        (owner->*exec[current])();
        ++frame;
        if(timeline)timeline->func_00352210(true,static_cast<f32>(frame));
    }
};
struct Obj70FB60 {u32 func_0053F9B8();};
extern Obj70FB60* data_0070FB60;
struct NpcExec30 {
    u8 pad0[0x838];f32 f838;u8 pad83c[0x960-0x83c];NpcExecState30 state;
    void func_004BCAA8();void func_004BC8D8();void func_006177C0(s32,bool);
};
void target(NpcExec30*p){
    p->f838=0.8f;
    NpcExecState30* s=&p->state;
    s->execute();
    if(data_0070FB60->func_0053F9B8()==0){
        if(p->state.current!=5&&p->state.current!=6){
            if(p->state.current==0)p->func_006177C0(5,false);
            else p->func_006177C0(6,false);
        }
    }
    p->func_004BCAA8();
    p->func_004BC8D8();
}
