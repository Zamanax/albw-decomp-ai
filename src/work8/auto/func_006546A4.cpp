#include "../../work7/gpt24/range.h"
extern GameActors24* data_00706E20;
extern void func_004F8638(void*,s32);
struct Node6546{char pad[0x10];u32 v;};
struct Mid6546{char pad[0x3e8];Node6546* node;};
struct Obj6546{char pad[0x2cc];u32 m2cc;char pad2d0[0x3dc-0x2d0];Vec3_24 velocity;};
extern "C" void target(Obj6546*p){
    Mid6546* m=(Mid6546*)((char*)data_00706E20+0x3D800);
    Node6546** pp=&m->node;
    Node6546* n=*pp;
    u32& s=n->v;
    if(s){if(s==p->m2cc)s=0;}
    p->velocity.x=0.0f;p->velocity.y=0.0f;p->velocity.z=0.0f;
    func_004F8638(p,-1);
}
