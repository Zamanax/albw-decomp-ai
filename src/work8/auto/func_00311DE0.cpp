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
struct NpcExec30 {u8 pad0[0x78c];void*child;u8 gap[0x960-0x790];NpcExecState30 state;u8 gap2[0xa3b-0x960-sizeof(NpcExecState30)];u8 flag;};
extern void func_004BC8D8(NpcExec30*);
extern void func_00652D04(NpcExec30*);
extern const float bss_0077EF84[3];
extern void func_00151150(void*,const float*);
void func_00311DE0(NpcExec30*p){
    NpcExecState30* s=&p->state;
    s->execute();
    func_004BC8D8(p);
    if(p->flag&&p->child)func_00151150(p->child,bss_0077EF84);
    func_00652D04(p);
}
