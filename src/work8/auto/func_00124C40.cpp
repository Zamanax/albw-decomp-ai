struct Actor;
struct Timeline{void func_00352210(bool,float);};
struct SM{
typedef void(Actor::*Func)();
unsigned int counter; signed char cur,next; unsigned char num; char pad[9];
Timeline* timeline; Actor* owner; Func* enter; Func* exec; Func* exit;
void func_0065650C(int);
void execute(){(owner->*exec[cur])();++counter;if(timeline)timeline->func_00352210(true,(float)counter);}
};
struct Pair{unsigned int a,b;};
struct Actor{
char p0[0x3e0]; float vy;
char p3e4[0x8bc-0x3e4];
SM state;
char p8e0[0x944-0x8e0];
Pair m944;
char p94c[0x959-0x94c];
unsigned char m959;
};
bool func_004F70A8(Actor*);
bool func_004F8998(Actor*,int,int);
void func_004F48F0(Actor*);
void func_004F5588(Actor*);
void func_004F5BD8(Actor*,int,int);
float func_004F898C();
void func_004FB0D8(Actor*,float*);
void func_00124C40(Actor*o){
if(o->m959){
Pair c=o->m944;
if(c.a<c.b)o->m944.a=c.a+1;
else o->m959=0;
}
if(func_004F70A8(o)){
if(o->state.cur!=8&&o->state.cur!=9&&func_004F8998(o,0,0))o->state.func_0065650C(8);
o->state.execute();
o->vy=-func_004F898C();
func_004FB0D8(o,&o->vy);
func_004F48F0(o);
func_004F5588(o);
func_004F5BD8(o,0,0);
}}
