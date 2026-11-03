typedef unsigned int u32; typedef signed char s8; typedef unsigned char u8; typedef float f32;
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
struct NpcExec30 {
    u8 pad0[0x47c]; void* m47c; u8 p480[0x4c0-0x480];
    NpcExecState30 state;
    u8 p4e4[0x518-0x4e4]; u8 m518;
    void func_001E410C();
};
extern "C" void func_004CEAF0(void*);
extern "C" void func_00332970(void*, u32);
extern "C" void func_00332AB8(void*);
extern "C" void func_00332BFC(void*);
extern u32 data_00693328;
void target(NpcExec30* p){
    if (!p->m518) {
        func_00332970(p, data_00693328);
        func_00332AB8(p);
        func_00332BFC(p);
        p->m518 = 1;
    }
    p->state.execute();
    p->func_001E410C();
    func_004CEAF0(p->m47c);
}
