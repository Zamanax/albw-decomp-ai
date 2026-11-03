typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
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
struct Pair50c { u32 a; u32 b; };
struct NpcExec30 {
    u8 pad0[0x47c]; void* m47c; u8 p480[0x4c0-0x480];
    NpcExecState30 state;
    u8 p4e4[0x508-0x4e4]; void* m508; Pair50c pr; u8 p514[0x51d-0x514]; u8 m51d;
    void func_001E410C();
};
extern "C" void func_004CEAF0(void*);
extern "C" void func_00165E28(void*, u32);
extern u8 data_00709700[];
void target(NpcExec30* p){
    p->state.execute();
    p->func_001E410C();
    func_004CEAF0(p->m47c);
    if (p->m51d) {
        Pair50c q = p->pr;
        if (q.b > q.a) { p->pr.a = q.a + 1; }
        else {
            func_00165E28(p->m508, *(u16*)(data_00709700 + 0x2a));
            p->m51d = 0;
        }
    }
}
