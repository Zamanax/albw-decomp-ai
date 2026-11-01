struct Actor;
struct Timeline{void func_00352210(bool,float);};
struct SM{
typedef void(Actor::*Func)();
unsigned int counter; signed char cur,next; unsigned char num; char pad[9];
Timeline* timeline; Actor* owner; Func* enter; Func* exec; Func* exit;
void func_006563C8(int);
void execute(){(owner->*exec[cur])();++counter;if(timeline)timeline->func_00352210(true,(float)counter);}
};
struct Actor{char p[0x8bc];SM state;};
bool func_004F70A8(Actor*);
bool func_004F8998(Actor*,int,int);
void func_004F48F0(Actor*);
void func_004F5588(Actor*);
void func_004F5BD8(Actor*,int,int);
float func_004F898C();
void func_004F8964(float*,bool,float);
void func_004FB0D8(Actor*,float*);
void func_00123070(Actor*o){
if(func_004F70A8(o)){
if(o->state.cur!=1&&o->state.cur!=2&&func_004F8998(o,0,0))o->state.func_006563C8(1);
o->state.execute();
float g=func_004F898C();
func_004F8964((float*)((char*)o+0x3e0),true,g);
func_004FB0D8(o,(float*)((char*)o+0x3e0));
func_004F48F0(o);
func_004F5588(o);
func_004F5BD8(o,0,0);
}}
