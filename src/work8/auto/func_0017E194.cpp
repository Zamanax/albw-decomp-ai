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
struct NpcExec30 {u8 pad0[0x960];NpcExecState30 state;void func_004C00F4();void func_004BC8D8();};
void target(NpcExec30*p){p->state.execute();p->func_004C00F4();p->func_004BC8D8();}
