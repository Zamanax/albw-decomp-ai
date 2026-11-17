typedef unsigned int u32;
extern void func_004FCD5C(char* o, u32 a);
extern void func_004FCDF4(char* o, u32 a);
extern void func_004FD038(char* o, u32 a);
extern void func_004CF478(void* p, u32 a, u32 b);
extern void func_004FABDC(char* o, u32 a, u32 b, u32 c);
typedef struct Obj { char pad0[0x59C]; u32 flags; char pad1[0x8EC - 0x5A0]; void* ptr8ec; } Obj;
static inline void clr(Obj* p, u32 m) { p->flags &= ~m; }

void func_00267A24(Obj* p)
{
    clr(p, 1u);
    func_004FCD5C((char*)p + 0x400 + 0x1A8, 0);
    func_004CF478(*(void**)((char*)p->ptr8ec + 0x18), 0, 0);
    clr(p, 2u);
    func_004FCDF4((char*)p + 0x400 + 0x1A8, 0);
    func_004FABDC((char*)p, 0, 0xFFFFFFFFu, 0);
    clr(p, 4u);
    func_004FD038((char*)p + 0x400 + 0x1A8, 0);
    clr(p, 0x80u);
}
