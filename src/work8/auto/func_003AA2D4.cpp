typedef unsigned char u8;
typedef unsigned int u32;

struct Q { virtual void f0(void* p, u32 z); };
struct Sub134 { char pad0[0x44]; u32 m44; Q* m48; char pad4c[4]; };
struct Obj { char pad0[0x134]; Sub134 m134; };
struct Glob { char pad0[0x66]; u8 m66; };
extern Glob* data_00709DF8;

void func_0010961C(void* p);
void func_00109698(void* p);

static inline void finishSub(Sub134* p, u32 z) {
    func_0010961C(p);
    Q* q = p->m48;
    if (q != 0) {
        q->f0(p, z);
    }
    p->m44 = z;
}

void func_003AA2D4(Obj* self) {
    Sub134* p = &self->m134;
    finishSub(p, 0);
    func_00109698(p);
    if (data_00709DF8) data_00709DF8->m66 = 0;
}
